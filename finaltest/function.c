#include "datatype.h"
#include "function.h"

Student students[MAX];
int studentCount = 0;

const char *FILE_PATH = "hocsinh.bin";

// Hàm thêm sinh viên vào danh sách
void addStudent() {
    if (studentCount >= MAX) {
        printf("Danh sach sinh vien da day!\n");
        return;
    }

    char studentId[10];
    int idExists = 0;

    do {
        printf("Nhap ma sinh vien: ");
        scanf("%9s", studentId);
        getchar();

        idExists = 0;
        for (int i = 0; i < studentCount; i++) {
            if (strcmp(students[i].studentId, studentId) == 0) {
                idExists = 1;
                break;
            }
        }

        if (idExists) {
            printf("Ma sinh vien da ton tai, vui long nhap ma khac!\n");
        } else {
            break;
        }
    } while (idExists);

    // Nh?p thông tin sinh viên
    strcpy(students[studentCount].studentId, studentId);
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

// Hàm luu danh sách sinh viên vào file
void saveStudentsToFile() {
    FILE *file = fopen(FILE_PATH, "wb");  // M? file ? ch? d? ghi nh? phân
    if (file == NULL) {
        printf("Loi khi mo file!\n");
        return;
    }
    size_t written = fwrite(students, sizeof(Student), studentCount, file);  // Ghi d? li?u vào file
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

    printf("\n**** All Students ****\n");
    printf("+============+===================+====================+===============+===========+\n");
    printf("| %-10s | %-17s | %-18s | %-13s | %-9s |\n", "ID", "Name", "Email", "Phone", "Course");
    printf("+============+===================+====================+===============+===========+\n");

    for (int i = 0; i < studentCount; i++) {
        printf("| %-10s | %-17s | %-18s | %-13s | %-9d |\n", 
               students[i].studentId, students[i].name, 
               students[i].email, students[i].phone, i + 1);
        printf("+------------+-------------------+--------------------+---------------+-----------+\n");
    }

    backToMenu();  // Quay l?i menu chính
}

// Hàm c?p nh?t thông tin sinh viên
void updateStudent() {
    char studentId[10];
    printf("Nhap ma sinh vien muon sua: ");
    scanf("%9s", studentId);
    getchar();

    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].studentId, studentId) == 0) {
            printf("Nhap ten moi: ");
            fgets(students[i].name, sizeof(students[i].name), stdin);
            strtok(students[i].name, "\n");

            printf("Nhap email moi: ");
            fgets(students[i].email, sizeof(students[i].email), stdin);
            strtok(students[i].email, "\n");

            printf("Nhap so dien thoai moi: ");
            scanf("%19s", students[i].phone);
            getchar();

            saveStudentsToFile();
            printf("\nThong tin sinh vien da duoc cap nhat thanh cong!\n");
            return;
        }
    }
    printf("Sinh vien voi ma ID '%s' khong ton tai!\n", studentId);
}

// Hàm tìm ki?m sinh viên theo tên
void searchStudentByName() {
    char searchName[50];
    printf("Nhap ten sinh vien muon tim kiem: ");
    fgets(searchName, sizeof(searchName), stdin);
    strtok(searchName, "\n");

    for (int i = 0; i < studentCount; i++) {
        if (strstr(students[i].name, searchName) != NULL) {
            printf("ID: %s, Ten: %s, Email: %s, Phone: %s\n", students[i].studentId, students[i].name, students[i].email, students[i].phone);
        }
    }
}

// Hàm xóa sinh viên kh?i danh sách
void deleteStudent() {
    if (studentCount == 0) {
        printf("Danh sach sinh vien dang trong!\n");
        return;
    }

    char studentId[10];
    printf("Nhap ma sinh vien muon xoa: ");
    scanf("%9s", studentId);
    getchar();

    int foundIndex = -1;
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].studentId, studentId) == 0) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        printf("Khong tim thay sinh vien voi ID '%s'!\n", studentId);
        return;
    }

    for (int i = foundIndex; i < studentCount - 1; i++) {
        students[i] = students[i + 1];
    }
    studentCount--;
    saveStudentsToFile();
    printf("Sinh vien da duoc xoa thanh cong!\n");
}

// Hàm quay l?i menu chính
void backToMenu() {
    char option;
    printf("\nGo back(b)? or Exit(0)?: ");
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

