#ifndef GEOMETRYCALCULATOR_H_HEADER_INCLUDED_B0F93B24
#define GEOMETRYCALCULATOR_H_HEADER_INCLUDED_B0F93B24


//##ModelId=4F06FC6C01D4
void inline TcCoordConverseFst(VISZ_DRAWPARMS *pParm,vector<SPo_DPoint2D> *pOrdinates,PointF *ptOut)//快速批量算法，执行较快
{
	int i=0;
	for(vector<SPo_DPoint2D>::iterator itr=pOrdinates->begin();itr!=pOrdinates->end();itr++,i++)
		pParm->TcCoordConverse(itr->x,itr->y,&(ptOut[i].X),&(ptOut[i].Y));
};
///////关于点的依次缩放旋转后平移的转换
template<class TYPE1> void inline SPoPntsConvRotateAndMove(SPo_TplPoint<TYPE1> *pts/*in and out*/,int nCount,float fRate/*缩放比例系数!=0*/,double dAngle/*旋转的弧度*/,double dOffsetX,double dOffsetY)
{
	for(int i = 0;i<nCount;i++)
	{
		double dox = pts[i].x*fRate;
		double doy = pts[i].y*fRate;//缩放
		double tdox = dox*cos(dAngle)-doy*sin(dAngle);
		double tdoy = dox*sin(dAngle)+doy*cos(dAngle);//旋转
		pts[i].x = (TYPE1)(tdox+dOffsetX);
		pts[i].y = (TYPE1)(tdoy+dOffsetY);//平移
	}
};

///////关于点的依次缩放旋转后平移的转换
void inline SPoPntsConvRotateAndMove(POINT *pts/*in and out*/,int nCount,float fRate/*缩放比例系数!=0*/,double dAngle/*旋转的弧度*/,double dOffsetX,double dOffsetY)
{
	for(int i = 0;i<nCount;i++)
	{
		double dox = pts[i].x*fRate;
		double doy = pts[i].y*fRate;//缩放
		double tdox = dox*cos(dAngle)-doy*sin(dAngle);
		double tdoy = dox*sin(dAngle)+doy*cos(dAngle);//旋转
		pts[i].x = (LONG)(tdox+dOffsetX);
		pts[i].y = (LONG)(tdoy+dOffsetY);//平移
	}
};

///////关于点的依次缩放旋转后平移的转换
void inline SPoPntsConvRotateAndMove(PointF *pts/*in and out*/,int nCount,float fRate/*缩放比例系数!=0*/,double dAngle/*旋转的弧度*/,double dOffsetX,double dOffsetY)
{
	for(int i = 0;i<nCount;i++)
	{
		double dox = pts[i].X*fRate;
		double doy = pts[i].Y*fRate;//缩放
		double tdox = dox*cos(dAngle)-doy*sin(dAngle);
		double tdoy = dox*sin(dAngle)+doy*cos(dAngle);//旋转
		pts[i].X = (float)(tdox+dOffsetX);
		pts[i].Y = (float)(tdoy+dOffsetY);//平移
	}
};

///////关于点的依次缩放旋转后平移的转换
void inline SPoPntsConvRotateAndMove(Point *pts/*in and out*/,int nCount,float fRate/*缩放比例系数!=0*/,double dAngle/*旋转的弧度*/,double dOffsetX,double dOffsetY)
{
	for(int i = 0;i<nCount;i++)
	{
		double dox = pts[i].X*fRate;
		double doy = pts[i].Y*fRate;//缩放
		double tdox = dox*cos(dAngle)-doy*sin(dAngle);
		double tdoy = dox*sin(dAngle)+doy*cos(dAngle);//旋转
		pts[i].X = (INT)(tdox+dOffsetX);
		pts[i].Y = (INT)(tdoy+dOffsetY);//平移
	}
};

///////关于点的依次缩放旋转后平移的转换
template<class TYPE1> void inline SPoPntsConvRotateAndMove(SPo_TplPoint2D<TYPE1> *pts/*in and out*/,int nCount,float fRate/*缩放比例系数!=0*/,double dAngle/*旋转的弧度*/,double dOffsetX,double dOffsetY)
{
	for(int i = 0;i<nCount;i++)
	{
		double dox = pts[i].x*fRate;
		double doy = pts[i].y*fRate;//缩放
		double tdox = dox*cos(dAngle)-doy*sin(dAngle);
		double tdoy = dox*sin(dAngle)+doy*cos(dAngle);//旋转
		pts[i].x = (TYPE1)(tdox+dOffsetX);
		pts[i].y = (TYPE1)(tdoy+dOffsetY);//平移
	}
};
//计算两点间的距离
template <class TYPE1,class TYPE2> double inline CalDistance(TYPE1 x1,TYPE1 y1,TYPE2 x2,TYPE2 y2)
{
	return sqrt((double)(x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
};

template <class PNTTYPE1,class PNTTYPE2> double inline CalDistance(PNTTYPE1 &p1,PNTTYPE2 &p2)
{
	double dpx1=0;double dpy1=0;double dpx2=0;double dpy2=0;
	TplGetXYCoordPoint(p1,dpx1,dpy1);TplGetXYCoordPoint(p2,dpx2,dpy2);
	return CalDistance(dpx1,dpy1,dpx2,dpy2);
};

template <class PNTSLSTPTR> SPo_DRect GetBoundD(PNTSLSTPTR pPntLst,int nPtsCnt)
{
	double fleft=0;double fright = 0;double ftop = 0;double fbottom = 0;
	TplGetXYCoordPointsList(pPntLst,0,fleft,ftop);
	fright = fleft; fbottom = ftop;
	double dvx=0;double dvy=0;
	for(int i = 1;i<nPtsCnt;i++)
	{
		TplGetXYCoordPointsList(pPntLst,i,dvx,dvy);

		fleft = min(fleft,dvx);
		fright = max(fright,dvx);
		ftop = min(ftop,dvy);
		fbottom = max(fbottom,dvy);
	}
	return SPo_DRect(fleft,ftop,fright,fbottom);
};

///////////////////////////此处约定角度的方向，在笛卡尔坐标系中，直线p1p2方向与水平x轴正方向的夹角为角度方向，取值为[0,360),或者[0,PO_2PI)
///////////////////////////若是在默认屏幕的y轴向下的坐标系中，
//------返回pt1->pt2的角度(以度计量)//bYup表示是否Y轴向上
template <class TYPE1> double inline GetAngleAng(TYPE1 x1,TYPE1 y1,TYPE1 x2,TYPE1 y2)
{
	double AngAng=0;
	double ddx=x2-x1;double ddy=y2-y1;
	if(IsValueNearUnlimited(ddx,0))
	{
		if(y2>y1)AngAng= 90.0;
		else AngAng= 270.0;
	}
	else
	{
		AngAng = RADIAN_TO_ANGLE(atan(ddy/ddx));
		if(y2>y1)
		{
			if(AngAng<0)AngAng+=180;
			//else  AngAng;
		}
		else
		{
			if(AngAng==0)
			{
				if(ddx<0)
					AngAng = 180;
				else
					AngAng = 0;
			}
			else if(AngAng<0)AngAng+=360;
			else AngAng+=180;
		}
	}
	return AngAng;
};
/////////////////////任意类型的两个点求直线二维上的倾角,返回弧度//bYup表示是否Y轴向上
template <class TYPE1> double inline GetAngleRad(TYPE1 x1,TYPE1 y1,TYPE1 x2,TYPE1 y2)
{
	double AngRad=0;
	double ddx=x2-x1;double ddy=y2-y1;
	if(IsValueNearUnlimited(ddx,0))
	{
		if(y2>y1)AngRad=PO_PIHALF;
		else AngRad=PO_3P2PI;
	}
	else
	{
		AngRad=atan(ddy/ddx);
		if(y2>y1)
		{
			if(AngRad<0)AngRad+=PO_PI;
		}
		else
		{
			if(AngRad==0)
			{
				if(ddx<0)
					AngRad = PO_PI;
				else
					AngRad = 0;
			}
			else if(AngRad<0)AngRad+=PO_2PI;
			else AngRad+=PO_PI;
		}
	}
	return AngRad;
};

//以度计量的角度从笛卡尔坐标系到屏幕坐标系转换
double inline AngleAng_DCRTOSCR(double dAng)
{
	while(dAng>360){dAng-=360;}
	if(IsValueNearUnlimited(dAng,0))return 0;
	else return 360-dAng;
};
//以度计量的角度从屏幕坐标系到笛卡尔坐标系转换
double inline AngleAng_SCRTODCR(double dAng)
{
	return AngleAng_DCRTOSCR(dAng);
};

//以弧度计量的角度从笛卡尔坐标系到屏幕坐标系转换
double inline AngleRad_DCRTOSCR(double dRad)
{
	while(dRad>PO_2PI){dRad-=PO_2PI;}
	if(IsValueNearUnlimited(dRad,0))return 0;
	else return PO_2PI-dRad;
};
//以弧度计量的角度从屏幕坐标系到笛卡尔坐标系转换
double inline AngleRad_SCRTODCR(double dRad)
{
	return AngleRad_DCRTOSCR(dRad);
};

//点p到由p1p2组成的无限长直线的距离
template <class TYPE,class TYPE1> double inline CalDistancePointLineUnlimited(TYPE pX,TYPE pY,TYPE1 pX1,TYPE1 pY1,TYPE1 pX2,TYPE1 pY2)
{
	double c=CalDistance(pX1,pY1,pX2,pY2);		if(c<0.000001) return CalDistance(pX,pY,pX1,pY1);
	
	if(fabs(pX1-pX2)<0.000001/*<0.1*/)//垂线//d=;//点到直线段延长线的垂线距离
	{
		return fabs(pX-pX1);
	}
	else if(fabs(pY1-pY2)<0.000001/*<0.1*/)//水平线
	{
		return fabs(pY-pY1);
	}
	else
	{
		double k = (double)(pY2-pY1)/(pX2-pX1);//P1P2斜率,-1/k标识垂线的斜率;经过P1P2的直线：y = k*x+f;		
		double f = pY1-k*pX1;
		//过P1的垂线方程:y=(-1/k)*x+h1;	过P2的垂线方程:y=(-1/k)*x+h2;
		double h1 = pY1+pX1/k;double h2 = pY2+pX2/k;double h = pY+pX/k;
		
		double xPos = (h-f)/(k+1/k);
		double yPos = k*xPos+f;
		return CalDistance(pX,pY,xPos,yPos);
	}
};

//点p到线段p1p2的距离
template <class TYPE,class TYPE1> double inline CalDistancePointLine(TYPE pX,TYPE pY,TYPE1 pX1,TYPE1 pY1,TYPE1 pX2,TYPE1 pY2)
{
	double a=CalDistance(pX1,pY1,pX,pY);		if(a<0.000001) return 0.0;
	
	double b=CalDistance(pX,pY,pX2,pY2);		if(b<0.000001) return 0.0;
	
	double c=CalDistance(pX1,pY1,pX2,pY2);		if(c<0.000001) return a;
	
	if(fabs(pX1-pX2)<0.000001/*<0.1*/)//垂线//d=;//点到直线段延长线的垂线距离
	{
		if(pY<min(pY1,pY2)||pY>max(pY1,pY2))
			return min(a,b);
		else 
			return fabs(pX-pX1);
	}
	else if(fabs(pY1-pY2)<0.000001/*<0.1*/)//水平线
	{
		if(pX<min(pX1,pX2)||pX>max(pX1,pX2))
			return min(a,b);
		else
			return fabs(pY-pY1);
	}
	else
	{
		double k = (double)(pY2-pY1)/(pX2-pX1);//P1P2斜率,-1/k标识垂线的斜率;经过P1P2的直线：y = k*x+f;		
		double f = pY1-k*pX1;
		//过P1的垂线方程:y=(-1/k)*x+h1;	过P2的垂线方程:y=(-1/k)*x+h2;
		double h1 = pY1+pX1/k;double h2 = pY2+pX2/k;double h = pY+pX/k;
		
		if(h<min(h1,h2)||h>max(h1,h2))
		{
			return min(a,b);
		}
		else
		{///////////////经过P的垂线：y=(-1/k)*x+h;经过P1P2的直线：y = k*x+f;
			double xPos = (h-f)/(k+1/k);
			double yPos = k*xPos+f;
			return CalDistance(pX,pY,xPos,yPos);
		}
	}
};

//点p到线段p1p2的距离
template <class PNTTYPE,class TYPE1> double inline CalDistancePointLine(PNTTYPE &pCmpPt,TYPE1 pX1,TYPE1 pY1,TYPE1 pX2,TYPE1 pY2)
{
	double x=0;double y=0;
	TplGetXYCoordPoint(pCmpPt,x,y);
	return CalDistancePointLine(x,y,pX1,pY1,pX2,pY2);
};

//点p到线段p1p2的距离
template <class PNTTYPE1,class PNTTYPE2> double inline CalDistancePointLine(PNTTYPE1 &pCmpPt,PNTTYPE2 &pP1,PNTTYPE2 &pP2)
{
	double x=0;double y=0;double pX1=0;double pY1=0;double pX2=0;double pY2=0;
	TplGetXYCoordPoint(pCmpPt,x,y);TplGetXYCoordPoint(pP1,pX1,pY1);TplGetXYCoordPoint(pP2,pX2,pY2);
	return CalDistancePointLine(x,y,pX1,pY1,pX2,pY2);
};

//计算三点三角形面积
template <class TYPE,class TYPE1> double inline CalArea3pTrig(TYPE pX,TYPE pY,TYPE1 pX1,TYPE1 pY1,TYPE1 pX2,TYPE1 pY2)
{
	return 0.5*CalDistance(pX1,pY1,pX2,pY2)*CalDistancePointLine(pX,pY,pX1,pY1,pX2,pY2);
}
//计算三点三角形面积
template <class PNTTYPE1,class PNTTYPE2> double inline CalArea3pTrig(PNTTYPE1 &pCmpPt,PNTTYPE2 &pP1,PNTTYPE2 &pP2)
{
	return 0.5*CalDistance(pP1,pP2)*CalDistancePointLine(pCmpPt,pP1,pP2);
}
//计算线段p1p2上到p距离最近的点，而且z坐标还表明了在线段的前端(-1)，中间(0)，后端(1)
template <class TYPE,class TYPE1,class TYPE2> SPo_DPoint inline CalNearestPointOnLineFrom(TYPE pX,TYPE pY,TYPE1 pX1,TYPE1 pY1,TYPE2 pX2,TYPE2 pY2)
{
	double a=CalDistance(pX1,pY1,pX,pY);		if(a<0.000001) return SPo_DPoint(pX1,pY1,-1);
	
	double b=CalDistance(pX,pY,pX2,pY2);		if(b<0.000001) return SPo_DPoint(pX2,pY2,1);
	
	double c=CalDistance(pX1,pY1,pX2,pY2);		if(c<0.000001) return SPo_DPoint(pX2,pY2,0);
	
	if(fabs(pX1-pX2)<0.000001/*<0.1*/)//垂线//d=;//点到直线段延长线的垂线距离
	{
		if(pY<=min(pY1,pY2))
			return SPo_DPoint(pX1,min(pY1,pY2),pY1>pY2?1:-1);
		else if(pY>=max(pY1,pY2))
			return SPo_DPoint(pX1,max(pY1,pY2),pY1>pY2?-1:1);
		else
			return SPo_DPoint(pX1,pY,0);
	}
	else if(fabs(pY1-pY2)<0.000001/*<0.1*/)//水平线
	{
		if(pX<=min(pX1,pX2))
			return SPo_DPoint(min(pX1,pX2),pY1,pX1>pX2?1:-1);
		else if(pX>=max(pX1,pX2))
			return SPo_DPoint(max(pX1,pX2),pY1,pX1>pX2?-1:1);
		else
			return SPo_DPoint(pX,pY1,0);
	}
	else
	{
		double k = (double)(pY2-pY1)/(pX2-pX1);//P1P2斜率,-1/k标识垂线的斜率;经过P1P2的直线：y = k*x+f;		
		double f = pY1-k*pX1;
		//过P1的垂线方程:y=(-1/k)*x+h1;	过P2的垂线方程:y=(-1/k)*x+h2;
		double h1 = pY1+pX1/k;double h2 = pY2+pX2/k;double h = pY+pX/k;
		if(h<min(h1,h2)||h>max(h1,h2))
		{
			if(a<b)
				return SPo_DPoint(pX1,pY1,-1);
			else 
				return SPo_DPoint(pX2,pY2,1);
		}
		else
		{///////////////经过P的垂线：y=(-1/k)*x+h;经过P1P2的直线：y = k*x+f;
			double xPos = (h-f)/(k+1/k);
			double yPos = k*xPos+f;
			return SPo_DPoint(xPos,yPos,0);
		}
	}
};

double inline TextDirAngleFromPP(double dx1,double dy1,double dx2,double dy2,bool bVerti=false/*是否垂直*/)
{
	if((dx1==dx2)&&(dy1==dy2))	return 0;
	
	if(dx1==dx2)//垂直线
	{
		return bVerti?(dy1>dy2?0:PO_PI):(dy1>dy2?PO_PIHALF:PO_3P2PI);
	}
	else if(dy1==dy2)//水平线
	{
		return bVerti?(dx1<dx2?PO_3P2PI:PO_PIHALF):(dx1<dx2?0:PO_PI);
	}
	else//斜线
	{
		double k0 = (dy2-dy1)/(dx2-dx1);
		
		double ddangle = atan(k0);

		return bVerti?(dx1>dx2?PO_PI/2-ddangle:-PO_PI/2-ddangle):(dx1>dx2?PO_PI-ddangle:-ddangle);
	}
};

#pragma warning (disable:4786)//定义名称过长的警告
//计算折线pts上到p距离最近的点,其中返回值中的z坐标记录了该点沿折线前进方向的角度,返回弧度值//z角度坐标的取值为以下方式
//0在端点上，方向为首末线段的方向角
//1在某段上，为该段的方向角
//2在中间的某个节点上（非端点），为前段方向角减去后前两段夹角的一半
template <class TYPE,class PNTSLSTPTR/*点串列表地址类型*/> SPo_DPoint inline CalNearestPointOnStrockLineFrom(TYPE pX,TYPE pY,PNTSLSTPTR pPntsLst,int npcnt)
{
	SPo_DPoint dp;
	if(npcnt<2)return dp;
	
	map<double,SPo_DPoint> dispmap;
	double dismin;double px1=0;double py1=0;double px2=0;double py2=0;
	for(int i=0;i<npcnt-1;i++)
	{
		TplGetXYCoordPointsList(pPntsLst,i,px1,py1);TplGetXYCoordPointsList(pPntsLst,i+1,px2,py2);//获取点坐标

		double dDis=CalDistancePointLine(pX,pY,px1,py1,px2,py2);//计算距离
		SPo_DPoint pShort=CalNearestPointOnLineFrom(pX,pY,px1,py1,px2,py2);//计算线上点
		dismin=(i==0?dDis:min(dismin,dDis));int nLab = pShort.z;
		//计算角度///////////////////////////////////////////////////////////////
		double ang12=TextDirAngleFromPP(px1,py1,px2,py2);
		if(i==0)/////////////////第一次
		{
			if(nLab==1)//后端
			{
				if(npcnt==2)
					pShort.z=ang12;
				else//////////
				{
					double px3=0;double py3=0;TplGetXYCoordPointsList(pPntsLst,i+2,px3,py3);//获取点坐标
					double ang23=TextDirAngleFromPP(px2,py2,px3,py3);
					pShort.z=(ang12+ang23)/2;
				}
			}
			else
				pShort.z=ang12;
		}
		else if(i==(npcnt-2))//最末次
		{
			if(nLab==-1)//前端
			{
				double px0=0;double py0=0;TplGetXYCoordPointsList(pPntsLst,i-1,px0,py0);//获取点坐标
				double ang01=TextDirAngleFromPP(px0,py0,px1,py1);
				pShort.z = (ang01+ang12)/2;
			}
			else
				pShort.z=ang12;
		}
		else
		{
			switch(nLab)
			{
			case -1:
				{
					double px0=0;double py0=0;TplGetXYCoordPointsList(pPntsLst,i-1,px0,py0);//获取点坐标
					double ang01=TextDirAngleFromPP(px0,py0,px1,py1);
					pShort.z = (ang01+ang12)/2;
				}
				break;
			case 1:
				{
					double px3=0;double py3=0;TplGetXYCoordPointsList(pPntsLst,i+2,px3,py3);//获取点坐标
					double ang23=TextDirAngleFromPP(px2,py2,px3,py3);
					pShort.z=(ang12+ang23)/2;
				}
				break;
			default:pShort.z=ang12;
				break;
			}
		}
		//////////////////////////////////////////////////////////////////////////		
		dispmap.insert(map<double,SPo_DPoint>::value_type(dDis,pShort));
	}
	map<double,SPo_DPoint>::iterator itr=dispmap.find(dismin);
	if(itr!=dispmap.end())
		return itr->second;
	else
		return dp;
};

/// <summary>
/// 计算由directX1,directY1,directX2,directY2组成两点的方向直线与下x1,y1,x2,y2组成线段的交点
/// </summary>
/// <param name="x1">线段第一点坐标X</param>
/// <param name="y1">线段第一点坐标Y</param>
/// <param name="x2">线段第二点坐标X</param>
/// <param name="y2">线段第二点坐标Y</param>
/// <param name="directX1">第一个方向点的坐标X</param>
/// <param name="directY1">第一个方向点的坐标Y</param>
/// <param name="directX2">第二个方向点的坐标X</param>
/// <param name="directY2">第二个方向点的坐标Y</param>
/// <param name="dPt.x">交点的X坐标</param>
/// <param name="dPt.y">交点的Y坐标</param>
//返回值的z坐标表示是否有交点
template <class TYPE1,class TYPE2> SPo_DPoint inline GetLinesConnction(TYPE1 x1,TYPE1 y1,TYPE1 x2,TYPE1 y2,
								TYPE2 directX1,TYPE2 directY1,TYPE2 directX2,TYPE2 directY2)
{
	SPo_DPoint dPt;
	if((x1==x2&&y1==y2)||(directX1==directX2&&directY1==directY2))
	{dPt.x=dPt.y=dPt.z=0;}
	else	//不是同一点
	{
		if((x1-x2)*(directY1-directY2)==(y1-y2)*(directX1-directX2))
		{dPt.x=dPt.y=dPt.z=0;}
		else//不平行或不重和
		{
			if(y1==y2)
			{
				if(directY1==directY2)
				{
					dPt.x=dPt.y=dPt.z=0;
				}
				else 
				{
					dPt.y=y1;dPt.x=(directX1-directX2)*(y1-directY1)/(directY1-directY2)+directX1;
					if(dPt.x<=max(x1,x2)&&dPt.x>=min(x1,x2))
						dPt.z = 1;
					else dPt.z = 0;
				}
			}
			else if(directY1==directY2)
			{
				if(y1==y2){dPt.x=dPt.y=dPt.z=0;}
				else 
				{
					dPt.y=directY1;dPt.x=(x1-x2)*(directY1-y1)/(y1-y2)+x1;
					if(dPt.x<=max(x1,x2)&&dPt.x>=min(x1,x2))
						dPt.z = 1;
					else
						dPt.z = 0;
				}
			}
			else
			{
				double t=(x1-x2)/(y1-y2),dt=(directX1-directX2)/(directY1-directY2);
				if(t==dt){dPt.x=dPt.y=dPt.z=0;}
				else
				{
					dPt.y=(directX1-x1+t*y1-dt*directY1)/(t-dt);dPt.x=t*(dPt.y-y1)+x1;
					if((dPt.x>=min(x1,x2)&&dPt.x<=max(x1,x2))
						&&(dPt.y>=min(y1,y2)&&dPt.y<=max(y1,y2)))
						dPt.z = 1;
					else
						dPt.z = 0;
				}
			}
		}
	}
	return dPt;
};

template <class PNTTYPE1,class PNTTYPE2> SPo_DPoint inline GetLinesConnction(PNTTYPE1 &p1,PNTTYPE1 &p2,PNTTYPE2 &p3,PNTTYPE2 &p4)
{
	double x1=0;double y1=0;double x2=0;double y2=0;double x3=0;double y3=0;double x4=0;double y4=0;
	TplGetXYCoordPoint(p1,x1,y1);TplGetXYCoordPoint(p2,x2,y2);
	TplGetXYCoordPoint(p3,x3,y3);TplGetXYCoordPoint(p4,x4,y4);
	return GetLinesConnction(x1,y1,x2,y2,x3,y3,x4,y4);
};
//计算直线p1p2和直线p3p4的交点坐标,返回值中的z代表是否已经求得p结果
template <class TYPE12,class TYPE34> SPo_DPoint CalLineWithLineIntersectPoint(TYPE12 x1,TYPE12 y1,
																			  TYPE12 x2,TYPE12 y2,
																			  TYPE34 x3,TYPE34 y3,
																			  TYPE34 x4,TYPE34 y4)
{
	SPo_DPoint dPtR(0,0,0);
	if((x1==x2&&y1==y2)||(x3==x4&&y3==y4))
		0;
	else
	{
		if((x1==x3&&y1==y3)||(x3==x2&&y3==y2))
		{
			dPtR.x = x3;dPtR.y=y3;dPtR.z = 1;
		}
		else if((x1==x4&&y1==y4)||(x2==x4&&y2==y4))
		{
			dPtR.x = x4;dPtR.y=y4;dPtR.z = 1;
		}
		else if((x1==x3&&y1==y3)||(x1==x4&&y1==y4))
		{
			dPtR.x = x1;dPtR.y=y1;dPtR.z = 1;
		}
		else if((x3==x2&&y3==y2)||(x2==x4&&y2==y4))
		{
			dPtR.x = x2;dPtR.y=y2;dPtR.z = 1;
		}
		else
		{
			double dx1=x2-x1;double dx2=x4-x3;double dy1=y2-y1;double dy2=y4-y3;
			if(dx2*dy1-dy2*dx1)//两条直线必相交
			{
				dPtR.x = (dx1*dx2*(y3-y1)+dx2*x1*dy1-dx1*x3*dy2)/(dx2*dy1-dx1*dy2);
				dPtR.y = (y1*dx1*dy2-y3*dx2*dy1+(x3-x1)*dy1*dy2)/(dy2*dx1-dx2*dy1);
				dPtR.z = 1;
			}
			else//两直线必平行.
				0;
		}
	}
	return dPtR;
};
//---------通过已知点和距离在某个角度上得到另一点----------未知点pt1->pt(已知点)
template <class TYPE,class PNTTYPE> SPo_DPoint2D inline GetPtFromPtAndLength(TYPE Length,PNTTYPE &pt, double radian)
{	
	double dx=0;double dy=0;TplGetXYCoordPoint(pt,dx,dy);
	double rx = dx - cos(radian) * Length;
	double ry = dy - sin(radian) * Length;
	
	return SPo_DPoint2D(rx,ry);
};
//判断线段与线段的关系，交为TRUE 其他FALSE,其中一条线为特殊水平线
template<class TYPE1,class TYPE2> bool inline IsLineWithHLine(TYPE1 xleft,TYPE1 xright,TYPE1 yline,TYPE2 spX,TYPE2 spY,TYPE2 fpX,TYPE2 fpY)
{
	if((yline-spY)*(yline-fpY)<=0)
	{
		float dx=fpX-spX;	float dy=fpY-spY;
		if((((yline-spY)*dx-(xleft-spX)*dy)*
			((yline-spY)*dx-(xright-spX)*dy))<0)
			return true;
		else
			return false;
	}
	else
		return false;
};

//判断线段与线段的关系，交为TRUE 其他FALSE,
//p1 p2 构成第一条线段，p3，p4构成另一条线段
template<class TYPE1,class TYPE2> bool inline IsLineWithLine(TYPE1 p1x,TYPE1 p1y,TYPE1 p2x,TYPE1 p2y,
															 TYPE2 p3x,TYPE2 p3y,TYPE2 p4x,TYPE2 p4y)
{
	float dx=p2x-p1x;float dy=p2y-p1y;
	
	bool Con12=(((p3y-p1y)*dx-dy*(p3x-p1x))*((p4y-p1y)*dx-dy*(p4x-p1x))<0?true:false);
	
	dx=p4x-p3x;dy=p4y-p3y;
	
	bool Con34=(((p1y-p3y)*dx-dy*(p1x-p3x))*((p2y-p3y)*dx-dy*(p2x-p3x))<0?true:false);
	
	return (Con34&&Con12);
};

//判断线段与线段的关系，交为TRUE 其他FALSE,
//p1 p2 构成第一条线段，p3，p4构成另一条线段
template<class PNTTYPE1,class PNTTYPE2> bool inline IsLineWithLine(PNTTYPE1 *pt1,PNTTYPE1 *pt2,
															 PNTTYPE2 *pt3,PNTTYPE2 *pt4)
{
	double dx1=0;double dy1=0;
	TplGetXYCoordPoint(*pt1,dx1,dy1);
	double dx2=0;double dy2=0;
	TplGetXYCoordPoint(*pt2,dx2,dy2);
	double dx3=0;double dy3=0;
	TplGetXYCoordPoint(*pt3,dx3,dy3);
	double dx4=0;double dy4=0;
	TplGetXYCoordPoint(*pt4,dx4,dy4);
	float dx=dx2-dx1;float dy=dy2-dy1;
	
	bool Con12=(((dy3-dy1)*dx-dy*(dx3-dx1))*((dy4-dy1)*dx-dy*(dx4-dx1))<0?true:false);
	
	dx=dx4-dx3;dy=dy4-dy3;
	
	bool Con34=(((dy1-dy3)*dx-dy*(dx1-dx3))*((dy2-dy3)*dx-dy*(dx2-dx3))<0?true:false);
	
	return (Con34&&Con12);
};

//判断线段与线段的关系，交为TRUE 其他FALSE,其中一条线为特殊垂线
template<class TYPE1,class TYPE2> bool inline IsLineWithVLine(TYPE1 ytop,TYPE1 ybottom,TYPE1 xline,
															  TYPE2 spX,TYPE2 spY,TYPE2 fpX,TYPE2 fpY)
{	
	if((xline-spX)*(xline-fpX)<=0)
	{
		float dx=fpX-spX;	float dy=fpY-spY;
		if((((ytop-spY)*dx-(xline-spX)*dy)*
			((ybottom-spY)*dx-(xline-spX)*dy))<0)
			return true;
		else
			return false;
	}
	else
		return false;
};
//垂线法判断点是否在区域多边形内部,多边形的点串个数大于等于4,起点和末点重合(封闭)
template<class TYPE,class PNTSLSTPTR/*点串列表地址类型*/,class INTSLSTPTR> bool inline IsPfInPgnXY(TYPE x,TYPE y,PNTSLSTPTR pPntLst,int nPtsCnt,
																							INTSLSTPTR pRings,int nRcnt,double rRadia=0,bool bExtOut = true/*是否向外扩展得到是内部的结果?否则内部包含了距离太近也不算在内部*/)
{
	if(nPtsCnt>3)
	{
		double prex=0;double prey=0;double thpx=0;double thpy=0;int ringr=0;
		
		int iPtor = 0;int i=0;
		
		int lwP=0;//记录与垂线向下延长时与边的交点个数
		for(int r=0;r<nRcnt;r++)
		{
			TplGSRingPnumRingsList(pRings,r,ringr);
			for(i=1;i<ringr;i++)
			{
				TplGetXYCoordPointsList(pPntLst,iPtor+i-1,prex,prey);
				TplGetXYCoordPointsList(pPntLst,iPtor+i,thpx,thpy);
				if(!(thpx==prex&&thpy==prey))//跳过中间的重合结点,如果前一点不等于后一点;
				{
					if(((x-thpx==0)&&(y-thpy==0))||((x-prex==0)&&(y-prey==0)))
						return true;//与节点重合,这里我们认为在内部//20160803
					else
					{
						if(((rRadia!=0)&&bExtOut)&&(IsLineWithHLine(x-rRadia/2,x+rRadia/2,y-rRadia/2,thpx,thpy,prex,prey)||
							IsLineWithHLine(x-rRadia/2,x+rRadia/2,y+rRadia/2,thpx,thpy,prex,prey)||
							IsLineWithVLine(y-rRadia/2,y+rRadia/2,x+rRadia/2,thpx,thpy,prex,prey)||
							IsLineWithVLine(y-rRadia/2,y+rRadia/2,x-rRadia/2,thpx,thpy,prex,prey)))//如果要进行扩展比较
							return false;
						
						if ( thpx == prex || // p1p2 与 y=p0.y平行 
							x < min(prex, thpx) || // 交点在p1p2延长线上 
							x >= max(prex, thpx) ) // 交点在p1p2延长线上 
							continue; 						
						if ((thpx-prex)*((thpy-prey)*(x-prex)-(thpx-prex)*(y-prey))<0) 
							lwP++; // 只统计单边交点 
					}
				}
			}
			////////
			iPtor += ringr;
		}				
		return (lwP%2)==1?true:false;	//交点奇数个true//交点偶数个false
	}
	else return false;
};

//垂线法判断点是否在区域多边形内部,多边形的点串个数大于等于4,起点和末点重合(封闭)
template<class CMPPNTTYPE/*参考点类型*/,class PNTSLSTPTR/*点串列表地址类型*/,class INTSLSTPTR/*多封闭环数组指针*/> bool inline IsPfInPgnXY(CMPPNTTYPE &cmpPt,PNTSLSTPTR pPntLst,int nPtsCnt,
																							INTSLSTPTR pRings,int nRcnt,double rRadia=0,bool bExtOut = true/*是否向外扩展得到是内部的结果?否则内部包含了距离太近也不算在内部*/)
{
	double x=0;double y=0;
	TplGetXYCoordPoint(cmpPt,x,y);
	return IsPfInPgnXY(x,y,pPntLst,nPtsCnt,pRings,nRcnt,rRadia,bExtOut);
};

//点是否在矩形之内,后四个参数分别给定矩形对角线上两点的x与y坐标,xy顺序固定,它们各自大小顺序可忽略
template<class TYPE1,class TYPE2> bool inline IsPfInRect(TYPE1 px,TYPE1 py,TYPE2 x1,TYPE2 y1,TYPE2 x2,TYPE2 y2)
{
	return ((px-x1)*(px-x2)<=0)&&((py-y1)*(py-y2)<=0);
};
//点是否在矩形之内,后四个参数分别给定矩形对角线上两点的x与y坐标,xy顺序固定,它们各自大小顺序可忽略
template<class TYPE1,class RECTTYPE> bool inline IsPfInRect(TYPE1 px,TYPE1 py,RECTTYPE *prc)
{
	double x1=0;double y1=0;double x2=0;double y2=0;
	TplGS4XYInRect(*prc,x1,y1,x2,y2);
	return IsPfInRect(px,py,x1,y1,x2,y2);
};
//点是否在矩形之内,后四个参数分别给定矩形对角线上两点的x与y坐标,xy顺序固定,它们各自大小顺序可忽略
template<class CMPPNTTYPE,class TYPE2> bool inline IsPfInRect(CMPPNTTYPE &cmpP,TYPE2 x1,TYPE2 y1,TYPE2 x2,TYPE2 y2)
{
	double x=0;double y=0;
	TplGetXYCoordPoint(cmpP,x,y);
	return IsPfInRect(x,y,x1,y1,x2,y2);
};
//点是否在矩形之内,后四个参数分别给定矩形对角线上两点的x与y坐标,xy顺序固定,它们各自大小顺序可忽略
template<class CMPPNTTYPE,class RECTTYPE> bool inline IsPfInRect(CMPPNTTYPE &cmpP,RECTTYPE *prc)
{
	double x=0;double y=0;
	TplGetXYCoordPoint(cmpP,x,y);
	return IsPfInRect(x,y,prc);
};

//判断点是否在圆内部(点与圆是否有相交部分)，fradias是投影系内的长度,pCenter是圆心,pf是要判断的点
template<class TYPE1,class TYPE2> bool inline IsPfInRound(TYPE1 pcx,TYPE1 pcy,double fradias,TYPE2 pfx,TYPE2 pfy)
{
	return (CalDistance(pcx,pcy,pfx,pfy)<fradias?true:false);
};

//判断点是否在圆内部(点与圆是否有相交部分)，fradias是投影系内的长度,pCenter是圆心,pf是要判断的点
template<class PNTTYPE1,class PNTTYPE2> bool inline IsPfInRound(PNTTYPE1 *pCenter,double fradias,PNTTYPE2 *pf)
{
	double pcx=0;double pcy=0;double pfx=0;double pfy=0;
	TplGetXYCoordPoint(*pCenter,pcx,pcy);TplGetXYCoordPoint(*pf,pfx,pfy);
	return IsPfInRound(pcx,pcy,fradias,pfx,pfy);
};
/////////////////////////////////////点是否靠近多点组成的折线
template<class TYPE1,class PNTSLSTPTR/*点串列表地址类型*/,class TYPE2> bool inline IsPfNearPll(TYPE1 sx,TYPE1 sy,PNTSLSTPTR pPolyline,int LinePointsCount,TYPE2 tTolerance)
{
	double x1=0;double y1=0;double x2=0;double y2=0;
	for(int i=0;i<LinePointsCount-1;i++)
	{
		TplGetXYCoordPointsList(pPolyline,i,x1,y1);TplGetXYCoordPointsList(pPolyline,i+1,x2,y2);
		if(!(CalDistancePointLine(sx,sy,x1,y1,x2,y2)>tTolerance))
			return true;
	}
	return false;
};
//计算比较点pC是否位于由AOB组成的小于PI角的二维空间区域，否则位于区域之外的另一侧
template<class TYPE0,class TYPE1,class TYPE2,class TYPE3> bool inline IsPfInLowPIAngleRegion(TYPE0 pCx,TYPE0 pCy,TYPE1 pAx,TYPE1 pAy,TYPE2 pOx,TYPE2 pOy,TYPE3 pBx,TYPE3 pBy)
{
	if(CalDistancePointLineUnlimited(pCx,pCy,pAx,pAy,pOx,pOy)<0.000001)return true;///在直线上
	if(CalDistancePointLineUnlimited(pCx,pCy,pBx,pBy,pOx,pOy)<0.000001)return true;///在直线上
	double dA=GetDirAngle(pOx,pOy,pAx,pAy);
	double dB=GetDirAngle(pOx,pOy,pBx,pBy);
	double dC=GetDirAngle(pOx,pOy,pCx,pCy);
	return fabs(dA-dB)<PO_PI?((dA-dC)*(dB-dC)<0?true:false):((dA-dC)*(dB-dC)<0?false:true);
}
/////////////////////////////////////点是否靠近多点组成的折线
template<class PNTTYPE,class PNTSLSTPTR/*点串列表地址类型*/,class TYPE2> bool inline IsPfNearPll(PNTTYPE &pCmpPt,PNTSLSTPTR pPolyline,int LinePointsCount,TYPE2 tTolerance)
{
	double x=0;double y=0;TplGetXYCoordPoint(pCmpPt,x,y);
	return IsPfNearPll(x,y,pPolyline,LinePointsCount,tTolerance);
};

//判断多边形与另一个多边形是否相交
template<class PNTSLSTPTR1/*点串列表地址类型*/,class PNTSLSTPTR2/*点串列表地址类型*/,class INTSLSTPTR1,class INTSLSTPTR2> bool inline IsPgnAndPgnIntersectWith(
 PNTSLSTPTR1 rgnPoints1,int rgnPtsCount1,INTSLSTPTR1 rgnlist1,int rgncount1,
 PNTSLSTPTR2 rgnPoints2,int rgnPtsCount2,INTSLSTPTR2 rgnlist2,int rgncount2)
{
	//如果第一个多边形的任意一个线段与另一个多边形的任意一个线段有相交,两个几何图形就相交
	int i=0;int j=0;
	bool b1In2 = IsPfInPgnXY(*TplGetPointRefInPoints(rgnPoints1,0),rgnPoints2,rgnPtsCount2,rgnlist2,rgncount2);
	bool b2In1 = IsPfInPgnXY(*TplGetPointRefInPoints(rgnPoints2,0),rgnPoints1,rgnPtsCount1,rgnlist1,rgncount1);
	for(i=0;i<rgnPtsCount1-1;i++)
	{
		for(j=0;j<rgnPtsCount2-1;j++)
		{
			if(IsLineWithLine(TplGetPointRefInPoints(rgnPoints1,i),TplGetPointRefInPoints(rgnPoints1,i+1),
				TplGetPointRefInPoints(rgnPoints2,j),TplGetPointRefInPoints(rgnPoints2,j+1)))
				return true;
			b2In1 = (b2In1&&IsPfInPgnXY(*TplGetPointRefInPoints(rgnPoints2,j+1),rgnPoints1,rgnPtsCount1,rgnlist1,rgncount1));
		}//如果没有符合上述情况的相交,继续判断(只剩2种情况:多边形1在多边形2内部,多边形2在多边形1内部)
		b1In2 = (b1In2&&IsPfInPgnXY(*TplGetPointRefInPoints(rgnPoints1,i+1),rgnPoints2,rgnPtsCount2,rgnlist2,rgncount2));
	}
	return b2In1||b1In2;
};

//判断多边形与折线是否相交
template<class PNTSLSTPTR1/*点串列表地址类型*/,class INTSLSTPTR1,class PNTSLSTPTR2/*点串列表地址类型*/> bool inline IsPgnAndPllIntersectWith(PNTSLSTPTR1 rgnPoints,int rgnPtsCount,INTSLSTPTR1 rgnlist,int rgncount,
																		 PNTSLSTPTR2 pllPoints,int pllPtsCount)
{
	//如果折线中的任意一个线段与多边形的任意一个线段有相交,两个几何图形就相交
	int i=0;int j=0;int r=0;int jindex = 0;
	bool plnpInrgn = IsPfInPgnXY(*TplGetPointRefInPoints(pllPoints,0),rgnPoints,rgnPtsCount,rgnlist,rgncount);//假设一开始折线点在多边形内部
	for(i=0;i<pllPtsCount-1;i++)
	{
		jindex = 0;int ringr=0;
		for(r=0;r<rgncount;r++)
		{
			TplGSRingPnumRingsList(rgnlist,r,ringr);
			for(j=0;j<ringr-1;j++)
			{
				if(IsLineWithLine(TplGetPointRefInPoints(pllPoints,i),TplGetPointRefInPoints(pllPoints,i+1),TplGetPointRefInPoints(rgnPoints,jindex+j),TplGetPointRefInPoints(rgnPoints,jindex+j+1)))
					return true;
			}
			////////////////////
			jindex += ringr;
		}
		//如果没有符合上述情况的相交,继续判断(只剩1种情况:折线在多边形内部)
		plnpInrgn = (plnpInrgn||IsPfInPgnXY(*TplGetPointRefInPoints(pllPoints,i+1),rgnPoints,rgnPtsCount,rgnlist,rgncount));//从第二点开始看是否在多边形内部
	}
	return plnpInrgn;
};

//////////////////////////两个折线串是否相交//////////////////////////////////////////
template<class PNTSLSTPTR1,class PNTSLSTPTR2> bool inline IsPllAndPllIntersectWith(PNTSLSTPTR1 pPolyline1,int PointsCount1,PNTSLSTPTR2 pPolyline2,int PointsCount2)
{
	double x1=0;double y1=0;double x2=0;double y2=0;
	double x3=0;double y3=0;double x4=0;double y4=0;
	for(int i=0;i<PointsCount1-1;i++)
	{
		TplGetXYCoordPointsList(pPolyline1,i,x1,y1);
		TplGetXYCoordPointsList(pPolyline1,i+1,x2,y2);
		for(int j=0;j<PointsCount2-1;j++)
		{
			TplGetXYCoordPointsList(pPolyline2,j,x3,y3);
			TplGetXYCoordPointsList(pPolyline2,j+1,x4,y4);
			if(IsLineWithLine(x1,y1,x2,y2,x3,y3,x4,y4))
				return true;
		}
	}
	return false;
};

//////////////////////////////////////////////////////////////////////////
template<class TYPE1,class PNTSLSTPTR> bool inline IsRectAndPolyLineIntersectWith(TYPE1 leftx1,TYPE1 topy1,TYPE1 rightx2,TYPE1 bottomy2,
																			 PNTSLSTPTR plPtlist,int pstCount)
{
	if(pstCount==0)return false;//hls added 20100925
	double pprex=0;double pprey=0;double pthpx=0;double pthpy=0;

	TplGetXYCoordPointsList(plPtlist,0,pprex,pprey);
	if(IsPfInRect(pprex,pprey,leftx1,topy1,rightx2,bottomy2))
	{
		return true;
	}
	for(int i=1;i<pstCount;i++)////第一点已讨论从第二点开始
	{
		TplGetXYCoordPointsList(plPtlist,i,pthpx,pthpy);
		
		if(IsPfInRect(pthpx,pthpy,leftx1,topy1,rightx2,bottomy2))
		{
			return true;
		}
		else
		{	//只要有一条线与矩形边界相交//if((*ppre)!=(*pthp))
			if(!(pprex==pthpx||pprey==pthpy))
			{
				if (IsLineWithVLine(topy1,bottomy2,leftx1,pprex,pprey,pthpx,pthpy)||
					IsLineWithVLine(topy1,bottomy2,rightx2,pprex,pprey,pthpx,pthpy)||
					IsLineWithHLine(leftx1,rightx2,topy1,pprex,pprey,pthpx,pthpy)||
					IsLineWithHLine(leftx1,rightx2,bottomy2,pprex,pprey,pthpx,pthpy))
					return true;
			}
		}
		pprex=pthpx;pprey=pthpy;
	}
	return false;
};

template<class RECTPTRTYPE,class PNTSLSTPTR> bool inline IsRectAndPolyLineIntersectWith(RECTPTRTYPE pRect,
																			 PNTSLSTPTR plPtlist,int pstCount)
{
	double x1=0;double y1=0;double x2=0;double y2=0;
	TplGS4XYInRect(pRect,x1,y1,x2,y2);
	return IsRectAndPolyLineIntersectWith(x1,y1,x2,y2,plPtlist,pstCount);
};

//边线相交的关系
#define RELATION_FT_CCRS 1//边线相交的关系
//前者包含后者的关系,而且边线完全不交
#define RELATION_FT_CONT 2//前者包含后者的关系,而且边线完全不交
//后者包含前者的关系,而且边线完全不交
#define RELATION_FT_CINT 3//后者包含前者的关系,而且边线完全不交
//两者相离的关系
#define RELATION_FT_CDPT 4//两者相离的关系
//判断矩形与封闭折线(区域)的相交关系
template<class TYPE1,class PNTSLSTPTR/*点串列表地址类型*/,class INTSLSTPTR> bool inline GetRectAndPolygonRelation(TYPE1 leftx1,TYPE1 topy1,TYPE1 rightx2,TYPE1 bottomy2,
																			PNTSLSTPTR pPntLst,int ptsCount,INTSLSTPTR rgnlist,int rgncount,
																			DWORD rMode/**/)
{
	
	switch(rMode)
	{
	case RELATION_FT_CCRS://边线相交的关系
		{
			return IsRectAndPolyLineIntersectWith(leftx1,topy1,rightx2,bottomy2,pPntLst,ptsCount);
		}
		break;
	case RELATION_FT_CONT://前者包含后者的关系,而且边线完全不交
		{
			double dx=0;double dy=0;
			for(int i=0;i<ptsCount;i++)
			{
				TplGetXYCoordPointsList(pPntLst,i,dx,dy);
				if(!IsPfInRect(dx,dy,leftx1,topy1,rightx2,bottomy2))
					return false;
			}
			return true;
		}
		break;
	case RELATION_FT_CINT://后者包含前者的关系,而且边线完全不交
		{
			return IsPfInPgnXY(leftx1,topy1,pPntLst,ptsCount,rgnlist,rgncount)&&
				IsPfInPgnXY(leftx1,bottomy2,pPntLst,ptsCount,rgnlist,rgncount)&&
				IsPfInPgnXY(rightx2,topy1,pPntLst,ptsCount,rgnlist,rgncount)&&
				IsPfInPgnXY(rightx2,bottomy2,pPntLst,ptsCount,rgnlist,rgncount);
		}
		break;
	case RELATION_FT_CDPT://两者相离的关系
		{
			return (!GetRectAndPolygonRelation(leftx1,topy1,rightx2,bottomy2,pPntLst,ptsCount,rgnlist,rgncount,RELATION_FT_CCRS))&&
				(!GetRectAndPolygonRelation(leftx1,topy1,rightx2,bottomy2,pPntLst,ptsCount,rgnlist,rgncount,RELATION_FT_CONT))&&
				(!GetRectAndPolygonRelation(leftx1,topy1,rightx2,bottomy2,pPntLst,ptsCount,rgnlist,rgncount,RELATION_FT_CINT));//不相交不包含也不被包含
		}
		break;
	default:
		break;
	}
	return false;
};

//判断矩形与封闭折线(区域)的相交关系
template<class RECTTYPEPTR,class PNTSLSTPTR/*点串列表地址类型*/,class INTSLSTPTR> bool inline GetRectAndPolygonRelation(RECTTYPEPTR &rc,
																			PNTSLSTPTR pPntLst,int ptsCount,INTSLSTPTR rgnlist,int rgncount,
																			DWORD rMode/**/)
{
	double x1=0;double y1=0;double x2=0;double y2=0;
	TplGS4XYInRect(rc,x1,y1,x2,y2);
	return GetRectAndPolygonRelation(x1,y1,x2,y2,pPntLst,ptsCount,rgnlist,rgncount,rMode);
};

template<class TYPE,class PNTSLSTPTR,class INTSLSTPTR> bool inline IsRectAndPolygonIntersectWith(TYPE leftx1,TYPE topy1,TYPE rightx2,TYPE bottomy2,
																				PNTSLSTPTR rgnPtlist,int ptsCount,INTSLSTPTR rgnlist,int rgncount)
{	//若与封闭折线不相交，可能区域包含矩形
	if(IsRectAndPolyLineIntersectWith(leftx1,topy1,rightx2,bottomy2,rgnPtlist,ptsCount))
		return true;
	else
	{
		if(IsPfInPgnXY(leftx1,topy1,rgnPtlist,ptsCount,rgnlist,rgncount)||
			IsPfInPgnXY(leftx1,bottomy2,rgnPtlist,ptsCount,rgnlist,rgncount)||
			IsPfInPgnXY(rightx2,topy1,rgnPtlist,ptsCount,rgnlist,rgncount)||
			IsPfInPgnXY(rightx2,bottomy2,rgnPtlist,ptsCount,rgnlist,rgncount))//矩形被包含
			return true;
		else
		{
			double x=0;double y=0;TplGetXYCoordPointsList(rgnPtlist,0,x,y);
			if(IsPfInRect(x,y,leftx1,topy1,rightx2,bottomy2))//多边形被包含
				return true;
			else
				return false;
		}
	}
};
template<class RECTPTRTYPE,class PNTSLSTPTR,class INTSLSTPTR> bool inline IsRectAndPolygonIntersectWith(RECTPTRTYPE pRect,
																				PNTSLSTPTR rgnPtlist,int ptsCount,INTSLSTPTR rgnlist,int rgncount)
{
	double x1=0;double y1=0;double x2=0;double y2=0;
	TplGS4XYInRect(pRect,x1,y1,x2,y2);
	return IsRectAndPolygonIntersectWith(x1,y1,x2,y2,rgnPtlist,ptsCount,rgnlist,rgncount);
};

//判断圆形与折线是否有相交部分，fradias是投影系内的长度,p是圆心
template<class PNTTYPE,class PNTSLSTPTR> bool inline IsRoundAndPolyLineIntersectWith(PNTTYPE &pCenter,double fradias, PNTSLSTPTR plPtlist,int ptsCount)
{
	if(ptsCount==1)
		return IsPfInRound(&pCenter,fradias,TplGetPointRefInPoints(plPtlist,0));
	else
	{
		for(int i=0;i<ptsCount-1;i++)//找任意一线段在圆内
		{
			if(CalDistancePointLine(pCenter,*TplGetPointRefInPoints(plPtlist,i),*TplGetPointRefInPoints(plPtlist,i+1))<fradias)
			{
				return true;
			}
		}
		return false;
	}
};

//判断圆形与多边形区域是否有相交部分,fradias是投影系内的长度,p是圆心
template<class PNTTYPE,class PNTSLSTPTR,class INTSLSTPTR> bool inline IsRoundAndPolygonIntersectWith(PNTTYPE &pCenter,double fradias,
																			 PNTSLSTPTR rgnPtlist,int ptsCount,INTSLSTPTR rgnlist,int rgncount)
{
	if(ptsCount<3)
		return IsRoundAndPolyLineIntersectWith(pCenter,fradias,rgnPtlist,ptsCount);
	else
	{
		for(int i=0;i<ptsCount-1;i++)//找任意一线段在圆内
		{
			if(CalDistancePointLine(pCenter,*TplGetPointRefInPoints(rgnPtlist,i),*TplGetPointRefInPoints(rgnPtlist,i+1))<fradias)
			{
				return true;
			}
		}
		//或者可能圆在多边形的内部
		return IsPfInPgnXY(pCenter,rgnPtlist,ptsCount,rgnlist,rgncount);
	}
};
//判断圆形与两点组成的矩形是否相交
template<class TYPE1,class TYPE2> bool inline IsRoundAndRectIntersectWith(TYPE1 cx,TYPE1 cy,TYPE1 fradias,TYPE2 rx1,TYPE2 ry1,TYPE2 rx2,TYPE2 ry2)
{
	if( CalDistancePointLine(cx,cy,rx1,ry1,rx1,ry2)<=fradias||
		CalDistancePointLine(cx,cy,rx1,ry1,rx2,ry1)<=fradias||
		CalDistancePointLine(cx,cy,rx2,ry1,rx2,ry2)<=fradias||
		CalDistancePointLine(cx,cy,rx1,ry2,rx2,ry2)<=fradias)//找任意一线段在圆内
		return true;
	//或者可能圆在矩形的内部
	return IsPfInRect(cx,cy,rx1,ry1,rx2,ry2);	
};
//判断圆形与两点组成的矩形是否相交
template<class TYPE1,class RECTPTRTPE> bool inline IsRoundAndRectIntersectWith(TYPE1 cx,TYPE1 cy,TYPE1 fradias,RECTPTRTPE pRect)
{
	double x1=0;double y1=0;double x2=0;double y2=0;
	TplGS4XYInRect(pRect,x1,y1,x2,y2);
	return IsRoundAndRectIntersectWith(cx,cy,x1,y1,x2,y2);
};
//判断圆形与两点组成的矩形是否相交
template<class PNTTYPE,class TYPE1,class RECTPTRTPE> bool inline IsRoundAndRectIntersectWith(PNTTYPE &pCenter,TYPE1 fradias,RECTPTRTPE pRect)
{
	double x=0;double y=0;
	TplGetXYCoordPoint(pCenter,x,y);
	return IsRoundAndRectIntersectWith(x,y,pRect);
};

//单点选取面型要素
template <class PNTTYPE,class PNTSLSTPTR,class INTSLSTPTR> bool inline PNTselApFeatures(PNTTYPE &pCtroPoint/*单个控制点*/, PNTSLSTPTR ptsTarget, int pstCount, INTSLSTPTR rgnlist,int rgncount,float fTolerance)
{
	return IsPfInPgnXY(pCtroPoint,ptsTarget,pstCount,rgnlist,rgncount);
};
//单点选取点型要素	
template <class PNTTYPE1,class PNTTYPE2> bool inline PNTselPpfeatures(PNTTYPE1 &pCtroPoint, PNTTYPE2 &pTarget/*目标点的第一个定位点*/, float fTolerance)
{
	return CalDistance(pCtroPoint,pTarget)<fTolerance?true:false;
};
//单点选取线型要素
template <class PNTTYPE,class PNTSLSTPTR> bool inline PNTselLpFeatures(PNTTYPE &pCtroPoint, PNTSLSTPTR ptsTarget/*目标要素的坐标数组*/, int pstCount, float fTolerance)
{
	if(pstCount == 0)		return false;
	else if(pstCount == 1)	return CalDistance(pCtroPoint,*TplGetPointRefInPoints(ptsTarget,0))<fTolerance?true:false;
	else
	{
		for(int i=0;i<pstCount-1;i++)
		{
			if(CalDistancePointLine(pCtroPoint,*TplGetPointRefInPoints(ptsTarget,i),*TplGetPointRefInPoints(ptsTarget,i+1))<=fTolerance)
				return true;
		}
		return false;
	}
};

//由前三点获取平行四边型的第四点
PointF inline GetPointOf4InPxsbx(float x1,float y1,float x2,float y2,float x3,float y3)
{
	return PointF(x3-x2+x1,y3-y2+y1);
};

//由前三点获取平行四边型的第四点
template<class PNTTYPE> PointF inline GetPointOf4InPxsbx(PNTTYPE &pt1,PNTTYPE &pt2,PNTTYPE &pt3)
{
	double x1=0;double y1=0;double x2=0;double y2=0;double x3=0;double y3=0;
	TplGetXYCoordPoint(pt1,x1,y1);TplGetXYCoordPoint(pt2,x2,y2);TplGetXYCoordPoint(pt3,x3,y3);
	return GetPointOf4InPxsbx(x1,y1,x2,y2,x3,y3);
};

//##Begin Model Documentation
//按照先后顺序方向计算两点直线的方向角(0~2*PI)，直角坐标系采用y下，x右的方向,返回
//值为双精度型弧度
//##End Model Documentation
//##ModelId=46EDE5B80186
double inline GetDirAngle(double x1, double y1, double x2, double y2)
{
	double angle = 0;			
	double dy = y1-y2;//坐标纵轴翻转
	double dx = x2-x1;
	dx==0?(dy==0?(angle=0)
		:(dy>0?(angle=PO_PI/2):(angle=PO_PI*1.5)))
		:(dx>0?(dy>0?(angle=atan(dy/dx)):(PO_PI*2+atan(dy/dx)))
		:(PO_PI+atan(dy/dx)));
	return angle;
};

//##Begin Model Documentation
//按照先后顺序方向计算三点两直线组成的以中点为圆心的方向角(0~2*PI)即前进方向向左的
//夹角，直角坐标系采用y下，x右的方向,返回值为双精度型弧度
//##End Model Documentation
//##ModelId=46EDE60B0213
double inline GetDirAngle3(double x1, double y1, double x2, double y2, double x3, double y3)
{
	double angle1 = GetDirAngle(x2,y2,x1,y1);
	double angle2 = GetDirAngle(x2,y2,x3,y3);
	double angle3 = angle1-angle2;
	return (angle3<0?(PO_PI*2-angle3):angle3);
};



#endif /* GEOMETRYCALCULATOR_H_HEADER_INCLUDED_B0F93B24 */
