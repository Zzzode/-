#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "conio.h"
#include "Menu.h"
#include "initial.h"
#include "DataManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>
#include "imgui.h"

void zf_process(char zf) //�ַ�������
{
    uiGetChar(zf); // GUI�ַ�����
    pm_display();  //ˢ����ʾ
}

void jp_process(int jp, int event) //���̴�����
{
    uiGetKeyboard(jp, event); // GUI��ȡ����
    pm_display();              // ˢ����ʾ
}

void sb_process(int x, int y, int button, int event) //��괦����
{
    uiGetMouse(x, y, button, event); //GUI��ȡ���
    pm_display();                     // ˢ����ʾ
}

void initial() {
    // ��ʼ�����ں�ͼ��ϵͳ
    SetWindowTitle("ѧ����Ϣ����ϵͳ");

    InitGraphics(); //��ʼ������

    ck_width = GetWindowWidth(); // ��ô��ڳߴ�
    ck_height = GetWindowHeight();

    // ע��ʱ����Ӧ����
    registerCharEvent(zf_process);       // �ַ�
    registerKeyboardEvent(jp_process); // ����
    registerMouseEvent(sb_process);       // ���
}

#if defined(MENU)

// �˵���ʾ����
void drawMainMenu() {
    static char *UseIntroductions[] = {"����",
                                       "���� | Ctrl-E",
                                       "�˳� | Ctrl-P"};
    static char *selectedLabel = NULL;

    double ChangH = GetFontHeight();
    double x = 0; //ChangH/8;
    double y = ck_height;
    double h = ChangH * 1.5;                               // �ؼ��߶�
    double w = TextStringWidth(UseIntroductions[0]) * 1.5; // �ؼ����
    double wlist = TextStringWidth(UseIntroductions[2]) * 1.2;
    int selection;

    // menu bar
    drawMenuBar(0, y - h, ck_width, h);
    // File �˵�
    selection = menuList(GenUIID(0), x, y - h, w, wlist, h, UseIntroductions, 3);
    if (selection > 0)
        selectedLabel = UseIntroductions[selection];
    if (selection == 1) {
        userId[80] = "";
        passwd[80] = "";
        FLAG = 0;
        OptionInterface = 0;
    }
    if (selection == 2)
        exit(-1); // choose to exit
}

#endif

#if defined(EDITBOX)

// �ı��༭����
void DrawLoginEditText() {
    static char status[200] = "";
    static char hint[] = "���¼   ";
    static char title[120] = "��ӭ����  ѧ����Ϣ����ϵͳ   ";
    double ChangH = GetFontHeight();
    double h = ChangH * 2;     // �ؼ��߶�
    double w = ck_width / 4.4; // �ؼ����
    double x = ck_width / 2.7;
    double y = ck_height / 2 - h;

    textbox(GenUIID(0), ck_width / 2 - TextStringWidth(title) / 2, 1.5 * y, TextStringWidth(title), 2 * h, title,
            sizeof(title));
    textbox(GenUIID(0), ck_width / 2 - TextStringWidth(hint) / 2, y, TextStringWidth(hint), h, hint, sizeof(hint));

    SetPenColor("Brown");
    drawLabel(ck_width / 2 - TextStringWidth("�˻�: ") - w / 2, (y -= h * 1.2) + ChangH * 0.7, "�˻�");
    if (textbox(GenUIID(0), ck_width / 2 - w / 2, y, w, h, userId, sizeof(userId))) {
        sprintf(status, "������id��%s ���룺%s", userId, passwd);
    }

    SetPenColor("Brown");
    drawLabel(ck_width / 2 - TextStringWidth("����: ") - w / 2, (y -= h * 1.2) + ChangH * 0.7, "����");
    if (textbox(GenUIID(0), ck_width / 2 - w / 2, y, w, h, passwd, sizeof(passwd))) {
        sprintf(status, "������id��%s ���룺%s", userId, passwd);
    }

    SetPenColor("Blue");
    drawLabel(x, y -= ChangH * 1.2, status);
}

void DrawSuperAdminEditText() {
    static char status[200] = "";
    static char title[] = " ��ӭ��������Ա   ";
    static char insertStu[] = "���������ѧ��   ";
    static char insertProf[] = "��������½���   ";
    static char insertCM[] = "��������°༶����Ա   ";
    static char insertIM[] = "���������ѧԺ����Ա   ";
    static char insertI[] = "���������ѧԺ   ";
    double ChangH = GetFontHeight();
    double h = ChangH * 2;     // �ؼ��߶�
    double w = ck_width / 4.4; // �ؼ����
    double x = ck_width / 2.7;
    double y = ck_height / 2 + h * 2;
    switch (OptionInterface) {
        case SuperOptions:
            textbox(GenUIID(0), ck_width / 2 - TextStringWidth(title) / 2, ck_height / 2 + h * 3,
                    TextStringWidth(title), 1.5 * h,
                    title,
                    sizeof(title));
            break;
        case InsertStu:
            textbox(GenUIID(0), ck_width / 2 - TextStringWidth(insertStu) / 2, ck_height / 2 + h * 3,
                    TextStringWidth(title), 1.5 * h,
                    insertStu,
                    sizeof(insertStu));
            SetPenColor("Brown");
            drawLabel(ck_width / 2 - w / 2 - TextStringWidth("ѧ��id(6λ����) "), (y -= h * 1.2) + ChangH * 0.7,
                      "ѧ��id(6λ����)");
            if (textbox(GenUIID(0), ck_width / 2 - w / 2, y, w, h, stuIdStr, sizeof(stuIdStr))) { ;
            }
            SetPenColor("Brown");
            drawLabel(ck_width / 2 - w / 2 - TextStringWidth("ѧ���༶id "), (y -= h * 1.2) + ChangH * 0.7, "ѧ���༶id");
            if (textbox(GenUIID(0), ck_width / 2 - w / 2, y, w, h, classIdStr, sizeof(classIdStr))) { ;
            }
            SetPenColor("Brown");
            drawLabel(ck_width / 2 - w / 2 - TextStringWidth("ѧ������ "), (y -= h * 1.2) + ChangH * 0.7, "ѧ������");
            if (textbox(GenUIID(0), ck_width / 2 - w / 2, y, w, h, stuName, sizeof(stuName))) { ;
            }
            break;
        case InsertProf:
            textbox(GenUIID(0), ck_width / 2 - TextStringWidth(insertProf) / 2, ck_height / 2 + h * 3,
                    TextStringWidth(insertProf), 1.5 * h,
                    insertProf,
                    sizeof(insertProf));
            SetPenColor("Brown");
            drawLabel(ck_width / 2 - w / 2 - TextStringWidth("����id(4λ����) "), (y -= h * 1.2) + ChangH * 0.7,
                      "����id(4λ����)");
            if (textbox(GenUIID(0), ck_width / 2 - w / 2, y, w, h, profIdStr, sizeof(profIdStr))) { ;
            }
            SetPenColor("Brown");
            drawLabel(ck_width / 2 - w / 2 - TextStringWidth("�������� "), (y -= h * 1.2) + ChangH * 0.7, "��������");
            if (textbox(GenUIID(0), ck_width / 2 - w / 2, y, w, h, profName, sizeof(profName))) { ;
            }
            break;
        case InsertCM:
            textbox(GenUIID(0), ck_width / 2 - TextStringWidth(insertCM) / 2, ck_height / 2 + h * 3,
                    TextStringWidth(insertCM), 1.5 * h,
                    insertCM,
                    sizeof(insertCM));
            SetPenColor("Brown");
            drawLabel(ck_width / 2 - w / 2 - TextStringWidth("�༶����Աid(3λ����) "), (y -= h * 1.2) + ChangH * 0.7,
                      "�༶����Աid(3λ����) ");
            if (textbox(GenUIID(0), ck_width / 2 - w / 2, y, w, h, classManagerIdStr, sizeof(classManagerIdStr))) { ;
            }
            SetPenColor("Brown");
            drawLabel(ck_width / 2 - w / 2 - TextStringWidth("�༶id "), (y -= h * 1.2) + ChangH * 0.7, "�༶id");
            if (textbox(GenUIID(0), ck_width / 2 - w / 2, y, w, h, classIdStr, sizeof(classIdStr))) { ;
            }
            SetPenColor("Brown");
            drawLabel(ck_width / 2 - w / 2 - TextStringWidth("����Ա���� "), (y -= h * 1.2) + ChangH * 0.7, "����Ա����");
            if (textbox(GenUIID(0), ck_width / 2 - w / 2, y, w, h, classManagerName, sizeof(classManagerName))) { ;
            }
            break;
        case InsertIM:
            textbox(GenUIID(0), ck_width / 2 - TextStringWidth(insertIM) / 2, ck_height / 2 + h * 3,
                    TextStringWidth(insertIM), 1.5 * h,
                    insertIM,
                    sizeof(insertIM));
            SetPenColor("Brown");
            drawLabel(ck_width / 2 - w / 2 - TextStringWidth("ѧԺ����Աid(2λ����) "), (y -= h * 1.2) + ChangH * 0.7,
                      "ѧԺ����Աid(2λ����)");
            if (textbox(GenUIID(0), ck_width / 2 - w / 2, y, w, h, instManagerIdStr, sizeof(instManagerIdStr))) { ;
            }
            SetPenColor("Brown");
            drawLabel(ck_width / 2 - w / 2 - TextStringWidth("ѧԺid "), (y -= h * 1.2) + ChangH * 0.7, "ѧԺid");
            if (textbox(GenUIID(0), ck_width / 2 - w / 2, y, w, h, instIdStr, sizeof(instIdStr))) { ;
            }
            SetPenColor("Brown");
            drawLabel(ck_width / 2 - w / 2 - TextStringWidth("����Ա���� "), (y -= h * 1.2) + ChangH * 0.7, "����Ա����");
            if (textbox(GenUIID(0), ck_width / 2 - w / 2, y, w, h, instManagerName, sizeof(instManagerName))) { ;
            }
            break;
        case InsertI:
            textbox(GenUIID(0), ck_width / 2 - TextStringWidth(insertI) / 2, ck_height / 2 + h * 3,
                    TextStringWidth(insertI), 1.5 * h,
                    insertI,
                    sizeof(insertI));
            SetPenColor("Brown");
            drawLabel(ck_width / 2 - w / 2 - TextStringWidth("ѧԺid "), (y -= h * 1.2) + ChangH * 0.7,
                      "ѧԺid");
            if (textbox(GenUIID(0), ck_width / 2 - w / 2, y, w, h, instIdStr, sizeof(instIdStr))) { ;
            }
            SetPenColor("Brown");
            drawLabel(ck_width / 2 - w / 2 - TextStringWidth("ѧԺ�� "), (y -= h * 1.2) + ChangH * 0.7, "ѧԺ��");
            if (textbox(GenUIID(0), ck_width / 2 - w / 2, y, w, h, instName, sizeof(instName))) { ;
            }
            break;
        default:
            break;
    }
}

// TODO
void DrawInstManagerEditText(){
    static char title[] = " ��ӭѧԺ����Ա   ";
    static char insertCM[] = "��������°༶����Ա   ";
    double ChangH = GetFontHeight();
    double h = ChangH * 2;     // �ؼ��߶�
    double w = ck_width / 4; // �ؼ����
    double x = ck_width / 5;
    double y = ck_height / 2 + h * 2;
    int k = 0;
    switch (OptionInterface) {
        case InstManagerOptions:
            textbox(GenUIID(0), ck_width / 2 - TextStringWidth(title) / 2, ck_height / 2 + h * 3,
                    TextStringWidth(title), 1.5 * h,
                    title,
                    sizeof(title));
            break;
        case InsertCM:
            textbox(GenUIID(0), ck_width / 2 - TextStringWidth(insertCM) / 2, ck_height / 2 + h * 3,
                    TextStringWidth(insertCM), 1.5 * h,
                    insertCM,
                    sizeof(insertCM));
            SetPenColor("Brown");
            drawLabel(ck_width / 2 - w / 2 - TextStringWidth("�༶����Աid(3λ����) "), (y -= h * 1.2) + ChangH * 0.7,
                      "�༶����Աid(3λ����) ");
            if (textbox(GenUIID(0), ck_width / 2 - w / 2, y, w, h, classManagerIdStr, sizeof(classManagerIdStr))) { ;
            }
            SetPenColor("Brown");
            drawLabel(ck_width / 2 - w / 2 - TextStringWidth("�༶id "), (y -= h * 1.2) + ChangH * 0.7, "�༶id");
            if (textbox(GenUIID(0), ck_width / 2 - w / 2, y, w, h, classIdStr, sizeof(classIdStr))) { ;
            }
            SetPenColor("Brown");
            drawLabel(ck_width / 2 - w / 2 - TextStringWidth("����Ա���� "), (y -= h * 1.2) + ChangH * 0.7, "����Ա����");
            if (textbox(GenUIID(0), ck_width / 2 - w / 2, y, w, h, classManagerName, sizeof(classManagerName))) { ;
            }
            break;
    }
}

// TODO
void DrawProfessionEditText(){
    static char title[] = " ��ӭ����   ";
    double ChangH = GetFontHeight();
    double h = ChangH * 2;     // �ؼ��߶�
    double w = ck_width / 6; // �ؼ����
    double x = ck_width / 5.1;
    double y = ck_height / 2 + h * 2;
    int k = 0;
    switch (OptionInterface) {
        case ProfessionOptions:
            textbox(GenUIID(0), ck_width / 2 - TextStringWidth(title) / 2, ck_height / 2 + h * 3,
                    TextStringWidth(title), 1.5 * h,
                    title,
                    sizeof(title));
            break;
    }
}

// TODO
void DrawStudentEditText(){
    static char title[] = " ��ӭͬѧ   ";
    double ChangH = GetFontHeight();
    double h = ChangH * 2;     // �ؼ��߶�
    double w = ck_width / 4; // �ؼ����
    double x = ck_width / 5;
    double y = ck_height / 2 + h * 2;
    int k = 0;
    switch (OptionInterface) {
        case StuOptions:
            textbox(GenUIID(0), ck_width / 2 - TextStringWidth(title) / 2, ck_height / 2 + h * 3,
                    TextStringWidth(title), 1.5 * h,
                    title,
                    sizeof(title));
            break;
    }
}

void drawEditText() {
    switch (FLAG) {
        case 0:
            DrawLoginEditText();
            break;
        case SuperAdmin:
            DrawSuperAdminEditText();
            break;
        case InstManagers:
            DrawInstManagerEditText();
            break;
        case Professions:
            DrawProfessionEditText();
            break;
        case Students:
            DrawStudentEditText();
            break;
    }
}

#endif

#if defined(BUTTON)

void DrawLoginBotton() {
    char *ptr = NULL;
    int id = strtol(userId, &ptr, 10);
    int password = strtol(passwd, &ptr, 10);

    double ChangH = GetFontHeight();
    double h = ChangH * 2; // �ؼ��߶�
    double x = ck_width / 13;
    double y = ck_height / 2 - h;
    double w = ck_width / 5; // �ؼ����

    if (button(GenUIID(0), x, y, w, h, allowLoginBottons ? "�����¼Ȩ��" : "ѡ�����Ȩ�޲���¼"))
        allowLoginBottons = !allowLoginBottons;

    if (allowLoginBottons) {
        int k = 0;
        for (k = 0; k < 4; k++) {
            char bottomLogin[100];
            if (k == 0) {
                sprintf(bottomLogin, "ѧԺ���� ��¼");
                if (button(GenUIID(k), 6 * x + w * 1.2, y - k * h * 2, w, h, bottomLogin)) {
                    FLAG = Login(id, password);
                    OptionInterface = FLAG == InstManagers ? InstManagerOptions : 0;
                }
            } else if (k == 1) {
                sprintf(bottomLogin, "��ʦ���� ��¼");
                if (button(GenUIID(k), 6 * x + w * 1.2, y - k * h * 2, w, h, bottomLogin)) {
                    FLAG = Login(id, password);
                    OptionInterface = FLAG == Professions ? ProfessionOptions : 0;
                }
            } else if (k == 2) {
                sprintf(bottomLogin, "ѧ������ ��¼");
                if (button(GenUIID(k), 6 * x + w * 1.2, y - k * h * 2, w, h, bottomLogin)) {
                    FLAG = Login(id, password);
                    OptionInterface = FLAG == Students ? StuOptions : 0;
                }
            } else if (k == 3) {
                sprintf(bottomLogin, "���ܼ��� ��¼");
                if (button(GenUIID(k), 6 * x + w * 1.2, y - k * h * 2, w, h, bottomLogin)) {
                    FLAG = Login(id, password);
                    OptionInterface = FLAG == SuperAdmin ? SuperOptions : 0;
                }
            }
        }
    }

    if (button(GenUIID(0), x, y - 1.5 * h, w, h, "����ϵͳ������ɫ")) {
        static int times = 0;
        usePredefinedColors(++times);
    }

    if (button(GenUIID(0), x, y - 3 * h, w, h, "�˳�")) {
        exit(-1);
    }
}

void DrawSuperAdminBotton() {
    double ChangH = GetFontHeight();
    double h = ChangH * 2;     // �ؼ��߶�
    double w = ck_width / 6; // �ؼ����
    double x = ck_width / 6;
    double y = GetWindowHeight() / 2;
    char options[100];

    switch (OptionInterface) {
        case SuperOptions:
            for (int k = 0; k < 5; k++) {
                if (k == 0) {
                    sprintf(options, "���ѧ��");
                    if (button(GenUIID(k), ck_width / 2 - 2.5 * w, y, 0.8 * w, h, options)) {
                        // ��ʾѧ��ѡ��
                        OptionInterface = InsertStu;
                    }
                } else if (k == 1) {
                    sprintf(options, "��ӽ�ʦ");
                    if (button(GenUIID(k), ck_width / 2 - 1.5 * w, y, 0.8 * w, h, options)) {
                        OptionInterface = InsertProf;
                    }
                } else if (k == 2) {
                    sprintf(options, "��Ӱ��");
                    if (button(GenUIID(k), ck_width / 2 - 0.5 * w, y, 0.8 * w, h, options)) {
                        OptionInterface = InsertCM;
                    }
                } else if (k == 3) {
                    sprintf(options, "���Ժ��");
                    if (button(GenUIID(k), ck_width / 2 + 0.5 * w, y, 0.8 * w, h, options)) {
                        OptionInterface = InsertIM;
                    }
                } else if (k == 4) {
                    sprintf(options, "���ѧԺ");
                    if (button(GenUIID(k), ck_width / 2 + 1.5 * w, y, 0.8 * w, h, options)) {
                        OptionInterface = InsertI;
                    }
                }
            }
            break;
        case InsertStu:
            sprintf(options, "ȷ�����");
            if (button(GenUIID(0), ck_width / 2 - TextStringWidth("ȷ�����  ") / 2, y - h * 3.5,
                       TextStringWidth("ȷ�����  "), h, options)) {
                stuIdInt = atoi(stuIdStr);
                classIdInt = atoi(classIdStr);

                if (cInsertStudents(classIdInt)) {
                    SetPenColor("Blue");
                    drawLabel(ck_width / 2 - TextStringWidth("�ɹ����ѧ��, ��ʼ����Ϊ123456") / 2, y - h * 4,
                              "�ɹ����ѧ��, ��ʼ����Ϊ123456");
                    stuIdInt = 0;
                    classIdInt = 0;
                }
            }
            break;
        case InsertProf:
            sprintf(options, "ȷ�����");
            if (button(GenUIID(0), ck_width / 2 - TextStringWidth("ȷ�����  ") / 2, y - h * 3.5,
                       TextStringWidth("ȷ�����  "), h, options)) {
                profIdInt = atoi(profIdStr);

                if (InsertProfession()) {
                    SetPenColor("Blue");
                    drawLabel(ck_width / 2 - TextStringWidth("�ɹ���ӽ���, ��ʼ����Ϊ123456") / 2, y - h * 4,
                              "�ɹ���ӽ���, ��ʼ����Ϊ123456");
                    profIdInt = 0;
                }
            }
            break;
        case InsertCM:
            sprintf(options, "ȷ�����");
            if (button(GenUIID(0), ck_width / 2 - TextStringWidth("ȷ�����  ") / 2, y - h * 3.5,
                       TextStringWidth("ȷ�����  "), h, options)) {
                classIdInt = atoi(classIdStr);
                classManagerIdInt = atoi(classManagerIdStr);

                if (InsertClassManager(classIdInt)) {
                    SetPenColor("Blue");
                    drawLabel(ck_width / 2 - TextStringWidth("�ɹ���Ӱ༶����Ա, ��ʼ����Ϊ123456") / 2, y - h * 4,
                              "�ɹ���Ӱ༶����Ա, ��ʼ����Ϊ123456");
                    classIdInt = 0;
                    classManagerIdInt = 0;
                }
            }
            break;
        case InsertIM:
            sprintf(options, "ȷ�����");
            if (button(GenUIID(0), ck_width / 2 - TextStringWidth("ȷ�����  ") / 2, y - h * 3.5,
                       TextStringWidth("ȷ�����  "), h, options)) {
                instIdInt = atoi(instIdStr);
                instManagerIdInt = atoi(instManagerIdStr);

                if (InsertInstManager(instIdInt)) {
                    SetPenColor("Blue");
                    drawLabel(ck_width / 2 - TextStringWidth("�ɹ����ѧԺ����Ա, ��ʼ����Ϊ123456") / 2, y - h * 4,
                              "�ɹ����ѧԺ����Ա, ��ʼ����Ϊ123456");
                    instIdInt = 0;
                    instManagerIdInt = 0;
                }
            }
            break;
        case InsertI:
            sprintf(options, "ȷ�����");
            if (button(GenUIID(0), ck_width / 2 - TextStringWidth("ȷ�����  ") / 2, y - h * 3.5,
                       TextStringWidth("ȷ�����  "), h, options)) {
                instIdInt = atoi(instIdStr);

                if (InsertInst()) {
                    SetPenColor("Blue");
                    drawLabel(ck_width / 2 - TextStringWidth("�ɹ����ѧԺ") / 2, y - h * 4,
                              "�ɹ����ѧԺ");
                    instIdInt = 0;
                }
            }
            break;
        default:
            break;
    }
}

// TODO
void DrawStuBotton(){
    double ChangH = GetFontHeight();
    double h = ChangH * 2;     // �ؼ��߶�
    double w = ck_width / 6; // �ؼ����
    double x = ck_width / 6;
    double y = GetWindowHeight() / 2;
    char options[100];

    switch (OptionInterface) {
        case StuOptions:
            for (int k = 0; k < 3; k++) {
                if (k == 0) {
                    sprintf(options, "�鿴�ɼ�");
                    if (button(GenUIID(k), ck_width / 2 - 1.5 * w, y, 0.8 * w, h, options)) { ;
                    }
                } else if (k == 1) {
                    sprintf(options, "�鿴�γ�");
                    if (button(GenUIID(k), ck_width / 2 - 0.5 * w, y, 0.8 * w, h, options)) { ;
                    }
                } else if (k == 2) {
                    sprintf(options, "�鿴��Ϣ");
                    if (button(GenUIID(k), ck_width / 2 + 0.5 * w, y, 0.8 * w, h, options)) { ;
                    }
                }
            }
            break;
        case InsertStu:
            sprintf(options, "ȷ�����");
            if (button(GenUIID(0), ck_width / 2 - TextStringWidth("ȷ�����  ") / 2, y - h * 3.5,
                       TextStringWidth("ȷ�����  "), h, options)) {
                ;
            }
            break;
        case InsertProf:
            sprintf(options, "ȷ�����");
            if (button(GenUIID(0), ck_width / 2 - TextStringWidth("ȷ�����  ") / 2, y - h * 3.5,
                       TextStringWidth("ȷ�����  "), h, options)) {
                ;
            }
            break;
        case InsertCM:
            sprintf(options, "ȷ�����");
            if (button(GenUIID(0), ck_width / 2 - TextStringWidth("ȷ�����  ") / 2, y - h * 3.5,
                       TextStringWidth("ȷ�����  "), h, options)) {
                ;
            }
            break;
        default:
            break;
    };
}

// TODO
void DrawProfBotton(){
    double ChangH = GetFontHeight();
    double h = ChangH * 2;     // �ؼ��߶�
    double w = ck_width / 6; // �ؼ����
    double x = ck_width / 6;
    double y = GetWindowHeight() / 2;
    char options[100];

    switch (OptionInterface) {
        case ProfessionOptions:
            for (int k = 0; k < 5; k++) {
                if (k == 0) {
                    sprintf(options, "�޸Ŀγ�");
                    if (button(GenUIID(k), ck_width / 2 - 2.5 * w, y, 0.8 * w, h, options)) { ;
                    }
                } else if (k == 1) {
                    sprintf(options, "���ѧ��");
                    if (button(GenUIID(k), ck_width / 2 - 1.5 * w, y, 0.8 * w, h, options)) { ;
                    }
                } else if (k == 2) {
                    sprintf(options, "ɾ��ѧ��");
                    if (button(GenUIID(k), ck_width / 2 - 0.5 * w, y, 0.8 * w, h, options)) { ;
                    }
                } else if (k == 3) {
                    sprintf(options, "�鿴����");
                    if (button(GenUIID(k), ck_width / 2 + 0.5 * w, y, 0.8 * w, h, options)) { ;
                    }
                } else if (k == 4) {
                    sprintf(options, "�ɼ����");
                    if (button(GenUIID(k), ck_width / 2 + 1.5 * w, y, 0.8 * w, h, options)) { ;
                    }
                }
            }
            break;
        case InsertStu:
            sprintf(options, "ȷ�����");
            if (button(GenUIID(0), ck_width / 2 - TextStringWidth("ȷ�����  ") / 2, y - h * 3.5,
                       TextStringWidth("ȷ�����  "), h, options)) {
                ;
            }
            break;
        case InsertProf:
            sprintf(options, "ȷ�����");
            if (button(GenUIID(0), ck_width / 2 - TextStringWidth("ȷ�����  ") / 2, y - h * 3.5,
                       TextStringWidth("ȷ�����  "), h, options)) {
                ;
            }
            break;
        case InsertCM:
            sprintf(options, "ȷ�����");
            if (button(GenUIID(0), ck_width / 2 - TextStringWidth("ȷ�����  ") / 2, y - h * 3.5,
                       TextStringWidth("ȷ�����  "), h, options)) {
                ;
            }
            break;
        case InsertIM:
            sprintf(options, "ȷ�����");
            if (button(GenUIID(0), ck_width / 2 - TextStringWidth("ȷ�����  ") / 2, y - h * 3.5,
                       TextStringWidth("ȷ�����  "), h, options)) {
                ;
            }
            break;
        case InsertI:
            sprintf(options, "ȷ�����");
            if (button(GenUIID(0), ck_width / 2 - TextStringWidth("ȷ�����  ") / 2, y - h * 3.5,
                       TextStringWidth("ȷ�����  "), h, options)) {
                ;
            }
            break;
        default:
            break;
    };
}

// TODO
void DrawInstBotton(){
    double ChangH = GetFontHeight();
    double h = ChangH * 2;     // �ؼ��߶�
    double w = ck_width / 6; // �ؼ����
    double x = ck_width / 6;
    double y = GetWindowHeight() / 2;
    char options[100];

    switch (OptionInterface) {
        case InstManagerOptions:
            for (int k = 0; k < 3; k++) {
                if (k == 0) {
                    sprintf(options, "��Ӱ༶");
                    if (button(GenUIID(k), ck_width / 2 - 1.5 * w, y, 0.8 * w, h, options)) {
                        OptionInterface = InsertClass;
                    }
                } else if (k == 1) {
                    sprintf(options, "��Ӱ༶����Ա");
                    if (button(GenUIID(k), ck_width / 2 - 0.5 * w, y, 0.8 * w, h, options)) {
                        OptionInterface = InsertCM;
                    }
                } else if (k == 2) {
                    sprintf(options, "����γ�");
                    if (button(GenUIID(k), ck_width / 2 + 0.5 * w, y, 0.8 * w, h, options)) {
                        OptionInterface = InsertCourse;
                    }
                }
            }
            break;
        case InsertClass:
            //TODO
            sprintf(options, "ȷ�����");
            if (button(GenUIID(0), ck_width / 2 - TextStringWidth("ȷ�����  ") / 2, y - h * 3.5,
                       TextStringWidth("ȷ�����  "), h, options)) {
                ;
            }
            break;
        case ModifyProfession:
            //TODO
            sprintf(options, "ȷ�����");
            if (button(GenUIID(0), ck_width / 2 - TextStringWidth("ȷ�����  ") / 2, y - h * 3.5,
                       TextStringWidth("ȷ�����  "), h, options)) {
                ;
            }
            break;
        case InsertCM:
            sprintf(options, "ȷ�����");
            if (button(GenUIID(0), ck_width / 2 - TextStringWidth("ȷ�����  ") / 2, y - h * 3.5,
                       TextStringWidth("ȷ�����  "), h, options)) {
                classIdInt = atoi(classIdStr);
                classManagerIdInt = atoi(classManagerIdStr);

                if (InsertClassManager(classIdInt)) {
                    SetPenColor("Blue");
                    drawLabel(ck_width / 2 - TextStringWidth("�ɹ���Ӱ༶����Ա, ��ʼ����Ϊ123456") / 2, y - h * 4,
                              "�ɹ���Ӱ༶����Ա, ��ʼ����Ϊ123456");
                    classIdInt = 0;
                    classManagerIdInt = 0;
                }
            }
            break;
        default:
            break;
    };
}

// ��ť��ʾ����
void drawButtons() {
    switch (FLAG) {
        case 0:
            DrawLoginBotton();
            break;
        case SuperAdmin:
            DrawSuperAdminBotton();
            break;
        case Students:
            DrawStuBotton();
            break;
        case Professions:
            DrawProfBotton();
        case InstManagers:
            DrawInstBotton();
    }
}

#endif // #if defined(DEMO_BUTTON)

void pm_display() {
    // ����
    DisplayClear();

#if defined(MENU)
    // ���ƺʹ���˵�
    drawMainMenu();
#endif

#if defined(BUTTON)
    // ��ť
    drawButtons();
#endif

#if defined(EDITBOX)
    // �༭�ı��ַ���
    drawEditText();
#endif
}
