//
// Created by ZODE on 2020/5/30.
//

#include "../include/DataManager.h"

void CheckProfession(int id, int passwd) {
    FILE *fp;
    int LoginFlag = 0;
    int listCount = 0;
    // 结构体初始化
    ProfessionList *thisList = (ProfessionList *) malloc(sizeof(ProfessionList));
    ProfessionList *ptr = thisList;
    thisList->next = NULL;
    thisList->id = 0;

    // 判断数据文件是否存在
    if ((fp = fopen("Students.txt", "rb")) == NULL) {
        puts("文件不存在.");
        return;
    }

    // 从文件中查询链表中学生信息
    while (!feof(fp) && thisList != NULL) {
        ProfessionList *tmpNode = (ProfessionList *) malloc(sizeof(ProfessionList));
        if (fread(tmpNode, sizeof(struct Student), 1, fp) == 1) {
            listCount++;
            tmpNode->next = NULL;
            thisList->next = tmpNode;
            thisList = thisList->next;
        }
    }

    fclose(fp);

    if (listCount == 0) {
        printf("文件中没有记录！\n");
        return;
    }

    while (ptr != NULL) {
        if (id == ptr->id) {
            if (ptr->password == passwd) {
                puts("查询到教授存在.");
                LoginFlag = 1;
            }
            break;
        }
        ptr = ptr->next;
    }

    if (LoginFlag == 0) {
        puts("教授不存在.");
        return;
    }

    /// 开始教授的操作
}

void CheckInstManager(int id, int passwd) {
    FILE *fp;
    int LoginFlag = 0;
    int listCount = 0;
    // 结构体初始化
    InstManagerList *thisList = (InstManagerList *) malloc(sizeof(InstManagerList));
    InstManagerList *ptr = thisList;
    thisList->next = NULL;
    thisList->id = 0;

    // 判断数据文件是否存在
    if ((fp = fopen("Students.txt", "rb")) == NULL) {
        puts("文件不存在.");
        return;
    }

    // 从文件中查询链表中学生信息
    while (!feof(fp) && thisList != NULL) {
        InstManagerList *tmpNode = (InstManagerList *) malloc(sizeof(InstManagerList));
        if (fread(tmpNode, sizeof(struct Student), 1, fp) == 1) {
            listCount++;
            tmpNode->next = NULL;
            thisList->next = tmpNode;
            thisList = thisList->next;
        }
    }

    fclose(fp);

    if (listCount == 0) {
        printf("文件中没有记录！\n");
        return;
    }

    while (ptr != NULL) {
        if (id == ptr->id) {
            if (ptr->password == passwd) {
                puts("查询到学院管理员存在");
                LoginFlag = 1;
            }
            break;
        }
        ptr = ptr->next;
    }

    if (LoginFlag == 0) {
        puts("管理员不存在");
        return;
    }

    /// 开始学院管理员的操作
}


char *itoa(int num, char *str, int radix) {
    // 索引表
    char index[] = "0123456789ABCDEF";
    unsigned unum;
    // 中间变量
    int i = 0, j, k;
    // 确定unum的值
    if (radix == 10 && num < 0)// 十进制负数
    {
        unum = (unsigned) -num;
        str[i++] = '-';
    } else unum = (unsigned) num;// 其他情况
    // 转换
    do {
        str[i++] = index[unum % (unsigned) radix];
        unum /= radix;
    } while (unum);
    str[i] = '\0';
    // 逆序
    if (str[0] == '-')
        k = 1;// 十进制负数
    else
        k = 0;

    for (j = k; j <= (i - 1) / 2; j++) {
        char temp;
        temp = str[j];
        str[j] = str[i - 1 + k - j];
        str[i - 1 + k - j] = temp;
    }
    return str;
}
