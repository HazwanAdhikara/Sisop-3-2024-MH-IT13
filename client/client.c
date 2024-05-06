#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define MAX_BUFFER_SIZE 1024

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[MAX_BUFFER_SIZE] = {0};
    char command[MAX_BUFFER_SIZE] = {0};

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }

    // Connect to server
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    // Send commands to server and receive responses
    while (1) {
        printf("Enter command (or 'exit' to quit): ");
        fgets(command, MAX_BUFFER_SIZE, stdin);

        // Check for exit command
        if (strcmp(command, "exit\n") == 0) {
            send(sock, command, strlen(command), 0);
            break;
        }

        send(sock, command, strlen(command), 0);

        // Receive response from server
        read(sock, buffer, MAX_BUFFER_SIZE);
        printf("Server response: %s\n", buffer);
        memset(buffer, 0, MAX_BUFFER_SIZE);
    }

    close(sock);

    return 0;
}
