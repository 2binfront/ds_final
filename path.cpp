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

//求直接线路
void direct_path()
{
	//建立二维数组求出所有地铁线路
	//string str[3][12];//string str[subway_num][G.vexnum];
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

	//输出	起始站点：str2	终点：str3
	ofstream myout("地铁导航.txt", ios::out | ios::app);
	if (myout.is_open())
	{
		myout << "起始站: " << str2 << endl;
		myout << "终点站: " << str3 << "\n" << endl;
		myout.close();
	}

	//查找直达线路并作记录	
	for (i = 0; i < subway_num; i++)
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
			cout << "该线路号为  " << i + 1 << "  号地铁线路" << endl;
		}
	}
	if (flag == false)
	{
		cout << "该两站点之间没有直达路线! 为您显示换乘地铁路线!" << endl;
		Indirect_path(str2, str3);
	}
	//return flag;     //若flag = false，表示没有直达路线
}

//最优换乘路线（迪杰斯特拉算法） 
void djc(int v0)
{
	int v, u;
	for (v = 0; v < G.vexnum; v++)
	{
		visit[v] = false;
		if (G.arcs[v0][v].adj_loc <= 0)
		{
			min_length[v] = MAXROAD;
		}  //对min_length数组初始化 （最短路程记录数组） 
		else {
			min_length[v] = 1;
		}//v与v0相邻且位于相同线路
		/*for (u = 0; u < G.vexnum; u++)*/
		S[v].vex_loc = 0;   //对S数组初始化（换乘记录数组） 
		if (min_length[v] < MAXROAD)
		{
			S[v].vex[++S[v].vex_loc] = v0; //v0到v点相邻时记录路径v0->v，且忽略S[v].vex[0]
			S[v].vex[++S[v].vex_loc] = v;
		}
	}
	min_length[v0] = 0;
	visit[v0] = true;                    //v0为起点 
	int i, min;                                    //min为到达未访问站点的最短路程 
	for (i = 1; i < G.vexnum; i++)                   //计算起始站到所有站点的最短路径 
	{
		min = MAXROAD;
		for (u = 0; u < G.vexnum; u++)//首先找到min_length[]中的最短路径导向的站点v
		{
			if (!visit[u])
				if (min_length[u] < min) { v = u; min = min_length[u]; }
		}
		visit[v] = true;
		for (u = 0; u < G.vexnum; u++)
		{
			if (!visit[u] && G.arcs[v][u].adj_loc > 0 && min + 1 < min_length[u])
			{
				min_length[u] = min_length[v] + 1;
				S[u] = S[v];//更新到u的最短路径的上一个顶点是v，并且继承到v的最短路径信息
				S[u].vex[++S[u].vex_loc] = u;
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
	cout << "换乘地铁路线显示：" << endl;
	loc1 = locate_v(str1);
	loc2 = locate_v(str2);
	djc(loc1);
	for (i = 2; i <= S[loc2].vex_loc; i++)
	{
		cout << "前往站点" << G.vex[S[loc2].vex[i]];
		cout << "     地铁路线号为" << G.arcs[S[loc2].vex[i - 1]][S[loc2].vex[i]].adj[0] << "号地铁路线" << endl;
	}
	cout << endl;

}