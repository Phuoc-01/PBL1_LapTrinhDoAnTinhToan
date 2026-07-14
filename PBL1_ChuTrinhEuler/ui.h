#ifndef UI_H
#define UI_H

#include <stdio.h>

#define CONSOLE_RESET   "\033[0m"
#define CONSOLE_BOLD    "\033[1m"

#define CONSOLE_TITLE   "\033[38;2;100;180;250m"    
#define CONSOLE_STEP    "\033[38;2;0;180;180m"       
#define CONSOLE_SUCCESS "\033[38;2;0;180;80m"        
#define CONSOLE_ERROR   "\033[38;2;220;80;80m"       
#define CONSOLE_RESULT  "\033[38;2;80;180;180m"      
#define CONSOLE_MENU    "\033[38;2;140;140;200m"     
#define CONSOLE_WHITE   "\033[38;2;220;220;220m"     
#define CONSOLE_GRAY    "\033[38;2;120;120;140m"     
#define CONSOLE_GOLD    "\033[38;2;220;180;80m"     

void print_header();
void print_step(const char *msg);
void print_error(const char *msg);
void print_success(const char *msg);
void print_menu(int num, const char *text);
void print_result(const char *title, const char *content);
void print_loading(const char *msg);
void print_center(const char *text, const char *color);
void clear_screen();

#endif

