//
// Created by ZODE on 2020/5/30.
//

#include "Menu.h"
//#include "DataManager.h"

/**
 * @brief ѧ��ѧ��6λ ��ʦ���4λ �༶����3λ ѧԺ����Ա2λ
 * \brief ������ǿ��6λ
 * @return 0 ��¼����
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
            puts("��Ч��id������.");
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

// TODO 1 2 3 ������
void ShowStudentMenu(StudentList *stu) {
    int select = 0;
    printf("��ѡ��ѧ������: 1�鿴�ɼ� 2�鿴�γ� 3�޸ĸ�����Ϣ: ");
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
            puts("��Ч��ѡ��");
            break;
    }
}

// TODO 3 5 ��ʵ�ּ�����
void ShowProfessionMenu(ProfessionList *prof) {
    int select = 0;
    int id = 0;
    printf("��ѡ����ڲ���: 1�޸Ŀγ��� 2���ѧ�� 3ɾ��ѧ�� 4�鿴���� 5���: ");
    scanf("%d", &select);

    switch (select) {
        case 1:
            printf("������γ�id: ");
            scanf("%d", &id);
            ModifyCourseName(prof, id);
            break;
        case 2:
            printf("������γ�id��");
            scanf("%d", &id);
            pInsertStudents(prof, id);
            break;
        case 3:
            printf("��ʱ��δ�������\n");
//            pDeleteStudents(prof);
            break;
        case 4:
            printf("������γ�id");
            scanf("%d", &id);
            ShowStuList(prof, id);
            break;
        case 5:
            printf("��ʱ��δ�������\n");
            break;
        default:
            puts("��Ч��ѡ��");
            break;
    }
}

// TODO  4 ��ʵ��
void ShowClassManagerMenu(ClassManagerList *classManager) {
    int select = 0;
    int stuId;
    printf("��ѡ��༶����Ա����: 1���ѧ�� 2�޸�ѧ����Ϣ 3��ѯѧ�� 4ɾ��ѧ��: "); // ����Ϊ�༶����Աû���޸ĳɼ���Ȩ��
    scanf("%d", &select);

    switch (select) {
        case 1:
            cInsertStudents(classManager->classId);
            break;
        case 2:
            printf("������ѧ��id: ");
            scanf("%d", &stuId);
            cModifyStudentInfo(classManager->classId, stuId);
            break;
        case 3:
            printf("������ѧ��id: ");
            scanf("%d", &stuId);
            cQueryStudent(classManager->classId, stuId);
            break;
        case 4:
            printf("������ѧ��id: ");
            scanf("%d", &stuId);
            cDeleteStudents(classManager->classId, stuId);
            break;
        default:
            puts("��Ч��ѡ��");
            break;
    }
}

void ShowInstManagerMenu(InstManagerList *inst) {
    int select = 0;
    int classId = 0;
    printf("��ѡ��ѧԺ����Ա�Ĳ���: 1��Ӱ༶ 2ɾ���༶ 3�޸İ༶����Ա 4��Ӱ༶����Ա 5��ӿγ�: ");
    scanf("%d", &select);

    switch (select) {
        case 1:
            CreateClass();
            break;
        case 2:
            printf("������༶id: ");
            scanf("%d", &classId);
            DeleteClass(classId);
            break;
        case 3:
            printf("������༶id: ");
            scanf("%d", &classId);
            ModifyClassManager(classId);
            break;
        case 4:
            printf("������༶id: ");
            scanf("%d", &classId);
            InsertClassManager(classId);
            break;
        case 5:
            InsertCourses();
            break;
        default:
            puts("��Ч��ѡ��");
            break;
    }
}