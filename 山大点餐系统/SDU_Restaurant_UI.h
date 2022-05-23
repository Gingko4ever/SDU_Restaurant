#pragma once

/*服务员*/
int Waiter_Menu(void); //服务员菜单页面

void Waiter_Food_Show(void); //服务员展示菜品界面

void Waiter_Food_Order(void); //服务员展示点菜界面

void Waiter_Food_Check(void); //服务员展示结账界面

void Waiter_Seat_Select(void); //服务员座位预定界面

void Waiter_Passwd_Change(void); //服务员修改密码界面

void Waiter_Seat_Cancel(void); //服务员取消预定界面

/*管理员*/
int Admin_Menu(void); //管理员菜单页面

void Admin_Food_Change(void); //管理员更改餐品信息

void Admin_Waiter_Change(void); //管理员更改服务员信息

void Admin_Seat_Infom(void);//管理员展示座位情况

void Admin_Daily_Profit(void);//管理员展示每日利润

void Admin_Statistics_Analysis();//管理员展示菜品销量

void Admin_Passwd_Change();//管理员更改密码

void Admin_VIP_Change(void);//管理员更改VIP信息

/*UI界面*/
enum UserType SDU_Restaurant_Welcome(void); //用户类型选择页面

void Loading_Menu(char* ID_input, char* password_input); //登录菜单界面

int Check_ID_Passwd(char* ID_input, char* password_input, enum UserType* userType, int Choice); //检测密码是否匹配

void Show_Exit_Program(void); //退出程序页面

void clearScreenBuffer(void); //清空屏幕缓冲区
