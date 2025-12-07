#ifndef UI_H
#define UI_H

#include "http_methods.h"
#include "http_client.h"

void clear_screen(void);
void display_welcome(void);
void display_goodbye(void);
HttpMethod select_http_method(void);
void input_hostname(char *hostname, int max_len);
void input_path(char *path, int max_len);
void input_headers(char *headers, int max_len);
void input_body(char *body, int max_len);
void display_request_summary(HttpRequest *request);
void display_response(const char *response);
int confirm_action(const char *message);
char getch(void);

#endif