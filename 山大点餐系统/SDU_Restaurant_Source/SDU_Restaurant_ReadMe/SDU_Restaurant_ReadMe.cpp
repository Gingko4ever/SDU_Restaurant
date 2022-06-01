#include"SDU_Restaurant_ReadMe.h"
#include<stdio.h>
#include<windows.h>
#include <graphics.h>    
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
    SetConsoleTitle(TEXT("山 大 餐 饮 系 统 说 明 书"));
    system("mode con cols=60 lines=35");
    //获取当前窗口句柄
    HWND hwnd = GetHWnd();
    //把黑色的背景设置为透明
    SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 150, LWA_ALPHA);
}