#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <stack>
#include"graph.h"

using namespace std;

extern graph G;
extern int subway[10];//��¼����·�ߺ� 
extern int subway_num;//��¼����·���� 
extern bool visit[100];   //��־վ����û�б����ʹ�	
extern station S[100];        //����վ���¼  
extern int min_length[100];    //����վ�㵽����վ������·�� 

//�ж϶����Ƿ��ظ�
int vex_repeat(string& v)
{
	int i = 0;
	for (i = 0; i < 100; i++)
	{
		if (v == G.vex[i])   //vex���� 
			return 0;
	}
	return 1;
}

//ȷ��ĳ������ v ��ͼ G �е�λ��
int locate_v(string v)
{
	int i;
	for (i = 0; i < 100; i++)
	{
		if (G.vex[i] == v)//string�����еĺ��ֿ���ֱ�ӱȽ��Ƿ���� 
			return i;
	}
	return -1;
}

//���ͼG�Ķ���
void print_v()//��ʾվ�� 
{
	for (int i = 0; i < G.vexnum; i++)
	{
		cout << i << ":" << G.vex[i] << endl;
	}
}


//���ͼG���ڽӾ���
void print_arcs() {
	static string** str = new string * [subway_num];
	for (int i = 0; i < subway_num; i++)
	{
		str[i] = new string[G.vexnum];
	}
	for (int k = 0; k < subway_num; k++)//��·��
	{
		int a = 0;//ĳ·���ϵĶ��������±�
		cout << k + 1 << "���ߣ�";
		for (int i = 1; i < G.vexnum; i++)//��������
		{
			for (int j = 0; j < i; j++)//i֮ǰ�Ķ���
			{
				for (int count = 0; count < G.arcs[i][j].adj_loc; count++)//ij�߾����ĵ�����·�����������������
				{
					if (G.arcs[i][j].adj[count] == subway[k])//ͬһ��·
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

//�жϵ������Ƿ��Ѵ��� 
int locate_subway(int t)
{
	for (int i = 0; i < subway_num; i++)
	{
		if (subway[i] == t)return 1;
	}
	return -1;
}
