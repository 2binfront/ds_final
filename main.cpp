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
int road[50] = { 1,2,3 };//记录公交路线号 
int road_a = 3;//记录公交路线数 
bool visit[500];   //标志站点有没有被访问过	
p P[500];       //换乘站点记录 
int D[500];    //所在站点到其他站点的最短路程 

//初始化图的顶点数组
void Create_vex()
{
	for (int k = 12; k < 500; k++)
	{
		G.vex[k] = "0";
	}
	G.vexnum = 12;

}

//建立邻接矩阵的存储结构
void Creat_arcs()
{
	int sum_arcs = 0;  //记录边的总数
	//对邻接矩阵进行初始化
	for (int i = 0; i < 500; i++)
	{
		for (int j = 0; j < 500; j++)
		{
			G.arcs[i][j].adj_loc = 0;
			for (int c = 0; c < 100; c++)
			{
				G.arcs[i][j].adj[c] = 0;
			}
		}
	}
	//1号线 
	G.arcs[1][2].adj[G.arcs[1][2].adj_loc++] = 1;
	G.arcs[2][3].adj[G.arcs[2][3].adj_loc++] = 1;
	G.arcs[3][4].adj[G.arcs[3][4].adj_loc++] = 1;
	G.arcs[4][5].adj[G.arcs[4][5].adj_loc++] = 1;
	G.arcs[5][6].adj[G.arcs[5][6].adj_loc++] = 1;

	G.arcs[6][5].adj[G.arcs[6][5].adj_loc++] = 1;
	G.arcs[5][4].adj[G.arcs[5][4].adj_loc++] = 1;
	G.arcs[4][3].adj[G.arcs[4][3].adj_loc++] = 1;
	G.arcs[3][2].adj[G.arcs[3][2].adj_loc++] = 1;
	G.arcs[2][1].adj[G.arcs[2][1].adj_loc++] = 1;
	//2号线 
	G.arcs[1][7].adj[G.arcs[1][7].adj_loc++] = 2;
	G.arcs[7][3].adj[G.arcs[7][3].adj_loc++] = 2;
	G.arcs[3][4].adj[G.arcs[3][4].adj_loc++] = 2;
	G.arcs[4][10].adj[G.arcs[4][10].adj_loc++] = 2;
	G.arcs[10][11].adj[G.arcs[10][11].adj_loc++] = 2;

	G.arcs[11][10].adj[G.arcs[11][10].adj_loc++] = 2;
	G.arcs[10][4].adj[G.arcs[10][4].adj_loc++] = 2;
	G.arcs[4][3].adj[G.arcs[4][3].adj_loc++] = 2;
	G.arcs[3][7].adj[G.arcs[3][7].adj_loc++] = 2;
	G.arcs[7][1].adj[G.arcs[7][1].adj_loc++] = 2;
	//3号线 
	G.arcs[0][6].adj[G.arcs[0][6].adj_loc++] = 3;
	G.arcs[6][8].adj[G.arcs[6][8].adj_loc++] = 3;
	G.arcs[8][10].adj[G.arcs[8][10].adj_loc++] = 3;
	G.arcs[10][1].adj[G.arcs[10][1].adj_loc++] = 3;
	G.arcs[1][10].adj[G.arcs[1][10].adj_loc++] = 3;
	G.arcs[10][8].adj[G.arcs[10][8].adj_loc++] = 3;
	G.arcs[8][6].adj[G.arcs[8][6].adj_loc++] = 3;
	G.arcs[6][0].adj[G.arcs[6][0].adj_loc++] = 3;
	G.arcnum = 14;
}

//建立图的存储结构
void Creat_graph()
{
	Create_vex();
	Creat_arcs();
}

void print_admin()
{
	system("cls"); //清屏 
	int choose;
	while (1)
	{
		cout << "           &欢迎使用公交查询系统&           " << endl;
		cout << "********************************************" << endl;
		cout << "*            1.显示所有站点信息            *" << endl;
		cout << "*------------------------------------------*" << endl;
		cout << "*        2.显示站点之间的公交路线号        *" << endl;
		cout << "*------------------------------------------*" << endl;
		cout << "*              3.新增站点信息              *" << endl;
		cout << "*------------------------------------------*" << endl;
		cout << "*              4.删除站点信息              *" << endl;
		cout << "*------------------------------------------*" << endl;
		cout << "*              5.修改站点名称              *" << endl;
		cout << "*------------------------------------------*" << endl;
		cout << "*            6.手动增加公交路线            *" << endl;
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
		case 1:print_vex(); break;
		case 2:print_arcs(); break;
		case 3:add_vex(); break;
		case 4:dele_vex(); break;
		case 5:modify_vex(); break;
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
		cout << "           &欢迎使用公交查询系统&           " << endl;
		cout << "********************************************" << endl;
		cout << "*            1.显示所有站点信息            *" << endl;
		cout << "*------------------------------------------*" << endl;
		cout << "*        2.显示站点之间的公交路线号        *" << endl;
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
		case 1:print_vex(); break;
		case 2:print_arcs(); break;
		case 3:direct_path(); break;
		case 4:
		{
			cout << "退出程序"; exit(1);
		}
		default:cout << "您的选择有误！" << endl;
		}
		system("pause");//程序暂停 
		system("cls"); //清屏 
	}
}

int main()
{
	int choose;
	string pwd_correct="123456";
	string pwd_input;
	Creat_graph();
	while (1)
	{
		cout << "           &欢迎使用公交查询系统&           " << endl;
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
			Sleep(1500);
			system("cls"); //清屏 
			continue;
		}
	}
	return 0;
}