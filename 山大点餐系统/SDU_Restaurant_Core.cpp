#pragma warning(disable:6011)//警告C6011：取消对NULL指针的引用；已在Assert_Program(void* ptr)中进行判断
#include "SDU_Restaurant_Core.h"
#include "SDU_Restaurant_IO.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graphics.h>    
#include <windows.h>
#include <time.h>
extern struct SDU_Restaurant_Data SDU_Restaurant;

/*————————功能性函数————————*/

/*判断异常*/
void Assert_Program(void* ptr)
{
    if (ptr == NULL)
    {
        printf("程序发生错误 !即将退出程序...\n"); //原因可能是堆内存分配失败，系统内存不足导致
        SDU_Restaurant_Sleep(1000);
        exit(EXIT_FAILURE);
    }
}

/*休眠暂停*/
void SDU_Restaurant_Sleep(unsigned long dwMilliseconds)
{
    Sleep((DWORD)dwMilliseconds); //在<window.h>里 typedef unsigned long DWORD
}

/*初始化控制台字体和字体大小*/
VOID ChangeConsoleForntsAndSize(VOID)
{
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof cfi;
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;
    cfi.dwFontSize.Y = 16;
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    wcscpy_s(cfi.FaceName, L"楷体");
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

/*隐藏光标*/
VOID HideConsoleCursor(VOID)
{
    CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

/*获得终端宽度*/
LONG GetWindowWidth(HWND hwnd)
{
    RECT rect;
    GetWindowRect(hwnd, &rect);
    return (rect.right - rect.left);
}

/*获得终端高度*/
LONG GetWindowHeight(HWND hwnd)
{
    RECT rect;
    GetWindowRect(hwnd, &rect);
    return (rect.bottom - rect.top);
}

/*初始化控制台窗口*/
void SDU_Restaurant_Console_Init(void)
{
    // HideConsoleCursor();//隐藏光标
    ChangeConsoleForntsAndSize(); //改变字体和字体大小
    int nWidth = GetWindowWidth(GetConsoleWindow());
    int nHeight = GetWindowHeight(GetConsoleWindow());
    MoveWindow(GetConsoleWindow(), 520, 100, nWidth, nHeight, TRUE);
    SetConsoleTitle(TEXT("山 大 餐 饮 系 统"));
    system("mode con cols=60 lines=35");
    //获取当前窗口句柄
    HWND hwnd = GetHWnd();
    //把黑色的背景设置为透明
    SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 150, LWA_ALPHA);
}

/*VIP判断*/
int Judge_VIP( long long int phonenum)
{
    NODE_V* pr = SDU_Restaurant.current_vip;
    for (; pr != NULL; pr = pr->next)
    {
        if (pr->data.phonenum == phonenum ) {
            return 1;
        }
    }
    return 0;
}
/*日期判断*/
void Judge_Date(NODE_D* pHead_d)
{
    struct tm flag;
    time_t now;
    time(&now);
    localtime_s(&flag,&now);

    if (pHead_d == NULL)
    {
        /*清空营业额*/
        SDU_Restaurant.Day_Profit = 0;
        /*更新时间*/
        struct Date Current_Date;
        Current_Date.year = flag.tm_year + 1900;
        Current_Date.month = flag.tm_mon + 1;
        Current_Date.day = flag.tm_mday;
        Current_Date.profit = 0;

        SDU_Add_Date(pHead_d, Current_Date);
        Save_Date_Inform();

        return;
    }
    else if (!(flag.tm_year + 1900 == pHead_d->data.year && flag.tm_mday == pHead_d->data.day && flag.tm_mon + 1 == pHead_d->data.month)) //不是同一天
    {

        /*清空营业额*/
        SDU_Restaurant.Day_Profit = 0;
        /*更新时间*/
        struct Date Current_Date;
        Current_Date.year = flag.tm_year + 1900;
        Current_Date.month = flag.tm_mon + 1;
        Current_Date.day = flag.tm_mday;
        Current_Date.profit = 0;

        SDU_Add_Date(pHead_d, Current_Date);
        Save_Date_Inform();
    }
}

/*程序初始化*/
void SDU_Restaurant_Init(int argc, char const* argv[])
{
    SDU_Restaurant_Console_Init(); //初始化控制台窗口

    //Create_DataBaseFiles(); //初始化数据文件，历史数据将被覆盖

    int num; // num作为循环利用变量，每次从文件中录入数值时，先重置为0，再随文件内容进行更新

    /*读取菜品数据*/
    struct food* Read_foods;
    Read_Food_Inform(&Read_foods, &num);
    NODE_F* pHead_f = Load_Food_Inform(Read_foods, num);
    SDU_Restaurant.current_foods = pHead_f;
    SDU_Restaurant.foodsCount = num;

    /*读取服务员数据*/
    struct Waiter* Read_waiters;
    Read_Waiter_Inform(&Read_waiters, &num);
    NODE_W* pHead_w = Load_Waiter_Inform(Read_waiters, num);
    SDU_Restaurant.current_waiters = pHead_w;
    SDU_Restaurant.waitersCount = num;
    SDU_Restaurant.waiter_Login = NULL;

    /*读取顾客数据*/
    struct Customer* Read_customers;
    Read_Customer_Inform(&Read_customers, &num);
    NODE_C* pHead_c = Load_Customer_Inform(Read_customers, num);
    SDU_Restaurant.current_customer = pHead_c;
    SDU_Restaurant.customerCount = num;

    /*读取VIP数据*/
    struct VIP* Read_vips;
    Read_VIP_Inform(&Read_vips, &num);
    NODE_V* pHead_v = Load_VIP_Inform(Read_vips, num);
    SDU_Restaurant.current_vip = pHead_v;
    SDU_Restaurant.vipsCount = num;

    /*读取日期数据*/
    struct Date* Read_dates;
    Read_Date_Inform(&Read_dates, &num);
    NODE_D* pHead_d = Load_Profit_Inform(Read_dates, num);
    SDU_Restaurant.current_date = pHead_d;
    SDU_Restaurant.dateCount = num;
    if (SDU_Restaurant.current_date != NULL)
        SDU_Restaurant.Day_Profit = SDU_Restaurant.current_date->data.profit;
    Judge_Date(SDU_Restaurant.current_date); //判断系统日期，决定是否清空当日营业额

    /*读取座位信息*/
    Read_SeatMap_Inform((struct Seat*)&SDU_Restaurant.seatsMap);

    /*初始化current_user结构体*/
    SDU_Restaurant.user = UserType::undefine;
}

/*————————增添链表操作————————*/

/*——尾插法——*/
/*将菜品数据添加到菜品链表尾部*/
NODE_F* Add_To_Tail(NODE_F* pHead_f, struct food Data)
{
    /*创建新的链表节点*/
    NODE_F* pNode = (NODE_F*)malloc(sizeof(NODE_F));
    Assert_Program(pNode);
    if (pNode != NULL) {
        pNode->data = Data;
        pNode->next = NULL;
    }
    /*若原链表为空*/
    if (pHead_f == NULL)
    {
        if (pNode != NULL) {
            pNode->next = pHead_f;
            pHead_f = pNode;
        }
    }

    /*若原链表非空*/
    else
    {
        NODE_F* pr = NULL;
        pr = pHead_f;
        while (!(pr->next == NULL)) //迭代到链表尾部
        {
            pr = pr->next;
        }
        pr->next = pNode; //添加新结点到链表尾部
    }
    return pHead_f;
}

/*将服务员数据添加到服务员链表尾部*/
NODE_W* Add_To_Tail(NODE_W* pHead_w, struct Waiter Data)
{
    /*创建新的链表节点*/
    NODE_W* pNode = (NODE_W*)malloc(sizeof(NODE_W));
    Assert_Program(pNode);
    if (pNode != NULL)
    {
        pNode->data = Data;
        pNode->next = NULL;

        /*若原链表为空*/
        if (pHead_w == NULL)
        {
            pNode->next = pHead_w;
            pHead_w = pNode;
        }

        /*若原链表非空*/
        else
        {
            NODE_W* pr = NULL;
            pr = pHead_w;
            while (!(pr->next == NULL)) //迭代到链表尾部
            {
                pr = pr->next;
            }
            pr->next = pNode; //添加新结点到链表尾部
        }
    }
    return pHead_w;
}

/*——头插法——*/
/*将菜品数据添加到菜品链表头部*/
NODE_F* Add_To_Head(NODE_F* pHead_f, struct food data)
{
    /*创建新的链表节点*/
    NODE_F* pNode = (NODE_F*)malloc(sizeof(NODE_F));
    Assert_Program(pNode);
    if (pNode != NULL)
    {
        pNode->data = data;
        pNode->next = NULL;
        pNode->next = pHead_f; //添加新结点到链表头部
        pHead_f = pNode;
    }
    return pHead_f;
}

/*将服务员数据添加到服务员链表头部*/
NODE_W* Add_To_Head(NODE_W* pHead_w, struct Waiter data)
{
    /*创建新的链表节点*/
    NODE_W* pNode = (NODE_W*)malloc(sizeof(NODE_W));
    Assert_Program(pNode);
    if (pNode != NULL)
    {
        pNode->data = data;
        pNode->next = NULL;
        pNode->next = pHead_w; //添加新结点到链表头部
        pHead_w = pNode;
    }
    return pHead_w;
}

/*将日期数据添加到日期链表头部*/
NODE_D* Add_To_Head(NODE_D* pHead_d, struct Date data)
{
    /*创建新的链表节点*/
    NODE_D* pNode = (NODE_D*)malloc(sizeof(NODE_D));
    Assert_Program(pNode);
    if (pNode != NULL)
    {
        pNode->data = data;
        pNode->next = NULL;
        pNode->next = pHead_d; //添加新结点到链表头部
        pHead_d = pNode;
    }
    return pHead_d;
}

/*————————打印链表操作————————*/

/*遍历输出食物链表信息*/
void Print_LinkTable(NODE_F* pHead_f)
{
    NODE_F* pr = NULL;
    if (0 == SDU_Restaurant.foodsCount)
        return;
    for (pr = pHead_f; !(pr == NULL); pr = pr->next)
        printf("      %02d\t\t  %-15s\t %-3.2lf元\n", pr->data.id, pr->data.name, pr->data.price);
}

void Show_LinkTable(NODE_F* pHead_f)
{
    NODE_F* pr = NULL;
    if (0 == SDU_Restaurant.foodsCount)
        return;
    for (pr = pHead_f; !(pr == NULL); pr = pr->next)
        printf("      %02d\t %-15s\t %-3.2lf元\t%2d\n", pr->data.id, pr->data.name, pr->data.price,pr->data.orderCount);
}

/*遍历输出服务员链表信息*/
void Print_LinkTable(NODE_W* pHead_w)
{
    NODE_W* pr = NULL;
    if (0 == SDU_Restaurant.waitersCount)
        return;
    for (pr = pHead_w; !(pr == NULL); pr = pr->next)
        printf("    %s\t\t %-15s\t %-3.2f元\n", pr->data.id, pr->data.waiterNick, pr->data.profit);
    printf("\n");
}

/*遍历输出顾客链表信息*/
void Print_LinkTable(NODE_C* pHead_c)
{
    NODE_C* pr = NULL;
    if (0 == SDU_Restaurant.customerCount)
        return;
    for (pr = pHead_c; !(pr == NULL); pr = pr->next)
        printf("    %d\t\t %.2f\t \n", pr->data.Seatnum, pr->data.order.ExpensesToBePaid);
    printf("\n");
}

/*遍历输出日期链表信息*/
void Print_LinkTable(NODE_D* pHead_d)
{
    NODE_D* pr = NULL;
    if (0 == SDU_Restaurant.dateCount)
        return;
    for (pr = pHead_d; !(pr == NULL); pr = pr->next)
        printf("    %d\t\t %d\t \n", pr->data.year, pr->data.month);
    printf("\n");
}

/*打印VIP链表*/
void Print_LinkTable(NODE_V* pHead_v)
{
    NODE_V* pr = NULL;
    if (0 == SDU_Restaurant.dateCount)
        return;
    for (pr = pHead_v; !(pr == NULL); pr = pr->next)
        printf("    %06d\t        %lld\t\t %.2f\n", pr->data.cardnum, pr->data.phonenum,pr->data.money);
    printf("\n");
}

/*————————加载操作————————*/

NODE_F* Load_Food_Inform(struct food* foods, int num)
{
    NODE_F* pHead_f = NULL;
    int i;
    for (i = 0; i < num; i++)
        pHead_f = Add_To_Tail(pHead_f, foods[i]);
    return pHead_f;
}

NODE_W* Load_Waiter_Inform(struct Waiter* waiters, int num)
{
    NODE_W* pHead_w = NULL;
    int i;
    for (i = 0; i < num; i++)
        pHead_w = Add_To_Tail(pHead_w, waiters[i]);
    return pHead_w;
}

NODE_C* Load_Customer_Inform(struct Customer* customers, int num)
{
    NODE_C* pHead_c = NULL;
    int i;
    for (i = 0; i < num; i++)
    {

        pHead_c = Add_To_Tail(pHead_c, customers[i]);
    }
    return pHead_c;
}

NODE_V* Load_VIP_Inform(struct VIP* vips, int num)
{
    NODE_V* pHead_v = NULL;
    int i;
    for (i = 0; i < num; i++)
    {

        pHead_v = Add_To_Tail(pHead_v, vips[i]);
    }
    return pHead_v;
}

NODE_D* Load_Profit_Inform(struct Date* dates, int num)
{
    NODE_D* pHead_d = NULL;
    int i;
    for (i = 0; i < num; i++)
    {
        pHead_d = Add_To_Tail(pHead_d, dates[i]);
    }
    return pHead_d;
}

/*————————增添操作————————*/

/*将新增菜品添加到菜品链表*/
void SDU_Add_Food(NODE_F* pHead_f, struct food& newFood)
{
    NODE_F* pNode = (NODE_F*)malloc(sizeof(NODE_F));
    NODE_F* pr = NULL;
    if (pNode != NULL)
    {
        pNode->data = newFood;
        pNode->next = NULL;
    }
    Assert_Program(pNode);
    if (pHead_f != NULL)
    {
        for (pr = SDU_Restaurant.current_foods; !(pr == NULL); pr = pr->next) //避免菜品重复添加
            if (pNode != NULL) {
                if (strcmp(pNode->data.name, pr->data.name) == 0)
                {
                    printf("  该 菜 品 已 添 加 过\n");
                    SDU_Restaurant_Sleep(1300);
                    return;
                }
            }
        for (pr = SDU_Restaurant.current_foods; !(pr == NULL); pr = pr->next)
            if (pr->next == NULL) //迭代到菜品链表尾部
            {
                pNode->data.id = 1 + pr->data.id;
                pr->next = pNode;
                pr = pNode;
                break;
            }
    }
    else
    {
        if (pNode != NULL) {
            pNode->data.id = 1;
            pNode->next = pHead_f;
            pHead_f = pNode;
        }
    }
    SDU_Restaurant.foodsCount++;
    SDU_Restaurant.current_foods = pHead_f;
}

/*将新增服务员添加到服务员链表*/
void SDU_Add_Waiter(NODE_W* pHead_w, struct Waiter& newWaiter)
{
    NODE_W* pNode = (NODE_W*)malloc(sizeof(NODE_W));
    NODE_W* pr = NULL;
    if (pNode != NULL)
    {
        pNode->data = newWaiter;
        pNode->next = NULL;
    }
    Assert_Program(pNode);
    if (pHead_w != NULL)
    {

        for (pr = SDU_Restaurant.current_waiters; !(pr == NULL); pr = pr->next) //避免菜品重复添加
            if (pNode != NULL) {
                if (strcmp(pNode->data.id, pr->data.id) == 0)
                {
                    printf("            该 工 号 已 添 加 过\n");
                    SDU_Restaurant_Sleep(1300);
                    return;
                }
            }

        for (pr = SDU_Restaurant.current_waiters; !(pr == NULL); pr = pr->next)
            if (pr->next == NULL) //迭代到服务员链表尾部
            {
                pNode->data.NO = 1 + pr->data.NO;
                pr->next = pNode;
                pr = pNode;
                break;
            }
    }
    else
    {
        if (pNode != NULL) {
            pNode->data.NO = 1;
            pNode->next = pHead_w;
            pHead_w = pNode;
        }
    }
    SDU_Restaurant.waitersCount++;
    SDU_Restaurant.current_waiters = pHead_w;
}

/*将新增顾客添加到顾客链表*/
void SDU_Add_Customer(NODE_C* pHead_c, struct Customer& newcustomers)
{

    NODE_C* pNode = (NODE_C*)malloc(sizeof(NODE_C));
    NODE_C* pr = NULL;
    if (pNode != NULL)
    {
        pNode->data = newcustomers;
        pNode->next = NULL;
    }
    Assert_Program(pNode);

    if (pHead_c != NULL)
    {
        for (pr = SDU_Restaurant.current_customer; !(pr == NULL); pr = pr->next)
            if (pr->next == NULL) //迭代到顾客链表尾部
            {
                pr->next = pNode;
                pr = pNode;
                break;
            }
    }
    else
    {
        if (pNode != NULL) {
            pNode->next = pHead_c;
            pHead_c = pNode;
        }
    }

    SDU_Restaurant.customerCount++;
    SDU_Restaurant.current_customer = pHead_c;
}

/*将新增日期添加到日期链表*/
void SDU_Add_Date(NODE_D* pHead_d, struct Date& newDate)
{
    SDU_Restaurant.current_date = Add_To_Head(pHead_d, newDate);
    SDU_Restaurant.dateCount++;
}
/*将新增VIP顾客添加到VIP链表*/
void SDU_Add_VIP(NODE_V* pHead_v, struct VIP& newVIP)
{
    SDU_Restaurant.current_vip = Add_To_Tail(pHead_v, newVIP);
    SDU_Restaurant.vipsCount++;
}

/*————————存储操作————————*/

/*将菜品信息存储到文件*/
void Save_Food_Inform(void)
{
    struct food* foods = NULL;
    if (SDU_Restaurant.foodsCount != 0) {
        foods = (struct food*)malloc(SDU_Restaurant.foodsCount * sizeof(struct food));
        Assert_Program(foods);
    }
    else
        foods = NULL;
    NODE_F* pr = NULL;
    int i = 0;
    for (pr = SDU_Restaurant.current_foods; !(pr == NULL); pr = pr->next)
    {
        if (foods != NULL)
            foods[i] = pr->data;
        i++;
    }
    Write_Food_Inform(foods, SDU_Restaurant.foodsCount);
}

/*将服务员信息存储到文件*/
void Save_Waiter_Inform(void)
{
    struct Waiter* waiters = NULL;
    if (SDU_Restaurant.waitersCount != 0) {
        waiters = (struct Waiter*)malloc(SDU_Restaurant.waitersCount * sizeof(struct Waiter));
        Assert_Program(waiters);
    }
    else
        waiters = NULL;
    NODE_W* pr = NULL;
    int i = 0;
    for (pr = SDU_Restaurant.current_waiters; !(pr == NULL); pr = pr->next)
    {
        if (waiters != NULL)
            waiters[i] = pr->data;
        i++;
    }
    Write_Waiter_Inform(waiters, SDU_Restaurant.waitersCount);
}

/*将顾客信息存储到文件*/
void Save_Customer_Inform(void)
{
    struct Customer* customers = NULL;
    if (SDU_Restaurant.customerCount != 0) {
        customers = (struct Customer*)malloc(SDU_Restaurant.customerCount * sizeof(struct Customer));
        Assert_Program(customers);
    }
    else
        customers = NULL;

    NODE_C* pr = NULL;
    int i = 0;
    for (pr = SDU_Restaurant.current_customer; !(pr == NULL); pr = pr->next)
    {
        if (customers != NULL)
        {
            customers[i] = pr->data;
            i++;
        }
    }
    Write_Customer_Inform(customers, SDU_Restaurant.customerCount);
}

/*将日期信息存储到文件*/
void Save_Date_Inform(void)
{
    struct Date* dates = NULL;
    if (SDU_Restaurant.dateCount != 0) {
        dates = (struct Date*)malloc(SDU_Restaurant.dateCount * sizeof(struct Date));
        Assert_Program(dates);
    }
    else
        dates = NULL;
    NODE_D* pr = NULL;
    int i = 0;
    if(SDU_Restaurant.current_date!=NULL)
    for (pr = SDU_Restaurant.current_date; !(pr == NULL); pr = pr->next)
    {
        if (dates != NULL) {
            dates[i] = pr->data;
            i++;
        }
    }
    Write_Date_Inform(dates, SDU_Restaurant.dateCount);
}
/*将VIP信息存储到文件*/
void Save_VIP_Inform(void)
{
    struct VIP* vips = NULL;
    if (SDU_Restaurant.vipsCount != 0) {
        vips = (struct VIP*)malloc(SDU_Restaurant.vipsCount * sizeof(struct VIP));
        Assert_Program(vips);
    }
    else
        vips = NULL;
    NODE_V* pr = NULL;
    int i = 0;
    if (SDU_Restaurant.current_vip != NULL)
        for (pr = SDU_Restaurant.current_vip; !(pr == NULL); pr = pr->next)
        {
            if (vips != NULL) {
                vips[i] = pr->data;
                i++;
            }
        }
    Write_VIP_Inform(vips, SDU_Restaurant.vipsCount);
}

/*————————删除操作————————*/

/*根据序号值, 删除相应的菜品数据*/
NODE_F* SDU_Delete_Food(NODE_F* pHead_f, int id)
{
    if (pHead_f == NULL) //判断是否为空表
        return NULL;
    /*对于在表头的数据特殊处理*/
    if (id == pHead_f->data.id)
    {
        NODE_F* pDelete = pHead_f;
        pHead_f = pHead_f->next;
        SDU_Restaurant.foodsCount--;
        free(pDelete);
    }
    /*不是在表头的数据*/
    else
    {
        NODE_F* pLast = pHead_f;
        NODE_F* pNext = pHead_f->next;
        NODE_F* pDelete = NULL;
        if (pNext == NULL) //如果没找到
        {
            printf("未找到对应序号值!\n");
            SDU_Restaurant_Sleep(1000);
            return pHead_f;
        }
        while (1)
        {
            /* 这里一定要先判断找到数据，再将pLast、pNext往下移动，顺序不能反，否则链表第二个数据就会被忽略过去*/
            if (id == pNext->data.id) //如果找到
            {
                pDelete = pNext;
                pLast->next = pNext->next;

                SDU_Restaurant.foodsCount--;
                free(pDelete); //防止内存泄漏
                break;
            }
            if (pNext->next == NULL) //如果没找到
            {
                printf("未找到对应序号值!\n");
                SDU_Restaurant_Sleep(1000);
                break;
            }
            else
            {
                pLast = pLast->next;
                pNext = pNext->next;
            }
        }
    }
    return pHead_f;
}

/*根据序号值, 删除相应的服务员数据*/
NODE_W* SDU_Delete_Waiter(NODE_W* pHead_w, char* id)
{
    if (pHead_w == NULL) //判断是否为空表
        return NULL;

    /*对于在表头的数据特殊处理*/
    if (0 == strcmp(pHead_w->data.id, id))
    {
        NODE_W* pDelete = pHead_w;
        pHead_w = pHead_w->next;
        SDU_Restaurant.waitersCount--;
        free(pDelete);
    }

    /*不是在表头的数据*/
    else
    {
        NODE_W* pLast = pHead_w;
        NODE_W* pNext = pHead_w->next;
        NODE_W* pDelete = NULL;
        if (pNext == NULL) //如果没找到
        {
            printf("未找到对应序号值!\n");
            SDU_Restaurant_Sleep(1000);
            return pHead_w;
        }
        while (1)
        {
            /* 这里一定要先判断找到数据，再将pLast、pNext往下移动，顺序不能反，否则链表第二个数据就会被忽略过去*/

            if (0 == strcmp(pNext->data.id, id)) //如果找到
            {
                pDelete = pNext;
                pLast->next = pNext->next;

                SDU_Restaurant.waitersCount--;
                free(pDelete); //防止内存泄漏
                break;
            }
            if (pNext->next == NULL) //如果没找到
            {
                printf("未找到对应序号值!\n");
                SDU_Restaurant_Sleep(1000);
                break;
            }
            else
            {
                pLast = pLast->next;
                pNext = pNext->next;
            }
        }
    }
    return pHead_w;
}

/*根据桌号, 删除相应的顾客数据*/
NODE_C* SDU_Delete_Customer(NODE_C* pHead_c, int seatnum)
{
    if (pHead_c == NULL) //判断是否为空表
        return NULL;

    /*对于在表头的数据特殊处理*/
    if (pHead_c->data.Seatnum == seatnum)
    {
        NODE_C* pDelete = pHead_c;
        pHead_c = pHead_c->next;
        SDU_Restaurant.customerCount--;
        free(pDelete);
    }

    /*不是在表头的数据*/
    else
    {
        NODE_C* pLast = pHead_c;
        NODE_C* pNext = pHead_c->next;
        NODE_C* pDelete = NULL;
        if (pNext == NULL) //如果没找到
        {
            printf("未找到对应序号值!\n");
            SDU_Restaurant_Sleep(1000);
            return pHead_c;
        }
        while (1)
        {
            /* 这里一定要先判断找到数据，再将pLast、pNext往下移动，顺序不能反，否则链表第二个数据就会被忽略过去*/

            if (pNext->data.Seatnum == seatnum) //如果找到
            {
                pDelete = pNext;
                pLast->next = pNext->next;

                SDU_Restaurant.customerCount--;
                free(pDelete); //防止内存泄漏
                break;
            }
            if (pNext->next == NULL) //如果没找到
            {
                printf("未找到对应序号值!\n");
                SDU_Restaurant_Sleep(1000);
                break;
            }
            else
            {
                pLast = pLast->next;
                pNext = pNext->next;
            }
        }
    }
    return pHead_c;
}

/*在订单中，根据序号值, 删除相应的已订菜品数据*/
int Delet_Food_From_Order(int foodID, struct Order* order)
{
    NODE_F* pHead_f = SDU_Restaurant.current_foods;
    NODE_F* pr;

    pr = pHead_f;
    int i;
    for (i = 0; i < SDU_Restaurant.foodsCount; i++)
    {
        if (foodID == pr->data.id) //找到对应菜品
        {
             pr->data.orderCount--; //记录菜品历史销量
             Save_Food_Inform();
            if (order->foodCount == 0)
            {
                printf("未进行点菜，无法删除！");
                SDU_Restaurant_Sleep(1000);
                return 1;
            }
            for (int i = order->foodCount - 1; i >= 0; i--)
            {
                if (order->foods[i].id == foodID)
                {
                    order->ExpensesToBePaid -= order->foods[i].price;

                    for (int j = i; j < order->foodCount - 1; j++)
                        order->foods[j] = order->foods[j + 1];
                    order->foodCount--;
                    break;
                }
            }
            int newSize = (order->foodCount - 1) * sizeof(struct food); //扩大订单空间，以能够继续容纳菜品信息
            // order->foods = (struct food*)realloc(order->foods, newSize);//避免返回NULL，可能导致内存泄漏 //用固定数组取代了
            Assert_Program(order->foods);

            return 1;
        }
        pr = pr->next;
    }
    return 0;
}
/*根据卡号, 删除相应的VIP数据*/
NODE_V* SDU_Delete_VIP(NODE_V* pHead_v, int cardnum)
{
    if (pHead_v == NULL) //判断是否为空表
        return NULL;

    /*对于在表头的数据特殊处理*/
    if (pHead_v->data.cardnum == cardnum)
    {
        NODE_V* pDelete = pHead_v;
        pHead_v = pHead_v->next;
        SDU_Restaurant.vipsCount--;
        free(pDelete);
    }

    /*不是在表头的数据*/
    else
    {
        NODE_V* pLast = pHead_v;
        NODE_V* pNext = pHead_v->next;
        NODE_V* pDelete = NULL;
        if (pNext == NULL) //如果没找到
        {
            printf("未找到对应序号值!\n");
            SDU_Restaurant_Sleep(1000);
            return pHead_v;
        }
        while (1)
        {
            /* 这里一定要先判断找到数据，再将pLast、pNext往下移动，顺序不能反，否则链表第二个数据就会被忽略过去*/

            if (pNext->data.cardnum == cardnum) //如果找到
            {
                pDelete = pNext;
                pLast->next = pNext->next;

                SDU_Restaurant.vipsCount--;
                free(pDelete); //防止内存泄漏
                break;
            }
            if (pNext->next == NULL) //如果没找到
            {
                printf("未找到对应序号值!\n");
                SDU_Restaurant_Sleep(1000);
                break;
            }
            else
            {
                pLast = pLast->next;
                pNext = pNext->next;
            }
        }
    }
    return pHead_v;
}

/*————————排序更新操作————————*/

/*使菜品链表的序号刷新为有序化，根据新增时间顺序排序*/
void Order_By_ID(NODE_F* pHead_f)
{
    NODE_F* pr = pHead_f;
    int idx = 1;
    while (pr != NULL)
    {
        pr->data.id = idx++;
        pr = pr->next;
    }
}

/*使服务员链表的序号刷新为有序化，根据新增时间顺序排序*/
void Order_By_ID(NODE_W* pHead_w)
{
    NODE_W* pr = pHead_w;
    int idx = 1;
    while (pr != NULL)
    {
        pr->data.NO = idx++;
        pr = pr->next;
    }
}

/*归并排序*/
NODE_V* Order_Merge_Sort_By_Cardnum(NODE_V* head1, NODE_V* head2)
{
    if (head1 == NULL)
        return head2;
    if (head2 == NULL)
        return head1;

    NODE_V* res, * p;
    if (head1->data.cardnum < head2->data.cardnum)
    {
        res = head1;
        head1 = head1->next;
    }
    else
    {
        res = head2;
        head2 = head2->next;
    }
    p = res;
    while (head1 != NULL && head2 != NULL)
    {
        if (head1->data.cardnum < head2->data.cardnum)
        {
            p->next = head1;
            head1 = head1->next;
        }
        else
        {
            p->next = head2;
            head2 = head2->next;
        }
        p = p->next;
    }
    if (head1 != NULL)
        p->next = head1;
    else if (head2 != NULL)
        p->next = head2;
    return res;
}

/*将顾客根据桌号排序*/
NODE_V* Order_By_Cardnum(NODE_V* pHead_v)
{

    if (pHead_v == NULL || pHead_v->next == NULL)
        return pHead_v;
    else
    {
        NODE_V* fast = pHead_v, * slow = pHead_v;
        while (fast->next != NULL && fast->next->next != NULL)
        {
            fast = fast->next->next;
            slow = slow->next;
        }
        fast = slow;
        slow = slow->next;
        fast->next = NULL;
        fast = Order_By_Cardnum(pHead_v);
        slow = Order_By_Cardnum(slow);
        return Order_Merge_Sort_By_Cardnum(fast, slow);
    }
}

/*归并排序*/
NODE_C* Order_Merge_Sort_By_Seatnum(NODE_C* head1, NODE_C* head2)
{
    if (head1 == NULL)
        return head2;
    if (head2 == NULL)
        return head1;

    NODE_C* res, * p;
    if (head1->data.Seatnum < head2->data.Seatnum)
    {
        res = head1;
        head1 = head1->next;
    }
    else
    {
        res = head2;
        head2 = head2->next;
    }
    p = res;
    while (head1 != NULL && head2 != NULL)
    {
        if (head1->data.Seatnum < head2->data.Seatnum)
        {
            p->next = head1;
            head1 = head1->next;
        }
        else
        {
            p->next = head2;
            head2 = head2->next;
        }
        p = p->next;
    }
    if (head1 != NULL)
        p->next = head1;
    else if (head2 != NULL)
        p->next = head2;
    return res;
}

/*将顾客根据桌号排序*/
NODE_C* Order_By_Seatnum(NODE_C* pHead_c)
{

    if (pHead_c == NULL || pHead_c->next == NULL)
        return pHead_c;
    else
    {
        NODE_C* fast = pHead_c, * slow = pHead_c;
        while (fast->next != NULL && fast->next->next != NULL)
        {
            fast = fast->next->next;
            slow = slow->next;
        }
        fast = slow;
        slow = slow->next;
        fast->next = NULL;
        fast = Order_By_Seatnum(pHead_c);
        slow = Order_By_Seatnum(slow);
        return Order_Merge_Sort_By_Seatnum(fast, slow);
    }
}

/*————————添加操作————————*/

/*将菜品信息添加到订单*/
int Add_Food_To_Order(int foodID, struct Order* order)
{
    NODE_F* pHead_f = SDU_Restaurant.current_foods;
    NODE_F* pr;

    pr = pHead_f;
    int i;
    for (i = 0; i < SDU_Restaurant.foodsCount; i++)
    {
        if (foodID == pr->data.id) //找到对应菜品
        {
            pr->data.orderCount++; //记录菜品历史销量
            Save_Food_Inform();

            int newSize = (order->foodCount + 1) * sizeof(struct food); //扩大订单空间，以能够继续容纳菜品信息

            // order->foods = (struct food*)realloc(order->foods, newSize);//避免返回NULL，可能导致内存泄漏 //用固定数组取代了
            Assert_Program(order->foods);

            /*更新订单*/
            order->foods[(order->foodCount + 1) - 1] = pr->data;
            order->foodCount++;
            order->ExpensesToBePaid += pr->data.price;
            return 1;
        }
        pr = pr->next;
    }
    return 0;
}

/*将顾客数据添加到顾客链表尾部*/
NODE_C* Add_To_Tail(NODE_C* pHead_c, struct Customer Data)
{
    /*创建新的链表节点*/
    NODE_C* pNode = (NODE_C*)malloc(sizeof(NODE_C));
    Assert_Program(pNode);
    if (pNode != NULL) {
        pNode->data = Data;
        pNode->next = NULL;
    }
    /*若原链表为空*/
    if (pHead_c == NULL)
    {
        if (pNode != NULL) {
            pNode->next = pHead_c;
            pHead_c = pNode;
        }
    }

    /*若原链表非空*/
    else
    {
        NODE_C* pr = NULL;
        pr = pHead_c;
        while (!(pr->next == NULL)) //迭代到链表尾部
        {
            pr = pr->next;
        }
        pr->next = pNode; //添加新结点到链表尾部
    }
    return pHead_c;
}


/*将VIP数据添加到顾客链表尾部*/
NODE_V* Add_To_Tail(NODE_V* pHead_v, struct VIP Data)
{
    /*创建新的链表节点*/
    NODE_V* pNode = (NODE_V*)malloc(sizeof(NODE_V));
    Assert_Program(pNode);
        pNode->data = Data;
        pNode->next = NULL;
    /*若原链表为空*/
    if (pHead_v == NULL)
    {
        if (pNode != NULL) {
            pNode->next = pHead_v;
            pHead_v = pNode;
        }
    }

    /*若原链表非空*/
    else
    {
        NODE_V* pr = NULL;
        pr = pHead_v;
        while (!(pr->next == NULL)) //迭代到链表尾部
        {
            pr = pr->next;
        }
        pr->next = pNode; //添加新结点到链表尾部
    }
    return pHead_v;
}

/*将日期数据添加到日期链表尾部*/
NODE_D* Add_To_Tail(NODE_D* pHead_d, struct Date Data)
{
    /*创建新的链表节点*/
    NODE_D* pNode = (NODE_D*)malloc(sizeof(NODE_D));
    Assert_Program(pNode);
    if (pNode != NULL) {
        pNode->data = Data;
        pNode->next = NULL;
    }
    /*若原链表为空*/
    if (pHead_d == NULL)
    {
        if (pNode != NULL) {
            pNode->next = pHead_d;
            pHead_d = pNode;
        }
    }

    /*若原链表非空*/
    else
    {
        NODE_D* pr = NULL;
        pr = pHead_d;
        while (!(pr->next == NULL)) //迭代到链表尾部
        {
            pr = pr->next;
        }
        pr->next = pNode; //添加新结点到链表尾部
    }
    return pHead_d;
}

/*————————餐桌操作————————*/

/*清除所有座位信息*/
void Clear_Seat_Inform(void)
{
    for (int i = 0; i < SEATINFO_HEIGHT; i++)
    {
        for (int j = 0; j < SEATINFO_WIDTH; j++)
        {
            if (SDU_Restaurant.seatsMap[i][j].isSelected)
            {
                SDU_Restaurant.seatsMap[i][j].isSelected = 0;
            }
        }
    }
}

/*用完餐后离开座位*/
void Leave_Seat(int num)
{
    int row, col;
    col = (num - 1) % SEATINFO_WIDTH;
    row = (num - col) / SEATINFO_WIDTH;
    SDU_Restaurant.seatsMap[row][col].isSelected = 0;
}