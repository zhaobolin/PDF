#ifndef IGEO_CIRCULARARC_H_HEADER_INCLUDED_B9D3382A
#define IGEO_CIRCULARARC_H_HEADER_INCLUDED_B9D3382A
#include "IGeo_Curve.h"

class IPo_SpatialReference;
class IGeo_Geometry;

//////////////////////////////////////////////////////////////////////////
//##ModelId=4B2B8A75002E
template <class TYPE> class CArcIterativeObj  
{
public:
	//##ModelId=4B2B8A75003F
	CArcIterativeObj()
	{
		m_fArc		= 0.;
		m_fChord	= 0.;
		m_fTangent	= 0.;
		
	};
	//##ModelId=4B2B8A750040
	virtual ~CArcIterativeObj(){};

	//----------------用弧长和切线长求半径和弧心角-----------------
	//##ModelId=4B2B8A750042
	TYPE Arc_Tangent_f(TYPE x)//原函数
	{
		TYPE	y = TYPE(tan(x/2)/x - m_fTangent/m_fArc);
		
		return   (y);   
	}
	//##ModelId=4B2B8A750044
	TYPE Arc_Tangent_g(TYPE x)//导函数
	{
		TYPE	y = TYPE(1/(2*x*cos(x/2)*cos(x/2))) - tan(x/2)/(x*x);

		return  (y);   		
	}
	//##ModelId=4B2B8A750046
	TYPE Arc_Tangent_s(TYPE x)////迭代函数
	{
		TYPE   y = x-(TYPE)Arc_Tangent_f(x)/Arc_Tangent_g(x);   
		return (y);   
		
	}
	//##ModelId=4B2B8A750048
	TYPE Arc_Tangent_course(TYPE X0, TYPE e, int n)//迭代过程函数
	{
		TYPE   X1;      
		
		for(int k=1;k<=n;k++)   
		{
			if(Arc_Tangent_g(X0)==0)   break;
			else
			{
				X1=Arc_Tangent_s(X0);
				if(fabs(X1-X0) < e && fabs(Arc_Tangent_f(X1)) < e)   
				{
					break;
				}
				else
				{
					if(k==n)	break;
					else X0 = X1;
				}
			}
		}
		return X1;
	}
	//-------------------------------------------------------------

	//------------------用弧长和弦长求半径和弧心角-----------------------
	//##ModelId=4B2B8A750050
	TYPE Arc_Chord_f(TYPE x)//原函数
	{
		TYPE   y = (TYPE)(2*sin(x/2)/x)-m_fChord/m_fArc;   
		return   y;   		
	}
	//##ModelId=4B2B8A750052
	TYPE Arc_Chord_g(TYPE x)//导函数
	{
		TYPE   y = (TYPE)(cos(x/2)/x - 2*sin(x/2)/(x*x));   
		return   y;   				
	}
	//##ModelId=4B2B8A750054
	TYPE Arc_Chord_s(TYPE x)////迭代函数
	{
		TYPE   y = (TYPE)(x-Arc_Chord_f(x)/Arc_Chord_g(x));   
		return   y;   		
	}
	template <class TYPE1> TYPE Arc_Chord_course(TYPE X0, TYPE e, TYPE1 n)//迭代过程函数
	{
		TYPE   X1;      
		
		for(TYPE1 k=1;k<=n;k++)   
		{
			if(Arc_Chord_g(X0)==0)   break;
			else
			{
				X1=Arc_Chord_s(X0);
				if(fabs(X1-X0)<e)   
				{
					break;
				}
				else
				{
					if(k==n)	break;
					else X0 = X1;
				}
			}
		}
		return X1;
		
	}
	//------------------用弦长和切线长求半径和弧心角-----------------------
	//##ModelId=4B2B8A750056
	TYPE Chord_Tangent_f(TYPE x)//原函数
	{
		TYPE	y = TYPE(2*cos(x/2)) - m_fChord/m_fTangent; 
		return  y;   				
	}
	//##ModelId=4B2B8A750058
	TYPE Chord_Tangent_g(TYPE x)//导函数
	{
		TYPE	y = -sin(x/2);   
		return  y;   						
	}
	//##ModelId=4B2B8A75005A
	TYPE Chord_Tangent_s(TYPE x)////迭代函数
	{
		TYPE   y = (TYPE)(x-Chord_Tangent_f(x)/Chord_Tangent_g(x));   
		return   y;   				
	}
	template <class TYPE1> TYPE Chord_Tangent_course(TYPE X0, TYPE e, TYPE1 n)//迭代过程函数
	{
		TYPE   X1;      
		
		for(TYPE1 k=1;k<=n;k++)   
		{
			if(Chord_Tangent_g(X0)==0)   break;
			else
			{
				X1 = Chord_Tangent_s(X0);
				
				if(fabs(X1-X0) < e && fabs(Chord_Tangent_f(X1)) < e)   
				{
					break;
				}
				else
				{
					if(k==n)	break;
					else X0 = X1;
				}
			}
		}
		return X1;		
	}
	//--------------------------------------------------------------
	//##ModelId=4B2B8A75005E
	void	SetArcNum(TYPE arc)
	{
		m_fArc = arc;
	}
	//##ModelId=4B2B8A750060
	void	SetChordNum(TYPE chord)
	{
		m_fChord = chord;
	}
	//##ModelId=4B2B8A750062
	void	SetTangentNum(TYPE tangent)
	{
		m_fTangent = tangent;
	}

private:
	//##ModelId=4B2B8A750064
	TYPE m_fArc;
	//##ModelId=4B2B8A750065
	TYPE m_fChord;
	//##ModelId=4B2B8A750066
	TYPE m_fTangent;
};

//##ModelId=4B2B8A75006D
typedef CArcIterativeObj<double> CArcIterativeObjD;
//##ModelId=4B2B8A720181
template <class TYPE> struct LOG_CIRCULARARC
{
public:
	//##ModelId=4B2B8A720189
	SPo_TplPoint2D<TYPE> center;
	//##ModelId=4B2B8A72018D
	TYPE radius;
	//##ModelId=4B2B8A720196
	double beginAngle;//按照角度来度量的开始角
	//##ModelId=4B2B8A720197
	double endAngle;//按照角度来度量的终止角
	//##ModelId=4B2B8A7201A5
	bool bccw;//圆弧走向是否顺逆时针
public:
	//##ModelId=4B2B8A7201A6
	SPo_TplRect<TYPE> GetBoundsRect()
	{
		SPo_TplRect<TYPE> boundRect;
		boundRect.left	 = center.x	 - radius;
		boundRect.right	 = center.x	 + radius;
		boundRect.top	 = center.y	 - radius;
		boundRect.bottom = center.y	 + radius;
		
		return boundRect;
	}
	// 得到起点
	//##ModelId=4B2B8A7201A7
	SPo_TplPoint2D<TYPE> GetStartPoint()
	{
		SPo_TplPoint2D<TYPE>	startPoint;	
		double	dRadian = ANGLE_TO_RADIAN( beginAngle );		
		startPoint.x = center.x + radius* cos( dRadian );
		startPoint.y = center.y + radius* sin( dRadian );		
		return startPoint;
	}
	
	// 得到终点	
	//##ModelId=4B2B8A7201B5
	SPo_TplPoint2D<TYPE> GetEndPoint()
	{
		SPo_TplPoint2D<TYPE>	 endPoint;		
		double	dRadian = ANGLE_TO_RADIAN( endAngle );		
		endPoint.x = center.x + radius* cos ( dRadian );
		endPoint.y = center.y + radius* sin ( dRadian );		
		return endPoint;
	}
	//##ModelId=4B2B8A7201B6
	void OnDraw(CDC *pDC)
	{
		SPo_TplRect<TYPE> bound=GetBoundsRect();
		SPo_TplPoint2D<TYPE> startPoint = GetStartPoint();
		SPo_TplPoint2D<TYPE> endPoint = GetEndPoint();
		
		//---------------------------uyyuiuyrtyu----------------------------
		pDC->SetArcDirection(bccw?AD_COUNTERCLOCKWISE:AD_CLOCKWISE);    // 顺时针
		pDC->Arc(int(bound.left),
			int(bound.top), 
			int(bound.right), 
			int(bound.bottom), 
			int(startPoint.x), 
			int(startPoint.y), 
			int(endPoint.x), 
			int(endPoint.y));
		
	}
	//##ModelId=4B2B8A7201C5
	void OnDrawGp(Graphics *pGp)
	{
	}
	//-----------------交换起止角度----------------
	//##ModelId=4B2B8A7201C7
	void SwapBeginEndAngle()
	{
		TYPE tmp;		
		tmp				= beginAngle;
		beginAngle		= endAngle;
		endAngle		= tmp;
	}
	////圆心、圆弧始点、圆弧走向是否逆时针、圆弧长度四条件创建圆弧
	template<class TYPE1,class TYPE2> void ConstructArcDistance(SPo_TplPoint2D<TYPE1> C_pt, SPo_TplPoint2D<TYPE2> S_pt, bool bCCW, double ArcDistance)
	{
		bccw = bCCW;
		center		= SPo_TplPoint2D<TYPE>((TYPE)(C_pt.x),(TYPE)(C_pt.y));
		radius		= (TYPE)(sqrt(pow(C_pt.x - S_pt.x, 2) + pow(C_pt.y - S_pt.y, 2)));
		beginAngle	= GetAngleAngMt(C_pt, S_pt);
		
		if(bCCW) endAngle	= beginAngle - RADIAN_TO_ANGLE(ArcDistance/radius);//注意：
		else endAngle		= beginAngle + RADIAN_TO_ANGLE(ArcDistance/radius);//在直角坐标系下这两个需要互换
	}
	////始点、圆弧走向是否逆时针、圆弧夹角\角度(0~2PI)、圆弧长度
	template<class TYPE1> void ConstructBearingAngleArc(SPo_TplPoint2D<TYPE1> S_pt, double Angle/*以度计量的角度值*/, bool bCCW, double angle_c, double ArcDistance)
	{
		if(angle_c == 0)	return;		
		bccw		= bCCW;		
		radius		= (TYPE)(ArcDistance/(angle_c*PO_PI/180));
		beginAngle		= Angle;		
		if(bCCW)endAngle	= Angle - angle_c;//注意：
		else	endAngle	= Angle + angle_c;//在直角坐标系下这两个需要互换
		SPo_TplPoint2D<TYPE1> tcenter = GetPtFromPtAndLength(radius, S_pt, ANGLE_TO_RADIAN(beginAngle));
		center		= SPo_TplPoint2D<TYPE>((TYPE)(tcenter.x),(TYPE)(tcenter.y));
	}
	////起始点、起始角度、圆弧走向是否逆时针、圆心角、圆弧长度
	template<class TYPE1> void ConstructBearingAngleChord(SPo_TplPoint2D<TYPE1> S_pt, double Angle/*以度计量的角度值*/, bool bCCW, double angle_c, double ChordDistance)
	{
		if(angle_c == 0)	return;
		bccw		= bCCW;		
		beginAngle		= Angle;		
		if(bCCW)endAngle	= Angle - angle_c;//注意：
		else	endAngle	= Angle + angle_c;//在直角坐标系下这两个需要互换		
		radius		= (TYPE)(ChordDistance/(2*sin(ANGLE_TO_RADIAN(Angle)/2)));
		SPo_TplPoint2D<TYPE1> tcenter = GetPtFromPtAndLength(radius, S_pt, ANGLE_TO_RADIAN(beginAngle));
		center		= SPo_TplPoint2D<TYPE>((TYPE)(tcenter.x),(TYPE)(tcenter.y));
	}
	////起始点、起始角度、圆弧走向是否逆时针、圆弧夹角、切线距离
	template<class TYPE1> void ConstructBearingAngleTangent(SPo_TplPoint2D<TYPE1> S_pt, double Angle/*以度计量的角度值*/, bool bCCW, double angle_c, double TangentDistance)
	{
		if(angle_c == 0)	return;		
		bccw		= bCCW;		
		beginAngle		= Angle;		
		if(bCCW)endAngle	= Angle - angle_c;//注意：
		else	endAngle	= Angle + angle_c;//在直角坐标系下这两个需要互换		
		radius		= (TYPE)(TangentDistance/tan(ANGLE_TO_RADIAN(90 - angle_c/2)));
		SPo_TplPoint2D<TYPE1> tcenter = GetPtFromPtAndLength(radius, S_pt, ANGLE_TO_RADIAN(beginAngle));
		center		= SPo_TplPoint2D<TYPE>((TYPE)(tcenter.x),(TYPE)(tcenter.y));
	}
	////起始点、起始角度、圆弧走向是否逆时针、圆弧长度、切线距离-------------试验----------新加
	template<class TYPE1> void ConstructBearingArcTangent(SPo_TplPoint2D<TYPE1> S_pt,  double Angle/*以度计量的角度值*/, bool bCCW, double ArcDistance, double TangentDistance)
	{
		beginAngle = Angle;		
		CArcIterativeObjD obj;
		obj.SetArcNum(ArcDistance);
		obj.SetTangentNum(TangentDistance);		
		TYPE	CentralRadian = fabs(obj.Arc_Tangent_course(2, 0.000001, 100));//初值，精度，迭代次数		
		if(CentralRadian == 0)	return;		
		radius = (TYPE)(ArcDistance/CentralRadian);
		bccw		= bCCW;		
		TYPE	CentralAngle = RADIAN_TO_ANGLE(CentralRadian);		
		if(bCCW)endAngle	= Angle - CentralAngle;//注意：
		else	endAngle	= Angle + CentralAngle;//在直角坐标系下这两个需要互换	
		SPo_TplPoint2D<TYPE1> tcenter = GetPtFromPtAndLength(radius, S_pt, ANGLE_TO_RADIAN(beginAngle));
		center		= SPo_TplPoint2D<TYPE>((TYPE)(tcenter.x),(TYPE)(tcenter.y));
	}
	////起始点、起始角、圆弧走向是否逆时针、弦长、弧长
	template<class TYPE1> void ConstructBearingChordArc(SPo_TplPoint2D<TYPE1> S_pt, double Angle/*以度计量的角度值*/, bool bCCW, double ChordDistance, double ArcDistance)
	{
		beginAngle = Angle;		
		CArcIterativeObjD obj;
		obj.SetArcNum(ArcDistance);
		obj.SetChordNum(ChordDistance);		
		TYPE	CentralRadian = fabs(obj.Arc_Chord_course(2, 0.000001, 100));//初值，精度，迭代次数		
		if(CentralRadian == 0)	return;		
		radius = (TYPE)(ArcDistance/CentralRadian);
		bccw = bCCW;		
		TYPE	CentralAngle = RADIAN_TO_ANGLE(CentralRadian);		
		if(bCCW)endAngle	= Angle - CentralAngle;//注意：
		else	endAngle	= Angle + CentralAngle;//在直角坐标系下这两个需要互换	
		SPo_TplPoint2D<TYPE1> tcenter = GetPtFromPtAndLength(radius, S_pt, ANGLE_TO_RADIAN(beginAngle));
		center		= SPo_TplPoint2D<TYPE>((TYPE)(tcenter.x),(TYPE)(tcenter.y));
	}
	////起始点、起始角、圆弧走向是否逆时针、弦长、切线距离
	template<class TYPE1> void ConstructBearingChordTangent(SPo_TplPoint2D<TYPE1> S_pt, double Angle/*以度计量的角度值*/, bool bCCW, double ChordDistance, double TangentDistance)
	{
		beginAngle = Angle;		
		CArcIterativeObjD obj;
		obj.SetTangentNum(TangentDistance);
		obj.SetChordNum(ChordDistance);		
		TYPE	CentralRadian = fabs(obj.Chord_Tangent_course(2, 0.000001, 100));//初值，精度，迭代次数		
		if(CentralRadian == 0)	return;		
		radius = (TYPE)(ChordDistance/(2*sin(CentralRadian/2)));
		bccw		= bCCW;		
		TYPE	CentralAngle = RADIAN_TO_ANGLE(CentralRadian);		
		if(bCCW)endAngle	= Angle - CentralAngle;//注意：
		else	endAngle	= Angle + CentralAngle;//在直角坐标系下这两个需要互换
		SPo_TplPoint2D<TYPE1> tcenter = GetPtFromPtAndLength(radius, S_pt, ANGLE_TO_RADIAN(beginAngle));
		center		= SPo_TplPoint2D<TYPE>((TYPE)(tcenter.x),(TYPE)(tcenter.y));
	}
	////起始点、起始角、圆弧走向是否逆时针、半径、夹角
	template<class TYPE1> void ConstructBearingRadiusAngle(SPo_TplPoint2D<TYPE1> S_pt, double Angle/*以度计量的角度值*/, bool bCCW, double Radiu, double CentralAngle)
	{
		if(CentralAngle == 0)	return;		
		bccw		= bCCW;		
		beginAngle	= Angle;		
		if(bCCW)endAngle	= Angle - CentralAngle;//注意：
		else	endAngle	= Angle + CentralAngle;//在直角坐标系下这两个需要互换		
		radius		= (TYPE)Radiu;
		SPo_TplPoint2D<TYPE1> tcenter = GetPtFromPtAndLength(radius, S_pt, ANGLE_TO_RADIAN(beginAngle));
		center		= SPo_TplPoint2D<TYPE>((TYPE)(tcenter.x),(TYPE)(tcenter.y));	
	}
	////起始点、起始角、圆弧走向是否逆时针、半径、弧长
	template<class TYPE1> void ConstructBearingRadiusArc(SPo_TplPoint2D<TYPE1> S_pt, double Angle/*以度计量的角度值*/, bool bCCW, double Radiu, double ArcDistance)
	{
		if(ArcDistance == 0)	return;		
		bccw		= bCCW;		
		radius		= (TYPE)Radiu;		
		TYPE CentralAngle		= RADIAN_TO_ANGLE(ArcDistance/Radiu);		
		beginAngle	= Angle;		
		if(bCCW)endAngle	= Angle - CentralAngle;//注意：
		else	endAngle	= Angle + CentralAngle;//在直角坐标系下这两个需要互换
		SPo_TplPoint2D<TYPE1> tcenter = GetPtFromPtAndLength(radius, S_pt, ANGLE_TO_RADIAN(beginAngle));
		center		= SPo_TplPoint2D<TYPE>((TYPE)(tcenter.x),(TYPE)(tcenter.y));
	}
	////起始点、起始角、圆弧走向是否逆时针、半径、弦长、是否劣弧(所占圆心角<PI,否则优弧)
	template<class TYPE1> void ConstructBearingRadiusChord(SPo_TplPoint2D<TYPE1> S_pt, double Angle/*以度计量的角度值*/, bool bCCW, double Radiu, double ChordDistance, bool bMinor)
	{
		if(ChordDistance == 0)	return;		
		bccw		= bCCW;		
		radius		= (TYPE)Radiu;		
		TYPE CentralAngle	= 2 * RADIAN_TO_ANGLE(asin(ChordDistance/(2*Radiu)));		
		beginAngle	= Angle;		
		if(bCCW)endAngle	= Angle - CentralAngle;//注意：
		else	endAngle	= Angle + CentralAngle;//在直角坐标系下这两个需要互换
		SPo_TplPoint2D<TYPE1> tcenter = GetPtFromPtAndLength(radius, S_pt, ANGLE_TO_RADIAN(beginAngle));		
		center		= SPo_TplPoint2D<TYPE>((TYPE)(tcenter.x),(TYPE)(tcenter.y));
		if(!bMinor)	SwapBeginEndAngle();
	}
	////起始点、起始角、圆弧走向是否逆时针、半径、切线距离
	template<class TYPE1> void ConstructBearingRadiusTangent(SPo_TplPoint2D<TYPE1> S_pt, double Angle/*以度计量的角度值*/, bool bCCW, double Radiu, double TangentDistance)
	{
		radius = (TYPE)Radiu;
		TYPE CentralAngle	= 2 * RADIAN_TO_ANGLE(atan(TangentDistance/Radiu));
		bccw		= bCCW;
		beginAngle	= Angle;
		if(bCCW)endAngle	= Angle - CentralAngle;//注意：
		else	endAngle	= Angle + CentralAngle;//在直角坐标系下这两个需要互换
		SPo_TplPoint2D<TYPE1> tcenter = GetPtFromPtAndLength(Radiu, S_pt, ANGLE_TO_RADIAN(beginAngle));
		center		= SPo_TplPoint2D<TYPE>((TYPE)(tcenter.x),(TYPE)(tcenter.y));
	}
	////圆心、始点坐标、圆弧走向是否逆时针、弦长
	template<class TYPE1,class TYPE2> void ConstructChordDistance(SPo_TplPoint2D<TYPE1> C_pt, SPo_TplPoint2D<TYPE2> S_pt, bool bCCW, double ChordDistance)
	{
		center		= SPo_TplPoint2D<TYPE>((TYPE)(C_pt.x),(TYPE)(C_pt.y));		
		radius		= (TYPE)(sqrt(pow(C_pt.x - S_pt.x, 2) + pow(C_pt.y - S_pt.y, 2)));
		beginAngle	= GetAngleAngMt(C_pt, S_pt);		
		double CentreRadian	= fabs(asin(ChordDistance/2*radius));		
		bccw		= bCCW;		
		double CentralAngle	= RADIAN_TO_ANGLE(CentreRadian);		
		if(bCCW)endAngle	= beginAngle - CentralAngle;//注意：
		else	endAngle	= beginAngle + CentralAngle;//在直角坐标系下这两个需要互换
	}
	//圆心、半径、圆弧走向是否逆时针
	template<class TYPE1> void ConstructCircle(SPo_TplPoint2D<TYPE1> C_pt, double Radiu, bool bCCW)
	{
		center		= SPo_TplPoint2D<TYPE>((TYPE)(C_pt.x),(TYPE)(C_pt.y));	
		radius = (TYPE)Radiu;
		beginAngle = 0;
		endAngle = 360;
	}
	////始点、末点、圆弧走向是否逆时针、夹角
	template<class TYPE1,class TYPE2> void ConstructEndPointsAngle(SPo_TplPoint2D<TYPE1> S_pt, SPo_TplPoint2D<TYPE2> E_pt, bool bCCW, double CentralAngle)
	{
		double CentralRadian = ANGLE_TO_RADIAN(CentralAngle);		
		radius		= (TYPE)(fabs(sqrt(pow(S_pt.x - E_pt.x, 2) + pow(S_pt.y - E_pt.y, 2))/(2*sin(CentralRadian/2))));
		double a = (E_pt.x*E_pt.x - S_pt.x*S_pt.x)/(2*(E_pt.y - S_pt.y)) + (E_pt.y + S_pt.y)/2;
		double b = (E_pt.x - S_pt.x)/(E_pt.y - S_pt.y);
		double c = b * b +1;
		double d = -2*(S_pt.x + b*(a - S_pt.y));
		double e = S_pt.x*S_pt.x + pow(a - S_pt.y, 2) - radius*radius;		
		if(d*d - 4*c*e < 0)	return;
		double TEMP = 0;
		bccw = bCCW;
		if(bCCW)
		{
			double x1 = (-d + sqrt(d*d - 4*c*e))/(2*c);
			double y1 = a - b*x1;		
			center.x = (TYPE)x1;
			center.y = (TYPE)y1;		
			beginAngle	= GetAngleAngMt(center, S_pt);
			endAngle		= GetAngleAngMt(center, E_pt);		
			TEMP = endAngle - beginAngle;
			if(fabs(TEMP - CentralAngle) > 0.01)	SwapBeginEndAngle();		
			//if(!bCCW)	SwapBeginEndAngle();		
			//DrawArc(pDC);		
		}
		else
		{
			double x2 = (-d - sqrt(d*d - 4*c*e))/(2*c);
			double y2 = a - b*x2;
			center.x = (TYPE)x2;
			center.y = (TYPE)y2;		
			beginAngle	= GetAngleAngMt(center, S_pt);
			endAngle	= GetAngleAngMt(center, E_pt);		
			TEMP = endAngle - beginAngle;		
			if(fabs(TEMP - CentralAngle) > 0.01)	SwapBeginEndAngle();		
			//if(!bCCW)	SwapBeginEndAngle();		
			//DrawArc(pDC);
		}
	}
	////始点、末点、圆弧走向是否逆时针、弧长
	template<class TYPE1,class TYPE2> void ConstructEndPointsArc(SPo_TplPoint2D<TYPE1> S_pt, SPo_TplPoint2D<TYPE2> E_pt, bool bCCW, double ArcDistance)
	{
		double	ChordDistance = sqrt(pow(S_pt.x - E_pt.x, 2) + pow(S_pt.y - E_pt.y, 2));
		
		CArcIterativeObjD obj;
		obj.SetArcNum(ArcDistance);
		obj.SetChordNum(ChordDistance);
		
		double	CentralRadian = fabs(obj.Arc_Chord_course(2, 0.000001, 100));//初值，精度，迭代次数
		
		if(CentralRadian == 0)	return;
		
		double	CentralAngle = RADIAN_TO_ANGLE(CentralRadian);
		
		double radiu1 = ArcDistance/CentralRadian;
		
		ConstructEndPointsAngle(S_pt, E_pt, bCCW, CentralAngle/*, pDC*/);
	}
	////始点、末点、圆弧走向是否逆时针、弦高
	template<class TYPE1,class TYPE2> void ConstructEndPointsChordHeight(SPo_TplPoint2D<TYPE1> S_pt, SPo_TplPoint2D<TYPE2> E_pt, bool bCCW, double ChordHeight)
	{
		radius		= (TYPE)((pow(S_pt.x - E_pt.x, 2)/4 + pow(S_pt.y - E_pt.y, 2)/4 + pow(ChordHeight, 2))/(2*ChordHeight));
		double CentralAngle	= RADIAN_TO_ANGLE(2 * asin(sqrt(pow(S_pt.x - E_pt.x, 2) + pow(S_pt.y - E_pt.y, 2))/(2*radius)));
		double a = (E_pt.x*E_pt.x - S_pt.x*S_pt.x)/(2*(E_pt.y - S_pt.y)) + (E_pt.y + S_pt.y)/2;
		double b = (E_pt.x - S_pt.x)/(E_pt.y - S_pt.y);
		double c = b * b +1;
		double d = -2*(S_pt.x + b*(a - S_pt.y));
		double e = S_pt.x*S_pt.x + pow(a - S_pt.y, 2) - radius*radius;
		if(d*d - 4*c*e < 0)	return;
		double TEMP = 0;
		if(bCCW)
		{
			double x1 = (-d + sqrt(d*d - 4*c*e))/(2*c);
			double y1 = a - b*x1;			
			center.x = (TYPE)x1;
			center.y = (TYPE)y1;			
			beginAngle	= GetAngleAngMt(center, S_pt);
			endAngle		= GetAngleAngMt(center, E_pt);			
			TEMP = endAngle - beginAngle;			
			if(fabs(TEMP - CentralAngle) > 0.01)	SwapBeginEndAngle();			
			if(!bCCW)	SwapBeginEndAngle();			
			//if(!bCCW)DrawArc(pDC);
		}
		else
		{
			double x2 = (-d - sqrt(d*d - 4*c*e))/(2*c);
			double y2 = a - b*x2;
			center.x = (TYPE)x2;
			center.y = (TYPE)y2;
			beginAngle	= GetAngleAngMt(center, S_pt);
			endAngle	= GetAngleAngMt(center, E_pt);			
			TEMP = endAngle - beginAngle;			
			if(fabs(TEMP - CentralAngle) > 0.01)	SwapBeginEndAngle();			
			if(!bCCW)	SwapBeginEndAngle();			
			//if(bCCW)DrawArc(pDC);
		}
	}
	////始点、末点、圆弧走向是否逆时针、半径、是否劣弧(所占圆心角<PI,否则优弧)
	template<class TYPE1,class TYPE2> bool ConstructEndPointsRadius(SPo_TplPoint2D<TYPE1> S_pt, SPo_TplPoint2D<TYPE2> E_pt, bool bCCW, double Radiu, bool bMinor)
	{	
		radius = (TYPE)Radiu;
		if(E_pt.y - S_pt.y==0)	return false;
		double a = (E_pt.x*E_pt.x - S_pt.x*S_pt.x)/(2*(E_pt.y - S_pt.y)) + (E_pt.y + S_pt.y)/2;
		double b = (E_pt.x - S_pt.x)/(E_pt.y - S_pt.y);
		double c = b * b +1;
		double d = -2*(S_pt.x + b*(a - S_pt.y));
		double e = S_pt.x*S_pt.x + pow(a - S_pt.y, 2) - radius*radius;		
		if(d*d - 4*c*e < 0)	return false;
		double TEMP = 0;
		if(bCCW)
		{
			double x1 = (-d + sqrt(d*d - 4*c*e))/(2*c);
			double y1 = a - b*x1;			
			center.x = (TYPE)x1;
			center.y = (TYPE)y1;			
			beginAngle	= GetAngleAngMt(center, S_pt);
			endAngle	= GetAngleAngMt(center, E_pt);			
			TEMP = endAngle - beginAngle;			
			if(bMinor&&fabs(TEMP) > 180)	SwapBeginEndAngle();			
			if(!bCCW)	SwapBeginEndAngle();			
			//DrawArc(pDC);
		}
		else
		{
			double x2 = (-d - sqrt(d*d - 4*c*e))/(2*c);
			double y2 = a - b*x2;
			center.x = (TYPE)x2;
			center.y = (TYPE)y2;			
			beginAngle	= GetAngleAngMt(center, S_pt);
			endAngle	= GetAngleAngMt(center, E_pt);			
			TEMP = endAngle - beginAngle;			
			if(bMinor&&fabs(TEMP) > 180)	SwapBeginEndAngle();			
			if(!bCCW)	SwapBeginEndAngle();			
			//DrawArc(pDC);
		}
		return true;
	}
	////始点、末点、圆弧走向是否逆时针、切线距离
	template<class TYPE1,class TYPE2> void ConstructEndPointsTangent(SPo_TplPoint2D<TYPE1> S_pt, SPo_TplPoint2D<TYPE2> E_pt, bool bCCW, double TangentDistance)
	{
		double ChordDistance = sqrt(pow(S_pt.x - E_pt.x, 2) + pow(S_pt.y - E_pt.y, 2));
		
		CArcIterativeObjD obj;
		
		obj.SetTangentNum(TangentDistance);
		obj.SetChordNum(ChordDistance);
		
		double	CentralRadian = fabs(obj.Chord_Tangent_course(2, 0.000001, 100));//初值，精度，迭代次数
		
		if(CentralRadian == 0)	return;
		
		double	CentralAngle = RADIAN_TO_ANGLE(CentralRadian);
		
		ConstructEndPointsAngle(S_pt, E_pt, bCCW, CentralAngle/*, pDC*/);
	}
	//切线1、切线2、弧起点、？
	template<class TYPE1,class TYPE2,class TYPE3,class TYPE4> void ConstructFilletPoint(LOG_LINE<TYPE1> Segment1, LOG_LINE<TYPE2> Segment2, SPo_TplPoint2D<TYPE3> S_pt, SPo_TplPoint2D<TYPE4> hintPoint)//
	{

	}
	//切线1、切线2、半径、？
	template<class TYPE1,class TYPE2,class TYPE3> void ConstructFilletRadius(LOG_LINE<TYPE1> Segment1, LOG_LINE<TYPE2> Segment2, double Radiu, SPo_TplPoint2D<TYPE3> hintPoint)//
	{

	}
	//切线、？、以知点
	template<class TYPE1,class TYPE2> void ConstructTangentAndPoint(LOG_LINE<TYPE1> Segment, bool bAtStart, SPo_TplPoint2D<TYPE2> pt)//
	{
		SPo_TplPoint2D<TYPE1> E_pt;		
		if(bAtStart)	E_pt = Segment.start;
		else			E_pt = Segment.end;		
		double TangentDistance = sqrt(pow(Segment.start.x - Segment.end.x, 2) + pow(Segment.start.y - Segment.end.y, 2));
		ConstructEndPointsTangent(pt, E_pt, true, TangentDistance/*, pDC*/);
	}
	//切线、？、圆弧走向是否逆时针、圆心角、弧长
	template<class TYPE1> void ConstructTangentAngleArc(LOG_LINE<TYPE1> Segment, bool bAtStart, bool bCCW, double CentralAngle, double ArcDistance)//
	{
		//首先要保证Segment为直线,即Segment.start != Segment.end
		if(Segment.end==Segment.start)	return ;		
		double CentralRadian = ANGLE_TO_RADIAN(CentralAngle);
		radius = (TYPE)(ArcDistance/CentralRadian);		
		ConstructTangentRadiusAngle(Segment, bAtStart, bCCW, radius, CentralAngle/*, pDC*/);
	}
	//切线、？、圆弧走向是否逆时针、圆心角、弦长
	template<class TYPE1> void ConstructTangentAngleChord(LOG_LINE<TYPE1> Segment, bool bAtStart, bool bCCW, double CentralAngle, double ChordDistance)//
	{
		//首先要保证Segment为直线,即Segment.start != Segment.end
		if(Segment.end==Segment.start)	return ;		
		double CentralRadian	= ANGLE_TO_RADIAN(CentralAngle);
		radius		= (TYPE)(fabs(ChordDistance/(2*sin(CentralRadian/2))));
		ConstructTangentRadiusAngle(Segment, bAtStart, bCCW, radius, CentralAngle/*, pDC*/);
	}
	//切线、？、圆弧走向是否逆时针、圆心角、切线距离
	template<class TYPE1> void ConstructTangentAngleTangent(LOG_LINE<TYPE1> Segment, bool bAtStart, bool bCCW, double CenterAngle, double TangentDistance)
	{
		double CentralRadian	= ANGLE_TO_RADIAN(CentralAngle);		
		radius		= (TYPE)(fabs(TangentDistance/tan(CentralRadian/2)));
		ConstructTangentRadiusAngle(Segment, bAtStart, bCCW, radius, CentralAngle/*, pDC*/);
	}
	//切线、？、圆弧走向是否逆时针、弧长、切线距离
	template<class TYPE1> void ConstructTangentArcTangent(LOG_LINE<TYPE1> Segment, bool bAtStart, bool bCCW, double ArcDistance, double TangentDistance)
	{
		//beginAngle = Angle;		
		CArcIterativeObjD obj;
		obj.SetArcNum(ArcDistance);
		obj.SetTangentNum(TangentDistance);		
		double	CentralRadian = fabs(obj.Arc_Tangent_course(2, 0.000001, 100));//初值，精度，迭代次数		
		if(CentralRadian == 0)	return;		
		radius = (TYPE)(ArcDistance/CentralRadian);
		double	CentralAngle = RADIAN_TO_ANGLE(CentralRadian);		
		ConstructTangentRadiusAngle(Segment, bAtStart, bCCW, radius, CentralAngle/*, pDC*/);
	}
	//切线、？、圆弧走向是否逆时针、弧长、弧长
	template<class TYPE1> void ConstructTangentChordArc(LOG_LINE<TYPE1> Segment, bool bAtStart, bool bCCW, double ChordDistance, double ArcDistance)
	{
		CArcIterativeObjD obj;
		obj.SetArcNum(ArcDistance);
		obj.SetChordNum(ChordDistance);		
		double	CentralRadian = fabs(obj.Arc_Chord_course(2, 0.000001, 100));//初值，精度，迭代次数		
		if(CentralRadian == 0)	return;		
		radius = (TYPE)(ArcDistance/CentralRadian);
		double	CentralAngle = RADIAN_TO_ANGLE(CentralRadian);		
		ConstructTangentRadiusAngle(Segment, bAtStart, bCCW, radius, CentralAngle/*, pDC*/);
	}
	//切线、？、圆弧走向是否逆时针、弦长、切线距离
	template<class TYPE1> void ConstructTangentChordTangent(LOG_LINE<TYPE1> Segment, bool bAtStart, bool bCCW, double ChordDistance, double TangentDistance)
	{
		CArcIterativeObjD obj;		
		obj.SetTangentNum(TangentDistance);
		obj.SetChordNum(ChordDistance);		
		double	CentralRadian = fabs(obj.Chord_Tangent_course(2, 0.000001, 100));//初值，精度，迭代次数		
		if(CentralRadian == 0)	return;		
		radius = (TYPE)(ChordDistance/(2*sin(CentralRadian/2)));
		double	CentralAngle = RADIAN_TO_ANGLE(CentralRadian);		
		ConstructTangentRadiusAngle(Segment, bAtStart, bCCW, radius, CentralAngle/*, pDC*/);
	}
	//圆心点、始点、圆弧走向是否逆时针、切线距离
	template<class TYPE1,class TYPE2> void ConstructTangentDistance(SPo_TplPoint2D<TYPE1> C_pt, SPo_TplPoint2D<TYPE2> S_pt, bool bCCW, double TangentDistance)
	{
		bccw		= bCCW;		
		center		= SPo_TplPoint2D<TYPE>((TYPE)(C_pt.x),(TYPE)(C_pt.y));
		radius		= (TYPE)(sqrt(pow(C_pt.x - S_pt.x, 2) + pow(C_pt.y - S_pt.y, 2)));
		beginAngle	= GetAngleAngMt(C_pt, S_pt);		
		double CentralRadian	= fabs(2*atan(TangentDistance/radius));		
		if(bCCW)endAngle	= Angle - CentralAngle;//注意：
		else	endAngle	= Angle + CentralAngle;//在直角坐标系下这两个需要互换
	}
	//切线、？、圆弧走向是否逆时针、半径、圆心角
	template<class TYPE1> void ConstructTangentRadiusAngle(LOG_LINE<TYPE1> Segment, bool bAtStart, bool bCCW, double Radius, double CentralAngle)
	{
		//首先要保证Segment为直线,即Segment.start != Segment.end
		if(Segment.end==Segment.start)	return ;
		bccw = bCCW;		
		radius = (TYPE)Radius;		
		SPo_TplPoint2D<TYPE1> S_pt;//圆弧端点
		SPo_TplPoint2D<TYPE1> O_pt;//直线另一点		
		double CentralRadian = ANGLE_TO_RADIAN(CentralAngle);		
		if(bAtStart)	{S_pt = Segment.start;O_pt = Segment.end;}
		else			{S_pt = Segment.end;O_pt = Segment.start;}		
		//Segment长度的平方
		double	SegmentLong	= pow(Segment.start.x - Segment.end.x, 2) + pow(Segment.start.y - Segment.end.y, 2);		
		if(S_pt.x == O_pt.x)//当Segment为平行与Y轴的直线时
		{
			double y = (SegmentLong + S_pt.y*S_pt.y - O_pt.y*O_pt.y)/(2*(S_pt.y - O_pt.y));
			
			double a = fabs(Radius*Radius - (y - S_pt.y)*(y - S_pt.y));
			
			//===================第一种解==================
			center.y = (TYPE)y;
			center.x = (TYPE)(S_pt.x + sqrt(a));
			
			beginAngle	= GetAngleAngMt(center, S_pt);
			
			if(bCCW)endAngle	= beginAngle - CentralAngle;//注意：
			else	endAngle	= beginAngle + CentralAngle;//在直角坐标系下这两个需要互换
			
			//DrawArc(pDC);
			//=============================================
			
			//====================第二种解=================
			center.y = (TYPE)y;
			center.x = (TYPE)(S_pt.x - sqrt(a));
			
			beginAngle	= GetAngleAngMt(center, S_pt);
			
			if(bCCW)endAngle	= beginAngle - CentralAngle;//注意：
			else	endAngle	= beginAngle + CentralAngle;//在直角坐标系下这两个需要互换			
			//DrawArc(pDC);
			//=============================================
		}
		else//其他情况
		{
			double	a = (SegmentLong + S_pt.x*S_pt.x - O_pt.x*O_pt.x + S_pt.y*S_pt.y - O_pt.y*O_pt.y)/(2*(S_pt.x - O_pt.x));
			double	b = (O_pt.y - S_pt.y)/(S_pt.x - O_pt.x);
			double	c = a - S_pt.x;
			double	e = b*b + 1;
			double	f = 2*(c*b - S_pt.y);
			double	g = c*c + S_pt.y*S_pt.y - Radius*Radius;
			
			double	h = f*f - 4*e*g;
			if(h >=0)
			{
				//==================第一种解=================
				double y = (-f + sqrt(h))/(2*e);
				
				center.y = (TYPE)y;
				center.x = (TYPE)(a + b*y);
				
				beginAngle	= GetAngleAngMt(center, S_pt);
				
				if(bCCW)endAngle	= beginAngle - CentralAngle;//注意：
				else	endAngle	= beginAngle + CentralAngle;//在直角坐标系下这两个需要互换				
				//DrawArc(pDC);
				//============================================
				if(h == 0)	return;
				//==================第二种解=================//这儿有问题
				double y1 = (-f - sqrt(h))/(2*e);
				
				center.y = (TYPE)y1;
				center.x = (TYPE)(a + b*y1);
				
				beginAngle	= GetAngleAngMt(center, S_pt);//这儿的问题?
				
				if(bCCW)endAngle	= beginAngle - CentralAngle;//注意：
				else	endAngle	= beginAngle + CentralAngle;//在直角坐标系下这两个需要互换				
				//DrawArc(pDC);//这儿的问题?
				//===========================================
			}
			else	return;
		}
	}
	//切线、？、圆弧走向是否逆时针、半径、弧长
	template<class TYPE1> void ConstructTangentRadiusArc(LOG_LINE<TYPE1> Segment, bool bAtStart, bool bCCW, double Radius, double ArcDistance)
	{
		//首先要保证Segment为直线,即Segment.start != Segment.end
		if(Segment.start==Segment.end)	return ;
		double CentralAngle = RADIAN_TO_ANGLE(ArcDistance/Radiu);		
		ConstructTangentRadiusAngle(Segment, bAtStart, bCCW, Radius, CentralAngle/*, pDC*/);
	}
	//切线、？、圆弧走向是否逆时针、半径、弦长
	template<class TYPE1> void ConstructTangentRadiusChord(LOG_LINE<TYPE1> Segment, bool bAtStart, bool bCCW, double Radius, double ChordDistance)
	{
		//首先要保证Segment为直线,即Segment.start != Segment.end
		if(Segment.start==Segment.end)	return ;		
		double CentralRadian = 2*asin(ChordDistance/(2*Radius));		
		double CentralAngle = RADIAN_TO_ANGLE(CentralRadian);		
		ConstructTangentRadiusAngle(Segment, bAtStart, bCCW, Radius, CentralAngle/*, pDC*/);//
	}
	//切线、？、圆弧走向是否逆时针、半径、切线距离
	template<class TYPE1> void ConstructTangentRadiusTangent(LOG_LINE<TYPE1> Segment, bool bAtStart, bool bCCW, double Radius, double TangentDistance)
	{
		//首先要保证Segment为直线,即Segment.start != Segment.end
		if(Segment.start==Segment.end)	return ;		
		double CentralRadian = 2*fabs(atan(TangentDistance/Radius));		
		double CentralAngle = RADIAN_TO_ANGLE(CentralRadian);		
		ConstructTangentRadiusAngle(Segment, bAtStart, bCCW, Radius, CentralAngle/*, pDC*/);//
	}
	//始点、圆弧中间任一点、终点、是否使用存在的圆心（如果三点在一条直线上，圆心无限远，找不到圆心点）
	template<class TYPE1,class TYPE2,class TYPE3> bool ConstructThreePoint(SPo_TplPoint2D<TYPE1> S_pt, SPo_TplPoint2D<TYPE2> M_pt, SPo_TplPoint2D<TYPE3> E_pt, bool bUseExistingCenter)
	{
		if(M_pt.x - S_pt.x==0||E_pt.x - M_pt.x==0)	return false;
		SPo_TplPoint2D<double>	C_pt;		
		double K1 = (M_pt.y - S_pt.y)/(M_pt.x - S_pt.x);//始点到中点的斜率
		double K2 = (E_pt.y - M_pt.y)/(E_pt.x - M_pt.x);//中点到末点的斜率		
		if(K1 == K2)	return false;//三点在一条直线上,找不到圆心点		
		SPo_TplPoint2D<double> SM_pt;//圆弧上始点到中点的中间点
		SPo_TplPoint2D<double> ME_pt;//圆弧上中点到末点的中间点		
		SM_pt.x = (M_pt.x + S_pt.x)/2;
		SM_pt.y = (M_pt.y + S_pt.y)/2;		
		ME_pt.x	= (E_pt.x + M_pt.x)/2;
		ME_pt.y	= (E_pt.y + M_pt.y)/2;		
		if(K1 != 0 && K2 != 0)
		{
			
			double b1 = SM_pt.y + SM_pt.x/K1;
			double b2 = ME_pt.y + ME_pt.x/K2;			
			if (1/K1 != 0 && 1/K2 != 0)
			{
				C_pt.x = (b2 - b1)*K1*K2/(K1 - K2);
				C_pt.y = b1 -C_pt.x/K1; 
			}
			else if(1/K1 == 0)
			{
				C_pt.y = b1; 
				C_pt.x = (b2 - C_pt.y)*K2;
				
			}
			else if(1/K2 == 0)
			{
				C_pt.y = b2; 
				C_pt.x = (b1 - C_pt.y)*K1;
			}
			else{}
		}
		else if(K1 == 0)
		{
			double b2 = ME_pt.y + ME_pt.x/K2;			
			C_pt.x = SM_pt.x;
			C_pt.y = b2 -C_pt.x/K2;
		}
		else if (K2 == 0)
		{
			double b1 = SM_pt.y + SM_pt.x/K1;			
			C_pt.x = ME_pt.x;
			C_pt.y = b1 -C_pt.x/K1;
		}
		else{}		
		center.x = (TYPE)(C_pt.x);
		center.y = (TYPE)(C_pt.y);
		radius	= (TYPE)(sqrt(pow(C_pt.x - S_pt.x, 2) + pow(C_pt.y - S_pt.y, 2)));
		beginAngle = GetAngleAngMt(C_pt, S_pt);// if(beginAngle < 0)//	beginAngle += 360;
		endAngle	= GetAngleAngMt(C_pt, E_pt); //if(endAngle < 0)//	endAngle += 360;
		//double middleAngle= GetAngleAngMt(C_pt, M_pt);
		return true;
	}
	//创建由三个点确定的内切圆----------------新加-----有问题
	template<class TYPE1,class TYPE2,class TYPE3> void ConstructThreePointIn(SPo_TplPoint2D<TYPE> S_pt, SPo_TplPoint2D<TYPE> M_pt, SPo_TplPoint2D<TYPE> E_pt)
	{
	}
};

//##ModelId=4B2B8A7201D4
typedef LOG_CIRCULARARC<double> LOGD_CIRCULARARC;
//##ModelId=4B2B8A7201D6
typedef LOG_CIRCULARARC<int> LOGI_CIRCULARARC;
//##ModelId=4B2B8A7201E5
typedef LOG_CIRCULARARC<float> LOGF_CIRCULARARC;
//##ModelId=4B2B8A7201F4
typedef LOG_CIRCULARARC<long> LOGL_CIRCULARARC;

//##ModelId=4B2B8A7201F6
template <class TYPE> struct LOG_CIRCLE
{
	//##ModelId=4B2B8A720206
	SPo_TplPoint2D<TYPE> center;
	//##ModelId=4B2B8A72020A
	TYPE radius;
};
//##ModelId=4B2B8A720213
typedef LOG_CIRCLE<double> LOGD_CIRCLE;
//##ModelId=4B2B8A720215
typedef LOG_CIRCLE<int> LOGI_CIRCLE;
//##ModelId=4B2B8A720223
typedef LOG_CIRCLE<float> LOGF_CIRCLE;
//##ModelId=4B2B8A720225
typedef LOG_CIRCLE<long> LOGL_CIRCLE;
//brief
//     圆弧线对象接口
//     它是圆边线的一部分，它由起始点、圆弧组成。
// 圆弧构成方式是三个点确定，第一点圆弧起点，第二点圆弧终点，圆弧方向是从起点到终点的顺时针方向弧段，第三点是圆心。
//##ModelId=4B2B8A720251
class IGeo_CircularArc : public IGeo_Curve
{
  public:
	//##ModelId=4B2B8A720262
	virtual LOG_CIRCULARARC<double> GetLogCircleArc() = 0;

	//##ModelId=4B2B8A720264
	virtual void SetLogCircleArc(LOG_CIRCULARARC<double> log) = 0;
    //brief
    //     设置圆弧圆心点坐标。
    //     根据给定的空间参考系设置圆心点坐标。
    // 
    //return
    //     设置成功，则返回true，否则返回false。
    // 
    //param
    //     sPoint: 圆心坐标。
    //     pSpatialReference: 所设置的圆心坐标对应的空间参考系。缺省为NULL，表示使用圆弧本身的空间参考系。
    //##ModelId=4B2B8A720267
    virtual bool SetCenterPoint(SPo_DPoint sPoint, IPo_SpatialReference* pSpatialReference = NULL) = 0;

    //brief
    //     获取圆弧圆心点坐标。
    //     根据给定的空间参考系获取圆心点坐标。
    // 
    //return
    //     返回圆心点坐标，若空间坐标转换失败则返回    SPo_Point(0,0)。
    // 
    //param
    //     pSpatialReference: 需要返回的圆心坐标对应的空间参考系。缺省为NULL，表示使用圆弧本身的空间参考系。
    //##ModelId=4B2B8A72026B
    virtual SPo_DPoint GetCenterPoint(IPo_SpatialReference* pSpatialReference = NULL) = 0;

    //brief
    //     设置圆弧起点坐标。
    //     根据给定的空间参考系设置圆弧起点坐标。
    // 
    //return
    //     设置成功，则返回true，否则返回false。
    // 
    //param
    //     sPoint: 圆弧起点坐标。
    //     pSpatialReference: 所设置的圆弧起点坐标对应的空间参考系。缺省为NULL，表示使用圆弧本身的空间参考系。
    //##ModelId=4B2B8A72026E
    virtual bool SetStartPoint(SPo_DPoint sPoint, IPo_SpatialReference* pSpatialReference = NULL) = 0;

    //brief
    //     获取圆弧起点坐标。
    //     根据给定的空间参考系获取圆弧起点坐标。
    // 
    //return
    //     返回圆弧起点坐标，若空间坐标转换失败则返回SPo_Point(0,0)。
    // 
    //param
    //     pSpatialReference: 需要返回的圆弧起点坐标对应的空间参考系。缺省为NULL，表示使用圆弧本身的空间参考系。
    //##ModelId=4B2B8A720272
    virtual SPo_DPoint GetStartPoint(IPo_SpatialReference* pSpatialReference = NULL) = 0;

    //brief
    //     设置圆弧终点坐标。
    //     根据给定的空间参考系设置圆弧终点坐标。
    // 
    //return
    //     设置成功，则返回true，否则返回false。
    // 
    //param
    //     sPoint: 圆弧终点坐标。
    //     pSpatialReference: 所设置的圆弧终点坐标对应的空间参考系。缺省为NULL，表示使用圆弧本身的空间参考系。
    //##ModelId=4B2B8A720275
    virtual bool SetEndPoint(SPo_DPoint sPoint, IPo_SpatialReference* pSpatialReference = NULL) = 0;

    //brief
    //     获取圆弧终点坐标。
    //     根据给定的空间参考系获取圆弧终点坐标。
    // 
    //return
    //     返回圆弧起点坐标，若空间坐标转换失败则返回SPo_Point(0,0)。
    // 
    //param
    //     pSpatialReference: 需要返回的圆弧终点坐标对应的空间参考系。缺省为NULL，表示使用圆弧本身的空间参考系。
    //##ModelId=4B2B8A720279
    virtual SPo_DPoint GetEndPoint(IPo_SpatialReference* pSpatialReference = NULL) = 0;

    //brief
    //     设置圆弧半径
    // 
    //param
    //     dRadius 圆弧半径
    //##ModelId=4B2B8A72027C
    virtual void SetRadius(double dRadius) = 0;

    //brief
    //     获取圆弧半径
    // 
    //return
    //     返回圆弧半径
    //##ModelId=4B2B8A72027F
    virtual double GetRadius() = 0;

    //brief
    //     设置圆弧起始角度
    // 
    //param
    //     dAng 圆弧起始角度
    //##ModelId=4B2B8A720281
    virtual void SetFromAngle(double dAng) = 0;

    //brief
    //     获取圆弧起始角度
    // 
    //return
    //     返回圆弧起始角度
    //##ModelId=4B2B8A720284
    virtual double GetFromAngle() = 0;

    //brief
    //     设置圆弧终止角度
    // 
    //param
    //     dAng 圆弧终止角度
    //##ModelId=4B2B8A720286
    virtual void SetToAngle(double dAng) = 0;

    //brief
    //     获取圆弧终止角度
    // 
    //return
    //     返回圆弧终止角度
    //##ModelId=4B2B8A720289
    virtual double GetToAngle() = 0;

    //brief
    //     设置圆弧弦长
    // 
    //param
    //     dLength 圆弧弦长
    //##ModelId=4B2B8A72028B
    virtual void SetChordLength(double dLength) = 0;

    //brief
    //     获取圆弧弦长
    // 
    //return
    //     返回圆弧弦长
    //##ModelId=4B2B8A72028E
    virtual double GetChordLength() = 0;

    //brief
    //     设置圆弧弦高
    // 
    //param
    //     dHeight 圆弧弦高
    //     备注 : 弦高为从弦中点至圆弧的垂直距离，为正值
    //##ModelId=4B2B8A720290
    virtual void SetChordHeight(double dLength) = 0;

    //brief
    //     获取圆弧弦高
    // 
    //return
    //     返回圆弧弦高
    //     备注 : 弦高为从弦中点至圆弧的垂直距离，为正值
    //##ModelId=4B2B8A720293
    virtual double GetChordHeight() = 0;

    //brief
    //     设置圆弧中心角度
    // 
    //param
    //     dAng 圆弧中心角度
    //##ModelId=4B2B8A720295
    virtual void SetCentralAngle(double dAng) = 0;

    //brief
    //     获取圆弧中心角度
    // 
    //return
    //     返回圆弧中心角度
    //##ModelId=4B2B8A720298
    virtual double GetCentralAngle() = 0;

    //brief
    //     创建圆弧的补足部分
    //     新建圆弧的起止点与原有圆弧相反。
    // 
    //     备注 : 新创建的圆弧用完需要进行释放
    //##ModelId=4B2B8A72029A
    virtual IGeo_Geometry* CreateComplement() = 0;

    //brief
    //     取圆弧的补足部分
    //     将圆弧的起止点进行互换。
    // 
    //return
    //     成功返回true。
    //##ModelId=4B2B8A72029C
    virtual bool Complement() = 0;

    //brief
    //     判断给定的点是否在圆弧上
    //     根据给定的点及空间参考系判断其是否在线段上。
    // 
    //return
    //     位于线段上，则返回true，否则返回false。
    // 
    //param
    //     sPoint: 需要判断的点坐标。
    //     dTolerance 判断阈值。
    //     pSpatialReference: 点坐标对应的空间参考系。缺省为NULL，表示使用线段本身的空间参考系。
    //##ModelId=4B2B8A72029E
    virtual bool IsPointOnArc(SPo_DPoint sPoint, double dTolerance = 0.0, IPo_SpatialReference* pSpatialReference = NULL) = 0;

    //brief
    //     判断给定的点对象是否在圆弧上
    // 
    //return
    //     位于线段上，则返回true，否则返回false。
    // 
    //param
    //     pPoint: 需要判断的点对象。
    //     dTolerance 判断阈值。
    //##ModelId=4B2B8A7202A3
    virtual bool IsPointOnArc(const IGeo_Geometry* pPoint, double dTolerance = 0.0) = 0;

};
extern "C" __declspec(dllexport) IGeo_CircularArc *CreateGeoCirArc(LOGD_CIRCULARARC lg);

#endif /* IGEO_CIRCULARARC_H_HEADER_INCLUDED_B9D3382A */
