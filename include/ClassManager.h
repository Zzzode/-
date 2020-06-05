//
// Created by ZODE on 2020/6/1.
//

#ifndef STUDENTS_MANAGER_CLASSMANAGER_H
#define STUDENTS_MANAGER_CLASSMANAGER_H

#include "DataManager.h"

/// 在班级中批量添加学生
int cInsertStudents(int classId);
/// 登录
int LoginClassManager(int id, int password);
/// 查询学生
void cQueryStudent(int classId, int stuId);
/// 修改学生信息
void cModifyStudentInfo(int classId, int studentId);
/// 删除学生
void cDeleteStudents(int classId, int studentId);
/// 显示学生信息
void ShowStudentInfo(StudentList *stu);

#endif //STUDENTS_MANAGER_CLASSMANAGER_H
