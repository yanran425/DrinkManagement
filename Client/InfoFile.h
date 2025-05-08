#pragma once

#include <list>
#include <fstream>
#include <iostream>
#include <string>

#define _F_LOGIN "./login.ini"
#define _F_STOCK "./stock.txt"

using namespace std;

struct msg
{
	int id = 0;				//��Ʒid
	string name = "";	//��Ʒ��
	double price = 0;			//��Ʒ�۸�
	int num = 0;			//��Ʒ����
};

class CInfoFile
{
public:
	CInfoFile();
	~CInfoFile();

	//��ȡ��½��Ϣ
	void ReadLogin(CString &name, CString &pwd);

	//�޸�����
	void WritePwd(char* name, char* pwd);

	// ��ȡ��Ʒ����
	void ReadDocline();

	//��Ʒд���ļ�
	void WirteDocline();

	//�������Ʒ
	void Addline(CString name, int num, double price);

	list<msg> ls;	//�洢��Ʒ����
	int num = 0;			//������¼��Ʒ����
};

