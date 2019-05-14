#ifndef GEOMETRYCALCULATOR_H_HEADER_INCLUDED_B0F93B24
#define GEOMETRYCALCULATOR_H_HEADER_INCLUDED_B0F93B24


//##ModelId=4F06FC6C01D4
void inline TcCoordConverseFst(VISZ_DRAWPARMS *pParm,vector<SPo_DPoint2D> *pOrdinates,PointF *ptOut)//���������㷨��ִ�нϿ�
{
	int i=0;
	for(vector<SPo_DPoint2D>::iterator itr=pOrdinates->begin();itr!=pOrdinates->end();itr++,i++)
		pParm->TcCoordConverse(itr->x,itr->y,&(ptOut[i].X),&(ptOut[i].Y));
};
///////���ڵ������������ת��ƽ�Ƶ�ת��
template<class TYPE1> void inline SPoPntsConvRotateAndMove(SPo_TplPoint<TYPE1> *pts/*in and out*/,int nCount,float fRate/*���ű���ϵ��!=0*/,double dAngle/*��ת�Ļ���*/,double dOffsetX,double dOffsetY)
{
	for(int i = 0;i<nCount;i++)
	{
		double dox = pts[i].x*fRate;
		double doy = pts[i].y*fRate;//����
		double tdox = dox*cos(dAngle)-doy*sin(dAngle);
		double tdoy = dox*sin(dAngle)+doy*cos(dAngle);//��ת
		pts[i].x = (TYPE1)(tdox+dOffsetX);
		pts[i].y = (TYPE1)(tdoy+dOffsetY);//ƽ��
	}
};

///////���ڵ������������ת��ƽ�Ƶ�ת��
void inline SPoPntsConvRotateAndMove(POINT *pts/*in and out*/,int nCount,float fRate/*���ű���ϵ��!=0*/,double dAngle/*��ת�Ļ���*/,double dOffsetX,double dOffsetY)
{
	for(int i = 0;i<nCount;i++)
	{
		double dox = pts[i].x*fRate;
		double doy = pts[i].y*fRate;//����
		double tdox = dox*cos(dAngle)-doy*sin(dAngle);
		double tdoy = dox*sin(dAngle)+doy*cos(dAngle);//��ת
		pts[i].x = (LONG)(tdox+dOffsetX);
		pts[i].y = (LONG)(tdoy+dOffsetY);//ƽ��
	}
};

///////���ڵ������������ת��ƽ�Ƶ�ת��
void inline SPoPntsConvRotateAndMove(PointF *pts/*in and out*/,int nCount,float fRate/*���ű���ϵ��!=0*/,double dAngle/*��ת�Ļ���*/,double dOffsetX,double dOffsetY)
{
	for(int i = 0;i<nCount;i++)
	{
		double dox = pts[i].X*fRate;
		double doy = pts[i].Y*fRate;//����
		double tdox = dox*cos(dAngle)-doy*sin(dAngle);
		double tdoy = dox*sin(dAngle)+doy*cos(dAngle);//��ת
		pts[i].X = (float)(tdox+dOffsetX);
		pts[i].Y = (float)(tdoy+dOffsetY);//ƽ��
	}
};

///////���ڵ������������ת��ƽ�Ƶ�ת��
void inline SPoPntsConvRotateAndMove(Point *pts/*in and out*/,int nCount,float fRate/*���ű���ϵ��!=0*/,double dAngle/*��ת�Ļ���*/,double dOffsetX,double dOffsetY)
{
	for(int i = 0;i<nCount;i++)
	{
		double dox = pts[i].X*fRate;
		double doy = pts[i].Y*fRate;//����
		double tdox = dox*cos(dAngle)-doy*sin(dAngle);
		double tdoy = dox*sin(dAngle)+doy*cos(dAngle);//��ת
		pts[i].X = (INT)(tdox+dOffsetX);
		pts[i].Y = (INT)(tdoy+dOffsetY);//ƽ��
	}
};

///////���ڵ������������ת��ƽ�Ƶ�ת��
template<class TYPE1> void inline SPoPntsConvRotateAndMove(SPo_TplPoint2D<TYPE1> *pts/*in and out*/,int nCount,float fRate/*���ű���ϵ��!=0*/,double dAngle/*��ת�Ļ���*/,double dOffsetX,double dOffsetY)
{
	for(int i = 0;i<nCount;i++)
	{
		double dox = pts[i].x*fRate;
		double doy = pts[i].y*fRate;//����
		double tdox = dox*cos(dAngle)-doy*sin(dAngle);
		double tdoy = dox*sin(dAngle)+doy*cos(dAngle);//��ת
		pts[i].x = (TYPE1)(tdox+dOffsetX);
		pts[i].y = (TYPE1)(tdoy+dOffsetY);//ƽ��
	}
};
//���������ľ���
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

///////////////////////////�˴�Լ���Ƕȵķ����ڵѿ�������ϵ�У�ֱ��p1p2������ˮƽx��������ļн�Ϊ�Ƕȷ���ȡֵΪ[0,360),����[0,PO_2PI)
///////////////////////////������Ĭ����Ļ��y�����µ�����ϵ�У�
//------����pt1->pt2�ĽǶ�(�Զȼ���)//bYup��ʾ�Ƿ�Y������
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
/////////////////////�������͵���������ֱ�߶�ά�ϵ����,���ػ���//bYup��ʾ�Ƿ�Y������
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

//�Զȼ����ĽǶȴӵѿ�������ϵ����Ļ����ϵת��
double inline AngleAng_DCRTOSCR(double dAng)
{
	while(dAng>360){dAng-=360;}
	if(IsValueNearUnlimited(dAng,0))return 0;
	else return 360-dAng;
};
//�Զȼ����ĽǶȴ���Ļ����ϵ���ѿ�������ϵת��
double inline AngleAng_SCRTODCR(double dAng)
{
	return AngleAng_DCRTOSCR(dAng);
};

//�Ի��ȼ����ĽǶȴӵѿ�������ϵ����Ļ����ϵת��
double inline AngleRad_DCRTOSCR(double dRad)
{
	while(dRad>PO_2PI){dRad-=PO_2PI;}
	if(IsValueNearUnlimited(dRad,0))return 0;
	else return PO_2PI-dRad;
};
//�Ի��ȼ����ĽǶȴ���Ļ����ϵ���ѿ�������ϵת��
double inline AngleRad_SCRTODCR(double dRad)
{
	return AngleRad_DCRTOSCR(dRad);
};

//��p����p1p2��ɵ����޳�ֱ�ߵľ���
template <class TYPE,class TYPE1> double inline CalDistancePointLineUnlimited(TYPE pX,TYPE pY,TYPE1 pX1,TYPE1 pY1,TYPE1 pX2,TYPE1 pY2)
{
	double c=CalDistance(pX1,pY1,pX2,pY2);		if(c<0.000001) return CalDistance(pX,pY,pX1,pY1);
	
	if(fabs(pX1-pX2)<0.000001/*<0.1*/)//����//d=;//�㵽ֱ�߶��ӳ��ߵĴ��߾���
	{
		return fabs(pX-pX1);
	}
	else if(fabs(pY1-pY2)<0.000001/*<0.1*/)//ˮƽ��
	{
		return fabs(pY-pY1);
	}
	else
	{
		double k = (double)(pY2-pY1)/(pX2-pX1);//P1P2б��,-1/k��ʶ���ߵ�б��;����P1P2��ֱ�ߣ�y = k*x+f;		
		double f = pY1-k*pX1;
		//��P1�Ĵ��߷���:y=(-1/k)*x+h1;	��P2�Ĵ��߷���:y=(-1/k)*x+h2;
		double h1 = pY1+pX1/k;double h2 = pY2+pX2/k;double h = pY+pX/k;
		
		double xPos = (h-f)/(k+1/k);
		double yPos = k*xPos+f;
		return CalDistance(pX,pY,xPos,yPos);
	}
};

//��p���߶�p1p2�ľ���
template <class TYPE,class TYPE1> double inline CalDistancePointLine(TYPE pX,TYPE pY,TYPE1 pX1,TYPE1 pY1,TYPE1 pX2,TYPE1 pY2)
{
	double a=CalDistance(pX1,pY1,pX,pY);		if(a<0.000001) return 0.0;
	
	double b=CalDistance(pX,pY,pX2,pY2);		if(b<0.000001) return 0.0;
	
	double c=CalDistance(pX1,pY1,pX2,pY2);		if(c<0.000001) return a;
	
	if(fabs(pX1-pX2)<0.000001/*<0.1*/)//����//d=;//�㵽ֱ�߶��ӳ��ߵĴ��߾���
	{
		if(pY<min(pY1,pY2)||pY>max(pY1,pY2))
			return min(a,b);
		else 
			return fabs(pX-pX1);
	}
	else if(fabs(pY1-pY2)<0.000001/*<0.1*/)//ˮƽ��
	{
		if(pX<min(pX1,pX2)||pX>max(pX1,pX2))
			return min(a,b);
		else
			return fabs(pY-pY1);
	}
	else
	{
		double k = (double)(pY2-pY1)/(pX2-pX1);//P1P2б��,-1/k��ʶ���ߵ�б��;����P1P2��ֱ�ߣ�y = k*x+f;		
		double f = pY1-k*pX1;
		//��P1�Ĵ��߷���:y=(-1/k)*x+h1;	��P2�Ĵ��߷���:y=(-1/k)*x+h2;
		double h1 = pY1+pX1/k;double h2 = pY2+pX2/k;double h = pY+pX/k;
		
		if(h<min(h1,h2)||h>max(h1,h2))
		{
			return min(a,b);
		}
		else
		{///////////////����P�Ĵ��ߣ�y=(-1/k)*x+h;����P1P2��ֱ�ߣ�y = k*x+f;
			double xPos = (h-f)/(k+1/k);
			double yPos = k*xPos+f;
			return CalDistance(pX,pY,xPos,yPos);
		}
	}
};

//��p���߶�p1p2�ľ���
template <class PNTTYPE,class TYPE1> double inline CalDistancePointLine(PNTTYPE &pCmpPt,TYPE1 pX1,TYPE1 pY1,TYPE1 pX2,TYPE1 pY2)
{
	double x=0;double y=0;
	TplGetXYCoordPoint(pCmpPt,x,y);
	return CalDistancePointLine(x,y,pX1,pY1,pX2,pY2);
};

//��p���߶�p1p2�ľ���
template <class PNTTYPE1,class PNTTYPE2> double inline CalDistancePointLine(PNTTYPE1 &pCmpPt,PNTTYPE2 &pP1,PNTTYPE2 &pP2)
{
	double x=0;double y=0;double pX1=0;double pY1=0;double pX2=0;double pY2=0;
	TplGetXYCoordPoint(pCmpPt,x,y);TplGetXYCoordPoint(pP1,pX1,pY1);TplGetXYCoordPoint(pP2,pX2,pY2);
	return CalDistancePointLine(x,y,pX1,pY1,pX2,pY2);
};

//�����������������
template <class TYPE,class TYPE1> double inline CalArea3pTrig(TYPE pX,TYPE pY,TYPE1 pX1,TYPE1 pY1,TYPE1 pX2,TYPE1 pY2)
{
	return 0.5*CalDistance(pX1,pY1,pX2,pY2)*CalDistancePointLine(pX,pY,pX1,pY1,pX2,pY2);
}
//�����������������
template <class PNTTYPE1,class PNTTYPE2> double inline CalArea3pTrig(PNTTYPE1 &pCmpPt,PNTTYPE2 &pP1,PNTTYPE2 &pP2)
{
	return 0.5*CalDistance(pP1,pP2)*CalDistancePointLine(pCmpPt,pP1,pP2);
}
//�����߶�p1p2�ϵ�p��������ĵ㣬����z���껹���������߶ε�ǰ��(-1)���м�(0)�����(1)
template <class TYPE,class TYPE1,class TYPE2> SPo_DPoint inline CalNearestPointOnLineFrom(TYPE pX,TYPE pY,TYPE1 pX1,TYPE1 pY1,TYPE2 pX2,TYPE2 pY2)
{
	double a=CalDistance(pX1,pY1,pX,pY);		if(a<0.000001) return SPo_DPoint(pX1,pY1,-1);
	
	double b=CalDistance(pX,pY,pX2,pY2);		if(b<0.000001) return SPo_DPoint(pX2,pY2,1);
	
	double c=CalDistance(pX1,pY1,pX2,pY2);		if(c<0.000001) return SPo_DPoint(pX2,pY2,0);
	
	if(fabs(pX1-pX2)<0.000001/*<0.1*/)//����//d=;//�㵽ֱ�߶��ӳ��ߵĴ��߾���
	{
		if(pY<=min(pY1,pY2))
			return SPo_DPoint(pX1,min(pY1,pY2),pY1>pY2?1:-1);
		else if(pY>=max(pY1,pY2))
			return SPo_DPoint(pX1,max(pY1,pY2),pY1>pY2?-1:1);
		else
			return SPo_DPoint(pX1,pY,0);
	}
	else if(fabs(pY1-pY2)<0.000001/*<0.1*/)//ˮƽ��
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
		double k = (double)(pY2-pY1)/(pX2-pX1);//P1P2б��,-1/k��ʶ���ߵ�б��;����P1P2��ֱ�ߣ�y = k*x+f;		
		double f = pY1-k*pX1;
		//��P1�Ĵ��߷���:y=(-1/k)*x+h1;	��P2�Ĵ��߷���:y=(-1/k)*x+h2;
		double h1 = pY1+pX1/k;double h2 = pY2+pX2/k;double h = pY+pX/k;
		if(h<min(h1,h2)||h>max(h1,h2))
		{
			if(a<b)
				return SPo_DPoint(pX1,pY1,-1);
			else 
				return SPo_DPoint(pX2,pY2,1);
		}
		else
		{///////////////����P�Ĵ��ߣ�y=(-1/k)*x+h;����P1P2��ֱ�ߣ�y = k*x+f;
			double xPos = (h-f)/(k+1/k);
			double yPos = k*xPos+f;
			return SPo_DPoint(xPos,yPos,0);
		}
	}
};

double inline TextDirAngleFromPP(double dx1,double dy1,double dx2,double dy2,bool bVerti=false/*�Ƿ�ֱ*/)
{
	if((dx1==dx2)&&(dy1==dy2))	return 0;
	
	if(dx1==dx2)//��ֱ��
	{
		return bVerti?(dy1>dy2?0:PO_PI):(dy1>dy2?PO_PIHALF:PO_3P2PI);
	}
	else if(dy1==dy2)//ˮƽ��
	{
		return bVerti?(dx1<dx2?PO_3P2PI:PO_PIHALF):(dx1<dx2?0:PO_PI);
	}
	else//б��
	{
		double k0 = (dy2-dy1)/(dx2-dx1);
		
		double ddangle = atan(k0);

		return bVerti?(dx1>dx2?PO_PI/2-ddangle:-PO_PI/2-ddangle):(dx1>dx2?PO_PI-ddangle:-ddangle);
	}
};

#pragma warning (disable:4786)//�������ƹ����ľ���
//��������pts�ϵ�p��������ĵ�,���з���ֵ�е�z�����¼�˸õ�������ǰ������ĽǶ�,���ػ���ֵ//z�Ƕ������ȡֵΪ���·�ʽ
//0�ڶ˵��ϣ�����Ϊ��ĩ�߶εķ����
//1��ĳ���ϣ�Ϊ�öεķ����
//2���м��ĳ���ڵ��ϣ��Ƕ˵㣩��Ϊǰ�η���Ǽ�ȥ��ǰ���μнǵ�һ��
template <class TYPE,class PNTSLSTPTR/*�㴮�б��ַ����*/> SPo_DPoint inline CalNearestPointOnStrockLineFrom(TYPE pX,TYPE pY,PNTSLSTPTR pPntsLst,int npcnt)
{
	SPo_DPoint dp;
	if(npcnt<2)return dp;
	
	map<double,SPo_DPoint> dispmap;
	double dismin;double px1=0;double py1=0;double px2=0;double py2=0;
	for(int i=0;i<npcnt-1;i++)
	{
		TplGetXYCoordPointsList(pPntsLst,i,px1,py1);TplGetXYCoordPointsList(pPntsLst,i+1,px2,py2);//��ȡ������

		double dDis=CalDistancePointLine(pX,pY,px1,py1,px2,py2);//�������
		SPo_DPoint pShort=CalNearestPointOnLineFrom(pX,pY,px1,py1,px2,py2);//�������ϵ�
		dismin=(i==0?dDis:min(dismin,dDis));int nLab = pShort.z;
		//����Ƕ�///////////////////////////////////////////////////////////////
		double ang12=TextDirAngleFromPP(px1,py1,px2,py2);
		if(i==0)/////////////////��һ��
		{
			if(nLab==1)//���
			{
				if(npcnt==2)
					pShort.z=ang12;
				else//////////
				{
					double px3=0;double py3=0;TplGetXYCoordPointsList(pPntsLst,i+2,px3,py3);//��ȡ������
					double ang23=TextDirAngleFromPP(px2,py2,px3,py3);
					pShort.z=(ang12+ang23)/2;
				}
			}
			else
				pShort.z=ang12;
		}
		else if(i==(npcnt-2))//��ĩ��
		{
			if(nLab==-1)//ǰ��
			{
				double px0=0;double py0=0;TplGetXYCoordPointsList(pPntsLst,i-1,px0,py0);//��ȡ������
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
					double px0=0;double py0=0;TplGetXYCoordPointsList(pPntsLst,i-1,px0,py0);//��ȡ������
					double ang01=TextDirAngleFromPP(px0,py0,px1,py1);
					pShort.z = (ang01+ang12)/2;
				}
				break;
			case 1:
				{
					double px3=0;double py3=0;TplGetXYCoordPointsList(pPntsLst,i+2,px3,py3);//��ȡ������
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
/// ������directX1,directY1,directX2,directY2�������ķ���ֱ������x1,y1,x2,y2����߶εĽ���
/// </summary>
/// <param name="x1">�߶ε�һ������X</param>
/// <param name="y1">�߶ε�һ������Y</param>
/// <param name="x2">�߶εڶ�������X</param>
/// <param name="y2">�߶εڶ�������Y</param>
/// <param name="directX1">��һ������������X</param>
/// <param name="directY1">��һ������������Y</param>
/// <param name="directX2">�ڶ�������������X</param>
/// <param name="directY2">�ڶ�������������Y</param>
/// <param name="dPt.x">�����X����</param>
/// <param name="dPt.y">�����Y����</param>
//����ֵ��z�����ʾ�Ƿ��н���
template <class TYPE1,class TYPE2> SPo_DPoint inline GetLinesConnction(TYPE1 x1,TYPE1 y1,TYPE1 x2,TYPE1 y2,
								TYPE2 directX1,TYPE2 directY1,TYPE2 directX2,TYPE2 directY2)
{
	SPo_DPoint dPt;
	if((x1==x2&&y1==y2)||(directX1==directX2&&directY1==directY2))
	{dPt.x=dPt.y=dPt.z=0;}
	else	//����ͬһ��
	{
		if((x1-x2)*(directY1-directY2)==(y1-y2)*(directX1-directX2))
		{dPt.x=dPt.y=dPt.z=0;}
		else//��ƽ�л��غ�
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
//����ֱ��p1p2��ֱ��p3p4�Ľ�������,����ֵ�е�z�����Ƿ��Ѿ����p���
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
			if(dx2*dy1-dy2*dx1)//����ֱ�߱��ཻ
			{
				dPtR.x = (dx1*dx2*(y3-y1)+dx2*x1*dy1-dx1*x3*dy2)/(dx2*dy1-dx1*dy2);
				dPtR.y = (y1*dx1*dy2-y3*dx2*dy1+(x3-x1)*dy1*dy2)/(dy2*dx1-dx2*dy1);
				dPtR.z = 1;
			}
			else//��ֱ�߱�ƽ��.
				0;
		}
	}
	return dPtR;
};
//---------ͨ����֪��;�����ĳ���Ƕ��ϵõ���һ��----------δ֪��pt1->pt(��֪��)
template <class TYPE,class PNTTYPE> SPo_DPoint2D inline GetPtFromPtAndLength(TYPE Length,PNTTYPE &pt, double radian)
{	
	double dx=0;double dy=0;TplGetXYCoordPoint(pt,dx,dy);
	double rx = dx - cos(radian) * Length;
	double ry = dy - sin(radian) * Length;
	
	return SPo_DPoint2D(rx,ry);
};
//�ж��߶����߶εĹ�ϵ����ΪTRUE ����FALSE,����һ����Ϊ����ˮƽ��
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

//�ж��߶����߶εĹ�ϵ����ΪTRUE ����FALSE,
//p1 p2 ���ɵ�һ���߶Σ�p3��p4������һ���߶�
template<class TYPE1,class TYPE2> bool inline IsLineWithLine(TYPE1 p1x,TYPE1 p1y,TYPE1 p2x,TYPE1 p2y,
															 TYPE2 p3x,TYPE2 p3y,TYPE2 p4x,TYPE2 p4y)
{
	float dx=p2x-p1x;float dy=p2y-p1y;
	
	bool Con12=(((p3y-p1y)*dx-dy*(p3x-p1x))*((p4y-p1y)*dx-dy*(p4x-p1x))<0?true:false);
	
	dx=p4x-p3x;dy=p4y-p3y;
	
	bool Con34=(((p1y-p3y)*dx-dy*(p1x-p3x))*((p2y-p3y)*dx-dy*(p2x-p3x))<0?true:false);
	
	return (Con34&&Con12);
};

//�ж��߶����߶εĹ�ϵ����ΪTRUE ����FALSE,
//p1 p2 ���ɵ�һ���߶Σ�p3��p4������һ���߶�
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

//�ж��߶����߶εĹ�ϵ����ΪTRUE ����FALSE,����һ����Ϊ���ⴹ��
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
//���߷��жϵ��Ƿ������������ڲ�,����εĵ㴮�������ڵ���4,����ĩ���غ�(���)
template<class TYPE,class PNTSLSTPTR/*�㴮�б��ַ����*/,class INTSLSTPTR> bool inline IsPfInPgnXY(TYPE x,TYPE y,PNTSLSTPTR pPntLst,int nPtsCnt,
																							INTSLSTPTR pRings,int nRcnt,double rRadia=0,bool bExtOut = true/*�Ƿ�������չ�õ����ڲ��Ľ��?�����ڲ������˾���̫��Ҳ�������ڲ�*/)
{
	if(nPtsCnt>3)
	{
		double prex=0;double prey=0;double thpx=0;double thpy=0;int ringr=0;
		
		int iPtor = 0;int i=0;
		
		int lwP=0;//��¼�봹�������ӳ�ʱ��ߵĽ������
		for(int r=0;r<nRcnt;r++)
		{
			TplGSRingPnumRingsList(pRings,r,ringr);
			for(i=1;i<ringr;i++)
			{
				TplGetXYCoordPointsList(pPntLst,iPtor+i-1,prex,prey);
				TplGetXYCoordPointsList(pPntLst,iPtor+i,thpx,thpy);
				if(!(thpx==prex&&thpy==prey))//�����м���غϽ��,���ǰһ�㲻���ں�һ��;
				{
					if(((x-thpx==0)&&(y-thpy==0))||((x-prex==0)&&(y-prey==0)))
						return true;//��ڵ��غ�,����������Ϊ���ڲ�//20160803
					else
					{
						if(((rRadia!=0)&&bExtOut)&&(IsLineWithHLine(x-rRadia/2,x+rRadia/2,y-rRadia/2,thpx,thpy,prex,prey)||
							IsLineWithHLine(x-rRadia/2,x+rRadia/2,y+rRadia/2,thpx,thpy,prex,prey)||
							IsLineWithVLine(y-rRadia/2,y+rRadia/2,x+rRadia/2,thpx,thpy,prex,prey)||
							IsLineWithVLine(y-rRadia/2,y+rRadia/2,x-rRadia/2,thpx,thpy,prex,prey)))//���Ҫ������չ�Ƚ�
							return false;
						
						if ( thpx == prex || // p1p2 �� y=p0.yƽ�� 
							x < min(prex, thpx) || // ������p1p2�ӳ����� 
							x >= max(prex, thpx) ) // ������p1p2�ӳ����� 
							continue; 						
						if ((thpx-prex)*((thpy-prey)*(x-prex)-(thpx-prex)*(y-prey))<0) 
							lwP++; // ֻͳ�Ƶ��߽��� 
					}
				}
			}
			////////
			iPtor += ringr;
		}				
		return (lwP%2)==1?true:false;	//����������true//����ż����false
	}
	else return false;
};

//���߷��жϵ��Ƿ������������ڲ�,����εĵ㴮�������ڵ���4,����ĩ���غ�(���)
template<class CMPPNTTYPE/*�ο�������*/,class PNTSLSTPTR/*�㴮�б��ַ����*/,class INTSLSTPTR/*���ջ�����ָ��*/> bool inline IsPfInPgnXY(CMPPNTTYPE &cmpPt,PNTSLSTPTR pPntLst,int nPtsCnt,
																							INTSLSTPTR pRings,int nRcnt,double rRadia=0,bool bExtOut = true/*�Ƿ�������չ�õ����ڲ��Ľ��?�����ڲ������˾���̫��Ҳ�������ڲ�*/)
{
	double x=0;double y=0;
	TplGetXYCoordPoint(cmpPt,x,y);
	return IsPfInPgnXY(x,y,pPntLst,nPtsCnt,pRings,nRcnt,rRadia,bExtOut);
};

//���Ƿ��ھ���֮��,���ĸ������ֱ�������ζԽ����������x��y����,xy˳��̶�,���Ǹ��Դ�С˳��ɺ���
template<class TYPE1,class TYPE2> bool inline IsPfInRect(TYPE1 px,TYPE1 py,TYPE2 x1,TYPE2 y1,TYPE2 x2,TYPE2 y2)
{
	return ((px-x1)*(px-x2)<=0)&&((py-y1)*(py-y2)<=0);
};
//���Ƿ��ھ���֮��,���ĸ������ֱ�������ζԽ����������x��y����,xy˳��̶�,���Ǹ��Դ�С˳��ɺ���
template<class TYPE1,class RECTTYPE> bool inline IsPfInRect(TYPE1 px,TYPE1 py,RECTTYPE *prc)
{
	double x1=0;double y1=0;double x2=0;double y2=0;
	TplGS4XYInRect(*prc,x1,y1,x2,y2);
	return IsPfInRect(px,py,x1,y1,x2,y2);
};
//���Ƿ��ھ���֮��,���ĸ������ֱ�������ζԽ����������x��y����,xy˳��̶�,���Ǹ��Դ�С˳��ɺ���
template<class CMPPNTTYPE,class TYPE2> bool inline IsPfInRect(CMPPNTTYPE &cmpP,TYPE2 x1,TYPE2 y1,TYPE2 x2,TYPE2 y2)
{
	double x=0;double y=0;
	TplGetXYCoordPoint(cmpP,x,y);
	return IsPfInRect(x,y,x1,y1,x2,y2);
};
//���Ƿ��ھ���֮��,���ĸ������ֱ�������ζԽ����������x��y����,xy˳��̶�,���Ǹ��Դ�С˳��ɺ���
template<class CMPPNTTYPE,class RECTTYPE> bool inline IsPfInRect(CMPPNTTYPE &cmpP,RECTTYPE *prc)
{
	double x=0;double y=0;
	TplGetXYCoordPoint(cmpP,x,y);
	return IsPfInRect(x,y,prc);
};

//�жϵ��Ƿ���Բ�ڲ�(����Բ�Ƿ����ཻ����)��fradias��ͶӰϵ�ڵĳ���,pCenter��Բ��,pf��Ҫ�жϵĵ�
template<class TYPE1,class TYPE2> bool inline IsPfInRound(TYPE1 pcx,TYPE1 pcy,double fradias,TYPE2 pfx,TYPE2 pfy)
{
	return (CalDistance(pcx,pcy,pfx,pfy)<fradias?true:false);
};

//�жϵ��Ƿ���Բ�ڲ�(����Բ�Ƿ����ཻ����)��fradias��ͶӰϵ�ڵĳ���,pCenter��Բ��,pf��Ҫ�жϵĵ�
template<class PNTTYPE1,class PNTTYPE2> bool inline IsPfInRound(PNTTYPE1 *pCenter,double fradias,PNTTYPE2 *pf)
{
	double pcx=0;double pcy=0;double pfx=0;double pfy=0;
	TplGetXYCoordPoint(*pCenter,pcx,pcy);TplGetXYCoordPoint(*pf,pfx,pfy);
	return IsPfInRound(pcx,pcy,fradias,pfx,pfy);
};
/////////////////////////////////////���Ƿ񿿽������ɵ�����
template<class TYPE1,class PNTSLSTPTR/*�㴮�б��ַ����*/,class TYPE2> bool inline IsPfNearPll(TYPE1 sx,TYPE1 sy,PNTSLSTPTR pPolyline,int LinePointsCount,TYPE2 tTolerance)
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
//����Ƚϵ�pC�Ƿ�λ����AOB��ɵ�С��PI�ǵĶ�ά�ռ����򣬷���λ������֮�����һ��
template<class TYPE0,class TYPE1,class TYPE2,class TYPE3> bool inline IsPfInLowPIAngleRegion(TYPE0 pCx,TYPE0 pCy,TYPE1 pAx,TYPE1 pAy,TYPE2 pOx,TYPE2 pOy,TYPE3 pBx,TYPE3 pBy)
{
	if(CalDistancePointLineUnlimited(pCx,pCy,pAx,pAy,pOx,pOy)<0.000001)return true;///��ֱ����
	if(CalDistancePointLineUnlimited(pCx,pCy,pBx,pBy,pOx,pOy)<0.000001)return true;///��ֱ����
	double dA=GetDirAngle(pOx,pOy,pAx,pAy);
	double dB=GetDirAngle(pOx,pOy,pBx,pBy);
	double dC=GetDirAngle(pOx,pOy,pCx,pCy);
	return fabs(dA-dB)<PO_PI?((dA-dC)*(dB-dC)<0?true:false):((dA-dC)*(dB-dC)<0?false:true);
}
/////////////////////////////////////���Ƿ񿿽������ɵ�����
template<class PNTTYPE,class PNTSLSTPTR/*�㴮�б��ַ����*/,class TYPE2> bool inline IsPfNearPll(PNTTYPE &pCmpPt,PNTSLSTPTR pPolyline,int LinePointsCount,TYPE2 tTolerance)
{
	double x=0;double y=0;TplGetXYCoordPoint(pCmpPt,x,y);
	return IsPfNearPll(x,y,pPolyline,LinePointsCount,tTolerance);
};

//�ж϶��������һ��������Ƿ��ཻ
template<class PNTSLSTPTR1/*�㴮�б��ַ����*/,class PNTSLSTPTR2/*�㴮�б��ַ����*/,class INTSLSTPTR1,class INTSLSTPTR2> bool inline IsPgnAndPgnIntersectWith(
 PNTSLSTPTR1 rgnPoints1,int rgnPtsCount1,INTSLSTPTR1 rgnlist1,int rgncount1,
 PNTSLSTPTR2 rgnPoints2,int rgnPtsCount2,INTSLSTPTR2 rgnlist2,int rgncount2)
{
	//�����һ������ε�����һ���߶�����һ������ε�����һ���߶����ཻ,��������ͼ�ξ��ཻ
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
		}//���û�з�������������ཻ,�����ж�(ֻʣ2�����:�����1�ڶ����2�ڲ�,�����2�ڶ����1�ڲ�)
		b1In2 = (b1In2&&IsPfInPgnXY(*TplGetPointRefInPoints(rgnPoints1,i+1),rgnPoints2,rgnPtsCount2,rgnlist2,rgncount2));
	}
	return b2In1||b1In2;
};

//�ж϶�����������Ƿ��ཻ
template<class PNTSLSTPTR1/*�㴮�б��ַ����*/,class INTSLSTPTR1,class PNTSLSTPTR2/*�㴮�б��ַ����*/> bool inline IsPgnAndPllIntersectWith(PNTSLSTPTR1 rgnPoints,int rgnPtsCount,INTSLSTPTR1 rgnlist,int rgncount,
																		 PNTSLSTPTR2 pllPoints,int pllPtsCount)
{
	//��������е�����һ���߶������ε�����һ���߶����ཻ,��������ͼ�ξ��ཻ
	int i=0;int j=0;int r=0;int jindex = 0;
	bool plnpInrgn = IsPfInPgnXY(*TplGetPointRefInPoints(pllPoints,0),rgnPoints,rgnPtsCount,rgnlist,rgncount);//����һ��ʼ���ߵ��ڶ�����ڲ�
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
		//���û�з�������������ཻ,�����ж�(ֻʣ1�����:�����ڶ�����ڲ�)
		plnpInrgn = (plnpInrgn||IsPfInPgnXY(*TplGetPointRefInPoints(pllPoints,i+1),rgnPoints,rgnPtsCount,rgnlist,rgncount));//�ӵڶ��㿪ʼ���Ƿ��ڶ�����ڲ�
	}
	return plnpInrgn;
};

//////////////////////////�������ߴ��Ƿ��ཻ//////////////////////////////////////////
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
	for(int i=1;i<pstCount;i++)////��һ�������۴ӵڶ��㿪ʼ
	{
		TplGetXYCoordPointsList(plPtlist,i,pthpx,pthpy);
		
		if(IsPfInRect(pthpx,pthpy,leftx1,topy1,rightx2,bottomy2))
		{
			return true;
		}
		else
		{	//ֻҪ��һ��������α߽��ཻ//if((*ppre)!=(*pthp))
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

//�����ཻ�Ĺ�ϵ
#define RELATION_FT_CCRS 1//�����ཻ�Ĺ�ϵ
//ǰ�߰������ߵĹ�ϵ,���ұ�����ȫ����
#define RELATION_FT_CONT 2//ǰ�߰������ߵĹ�ϵ,���ұ�����ȫ����
//���߰���ǰ�ߵĹ�ϵ,���ұ�����ȫ����
#define RELATION_FT_CINT 3//���߰���ǰ�ߵĹ�ϵ,���ұ�����ȫ����
//��������Ĺ�ϵ
#define RELATION_FT_CDPT 4//��������Ĺ�ϵ
//�жϾ�����������(����)���ཻ��ϵ
template<class TYPE1,class PNTSLSTPTR/*�㴮�б��ַ����*/,class INTSLSTPTR> bool inline GetRectAndPolygonRelation(TYPE1 leftx1,TYPE1 topy1,TYPE1 rightx2,TYPE1 bottomy2,
																			PNTSLSTPTR pPntLst,int ptsCount,INTSLSTPTR rgnlist,int rgncount,
																			DWORD rMode/**/)
{
	
	switch(rMode)
	{
	case RELATION_FT_CCRS://�����ཻ�Ĺ�ϵ
		{
			return IsRectAndPolyLineIntersectWith(leftx1,topy1,rightx2,bottomy2,pPntLst,ptsCount);
		}
		break;
	case RELATION_FT_CONT://ǰ�߰������ߵĹ�ϵ,���ұ�����ȫ����
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
	case RELATION_FT_CINT://���߰���ǰ�ߵĹ�ϵ,���ұ�����ȫ����
		{
			return IsPfInPgnXY(leftx1,topy1,pPntLst,ptsCount,rgnlist,rgncount)&&
				IsPfInPgnXY(leftx1,bottomy2,pPntLst,ptsCount,rgnlist,rgncount)&&
				IsPfInPgnXY(rightx2,topy1,pPntLst,ptsCount,rgnlist,rgncount)&&
				IsPfInPgnXY(rightx2,bottomy2,pPntLst,ptsCount,rgnlist,rgncount);
		}
		break;
	case RELATION_FT_CDPT://��������Ĺ�ϵ
		{
			return (!GetRectAndPolygonRelation(leftx1,topy1,rightx2,bottomy2,pPntLst,ptsCount,rgnlist,rgncount,RELATION_FT_CCRS))&&
				(!GetRectAndPolygonRelation(leftx1,topy1,rightx2,bottomy2,pPntLst,ptsCount,rgnlist,rgncount,RELATION_FT_CONT))&&
				(!GetRectAndPolygonRelation(leftx1,topy1,rightx2,bottomy2,pPntLst,ptsCount,rgnlist,rgncount,RELATION_FT_CINT));//���ཻ������Ҳ��������
		}
		break;
	default:
		break;
	}
	return false;
};

//�жϾ�����������(����)���ཻ��ϵ
template<class RECTTYPEPTR,class PNTSLSTPTR/*�㴮�б��ַ����*/,class INTSLSTPTR> bool inline GetRectAndPolygonRelation(RECTTYPEPTR &rc,
																			PNTSLSTPTR pPntLst,int ptsCount,INTSLSTPTR rgnlist,int rgncount,
																			DWORD rMode/**/)
{
	double x1=0;double y1=0;double x2=0;double y2=0;
	TplGS4XYInRect(rc,x1,y1,x2,y2);
	return GetRectAndPolygonRelation(x1,y1,x2,y2,pPntLst,ptsCount,rgnlist,rgncount,rMode);
};

template<class TYPE,class PNTSLSTPTR,class INTSLSTPTR> bool inline IsRectAndPolygonIntersectWith(TYPE leftx1,TYPE topy1,TYPE rightx2,TYPE bottomy2,
																				PNTSLSTPTR rgnPtlist,int ptsCount,INTSLSTPTR rgnlist,int rgncount)
{	//���������߲��ཻ�����������������
	if(IsRectAndPolyLineIntersectWith(leftx1,topy1,rightx2,bottomy2,rgnPtlist,ptsCount))
		return true;
	else
	{
		if(IsPfInPgnXY(leftx1,topy1,rgnPtlist,ptsCount,rgnlist,rgncount)||
			IsPfInPgnXY(leftx1,bottomy2,rgnPtlist,ptsCount,rgnlist,rgncount)||
			IsPfInPgnXY(rightx2,topy1,rgnPtlist,ptsCount,rgnlist,rgncount)||
			IsPfInPgnXY(rightx2,bottomy2,rgnPtlist,ptsCount,rgnlist,rgncount))//���α�����
			return true;
		else
		{
			double x=0;double y=0;TplGetXYCoordPointsList(rgnPtlist,0,x,y);
			if(IsPfInRect(x,y,leftx1,topy1,rightx2,bottomy2))//����α�����
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

//�ж�Բ���������Ƿ����ཻ���֣�fradias��ͶӰϵ�ڵĳ���,p��Բ��
template<class PNTTYPE,class PNTSLSTPTR> bool inline IsRoundAndPolyLineIntersectWith(PNTTYPE &pCenter,double fradias, PNTSLSTPTR plPtlist,int ptsCount)
{
	if(ptsCount==1)
		return IsPfInRound(&pCenter,fradias,TplGetPointRefInPoints(plPtlist,0));
	else
	{
		for(int i=0;i<ptsCount-1;i++)//������һ�߶���Բ��
		{
			if(CalDistancePointLine(pCenter,*TplGetPointRefInPoints(plPtlist,i),*TplGetPointRefInPoints(plPtlist,i+1))<fradias)
			{
				return true;
			}
		}
		return false;
	}
};

//�ж�Բ�������������Ƿ����ཻ����,fradias��ͶӰϵ�ڵĳ���,p��Բ��
template<class PNTTYPE,class PNTSLSTPTR,class INTSLSTPTR> bool inline IsRoundAndPolygonIntersectWith(PNTTYPE &pCenter,double fradias,
																			 PNTSLSTPTR rgnPtlist,int ptsCount,INTSLSTPTR rgnlist,int rgncount)
{
	if(ptsCount<3)
		return IsRoundAndPolyLineIntersectWith(pCenter,fradias,rgnPtlist,ptsCount);
	else
	{
		for(int i=0;i<ptsCount-1;i++)//������һ�߶���Բ��
		{
			if(CalDistancePointLine(pCenter,*TplGetPointRefInPoints(rgnPtlist,i),*TplGetPointRefInPoints(rgnPtlist,i+1))<fradias)
			{
				return true;
			}
		}
		//���߿���Բ�ڶ���ε��ڲ�
		return IsPfInPgnXY(pCenter,rgnPtlist,ptsCount,rgnlist,rgncount);
	}
};
//�ж�Բ����������ɵľ����Ƿ��ཻ
template<class TYPE1,class TYPE2> bool inline IsRoundAndRectIntersectWith(TYPE1 cx,TYPE1 cy,TYPE1 fradias,TYPE2 rx1,TYPE2 ry1,TYPE2 rx2,TYPE2 ry2)
{
	if( CalDistancePointLine(cx,cy,rx1,ry1,rx1,ry2)<=fradias||
		CalDistancePointLine(cx,cy,rx1,ry1,rx2,ry1)<=fradias||
		CalDistancePointLine(cx,cy,rx2,ry1,rx2,ry2)<=fradias||
		CalDistancePointLine(cx,cy,rx1,ry2,rx2,ry2)<=fradias)//������һ�߶���Բ��
		return true;
	//���߿���Բ�ھ��ε��ڲ�
	return IsPfInRect(cx,cy,rx1,ry1,rx2,ry2);	
};
//�ж�Բ����������ɵľ����Ƿ��ཻ
template<class TYPE1,class RECTPTRTPE> bool inline IsRoundAndRectIntersectWith(TYPE1 cx,TYPE1 cy,TYPE1 fradias,RECTPTRTPE pRect)
{
	double x1=0;double y1=0;double x2=0;double y2=0;
	TplGS4XYInRect(pRect,x1,y1,x2,y2);
	return IsRoundAndRectIntersectWith(cx,cy,x1,y1,x2,y2);
};
//�ж�Բ����������ɵľ����Ƿ��ཻ
template<class PNTTYPE,class TYPE1,class RECTPTRTPE> bool inline IsRoundAndRectIntersectWith(PNTTYPE &pCenter,TYPE1 fradias,RECTPTRTPE pRect)
{
	double x=0;double y=0;
	TplGetXYCoordPoint(pCenter,x,y);
	return IsRoundAndRectIntersectWith(x,y,pRect);
};

//����ѡȡ����Ҫ��
template <class PNTTYPE,class PNTSLSTPTR,class INTSLSTPTR> bool inline PNTselApFeatures(PNTTYPE &pCtroPoint/*�������Ƶ�*/, PNTSLSTPTR ptsTarget, int pstCount, INTSLSTPTR rgnlist,int rgncount,float fTolerance)
{
	return IsPfInPgnXY(pCtroPoint,ptsTarget,pstCount,rgnlist,rgncount);
};
//����ѡȡ����Ҫ��	
template <class PNTTYPE1,class PNTTYPE2> bool inline PNTselPpfeatures(PNTTYPE1 &pCtroPoint, PNTTYPE2 &pTarget/*Ŀ���ĵ�һ����λ��*/, float fTolerance)
{
	return CalDistance(pCtroPoint,pTarget)<fTolerance?true:false;
};
//����ѡȡ����Ҫ��
template <class PNTTYPE,class PNTSLSTPTR> bool inline PNTselLpFeatures(PNTTYPE &pCtroPoint, PNTSLSTPTR ptsTarget/*Ŀ��Ҫ�ص���������*/, int pstCount, float fTolerance)
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

//��ǰ�����ȡƽ���ı��͵ĵ��ĵ�
PointF inline GetPointOf4InPxsbx(float x1,float y1,float x2,float y2,float x3,float y3)
{
	return PointF(x3-x2+x1,y3-y2+y1);
};

//��ǰ�����ȡƽ���ı��͵ĵ��ĵ�
template<class PNTTYPE> PointF inline GetPointOf4InPxsbx(PNTTYPE &pt1,PNTTYPE &pt2,PNTTYPE &pt3)
{
	double x1=0;double y1=0;double x2=0;double y2=0;double x3=0;double y3=0;
	TplGetXYCoordPoint(pt1,x1,y1);TplGetXYCoordPoint(pt2,x2,y2);TplGetXYCoordPoint(pt3,x3,y3);
	return GetPointOf4InPxsbx(x1,y1,x2,y2,x3,y3);
};

//##Begin Model Documentation
//�����Ⱥ�˳�����������ֱ�ߵķ����(0~2*PI)��ֱ������ϵ����y�£�x�ҵķ���,����
//ֵΪ˫�����ͻ���
//##End Model Documentation
//##ModelId=46EDE5B80186
double inline GetDirAngle(double x1, double y1, double x2, double y2)
{
	double angle = 0;			
	double dy = y1-y2;//�������ᷭת
	double dx = x2-x1;
	dx==0?(dy==0?(angle=0)
		:(dy>0?(angle=PO_PI/2):(angle=PO_PI*1.5)))
		:(dx>0?(dy>0?(angle=atan(dy/dx)):(PO_PI*2+atan(dy/dx)))
		:(PO_PI+atan(dy/dx)));
	return angle;
};

//##Begin Model Documentation
//�����Ⱥ�˳�������������ֱ����ɵ����е�ΪԲ�ĵķ����(0~2*PI)��ǰ�����������
//�нǣ�ֱ������ϵ����y�£�x�ҵķ���,����ֵΪ˫�����ͻ���
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
