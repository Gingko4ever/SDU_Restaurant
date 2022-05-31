#include"SDU_Restaurant_Init.h"
#include<stdio.h>
#include<windows.h>
struct SDU_Restaurant_Data SDU_Restaurant;

int main()
{
	SDU_Restaurant_Console_Init();

	Create_DataBaseFiles();
	printf("\n\n\n\n\n\n\t     山 大 餐 饮 系 统 欢 迎 您 的 使 用 \n\n\n\t       数 据 文 件 已 初 始 化 成 功 ！ ");
	SDU_Restaurant_Sleep(4000);
	return 0;
}