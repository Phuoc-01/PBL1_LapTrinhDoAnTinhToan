#include "ui.h"
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#endif

void clear_screen(){
    system("cls||clear");
}


void print_header(){
    clear_screen();
    
    printf("\n");
    printf(CONSOLE_TITLE CONSOLE_BOLD);
    printf("					+----------------------------------------------------------------------------+\n");
    printf("					?                                                                            ?\n");
    printf("					?                     CHUONG TRINH TIM CHU TRINH EULER                       ?\n");
    printf("					?                                                                            ?\n");
    printf("					?----------------------------------------------------------------------------?\n");
    printf(CONSOLE_RESET);
    printf(CONSOLE_WHITE);
    printf("					?     Sinh vien: Ho Tan Phuoc - Phan Huu Tri                                 ?\n");
    printf("					?     Giang vien: Nguyen Van Hieu                                            ?\n");
    printf(CONSOLE_TITLE CONSOLE_BOLD);
    printf("					+----------------------------------------------------------------------------+\n");
    printf(CONSOLE_RESET);
    printf("\n");
}

void print_step(const char *msg){
    printf(CONSOLE_STEP CONSOLE_BOLD "\n? %s\n" CONSOLE_RESET, msg);
    printf(CONSOLE_GRAY "--------------------------------------------------------------------------------\n" CONSOLE_RESET);
}

void print_error(const char *msg){
    printf(CONSOLE_ERROR CONSOLE_BOLD "\n? Loi: %s\n" CONSOLE_RESET, msg);
}

void print_success(const char *msg){
    printf(CONSOLE_SUCCESS CONSOLE_BOLD "\n? %s\n" CONSOLE_RESET, msg);
}

void print_menu(int num, const char *text){
    printf(CONSOLE_MENU "  %d. " CONSOLE_RESET, num);
    printf(CONSOLE_WHITE "%s\n" CONSOLE_RESET, text);
}

void print_result(const char *title, const char *content){
    printf(CONSOLE_RESULT CONSOLE_BOLD);
    printf("\n+--------------------------------------------------------------------------------+\n");
    printf("? %-78s ?\n", title);
    printf("+--------------------------------------------------------------------------------?\n");
    printf("? " CONSOLE_RESET);
    printf("%s", content);
    int len = strlen(content);
    for(int i = len; i < 78; i++) printf(" ");
    printf(CONSOLE_RESULT CONSOLE_BOLD "?\n");
    printf("+--------------------------------------------------------------------------------+\n" CONSOLE_RESET);
}

void print_loading(const char *msg){
    printf(CONSOLE_STEP "\n? %s...\n" CONSOLE_RESET, msg);
}

