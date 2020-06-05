//
// Created by ZODE on 2020/6/1.
//

#ifndef STUDENTS_MANAGER_PROFESSION_H
#define STUDENTS_MANAGER_PROFESSION_H
#include "DataManager.h"

int LoginProfession(int id, int passwd);
void ModifyCourseName(ProfessionList *, int courseId);
void pInsertStudents(ProfessionList *prof, int courseId);
void pDeleteStudents(ProfessionList *prof);
void ShowStuList(ProfessionList *prof, int courseId);

#endif //STUDENTS_MANAGER_PROFESSION_H
