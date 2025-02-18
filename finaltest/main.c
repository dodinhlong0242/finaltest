#include "datatype.h"
#include "function.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RESET   "\x1b[0m"
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define WHITE   "\x1b[37m"
#define BOLD    "\x1b[1m"    // Th�m ki?u in d?m
#define UNDERLINE "\x1b[4m" // Th�m ki?u g?ch ch�n

// M?ng m�u
const char* colors[] = {RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE};

// H�m in ra van b?n c� m�u s?c
void printWithColor(const char* text, int colorIndex) {
    if (colorIndex >= 0 && colorIndex < 7) {
        printf("%s%s%s", colors[colorIndex], text, RESET);
    } else {
        printf("%s", text);
    }
}

// H�m in ra van b?n in d?m v?i m�u s?c
void printWithBoldColor(const char* text, int colorIndex) {
    if (colorIndex >= 0 && colorIndex < 7) {
        printf("%s%s%s%s", BOLD, colors[colorIndex], text, RESET); // Th�m BOLD v�o
    } else {
        printf("%s", text);
    }
}

// H�m hi?n th? menu ch�nh v?i c�c m�u s?c
void showMenu() {
    printWithColor("*** He thong Quan ly Sinh vien ***\n\n", CYAN);
    printWithBoldColor("CHON VAI TRO CUA BAN\n", YELLOW);
    printWithColor("=====================\n", RED);
    printWithColor("[1] Quan tri vien.\n", GREEN);        // M�u xanh l� c�y
    printWithColor("[2] Sinh vien.\n", BLUE);            // M�u xanh duong
    printWithColor("[3] Giang vien.\n", MAGENTA);     // M�u t�m
    printWithColor("[0] Thoat chuong trinh.\n", CYAN); // M�u cyan
    printWithColor("=====================\n", RED);
    printWithBoldColor("Nhap lua chon cua ban: ", WHITE);  // In d?m v� m�u tr?ng
}

// H�m hi?n th? th�ng b�o khi ngu?i d�ng nh?p sai l?a ch?n
void invalidChoice() {
    printWithColor("Lua chon khong hop le!\n", RED);  // M�u d? cho l?i
}

// H�m b?t d?u h? th?ng v� x? l� c�c ch?c nang
void start() {
    loadStudentsFromFile();  // T?i d? li?u sinh vi�n t? file

    while (1) {
        showMenu();  // Hi?n th? menu ch�nh
        int choice;
        printf("Nhap lua chon: ");
        scanf("%d", &choice);
        system("cls");  // X�a m�n h�nh

        // Th?c hi?n c�c ch?c nang theo l?a ch?n
        switch (choice) {
            case 1:
                printWithColor("Ban chon Quan tri vien.\n", GREEN);
                // Th�m c�c ch?c nang qu?n tr? vi�n ? d�y n?u c?n
                showAdminMenu();
                break;
            case 2:
                showStudentMenu();  // Hi?n th? menu qu?n l� sinh vi�n
                break;
            case 3:
                printWithColor("Ban chon Giang vien.\n", BLUE);
                showTeacherMenu();  // Hi?n th? menu qu?n l� gi?ng vi�n
                break;
            case 0:
                printWithColor("Thoat chuong trinh...\n", CYAN);
                exit(0);  // Tho�t chuong tr�nh
            default:
                invalidChoice();  // Hi?n th? th�ng b�o l?i khi nh?p sai
        }
    }
}

void showAdminMenu() {
    // T?o m?t menu gi? d?nh cho qu?n tr? vi�n (admin)
    int choice;
    do {
        printf("\n**** Menu Quan Tri Vien ****\n");
        printf("1. Quan ly giang vien\n");
        printf("2. Quan ly sinh vien\n");
        printf("3. Thoat\n");
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                showTeacherMenu();  // Qu?n l� gi?ng vi�n
                break;
            case 2:
                showStudentMenu();  // Qu?n l� sinh vi�n
                break;
            case 3:
                return;  // Quay l?i menu ch�nh
            default:
                invalidChoice();
        }
    } while (1);
}

// H�m main
int main() {
    start();  // B?t d?u h? th?ng qu?n l� sinh vi�n
    return 0;
}

