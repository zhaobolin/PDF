#ifndef IGEO_LINE_H_HEADER_INCLUDED_B9D314AF
#define IGEO_LINE_H_HEADER_INCLUDED_B9D314AF
#include "IGeo_Curve.h"
class IPo_SpatialReference;
class IGeo_Geometry;


//##ModelId=4B2B8A71025C
template <class T> struct LOG_LINE
{
public:
	//##ModelId=4B2B8A710262
	SPo_TplPoint2D<T> start;
	//##ModelId=4B2B8A710267
	SPo_TplPoint2D<T> end;
public:	
	//////δ������㵽�Ľ�β�˵��ڽ�ƽ���ߵ��ĸ������ϣ�//���
	template<class TYPE1,class TYPE2,class TYPE3,class TYPE4> void ConstructAngleBisector(SPo_TplPoint2D<TYPE1> S_pt, SPo_TplPoint2D<TYPE2> C_pt, SPo_TplPoint2D<TYPE3> E_pt, TYPE4 fLength, bool bUseAcuteAngle)//ʼ�㡢�е㡢ĩ�㡢���ȡ��Ƿ����
	{
		double fAngle_s = GetAngleAngMt(C_pt.x,C_pt.y, S_pt.x,S_pt.y);
		
		double fAngle_e = GetAngleAngMt(C_pt.x,C_pt.y, E_pt.x,E_pt.y);
		
		double fAngle	= fAngle_s + (fAngle_e - fAngle_s)/2;
		
		double fRadian = ANGLE_TO_RADIAN(fAngle);
		
		if(bUseAcuteAngle)
		{	
			end.x = (T) (C_pt.x + fLength * cos(fRadian));
			
			end.y = (T) (C_pt.y + fLength * sin(fRadian));
		}
		else
		{
			end.x = (T) (C_pt.x - fLength * cos(fRadian));
			end.y = (T) (C_pt.y - fLength * sin(fRadian));
		}
		start = C_pt;
	};
};
//##ModelId=4B2B8A71026B
typedef LOG_LINE<double> LOGD_LINE;
//##ModelId=4B2B8A71026D
typedef LOG_LINE<int> LOGI_LINE;
//##ModelId=4B2B8A710272
typedef LOG_LINE<float> LOGF_LINE;
//##ModelId=4B2B8A710274
typedef LOG_LINE<long> LOGL_LINE;


//brief
//     �߶μ��ζ���ӿ�
//     ��������֮���ֱ�߶ζ�������򵥵��߶���
//##ModelId=4B2B8A710281
class IGeo_Line : public IGeo_Curve
{
  public:
	//##ModelId=4B2B8A710283
	virtual LOG_LINE<double> GetLogLine() = 0;

	//##ModelId=4B2B8A710285
	virtual void SetLogLine(LOG_LINE<double> log) = 0;
    //brief
    //     �жϸ����ĵ��Ƿ����߶���
    //     ���ݸ����ĵ㼰�ռ�ο�ϵ�ж����Ƿ����߶��ϡ�
    // 
    //return
    //     λ���߶��ϣ��򷵻�true�����򷵻�false��
    // 
    //param
    //     sPoint: ��Ҫ�жϵĵ����ꡣ
    //     dTolerance �ж���ֵ��
    //     pSpatialReference: �������Ӧ�Ŀռ�ο�ϵ��ȱʡΪNULL����ʾʹ���߶α���Ŀռ�ο�ϵ��
    //##ModelId=4B2B8A710288
    virtual bool IsPointOnLine(SPo_DPoint sPoint, IPo_SpatialReference* pSpatialReference = NULL, double dTolerance = 0.0) = 0;

    //brief
    //     �жϸ����ĵ�����Ƿ����߶���
    // 
    //return
    //     λ���߶��ϣ��򷵻�true�����򷵻�false��
    // 
    //param
    //     pPoint: ��Ҫ�жϵĵ����
    //     dTolerance �ж���ֵ��
    //##ModelId=4B2B8A710290
    virtual bool IsPointOnLine(const IGeo_Geometry* pPoint, double dTolerance = 0.0) = 0;

    //brief
    //     ��ȡ�߶���x������н�
    // 
    //return
    //     ���ؼн�
    //     ��ע : �߶η���Ϊ������յ㣬����ֵΪ0��2*Pi
    //##ModelId=4B2B8A710294
    virtual double GetAngle() = 0;

    //brief
    //     ����ֱ�߶εĽ���
    // 
    //return
    //     û�н��㷵��0��һ�����㷵��1���ཻΪ�߶η���2
    // 
    //param
    //     pGeo: �����ཻ���߶���
    //     sPoint: ����
    //     sLinePt: �ཻ�߶ε���һ�˵�
    //     pSpatialReference: ����������Ӧ�Ŀռ�ο�ϵ��ȱʡΪNULL����ʾʹ�����߶�(this)�Ŀռ�ο�ϵ��
    //##ModelId=4B2B8A710296
    virtual int GetCross(const IGeo_Geometry* pGeo, SPo_DPoint& sPoint, SPo_DPoint& sLinePt, IPo_SpatialReference* pSpatialReference = NULL) = 0;

};

extern "C" __declspec(dllexport) IGeo_Line *CreateGeoLineIndirect(LOGD_LINE lg);

#endif /* IGEO_LINE_H_HEADER_INCLUDED_B9D314AF */
