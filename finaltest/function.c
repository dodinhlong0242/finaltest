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

    // Kiem tra ID sinh vien da ton tai hay chua
    char studentId[10];
    int idExists = 0;
    
    do {
        printf("Nhap ma sinh vien: ");
        scanf("%9s", studentId);
        getchar();

        // Kiem tra xem ID da ton tai trong danh sach sinh vien
        idExists = 0;
        for (int i = 0; i < studentCount; i++) {
            if (strcmp(students[i].studentId, studentId) == 0) {
                idExists = 1;  // ID ton tai, yeu cau nhap lai
                break;
            }
        }

        if (idExists) {
            printf("Ma sinh vien da ton tai, vui long nhap ma khac!\n");
        } else {
            break;  // ID chua ton tai, cho phep nhap thong tin sinh vien
        }
    } while (idExists);  // Lap lai neu ID ton tai

    // Them sinh vien vao danh sach
    strcpy(students[studentCount].studentId, studentId);  // Luu ID sinh vien
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

    studentCount++;  // Tang s? lu?ng sinh viên
    saveStudentsToFile();  // Luu thông tin sinh viên vào file
    printf("\nSinh vien da duoc them thanh cong!\n");

    backToMenu();  // Quay l?i menu chính
}

void listStudents() {
    if (studentCount == 0) {
        printf("Khong co sinh vien nao!\n");
        return;
    }

    printf("\n**** All Students ****\n");

    printf("+============+================+======================+===============+===========+\n");
    printf("| %-10s | %-14s | %-20s | %-13s | %-9s |\n", "ID", "Name", "Email", "Phone", "Course");
    printf("+============+================+======================+===============+===========+\n");

    for (int i = 0; i < studentCount; i++) {
        printf("| %-10s | %-14s | %-20s | %-13s | %-9d |\n", 
               students[i].studentId, students[i].name, 
               students[i].email, students[i].phone, i + 1);
        printf("+------------+----------------+----------------------+---------------+-----------+\n");
    }

    backToMenu();  // Quay l?i menu chính
}

void saveStudentsToFile() {
    FILE *file = fopen(FILE_PATH, "wb");  // M? file ? ch? d? ghi nh? phân
    if (file == NULL) {
        printf("Loi khi mo file!\n");
        return;
    }
    fwrite(students, sizeof(Student), studentCount, file);  // Ghi d? li?u vào file
    fclose(file);  // Ð?m b?o dóng file sau khi ghi
    printf("Danh sach sinh vien da duoc luu vao file %s\n", FILE_PATH);
}

void loadStudentsFromFile() {
    FILE *file = fopen(FILE_PATH, "rb");  // M? file ? ch? d? d?c nh? phân
    if (file == NULL) {
        printf("Khong tim thay file danh sach sinh vien, tao danh sach moi.\n");
        return;
    }
    studentCount = fread(students, sizeof(Student), MAX, file);  // Ð?c d? li?u t? file
    fclose(file);  // Ð?m b?o dóng file sau khi d?c
    printf("Danh sach sinh vien da duoc nap thanh cong!\n");
}

void updateStudent() {
    char studentId[10];
    int found = 0;

    printf("Nhap ma sinh vien muon sua: ");
    scanf("%9s", studentId);
    getchar();

    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].studentId, studentId) == 0) {
            found = 1;

            printf("\nThong tin sinh vien hien tai:\n");
            printf("ID: %s\n", students[i].studentId);
            printf("Ten: %s\n", students[i].name);
            printf("Ngay Sinh: %02d/%02d/%04d\n", students[i].dateOfBirth.day, students[i].dateOfBirth.month, students[i].dateOfBirth.year);
            printf("Gioi Tinh: %s\n", students[i].gender == 0 ? "Nam" : "Nu");
            printf("Email: %s\n", students[i].email);
            printf("So DT: %s\n", students[i].phone);

            printf("\nNhap thong tin moi cho sinh vien:\n");

            printf("Nhap ten sinh vien moi: ");
            fgets(students[i].name, sizeof(students[i].name), stdin);
            strtok(students[i].name, "\n");

            printf("Nhap ngay sinh moi (dd mm yyyy): ");
            scanf("%d %d %d", &students[i].dateOfBirth.day, &students[i].dateOfBirth.month, &students[i].dateOfBirth.year);
            getchar();

            printf("Nhap gioi tinh moi (0: Nam, 1: Nu): ");
            scanf("%d", &students[i].gender);
            getchar();

            printf("Nhap email moi: ");
            fgets(students[i].email, sizeof(students[i].email), stdin);
            strtok(students[i].email, "\n");

            printf("Nhap so dien thoai moi: ");
            scanf("%19s", students[i].phone);
            getchar();

            saveStudentsToFile();  // Luu thông tin dã s?a vào file
            printf("\nThong tin sinh vien da duoc sua thanh cong!\n");

            backToMenu();  // Quay l?i menu chính
            break;
        }
    }

    if (!found) {
        printf("Sinh vien voi ma ID '%s' khong ton tai!\n", studentId);
    }
}

void backToMenu() {
    char option;
    printf("\nQuay lai menu chinh (b) hoac Thoat (0)?: ");
    scanf(" %c", &option);
    if (option == 'b') {
        return;
    } else if (option == '0') {
        exit(0);
    } else {
        printf("Lua chon khong hop le! Thoat chuong trinh.\n");
        exit(0);
    }
}

