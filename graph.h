#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <stack>
#ifndef graph_H
#define graph_H

using namespace std;

//邻接矩阵的存储结构
typedef struct cell
{
	int adj[100];//经过该的地铁路线号
	int adj_loc;  //记录每个站点所经过的地铁线路数，在程序中用作标记量
}matrix[100][100];

//无向带权图的存储结构
typedef struct map
{
	string vex[100] = { "迈皋桥","南京站","鼓楼","新街口","安德门","南京南站","小龙湾","天印大道","中国药科大学","经天路","南大仙林校区","金马路","孝陵卫","苜蓿园","大行宫","汉中门","奥体东","油坊桥","鱼嘴","林场","泰冯路","上元门","雨花门","九龙湖","东大九龙湖校区","秣周东路" };
	//顶点字符串数组
	matrix arcs;             //邻接矩阵
	int vexnum, arcnum;     //顶点数量和边的数量
}graph;

typedef struct road {
	int vex[100]; //站点顺序 
	int vex_loc;  //站点的总数 
}station;

//对图进行运用迪杰斯特拉算法完成换乘搜索
//全局变量的定义
#define MAXROAD 100 //路程最大值

void Indirect_path(string str1, string str2);
void djc(int v0);
void direct_path();

int vex_repeat(string& v);
int locate_v(string v);
int locate_subway(int j);

void print_v();
void print_arcs();
void print_user();
void print_admin();

void define_arcs(int i, int j, int road);
void createG();
void delete_v();
void add_v();
void add_line();
void modify_v();
int modify_adj();
#endif