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

//��ֱ����·
void direct_path()
{
	//������ά����������е�����·
	//string str[3][12];//string str[subway_num][G.vexnum];
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

	//���	��ʼվ�㣺str2	�յ㣺str3
	ofstream myout("��������.txt", ios::out | ios::app);
	if (myout.is_open())
	{
		myout << "��ʼվ: " << str2 << endl;
		myout << "�յ�վ: " << str3 << "\n" << endl;
		myout.close();
	}

	//����ֱ����·������¼	
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
		if ((flag1 == true) && (flag2 == true))//��ʾֱ����·���ҳɹ�
		{
			flag = true;
			cout << "����վ��֮�����ֱ����·" << endl;
			cout << "����·��Ϊ  " << i + 1 << "  �ŵ�����·" << endl;
		}
	}
	if (flag == false)
	{
		cout << "����վ��֮��û��ֱ��·��! Ϊ����ʾ���˵���·��!" << endl;
		Indirect_path(str2, str3);
	}
	//return flag;     //��flag = false����ʾû��ֱ��·��
}

//���Ż���·�ߣ��Ͻ�˹�����㷨�� 
void djc(int v0)
{
	int v, u;
	for (v = 0; v < G.vexnum; v++)
	{
		visit[v] = false;
		if (G.arcs[v0][v].adj_loc <= 0)
		{
			min_length[v] = MAXROAD;
		}  //��min_length�����ʼ�� �����·�̼�¼���飩 
		else {
			min_length[v] = 1;
		}//v��v0������λ����ͬ��·
		/*for (u = 0; u < G.vexnum; u++)*/
		S[v].vex_loc = 0;   //��S�����ʼ�������˼�¼���飩 
		if (min_length[v] < MAXROAD)
		{
			S[v].vex[++S[v].vex_loc] = v0; //v0��v������ʱ��¼·��v0->v���Һ���S[v].vex[0]
			S[v].vex[++S[v].vex_loc] = v;
		}
	}
	min_length[v0] = 0;
	visit[v0] = true;                    //v0Ϊ��� 
	int i, min;                                    //minΪ����δ����վ������·�� 
	for (i = 1; i < G.vexnum; i++)                   //������ʼվ������վ������·�� 
	{
		min = MAXROAD;
		for (u = 0; u < G.vexnum; u++)//�����ҵ�min_length[]�е����·�������վ��v
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
				S[u] = S[v];//���µ�u�����·������һ��������v�����Ҽ̳е�v�����·����Ϣ
				S[u].vex[++S[u].vex_loc] = u;
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
	cout << "���˵���·����ʾ��" << endl;
	loc1 = locate_v(str1);
	loc2 = locate_v(str2);
	djc(loc1);
	for (i = 2; i <= S[loc2].vex_loc; i++)
	{
		cout << "ǰ��վ��" << G.vex[S[loc2].vex[i]];
		cout << "     ����·�ߺ�Ϊ" << G.arcs[S[loc2].vex[i - 1]][S[loc2].vex[i]].adj[0] << "�ŵ���·��" << endl;
	}
	cout << endl;

}