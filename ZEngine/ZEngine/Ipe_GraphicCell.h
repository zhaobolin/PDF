#pragma once
#include<string>
class Ipe_GraphicCell
{
	int type;
public:
	Ipe_GraphicCell(void);
	~Ipe_GraphicCell(void);
	virtual int gettype(){return 0;};//0-���� 1-ֱ�߼� 2-���߼�
	int GetPointCount();
	virtual void printPoint(){printf("������������");};
	//SPo_DPoint2D *GetPoint();
private:
	//vector<SPo_DPoint2D> m_pointarr;
};

