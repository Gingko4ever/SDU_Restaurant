#include"SDU_Restaurant_ReadMe.h"
#include <iostream>
#include<windows.h>
using namespace std;
int ar[5] = {0, 14,10,12,13};
int main()
{

    SDU_Restaurant_Console_Init();
    cout << endl
         << endl;

    for (int i = 1; i <= 4; i++) 
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ar[i]); //µ­ºìÉ«
        cout << "\t    _________       ________         ___     ___" << endl
            << "\t   /  ______/      /  ___   |       /  /    /  /" << endl
            << "\t  /  /______      /  /   |  |      /  /    /  /" << endl
            << "\t /______   /     /  /    /  /     /  /    /  /" << endl
            << "\t ______/  /     /  /___ /  /     /  /____/  /" << endl
            << "\t/________/     /__________/     /__________/" << endl<<endl;

        SDU_Restaurant_Sleep(1200);
    }
    SDU_Restaurant_Sleep(2000);

}