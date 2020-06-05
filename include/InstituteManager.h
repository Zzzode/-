//
// Created by ZODE on 2020/6/1.
//

#ifndef STUDENTS_MANAGER_INSTITUTEMANAGER_H
#define STUDENTS_MANAGER_INSTITUTEMANAGER_H

int LoginInstManager(int id, int passwd);
void CreateClass();
void DeleteClass(int classId);
void ModifyClassManager(int classId);
int InsertProfession();
int InsertClassManager(int classId);
void InsertCourses();
void ClassItem();
void Summary();

#endif //STUDENTS_MANAGER_INSTITUTEMANAGER_H
