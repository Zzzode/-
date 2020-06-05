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

    // �ṹ���ʼ��
    StudentList *thisList = (StudentList *) malloc(sizeof(StudentList));
    StudentList *ptr = thisList;

    thisList->next = NULL;
    thisList->id = 0;

    // �ж������ļ��Ƿ����
    if ((fp = fopen("Students.txt", "r")) == NULL) {
        puts("Students.txt�ļ�������.");
        return 0;
    }

    // ���ļ��в�ѯ������ѧ����Ϣ
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
        printf("Students.txt�ļ���û�м�¼.\n");
        return 0;
    }

    while (ptr != NULL) {
        ptr = ptr->next;
        if (id == ptr->id) {
            printf("��ѯ��ѧ������.");
            if (ptr->password == passwd) {
                printf("������ȷ����½�ɹ� %s ͬѧ\n", ptr->name);
                LoginFlag = 1;
                break;
            } else {
                printf("�������\n");
                return 0;
            }
        }
    }

    if (LoginFlag == 0) {
        puts("ѧ��������.");
        return 0;
    }
    return Students;
    /// ��ʼѧ������
    ShowStudentMenu(ptr);
}

/// �޸�ѧ����Ϣ
void ChangeMyInfo(StudentList *stu) {
    int listCount = 0;
    char ch[2];
    char newName[15];
    FILE *fp;

    // �ṹ���ʼ��
    StudentList *thisList = (StudentList *) malloc(sizeof(StudentList));
    StudentList *thisListHead = thisList;

    thisList->next = NULL;
    thisList->id = 0;

    if ((fp = fopen("Students.txt", "r")) == NULL) {
        printf("�ļ�������.\n");
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
        printf("�ļ���û�м�¼.\n");

    if ((fp = fopen("Students.txt", "wb+")) == NULL) {
        printf("�ļ�������.\n");
        return;
    }

    printf("�޸�����(y/n):");
    scanf("%s", ch);
    if (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0) {
        StudentList *ptr = thisListHead;

        while (ptr->next != NULL) {
            ptr = ptr->next;
            if (ptr->id == stu->id)
                break;
        }
        if (ptr->id != stu->id){
            printf("ѧ��������\n");
            return;
        }

        printf("�����޸����� %s\n", ptr->name);
        printf("�������޸ĺ������: ");
        scanf("%s", ptr->name);
        strcpy(newName, ptr->name);

        ptr = thisListHead;
        while (ptr->next != NULL) {
            ptr = ptr->next;
            if (fwrite(ptr, sizeof(struct Course), 1, fp) != 1) {
                puts("�޸�����ʧ��.");
                return;
            }
        }
    }
    printf("�޸ĳɹ���ѧ������Ϊ %s", newName);
}

/// ������пγ̵ĳɼ�
void CheckGrade(StudentList *stu) {
    int listGradeCount = 0, sum = 0, allCredit = 0;
    char grade[] = "GradeStu_", txt[] = ".txt", sid[2];
    FILE *gradeFp;

    /// ��stuIdת�����ַ���
    itoa(stu->id, sid, 10);
    char *courseTxt = (char *) malloc(strlen(grade) + strlen(txt) + strlen(sid));
    sprintf(courseTxt, "%s%s%s", grade, sid, txt);
//    printf("%s", classTxt);

    // �ɼ��ṹ���ʼ��
    GradeList *thisList = (GradeList *) malloc(sizeof(GradeList));
    GradeList *thisHead = thisList;
    thisList->next = NULL;
    thisList->grade = 0;

    /// ��ȡѧ���ɼ���Ϣ�ļ�
    if ((gradeFp = fopen(courseTxt, "r")) == NULL) {
        printf("�ļ�������.\n");
        return;
    }

    // �洢����
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
        printf("%s û�гɼ���¼.\n", stu->name);
        return;
    }

    while (thisHead->next != NULL) {
        thisHead = thisHead->next;
        printf("�γ�id: %d, �γ���: %s, �ɼ�: %d, ѧ��: %d", thisHead->courseId, thisHead->courseName, thisHead->grade,
               thisHead->credit);
        sum += thisHead->credit * thisHead->grade;
        allCredit += thisHead->credit;
    }
    printf("%s ƽ���ɼ�(zju����ٷ���): %d", stu->name, sum/allCredit);
}

/// ����γ��б�
void CheckCourses(StudentList *stu) {
    int listGradeCount = 0, sum = 0, allCredit = 0;
    char stuCourse[] = "CourseStu_", txt[] = ".txt", sid[2];
    FILE *gradeFp;

    /// ��stuIdת�����ַ���
    itoa(stu->id, sid, 10);
    char *courseTxt = (char *) malloc(strlen(stuCourse) + strlen(txt) + strlen(sid));
    sprintf(courseTxt, "%s%s%s", stuCourse, sid, txt);
//    printf("%s", classTxt);

    // �ɼ��ṹ���ʼ��
    CourseList *thisList = (CourseList *) malloc(sizeof(CourseList));
    CourseList *thisHead = thisList;
    thisList->next = NULL;
    thisList->id = 0;
    thisList->credit = 0;
    thisList->profId = 0;

    /// ��ȡѧ���ɼ���Ϣ�ļ�
    if ((gradeFp = fopen(courseTxt, "r")) == NULL) {
        printf("�ļ�������.\n");
        return;
    }

    // �洢����
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
        printf("%s û�пγ̼�¼.\n", stu->name);
        return;
    }

    while (thisHead->next != NULL) {
        thisHead = thisHead->next;
        printf("�γ�id: %d, �γ���: %s, ѧ��: %d", thisHead->id, thisHead->courseName, thisHead->credit);
        sum ++;
        allCredit += thisHead->credit;
    }
    printf("%s �� %d �ڿγ�, ��ѧ�� %d", stu->name, sum, allCredit);
}