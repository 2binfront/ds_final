#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <stack>
#include <Windows.h>
#include"graph.h"

using namespace std;

graph G;
int road[50] = { 1,2,3 };//��¼����·�ߺ� 
int road_a = 3;//��¼����·���� 
bool visit[500];   //��־վ����û�б����ʹ�	
p P[500];       //����վ���¼ 
int D[500];    //����վ�㵽����վ������·�� 

//��ʼ��ͼ�Ķ�������
void Create_vex()
{
	for (int k = 12; k < 500; k++)
	{
		G.vex[k] = "0";
	}
	G.vexnum = 12;

}

//�����ڽӾ���Ĵ洢�ṹ
void Creat_arcs()
{
	int sum_arcs = 0;  //��¼�ߵ�����
	//���ڽӾ�����г�ʼ��
	for (int i = 0; i < 500; i++)
	{
		for (int j = 0; j < 500; j++)
		{
			G.arcs[i][j].adj_loc = 0;
			for (int c = 0; c < 100; c++)
			{
				G.arcs[i][j].adj[c] = 0;
			}
		}
	}
	//1���� 
	G.arcs[1][2].adj[G.arcs[1][2].adj_loc++] = 1;
	G.arcs[2][3].adj[G.arcs[2][3].adj_loc++] = 1;
	G.arcs[3][4].adj[G.arcs[3][4].adj_loc++] = 1;
	G.arcs[4][5].adj[G.arcs[4][5].adj_loc++] = 1;
	G.arcs[5][6].adj[G.arcs[5][6].adj_loc++] = 1;

	G.arcs[6][5].adj[G.arcs[6][5].adj_loc++] = 1;
	G.arcs[5][4].adj[G.arcs[5][4].adj_loc++] = 1;
	G.arcs[4][3].adj[G.arcs[4][3].adj_loc++] = 1;
	G.arcs[3][2].adj[G.arcs[3][2].adj_loc++] = 1;
	G.arcs[2][1].adj[G.arcs[2][1].adj_loc++] = 1;
	//2���� 
	G.arcs[1][7].adj[G.arcs[1][7].adj_loc++] = 2;
	G.arcs[7][3].adj[G.arcs[7][3].adj_loc++] = 2;
	G.arcs[3][4].adj[G.arcs[3][4].adj_loc++] = 2;
	G.arcs[4][10].adj[G.arcs[4][10].adj_loc++] = 2;
	G.arcs[10][11].adj[G.arcs[10][11].adj_loc++] = 2;

	G.arcs[11][10].adj[G.arcs[11][10].adj_loc++] = 2;
	G.arcs[10][4].adj[G.arcs[10][4].adj_loc++] = 2;
	G.arcs[4][3].adj[G.arcs[4][3].adj_loc++] = 2;
	G.arcs[3][7].adj[G.arcs[3][7].adj_loc++] = 2;
	G.arcs[7][1].adj[G.arcs[7][1].adj_loc++] = 2;
	//3���� 
	G.arcs[0][6].adj[G.arcs[0][6].adj_loc++] = 3;
	G.arcs[6][8].adj[G.arcs[6][8].adj_loc++] = 3;
	G.arcs[8][10].adj[G.arcs[8][10].adj_loc++] = 3;
	G.arcs[10][1].adj[G.arcs[10][1].adj_loc++] = 3;
	G.arcs[1][10].adj[G.arcs[1][10].adj_loc++] = 3;
	G.arcs[10][8].adj[G.arcs[10][8].adj_loc++] = 3;
	G.arcs[8][6].adj[G.arcs[8][6].adj_loc++] = 3;
	G.arcs[6][0].adj[G.arcs[6][0].adj_loc++] = 3;
	G.arcnum = 14;
}

//����ͼ�Ĵ洢�ṹ
void Creat_graph()
{
	Create_vex();
	Creat_arcs();
}

void print_admin()
{
	system("cls"); //���� 
	int choose;
	while (1)
	{
		cout << "           &��ӭʹ�ù�����ѯϵͳ&           " << endl;
		cout << "********************************************" << endl;
		cout << "*            1.��ʾ����վ����Ϣ            *" << endl;
		cout << "*------------------------------------------*" << endl;
		cout << "*        2.��ʾվ��֮��Ĺ���·�ߺ�        *" << endl;
		cout << "*------------------------------------------*" << endl;
		cout << "*              3.����վ����Ϣ              *" << endl;
		cout << "*------------------------------------------*" << endl;
		cout << "*              4.ɾ��վ����Ϣ              *" << endl;
		cout << "*------------------------------------------*" << endl;
		cout << "*              5.�޸�վ������              *" << endl;
		cout << "*------------------------------------------*" << endl;
		cout << "*            6.�ֶ����ӹ���·��            *" << endl;
		cout << "*------------------------------------------*" << endl;
		cout << "*            7.����վ������·            *" << endl;
		cout << "*------------------------------------------*" << endl;
		cout << "*           8.������վ֮���·��           *" << endl;
		cout << "*------------------------------------------*" << endl;
		cout << "*                9.�˳�����                *" << endl;
		cout << "*------------------------------------------*" << endl;
		cout << "*                  ��ѡ��                  *" << endl;
		cout << "********************************************" << endl;
		cin >> choose;
		switch (choose)
		{
		case 1:print_vex(); break;
		case 2:print_arcs(); break;
		case 3:add_vex(); break;
		case 4:dele_vex(); break;
		case 5:modify_vex(); break;
		case 6:add_line(); break;
		case 7:modify_adj(); break;
		case 8:direct_path(); break;
		case 9:
		{
			cout << "�˳�����"; exit(1);
		}
		default:cout << "����ѡ������" << endl;
		}
		system("pause");//������ͣ 
		system("cls"); //���� 
	}
}

void print_user() 
{
	int choose;
	while (1)
	{
		system("cls"); //���� 
		cout << "           &��ӭʹ�ù�����ѯϵͳ&           " << endl;
		cout << "********************************************" << endl;
		cout << "*            1.��ʾ����վ����Ϣ            *" << endl;
		cout << "*------------------------------------------*" << endl;
		cout << "*        2.��ʾվ��֮��Ĺ���·�ߺ�        *" << endl;
		cout << "*------------------------------------------*" << endl;
		cout << "*           3.������վ֮���·��           *" << endl;
		cout << "*------------------------------------------*" << endl;
		cout << "*                4.�˳�����                *" << endl;
		cout << "*------------------------------------------*" << endl;
		cout << "*                  ��ѡ��                  *" << endl;
		cout << "********************************************" << endl;
		cin >> choose;
		switch (choose)
		{
		case 1:print_vex(); break;
		case 2:print_arcs(); break;
		case 3:direct_path(); break;
		case 4:
		{
			cout << "�˳�����"; exit(1);
		}
		default:cout << "����ѡ������" << endl;
		}
		system("pause");//������ͣ 
		system("cls"); //���� 
	}
}

int main()
{
	int choose;
	string pwd_correct="123456";
	string pwd_input;
	Creat_graph();
	while (1)
	{
		cout << "           &��ӭʹ�ù�����ѯϵͳ&           " << endl;
		cout << "********************************************" << endl;
		cout << "*             &��ѡ���������&             *" << endl;
		cout << "*------------------------------------------*" << endl;
		cout << "*                 1.�û�                   *" << endl;
		cout << "*------------------------------------------*" << endl;
		cout << "*                2.����Ա                  *" << endl;
		cout << "*------------------------------------------*" << endl;
		cin >> choose;
		if (choose == 1)
			print_user();
		else if (choose == 2)
		{
			cout << "*            ���������Ա����            *" << endl;
			cin >> pwd_input;
			if (pwd_correct == pwd_input)
				print_admin();
			else
			{
				cout << "*      ������󣬼����˳�����     *" << endl;
				Sleep(2000); exit(1);
			}
		}
		else
		{
			cout << "*         ������������������        *" << endl;
			Sleep(1500);
			system("cls"); //���� 
			continue;
		}
	}
	return 0;
}