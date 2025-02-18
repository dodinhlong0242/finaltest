#ifndef FUNCTION_H
#define FUNCTION_H

#include "datatype.h"

// Student management functions
void addStudent();
void listStudents();
void saveStudentsToFile();
void loadStudentsFromFile();
void updateStudent();
void deleteStudent();
void searchStudentByName();
void backToMenu();
void flush();  // Declare flush function
void showMenu();  // Declare showMenu function
void sortStudentsByName();
void showStudentMenu();  // Declare showStudentMenu function

// Teacher management functions
void addTeacher();
void listTeachers();
void updateTeacher();
void deleteTeacher();
void searchTeacher();
void assignClassToTeacher();
void showTeacherMenu();  // Declare showTeacherMenu function

// Class management functions
void addClass();
void listClasses();
void updateClass();
void deleteClass();
void classDetails();
void addStudentToClass();
void removeStudentFromClass();
void sortClassByName();
void showClassMenu();  // Declare showClassMenu function

// Utility functions for printing with color
void printWithColor(const char* text, int colorIndex);
void printWithBoldColor(const char* text, int colorIndex);

#endif

