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

	//----------------�û��������߳���뾶�ͻ��Ľ�-----------------
	//##ModelId=4B2B8A750042
	TYPE Arc_Tangent_f(TYPE x)//ԭ����
	{
		TYPE	y = TYPE(tan(x/2)/x - m_fTangent/m_fArc);
		
		return   (y);   
	}
	//##ModelId=4B2B8A750044
	TYPE Arc_Tangent_g(TYPE x)//������
	{
		TYPE	y = TYPE(1/(2*x*cos(x/2)*cos(x/2))) - tan(x/2)/(x*x);

		return  (y);   		
	}
	//##ModelId=4B2B8A750046
	TYPE Arc_Tangent_s(TYPE x)////��������
	{
		TYPE   y = x-(TYPE)Arc_Tangent_f(x)/Arc_Tangent_g(x);   
		return (y);   
		
	}
	//##ModelId=4B2B8A750048
	TYPE Arc_Tangent_course(TYPE X0, TYPE e, int n)//�������̺���
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

	//------------------�û������ҳ���뾶�ͻ��Ľ�-----------------------
	//##ModelId=4B2B8A750050
	TYPE Arc_Chord_f(TYPE x)//ԭ����
	{
		TYPE   y = (TYPE)(2*sin(x/2)/x)-m_fChord/m_fArc;   
		return   y;   		
	}
	//##ModelId=4B2B8A750052
	TYPE Arc_Chord_g(TYPE x)//������
	{
		TYPE   y = (TYPE)(cos(x/2)/x - 2*sin(x/2)/(x*x));   
		return   y;   				
	}
	//##ModelId=4B2B8A750054
	TYPE Arc_Chord_s(TYPE x)////��������
	{
		TYPE   y = (TYPE)(x-Arc_Chord_f(x)/Arc_Chord_g(x));   
		return   y;   		
	}
	template <class TYPE1> TYPE Arc_Chord_course(TYPE X0, TYPE e, TYPE1 n)//�������̺���
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
	//------------------���ҳ������߳���뾶�ͻ��Ľ�-----------------------
	//##ModelId=4B2B8A750056
	TYPE Chord_Tangent_f(TYPE x)//ԭ����
	{
		TYPE	y = TYPE(2*cos(x/2)) - m_fChord/m_fTangent; 
		return  y;   				
	}
	//##ModelId=4B2B8A750058
	TYPE Chord_Tangent_g(TYPE x)//������
	{
		TYPE	y = -sin(x/2);   
		return  y;   						
	}
	//##ModelId=4B2B8A75005A
	TYPE Chord_Tangent_s(TYPE x)////��������
	{
		TYPE   y = (TYPE)(x-Chord_Tangent_f(x)/Chord_Tangent_g(x));   
		return   y;   				
	}
	template <class TYPE1> TYPE Chord_Tangent_course(TYPE X0, TYPE e, TYPE1 n)//�������̺���
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
	double beginAngle;//���սǶ��������Ŀ�ʼ��
	//##ModelId=4B2B8A720197
	double endAngle;//���սǶ�����������ֹ��
	//##ModelId=4B2B8A7201A5
	bool bccw;//Բ�������Ƿ�˳��ʱ��
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
	// �õ����
	//##ModelId=4B2B8A7201A7
	SPo_TplPoint2D<TYPE> GetStartPoint()
	{
		SPo_TplPoint2D<TYPE>	startPoint;	
		double	dRadian = ANGLE_TO_RADIAN( beginAngle );		
		startPoint.x = center.x + radius* cos( dRadian );
		startPoint.y = center.y + radius* sin( dRadian );		
		return startPoint;
	}
	
	// �õ��յ�	
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
		pDC->SetArcDirection(bccw?AD_COUNTERCLOCKWISE:AD_CLOCKWISE);    // ˳ʱ��
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
	//-----------------������ֹ�Ƕ�----------------
	//##ModelId=4B2B8A7201C7
	void SwapBeginEndAngle()
	{
		TYPE tmp;		
		tmp				= beginAngle;
		beginAngle		= endAngle;
		endAngle		= tmp;
	}
	////Բ�ġ�Բ��ʼ�㡢Բ�������Ƿ���ʱ�롢Բ����������������Բ��
	template<class TYPE1,class TYPE2> void ConstructArcDistance(SPo_TplPoint2D<TYPE1> C_pt, SPo_TplPoint2D<TYPE2> S_pt, bool bCCW, double ArcDistance)
	{
		bccw = bCCW;
		center		= SPo_TplPoint2D<TYPE>((TYPE)(C_pt.x),(TYPE)(C_pt.y));
		radius		= (TYPE)(sqrt(pow(C_pt.x - S_pt.x, 2) + pow(C_pt.y - S_pt.y, 2)));
		beginAngle	= GetAngleAngMt(C_pt, S_pt);
		
		if(bCCW) endAngle	= beginAngle - RADIAN_TO_ANGLE(ArcDistance/radius);//ע�⣺
		else endAngle		= beginAngle + RADIAN_TO_ANGLE(ArcDistance/radius);//��ֱ������ϵ����������Ҫ����
	}
	////ʼ�㡢Բ�������Ƿ���ʱ�롢Բ���н�\�Ƕ�(0~2PI)��Բ������
	template<class TYPE1> void ConstructBearingAngleArc(SPo_TplPoint2D<TYPE1> S_pt, double Angle/*�Զȼ����ĽǶ�ֵ*/, bool bCCW, double angle_c, double ArcDistance)
	{
		if(angle_c == 0)	return;		
		bccw		= bCCW;		
		radius		= (TYPE)(ArcDistance/(angle_c*PO_PI/180));
		beginAngle		= Angle;		
		if(bCCW)endAngle	= Angle - angle_c;//ע�⣺
		else	endAngle	= Angle + angle_c;//��ֱ������ϵ����������Ҫ����
		SPo_TplPoint2D<TYPE1> tcenter = GetPtFromPtAndLength(radius, S_pt, ANGLE_TO_RADIAN(beginAngle));
		center		= SPo_TplPoint2D<TYPE>((TYPE)(tcenter.x),(TYPE)(tcenter.y));
	}
	////��ʼ�㡢��ʼ�Ƕȡ�Բ�������Ƿ���ʱ�롢Բ�Ľǡ�Բ������
	template<class TYPE1> void ConstructBearingAngleChord(SPo_TplPoint2D<TYPE1> S_pt, double Angle/*�Զȼ����ĽǶ�ֵ*/, bool bCCW, double angle_c, double ChordDistance)
	{
		if(angle_c == 0)	return;
		bccw		= bCCW;		
		beginAngle		= Angle;		
		if(bCCW)endAngle	= Angle - angle_c;//ע�⣺
		else	endAngle	= Angle + angle_c;//��ֱ������ϵ����������Ҫ����		
		radius		= (TYPE)(ChordDistance/(2*sin(ANGLE_TO_RADIAN(Angle)/2)));
		SPo_TplPoint2D<TYPE1> tcenter = GetPtFromPtAndLength(radius, S_pt, ANGLE_TO_RADIAN(beginAngle));
		center		= SPo_TplPoint2D<TYPE>((TYPE)(tcenter.x),(TYPE)(tcenter.y));
	}
	////��ʼ�㡢��ʼ�Ƕȡ�Բ�������Ƿ���ʱ�롢Բ���нǡ����߾���
	template<class TYPE1> void ConstructBearingAngleTangent(SPo_TplPoint2D<TYPE1> S_pt, double Angle/*�Զȼ����ĽǶ�ֵ*/, bool bCCW, double angle_c, double TangentDistance)
	{
		if(angle_c == 0)	return;		
		bccw		= bCCW;		
		beginAngle		= Angle;		
		if(bCCW)endAngle	= Angle - angle_c;//ע�⣺
		else	endAngle	= Angle + angle_c;//��ֱ������ϵ����������Ҫ����		
		radius		= (TYPE)(TangentDistance/tan(ANGLE_TO_RADIAN(90 - angle_c/2)));
		SPo_TplPoint2D<TYPE1> tcenter = GetPtFromPtAndLength(radius, S_pt, ANGLE_TO_RADIAN(beginAngle));
		center		= SPo_TplPoint2D<TYPE>((TYPE)(tcenter.x),(TYPE)(tcenter.y));
	}
	////��ʼ�㡢��ʼ�Ƕȡ�Բ�������Ƿ���ʱ�롢Բ�����ȡ����߾���-------------����----------�¼�
	template<class TYPE1> void ConstructBearingArcTangent(SPo_TplPoint2D<TYPE1> S_pt,  double Angle/*�Զȼ����ĽǶ�ֵ*/, bool bCCW, double ArcDistance, double TangentDistance)
	{
		beginAngle = Angle;		
		CArcIterativeObjD obj;
		obj.SetArcNum(ArcDistance);
		obj.SetTangentNum(TangentDistance);		
		TYPE	CentralRadian = fabs(obj.Arc_Tangent_course(2, 0.000001, 100));//��ֵ�����ȣ���������		
		if(CentralRadian == 0)	return;		
		radius = (TYPE)(ArcDistance/CentralRadian);
		bccw		= bCCW;		
		TYPE	CentralAngle = RADIAN_TO_ANGLE(CentralRadian);		
		if(bCCW)endAngle	= Angle - CentralAngle;//ע�⣺
		else	endAngle	= Angle + CentralAngle;//��ֱ������ϵ����������Ҫ����	
		SPo_TplPoint2D<TYPE1> tcenter = GetPtFromPtAndLength(radius, S_pt, ANGLE_TO_RADIAN(beginAngle));
		center		= SPo_TplPoint2D<TYPE>((TYPE)(tcenter.x),(TYPE)(tcenter.y));
	}
	////��ʼ�㡢��ʼ�ǡ�Բ�������Ƿ���ʱ�롢�ҳ�������
	template<class TYPE1> void ConstructBearingChordArc(SPo_TplPoint2D<TYPE1> S_pt, double Angle/*�Զȼ����ĽǶ�ֵ*/, bool bCCW, double ChordDistance, double ArcDistance)
	{
		beginAngle = Angle;		
		CArcIterativeObjD obj;
		obj.SetArcNum(ArcDistance);
		obj.SetChordNum(ChordDistance);		
		TYPE	CentralRadian = fabs(obj.Arc_Chord_course(2, 0.000001, 100));//��ֵ�����ȣ���������		
		if(CentralRadian == 0)	return;		
		radius = (TYPE)(ArcDistance/CentralRadian);
		bccw = bCCW;		
		TYPE	CentralAngle = RADIAN_TO_ANGLE(CentralRadian);		
		if(bCCW)endAngle	= Angle - CentralAngle;//ע�⣺
		else	endAngle	= Angle + CentralAngle;//��ֱ������ϵ����������Ҫ����	
		SPo_TplPoint2D<TYPE1> tcenter = GetPtFromPtAndLength(radius, S_pt, ANGLE_TO_RADIAN(beginAngle));
		center		= SPo_TplPoint2D<TYPE>((TYPE)(tcenter.x),(TYPE)(tcenter.y));
	}
	////��ʼ�㡢��ʼ�ǡ�Բ�������Ƿ���ʱ�롢�ҳ������߾���
	template<class TYPE1> void ConstructBearingChordTangent(SPo_TplPoint2D<TYPE1> S_pt, double Angle/*�Զȼ����ĽǶ�ֵ*/, bool bCCW, double ChordDistance, double TangentDistance)
	{
		beginAngle = Angle;		
		CArcIterativeObjD obj;
		obj.SetTangentNum(TangentDistance);
		obj.SetChordNum(ChordDistance);		
		TYPE	CentralRadian = fabs(obj.Chord_Tangent_course(2, 0.000001, 100));//��ֵ�����ȣ���������		
		if(CentralRadian == 0)	return;		
		radius = (TYPE)(ChordDistance/(2*sin(CentralRadian/2)));
		bccw		= bCCW;		
		TYPE	CentralAngle = RADIAN_TO_ANGLE(CentralRadian);		
		if(bCCW)endAngle	= Angle - CentralAngle;//ע�⣺
		else	endAngle	= Angle + CentralAngle;//��ֱ������ϵ����������Ҫ����
		SPo_TplPoint2D<TYPE1> tcenter = GetPtFromPtAndLength(radius, S_pt, ANGLE_TO_RADIAN(beginAngle));
		center		= SPo_TplPoint2D<TYPE>((TYPE)(tcenter.x),(TYPE)(tcenter.y));
	}
	////��ʼ�㡢��ʼ�ǡ�Բ�������Ƿ���ʱ�롢�뾶���н�
	template<class TYPE1> void ConstructBearingRadiusAngle(SPo_TplPoint2D<TYPE1> S_pt, double Angle/*�Զȼ����ĽǶ�ֵ*/, bool bCCW, double Radiu, double CentralAngle)
	{
		if(CentralAngle == 0)	return;		
		bccw		= bCCW;		
		beginAngle	= Angle;		
		if(bCCW)endAngle	= Angle - CentralAngle;//ע�⣺
		else	endAngle	= Angle + CentralAngle;//��ֱ������ϵ����������Ҫ����		
		radius		= (TYPE)Radiu;
		SPo_TplPoint2D<TYPE1> tcenter = GetPtFromPtAndLength(radius, S_pt, ANGLE_TO_RADIAN(beginAngle));
		center		= SPo_TplPoint2D<TYPE>((TYPE)(tcenter.x),(TYPE)(tcenter.y));	
	}
	////��ʼ�㡢��ʼ�ǡ�Բ�������Ƿ���ʱ�롢�뾶������
	template<class TYPE1> void ConstructBearingRadiusArc(SPo_TplPoint2D<TYPE1> S_pt, double Angle/*�Զȼ����ĽǶ�ֵ*/, bool bCCW, double Radiu, double ArcDistance)
	{
		if(ArcDistance == 0)	return;		
		bccw		= bCCW;		
		radius		= (TYPE)Radiu;		
		TYPE CentralAngle		= RADIAN_TO_ANGLE(ArcDistance/Radiu);		
		beginAngle	= Angle;		
		if(bCCW)endAngle	= Angle - CentralAngle;//ע�⣺
		else	endAngle	= Angle + CentralAngle;//��ֱ������ϵ����������Ҫ����
		SPo_TplPoint2D<TYPE1> tcenter = GetPtFromPtAndLength(radius, S_pt, ANGLE_TO_RADIAN(beginAngle));
		center		= SPo_TplPoint2D<TYPE>((TYPE)(tcenter.x),(TYPE)(tcenter.y));
	}
	////��ʼ�㡢��ʼ�ǡ�Բ�������Ƿ���ʱ�롢�뾶���ҳ����Ƿ��ӻ�(��ռԲ�Ľ�<PI,�����Ż�)
	template<class TYPE1> void ConstructBearingRadiusChord(SPo_TplPoint2D<TYPE1> S_pt, double Angle/*�Զȼ����ĽǶ�ֵ*/, bool bCCW, double Radiu, double ChordDistance, bool bMinor)
	{
		if(ChordDistance == 0)	return;		
		bccw		= bCCW;		
		radius		= (TYPE)Radiu;		
		TYPE CentralAngle	= 2 * RADIAN_TO_ANGLE(asin(ChordDistance/(2*Radiu)));		
		beginAngle	= Angle;		
		if(bCCW)endAngle	= Angle - CentralAngle;//ע�⣺
		else	endAngle	= Angle + CentralAngle;//��ֱ������ϵ����������Ҫ����
		SPo_TplPoint2D<TYPE1> tcenter = GetPtFromPtAndLength(radius, S_pt, ANGLE_TO_RADIAN(beginAngle));		
		center		= SPo_TplPoint2D<TYPE>((TYPE)(tcenter.x),(TYPE)(tcenter.y));
		if(!bMinor)	SwapBeginEndAngle();
	}
	////��ʼ�㡢��ʼ�ǡ�Բ�������Ƿ���ʱ�롢�뾶�����߾���
	template<class TYPE1> void ConstructBearingRadiusTangent(SPo_TplPoint2D<TYPE1> S_pt, double Angle/*�Զȼ����ĽǶ�ֵ*/, bool bCCW, double Radiu, double TangentDistance)
	{
		radius = (TYPE)Radiu;
		TYPE CentralAngle	= 2 * RADIAN_TO_ANGLE(atan(TangentDistance/Radiu));
		bccw		= bCCW;
		beginAngle	= Angle;
		if(bCCW)endAngle	= Angle - CentralAngle;//ע�⣺
		else	endAngle	= Angle + CentralAngle;//��ֱ������ϵ����������Ҫ����
		SPo_TplPoint2D<TYPE1> tcenter = GetPtFromPtAndLength(Radiu, S_pt, ANGLE_TO_RADIAN(beginAngle));
		center		= SPo_TplPoint2D<TYPE>((TYPE)(tcenter.x),(TYPE)(tcenter.y));
	}
	////Բ�ġ�ʼ�����ꡢԲ�������Ƿ���ʱ�롢�ҳ�
	template<class TYPE1,class TYPE2> void ConstructChordDistance(SPo_TplPoint2D<TYPE1> C_pt, SPo_TplPoint2D<TYPE2> S_pt, bool bCCW, double ChordDistance)
	{
		center		= SPo_TplPoint2D<TYPE>((TYPE)(C_pt.x),(TYPE)(C_pt.y));		
		radius		= (TYPE)(sqrt(pow(C_pt.x - S_pt.x, 2) + pow(C_pt.y - S_pt.y, 2)));
		beginAngle	= GetAngleAngMt(C_pt, S_pt);		
		double CentreRadian	= fabs(asin(ChordDistance/2*radius));		
		bccw		= bCCW;		
		double CentralAngle	= RADIAN_TO_ANGLE(CentreRadian);		
		if(bCCW)endAngle	= beginAngle - CentralAngle;//ע�⣺
		else	endAngle	= beginAngle + CentralAngle;//��ֱ������ϵ����������Ҫ����
	}
	//Բ�ġ��뾶��Բ�������Ƿ���ʱ��
	template<class TYPE1> void ConstructCircle(SPo_TplPoint2D<TYPE1> C_pt, double Radiu, bool bCCW)
	{
		center		= SPo_TplPoint2D<TYPE>((TYPE)(C_pt.x),(TYPE)(C_pt.y));	
		radius = (TYPE)Radiu;
		beginAngle = 0;
		endAngle = 360;
	}
	////ʼ�㡢ĩ�㡢Բ�������Ƿ���ʱ�롢�н�
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
	////ʼ�㡢ĩ�㡢Բ�������Ƿ���ʱ�롢����
	template<class TYPE1,class TYPE2> void ConstructEndPointsArc(SPo_TplPoint2D<TYPE1> S_pt, SPo_TplPoint2D<TYPE2> E_pt, bool bCCW, double ArcDistance)
	{
		double	ChordDistance = sqrt(pow(S_pt.x - E_pt.x, 2) + pow(S_pt.y - E_pt.y, 2));
		
		CArcIterativeObjD obj;
		obj.SetArcNum(ArcDistance);
		obj.SetChordNum(ChordDistance);
		
		double	CentralRadian = fabs(obj.Arc_Chord_course(2, 0.000001, 100));//��ֵ�����ȣ���������
		
		if(CentralRadian == 0)	return;
		
		double	CentralAngle = RADIAN_TO_ANGLE(CentralRadian);
		
		double radiu1 = ArcDistance/CentralRadian;
		
		ConstructEndPointsAngle(S_pt, E_pt, bCCW, CentralAngle/*, pDC*/);
	}
	////ʼ�㡢ĩ�㡢Բ�������Ƿ���ʱ�롢�Ҹ�
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
	////ʼ�㡢ĩ�㡢Բ�������Ƿ���ʱ�롢�뾶���Ƿ��ӻ�(��ռԲ�Ľ�<PI,�����Ż�)
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
	////ʼ�㡢ĩ�㡢Բ�������Ƿ���ʱ�롢���߾���
	template<class TYPE1,class TYPE2> void ConstructEndPointsTangent(SPo_TplPoint2D<TYPE1> S_pt, SPo_TplPoint2D<TYPE2> E_pt, bool bCCW, double TangentDistance)
	{
		double ChordDistance = sqrt(pow(S_pt.x - E_pt.x, 2) + pow(S_pt.y - E_pt.y, 2));
		
		CArcIterativeObjD obj;
		
		obj.SetTangentNum(TangentDistance);
		obj.SetChordNum(ChordDistance);
		
		double	CentralRadian = fabs(obj.Chord_Tangent_course(2, 0.000001, 100));//��ֵ�����ȣ���������
		
		if(CentralRadian == 0)	return;
		
		double	CentralAngle = RADIAN_TO_ANGLE(CentralRadian);
		
		ConstructEndPointsAngle(S_pt, E_pt, bCCW, CentralAngle/*, pDC*/);
	}
	//����1������2������㡢��
	template<class TYPE1,class TYPE2,class TYPE3,class TYPE4> void ConstructFilletPoint(LOG_LINE<TYPE1> Segment1, LOG_LINE<TYPE2> Segment2, SPo_TplPoint2D<TYPE3> S_pt, SPo_TplPoint2D<TYPE4> hintPoint)//
	{

	}
	//����1������2���뾶����
	template<class TYPE1,class TYPE2,class TYPE3> void ConstructFilletRadius(LOG_LINE<TYPE1> Segment1, LOG_LINE<TYPE2> Segment2, double Radiu, SPo_TplPoint2D<TYPE3> hintPoint)//
	{

	}
	//���ߡ�������֪��
	template<class TYPE1,class TYPE2> void ConstructTangentAndPoint(LOG_LINE<TYPE1> Segment, bool bAtStart, SPo_TplPoint2D<TYPE2> pt)//
	{
		SPo_TplPoint2D<TYPE1> E_pt;		
		if(bAtStart)	E_pt = Segment.start;
		else			E_pt = Segment.end;		
		double TangentDistance = sqrt(pow(Segment.start.x - Segment.end.x, 2) + pow(Segment.start.y - Segment.end.y, 2));
		ConstructEndPointsTangent(pt, E_pt, true, TangentDistance/*, pDC*/);
	}
	//���ߡ�����Բ�������Ƿ���ʱ�롢Բ�Ľǡ�����
	template<class TYPE1> void ConstructTangentAngleArc(LOG_LINE<TYPE1> Segment, bool bAtStart, bool bCCW, double CentralAngle, double ArcDistance)//
	{
		//����Ҫ��֤SegmentΪֱ��,��Segment.start != Segment.end
		if(Segment.end==Segment.start)	return ;		
		double CentralRadian = ANGLE_TO_RADIAN(CentralAngle);
		radius = (TYPE)(ArcDistance/CentralRadian);		
		ConstructTangentRadiusAngle(Segment, bAtStart, bCCW, radius, CentralAngle/*, pDC*/);
	}
	//���ߡ�����Բ�������Ƿ���ʱ�롢Բ�Ľǡ��ҳ�
	template<class TYPE1> void ConstructTangentAngleChord(LOG_LINE<TYPE1> Segment, bool bAtStart, bool bCCW, double CentralAngle, double ChordDistance)//
	{
		//����Ҫ��֤SegmentΪֱ��,��Segment.start != Segment.end
		if(Segment.end==Segment.start)	return ;		
		double CentralRadian	= ANGLE_TO_RADIAN(CentralAngle);
		radius		= (TYPE)(fabs(ChordDistance/(2*sin(CentralRadian/2))));
		ConstructTangentRadiusAngle(Segment, bAtStart, bCCW, radius, CentralAngle/*, pDC*/);
	}
	//���ߡ�����Բ�������Ƿ���ʱ�롢Բ�Ľǡ����߾���
	template<class TYPE1> void ConstructTangentAngleTangent(LOG_LINE<TYPE1> Segment, bool bAtStart, bool bCCW, double CenterAngle, double TangentDistance)
	{
		double CentralRadian	= ANGLE_TO_RADIAN(CentralAngle);		
		radius		= (TYPE)(fabs(TangentDistance/tan(CentralRadian/2)));
		ConstructTangentRadiusAngle(Segment, bAtStart, bCCW, radius, CentralAngle/*, pDC*/);
	}
	//���ߡ�����Բ�������Ƿ���ʱ�롢���������߾���
	template<class TYPE1> void ConstructTangentArcTangent(LOG_LINE<TYPE1> Segment, bool bAtStart, bool bCCW, double ArcDistance, double TangentDistance)
	{
		//beginAngle = Angle;		
		CArcIterativeObjD obj;
		obj.SetArcNum(ArcDistance);
		obj.SetTangentNum(TangentDistance);		
		double	CentralRadian = fabs(obj.Arc_Tangent_course(2, 0.000001, 100));//��ֵ�����ȣ���������		
		if(CentralRadian == 0)	return;		
		radius = (TYPE)(ArcDistance/CentralRadian);
		double	CentralAngle = RADIAN_TO_ANGLE(CentralRadian);		
		ConstructTangentRadiusAngle(Segment, bAtStart, bCCW, radius, CentralAngle/*, pDC*/);
	}
	//���ߡ�����Բ�������Ƿ���ʱ�롢����������
	template<class TYPE1> void ConstructTangentChordArc(LOG_LINE<TYPE1> Segment, bool bAtStart, bool bCCW, double ChordDistance, double ArcDistance)
	{
		CArcIterativeObjD obj;
		obj.SetArcNum(ArcDistance);
		obj.SetChordNum(ChordDistance);		
		double	CentralRadian = fabs(obj.Arc_Chord_course(2, 0.000001, 100));//��ֵ�����ȣ���������		
		if(CentralRadian == 0)	return;		
		radius = (TYPE)(ArcDistance/CentralRadian);
		double	CentralAngle = RADIAN_TO_ANGLE(CentralRadian);		
		ConstructTangentRadiusAngle(Segment, bAtStart, bCCW, radius, CentralAngle/*, pDC*/);
	}
	//���ߡ�����Բ�������Ƿ���ʱ�롢�ҳ������߾���
	template<class TYPE1> void ConstructTangentChordTangent(LOG_LINE<TYPE1> Segment, bool bAtStart, bool bCCW, double ChordDistance, double TangentDistance)
	{
		CArcIterativeObjD obj;		
		obj.SetTangentNum(TangentDistance);
		obj.SetChordNum(ChordDistance);		
		double	CentralRadian = fabs(obj.Chord_Tangent_course(2, 0.000001, 100));//��ֵ�����ȣ���������		
		if(CentralRadian == 0)	return;		
		radius = (TYPE)(ChordDistance/(2*sin(CentralRadian/2)));
		double	CentralAngle = RADIAN_TO_ANGLE(CentralRadian);		
		ConstructTangentRadiusAngle(Segment, bAtStart, bCCW, radius, CentralAngle/*, pDC*/);
	}
	//Բ�ĵ㡢ʼ�㡢Բ�������Ƿ���ʱ�롢���߾���
	template<class TYPE1,class TYPE2> void ConstructTangentDistance(SPo_TplPoint2D<TYPE1> C_pt, SPo_TplPoint2D<TYPE2> S_pt, bool bCCW, double TangentDistance)
	{
		bccw		= bCCW;		
		center		= SPo_TplPoint2D<TYPE>((TYPE)(C_pt.x),(TYPE)(C_pt.y));
		radius		= (TYPE)(sqrt(pow(C_pt.x - S_pt.x, 2) + pow(C_pt.y - S_pt.y, 2)));
		beginAngle	= GetAngleAngMt(C_pt, S_pt);		
		double CentralRadian	= fabs(2*atan(TangentDistance/radius));		
		if(bCCW)endAngle	= Angle - CentralAngle;//ע�⣺
		else	endAngle	= Angle + CentralAngle;//��ֱ������ϵ����������Ҫ����
	}
	//���ߡ�����Բ�������Ƿ���ʱ�롢�뾶��Բ�Ľ�
	template<class TYPE1> void ConstructTangentRadiusAngle(LOG_LINE<TYPE1> Segment, bool bAtStart, bool bCCW, double Radius, double CentralAngle)
	{
		//����Ҫ��֤SegmentΪֱ��,��Segment.start != Segment.end
		if(Segment.end==Segment.start)	return ;
		bccw = bCCW;		
		radius = (TYPE)Radius;		
		SPo_TplPoint2D<TYPE1> S_pt;//Բ���˵�
		SPo_TplPoint2D<TYPE1> O_pt;//ֱ����һ��		
		double CentralRadian = ANGLE_TO_RADIAN(CentralAngle);		
		if(bAtStart)	{S_pt = Segment.start;O_pt = Segment.end;}
		else			{S_pt = Segment.end;O_pt = Segment.start;}		
		//Segment���ȵ�ƽ��
		double	SegmentLong	= pow(Segment.start.x - Segment.end.x, 2) + pow(Segment.start.y - Segment.end.y, 2);		
		if(S_pt.x == O_pt.x)//��SegmentΪƽ����Y���ֱ��ʱ
		{
			double y = (SegmentLong + S_pt.y*S_pt.y - O_pt.y*O_pt.y)/(2*(S_pt.y - O_pt.y));
			
			double a = fabs(Radius*Radius - (y - S_pt.y)*(y - S_pt.y));
			
			//===================��һ�ֽ�==================
			center.y = (TYPE)y;
			center.x = (TYPE)(S_pt.x + sqrt(a));
			
			beginAngle	= GetAngleAngMt(center, S_pt);
			
			if(bCCW)endAngle	= beginAngle - CentralAngle;//ע�⣺
			else	endAngle	= beginAngle + CentralAngle;//��ֱ������ϵ����������Ҫ����
			
			//DrawArc(pDC);
			//=============================================
			
			//====================�ڶ��ֽ�=================
			center.y = (TYPE)y;
			center.x = (TYPE)(S_pt.x - sqrt(a));
			
			beginAngle	= GetAngleAngMt(center, S_pt);
			
			if(bCCW)endAngle	= beginAngle - CentralAngle;//ע�⣺
			else	endAngle	= beginAngle + CentralAngle;//��ֱ������ϵ����������Ҫ����			
			//DrawArc(pDC);
			//=============================================
		}
		else//�������
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
				//==================��һ�ֽ�=================
				double y = (-f + sqrt(h))/(2*e);
				
				center.y = (TYPE)y;
				center.x = (TYPE)(a + b*y);
				
				beginAngle	= GetAngleAngMt(center, S_pt);
				
				if(bCCW)endAngle	= beginAngle - CentralAngle;//ע�⣺
				else	endAngle	= beginAngle + CentralAngle;//��ֱ������ϵ����������Ҫ����				
				//DrawArc(pDC);
				//============================================
				if(h == 0)	return;
				//==================�ڶ��ֽ�=================//���������
				double y1 = (-f - sqrt(h))/(2*e);
				
				center.y = (TYPE)y1;
				center.x = (TYPE)(a + b*y1);
				
				beginAngle	= GetAngleAngMt(center, S_pt);//���������?
				
				if(bCCW)endAngle	= beginAngle - CentralAngle;//ע�⣺
				else	endAngle	= beginAngle + CentralAngle;//��ֱ������ϵ����������Ҫ����				
				//DrawArc(pDC);//���������?
				//===========================================
			}
			else	return;
		}
	}
	//���ߡ�����Բ�������Ƿ���ʱ�롢�뾶������
	template<class TYPE1> void ConstructTangentRadiusArc(LOG_LINE<TYPE1> Segment, bool bAtStart, bool bCCW, double Radius, double ArcDistance)
	{
		//����Ҫ��֤SegmentΪֱ��,��Segment.start != Segment.end
		if(Segment.start==Segment.end)	return ;
		double CentralAngle = RADIAN_TO_ANGLE(ArcDistance/Radiu);		
		ConstructTangentRadiusAngle(Segment, bAtStart, bCCW, Radius, CentralAngle/*, pDC*/);
	}
	//���ߡ�����Բ�������Ƿ���ʱ�롢�뾶���ҳ�
	template<class TYPE1> void ConstructTangentRadiusChord(LOG_LINE<TYPE1> Segment, bool bAtStart, bool bCCW, double Radius, double ChordDistance)
	{
		//����Ҫ��֤SegmentΪֱ��,��Segment.start != Segment.end
		if(Segment.start==Segment.end)	return ;		
		double CentralRadian = 2*asin(ChordDistance/(2*Radius));		
		double CentralAngle = RADIAN_TO_ANGLE(CentralRadian);		
		ConstructTangentRadiusAngle(Segment, bAtStart, bCCW, Radius, CentralAngle/*, pDC*/);//
	}
	//���ߡ�����Բ�������Ƿ���ʱ�롢�뾶�����߾���
	template<class TYPE1> void ConstructTangentRadiusTangent(LOG_LINE<TYPE1> Segment, bool bAtStart, bool bCCW, double Radius, double TangentDistance)
	{
		//����Ҫ��֤SegmentΪֱ��,��Segment.start != Segment.end
		if(Segment.start==Segment.end)	return ;		
		double CentralRadian = 2*fabs(atan(TangentDistance/Radius));		
		double CentralAngle = RADIAN_TO_ANGLE(CentralRadian);		
		ConstructTangentRadiusAngle(Segment, bAtStart, bCCW, Radius, CentralAngle/*, pDC*/);//
	}
	//ʼ�㡢Բ���м���һ�㡢�յ㡢�Ƿ�ʹ�ô��ڵ�Բ�ģ����������һ��ֱ���ϣ�Բ������Զ���Ҳ���Բ�ĵ㣩
	template<class TYPE1,class TYPE2,class TYPE3> bool ConstructThreePoint(SPo_TplPoint2D<TYPE1> S_pt, SPo_TplPoint2D<TYPE2> M_pt, SPo_TplPoint2D<TYPE3> E_pt, bool bUseExistingCenter)
	{
		if(M_pt.x - S_pt.x==0||E_pt.x - M_pt.x==0)	return false;
		SPo_TplPoint2D<double>	C_pt;		
		double K1 = (M_pt.y - S_pt.y)/(M_pt.x - S_pt.x);//ʼ�㵽�е��б��
		double K2 = (E_pt.y - M_pt.y)/(E_pt.x - M_pt.x);//�е㵽ĩ���б��		
		if(K1 == K2)	return false;//������һ��ֱ����,�Ҳ���Բ�ĵ�		
		SPo_TplPoint2D<double> SM_pt;//Բ����ʼ�㵽�е���м��
		SPo_TplPoint2D<double> ME_pt;//Բ�����е㵽ĩ����м��		
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
	//������������ȷ��������Բ----------------�¼�-----������
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
//     Բ���߶���ӿ�
//     ����Բ���ߵ�һ���֣�������ʼ�㡢Բ����ɡ�
// Բ�����ɷ�ʽ��������ȷ������һ��Բ����㣬�ڶ���Բ���յ㣬Բ�������Ǵ���㵽�յ��˳ʱ�뷽�򻡶Σ���������Բ�ġ�
//##ModelId=4B2B8A720251
class IGeo_CircularArc : public IGeo_Curve
{
  public:
	//##ModelId=4B2B8A720262
	virtual LOG_CIRCULARARC<double> GetLogCircleArc() = 0;

	//##ModelId=4B2B8A720264
	virtual void SetLogCircleArc(LOG_CIRCULARARC<double> log) = 0;
    //brief
    //     ����Բ��Բ�ĵ����ꡣ
    //     ���ݸ����Ŀռ�ο�ϵ����Բ�ĵ����ꡣ
    // 
    //return
    //     ���óɹ����򷵻�true�����򷵻�false��
    // 
    //param
    //     sPoint: Բ�����ꡣ
    //     pSpatialReference: �����õ�Բ�������Ӧ�Ŀռ�ο�ϵ��ȱʡΪNULL����ʾʹ��Բ������Ŀռ�ο�ϵ��
    //##ModelId=4B2B8A720267
    virtual bool SetCenterPoint(SPo_DPoint sPoint, IPo_SpatialReference* pSpatialReference = NULL) = 0;

    //brief
    //     ��ȡԲ��Բ�ĵ����ꡣ
    //     ���ݸ����Ŀռ�ο�ϵ��ȡԲ�ĵ����ꡣ
    // 
    //return
    //     ����Բ�ĵ����꣬���ռ�����ת��ʧ���򷵻�    SPo_Point(0,0)��
    // 
    //param
    //     pSpatialReference: ��Ҫ���ص�Բ�������Ӧ�Ŀռ�ο�ϵ��ȱʡΪNULL����ʾʹ��Բ������Ŀռ�ο�ϵ��
    //##ModelId=4B2B8A72026B
    virtual SPo_DPoint GetCenterPoint(IPo_SpatialReference* pSpatialReference = NULL) = 0;

    //brief
    //     ����Բ��������ꡣ
    //     ���ݸ����Ŀռ�ο�ϵ����Բ��������ꡣ
    // 
    //return
    //     ���óɹ����򷵻�true�����򷵻�false��
    // 
    //param
    //     sPoint: Բ��������ꡣ
    //     pSpatialReference: �����õ�Բ����������Ӧ�Ŀռ�ο�ϵ��ȱʡΪNULL����ʾʹ��Բ������Ŀռ�ο�ϵ��
    //##ModelId=4B2B8A72026E
    virtual bool SetStartPoint(SPo_DPoint sPoint, IPo_SpatialReference* pSpatialReference = NULL) = 0;

    //brief
    //     ��ȡԲ��������ꡣ
    //     ���ݸ����Ŀռ�ο�ϵ��ȡԲ��������ꡣ
    // 
    //return
    //     ����Բ��������꣬���ռ�����ת��ʧ���򷵻�SPo_Point(0,0)��
    // 
    //param
    //     pSpatialReference: ��Ҫ���ص�Բ����������Ӧ�Ŀռ�ο�ϵ��ȱʡΪNULL����ʾʹ��Բ������Ŀռ�ο�ϵ��
    //##ModelId=4B2B8A720272
    virtual SPo_DPoint GetStartPoint(IPo_SpatialReference* pSpatialReference = NULL) = 0;

    //brief
    //     ����Բ���յ����ꡣ
    //     ���ݸ����Ŀռ�ο�ϵ����Բ���յ����ꡣ
    // 
    //return
    //     ���óɹ����򷵻�true�����򷵻�false��
    // 
    //param
    //     sPoint: Բ���յ����ꡣ
    //     pSpatialReference: �����õ�Բ���յ������Ӧ�Ŀռ�ο�ϵ��ȱʡΪNULL����ʾʹ��Բ������Ŀռ�ο�ϵ��
    //##ModelId=4B2B8A720275
    virtual bool SetEndPoint(SPo_DPoint sPoint, IPo_SpatialReference* pSpatialReference = NULL) = 0;

    //brief
    //     ��ȡԲ���յ����ꡣ
    //     ���ݸ����Ŀռ�ο�ϵ��ȡԲ���յ����ꡣ
    // 
    //return
    //     ����Բ��������꣬���ռ�����ת��ʧ���򷵻�SPo_Point(0,0)��
    // 
    //param
    //     pSpatialReference: ��Ҫ���ص�Բ���յ������Ӧ�Ŀռ�ο�ϵ��ȱʡΪNULL����ʾʹ��Բ������Ŀռ�ο�ϵ��
    //##ModelId=4B2B8A720279
    virtual SPo_DPoint GetEndPoint(IPo_SpatialReference* pSpatialReference = NULL) = 0;

    //brief
    //     ����Բ���뾶
    // 
    //param
    //     dRadius Բ���뾶
    //##ModelId=4B2B8A72027C
    virtual void SetRadius(double dRadius) = 0;

    //brief
    //     ��ȡԲ���뾶
    // 
    //return
    //     ����Բ���뾶
    //##ModelId=4B2B8A72027F
    virtual double GetRadius() = 0;

    //brief
    //     ����Բ����ʼ�Ƕ�
    // 
    //param
    //     dAng Բ����ʼ�Ƕ�
    //##ModelId=4B2B8A720281
    virtual void SetFromAngle(double dAng) = 0;

    //brief
    //     ��ȡԲ����ʼ�Ƕ�
    // 
    //return
    //     ����Բ����ʼ�Ƕ�
    //##ModelId=4B2B8A720284
    virtual double GetFromAngle() = 0;

    //brief
    //     ����Բ����ֹ�Ƕ�
    // 
    //param
    //     dAng Բ����ֹ�Ƕ�
    //##ModelId=4B2B8A720286
    virtual void SetToAngle(double dAng) = 0;

    //brief
    //     ��ȡԲ����ֹ�Ƕ�
    // 
    //return
    //     ����Բ����ֹ�Ƕ�
    //##ModelId=4B2B8A720289
    virtual double GetToAngle() = 0;

    //brief
    //     ����Բ���ҳ�
    // 
    //param
    //     dLength Բ���ҳ�
    //##ModelId=4B2B8A72028B
    virtual void SetChordLength(double dLength) = 0;

    //brief
    //     ��ȡԲ���ҳ�
    // 
    //return
    //     ����Բ���ҳ�
    //##ModelId=4B2B8A72028E
    virtual double GetChordLength() = 0;

    //brief
    //     ����Բ���Ҹ�
    // 
    //param
    //     dHeight Բ���Ҹ�
    //     ��ע : �Ҹ�Ϊ�����е���Բ���Ĵ�ֱ���룬Ϊ��ֵ
    //##ModelId=4B2B8A720290
    virtual void SetChordHeight(double dLength) = 0;

    //brief
    //     ��ȡԲ���Ҹ�
    // 
    //return
    //     ����Բ���Ҹ�
    //     ��ע : �Ҹ�Ϊ�����е���Բ���Ĵ�ֱ���룬Ϊ��ֵ
    //##ModelId=4B2B8A720293
    virtual double GetChordHeight() = 0;

    //brief
    //     ����Բ�����ĽǶ�
    // 
    //param
    //     dAng Բ�����ĽǶ�
    //##ModelId=4B2B8A720295
    virtual void SetCentralAngle(double dAng) = 0;

    //brief
    //     ��ȡԲ�����ĽǶ�
    // 
    //return
    //     ����Բ�����ĽǶ�
    //##ModelId=4B2B8A720298
    virtual double GetCentralAngle() = 0;

    //brief
    //     ����Բ���Ĳ��㲿��
    //     �½�Բ������ֹ����ԭ��Բ���෴��
    // 
    //     ��ע : �´�����Բ��������Ҫ�����ͷ�
    //##ModelId=4B2B8A72029A
    virtual IGeo_Geometry* CreateComplement() = 0;

    //brief
    //     ȡԲ���Ĳ��㲿��
    //     ��Բ������ֹ����л�����
    // 
    //return
    //     �ɹ�����true��
    //##ModelId=4B2B8A72029C
    virtual bool Complement() = 0;

    //brief
    //     �жϸ����ĵ��Ƿ���Բ����
    //     ���ݸ����ĵ㼰�ռ�ο�ϵ�ж����Ƿ����߶��ϡ�
    // 
    //return
    //     λ���߶��ϣ��򷵻�true�����򷵻�false��
    // 
    //param
    //     sPoint: ��Ҫ�жϵĵ����ꡣ
    //     dTolerance �ж���ֵ��
    //     pSpatialReference: �������Ӧ�Ŀռ�ο�ϵ��ȱʡΪNULL����ʾʹ���߶α���Ŀռ�ο�ϵ��
    //##ModelId=4B2B8A72029E
    virtual bool IsPointOnArc(SPo_DPoint sPoint, double dTolerance = 0.0, IPo_SpatialReference* pSpatialReference = NULL) = 0;

    //brief
    //     �жϸ����ĵ�����Ƿ���Բ����
    // 
    //return
    //     λ���߶��ϣ��򷵻�true�����򷵻�false��
    // 
    //param
    //     pPoint: ��Ҫ�жϵĵ����
    //     dTolerance �ж���ֵ��
    //##ModelId=4B2B8A7202A3
    virtual bool IsPointOnArc(const IGeo_Geometry* pPoint, double dTolerance = 0.0) = 0;

};
extern "C" __declspec(dllexport) IGeo_CircularArc *CreateGeoCirArc(LOGD_CIRCULARARC lg);

#endif /* IGEO_CIRCULARARC_H_HEADER_INCLUDED_B9D3382A */
