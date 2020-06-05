//
// Created by ZODE on 2020/6/4.
//

#ifndef STUDENTS_MANAGER_INITIAL_H
#define STUDENTS_MANAGER_INITIAL_H

#define MENU
#define BUTTON
#define ROTATE
#define EDITBOX

enum InterfaceN{
    StuOptions = 6, SuperOptions = 7, InsertStu = 8,
    InsertProf = 9, InsertCM = 10, InsertIM = 11, InsertCourse = 12,
    InsertI = 13, ProfessionOptions = 14, InstManagerOptions = 15,
    ClassManagerOptions = 16, ModifyProfession = 17, InsertClass = 18
};

static double ck_width, ck_height; // ���ڳߴ�
static int FLAG = 0;               //����������
static int allowLoginBottons = 0; //�����¼��ť
//static int classID[10];
static char userId[80] = "";
static char passwd[80] = "";
// �༶����Ա���
int classManagerIdInt;
char classManagerIdStr[30];
char classManagerName[15];
// ѧԺ����Ա���
int instManagerIdInt;
char instManagerIdStr[30];
char instManagerName[15];
// �༶���ȫ�ֱ���
int classIdInt;
char classIdStr[30];
// ѧ�����ȫ�ֱ���
int stuIdInt;
char stuIdStr[30];
char stuName[15];
// ����ѡ��
int OptionInterface;
// ѡ��
int selection;
// �������ȫ�ֱ���
int profIdInt;
char profIdStr[30];
char profName[15];
// ѧԺ���
int instIdInt;
char instIdStr[30];
char instName[30];

void DisplayClear(void); //��Ļ����

void pm_display(void); //��Ļ��ʾ����
void DrawLoginEditText();
void DrawSuperAdminEditText();

void DrawLoginBotton();

#endif //STUDENTS_MANAGER_INITIAL_H
