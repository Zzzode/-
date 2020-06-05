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

void zf_process(char zf) //字符处理函数
{
    uiGetChar(zf); // GUI字符输入
    pm_display();  //刷新显示
}

void jp_process(int jp, int event) //键盘处理函数
{
    uiGetKeyboard(jp, event); // GUI获取键盘
    pm_display();              // 刷新显示
}

void sb_process(int x, int y, int button, int event) //鼠标处理函数
{
    uiGetMouse(x, y, button, event); //GUI获取鼠标
    pm_display();                     // 刷新显示
}

void initial() {
    // 初始化窗口和图形系统
    SetWindowTitle("学生信息管理系统");

    InitGraphics(); //初始化窗口

    ck_width = GetWindowWidth(); // 获得窗口尺寸
    ck_height = GetWindowHeight();

    // 注册时间响应函数
    registerCharEvent(zf_process);       // 字符
    registerKeyboardEvent(jp_process); // 键盘
    registerMouseEvent(sb_process);       // 鼠标
}

#if defined(MENU)

// 菜单演示程序
void drawMainMenu() {
    static char *UseIntroductions[] = {"功能",
                                       "返回 | Ctrl-E",
                                       "退出 | Ctrl-P"};
    static char *selectedLabel = NULL;

    double ChangH = GetFontHeight();
    double x = 0; //ChangH/8;
    double y = ck_height;
    double h = ChangH * 1.5;                               // 控件高度
    double w = TextStringWidth(UseIntroductions[0]) * 1.5; // 控件宽度
    double wlist = TextStringWidth(UseIntroductions[2]) * 1.2;
    int selection;

    // menu bar
    drawMenuBar(0, y - h, ck_width, h);
    // File 菜单
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

// 文本编辑程序
void DrawLoginEditText() {
    static char status[200] = "";
    static char hint[] = "请登录   ";
    static char title[120] = "欢迎来到  学生信息管理系统   ";
    double ChangH = GetFontHeight();
    double h = ChangH * 2;     // 控件高度
    double w = ck_width / 4.4; // 控件宽度
    double x = ck_width / 2.7;
    double y = ck_height / 2 - h;

    textbox(GenUIID(0), ck_width / 2 - TextStringWidth(title) / 2, 1.5 * y, TextStringWidth(title), 2 * h, title,
            sizeof(title));
    textbox(GenUIID(0), ck_width / 2 - TextStringWidth(hint) / 2, y, TextStringWidth(hint), h, hint, sizeof(hint));

    SetPenColor("Brown");
    drawLabel(ck_width / 2 - TextStringWidth("账户: ") - w / 2, (y -= h * 1.2) + ChangH * 0.7, "账户");
    if (textbox(GenUIID(0), ck_width / 2 - w / 2, y, w, h, userId, sizeof(userId))) {
        sprintf(status, "已输入id：%s 密码：%s", userId, passwd);
    }

    SetPenColor("Brown");
    drawLabel(ck_width / 2 - TextStringWidth("密码: ") - w / 2, (y -= h * 1.2) + ChangH * 0.7, "密码");
    if (textbox(GenUIID(0), ck_width / 2 - w / 2, y, w, h, passwd, sizeof(passwd))) {
        sprintf(status, "已输入id：%s 密码：%s", userId, passwd);
    }

    SetPenColor("Blue");
    drawLabel(x, y -= ChangH * 1.2, status);
}

void DrawSuperAdminEditText() {
    static char status[200] = "";
    static char title[] = " 欢迎超级管理员   ";
    static char insertStu[] = "正在添加新学生   ";
    static char insertProf[] = "正在添加新教授   ";
    static char insertCM[] = "正在添加新班级管理员   ";
    static char insertIM[] = "正在添加新学院管理员   ";
    static char insertI[] = "正在添加新学院   ";
    double ChangH = GetFontHeight();
    double h = ChangH * 2;     // 控件高度
    double w = ck_width / 4.4; // 控件宽度
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
            drawLabel(ck_width / 2 - w / 2 - TextStringWidth("学生id(6位数字) "), (y -= h * 1.2) + ChangH * 0.7,
                      "学生id(6位数字)");
            if (textbox(GenUIID(0), ck_width / 2 - w / 2, y, w, h, stuIdStr, sizeof(stuIdStr))) { ;
            }
            SetPenColor("Brown");
            drawLabel(ck_width / 2 - w / 2 - TextStringWidth("学生班级id "), (y -= h * 1.2) + ChangH * 0.7, "学生班级id");
            if (textbox(GenUIID(0), ck_width / 2 - w / 2, y, w, h, classIdStr, sizeof(classIdStr))) { ;
            }
            SetPenColor("Brown");
            drawLabel(ck_width / 2 - w / 2 - TextStringWidth("学生姓名 "), (y -= h * 1.2) + ChangH * 0.7, "学生姓名");
            if (textbox(GenUIID(0), ck_width / 2 - w / 2, y, w, h, stuName, sizeof(stuName))) { ;
            }
            break;
        case InsertProf:
            textbox(GenUIID(0), ck_width / 2 - TextStringWidth(insertProf) / 2, ck_height / 2 + h * 3,
                    TextStringWidth(insertProf), 1.5 * h,
                    insertProf,
                    sizeof(insertProf));
            SetPenColor("Brown");
            drawLabel(ck_width / 2 - w / 2 - TextStringWidth("教授id(4位数字) "), (y -= h * 1.2) + ChangH * 0.7,
                      "教授id(4位数字)");
            if (textbox(GenUIID(0), ck_width / 2 - w / 2, y, w, h, profIdStr, sizeof(profIdStr))) { ;
            }
            SetPenColor("Brown");
            drawLabel(ck_width / 2 - w / 2 - TextStringWidth("教授姓名 "), (y -= h * 1.2) + ChangH * 0.7, "教授姓名");
            if (textbox(GenUIID(0), ck_width / 2 - w / 2, y, w, h, profName, sizeof(profName))) { ;
            }
            break;
        case InsertCM:
            textbox(GenUIID(0), ck_width / 2 - TextStringWidth(insertCM) / 2, ck_height / 2 + h * 3,
                    TextStringWidth(insertCM), 1.5 * h,
                    insertCM,
                    sizeof(insertCM));
            SetPenColor("Brown");
            drawLabel(ck_width / 2 - w / 2 - TextStringWidth("班级管理员id(3位数字) "), (y -= h * 1.2) + ChangH * 0.7,
                      "班级管理员id(3位数字) ");
            if (textbox(GenUIID(0), ck_width / 2 - w / 2, y, w, h, classManagerIdStr, sizeof(classManagerIdStr))) { ;
            }
            SetPenColor("Brown");
            drawLabel(ck_width / 2 - w / 2 - TextStringWidth("班级id "), (y -= h * 1.2) + ChangH * 0.7, "班级id");
            if (textbox(GenUIID(0), ck_width / 2 - w / 2, y, w, h, classIdStr, sizeof(classIdStr))) { ;
            }
            SetPenColor("Brown");
            drawLabel(ck_width / 2 - w / 2 - TextStringWidth("管理员姓名 "), (y -= h * 1.2) + ChangH * 0.7, "管理员姓名");
            if (textbox(GenUIID(0), ck_width / 2 - w / 2, y, w, h, classManagerName, sizeof(classManagerName))) { ;
            }
            break;
        case InsertIM:
            textbox(GenUIID(0), ck_width / 2 - TextStringWidth(insertIM) / 2, ck_height / 2 + h * 3,
                    TextStringWidth(insertIM), 1.5 * h,
                    insertIM,
                    sizeof(insertIM));
            SetPenColor("Brown");
            drawLabel(ck_width / 2 - w / 2 - TextStringWidth("学院管理员id(2位数字) "), (y -= h * 1.2) + ChangH * 0.7,
                      "学院管理员id(2位数字)");
            if (textbox(GenUIID(0), ck_width / 2 - w / 2, y, w, h, instManagerIdStr, sizeof(instManagerIdStr))) { ;
            }
            SetPenColor("Brown");
            drawLabel(ck_width / 2 - w / 2 - TextStringWidth("学院id "), (y -= h * 1.2) + ChangH * 0.7, "学院id");
            if (textbox(GenUIID(0), ck_width / 2 - w / 2, y, w, h, instIdStr, sizeof(instIdStr))) { ;
            }
            SetPenColor("Brown");
            drawLabel(ck_width / 2 - w / 2 - TextStringWidth("管理员姓名 "), (y -= h * 1.2) + ChangH * 0.7, "管理员姓名");
            if (textbox(GenUIID(0), ck_width / 2 - w / 2, y, w, h, instManagerName, sizeof(instManagerName))) { ;
            }
            break;
        case InsertI:
            textbox(GenUIID(0), ck_width / 2 - TextStringWidth(insertI) / 2, ck_height / 2 + h * 3,
                    TextStringWidth(insertI), 1.5 * h,
                    insertI,
                    sizeof(insertI));
            SetPenColor("Brown");
            drawLabel(ck_width / 2 - w / 2 - TextStringWidth("学院id "), (y -= h * 1.2) + ChangH * 0.7,
                      "学院id");
            if (textbox(GenUIID(0), ck_width / 2 - w / 2, y, w, h, instIdStr, sizeof(instIdStr))) { ;
            }
            SetPenColor("Brown");
            drawLabel(ck_width / 2 - w / 2 - TextStringWidth("学院名 "), (y -= h * 1.2) + ChangH * 0.7, "学院名");
            if (textbox(GenUIID(0), ck_width / 2 - w / 2, y, w, h, instName, sizeof(instName))) { ;
            }
            break;
        default:
            break;
    }
}

// TODO
void DrawInstManagerEditText(){
    static char title[] = " 欢迎学院管理员   ";
    static char insertCM[] = "正在添加新班级管理员   ";
    double ChangH = GetFontHeight();
    double h = ChangH * 2;     // 控件高度
    double w = ck_width / 4; // 控件宽度
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
            drawLabel(ck_width / 2 - w / 2 - TextStringWidth("班级管理员id(3位数字) "), (y -= h * 1.2) + ChangH * 0.7,
                      "班级管理员id(3位数字) ");
            if (textbox(GenUIID(0), ck_width / 2 - w / 2, y, w, h, classManagerIdStr, sizeof(classManagerIdStr))) { ;
            }
            SetPenColor("Brown");
            drawLabel(ck_width / 2 - w / 2 - TextStringWidth("班级id "), (y -= h * 1.2) + ChangH * 0.7, "班级id");
            if (textbox(GenUIID(0), ck_width / 2 - w / 2, y, w, h, classIdStr, sizeof(classIdStr))) { ;
            }
            SetPenColor("Brown");
            drawLabel(ck_width / 2 - w / 2 - TextStringWidth("管理员姓名 "), (y -= h * 1.2) + ChangH * 0.7, "管理员姓名");
            if (textbox(GenUIID(0), ck_width / 2 - w / 2, y, w, h, classManagerName, sizeof(classManagerName))) { ;
            }
            break;
    }
}

// TODO
void DrawProfessionEditText(){
    static char title[] = " 欢迎教授   ";
    double ChangH = GetFontHeight();
    double h = ChangH * 2;     // 控件高度
    double w = ck_width / 6; // 控件宽度
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
    static char title[] = " 欢迎同学   ";
    double ChangH = GetFontHeight();
    double h = ChangH * 2;     // 控件高度
    double w = ck_width / 4; // 控件宽度
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
    double h = ChangH * 2; // 控件高度
    double x = ck_width / 13;
    double y = ck_height / 2 - h;
    double w = ck_width / 5; // 控件宽度

    if (button(GenUIID(0), x, y, w, h, allowLoginBottons ? "收起登录权限" : "选择你的权限并登录"))
        allowLoginBottons = !allowLoginBottons;

    if (allowLoginBottons) {
        int k = 0;
        for (k = 0; k < 4; k++) {
            char bottomLogin[100];
            if (k == 0) {
                sprintf(bottomLogin, "学院级别 登录");
                if (button(GenUIID(k), 6 * x + w * 1.2, y - k * h * 2, w, h, bottomLogin)) {
                    FLAG = Login(id, password);
                    OptionInterface = FLAG == InstManagers ? InstManagerOptions : 0;
                }
            } else if (k == 1) {
                sprintf(bottomLogin, "教师级别 登录");
                if (button(GenUIID(k), 6 * x + w * 1.2, y - k * h * 2, w, h, bottomLogin)) {
                    FLAG = Login(id, password);
                    OptionInterface = FLAG == Professions ? ProfessionOptions : 0;
                }
            } else if (k == 2) {
                sprintf(bottomLogin, "学生级别 登录");
                if (button(GenUIID(k), 6 * x + w * 1.2, y - k * h * 2, w, h, bottomLogin)) {
                    FLAG = Login(id, password);
                    OptionInterface = FLAG == Students ? StuOptions : 0;
                }
            } else if (k == 3) {
                sprintf(bottomLogin, "超管级别 登录");
                if (button(GenUIID(k), 6 * x + w * 1.2, y - k * h * 2, w, h, bottomLogin)) {
                    FLAG = Login(id, password);
                    OptionInterface = FLAG == SuperAdmin ? SuperOptions : 0;
                }
            }
        }
    }

    if (button(GenUIID(0), x, y - 1.5 * h, w, h, "更换系统界面颜色")) {
        static int times = 0;
        usePredefinedColors(++times);
    }

    if (button(GenUIID(0), x, y - 3 * h, w, h, "退出")) {
        exit(-1);
    }
}

void DrawSuperAdminBotton() {
    double ChangH = GetFontHeight();
    double h = ChangH * 2;     // 控件高度
    double w = ck_width / 6; // 控件宽度
    double x = ck_width / 6;
    double y = GetWindowHeight() / 2;
    char options[100];

    switch (OptionInterface) {
        case SuperOptions:
            for (int k = 0; k < 5; k++) {
                if (k == 0) {
                    sprintf(options, "添加学生");
                    if (button(GenUIID(k), ck_width / 2 - 2.5 * w, y, 0.8 * w, h, options)) {
                        // 显示学生选项
                        OptionInterface = InsertStu;
                    }
                } else if (k == 1) {
                    sprintf(options, "添加教师");
                    if (button(GenUIID(k), ck_width / 2 - 1.5 * w, y, 0.8 * w, h, options)) {
                        OptionInterface = InsertProf;
                    }
                } else if (k == 2) {
                    sprintf(options, "添加班管");
                    if (button(GenUIID(k), ck_width / 2 - 0.5 * w, y, 0.8 * w, h, options)) {
                        OptionInterface = InsertCM;
                    }
                } else if (k == 3) {
                    sprintf(options, "添加院管");
                    if (button(GenUIID(k), ck_width / 2 + 0.5 * w, y, 0.8 * w, h, options)) {
                        OptionInterface = InsertIM;
                    }
                } else if (k == 4) {
                    sprintf(options, "添加学院");
                    if (button(GenUIID(k), ck_width / 2 + 1.5 * w, y, 0.8 * w, h, options)) {
                        OptionInterface = InsertI;
                    }
                }
            }
            break;
        case InsertStu:
            sprintf(options, "确定添加");
            if (button(GenUIID(0), ck_width / 2 - TextStringWidth("确定添加  ") / 2, y - h * 3.5,
                       TextStringWidth("确定添加  "), h, options)) {
                stuIdInt = atoi(stuIdStr);
                classIdInt = atoi(classIdStr);

                if (cInsertStudents(classIdInt)) {
                    SetPenColor("Blue");
                    drawLabel(ck_width / 2 - TextStringWidth("成功添加学生, 初始密码为123456") / 2, y - h * 4,
                              "成功添加学生, 初始密码为123456");
                    stuIdInt = 0;
                    classIdInt = 0;
                }
            }
            break;
        case InsertProf:
            sprintf(options, "确定添加");
            if (button(GenUIID(0), ck_width / 2 - TextStringWidth("确定添加  ") / 2, y - h * 3.5,
                       TextStringWidth("确定添加  "), h, options)) {
                profIdInt = atoi(profIdStr);

                if (InsertProfession()) {
                    SetPenColor("Blue");
                    drawLabel(ck_width / 2 - TextStringWidth("成功添加教授, 初始密码为123456") / 2, y - h * 4,
                              "成功添加教授, 初始密码为123456");
                    profIdInt = 0;
                }
            }
            break;
        case InsertCM:
            sprintf(options, "确定添加");
            if (button(GenUIID(0), ck_width / 2 - TextStringWidth("确定添加  ") / 2, y - h * 3.5,
                       TextStringWidth("确定添加  "), h, options)) {
                classIdInt = atoi(classIdStr);
                classManagerIdInt = atoi(classManagerIdStr);

                if (InsertClassManager(classIdInt)) {
                    SetPenColor("Blue");
                    drawLabel(ck_width / 2 - TextStringWidth("成功添加班级管理员, 初始密码为123456") / 2, y - h * 4,
                              "成功添加班级管理员, 初始密码为123456");
                    classIdInt = 0;
                    classManagerIdInt = 0;
                }
            }
            break;
        case InsertIM:
            sprintf(options, "确定添加");
            if (button(GenUIID(0), ck_width / 2 - TextStringWidth("确定添加  ") / 2, y - h * 3.5,
                       TextStringWidth("确定添加  "), h, options)) {
                instIdInt = atoi(instIdStr);
                instManagerIdInt = atoi(instManagerIdStr);

                if (InsertInstManager(instIdInt)) {
                    SetPenColor("Blue");
                    drawLabel(ck_width / 2 - TextStringWidth("成功添加学院管理员, 初始密码为123456") / 2, y - h * 4,
                              "成功添加学院管理员, 初始密码为123456");
                    instIdInt = 0;
                    instManagerIdInt = 0;
                }
            }
            break;
        case InsertI:
            sprintf(options, "确定添加");
            if (button(GenUIID(0), ck_width / 2 - TextStringWidth("确定添加  ") / 2, y - h * 3.5,
                       TextStringWidth("确定添加  "), h, options)) {
                instIdInt = atoi(instIdStr);

                if (InsertInst()) {
                    SetPenColor("Blue");
                    drawLabel(ck_width / 2 - TextStringWidth("成功添加学院") / 2, y - h * 4,
                              "成功添加学院");
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
    double h = ChangH * 2;     // 控件高度
    double w = ck_width / 6; // 控件宽度
    double x = ck_width / 6;
    double y = GetWindowHeight() / 2;
    char options[100];

    switch (OptionInterface) {
        case StuOptions:
            for (int k = 0; k < 3; k++) {
                if (k == 0) {
                    sprintf(options, "查看成绩");
                    if (button(GenUIID(k), ck_width / 2 - 1.5 * w, y, 0.8 * w, h, options)) { ;
                    }
                } else if (k == 1) {
                    sprintf(options, "查看课程");
                    if (button(GenUIID(k), ck_width / 2 - 0.5 * w, y, 0.8 * w, h, options)) { ;
                    }
                } else if (k == 2) {
                    sprintf(options, "查看信息");
                    if (button(GenUIID(k), ck_width / 2 + 0.5 * w, y, 0.8 * w, h, options)) { ;
                    }
                }
            }
            break;
        case InsertStu:
            sprintf(options, "确定添加");
            if (button(GenUIID(0), ck_width / 2 - TextStringWidth("确定添加  ") / 2, y - h * 3.5,
                       TextStringWidth("确定添加  "), h, options)) {
                ;
            }
            break;
        case InsertProf:
            sprintf(options, "确定添加");
            if (button(GenUIID(0), ck_width / 2 - TextStringWidth("确定添加  ") / 2, y - h * 3.5,
                       TextStringWidth("确定添加  "), h, options)) {
                ;
            }
            break;
        case InsertCM:
            sprintf(options, "确定添加");
            if (button(GenUIID(0), ck_width / 2 - TextStringWidth("确定添加  ") / 2, y - h * 3.5,
                       TextStringWidth("确定添加  "), h, options)) {
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
    double h = ChangH * 2;     // 控件高度
    double w = ck_width / 6; // 控件宽度
    double x = ck_width / 6;
    double y = GetWindowHeight() / 2;
    char options[100];

    switch (OptionInterface) {
        case ProfessionOptions:
            for (int k = 0; k < 5; k++) {
                if (k == 0) {
                    sprintf(options, "修改课程");
                    if (button(GenUIID(k), ck_width / 2 - 2.5 * w, y, 0.8 * w, h, options)) { ;
                    }
                } else if (k == 1) {
                    sprintf(options, "添加学生");
                    if (button(GenUIID(k), ck_width / 2 - 1.5 * w, y, 0.8 * w, h, options)) { ;
                    }
                } else if (k == 2) {
                    sprintf(options, "删除学生");
                    if (button(GenUIID(k), ck_width / 2 - 0.5 * w, y, 0.8 * w, h, options)) { ;
                    }
                } else if (k == 3) {
                    sprintf(options, "查看名单");
                    if (button(GenUIID(k), ck_width / 2 + 0.5 * w, y, 0.8 * w, h, options)) { ;
                    }
                } else if (k == 4) {
                    sprintf(options, "成绩打分");
                    if (button(GenUIID(k), ck_width / 2 + 1.5 * w, y, 0.8 * w, h, options)) { ;
                    }
                }
            }
            break;
        case InsertStu:
            sprintf(options, "确定添加");
            if (button(GenUIID(0), ck_width / 2 - TextStringWidth("确定添加  ") / 2, y - h * 3.5,
                       TextStringWidth("确定添加  "), h, options)) {
                ;
            }
            break;
        case InsertProf:
            sprintf(options, "确定添加");
            if (button(GenUIID(0), ck_width / 2 - TextStringWidth("确定添加  ") / 2, y - h * 3.5,
                       TextStringWidth("确定添加  "), h, options)) {
                ;
            }
            break;
        case InsertCM:
            sprintf(options, "确定添加");
            if (button(GenUIID(0), ck_width / 2 - TextStringWidth("确定添加  ") / 2, y - h * 3.5,
                       TextStringWidth("确定添加  "), h, options)) {
                ;
            }
            break;
        case InsertIM:
            sprintf(options, "确定添加");
            if (button(GenUIID(0), ck_width / 2 - TextStringWidth("确定添加  ") / 2, y - h * 3.5,
                       TextStringWidth("确定添加  "), h, options)) {
                ;
            }
            break;
        case InsertI:
            sprintf(options, "确定添加");
            if (button(GenUIID(0), ck_width / 2 - TextStringWidth("确定添加  ") / 2, y - h * 3.5,
                       TextStringWidth("确定添加  "), h, options)) {
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
    double h = ChangH * 2;     // 控件高度
    double w = ck_width / 6; // 控件宽度
    double x = ck_width / 6;
    double y = GetWindowHeight() / 2;
    char options[100];

    switch (OptionInterface) {
        case InstManagerOptions:
            for (int k = 0; k < 3; k++) {
                if (k == 0) {
                    sprintf(options, "添加班级");
                    if (button(GenUIID(k), ck_width / 2 - 1.5 * w, y, 0.8 * w, h, options)) {
                        OptionInterface = InsertClass;
                    }
                } else if (k == 1) {
                    sprintf(options, "添加班级管理员");
                    if (button(GenUIID(k), ck_width / 2 - 0.5 * w, y, 0.8 * w, h, options)) {
                        OptionInterface = InsertCM;
                    }
                } else if (k == 2) {
                    sprintf(options, "插入课程");
                    if (button(GenUIID(k), ck_width / 2 + 0.5 * w, y, 0.8 * w, h, options)) {
                        OptionInterface = InsertCourse;
                    }
                }
            }
            break;
        case InsertClass:
            //TODO
            sprintf(options, "确定添加");
            if (button(GenUIID(0), ck_width / 2 - TextStringWidth("确定添加  ") / 2, y - h * 3.5,
                       TextStringWidth("确定添加  "), h, options)) {
                ;
            }
            break;
        case ModifyProfession:
            //TODO
            sprintf(options, "确定添加");
            if (button(GenUIID(0), ck_width / 2 - TextStringWidth("确定添加  ") / 2, y - h * 3.5,
                       TextStringWidth("确定添加  "), h, options)) {
                ;
            }
            break;
        case InsertCM:
            sprintf(options, "确定添加");
            if (button(GenUIID(0), ck_width / 2 - TextStringWidth("确定添加  ") / 2, y - h * 3.5,
                       TextStringWidth("确定添加  "), h, options)) {
                classIdInt = atoi(classIdStr);
                classManagerIdInt = atoi(classManagerIdStr);

                if (InsertClassManager(classIdInt)) {
                    SetPenColor("Blue");
                    drawLabel(ck_width / 2 - TextStringWidth("成功添加班级管理员, 初始密码为123456") / 2, y - h * 4,
                              "成功添加班级管理员, 初始密码为123456");
                    classIdInt = 0;
                    classManagerIdInt = 0;
                }
            }
            break;
        default:
            break;
    };
}

// 按钮演示程序
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
    // 清屏
    DisplayClear();

#if defined(MENU)
    // 绘制和处理菜单
    drawMainMenu();
#endif

#if defined(BUTTON)
    // 按钮
    drawButtons();
#endif

#if defined(EDITBOX)
    // 编辑文本字符串
    drawEditText();
#endif
}
