//
// Created by zhang on 2020/5/31.
//

#include "../include/Students.h"
#include "../include/DataManager.h"
#include "../include/Menu.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int LoginStudent(int id, int passwd) {
    FILE *fp;
    int LoginFlag = 0;
    int listCount = 0;

    // 结构体初始化
    StudentList *thisList = (StudentList *) malloc(sizeof(StudentList));
    StudentList *ptr = thisList;

    thisList->next = NULL;
    thisList->id = 0;

    // 判断数据文件是否存在
    if ((fp = fopen("Students.txt", "r")) == NULL) {
        puts("Students.txt文件不存在.");
        return 0;
    }

    // 从文件中查询链表中学生信息
    while (!feof(fp)) {
        StudentList *tmpNode = (StudentList *) malloc(sizeof(StudentList));
        if (fread(tmpNode, sizeof(struct Student), 1, fp) == 1) {
            listCount++;
            tmpNode->next = NULL;
            thisList->next = tmpNode;
            thisList = thisList->next;
            if (thisList == NULL)
                break;
        }
    }

    fclose(fp);

    if (listCount == 0) {
        printf("Students.txt文件中没有记录.\n");
        return 0;
    }

    while (ptr != NULL) {
        ptr = ptr->next;
        if (id == ptr->id) {
            printf("查询到学生存在.");
            if (ptr->password == passwd) {
                printf("密码正确，登陆成功 %s 同学\n", ptr->name);
                LoginFlag = 1;
                break;
            } else {
                printf("密码错误\n");
                return 0;
            }
        }
    }

    if (LoginFlag == 0) {
        puts("学生不存在.");
        return 0;
    }
    return Students;
    /// 开始学生操作
    ShowStudentMenu(ptr);
}

/// 修改学生信息
void ChangeMyInfo(StudentList *stu) {
    int listCount = 0;
    char ch[2];
    char newName[15];
    FILE *fp;

    // 结构体初始化
    StudentList *thisList = (StudentList *) malloc(sizeof(StudentList));
    StudentList *thisListHead = thisList;

    thisList->next = NULL;
    thisList->id = 0;

    if ((fp = fopen("Students.txt", "r")) == NULL) {
        printf("文件不存在.\n");
        return;
    }

    while (!feof(fp)) {
        StudentList *tmpNode = (StudentList *) malloc(sizeof(StudentList));
        if (fread(tmpNode, sizeof(StudentList), 1, fp) == 1) {
            listCount++;
            tmpNode->next = NULL;
            thisList->next = tmpNode;
            thisList = thisList->next;
            if (thisList == NULL)
                break;
        }
    }
    fclose(fp);

    if (listCount == 0)
        printf("文件中没有记录.\n");

    if ((fp = fopen("Students.txt", "wb+")) == NULL) {
        printf("文件不存在.\n");
        return;
    }

    printf("修改姓名(y/n):");
    scanf("%s", ch);
    if (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0) {
        StudentList *ptr = thisListHead;

        while (ptr->next != NULL) {
            ptr = ptr->next;
            if (ptr->id == stu->id)
                break;
        }
        if (ptr->id != stu->id){
            printf("学生不存在\n");
            return;
        }

        printf("正在修改姓名 %s\n", ptr->name);
        printf("请输入修改后的姓名: ");
        scanf("%s", ptr->name);
        strcpy(newName, ptr->name);

        ptr = thisListHead;
        while (ptr->next != NULL) {
            ptr = ptr->next;
            if (fwrite(ptr, sizeof(struct Course), 1, fp) != 1) {
                puts("修改姓名失败.");
                return;
            }
        }
    }
    printf("修改成功，学生姓名为 %s", newName);
}

/// 输出所有课程的成绩
void CheckGrade(StudentList *stu) {
    int listGradeCount = 0, sum = 0, allCredit = 0;
    char grade[] = "GradeStu_", txt[] = ".txt", sid[2];
    FILE *gradeFp;

    /// 将stuId转换成字符串
    itoa(stu->id, sid, 10);
    char *courseTxt = (char *) malloc(strlen(grade) + strlen(txt) + strlen(sid));
    sprintf(courseTxt, "%s%s%s", grade, sid, txt);
//    printf("%s", classTxt);

    // 成绩结构体初始化
    GradeList *thisList = (GradeList *) malloc(sizeof(GradeList));
    GradeList *thisHead = thisList;
    thisList->next = NULL;
    thisList->grade = 0;

    /// 读取学生成绩信息文件
    if ((gradeFp = fopen(courseTxt, "r")) == NULL) {
        printf("文件不存在.\n");
        return;
    }

    // 存储数据
    while (!feof(gradeFp)) {
        GradeList *tmpNode = (GradeList *) malloc(sizeof(GradeList));
        if (fread(tmpNode, sizeof(GradeList), 1, gradeFp) == 1) {
            listGradeCount++;
            tmpNode->next = NULL;
            thisList->next = tmpNode;
            thisList = thisList->next;
            if (thisList == NULL)
                break;
        }
    }
    fclose(gradeFp);

    if (listGradeCount == 0) {
        printf("%s 没有成绩记录.\n", stu->name);
        return;
    }

    while (thisHead->next != NULL) {
        thisHead = thisHead->next;
        printf("课程id: %d, 课程名: %s, 成绩: %d, 学分: %d", thisHead->courseId, thisHead->courseName, thisHead->grade,
               thisHead->credit);
        sum += thisHead->credit * thisHead->grade;
        allCredit += thisHead->credit;
    }
    printf("%s 平均成绩(zju计算百分制): %d", stu->name, sum/allCredit);
}

/// 输出课程列表
void CheckCourses(StudentList *stu) {
    int listGradeCount = 0, sum = 0, allCredit = 0;
    char stuCourse[] = "CourseStu_", txt[] = ".txt", sid[2];
    FILE *gradeFp;

    /// 将stuId转换成字符串
    itoa(stu->id, sid, 10);
    char *courseTxt = (char *) malloc(strlen(stuCourse) + strlen(txt) + strlen(sid));
    sprintf(courseTxt, "%s%s%s", stuCourse, sid, txt);
//    printf("%s", classTxt);

    // 成绩结构体初始化
    CourseList *thisList = (CourseList *) malloc(sizeof(CourseList));
    CourseList *thisHead = thisList;
    thisList->next = NULL;
    thisList->id = 0;
    thisList->credit = 0;
    thisList->profId = 0;

    /// 读取学生成绩信息文件
    if ((gradeFp = fopen(courseTxt, "r")) == NULL) {
        printf("文件不存在.\n");
        return;
    }

    // 存储数据
    while (!feof(gradeFp)) {
        CourseList *tmpNode = (CourseList *) malloc(sizeof(CourseList));
        if (fread(tmpNode, sizeof(CourseList), 1, gradeFp) == 1) {
            listGradeCount++;
            tmpNode->next = NULL;
            thisList->next = tmpNode;
            thisList = thisList->next;
            if (thisList == NULL)
                break;
        }
    }
    fclose(gradeFp);

    if (listGradeCount == 0) {
        printf("%s 没有课程记录.\n", stu->name);
        return;
    }

    while (thisHead->next != NULL) {
        thisHead = thisHead->next;
        printf("课程id: %d, 课程名: %s, 学分: %d", thisHead->id, thisHead->courseName, thisHead->credit);
        sum ++;
        allCredit += thisHead->credit;
    }
    printf("%s 共 %d 节课程, 总学分 %d", stu->name, sum, allCredit);
}