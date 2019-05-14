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
	//////未解决计算到的结尾端点在角平分线的哪个方向上？//解决
	template<class TYPE1,class TYPE2,class TYPE3,class TYPE4> void ConstructAngleBisector(SPo_TplPoint2D<TYPE1> S_pt, SPo_TplPoint2D<TYPE2> C_pt, SPo_TplPoint2D<TYPE3> E_pt, TYPE4 fLength, bool bUseAcuteAngle)//始点、中点、末点、长度、是否锐角
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
//     线段几何对象接口
//     连接两点之间的直线段对象，是最简单的线对象
//##ModelId=4B2B8A710281
class IGeo_Line : public IGeo_Curve
{
  public:
	//##ModelId=4B2B8A710283
	virtual LOG_LINE<double> GetLogLine() = 0;

	//##ModelId=4B2B8A710285
	virtual void SetLogLine(LOG_LINE<double> log) = 0;
    //brief
    //     判断给定的点是否在线段上
    //     根据给定的点及空间参考系判断其是否在线段上。
    // 
    //return
    //     位于线段上，则返回true，否则返回false。
    // 
    //param
    //     sPoint: 需要判断的点坐标。
    //     dTolerance 判断阈值。
    //     pSpatialReference: 点坐标对应的空间参考系。缺省为NULL，表示使用线段本身的空间参考系。
    //##ModelId=4B2B8A710288
    virtual bool IsPointOnLine(SPo_DPoint sPoint, IPo_SpatialReference* pSpatialReference = NULL, double dTolerance = 0.0) = 0;

    //brief
    //     判断给定的点对象是否在线段上
    // 
    //return
    //     位于线段上，则返回true，否则返回false。
    // 
    //param
    //     pPoint: 需要判断的点对象。
    //     dTolerance 判断阈值。
    //##ModelId=4B2B8A710290
    virtual bool IsPointOnLine(const IGeo_Geometry* pPoint, double dTolerance = 0.0) = 0;

    //brief
    //     获取线段与x轴正向夹角
    // 
    //return
    //     返回夹角
    //     备注 : 线段方向为起点至终点，返回值为0－2*Pi
    //##ModelId=4B2B8A710294
    virtual double GetAngle() = 0;

    //brief
    //     求两直线段的交点
    // 
    //return
    //     没有交点返回0，一个交点返回1，相交为线段返回2
    // 
    //param
    //     pGeo: 求与相交的线对象
    //     sPoint: 交点
    //     sLinePt: 相交线段的另一端点
    //     pSpatialReference: 输出点坐标对应的空间参考系。缺省为NULL，表示使用主线段(this)的空间参考系。
    //##ModelId=4B2B8A710296
    virtual int GetCross(const IGeo_Geometry* pGeo, SPo_DPoint& sPoint, SPo_DPoint& sLinePt, IPo_SpatialReference* pSpatialReference = NULL) = 0;

};

extern "C" __declspec(dllexport) IGeo_Line *CreateGeoLineIndirect(LOGD_LINE lg);

#endif /* IGEO_LINE_H_HEADER_INCLUDED_B9D314AF */
