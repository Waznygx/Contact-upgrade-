#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<memory.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#define max_name 12
#define max_sex 10
#define max_address 30
#define init_cap 5
#define add_cap 2
//#define max_person 10000

//��Ϣ����������
typedef struct message_content//©��typedef������main.c��struct�޷�ʡ��
{
	char name[max_name];
	char sex[max_sex];
	int age;
	int tele;
	char address[max_address];
}content;

//��̬����
typedef struct person_message
{
	content* all_data;//ָ���ڴ�����Ŀռ䣬���������Ϣ
	int capacity;//ͨѶ¼������
	int available_data;//������Ϣ�ĸ���
}message;

//��̬�洢
////ͨѶ¼
//typedef struct person_message
//{
//	content all_data[max_person];//ͨѶ¼������
//	int available_data;//������Ϣ�ĸ���
//}message;


//��������(д��message��������struct�Ļ��ᱨ��)
void init_message(message* mess);
void add_message(message* mess);
void print_message(const message* mess);//����û�뵽Ҫ�̶�mess
void delete_message(message* mess);
void search_message(message* mess);
int find_all_names(message* mess, char name[], int ret[]);//û���ǵ�ɾ�����޸ġ���ѯ��Ҫ�õ������ҡ�ָ��
void modify_message(message* mess);
void sort_message(message* mess);
void sort_menu();
void sort1(message* mess);
void sort2(message* mess);
void release_message(message* mess);
void fwrite_message(message* mess);
void fread_message(message* mess);
void expend_capacity(message* mess);

