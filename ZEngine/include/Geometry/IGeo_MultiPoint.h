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
				double Angle_C = GetAngleAngMt(earc.center, pt);//圆心点与已知点的的夹角				
				if(Angle_C < 0) Angle_C += 360;				
				//切线与点心连线夹角
				double Angle_P = RADIAN_TO_ANGLE(asin(earc.radius/dis));//切线与中线的夹角				
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
//     基本几何对象--多点对象接口
//##ModelId=4B2B8A710225
class IGeo_MultiPoint : public IGeo_Geometry
{
  public:
    //brief
    //     设置点坐标。
    //     根据给定的空间参考系设置指定下标的点的坐标    。
    //return
    //     设置成功，则返回true，否则返回false。
    //param
    //     nIndex: 需设置坐标的点的下标。0<=nIndex<点    数
    //     sPoint: 所设置的点坐标。
    //     pSpatialReference: 所设置的点坐标对应的空间    参考系。缺省为NULL，表示使用多点本身的空间    参考系。
    //##ModelId=4B2B8A710233
    virtual bool SetPoint(int nIndex, SPo_DPoint sPoint, IPo_SpatialReference* pSpatialRefernce = NULL) = 0;

    //brief
    //     添加点。
    //     根据给定的空间参考系和下标位置为多点对象添    加一个点。
    //return
    //     添加成功，则返回true，否则返回false。
    //param
    //     sPoint: 所添加的点的坐标。
    //     pSpatialReference: 所添加的点的坐标对应的空    间参考系。缺省为NULL，表示使用多点本身的空    间参考系。
    //##ModelId=4B2B8A710238
    virtual bool AddPoint(int iIndex, SPo_DPoint sPoint, IPo_SpatialReference* pSpatialReference = NULL) = 0;

    //brief
    //     删除点。
    //     根据下标位置删除多点中的一个点。
    //return    
    //     删除成功，则返回true，否则返回false。
    //param
    //     nIndex: 需被删除的点的下标位置。
    //     备注 : 0<=nIndex<点个数；删除点时重新分配内    存；后续点的下标将发生变动，点个数减1。
    //##ModelId=4B2B8A71023D
    virtual bool DeletePoint(int nIndex) = 0;

    //brief
    //     删除点。
    //     根据位置删除多点中的一个点。
    //return
    //     删除成功，则返回true，否则返回false。
    //param
    //     sPoint : 给定的点位置。
    //     dTolerance : 坐标位置阈值。
    //     pSpatialReference : 给定位置坐标对应的空间    参考系。缺省为NULL，表示使用多点本身的空间    参考系。
    // 备注 : 以给定点为圆心，dTolerance为半径的圆内多点中的点。
    //##ModelId=4B2B8A710240
    virtual bool DeletePoint(SPo_DPoint sPoint, double dTolerance, IPo_SpatialReference* pSpatialRefernce = NULL) = 0;

    //brief
    //     获取指定位置的点坐标
    //param
    //     iIndex:序数
    //return
    //     点坐标
    //##ModelId=4B2B8A710245
    virtual SPo_DPoint QueryPoint(int iIndex) = 0;

    //brief 
    //     得到点的个数
    //param
    //     无
    //return
    //     点的个数
    //##ModelId=4B2B8A710248
    virtual int PointCount() = 0;

    //brief
    //     替换所有点对象 
    //param
    //     iCount:点个数
    //     pPoints:点对象
    //return
    //     替换成功返回true
    //##ModelId=4B2B8A71024A
    virtual bool SetPoints(
        //parameter:point number
        int iCount, SPo_DPoint* pPoint) = 0;

    //brief 
    //     增加多个点
    //param
    //     iIndex:序数
    //     iCount:点个数
    //     pPoint:点对象
    //return
    //     成功true
    //##ModelId=4B2B8A71024E
    virtual bool AddPoints(int iindex, 
        //brief parameter: point number
        int iCount, 
        //brief parameter:point values
        SPo_DPoint* pPoint) = 0;

    //brief
    //     remove some points
    //param
    //     iIndex:序数
    //     iCount:点个数
    //return
    //     成功返回true
    //##ModelId=4B2B8A710253
    virtual bool DeletePoints(
        //brief parameter:setting position
        int iIndex, 
        //brief parameter:remove points number
        int iCount) = 0;

    //brief
    //     查询指定位置后若干个点
    //param
    //     iIndex:序数
    //     iCount:点个数   
    //     pPoint:返回点对象
    //return
    //     成功true
    //##ModelId=4B2B8A710257
    virtual bool QueryPoints(int iIndex, int iCount, SPo_DPoint* pPoint) = 0;

};
extern "C" __declspec(dllexport) IGeo_MultiPoint *CreateGeoMultiPointIndirect(LOGD_MULTIPOINT lg);

#endif /* IGEO_MULTIPOINT_H_HEADER_INCLUDED_B9D34F72 */
