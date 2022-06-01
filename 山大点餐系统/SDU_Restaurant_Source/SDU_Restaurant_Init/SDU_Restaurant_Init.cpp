#include"SDU_Restaurant_Init.h"
#include<stdio.h>
#include<windows.h>
#include <graphics.h>    
extern struct SDU_Restaurant_Data SDU_Restaurant;

//数据文件初始化
void Create_DataBaseFiles(void)
{
    /*初始化DataBase_SeatsMap内容*/
    int row, col;
    for (row = 0; row < SEATINFO_HEIGHT; row++)
    {
        for (col = 0; col < SEATINFO_WIDTH; col++)
        {

            SDU_Restaurant.seatsMap[row][col].isSelected = 0;
            SDU_Restaurant.seatsMap[row][col].row = row;
            SDU_Restaurant.seatsMap[row][col].col = col;
        }
    }
    Write_SeatMap_Inform((struct Seat*)&SDU_Restaurant.seatsMap);

    /*初始化DataBase_Food内容*/
    Write_Food_Inform((struct food*)0, 0);

    /*初始化DataBase_Waiter内容*/
    Write_Waiter_Inform((struct Waiter*)0, 0);

    /*初始化DataBase_Customer内容*/
    Write_Customer_Inform((struct Customer*)0, 0);

    /*初始化DataBase_Admin内容*/
    Write_Admin_Inform("admin", "admin");

    /*初始化DataBase_Date内容*/
    Write_Date_Inform((struct Date*)0, 0);

    /*初始化DataBase_VIP内容*/
    Write_VIP_Inform((struct VIP*)0, 0);
}
/*将菜品数组信息写入文件*/
void Write_Food_Inform(struct food foods[], int num)
{
    FILE* fp;
    errno_t err;
    if ((err = fopen_s(&fp, "DataBase_Food.txt", "wb")) == 0)
    {
        fwrite(&num, sizeof(int), 1, fp);
        fwrite(foods, sizeof(struct food), num, fp);

        fclose(fp);
    }
    else
    {
        printf("文件打开失败！\n");
        exit(EXIT_FAILURE);
    }
}

/*将服务员数组信息写入文件*/
void Write_Waiter_Inform(struct Waiter waiters[], int num)
{
    FILE* fp;
    errno_t err;
    if ((err = fopen_s(&fp, "DataBase_Waiter.txt", "wb")) == 0)
    {
        fwrite(&num, sizeof(int), 1, fp);
        fwrite(waiters, sizeof(struct Waiter), num, fp);
        fclose(fp);
    }
    else
    {
        printf("文件打开失败！\n");
        exit(EXIT_FAILURE);
    }
}

/*将顾客数组信息写入文件*/
void Write_Customer_Inform(struct Customer customer[], int num)
{
    FILE* fp;
    errno_t err;

    if ((err = fopen_s(&fp, "DataBase_Customer.txt", "wb")) == 0)
    {
        fwrite(&num, sizeof(int), 1, fp);
        if (customer != NULL)
            fwrite(customer, sizeof(struct Customer), num, fp);
        else
            fwrite((struct Customer*)0, sizeof(struct Customer), 0, fp);
        fclose(fp);
    }
    else
    {
        printf("文件打开失败！\n");
        exit(EXIT_FAILURE);
    }
}

/*将VIP数组信息写入文件*/
void Write_VIP_Inform(struct VIP vips[], int num)
{
    FILE* fp;
    errno_t err;

    if ((err = fopen_s(&fp, "DataBase_VIP.txt", "wb")) == 0)
    {
        fwrite(&num, sizeof(int), 1, fp);
        if (vips != NULL)
            fwrite(vips, sizeof(struct VIP), num, fp);
        else
            fwrite((struct VIP*)0, sizeof(struct VIP), 0, fp);
        fclose(fp);
    }
    else
    {
        printf("文件打开失败！\n");
        exit(EXIT_FAILURE);
    }
}

/*将日利润信息写入文件*/
void Write_Date_Inform(struct Date date[], int num)
{
    FILE* fp;
    errno_t err;
    if ((err = fopen_s(&fp, "DataBase_Date.txt", "wb")) == 0)
    {
        fwrite(&num, sizeof(int), 1, fp);

        fwrite(date, sizeof(struct Date), num, fp);
        fclose(fp);
    }
    else
    {
        printf("文件打开失败！\n");
        exit(EXIT_FAILURE);
    }
}

/*将管理员数组信息写入文件，目前只有一位管理员const char id[]，若未多管理员需改为struct Admin admin[]*/
void Write_Admin_Inform(const char id[], const char ps[])
{

    FILE* fp;
    errno_t err;
    if ((err = fopen_s(&fp, "DataBase_Admin.txt", "wb")) == 0)
    {
        fputs(id, fp);
        fputs(" ", fp);
        fputs(ps, fp);
        fclose(fp);
    }
    else
    {
        printf("文 件 打 开 失 败！\n");
        exit(EXIT_FAILURE);
    }
}

/*将座位信息写入文件*/
void Write_SeatMap_Inform(struct Seat* pSeatsMap)
{
    FILE* fp;
    errno_t err;
    if ((err = fopen_s(&fp, "DataBase_SeatsMap.txt", "wb")) == 0)
    {
        fwrite(pSeatsMap, sizeof(struct Seat), SEATINFO_HEIGHT * SEATINFO_WIDTH, fp);
        fclose(fp);
    }
    else
    {
        printf("文 件 打 开 失 败！\n");
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
    SetConsoleTitle(TEXT("山 大 餐 饮 系 统 初 始 化"));
    system("mode con cols=60 lines=35");
    //获取当前窗口句柄
    HWND hwnd = GetHWnd();
    //把黑色的背景设置为透明
    SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 150, LWA_ALPHA);
}