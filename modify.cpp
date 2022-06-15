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

//�ֶ�¼���µ�վ��
void add_v()//�ֶ�����վ�� 
{
	string str, str1, str2;
	int num, j;
	int station, station1, station2;
	while (1)
	{
		cout << "��������Ҫ���ӵ�վ��:" << endl;
		cin >> str;
		station = locate_v(str);
		if (station != -1)
		{
			cout << "��վ���Ѵ���" << endl;
			continue;
		}
		else break;
	}
	cout << "���������վ�����ڵ���������" << endl;
	cin >> num;
	j = locate_subway(num);
	if (j == -1)//�¼�·�ߺţ�����ȫ�ֱ��� 
	{
		subway[subway_num] = num;
		num++;
	}
	while (1)
	{
		cout << "��վ���ǰһվ�ǣ�" << endl;
		cin >> str1;
		station1 = locate_v(str1);
		if (station1 == -1)
		{
			cout << "��վ�㲻���ڣ�����������" << endl;
			continue;
		}
		cout << "��վ��ĺ�һվ�ǣ�" << endl;
		cin >> str2;
		station2 = locate_v(str2);
		if (station2 == -1)
		{
			cout << "��վ�㲻���ڣ�����������" << endl;
			continue;
		}
		if (station2 != -1 && station1 != -1)break;
	}
	G.vex[G.vexnum] = str;           //����վ�����Ϣ���ӵ�vex��������
	//��������·���м�¼
	G.arcs[station1][G.vexnum].adj[G.arcs[station1][G.vexnum].adj_loc++] = num;
	G.arcs[G.vexnum][station1].adj[G.arcs[G.vexnum][station1].adj_loc++] = num;
	G.arcs[station2][G.vexnum].adj[G.arcs[station2][G.vexnum].adj_loc++] = num;
	G.arcs[G.vexnum][station2].adj[G.arcs[G.vexnum][station2].adj_loc++] = num;
	G.vexnum++;                      //վ����������
	cout << "��վ��¼��ɹ���" << endl;
}

//ɾ���ִ��վ��
void delete_v()
{
	string str;
	int station = -1;
	cout << "��������Ҫɾ����վ�����ƣ�" << endl;
	cin >> str;
	station = locate_v(str);
	if (station == -1)
	{
		cout << "ɾ��ʧ�ܣ���վ�㲻���ڣ�" << endl;
	}
	if (station != 0)
	{
		G.vex[station] = "0";            //����վ���������
		for (int i = 0; i < G.vexnum; i++)
		{
			for (int j = 0; j < 100; j++)
			{
				G.arcs[station][i].adj[j] = 0;
				G.arcs[i][station].adj[j] = 0;  //���洢վ��Ȩֵ���������
			}
			G.arcs[station][i].adj_loc = 0;
			G.arcs[i][station].adj_loc = 0;     //����ʾ��վ���Ȩֵ�����ı�������
		}
		//G.vexnum--;ʵ����û����ȫɾ����������������Ĵ洢�ռ�
		cout << "ɾ��վ��ɹ���" << endl;
	}
}


//�޸�վ������
void modify_v()
{
	string str;
	string str1;
	int station = -1;
	cout << "��������Ҫ�޸ĵ�վ������ : " << endl;
	cin >> str;
	station = locate_v(str);
	if (station == -1)
	{
		cout << "�޸�վ��ʧ��!   " << "��վ�㲻���ڣ� " << endl;
	}
	if (station != -1)
	{
		cout << "�������޸ĺ�����ƣ�" << endl;
		cin >> str1;
		G.vex[station] = str1;
		cout << "վ���޸ĳɹ���" << endl;
	}

}
void add_arcs(int i, int j, int road)
{
	G.arcs[i][j].adj[G.arcs[i][j].adj_loc] = road;
	G.arcs[i][j].adj_loc++;
}
//����Ա�ֶ������µĵ�����·
void add_line()
{
	string st1, st2;
	int linenum;
	int station1, station2;
	cout << "��������Ҫ��������վ��֮��������·��" << endl;
	cout << "�����������һ��վ��" << endl;
	cin >> st1;
	cout << "����������ڶ���վ��" << endl;
	cin >> st2;
	cout << "��������Ҫ���ӵ���·������" << endl;
	cin >> linenum;
	station1 = locate_v(st1);
	station2 = locate_v(st2);
	add_arcs(station1, station2, linenum);
	add_arcs(station2, station1, linenum);
	cout << "��վ��¼��ɹ���" << endl;
}

//����վ������·��
int modify_adj()
{
	string str1, str2;
	int lint1, lint2;
	int line1, line2;
	cout << "��������Ҫ�޸���·�ŵ�վ��" << endl;
	cout << "�������һ��վ�㣺" << endl;
	cin >> str1;
	cout << "������ڶ���վ�㣺" << endl;
	cin >> str2;
	lint1 = locate_v(str1);
	lint2 = locate_v(str2);               //�ҵ�������վ���ھ����е�λ��
	if (G.arcs[lint1][lint2].adj_loc)
		cout << "��վ����Ѿ����ڵ���·���ǣ�";
	int flag = 0;            //��Ϊ��ǣ��������վ֮���Ƿ�����·��ͨ
	int i = 0, j = 0;
	for (int i = 0; i < G.arcs[lint1][lint2].adj_loc; i++)
		//�����վ����Ѿ����ڵ���·��
	{
		cout << G.arcs[lint1][lint2].adj[i] << "�� ";
		flag = 1;
	}
	if (flag == 0)
	{
		cout << "���������վ֮�䲻������·�������ֶ�������·" << endl;
		return 0;
	}
	cout << endl;
	cout << "��������Ҫ�Ķ���վ������·��" << endl;
	cin >> line1;
	cout << "�������޸ĺ����·��" << endl;
	cin >> line2;
	for (int j = 0; j < G.arcs[lint1][lint2].adj_loc; j++)
	{
		if (G.arcs[lint1][lint2].adj[j] == line1)
		{
			G.arcs[lint1][lint2].adj[i] = line2;
			G.arcs[lint2][lint1].adj[i] = line2;
			cout << "վ�����·���޸ĳɹ���" << endl;
			break;
		}
	}
	if (j == G.arcs[lint1][lint2].adj_loc)
		cout << "������������!" << endl;
	return 1;
}
