#pragma once
#include<string>
class Ipe_GraphicCell
{
	int type;
public:
	Ipe_GraphicCell(void);
	~Ipe_GraphicCell(void);
	virtual int gettype(){return 0;};//0-父类 1-直线集 2-曲线集
	int GetPointCount();
	virtual void printPoint(){printf("父类的输出函数");};
	//SPo_DPoint2D *GetPoint();
private:
	//vector<SPo_DPoint2D> m_pointarr;
};

