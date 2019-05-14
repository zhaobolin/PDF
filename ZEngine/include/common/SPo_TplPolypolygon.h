#ifndef SPO_TPLPOLYPOLYGON_H_HEADER_INCLUDED_B0F945B5
#define SPO_TPLPOLYPOLYGON_H_HEADER_INCLUDED_B0F945B5

template <class PNTTYPE> class SPo_TplPolypolygon
{
public:
	//封闭环的个数
	vector<int> m_vCloseFeature;
	//所有坐标点串
	vector<PNTTYPE> m_vOrdinates;
	//缓存指针,用于直接返回点的数组
	PNTTYPE *m_pPoints;
	//缓存环数指针
	int *m_pRings;
	//
	DWORD *m_pRingsL;
public:
	SPo_TplPolypolygon()
	{
		m_pPoints = NULL;
		m_pRings = NULL;
		m_pRingsL = NULL;	
	};
	~SPo_TplPolypolygon()
	{
		if(m_pPoints)delete []m_pPoints;m_pPoints=NULL;
		if(m_pRings)delete[]m_pRings;m_pRings=NULL;
		if(m_pRingsL)delete[]m_pRingsL;m_pRingsL=NULL;
	};	
	//重写拷贝初始化函数
	template<class PNTTYPE2> SPo_TplPolypolygon(const SPo_TplPolypolygon<PNTTYPE2> &other)
	{
		SPo_TplPolypolygon<PNTTYPE2> *pother = (SPo_TplPolypolygon<PNTTYPE2> *)(&other);

		for(vector<int>::iterator itr=pother->m_vCloseFeature.begin();itr!=pother->m_vCloseFeature.end();itr++)
			m_vCloseFeature.push_back(*itr);
		double x=0;double y=0;
		for(vector<PNTTYPE2>::iterator ptr=pother->m_vOrdinates.begin();ptr!=pother->m_vOrdinates.end();ptr++)
		{
			PNTTYPE pnt1;
			TplGetXYCoordPoint(*ptr,x,y);
			TplSetXYCoordPoint(pnt1,x,y);
			m_vOrdinates.push_back(pnt1);
		}

		m_pPoints = NULL;
		m_pRings = NULL;
		m_pRingsL = NULL;
	};
    // \brief 转换赋值运算
    // 
    // 将给定windows点的数值赋给当前点结构
    // 
    // \return 当前点结构的引用
    // 
    // \param right：转换赋值运算右操作数
    //##ModelId=44278F7601D4
    template<class PNTTYPE2> SPo_TplPolypolygon& operator=(const SPo_TplPolypolygon<PNTTYPE2> &right)
	{
		SPo_TplPolypolygon<PNTTYPE2> *pright = (SPo_TplPolypolygon<PNTTYPE2> *)&right;
		for(vector<int>::iterator itr=pright->m_vCloseFeature.begin();itr!=pright->m_vCloseFeature.end();itr++)
			m_vCloseFeature.push_back(*itr);
		double x=0;double y=0;
		for(vector<PNTTYPE2>::iterator ptr=pright->m_vOrdinates.begin();ptr!=pright->m_vOrdinates.end();ptr++)
		{
			PNTTYPE pnt1;
			TplGetXYCoordPoint(*ptr,x,y);
			TplSetXYCoordPoint(pnt1,x,y);
			m_vOrdinates.push_back(pnt1);
		}
		m_pPoints = NULL;
		m_pRings = NULL;
		m_pRingsL = NULL;
		return *this ;
	};

	int GetPointsCount()
	{
		return m_vOrdinates.size();
	};
	int GetRingsCount()
	{
		return m_vCloseFeature.size();
	};
	int *GetRingsPtr(bool bReAlloc=true)
	{
		if(bReAlloc)
		{
			if(m_pRings)delete []m_pRings;
			size_t sz=GetRingsCount();
			m_pRings=new int[sz];size_t ui=0;
			for(vector<int>::iterator itr=m_vCloseFeature.begin();itr!=m_vCloseFeature.end();itr++,ui++)
				m_pRings[ui] = *itr;
		}
		return m_pRings;
	};
	DWORD *GetRingsPtrL(bool bReAlloc=true)
	{
		if(bReAlloc)
		{
			if(m_pRingsL)delete []m_pRingsL;
			size_t sz=GetRingsCount();
			m_pRingsL=new DWORD[sz];size_t ui=0;
			for(vector<int>::iterator itr=m_vCloseFeature.begin();itr!=m_vCloseFeature.end();itr++,ui++)
				m_pRingsL[ui] = *itr;
		}
		return m_pRingsL;
	};
	PNTTYPE *GetPointsPtr(bool bReAlloc=true)
	{
		if(bReAlloc)
		{
			if(m_pPoints)delete []m_pPoints;
			size_t sz=GetPointsCount();
			m_pPoints=new PNTTYPE[sz];size_t ui=0;
			for(vector<PNTTYPE>::iterator itr=m_vOrdinates.begin();itr!=m_vOrdinates.end();itr++,ui++)
			{
				m_pPoints[ui] = *itr;
			}
		}
		return m_pPoints;
	};
	PNTTYPE *GetPointRef(int iIndex)
	{
		if(iIndex<0||iIndex>GetPointsCount()-1)return NULL;
		else
			return m_vOrdinates.begin()+iIndex;
	}
	void GetXYCoordFromPoint(int iIndex,double &rx,double &ry)
	{
		PNTTYPE *pp=GetPointRef(iIndex);
		TplGetXYCoordPoint(*pp,rx,ry);
	}
	void SetXYCoordToPoint(int iIndex,double &xval,double &yval)
	{
		PNTTYPE *pp=GetPointRef(iIndex);
		TplSetXYCoordPoint(*pp,xval,yval);
	};
	bool IsEmpty()
	{
		return m_vOrdinates.size()==0;
	};
	void MakeEmpty()
	{
		m_vCloseFeature.clear();
		m_vOrdinates.clear();
		if(m_pPoints)delete []m_pPoints;m_pPoints=NULL;
		if(m_pRings)delete []m_pRings;m_pRings=NULL;
		if(m_pRingsL)delete []m_pRingsL;m_pRingsL=NULL;
	};
	template <class PTRRECTTYPE> void UnionRect(PTRRECTTYPE prc)//增加矩形
	{
		double xmin=0;double xmax=0;
		double ymin=0;double ymax=0;

		PtlGSXYMaxMinOfRect(prc,xmin,ymin,xmax,ymax);

		m_vOrdinates.push_back(PNTTYPE(xmin,ymin));
		m_vOrdinates.push_back(PNTTYPE(xmax,ymin));
		m_vOrdinates.push_back(PNTTYPE(xmax,ymax));
		m_vOrdinates.push_back(PNTTYPE(xmin,ymax));
		m_vOrdinates.push_back(PNTTYPE(xmin,ymin));
		m_vCloseFeature.push_back(5);
	};
	template <class TYPE1> void UnionRect(TYPE1 x1,TYPE1 y1,TYPE1 x2,TYPE1 y2)//增加矩形
	{
		double xmin=min(x1,x2);double xmax=max(x1,x2);
		double ymin=min(y1,y2);double ymax=max(y1,y2);
		m_vOrdinates.push_back(PNTTYPE(xmin,ymin));
		m_vOrdinates.push_back(PNTTYPE(xmax,ymin));
		m_vOrdinates.push_back(PNTTYPE(xmax,ymax));
		m_vOrdinates.push_back(PNTTYPE(xmin,ymax));
		m_vOrdinates.push_back(PNTTYPE(xmin,ymin));
		m_vCloseFeature.push_back(5);
	};
	template <class PNTSLSTPTR/*点串列表地址类型*/> void UnionPoly(PNTSLSTPTR pPntsLst,int ncnt)//增加封闭多边形(TYPE pX,TYPE pY,PNTSLSTPTR pPntsLst,int npcnt)
	{
		int rs = ncnt;double x=0;double y=0;
		for(int i=0;i<ncnt;i++)
		{
			TplGetXYCoordPointsList(pPntsLst,i,x,y);
			PNTTYPE pt;
			TplSetXYCoordPoint(pt,x,y);
			m_vOrdinates.push_back(pt);
		}
		double x00=0;double y00=0;double x11=0;double y11=0;
		TplGetXYCoordPointsList(pPntsLst,0,x00,y00);
		TplGetXYCoordPointsList(pPntsLst,ncnt-1,x11,y11);
		if(!(x00==x11&&y00==y11))//////////如果没有封闭，强制封闭
		{
			m_vOrdinates.push_back(PNTTYPE(x00,y00));rs++;
		}
		m_vCloseFeature.push_back(rs);
	};	
	template <class PNTSLSTPTR,class RINGSLSTPTR> void UnionPolys(PNTSLSTPTR pts,RINGSLSTPTR rings,int rcnt)//增加封闭多边形
	{
		int pIndex = 0;int iringpntcnt=0;double x=0;double y=0;
		double x00=0;double y00=0;double x11=0;double y11=0;int rpcntinsert=0;
		for(int r=0;r<rcnt;r++)
		{
			TplGSRingPnumRingsList(rings,r,iringpntcnt);rpcntinsert=iringpntcnt;//获得当前环的点个数
			for(int ip=0;ip<iringpntcnt;ip++)
			{
				TplGetXYCoordPointsList(pts,pIndex+ip,x,y);
				PNTTYPE pt;
				TplSetXYCoordPoint(pt,x,y);
				m_vOrdinates.push_back(pt);
			}
			TplGetXYCoordPointsList(pts,pIndex,x00,y00);
			TplGetXYCoordPointsList(pts,pIndex+iringpntcnt-1,x11,y11);
			if(!(x00==x11&&y00==y11))//////////如果没有封闭，强制封闭
			{
				m_vOrdinates.push_back(PNTTYPE(x00,y00));rpcntinsert++;
			}
			m_vCloseFeature.push_back(rpcntinsert);

			pIndex+=iringpntcnt;
		}
	};
	template<class PNTTYPE2> void Union(SPo_TplPolypolygon<PNTTYPE2> &other)
	{
		if(!other.IsEmpty())
		{
			PNTTYPE2 *pts = other.GetPointsPtr();int idex=0;
			int nRings=other.GetRingsCount();int *pRings=other.GetRingsPtr();
			double x=0;double y=0;
			for(int r=0;r<nRings;r++)
			{
				for(int j=0;j<pRings[r];j++)
				{
					PNTTYPE pnt1;
					TplGetXYCoordPoint(pts[idex+j],x,y);
					TplSetXYCoordPoint(pnt1,x,y);

					m_vOrdinates.push_back(pnt1);
				}
				m_vCloseFeature.push_back(pRings[r]);
				idex += pRings[r];
			}
		}
	}
	void XorRect(CRect &rc)//除去矩形
	{
	};
	void XorRect(RectF &rc)//除去矩形
	{
	};
	void XorRect(Rect &rc)//除去矩形
	{
	};
	template <class TYPE1> void XorRect(SPo_TplRect<TYPE1> &rc)//除去矩形
	{
	};
	template <class TYPE1> void XorRect(TYPE1 x1,TYPE1 y1,TYPE1 x2,TYPE1 y2)//除去矩形
	{
	};	
	void ReverseRegions(CRect &rc)//计算本多边形与输入矩形相反的多边形，更新后的为该新多边形
	{
	};
	void ReverseRegions(RectF &rc)//计算本多边形与输入矩形相反的多边形，更新后的为该新多边形
	{
	};
	void ReverseRegions(Rect &rc)//计算本多边形与输入矩形相反的多边形，更新后的为该新多边形
	{
	};
	template <class TYPE1> void ReverseRegions(SPo_TplRect<TYPE1> &rc)//计算本多边形与输入矩形相反的多边形，更新后的为该新多边形
	{
	};
	template <class TYPE1> void ReverseRegions(TYPE1 x1,TYPE1 y1,TYPE1 x2,TYPE1 y2)//计算本多边形与输入矩形相反的多边形，更新后的为该新多边形
	{
	};
	template <class TYPE1> void Offset(TYPE1 ofx,TYPE1 ofy)//偏移对象
	{
		for(vector<PNTTYPE>::iterator itr = m_vOrdinates.begin();
		itr!=m_vOrdinates.end();itr++)
		{
			*itr = *itr+PNTTYPE(ofx,ofy);
		}
	};
	//以ox，oy为圆心，旋转一定的角度后内部转换（选装方向按照笛卡尔坐标系为准）
	template <class TYPE1> void RotateTrans(TYPE1 &ox,TYPE1 &oy,double dAngHudu)
	{
		int n=GetPointsCount();double dx=0;double dy=0;
		for(int i=0;i<n;i++)
		{
			PNTTYPE *pRef = GetPointRef(i);
			TplGetXYCoordPoint(*pRef,dx,dy);
			dx-=ox;dy-=oy;
			double nx=ox+dx*cos(dAngHudu)-dy*sin(dAngHudu);double ny=oy+dx*sin(dAngHudu)+dy*cos(dAngHudu);
			TplSetXYCoordPoint(*pRef,nx,ny);
		}
	};
	unsigned int HitTest(double sx,double sy, bool bSelected/*是否已经被选取*/,double dTx,double dTy/*设备坐标下的阈值*/)
	{
		int pstCount = GetPointsCount();
		if(pstCount==0)	return 0;
		int ipt = 0;
		if(bSelected)//要抓取结构点
		{
			for(ipt=0;ipt<pstCount;ipt++)
			{
				PNTTYPE *vp=GetPointRef(ipt);
				double xval=0;double yval=0;
				TplGetXYCoordPoint(*vp,xval,yval);
				if((xval+dTx>=sx&&sx>=xval-dTx)&&(yval+dTy>=sy&&sy>=yval-dTy))
					return ipt+1;//抓住了，返回点序号+1
			}
			return 0;//没有抓住
		}
		else//要抓取本对象
		{
			if(pstCount>3)
			{
				PNTTYPE *ppre;		PNTTYPE *pthp;	int rgncount = GetRingsCount();
				
				int iPtor = 0;int i=0;			int lwP=0;//记录与垂线向下延长时与边的交点个数
				int *rings = GetRingsPtr();double prexv=0;double preyv=0;double thpxv=0;double thpyv=0;
				for(int r=0;r<rgncount;r++)
				{	////////
					for(i=1;i<rings[r];i++)
					{
						ppre = GetPointRef(iPtor+i-1);	pthp = GetPointRef(iPtor+i);
						TplGetXYCoordPoint(*ppre,prexv,preyv);
						TplGetXYCoordPoint(*pthp,thpxv,thpyv);
						if(!(thpxv==prexv&&thpyv==preyv))//跳过中间的重合结点,如果前一点不等于后一点;
						{
							if(((sx-thpxv==0)&&(sy-thpyv==0))||((sx-prexv==0)&&(sy-preyv==0)))
								return true;//与节点重合,这里我们认为在内部//20160803
							else
							{
								if ( thpxv == prexv || // p1p2 与 y=p0.Y平行 
									sx < min(prexv, thpxv) || // 交点在p1p2延长线上 
									sx >= max(prexv, thpxv) ) // 交点在p1p2延长线上 
									continue; 						
								if ((thpxv-prexv)*((thpyv-preyv)*(sx-prexv)-(thpxv-prexv)*(sy-preyv))<0) 
									lwP++; // 只统计单边交点 
							}
						}
					}
					////////
					iPtor += rings[r];
				}				
				return (lwP%2)==1?true:false;	//交点奇数个true//交点偶数个false
			}
			else return false;
		}	
	};
	//判断与矩形是否有相交
	bool IsIntersect(double x1,double y1,double x2,double y2/*组成矩形的两个点坐标*/)
	{
		int *rings = GetRingsPtr();
		return IsRectAndPolygonIntersectWith(x1,y1,x2,y2,&m_vOrdinates,m_vOrdinates.size(),rings,GetRingsCount());
	};
	//获取外接矩形
	SPo_DRect GetBound()
	{
		SPo_DRect drc;double dx=0;double dy=0;
		int n=GetPointsCount();
		for(int i=0;i<n;i++)
		{
			PNTTYPE *p=GetPointRef(i);
			TplGetXYCoordPoint(*p,dx,dy);
			if(i==0)
			{
				drc.left=drc.right=dx;drc.top=drc.bottom=dy;
			}
			else
			{
				drc.left=min(drc.left,dx);
				drc.right=max(drc.right,dx);
				drc.top=min(drc.top,dy);
				drc.bottom=max(drc.bottom,dy);
			}
		}
		return drc;
	}
};
typedef SPo_TplPolypolygon<PointF> SPo_PolypolygonPointF;
typedef SPo_TplPolypolygon<Point> SPo_PolypolygonPoint;
typedef SPo_TplPolypolygon<CPoint> SPo_PolypolygonCPoint;
typedef SPo_TplPolypolygon<SPo_DPoint2D> SPo_PolypolygonDPoint2D;
typedef SPo_TplPolypolygon<SPo_FPoint2D> SPo_PolypolygonFPoint2D;
typedef SPo_TplPolypolygon<SPo_IPoint2D> SPo_PolypolygonIPoint2D;
typedef SPo_TplPolypolygon<SPo_DPoint> SPo_PolypolygonDPoint;
typedef SPo_TplPolypolygon<SPo_FPoint> SPo_PolypolygonFPoint;
typedef SPo_TplPolypolygon<SPo_IPoint> SPo_PolypolygonIPoint;


///////////////////////////////////////////////////////////
////////////用SPo_PolypolygonPointF构建Region
// inline bool RegionFromSpoPolypolygon(Region *pRgn,SPo_PolypolygonPointF *pPgn)
// {
// 	if(pPgn->IsEmpty())return true;
// 	pRgn->MakeEmpty();
// 	GraphicsPath pthClip;
// 	int nRings=pPgn->GetRingsCount();PointF *pPoints = pPgn->GetPointsPtr();
// 	int *pRings = pPgn->GetRingsPtr();int pdx=0;
// 	for(int r=0;r<nRings;r++)
// 	{
// 		pthClip.AddPolygon(pPoints+pdx,pRings[r]);
// 		pthClip.CloseFigure();
// 		pdx += pRings[r];
// 	}
// 	pRgn->Union(&pthClip);
// 	return true;
// }

inline bool GpathFromSpoPolypolygon(GraphicsPath *pPth,SPo_PolypolygonPointF *pPgn)
{
	int nRings=pPgn->GetRingsCount();PointF *pPoints = pPgn->GetPointsPtr();
	int *pRings = pPgn->GetRingsPtr();int pdx=0;
	for(int r=0;r<nRings;r++)
	{
		pPth->AddPolygon(pPoints+pdx,pRings[r]);
		pPth->CloseFigure();
		pdx += pRings[r];
	}
	return true;
}

#endif /* SPO_TPLPOLYPOLYGON_H_HEADER_INCLUDED_B0F945B5 */
