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
    // �ṹ���ʼ��
    InstManagerList *thisList = (InstManagerList *) malloc(sizeof(InstManagerList));
    InstManagerList *ptr = thisList;
    thisList->next = NULL;
    thisList->id = 0;

    // �ж������ļ��Ƿ����
    if ((fp = fopen("InstManager.txt", "r")) == NULL) {
        puts("InstManager.txt�ļ�������.");
        return 0;
    }

    // ���ļ��в�ѯ������ѧ����Ϣ
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
        printf("InstManager.txt�ļ���û�м�¼.\n");
        return 0;
    }

    while (ptr != NULL) {
        if (id == ptr->id) {
            if (ptr->password == passwd) {
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
        puts("����Ա������.");
        return 0;
    }
    return InstManagers;
    /// ��ʼѧ������
    ShowInstManagerMenu(ptr);
}

void CreateClass(){
    int InClassCount = 0;
    char ch[2];
    FILE *classFp;

    // ���ڽṹ���ʼ��
    ClassList *thisList = (ClassList *) malloc(sizeof(ClassList));
    ClassList *thisHead = thisList;

    thisList->next = NULL;
    thisList->id = 0;

    /// ��ȡ������Ϣ�ļ�
    if ((classFp = fopen("Classes.txt", "r")) == NULL) {
        printf("�ļ�������.\n");
        return;
    }

    // �洢����
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
        printf("�ļ���û�м�¼.\n");

    if ((classFp = fopen("Classes.txt", "ab+")) == NULL) {
        printf("�ļ�������.\n");
        return;
    }

    printf("����༶��Ϣ(y/n):");
    scanf("%s", ch);
    while (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0) {
        ClassList *tmpNode = (ClassList *) malloc(sizeof(ClassList));
        ClassList *classPtr = thisHead;

        printf("�༶id: "); // ��ʦ���4λ
        scanf("%d", &tmpNode->id);
        printf("רҵ����: ");
        scanf("%s", tmpNode->majorName);

        /// �жϵ�ǰ�����Ƿ����
        while (classPtr->next != NULL){
            classPtr = classPtr->next;
            if (tmpNode->id == classPtr->id) {
                printf("�༶id�Ѿ����ڣ������������.");
                getchar();
                fclose(classFp);
                return;
            }
        }

        if (fwrite(tmpNode, sizeof(ClassList), 1, classFp) == 1) {
            classPtr->next = tmpNode;
            classPtr = classPtr->next;
            classPtr->next = NULL;
            printf("%s%d �༶������\n", tmpNode->majorName, tmpNode->id);
        } else {
            printf("����ʧ�ܣ��������.");
            getchar();
        }

        printf("����(y/n):");
        scanf("%s", ch);
    }
    fclose(classFp);
    printf("�༶�����ɹ�.\n");
}

/// ! ɾ���༶֮�� �༶�е�ѧ���Լ�����Ա�����ᱻɾ��
void DeleteClass(int classId){
    int listClassCount = 0, isDelete = 0;
    char ch[2];
    FILE *classFp;

    // �ṹ���ʼ��
    ClassList *thisList = (ClassList *) malloc(sizeof(ClassList));
    ClassList *thisHead = thisList;

    thisList->next = NULL;
    thisList->id = 0;

    /// ��ȡ��Ϣ�ļ�
    if ((classFp = fopen("Classes.txt", "r")) == NULL) {
        printf("�ļ�������.\n");
        return;
    }

    // �洢����
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
        printf("�ļ���û�м�¼.\n");

    printf("ȷ��Ҫɾ����(y/n):");
    scanf("%s", ch);
    while (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0) {
        if ((classFp = fopen("Classes.txt", "wb+")) == NULL) {
            printf("�ļ�������.\n");
            return;
        }

        ClassList *tmpNode = (ClassList *) malloc(sizeof(ClassList));
        ClassList *classPtr = thisHead;

        /// �жϵ�ǰ�༶�Ƿ����
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
            puts("ɾ��ʧ�ܣ��༶������");
            return;
        }

        printf("����(y/n):");
        scanf("%s", ch);
    }
    fclose(classFp);
    printf("�༶ɾ���ɹ�.\n");
}

void ModifyClassManager(int classId){
    int listCount = 0;
    char ch[2];
    char newName[15];
    FILE *fp;

    // �ṹ���ʼ��
    ClassManagerList *thisList = (ClassManagerList *) malloc(sizeof(ClassManagerList));
    ClassManagerList *thisListHead = thisList;

    thisList->next = NULL;
    thisList->id = 0;

    if ((fp = fopen("ClassManagers.txt", "r")) == NULL) {
        printf("�ļ�������.\n");
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
        printf("�ļ���û�м�¼.\n");

    if ((fp = fopen("ClassManagerList.txt", "wb+")) == NULL) {
        printf("�ļ�������.\n");
        return;
    }

    printf("�޸İ༶����Ա����(y/n):");
    scanf("%s", ch);
    if (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0) {
        ClassManagerList *ptr = thisListHead;

        while (ptr->next != NULL) {
            ptr = ptr->next;
            if (ptr->classId == classId)
                break;
        }
        if (ptr->classId != classId){
            printf("�������Ա������\n");
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
    printf("�޸ĳɹ�������Ա����Ϊ %s", newName);
}

int InsertProfession() {
    int listProfCount = 0;
    char ch[2] = "y";
    FILE *profFp;

    // ���ڽṹ���ʼ��
    ProfessionList *thisList = (ProfessionList *) malloc(sizeof(ProfessionList));
    ProfessionList *thisHead = thisList;

    thisList->next = NULL;
    thisList->id = 0;

    /// ��ȡ������Ϣ�ļ�
    if ((profFp = fopen("Professions.txt", "r")) == NULL) {
        printf("Professions.txt�ļ�������.\n");
        return 0;
    }

    // �洢����
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
        printf("Professions.txt�ļ���û�м�¼.\n");

    if ((profFp = fopen("Professions.txt", "ab+")) == NULL) {
        printf("Professions.txt�ļ�������.\n");
        return 0;
    }

    printf("���������Ϣ(y/n): y\n");
    if (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0) {
        ProfessionList *tmpNode = (ProfessionList *) malloc(sizeof(ProfessionList));
        ProfessionList *proPtr = thisHead;

        printf("����id: %d\n", profIdInt); // ��ʦ���4λ
        tmpNode->id = profIdInt;

        /// �жϵ�ǰ�����Ƿ����
        while (proPtr->next != NULL){
            proPtr = proPtr->next;
            if (tmpNode->id == proPtr->id) {
                printf("����id�Ѿ�����\n");
                fclose(profFp);
                return 0;
            }
        }

        printf("������: %s\n", profName);
        strcpy(tmpNode->name, profName);
        tmpNode->password = 123456;

        if (fwrite(tmpNode, sizeof(ProfessionList), 1, profFp) == 1) {
            proPtr->next = tmpNode;
            proPtr = proPtr->next;
            proPtr->next = NULL;
            printf("%s �����棬��ʼ����Ϊ123456\n", tmpNode->name);
        } else {
            printf("����ʧ��\n");
        }
    }
    fclose(profFp);
    printf("������Ϣ¼��ɹ�\n");
    return 1;
}

int InsertClassManager(int classId){
    int classManagerCount = 0, classCount = 0;
    char ch[2] = "y";
    FILE *classManagerFp, *classFp;

    // ���ڽṹ���ʼ��
    ClassManagerList *thisManagerList = (ClassManagerList *) malloc(sizeof(ClassManagerList));
    ClassList *thisClassList = (ClassList *)malloc(sizeof(ClassList));
    ClassManagerList *thisManagerHead = thisManagerList;
    ClassList *thisClassHead = thisClassList;

    thisManagerList->next = NULL;
    thisManagerList->id = 0;
    thisClassList->next = NULL;
    thisClassList->id = 0;

    /// ��ȡ��Ϣ�ļ�
    if ((classManagerFp = fopen("ClassManagers.txt", "r")) == NULL) {
        printf("�ļ�������.\n");
        return 0;
    }
    if ((classFp = fopen("Classes.txt", "r")) == NULL) {
        printf("�ļ�������.\n");
        return 0;
    }

    // �洢����
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
        printf("�༶����Ա�ļ���û�м�¼.\n");
    if (classCount == 0)
        printf("û�а༶");

    if ((classManagerFp = fopen("ClassManagers.txt", "ab+")) == NULL) {
        printf("�༶����Ա�ļ�������.\n");
        return 0;
    }
    if ((classFp = fopen("Classes.txt", "ab+")) == NULL) {
        printf("�༶�ļ�������.\n");
        return 0;
    }

    printf("����༶����Ա��Ϣ(y/n): y\n");
    if (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0) {
        ClassManagerList *tmpClassManagerNode = (ClassManagerList *) malloc(sizeof(ClassManagerList));
        ClassManagerList *classManagerPtr = thisManagerHead;
        ClassList  *classPtr = thisClassHead;

        while (classPtr->next != NULL){
            classPtr = classPtr->next;
            if (classId == classPtr->id) {
                printf("�ҵ��༶ %s%d\n", classPtr->majorName, classPtr->id);
                break;
            }
        }
        if (classPtr->id != classId){
            puts("�༶������\n");
            fclose(classManagerFp);
            fclose(classFp);
            return 0;
        }

        tmpClassManagerNode->classId = classId;
        tmpClassManagerNode->password = 123456;

        printf("�༶����Աid: %d\n", classIdInt); // �༶����Ա���3λ
        tmpClassManagerNode->id = classManagerIdInt;

        /// �жϵ�ǰ����Ա�Ƿ����
        while (classManagerPtr->next != NULL){
            classManagerPtr = classManagerPtr->next;
            if (tmpClassManagerNode->id == classManagerPtr->id) {
                printf("�༶����Աid�Ѿ�����\n");
                fclose(classManagerFp);
                fclose(classFp);
                return 0;
            }
        }

        printf("�༶����Ա��: %s\n", classManagerName);
        strcpy(tmpClassManagerNode->name, classManagerName);

        if (fwrite(tmpClassManagerNode, sizeof(ClassManagerList), 1, classManagerFp) == 1) {
            classManagerPtr->next = tmpClassManagerNode;
            classManagerPtr = classManagerPtr->next;
            classManagerPtr->next = NULL;
            printf("%s �����棬��ʼ����Ϊ123456\n", tmpClassManagerNode->name);
        } else
            printf("����ʧ��\n");
    }
    fclose(classManagerFp);
    fclose(classFp);
    printf("�༶����Ա��Ϣ¼��ɹ�.\n");
    return 1;
}

void InsertCourses(){
    int listCourseCount = 0, listProfCount = 0;
    char ch[2];
    FILE *courseFp, *proFp;

    // �ṹ���ʼ��
    CourseList *thisCourseList = (CourseList *) malloc(sizeof(CourseList));
    ProfessionList *thisProfList = (ProfessionList *) malloc(sizeof(ProfessionList));
    CourseList *thisCourseHead = thisCourseList;
    ProfessionList *thisProfHead = thisProfList;
    thisCourseList->next = NULL;
    thisCourseList->id = 0;
    thisProfList->next = NULL;
    thisProfList->id = 0;

    if ((courseFp = fopen("Courses.txt", "r")) == NULL) {
        printf("�ļ�������.\n");
        return;
    }
    if ((proFp = fopen("Professions.txt", "r")) == NULL) {
        printf("�ļ�������.\n");
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
        printf("�γ��ļ���û�м�¼\n");
    if (listProfCount == 0)
        printf("�����ļ���û�м�¼\n");

    if ((courseFp = fopen("Courses.txt", "ab+")) == NULL) {
        printf("�γ��ļ�������.\n");
        return;
    }

    printf("����γ���Ϣ(y/n):");
    scanf("%s", ch);
    while (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0) {
        CourseList *tmpNode = (CourseList *) malloc(sizeof(CourseList));
        CourseList *coursePtr = thisCourseHead;
        ProfessionList *profPtr = thisProfHead;

        printf("�γ�id: ");
        scanf("%d", &tmpNode->id);

        while (coursePtr->next != NULL) {
            coursePtr = coursePtr->next;
            if (tmpNode->id == coursePtr->id) {
                printf("�γ�id�Ѿ����ڣ������������.");
                getchar();
                fclose(courseFp);
                return;
            }
        }

        printf("�γ�����: ");
        scanf("%s", tmpNode->courseName);
        printf("����id: ");
        scanf("%d", &tmpNode->profId);
        printf("ѧ��: ");
        scanf("%d", &tmpNode->credit);

        while (profPtr->next != NULL) {
            profPtr = profPtr->next;
            if (tmpNode->profId == profPtr->id) {
                printf("���ҵ� %s ����\n", profPtr->name);
                break;
            }
        }
        if (tmpNode->profId != profPtr->id){
            printf("û����λ����\n");
            return;
        }

        if (fwrite(tmpNode, sizeof(CourseList), 1, courseFp) == 1) {
            coursePtr->next = tmpNode;
            coursePtr = coursePtr->next;
            coursePtr->next = NULL;
            printf("%s ������\n", tmpNode->courseName);
        } else{
            printf("����ʧ�ܣ��������.");
            getchar();
        }

        printf("����(y/n):"); /*ѯ���Ƿ����*/
        scanf("%s", ch);
    }
    fclose(courseFp);
    printf("�γ���Ϣ¼��ɹ�.\n");
}