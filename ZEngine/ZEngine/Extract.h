#pragma once
#include <string>
#include <fstream>
#include "MuInclude.h"
#include "VectorSet.h"
using namespace std;
class EX_PORT Extract
{
	VectorSet * vectorset;
public:
	Extract(void);
	~Extract(void);
	void GetStructureFromPDF(char* input);//��ָ���ĵ�����ȡʸ������,������������������󼯵�ָ�� �൱�ڳ�ʼ��
	VectorSet * getvectorset();//��ȡ���extract������е�ָ��ʸ�����󼯵�ָ��
	void CreateDocument(char* filepath);//����ʸ�����󼯵�ָ��·��
};

