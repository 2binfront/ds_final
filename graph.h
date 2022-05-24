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
typedef struct Cell
{
	int adj[100];  //�洢Ȩֵ		������Ȩֵ���Ǿ����ö���Ĺ���·�ߺ�

  //��¼ÿ��վ���������Ĺ�����·�����ڳ��������������
	int adj_loc;
}cell[500][500];

//�����Ȩͼ�Ĵ洢�ṹ
typedef struct map
{
	string vex[500] = { "�칤Ժ","��Դ���ʻ���","��ˮ·","����֮������","�����е�����","�̵������","���ٹ㳡","��԰�׸�","Ԫ��·","����·","����·","������" };
	//�����ַ�������
	cell arcs;             //�ڽӾ���
	int vexnum, arcnum;     //���������ͱߵ�����
}graph;

typedef struct load {
	int vex[500]; //վ��˳�� 
	int vex_loc;  //վ������� 
}p;


//��ͼ�������õϽ�˹�����㷨��ɻ�������
//ȫ�ֱ����Ķ���
#define INFMAX 500 //·�����ֵ



void Indirect_path(string str1, string str2);
void djc(int v0);
void direct_path();

int vex_repeat(string& point);
int Locate_vex(string v);
int Locate_road(int j);

void print_vex();
void print_arcs();

void Create_vex();
void Creat_arcs();
void Creat_graph();


void dele_vex();
void add_vex();
void add_line();
void modify_vex();
int modify_adj();


#endif