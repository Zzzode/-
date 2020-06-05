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

static double ck_width, ck_height; // 窗口尺寸
static int FLAG = 0;               //用于清屏；
static int allowLoginBottons = 0; //允许登录按钮
//static int classID[10];
static char userId[80] = "";
static char passwd[80] = "";
// 班级管理员相关
int classManagerIdInt;
char classManagerIdStr[30];
char classManagerName[15];
// 学院管理员相关
int instManagerIdInt;
char instManagerIdStr[30];
char instManagerName[15];
// 班级相关全局变量
int classIdInt;
char classIdStr[30];
// 学生相关全局变量
int stuIdInt;
char stuIdStr[30];
char stuName[15];
// 界面选项
int OptionInterface;
// 选项
int selection;
// 教授相关全局变量
int profIdInt;
char profIdStr[30];
char profName[15];
// 学院相关
int instIdInt;
char instIdStr[30];
char instName[30];

void DisplayClear(void); //屏幕清理

void pm_display(void); //屏幕显示函数
void DrawLoginEditText();
void DrawSuperAdminEditText();

void DrawLoginBotton();

#endif //STUDENTS_MANAGER_INITIAL_H
