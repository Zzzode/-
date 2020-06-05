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

// TODO ���ѧԺȨ�޹���
int LoginAdmin(){
    int select = 0, classId = 0, instId = 0;
    printf("��ѡ��ܳ�����Ա������1���ѧ�� 2��ӽ��� 3���ѧԺ����Ա 4��Ӱ༶����Ա 5��ӿγ� 6���ѧԺ: ");
    scanf("%d", &select);

    switch (select) {
        case 1:
            printf("��������ӵ�ѧ���༶��");
            scanf("%d", &classId);
            cInsertStudents(classId);
            break;
        case 2:
            InsertProfession();
            break;
        case 3:
            printf("��������ӵĹ���Ա��ѧԺid��");
            scanf("%d", &instId);
            InsertInstManager(instId);
            break;
        case 4:
            printf("���������Ա�༶id��");
            scanf("%d", &classId);
            InsertClassManager(classId);
            break;
        case 5:
            printf("��ʱ���ṩ�˹��ܣ���ת��ѧԺ����Ա����");
//            InsertCourses();
            break;
        case 6:
            InsertInst();
            break;
        default:
            puts("��Ч��ѡ��");
            break;
    }
    return SuperAdmin;
}

// FIXME ��Ҫ�ж��Ƿ����ѧԺ
int InsertInstManager(int instId) {
    int listInstCount = 0; /*m�Ǽ�¼������*/
    char ch[2] = "y";
    FILE *instFp;

    // ���ڽṹ���ʼ��
    InstManagerList *thisList = (InstManagerList *) malloc(sizeof(InstManagerList));
    InstManagerList *thisHead = thisList;

    thisList->next = NULL;
    thisList->id = 0;

    /// ��ȡ������Ϣ�ļ�
    if ((instFp = fopen("InstManager.txt", "r")) == NULL) {
        printf("InstManager.txt�ļ�������.\n");
        return 0;
    }

    // �洢����
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
        printf("InstManager.txt�ļ���û�м�¼.\n");

    if ((instFp = fopen("InstManager.txt", "ab+")) == NULL) {
        printf("InstManager.txt�ļ�������.\n");
        return 0;
    }

    printf("����ѧԺ����Ա��Ϣ(y/n): y\n");
    if (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0) {
        InstManagerList *tmpNode = (InstManagerList *) malloc(sizeof(InstManagerList));
        InstManagerList *instPtr = thisHead;

        printf("ѧԺ����Աid(2λʮ����): %d\n", instManagerIdInt); // ѧԺ����Ա���2λ
        tmpNode->id = instManagerIdInt;

        /// �жϵ�ǰ�Ƿ����
        while (instPtr->next != NULL){
            instPtr = instPtr->next;
            if (tmpNode->id == instPtr->id) {
                printf("ѧԺ����Աid�Ѿ�����\n");
                fclose(instFp);
                return 0;
            }
        }

        printf("ѧԺ����Ա��: %s\n", instManagerName);
        strcpy(tmpNode->name, instManagerName);
        tmpNode->instId = instId;
        tmpNode->password = 123456;

        if (fwrite(tmpNode, sizeof(InstManagerList), 1, instFp) == 1) {
            instPtr->next = tmpNode;
            instPtr = instPtr->next;
            instPtr->next = NULL;
            printf("%s �����棬��ʼ����Ϊ123456\n", tmpNode->name);
        } else
            printf("����ʧ��\n");
    }
    fclose(instFp);
    printf("ѧԺ����Ա��Ϣ¼��ɹ�\n");
    return 1;
}

int InsertInst(){
    int listInstCount = 0; /*m�Ǽ�¼������*/
    char ch[2] = "y";
    FILE *instFp;

    // ���ڽṹ���ʼ��
    InstituteList *thisList = (InstituteList *) malloc(sizeof(InstituteList));
    InstituteList *thisHead = thisList;

    thisList->next = NULL;
    thisList->id = 0;

    /// ��ȡ������Ϣ�ļ�
    if ((instFp = fopen("Institutes.txt", "r")) == NULL) {
        printf("Institutes.txt�ļ�������.\n");
        return 0;
    }

    // �洢����
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
        printf("Institutes.txt�ļ���û�м�¼.\n");

    if ((instFp = fopen("Institutes.txt", "ab+")) == NULL) {
        printf("Institutes.txt�ļ�������.\n");
        return 0;
    }

    printf("����ѧԺ��Ϣ(y/n): y\n");
    if (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0) {
        InstituteList *tmpNode = (InstituteList *) malloc(sizeof(InstituteList));
        InstituteList *instPtr = thisHead;

        printf("ѧԺid: %d\n", instIdInt); // ѧԺ����Ա���2λ
        tmpNode->id = instIdInt;
        /// �жϵ�ǰ�����Ƿ����
        while (instPtr->next != NULL){
            instPtr = instPtr->next;
            if (tmpNode->id == instPtr->id) {
                printf("ѧԺid�Ѿ�����\n");
                fclose(instFp);
                return 0;
            }
        }

        printf("ѧԺ��: %s\n", instName);
        strcpy(tmpNode->instName, instName);

        if (fwrite(tmpNode, sizeof(InstituteList), 1, instFp) == 1) {
            instPtr->next = tmpNode;
            instPtr = instPtr->next;
            instPtr->next = NULL;
            printf("%s ѧԺ������\n", tmpNode->instName);
        } else
            printf("����ʧ��\n");
    }
    fclose(instFp);
    printf("ѧԺ��Ϣ¼��ɹ�.\n");
    return 1;
}