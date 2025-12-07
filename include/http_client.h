#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include "http_methods.h"

#define MAX_HOSTNAME 256
#define MAX_PATH 512
#define MAX_HEADERS 2048
#define MAX_BODY 4096
#define BUFFER_SIZE 8192

typedef struct {
    HttpMethod method;
    char hostname[MAX_HOSTNAME];
    char path[MAX_PATH];
    int port;
    char headers[MAX_HEADERS];
    char body[MAX_BODY];
} HttpRequest;

int send_http_request(HttpRequest *request, char *response, int response_size);
int resolve_hostname(const char *hostname, char *ip_address);

#endif