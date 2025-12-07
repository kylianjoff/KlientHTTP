#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ui.h"
#include "http_client.h"
#include "utils.h"

int main(void) {
    HttpRequest request;
    char response[BUFFER_SIZE * 4];

    display_welcome();

    while(1) {
        memset(&request, 0, sizeof(HttpRequest));
        request.port = 80;
        strcpy(request.path, "/");

        request.method = select_http_method();

        input_hostname(request.hostname, MAX_HOSTNAME);
        if(strlen(request.hostname) == 0) {
            continue;
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
        if(send_http_request(&request, response, sizeof(response)) == 0) {
            display_response(response);
        } else {
            print_colored("\nErreur lors de l'envoie de la requête\n", COLOR_RED);
        }

        if(!confirm_action("\nFaire une autre requête ?")) {
            break;
        }
    }

    display_goodbye();
    return 0;
}