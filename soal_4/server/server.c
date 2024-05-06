#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <time.h>

#define PORT 8080
#define MAX_BUFFER_SIZE 1024
#define MAX_CHANGE_LOG_SIZE 1024

void write_to_change_log(const char* type, const char* message) {
    time_t now;
    struct tm* local_time;
    char change_log_entry[MAX_CHANGE_LOG_SIZE];

    // Get current time
    now = time(NULL);
    local_time = localtime(&now);

    // Format log entry
    strftime(change_log_entry, MAX_CHANGE_LOG_SIZE, "[%d/%m/%y] [%H:%M:%S]", local_time);

    // Write to change log file
    FILE* fp = fopen("change.log", "a");
    if (fp != NULL) {
        fprintf(fp, "%s [%s] %s\n", change_log_entry, type, message);
        fclose(fp);
    }
}

void handle_client_request(int client_socket) {
    char buffer[MAX_BUFFER_SIZE] = {0};
    char response[MAX_BUFFER_SIZE] = {0};
    char command[MAX_BUFFER_SIZE] = {0};
    char args[MAX_BUFFER_SIZE] = {0};

    // Read client command and arguments
    read(client_socket, buffer, MAX_BUFFER_SIZE);
    sscanf(buffer, "%s %[^\n]", command, args);

    // Perform action based on command
    if (strcmp(command, "list_all") == 0) {
        // Read data from myanimelist.csv and send to client
        FILE* fp = fopen("myanimelist.csv", "r");
        if (fp != NULL) {
            char line[MAX_BUFFER_SIZE];
            while (fgets(line, sizeof(line), fp) != NULL) {
                strcat(response, line);
            }
            fclose(fp);
        } else {
            strcpy(response, "Error reading myanimelist.csv");
        }
    } else if (strcmp(command, "list_genre") == 0) {
        // Read genre from arguments and send titles with matching genre
        char genre[MAX_BUFFER_SIZE];
        sscanf(args, "%s", genre);

        FILE* fp = fopen("myanimelist.csv", "r");
        if (fp != NULL) {
            char line[MAX_BUFFER_SIZE];
            while (fgets(line, sizeof(line), fp) != NULL) {
                if (strstr(line, genre) != NULL) {
                    strcat(response, line);
                }
            }
            fclose(fp);
        } else {
            strcpy(response, "Error reading myanimelist.csv");
        }
    } else if (strcmp(command, "list_day") == 0) {
        // Read day from arguments and send titles with matching day
        char day[MAX_BUFFER_SIZE];
        sscanf(args, "%s", day);

        FILE* fp = fopen("myanimelist.csv", "r");
        if (fp != NULL) {
            char line[MAX_BUFFER_SIZE];
            while (fgets(line, sizeof(line), fp) != NULL) {
                char* token = strtok(line, ",");
                if (strcmp(token, day) == 0) {
                    strcat(response, line);
                }
            }
            fclose(fp);
        } else {
            strcpy(response, "Error reading myanimelist.csv");
        }
    } else if (strcmp(command, "list_status") == 0) {
        // Read title from arguments and send status of that anime
        char title[MAX_BUFFER_SIZE];
        sscanf(args, "%s", title);

        FILE* fp = fopen("myanimelist.csv", "r");
        if (fp != NULL) {
            char line[MAX_BUFFER_SIZE];
            while (fgets(line, sizeof(line), fp) != NULL) {
                char* token = strtok(line, ",");
                token = strtok(NULL, ",");
                token = strtok(NULL, ",");
                token = strtok(NULL, ",");
                if (strcmp(token, title) == 0) {
                    char* status = strtok(NULL, ",");
                    sprintf(response, "Status of %s: %s", title, status);
                    break;
                }
            }
            fclose(fp);
        } else {
            strcpy(response, "Error reading myanimelist.csv");
        }
    } else if (strcmp(command, "add") == 0) {
        // Add new anime to myanimelist.csv
        FILE* fp = fopen("myanimelist.csv", "a");
        if (fp != NULL) {
            fprintf(fp, "%s\n", args);
            fclose(fp);
            sprintf(response, "Anime '%s' berhasil ditambahkan", args);
            write_to_change_log("ADD", response);
        } else {
            strcpy(response, "Error writing to myanimelist.csv");
        }
    } else if (strcmp(command, "edit") == 0) {
        // Edit an existing anime in myanimelist.csv
        char old_line[MAX_BUFFER_SIZE];
        char new_line[MAX_BUFFER_SIZE];
        sscanf(args, "%[^,],%s", old_line, new_line);

        FILE* fp = fopen("myanimelist.csv", "r+");
        if (fp != NULL) {
            char temp_file[MAX_BUFFER_SIZE] = "temp.csv";
            FILE* temp = fopen(temp_file, "w");
            if (temp != NULL) {
                char line[MAX_BUFFER_SIZE];
                int edited = 0;
                while (fgets(line, sizeof(line), fp) != NULL) {
                    if (strstr(line, old_line) != NULL && !edited) {
                        fprintf(temp, "%s\n", new_line);
                        edited = 1;
                        sprintf(response, "Anime '%s' berhasil diubah menjadi '%s'", old_line, new_line);
                        write_to_change_log("EDIT", response);
                    } else {
                        fputs(line, temp);
                    }
                }
                fclose(temp);
                fclose(fp);
                remove("myanimelist.csv");
                rename(temp_file, "myanimelist.csv");
            } else {
                strcpy(response, "Error creating temporary file");
            }
        } else {
            strcpy(response, "Error opening myanimelist.csv");
        }
    } else if (strcmp(command, "delete") == 0) {
        // Delete an anime from myanimelist.csv
        char title[MAX_BUFFER_SIZE];
        sscanf(args, "%s", title);

        FILE* fp = fopen("myanimelist.csv", "r");
        if (fp != NULL) {
            char temp_file[MAX_BUFFER_SIZE] = "temp.csv";
            FILE* temp = fopen(temp_file, "w");
            if (temp != NULL) {
                char line[MAX_BUFFER_SIZE];
                int deleted = 0;
                while (fgets(line, sizeof(line), fp) != NULL) {
                    char* token = strtok(line, ",");
                    token = strtok(NULL, ",");
                    token = strtok(NULL, ",");
                    token = strtok(NULL, ",");
                    if (strcmp(token, title) !=
                    0) {
                        fputs(line, temp);
                    } else {
                        deleted = 1;
                        sprintf(response, "Anime '%s' berhasil dihapus", title);
                        write_to_change_log("DEL", response);
                    }
                }
                fclose(temp);
                fclose(fp);
                remove("myanimelist.csv");
                rename(temp_file, "myanimelist.csv");
            } else {
                strcpy(response, "Error creating temporary file");
            }
        } else {
            strcpy(response, "Error opening myanimelist.csv");
        }
    } else if (strcmp(command, "exit") == 0) {
        // Close connection with client
        strcpy(response, "Closing connection");
    } else {
        strcpy(response, "Invalid Command");
    }

    // Send response to client
    write(client_socket, response, strlen(response));
}

int main() {
    int server_fd, client_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Create server socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind server socket to port
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server started on port %d\n", PORT);

    // Accept incoming connections and handle requests
    while (1) {
        printf("Waiting for incoming connections...\n");

        if ((client_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
            perror("Accept failed");
            exit(EXIT_FAILURE);
        }

        printf("New client connected\n");

        // Handle client request
        handle_client_request(client_socket);

        // Close the connection with the client
        close(client_socket);
        printf("Client disconnected\n");
    }

    return 0;
}
