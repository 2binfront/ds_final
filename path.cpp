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

//��ֱ����·
void direct_path()
{
	//������ά����������й�����·
	//string str[3][12];//string str[road_a][G.vexnum];
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
	int i = 0;
	int j = 0;
	//string str1;
	string str2;   //��ʼվ
	string str3;   //�յ�վ
	int loca1, loca2, loca3, loca4;
	bool flag1, flag2;
	bool flag = false;
	cout << "-------����·��ѡ��------" << endl;
	cout << "������������ʼվ��";
	cin >> str2;
	cout << "�����������յ�վ��";
	cin >> str3;

	//����ֱ����·������¼	
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

		if ((flag1 == true) && (flag2 == true))//��ʾֱ����·���ҳɹ�
		{
			flag = true;
			cout << "����վ��֮�����ֱ����·" << endl;
			cout << "����·��Ϊ  " << i + 1 << "  �Ź�����·" << endl;
		}
	}
	if (flag == false)
		cout << "����վ��֮��û��ֱ��·��! Ϊ����ʾ���˹���·��!" << endl;
	Indirect_path(str2, str3);
	//return flag;     //��falg = false����ʾû��ֱ��·��
}

//���Ż���·�ߣ��Ͻ�˹�����㷨�� 
void djc(int v0)
{
	int v, w;
	for (v = 0; v < G.vexnum; v++)
	{
		visit[v] = false;
		if (G.arcs[v0][v].adj_loc <= 0) D[v] = INFMAX;  //��D�����ʼ�� �����·�̼�¼���飩 
		else D[v] = 1;//v��v0������λ����ͬ��·
		/*for (w = 0; w < G.vexnum; w++)*/
		P[v].vex_loc = 0;   //��P�����ʼ�������˼�¼���飩 
		if (D[v] < INFMAX)
		{
			P[v].vex[++P[v].vex_loc] = v0; //v0��v������ʱ��¼·��v0->v���Һ���P[v].vex[0]
			P[v].vex[++P[v].vex_loc] = v;
		}
	}
	D[v0] = 0;
	visit[v0] = true;                    //v0Ϊ��� 
	int i, min;                                    //minΪ����δ����վ������·�� 
	for (i = 1; i < G.vexnum; i++)                   //������ʼվ������վ������·�� 
	{
		min = INFMAX;
		for (w = 0; w < G.vexnum; w++)//�����ҵ�D[]�е����·�������վ��v
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
				P[w] = P[v];//���µ�w�����·������һ��������v�����Ҽ̳е�v�����·����Ϣ
				P[w].vex[++P[w].vex_loc] = w;
			}
		}
	}
}

//���˳�����·	
void Indirect_path(string str1, string str2)

{
	int i;
	int loc1, loc2;
	//string str1, str2;
	cout << "���˹���·����ʾ��" << endl;
	//cout << "��������ʼվ�㣺";
	//cin >> str1;
	//cout << "�������յ�վ��";
	//cin >> str2;
	loc1 = Locate_vex(str1);
	loc2 = Locate_vex(str2);
	djc(loc1);
	for (i = 2; i <= P[loc2].vex_loc; i++)
	{
		cout << "ǰ��վ��" << G.vex[P[loc2].vex[i]];
		cout << "     ����·�ߺ�Ϊ" << G.arcs[P[loc2].vex[i - 1]][P[loc2].vex[i]].adj[0] << "�Ź���·��" << endl;
	}
	cout << endl;

}