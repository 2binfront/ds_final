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
int subway[10] = { 1,2,3 };//��¼����·�ߺ� 
int subway_num = 3;//��¼����·���� 
bool visit[100];   //��־վ����û�б����ʹ�	
station S[100];       //����վ���¼ 
int min_length[100];    //����վ�㵽����վ������·�� 

void define_arcs(int i, int j, int road) //i,j��վ���ţ�road�ǵ�����
{
	G.arcs[i][j].adj[G.arcs[i][j].adj_loc] = road;
	G.arcs[i][j].adj_loc++;
}

//����ͼ�Ĵ洢�ṹ
void createG()
{
	//��ʼ��ͼ�Ķ�������
	for (int i = 26; i < 100; i++)
	{
		G.vex[i] = "0";
	}
	G.vexnum = 26;//����26վ
	int sum_arcs = 0;  //��¼�ߵ�����
	//���ڽӾ�����г�ʼ��
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			G.arcs[i][j].adj_loc = 0;
			for (int k = 0; k < 100; k++)
			{
				G.arcs[i][j].adj[k] = 0;
			}
		}
	}
	//1����
	//�����Ǿ���
	define_arcs(0, 1, 1);
	define_arcs(1, 2, 1);
	define_arcs(2, 3, 1);
	define_arcs(3, 4, 1);
	define_arcs(4, 5, 1);
	define_arcs(5, 6, 1);
	define_arcs(6, 7, 1);
	define_arcs(7, 8, 1);
	//2���� 
	define_arcs(9, 10, 2);
	define_arcs(10, 11, 2);
	define_arcs(11, 12, 2);
	define_arcs(12, 13, 2);
	define_arcs(13, 14, 2);
	define_arcs(14, 3, 2);
	define_arcs(3, 15, 2);
	define_arcs(15, 16, 2);
	define_arcs(16, 17, 2);
	define_arcs(17, 18, 2);
	//3����
	define_arcs(19, 20, 3);
	define_arcs(20, 21, 3);
	define_arcs(21, 1, 3);
	define_arcs(1, 14, 3);
	define_arcs(14, 22, 3);
	define_arcs(22, 5, 3);
	define_arcs(5, 23, 3);
	define_arcs(23, 24, 3);
	define_arcs(24, 25, 3);

	//�����Ǿ���
	//1����
	define_arcs(8, 7, 1);
	define_arcs(7, 6, 1);
	define_arcs(6, 5, 1);
	define_arcs(5, 4, 1);
	define_arcs(4, 3, 1);
	define_arcs(3, 2, 1);
	define_arcs(2, 1, 1);
	define_arcs(1, 0, 1);
	//2���� 
	define_arcs(18, 17, 2);
	define_arcs(17, 16, 2);
	define_arcs(16, 15, 2);
	define_arcs(15, 3, 2);
	define_arcs(3, 14, 2);
	define_arcs(14, 13, 2);
	define_arcs(13, 12, 2);
	define_arcs(12, 11, 2);
	define_arcs(11, 10, 2);
	define_arcs(10, 9, 2);
	//3���� 
	define_arcs(25, 24, 3);
	define_arcs(24, 23, 3);
	define_arcs(23, 5, 3);
	define_arcs(5, 22, 3);
	define_arcs(22, 14, 3);
	define_arcs(14, 1, 3);
	define_arcs(1, 21, 3);
	define_arcs(21, 20, 3);
	define_arcs(20, 19, 3);
	G.arcnum = 27;
}

void print_admin()
{
	system("cls"); //���� 
	int choose;
	while (1)
	{
		cout << "           &��ӭʹ�õ�����ѯϵͳ&           " << endl;
		cout << "********************************************" << endl;
		cout << "*            1.��ʾ����վ����Ϣ            *" << endl;
		cout << "*------------------------------------------*" << endl;
		cout << "*        2.��ʾվ��֮��ĵ���·�ߺ�        *" << endl;
		cout << "*------------------------------------------*" << endl;
		cout << "*              3.����վ����Ϣ              *" << endl;
		cout << "*------------------------------------------*" << endl;
		cout << "*              4.ɾ��վ����Ϣ              *" << endl;
		cout << "*------------------------------------------*" << endl;
		cout << "*              5.�޸�վ������              *" << endl;
		cout << "*------------------------------------------*" << endl;
		cout << "*            6.�ֶ����ӵ���·��            *" << endl;
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
		case 1:print_v(); break;
		case 2:print_arcs(); break;
		case 3:add_v(); break;
		case 4:delete_v(); break;
		case 5:modify_v(); break;
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
		cout << "           &��ӭʹ�õ�����ѯϵͳ&           " << endl;
		cout << "********************************************" << endl;
		cout << "*            1.��ʾ����վ����Ϣ            *" << endl;
		cout << "*------------------------------------------*" << endl;
		cout << "*        2.��ʾվ��֮��ĵ���·�ߺ�        *" << endl;
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
		case 1:print_v(); break;
		case 2:print_arcs(); break;
		case 3:direct_path(); break;
		case 4:
		{
			cout << "�˳�����"; exit(1);
		}
		default:cout << "����ѡ����������������1-4��" << endl;
		}
		system("pause");
		system("cls");
	}
}

int main()
{
	int choose;
	string pwd_correct = "123456";
	string pwd_input;
	createG();
	while (1)
	{
		cout << "           &��ӭʹ�õ�����ѯϵͳ&           " << endl;
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
			Sleep(2000);
			system("cls");
			continue;
		}
	}
	return 0;
}