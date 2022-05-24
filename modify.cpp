#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <stack>
#include"graph.h"

using namespace std;

extern graph G;
extern int road[50];//记录公交路线号 
extern int road_a;//记录公交路线数 


extern bool visit[500];   //标志站点有没有被访问过	
extern p P[500];        //换乘站点记录 
extern int D[500];    //所在站点到其他站点的最短路程 

//手动录入新的站点
void add_vex()//手动输入站点 
{
	string str, str1, str2;
	int num, j;
	int loca1, loca2, loca;
	while (1)
	{
		cout << "请您输入需要增加的新的站点:" << endl;
		cin >> str;
		loca = Locate_vex(str);
		if (loca != -1)
		{
			cout << "该站点已存在，请重新输入" << endl;
			continue;
		}
		else break;
	}

	cout << "请您输入该站点属于几路公交车" << endl;
	cin >> num;
	j = Locate_road(num);
	if (j == -1)//新加路线号，更新全局变量 
	{
		road[road_a] = num;
		num++;
	}
	while (1)
	{
		cout << "请您输入该站点的前一站是：" << endl;
		cin >> str1;
		loca1 = Locate_vex(str1);
		if (loca1 == -1)
		{
			cout << "该站点不存在，请重新输入" << endl;
			continue;
		}
		cout << "请您输入该站点的后一站是：" << endl;
		cin >> str2;
		loca2 = Locate_vex(str2);
		if (loca2 == -1)
		{
			cout << "该站点不存在，请重新输入" << endl;
			continue;
		}
		if (loca2 != -1 && loca1 != -1)break;
	}
	G.vex[G.vexnum] = str;           //将该站点的信息增加到vex的数组中
	//loca1 = Locate_vex(str1);
	//loca2 = Locate_vex(str2);        //定位str1和str2的位置
	//对新增线路进行记录
	G.arcs[loca1][G.vexnum].adj[G.arcs[loca1][G.vexnum].adj_loc++] = num;
	G.arcs[G.vexnum][loca1].adj[G.arcs[G.vexnum][loca1].adj_loc++] = num;
	G.arcs[loca2][G.vexnum].adj[G.arcs[loca2][G.vexnum].adj_loc++] = num;
	G.arcs[G.vexnum][loca2].adj[G.arcs[G.vexnum][loca2].adj_loc++] = num;
	G.vexnum++;                      //站的数量增加
	cout << "该站点录入成功！" << endl;
}

//删除现存的站点
void dele_vex()
{
	string str;
	int locale = -1;
	cout << "请您输入要删除的站点名称：" << endl;
	cin >> str;
	locale = Locate_vex(str);
	if (locale == -1)
	{
		cout << "删除现存站点失败！" << endl << "该站点不存在！" << endl;
	}
	if (locale != 0)
	{
		G.vex[locale] = "0";            //将该站点名称清空
		for (int i = 0; i < G.vexnum; i++)
		{
			for (int j = 0; j < 100; j++)
			{
				G.arcs[locale][i].adj[j] = 0;
				G.arcs[i][locale].adj[j] = 0;  //将存储站点权值的数组清空
			}
			G.arcs[locale][i].adj_loc = 0;
			G.arcs[i][locale].adj_loc = 0;     //将表示该站点的权值数量的变量清零
		}
		//G.vexnum--;实际上没有完全删除，保留了数组里的存储空间
		cout << "删除站点成功！" << endl;
	}
}


//修改站点名称
void modify_vex()
{
	string str;
	string str1;
	int loca = -1;
	cout << "请输入您要修改的站点名称 : " << endl;
	cin >> str;
	loca = Locate_vex(str);
	if (loca == -1)
	{
		cout << "修改站点失败!   " << "该站点不存在！ " << endl;
	}
	if (loca != -1)
	{
		cout << "请输入修改后的名称：" << endl;
		cin >> str1;
		G.vex[loca] = str1;
		cout << "站点修改成功！" << endl;
	}

}

//管理员手动增加新的公交线路
void add_line()
{
	string st1, st2;
	int linenum;
	int locate1, locate2;
	cout << "请您输入要在哪两个站点之间增加线路：" << endl;
	cout << "请您先输入第一个站点" << endl;
	cin >> st1;
	cout << "请您再输入第二个站点" << endl;
	cin >> st2;
	cout << "请您输入要增加的线路号数：" << endl;
	cin >> linenum;
	locate1 = Locate_vex(st1);
	locate2 = Locate_vex(st2);
	G.arcs[locate1][locate2].adj[G.arcs[locate1][locate2].adj_loc++] = linenum;
	G.arcs[locate2][locate1].adj[G.arcs[locate2][locate1].adj_loc++] = linenum;
	cout << "该站点录入成功！" << endl;
}

//调整站点间的线路号
int modify_adj()
{
	string str1, str2;
	int lint1, lint2;
	int line1, line2;
	cout << "请输入想要修改线路号的站点" << endl;
	cout << "请输入第一个站点：" << endl;
	cin >> str1;
	cout << "请输入第二个站点：" << endl;
	cin >> str2;
	lint1 = Locate_vex(str1);
	lint2 = Locate_vex(str2);               //找到这两个站点在矩阵中的位置
	if (G.arcs[lint1][lint2].adj_loc)
		cout << "该站点间已经存在的线路号是：";
	int flag = 0;            //作为标记，检查这两站之间是否有线路相通
	int i = 0, j = 0;
	for (int i = 0; i < G.arcs[lint1][lint2].adj_loc; i++)
		//输出两站点间已经存在的线路号
	{
		cout << G.arcs[lint1][lint2].adj[i] << "号 ";
		flag = 1;
	}
	if (flag == 0)
	{
		cout << "您输入的两站之间不存在线路，请您手动增加线路" << endl;
		return 0;
	}
	cout << endl;
	cout << "请输入想要改动的站点间的线路号" << endl;
	cin >> line1;
	cout << "请输入修改后的线路号" << endl;
	cin >> line2;
	for (int j = 0; j < G.arcs[lint1][lint2].adj_loc; j++)
	{
		if (G.arcs[lint1][lint2].adj[j] == line1)
		{
			G.arcs[lint1][lint2].adj[i] = line2;
			G.arcs[lint2][lint1].adj[i] = line2;
			cout << "站点的线路号修改成功！" << endl;
			break;
		}
	}
	if (j == G.arcs[lint1][lint2].adj_loc)
		cout << "您的输入有误!" << endl;
	return 1;
}
