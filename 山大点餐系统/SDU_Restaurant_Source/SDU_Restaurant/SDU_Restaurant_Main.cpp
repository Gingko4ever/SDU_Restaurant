#include "SDU_Restaurant_Core.h"
#include "SDU_Restaurant_IO.h"
#include "SDU_Restaurant_UI.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct SDU_Restaurant_Data SDU_Restaurant;
bool EXIT;

int main(int argc, char const* argv[])
{
    /*数据文件读取、全局变量初始化*/
    SDU_Restaurant_Init(argc, argv);

    while (1)
    {
        EXIT = false;
        
        /*用户选择身份(管理员OR服务员)*/
        enum class UserType userType = SDU_Restaurant_Welcome();

        /*管理员*/
        if (userType == UserType::admin)
        {
            while (1)
            {
                if (EXIT == true)
                    break;
                int choice = Admin_Menu();
                switch (choice)
                {
                case 1: //查看座位信息.
                    Admin_Seat_Infom();
                    break;
                case 2: //查看营业总额
                    Admin_Daily_Profit();
                    break;
                case 3: //更改菜品信息
                    Admin_Food_Change();
                    break;
                case 4: //更改服务员信息
                    Admin_Waiter_Change();
                    break;
                case 5://更改VIP信息
                    Admin_VIP_Change();
                    break;
                case 6: //修改管理员密码
                    Admin_Passwd_Change();
                    break;
                case 7:  //菜品销量分析.
                    Admin_Statistics_Analysis();
                    break;
                case 8: //管理员账号登出
                    EXIT = 1;
                    break;
                case 0: //退出程序
                    Show_Exit_Program();
                    break;
                }
            }
        }

        /*服务员*/
        else if (userType == UserType::waiter)
        {
            while (1)
            {
                if (EXIT == true)
                    break;
                int choice = Waiter_Menu();
                switch (choice)
                {
                case 1: //选择座位
                    Waiter_Seat_Select();
                    break;
                case 2: //展示菜单
                    Waiter_Food_Show();
                    break;
                case 3: //登记点餐
                    Waiter_Food_Order();
                    break;
                case 4: //结算账单
                    Waiter_Food_Check();
                    break;
                case 5: //取消餐桌预定
                    Waiter_Seat_Cancel();
                    break;
                case 6: //修改服务员密码
                    Waiter_Passwd_Change();
                    break;
                case 7: //服务员账号登出
                    EXIT = 1;
                    break;
                case 0: //退出程序
                    Show_Exit_Program();
                    break;
                }
            }
        }
    }
    return 0;
}
