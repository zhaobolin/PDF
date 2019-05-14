#ifndef IGEO_MULTIPOINT_H_HEADER_INCLUDED_B9D34F72
#define IGEO_MULTIPOINT_H_HEADER_INCLUDED_B9D34F72
#include "IGeo_Geometry.h"
class IPo_SpatialReference;

//##ModelId=4B2B8A710203
template<class TYPE> struct LOG_MULTIPOINT
{
public:
	//##ModelId=4B2B8A710207
	vector<SPo_TplPoint2D<TYPE> > m_tpOrdinates;
public:
	template<class TYPE1> void ConstructArcPoints(LOG_CIRCULARARC<TYPE1> arc)
	{
	}
	template<class TYPE1> void ConstructDivideEqual(LOG_CIRCULARARC<TYPE1> arc, int iNum)
	{
		if(iNum<1)	return ;
		m_tpOrdinates.clear();
		double radian = ANGLE_TO_RADIAN(arc.beginAngle);
		double stepradian = ANGLE_TO_RADIAN(arc.endAngle-arc.beginAngle)/iNum;
		for(int i = 0; i < iNum+1; i++)
		{
			m_tpOrdinates.push_back(SPo_TplPoint2D<TYPE>((TYPE)(arc.center.x + arc.radius * cos(radian)),(TYPE)(arc.center.y + arc.radius * sin(radian))));
			radian += PO_2PI/iNum;
		}
	}
	template<class TYPE1> void ConstructDivideLength(LOG_CIRCLE<TYPE1> circle, double dis)
	{
		m_tpOrdinates.clear();
		int iNum = int(PO_2PI*circle.radius/dis);		
		TYPE radian = 0;	
		for(int i = 0; i < iNum; i++)
		{
			m_tpOrdinates.push_back(SPo_TplPoint2D<TYPE>((TYPE)(circle.center.x + circle.radius * cos(radian)),(TYPE)(circle.center.y + circle.radius * sin(radian))));
			radian += dis/circle.radius;
		}
	}
	//##ModelId=4B2B8A71020B
	void ConstructIntersection()
	{
		return NULL;
	}
	//##ModelId=4B2B8A71020C
	void ConstructIntersectionEx()
	{
		return NULL;
	}
	template<class TYPE1,class TYPE2> void ConstructTangent(LOG_CIRCLE<TYPE1> earc, SPo_TplPoint2D<TYPE2> pt)
	{
		m_tpOrdinates.clear();		
		double MaxAngle = max(earc.beginAngle, earc.endAngle);
		double MinAngle = min(earc.beginAngle, earc.endAngle);
		
		double dis = sqrt(pow(pt.x - earc.center.x, 2) + pow(pt.y - earc.center.y, 2));
		
		if(dis >= earc.radius)
		{
			if(dis == earc.radius)
				m_tpOrdinates.push_back(SPo_TplPoint2D<TYPE>((TYPE)(pt.x),(TYPE)(pt.y)));
			else
			{
				double Angle_C = GetAngleAngMt(earc.center, pt);//Բ�ĵ�����֪��ĵļн�				
				if(Angle_C < 0) Angle_C += 360;				
				//������������߼н�
				double Angle_P = RADIAN_TO_ANGLE(asin(earc.radius/dis));//���������ߵļн�				
				double Angle_T = Angle_C + 90 - Angle_P;				
				if(Angle_T >= MinAngle, Angle_T <= MaxAngle)
				{
					double	dRadian = ANGLE_TO_RADIAN( Angle_T );
					m_tpOrdinates.push_back(SPo_TplPoint2D<TYPE>((TYPE)(earc.center.x + earc.radius* cos ( dRadian )),(TYPE)(earc.center.y + earc.radius* sin ( dRadian ))));
				}				
				double Angle_T1 = Angle_C - (90 - Angle_P);				
				if(Angle_T1 >= MinAngle, Angle_T1 <= MaxAngle)
				{
					double	dRadian1 = ANGLE_TO_RADIAN( Angle_T1 );
					m_tpOrdinates.push_back(SPo_TplPoint2D<TYPE>((TYPE)(earc.center.x + earc.radius* cos ( dRadian1 )),(TYPE)(earc.center.y + earc.radius* sin ( dRadian1 ))));
				}
			}
		}
	}	
};
//##ModelId=4B2B8A710213
typedef LOG_MULTIPOINT<double> LOGD_MULTIPOINT;
//##ModelId=4B2B8A710215
typedef LOG_MULTIPOINT<float> LOGF_MULTIPOINT;
//##ModelId=4B2B8A710217
typedef LOG_MULTIPOINT<int> LOGI_MULTIPOINT;
//##ModelId=4B2B8A710223
typedef LOG_MULTIPOINT<long> LOGL_MULTIPOINT;
//brief
//     �������ζ���--������ӿ�
//##ModelId=4B2B8A710225
class IGeo_MultiPoint : public IGeo_Geometry
{
  public:
    //brief
    //     ���õ����ꡣ
    //     ���ݸ����Ŀռ�ο�ϵ����ָ���±�ĵ������    ��
    //return
    //     ���óɹ����򷵻�true�����򷵻�false��
    //param
    //     nIndex: ����������ĵ���±ꡣ0<=nIndex<��    ��
    //     sPoint: �����õĵ����ꡣ
    //     pSpatialReference: �����õĵ������Ӧ�Ŀռ�    �ο�ϵ��ȱʡΪNULL����ʾʹ�ö�㱾��Ŀռ�    �ο�ϵ��
    //##ModelId=4B2B8A710233
    virtual bool SetPoint(int nIndex, SPo_DPoint sPoint, IPo_SpatialReference* pSpatialRefernce = NULL) = 0;

    //brief
    //     ��ӵ㡣
    //     ���ݸ����Ŀռ�ο�ϵ���±�λ��Ϊ��������    ��һ���㡣
    //return
    //     ��ӳɹ����򷵻�true�����򷵻�false��
    //param
    //     sPoint: ����ӵĵ�����ꡣ
    //     pSpatialReference: ����ӵĵ�������Ӧ�Ŀ�    ��ο�ϵ��ȱʡΪNULL����ʾʹ�ö�㱾��Ŀ�    ��ο�ϵ��
    //##ModelId=4B2B8A710238
    virtual bool AddPoint(int iIndex, SPo_DPoint sPoint, IPo_SpatialReference* pSpatialReference = NULL) = 0;

    //brief
    //     ɾ���㡣
    //     �����±�λ��ɾ������е�һ���㡣
    //return    
    //     ɾ���ɹ����򷵻�true�����򷵻�false��
    //param
    //     nIndex: �豻ɾ���ĵ���±�λ�á�
    //     ��ע : 0<=nIndex<�������ɾ����ʱ���·�����    �棻��������±꽫�����䶯���������1��
    //##ModelId=4B2B8A71023D
    virtual bool DeletePoint(int nIndex) = 0;

    //brief
    //     ɾ���㡣
    //     ����λ��ɾ������е�һ���㡣
    //return
    //     ɾ���ɹ����򷵻�true�����򷵻�false��
    //param
    //     sPoint : �����ĵ�λ�á�
    //     dTolerance : ����λ����ֵ��
    //     pSpatialReference : ����λ�������Ӧ�Ŀռ�    �ο�ϵ��ȱʡΪNULL����ʾʹ�ö�㱾��Ŀռ�    �ο�ϵ��
    // ��ע : �Ը�����ΪԲ�ģ�dToleranceΪ�뾶��Բ�ڶ���еĵ㡣
    //##ModelId=4B2B8A710240
    virtual bool DeletePoint(SPo_DPoint sPoint, double dTolerance, IPo_SpatialReference* pSpatialRefernce = NULL) = 0;

    //brief
    //     ��ȡָ��λ�õĵ�����
    //param
    //     iIndex:����
    //return
    //     ������
    //##ModelId=4B2B8A710245
    virtual SPo_DPoint QueryPoint(int iIndex) = 0;

    //brief 
    //     �õ���ĸ���
    //param
    //     ��
    //return
    //     ��ĸ���
    //##ModelId=4B2B8A710248
    virtual int PointCount() = 0;

    //brief
    //     �滻���е���� 
    //param
    //     iCount:�����
    //     pPoints:�����
    //return
    //     �滻�ɹ�����true
    //##ModelId=4B2B8A71024A
    virtual bool SetPoints(
        //parameter:point number
        int iCount, SPo_DPoint* pPoint) = 0;

    //brief 
    //     ���Ӷ����
    //param
    //     iIndex:����
    //     iCount:�����
    //     pPoint:�����
    //return
    //     �ɹ�true
    //##ModelId=4B2B8A71024E
    virtual bool AddPoints(int iindex, 
        //brief parameter: point number
        int iCount, 
        //brief parameter:point values
        SPo_DPoint* pPoint) = 0;

    //brief
    //     remove some points
    //param
    //     iIndex:����
    //     iCount:�����
    //return
    //     �ɹ�����true
    //##ModelId=4B2B8A710253
    virtual bool DeletePoints(
        //brief parameter:setting position
        int iIndex, 
        //brief parameter:remove points number
        int iCount) = 0;

    //brief
    //     ��ѯָ��λ�ú����ɸ���
    //param
    //     iIndex:����
    //     iCount:�����   
    //     pPoint:���ص����
    //return
    //     �ɹ�true
    //##ModelId=4B2B8A710257
    virtual bool QueryPoints(int iIndex, int iCount, SPo_DPoint* pPoint) = 0;

};
extern "C" __declspec(dllexport) IGeo_MultiPoint *CreateGeoMultiPointIndirect(LOGD_MULTIPOINT lg);

#endif /* IGEO_MULTIPOINT_H_HEADER_INCLUDED_B9D34F72 */
