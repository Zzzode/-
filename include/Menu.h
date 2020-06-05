//
// Created by ZODE on 2020/5/30.
//

#ifndef STUDENTS_MANAGER_MENU_H
#define STUDENTS_MANAGER_MENU_H

#include "DataManager.h"
#include "Students.h"
#include "Profession.h"
#include "InstituteManager.h"
#include "ClassManager.h"
#include "SuperAdmin.h"
#include <stdio.h>

/// Login
int Login(int id, int password);

/// Files
void CreateNewFile();
//void OpenFile();
void CloseFile();
void SaveFile();
void Quit();

/// Institute
void ShowInstManagerMenu(InstManagerList *inst);

/// ClassManager
void ShowClassManagerMenu(ClassManagerList *classManager);

/// Profession
void ShowProfessionMenu(ProfessionList *prof);

/// Students
void ShowStudentMenu(StudentList *stu);

///  Help
void About();
void Usage();
void Copyright();

/// Status
void Status();

#endif //STUDENTS_MANAGER_MENU_H
