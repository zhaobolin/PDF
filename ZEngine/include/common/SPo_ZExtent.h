#ifndef SPO_ZEXTENT_H_HEADER_INCLUDED_BB16469D
#define SPO_ZEXTENT_H_HEADER_INCLUDED_BB16469D

// Zֵֵ��Ľṹ�壬��������������Zֵֵ�����СֵZMin��Zֵֵ������ֵZMax
//##ModelId=44E9F10E0056
struct SPo_ZExtent
{
	SPo_ZExtent(double dvalmin,double dvalmax)
	{
		dZMin = dvalmin;
		dZMax = dvalmax;
	}
	SPo_ZExtent()
	{
		dZMin = 0;
		dZMax = 0;
	}
    // �ռ�ο���Zֵֵ����Сֵ
    //##ModelId=44E9F12A0133
    double dZMin;

    // �ռ�ο���Zֵֵ�����ֵ
    //##ModelId=44E9F1470333
    double dZMax;

};



#endif /* SPO_ZEXTENT_H_HEADER_INCLUDED_BB16469D */
