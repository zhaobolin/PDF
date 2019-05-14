#ifndef SPO_TPLPOLYPOLYGON_H_HEADER_INCLUDED_B0F945B5
#define SPO_TPLPOLYPOLYGON_H_HEADER_INCLUDED_B0F945B5

template <class PNTTYPE> class SPo_TplPolypolygon
{
public:
	//��ջ��ĸ���
	vector<int> m_vCloseFeature;
	//��������㴮
	vector<PNTTYPE> m_vOrdinates;
	//����ָ��,����ֱ�ӷ��ص������
	PNTTYPE *m_pPoints;
	//���滷��ָ��
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
	//��д������ʼ������
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
    // \brief ת����ֵ����
    // 
    // ������windows�����ֵ������ǰ��ṹ
    // 
    // \return ��ǰ��ṹ������
    // 
    // \param right��ת����ֵ�����Ҳ�����
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
	template <class PTRRECTTYPE> void UnionRect(PTRRECTTYPE prc)//���Ӿ���
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
	template <class TYPE1> void UnionRect(TYPE1 x1,TYPE1 y1,TYPE1 x2,TYPE1 y2)//���Ӿ���
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
	template <class PNTSLSTPTR/*�㴮�б��ַ����*/> void UnionPoly(PNTSLSTPTR pPntsLst,int ncnt)//���ӷ�ն����(TYPE pX,TYPE pY,PNTSLSTPTR pPntsLst,int npcnt)
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
		if(!(x00==x11&&y00==y11))//////////���û�з�գ�ǿ�Ʒ��
		{
			m_vOrdinates.push_back(PNTTYPE(x00,y00));rs++;
		}
		m_vCloseFeature.push_back(rs);
	};	
	template <class PNTSLSTPTR,class RINGSLSTPTR> void UnionPolys(PNTSLSTPTR pts,RINGSLSTPTR rings,int rcnt)//���ӷ�ն����
	{
		int pIndex = 0;int iringpntcnt=0;double x=0;double y=0;
		double x00=0;double y00=0;double x11=0;double y11=0;int rpcntinsert=0;
		for(int r=0;r<rcnt;r++)
		{
			TplGSRingPnumRingsList(rings,r,iringpntcnt);rpcntinsert=iringpntcnt;//��õ�ǰ���ĵ����
			for(int ip=0;ip<iringpntcnt;ip++)
			{
				TplGetXYCoordPointsList(pts,pIndex+ip,x,y);
				PNTTYPE pt;
				TplSetXYCoordPoint(pt,x,y);
				m_vOrdinates.push_back(pt);
			}
			TplGetXYCoordPointsList(pts,pIndex,x00,y00);
			TplGetXYCoordPointsList(pts,pIndex+iringpntcnt-1,x11,y11);
			if(!(x00==x11&&y00==y11))//////////���û�з�գ�ǿ�Ʒ��
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
	void XorRect(CRect &rc)//��ȥ����
	{
	};
	void XorRect(RectF &rc)//��ȥ����
	{
	};
	void XorRect(Rect &rc)//��ȥ����
	{
	};
	template <class TYPE1> void XorRect(SPo_TplRect<TYPE1> &rc)//��ȥ����
	{
	};
	template <class TYPE1> void XorRect(TYPE1 x1,TYPE1 y1,TYPE1 x2,TYPE1 y2)//��ȥ����
	{
	};	
	void ReverseRegions(CRect &rc)//���㱾���������������෴�Ķ���Σ����º��Ϊ���¶����
	{
	};
	void ReverseRegions(RectF &rc)//���㱾���������������෴�Ķ���Σ����º��Ϊ���¶����
	{
	};
	void ReverseRegions(Rect &rc)//���㱾���������������෴�Ķ���Σ����º��Ϊ���¶����
	{
	};
	template <class TYPE1> void ReverseRegions(SPo_TplRect<TYPE1> &rc)//���㱾���������������෴�Ķ���Σ����º��Ϊ���¶����
	{
	};
	template <class TYPE1> void ReverseRegions(TYPE1 x1,TYPE1 y1,TYPE1 x2,TYPE1 y2)//���㱾���������������෴�Ķ���Σ����º��Ϊ���¶����
	{
	};
	template <class TYPE1> void Offset(TYPE1 ofx,TYPE1 ofy)//ƫ�ƶ���
	{
		for(vector<PNTTYPE>::iterator itr = m_vOrdinates.begin();
		itr!=m_vOrdinates.end();itr++)
		{
			*itr = *itr+PNTTYPE(ofx,ofy);
		}
	};
	//��ox��oyΪԲ�ģ���תһ���ĽǶȺ��ڲ�ת����ѡװ�����յѿ�������ϵΪ׼��
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
	unsigned int HitTest(double sx,double sy, bool bSelected/*�Ƿ��Ѿ���ѡȡ*/,double dTx,double dTy/*�豸�����µ���ֵ*/)
	{
		int pstCount = GetPointsCount();
		if(pstCount==0)	return 0;
		int ipt = 0;
		if(bSelected)//Ҫץȡ�ṹ��
		{
			for(ipt=0;ipt<pstCount;ipt++)
			{
				PNTTYPE *vp=GetPointRef(ipt);
				double xval=0;double yval=0;
				TplGetXYCoordPoint(*vp,xval,yval);
				if((xval+dTx>=sx&&sx>=xval-dTx)&&(yval+dTy>=sy&&sy>=yval-dTy))
					return ipt+1;//ץס�ˣ����ص����+1
			}
			return 0;//û��ץס
		}
		else//Ҫץȡ������
		{
			if(pstCount>3)
			{
				PNTTYPE *ppre;		PNTTYPE *pthp;	int rgncount = GetRingsCount();
				
				int iPtor = 0;int i=0;			int lwP=0;//��¼�봹�������ӳ�ʱ��ߵĽ������
				int *rings = GetRingsPtr();double prexv=0;double preyv=0;double thpxv=0;double thpyv=0;
				for(int r=0;r<rgncount;r++)
				{	////////
					for(i=1;i<rings[r];i++)
					{
						ppre = GetPointRef(iPtor+i-1);	pthp = GetPointRef(iPtor+i);
						TplGetXYCoordPoint(*ppre,prexv,preyv);
						TplGetXYCoordPoint(*pthp,thpxv,thpyv);
						if(!(thpxv==prexv&&thpyv==preyv))//�����м���غϽ��,���ǰһ�㲻���ں�һ��;
						{
							if(((sx-thpxv==0)&&(sy-thpyv==0))||((sx-prexv==0)&&(sy-preyv==0)))
								return true;//��ڵ��غ�,����������Ϊ���ڲ�//20160803
							else
							{
								if ( thpxv == prexv || // p1p2 �� y=p0.Yƽ�� 
									sx < min(prexv, thpxv) || // ������p1p2�ӳ����� 
									sx >= max(prexv, thpxv) ) // ������p1p2�ӳ����� 
									continue; 						
								if ((thpxv-prexv)*((thpyv-preyv)*(sx-prexv)-(thpxv-prexv)*(sy-preyv))<0) 
									lwP++; // ֻͳ�Ƶ��߽��� 
							}
						}
					}
					////////
					iPtor += rings[r];
				}				
				return (lwP%2)==1?true:false;	//����������true//����ż����false
			}
			else return false;
		}	
	};
	//�ж�������Ƿ����ཻ
	bool IsIntersect(double x1,double y1,double x2,double y2/*��ɾ��ε�����������*/)
	{
		int *rings = GetRingsPtr();
		return IsRectAndPolygonIntersectWith(x1,y1,x2,y2,&m_vOrdinates,m_vOrdinates.size(),rings,GetRingsCount());
	};
	//��ȡ��Ӿ���
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
////////////��SPo_PolypolygonPointF����Region
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
