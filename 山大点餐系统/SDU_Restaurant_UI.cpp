#pragma warning(disable : 6386) //警告C6386：可能缓冲区溢出；已进行数据范围判断，不会产生溢出
#include "SDU_Restaurant_Core.h"
#include "SDU_Restaurant_UI.h"
#include "SDU_Restaurant_IO.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <graphics.h>
#include <io.h>
extern struct SDU_Restaurant_Data SDU_Restaurant;

/*清空屏幕缓冲区*/
void clearScreenBuffer(void)
{
    char c;
    while ((c = getchar()) != EOF && c != '\n')
        ;
}

/*登录菜单界面*/
void Loading_Menu(char* ID_input, char* password_input)
{
    printf("\t   请 输 入 工 号 \n\n");
    printf("\t   ( 单 击 回 车 结 束 输 入)\n\n");
    printf("\t   > ");
    fscanf_s(stdin, "%s", ID_input, USRID_LENGTH_MAX);
    printf("\n\n");
    printf("\t   请 输 入 密 码 \n\n");
    printf("\t   ( 单 击 回 车 结 束 输 入)\n\n");
    printf("\t   > ");

    /*隐式密码输入*/
    char ch;
    int idx = 0;
    while (1)
    {
        ch = _getch();
        if (ch == '\r')
            break;
        else if (ch == '\b' && idx > 0)
        {
            printf("\b \b");
            idx--;
        }
        else if (ch == '\b' && idx == 0)
            continue;
        else
        {
            password_input[idx++] = ch;
            printf("*");
        }
    }
    password_input[idx] = '\0';

    /*显式密码输入*/
    // fscanf(stdin, "%s", password_input);

    clearScreenBuffer();
}

/*检测密码是否匹配*/
int Check_ID_Passwd(char* ID_input, char* password_input, enum class UserType* userType, int Choice)
{
    int st = 0;
    int flag = 0;
    if (Choice == 1)
    {
        st = Check_Admin(ID_input, password_input);
    }
    if (Choice == 2)
    {
        st = Check_Waiter(ID_input, password_input);
    }
    if (!st)
    {
        /*密码或工号不匹配*/
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); //淡红色
        printf("\n\n\n\t   密 码 或 工 号 错 误 !\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); //恢复白色
        SDU_Restaurant_Sleep(1200);
        *userType = UserType::undefine;
        SDU_Restaurant.user = UserType::undefine;
    }
    else
    {
        /*密码与工号均匹配*/
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); //淡绿色
        printf("\n\n\n\t   登 录 成 功 !\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); //恢复白色
        SDU_Restaurant_Sleep(1200);
        flag = 1;
    }
    system("cls");
    return flag;
}

/*用户类型选择页面*/
enum UserType SDU_Restaurant_Welcome(void)
{
    enum UserType userType = UserType::undefine;
    int Choice = 0;
    char ID_input[USRID_LENGTH_MAX + 1];
    char password_input[USRPAS_LENGTH_MAX + 1];
    system("cls");
    while (!(userType == UserType::admin || userType == UserType::waiter))
    {
        printf("\n\n\n");
        printf(" ############## 欢 迎 使 用 山 大 餐 饮 系 统 #############\n\n\n");
        printf("\t\t   请 选 择 您 的 身 份:\n\n\n");
        printf("\t\t    1) 我 是 管 理 员.\n\n");
        printf("\t\t    2) 我 是 服 务 员.\n\n\n");
        printf("\t请 输 入 您 的 身 份 所 对 应 的 序 号: [ ]\b\b");
        scanf_s("%d", &Choice);
        clearScreenBuffer();
        system("cls");
        if (Choice == 2)
        {
            printf("\n\n\n");
            printf(" -------- 欢 迎 使 用 山 大 餐 饮 服 务 员 系 统 ---------\n\n\n\n");
            Loading_Menu(ID_input, password_input);
            if (Check_ID_Passwd(ID_input, password_input, &userType, Choice))
            {
                userType = UserType::waiter;
                SDU_Restaurant.user = UserType::waiter;
            }
        }
        else if (Choice == 1)
        {
            printf("\n\n\n");
            printf(" -------- 欢 迎 使 用 山 大 餐 饮 管 理 员 系 统 ---------\n\n\n\n");
            Loading_Menu(ID_input, password_input);
            if (Check_ID_Passwd(ID_input, password_input, &userType, Choice))
            {
                userType = UserType::admin;
                SDU_Restaurant.user = UserType::admin;
            }
        }
    }
    return userType;
}

/*管理员菜单页面*/
int Admin_Menu(void)
{
    system("cls");
    printf("\n\n\n");
    printf(" -------- 欢 迎 使 用 山 大 餐 饮 管 理 员 系 统 ---------\n\n\n");
    printf("\t\t    [1] 座 位 信 息\n\n");
    printf("\t\t    [2] 营 业 总 额\n\n");
    printf("\t\t    [3] 更 改 菜 品\n\n");
    printf("\t\t    [4] 更 改 员 工\n\n");
    printf("\t\t    [5] 更 改 V I P\n\n");
    printf("\t\t    [6] 更 改 密 码\n\n");
    printf("\t\t    [7] 菜 品 分 析\n\n");
    printf("\t\t    [8] 账 号 登 出\n\n");
    printf("\t\t    [0] 退 出 程 序\n\n");
    printf("\t Admin, 你 好!\n\n");
    printf("\t 请 输 入 请 输 入 相 应 的 指 令 序 号: [ ]\b\b");
    int Choice;
    scanf_s("%d", &Choice);
    clearScreenBuffer();
    return Choice;
}

/*服务员菜单页面*/
int Waiter_Menu(void)
{

    system("cls");
    printf("\n\n\n");
    printf(" -------- 欢 迎 使 用 山 大 餐 饮 服 务 员 系 统 ---------\n\n\n");
    printf("\t\t    [1] 座 位 预 定\n\n");
    printf("\t\t    [2] 展 示 菜 品\n\n");
    printf("\t\t    [3] 点 餐 服 务\n\n");
    printf("\t\t    [4] 结 算 账 单\n\n");
    printf("\t\t    [5] 取 消 预 定\n\n");
    printf("\t\t    [6] 修 改 密 码\n\n");
    printf("\t\t    [7] 账 号 登 出\n\n");
    printf("\t\t    [0] 退 出 程 序\n\n\n");
    printf("\t %s, 你 好!\n\n", SDU_Restaurant.waiter_Login->waiterNick);
    printf("\t 请 输 入 相 应 的 指 令 序 号: [ ]\b\b");
    int Choice;
    scanf_s("%d", &Choice);
    clearScreenBuffer();
    return Choice;
}

/*展示菜单界面*/
void Waiter_Food_Show(void)
{
    while (1)
    {
        system("cls");
        printf("\n\n\n");
        printf(" -------- 欢 迎 使 用 山 大 餐 饮 服 务 员 系 统 ---------\n\n\n");
        printf("    序 号\t\t菜   名\t\t\t 单 价\n");
        printf(" ==========================================================\n\n");
        Print_LinkTable(SDU_Restaurant.current_foods);
        printf("\n ==========================================================\n\n");
        printf("  输 入 序 号 查 看 相 应 菜 品 图 片：\n\n");
        printf("  输 入 0 返 回 上 一 级 菜 单...\n\n");
        IMAGE picture;
        NODE_F* pr = NULL;
        int Choi = 0;
        printf("  请 输 入 菜 品 序 号: [ ]\b\b");
        scanf_s("%d", &Choi);
        clearScreenBuffer();
        if (!Choi)
            break;
        for (pr = SDU_Restaurant.current_foods; !(pr == NULL); pr = pr->next)
        {
            if (Choi == pr->data.id)
            {
                if (0 == strcmp(EMPTY_ADDRESS, pr->data.address)) // EMPTY_ADRESS标识无图片菜品
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); //恢复白色
                    printf("\n  该 菜 品 暂 无 图 片！");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); //恢复白色
                    SDU_Restaurant_Sleep(1200);
                }
                else
                {
                    loadimage(&picture, pr->data.address, 640, 480);
                    initgraph(640, 480);
                    putimage(0, 0, &picture);
                    char GET_CHAR = getchar();
                    closegraph();
                }
                break;
            }
        }
        if (pr == NULL)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); //淡红色
            printf("\n  错 误 的 菜 品 序 号！");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); //恢复白色
            SDU_Restaurant_Sleep(1200);
        }
    }
    system("cls");
}

/*显示结账界面*/
double Check_VIP(void)
{
    while (1)
    {
        system("cls");
        printf("\n\n\n");
        printf(" -------- 欢 迎 使 用 山 大 餐 饮 服 务 员 系 统 ---------\n\n\n");
        double discount = 1;
        printf("\n\t   该 账 单 尚 未 打 折 哦 ~\n\n\t   请 问 您 是 否 是 VIP ?  ( y / n )\n\n");
        printf("\t   > ");
        char GETCHAR = getchar();
        clearScreenBuffer();
        if (GETCHAR == 'y' || GETCHAR == 'Y')
        {
            long long int phonenumber;
            printf("\n\n\t   请 输 入 手 机 号\n\n");
            printf("\t   > ");
            scanf_s("%lld", &phonenumber);
            clearScreenBuffer();
            // discount = Judge_VIP(phonenumber) ? 0.9 : 1;
            if (Judge_VIP(phonenumber))
            {
                discount = 0.9;
                return discount;
            }
            else
            {
                printf("\n\n\t   该 号 码 不 是 VIP，请 重 新 输 入\n\n");
                SDU_Restaurant_Sleep(1000);
            }
        }
        else if (GETCHAR == 'n' || GETCHAR == 'N')
        {
            return discount;
        }
        else
        {
            printf("\n\n\t   请 输 入 正 确 选 项\n\n");
            SDU_Restaurant_Sleep(1000);
        }
    }
}
void Waiter_Food_Check(void)
{
    while (1)
    {
        system("cls");
        printf("\n\n\n");
        printf(" -------- 欢 迎 使 用 山 大 餐 饮 服 务 员 系 统 ---------\n\n\n");
        printf("\t   请 输 入 顾 客 桌 号 \n\n");
        printf("\t   ( 输 入 0 返 回 上  一  级 菜 单)\n\n");
        printf("\t   > ");
        int seat;
        int col, row;
        scanf_s("%d", &seat);
        if (seat == 0)
            break;
        col = (seat - 1) % SEATINFO_WIDTH;
        row = (seat - col) / SEATINFO_WIDTH;
        clearScreenBuffer();
        if (0 == SDU_Restaurant.seatsMap[row][col].isSeated)
        {
            printf("  该 桌 尚 未 点 餐");
            SDU_Restaurant_Sleep(1000);
            return;
        }
       NODE_C* pr = SDU_Restaurant.current_customer;
        for (; pr != NULL; pr = pr->next)
        {
            if (seat == pr->data.Seatnum)
                break;
        } 
        if (pr == NULL)
        {
            printf("\t该 座 位 暂 无 顾 客！\n\n");
            SDU_Restaurant_Sleep(1200);
            system("cls");
        }
        else
        {
            if (pr->data.order.isDiscount == 0) {
                double discount = Check_VIP();
                pr->data.order.ExpensesToBePaid = discount * pr->data.order.ExpensesToBePaid;
                pr->data.order.isDiscount = 1;
            }

            while (1)
            {
                system("cls");
                printf("\n\n\n");
                printf(" -------- 欢 迎 使 用 山 大 餐 饮 服 务 员 系 统 ---------\n\n\n");
                printf("\t顾 客 身 份：");
                if (pr->data.order.isDiscount == 0) {
                    printf("\t非 V I P 用 户\n\n");
                }
                else if (pr->data.order.isDiscount == 1) {
                    printf("\tV I P 用 户\n\n");
                }
                printf("\n\n\t需 收 款 金 额 为：");
                printf("\t%.2f元\n", pr->data.order.ExpensesToBePaid);

                printf(" ==========================================================\n\n");
                printf("\t请 输 入 收 款 金 额 ( 单 位 ：元 )(输 入 0 退 出)\n\n\t>  ");
                double temp = pr->data.order.ExpensesToBePaid;
                double paid = 0;
                scanf_s("%lf", &paid);
                clearScreenBuffer();
                pr->data.order.ExpensesToBePaid -= paid; //扣钱

                if (paid - 0 < 0.00001)
                    break;
                if (pr->data.order.ExpensesToBePaid - 0 > 0.000001)
                {
                    printf("\n\t收 款 成 功！顾 客 还 需 支 付 %.2f 元。\n\n", pr->data.order.ExpensesToBePaid);
                    SDU_Restaurant_Sleep(1000);
                    SDU_Restaurant.Day_Profit += paid;
                    SDU_Restaurant.current_date->data.profit = SDU_Restaurant.Day_Profit;
                    Save_Date_Inform();
                }

                else if (pr->data.order.ExpensesToBePaid - 0 <= 0.000001)
                {
                    if (pr->data.order.ExpensesToBePaid - 0 < 0.000001)
                        printf("\n\t收 款 成 功！需 找 零 %.2f 元。\n\n", -pr->data.order.ExpensesToBePaid);
                    else if (pr->data.order.ExpensesToBePaid - 0 == 0.000001)
                        printf("\n\t收 款 成 功！\n\n");
                    SDU_Restaurant_Sleep(1000);
                    pr->data.order.isDiscount = 0;
                    pr->data.order.ExpensesToBePaid = 0;
                    SDU_Restaurant.seatsMap[row][col].isSeated = 0;
                    SDU_Restaurant.Day_Profit += temp;
                    SDU_Restaurant.current_date->data.profit = SDU_Restaurant.Day_Profit;
                    Save_Date_Inform();
                    SDU_Restaurant.waiter_Login->profit += temp;
                    Save_Waiter_Inform();
                    Leave_Seat(seat);
                    SDU_Restaurant.current_customer = SDU_Delete_Customer(SDU_Restaurant.current_customer, seat);
                    Save_Customer_Inform();
                    Write_SeatMap_Inform((struct Seat*)&SDU_Restaurant.seatsMap);
                    printf(" ==========================================================\n\n");
                    printf(" 按 Enter 键 返 回 上 一 级 菜 单...");
                    char GET_CHAR = getchar();
                    break;
                }
            }
        }
    }
}

/*管理员更改餐品信息*/
void Admin_Food_Change(void)
{
    while (1)
    {
        system("cls");
        printf("\n\n\n");
        printf(" -------- 欢 迎 使 用 山 大 餐 饮 管 理 员 系 统 ---------\n\n\n");
        printf("    序 号\t\t菜   名\t\t\t 单 价\n");
        printf(" ==========================================================\n\n");
        Print_LinkTable(SDU_Restaurant.current_foods);
        printf("\n ==========================================================\n\n");
        printf("  \"add [菜 品 名] [单 价] [图 片 地 址]\" 添 加 菜 品\n\n");
        printf("  单 价 取 整，若 暂 无 图 片 则 请 输 入 \"EMPTY_ADRESS\"\n\n");
        printf("  \"del [序 号]\" 删 除 菜 品\n\n");
        printf("  \"quit\" 返 回 上 一 级 菜 单\n\n");
        printf("   $ admin > ");
        char cmd[30] = { 0 };
        scanf_s("%s", cmd, sizeof(cmd));
        if (strcmp(cmd, "add") == 0)
        {
            //新增菜品信息
            struct food newFood;
            scanf_s(" %s", newFood.name, sizeof(newFood.name));
            scanf_s(" %lf", &newFood.price);
            scanf_s(" %s", newFood.address, sizeof(newFood.address));
            newFood.orderCount = 0;

            struct _finddata_t File;
            long handle = _findfirst(newFood.address, &File);
            if (handle == -1)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);        //淡红色
                printf("\n  图 片 地 址 无 效，已 自 动 设 为 EMPTY_ADDRESS !\n\n"); //无法判断文件地址的大小写,但CMD本就大小写不敏感
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);         //恢复白色
                strcpy_s(newFood.address, EMPTY_ADDRESS);
                SDU_Restaurant_Sleep(1200);
            }
            //更新菜品链表
            SDU_Add_Food(SDU_Restaurant.current_foods, newFood);

            //存储到文件
            Save_Food_Inform();
            clearScreenBuffer(); //若add 后仍有内容则略去
        }
        else if (strcmp(cmd, "del") == 0)
        {
            if (!(0 == SDU_Restaurant.foodsCount)) //判断菜品库是否为空
            {
                int id;
                scanf_s(" %d", &id);
                SDU_Restaurant.current_foods = SDU_Delete_Food(SDU_Restaurant.current_foods, id);
                Save_Food_Inform();
            }
            else
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); //淡红色
                printf("\n  菜 品 库 为 空，无 法 继 续 删 除！");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); //恢复白色
                SDU_Restaurant_Sleep(1000);
            }
            Order_By_ID(SDU_Restaurant.current_foods);
            clearScreenBuffer(); //若del 后仍有内容则略去
        }
        else if (strcmp(cmd, "quit") == 0)
            break;
        else
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); //淡红色
            printf("\n  所 输 入 的 命 令 格 式 有 误！");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); //白色
            SDU_Restaurant_Sleep(500);
        }
    }
    clearScreenBuffer();
    system("cls");
}

/*管理员更改服务员信息*/
void Admin_Waiter_Change(void)
{
    while (1)
    {
        system("cls");
        printf("\n\n\n");
        printf(" -------- 欢 迎 使 用 山 大 餐 饮 管 理 员 系 统 ---------\n\n\n");
        printf("     工 号\t\t 姓  名\t\t\t 盈 利\n");
        printf(" ==========================================================\n\n");
        Print_LinkTable(SDU_Restaurant.current_waiters);
        printf(" ==========================================================\n\n");
        printf("  输 入 \"add [工 号] [姓 名] [图 片 地 址]\" 添 加 员 工）\n\n");
        printf("  初 始 化 密 码  为 123456，初 始 化 盈 利 为 0  \n\n  若 暂 无 图 片 则 请 输 入 \"EMPTY_ADRESS\"\n\n");
        printf("  输 入 \"del [工 号]\" 删 除 员 工\n\n");
        printf("  输 入 \"chek [工 号]\" 查 看 图 片\n\n");
        printf("  输 入 \"quit\" 返 回 上 一 级 菜 单\n\n");
        printf("   $ admin > ");
        char cmd[30] = { 0 };
        scanf_s("%s", cmd, sizeof(cmd));
        if (strcmp(cmd, "add") == 0)
        {
            //新增服务员信息
            struct Waiter newWaiter;
            scanf_s(" %s", newWaiter.id, sizeof(newWaiter.id));
            scanf_s(" %s", newWaiter.waiterNick, sizeof(newWaiter.waiterNick));
            scanf_s(" %s", newWaiter.waiter_address, sizeof(newWaiter.waiter_address));
            strcpy_s(newWaiter.passwd, "123456"); //密码初始化
            newWaiter.profit = 0;
            struct _finddata_t File;
            long handle = _findfirst(newWaiter.waiter_address, &File);
            if (handle == -1)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);        //淡红色
                printf("\n  图 片 地 址 无 效，已 自 动 设 为 EMPTY_ADDRESS !\n\n"); //无法判断文件地址的大小写,但CMD本就大小写不敏感
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);         //恢复白色
                strcpy_s(newWaiter.waiter_address, EMPTY_ADDRESS);
                SDU_Restaurant_Sleep(1200);
            }
            //更新菜品链表
            SDU_Add_Waiter(SDU_Restaurant.current_waiters, newWaiter);

            //存储到文件
            Save_Waiter_Inform();
            clearScreenBuffer(); //若add 后仍有内容则略去
        }
        else if (strcmp(cmd, "del") == 0)
        {
            if (!(0 == SDU_Restaurant.waitersCount)) //判断服务员库是否为空
            {
                char id[WAITERID_LENGTH_MAX];
                scanf_s(" %s", id, sizeof(id));
                SDU_Restaurant.current_waiters = SDU_Delete_Waiter(SDU_Restaurant.current_waiters, id);
                Save_Waiter_Inform();
            }
            else
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); //淡红色
                printf("\n  服 务 员 列 表 为 空，无 法 继 续 删 除！");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); //恢复白色
                SDU_Restaurant_Sleep(1000);
            }
            Order_By_ID(SDU_Restaurant.current_waiters);
            clearScreenBuffer(); //若del 后仍有内容则略去
        }
        else if (strcmp(cmd, "chek") == 0)
        {
            IMAGE picture;
            NODE_W* pr = NULL;
            char id[WAITERID_LENGTH_MAX];
            scanf_s(" %s", id, sizeof(id));
            clearScreenBuffer();
            for (pr = SDU_Restaurant.current_waiters; !(pr == NULL); pr = pr->next)
            {
                if (0 == strcmp(id, pr->data.id))
                {
                    if (0 == strcmp(EMPTY_ADDRESS, pr->data.waiter_address)) // EMPTY_ADRESS标识无图片菜品
                    {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); //恢复白色
                        printf("\n  该 员 工 暂 无 图 片！");
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); //恢复白色
                        SDU_Restaurant_Sleep(1200);
                    }
                    else
                    {
                        loadimage(&picture, pr->data.waiter_address, 640, 480);
                        initgraph(640, 480);
                        putimage(0, 0, &picture);
                        char GET_CHAR = getchar();
                        closegraph();
                    }
                    break;
                }
            }
            if (pr == NULL)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); //淡红色
                printf("\n  错 误 的 员 工 序 号！");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); //恢复白色
                SDU_Restaurant_Sleep(1200);
            }
        }
        else if (strcmp(cmd, "quit") == 0)
            break;
        else
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); //淡红色
            printf("\n  所 输 入 的 命 令 格 式 有 误！");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); //白色
            SDU_Restaurant_Sleep(500);
        }
    }
    clearScreenBuffer();
    system("cls");
}
/*管理员更改VIP信息*/
void Admin_VIP_Change(void)
{
    while (1)
    {
        system("cls");
        printf("\n\n\n");
        printf(" -------- 欢 迎 使 用 山 大 餐 饮 管 理 员 系 统 ---------\n\n\n");
        printf("     卡 号\t\t电 话\t\t  余 额\n");
        printf(" ==========================================================\n\n");
        Print_LinkTable(SDU_Restaurant.current_vip);
        printf(" ==========================================================\n\n");
        printf("  输 入 \"add [卡 号] [电 话] [余 额]\" 添 加 VIP 顾 客）\n\n");
        // printf("  初 始 化 密 码  为 123456，初 始 化 盈 利 为 0  \n\n  若 暂 无 图 片 则 请 输 入 \"EMPTY_ADRESS\"\n\n");
        printf("  输 入 \"del [卡 号]\" 删 除 VIP\n\n");
        printf("  输 入 \"quit\" 返 回 上 一 级 菜 单\n\n");
        printf("   $ admin > ");
        char cmd[30] = { 0 };
        scanf_s("%s", cmd, sizeof(cmd));
        if (strcmp(cmd, "add") == 0)
        {
            //新增服务员信息
            struct VIP newVIP;
            scanf_s(" %d", &newVIP.cardnum);
            scanf_s(" %lld", &newVIP.phonenum);
            scanf_s(" %lf", &newVIP.money);
            //更新菜品链表
            SDU_Add_VIP(SDU_Restaurant.current_vip, newVIP);

            //存储到文件
            Save_VIP_Inform();
            clearScreenBuffer(); //若add 后仍有内容则略去
        }
        else if (strcmp(cmd, "del") == 0)
        {
            if (!(0 == SDU_Restaurant.vipsCount)) //判断服务员库是否为空
            {
                int cardnum;
                scanf_s(" %d", &cardnum);
                SDU_Restaurant.current_vip = SDU_Delete_VIP(SDU_Restaurant.current_vip, cardnum);
                Save_VIP_Inform();
            }
            else
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); //淡红色
                printf("\n  VIP 列 表 为 空，无 法 继 续 删 除！");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); //恢复白色
                SDU_Restaurant_Sleep(1000);
            }
            // Order_By_ID(SDU_Restaurant.current_waiters);
            clearScreenBuffer(); //若del 后仍有内容则略去
        }
        else if (strcmp(cmd, "quit") == 0)
            break;
        else
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); //淡红色
            printf("\n  所 输 入 的 命 令 格 式 有 误！");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); //白色
            SDU_Restaurant_Sleep(500);
        }
    }
    clearScreenBuffer();
    system("cls");
}

/*退出程序界面*/
void Show_Exit_Program(void)
{
    system("cls");
    printf("\n\n\n\n\n\n");
    printf("\t         感 谢 您 的 使 用，再 见 ！            \n\n\n\n\n");
    SDU_Restaurant_Sleep(1000);
    exit(EXIT_FAILURE);
}

/*预定座位页面*/
void Waiter_Seat_Select(void)
{
    int row, col, num;
    while (1)
    {
        system("cls");
        printf("\n\n\n");
        printf(" -------- 欢 迎 使 用 山 大 餐 饮 服 务 员 系 统 ---------\n\n");
        printf("    这 是 餐 厅 实 时 座 位 图：\n");
        printSeatsMap();
        printf("    \"*\" ：表 示 已 预 约 的 顾 客\n    \"@\" ：表 示 正 在 用 餐 的 顾 客\n");
        printf("    您 可 以 输 入 [餐 桌 号] 来 选 择 一 个 座 位\n    输 入 0 返 回 上 一 级 菜 单...\n\n");
        printf("    我 要 选 的 位 置: ");
        scanf_s("%d", &num);
        col = (num - 1) % SEATINFO_WIDTH;
        row = (num - col) / SEATINFO_WIDTH;
        if (num == 0)
            break;
        if ((col < 0 || col >= SEATINFO_WIDTH) || (row < 0 || row >= SEATINFO_HEIGHT))
        {
            printf("\n   这 个 位 置 不 存 在~\n");
            SDU_Restaurant_Sleep(1000);
            continue;
        }
        //判断座位是否可选择
        if (Check_Selected(num))
        {
            printf("\n   这 个 位 置 已 经 被 占 了~\n");
            SDU_Restaurant_Sleep(1000);
            continue;
        }
        else if (Check_Seated(num))
        {
            printf("\n   这 个 位 置 正 在 用 餐 了~\n");
            SDU_Restaurant_Sleep(1000);
            continue;
        }

        clearScreenBuffer();
        printf("    您 选 择 了 第 %d 排 第 %d 列 的 座 位，桌 号 为 %d\n", row + 1, col + 1, num);

        struct Customer newcustomer;
        newcustomer.Seatnum = num;              //新顾客的座位
        newcustomer.order.ExpensesToBePaid = 0; //初始化新顾客的订单
        newcustomer.order.foodCount = 0;
        strcpy_s(newcustomer.address, EMPTY_ADDRESS);
        SDU_Add_Customer(SDU_Restaurant.current_customer, newcustomer);
        Save_Customer_Inform();

        SDU_Restaurant.seatsMap[row][col].isSelected = 1; //选中输入的座位
        SDU_Restaurant.seatsMap[row][col].isSeated = 0;   //选中输入的座位
        Write_SeatMap_Inform((struct Seat*)&SDU_Restaurant.seatsMap);
        SDU_Restaurant_Sleep(1000);
    }
    system("cls");
}

/*登记订单界面*/
void Waiter_Food_Order(void)
{
    int num;
    int col, row;
    NODE_C* pr = SDU_Restaurant.current_customer;
    bool quit = false;
    while (1)
    {
        system("cls");
        printf("\n\n\n");
        printf(" -------- 欢 迎 使 用 山 大 餐 饮 服 务 员 系 统 ---------\n\n\n");
        printf("\t   请 输 入 顾 客 桌 号 \n\n");
        printf("\t   ( 输 入 0 返 回 上  一  级 菜 单)\n\n");
        printf("\t   > ");
        scanf_s("%d", &num);
        col = (num - 1) % SEATINFO_WIDTH;
        row = (num - col) / SEATINFO_WIDTH;
        clearScreenBuffer();
        if (!num)
        {
            quit = true;
            break;
        }
        else
        {
            for (pr = SDU_Restaurant.current_customer; pr != NULL; pr = pr->next)
            {
                if (pr->data.Seatnum == num) {
                    pr->data.order.isDiscount = 0;
                    break;
                }
            }

            if (pr == NULL)
            {
                printf("该 桌 暂 无 顾 客！");
                SDU_Restaurant_Sleep(1200);
            }
            else
                break;
        }
    }
    if (quit == false)
        while (1)
        {
            system("cls");
            printf("\n\n\n");
            printf(" -------- 欢 迎 使 用 山 大 餐 饮 服 务 员 系 统 ---------\n\n");
            printf("    序 号\t\t菜   名\t\t\t 单 价\n");
            printf(" ==========================================================\n");
            Print_LinkTable(SDU_Restaurant.current_foods);
            printf(" ==========================================================\n\n");

            int i;
            if (!(pr->data.order.foodCount == 0))
            {

                printf("\t\t      顾 客 订 单\n\n");
                printf("    序 号\t\t菜   名\t\t\t 单 价\n");
                printf(" ==========================================================\n");

                for (i = 0; i < pr->data.order.foodCount; i++)
                    printf("      %02d\t\t  %-15s\t %3.2lf 元\n", pr->data.order.foods[i].id, pr->data.order.foods[i].name, pr->data.order.foods[i].price);
                printf(" ==========================================================\n");
                printf("    总 菜 品 数: %2d\t\t 应 支 付 金 额: %3.2f 元\n\n", pr->data.order.foodCount, pr->data.order.ExpensesToBePaid);
            }

            printf("    请 输 入 菜 品 所 对 应 的 序 号 进 行 点 餐： \n\n    输 入 0 返 回 上 一 级 菜 单...\n\n");
            static int addResult = -1; //初值不能是0
            if (!addResult)            //如果上一次添加了非法foodID导致上一次添加失败，这里给与提示
            {
                printf("    这 个 序 号 不 存 在 ，请 输 入 正 确 的 菜 品 序 号.\n");
            }
            int foodID;
            printf("    请 输 入 菜 品 序 号: [ ]\b\b");
            addResult = scanf_s("%d", &foodID);
            clearScreenBuffer();
            system("cls");
            if (foodID == 0)
            {
                break;
            }
            else if (foodID > 0 && addResult)
            {
                addResult = Add_Food_To_Order(foodID, &pr->data.order);
            }

            else if (addResult)
            {
                addResult = Delet_Food_From_Order(-foodID, &pr->data.order);
            }
            Save_Customer_Inform();
        }
    if (pr != NULL && pr->data.order.foodCount)
    {
        SDU_Restaurant.seatsMap[row][col].isSelected = 0;
        SDU_Restaurant.seatsMap[row][col].isSeated = 1;
        Write_SeatMap_Inform((struct Seat*)&SDU_Restaurant.seatsMap);
    }
}

/*打印每日营业额*/
void Print_Daily_Profit(NODE_D* pHead_d)
{
    NODE_D* pr = NULL;
    if (0 == SDU_Restaurant.dateCount)
        return;
    for (pr = pHead_d; !(pr == NULL); pr = pr->next)
        printf("       \t%04d / %02d / %02d\t\t      %10.2f 元\n", pr->data.year, pr->data.month, pr->data.day, pr->data.profit);
}

/*展示当前座位情况*/
void printSeatsMap()
{
    int row, col;
    printf("   ");
    printf("\n");
    for (row = 0; row < SEATINFO_HEIGHT; row++)
    {
        printf("   ");
        for (col = 0; col < SEATINFO_WIDTH; col++)
        {
            char ch;
            if (SDU_Restaurant.seatsMap[row][col].isSeated)
            {
                ch = '@';
            }
            else if (SDU_Restaurant.seatsMap[row][col].isSelected)
            {
                ch = '*';
            }
            else
            {
                ch = ' ';
            }
            printf(" %02d[%c]", row * SEATINFO_WIDTH + col + 1, ch);
        }
        printf("\n\n");
    }
}

/*管理员查看营业总额*/
void Admin_Daily_Profit(void)
{
    system("cls");
    printf("\n\n\n");
    printf(" -------- 欢 迎 使 用 山 大 餐 饮 管 理 员 系 统 ---------\n\n");
    printf("\t    日 期\t\t\t 利 润\n");
    printf(" ==========================================================\n\n");
    Print_Daily_Profit(SDU_Restaurant.current_date);
    printf("\n ==========================================================\n");

    system("pause");
}

/*管理员展示座位情况*/
void Admin_Seat_Infom(void)
{
    system("cls");
    printf("\n\n\n");
    printf(" -------- 欢 迎 使 用 山 大 餐 饮 管 理 员 系 统 ---------\n\n");
    printf("    这 是 餐 厅 实 时 座 位 图：\n");
    printSeatsMap();

    int customer_count = 0;
    for (int i = 0; i < SEATINFO_HEIGHT; i++)
        for (int j = 0; j < SEATINFO_WIDTH; j++)
            if (SDU_Restaurant.seatsMap[i][j].isSelected||SDU_Restaurant.seatsMap[i][j].isSeated)
                customer_count++;

    printf("============================================================\n");
    printf("    当 前 餐 厅 中 共 有 %d 桌 顾 客\n", customer_count);
    printf("============================================================\n\n");
    printf("    按 Enter 返 回 上 一 级 菜 单 界 面...");
    char GETCHAR = getchar();
    system("cls");
}
void Admin_Statistics_Analysis(void)
{
    system("cls");
    printf("\n\n\n");
    printf(" -------- 欢 迎 使 用 山 大 餐 饮 管 理 员 系 统 ---------\n\n");
    printf("    序 号\t  菜   名\t   单 价\t销量\n");
    printf("============================================================\n");
    Show_LinkTable(SDU_Restaurant.current_foods);
    printf("============================================================\n");
    system("pause");
}
/*取消预定*/
void Waiter_Seat_Cancel(void)

{
    while (1)
    {
        system("cls");
        printf("\n\n\n");
        printf(" -------- 欢 迎 使 用 山 大 餐 饮 服 务 员 系 统 ---------\n\n");
        printf("    这 是 餐 厅 实 时 座 位 图：\n");
        printSeatsMap();
        printf("    您 可 以 输 入 [餐 桌 号] 来 取 消 一 个 座 位 的 预 定\n\n    输 入 0 返 回 上 一 级 菜 单...\n\n");
        int row, col, num;
        printf("    我 要 取 消 的 位 置: ");
        scanf_s("%d", &num);
        col = (num - 1) % SEATINFO_WIDTH;
        row = (num - col) / SEATINFO_WIDTH;
        if (num == 0)
            break;

        //判断座位是否可删除
        if (Check_Selected(num))
        {
            SDU_Restaurant.seatsMap[row][col].isSelected = 0;
            printf("    已 成 功 取 消 预 定 了 第 %d 排 第 %d 列 的 座 位\n", row + 1, col + 1);
            SDU_Restaurant.current_customer = SDU_Delete_Customer(SDU_Restaurant.current_customer, num);
            Save_Customer_Inform();
            Write_SeatMap_Inform((struct Seat*)&SDU_Restaurant.seatsMap);
            SDU_Restaurant_Sleep(1000);
        }
        else if (Check_Seated(num))
        {
            printf("    该 位 置 正 在 用 餐，无 法 取 消 预 定\n");
            SDU_Restaurant_Sleep(1000);
        }
        else if (!Check_Selected(num)) //没人选过的座位
        {
            printf("    该 位 置 尚 未 预 定，无 法 取 消\n");
            SDU_Restaurant_Sleep(1000);
        }
        else if (!(col >= 0 && col < SEATINFO_WIDTH) && (row >= 0 && row < SEATINFO_HEIGHT))
        {
            printf("    该 桌 号 不 存 在，无 法 取 消\n");
            SDU_Restaurant_Sleep(1000);
        }
        Write_SeatMap_Inform((struct Seat*)&SDU_Restaurant.seatsMap);
        clearScreenBuffer();
    }
    system("cls");
}

/*管理员修改账户密码*/
void Admin_Passwd_Change(void)
{
    system("cls");
    printf("\n\n\n");
    printf(" -------- 欢 迎 使 用 山 大 餐 饮 管 理 员 系 统 ---------\n\n\n");
    printf("\t   请 输 入 旧 密 码 \n\n");
    printf("\t   ( 单 击 回 车 结 束 输 入)\n\n");
    printf("\t   > ");
    char oldpasswd[ADMINPAS_LENGTH_MAX];
    scanf_s("%s", oldpasswd, ADMINPAS_LENGTH_MAX);
    printf("\n\n");
    printf("\t   请 输 入 新 密 码 \n\n");
    printf("\t   ( 单 击 回 车 结 束 输 入)\n\n");
    printf("\t   > ");
    char newpasswd[ADMINPAS_LENGTH_MAX] = { 0 };
    scanf_s("%s", newpasswd, ADMINPAS_LENGTH_MAX);
    printf("\n\n");
    if (Check_Admin("admin", oldpasswd))
    {
        printf("\t   请 确 认 密 码\n");
        printf("\t   ( 单 击 回 车 结 束 输 入)\n\n");
        printf("\t   > ");
        char newpasswd2[ADMINPAS_LENGTH_MAX] = { 0 };
        scanf_s("%s", newpasswd2, ADMINPAS_LENGTH_MAX);
        if (0 == strcmp(newpasswd, newpasswd2))
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); //淡绿色
            printf("\n\n\t   修 改 成 功 !");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); //恢复白色
            SDU_Restaurant_Sleep(1200);
            Write_Admin_Inform("admin", newpasswd);
        }
        else
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); //淡红色
            printf("\n\n\t   新 密 码 两 次 输 入 不 一 致 !");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); //恢复白色
            SDU_Restaurant_Sleep(1000);
        }
    }
    else
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); //淡红色
        printf("\n\n\t   旧 密 码 错 误 !");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); //恢复白色
        SDU_Restaurant_Sleep(1000);
    }
}

/*服务员修改密码界面*/
void Waiter_Passwd_Change(void)
{
    system("cls");
    printf("\n\n\n");
    printf(" -------- 欢 迎 使 用 山 大 餐 饮 服 务 员 系 统 ---------\n\n\n");
    printf("\t   请 输 入 旧 密 码 \n\n");
    printf("\t   ( 单 击 回 车 结 束 输 入)\n\n");
    printf("\t   > ");
    char oldpasswd[WAITERPAS_LENGTH_MAX] = { 0 };
    scanf_s("%s", oldpasswd, WAITERPAS_LENGTH_MAX);
    printf("\n\n");
    printf("\t   请 输 入 新 密 码 \n\n");
    printf("\t   ( 单 击 回 车 结 束 输 入)\n\n");
    printf("\t   > ");
    char newpasswd[WAITERPAS_LENGTH_MAX] = { 0 };
    scanf_s("%s", newpasswd, WAITERPAS_LENGTH_MAX);
    printf("\n\n");
    if (0 == strcmp(oldpasswd, SDU_Restaurant.waiter_Login->passwd))
    {
        printf("\t   请 确 认 密 码\n\n");
        printf("\t   ( 单 击 回 车 结 束 输 入)\n\n");
        printf("\t   > ");
        char newpasswd2[WAITERPAS_LENGTH_MAX] = { 0 };
        scanf_s("%s", newpasswd2, WAITERPAS_LENGTH_MAX);
        if (0 == strcmp(newpasswd, newpasswd2))
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); //淡绿色
            printf("\n\n\n\t   修 改 成 功 !");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); //恢复白色
            SDU_Restaurant_Sleep(1200);
            strcpy_s(SDU_Restaurant.waiter_Login->passwd, newpasswd);
            Save_Waiter_Inform();
        }
        else
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); //淡红色
            printf("\n\n\n\t   新 密 码 两 次 输 入 不 一 致 !");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); //恢复白色
            SDU_Restaurant_Sleep(1000);
        }
    }
    else
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); //淡红色
        printf("\n\n\n\t   旧 密 码 错 误 !");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); //恢复白色
        SDU_Restaurant_Sleep(1000);
    }
}
