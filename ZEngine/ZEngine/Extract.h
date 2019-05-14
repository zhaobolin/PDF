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
	void GetStructureFromPDF(char* input);//从指定文档中提取矢量对象集,并令这个类持有这个对象集的指针 相当于初始化
	VectorSet * getvectorset();//获取这个extract对象持有的指向矢量对象集的指针
	void CreateDocument(char* filepath);//导出矢量对象集到指定路径
};

