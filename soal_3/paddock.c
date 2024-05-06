#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <syslog.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "actions.h"

#define PORT 8081

int main()
{
    pid_t pid, sid;
    pid = fork();

    if (pid < 0)
    {
        exit(EXIT_FAILURE);
    }

    if (pid > 0)
    {
        exit(EXIT_SUCCESS);
    }

    umask(0);

    sid = setsid();
    if (sid < 0)
    {
        exit(EXIT_FAILURE);
    }

    if ((chdir("/")) < 0)
    {
        exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    openlog("paddock", LOG_PID, LOG_DAEMON);
    syslog(LOG_NOTICE, "paddock started");

    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *response;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        syslog(LOG_ERR, "Socket creation failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        syslog(LOG_ERR, "Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0)
    {
        syslog(LOG_ERR, "Listen failed");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
        {
            syslog(LOG_ERR, "Accept failed");
            exit(EXIT_FAILURE);
        }

        read(new_socket, buffer, 1024);
        syslog(LOG_INFO, "Received: %s", buffer);

        char command[50], info[50];
        if (sscanf(buffer, "[%[^]]] : [%[^]]", command, info) == 2)
        {
            if (strcmp(command, "[Driver]") == 0)
            {
                float jarak = atof(info);
                response = gap(jarak);
            }
            else if (strcmp(command, "[Fuel]") == 0)
            {

                int sisaBensin = atoi(info);
                response = fuel(sisaBensin);
            }
            else if (strcmp(command, "[Tire]") == 0)
            {

                int sisaBan = atoi(info);
                response = tire(sisaBan);
            }
            else if (strcmp(command, "[TireChange]") == 0)
            {
                response = tireChange(info);
            }
            else
            {
                response = "Command Tidak Diketahui";
            }
        }
        else
        {
            response = "Format pesan tidak valid";
        }

        send(new_socket, response, strlen(response), 0);
        syslog(LOG_INFO, "Response sent: %s", response);

        close(new_socket);
    }

    syslog(LOG_NOTICE, "paddock terminated");
    closelog();

    return EXIT_SUCCESS;
}
