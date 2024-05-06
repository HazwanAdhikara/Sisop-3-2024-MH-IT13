#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8081
#define IP "127.0.0.1"

int main(int argc, char *argv[])
{
    if (argc != 5)
    {
        printf("Usage: %s -c COMMAND -i INFO\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int sock = 0;
    struct sockaddr_in serv_addr;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, IP, &serv_addr.sin_addr) <= 0)
    {
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    // Construct message
    char message[256];
    sprintf(message, "-c [%s] -i [%s]", argv[2], argv[4]);

    // Mengirim Response
    send(sock, message, strlen(message), 0);

    // Menerima Response
    char buffer[1024] = {0};
    int bytes_received = recv(sock, buffer, sizeof(buffer), 0);
    if (bytes_received < 0)
    {
        perror("Receive failed");
        close(sock);
        exit(EXIT_FAILURE);
    }

    printf("Response : %s\n", buffer);

    close(sock);

    return 0;
}
