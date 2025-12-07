#ifndef HTTP_METHODS_H
#define HTTP_METHODS_H

typedef enum {
    METHOD_GET = 0,
    METHOD_POST,
    METHOD_PUT,
    METHOD_DELETE,
    METHOD_HEAD,
    METHOD_OPTIONS,
    METHOD_PATCH,
    METHOD_TRACE,
    METHOD_CONNECT
} HttpMethod;

const char* get_method_name(HttpMethod method);
const char* get_method_description(HttpMethod method);
int get_method_count(void);

#endif