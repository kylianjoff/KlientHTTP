#include <stdio.h>
#include <string.h>
#include "utils.h"

void trim_newline(char *str) {
    size_t len = strlen(str);
    if(len > 0 && (str[len-1] == '\n' || str[len-1] == '\r')) {
        str[len-1] = '\0';
    }
    if(len > 1 && (str[len-2] == '\n' || str[len-2] == '\r')) {
        str[len-2] = '\0';
    }
}

void print_colored(const char *text, const char *color) {
    printf("%s%s%s", color, text, COLOR_RESET);
}

void print_box(const char *text) {
    int len = strlen(text);
    printf("╔");
    for(int i=0; i<len+2; i++) printf("═");
    printf("╗\n");
    printf("║ %s ║\n", text);
    printf("╚");
    for(int i=0; i<len+2; i++) printf("═");
    printf("╝\n");
}