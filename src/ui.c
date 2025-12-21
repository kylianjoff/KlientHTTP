#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include "ui.h"
#include "utils.h"

char getch(void) {
    char buf = 0;
    struct termios old = {0};
    fflush(stdout);
    if(tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if(tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if(read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if(tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return buf;
}

void clear_screen(void) {
    printf("\033[2J\033[H");
}

void display_welcome(void) {
    clear_screen();
    print_colored("╔═══════════════════════════════════════════════════════╗\n", COLOR_CYAN);
    print_colored("║                                                       ║\n", COLOR_CYAN);
    print_colored("║                      KlientHTTP                       ║\n", COLOR_CYAN);
    print_colored("║                                                       ║\n", COLOR_CYAN);
    print_colored("║                     Kylian JULIA                      ║\n", COLOR_CYAN);
    print_colored("║        https://github.com/kylianjoff/KlientHTTP       ║\n", COLOR_CYAN);
    print_colored("║                    kylianjulia.fr                     ║\n", COLOR_CYAN);
    print_colored("║                                                       ║\n", COLOR_CYAN);
    print_colored("║          Navigation: ↑/↓    Sélection: ENTER          ║\n", COLOR_CYAN);
    print_colored("║                                                       ║\n", COLOR_CYAN);
    print_colored("╚═══════════════════════════════════════════════════════╝\n", COLOR_CYAN);
    printf("\n");
    printf("Appuyez sur une touche pour continuer...");
    getch();
}

void display_goodbye(void) {
    clear_screen();
    print_colored("\nMerci d'avoir utilisé KlientHTTP !\n\n", COLOR_CYAN);
}

HttpMethod select_http_method(void) {
    int selected = 0;
    int count = get_method_count();
    char c;

    while(1) {
        clear_screen();
        print_colored("═══ Sélection de la méthode HTTP ═══\n\n", COLOR_CYAN);
        printf("Utilisez les flèches ↑/↓ pour naviguer et ENTER pour sélectionner.\n\n");

        for(int i=0; i<count; i++) {
            if(i==selected) {
                printf(COLOR_GREEN "> %s - %s" COLOR_RESET "\n", get_method_name((HttpMethod)i), get_method_description((HttpMethod)i));
            } else {
                printf("  %s - %s\n", get_method_name((HttpMethod)i), get_method_description((HttpMethod)i));
            }
        }

        c = getch();

        if(c == '\n' || c == '\r') {
            return (HttpMethod)selected;
        } else if (c == 27) {
            getch();
            c = getch();
            if(c == 'A') {
                selected = (selected - 1 + count) % count;
            } else if (c == 'B') {
                selected = (selected + 1) % count;
            }
        }
    }
}

void input_hostname(char *hostname, int max_len) {
    clear_screen();
    print_colored("═══ HOSTNAME / DOMAINE ═══\n\n", COLOR_CYAN);
    printf("Exemples : www.google.com, api.github.com, localhost\n\n");
    printf(COLOR_YELLOW "HOSTNAME : " COLOR_RESET);
    fgets(hostname, max_len, stdin);
    trim_newline(hostname);
}

void input_path(char *path, int max_len) {
    clear_screen();
    print_colored("═══ CHEMIN (PATH) ═══\n\n", COLOR_CYAN);
    printf("Exemples: /, /api/users, /search?q=test\n");
    printf("Laisser vide pour '/'\n\n");
    printf(COLOR_YELLOW "PATH : " COLOR_RESET);
    char temp[512];
    fgets(temp, max_len, stdin);
    trim_newline(temp);
    if(strlen(temp) > 0) {
        strcpy(path, temp);
    }
}

void input_headers(char *headers, int max_len) {
    clear_screen();
    print_colored("═══ HEADERS Personnalisés ═══\n\n", COLOR_CYAN);
    printf("Format: Header-Name: value\n");
    printf("Exemple : Authorization: Bearer token123\n\n");
    printf(COLOR_YELLOW "Headers : " COLOR_RESET);
    fgets(headers, max_len, stdin);
    trim_newline(headers);
}

void input_body(char *body, int max_len) {
    clear_screen();
    print_colored("═══ Body (JSON) ═══\n\n", COLOR_CYAN);
    printf("Exemple: {\"name\":\"John\",\"age\":30}\n\n");
    printf(COLOR_YELLOW "Body : " COLOR_RESET);
    fgets(body, max_len, stdin);
    trim_newline(body);
}

void display_request_summary(HttpRequest *request) {
    clear_screen();
    print_colored("═══ Récapitulatif de la requête ═══\n\n", COLOR_CYAN);
    printf(COLOR_BOLD "Méthode :   " COLOR_RESET "%s\n", get_method_name(request->method));
    printf(COLOR_BOLD "Hostname :  " COLOR_RESET "%s\n", request->hostname);
    printf(COLOR_BOLD "Port :      " COLOR_RESET "%d\n", request->port);
    printf(COLOR_BOLD "Path :      " COLOR_RESET "%s\n", request->path);
    if(strlen(request->headers) > 0) {
        printf(COLOR_BOLD "Headers : " COLOR_RESET "%s\n", request->headers);
    }
    if(strlen(request->body) > 0) {
        printf(COLOR_BOLD "Body : " COLOR_RESET "%s\n", request->body);
    }
    printf("\n");
}

void display_response(const char *response) {
    clear_screen();
    print_colored("═══ Réponse du serveur ═══\n\n", COLOR_GREEN);
    printf("%s\n", response);
    print_colored("\n═══ Fin de la réponse ═══\n", COLOR_GREEN);
}

int confirm_action(const char *message) {
    printf("\n%s%s (O/n) : %s", COLOR_YELLOW, message, COLOR_RESET);
    char c = getch();
    printf("%c\n", c);
    return (c != 'n' && c != 'N');
}