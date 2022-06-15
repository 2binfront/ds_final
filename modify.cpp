#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <stack>
#include"graph.h"

using namespace std;

extern graph G;
extern int subway[10];//记录地铁路线号 
extern int subway_num;//记录地铁路线数 
extern bool visit[100];   //标志站点有没有被访问过	
extern station S[100];        //换乘站点记录 
extern int min_length[100];    //所在站点到其他站点的最短路程 

//手动录入新的站点
void add_v()//手动输入站点 
{
	string str, str1, str2;
	int num, j;
	int station, station1, station2;
	while (1)
	{
		cout << "请输入您要增加的站点:" << endl;
		cin >> str;
		station = locate_v(str);
		if (station != -1)
		{
			cout << "该站点已存在" << endl;
			continue;
		}
		else break;
	}
	cout << "请您输入该站点属于地铁几号线" << endl;
	cin >> num;
	j = locate_subway(num);
	if (j == -1)//新加路线号，更新全局变量 
	{
		subway[subway_num] = num;
		num++;
	}
	while (1)
	{
		cout << "该站点的前一站是：" << endl;
		cin >> str1;
		station1 = locate_v(str1);
		if (station1 == -1)
		{
			cout << "该站点不存在，请重新输入" << endl;
			continue;
		}
		cout << "该站点的后一站是：" << endl;
		cin >> str2;
		station2 = locate_v(str2);
		if (station2 == -1)
		{
			cout << "该站点不存在，请重新输入" << endl;
			continue;
		}
		if (station2 != -1 && station1 != -1)break;
	}
	G.vex[G.vexnum] = str;           //将该站点的信息增加到vex的数组中
	//对新增线路进行记录
	G.arcs[station1][G.vexnum].adj[G.arcs[station1][G.vexnum].adj_loc++] = num;
	G.arcs[G.vexnum][station1].adj[G.arcs[G.vexnum][station1].adj_loc++] = num;
	G.arcs[station2][G.vexnum].adj[G.arcs[station2][G.vexnum].adj_loc++] = num;
	G.arcs[G.vexnum][station2].adj[G.arcs[G.vexnum][station2].adj_loc++] = num;
	G.vexnum++;                      //站的数量增加
	cout << "该站点录入成功！" << endl;
}

//删除现存的站点
void delete_v()
{
	string str;
	int station = -1;
	cout << "请您输入要删除的站点名称：" << endl;
	cin >> str;
	station = locate_v(str);
	if (station == -1)
	{
		cout << "删除失败！该站点不存在！" << endl;
	}
	if (station != 0)
	{
		G.vex[station] = "0";            //将该站点名称清空
		for (int i = 0; i < G.vexnum; i++)
		{
			for (int j = 0; j < 100; j++)
			{
				G.arcs[station][i].adj[j] = 0;
				G.arcs[i][station].adj[j] = 0;  //将存储站点权值的数组清空
			}
			G.arcs[station][i].adj_loc = 0;
			G.arcs[i][station].adj_loc = 0;     //将表示该站点的权值数量的变量清零
		}
		//G.vexnum--;实际上没有完全删除，保留了数组里的存储空间
		cout << "删除站点成功！" << endl;
	}
}


//修改站点名称
void modify_v()
{
	string str;
	string str1;
	int station = -1;
	cout << "请输入您要修改的站点名称 : " << endl;
	cin >> str;
	station = locate_v(str);
	if (station == -1)
	{
		cout << "修改站点失败!   " << "该站点不存在！ " << endl;
	}
	if (station != -1)
	{
		cout << "请输入修改后的名称：" << endl;
		cin >> str1;
		G.vex[station] = str1;
		cout << "站点修改成功！" << endl;
	}

}
void add_arcs(int i, int j, int road)
{
	G.arcs[i][j].adj[G.arcs[i][j].adj_loc] = road;
	G.arcs[i][j].adj_loc++;
}
//管理员手动增加新的地铁线路
void add_line()
{
	string st1, st2;
	int linenum;
	int station1, station2;
	cout << "请您输入要在哪两个站点之间增加线路：" << endl;
	cout << "请您先输入第一个站点" << endl;
	cin >> st1;
	cout << "请您再输入第二个站点" << endl;
	cin >> st2;
	cout << "请您输入要增加的线路号数：" << endl;
	cin >> linenum;
	station1 = locate_v(st1);
	station2 = locate_v(st2);
	add_arcs(station1, station2, linenum);
	add_arcs(station2, station1, linenum);
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
	lint1 = locate_v(str1);
	lint2 = locate_v(str2);               //找到这两个站点在矩阵中的位置
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
