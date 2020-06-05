//
// Created by ZODE on 2020/6/1.
//

#include "SuperAdmin.h"
#include "ClassManager.h"
#include "InstituteManager.h"
#include "DataManager.h"
#include "initial.h"
#include <stdio.h>
#include <string.h>

// TODO 添加学院权限管理
int LoginAdmin(){
    int select = 0, classId = 0, instId = 0;
    printf("请选择管超级理员操作：1添加学生 2添加教授 3添加学院管理员 4添加班级管理员 5添加课程 6添加学院: ");
    scanf("%d", &select);

    switch (select) {
        case 1:
            printf("请输入添加的学生班级：");
            scanf("%d", &classId);
            cInsertStudents(classId);
            break;
        case 2:
            InsertProfession();
            break;
        case 3:
            printf("请输入添加的管理员的学院id：");
            scanf("%d", &instId);
            InsertInstManager(instId);
            break;
        case 4:
            printf("请输入管理员班级id：");
            scanf("%d", &classId);
            InsertClassManager(classId);
            break;
        case 5:
            printf("暂时不提供此功能，请转由学院管理员操作");
//            InsertCourses();
            break;
        case 6:
            InsertInst();
            break;
        default:
            puts("无效的选项");
            break;
    }
    return SuperAdmin;
}

// FIXME 需要判断是否存在学院
int InsertInstManager(int instId) {
    int listInstCount = 0; /*m是记录的条数*/
    char ch[2] = "y";
    FILE *instFp;

    // 教授结构体初始化
    InstManagerList *thisList = (InstManagerList *) malloc(sizeof(InstManagerList));
    InstManagerList *thisHead = thisList;

    thisList->next = NULL;
    thisList->id = 0;

    /// 读取教授信息文件
    if ((instFp = fopen("InstManager.txt", "r")) == NULL) {
        printf("InstManager.txt文件不存在.\n");
        return 0;
    }

    // 存储数据
    while (!feof(instFp)) {
        InstManagerList *tmpNode = (InstManagerList *) malloc(sizeof(InstManagerList));
        if (fread(tmpNode, sizeof(InstManagerList), 1, instFp) == 1) {
            listInstCount++;
            tmpNode->next = NULL;
            thisList->next = tmpNode;
            thisList = thisList->next;
            if (thisList == NULL)
                break;
        }
    }
    fclose(instFp);

    if (listInstCount == 0)
        printf("InstManager.txt文件中没有记录.\n");

    if ((instFp = fopen("InstManager.txt", "ab+")) == NULL) {
        printf("InstManager.txt文件不存在.\n");
        return 0;
    }

    printf("输入学院管理员信息(y/n): y\n");
    if (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0) {
        InstManagerList *tmpNode = (InstManagerList *) malloc(sizeof(InstManagerList));
        InstManagerList *instPtr = thisHead;

        printf("学院管理员id(2位十进制): %d\n", instManagerIdInt); // 学院管理员编号2位
        tmpNode->id = instManagerIdInt;

        /// 判断当前是否存在
        while (instPtr->next != NULL){
            instPtr = instPtr->next;
            if (tmpNode->id == instPtr->id) {
                printf("学院管理员id已经存在\n");
                fclose(instFp);
                return 0;
            }
        }

        printf("学院管理员名: %s\n", instManagerName);
        strcpy(tmpNode->name, instManagerName);
        tmpNode->instId = instId;
        tmpNode->password = 123456;

        if (fwrite(tmpNode, sizeof(InstManagerList), 1, instFp) == 1) {
            instPtr->next = tmpNode;
            instPtr = instPtr->next;
            instPtr->next = NULL;
            printf("%s 被保存，初始密码为123456\n", tmpNode->name);
        } else
            printf("保存失败\n");
    }
    fclose(instFp);
    printf("学院管理员信息录入成功\n");
    return 1;
}

int InsertInst(){
    int listInstCount = 0; /*m是记录的条数*/
    char ch[2] = "y";
    FILE *instFp;

    // 教授结构体初始化
    InstituteList *thisList = (InstituteList *) malloc(sizeof(InstituteList));
    InstituteList *thisHead = thisList;

    thisList->next = NULL;
    thisList->id = 0;

    /// 读取教授信息文件
    if ((instFp = fopen("Institutes.txt", "r")) == NULL) {
        printf("Institutes.txt文件不存在.\n");
        return 0;
    }

    // 存储数据
    while (!feof(instFp)) {
        InstituteList *tmpNode = (InstituteList *) malloc(sizeof(InstituteList));
        if (fread(tmpNode, sizeof(InstituteList), 1, instFp) == 1) {
            listInstCount++;
            tmpNode->next = NULL;
            thisList->next = tmpNode;
            thisList = thisList->next;
            if (thisList == NULL)
                break;
        }
    }
    fclose(instFp);

    if (listInstCount == 0)
        printf("Institutes.txt文件中没有记录.\n");

    if ((instFp = fopen("Institutes.txt", "ab+")) == NULL) {
        printf("Institutes.txt文件不存在.\n");
        return 0;
    }

    printf("输入学院信息(y/n): y\n");
    if (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0) {
        InstituteList *tmpNode = (InstituteList *) malloc(sizeof(InstituteList));
        InstituteList *instPtr = thisHead;

        printf("学院id: %d\n", instIdInt); // 学院管理员编号2位
        tmpNode->id = instIdInt;
        /// 判断当前教授是否存在
        while (instPtr->next != NULL){
            instPtr = instPtr->next;
            if (tmpNode->id == instPtr->id) {
                printf("学院id已经存在\n");
                fclose(instFp);
                return 0;
            }
        }

        printf("学院名: %s\n", instName);
        strcpy(tmpNode->instName, instName);

        if (fwrite(tmpNode, sizeof(InstituteList), 1, instFp) == 1) {
            instPtr->next = tmpNode;
            instPtr = instPtr->next;
            instPtr->next = NULL;
            printf("%s 学院被保存\n", tmpNode->instName);
        } else
            printf("保存失败\n");
    }
    fclose(instFp);
    printf("学院信息录入成功.\n");
    return 1;
}