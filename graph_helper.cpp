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

//判断顶点是否重复
int vex_repeat(string& v)
{
	int i = 0;
	for (i = 0; i < 100; i++)
	{
		if (v == G.vex[i])   //vex顶点 
			return 0;
	}
	return 1;
}

//确定某个顶点 v 在图 G 中的位置
int locate_v(string v)
{
	int i;
	for (i = 0; i < 100; i++)
	{
		if (G.vex[i] == v)//string定义中的汉字可以直接比较是否相等 
			return i;
	}
	return -1;
}

//输出图G的顶点
void print_v()//显示站点 
{
	for (int i = 0; i < G.vexnum; i++)
	{
		cout << i << ":" << G.vex[i] << endl;
	}
}


//输出图G的邻接矩阵
void print_arcs() {
	static string** str = new string * [subway_num];
	for (int i = 0; i < subway_num; i++)
	{
		str[i] = new string[G.vexnum];
	}
	for (int k = 0; k < subway_num; k++)//线路号
	{
		int a = 0;//某路线上的顶点排序下标
		cout << k + 1 << "号线：";
		for (int i = 1; i < G.vexnum; i++)//遍历顶点
		{
			for (int j = 0; j < i; j++)//i之前的顶点
			{
				for (int count = 0; count < G.arcs[i][j].adj_loc; count++)//ij边经过的地铁线路数量，矩阵的下三角
				{
					if (G.arcs[i][j].adj[count] == subway[k])//同一线路
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
}

//判断地铁号是否已存在 
int locate_subway(int t)
{
	for (int i = 0; i < subway_num; i++)
	{
		if (subway[i] == t)return 1;
	}
	return -1;
}
