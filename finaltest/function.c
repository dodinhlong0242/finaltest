#include "datatype.h"
#include "function.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Student students[MAX];
int studentCount = 0;
const char *FILE_PATH = "hocsinh.bin";

// Hàm xóa b?t du th?a d?u vào
void flush() {
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF);  // Lo?i b? ký t? th?a
}

// Hàm thêm sinh viên vào danh sách
void addStudent() {
    printf("\n**** Them Sinh Vien Moi ****\n");

    if (studentCount >= MAX) {
        printf("Danh sach sinh vien da day!\n");
        return;
    }

    char studentId[10];
    int idExists = 0;

    do {
        printf("Nhap Ma Sinh Vien: ");
        scanf("%9s", studentId);
        flush();  // Lo?i b? ký t? th?a

        idExists = 0;
        for (int i = 0; i < studentCount; i++) {
            if (strcmp(students[i].studentId, studentId) == 0) {
                idExists = 1;
                break;
            }
        }

        if (idExists) {
            printf("Loi: Ma sinh vien da ton tai.\n");
        } else {
            break;
        }
    } while (idExists);

    // Nh?p thông tin sinh viên và luu
    strcpy(students[studentCount].studentId, studentId);
    printf("Nhap Ten Sinh Vien: ");
    fgets(students[studentCount].name, sizeof(students[studentCount].name), stdin);
    strtok(students[studentCount].name, "\n");  // Lo?i b? ký t? '\n'

    printf("Nhap Email: ");
    fgets(students[studentCount].email, sizeof(students[studentCount].email), stdin);
    strtok(students[studentCount].email, "\n");

    printf("Nhap So Dien Thoai: ");
    fgets(students[studentCount].phone, sizeof(students[studentCount].phone), stdin);
    strtok(students[studentCount].phone, "\n");

    printf("So Mon Hoc: ");
    int numCourses;
    scanf("%d", &numCourses);
    flush();  // Lo?i b? ký t? th?a
    if (numCourses > MAX_COURSES) {
        printf("So mon hoc qua lon! Vui long nhap lai.\n");
        return;
    }
    for (int i = 0; i < numCourses; i++) {
        printf("Nhap Ma Mon %d: ", i + 1);
        fgets(students[studentCount].courses[i].courseCode, sizeof(students[studentCount].courses[i].courseCode), stdin);
        strtok(students[studentCount].courses[i].courseCode, "\n");

        printf("Nhap Ten Mon %d: ", i + 1);
        fgets(students[studentCount].courses[i].courseName, sizeof(students[studentCount].courses[i].courseName), stdin);
        strtok(students[studentCount].courses[i].courseName, "\n");
    }

    studentCount++;
    saveStudentsToFile();
    printf("Sinh vien da duoc them thanh cong.\n");
    backToMenu();  // Quay l?i menu
}

// Hàm luu danh sách sinh viên vào file
void saveStudentsToFile() {
    FILE *file = fopen(FILE_PATH, "wb");
    if (file == NULL) {
        printf("Loi khi mo file!\n");
        return;
    }
    size_t written = fwrite(students, sizeof(Student), studentCount, file);
    if (written != studentCount) {
        printf("Loi khi ghi du lieu vao file!\n");
    } else {
        printf("Danh sach sinh vien da duoc luu vao file %s\n", FILE_PATH);
    }
    fclose(file);  // Ð?m b?o dóng file sau khi ghi
}

// Hàm t?i danh sách sinh viên t? file
void loadStudentsFromFile() {
    FILE *file = fopen(FILE_PATH, "rb");
    if (file == NULL) {
        printf("Khong tim thay file danh sach sinh vien, tao danh sach moi.\n");
        return;
    }
    studentCount = fread(students, sizeof(Student), MAX, file);
    fclose(file);
    printf("Danh sach sinh vien da duoc nap thanh cong!\n");
}

// Hàm hi?n th? danh sách sinh viên du?i d?ng b?ng
void listStudents() {
    if (studentCount == 0) {
        printf("Khong co sinh vien nao!\n");
        return;
    }

    printf("\n**** Tat Ca Sinh Vien ****\n");
    printf("+============+===================+====================+===============+===========+\n");
    printf("| %-10s | %-17s | %-18s | %-13s | %-9s |\n", "ID", "Ten", "Email", "So Dien Thoai", "Khoa");
    printf("+============+===================+====================+===============+===========+\n");

    for (int i = 0; i < studentCount; i++) {
        printf("| %-10s | %-17s | %-18s | %-13s | %-9d |\n", 
               students[i].studentId, students[i].name, 
               students[i].email, students[i].phone, i + 1);
        printf("+------------+-------------------+--------------------+---------------+-----------+\n");
    }

    backToMenu();  // Quay l?i menu
}

// Hàm c?p nh?t thông tin sinh viên
void updateStudent() {
    printf("\n**** Sua Thong Tin Sinh Vien ****\n");

    char studentId[10];
    printf("Nhap Ma Sinh Vien: ");
    scanf("%9s", studentId);
    flush();

    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].studentId, studentId) == 0) {
            printf("Nhap Ten Moi: ");
            fgets(students[i].name, sizeof(students[i].name), stdin);
            strtok(students[i].name, "\n");

            printf("Nhap Email Moi: ");
            fgets(students[i].email, sizeof(students[i].email), stdin);
            strtok(students[i].email, "\n");

            printf("Nhap So Dien Thoai Moi: ");
            fgets(students[i].phone, sizeof(students[i].phone), stdin);
            strtok(students[i].phone, "\n");

            saveStudentsToFile();
            printf("Thong tin sinh vien da duoc cap nhat thanh cong.\n");
            backToMenu();
            return;
        }
    }
    printf("Sinh vien voi ma ID '%s' khong ton tai!\n", studentId);
    backToMenu();
}

// Hàm xóa sinh viên kh?i danh sách
void deleteStudent() {
    printf("\n**** Xoa Sinh Vien ****\n");

    char studentId[10];
    printf("Nhap Ma Sinh Vien: ");
    scanf("%9s", studentId);
    flush();

    int foundIndex = -1;
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].studentId, studentId) == 0) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        printf("Khong tim thay sinh vien voi ID '%s'!\n", studentId);
        backToMenu();
        return;
    }

    // Di chuy?n sinh viên lên d? xóa
    for (int i = foundIndex; i < studentCount - 1; i++) {
        students[i] = students[i + 1];
    }
    studentCount--;
    saveStudentsToFile();
    printf("Sinh vien da duoc xoa thanh cong.\n");
    backToMenu();
}

// Hàm s?p x?p danh sách sinh viên theo tên
void sortStudentsByName() {
    int choice;

    printf("\nChon thu tu sap xep:\n");
    printf("1. Sap xep tang dan\n");
    printf("2. Sap xep giam dan\n");
    printf("Nhap lua chon: ");
    scanf("%d", &choice);

    for (int i = 0; i < studentCount - 1; i++) {
        for (int j = i + 1; j < studentCount; j++) {
            int compareResult = strcmp(students[i].name, students[j].name);

            if ((choice == 1 && compareResult > 0) || (choice == 2 && compareResult < 0)) {
                // Hoán d?i v? trí sinh viên
                Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }

    printf("\nDanh sach sinh vien sau khi sap xep:\n");
    listStudents();  // Hi?n th? l?i danh sách sau khi s?p x?p
}

// Hàm quay l?i menu chính
void backToMenu() {
    char option;
    do {
        printf("\nQuay lai menu chinh (b)? Hoac Thoat (0)?: ");
        scanf(" %c", &option);
        flush();
        if (option == 'b') {
            return;  // Quay l?i menu chính
        } else if (option == '0') {
            exit(0);  // Thoát chuong trình
        } else {
            printf("Lua chon khong hop le! Thoat chuong trinh.\n");
            exit(0);  // Thoát n?u ngu?i dùng nh?p l?a ch?n không h?p l?
        }
    } while (1);
}

// Hàm tìm ki?m sinh viên theo tên
void searchStudentByName() {
    char name[100];
    printf("Nhap ten sinh vien can tim: ");
    getchar();
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;  

  
    if (strlen(name) == 0) {
        printf("Vui long nhap ten sinh vien.\n");
        
        backToMenu();  
        return;
    }

     int found = 0;

        // In tiêu d? b?ng
        printf("\n+============+===================+====================+===============+===========+\n");
        printf("| %-10s | %-17s | %-18s | %-13s | %-9s |\n", "ID", "Ten", "Email", "So Dien Thoai", "Khoa");
        printf("+============+===================+====================+===============+===========+\n");

        for (int i = 0; i < studentCount; i++) {
            // Tìm ki?m sinh viên theo tên (ch?a chu?i nh?p vào)
            if (strstr(students[i].name, name) != NULL) {
                printf("| %-10s | %-17s | %-18s | %-13s | %-9d |\n",
                       students[i].studentId, students[i].name,
                       students[i].email, students[i].phone, i + 1);
                found = 1;
        }
    }
 
                printf("+------------+-------------------+--------------------+---------------+-----------+\n");
    if (!found) {
        printf("Khong tim thay sinh vien co ten: %s\n", name);
    }
    backToMenu();  
}

// Hàm hi?n th? menu chính
void showMenu() {
    printf("\n===================================\n");
    printf("    HE THONG QUAN LY SINH VIEN    \n");
    printf("===================================\n");

    printf("==============================\n");
    printf("        MENU QUAN LY SINH VIEN:\n");
    printf("==============================\n");
    printf("1. Hien thi danh sach sinh vien\n");
    printf("2. Them sinh vien\n");
    printf("3. Sua thong tin sinh vien\n");
    printf("4. Xoa sinh vien\n");
    printf("5. Tim kiem sinh vien theo ten\n");
    printf("6. Sap xep danh sach sinh vien\n");
    printf("7. Thoat\n");
    printf("==============================\n");
}

