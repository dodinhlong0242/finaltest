#include "datatype.h"
#include "function.h"

Student students[MAX];
int studentCount = 0;

const char *FILE_PATH = "hocsinh.bin";

void addStudent() {
    if (studentCount >= MAX) {
        printf("Danh sach sinh vien da day!\n");
        return;
    }
    printf("Nhap ma sinh vien: ");
    scanf("%9s", students[studentCount].studentId);
    getchar();
    printf("Nhap ten sinh vien: ");
    fgets(students[studentCount].name, sizeof(students[studentCount].name), stdin);
    strtok(students[studentCount].name, "\n");
    printf("Nhap ngay sinh (dd mm yyyy): ");
    scanf("%d %d %d", &students[studentCount].dateOfBirth.day, &students[studentCount].dateOfBirth.month, &students[studentCount].dateOfBirth.year);
    getchar();
    printf("Nhap gioi tinh (0: Nam, 1: Nu): ");
    scanf("%d", &students[studentCount].gender);
    getchar();
    printf("Nhap email: ");
    fgets(students[studentCount].email, sizeof(students[studentCount].email), stdin);
    strtok(students[studentCount].email, "\n");
    printf("Nhap so dien thoai: ");
    scanf("%19s", students[studentCount].phone);
    getchar();

    studentCount++;
    saveStudentsToFile();
    printf("\nSinh vien da duoc them thanh cong!\n");
}

void listStudents() {
    if (studentCount == 0) {
        printf("Khong co sinh vien nao!\n");
        return;
    }

    printf("\n**** All Students ****\n");

    // In du?ng k? trên c?a b?ng
    printf("+============+================+======================+===============+===========+\n");
    printf("| %-10s | %-14s | %-20s | %-13s | %-9s |\n", "ID", "Name", "Email", "Phone", "Course");
    printf("+============+================+======================+===============+===========+\n");

    // In t?ng sinh viên trong danh sách
    for (int i = 0; i < studentCount; i++) {
        printf("| %-10s | %-14s | %-20s | %-13s | %-9d |\n", 
               students[i].studentId, students[i].name, 
               students[i].email, students[i].phone, i + 1);
        printf("+------------+----------------+----------------------+---------------+-----------+\n");
    }

    // Tùy ch?n quay l?i ho?c thoát
    char option;
    printf("\nGo back (b) or Exit (0)?: ");
    scanf(" %c", &option);
    if (option == '0') {
        exit(0);
    }
}

void saveStudentsToFile() {
    FILE *file = fopen(FILE_PATH, "wb");
    if (file == NULL) {
        printf("Loi khi mo file!\n");
        return;
    }
    fwrite(students, sizeof(Student), studentCount, file);
    fclose(file);
    printf("Danh sach sinh vien da duoc luu vao file %s\n", FILE_PATH);
}

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

