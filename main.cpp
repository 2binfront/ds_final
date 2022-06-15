#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <stack>
#include <Windows.h>
#include"graph.h"

using namespace std;

graph G;
int subway[10] = { 1,2,3 };//记录地铁路线号 
int subway_num = 3;//记录地铁路线数 
bool visit[100];   //标志站点有没有被访问过	
station S[100];       //换乘站点记录 
int min_length[100];    //所在站点到其他站点的最短路程 

void define_arcs(int i, int j, int road) //i,j是站点编号，road是地铁号
{
	G.arcs[i][j].adj[G.arcs[i][j].adj_loc] = road;
	G.arcs[i][j].adj_loc++;
}

//建立图的存储结构
void createG()
{
	//初始化图的顶点数组
	for (int i = 26; i < 100; i++)
	{
		G.vex[i] = "0";
	}
	G.vexnum = 26;//共有26站
	int sum_arcs = 0;  //记录边的总数
	//对邻接矩阵进行初始化
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			G.arcs[i][j].adj_loc = 0;
			for (int k = 0; k < 100; k++)
			{
				G.arcs[i][j].adj[k] = 0;
			}
		}
	}
	//1号线
	//上三角矩阵
	define_arcs(0, 1, 1);
	define_arcs(1, 2, 1);
	define_arcs(2, 3, 1);
	define_arcs(3, 4, 1);
	define_arcs(4, 5, 1);
	define_arcs(5, 6, 1);
	define_arcs(6, 7, 1);
	define_arcs(7, 8, 1);
	//2号线 
	define_arcs(9, 10, 2);
	define_arcs(10, 11, 2);
	define_arcs(11, 12, 2);
	define_arcs(12, 13, 2);
	define_arcs(13, 14, 2);
	define_arcs(14, 3, 2);
	define_arcs(3, 15, 2);
	define_arcs(15, 16, 2);
	define_arcs(16, 17, 2);
	define_arcs(17, 18, 2);
	//3号线
	define_arcs(19, 20, 3);
	define_arcs(20, 21, 3);
	define_arcs(21, 1, 3);
	define_arcs(1, 14, 3);
	define_arcs(14, 22, 3);
	define_arcs(22, 5, 3);
	define_arcs(5, 23, 3);
	define_arcs(23, 24, 3);
	define_arcs(24, 25, 3);

	//下三角矩阵
	//1号线
	define_arcs(8, 7, 1);
	define_arcs(7, 6, 1);
	define_arcs(6, 5, 1);
	define_arcs(5, 4, 1);
	define_arcs(4, 3, 1);
	define_arcs(3, 2, 1);
	define_arcs(2, 1, 1);
	define_arcs(1, 0, 1);
	//2号线 
	define_arcs(18, 17, 2);
	define_arcs(17, 16, 2);
	define_arcs(16, 15, 2);
	define_arcs(15, 3, 2);
	define_arcs(3, 14, 2);
	define_arcs(14, 13, 2);
	define_arcs(13, 12, 2);
	define_arcs(12, 11, 2);
	define_arcs(11, 10, 2);
	define_arcs(10, 9, 2);
	//3号线 
	define_arcs(25, 24, 3);
	define_arcs(24, 23, 3);
	define_arcs(23, 5, 3);
	define_arcs(5, 22, 3);
	define_arcs(22, 14, 3);
	define_arcs(14, 1, 3);
	define_arcs(1, 21, 3);
	define_arcs(21, 20, 3);
	define_arcs(20, 19, 3);
	G.arcnum = 27;
}

void print_admin()
{
	system("cls"); //清屏 
	int choose;
	while (1)
	{
		cout << "           &欢迎使用地铁查询系统&           " << endl;
		cout << "********************************************" << endl;
		cout << "*            1.显示所有站点信息            *" << endl;
		cout << "*------------------------------------------*" << endl;
		cout << "*        2.显示站点之间的地铁路线号        *" << endl;
		cout << "*------------------------------------------*" << endl;
		cout << "*              3.新增站点信息              *" << endl;
		cout << "*------------------------------------------*" << endl;
		cout << "*              4.删除站点信息              *" << endl;
		cout << "*------------------------------------------*" << endl;
		cout << "*              5.修改站点名称              *" << endl;
		cout << "*------------------------------------------*" << endl;
		cout << "*            6.手动增加地铁路线            *" << endl;
		cout << "*------------------------------------------*" << endl;
		cout << "*            7.调整站点间的线路            *" << endl;
		cout << "*------------------------------------------*" << endl;
		cout << "*           8.搜索两站之间的路线           *" << endl;
		cout << "*------------------------------------------*" << endl;
		cout << "*                9.退出程序                *" << endl;
		cout << "*------------------------------------------*" << endl;
		cout << "*                  请选择                  *" << endl;
		cout << "********************************************" << endl;
		cin >> choose;
		switch (choose)
		{
		case 1:print_v(); break;
		case 2:print_arcs(); break;
		case 3:add_v(); break;
		case 4:delete_v(); break;
		case 5:modify_v(); break;
		case 6:add_line(); break;
		case 7:modify_adj(); break;
		case 8:direct_path(); break;
		case 9:
		{
			cout << "退出程序"; exit(1);
		}
		default:cout << "您的选择有误！" << endl;
		}
		system("pause");//程序暂停 
		system("cls"); //清屏 
	}
}

void print_user()
{
	int choose;
	while (1)
	{
		system("cls"); //清屏 
		cout << "           &欢迎使用地铁查询系统&           " << endl;
		cout << "********************************************" << endl;
		cout << "*            1.显示所有站点信息            *" << endl;
		cout << "*------------------------------------------*" << endl;
		cout << "*        2.显示站点之间的地铁路线号        *" << endl;
		cout << "*------------------------------------------*" << endl;
		cout << "*           3.搜索两站之间的路线           *" << endl;
		cout << "*------------------------------------------*" << endl;
		cout << "*                4.退出程序                *" << endl;
		cout << "*------------------------------------------*" << endl;
		cout << "*                  请选择                  *" << endl;
		cout << "********************************************" << endl;
		cin >> choose;
		switch (choose)
		{
		case 1:print_v(); break;
		case 2:print_arcs(); break;
		case 3:direct_path(); break;
		case 4:
		{
			cout << "退出程序"; exit(1);
		}
		default:cout << "您的选择有误！请输入数字1-4！" << endl;
		}
		system("pause");
		system("cls");
	}
}

int main()
{
	int choose;
	string pwd_correct = "123456";
	string pwd_input;
	createG();
	while (1)
	{
		cout << "           &欢迎使用地铁查询系统&           " << endl;
		cout << "********************************************" << endl;
		cout << "*             &请选择您的身份&             *" << endl;
		cout << "*------------------------------------------*" << endl;
		cout << "*                 1.用户                   *" << endl;
		cout << "*------------------------------------------*" << endl;
		cout << "*                2.管理员                  *" << endl;
		cout << "*------------------------------------------*" << endl;
		cin >> choose;
		if (choose == 1)
			print_user();
		else if (choose == 2)
		{
			cout << "*            请输入管理员密码            *" << endl;
			cin >> pwd_input;
			if (pwd_correct == pwd_input)
				print_admin();
			else
			{
				cout << "*      密码错误，即将退出程序     *" << endl;
				Sleep(2000); exit(1);
			}
		}
		else
		{
			cout << "*         输入有误，请重新输入        *" << endl;
			Sleep(2000);
			system("cls");
			continue;
		}
	}
	return 0;
}