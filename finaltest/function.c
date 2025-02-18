#include "datatype.h"
#include "function.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Teacher teachers[MAX_TEACHERS];
int teacherCount = 0;

// Hàm thêm gi?ng viên
void addTeacher() {
    printf("\n**** Them Giang Vien Moi ****\n");

    if (teacherCount >= MAX_TEACHERS) {
        printf("Danh sach giang vien da day!\n");
        return;
    }

    char teacherId[10];
    int idExists = 0;

    do {
        printf("Nhap Ma Giang Vien: ");
        scanf("%9s", teacherId);
        flush();

        idExists = 0;
        for (int i = 0; i < teacherCount; i++) {
            if (strcmp(teachers[i].teacherId, teacherId) == 0) {
                idExists = 1;
                break;
            }
        }

        if (idExists) {
            printf("Loi: Ma giang vien da ton tai.\n");
        } else {
            break;
        }
    } while (idExists);

    // Nhap thong tin giang vien
    strcpy(teachers[teacherCount].teacherId, teacherId);
    printf("Nhap Ten Giang Vien: ");
    fgets(teachers[teacherCount].name, sizeof(teachers[teacherCount].name), stdin);
    strtok(teachers[teacherCount].name, "\n");

    printf("Nhap Email: ");
    fgets(teachers[teacherCount].email, sizeof(teachers[teacherCount].email), stdin);
    strtok(teachers[teacherCount].email, "\n");

    printf("Nhap So Dien Thoai: ");
    fgets(teachers[teacherCount].phone, sizeof(teachers[teacherCount].phone), stdin);
    strtok(teachers[teacherCount].phone, "\n");

    teacherCount++;
    saveTeachersToFile();
    printf("Giang vien da duoc them thanh cong.\n");
    backToMenu();  // Quay lai menu
}

// Hàm luu danh sách gi?ng viên vào file
void saveTeachersToFile() {
    FILE *file = fopen("giangvien.dat", "wb");
    if (file == NULL) {
        printf("Loi khi mo file!\n");
        return;
    }
    size_t written = fwrite(teachers, sizeof(Teacher), teacherCount, file);
    if (written != teacherCount) {
        printf("Loi khi ghi du lieu vao file!\n");
    } else {
        printf("Danh sach giang vien da duoc luu vao file giangvien.dat\n");
    }
    fclose(file);  // Dong file sau khi ghi
}

// Hàm t?i danh sách gi?ng viên t? file
void loadTeachersFromFile() {
    FILE *file = fopen("giangvien.dat", "rb");
    if (file == NULL) {
        printf("Khong tim thay file danh sach giang vien, tao danh sach moi.\n");
        return;
    }
    teacherCount = fread(teachers, sizeof(Teacher), MAX_TEACHERS, file);
    fclose(file);
    printf("Danh sach giang vien da duoc tai thanh cong!\n");
}

// Hàm hi?n th? danh sách gi?ng viên
void listTeachers() {
    if (teacherCount == 0) {
        printf("Khong co giang vien nao!\n");
        return;
    }

    printf("\n**** Tat Ca Giang Vien ****\n");
    printf("+============+===================+====================+===============+\n");
    printf("| %-10s | %-17s | %-18s | %-13s |\n", "ID", "Ten", "Email", "So Dien Thoai");
    printf("+============+===================+====================+===============+\n");

    for (int i = 0; i < teacherCount; i++) {
        printf("| %-10s | %-17s | %-18s | %-13s |\n", 
               teachers[i].teacherId, teachers[i].name, 
               teachers[i].email, teachers[i].phone);
        printf("+------------+-------------------+--------------------+---------------+\n");
    }

    backToMenu();  // Quay lai menu
}

// Hàm quay l?i menu gi?ng viên
void backToTeacherMenu() {
    char option;
    do {
        printf("\nQuay lai menu giang vien (b)? Hoac Thoat (0)?: ");
        scanf(" %c", &option);
        flush();
        if (option == 'b') {
            return;  // Quay lai menu giang vien
        } else if (option == '0') {
            exit(0);  // Thoat chuong trinh
        } else {
            printf("Lua chon khong hop le! Thoat chuong trinh.\n");
            exit(0);  // Thoat neu lua chon khong hop le
        }
    } while (1);
}

// Hàm hi?n th? menu qu?n lý gi?ng viên
void showTeacherMenu() {
    int choice;
    do {
        printf("\n**** Menu Quan Ly Giang Vien ****\n");
        printf("1. Hien thi danh sach giang vien\n");
        printf("2. Them giang vien\n");
        printf("3. Cap nhat thong tin giang vien\n");
        printf("4. Xoa giang vien\n");
        printf("5. Tim kiem giang vien theo ten\n");
        printf("6. Sap xep danh sach giang vien\n");
        printf("7. Quay lai\n");
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                listTeachers();
                break;
            case 2:
                addTeacher();
                break;
            case 3:
                updateTeacher();
                break;
            case 4:
                deleteTeacher();
                break;
            case 5:
                searchTeacher();
                break;
            case 6:
                sortTeachersByName();
                break;
            case 7:
                return;  // Quay lai menu chinh
            default:
                printf("Lua chon khong hop le!\n");
        }
    } while (1);
}

// Hàm c?p nh?t thông tin gi?ng viên
void updateTeacher() {
    printf("\n**** Cap Nhat Thong Tin Giang Vien ****\n");

    char teacherId[10];
    printf("Nhap Ma Giang Vien: ");
    scanf("%9s", teacherId);
    flush();

    for (int i = 0; i < teacherCount; i++) {
        if (strcmp(teachers[i].teacherId, teacherId) == 0) {
            printf("Nhap Ten Moi: ");
            fgets(teachers[i].name, sizeof(teachers[i].name), stdin);
            strtok(teachers[i].name, "\n");

            printf("Nhap Email Moi: ");
            fgets(teachers[i].email, sizeof(teachers[i].email), stdin);
            strtok(teachers[i].email, "\n");

            printf("Nhap So Dien Thoai Moi: ");
            fgets(teachers[i].phone, sizeof(teachers[i].phone), stdin);
            strtok(teachers[i].phone, "\n");

            saveTeachersToFile();
            printf("Thong tin giang vien da duoc cap nhat thanh cong.\n");
            backToTeacherMenu();
            return;
        }
    }
    printf("Giang vien voi Ma ID '%s' khong ton tai!\n", teacherId);
    backToTeacherMenu();
}

// Hàm xóa gi?ng viên
void deleteTeacher() {
    printf("\n**** Xoa Giang Vien ****\n");

    char teacherId[10];
    printf("Nhap Ma Giang Vien: ");
    scanf("%9s", teacherId);
    flush();

    int foundIndex = -1;
    for (int i = 0; i < teacherCount; i++) {
        if (strcmp(teachers[i].teacherId, teacherId) == 0) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        printf("Khong tim thay giang vien voi ID '%s'!\n", teacherId);
        backToTeacherMenu();
        return;
    }

    // Di chuyen giang vien len de xoa
    for (int i = foundIndex; i < teacherCount - 1; i++) {
        teachers[i] = teachers[i + 1];
    }
    teacherCount--;
    saveTeachersToFile();
    printf("Giang vien da duoc xoa thanh cong.\n");
    backToTeacherMenu();
}

// Hàm tìm ki?m gi?ng viên theo tên
void searchTeacher() {
    char name[50];
    printf("Nhap ten giang vien can tim: ");
    getchar();  // To handle the newline character left by previous scanf
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;

    int found = 0;
    printf("\n+============+===================+====================+===============+\n");
    printf("| %-10s | %-17s | %-18s | %-13s |\n", "ID", "Ten", "Email", "So Dien Thoai");
    printf("+============+===================+====================+===============+\n");

    for (int i = 0; i < teacherCount; i++) {
        if (strstr(teachers[i].name, name) != NULL) {
            printf("| %-10s | %-17s | %-18s | %-13s |\n",
                   teachers[i].teacherId, teachers[i].name,
                   teachers[i].email, teachers[i].phone);
            found = 1;
        }
    }

    printf("+------------+-------------------+--------------------+---------------+\n");
    if (!found) {
        printf("Khong tim thay giang vien co ten: %s\n", name);
    }
    backToTeacherMenu();
}

// Hàm s?p x?p gi?ng viên theo tên
void sortTeachersByName() {
    int choice;

    printf("\nChon thu tu sap xep:\n");
    printf("1. Sap xep tang dan\n");
    printf("2. Sap xep giam dan\n");
    printf("Nhap lua chon: ");
    scanf("%d", &choice);

    for (int i = 0; i < teacherCount - 1; i++) {
        for (int j = i + 1; j < teacherCount; j++) {
            int compareResult = strcmp(teachers[i].name, teachers[j].name);

            if ((choice == 1 && compareResult > 0) || (choice == 2 && compareResult < 0)) {
                // Hoan vi giang vien
                Teacher temp = teachers[i];
                teachers[i] = teachers[j];
                teachers[j] = temp;
            }
        }
    }

    printf("\nDanh sach giang vien sau khi sap xep:\n");
    listTeachers();  // Hien thi danh sach giang vien sau khi sap xep
}

Student students[MAX];
int studentCount = 0;
const char *FILE_PATH = "hocsinh.bin";

// Ham flush input buffer
void flush() {
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF);  // Clear buffer
}

// Ham them sinh vien vao danh sach
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
        flush();

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

    // Nhap thong tin sinh vien va luu
    strcpy(students[studentCount].studentId, studentId);
    printf("Nhap Ten Sinh Vien: ");
    fgets(students[studentCount].name, sizeof(students[studentCount].name), stdin);
    strtok(students[studentCount].name, "\n");

    printf("Nhap Email: ");
    fgets(students[studentCount].email, sizeof(students[studentCount].email), stdin);
    strtok(students[studentCount].email, "\n");

    printf("Nhap So Dien Thoai: ");
    fgets(students[studentCount].phone, sizeof(students[studentCount].phone), stdin);
    strtok(students[studentCount].phone, "\n");

    printf("So Mon Hoc: ");
    int numCourses;
    scanf("%d", &numCourses);
    flush();
    if (numCourses > MAX_COURSES) {
        printf("So mon hoc qua nhieu! Vui long nhap lai.\n");
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
    backToMenu();  // Quay lai menu
}

// Ham luu danh sach sinh vien vao file
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
    fclose(file);  // Dong file sau khi ghi
}

// Ham tai danh sach sinh vien tu file
void loadStudentsFromFile() {
    FILE *file = fopen(FILE_PATH, "rb");
    if (file == NULL) {
        printf("Khong tim thay file danh sach sinh vien, tao danh sach moi.\n");
        return;
    }
    studentCount = fread(students, sizeof(Student), MAX, file);
    fclose(file);
    printf("Danh sach sinh vien da duoc tai thanh cong!\n");
}

// Ham hien thi danh sach sinh vien
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

    backToMenu();  // Quay lai menu
}

// Ham quay lai menu chinh
void backToMenu() {
    char option;
    do {
        printf("\nQuay lai menu chinh (b)? Hoac Thoat (0)?: ");
        scanf(" %c", &option);
        flush();
        if (option == 'b') {
            return;  // Quay lai menu chinh
        } else if (option == '0') {
            exit(0);  // Thoat chuong trinh
        } else {
            printf("Lua chon khong hop le! Thoat chuong trinh.\n");
            exit(0);  // Thoat neu lua chon khong hop le
        }
    } while (1);
}

// Ham hien thi menu quan ly sinh vien
void showStudentMenu() {
    int choice;
    do {
        printf("\n**** Menu Quan Ly Sinh Vien ****\n");
        printf("1. Hien thi danh sach sinh vien\n");
        printf("2. Them sinh vien\n");
        printf("3. Cap nhat thong tin sinh vien\n");
        printf("4. Xoa sinh vien\n");
        printf("5. Tim kiem sinh vien theo ten\n");
        printf("6. Sap xep danh sach sinh vien\n");
        printf("7. Quay lai\n");
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &choice);
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
                sortStudentsByName();
                break;
            case 7:
                return;  // Quay lai menu chinh
            default:
                printf("Lua chon khong hop le!\n");
        }
    } while (1);
}

// Ham cap nhat thong tin sinh vien
void updateStudent() {
    printf("\n**** Cap Nhat Thong Tin Sinh Vien ****\n");

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
    printf("Sinh vien voi Ma ID '%s' khong ton tai!\n", studentId);
    backToMenu();
}

// Ham xoa sinh vien khoi danh sach
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

    // Di chuyen sinh vien len de xoa
    for (int i = foundIndex; i < studentCount - 1; i++) {
        students[i] = students[i + 1];
    }
    studentCount--;
    saveStudentsToFile();
    printf("Sinh vien da duoc xoa thanh cong.\n");
    backToMenu();
}

// Ham tim kiem sinh vien theo ten
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

    // In bang tieu de
    printf("\n+============+===================+====================+===============+===========+\n");
    printf("| %-10s | %-17s | %-18s | %-13s | %-9s |\n", "ID", "Ten", "Email", "So Dien Thoai", "Khoa");
    printf("+============+===================+====================+===============+===========+\n");

    for (int i = 0; i < studentCount; i++) {
        // Tim kiem sinh vien theo ten (match chuoi con)
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

// Ham sap xep danh sach sinh vien theo ten
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
                // Hoan vi sinh vien
                Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }

    printf("\nDanh sach sinh vien sau khi sap xep:\n");
    listStudents();  // Hien thi danh sach sau khi sap xep
}

