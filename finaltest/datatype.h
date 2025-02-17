#ifndef DATATYPE_H
#define DATATYPE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define MAX_COURSES 5  // Define the maximum number of courses a student can have

// Struct Date
typedef struct {
    int day, month, year;
} Date;

// Struct Course
typedef struct {
    char courseCode[20];
    char courseName[100];
} Course;

// Struct Sinh Vien
typedef struct {
    char studentId[10];
    char classroomId[10];
    char name[50];
    Date dateOfBirth;
    int gender; // 0: Nam, 1: Nu
    char email[50];
    char phone[20];
    Course courses[MAX_COURSES];  // Array to store courses for each student
    int courseCount;  // Number of courses the student is enrolled in
} Student;

// Global variables
extern Student students[MAX];
extern int studentCount;

#endif

