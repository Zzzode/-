//
// Created by ZODE on 2020/6/1.
//

#include "ClassManager.h"
#include "initial.h"
#include "Menu.h"
#include <stdio.h>
#include <string.h>
//#include <stdlib.h>

int LoginClassManager(int id, int password) {
    FILE *Fp;
    int LoginFlag = 0;
    int listCount = 0;
    // 结构体初始化
    ClassManagerList *thisList = (ClassManagerList *) malloc(sizeof(ClassManagerList));
    ClassManagerList *ptr = thisList;
    thisList->next = NULL;
    thisList->id = 0;

    // 判断数据文件是否存在
    if ((Fp = fopen("ClassManagers.txt", "r")) == NULL) {
        puts("ClassManagers.txt文件不存在.");
        return 0;
    }

    // 从文件中查询链表中学生信息
    while (!feof(Fp)) {
        ClassManagerList *tmpNode = (ClassManagerList *) malloc(sizeof(ClassManagerList));
        if (fread(tmpNode, sizeof(ClassManagerList), 1, Fp) == 1) {
            listCount++;
            tmpNode->next = NULL;
            thisList->next = tmpNode;
            thisList = thisList->next;
            if (thisList == NULL)
                break;
        }
    }
    fclose(Fp);

    if (listCount == 0) {
        printf("ClassManagers.txt文件中没有记录.\n");
        return 0;
    }

    while (ptr != NULL) {
        if (id == ptr->id) {
            if (ptr->password == password) {
                printf("密码正确，登陆成功 %s 老师\n", ptr->name);
                LoginFlag = 1;
                break;
            } else {
                printf("密码错误\n");
                return 0;
            }
        }
        ptr = ptr->next;
    }

    if (LoginFlag == 0) {
        puts("班级管理员不存在");
        return 0;
    }
    return ClassManager;
    /// 开始学生操作
    ShowClassManagerMenu(ptr);
}


int cInsertStudents(int classId) {
    int listStuCount = 0, listClassCount = 0;
    char class[] = "Class_", txt[] = ".txt", cid[2], ch[2] = "y";
    FILE *stuFp, *classFp;

    /// 将classid转换成字符串
    itoa(classId, cid, 10);
    char *classTxt = (char *)malloc(strlen(class) + strlen(txt) + strlen(cid));
    sprintf(classTxt, "%s%s%s", class, cid, txt);
//    printf("%s", classTxt);

    // 所有学生的结构体初始化
    StudentList *thisStuList = (StudentList *) malloc(sizeof(StudentList));
    StudentList *thisStuHead = thisStuList;
    thisStuList->next = NULL;
    thisStuList->id = 0;
    thisStuList->classId = 0;

    // 班级学生的结构体初始化
    StudentList *thisClassStuList = (StudentList *) malloc(sizeof(StudentList));
    StudentList *thisClassStuHead = thisClassStuList;
    thisClassStuList->next = NULL;
    thisClassStuList->id = 0;
    thisClassStuList->classId = 0;

    // 打开文件
    if ((stuFp = fopen("Students.txt", "r")) == NULL) {
        printf("Students.txt文件不存在！\n");
        return 0;
    }

    if ((classFp = fopen(classTxt, "r")) == NULL) {
        printf("%s文件不存在！\n", classTxt);
        return 0;
    }

    /// 将两个文件中的数据读取至链表中
    while (!feof(stuFp)) {
        StudentList *tmpNode = (StudentList *) malloc(sizeof(StudentList));
        size_t size = sizeof(StudentList);
        size_t read = fread(tmpNode, size, 1, stuFp);
        if (read == 1) {
            listStuCount++;
            tmpNode->next = NULL;
            thisStuList->next = tmpNode;
            thisStuList = thisStuList->next;
            if (thisStuList == NULL)
                break;
        }
    }
    fclose(stuFp);
    while (!feof(classFp)) {
        StudentList *tmpNode = (StudentList *) malloc(sizeof(StudentList));
        size_t size = sizeof(StudentList);
        size_t read = fread(tmpNode, size, 1, classFp);
        if (read == 1) {
            listClassCount++;
            tmpNode->next = NULL;
            thisClassStuList->next = tmpNode;
            thisClassStuList = thisClassStuList->next;
            if (thisClassStuList == NULL)
                break;
        }
    }
    fclose(classFp);

    if (listStuCount == 0)
        printf("Students.txt文件中没有记录\n");
    if (listClassCount == 0)
        printf("%s文件中没有记录\n", classTxt);

    /// 再次打开txt文件
    if ((stuFp = fopen("Students.txt", "ab+")) == NULL) {
        printf("文件不存在\n");
        return 0;
    }
    if ((classFp = fopen(classTxt, "ab+")) == NULL) {
        printf("%s文件不存在\n", classTxt);
        return 0;
    }

    printf("输入学生信息(y/n): y\n");
    if (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0) {
        /// 初始化学生临时节点
        StudentList *tmpStuNode = (StudentList *) malloc(sizeof(StudentList));
        /// 初始化两个链表的指针
        StudentList *stuPtr = thisStuHead;
        StudentList *classStuPtr = thisClassStuHead;

        tmpStuNode->id = stuIdInt;
        printf("学号id: %d\n", stuIdInt);
//        scanf("%d", &tmpStuNode->id);

        /// 判断当前学生是否存在
        while (stuPtr->next != NULL){
            stuPtr = stuPtr->next;
            if (tmpStuNode->id == stuPtr->id) {
                printf("Students.txt中学生id已经存在\n");
                fclose(stuFp);
                fclose(classFp);
                return 0;
            }
        }

        /// 判断当前班级的学生节点是否存在
        while (classStuPtr->next != NULL){
            classStuPtr = classStuPtr->next;
            if (tmpStuNode->id == classStuPtr->id) {
                printf("%s中学生id已经存在\n", classTxt);
                fclose(stuFp);
                fclose(classFp);
                return 0;
            }
        }

        /// 初始化学生的其他信息
        printf("姓名: %s\n", stuName);
//        scanf("%s", tmpStuNode->name);
        strcpy(tmpStuNode->name, stuName);
        tmpStuNode->password = 123456;
        tmpStuNode->classId = classId;

        size_t size = sizeof(*tmpStuNode);
        if (fwrite(tmpStuNode, size, 1, stuFp) == 1 && fwrite(tmpStuNode, size, 1, classFp) == 1) {
            stuPtr->next = tmpStuNode;
            classStuPtr->next = tmpStuNode;
            stuPtr = stuPtr->next;
            classStuPtr = classStuPtr->next;
            stuPtr->next = NULL;
            classStuPtr->next = NULL;
            printf("%s 被保存，初始密码为123456\n", tmpStuNode->name);
        }
        else
            printf("保存失败\n");
    }
    fclose(stuFp);
    fclose(classFp);

    printf("学生信息录入成功.\n");
    return 1;
}

/// 学生列表和班级列表都要改
void cModifyStudentInfo(int classId, int studentId) {
    int listStuCount = 0, listClassStuCount = 0;
    char ch[2], newName[15];
    char stuClass[] = "Class_", txt[] = ".txt", cid[2];
    FILE *stuFp, *classStuFp;

    /// 将stuId转换成字符串
    itoa(classId, cid, 10);
    char *classTxt = (char *) malloc(strlen(stuClass) + strlen(txt) + strlen(cid));
    sprintf(classTxt, "%s%s%s", stuClass, cid, txt);

    // 结构体初始化
    StudentList *thisStuList = (StudentList *) malloc(sizeof(StudentList));
    StudentList *thisStuListHead = thisStuList;
    thisStuList->next = NULL;
    thisStuList->id = 0;

    StudentList *thisClassStuList = (StudentList *) malloc(sizeof(StudentList));
    StudentList *thisClassStuListHead = thisClassStuList;
    thisClassStuList->next = NULL;
    thisClassStuList->id = 0;

    if ((stuFp = fopen("Students.txt", "r")) == NULL) {
        printf("Students.txt文件不存在.\n");
        return;
    }

    if ((classStuFp = fopen(classTxt, "r")) == NULL) {
        printf("%s文件不存在.\n", classTxt);
        return;
    }

    while (!feof(stuFp)) {
        StudentList *tmpNode = (StudentList *) malloc(sizeof(StudentList));
        if (fread(tmpNode, sizeof(StudentList), 1, stuFp) == 1) {
            listStuCount++;
            tmpNode->next = NULL;
            thisStuList->next = tmpNode;
            thisStuList = thisStuList->next;
            if (thisStuList == NULL)
                break;
        }
    }
    fclose(stuFp);
    while (!feof(classStuFp)) {
        StudentList *tmpNode = (StudentList *) malloc(sizeof(StudentList));
        if (fread(tmpNode, sizeof(StudentList), 1, classStuFp) == 1) {
            listClassStuCount++;
            tmpNode->next = NULL;
            thisClassStuList->next = tmpNode;
            thisClassStuList = thisClassStuList->next;
            if (thisClassStuList == NULL)
                break;
        }
    }
    fclose(classStuFp);

    if (listStuCount == 0)
        printf("Students.txt文件中没有记录.\n");
    if (listClassStuCount == 0)
        printf("%s文件中没有记录.\n", classTxt);

    if ((stuFp = fopen("Students.txt", "wb+")) == NULL) {
        printf("Students.txt文件不存在.\n");
        return;
    }
    if ((classStuFp = fopen(classTxt, "wb+")) == NULL) {
        printf("%s文件不存在.\n", classTxt);
        return;
    }

    printf("修改学生姓名(y/n):");
    scanf("%s", ch);
    if (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0) {
        StudentList *stuPtr = thisStuListHead;
        StudentList *classStuPtr = thisClassStuListHead;

        /// 从全校学生中找到该学生
        while (stuPtr->next != NULL) {
            stuPtr = stuPtr->next;
            if (stuPtr->id == studentId)
                break;
        }
        if (stuPtr->id != studentId){
            printf("学生不存在\n");
            return;
        }

        // 查看学生是否在本班中
        while (classStuPtr->next != NULL) {
            classStuPtr = classStuPtr->next;
            if (classStuPtr->id == studentId)
                break;
        }
        if (classStuPtr->id != studentId){
            printf("学生不在本班\n");
            return;
        }

        printf("正在修改姓名 %s\n", stuPtr->name);
        printf("请输入修改后的姓名: ");
        scanf("%s", stuPtr->name);

        strcpy(classStuPtr->name, stuPtr->name);
        strcpy(newName, stuPtr->name);

        stuPtr = thisStuListHead;
        classStuPtr = thisClassStuListHead;

        while (stuPtr->next != NULL) {
            stuPtr = stuPtr->next;
            if (fwrite(stuPtr, sizeof(StudentList), 1, stuFp) != 1) {
                puts("修改姓名失败.");
                return;
            }
        }
        while (classStuPtr->next != NULL) {
            classStuPtr = classStuPtr->next;
            if (fwrite(classStuPtr, sizeof(StudentList), 1, classStuFp) != 1) {
                puts("修改姓名失败.");
                return;
            }
        }
    }
    printf("修改成功，学生姓名为 %s", newName);
}

void cQueryStudent(int classId, int stuId) {
    FILE *Fp;
    char cid[2], stuClass[] = "Class_", txt[] = ".txt";
    int listCount = 0;

    itoa(classId, cid, 10);
    char *classTxt = (char *) malloc(strlen(stuClass) + strlen(txt) + strlen(cid));
    sprintf(classTxt, "%s%s%s", stuClass, cid, txt);

    // 结构体初始化
    StudentList *thisList = (StudentList *) malloc(sizeof(StudentList));
    StudentList *ptr = thisList;
    thisList->next = NULL;
    thisList->id = 0;

    // 判断数据文件是否存在
    if ((Fp = fopen(classTxt, "r")) == NULL) {
        printf("%s 文件不存在.", classTxt);
        return;
    }

    // 从文件中查询链表中学生信息
    while (!feof(Fp)) {
        StudentList *tmpNode = (StudentList *) malloc(sizeof(StudentList));
        if (fread(tmpNode, sizeof(StudentList), 1, Fp) == 1) {
            listCount++;
            tmpNode->next = NULL;
            thisList->next = tmpNode;
            thisList = thisList->next;
            if (thisList == NULL)
                break;
        }
    }
    fclose(Fp);

    if (listCount == 0) {
        printf("%s文件中没有记录.\n", classTxt);
        return;
    }

    while (ptr->next != NULL) {
        ptr = ptr->next;
        if (stuId == ptr->id) {
            printf("查找到 %s 学生\n", ptr->name);
            break;
        }
    }
    if (ptr->id != stuId) {
        puts("学生不在本班");
        return;
    }

    printf("学号: %d, 姓名: %s, 班级id: %d", stuId, ptr->name, ptr->classId);
}

void cDeleteStudents(int classId, int stuId) {
//    int stuListCount = 0, classListCount = 0;
//    char ch[2];
//    FILE *stuFp, *classFp;
//
//    // 结构体初始化
//    ClassList *thisClassList = (ClassList *) malloc(sizeof(ClassList));
//    StudentList *thisStuList = (StudentList *) malloc(sizeof(StudentList));
//    ClassList *ptrClass = thisClassList;
//    StudentList *ptrStudent = thisStuList;
//    thisStuList->next = NULL;
//    thisClassList->next = NULL;
//    thisStuList->id = 0;
//    thisClassList->id = 0;
//
//    // 查看文件是否存在
//    if ((stuFp = fopen("Students.txt", "r+")) == NULL) {
//        printf("学生文件不存在\n");
//        return;
//    }
//    if ((classFp = fopen("Class.txt", "r+")) == NULL) {
//        printf("班级文件不存在\n");
//        return;
//    }
//
//    // 将文件内容存进链表
//    while (!feof(stuFp) && thisStuList != NULL) {
//        StudentList *tmpNode = (StudentList *) malloc(sizeof(StudentList));
//        if (fread(tmpNode, sizeof(struct Student), 1, stuFp) == 1) {
//            stuListCount++;
//            tmpNode->next = NULL;
//            thisStuList->next = tmpNode;
//            thisStuList = thisStuList->next;
//        }
//    }
////    fclose(stuFp);
//    while (!feof(classFp) && thisClassList != NULL) {
//        ClassList *tmpNode = (ClassList *) malloc(sizeof(ClassList));
//        if (fread(tmpNode, sizeof(struct Student), 1, classFp) == 1) {
//            stuListCount++;
//            tmpNode->next = NULL;
//            thisClassList->next = tmpNode;
//            thisClassList = thisClassList->next;
//        }
//    }
////    fclose(classFp);
//    if (stuListCount == 0 || classListCount == 0)
//        printf("没有记录\n");
//
//    // 查找班级id 学生id 并修改
//    printf("是否删除学生？(y/n):");
//    scanf("%s", ch);
//    if (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0) {
//        StudentList *tmpStuNode = NULL;
//        StudentList *prevStuNode = NULL;
//        ClassList *tmpClassNode = NULL;
//        ClassList *ptrTmpClassNode = NULL;
//
//        while (ptrClass != NULL) {
//            if (classId == ptrClass->id) {
//                puts("找到classId.");
//                tmpClassNode = ptrClass;
//                ptrTmpClassNode = tmpClassNode;
//                break;
//            }
//            ptrClass = ptrClass->next;
//        }
//
//        if (ptrTmpClassNode == NULL) {
//            puts("没有该班级.");
//            return;
//        }
//
//        StudentList *ptrClassStuNode = ptrTmpClassNode->student;
//        while (ptrClassStuNode != NULL) {
//            if (stuId == ptrClassStuNode->id) {
//                puts("找到stuId.");
//                break;
//            }
//            prevStuNode = ptrClassStuNode;
//            ptrClassStuNode = ptrClassStuNode->next;
//        }
//
//        if (ptrClassStuNode == NULL) {
//            printf("班级中没有该id.");
//            return;
//        }
//
//        prevStuNode->next = ptrClassStuNode->next;
//        free(ptrClassStuNode);
//
//        while (ptrStudent != NULL) {
//            if (stuId == ptrStudent->id) {
//                tmpStuNode = ptrStudent;
//                break;
//            }
//            prevStuNode = ptrClassStuNode;
//            ptrStudent = ptrStudent->next;
//        }
//
//        prevStuNode->next = ptrStudent->next;
//        free(ptrStudent);
//    }
//    puts("删除成功");
    ;
}

// FIXME
void ShowStudentInfo(StudentList *stu) {
    ;
}