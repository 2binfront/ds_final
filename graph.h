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
typedef struct Cell
{
	int adj[100];  //存储权值		？不是权值，是经过该顶点的公交路线号

  //记录每个站点所经过的公交线路数，在程序中用作标记量
	int adj_loc;
}cell[500][500];

//无向带权图的存储结构
typedef struct map
{
	string vex[500] = { "徐工院","汉源国际华城","丽水路","龙湖之家西门","徐州市档案馆","绿地商务城","海顿广场","公园首府","元和路","汉风路","普陀路","彭祖大道" };
	//顶点字符串数组
	cell arcs;             //邻接矩阵
	int vexnum, arcnum;     //顶点数量和边的数量
}graph;

typedef struct load {
	int vex[500]; //站点顺序 
	int vex_loc;  //站点的总数 
}p;


//对图进行运用迪杰斯特拉算法完成换乘搜索
//全局变量的定义
#define INFMAX 500 //路程最大值



void Indirect_path(string str1, string str2);
void djc(int v0);
void direct_path();

int vex_repeat(string& point);
int Locate_vex(string v);
int Locate_road(int j);

void print_vex();
void print_arcs();

void Create_vex();
void Creat_arcs();
void Creat_graph();


void dele_vex();
void add_vex();
void add_line();
void modify_vex();
int modify_adj();


#endif