//
// Created by ZODE on 2020/6/1.
//

#include "InstituteManager.h"
#include "DataManager.h"
#include "Menu.h"
#include "initial.h"
#include <stdio.h>
#include <string.h>

int LoginInstManager(int id, int passwd){
    FILE *fp;
    int LoginFlag = 0;
    int listCount = 0;
    // 结构体初始化
    InstManagerList *thisList = (InstManagerList *) malloc(sizeof(InstManagerList));
    InstManagerList *ptr = thisList;
    thisList->next = NULL;
    thisList->id = 0;

    // 判断数据文件是否存在
    if ((fp = fopen("InstManager.txt", "r")) == NULL) {
        puts("InstManager.txt文件不存在.");
        return 0;
    }

    // 从文件中查询链表中学生信息
    while (!feof(fp)) {
        InstManagerList *tmpNode = (InstManagerList *) malloc(sizeof(InstManagerList));
        if (fread(tmpNode, sizeof(InstManagerList), 1, fp) == 1) {
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
        printf("InstManager.txt文件中没有记录.\n");
        return 0;
    }

    while (ptr != NULL) {
        if (id == ptr->id) {
            if (ptr->password == passwd) {
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
        puts("管理员不存在.");
        return 0;
    }
    return InstManagers;
    /// 开始学生操作
    ShowInstManagerMenu(ptr);
}

void CreateClass(){
    int InClassCount = 0;
    char ch[2];
    FILE *classFp;

    // 教授结构体初始化
    ClassList *thisList = (ClassList *) malloc(sizeof(ClassList));
    ClassList *thisHead = thisList;

    thisList->next = NULL;
    thisList->id = 0;

    /// 读取教授信息文件
    if ((classFp = fopen("Classes.txt", "r")) == NULL) {
        printf("文件不存在.\n");
        return;
    }

    // 存储数据
    while (!feof(classFp)) {
        ClassList *tmpNode = (ClassList *) malloc(sizeof(ClassList));
        if (fread(tmpNode, sizeof(ClassList), 1, classFp) == 1) {
            InClassCount++;
            tmpNode->next = NULL;
            thisList->next = tmpNode;
            thisList = thisList->next;
            if (thisList == NULL)
                break;
        }
    }
    fclose(classFp);

    if (InClassCount == 0)
        printf("文件中没有记录.\n");

    if ((classFp = fopen("Classes.txt", "ab+")) == NULL) {
        printf("文件不存在.\n");
        return;
    }

    printf("输入班级信息(y/n):");
    scanf("%s", ch);
    while (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0) {
        ClassList *tmpNode = (ClassList *) malloc(sizeof(ClassList));
        ClassList *classPtr = thisHead;

        printf("班级id: "); // 教师编号4位
        scanf("%d", &tmpNode->id);
        printf("专业名称: ");
        scanf("%s", tmpNode->majorName);

        /// 判断当前教授是否存在
        while (classPtr->next != NULL){
            classPtr = classPtr->next;
            if (tmpNode->id == classPtr->id) {
                printf("班级id已经存在，按任意键继续.");
                getchar();
                fclose(classFp);
                return;
            }
        }

        if (fwrite(tmpNode, sizeof(ClassList), 1, classFp) == 1) {
            classPtr->next = tmpNode;
            classPtr = classPtr->next;
            classPtr->next = NULL;
            printf("%s%d 班级被保存\n", tmpNode->majorName, tmpNode->id);
        } else {
            printf("保存失败，按任意键.");
            getchar();
        }

        printf("继续(y/n):");
        scanf("%s", ch);
    }
    fclose(classFp);
    printf("班级创建成功.\n");
}

/// ! 删除班级之后 班级中的学生以及管理员并不会被删除
void DeleteClass(int classId){
    int listClassCount = 0, isDelete = 0;
    char ch[2];
    FILE *classFp;

    // 结构体初始化
    ClassList *thisList = (ClassList *) malloc(sizeof(ClassList));
    ClassList *thisHead = thisList;

    thisList->next = NULL;
    thisList->id = 0;

    /// 读取信息文件
    if ((classFp = fopen("Classes.txt", "r")) == NULL) {
        printf("文件不存在.\n");
        return;
    }

    // 存储数据
    while (!feof(classFp)) {
        ClassList *tmpNode = (ClassList *) malloc(sizeof(ClassList));
        if (fread(tmpNode, sizeof(ClassList), 1, classFp) == 1) {
            listClassCount++;
            tmpNode->next = NULL;
            thisList->next = tmpNode;
            thisList = thisList->next;
            if (thisList == NULL)
                break;
        }
    }
    fclose(classFp);

    if (listClassCount == 0)
        printf("文件中没有记录.\n");

    printf("确定要删除吗(y/n):");
    scanf("%s", ch);
    while (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0) {
        if ((classFp = fopen("Classes.txt", "wb+")) == NULL) {
            printf("文件不存在.\n");
            return;
        }

        ClassList *tmpNode = (ClassList *) malloc(sizeof(ClassList));
        ClassList *classPtr = thisHead;

        /// 判断当前班级是否存在
        while (classPtr->next != NULL){
            tmpNode = classPtr;
            classPtr = classPtr->next;
            if (classPtr->id == classId) {
                tmpNode->next = classPtr->next;
                isDelete = 1;
                free(classPtr);
                break;
            }
        }
        classPtr = thisHead;

        while (classPtr->next != NULL){
            classPtr = classPtr->next;
            fwrite(tmpNode, sizeof(ClassList), 1, classFp);
        }

        if (isDelete == 0) {
            puts("删除失败，班级不存在");
            return;
        }

        printf("继续(y/n):");
        scanf("%s", ch);
    }
    fclose(classFp);
    printf("班级删除成功.\n");
}

void ModifyClassManager(int classId){
    int listCount = 0;
    char ch[2];
    char newName[15];
    FILE *fp;

    // 结构体初始化
    ClassManagerList *thisList = (ClassManagerList *) malloc(sizeof(ClassManagerList));
    ClassManagerList *thisListHead = thisList;

    thisList->next = NULL;
    thisList->id = 0;

    if ((fp = fopen("ClassManagers.txt", "r")) == NULL) {
        printf("文件不存在.\n");
        return;
    }

    while (!feof(fp)) {
        ClassManagerList *tmpNode = (ClassManagerList *) malloc(sizeof(ClassManagerList));
        if (fread(tmpNode, sizeof(ClassManagerList), 1, fp) == 1) {
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

    if ((fp = fopen("ClassManagerList.txt", "wb+")) == NULL) {
        printf("文件不存在.\n");
        return;
    }

    printf("修改班级管理员姓名(y/n):");
    scanf("%s", ch);
    if (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0) {
        ClassManagerList *ptr = thisListHead;

        while (ptr->next != NULL) {
            ptr = ptr->next;
            if (ptr->classId == classId)
                break;
        }
        if (ptr->classId != classId){
            printf("本班管理员不存在\n");
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
    printf("修改成功，管理员姓名为 %s", newName);
}

int InsertProfession() {
    int listProfCount = 0;
    char ch[2] = "y";
    FILE *profFp;

    // 教授结构体初始化
    ProfessionList *thisList = (ProfessionList *) malloc(sizeof(ProfessionList));
    ProfessionList *thisHead = thisList;

    thisList->next = NULL;
    thisList->id = 0;

    /// 读取教授信息文件
    if ((profFp = fopen("Professions.txt", "r")) == NULL) {
        printf("Professions.txt文件不存在.\n");
        return 0;
    }

    // 存储数据
    while (!feof(profFp)) {
        ProfessionList *tmpNode = (ProfessionList *) malloc(sizeof(ProfessionList));
        if (fread(tmpNode, sizeof(ProfessionList), 1, profFp) == 1) {
            listProfCount++;
            tmpNode->next = NULL;
            thisList->next = tmpNode;
            thisList = thisList->next;
            if (thisList == NULL)
                break;
        }
    }
    fclose(profFp);

    if (listProfCount == 0)
        printf("Professions.txt文件中没有记录.\n");

    if ((profFp = fopen("Professions.txt", "ab+")) == NULL) {
        printf("Professions.txt文件不存在.\n");
        return 0;
    }

    printf("输入教授信息(y/n): y\n");
    if (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0) {
        ProfessionList *tmpNode = (ProfessionList *) malloc(sizeof(ProfessionList));
        ProfessionList *proPtr = thisHead;

        printf("教授id: %d\n", profIdInt); // 教师编号4位
        tmpNode->id = profIdInt;

        /// 判断当前教授是否存在
        while (proPtr->next != NULL){
            proPtr = proPtr->next;
            if (tmpNode->id == proPtr->id) {
                printf("教授id已经存在\n");
                fclose(profFp);
                return 0;
            }
        }

        printf("教授名: %s\n", profName);
        strcpy(tmpNode->name, profName);
        tmpNode->password = 123456;

        if (fwrite(tmpNode, sizeof(ProfessionList), 1, profFp) == 1) {
            proPtr->next = tmpNode;
            proPtr = proPtr->next;
            proPtr->next = NULL;
            printf("%s 被保存，初始密码为123456\n", tmpNode->name);
        } else {
            printf("保存失败\n");
        }
    }
    fclose(profFp);
    printf("教授信息录入成功\n");
    return 1;
}

int InsertClassManager(int classId){
    int classManagerCount = 0, classCount = 0;
    char ch[2] = "y";
    FILE *classManagerFp, *classFp;

    // 教授结构体初始化
    ClassManagerList *thisManagerList = (ClassManagerList *) malloc(sizeof(ClassManagerList));
    ClassList *thisClassList = (ClassList *)malloc(sizeof(ClassList));
    ClassManagerList *thisManagerHead = thisManagerList;
    ClassList *thisClassHead = thisClassList;

    thisManagerList->next = NULL;
    thisManagerList->id = 0;
    thisClassList->next = NULL;
    thisClassList->id = 0;

    /// 读取信息文件
    if ((classManagerFp = fopen("ClassManagers.txt", "r")) == NULL) {
        printf("文件不存在.\n");
        return 0;
    }
    if ((classFp = fopen("Classes.txt", "r")) == NULL) {
        printf("文件不存在.\n");
        return 0;
    }

    // 存储数据
    while (!feof(classManagerFp)) {
        ClassManagerList *tmpNode = (ClassManagerList *) malloc(sizeof(ClassManagerList));
        if (fread(tmpNode, sizeof(ClassManagerList), 1, classManagerFp) == 1) {
            classManagerCount++;
            tmpNode->next = NULL;
            thisManagerList->next = tmpNode;
            thisManagerList = thisManagerList->next;
            if (thisManagerList == NULL)
                break;
        }
    }
    fclose(classManagerFp);
    while (!feof(classFp)) {
        ClassList *tmpNode = (ClassList *) malloc(sizeof(ClassList));
        if (fread(tmpNode, sizeof(ClassList), 1, classFp) == 1) {
            classCount++;
            tmpNode->next = NULL;
            thisClassList->next = tmpNode;
            thisClassList = thisClassList->next;
            if (thisClassList == NULL)
                break;
        }
    }
    fclose(classFp);

    if (classManagerCount == 0)
        printf("班级管理员文件中没有记录.\n");
    if (classCount == 0)
        printf("没有班级");

    if ((classManagerFp = fopen("ClassManagers.txt", "ab+")) == NULL) {
        printf("班级管理员文件不存在.\n");
        return 0;
    }
    if ((classFp = fopen("Classes.txt", "ab+")) == NULL) {
        printf("班级文件不存在.\n");
        return 0;
    }

    printf("输入班级管理员信息(y/n): y\n");
    if (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0) {
        ClassManagerList *tmpClassManagerNode = (ClassManagerList *) malloc(sizeof(ClassManagerList));
        ClassManagerList *classManagerPtr = thisManagerHead;
        ClassList  *classPtr = thisClassHead;

        while (classPtr->next != NULL){
            classPtr = classPtr->next;
            if (classId == classPtr->id) {
                printf("找到班级 %s%d\n", classPtr->majorName, classPtr->id);
                break;
            }
        }
        if (classPtr->id != classId){
            puts("班级不存在\n");
            fclose(classManagerFp);
            fclose(classFp);
            return 0;
        }

        tmpClassManagerNode->classId = classId;
        tmpClassManagerNode->password = 123456;

        printf("班级管理员id: %d\n", classIdInt); // 班级管理员编号3位
        tmpClassManagerNode->id = classManagerIdInt;

        /// 判断当前管理员是否存在
        while (classManagerPtr->next != NULL){
            classManagerPtr = classManagerPtr->next;
            if (tmpClassManagerNode->id == classManagerPtr->id) {
                printf("班级管理员id已经存在\n");
                fclose(classManagerFp);
                fclose(classFp);
                return 0;
            }
        }

        printf("班级管理员名: %s\n", classManagerName);
        strcpy(tmpClassManagerNode->name, classManagerName);

        if (fwrite(tmpClassManagerNode, sizeof(ClassManagerList), 1, classManagerFp) == 1) {
            classManagerPtr->next = tmpClassManagerNode;
            classManagerPtr = classManagerPtr->next;
            classManagerPtr->next = NULL;
            printf("%s 被保存，初始密码为123456\n", tmpClassManagerNode->name);
        } else
            printf("保存失败\n");
    }
    fclose(classManagerFp);
    fclose(classFp);
    printf("班级管理员信息录入成功.\n");
    return 1;
}

void InsertCourses(){
    int listCourseCount = 0, listProfCount = 0;
    char ch[2];
    FILE *courseFp, *proFp;

    // 结构体初始化
    CourseList *thisCourseList = (CourseList *) malloc(sizeof(CourseList));
    ProfessionList *thisProfList = (ProfessionList *) malloc(sizeof(ProfessionList));
    CourseList *thisCourseHead = thisCourseList;
    ProfessionList *thisProfHead = thisProfList;
    thisCourseList->next = NULL;
    thisCourseList->id = 0;
    thisProfList->next = NULL;
    thisProfList->id = 0;

    if ((courseFp = fopen("Courses.txt", "r")) == NULL) {
        printf("文件不存在.\n");
        return;
    }
    if ((proFp = fopen("Professions.txt", "r")) == NULL) {
        printf("文件不存在.\n");
        return;
    }

    while (!feof(courseFp)) {
        CourseList *tmpNode = (CourseList *) malloc(sizeof(CourseList));
        if (fread(tmpNode, sizeof(CourseList), 1, courseFp) == 1) {
            listCourseCount++;
            tmpNode->next = NULL;
            thisCourseList->next = tmpNode;
            thisCourseList = thisCourseList->next;
            if (thisCourseList == NULL)
                break;
        }
    }
    fclose(courseFp);
    while (!feof(proFp)) {
        ProfessionList *tmpNode = (ProfessionList *) malloc(sizeof(ProfessionList));
        if (fread(tmpNode, sizeof(ProfessionList), 1, proFp) == 1) {
            listProfCount++;
            tmpNode->next = NULL;
            thisProfList->next = tmpNode;
            thisProfList = thisProfList->next;
            if (thisProfList == NULL)
                break;
        }
    }
    fclose(proFp);

    if (listCourseCount == 0)
        printf("课程文件中没有记录\n");
    if (listProfCount == 0)
        printf("教授文件中没有记录\n");

    if ((courseFp = fopen("Courses.txt", "ab+")) == NULL) {
        printf("课程文件不存在.\n");
        return;
    }

    printf("输入课程信息(y/n):");
    scanf("%s", ch);
    while (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0) {
        CourseList *tmpNode = (CourseList *) malloc(sizeof(CourseList));
        CourseList *coursePtr = thisCourseHead;
        ProfessionList *profPtr = thisProfHead;

        printf("课程id: ");
        scanf("%d", &tmpNode->id);

        while (coursePtr->next != NULL) {
            coursePtr = coursePtr->next;
            if (tmpNode->id == coursePtr->id) {
                printf("课程id已经存在，按任意键继续.");
                getchar();
                fclose(courseFp);
                return;
            }
        }

        printf("课程名称: ");
        scanf("%s", tmpNode->courseName);
        printf("教授id: ");
        scanf("%d", &tmpNode->profId);
        printf("学分: ");
        scanf("%d", &tmpNode->credit);

        while (profPtr->next != NULL) {
            profPtr = profPtr->next;
            if (tmpNode->profId == profPtr->id) {
                printf("查找到 %s 教授\n", profPtr->name);
                break;
            }
        }
        if (tmpNode->profId != profPtr->id){
            printf("没有这位教授\n");
            return;
        }

        if (fwrite(tmpNode, sizeof(CourseList), 1, courseFp) == 1) {
            coursePtr->next = tmpNode;
            coursePtr = coursePtr->next;
            coursePtr->next = NULL;
            printf("%s 被保存\n", tmpNode->courseName);
        } else{
            printf("保存失败，按任意键.");
            getchar();
        }

        printf("继续(y/n):"); /*询问是否继续*/
        scanf("%s", ch);
    }
    fclose(courseFp);
    printf("课程信息录入成功.\n");
}