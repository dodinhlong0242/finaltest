#ifndef DATATYPE_H
#define DATATYPE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define MAX_COURSES 5  // Define the maximum number of courses a student can have
#define MAX_CLASSES 50  // Define the maximum number of classes
#define MAX_TEACHERS 50  // Define the maximum number of teachers

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

// Struct Teacher
typedef struct {
    char teacherId[10];
    char name[50];
    char email[50];
    char phone[20];
} Teacher;

// Struct Class
typedef struct {
    char classId[10];
    char className[50];
    char teacherId[10];  // ID of the teacher in charge of this class
    int studentCount;    // Number of students in the class
    char studentIds[MAX];  // Array to store student IDs in this class
} Class;

// Global variables for students, teachers, and classes
extern Student students[MAX];
extern int studentCount;

extern Teacher teachers[MAX_TEACHERS];
extern int teacherCount;

extern Class classes[MAX_CLASSES];
extern int classCount;

#endif

