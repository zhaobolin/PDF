#ifndef IGEO_BAZIERCURVE_H_HEADER_INCLUDED_B9D37F50
#define IGEO_BAZIERCURVE_H_HEADER_INCLUDED_B9D37F50
#include "IGeo_Curve.h"
#include "IGeo_Point.h"

//##ModelId=4B2B8A7202A7
template <class T> struct LOG_BAZIERCURVE
{
public:
	//##ModelId=4B2B8A7202AB
	SPo_TplPoint2D<T> pt[4];
public:
	//##ModelId=4B2B8A7202AF
	void ConstructTangentsAtEndPoints(LOG_LINE<double> line1, LOG_LINE<double> line2)
	{
		pt[0] = line1.end;
		pt[1] = line1.start;
		pt[2] = line2.start;
		pt[3] = line2.end;
	}
};

//##ModelId=4B2B8A7202B2
typedef LOG_BAZIERCURVE<double> LOGD_BAZIERCURVE;
//##ModelId=4B2B8A7202B4
typedef LOG_BAZIERCURVE<int> LOGI_BAZIERCURVE;
//##ModelId=4B2B8A7202B6
typedef LOG_BAZIERCURVE<float> LOGF_BAZIERCURVE;
//##ModelId=4B2B8A7202B8
typedef LOG_BAZIERCURVE<long> LOGL_BAZIERCURVE;
//brief
//     ���������߶���ӿڣ��ĵ����
//##ModelId=4B2B8A7202BF
class IGeo_BazierCurve : public IGeo_Curve
{
  public:
	//##ModelId=4B2B8A7202C1
	virtual LOG_BAZIERCURVE<double> GetLogBazierCurve() = 0;

	//##ModelId=4B2B8A7202C3
	virtual void SetLogBazierCurve(LOG_BAZIERCURVE<double> log) = 0;
    //brief
    //     �õ�Bazier���߽Ƕ�
    // 
    //return   
    //      �Ƕ�
    //     
    //##ModelId=4B2B8A7202C6
    virtual double GetDegree() = 0;

    //brief   
    //     ����Bazier���߽Ƕ�
    // 
    //param
    // 
    //     dDegree:�Ƕ�ֵ
    //##ModelId=4B2B8A7202C8
    virtual bool SetDegree(double dDegree) = 0;

    //brief
    //     ���ÿ��Ƶ�ĵ���Ϣ
    // 
    //param
    //     iIndex:���
    //     Point:����Ϣ
    // 
    //##ModelId=4B2B8A7202CB
    virtual bool SetCoord(int iIndex, IGeo_Point *Point  ) = 0;

    //brief
    //     һ�����ö�����Ƶ��ֵ
    // 
    //param
    //     piIndex:�������
    //     pPoint:����Ϣ����
    // 
    //##ModelId=4B2B8A7202D0
    virtual bool SetCoords(int *piIndex, IGeo_Point ** pPoint) = 0;

    //brief
    //     �õ�ĳ�����Ƶ���Ϣ
    // 
    //param
    //     iIndex:���
    // 
    //return  
    //     ���Ƶ���Ϣ
    //  
    //##ModelId=4B2B8A7202D4
    virtual IGeo_Point * GetCoord(int iIndex) = 0;

    //brief
    //      �õ�������Ƶ���Ϣ
    // 
    //param
    //      piIndex:���ؿ��Ƶ�����
    //      pPoint:���ؿ��Ƶ���Ϣ,����λ�ô�index��ʼ.
    // 
    //##ModelId=4B2B8A7202D7
    virtual bool GetCoords(int *piIndex, IGeo_Point* pPoint) = 0;

    //brief
    //     �����ų����ʼ������
    //param
    //     rTangent:��������
    //     bSetByUser:�û����ã�true
    //##ModelId=4B2B8A7202DB
    virtual bool SetChordLengthTangentAtFrom(IGeo_Point& rTangent, bool bSetByUser) = 0;

    //brief
    //     �����ų����ʼ������
    //param
    //     rTangent:��������
    //     bSetByUser:�û����ã�true
    //##ModelId=4B2B8A7202DF
    virtual bool GetChordLengthTangentAtFrom(IGeo_Point& rTangent, bool &brSetByUser) = 0;

    // /brief
    //     �����ų������������
    //param
    //     rTangent:��������
    //     bSetByUser:�û����ã�true
    //##ModelId=4B2B8A7202E3
    virtual bool SetChordLengthTangentAtTo(IGeo_Point& rTangent, bool bSetByUser) = 0;

    // /brief
    //     �����ų������������
    //param
    //     rTangent:��������
    //     bSetByUser:�û����ã�true
    //##ModelId=4B2B8A7202E7
    virtual bool GetChordLengthTangentAtTo(IGeo_Point& rTangent, bool &brSetByUser) = 0;

};

extern "C" __declspec(dllexport) IGeo_BazierCurve * CreateGeoBazCurvIndirect(LOGD_BAZIERCURVE lg);

#endif /* IGEO_BAZIERCURVE_H_HEADER_INCLUDED_B9D37F50 */
