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
    int  isDiscount=0;
};

/*山大餐饮系统之用户类型*/
enum class UserType
{
    undefine, //未登录
    waiter,   //服务员
    admin     //管理员
};

/*山大餐饮系统之座位*/
struct Seat
{
    int isSeated;   //座位是否被占用
    int isSelected; //座位是否被预定
    int row;        //座位行号
    int col;        //座位列号
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

/*山大餐饮系统之菜品链表*/
struct node_v
{
    struct VIP data;
    struct node_v* next;
};
typedef struct node_v NODE_V;


/*山大餐饮系统之菜品链表*/
struct node_f
{
    struct food data;
    struct node_f* next;
};
typedef struct node_f NODE_F;

/*山大餐饮系统之服务员链表*/
struct node_w
{
    struct Waiter data;
    struct node_w* next;
};
typedef struct node_w NODE_W;

/*山大餐饮系统之顾客链表*/
struct node_c
{
    struct Customer data;
    struct node_c* next;
};
typedef struct node_c NODE_C;

/*山大餐饮系统之菜品链表*/
struct node_d
{
    struct Date data;
    struct node_d* next;
};

typedef struct node_d NODE_D;
/*山大餐饮系统之公共数据*/
struct SDU_Restaurant_Data
{
    /*日期盈利*/
    double Day_Profit = 0;//当日收入
    NODE_D* current_date; //指向日期的结构体数组空间的指针
    int dateCount;//已有日期总数

    /*服务员*/
    struct Waiter* waiter_Login; //目前登录的服务员
    NODE_W* current_waiters;     //指向服务员的结构体数组空间的指针
    int waitersCount;            //已有服务员总数

    /*顾客*/
    NODE_C* current_customer; //指向顾客的结构体数组空间的指针
    int customerCount;        //已有顾客总数
    
    /*菜品*/
    NODE_F* current_foods; //指向菜品的结构体数组空间的指针
    int foodsCount;        //已有菜品总数

    /*管理员*/
    char Admin_password[ADMINPAS_LENGTH_MAX + 1] = { 0 };    //系统管理员密码

    /*座位*/
    struct Seat seatsMap[SEATINFO_HEIGHT][SEATINFO_WIDTH]; //餐厅座位图信息

    /*用户*/
    UserType user;

    /*VIP*/
    NODE_V* current_vip; //指向VIP的结构体数组空间的指针
    int vipsCount;        //已有VIP总数
};


/*——函数部分——*/

/*日期*/
void Save_Date_Inform(void); //将日期信息从链表转化为数组存储到文件

NODE_D* Load_Profit_Inform(struct Date* dates, int num);//将日期数据从数组录入链表

NODE_D* Add_To_Tail(NODE_D* pHead_d, struct Date Data);//将日期数据添加到日期链表尾部

NODE_D* Add_To_Head(NODE_D* pHead_d, struct Date data);//将日期数据添加到日期链表头部


/*座位*/
void Leave_Seat(int num); //结完账后自动取消占有情况

void printSeatsMap(void); //打印当前餐厅的座位信息图

void Clear_Seat_Inform(void); //清除所有座位信息


/*管理员*/
void Print_Daily_Profit(NODE_D* pHead_d); //打印每日营业额


/*菜品*/
NODE_F* Add_To_Tail(NODE_F* pHead_f, struct food data); //将菜品数据添加到菜品链表尾部

NODE_F* Add_To_Head(NODE_F* pHead_f, struct food data); //将菜品数据添加到菜品链表头部

void Order_By_ID(NODE_F* pHead_f); //按ID从1开始递增排序

NODE_F* SDU_Delete_Food(NODE_F* pHead_f, int id); //根据序号值,删除相应的菜品数据

NODE_F* Load_Food_Inform(struct food* foods, int num); //将菜品数据从数组录入链表

int Add_Food_To_Order(int foodID, struct Order* order,double discount); //把菜品数据添加到订单

int Delet_Food_From_Order(int foodID, struct Order* order,double discount);//把从订单中删除已订菜品数据

void Save_Food_Inform(void); //将菜品信息从链表转化为数组存储到文件

void Print_LinkTable(NODE_F* pHead_f); //打印菜品链表
void Show_LinkTable(NODE_F* pHead_f);

void SDU_Add_Food(NODE_F* pHead_f, struct food& newFood); //将新增菜品添加到菜品链表

void SDU_Add_Date(NODE_D* pHead_d, struct Date& newDate); //将新增菜品添加到菜品链表


/*服务员*/
NODE_W* Add_To_Tail(NODE_W* pHead_w, struct Waiter data); //将服务员数据添加到服务员链表尾部

NODE_W* Add_To_Head(NODE_W* pHead_w, struct Waiter data); //将服务员数据添加到服务员链表头部

void Order_By_ID(NODE_W* pHead_w); //按ID从递增排序服务员

NODE_W* SDU_Delete_Waiter(NODE_W* pHead_w, char* id); //根据工号,删除相应的服务员数据

NODE_W* Load_Waiter_Inform(struct Waiter* waiters, int num); //将服务员数据从数组录入链表

void Save_Waiter_Inform(void); //将服务员信息从链表转化为数组存储到文件

void Print_LinkTable(NODE_W* pHead_w); //打印服务员链表

void SDU_Add_Waiter(NODE_W* pHead_w, struct Waiter& newWaiter); //将新增服务员添加到服务员链表


/*顾客*/
NODE_C* Add_To_Tail(NODE_C* pHead_c, struct Customer data); //将顾客数据添加到顾客链表尾部

NODE_C* Order_By_Seatnum(NODE_C* pHead_c); //按座号从递增排序

NODE_C* Order_Merge_Sort_By_Seatnum(NODE_C* head1, NODE_C* head2); //归并排序

NODE_C* SDU_Delete_Customer(NODE_C* pHead_c, int seatnum); //根据座号值,删除相应的顾客数据

NODE_C* Load_Customer_Inform(struct Customer* customer, int num); //将顾客数据从数组录入链表

void Save_Customer_Inform(void); //将顾客信息从链表转化为数组存储到文件

void SDU_Add_Customer(NODE_C* pHead_c, struct Customer& newcustomer); //将新增顾客添加到顾客链表

/*VIP*/
NODE_V* Load_VIP_Inform(struct VIP* vips, int num);

NODE_V* Add_To_Tail(NODE_V* pHead_v, struct VIP data); //将VIP数据添加到VIP链表尾部

NODE_V* Order_By_Cardnum(NODE_V* pHead_v); //按座号从递增排序

NODE_V* Order_Merge_Sort_By_Cardnum(NODE_V* head1, NODE_V* head2); //归并排序

NODE_V* SDU_Delete_VIP(NODE_V* pHead_v, int cardnum); //根据卡号,删除相应的VIP数据

void Save_VIP_Inform(void); //将VIP信息从链表转化为数组存储到文件

void Print_LinkTable(NODE_V* pHead_v); //打印VIP链表

void SDU_Add_VIP(NODE_V* pHead_v, struct VIP& newVIP); //将新增服务员添加到VIP链表

int Judge_VIP(long long int phonenum);//检测是否是VIP

/*功能性*/
void SDU_Restaurant_Sleep(unsigned long Milliseconds); //程序休眠暂停指定毫秒时间

void Assert_Program(void* ptr); //若分配空间出错则报错并结束程序

void SDU_Restaurant_Init(int argc, char const* argv[]); //数据文件初始化，数据文件读取，全局变量初始化

void SDU_Restaurant_Console_Init(void); //初始化控制台窗口


/*未定义*/

//根据用户名设定指定用户的账户余额
void setUserMoneyFromUsersHistory(char userNick[], int Money);

//打印前n个最受欢迎的食物
void printPopularFood(int maxOutNum);

//打印前n个最有钱的用户?
void printRichUser(int maxOutNum);
