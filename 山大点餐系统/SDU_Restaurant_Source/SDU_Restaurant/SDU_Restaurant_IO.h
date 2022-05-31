#pragma once

/*初始化*/
void Create_DataBaseFiles(void); //创建全新的数据库文件，原先的数据将被清空

/*座位*/
void Read_SeatMap_Inform(struct Seat* pSeatsMap); //从文件中读取座位图信息

void Write_SeatMap_Inform(struct Seat* pSeatsMap); //将座位图信息写入文件

bool Check_Seated(int num); //判断当前座位是否被占有

bool Check_Selected(int num); //判断当前座位是否被预定

/*菜品*/
void Read_Food_Inform(struct food* (*foods), int* num); //从文件中读取菜品信息

void Write_Food_Inform(struct food foods[], int num); //将菜品信息写入文件

/*服务员*/
void Read_Waiter_Inform(struct Waiter* (*waiters), int* num); //从文件中读取服务员信息

void Write_Waiter_Inform(struct Waiter waiters[], int num); //将服务员信息写入文件

int Check_Waiter(char* id_input, char* ps_input); //检查服务员密码是否正确

/*管理员*/
void Write_Admin_Inform(const char id[], const char ps[]); //将管理员信息写入文件

int Check_Admin(const char* id_input, char* ps_input); //检查管理员密码是否正确

/*顾客*/
void Read_Customer_Inform(struct Customer* (*customer), int* num); //从文件中读取顾客信息

void Write_Customer_Inform(struct Customer customer[], int num); //将顾客信息写入文件

/*VIP*/
void Read_VIP_Inform(struct VIP* (*vips), int* num); //从文件中读取顾客信息

void Write_VIP_Inform(struct VIP vips[], int num); //将顾客信息写入文件

/*日利润*/
void Read_Date_Inform(struct Date* (*dates), int* num); //从文件中读取日利润信息

void Write_Date_Inform(struct Date dates[], int num); //将日利润信息写入文件
