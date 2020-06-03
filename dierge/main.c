#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//#include<conio.h>

//结构体声明
typedef struct student
{
    char name[20];
    char num[20];
    char grade[20];
    int num1;
    int num2;
    int num3;
    struct student *next;
}Stu;

typedef struct login
{
    char account[20];
    char password[20];
    struct login *next;
}Login;

typedef struct use
{
    char user[20];
    char code[20];
    struct use *next;
}users;

//函数声明
void Menu(void);   //主界面*
void student_menu(void); //学生界面
void teacher_menu(void);  //老师界面*
void manager_menu(void);  //管理员界面*
//Stu *create1(void);  //创建链表，学生成绩录入
void create(Stu *head);
void create1(Login *head);
//Login *create(void);//创建链表，账号密码录入*
Stu *readlist1(void);//读取文件
Login *readlist(void);//读取文件*,,,账号和密码
void save1 (Stu *head); //信息(学生成绩）保存到文件*
void save (Login *head); //账号保存到文件*
void save2(users *head);
void search (Login *head); //查找账号和密码
void deleted(Login *head); //删除账号密码
void revise(Login *head); //修改账号密码*
void add(Login *head);  //增加账号密码
Stu *insert1(Stu *head);
Login *insert(Login *head);
//void showinfo(Stu *head); //输出账号密码
void watch_menu(void);  //查看代办事项
void search1_name(Stu *head);//查找学生成绩
void search1_num (Stu *head);
void  Input_login1(users *head);
void deleted1(Stu *head); //删除学生成绩
void revise1(Stu *head); //修改学生成绩*
void add1(Stu *head);  //增加学生成绩*
void showinfo1(Stu *head);//输出学生成绩（成绩分析）
void showinfo2(Stu *head);
void print1(Stu *head);
void print2(Stu *head);
void print(Login *head);
users* readlist2(void);
void registers(users *head);
users *insert2(users *head);
void  Input_login2(users *head);
void  Input_login3(users *head);
void showinfo(Stu *head){
}
void watch_menu(){
}


//主界面
void Menu()
{
    int n;
    
    system("cls");
    printf("\t\t\t|------------------------|\n");
    printf("\t\t\t|   ***学生管理系统****    |\n");
    printf("\t\t\t|------------------------|\n");
    printf("\t\t\t|     1.学生注册           |\n");
    printf("\t\t\t|     2.学生登陆           |\n");
    printf("\t\t\t|     3.老师登陆           ｜\n");
    printf("\t\t\t|     4.管理员登陆         ｜\n");
    printf("\t\t\t|     0.退出程序          ｜\n");
    printf("\t\t\t|------------------------|\n");
    printf("请选择1-4:");
    scanf("%d", &n);
    switch(n)
    {
    case 1:
        system("cls");
        //student_menu();
        users *head;
        head = readlist2();
        registers(head);
        //save2(head);
        break;
    case 2:
        system("cls");
        head = readlist2();
        Input_login1(head);
        break;
    case 3:
        system("cls");
        head = readlist2();
        Input_login2(head);
        break;
    case 4:
        system("cls");
        head = readlist2();
        Input_login3(head);
        break;
    case 0:
        exit(0);
    default:
        printf("输入有误，请重新输入！\n");
        Menu();
        break;
    }
}


/*注册文件到读取*/
users* readlist2()
{
    FILE *fp;
    users *head, *r, *ptemp;
    
    //head = (stu)malloc(sizeof(Stu));
    if((fp = fopen("/Users/guohongle/Desktop/user.txt", "r+")) == NULL)
    {
        printf("读取文件失败！");
        exit(1);
    }
    head = (users *)malloc(sizeof(users));
    head = NULL;
    r = head;
    while(!feof(fp))
    {
        ptemp =(users *)malloc(sizeof(users));
        fscanf(fp, "%s  %s\n", ptemp->user, ptemp->code);
        if(head == NULL)
        {
            head = ptemp;
            r = head;
        }else {
            r->next = ptemp;
            r = ptemp;
        }
    }
    r->next = NULL;
    fclose(fp);
    //getchar();
    return head;
}
void save2(users *head)
{
    users *p;
    FILE *fp;
    if((fp = fopen("/Users/guohongle/Desktop/user.txt","wt")) == NULL)
    {
        printf("打开文件失败！");
        //getchar();
        exit(0);
    }
    else {
        for(p = head; p != NULL; p = p->next)
            fprintf(fp, "%s  %s\n", p->user, p->code);
        printf("\n");
        printf("保存成功！\n");
        fclose(fp);
    }
}


/*注册*/
void registers(users *head)
{
    char name[20];
    
    users *h;
    head = readlist2();
    printf("请输入账号:");
    scanf("%s", name);
    for(h = head; h != NULL; h = h->next)
    {
        if(strcmp(h->user, name) == 0)
        {
            printf("此学生已存在！\n");
            break;
        }
    }
    if(h == NULL)
    {
        insert2(head);
        save2(head);
    }
    Menu();
}

users *insert2(users *head)
{
    char code1[20];
    users *pnew;
    head = readlist2();
    pnew = (users *)malloc(sizeof(users));
    printf("请输入账户：\n");
    scanf("%s", pnew->user);
    printf("请输入密码：\n");
    scanf("%s", pnew->code);
    printf("请再次确定密码\n");
    scanf("%s", code1);
    do {
        if(!strcmp(pnew->code, code1)) {
            pnew->next = head->next->next;
            head->next->next = pnew;
            printf("账号注册成功！\n");
            save2(head);
            Menu();
        }else {
            printf("两次密码不匹配！请重新输入！\n");
            scanf("%s",pnew->code);
            printf("请确认密码\n");
            scanf("%s", code1);
            Menu();
        }
    }while(1);
}

/*登录系统*/
void  Input_login1(users *head)
{
    char number[20];
    char code1[20];
    
    users *p;
    p = NULL;
    int i = 0;
    head = readlist2();
    printf("请输入账号：");
    scanf("%s", number);
    printf("请输入密码：");
    scanf("%s", code1);
    
    for(p = head; p != NULL; p = p->next)
    {
        if(strcmp(p->code ,code1)== 0 && strcmp(p->user, number) == 0)
        {
            printf("登陆成功！\n");
            student_menu();
            
        }
    }
    printf("密码错误！请重新输入：");
    scanf("%s", code1);
    i++;
    for(p = head; p != NULL; p = p->next)
    {
        if(strcmp(p->code ,code1)== 0 && strcmp(p->user, number) == 0)
        {
            printf("登陆成功！\n");
            student_menu();
            
        }
    }
    printf("密码错误！请重新输入：");
    scanf("%s", code1);
    i++;
    if(i == 0)
    {
        printf("未查找到该账户\n");
        printf("正在返回上一层...");
        Menu();
    }

}

void  Input_login2(users *head)
{
    char number[20];
    char code1[20];
    users *p;
    p = NULL;
    int i = 0;
    char c;
    head = readlist2();
    printf("请输入账号：");
    scanf("%s", number);
    printf("请输入密码：");
    //scanf("%s", code1);
    /*while(i < 7){
        system("stty -icanon");
        c = getchar();
        code1[i++] = c;
        printf("*");
        i++;
    }*/
    for(p = head; p != NULL; p = p->next)
    {
        if(strcmp(p->code ,code1)== 0 && strcmp(p->user, number) == 0)
        {
            printf("登陆成功！\n");
            teacher_menu();
        }
    }
    if(i == 0)
    {
        printf("未查找到该账户\n");
        printf("正在返回上一层...");
        Menu();
    }

}

void  Input_login3(users *head)
{
    char number[20];
    char code1[20];
    users *p;
    p = NULL;
    int i = 0;
    head = readlist2();
    printf("请输入账号：");
    scanf("%s", number);
    printf("请输入密码：");
    scanf("%s", code1);
    for(p = head; p != NULL; p = p->next)
    {
        if(strcmp(p->code ,code1)== 0 && strcmp(p->user, number) == 0)
        {
            printf("登陆成功！\n");
            manager_menu();
        }
    }
    if(i == 0)
    {
        printf("未查找到该账户\n");
        printf("正在返回上一层...");
        Menu();
    }

}


void student_menu()
{
    system("cls");
    int answer;
    struct student *head;
    head = readlist1();
    int n;
    printf("\n\n\n\n");
    printf("\t====================================\n");
    printf("\t|         欢迎进入学生管理系统          \n");
    printf("\t|         1.成绩查询                  \n");
    printf("\t|         2.查询本班成绩               \n");
    printf("\t|         3.成绩分析                  \n");
    printf("\t|         4.成绩申诉                  \n");
    printf("\t|         5.返回上一层                 \n");
    printf("\t|         0.退出                      \n");
    printf("\t======================================\n");
    scanf("%d", &n);
    switch (n) {
        case 1:
            system("cls");
            printf("请选择查询方式\n");
            printf("1.姓名\n2.学号\n");
            scanf("%d", &answer);
            if( answer == 1)
            {
                search1_name(head);//查询信息
            }
            if(answer == 2 )
            {
                search1_num(head);
            }
            if(answer != 1 && answer!= 2)
            {
                printf("输入错误\n");
            }
            student_menu();
        case 2:
            system("cls");
            print1(head);
            student_menu();
        case 3:
            system("cls");
            printf("请选择排序方式\n 1.升序  2.降序\n");
            scanf("%d", &answer);
            if(answer == 2)
            {
                showinfo1(head);
            }
            if(answer == 1 )
            {
                showinfo2(head);
            }
            if(answer != 1 && answer!= 2)
            {
                printf("输入错误\n");
            }
            student_menu();
        case 4:
            system("cls");
            printf("申诉成功！");
        case 5:
            system("cls");
            Menu();
        case 6:
            system("cls");
            break;
        default:
            system("pause");
            Menu();
            break;
    }
}

void teacher_menu()
{
    int n;
    int answer;
    Stu *head;
    head = readlist1();
    printf("\n\n\n\n");
    printf("\t------------------------------\n");
    printf("\t|      尊敬的老师您好！          |\n");
    printf("\t|      1.增加新的学生信息        |\n");  //*
    printf("\t|      2.删除学生信息           |\n");  //*
    printf("\t|      3.修改学生信息           |\n");  //*
    printf("\t|      4.查询学生信息           |\n");  //*
    printf("\t|      5.输出本班成绩           |\n");  //*
    printf("\t|      6.下载到文件             |\n");
    printf("\t|      7.成绩分析              |\n");  //*
    printf("\t|      8.提醒管理员进行成绩的更新  |\n");
    printf("\t|      9.返回上一层             |\n");  //*
    printf("请选择你要进行的操作：");
    scanf("%d", &n);
    switch (n) {
        case 1:
            system("cls");
            add1(head);
            teacher_menu();
            break;
        case 2:
            system("cls");
            deleted1(head);
            teacher_menu();
            break;
        case 3:
            system("cls");
            revise1(head);
            teacher_menu();
        case 4:
            //system("cls");
            //search1(head);
            //teacher_menu();
            printf("请选择查询方式\n");
            printf("1.姓名\n2.学号\n");
            scanf("%d", &answer);
            if( answer == 1)
            {
                search1_name(head);//查询信息
            }
            if(answer == 2 )
            {
                search1_num(head);
            }
            if(answer != 1 && answer!= 2)
            {
                printf("输入错误\n");
            }
            teacher_menu();
        case 5:
            system("cls");
            print1(head);
            teacher_menu();
        case 6:
            system("cls");
            save1(head);
            teacher_menu();
        case 7:
            system("cls");
            showinfo1(head);
            teacher_menu();
        case 8:
            system("cls");
            printf("进行成绩的更改！");
            manager_menu();
        case 9:
            system("cls");
            Menu();
            break;
        default:
            printf("输入有误，请重新输入！\n");
            system("cls");
            teacher_menu();
            break;
    }
}

void manager_menu()
{
    int n;
    Login *p, *head;
    head = readlist();
    //save(head);
    printf("\n\n\n\n");
    printf("\t-------------------------------\n");
    printf("\t|        尊敬的管理员您好！        \n");
    printf("\t|        1.录入所有的账号及密码         |\n");  //*
    printf("\t|        2.增加账号及密码              ｜\n");  //*
    printf("\t|        3.删除账号及密码              ｜\n");  //*
    printf("\t|        4.修改账号及密码              |\n");  //*
    printf("\t|        5.查找账号和密码              ｜\n");  //*
    printf("\t|        6.输出所有的账号和密码         ｜\n");  //*
    printf("\t|        7.下载所有的账号和密码到文件    ｜\n");  //*
    printf("\t|        8.进入教师端进行信息修改        ｜\n"); //*
    printf("\t|        9.返回上一层                  ｜\n");  //*
    printf("\t|        10.退出                      ｜\n");  //*
    printf("请选择您要进行的操作： ");
    scanf("%d", &n);
    switch(n)
    {
        case 1:
            system("cls");
            head = readlist();  //创建链表
            save(head); //保存函数
            manager_menu();
            break;
        case 2:
            system("cls");
            head = readlist();
            add(head);  //添加账号和密码
            manager_menu();
            break;
        case 3:
            system("cls");
            deleted(head);  //删除账号和密码
            manager_menu();
            break;
        case 4:
            system("cls");
            revise(head);  //修改账号和密码
            manager_menu();
            break;
        case 5:
            system("cls");
            search(head);  //查找账号和密码
            manager_menu();
            break;
        case 6:
            system("cls");
            //head = readlist();
            print(head);  //输出账号和密码
            manager_menu();
            break;
       case 7:
            system("cls");
            save(head);  //保存到文件
            manager_menu();
            break;
        case 8:
            system("cls");
            teacher_menu();
            break;
        case 9:
            system("cls");
            Menu();
            break;
        case 10:
            exit(0);
        default:
            printf("输入有误，请重新输入\n");
            system("pause");
            manager_menu();
            break;
    }
}



//读取文件,查看文件是否存在，若存在返回头指针。
Stu* readlist1()
{
    FILE *fp;
    Stu *head, *r, *ptemp;
    
    //head = (stu)malloc(sizeof(Stu));
    if((fp = fopen("/Users/guohongle/Desktop/class3.txt", "r+")) == NULL)
    {
        printf("读取文件失败！");
        exit(1);
    }
    head = (Stu *)malloc(sizeof(Stu));
    head = NULL;
    r = head;
    while(!feof(fp))
    {
        ptemp =(Stu *)malloc(sizeof(Stu));
        fscanf(fp, "%s  %s %s %d %d %d\n", ptemp->name, ptemp->num, ptemp->grade, &ptemp->num1, &ptemp->num2, &ptemp->num3);
        if(head == NULL)
        {
            head = ptemp;
            r = head;
        }else {
            r->next = ptemp;
            r = ptemp;
        }
    }
    r->next = NULL;
    fclose(fp);
    //getchar();
    return head;
}

Login* readlist()
{
    Login *head, *r, *ptemp;
    FILE *fp;
    if((fp = fopen("/Users/guohongle/Desktop/class2.txt", "r+")) == NULL)
    {
        printf("读取文件失败！");
    }
    head = (Login *)malloc(sizeof(Login));
    head = NULL;
    r = head;
    while(!feof(fp))
    {
        ptemp =(Login *)malloc(sizeof(Login));
        fscanf(fp, "%s %s\n", ptemp->account, ptemp->password);
        if(head == NULL)
        {
            head = ptemp;
            r = head;
        }else {
            r->next = ptemp;
            r = ptemp;
        }
    }
    r->next = NULL;
    fclose(fp);
    //getchar();
    return head;
}

void showinfo1(Stu *head){
    struct student *p = NULL;
    struct student *q = NULL;
    struct student *t = NULL;
    int x;
    char l[20], s[20];
     //char s;
     //char a;
     //if(head == NULL || head->next == NULL)
     //{
       //  return;
     //}
     for(p = head; p != NULL; p = p->next)
     {
         t = p;

         for(q = p->next; q != NULL; q = q->next)
         {
             if(q->num1 < t->num1)
             {
                 t = q;
             }
         }
         if(t != p)
         {
             x = p->num1;
             p->num1 = t->num1;
             t->num1 = x;
             strcpy(l, p->name);
             strcpy(p->name, t->name);
             strcpy(t->name, l);
             strcpy(s, p->num);
             strcpy(p->num, t->num);
             strcpy(t->num, s);
             //swap(p->num1, t->num1);
        }
     }
    printf("排序完成\n");
    getchar();
    save1(head);
}

void showinfo2(Stu *head){
    struct student *p = NULL;
    struct student *q = NULL;
    struct student *t = NULL;
    int x;
    char l[20], s[20];
     //char s;
     //char a;
     //if(head == NULL || head->next == NULL)
     //{
       //  return;
     //}
     for(p = head; p != NULL; p = p->next)
     {
         t = p;

         for(q = p->next; q != NULL; q = q->next)
         {
             if(q->num1 > t->num1)
             {
                 t = q;
             }
         }
         if(t != p)
         {
             x = p->num1;
             p->num1 = t->num1;
             t->num1 = x;
             strcpy(l, p->name);
             strcpy(p->name, t->name);
             strcpy(t->name, l);
             strcpy(s, p->num);
             strcpy(p->num, t->num);
             strcpy(t->num, s);
             //swap(p->num1, t->num1);
        }
     }
    printf("排序完成\n");
    getchar();
    save1(head);
}


//创建链表
void create1(Login *head)
{
    Stu *pnew, *pend;
    pnew = pend = (Stu *)malloc(sizeof(Stu));
    pnew->next = NULL;
    printf("请输入你的姓名：\n");
    scanf("%s", pnew->name);
    printf("请输入你的数学成绩：\n");
    scanf("%d", &pnew->num1);
    printf("请输入你的语文成绩：\n");
    scanf("%d", &pnew->num2);
    printf("请输入你的英语成绩：\n");
    scanf("%d", &pnew->num3);
    
    printf("\n");
    while(pnew->num1 != 0)
    {
        if(head == NULL)
        {
            head = pnew;
            pend = pnew;
        }
        else {
            pend->next = pnew;
            pend = pend->next;
        }
        pnew = (Stu *)malloc(sizeof(Stu));
        
        //printf("请输入你的账号：\n");
        //scanf("%s", pnew->account);
        //printf("请输入你的密码：\n");
        //scanf("%s", pnew->password);
        printf("请输入你的姓名：\n");
        scanf("%s", pnew->name);
        printf("请输入你的数学成绩：\n");
        scanf("%d", &pnew->num1);
        printf("请输入你的语文成绩：\n");
        scanf("%d", &pnew->num2);
        printf("请输入你的英语成绩：\n");
        scanf("%d", &pnew->num3);
        
        printf("\n");
        pnew->next = NULL;
    }
}

void create(Stu *head)
{
    
    Login *pnew, *pend;
    pnew = pend = (Login *)malloc(sizeof(Login));
    pnew->next = NULL;
    printf("请输入你的账号：\n");
    scanf("%s", pnew->account);
    printf("请输入你的密码：\n");
    scanf("%s", pnew->password);
    printf("\n");
    while(pnew->account[0] != '#')
    {
        if(head == NULL)
        {
            head = pnew;
            pend = pnew;
        }
        else {
            pend->next = pnew;
            pend = pend->next;
        }
        pnew = (Login *)malloc(sizeof(Login));
        
        printf("请输入你的账号：\n");
        scanf("%s", pnew->account);
        printf("请输入你的密码：\n");
        scanf("%s", pnew->password);
        
        printf("\n");
                pnew->next = NULL;
        }
}


//学生成绩信息保存至文件
void save1(Stu *head)
{
    Stu *p;
    FILE *fp;
    if((fp = fopen("/Users/guohongle/Desktop/class3.txt","wt")) == NULL)
    {
        printf("打开文件失败！");
        //getchar();
        exit(0);
    }
    else {
        for(p = head; p != NULL; p = p->next)
            fprintf(fp, "%s  %s %s %d %d %d\n", p->name, p->num, p->grade, p->num1, p->num2, p->num3);
        printf("\n");
        printf("保存成功！\n");
        fclose(fp);
    }
}
//账户信息保存至文件
void save(Login *head)
{
    Login *p;
    FILE *fp;
    if((fp = fopen("/Users/guohongle/Desktop/class2.txt","wt")) == NULL)
    {
        printf("打开文件失败！");
        //getchar();
        exit(0);
    }
    else {
        for(p = head; p != NULL; p = p->next)
            fprintf(fp, "%s %s\n",p->account, p->password);
        printf("\n");
        printf("保存成功！\n");
        fclose(fp);
    }
}

void print(Login *head)
{
    Login *p;
    for(p = head; p != NULL; p = p->next)
    {
        if(p == head)
        {
            printf("学生账户       学生密码\n");
            printf("-----------------------\n");
            printf("%-15s       %-15s\n", p->account, p->password);
        }
        else
        {
            printf("%-15s       %-15s\n", p->account, p->password);
        }
    }
}

void print1(Stu *head)
{
    Stu *p;
    p = head;
    while(p)
    {
        printf("%s\t %s\t %s\t %d\t %d\t %d\t\n",p->name, p->num, p->grade, p->num1, p->num2, p->num3);
        p = p->next;
    }
}

void print2(Stu *head)
{
    char name[20];
    scanf("%s", name);
    Stu *p;
    for(p = head; p != NULL; p = p->next)
    {
        if(p->name == name){
            printf("学生姓名    数学成绩    语文成绩    英语成绩\n");
            printf("------------------------------------------\n");
            printf("%-15s   %-15d   %-15d   %-15d",p->name, p->num1, p->num2, p->num3);
        }
    }
}


//修改学生成绩
void revise1()
{
    Stu *p, *head;
    head = readlist1();
    char name[20];
    int n, flag = 1;
    int i, j, k, l;
    while(flag)
    {
        system("cls");
        i = 0;
        j = 1;
        printf("\n\n");
        printf("请输入需要修改的学生姓名：");
        fflush(stdin);
        gets(name);
        for(p = head; p != NULL; p = p->next)
        {
            if((strcmp(p->name, name)) == 0)
            {
                i = 1;
                system("cls");
                printf("\n\n\n\n");
                printf("\t 您所查询的学生信息如下\n\n");
                printf("\t学生姓名          数学成绩        语文成绩        英语成绩");
                printf("\t-----------------------------------------------------\n");
                printf("\t%-15s     %-5d       %-5d      %-5d\n",p->name, p->num1, p->num2, p->num3);
                system("pause");
                while(j)
                {
                    printf("\n\n\n\n");
                    system("cls");
                    printf("\t          *****尊敬的老师您好！******        \n");
                    printf("\t------------------------------------------\n");
                    printf("\t|            1.修改学生姓名                 ｜\n");
                    printf("\t|            2.修改学生数学成绩              ｜\n");
                    printf("\t|            3.修改学生语文成绩              ｜\n");
                    printf("\t|            4.修改学生英语成绩              ｜\n");
                    printf("\t------------------------------------------\n");
                    printf("您要修改哪一项：");
                    scanf("%d", &n);
                    switch(n)
                    {
                        case 1:
                            printf("请输入修改后的学生姓名：");
                            scanf("%s", p->name);
                            break;
                        case 2:
                            printf("请输入修改后的数学成绩：");
                            scanf("%d", &p->num1);
                            break;
                        case 3:
                            printf("请输入修改后的语文成绩：");
                            scanf("%d", &p->num2);
                            break;
                        case 4:
                            printf("请输入修改后的英语成绩：");
                            scanf("%d", &p->num3);
                            break;
                        default:
                            printf("输入错误！！\n");
                            break;
                    }
                    printf("修改成功！");
                    system("cls");
                    save1(head);
                    printf("修改后的学生信息为：\n");
                    printf("\t-------------------------------------------\n");
                    printf("\t学生姓名        学生数学成绩       学生语文成绩      学生英语成绩\n");
                    printf("\t%-15s       %-5d       %-5d       %-5d\n", p->name, p->num1, p->num2, p->num3);
                    printf("是否继续修改？\n 1.继续\n0.退出\n");
                    scanf("%d", &k);
                    if(k == 0)
                        j = 0;
                }
                
            }
        }
        if(i == 0)
            printf("您所查询的学生不存在！\n");
        printf("是否继续修改其他学生信息？\n1.重新输入\t0.退出\n");
        scanf("%d", &l);
        if(l == 0)
            flag = 0;
    }
}

//修改账号密码信息
void revise()
{
    Login *p, *head;
    head = readlist();
    char account[20];
    int  flag = 1;
    int i, j;
    while(flag)
    {
        system("cls");
        i = 0;
        j = 1;
        printf("\n\n");
        printf("请输入需要修改的账号：");
        fflush(stdin);
        gets(account);
        for(p = head; p != NULL; p = p->next)
        {
            if((strcmp(p->account, account)) == 0)
            {
                i = 1;
                system("cls");
                printf("\n\n\n\n");
                printf("修改账号\n");
                printf("请输入新密码");
                scanf("%s", p->password);
                printf("修改完毕！请及时保存\n");
                save(head);
            }
            if(p == NULL)
            {
                printf("没有该学生账号\n");
            }
        }
        if(i == 0)
        {
            printf("没有该学生账号\n");
        }
        //save(head);
        manager_menu();
    }
    
}

void add1(Stu *head)
{
    char name1[20];
    Stu *h;
    head = readlist1();
    printf("请输入需要添加的学生姓名：");
    scanf("%s", name1);
    for(h = head; h != NULL; h = h->next)
    {
        if(strcmp(h->name, name1) == 0)
        {
            printf("此学生已存在，无需再次添加。\n");
            break;
        }
    }
    if(h == NULL)
    {
        head = insert1(head);
        save1(head);
    }
    teacher_menu();
}

Stu *insert1(Stu *head)
{
    Stu *pnew;
    head = readlist1();
    pnew = (Stu *)malloc(sizeof(Stu));
    printf("请输入学生名称：\n");
    scanf("%s", pnew->name);
    printf("请输入学生的学号：\n");
    scanf("%s", pnew->num);
    printf("请输入学生的班级：\n");
    scanf("%s", pnew->grade);
    printf("请输入学生数学成绩：\n");
    scanf("%d", &pnew->num1);
    printf("请输入学生语文成绩：\n");
    scanf("%d", &pnew->num2);
    printf("请输入学生英语成绩：\n");
    scanf("%d", &pnew->num3);
    pnew->next = head->next->next;
    head->next->next = pnew;
    return head;
}

void add()
{
    char account1[20];
    Login *h, *head;
    head = readlist();
    printf("请输入需要添加的学生账号：");
    scanf("%s", account1);
    for(h = head; h != NULL; h = h->next)
    {
        if(h->account == account1)
        {
            printf("此学生账号已存在，无需再次添加。\n");
            break;
        }
    }
    if(h == NULL)
    {
        head = insert(head);
        save(head);
        printf("添加后剩余账户的信息为：\n");
        print(head);
    }
    manager_menu();
}

Login *insert(Login *head)
{
    Login *pnew;
    head = readlist();
    pnew = (Login *)malloc(sizeof(Login));
    printf("请输入学生账户：\n");
    scanf("%s", pnew->account);
    printf("请输入学生密码：\n");
    scanf("%s", pnew->password);
    pnew->next = head;
    head = pnew;
    return head;
}

void deleted()
{
    char number[20];
    Login *head = readlist();
    Login *p = head, *q;
    printf("请输入需要删除的账号：");
    scanf("%s", number);
    int i = 0;
    while(p)
    {
        if(strcmp(p->account,number) != 0)
        {
            q = p;
            p = p->next;
        }
        else {
            if(p != head) {
                q->next = p->next;
                free(p);
                p = q->next;
            }
            else
            {
                head = head->next;
                free(p);
                p = head;
            }
            i++;
        }
    }
    if(i == 0)
    {
        printf("输入的账号不存在");
    }else {
        save(head);
        printf("删除后剩余账户的信息为：\n");
        print(head);
    }
}

void deleted1()
{
    char name[20];
    Stu *head = readlist1();
    Stu *p = head, *q;
    printf("请输入需要删除的学生姓名：");
    scanf("%s", name);
    while(p)
    {
        if(strcmp(p->name, name) != 0)
        {
            q = p;
            p = p->next;
        }
        else
        {
            if(p != head)
            {
                q->next = p->next;
                free(p);
                p = q->next;
            }
            else
            {
                head = head->next;
                free(p);
                p = head;
            }
        }
    }
    save1(head);
    printf("删除后剩余的学生信息：\n");
    print1(head);
}

void search (Login *head)
{
    char number[20];
    Login *p = NULL;
    int i = 0;
    head = readlist();
    printf("请输入要查询的编号：");
    scanf("%s", number);
    for(p = head; p != NULL; p = p->next)
    {
        if(strcmp(p->account ,number)== 0)
        {
            i++;
            p->next = NULL;
            print(p);
        }
    }
    if(i == 0)
    {
        printf("未查找到该账户\n");
        printf("正在返回上一层...");
        manager_menu();
    }
}

void search1_name(Stu *head)
{
    char name[20];
    Stu *p = NULL;
    int i = 0;
    head = readlist1();
    printf("请输入要查询的学生姓名：");
    scanf("%s", name);
    for(p = head; p != NULL; p = p->next)
    {
        if(strcmp(p->name, name)== 0)
        {
            i++;
            p->next = NULL;
            print1(p);
        }
    }
    if(i == 0)
    {
        printf("未找到对应的学生\n");
        printf("正在返回上一层...");
        system("cls");
        manager_menu();
    }
}

void search1_num(Stu *head)
{
    char num[20];
    Stu *p = NULL;
    int i = 0;
    head = readlist1();
    printf("请输入要查询的学生学号：");
    scanf("%s", num);
    for(p = head; p != NULL; p = p->next)
    {
        if(strcmp(p->num, num)== 0)
        {
            i++;
            p->next = NULL;
            print1(p);
        }
    }
    if(i == 0)
    {
        printf("未找到对应的学生\n");
        printf("正在返回上一层...");
        system("cls");
        manager_menu();
    }
}



int main() {
    //struct student *head,*head1;
    //system("mode con cols=90 lines=30");//调整窗口大小
    //head1 = readlist1();
    readlist();
    //save1(head);
    Menu();
    return 0;
}
