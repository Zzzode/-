//
// Created by ZODE on 2020/5/30.
//

#ifndef STUDENTS_MANAGER_DATAMANAGER_H
#define STUDENTS_MANAGER_DATAMANAGER_H

#include <stdlib.h>
#include <stdio.h>

/// 用户身份
enum Identity{
    InstManagers = 1, Professions = 2,
    ClassManager = 3, Students = 4, SuperAdmin = 5
};

/// 结构体声明
typedef struct Grade{
    int grade;
    int courseId;
    int credit;
    char courseName[30];
    struct Grade *next;
}GradeList;

typedef struct Course{
    int id;
    int profId;
    int credit;
    char courseName[30];
    struct Course *next;
}CourseList;

typedef struct Student{
    int id;
    int classId;
    char name[15];
    int password;
//    GradeList *grade;
//    CourseList *courses;
    struct Student *next;
}StudentList;

typedef struct ClassManager{
    int id;
    int classId;
    char name[15];
    int password;
    struct ClassManager *next;
}ClassManagerList;

typedef struct Profession{
    int id;
    char name[15];
    int password;
    struct Profession *next;
}ProfessionList;

typedef struct InstManager{
    int id;
    int instId;
    char name[15];
    int password;
    struct InstManager *next;
}InstManagerList;

typedef struct Class{
    int id;
    char majorName[30];
    struct Class *next;
}ClassList;

typedef struct Institute{
    int id;
    char instName[30];
    struct Institute *next;
}InstituteList;

/// 全局变量声明
StudentList *studentList;

/// 添加用户
void InsertUser(int id, int passwd, int identity);
/// 数字转字符串工具
char *itoa(int num, char *str, int radix);

#endif //STUDENTS_MANAGER_DATAMANAGER_H
