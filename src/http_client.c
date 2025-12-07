#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "http_client.h"
#include "utils.h"

int resolve_hostname(const char *hostname, char *ip_address) {
    struct hostent *he;
    struct in_addr **addr_list;

    he = gethostbyname(hostname);
    if(he == NULL) {
        return -1;
    }

    addr_list = (struct in_addr **)he->h_addr_list;
    if(addr_list[0] != NULL) {
        strcpy(ip_address, inet_ntoa(*addr_list[0]));
        return 0;
    }

    return -1;
}

int send_http_request(HttpRequest *request, char *response, int response_size) {
    int sockfd;
    struct sockaddr_in serv_addr;
    char ip_address[100];
    char buffer[BUFFER_SIZE];
    int bytes_received;
    int total_bytes = 0;

    printf("Résolution DNS de '%s'...\n", request->hostname);
    if(resolve_hostname(request->hostname, ip_address) != 0) {
        print_colored("Impossible de résoudre le hostname\n", COLOR_RED);
        return -1;
    }
    printf("Résolu : %s -> %s\n", request->hostname, ip_address);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0) {
        perror("Erreur socket");
        return -1;
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(request->port);
    inet_pton(AF_INET, ip_address, &serv_addr.sin_addr);

    printf("Connexion à %s:%d...\n", ip_address, request->port);
    if(connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Erreur connexion");
        close(sockfd);
        return -1;
    }
    print_colored("Connecté\n", COLOR_GREEN);

    int len = snprintf(buffer, BUFFER_SIZE,
        "%s %s HTTP/1.1\r\n"
        "Host: %s\r\n"
        "User-Agent: KlientHTTP/1.0\r\n"
        "Accept: */*\r\n",
        get_method_name(request->method),
        request->path,
        request->hostname
    );

    if(strlen(request->headers) > 0) {
        len += snprintf(buffer + len, BUFFER_SIZE - len, "%s\r\n", request->headers);
    }

    if(strlen(request->body) > 0) {
        len += snprintf(buffer + len, BUFFER_SIZE - len,
            "Content-Length: %ld\r\n"
            "Content-Type: application/json\r\n",
            strlen(request->body),
            request->body
        );
    } else {
        len += snprintf(buffer + len, BUFFER_SIZE - len, "Connection: close\r\n\r\n");
    }

    if(send(sockfd, buffer, len, 0) < 0) {
        perror("Erreur envoi");
        close(sockfd);
        return -1;
    }
    print_colored("Requête envoyée\n", COLOR_GREEN);

    printf("\nRéception de la réponse...\n");
    while((bytes_received = recv(sockfd, buffer, BUFFER_SIZE - 1, 0)) > 0 && total_bytes < response_size - 1) {
        buffer[bytes_received] = '\0';
        strncat(response, buffer, response_size - total_bytes - 1);
        total_bytes += bytes_received;
    }

    close(sockfd);
    return 0;
}