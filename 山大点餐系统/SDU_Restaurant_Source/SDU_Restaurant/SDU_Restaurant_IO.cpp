#include "SDU_Restaurant_Core.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern struct SDU_Restaurant_Data SDU_Restaurant;

/*读取菜品信息*/
void Read_Food_Inform(struct food* (*foods), int* num)
{
    FILE* fp;
    errno_t err;
    if ((err = fopen_s(&fp, "DataBase_Food.txt", "rb")) == 0)
    {
        (*num) = 0;

        fread(num, sizeof(int), 1, fp);
        (*foods) = (struct food*)calloc((*num), sizeof(struct food));
        Assert_Program(*foods);

        if (*foods == NULL) //无该条件判断将会出现警告Warning C6387
            return;
        fread(*foods, sizeof(struct food), (*num), fp);
        fclose(fp);
    }
    else
    {
        printf("\n\n\n\n\n\n\t\t  数 据 文 件 打 开 失 败 ！ \n\n\n\t\t    请 先 进 行 初 始 化  ");
        SDU_Restaurant_Sleep(4000);
        exit(EXIT_FAILURE);
    }
}

/*读取服务员信息*/
void Read_Waiter_Inform(struct Waiter* (*waiters), int* num)
{
    FILE* fp;
    errno_t err;
    if ((err = fopen_s(&fp, "DataBase_Waiter.txt", "rb")) == 0)
    {
        (*num) = 0;

        fread(num, sizeof(int), 1, fp);
        (*waiters) = (struct Waiter*)calloc((*num), sizeof(struct Waiter));
        Assert_Program(*waiters);

        if (*waiters == NULL) //无该条件判断将会出现警告Warning C6387
            return;
        fread(*waiters, sizeof(struct Waiter), (*num), fp);
        fclose(fp);
    }
    else
    {
        printf("\n\n\n\n\n\n\t\t  数 据 文 件 打 开 失 败 ！ \n\n\n\t\t    请 先 进 行 初 始 化  ");
        SDU_Restaurant_Sleep(4000);
        exit(EXIT_FAILURE);
    }
}

/*读取顾客信息*/
void Read_Customer_Inform(struct Customer* (*customers), int* num)
{
    FILE* fp;
    errno_t err;
    if ((err = fopen_s(&fp, "DataBase_Customer.txt", "rb")) == 0)
    {
        (*num) = 0;

        fread(num, sizeof(int), 1, fp);
        (*customers) = (struct Customer*)calloc((*num), sizeof(struct Customer));
        Assert_Program(*customers);

        if (*customers == NULL) //无该条件判断将会出现警告Warning C6387
            return;
        fread(*customers, sizeof(struct Customer), (*num), fp);
        fclose(fp);
    }
    else
    {
        printf("\n\n\n\n\n\n\t\t  数 据 文 件 打 开 失 败 ！ \n\n\n\t\t    请 先 进 行 初 始 化  ");
        SDU_Restaurant_Sleep(4000);
        exit(EXIT_FAILURE);
    }
}

/*读取VIP信息*/
void Read_VIP_Inform(struct VIP* (*vips), int* num)
{
    FILE* fp;
    errno_t err;
    if ((err = fopen_s(&fp, "DataBase_VIP.txt", "rb")) == 0)
    {
        (*num) = 0;

        fread(num, sizeof(int), 1, fp);
        (*vips) = (struct VIP*)calloc((*num), sizeof(struct VIP));
        Assert_Program(*vips);

        if (*vips == NULL) //无该条件判断将会出现警告Warning C6387
            return;
        fread(*vips, sizeof(struct VIP), (*num), fp);
        fclose(fp);
    }
    else
    {
        printf("\n\n\n\n\n\n\t\t  数 据 文 件 打 开 失 败 ！ \n\n\n\t\t    请 先 进 行 初 始 化  ");
        SDU_Restaurant_Sleep(4000);
        exit(EXIT_FAILURE);
    }
}

/*读取座位信息*/
void Read_SeatMap_Inform(struct Seat* pSeatsMap)
{
    FILE* fp;
    errno_t err;
    if ((err = fopen_s(&fp, "DataBase_SeatsMap.txt", "rb")) == 0)
    {
        // pSeatsMap = (struct Seat *)calloc(SEATINFO_HEIGHT*SEATINFO_WIDTH, sizeof(struct Seat));//遗留
        fread(pSeatsMap, sizeof(struct Seat), SEATINFO_HEIGHT * SEATINFO_WIDTH, fp);
        fclose(fp);
    }
    else
    {
        printf("\n\n\n\n\n\n\t\t  数 据 文 件 打 开 失 败 ！ \n\n\n\t\t    请 先 进 行 初 始 化  ");
        SDU_Restaurant_Sleep(4000);
        exit(EXIT_FAILURE);
    }
}

/*从文件中读取前一日日利润信息*/
void Read_Date_Inform(struct Date* (*dates), int* num)
{
    FILE* fp;
    errno_t err;
    if ((err = fopen_s(&fp, "DataBase_Date.txt", "rb")) == 0)
    {
        (*num) = 0;

        fread(num, sizeof(int), 1, fp);

        if (!(num == 0))
        {
            (*dates) = (struct Date*)calloc((*num), sizeof(struct Date));
            Assert_Program(*dates);
        }
        else
        {
            (*dates) = NULL;
        }

        if (*dates == NULL) //无该条件判断将会出现警告Warning C6387
            return;
        fread(*dates, sizeof(struct Date), (*num), fp);
        fclose(fp);
    }
    else
    {
        printf("\n\n\n\n\n\n\t\t  数 据 文 件 打 开 失 败 ！ \n\n\n\t\t    请 先 进 行 初 始 化  ");
        SDU_Restaurant_Sleep(4000);
        exit(EXIT_FAILURE);
    }
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
        printf("\n\n\n\n\n\n\t\t  数 据 文 件 打 开 失 败 ！ \n\n\n\t\t    请 先 进 行 初 始 化  ");
        SDU_Restaurant_Sleep(4000);
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
        printf("\n\n\n\n\n\n\t\t  数 据 文 件 打 开 失 败 ！ \n\n\n\t\t    请 先 进 行 初 始 化  ");
        SDU_Restaurant_Sleep(4000);
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
        printf("\n\n\n\n\n\n\t\t  数 据 文 件 打 开 失 败 ！ \n\n\n\t\t    请 先 进 行 初 始 化  ");
        SDU_Restaurant_Sleep(4000);
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
        printf("\n\n\n\n\n\n\t\t  数 据 文 件 打 开 失 败 ！ \n\n\n\t\t    请 先 进 行 初 始 化  ");
        SDU_Restaurant_Sleep(4000);
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
        printf("\n\n\n\n\n\n\t\t  数 据 文 件 打 开 失 败 ！ \n\n\n\t\t    请 先 进 行 初 始 化  ");
        SDU_Restaurant_Sleep(4000);
        exit(EXIT_FAILURE);
    }
}

/*将管理员数组信息写入文件，目前只有一位管理员const char id[]，若未多管理员需改为struct Admin admin[]*/
void Write_Admin_Inform(const char id[], const char ps[])
{
    if (strlen(id) > ADMINID_LENGTH_MAX) //限制工号长度上限
    {
        printf("工号太长了，只有前 %d 个字符被储存.\n", ADMINID_LENGTH_MAX);
        SDU_Restaurant_Sleep(1000);
    }
    if (strlen(ps) > ADMINPAS_LENGTH_MAX) //限制密码长度上限
    {
        printf("密码太长了，只有前 %d 个字符被储存.\n", ADMINPAS_LENGTH_MAX);
        SDU_Restaurant_Sleep(1000);
    }
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
        printf("\n\n\n\n\n\n\t\t  数 据 文 件 打 开 失 败 ！ \n\n\n\t\t    请 先 进 行 初 始 化  ");
        SDU_Restaurant_Sleep(4000);
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
        printf("\n\n\n\n\n\n\t\t  数 据 文 件 打 开 失 败 ！ \n\n\n\t\t    请 先 进 行 初 始 化  ");
        SDU_Restaurant_Sleep(4000);
        exit(EXIT_FAILURE);
    }
}

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

/*检验管理员身份*/
int Check_Admin(const char* id_input, char* ps_input)
{
    char id[ADMINID_LENGTH_MAX + 1] = { 0 };
    char ps[ADMINPAS_LENGTH_MAX + 1] = { 0 };
    FILE* fp;
    errno_t err;
    if ((err = fopen_s(&fp, "DataBase_Admin.txt", "rb")) == 0)
    {
        while (fscanf_s(fp, "%s %s", id, sizeof(id), ps, sizeof(ps)) != EOF)
        {
            if (strcmp(id, id_input) == 0 && strcmp(ps, ps_input) == 0)
            {
                fclose(fp);
                return 1;
            }
        }
        fclose(fp);
        return 0;
    }
    else
    {
        printf("\n\n\n\n\n\n\t\t  数 据 文 件 打 开 失 败 ！ \n\n\n\t\t    请 先 进 行 初 始 化  ");
        SDU_Restaurant_Sleep(4000);
        exit(EXIT_FAILURE);
    }
}

/*检验服务员身份*/
int Check_Waiter(char* id_input, char* ps_input)
{
    NODE_W* pr = NULL;
    if (0 == SDU_Restaurant.waitersCount)
        return 0;
    for (pr = SDU_Restaurant.current_waiters; !(pr == NULL); pr = pr->next)
    {
        if (0 == strcmp(pr->data.id, id_input) && 0 == strcmp(pr->data.passwd, ps_input))
        {

            SDU_Restaurant.waiter_Login = &pr->data;
            return 1;
        }
    }
    return 0;
}

/*判断座位是否被占用*/
bool Check_Seated(int num)
{
    int row, col;
    col = (num - 1) % SEATINFO_WIDTH;
    row = (num - col) / SEATINFO_WIDTH;
    if ((col >= 0 && col < SEATINFO_WIDTH) && (row >= 0 && row < SEATINFO_HEIGHT) && SDU_Restaurant.seatsMap[row][col].isSeated)
        return true;
    return false;
}

bool Check_Selected(int num)
{
    int row, col;
    col = (num - 1) % SEATINFO_WIDTH;
    row = (num - col) / SEATINFO_WIDTH;
    if ((col >= 0 && col < SEATINFO_WIDTH) && (row >= 0 && row < SEATINFO_HEIGHT) && SDU_Restaurant.seatsMap[row][col].isSelected)
        return true;
    return false;
}