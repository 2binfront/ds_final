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

//判断顶点是否重复
int vex_repeat(string& point)
{
	int i = 0;
	for (i = 0; i < 500; i++)
	{
		if (point == G.vex[i])   //vex顶点 
			return 0;
	}
	return 1;
}


//确定某个顶点 v 在图 G 中的位置
int Locate_vex(string v)
{
	int i;
	for (i = 0; i < 500; i++)
	{
		if (G.vex[i] == v)//string定义中的汉字可以直接比较是否相等 
			return i;
	}
	return -1;
}


//输出图G的顶点
void print_vex()//显示站点 
{
	for (int i = 0; i < G.vexnum; i++)
	{
		cout << i << ":" << G.vex[i] << endl;
	}
}


//输出图G的邻接矩阵
void print_arcs() {
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
}

//判断公交号是否已存在 
int Locate_road(int j)
{
	for (int i = 0; i < road_a; i++)
	{
		if (road[i] == j)return 1;
	}
	return -1;
}
