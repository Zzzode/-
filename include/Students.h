//
// Created by zhang on 2020/5/31.
//

#ifndef STUDENTS_MANAGER_STUDENTS_H
#define STUDENTS_MANAGER_STUDENTS_H

#include "DataManager.h"

int LoginStudent(int id, int passwd);
void ChangeMyInfo(StudentList *stu);
void Application();
void CheckGrade(StudentList *stu);
void CheckCourses(StudentList *stu);
void GatherInfo();

#endif //STUDENTS_MANAGER_STUDENTS_H
