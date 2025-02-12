#ifndef DATATYPE_H
#define DATATYPE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// Struct Date
typedef struct {
    int day, month, year;
} Date;

// Struct Sinh Vien
typedef struct {
    char studentId[10];
    char classroomId[10];
    char name[50];
    Date dateOfBirth;
    int gender; // 0: Nam, 1: Nu
    char email[50];
    char phone[20];
} Student;

// Bien toan cuc
extern Student students[MAX];
extern int studentCount;

#endif
