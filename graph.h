#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <stack>
#ifndef graph_H
#define graph_H

using namespace std;

//�ڽӾ���Ĵ洢�ṹ
typedef struct cell
{
	int adj[100];//�����õĵ���·�ߺ�
	int adj_loc;  //��¼ÿ��վ���������ĵ�����·�����ڳ��������������
}matrix[100][100];

//�����Ȩͼ�Ĵ洢�ṹ
typedef struct map
{
	string vex[100] = { "������","�Ͼ�վ","��¥","�½ֿ�","������","�Ͼ���վ","С����","��ӡ���","�й�ҩ�ƴ�ѧ","����·","�ϴ�����У��","����·","Т����","��ޣ԰","���й�","������","���嶫","�ͷ���","����","�ֳ�","̩��·","��Ԫ��","�껨��","������","���������У��","���ܶ�·" };
	//�����ַ�������
	matrix arcs;             //�ڽӾ���
	int vexnum, arcnum;     //���������ͱߵ�����
}graph;

typedef struct road {
	int vex[100]; //վ��˳�� 
	int vex_loc;  //վ������� 
}station;

//��ͼ�������õϽ�˹�����㷨��ɻ�������
//ȫ�ֱ����Ķ���
#define MAXROAD 100 //·�����ֵ

void Indirect_path(string str1, string str2);
void djc(int v0);
void direct_path();

int vex_repeat(string& v);
int locate_v(string v);
int locate_subway(int j);

void print_v();
void print_arcs();
void print_user();
void print_admin();

void define_arcs(int i, int j, int road);
void createG();
void delete_v();
void add_v();
void add_line();
void modify_v();
int modify_adj();
#endif