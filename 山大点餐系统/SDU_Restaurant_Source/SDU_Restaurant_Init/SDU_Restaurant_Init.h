#pragma once

/*——宏定义部分——*/

#define EMPTY_ADDRESS "EMPTY_ADDRESS"//非法图片_标识

#define GRAPHIC_LENGTH_MAX 50 //图片地址_最大长度

#define USERNICK_LENGTH_MAX 30 //用户昵称_最大长度

#define FOODNAME_LENGTH_MAX 30 //食物名称_最大长度

#define ADMINID_LENGTH_MAX 30  //管理员工号_最大长度

#define ADMINPAS_LENGTH_MAX 30 //管理员密码_最大长度

#define USRID_LENGTH_MAX 30 //服务员工号_最大长度

#define USRPAS_LENGTH_MAX 30 //服务员密码_最大长度

#define WAITERID_LENGTH_MAX 30 //服务员工号_最大长度

#define WAITERPAS_LENGTH_MAX 30 //服务员密码_最大长度

#define WAITERNICK_LENGTH_MAX 30 //服务员姓名_最大长度

#define ORDERFOODS_LENGTH_MAX 30 //订单菜品数目_最大长度

#define SEATINFO_HEIGHT 7 //座位矩阵_行数

#define SEATINFO_WIDTH 9 //座位矩阵_列数


/*——结构体部分——*/

/*山大餐饮系统之日期*/
struct Date
{
    int year;
    int month;
    int day;
    int orderCount;
    double profit;
};

/*山大餐饮系统之菜品*/
struct food
{
    int id;                           //菜品标号
    char name[FOODNAME_LENGTH_MAX];   //菜品名称
    double price;                     //菜品价格
    int orderCount;                   //菜品销量
    char address[GRAPHIC_LENGTH_MAX]; //菜品图片
};

/*山大餐饮系统之服务员*/
struct Waiter
{
    int NO;
    double profit;                             //服务员盈利
    char id[WAITERID_LENGTH_MAX];            //服务员ID
    char waiterNick[WAITERNICK_LENGTH_MAX];  //服务员昵称
    char passwd[ADMINPAS_LENGTH_MAX];        //服务员密码
    char waiter_address[GRAPHIC_LENGTH_MAX]; //服务员图片地址
};

/*山大餐饮系统之订单*/
struct Order
{
    int foodCount; //当前订单的食物数
    struct food foods[ORDERFOODS_LENGTH_MAX];
    double ExpensesToBePaid; //当前订单应付费用
    int  isDiscount = 0;
};
/*山大餐饮系统之座位*/
struct Seat
{
    int isSeated;   //座位是否被占用
    int isSelected; //座位是否被预定
    int row;        //座位行号
    int col;        //座位列号
};

/*山大餐饮系统之公共数据*/
struct SDU_Restaurant_Data
{
    /*座位*/
    struct Seat seatsMap[SEATINFO_HEIGHT][SEATINFO_WIDTH]; //餐厅座位图信息
};
/*山大餐饮系统之顾客*/
struct Customer
{
    int Seatnum;                      //桌号
    struct Order order;               //订单
    char address[GRAPHIC_LENGTH_MAX]; //目的是将TXT文件的编码格式由UTF-8转变为ANSI，不然会导致编码错误
};

/*山大餐饮系统之VIP*/
struct VIP
{
    int cardnum;
    long long int phonenum;
};


void Create_DataBaseFiles(void);

void Write_SeatMap_Inform(struct Seat* pSeatsMap); //将座位图信息写入文件

void Write_Food_Inform(struct food foods[], int num); //将菜品信息写入文件

void Write_Waiter_Inform(struct Waiter waiters[], int num); //将服务员信息写入文件

void Write_Admin_Inform(const char id[], const char ps[]); //将管理员信息写入文件

void Write_Customer_Inform(struct Customer customer[], int num); //将顾客信息写入文件

void Write_VIP_Inform(struct VIP vips[], int num); //将顾客信息写入文件

void Write_Date_Inform(struct Date dates[], int num); //将日利润信息写入文件

void SDU_Restaurant_Sleep(unsigned long Milliseconds); //程序休眠暂停指定毫秒时间

void SDU_Restaurant_Console_Init(void);
