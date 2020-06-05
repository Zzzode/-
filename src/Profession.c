//
// Created by ZODE on 2020/6/1.
//

#include "../include/Profession.h"
#include "../include/DataManager.h"
#include "../include/Menu.h"
#include <stdio.h>
#include <string.h>

int LoginProfession(int id, int passwd){
    FILE *fp;
    int LoginFlag = 0;
    int listCount = 0;

    // 结构体初始化
    ProfessionList *thisList = (ProfessionList *) malloc(sizeof(ProfessionList));
    ProfessionList *ptr = thisList;
    thisList->next = NULL;
    thisList->id = 0;

    // 判断数据文件是否存在
    if ((fp = fopen("Professions.txt", "r")) == NULL) {
        puts("Professions.txt文件不存在.");
        return 0;
    }

    // 从文件中查询链表中教授信息
    while (!feof(fp)) {
        ProfessionList *tmpNode = (ProfessionList *) malloc(sizeof(ProfessionList));
        if (fread(tmpNode, sizeof(ProfessionList), 1, fp) == 1) {
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
        printf("Professions.txt文件中没有记录.\n");
        return 0;
    }

    while (ptr->next != NULL) {
        ptr = ptr->next;
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
    }

    if (LoginFlag == 0) {
        puts("教授不存在.");
        return 0;
    }
    return Professions;

    /// 开始教授操作
    ShowProfessionMenu(ptr);
}

void ModifyCourseName(ProfessionList *prof, int courseId){
    int listCount = 0; /*m是记录的条数*/
    char ch[2];
    char newName[30];
    FILE *fp;

    // 结构体初始化
    CourseList *thisList = (CourseList *) malloc(sizeof(CourseList));
    CourseList *thisListHead = thisList;

    thisList->next = NULL;
    thisList->id = 0;

    if ((fp = fopen("Courses.txt", "r")) == NULL) {
        printf("文件不存在.\n");
        return;
    }

    while (!feof(fp)) {
        CourseList *tmpNode = (CourseList *) malloc(sizeof(CourseList));
        if (fread(tmpNode, sizeof(CourseList), 1, fp) == 1) {
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

    if ((fp = fopen("Courses.txt", "wb+")) == NULL) {
        printf("文件不存在.\n");
        return;
    }

    printf("修改课程名(y/n):");
    scanf("%s", ch);
    if (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0) {
        CourseList *ptr = thisListHead;

        while (ptr->next != NULL) {
            ptr = ptr->next;
            if (ptr->id == courseId && prof->id == ptr->profId)
                break;
        }

        if (ptr->id != courseId) {
            puts("未查询到课程.");
            ptr = thisListHead;
            while (ptr->next != NULL) {
                ptr = ptr->next;
                fwrite(ptr, sizeof(struct Course), 1, fp);
            }
            return;
        }
        if (prof->id != ptr->profId){
            puts("不是本课程教授，无法修改");
            return;
        }

        printf("正在修改课程 %s\n", ptr->courseName);
        printf("请输入修改后的课程名称: ");
        scanf("%s", ptr->courseName);
        strcpy(newName, ptr->courseName);

        ptr = thisListHead;
        while (ptr->next != NULL) {
            ptr = ptr->next;
            if (fwrite(ptr, sizeof(struct Course), 1, fp) != 1) {
                puts("修改课程失败.");
                return;
            }
        }
    }
    printf("修改成功，课程名为%s", newName);
}

// FIXME
void pInsertStudents(ProfessionList *prof, int courseId){
    int listStuCount = 0, listClassCount = 0, listCourseStuCount = 0;
    char course[] = "Course_", txt[] = ".txt", cid[2], ch[2];
    FILE *stuFp, *courseFp, *thisCourseFp;

    /// 将courseId转换成字符串
    itoa(courseId, cid, 10);
    char *courseTxt = (char *)malloc(strlen(course) + strlen(txt) + strlen(cid));
    sprintf(courseTxt, "%s%s%s", course, cid, txt);
//    printf("%s", courseTxt);

    // 所有学生的结构体初始化
    StudentList *thisStuList = (StudentList *) malloc(sizeof(StudentList));
    StudentList *thisStuHead = thisStuList;
    thisStuList->next = NULL;
    thisStuList->id = 0;
    thisStuList->classId = 0;

    StudentList *thisCourseStuList = (StudentList *) malloc(sizeof(StudentList));
    StudentList *thisCourseStuHead = thisCourseStuList;
    thisCourseStuList->next = NULL;
    thisCourseStuList->id = 0;
    thisCourseStuList->classId = 0;

    // 所有课程的结构体初始化
    CourseList *thisCourseList = (CourseList *) malloc(sizeof(CourseList));
    CourseList *thisCourseHead = thisCourseList;
    thisCourseList->next = NULL;
    thisCourseList->id = 0;
    thisCourseList->profId = 0;

    // 打开文件
    if ((stuFp = fopen("Students.txt", "r")) == NULL) {
        printf("学生文件不存在！\n");
        return;
    }

    if ((courseFp = fopen("Courses.txt", "r")) == NULL) {
        printf("课程文件不存在！\n");
        return;
    }

    if ((thisCourseFp = fopen(courseTxt, "r")) == NULL) {
        printf("本节课程文件不存在！\n");
        return;
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
    while (!feof(thisCourseFp)) {
        StudentList *tmpNode = (StudentList *) malloc(sizeof(StudentList));
        size_t size = sizeof(StudentList);
        size_t read = fread(tmpNode, size, 1, thisCourseFp);
        if (read == 1) {
            listCourseStuCount++;
            tmpNode->next = NULL;
            thisCourseStuList->next = tmpNode;
            thisCourseStuList = thisCourseStuList->next;
            if (thisCourseStuList == NULL)
                break;
        }
    }
    fclose(thisCourseFp);
    while (!feof(courseFp)) {
        CourseList *tmpNode = (CourseList *) malloc(sizeof(CourseList));
        size_t size = sizeof(CourseList);
        size_t read = fread(tmpNode, size, 1, courseFp);
        if (read == 1) {
            listClassCount++;
            tmpNode->next = NULL;
            thisCourseList->next = tmpNode;
            thisCourseList = thisCourseList->next;
            if (thisCourseList == NULL)
                break;
        }
    }
    fclose(courseFp);

    if (listStuCount == 0)
        printf("Students.txt文件中没有记录\n");
    if (listClassCount == 0)
        printf("Courses.txt文件中没有记录\n");
    if (listCourseStuCount == 0)
        printf("%s文件中没有记录\n", courseTxt);

    /// 再次打开txt文件
    if ((thisCourseFp = fopen(courseTxt, "ab+")) == NULL) {
        printf("文件不存在\n");
        return;
    }

    printf("输入学生信息(y/n):");
    scanf("%s", ch);
    while (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0) {
        /// 初始化学生临时节点
        int id;

        /// 初始化两个链表的指针
        StudentList *stuPtr = thisStuHead;
        StudentList *courseStuPtr = thisCourseStuHead;
        CourseList *coursePtr = thisCourseHead;

        printf("学号id:");
        scanf("%d", &id);

        /// 判断当前学生是否存在
        while (stuPtr->next != NULL){
            stuPtr = stuPtr->next;
            if (id == stuPtr->id) {
                printf("查找到学生%s存在\n", stuPtr->name);
                break;
            }
        }
        if (id != stuPtr->id){
            printf("学生不存在\n");
            return;
        }

        /// 判断当前课程是否存在
        while (coursePtr->next != NULL){
            coursePtr = coursePtr->next;
            if (courseId == coursePtr->id) {
                printf("课程 %s 存在\n", coursePtr->courseName);
                break;
            }
        }
        if (courseId != coursePtr->id){
            printf("课程不存在\n");
            return;
        }
        if (prof->id != coursePtr->profId){
            printf("不是本节课的教师\n");
            return;
        }

        while (courseStuPtr->next != NULL){
            courseStuPtr = courseStuPtr->next;
            if (id == courseStuPtr->id){
                printf("学生 %s 已在本课程中", courseStuPtr->name);
                return;
            }
        }

        size_t size = sizeof(StudentList);
        if (fwrite(stuPtr, size, 1, thisCourseFp) == 1) {
            StudentList *tmpStuNode = (StudentList *) malloc(sizeof(StudentList));

            tmpStuNode->id = stuPtr->id;
            strcpy(tmpStuNode->name, stuPtr->name);
            tmpStuNode->password = stuPtr->password;
            tmpStuNode->classId = stuPtr->classId;

            courseStuPtr->next = tmpStuNode;
            courseStuPtr = courseStuPtr->next;
            courseStuPtr->next = NULL;
            printf("%s 被添加\n", stuPtr->name);
        }
        else {
            printf("保存失败，按任意键.");
            getchar();
        }

        printf("继续(y/n):"); /*询问是否继续*/
        scanf("%s", ch);
    }
    fclose(thisCourseFp);
    printf("学生信息录入成功.\n");
}

// FIXME
void pDeleteStudents(ProfessionList *prof){
    ;
}

/// FIXME
void ShowStuList(ProfessionList *prof, int courseId){
    int listCount = 0; /*m是记录的条数*/
    char nameList;
//    char ch[2];
    FILE *fp;

    // 结构体初始化
    CourseList *thisList = (CourseList *) malloc(sizeof(CourseList));
    CourseList *ptr = thisList;
    thisList->next = NULL;
    thisList->id = 0;

    if ((fp = fopen("Courses.txt", "a+")) == NULL) {
        printf("文件不存在.\n");
        return;
    }

    while (!feof(fp) && thisList != NULL) {
        CourseList *tmpNode = (CourseList *) malloc(sizeof(CourseList));
        if (fread(tmpNode, sizeof(struct Student), 1, fp) == 1) {
            listCount++;
            tmpNode->next = NULL;
            thisList->next = tmpNode;
            thisList = thisList->next;
        }
    }
    fclose(fp);

    if (listCount == 0) {
        printf("文件中没有记录\n");
        return;
    }

    while (ptr != NULL){
        if (ptr->id == courseId && ptr->profId == prof->id)
            break;
        ptr = ptr->next;
    }
    if (ptr == NULL){
        puts("没有查到课程.");
        return;
    }

//    for (nameList = ptr->stuList; *nameList != NULL; nameList++)
//        puts(*nameList);

    puts("打印完成.");
}