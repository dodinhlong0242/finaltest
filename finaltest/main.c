#include "function.h"
#include <stdio.h>

int main() {
    loadStudentsFromFile();
    int choice;
    printf("\n===================================\n");
    printf("    HE THONG QUAN LY SINH VIEN    \n");
    printf("===================================\n");
    
    while (1) {
        printf("\n==============================\n");
        printf("        MENU QUAN LY SINH VIEN:\n");
        printf("==============================\n");
        printf("1. Hien thi danh sach sinh vien\n");
        printf("2. Them sinh vien\n");
        printf("3. Sua thong tin sinh vien\n");
        printf("4. Xoa sinh vien\n");
        printf("5. Tim kiem sinh vien theo ten\n");
        printf("6. Thoat\n");
        printf("==============================\n");
        printf("Nhap lua chon: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                listStudents();
                break;
            case 2:
                addStudent();
                break;
            case 3:
                updateStudent();
                break;
            case 4:
                deleteStudent();
                break;
            case 5:
                searchStudentByName();
                break;
            case 6:
                saveStudentsToFile(); // G?i hàm luu danh sách sinh viên
                exit(0);
            default:
                printf("Lua chon khong hop le! Xin vui long chon lai.\n");
        }
    }
    return 0;
}

