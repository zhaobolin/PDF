#ifndef IGEO_ELLIPTICARC_H_HEADER_INCLUDED_B9D36BC7
#define IGEO_ELLIPTICARC_H_HEADER_INCLUDED_B9D36BC7
#include "IGeo_Curve.h"
class IPo_SpatialReference;
class IGeo_Point;


//##ModelId=4B2B8A7200B3
template <class TYPE> struct LOG_ELLIPTICARC
{
public:
	//##ModelId=4B2B8A7200B9
	SPo_TplPoint2D<TYPE>	centre;				// Բ��
	//##ModelId=4B2B8A7200BD
	TYPE			semiMajorAxis;		// ���뾶
	//##ModelId=4B2B8A7200BE
	TYPE			semiMinorAxis;		// �̰뾶
	// ��Բ��ת�Ƕ�,�Ի��ȶ���
	//##ModelId=4B2B8A7200BF
	double		ratio;
	// ��ʼ�Ƕ�,�Ի��ȶ���
	//##ModelId=4B2B8A7200C0
	double		startradian;					
	// ��ֹ�Ƕ�,�Ի��ȶ���
	//##ModelId=4B2B8A7200C1
	double		endradian;
	//�Ի��ȶ���		
	//##ModelId=4B2B8A7200C2
	double		cita;
public:		
	//���δ���
	template<class TYPE1> void ConstructEnvelope(TYPE1 left,TYPE1 top,TYPE1 right,TYPE1 bottom)
	{
		TYPE1 minx = min(left,right);TYPE1 maxx = max(left,right);
		TYPE1 miny = min(top,bottom);TYPE1 maxy = max(top,bottom);		
		centre.x = (TYPE)(minx+(maxx-minx)/2);centre.y = (TYPE)(miny+(maxy-miny)/2);
		startradian = 0;endradian = ANGLE_TO_RADIAN(360);ratio = 0;		
		maxx-minx>maxy-miny?(semiMajorAxis = (maxx-minx)/2)+(semiMinorAxis = ((maxy-miny)/2)):
		(semiMajorAxis = (maxy-miny)/2)+(semiMinorAxis = ((maxx-minx)/2))+(ratio = ANGLE_TO_RADIAN(90));		
		cita = startradian;
	}
	template<class TYPE1,class TYPE2,class TYPE3,class TYPE4> void ConstructEnvelopeJx(SPo_TplPoint2D<TYPE1> pt1, SPo_TplPoint2D<TYPE2> pt2, SPo_TplPoint2D<TYPE3> pt3, SPo_TplPoint2D<TYPE4> pt4)//�㰴˳ʱ����
	{
		double temp1, temp2;		
		temp1 = min(pt1.x, pt2.x);
		temp2 = min(pt3.x, pt4.x);
		double left = min(temp1, temp2);		
		temp1 = min(pt1.y, pt2.y);
		temp2 = min(pt3.y, pt4.y);
		double bottom = min(temp1, temp2);		
		temp1 = max(pt1.x, pt2.x);
		temp2 = max(pt3.x, pt4.x);		
		double right = max(temp1, temp2);		
		temp1 = max(pt1.y, pt2.y);
		temp2 = max(pt3.y, pt4.y);		
		double top = max(temp1, temp2);		
		ConstructEnvelope(left, top, right, bottom);
	}
	template<class TYPE1,class TYPE2> void ConstructQuarterEllipse(SPo_TplPoint2D<TYPE1> S_pt, SPo_TplPoint2D<TYPE2> E_pt, double rotation/*0 or 90*/, double S_angle, double E_angle/*����90*/, bool bCCW)
	{
		semiMajorAxis	= (TYPE)fabs(S_pt.x - E_pt.x);
		semiMinorAxis	= (TYPE)fabs(S_pt.y - E_pt.y);		
		ratio			= ANGLE_TO_RADIAN(rotation);		
		if(S_pt.x - E_pt.x > 0)
		{
			if(S_pt.y - E_pt.y > 0)
			{
				centre.x	= (TYPE)(E_pt.x);
				centre.y	= (TYPE)(S_pt.y);
			}
			else
			{
				centre.x	= (TYPE)(S_pt.x);
				centre.y	= (TYPE)(E_pt.y);				
			}
		}
		else
		{
			if(S_pt.y - E_pt.y > 0)
			{
				centre.x	= (TYPE)(S_pt.x);
				centre.y	= (TYPE)(E_pt.y);				
			}
			else
			{
				centre.x	= (TYPE)(E_pt.x);
				centre.y	= (TYPE)(S_pt.y);
			}			
		}
		double BaseAngle	= GetAngleAngMt(centre, S_pt) - 90;		
		S_angle			= S_angle + BaseAngle;//-90����ϵת��		
		E_angle			= E_angle + BaseAngle;//-90����ϵת��		
		startradian		= ANGLE_TO_RADIAN(S_angle);
		endradian		= ANGLE_TO_RADIAN(E_angle);		
		cita = startradian;
	}
	template<class TYPE1,class TYPE2,class TYPE3> void ConstructTwoPointsEnvelope(SPo_TplPoint2D<TYPE1> S_pt, SPo_TplPoint2D<TYPE2> E_pt, SPo_TplRect<TYPE3> rect, double rotation)
	{
		centre.x	= (TYPE)((rect.left + rect.right)/2);
		centre.y	= (TYPE)((rect.bottom + rect.top)/2);		
		semiMajorAxis	= (TYPE)(fabs(rect.left - rect.right)/2);
		semiMinorAxis	= (TYPE)(fabs(rect.bottom - rect.top)/2);
		double startAngle	= GetAngleAngMt(centre, S_pt);//if(startAngle < 0) startAngle	+= 360;
		double endAngle	= GetAngleAngMt(centre, E_pt);//if(endAngle < 0)	endAngle	+= 360;
		if(startAngle > endAngle)
		{
			double temp  = startAngle;
			startAngle = endAngle;
			endAngle   = temp;
		}
		startradian		= ANGLE_TO_RADIAN(startAngle);
		endradian		= ANGLE_TO_RADIAN(endAngle);
		ratio			= ANGLE_TO_RADIAN(rotation);
		cita = startradian;
	}
	//��������԰�������˳��֪�����εķ���
	template<class TYPE1,class TYPE2,class TYPE3,class TYPE4,class TYPE5> void ConstructUpToFivePoints(SPo_TplPoint2D<TYPE1> S_pt, SPo_TplPoint2D<TYPE2> E_pt, SPo_TplPoint2D<TYPE3> thru, SPo_TplPoint2D<TYPE4> pt4, SPo_TplPoint2D<TYPE5> pt5)
	{		
	}
};

//##ModelId=4B2B8A7200C3
typedef LOG_ELLIPTICARC<double> LOGD_ELLIPTICARC;
//##ModelId=4B2B8A7200CC
typedef LOG_ELLIPTICARC<int> LOGI_ELLIPTICARC;
//##ModelId=4B2B8A7200CE
typedef LOG_ELLIPTICARC<float> LOGF_ELLIPTICARC;
//##ModelId=4B2B8A7200DB
typedef LOG_ELLIPTICARC<long> LOGL_ELLIPTICARC;

//##ModelId=4B2B8A7200DD
template <class TYPE> struct LOG_ELLIPSE
{
public:
	//##ModelId=4B2B8A7200ED
	SPo_TplPoint2D<TYPE>	centre;				// Բ��
	//##ModelId=4B2B8A7200F1
	TYPE			semiMajorAxis;		// ���뾶
	//##ModelId=4B2B8A7200F2
	TYPE			semiMinorAxis;		// �̰뾶
	//##ModelId=4B2B8A7200F3
	double		ratio;				// ��Բ��ת�Ƕ�	
	//##ModelId=4B2B8A7200FA
	double		cita;
};

//##ModelId=4B2B8A7200FB
typedef LOG_ELLIPSE<double> LOGD_ELLIPSE;
//##ModelId=4B2B8A7200FD
typedef LOG_ELLIPSE<int> LOGI_ELLIPSE;
//##ModelId=4B2B8A72010A
typedef LOG_ELLIPSE<float> LOGF_ELLIPSE;
//##ModelId=4B2B8A72010C
typedef LOG_ELLIPSE<long> LOGL_ELLIPSE;
//brief
//     ��Բ���߶���ӿ�
//##ModelId=4B2B8A72011A
class IGeo_EllipticArc : public IGeo_Curve
{
public:
	//##ModelId=4B2B8A720129
	virtual LOG_ELLIPTICARC<double> GetLogEllipticArc() = 0;
	///
	//##ModelId=4B2B8A72012B
	virtual void SetLogEllipticArc(LOG_ELLIPTICARC<double> log) = 0;
    //brief
    //     ������Բ��Բ�ĵ����ꡣ
    //     ���ݸ����Ŀռ�ο�ϵ������Բ�ĵ����ꡣ
    // 
    //return
    //     ���óɹ����򷵻�true�����򷵻�false��
    // 
    //param
    //     sPoint: ��Բ�����ꡣ
    //     pSpatialReference: �����õ���Բ�������Ӧ�Ŀռ�ο�ϵ��ȱʡΪNULL����ʾʹ����Բ������Ŀռ�ο�ϵ��
    //##ModelId=4B2B8A72012E
    virtual bool SetCenterPoint(SPo_DPoint sPoint, IPo_SpatialReference* pSpatialReference = NULL) = 0;

    //brief
    //     ��ȡԲ��Բ�ĵ����ꡣ
    //     ���ݸ����Ŀռ�ο�ϵ��ȡԲ�ĵ����ꡣ
    //     ����Բ�ĵ����꣬���ռ�����ת��ʧ���򷵻�SPo_Point(0,0)��
    // 
    //param
    //     pSpatialReference: ��Ҫ���ص�Բ�������Ӧ�Ŀռ�ο�ϵ��ȱʡΪNULL����ʾʹ��Բ������Ŀռ�ο�ϵ��
    //##ModelId=4B2B8A720132
    virtual SPo_DPoint GetCenterPoint(IPo_SpatialReference* pSpatialReference = NULL) = 0;

    //brief
    //     �������ļн�
    // 
    //param
    //     dAngle:���ļн�
    // 
    //return
    //     ���سɹ���true
    //##ModelId=4B2B8A720135
    virtual bool SetCentralAngle(double dAngle) = 0;

    //brief
    //     ��ȡ���ļн�
    // 
    //return
    //     ���ļн�
    //##ModelId=4B2B8A720138
    virtual double GetCentralAngle(IPo_SpatialReference* pSpatialReference = NULL) = 0;

    //brief
    //     �Ƿ�Բ��
    // 
    //return
    //     ��Բ��������true
    //##ModelId=4B2B8A72013B
    virtual bool IsCircular() = 0;

    //brief
    //     �Ƿ�˳ʱ��
    // 
    //return
    //     ��˳ʱ�룬����true
    //##ModelId=4B2B8A72013D
    virtual bool IsCounterClockwise() = 0;

    //brief
    //     �Ƿ��˻�Ϊ��
    // 
    //return
    //     �˻�Ϊ�ߣ�����true
    //##ModelId=4B2B8A72013F
    virtual bool IsLine(double dRadius) = 0;

    //brief
    //     �Ƿ�С��
    // 
    //return
    //     ��С��������true
    //##ModelId=4B2B8A720142
    virtual bool IsMinor() = 0;

    //brief
    //     �Ƿ��˻�Ϊ��
    // 
    //return
    //     ���˻�������true
    //##ModelId=4B2B8A720144
    virtual bool IsPoint() = 0;

    //brief
    //     ����Բ����ʼ�Ƕ�
    // 
    //param
    //     dAng Բ����ʼ�Ƕ�
    //##ModelId=4B2B8A720146
    virtual void SetFromAngle(double dAng) = 0;

    //brief
    //     ��ȡԲ����ʼ�Ƕ�
    // 
    //return
    //     ����Բ����ʼ�Ƕ�
    //##ModelId=4B2B8A720149
    virtual double GetFromAngle() = 0;

    //brief
    //     ����Բ����ֹ�Ƕ�
    // 
    //param
    //     dAng Բ����ֹ�Ƕ�
    //##ModelId=4B2B8A72014B
    virtual void SetToAngle(double dAng) = 0;

    //brief
    //     ��ȡԲ����ֹ�Ƕ�
    // 
    //return
    //     ����Բ����ֹ�Ƕ�
    //##ModelId=4B2B8A72014E
    virtual double GetToAngle() = 0;

    //brief
    //     ��ȡ��Բ�İ���
    // 
    //param
    //     drMajor:��������뾶
    //     drMinor:���ش���뾶
    //     drMinorMajorRatio:���ذ뾶��ֵ
    // 
    //##ModelId=4B2B8A720150
    virtual bool GetAxes(double &drMajor, double &drMinor, double &drMinorMajorRatio) = 0;

    //brief
    //     ������Բ����뾶
    // 
    //param
    //     Major:����뾶
    //     dMinorMajorRatio:�뾶��ֵ
    // 
    //##ModelId=4B2B8A720155
    virtual bool SetAxes(double Major, double dMinorMajorRatio) = 0;

    //brief
    //     ������Բ������
    // 
    //param
    //     bStd
    //     rCenter:���ĵ�
    //     rFromPoint:��ʼ��
    //     rToPoint:������
    //     dRotationAngle:������ת�Ƕ�
    //     dMinorMajorRatio:����뾶�볤��뾶��ֵ
    //     Orientation:����
    //     
    //##ModelId=4B2B8A720159
    virtual bool SetCoords(bool bStd, IGeo_Point& rCenter, IGeo_Point& rFromPoint, IGeo_Point& rToPoint, double dRotationAngle, double dMinorMajorRatio, poenumArcOrientation Orientation) = 0;

    //brief
    //     ���ò���ֵ
    // 
    //param
    //     bStd
    //     rCenter:���ĵ�
    //     rFromPoint:��ʼ��
    //     rToPoint:������
    //     dRotationAngle:������ת�Ƕ�
    //     dMinorMajorRatio:����뾶�볤��뾶��ֵ
    //     
    //##ModelId=4B2B8A720162
    virtual bool SetCoordsByAngle(bool bStd, IGeo_Point& rCenter, double dFromAngle, double dCentralAngle, double dRotationAngle, double dMajor, double dMinorMajorRatio) = 0;


    //brief
    //     ��ȡԲ�����ĽǶ�
    // 
    //return
    //     ����Բ�����ĽǶ�
    //##ModelId=4B2B8A72016B
    virtual double GetCentralAngle() = 0;

    //brief
    //     ȡԲ���Ĳ��㲿��
    //     ��Բ������ֹ����л�����
    // 
    //return
    //     �ɹ�����true��
    //##ModelId=4B2B8A72016D
    virtual bool Complement() = 0;

    //brief
    //     �õ�����ֵ
    // 
    //param
    //     bStd
    //     rCenter:���ĵ�
    //     rFromPoint:��ʼ��
    //     rToPoint:������
    //     dRotationAngle:������ת�Ƕ�
    //     dMinorMajorRatio:����뾶�볤��뾶��ֵ
    //     Orientation:����
    //##ModelId=4B2B8A72016F
    virtual bool GetCoords(bool &bStd, IGeo_Point &rCenter, IGeo_Point &rFromPoint, IGeo_Point &rToPoint, double &drRotationAngle, double &drMinorMajorRatio, poenumArcOrientation &rOrientation) = 0;

    //brief
    //     �õ�����ֵ
    // 
    //param
    //     bStd
    //     rCenter:���ĵ�
    //     rFromPoint:��ʼ��
    //     rToPoint:������
    //     dRotationAngle:������ת�Ƕ�
    //     dMinorMajorRatio:����뾶�볤��뾶��ֵ
    //     Orientation:����
    //##ModelId=4B2B8A720178
    virtual bool GetCoordsByAngle(bool &brStd, IGeo_Point &rCenter, double &drFromAngle, double &drCentralAngle, double &drRotationAngle, double &drMajor, double &drMinorMajorRatio) = 0;

};

extern "C" __declspec(dllexport) IGeo_EllipticArc *CreateGeoEllArcIndirect(LOGD_ELLIPTICARC lg);

#endif /* IGEO_ELLIPTICARC_H_HEADER_INCLUDED_B9D36BC7 */
