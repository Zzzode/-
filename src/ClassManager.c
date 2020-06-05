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
    // �ṹ���ʼ��
    ClassManagerList *thisList = (ClassManagerList *) malloc(sizeof(ClassManagerList));
    ClassManagerList *ptr = thisList;
    thisList->next = NULL;
    thisList->id = 0;

    // �ж������ļ��Ƿ����
    if ((Fp = fopen("ClassManagers.txt", "r")) == NULL) {
        puts("ClassManagers.txt�ļ�������.");
        return 0;
    }

    // ���ļ��в�ѯ������ѧ����Ϣ
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
        printf("ClassManagers.txt�ļ���û�м�¼.\n");
        return 0;
    }

    while (ptr != NULL) {
        if (id == ptr->id) {
            if (ptr->password == password) {
                printf("������ȷ����½�ɹ� %s ��ʦ\n", ptr->name);
                LoginFlag = 1;
                break;
            } else {
                printf("�������\n");
                return 0;
            }
        }
        ptr = ptr->next;
    }

    if (LoginFlag == 0) {
        puts("�༶����Ա������");
        return 0;
    }
    return ClassManager;
    /// ��ʼѧ������
    ShowClassManagerMenu(ptr);
}


int cInsertStudents(int classId) {
    int listStuCount = 0, listClassCount = 0;
    char class[] = "Class_", txt[] = ".txt", cid[2], ch[2] = "y";
    FILE *stuFp, *classFp;

    /// ��classidת�����ַ���
    itoa(classId, cid, 10);
    char *classTxt = (char *)malloc(strlen(class) + strlen(txt) + strlen(cid));
    sprintf(classTxt, "%s%s%s", class, cid, txt);
//    printf("%s", classTxt);

    // ����ѧ���Ľṹ���ʼ��
    StudentList *thisStuList = (StudentList *) malloc(sizeof(StudentList));
    StudentList *thisStuHead = thisStuList;
    thisStuList->next = NULL;
    thisStuList->id = 0;
    thisStuList->classId = 0;

    // �༶ѧ���Ľṹ���ʼ��
    StudentList *thisClassStuList = (StudentList *) malloc(sizeof(StudentList));
    StudentList *thisClassStuHead = thisClassStuList;
    thisClassStuList->next = NULL;
    thisClassStuList->id = 0;
    thisClassStuList->classId = 0;

    // ���ļ�
    if ((stuFp = fopen("Students.txt", "r")) == NULL) {
        printf("Students.txt�ļ������ڣ�\n");
        return 0;
    }

    if ((classFp = fopen(classTxt, "r")) == NULL) {
        printf("%s�ļ������ڣ�\n", classTxt);
        return 0;
    }

    /// �������ļ��е����ݶ�ȡ��������
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
        printf("Students.txt�ļ���û�м�¼\n");
    if (listClassCount == 0)
        printf("%s�ļ���û�м�¼\n", classTxt);

    /// �ٴδ�txt�ļ�
    if ((stuFp = fopen("Students.txt", "ab+")) == NULL) {
        printf("�ļ�������\n");
        return 0;
    }
    if ((classFp = fopen(classTxt, "ab+")) == NULL) {
        printf("%s�ļ�������\n", classTxt);
        return 0;
    }

    printf("����ѧ����Ϣ(y/n): y\n");
    if (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0) {
        /// ��ʼ��ѧ����ʱ�ڵ�
        StudentList *tmpStuNode = (StudentList *) malloc(sizeof(StudentList));
        /// ��ʼ�����������ָ��
        StudentList *stuPtr = thisStuHead;
        StudentList *classStuPtr = thisClassStuHead;

        tmpStuNode->id = stuIdInt;
        printf("ѧ��id: %d\n", stuIdInt);
//        scanf("%d", &tmpStuNode->id);

        /// �жϵ�ǰѧ���Ƿ����
        while (stuPtr->next != NULL){
            stuPtr = stuPtr->next;
            if (tmpStuNode->id == stuPtr->id) {
                printf("Students.txt��ѧ��id�Ѿ�����\n");
                fclose(stuFp);
                fclose(classFp);
                return 0;
            }
        }

        /// �жϵ�ǰ�༶��ѧ���ڵ��Ƿ����
        while (classStuPtr->next != NULL){
            classStuPtr = classStuPtr->next;
            if (tmpStuNode->id == classStuPtr->id) {
                printf("%s��ѧ��id�Ѿ�����\n", classTxt);
                fclose(stuFp);
                fclose(classFp);
                return 0;
            }
        }

        /// ��ʼ��ѧ����������Ϣ
        printf("����: %s\n", stuName);
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
            printf("%s �����棬��ʼ����Ϊ123456\n", tmpStuNode->name);
        }
        else
            printf("����ʧ��\n");
    }
    fclose(stuFp);
    fclose(classFp);

    printf("ѧ����Ϣ¼��ɹ�.\n");
    return 1;
}

/// ѧ���б�Ͱ༶�б�Ҫ��
void cModifyStudentInfo(int classId, int studentId) {
    int listStuCount = 0, listClassStuCount = 0;
    char ch[2], newName[15];
    char stuClass[] = "Class_", txt[] = ".txt", cid[2];
    FILE *stuFp, *classStuFp;

    /// ��stuIdת�����ַ���
    itoa(classId, cid, 10);
    char *classTxt = (char *) malloc(strlen(stuClass) + strlen(txt) + strlen(cid));
    sprintf(classTxt, "%s%s%s", stuClass, cid, txt);

    // �ṹ���ʼ��
    StudentList *thisStuList = (StudentList *) malloc(sizeof(StudentList));
    StudentList *thisStuListHead = thisStuList;
    thisStuList->next = NULL;
    thisStuList->id = 0;

    StudentList *thisClassStuList = (StudentList *) malloc(sizeof(StudentList));
    StudentList *thisClassStuListHead = thisClassStuList;
    thisClassStuList->next = NULL;
    thisClassStuList->id = 0;

    if ((stuFp = fopen("Students.txt", "r")) == NULL) {
        printf("Students.txt�ļ�������.\n");
        return;
    }

    if ((classStuFp = fopen(classTxt, "r")) == NULL) {
        printf("%s�ļ�������.\n", classTxt);
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
        printf("Students.txt�ļ���û�м�¼.\n");
    if (listClassStuCount == 0)
        printf("%s�ļ���û�м�¼.\n", classTxt);

    if ((stuFp = fopen("Students.txt", "wb+")) == NULL) {
        printf("Students.txt�ļ�������.\n");
        return;
    }
    if ((classStuFp = fopen(classTxt, "wb+")) == NULL) {
        printf("%s�ļ�������.\n", classTxt);
        return;
    }

    printf("�޸�ѧ������(y/n):");
    scanf("%s", ch);
    if (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0) {
        StudentList *stuPtr = thisStuListHead;
        StudentList *classStuPtr = thisClassStuListHead;

        /// ��ȫУѧ�����ҵ���ѧ��
        while (stuPtr->next != NULL) {
            stuPtr = stuPtr->next;
            if (stuPtr->id == studentId)
                break;
        }
        if (stuPtr->id != studentId){
            printf("ѧ��������\n");
            return;
        }

        // �鿴ѧ���Ƿ��ڱ�����
        while (classStuPtr->next != NULL) {
            classStuPtr = classStuPtr->next;
            if (classStuPtr->id == studentId)
                break;
        }
        if (classStuPtr->id != studentId){
            printf("ѧ�����ڱ���\n");
            return;
        }

        printf("�����޸����� %s\n", stuPtr->name);
        printf("�������޸ĺ������: ");
        scanf("%s", stuPtr->name);

        strcpy(classStuPtr->name, stuPtr->name);
        strcpy(newName, stuPtr->name);

        stuPtr = thisStuListHead;
        classStuPtr = thisClassStuListHead;

        while (stuPtr->next != NULL) {
            stuPtr = stuPtr->next;
            if (fwrite(stuPtr, sizeof(StudentList), 1, stuFp) != 1) {
                puts("�޸�����ʧ��.");
                return;
            }
        }
        while (classStuPtr->next != NULL) {
            classStuPtr = classStuPtr->next;
            if (fwrite(classStuPtr, sizeof(StudentList), 1, classStuFp) != 1) {
                puts("�޸�����ʧ��.");
                return;
            }
        }
    }
    printf("�޸ĳɹ���ѧ������Ϊ %s", newName);
}

void cQueryStudent(int classId, int stuId) {
    FILE *Fp;
    char cid[2], stuClass[] = "Class_", txt[] = ".txt";
    int listCount = 0;

    itoa(classId, cid, 10);
    char *classTxt = (char *) malloc(strlen(stuClass) + strlen(txt) + strlen(cid));
    sprintf(classTxt, "%s%s%s", stuClass, cid, txt);

    // �ṹ���ʼ��
    StudentList *thisList = (StudentList *) malloc(sizeof(StudentList));
    StudentList *ptr = thisList;
    thisList->next = NULL;
    thisList->id = 0;

    // �ж������ļ��Ƿ����
    if ((Fp = fopen(classTxt, "r")) == NULL) {
        printf("%s �ļ�������.", classTxt);
        return;
    }

    // ���ļ��в�ѯ������ѧ����Ϣ
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
        printf("%s�ļ���û�м�¼.\n", classTxt);
        return;
    }

    while (ptr->next != NULL) {
        ptr = ptr->next;
        if (stuId == ptr->id) {
            printf("���ҵ� %s ѧ��\n", ptr->name);
            break;
        }
    }
    if (ptr->id != stuId) {
        puts("ѧ�����ڱ���");
        return;
    }

    printf("ѧ��: %d, ����: %s, �༶id: %d", stuId, ptr->name, ptr->classId);
}

void cDeleteStudents(int classId, int stuId) {
//    int stuListCount = 0, classListCount = 0;
//    char ch[2];
//    FILE *stuFp, *classFp;
//
//    // �ṹ���ʼ��
//    ClassList *thisClassList = (ClassList *) malloc(sizeof(ClassList));
//    StudentList *thisStuList = (StudentList *) malloc(sizeof(StudentList));
//    ClassList *ptrClass = thisClassList;
//    StudentList *ptrStudent = thisStuList;
//    thisStuList->next = NULL;
//    thisClassList->next = NULL;
//    thisStuList->id = 0;
//    thisClassList->id = 0;
//
//    // �鿴�ļ��Ƿ����
//    if ((stuFp = fopen("Students.txt", "r+")) == NULL) {
//        printf("ѧ���ļ�������\n");
//        return;
//    }
//    if ((classFp = fopen("Class.txt", "r+")) == NULL) {
//        printf("�༶�ļ�������\n");
//        return;
//    }
//
//    // ���ļ����ݴ������
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
//        printf("û�м�¼\n");
//
//    // ���Ұ༶id ѧ��id ���޸�
//    printf("�Ƿ�ɾ��ѧ����(y/n):");
//    scanf("%s", ch);
//    if (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0) {
//        StudentList *tmpStuNode = NULL;
//        StudentList *prevStuNode = NULL;
//        ClassList *tmpClassNode = NULL;
//        ClassList *ptrTmpClassNode = NULL;
//
//        while (ptrClass != NULL) {
//            if (classId == ptrClass->id) {
//                puts("�ҵ�classId.");
//                tmpClassNode = ptrClass;
//                ptrTmpClassNode = tmpClassNode;
//                break;
//            }
//            ptrClass = ptrClass->next;
//        }
//
//        if (ptrTmpClassNode == NULL) {
//            puts("û�иð༶.");
//            return;
//        }
//
//        StudentList *ptrClassStuNode = ptrTmpClassNode->student;
//        while (ptrClassStuNode != NULL) {
//            if (stuId == ptrClassStuNode->id) {
//                puts("�ҵ�stuId.");
//                break;
//            }
//            prevStuNode = ptrClassStuNode;
//            ptrClassStuNode = ptrClassStuNode->next;
//        }
//
//        if (ptrClassStuNode == NULL) {
//            printf("�༶��û�и�id.");
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
//    puts("ɾ���ɹ�");
    ;
}

// FIXME
void ShowStudentInfo(StudentList *stu) {
    ;
}