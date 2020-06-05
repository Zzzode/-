//
// Created by ZODE on 2020/5/30.
//

#include "Menu.h"
//#include "DataManager.h"

/**
 * @brief 学生学号6位 教师编号4位 班级管理3位 学院管理员2位
 * \brief 简化密码强制6位
 * @return 0 登录错误
 */
int Login(int id, int password) {
    int identity = 0;

    if (id == 1 && password == 111111)
        identity = SuperAdmin;
    else {
        identity = id >= 100000 ? Students : (id >= 1000 ? Professions : (id >= 100 ? ClassManager : (id >= 10
                                                                                                      ? InstManagers
                                                                                                      : 0)));
        if (identity == 0 || password / 100000 == 0 || password / 100000 >= 10) {
            puts("无效的id或密码.");
            return 0;
        }
    }

    switch (identity) {
        case Students:
            return LoginStudent(id, password);
        case ClassManager:
            return LoginClassManager(id, password);
        case Professions:
            return LoginProfession(id, password);
        case InstManagers:
            return LoginInstManager(id, password);
        case SuperAdmin:
            return SuperAdmin;
            return LoginAdmin();
        default:
            return 0;
    }
}

// TODO 1 2 3 待测试
void ShowStudentMenu(StudentList *stu) {
    int select = 0;
    printf("请选择学生操作: 1查看成绩 2查看课程 3修改个人信息: ");
    scanf("%d", &select);

    switch (select) {
        case 1:
            CheckGrade(stu);
            break;
        case 2:
            CheckCourses(stu);
            break;
        case 3:
            ChangeMyInfo(stu);
            break;
        default:
            puts("无效的选项");
            break;
    }
}

// TODO 3 5 待实现及测试
void ShowProfessionMenu(ProfessionList *prof) {
    int select = 0;
    int id = 0;
    printf("请选择教授操作: 1修改课程名 2添加学生 3删除学生 4查看名单 5打分: ");
    scanf("%d", &select);

    switch (select) {
        case 1:
            printf("请输入课程id: ");
            scanf("%d", &id);
            ModifyCourseName(prof, id);
            break;
        case 2:
            printf("请输入课程id：");
            scanf("%d", &id);
            pInsertStudents(prof, id);
            break;
        case 3:
            printf("暂时还未调试完成\n");
//            pDeleteStudents(prof);
            break;
        case 4:
            printf("请输入课程id");
            scanf("%d", &id);
            ShowStuList(prof, id);
            break;
        case 5:
            printf("暂时还未调试完成\n");
            break;
        default:
            puts("无效的选项");
            break;
    }
}

// TODO  4 待实现
void ShowClassManagerMenu(ClassManagerList *classManager) {
    int select = 0;
    int stuId;
    printf("请选择班级管理员操作: 1添加学生 2修改学生信息 3查询学生 4删除学生: "); // 我认为班级管理员没有修改成绩的权限
    scanf("%d", &select);

    switch (select) {
        case 1:
            cInsertStudents(classManager->classId);
            break;
        case 2:
            printf("请输入学生id: ");
            scanf("%d", &stuId);
            cModifyStudentInfo(classManager->classId, stuId);
            break;
        case 3:
            printf("请输入学生id: ");
            scanf("%d", &stuId);
            cQueryStudent(classManager->classId, stuId);
            break;
        case 4:
            printf("请输入学生id: ");
            scanf("%d", &stuId);
            cDeleteStudents(classManager->classId, stuId);
            break;
        default:
            puts("无效的选项");
            break;
    }
}

void ShowInstManagerMenu(InstManagerList *inst) {
    int select = 0;
    int classId = 0;
    printf("请选择学院管理员的操作: 1添加班级 2删除班级 3修改班级管理员 4添加班级管理员 5添加课程: ");
    scanf("%d", &select);

    switch (select) {
        case 1:
            CreateClass();
            break;
        case 2:
            printf("请输入班级id: ");
            scanf("%d", &classId);
            DeleteClass(classId);
            break;
        case 3:
            printf("请输入班级id: ");
            scanf("%d", &classId);
            ModifyClassManager(classId);
            break;
        case 4:
            printf("请输入班级id: ");
            scanf("%d", &classId);
            InsertClassManager(classId);
            break;
        case 5:
            InsertCourses();
            break;
        default:
            puts("无效的选项");
            break;
    }
}