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

//求直接线路
void direct_path()
{
	//建立二维数组求出所有公交线路
	//string str[3][12];//string str[road_a][G.vexnum];
	static string** str = new string * [road_a];
	for (int i = 0; i < road_a; i++)
	{
		str[i] = new string[G.vexnum];
	}
	for (int k = 0; k < road_a; k++)//线路号
	{
		int a = 0;//某路线上的顶点排序下标
		cout << k + 1 << "号线：";
		for (int i = 1; i < G.vexnum; i++)//遍历顶点
		{
			for (int j = 0; j < i; j++)//i之前的顶点
			{
				for (int c = 0; c < G.arcs[i][j].adj_loc; c++)//ij边经过的公交线路数量，矩阵的下三角
				{
					if (G.arcs[i][j].adj[c] == road[k])//同一线路
					{
						int flag = 0;
						for (int h = 0; h < a; h++)
						{
							if (G.vex[i] == str[k][h])
							{
								flag += 1;
							}
							if (G.vex[j] == str[k][h])
							{
								flag += 2;
							}
						}
						if (!flag)
						{
							str[k][a] = G.vex[i];
							cout << str[k][a] << " ";
							a++;
							str[k][a] = G.vex[j];
							cout << str[k][a] << " ";
							a++;
						}
						else if (flag == 1)
						{
							str[k][a] = G.vex[j];
							cout << str[k][a] << " ";
							a++;
						}
						else if (flag == 2)
						{
							str[k][a] = G.vex[i];
							cout << str[k][a] << " ";
							a++;
						}
						else if (flag == 3)
						{
							continue;
						}
					}
				}
			}
		}
		cout << endl;
		str[k][a] = "0";
	}
	int i = 0;
	int j = 0;
	//string str1;
	string str2;   //起始站
	string str3;   //终点站
	int loca1, loca2, loca3, loca4;
	bool flag1, flag2;
	bool flag = false;
	cout << "-------最优路线选择------" << endl;
	cout << "请输入您的起始站：";
	cin >> str2;
	cout << "请输入您的终点站：";
	cin >> str3;

	//查找直达线路并作记录	
	for (i = 0; i < road_a; i++)
	{
		flag1 = false;
		flag2 = false;
		for (j = 0; j < G.vexnum; j++)
		{
			if (str2 == str[i][j])
			{
				loca1 = i;
				loca2 = j;
				flag1 = true;
			}
			if (str3 == str[i][j])
			{
				loca3 = i;
				loca4 = j;
				flag2 = true;
			}
		}

		if ((flag1 == true) && (flag2 == true))//表示直达线路查找成功
		{
			flag = true;
			cout << "该两站点之间存在直达线路" << endl;
			cout << "该线路号为  " << i + 1 << "  号公交线路" << endl;
		}
	}
	if (flag == false)
		cout << "该两站点之间没有直达路线! 为您显示换乘公交路线!" << endl;
	Indirect_path(str2, str3);
	//return flag;     //若falg = false，表示没有直达路线
}

//最优换乘路线（迪杰斯特拉算法） 
void djc(int v0)
{
	int v, w;
	for (v = 0; v < G.vexnum; v++)
	{
		visit[v] = false;
		if (G.arcs[v0][v].adj_loc <= 0) D[v] = INFMAX;  //对D数组初始化 （最短路程记录数组） 
		else D[v] = 1;//v与v0相邻且位于相同线路
		/*for (w = 0; w < G.vexnum; w++)*/
		P[v].vex_loc = 0;   //对P数组初始化（换乘记录数组） 
		if (D[v] < INFMAX)
		{
			P[v].vex[++P[v].vex_loc] = v0; //v0到v点相邻时记录路径v0->v，且忽略P[v].vex[0]
			P[v].vex[++P[v].vex_loc] = v;
		}
	}
	D[v0] = 0;
	visit[v0] = true;                    //v0为起点 
	int i, min;                                    //min为到达未访问站点的最短路程 
	for (i = 1; i < G.vexnum; i++)                   //计算起始站到所有站点的最短路径 
	{
		min = INFMAX;
		for (w = 0; w < G.vexnum; w++)//首先找到D[]中的最短路径导向的站点v
		{
			if (!visit[w])
				if (D[w] < min) { v = w; min = D[w]; }
		}
		visit[v] = true;
		for (w = 0; w < G.vexnum; w++)
		{
			if (!visit[w] && G.arcs[v][w].adj_loc > 0 && min + 1 < D[w])
			{
				D[w] = D[v] + 1;
				P[w] = P[v];//更新到w的最短路径的上一个顶点是v，并且继承到v的最短路径信息
				P[w].vex[++P[w].vex_loc] = w;
			}
		}
	}
}

//换乘车的线路	
void Indirect_path(string str1, string str2)

{
	int i;
	int loc1, loc2;
	//string str1, str2;
	cout << "换乘公交路线显示：" << endl;
	//cout << "请输入起始站点：";
	//cin >> str1;
	//cout << "请输入终点站：";
	//cin >> str2;
	loc1 = Locate_vex(str1);
	loc2 = Locate_vex(str2);
	djc(loc1);
	for (i = 2; i <= P[loc2].vex_loc; i++)
	{
		cout << "前往站点" << G.vex[P[loc2].vex[i]];
		cout << "     公交路线号为" << G.arcs[P[loc2].vex[i - 1]][P[loc2].vex[i]].adj[0] << "号公交路线" << endl;
	}
	cout << endl;

}