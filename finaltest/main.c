#include "function.h"

int main() {
    loadStudentsFromFile();
    int choice;
    printf("\n===================================\n");
    printf("    HE THONG QUAN LY SINH VIEN    \n");
    printf("===================================\n");
    while (1) {
    	printf("\n==============================\n");
        printf("\nMENU QUAN LY SINH VIEN:\n");
        printf("\n=============================\n");
        printf("1. Hien thi danh sach sinh vien\n");
        printf("2. Them sinh vien\n");
        printf("3. Sua thong tin sinh vien\n");
        printf("4. Thoat\n");
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
                saveStudentsToFile();
                exit(0);
            default:
                printf("Lua chon khong hop le!\n");
        }
    }
    return 0;
}

