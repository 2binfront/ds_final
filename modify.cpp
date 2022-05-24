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

//�ֶ�¼���µ�վ��
void add_vex()//�ֶ�����վ�� 
{
	string str, str1, str2;
	int num, j;
	int loca1, loca2, loca;
	while (1)
	{
		cout << "����������Ҫ���ӵ��µ�վ��:" << endl;
		cin >> str;
		loca = Locate_vex(str);
		if (loca != -1)
		{
			cout << "��վ���Ѵ��ڣ�����������" << endl;
			continue;
		}
		else break;
	}

	cout << "���������վ�����ڼ�·������" << endl;
	cin >> num;
	j = Locate_road(num);
	if (j == -1)//�¼�·�ߺţ�����ȫ�ֱ��� 
	{
		road[road_a] = num;
		num++;
	}
	while (1)
	{
		cout << "���������վ���ǰһվ�ǣ�" << endl;
		cin >> str1;
		loca1 = Locate_vex(str1);
		if (loca1 == -1)
		{
			cout << "��վ�㲻���ڣ�����������" << endl;
			continue;
		}
		cout << "���������վ��ĺ�һվ�ǣ�" << endl;
		cin >> str2;
		loca2 = Locate_vex(str2);
		if (loca2 == -1)
		{
			cout << "��վ�㲻���ڣ�����������" << endl;
			continue;
		}
		if (loca2 != -1 && loca1 != -1)break;
	}
	G.vex[G.vexnum] = str;           //����վ�����Ϣ���ӵ�vex��������
	//loca1 = Locate_vex(str1);
	//loca2 = Locate_vex(str2);        //��λstr1��str2��λ��
	//��������·���м�¼
	G.arcs[loca1][G.vexnum].adj[G.arcs[loca1][G.vexnum].adj_loc++] = num;
	G.arcs[G.vexnum][loca1].adj[G.arcs[G.vexnum][loca1].adj_loc++] = num;
	G.arcs[loca2][G.vexnum].adj[G.arcs[loca2][G.vexnum].adj_loc++] = num;
	G.arcs[G.vexnum][loca2].adj[G.arcs[G.vexnum][loca2].adj_loc++] = num;
	G.vexnum++;                      //վ����������
	cout << "��վ��¼��ɹ���" << endl;
}

//ɾ���ִ��վ��
void dele_vex()
{
	string str;
	int locale = -1;
	cout << "��������Ҫɾ����վ�����ƣ�" << endl;
	cin >> str;
	locale = Locate_vex(str);
	if (locale == -1)
	{
		cout << "ɾ���ִ�վ��ʧ�ܣ�" << endl << "��վ�㲻���ڣ�" << endl;
	}
	if (locale != 0)
	{
		G.vex[locale] = "0";            //����վ���������
		for (int i = 0; i < G.vexnum; i++)
		{
			for (int j = 0; j < 100; j++)
			{
				G.arcs[locale][i].adj[j] = 0;
				G.arcs[i][locale].adj[j] = 0;  //���洢վ��Ȩֵ���������
			}
			G.arcs[locale][i].adj_loc = 0;
			G.arcs[i][locale].adj_loc = 0;     //����ʾ��վ���Ȩֵ�����ı�������
		}
		//G.vexnum--;ʵ����û����ȫɾ����������������Ĵ洢�ռ�
		cout << "ɾ��վ��ɹ���" << endl;
	}
}


//�޸�վ������
void modify_vex()
{
	string str;
	string str1;
	int loca = -1;
	cout << "��������Ҫ�޸ĵ�վ������ : " << endl;
	cin >> str;
	loca = Locate_vex(str);
	if (loca == -1)
	{
		cout << "�޸�վ��ʧ��!   " << "��վ�㲻���ڣ� " << endl;
	}
	if (loca != -1)
	{
		cout << "�������޸ĺ�����ƣ�" << endl;
		cin >> str1;
		G.vex[loca] = str1;
		cout << "վ���޸ĳɹ���" << endl;
	}

}

//����Ա�ֶ������µĹ�����·
void add_line()
{
	string st1, st2;
	int linenum;
	int locate1, locate2;
	cout << "��������Ҫ��������վ��֮��������·��" << endl;
	cout << "�����������һ��վ��" << endl;
	cin >> st1;
	cout << "����������ڶ���վ��" << endl;
	cin >> st2;
	cout << "��������Ҫ���ӵ���·������" << endl;
	cin >> linenum;
	locate1 = Locate_vex(st1);
	locate2 = Locate_vex(st2);
	G.arcs[locate1][locate2].adj[G.arcs[locate1][locate2].adj_loc++] = linenum;
	G.arcs[locate2][locate1].adj[G.arcs[locate2][locate1].adj_loc++] = linenum;
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
	lint1 = Locate_vex(str1);
	lint2 = Locate_vex(str2);               //�ҵ�������վ���ھ����е�λ��
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
