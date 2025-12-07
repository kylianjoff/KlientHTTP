#ifndef UTILS_H
#define UTILS_H

void trim_newline(char *str);
void print_colored(const char *text, const char *color);
void print_box(const char *text);

#define COLOR_RESET     "\33[0m"
#define COLOR_RED       "\033[31m"
#define COLOR_GREEN     "\033[32m"
#define COLOR_YELLOW    "\033[33m"
#define COLOR_BLUE      "\033[34m"
#define COLOR_MAGENTA   "\033[35m"
#define COLOR_CYAN      "\033[36m"
#define COLOR_WHITE     "\033[37m"
#define COLOR_BOLD      "\033[1m"

#endif