#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <stack>
#include"graph.h"

using namespace std;

extern graph G;
extern int road[50];//��¼����·�ߺ� 
extern int road_a;//��¼����·���� 


extern bool visit[500];   //��־վ����û�б����ʹ�	
extern p P[500];        //����վ���¼  
extern int D[500];    //����վ�㵽����վ������·�� 

//�ж϶����Ƿ��ظ�
int vex_repeat(string& point)
{
	int i = 0;
	for (i = 0; i < 500; i++)
	{
		if (point == G.vex[i])   //vex���� 
			return 0;
	}
	return 1;
}


//ȷ��ĳ������ v ��ͼ G �е�λ��
int Locate_vex(string v)
{
	int i;
	for (i = 0; i < 500; i++)
	{
		if (G.vex[i] == v)//string�����еĺ��ֿ���ֱ�ӱȽ��Ƿ���� 
			return i;
	}
	return -1;
}


//���ͼG�Ķ���
void print_vex()//��ʾվ�� 
{
	for (int i = 0; i < G.vexnum; i++)
	{
		cout << i << ":" << G.vex[i] << endl;
	}
}


//���ͼG���ڽӾ���
void print_arcs() {
	static string** str = new string * [road_a];
	for (int i = 0; i < road_a; i++)
	{
		str[i] = new string[G.vexnum];
	}
	for (int k = 0; k < road_a; k++)//��·��
	{
		int a = 0;//ĳ·���ϵĶ��������±�
		cout << k + 1 << "���ߣ�";
		for (int i = 1; i < G.vexnum; i++)//��������
		{
			for (int j = 0; j < i; j++)//i֮ǰ�Ķ���
			{
				for (int c = 0; c < G.arcs[i][j].adj_loc; c++)//ij�߾����Ĺ�����·�����������������
				{
					if (G.arcs[i][j].adj[c] == road[k])//ͬһ��·
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

//�жϹ������Ƿ��Ѵ��� 
int Locate_road(int j)
{
	for (int i = 0; i < road_a; i++)
	{
		if (road[i] == j)return 1;
	}
	return -1;
}
