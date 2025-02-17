#include "datatype.h"
#include "function.h"
#include <stdio.h>
#include <stdlib.h>
void start(){
	loadStudentsFromFile();  // Load d? li?u sinh vi?n t? file

    while (1) {
        showMenu();  // Hi?n th? menu ch?nh
        int choice;
        printf("Nhap lua chon: ");
        scanf("%d", &choice);
        system("cls");

        // Th?c hi?n c?c ch?c nang theo l?a ch?n
        switch (choice) {
            case 1:
                listStudents();  // Hi?n th? danh s?ch sinh vi?n
                break;
            case 2:
                addStudent();  // Th?m sinh vi?n
                break;
            case 3:
                updateStudent();  // S?a th?ng tin sinh vi?n
                break;
            case 4:
                deleteStudent();  // X?a sinh vi?n
                break;
            case 5:
                searchStudentByName();  // T?m ki?m sinh vi?n theo t?n
                break;
            case 6:
                sortStudentsByName();  // S?p x?p danh s?ch sinh vi?n
                break;
            case 7:
                exit(0);  // Tho?t chuong tr?nh
            default:
                printf("Lua chon khong hop le!\n");
                break;
        }

        // Sau m?i ch?c nang, y?u c?u ngu?i d?ng quay l?i menu ch?nh ho?c tho?t
//        char option;
//        printf("\nQuay lai menu chinh (b)? Hoac Thoat (0)?: ");
//        scanf(" %c", &option);  // ??c l?a ch?n c?a ngu?i d?ng
//        if (option == '0') {
//            break;  // Tho?t chuong tr?nh
//        }
//        else if (option != 'b') {
//            printf("Lua chon khong hop le! Thoat chuong trinh.\n");
//            break;
//        }
    }
}
int main() {
    start();
    return 0;
}


