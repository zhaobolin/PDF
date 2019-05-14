#ifndef SPO_ANGLE_H_HEADER_INCLUDED_B612B892
#define SPO_ANGLE_H_HEADER_INCLUDED_B612B892

#define DDVAL_CVT_TEMP 0.000000001
////////////比较值与原始值无限接近
#define IsValueNearUnlimited(vCmp,vOrg) fabs(vCmp-vOrg)<DDVAL_CVT_TEMP?true:false

double inline TvalToNearestInt(double dval)
{
	if(fabs(dval-ceil(dval))<DDVAL_CVT_TEMP)return ceil(dval);
	else if(fabs(dval-floor(dval))<DDVAL_CVT_TEMP)return floor(dval);
	else return dval;
}

//##ModelId=49ED3A870222
struct SPo_Angle
{
public:
	SPo_Angle(double dArcAngle = 0)
	{
		m_bPositive=(dArcAngle<0?false:true);
		dArcAngle=fabs(dArcAngle);
		
		double fbm = dArcAngle*180*3600/PO_PI;
		
		double miaozheng = floor(fbm);
		if(fbm-miaozheng>1.0-DDVAL_CBT_MIAOACURATE)
		{
			fbm = miaozheng+1;miaozheng=fbm;//顶端
		}
		else if(fbm-miaozheng<DDVAL_CBT_MIAOACURATE)
		{
			fbm = miaozheng;//底端
		}
		__int64 miaoi64 = (__int64)miaozheng;
		
		m_uDu = miaoi64/3600;
		m_uFen = ((miaoi64%3600))/60;
		m_uMiao = (((miaoi64%3600))%60);
		m_fMiaoRest = fbm-3600.0*m_uDu-60.0*m_uFen-m_uMiao;
	}
	SPo_Angle(int iDu,int iFen,int iMiao)
	{
		m_bPositive=(iDu<0?false:true);
		iDu = abs(iDu);
		while (iDu>359)		iDu -= 360;
		iFen=abs(iFen);		
		while (iFen>59)	iFen -= 60;
		iMiao=abs(iMiao);
		while (iMiao>59) iMiao -= 60;
		
		m_uDu = (unsigned __int16)iDu;
		m_uFen = (unsigned __int8)iFen;
		m_uMiao = (unsigned __int8)iMiao;
		m_fMiaoRest =0;
	}
	int GetDu(bool bAbs=false)
	{
		return bAbs?m_uDu:(m_bPositive?m_uDu:-m_uDu);
	}
	int GetFen()
	{
		return m_uFen;
	}
	int GetMiao()
	{
		return m_uMiao;
	}
	double GetAllSecs()
	{
		return m_bPositive?(m_uDu*3600+m_uFen*60+m_uMiao+m_fMiaoRest):-(m_uDu*3600+m_uFen*60+m_uMiao+m_fMiaoRest);
	}
	double GetAllDus()
	{
		return GetAllSecs()/3600;
	}
	double GetAllArcs()
	{
		return GetAllDus()*PO_PI/180;
	}
	CString ToString()
	{
		if(GetDu()==0&&GetFen()==0&&GetMiao()==0)
			return "0°";
		else
		{
			int Du = GetDu(true);int Fen = GetFen();int Miao = GetMiao();
			CString strR;
			if(Miao==0)
			{
				if(m_bPositive)
					strR.Format("%d°%d′",Du,Fen);
				else
					strR.Format("-%d°%d′",Du,Fen);
			}
			else
			{
				if(m_bPositive)
					strR.Format("%d°%d′%d″",Du,Fen,Miao);
				else
					strR.Format("-%d°%d′%d″",Du,Fen,Miao);
			}
			return strR;
		}
	};
	//转成字符串的第二种方式
	CString ToString(unsigned int label/*0只精确到度；1精确到分；2精确到秒*/)
	{
		double Sec = ToAngleDoubleMiao();
		CString strrval;
		if(label==0)
		{
			if(Sec==0)
				strrval = "0°";
			else
			{						
				if(m_bPositive)	strrval.Format("%d°",GetDu(true));//return(String.Format("{0}°", du));
				else		strrval.Format("-%d°",GetDu(true));//return(String.Format("-{0}°", du));
			}
		}
		else if(label==1||label==2)
		{
			if(Sec==0)
			{
				if(label==1)	strrval = "0°0′";//		return(String.Format("{0}°{1}′", 0,0));
				else			strrval = "0°00′";//  	    return(String.Format("{0}°{1}{2}′", 0,0,));
			}
			else
			{
				if(m_bPositive)		
				{
					/*if(label==1) */strrval.Format("%d°%d′",GetDu(true),GetFen());//return(String.Format("{0}°{1}′", du,fen));
					//else		 strrval.Format("%d°%d′",GetDu(),GetFen());//return(String.Format("{0}°{1}′", du,fen));
				}
				else				
				{
					/*if(label==1)*/strrval.Format("-%d°%d′",GetDu(true),GetFen());//		return(String.Format("-{0}°{1}′", du,fen));
					//else		   	    return(String.Format("-{0}°{1}′", du,fen));
				}
			}
		}
		else//>=4
		{
			if(Sec==0)
				strrval = "0°00′00″";//				return(String.Format("{0}°{1}{2}′{3}{4}″", 0,0,0,0,0));
			else
			{						
				if(m_bPositive)	strrval.Format("%d°%d′%d″",GetDu(true),GetFen(),GetMiao());//				return(String.Format("{0}°{1}′{2}″", du,fen,miao));
				else		strrval.Format("-%d°%d′%d″",GetDu(true),GetFen(),GetMiao());//					return(String.Format("-{0}°{1}′{2}″", du,fen,miao));
			}
		}
		return strrval;
	};
	
	double ToAngleDoubleMiao(bool bAbs=false)//获取全部的秒
	{
		double dval = ((double)m_fMiaoRest+m_uMiao+60.0*m_uFen+3600.0*m_uDu);
		return bAbs?dval:(m_bPositive?dval:-dval);
	}
	double ToAngleDoubleDu(bool bAbs=false)
	{
		return ToAngleDoubleMiao(bAbs)/3600.0;
	}
	double ToAngleDoubleHudu(bool bAbs=false)
	{
		return ToAngleDoubleDu(bAbs)*PO_PI/180.0;
	}
	void FromAngleDoubleDu(double dDoubleDu)
	{
		double dArcAngle = dDoubleDu*PO_PI/180;
		
		*this = SPo_Angle(dArcAngle);
	}
	void FromLongSeconds(double dLongSeconds)
	{
		double dDu = dLongSeconds/3600.0;
		
		FromAngleDoubleDu(dDu);
	}
	void FromAngleArcs(double dArc)
	{
		FromAngleDoubleDu(dArc*180/PO_PI);
	}
	
	void MakeAcurate()//在精度范围内将角度计算准确,从邻近整度数来推算
	{
		if(m_fMiaoRest-floor(m_fMiaoRest)>1.0-DDVAL_CBT_MIAOACURATE)
		{
			m_fMiaoRest = 0;
			if(m_uMiao==59)
			{
				m_uMiao=0;
				if(m_uFen==59)
				{
					m_uFen=0;
					if(m_uDu==359)
					{
						m_uDu=0;
					}
					else
						m_uDu ++;
				}
				else
					m_uFen ++;
			}
			else
				m_uMiao++;
		}
		else if(m_fMiaoRest-floor(m_fMiaoRest)<DDVAL_CBT_MIAOACURATE)
		{
			m_fMiaoRest = 0;//底端
		}
	};
	bool operator==(const SPo_Angle &right)
	{
		return (m_uDu==right.m_uDu)&&
				(m_uFen==right.m_uFen)&&
				(m_uMiao==right.m_uMiao)&&
				(m_fMiaoRest==right.m_fMiaoRest)&&
				(m_bPositive==right.m_bPositive);
	};
	//角度 度位上的绝对值
	unsigned __int16 m_uDu;
	//角度分位上的绝对值
	unsigned __int8 m_uFen;
	//角度秒位上的绝对值
	unsigned __int8 m_uMiao;
	//除去以上剩余的浮点秒，<1.0
	float m_fMiaoRest;
	//是否是正值
	bool m_bPositive;
};


#define ANGLE_TO_RADIAN( angle )	angle * PO_PI / 180.
#define RADIAN_TO_ANGLE( riadin )	riadin * 180. / PO_PI 

//------返回笛卡尔坐标系pt1->pt2的角度\双精度型角度---[0,360)---
template<class TYPE1,class TYPE2> double inline GetAngleAngMt(TYPE1 x1,TYPE1 y1,TYPE2 x2,TYPE2 y2)
{
	double Ang=0;
	
	if(x2 - x1 == 0)
	{
		if(y2 - y1 < 0)	Ang = 270;//-90
		else	Ang = 90;//90;
	}
	else
	{
		Ang = RADIAN_TO_ANGLE(atan((y2 - y1)/(x2 - x1)));
		if((y2 - y1)*(x2 - x1)>0)////////13象限
		{
			if(y2>y1)//第一象限
				0;
			else//第3象限
				Ang += 180;
		}
		else///////////////24象限
		{
			if(y2>y1)//第2象限
				Ang += 180;
			else//4象限
				Ang += 360;
		}
	}
	return Ang;
};
//------返回笛卡尔坐标系pt1->pt2的角度\双精度型角度--[0,360)----
template<class TYPE1,class TYPE2> double inline GetAngleAngMt(SPo_TplPoint2D<TYPE1> pt1,SPo_TplPoint2D<TYPE2> pt2)
{
	return GetAngleAngMt(pt1.x,pt1.y,pt2.x,pt2.y);
};
//------返回笛卡尔坐标系pt1->pt2的角度\双精度型弧度---[0，2PI)---
template<class TYPE1,class TYPE2> double inline GetAngleRadMt(TYPE1 x1,TYPE1 y1,TYPE2 x2,TYPE2 y2)
{
	double Rad=0;
	
	if(x2 - x1 == 0)
	{
		if(y2 - y1 < 0)	Rad = PO_PIHALF*3;
		else	Rad = PO_PIHALF;
	}
	else
	{
		Rad = atan((y2 - y1)/(x2 - x1));
		if((y2 - y1)*(x2 - x1)>0)////////13象限
		{
			if(y2>y1)//第一象限
				0;
			else//第3象限
				Rad += PO_PI;
		}
		else///////////////24象限
		{
			if(y2>y1)//第2象限
				Rad += PO_PI;
			else//4象限
				Rad += PO_2PI;
		}
	}
	return Rad;
}
//------返回笛卡尔坐标系pt1->pt2的角度\双精度型弧度---[0，2PI)---
template<class TYPE1,class TYPE2> double inline GetAngleRadMt(SPo_TplPoint2D<TYPE1> pt1,SPo_TplPoint2D<TYPE2> pt2)
{
	return GetAngleRadMt(pt1.x,pt1.y,pt2.x,pt2.y);
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//------返回上小右大屏幕坐标系pt1->pt2的角度\双精度型角度---[0,360)---
template<class TYPE1,class TYPE2> double inline GetAngleAngSc(TYPE1 x1,TYPE1 y1,TYPE2 x2,TYPE2 y2)
{
	double Ang=0;
	
	if(x2 - x1 == 0)
	{
		if(y2 - y1 < 0)	Ang = 90;
		else	Ang = 270;
	}
	else
	{
		Ang = RADIAN_TO_ANGLE(atan((y2 - y1)/(x2 - x1)));
		if((y2 - y1)*(x2 - x1)>0)////////13象限
		{
			if(y2>y1)//第一象限
				Ang = 360-Ang;
			else//第3象限
				Ang = 180-Ang;
		}
		else///////////////24象限
		{
			if(y2>y1)//第2象限
				Ang = 180-Ang;
			else//4象限
				Ang = -Ang;
		}
	}
	return Ang;
};
//------返回上小右大屏幕坐标系pt1->pt2的角度\双精度型角度--[0,360)----
template<class TYPE1,class TYPE2> double inline GetAngleAngSc(SPo_TplPoint2D<TYPE1> pt1,SPo_TplPoint2D<TYPE2> pt2)
{
	return GetAngleAngSc(pt1.x,pt1.y,pt2.x,pt2.y);
};
//------返回上小右大屏幕坐标系pt1->pt2的角度\双精度型弧度---[0，2PI)---
template<class TYPE1,class TYPE2> double inline GetAngleRadSc(TYPE1 x1,TYPE1 y1,TYPE2 x2,TYPE2 y2)
{
	double Rad=0;
	
	if(x2 - x1 == 0)
	{
		if(y2 - y1 < 0)	Rad = 3*PO_PIHALF;
		else	Rad = PO_PIHALF;
	}
	else
	{
		Rad = atan((y2 - y1)/(x2 - x1));
		if((y2 - y1)*(x2 - x1)>0)////////13象限
		{
			if(y2>y1)//第一象限
				Rad = PO_2PI-Rad;
			else//第3象限
				Rad = PO_PI-Rad;
		}
		else///////////////24象限
		{
			if(y2>y1)//第2象限
				Rad = PO_PI-Rad;
			else//4象限
				Rad = -Rad;
		}
	}
	return Rad;
}
//------返回上小右大屏幕坐标系pt1->pt2的角度\双精度型弧度---[0，2PI)---
template<class TYPE1,class TYPE2> double inline GetAngleRadSc(SPo_TplPoint2D<TYPE1> pt1,SPo_TplPoint2D<TYPE2> pt2)
{
	return GetAngleRadSc(pt1.x,pt1.y,pt2.x,pt2.y);
}


#endif /* SPO_ANGLE_H_HEADER_INCLUDED_B612B892 */
