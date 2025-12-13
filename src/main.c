#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ui.h"
#include "http_client.h"
#include "utils.h"

int main(void) {
    HttpRequest request;
    char response[BUFFER_SIZE * 4];

    init_openssl();

    display_welcome();

    while(1) {
        memset(&request, 0, sizeof(HttpRequest));
        request.port = 80;
        request.use_https = 0;
        strcpy(request.path, "/");

        request.method = select_http_method();

        input_hostname(request.hostname, MAX_HOSTNAME);
        if(strlen(request.hostname) == 0) {
            continue;
        }

        if(confirm_action("Utiliser HTTPS ?")) {
            request.use_https = 1;
            request.port = 443;
            print_colored("Mode HTTPS activé\n", COLOR_GREEN);
        } else {
            request.use_https = 0;
            request.port = 80;
            print_colored("Mode HTTP activé\n", COLOR_YELLOW);
        }

        input_path(request.path, MAX_PATH);

        if(confirm_action("Ajouter des headers personnalisés ?")) {
            input_headers(request.headers, MAX_HEADERS);
        }

        if(request.method == METHOD_POST || request.method == METHOD_PUT || request.method == METHOD_PATCH) {
            if(confirm_action("Ajouter un body ?")) {
                input_body(request.body, MAX_BODY);
            }
        }

        display_request_summary(&request);

        if(!confirm_action("Envoyer cette requête ?")) {
            continue;
        }

        print_colored("\nEnvoie de la requête ...\n", COLOR_YELLOW);

        memset(response, 0, sizeof(response));

        int result;
        if(request.use_https) {
            result = send_https_request(&request, response, sizeof(response));
        } else {
            result = send_http_request(&request, response, sizeof(response));
        }

        if(result == 0) {
            display_response(response);
        } else {
            print_colored("\nErreur lors de l'envoie de la requête\n", COLOR_RED);
        }

        if(!confirm_action("\nFaire une autre requête ?")) {
            break;
        }
    }

    display_goodbye();
    cleanup_openssl();
    return 0;
}