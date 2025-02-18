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
#define BOLD    "\x1b[1m"    // Thêm ki?u in d?m
#define UNDERLINE "\x1b[4m" // Thêm ki?u g?ch chân

// M?ng màu
const char* colors[] = {RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE};

// Hàm in ra van b?n có màu s?c
void printWithColor(const char* text, int colorIndex) {
    if (colorIndex >= 0 && colorIndex < 7) {
        printf("%s%s%s", colors[colorIndex], text, RESET);
    } else {
        printf("%s", text);
    }
}

// Hàm in ra van b?n in d?m v?i màu s?c
void printWithBoldColor(const char* text, int colorIndex) {
    if (colorIndex >= 0 && colorIndex < 7) {
        printf("%s%s%s%s", BOLD, colors[colorIndex], text, RESET); // Thêm BOLD vào
    } else {
        printf("%s", text);
    }
}

// Hàm hi?n th? menu chính v?i các màu s?c
void showMenu() {
    printWithColor("*** He thong Quan ly Sinh vien ***\n\n", CYAN);
    printWithBoldColor("CHON VAI TRO CUA BAN\n", YELLOW);
    printWithColor("=====================\n", RED);
    printWithColor("[1] Quan tri vien.\n", GREEN);        // Màu xanh lá cây
    printWithColor("[2] Sinh vien.\n", BLUE);            // Màu xanh duong
    printWithColor("[3] Giang vien.\n", MAGENTA);     // Màu tím
    printWithColor("[0] Thoat chuong trinh.\n", CYAN); // Màu cyan
    printWithColor("=====================\n", RED);
    printWithBoldColor("Nhap lua chon cua ban: ", WHITE);  // In d?m và màu tr?ng
}

// Hàm hi?n th? thông báo khi ngu?i dùng nh?p sai l?a ch?n
void invalidChoice() {
    printWithColor("Lua chon khong hop le!\n", RED);  // Màu d? cho l?i
}

// Hàm b?t d?u h? th?ng và x? lý các ch?c nang
void start() {
    loadStudentsFromFile();  // T?i d? li?u sinh viên t? file

    while (1) {
        showMenu();  // Hi?n th? menu chính
        int choice;
        printf("Nhap lua chon: ");
        scanf("%d", &choice);
        system("cls");  // Xóa màn hình

        // Th?c hi?n các ch?c nang theo l?a ch?n
        switch (choice) {
            case 1:
                printWithColor("Ban chon Quan tri vien.\n", GREEN);
                // Thêm các ch?c nang qu?n tr? viên ? dây n?u c?n
                showAdminMenu();
                break;
            case 2:
                showStudentMenu();  // Hi?n th? menu qu?n lý sinh viên
                break;
            case 3:
                printWithColor("Ban chon Giang vien.\n", BLUE);
                showTeacherMenu();  // Hi?n th? menu qu?n lý gi?ng viên
                break;
            case 0:
                printWithColor("Thoat chuong trinh...\n", CYAN);
                exit(0);  // Thoát chuong trình
            default:
                invalidChoice();  // Hi?n th? thông báo l?i khi nh?p sai
        }
    }
}

void showAdminMenu() {
    // T?o m?t menu gi? d?nh cho qu?n tr? viên (admin)
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
                showTeacherMenu();  // Qu?n lý gi?ng viên
                break;
            case 2:
                showStudentMenu();  // Qu?n lý sinh viên
                break;
            case 3:
                return;  // Quay l?i menu chính
            default:
                invalidChoice();
        }
    } while (1);
}

// Hàm main
int main() {
    start();  // B?t d?u h? th?ng qu?n lý sinh viên
    return 0;
}

