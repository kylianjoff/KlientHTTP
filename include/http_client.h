#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include "http_methods.h"
#include <openssl/ssl.h>
#include <openssl/err.h>

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
    int use_https;
} HttpRequest;

int send_http_request(HttpRequest *request, char *response, int response_size);
int send_https_request(HttpRequest *request, char *response, int response_size);
int resolve_hostname(const char *hostname, char *ip_address);
void init_openssl(void);
void cleanup_openssl(void);

#endif