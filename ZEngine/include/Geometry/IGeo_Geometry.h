#ifndef IGEO_GEOMETRY_H_HEADER_INCLUDED_B9066FDF
#define IGEO_GEOMETRY_H_HEADER_INCLUDED_B9066FDF

class IPo_SpatialReference;
class IDS_DataBuffer;
#include "geo_commondef.h"
#include "..\common\IPo_Unknown.h"

//Oracle Spatial 中定义的几何类型
//---00	未知类型	用户自定义
//---01	点类型	几何对象包含1个点
//---02	线类型	几何对象由直线段或弧线段组成
//---03	多边形	几何对象包含一个的多边形
//---04	多类型集合	可包含所有类型的集合体
//---05	多个点	多个点的超集
//---06	多个线	多条线的超集
//---07	多个多边形	多个多边形的超集
//---08 暂时表示注记类型
//---如2001表示二维坐标中的一个点;3002表示三维坐标中的一条
//直线
//由Po_GeometryObject中的几何对象类型转到Po_Gde中（OracleSpatial）的几何对象类型
//##ModelId=46EDE88800AB
extern "C" __declspec(dllexport) int POGEO_TYPE3_OSPTGEO(int pogeotype);

//由Po_Gde中（OracleSpatial）的几何对象类型转到Po_GeometryObject中的几何对象类型
//##ModelId=46EDE88800BB
extern "C" __declspec(dllexport) int OSPTGEO_TYPE3_POGEO(int osptgeotype);

struct LOG_SDOGEOMETRY;
class IGeo_Geometry;
struct LOG_SDOGEOMETRY;


//##ModelId=4B2B8A7103D8
struct LOG_SDOGEOMETRY
{
	//几何对象类型码，基于Oracle Spatial定义的类型码
	//##ModelId=4B2B8A7103DA
	int m_nSrid;
	//OracleSpatial 的几何对象类型代码
	//##ModelId=4B2B8A720000
	int      m_nGtype;              //几何类型	
	//点要素纪录其坐标；线要素保留；面要素纪录面域点********
	//##ModelId=4B2B8A720002
	SPo_DPoint  m_gPoint;
	//几何对象坐标点串链表,存储几何数据。//点要素保留；线要素和面要素纪录其坐标串
	//##ModelId=4B2B8A720021
	vector<SPo_DPoint> m_dpsOrdinates; 
public:
	//存储图元数据
	//##ModelId=4B2B8A7102D1
	vector<SPo_IPoint> m_ipsElmInfos;
	
	//封闭单环组成点数的链表，例如五个环，它们的点数分别3，6，
	//9，20，58，也可以根据此项求得单环个数。
	//##ModelId=4B2B8A7102F1
	vector<int> m_ivRingFrameCntLst;
	
	//##ModelId=4B2B8A7102FE
	SPo_DRect m_rMBR;
	
	//##ModelId=4B2B8A720025
	LOG_SDOGEOMETRY()
	{
		m_nGtype=0;m_nSrid=0;//这两项的默认值设成0
	};
	//##ModelId=4B2B8A720026
	~LOG_SDOGEOMETRY(){};

	//重写拷贝初始化函数
	//##ModelId=4B2B8A720027
	LOG_SDOGEOMETRY(const LOG_SDOGEOMETRY &other)
	{
		m_nSrid = other.m_nSrid;
		m_nGtype = other.m_nGtype;
		m_gPoint = other.m_gPoint;
		int cnt = other.m_ipsElmInfos.size();
		for(int i=0;i<cnt;i++)
			m_ipsElmInfos.push_back(other.m_ipsElmInfos[i]);
		cnt = other.m_dpsOrdinates.size();
		for(i=0;i<cnt;i++)
			m_dpsOrdinates.push_back(other.m_dpsOrdinates[i]);
		cnt=other.m_ivRingFrameCntLst.size();
		for(i=0;i<cnt;i++)
			m_ivRingFrameCntLst.push_back(other.m_ivRingFrameCntLst[i]);
		
		m_rMBR=other.m_rMBR;
	};
    // \brief 相等运算
    // 
    // \return 如果相等，则返回1；否则，返回0。
    // 
    // \param right：相等运算右操作数
    //##ModelId=4B2B8A72002E
    bool operator==(const LOG_SDOGEOMETRY &right)
	{
		bool brval = (m_nSrid==right.m_nSrid);

		brval = (brval&&(m_nGtype==right.m_nGtype));
		
		brval = (brval&&(m_gPoint==right.m_gPoint));

		int ifcnt = m_ipsElmInfos.size();int ptcnt = m_dpsOrdinates.size();int i=0;

		brval = (brval&&(ifcnt==right.m_ipsElmInfos.size()));

		brval = (brval&&(ptcnt==right.m_dpsOrdinates.size()));
		
		for(i=0;i<ifcnt&&brval;i++)
			brval = (brval&&(m_ipsElmInfos[i]==right.m_ipsElmInfos[i]));
		for(i=0;i<ptcnt&&brval;i++)
			brval = (brval&&(m_dpsOrdinates[i]==right.m_dpsOrdinates[i]));
		int iivr = m_ivRingFrameCntLst.size();
		brval = (iivr==right.m_ivRingFrameCntLst.size());
		for(i=0;i<iivr&&brval;i++)
			brval = (brval&&(m_ivRingFrameCntLst[i]==right.m_ivRingFrameCntLst[i]));
		brval = (brval&&m_rMBR==right.m_rMBR);
				
		return brval;
	};
	
    // \brief 不相等运算
    // 
    // \return 如果不相等，则返回1；否则，返回0。
    // 
    // \param right：不相等运算右操作数
    //##ModelId=4B2B8A720030
    bool operator!=(const LOG_SDOGEOMETRY &right)
	{return !(*this == right) ;};
	
    
    // \brief 赋值运算
    // 
    // \return 当前点结构的引用
    // 
    // \param right：赋值运算右操作数
    //##ModelId=4B2B8A720032
    LOG_SDOGEOMETRY& operator=(const LOG_SDOGEOMETRY &right)
	{
		m_nSrid = right.m_nSrid;
		m_nGtype = right.m_nGtype;
		m_gPoint = right.m_gPoint;
		int cnt = right.m_ipsElmInfos.size();
		m_ipsElmInfos.clear();
		for(int i=0;i<cnt;i++)
			m_ipsElmInfos.push_back(right.m_ipsElmInfos[i]);
		cnt = right.m_dpsOrdinates.size();
		m_dpsOrdinates.clear();
		for(i=0;i<cnt;i++)
			m_dpsOrdinates.push_back(right.m_dpsOrdinates[i]);
		
		cnt = right.m_ivRingFrameCntLst.size();
		for(i=0;i<cnt;i++)
			m_ivRingFrameCntLst.push_back(right.m_ivRingFrameCntLst[i]);
		
		m_rMBR=right.m_rMBR;
		
		return *this ;
	};
	bool IsIntersect(double x1,double y1,double x2,double y2/*组成矩形的两个点坐标*/)
	{
		int nType = this->GetGeoType();
		switch(nType)
		{
		case GEO_TYPE_GEOPOINT:
			{				
				if(m_dpsOrdinates.size()==0)return false;
				return IsPfInRect(m_dpsOrdinates[0],x1,y1,x2,y2);
			}
			break;
		case GEO_TYPE_GEOPOLYLINE:
			{
				return IsRectAndPolyLineIntersectWith(x1,y1,x2,y2,&(m_dpsOrdinates),m_dpsOrdinates.size());
			}
			break;
		case GEO_TYPE_GEOPOLYGON:
			{
				return IsRectAndPolygonIntersectWith(x1,y1,x2,y2,&(m_dpsOrdinates),m_dpsOrdinates.size(),&m_ivRingFrameCntLst,m_ivRingFrameCntLst.size());
			}
			break;
		case GEO_TYPE_GEOANNOTATION:
			{
				return IsRectAndPolyLineIntersectWith(x1,y1,x2,y2,&m_dpsOrdinates,m_dpsOrdinates.size());
			}
			break;
		default:
			break;
		}
		return false;
	};
	void Offset(SPo_DPoint dOffsetPoint)
	{
		m_gPoint += dOffsetPoint;
		
		SPo_DPoint *pval = NULL;int nCount = m_dpsOrdinates.size();
		for(int iIndex=0;iIndex<nCount;iIndex++)
		{
			pval = (m_dpsOrdinates.begin()+iIndex);
			//if(!(m_pSpref == pSpatialReference || (pSpatialReference == NULL)))//坐标系和投影不同，需要进行坐标转换
			//{
			//	//之后用坐标转换改写代码.
			//	
			//}
			pval->Offset(dOffsetPoint);
		}
	};
	bool PllHitTest(SPo_DPoint sPoint, POINT &ipHit/*捕获细节，x,y分别表示断点前后节点序号，必定相邻或者相等*/,SPo_DPoint2D &dptConn/*线路径上的捕获断点*/,double dTolerance/* = 0.0*/)
	{
		int pstCount = m_dpsOrdinates.size();
		if(pstCount==0)	return 0;
		int ipt = 0;
		if(GetGeoType()!=GEO_TYPE_GEOPOLYLINE)return false;
		
		for(ipt=0;ipt<pstCount;ipt++)
		{
			if((m_dpsOrdinates[ipt].x+dTolerance>=sPoint.x&&sPoint.x>=m_dpsOrdinates[ipt].x-dTolerance)&&
				(m_dpsOrdinates[ipt].y+dTolerance>=sPoint.y&&sPoint.y>=m_dpsOrdinates[ipt].y-dTolerance))
			{
				ipHit.x = ipHit.y = ipt;
				dptConn.x = m_dpsOrdinates[ipt].x;dptConn.y = m_dpsOrdinates[ipt].y;
				
				return true;// ipt+1;//抓住了结构点，返回点序号+1
			}
		}
		if(pstCount>1)//还没有找到断点
		{
			SPo_DPoint *pPreOrd=NULL;SPo_DPoint*pCurOrd=NULL;
			for(ipt=0;ipt<pstCount-1;ipt++)
			{
				pPreOrd = m_dpsOrdinates.begin()+ipt;pCurOrd = m_dpsOrdinates.begin()+ipt+1;
				if(CalDistancePointLine(sPoint.x,sPoint.y,pPreOrd->x,pPreOrd->y,pCurOrd->x,pCurOrd->y)<=dTolerance)//捕获到了，求
				{//捕获到了，求直线m_dpsOrdinates[ipt];m_dpsOrdinates[ipt+1]段上的和点sPoint垂直的垂点
					SPo_DPoint dpt = CalNearestPointOnLineFrom(sPoint.x,sPoint.y,m_dpsOrdinates[ipt].x,m_dpsOrdinates[ipt].y,m_dpsOrdinates[ipt+1].x,m_dpsOrdinates[ipt+1].y);
					
					ipHit.x = ipt;ipHit.y = ipt+1;
					dptConn.x = dpt.x;dptConn.y = dpt.y;
					
					return true;
				}
			}
		}
		return false;
	};
	bool PllReverse()
	{
		if(GetGeoType() == GEO_TYPE_GEOPOLYLINE)
		{
			SPo_DPoint dPtTemp;
			int nPts = m_dpsOrdinates.size();
			int iflag = 0;int nCnt = (nPts/2);//循环次数
			for(int i = 0;i<nCnt;i++,iflag++)
			{//iflag 和 nPts-iflag-1坐标替换
				dPtTemp = *(m_dpsOrdinates.begin()+iflag);
				*(m_dpsOrdinates.begin()+iflag) = *(m_dpsOrdinates.begin()+(nPts-iflag-1));
				*(m_dpsOrdinates.begin()+(nPts-iflag-1)) = dPtTemp;
			}
			return true;
		}
		return false;
	};
	//增加一个环的点数
	bool PlnAppendRingPoints(int iVal)
	{
		if(iVal<1)return false;
		m_ivRingFrameCntLst.push_back(iVal);
		int *ivalref = (m_ivRingFrameCntLst.end()-1);
		*ivalref = iVal;
		return true;
	};
	void PlnClearRings()
	{
		m_ivRingFrameCntLst.clear();
	};
	//##ModelId=4B2B8A72003E
	bool IsEmpty()
	{
		return m_dpsOrdinates.size()==0?true:false;
	};
	SPo_DRect GetMBR(int nMode = GIS_COMPUTE_OFF, IPo_SpatialReference* pSpatialReference = NULL)
	{
		switch(nMode) 
		{
		case GIS_COMPUTE_ON:// 1002：重新计算
			{
				if(m_dpsOrdinates.size()>0)
				{
					vector<SPo_DPoint>::iterator itr = m_dpsOrdinates.begin();
					
					m_rMBR.bottom = m_rMBR.top = (*itr).y;				m_rMBR.left = m_rMBR.right = (*itr).x;
					itr++;
					for(;itr != m_dpsOrdinates.end();itr ++)
					{
						m_rMBR.bottom = max(m_rMBR.bottom,(*itr).y);
						m_rMBR.top = min(m_rMBR.top,(*itr).y);
						m_rMBR.right = max(m_rMBR.right,(*itr).x);
						m_rMBR.left = min(m_rMBR.left,(*itr).x);
					}
				}
			}
			break;
		case GIS_COMPUTE_ONCE://1003：如果没有计算过，则计算；  否则直接返回当前值
			if( m_rMBR.bottom == 0&&
				m_rMBR.top == 0&&
				m_rMBR.left == 0&&
				m_rMBR.right == 0)
			{
				m_rMBR = GetMBR(GIS_COMPUTE_ON,pSpatialReference);
			}
			break;
		default://GIS_COMPUTE_OFF//：1001或者其他。不计算，直接返回当前值（缺     省参数设置）
			break;
		}
		//if(!(m_pSpref == pSpatialReference || (pSpatialReference == NULL)))//坐标系和投影不同，需要进行坐标转换
		//{
		
		//}
		return m_rMBR;
	};
	SPo_DRect *GetMBRref(int nMode  = GIS_COMPUTE_OFF , IPo_SpatialReference* pSpatialReference  = NULL)
	{
		//	switch(nMode) 
		//	{
		//	case GIS_COMPUTE_ON:// 1002：重新计算
		//		{
		//			if(m_dpsOrdinates.size()>0)
		//			{
		//				MmgVector<SPo_DPoint>::iterator itr = m_dpsOrdinates.begin();
		//				
		//				m_rMBR.bottom = m_rMBR.top = (*itr).y;				m_rMBR.left = m_rMBR.right = (*itr).x;
		//				itr++;
		//				for(;itr != m_dpsOrdinates.end();itr ++)
		//				{
		//					m_rMBR.bottom = max(m_rMBR.bottom,(*itr).y);
		//					m_rMBR.top = min(m_rMBR.top,(*itr).y);
		//					m_rMBR.right = max(m_rMBR.right,(*itr).x);
		//					m_rMBR.left = min(m_rMBR.left,(*itr).x);
		//				}
		//			}
		//		}
		//		break;
		//	case GIS_COMPUTE_ONCE://1003：如果没有计算过，则计算；  否则直接返回当前值
		//		if( m_rMBR.bottom == 0&&
		//			m_rMBR.top == 0&&
		//			m_rMBR.left == 0&&
		//			m_rMBR.right == 0)
		//		{
		//			m_rMBR = GetMBR(GIS_COMPUTE_ON,pSpatialReference);
		//		}
		//		break;
		//	default://GIS_COMPUTE_OFF//：1001或者其他。不计算，直接返回当前值（缺     省参数设置）
		//		break;
		//	}
		return &m_rMBR;
	};
	int GetOsType()
	{
		return m_nGtype;
	};
	//##ModelId=4B2B8A72003F
	size_t GetBytesLength()
	{
		size_t dtsize = sizeof(size_t);
		
		dtsize += sizeof(int);
		
		dtsize += sizeof(int);
		
		if((m_nGtype%1000) == 1)
			dtsize += 3*sizeof(double);
		else if((m_nGtype%1000)==3)/////////////////////////////////hls added 20080620为存储面域点而做的修改
			dtsize += 3*sizeof(double);
		
		dtsize += sizeof(int);
		
		int elemcnt = m_ipsElmInfos.size();	
		for(int i=0;i<elemcnt;i++)
			dtsize += 3*sizeof(int);
		
		dtsize += sizeof(int);
		
		int ptscnt = m_dpsOrdinates.size();
		for(i=0;i<ptscnt;i++)
			dtsize += 3*sizeof(double);
		
		return dtsize;
	};

	//##ModelId=4B2B8A720040
	size_t FromBytes(PBYTE * ppBytes)
	{
		size_t pos = 0;	size_t dtsize = 0;
		pos += _cread(&dtsize,sizeof(size_t),1,(*ppBytes)+pos);
		pos += _cread(&m_nGtype,sizeof(int),1,(*ppBytes)+pos);
		pos += _cread(&m_nSrid,sizeof(int),1,(*ppBytes)+pos);
		if((m_nGtype%1000) == 1)
		{
			pos += _cread(&m_gPoint.x,sizeof(double),1,(*ppBytes)+pos);
			pos += _cread(&m_gPoint.y,sizeof(double),1,(*ppBytes)+pos);
			pos += _cread(&m_gPoint.z,sizeof(double),1,(*ppBytes)+pos);
		}
		else if((m_nGtype%1000)==3)/////////////////////////////////hls added 20080620为存储面域点而做的修改
		{
			pos += _cread(&m_gPoint.x,sizeof(double),1,(*ppBytes)+pos);
			pos += _cread(&m_gPoint.y,sizeof(double),1,(*ppBytes)+pos);
			pos += _cread(&m_gPoint.z,sizeof(double),1,(*ppBytes)+pos);
		}
		int elemcnt = 0;pos += _cread(&elemcnt,sizeof(int),1,(*ppBytes)+pos);
		m_ipsElmInfos.clear();
		for(int i=0;i<elemcnt;i++)
		{
			SPo_IPoint iptelem;
			m_ipsElmInfos.push_back(iptelem);
			SPo_IPoint *prefpt = (m_ipsElmInfos.end()-1);
			pos += _cread(&(prefpt->x),sizeof(int),1,(*ppBytes)+pos);
			pos += _cread(&(prefpt->y),sizeof(int),1,(*ppBytes)+pos);
			pos += _cread(&(prefpt->z),sizeof(int),1,(*ppBytes)+pos);
		}
		m_dpsOrdinates.clear();	
		int ptscnt = 0;
		pos += _cread(&ptscnt,sizeof(int),1,(*ppBytes)+pos);
		/////////////////////////////////////////////////////////////
		for(i=0;i<ptscnt;i++)
		{
			SPo_DPoint Dpoint;
			m_dpsOrdinates.push_back(Dpoint);
			SPo_DPoint *dptref = (m_dpsOrdinates.end()-1);
			pos += _cread(&(dptref->x),sizeof(double),1,(*ppBytes)+pos);
			pos += _cread(&(dptref->y),sizeof(double),1,(*ppBytes)+pos);
			pos += _cread(&(dptref->z),sizeof(double),1,(*ppBytes)+pos);
		}
		GetMBR(GIS_COMPUTE_ON);/////重新计算外接矩形
		return pos;
	};

	//##ModelId=4B2B8A720042
	size_t ToBytes(PBYTE * ppBytes)
	{
		size_t pos = 0;	size_t dtsize = 0;
		pos += _cwrite(&dtsize,sizeof(size_t),1,(*ppBytes)+pos);	
		pos += _cwrite(&m_nGtype,sizeof(int),1,(*ppBytes)+pos);
		pos += _cwrite(&m_nSrid,sizeof(int),1,(*ppBytes)+pos);
		if((m_nGtype%1000) == 1)//全部按照三维坐标
		{
			pos += _cwrite(&m_gPoint.x,sizeof(double),1,(*ppBytes)+pos);
			pos += _cwrite(&m_gPoint.y,sizeof(double),1,(*ppBytes)+pos);
			pos += _cwrite(&m_gPoint.z,sizeof(double),1,(*ppBytes)+pos);
		}
		else if((m_nGtype%1000)==3)/////////////////////////////////hls added 20080620为存储面域点而做的修改
		{
			pos += _cwrite(&m_gPoint.x,sizeof(double),1,(*ppBytes)+pos);
			pos += _cwrite(&m_gPoint.y,sizeof(double),1,(*ppBytes)+pos);
			pos += _cwrite(&m_gPoint.z,sizeof(double),1,(*ppBytes)+pos);
		}
		int elemcnt = m_ipsElmInfos.size();
		pos += _cwrite(&elemcnt,sizeof(int),1,(*ppBytes)+pos);	
		for(vector<SPo_IPoint>::iterator itr = m_ipsElmInfos.begin();itr!=m_ipsElmInfos.end();itr++)
		{
			pos += _cwrite(&((*itr).x),sizeof(int),1,(*ppBytes)+pos);
			pos += _cwrite(&((*itr).y),sizeof(int),1,(*ppBytes)+pos);
			pos += _cwrite(&((*itr).z),sizeof(int),1,(*ppBytes)+pos);
		}
		int ptscnt = m_dpsOrdinates.size();
		pos += _cwrite(&ptscnt,sizeof(int),1,(*ppBytes)+pos);
		for(vector<SPo_DPoint >::iterator pitr = m_dpsOrdinates.begin();pitr!=m_dpsOrdinates.end();pitr ++)
		{
			pos += _cwrite(&((*pitr).x),sizeof(double),1,(*ppBytes)+pos);
			pos += _cwrite(&((*pitr).y),sizeof(double),1,(*ppBytes)+pos);
			pos += _cwrite(&((*pitr).z),sizeof(double),1,(*ppBytes)+pos);
			
		}
		_cwrite(&pos,sizeof(size_t),1,*ppBytes);
		
		return pos;
	};
	int GetGeoType()
	{
		return OSPTGEO_TYPE3_POGEO(m_nGtype);
	};
	SPo_DPoint GetPoint(int nIndex, IPo_SpatialReference* pSpatialReference)
	{
		SPo_DPoint val;
		if(nIndex>-1&&nIndex<m_dpsOrdinates.size())
		{
			val = m_dpsOrdinates[nIndex];
			IPo_ProjCoordSys* pProjCoordSys = NULL;	IPo_Parameter **ppParameters = NULL;
			if(pSpatialReference&&(pProjCoordSys = pSpatialReference->GetProjCoordSysPtr())&&(ppParameters = pProjCoordSys->GetParameters()))//指定了空间参考系，需要进行坐标转换
			{	//之后用坐标转换改写代码.-----正解转换
				PRJCOORIDATE ProCoord;/*投影坐标*/					GEOCOORIDATE GeoCoord;/*地理坐标*/
				pProjCoordSys->Forward(1,&GeoCoord,&ProCoord);
				val.x = ProCoord.dX-ppParameters[0]->GetValue();
				val.y = ProCoord.dY-ppParameters[1]->GetValue();
			}
		}
		return val;
	};
	SPo_DPoint *GetPointPref(int nIndex, IPo_SpatialReference* pSpatialReference)
	{
		SPo_DPoint *pval = NULL;
		if(nIndex>-1&&nIndex<m_dpsOrdinates.size())
		{
			pval = (m_dpsOrdinates.begin()+nIndex);
			//if(!(m_pSpref == pSpatialReference || (pSpatialReference == NULL)))//坐标系和投影不同，需要进行坐标转换
			//{
			//	//之后用坐标转换改写代码.
			//	
			//}
		}
		return pval;
	};
	int GetPoints(int nPointCount, SPo_DPoint* & pPoints, IPo_SpatialReference* pSpatialReference = NULL, int nTolerance = 0)
	{
		int len = m_dpsOrdinates.size();	if(!(nTolerance<len))		return 0;//取值索引没给对 返回
		
		int returncnt = ((returncnt = len-nTolerance)>nPointCount?nPointCount:returncnt);//返回个数取小
		
		if(returncnt<1)						return 0;
		//缓存区已经存在
		
		for(int i = 0;i<returncnt;i++)
		{
			pPoints[i] = m_dpsOrdinates[nTolerance + i];
		}
		
		return static_cast<int>(returncnt);
	};
	unsigned int HitTest(SPo_DPoint sPoint, bool bSelected/*是否已经被选取*/,double dTolerance=0)
	{
		int pstCount = m_dpsOrdinates.size();
		if(pstCount==0)	return 0;
		int ipt = 0;
		if(bSelected)//要抓取结构点
		{
			for(ipt=0;ipt<pstCount;ipt++)
			{
				if((m_dpsOrdinates[ipt].x+dTolerance>=sPoint.x&&sPoint.x>=m_dpsOrdinates[ipt].x-dTolerance)&&
					(m_dpsOrdinates[ipt].y+dTolerance>=sPoint.y&&sPoint.y>=m_dpsOrdinates[ipt].y-dTolerance))
					return ipt+1;//抓住了，返回点序号+1
			}
			return 0;//没有抓住
		}
		else//要抓取本对象
		{
			int nType = this->GetGeoType();
			switch(nType)
			{
			case GEO_TYPE_GEOPOINT:
				{				
					SPo_DPoint ptTgt = m_dpsOrdinates[0];
					//选择正方形区域？？计算速度快(二维中)
					return ((m_dpsOrdinates[0].x+dTolerance>=sPoint.x&&sPoint.x>=m_dpsOrdinates[0].x-dTolerance)&&
						(m_dpsOrdinates[0].y+dTolerance>=sPoint.y&&sPoint.y>=m_dpsOrdinates[0].y-dTolerance));
					//选择圆形区域？？捕获精确，计算较慢(二维中)
					//double dist = sqrt((ptOriginal.x-ptval.x)*(ptOriginal.x-ptval.x)+(ptOriginal.y-ptval.y)*(ptOriginal.y-ptval.y));				
					//iscatch = (dist<=dTolerance);
				}
				break;
			case GEO_TYPE_GEOPOLYLINE:
				{
					if(pstCount<2)	return 0;
					SPo_DPoint *pPreOrd=NULL;SPo_DPoint *pCurOrd=NULL;
					for(ipt=0;ipt<pstCount-1;ipt++)
					{
						pPreOrd=m_dpsOrdinates.begin()+ipt;pCurOrd=m_dpsOrdinates.begin()+ipt+1;
						if(CalDistancePointLine(sPoint.x,sPoint.y,pPreOrd->x,pPreOrd->y,pCurOrd->x,pCurOrd->y)<=dTolerance)
							return 1;
					}
					return 0;
				}
				break;
			case GEO_TYPE_GEOPOLYGON:
				{
					if(m_dpsOrdinates.size()>3)
					{
						SPo_DPoint *ppre;		SPo_DPoint *pthp;	int rgncount = m_ivRingFrameCntLst.size();
						
						int iPtor = 0;int i=0;			int lwP=0;//记录与垂线向下延长时与边的交点个数
						
						for(int r=0;r<rgncount;r++)
						{	////////
							for(i=1;i<m_ivRingFrameCntLst[r];i++)
							{
								ppre = m_dpsOrdinates.begin()+iPtor+i-1;	pthp = m_dpsOrdinates.begin()+iPtor+i;
								if(!(pthp->x==ppre->x&&pthp->y==ppre->y))//跳过中间的重合结点,如果前一点不等于后一点;
								{
									if(((sPoint.x-pthp->x==0)&&(sPoint.y-pthp->y==0))||((sPoint.x-ppre->x==0)&&(sPoint.y-ppre->y==0)))
										return true;//与节点重合,这里我们认为在内部//20160803
									else
									{
										if ( pthp->x == ppre->x || // p1p2 与 y=p0.y平行 
											sPoint.x < min(ppre->x, pthp->x) || // 交点在p1p2延长线上 
											sPoint.x >= max(ppre->x, pthp->x) ) // 交点在p1p2延长线上 
											continue; 						
										if ((pthp->x-ppre->x)*((pthp->y-ppre->y)*(sPoint.x-ppre->x)-(pthp->x-ppre->x)*(sPoint.y-ppre->y))<0) 
											lwP++; // 只统计单边交点 
									}
								}
							}
							////////
							iPtor += m_ivRingFrameCntLst[r];
						}				
						return (lwP%2)==1?true:false;	//交点奇数个true//交点偶数个false
					}
					else return false;
				}
				break;
			case GEO_TYPE_GEOANNOTATION:
				{
					if(pstCount>1)
					{
						SPo_DPoint *pPreOrd=NULL;SPo_DPoint *pCurOrd=NULL;
						for(ipt=0;ipt<pstCount-1;ipt++)
						{
							pPreOrd=m_dpsOrdinates.begin()+ipt;pCurOrd=m_dpsOrdinates.begin()+ipt+1;
							if(CalDistancePointLine(sPoint.x,sPoint.y,pPreOrd->x,pPreOrd->y,pCurOrd->x,pCurOrd->y)<=dTolerance)
								return 1;
						}
						return 0;
					}
					else
					{
						for(ipt=0;ipt<pstCount;ipt++)//由于线型注记当作折线来捕获，参考线要素的捕获方法
						{
							if((m_dpsOrdinates[ipt].x+dTolerance>=sPoint.x&&sPoint.x>=m_dpsOrdinates[ipt].x-dTolerance)&&
								(m_dpsOrdinates[ipt].y+dTolerance>=sPoint.y&&sPoint.y>=m_dpsOrdinates[ipt].y-dTolerance))
								return 1;//抓住了，返回1
						}
						return 0;//没有抓住
					}
				}
				break;
			default:
				break;
			}
			return false;
		}	
	};
	////brief
	//    获取几何对象的定位点个数
	////return
	//    几何对象的定位点个数
	//##ModelId=464AC3550196
	int GetPointCount()
	{
		return m_dpsOrdinates.size();
	};
	
	bool SetMBR(SPo_DRect rect, IPo_SpatialReference* pSpatialReference = NULL)
	{
		m_rMBR = rect;
		return true;
	};
	bool SetEmpty()
	{
		m_ipsElmInfos.clear();
		m_dpsOrdinates.clear();
		m_ivRingFrameCntLst.clear();
		return true;
	}
	void ClearPoints()
	{
		m_dpsOrdinates.clear();
		
		m_ipsElmInfos.clear();
		
		m_ivRingFrameCntLst.clear();
	};
	bool DeletePoint(int iIndex)
	{
		if(iIndex>-1&&iIndex<m_dpsOrdinates.size())
		{
			m_dpsOrdinates.erase(m_dpsOrdinates.begin()+iIndex);
			//重新计算外接矩形
			if(m_dpsOrdinates.size()>0)
			{
				vector<SPo_DPoint>::iterator itr = m_dpsOrdinates.begin();
				
				m_rMBR.bottom = m_rMBR.top = (*itr).y;				m_rMBR.left = m_rMBR.right = (*itr).x;
				itr++;
				for(;itr != m_dpsOrdinates.end();itr ++)
				{
					m_rMBR.bottom = max(m_rMBR.bottom,(*itr).y);
					m_rMBR.top = min(m_rMBR.top,(*itr).y);
					m_rMBR.right = max(m_rMBR.right,(*itr).x);
					m_rMBR.left = min(m_rMBR.left,(*itr).x);
				}
			}
			return true;
		}
		return false;
	};
	SPo_DPoint *GetFirstOsGpoint()
	{
		return &m_gPoint;
	};
	bool AddPoint(SPo_DPoint sPoint, IPo_SpatialReference * pSpatialReference)
	{
		SPo_DPoint *pval = &sPoint;
		
		size_t scnt = m_dpsOrdinates.size();
		
		if(scnt>=2&&(m_nGtype == GEO_TYPE_GOS2POINT||m_nGtype == GEO_TYPE_GOS3POINT))///////////////如果是点要素
			return false;
		
		if(scnt==0)//第一次添加几何坐标
		{
			m_rMBR.bottom = m_rMBR.top = sPoint.y;
			m_rMBR.right = m_rMBR.left = sPoint.x;
		}
		else
		{
			m_rMBR.bottom = max(m_rMBR.bottom,sPoint.y);
			m_rMBR.top = min(m_rMBR.top,sPoint.y);
			m_rMBR.right = max(m_rMBR.right,sPoint.x);
			m_rMBR.left = min(m_rMBR.left,sPoint.x);
		}
		
		m_dpsOrdinates.push_back(sPoint);
		SPo_DPoint *pntref = (m_dpsOrdinates.end()-1);
		*pntref = sPoint;
		
		return true;
	};
	void RetrieveSpatialElemInfo(bool bCoordReset = true/*是否重因勾环按顺逆时针方向新组织坐标点*/)
	{
		switch(GetGeoType())
		{
		case GEO_TYPE_GEOPOINT:
			{
				m_ipsElmInfos.clear();
				if(m_dpsOrdinates.size()>0)
				{
					SPo_IPoint Ipt;
					m_ipsElmInfos.push_back(Ipt);
					SPo_IPoint *Iptref = (m_ipsElmInfos.end()-1);
					*Iptref = SPo_IPoint(1,1,1);
				}
			}
			break;
		case GEO_TYPE_GEOPOLYLINE:
			{
				m_ipsElmInfos.clear();
				if(m_dpsOrdinates.size()>0)
				{
					SPo_IPoint Ipt;
					m_ipsElmInfos.push_back(Ipt);
					SPo_IPoint *Iptref = (m_ipsElmInfos.end()-1);
					*Iptref = SPo_IPoint(1,2,1);
				}
			}
			break;
		case GEO_TYPE_GEOPOLYGON:
			{
				m_ipsElmInfos.clear();
		
				if(m_dpsOrdinates.size()<4)	return ;//多边形定位点个数>=4
				
				PlnCloseAll();//闭合环
				int ringcnt = m_ivRingFrameCntLst.size();
				if(ringcnt==0)	return ;
				bool *bPositive = new bool[ringcnt];//是否顺时针方向的数组
				SPo_DRect *pMBRs = new SPo_DRect[ringcnt];//所有外接矩形
				bool *bExtRing = new bool[ringcnt];//所有环的内外型标志代码的bool值。1003代表外环，2003代表内环
				for(int mmm=0;mmm<ringcnt;mmm++)
					bExtRing[mmm]=true;//开始都认为单环是外环，它被包含偶数次(include 0)都是外环，被包含奇数次是内环

				int iPtor = 0;/*坐标点的索引号起点*/	int iRingIndex = 0;	int ii=0;int jj=0;
				vector<int>::iterator itr = m_ivRingFrameCntLst.begin();
				//==============计算所有环的外接矩形*******
				for(itr = m_ivRingFrameCntLst.begin(),iRingIndex = 0;itr!=m_ivRingFrameCntLst.end();itr++,iRingIndex++)
				{
					//对于坐标串中的第itr个环
					for(int i=0;i<(*itr);i++)//
					{
						//=====================================计算外接矩形--------***********************************
						if(i == 0)
						{
							pMBRs[iRingIndex].left = pMBRs[iRingIndex].right = m_dpsOrdinates[iPtor+i].x;
							pMBRs[iRingIndex].bottom = pMBRs[iRingIndex].top = m_dpsOrdinates[iPtor+i].y;
						}
						else
						{
							pMBRs[iRingIndex].left = min(pMBRs[iRingIndex].left,m_dpsOrdinates[iPtor+i].x);
							pMBRs[iRingIndex].right = max(pMBRs[iRingIndex].right,m_dpsOrdinates[iPtor+i].x);
							pMBRs[iRingIndex].bottom = max(pMBRs[iRingIndex].bottom,m_dpsOrdinates[iPtor+i].y);
							pMBRs[iRingIndex].top = min(pMBRs[iRingIndex].top,m_dpsOrdinates[iPtor+i].y);
						}
					}
					//iPtor += (*itr);
				}
				//============================将最大外接矩形放在第一个==========********************************
				int maxMBRindex = 0;
				for(ii=0;ii<ringcnt;ii++)
				{
					for(jj=0;jj<ringcnt;jj++)
					{
						pMBRs[jj].IsWithin(&pMBRs[ii])?maxMBRindex=ii:maxMBRindex=jj;
					}
				}
				if(maxMBRindex>0)//将坐标重新排序，最大外接矩形的外环放在第一个==========********************************
				{
				}
				//======================================计算顺或者逆时针方向------******************************
				for(itr = m_ivRingFrameCntLst.begin(),iRingIndex = 0,iPtor = 0;itr!=m_ivRingFrameCntLst.end();itr++,iRingIndex++)
				{
					double anglesum = 0;
					//对于坐标串中的第itr个环
					for(int i=0;i<(*itr);i++)//
					{
						if(i>1)
						{
							//对于m_dpsOrdinates[iPtor+i-2],m_dpsOrdinates[iPtor+i-1],m_dpsOrdinates[iPtor+i]
							anglesum += GetDirAngle3(m_dpsOrdinates[iPtor+i-2].x,m_dpsOrdinates[iPtor+i-2].y,
													 m_dpsOrdinates[iPtor+i-1].x,m_dpsOrdinates[iPtor+i-1].y,
													 m_dpsOrdinates[iPtor+i].x,m_dpsOrdinates[iPtor+i].y);
						}
					}
					bPositive[iRingIndex] = (anglesum<(((*itr)-2)*PO_PI)?false:true);
					
					iPtor += (*itr);
				}
				//==========================================对于iRingIndex个环计算他们到底是内环还是外环***************	
				//以开始都认为单环是外环，它被包含偶数次都是外环，被包含奇数次是内环
				for(ii = 0;ii<ringcnt/*iRingIndex*/;ii++)
				{
					for(jj=0;jj<ringcnt/*iRingIndex*/;jj++)
					{
						if(ii==jj)	continue;
						pMBRs[ii].IsWithin(&pMBRs[jj])?(bExtRing[ii]=(!bExtRing[ii])):0;
					}
				}//=====================================================================================***************
				//==========================================调整内外环坐标串顺序，同时添加三元组信息*******************
				iPtor = 0;/*坐标点的索引号起点*/SPo_DPoint dptemp;
				for(ii=0;ii<iRingIndex;ii++)//环个数
				{
					if(bExtRing[ii])//是外环,坐标必须逆时针排列(否则坐标串要重新倒排)
					{
						if(bPositive[ii])//偶数次表示外环,坐标必须逆时针排列(否则坐标串要重新倒排)
						{
							//if(!bCoordReset)	//如果不重组

							for(jj=0;bCoordReset&&(jj<m_ivRingFrameCntLst[ii]/2);jj++)//m_ivRingFrameCntLst[ii]第ii环的坐标点数
							{
								dptemp = m_dpsOrdinates[iPtor+jj];
								m_dpsOrdinates[iPtor+jj].x = m_dpsOrdinates[iPtor+m_ivRingFrameCntLst[ii]-jj-1].x;
								m_dpsOrdinates[iPtor+jj].y = m_dpsOrdinates[iPtor+m_ivRingFrameCntLst[ii]-jj-1].y;
								//*(m_dpsOrdinates[iPtor+jj]) = *(m_dpsOrdinates[iPtor+m_ivRingFrameCntLst[ii]-jj-1]);

								(m_dpsOrdinates[iPtor+m_ivRingFrameCntLst[ii]-jj-1]) = dptemp;
							}
						}			
					}
					else//是内环
					{
						if(!bPositive[ii])//奇数次表示内环,坐标必须顺时针排列(否则坐标串要重新倒排)
						{
							//if(!bCoordReset)	//如果不重组
							for(jj=0;bCoordReset&&(jj<m_ivRingFrameCntLst[ii]/2);jj++)//m_ivRingFrameCntLst[ii]第ii环的坐标点数
							{
								dptemp = m_dpsOrdinates[iPtor+jj];
								m_dpsOrdinates[iPtor+jj].x = m_dpsOrdinates[iPtor+m_ivRingFrameCntLst[ii]-jj-1].x;
								m_dpsOrdinates[iPtor+jj].y = m_dpsOrdinates[iPtor+m_ivRingFrameCntLst[ii]-jj-1].y;
								//*(m_dpsOrdinates[iPtor+jj]) = *(m_dpsOrdinates[iPtor+m_ivRingFrameCntLst[ii]-jj-1]);
								m_dpsOrdinates[iPtor+m_ivRingFrameCntLst[ii]-jj-1] = dptemp;
							}
						}
					}
					//==============================添加一个元组
					SPo_IPoint Ipt;
					m_ipsElmInfos.push_back(Ipt);
					SPo_IPoint *Iptref = (m_ipsElmInfos.end()-1);
					*Iptref = SPo_IPoint(iPtor+1,bExtRing[ii]?1003:2003,1);

					iPtor += m_ivRingFrameCntLst[ii];
				}
				
				delete []bPositive;
				delete []pMBRs;
				delete []bExtRing;
			}
			break;
		case GEO_TYPE_GEOANNOTATION:
			{
				int len = m_ipsElmInfos.size();
				m_ipsElmInfos.clear();
				if(m_dpsOrdinates.size()>0)
				{
					SPo_IPoint Ipt;
					m_ipsElmInfos.push_back(Ipt);
					SPo_IPoint *Iptref = (m_ipsElmInfos.end()-1);
					*Iptref = SPo_IPoint(1,2,1);//认为是直线段的线串
				}
			}
			break;
		default:
			break;
		}
	};
	bool PlnCloseAll()
	{
		if(GEO_TYPE_GEOPOLYGON == GetGeoType())
		{
			m_ivRingFrameCntLst.clear();//清除
			int ptscnt = m_dpsOrdinates.size();
			SPo_DPoint ptCloser;
			int ecnt = 0;
			for(vector<SPo_DPoint>::iterator itr = m_dpsOrdinates.begin();itr!=m_dpsOrdinates.end();itr++)
			{
				ecnt ++;//未封闭开始计数
				
				if(ecnt == 1)	ptCloser = ((*itr));//起点
				else
				{
					if(ptCloser == ((*itr))&&ecnt>2)//找到一个封闭点
					{
						int icnt = 0;
						m_ivRingFrameCntLst.push_back(icnt);
						int *ivalref = (m_ivRingFrameCntLst.end()-1);
						*ivalref = ecnt;
						ecnt = 0;
					}
				}
			}
			if(ecnt>0)//有未封闭的多余点数
			{
				int icnt = 0;
				m_ivRingFrameCntLst.push_back(icnt);
				int *ivalref = (m_ivRingFrameCntLst.end()-1);
				*ivalref = ecnt;
			}
			
			return 1;
		}
		return false;
	};
	SPo_DPoint PlnGetCentralPoint()
	{
		return m_gPoint;
	};
	int PlnGetRingPointsCountOfIndex(int iIndex)
	{
		if(iIndex>-1&&iIndex<m_ivRingFrameCntLst.size())
		{
			vector<int>::iterator itr = m_ivRingFrameCntLst.begin()+iIndex;
			return *itr;
		}
		else
			return 0;
	};
	int PlnGetRingsCount()
	{
		return m_ivRingFrameCntLst.size();
	};
	bool PlnSetCentralPoint(SPo_DPoint sPoint, IPo_SpatialReference* pSpatialReference = NULL)
	{
		m_gPoint = sPoint;
		return true;
	};
	bool PntSetDirectionPoint(SPo_DPoint sPoint, IPo_SpatialReference* pSpatialReference  = NULL)
	{
		bool setval = false;
		
		int ptcnt = m_dpsOrdinates.size();
		
		SPo_DPoint tval = sPoint;
		
		if(ptcnt>0)
		{
			if(ptcnt == 1)
			{
				//if(!(m_pSpref == pSpatialReference || (pSpatialReference == NULL)))//坐标系和投影不同，需要进行坐标转换
				//{
				//	//将sPoint的坐标进行转换,存到ptval中
				//	//...
				//}
				//else//空间参考系与指定的相同
				//{
				//}
				m_dpsOrdinates.push_back(tval);
				SPo_DPoint *pntref = (m_dpsOrdinates.end()-1);
				*pntref = tval;
				setval = true;
			}
			else//有两点以上
			{
				tval = m_dpsOrdinates[1];
				//if(!(m_pSpref == pSpatialReference || (pSpatialReference == NULL)))//坐标系和投影不同，需要进行坐标转换
				//{
				//	//将sPoint的坐标进行转换,存到ptval中
				//	//...
				//}
				//else//空间参考系与指定的相同
				//{
				tval = sPoint;
				//}
				setval = true;
			}
		}
		
		return static_cast<bool>(setval);
	};
	bool PntSetPoint(SPo_DPoint sPoint, IPo_SpatialReference* pSpatialReference  = NULL, int iIndex = 0)
	{
		bool setval = false;
		
		int ptcnt = m_dpsOrdinates.size();
		
		if(iIndex == 0)//要设置第一点
		{
			if(ptcnt==0)//原来没有点
			{
				//if(!(m_pSpref == pSpatialReference || (pSpatialReference == NULL)))//坐标系和投影不同，需要进行坐标转换
				//{
				//	//将sPoint的坐标进行转换,存到ptval中
				//	//...
				//}
				m_dpsOrdinates.push_back(sPoint);
				SPo_DPoint *pntref = (m_dpsOrdinates.end()-1);
				*pntref = sPoint;
				setval = true;
			}
			else//原来有一个点以上
			{			
				SPo_DPoint *ptval = &(m_dpsOrdinates[0]);
				*ptval = sPoint;
				//if(!(m_pSpref == pSpatialReference || (pSpatialReference == NULL)))//坐标系和投影不同，需要进行坐标转换
				//{
				//	//将sPoint的坐标进行转换,存到ptval中
				//	//...
				//}
				setval = true;	
			}
			///设置外接矩形
			m_rMBR.bottom = m_rMBR.top = sPoint.y;
			m_rMBR.right = m_rMBR.left = sPoint.x;
		}
		else if(iIndex == 1)//要设置第二点
		{
			if(ptcnt==0)//原来没有点
			{
				SPo_DPoint	spt;
				m_dpsOrdinates.push_back(spt);//插入一个默认点
				//第二点的方向点
				SPo_DPoint *ptval = &sPoint;
				//if(!(m_pSpref == pSpatialReference || (pSpatialReference == NULL)))//坐标系和投影不同，需要进行坐标转换
				//{
				//	//将sPoint的坐标进行转换,存到ptval中
				//	//...
				//}
				m_dpsOrdinates.push_back(*ptval);
				SPo_DPoint *pntref = (m_dpsOrdinates.end()-1);
				*pntref = (*ptval);
				setval = true;
			}
			else if(ptcnt == 1)//原来有一个点
			{
				//第二点的方向点
				SPo_DPoint *ptval = &sPoint;
				//if(!(m_pSpref == pSpatialReference || (pSpatialReference == NULL)))//坐标系和投影不同，需要进行坐标转换
				//{
				//	//将sPoint的坐标进行转换,存到ptval中
				//	//...
				//}
				m_dpsOrdinates.push_back(*ptval);
				SPo_DPoint *pntref = (m_dpsOrdinates.end()-1);
				*pntref = (*ptval);
				
				setval = true;
			}
			else//点数有两点以上
			{			
				SPo_DPoint *ptval = &(m_dpsOrdinates[1]);
				*ptval = sPoint;
				//if(!(m_pSpref == pSpatialReference || (pSpatialReference == NULL)))//坐标系和投影不同，需要进行坐标转换
				//{
				//	//将sPoint的坐标进行转换,存到ptval中
				//	//...
				//}
				setval = true;	
			}
		}
		else
			setval = false;
		
		return setval;
	};	
	void TcCoordConverse(VISZ_DRAWPARMS *pParm)
	{
		pParm->TcCoordConverse(&m_dpsOrdinates,m_dpsOrdinates.size(),&m_dpsOrdinates);
		
		pParm->TcCoordConverse(&m_gPoint,1,&m_gPoint);
	};	
	void inline TcCoordConverseTran(VISZ_DRAWPARMS *pParm)
	{
		pParm->TcCoordConverseTran(&m_dpsOrdinates,m_dpsOrdinates.size(),&m_dpsOrdinates);
		
		pParm->TcCoordConverseTran(&m_gPoint,1,&m_gPoint);
	};
};
////////////////////hls changed 20110107
struct LOG_BASEGEOMETRY
{
public:
	//##ModelId=464AC3550203
	unsigned int m_nType;
	/////////////////////
	LOG_SDOGEOMETRY m_sdoGeometry;
public:	
    // \brief 赋值运算
    // 
    // \return 当前点结构的引用
    // 
    // \param right：赋值运算右操作数
    //##ModelId=4B2B8A720032
    LOG_BASEGEOMETRY& operator=(const LOG_BASEGEOMETRY &right)
	{
		m_nType = right.m_nType;
		m_sdoGeometry = right.m_sdoGeometry;
		m_sdoGeometry.m_nGtype = POGEO_TYPE3_OSPTGEO(m_nType);
		return *this ;
	};
	SPo_DPoint PlnGetCentralPoint(int nMode = GIS_COMPUTE_OFF)
	{
		return m_sdoGeometry.PlnGetCentralPoint();
	};
	int PlnGetRingPointsCountOfIndex(int iIndex)
	{
		return m_sdoGeometry.PlnGetRingPointsCountOfIndex(iIndex);
	};
	bool PntSetDirectionPoint(SPo_DPoint sPoint, IPo_SpatialReference* pSpatialReference /* = NULL */)
	{
		return m_sdoGeometry.PntSetDirectionPoint(sPoint,pSpatialReference);
	};
	bool PntSetPoint(SPo_DPoint sPoint, IPo_SpatialReference* pSpatialReference /* = NULL */, int iIndex /* = 0 */)
	{
		return m_sdoGeometry.PntSetPoint(sPoint,pSpatialReference,iIndex);
	};
	//##ModelId=464AC35103C9
	bool AddPoint(SPo_DPoint sPoint)
	{
		return m_sdoGeometry.AddPoint(sPoint,NULL);
	}	
	//计算几何数据量的字节数大小
	size_t GetBytesLength()
	{
		return m_sdoGeometry.GetBytesLength();
	};
	//ppBytes的内容规定为全部所需的几何对象数据及其数据量的大小，数据量大小按照提供的接口计算
	//##ModelId=46D66A84036B
	size_t ToBytes(PBYTE * ppBytes)
	{
		int gtype = POGEO_TYPE3_OSPTGEO(m_nType);//内部几何类型转为Oracle Spatial 类型
		m_sdoGeometry.m_nGtype = gtype;
		return m_sdoGeometry.ToBytes(ppBytes);
	}
	//ppBytes的内容规定为全部所需的几何对象数据及其数据量的大小，数据量大小按照提供的接口计算
	//##ModelId=46D66A84036D
	size_t FromBytes(PBYTE * ppBytes)
	{
		size_t szpos = m_sdoGeometry.FromBytes(ppBytes);
		m_nType = OSPTGEO_TYPE3_POGEO(m_sdoGeometry.m_nGtype);//Oracle Spatial 类型转为内部几何类型
		return szpos;
	}
	//清除全部定位点
	//##ModelId=46C4F907008C
	void ClearPoints()
	{
		m_sdoGeometry.ClearPoints();
	};
	bool DeletePoint(int iIndex)
	{
		return m_sdoGeometry.DeletePoint(iIndex);
	};
	SPo_DPoint *GetFirstOsGpoint()
	{
		return m_sdoGeometry.GetFirstOsGpoint();
	};
	//“内部函数”
	////brief
	//    获取几何对象类型
	//
	//    可根据该类型利用该类型的几何对象指针将基本    
	//几何对象转换为该类型的几何对象。
	////return
	//    几何对象的类型
	//##ModelId=464AC3550178
	int GetGeoType()
	{
		return m_nType;
	}

	//“内部函数”
	////brief
	//    获取几何对象的最小外接矩形
	////return
	//    几何对象的最小外接矩形
	////param
	//     nMode：获取方式。可能的取值为：
	//     PO_COMPUTE_OFF：不计算，直接返回当前值（缺     
	//省参数设置）
	//     PO_COMPUTE_ON：重新计算
	//     PO_COMPUTE_ONCE：如果没有计算过，则计算；     
	//否则直接返回当前值
	//
	//     pSpatialReference：希望获取的最小外接矩形     
	//所对应的空间参考系。缺省为NULL，表示使用几     
	//何对象本身的空间参考系。
	//##ModelId=464AC355017A
	SPo_DRect GetMBR(int nMode = GIS_COMPUTE_OFF, IPo_SpatialReference* pSpatialReference = NULL)
	{
		return m_sdoGeometry.GetMBR(nMode,pSpatialReference);
	};
	SPo_DRect *GetMBRref(int nMode  = GIS_COMPUTE_OFF , IPo_SpatialReference* pSpatialReference  = NULL)
	{
		return m_sdoGeometry.GetMBRref(nMode,pSpatialReference);
	};
	int GetOsType()
	{
		return m_sdoGeometry.GetOsType();
	};

	////brief
	//    获取几何对象的定位点
	//    根据下标和指定空间参考系获取定位点坐标
	//    0<=nIndex<定位点个数，若输入其它值则返回    
	//SPo_Point(0,0)。
	////return
	//    SPo_Point 定位点坐标
	////param
	//    nIndex: 定位点的下标
	//    pSpatialReference: 希望获取的定位点对应的空    
	//间参考系。缺省为NULL，表示使用几何对象本身    
	//的空间参考系。
	//##ModelId=464AC3550188
	SPo_DPoint GetPoint(int nIndex, IPo_SpatialReference* pSpatialReference = NULL)
	{
		return m_sdoGeometry.GetPoint(nIndex,pSpatialReference);
	};

	//brief
    //     获取几何对象的定位点的地址引用
    //     根据下标和指定空间参考系获取定位点坐标
    //     0<=nIndex<定位点个数，若输入其它值则返回    SPo_Point(0,0)。
    //return
    //     SPo_Point 定位点坐标
    //param
    //     nIndex: 定位点的下标
    //     pSpatialReference: 希望获取的定位点对应的空    间参考系。缺省为NULL，表示使用几何对象本身
    // 的空间参考系。
    //##ModelId=46AF5833030D
    SPo_DPoint *GetPointPref(int nIndex, IPo_SpatialReference* pSpatialReference = NULL)
	{
		return m_sdoGeometry.GetPointPref(nIndex,pSpatialReference);		
	}

	////brief
	//    获取几何对象的定位点个数
	////return
	//    几何对象的定位点个数
	//##ModelId=464AC3550196
	int GetPointCount()
	{
		return m_sdoGeometry.GetPointCount();
	}
	//brief
    //     成批获取定位点坐标。
    //     根据给定的所需获得的定位点的个数和采样容限    值成批获取定位点坐标。
    //return
    //     实际获得的定位点个数(<= nPointCount)。
    //param
    //     nPointCount: 所需获取的定位点个数。
    //     pPoints: 输出参数，实际获得的定位点坐标。
    //     pSpatialReference: 希望获取的定位点对应的空    间参考系。缺省为NULL，表示使用几何对象本身
    // 的空间参考系。
	//		取出的坐标要按照给出的pSpatialReference进行坐标转换
	//		即返回的坐标已经是pSpatialReference下的坐标
    //     nTolerance: 采样的容限值。缺省为0，直接获取
    // 前nPointCount个定位点的坐标。(认为它是取坐标串的起始位置，从第nTolerance个坐标开始往后取)
    //##ModelId=456253CB003E
    int GetPoints(int nPointCount, SPo_DPoint* & pPoints, IPo_SpatialReference* pSpatialReference = NULL, int nTolerance = 0)
	{
		return m_sdoGeometry.GetPoints(nPointCount,pPoints,pSpatialReference,nTolerance);
	};
	
	////brief
	//    是否定义了空的点集
	////return
	//    如果是空，返回true
	//##ModelId=464AC35501A7
	bool IsEmpty()
	{
		return m_sdoGeometry.IsEmpty();
	}

	////brief
	//    清空几何对象。
	////return
	//    清空成功，返回true
	//##ModelId=464AC35501A9
	bool SetEmpty()
	{
		return m_sdoGeometry.SetEmpty();
	}

	//“内部函数”
	////brief
	//    设置几何对象的最小外接矩形
	//    根据给定的空间参考系设置几何对象的最小外接    矩形
	///return
	//    最小外接矩形设置是否成功，若    
	//pSpatialReference不为空，且坐标转换不成功，    
	//则返回false，设置成功则返回true。
	////param
	//    rect: 需设置的最小外接矩形
	//    pSpatialReference: 最小外接矩形对应的空间参    
	//考系。缺省为NULL，表示使用几何对象本身的空    间参考系。
	//##ModelId=464AC35501B5
	bool SetMBR(SPo_DRect rect, IPo_SpatialReference* pSpatialReference = NULL)
	{
		return m_sdoGeometry.SetMBR(rect,pSpatialReference);
	}
	void Offset(SPo_DPoint dOffsetPoint)
	{
		m_sdoGeometry.Offset(dOffsetPoint);
	}
	//brief
    //     测试在指定容限允许的范围内，指定的点是否在    几何对象的范围内，亦即是否点中了该对象。
    //param
    //     sPoint: 指定的点，测试点,它是pSpatialReference下的坐标,内部转换后进行比较
    //     pSpatialReference: 测试点对应的空间参考系。    缺省为NULL，表示使用几何对象本身的空间参考    系。
    //     dTolerance: 阈值，容限值，单位与数据集的单    位相同
	//bSelected:是否已经被选取，如果为true，dTolerance要给值，函数要抓取几何对象的结构点handlepoint，返回值为点序号+1
	//如果为false，dTorlerance不一定要给值，函数要抓取几何对象，返回值为0（没抓住）1（抓住）
	//返回值为0时表示没有抓住对象也没有抓住结构点
    //##ModelId=456253CB030D
    int HitTest(SPo_DPoint sPoint, bool bSelected/*是否已经被选取*/,double dTolerance=0)
	{
		return m_sdoGeometry.HitTest(sPoint,bSelected,dTolerance);
	};
	//是否被单点选取
	//##ModelId=4829521B037A
	bool IsSelectedByPoint(SPo_DPoint *pSel/*点选取的定位坐标*/,float fTolerance/*选取距离的阈值*/)
	{
		switch(m_nType)
		{
		case GEO_TYPE_GEOPOINT:
			{
			}
			break;
		case GEO_TYPE_GEOPOLYLINE:
			{
			}
			break;
		case GEO_TYPE_GEOPOLYGON:
			{				
			}
			break;
		case GEO_TYPE_GEOANNOTATION:
			{
			}
			break;
		case GEO_TYPE_GEORECT:
			{			
			}
			break;
		default:
			break;
		}
		return false;
	}
	//是否被圆选取(该要素与圆内区域有相交部分)
	//##ModelId=4829521C0000
	bool IsSelectedByCircle(SPo_DPoint *pCenter/*圆选取的圆心点*/,SPo_DPoint *pPointOnCircle/*圆弧上的另一点*/)
	{
		switch(m_nType)
		{
		case GEO_TYPE_GEOPOINT:
			{
			}
			break;
		case GEO_TYPE_GEOPOLYLINE:
			{
			}
			break;
		case GEO_TYPE_GEOPOLYGON:
			{				
			}
			break;
		case GEO_TYPE_GEOANNOTATION:
			{
			}
			break;
		case GEO_TYPE_GEORECT:
			{			
			}
			break;
		default:
			break;
		}
		return false;
	}
	//是否被矩形选取(该要素与矩形内区域有相交部分)
	//##ModelId=4829521C004E
	bool IsSelectedByRect(SPo_DPoint *pP1/*矩形对角线上的一点*/,SPo_DPoint *pP2/*矩形对角线上的另一点*/)
	{
		switch(m_nType)
		{
		case GEO_TYPE_GEOPOINT:
			{
				//hls added 20091205
				if(m_sdoGeometry.m_dpsOrdinates.size()==0)return false;
				return IsPfInRect(m_sdoGeometry.m_dpsOrdinates[0],pP1->x,pP1->y,pP2->x,pP2->y);
			}
			break;
		case GEO_TYPE_GEOPOLYLINE:
			{
				//hls added 20091205	
				return IsRectAndPolyLineIntersectWith(pP1->x,pP1->y,pP2->x,pP2->y,&(m_sdoGeometry.m_dpsOrdinates),m_sdoGeometry.m_dpsOrdinates.size());
			}
			break;
		case GEO_TYPE_GEOPOLYGON:
			{
				return IsRectAndPolygonIntersectWith(pP1->x,pP1->y,pP2->x,pP2->y,&(m_sdoGeometry.m_dpsOrdinates),m_sdoGeometry.m_dpsOrdinates.size(),&(m_sdoGeometry.m_ivRingFrameCntLst),m_sdoGeometry.m_ivRingFrameCntLst.size());
			}
			break;
		case GEO_TYPE_GEOANNOTATION:
			{
				//hls added 20091205//判断1点2点多点都兼容
				return IsRectAndPolyLineIntersectWith(pP1->x,pP1->y,pP2->x,pP2->y,&(m_sdoGeometry.m_dpsOrdinates),m_sdoGeometry.m_dpsOrdinates.size());
			}
			break;
		case GEO_TYPE_GEORECT:
			{			
			}
			break;
		default:
			break;
		}
		return false;
	}
	//是否被多边形选取(该要素与多边形内区域有相交部分)
	//##ModelId=4829521C00AB
	bool IsSelectedByPolygon(SPo_DPoint *pPoints,int nPointCount)
	{
		switch(m_nType)
		{
		case GEO_TYPE_GEOPOINT:
			{
			}
			break;
		case GEO_TYPE_GEOPOLYLINE:
			{
			}
			break;
		case GEO_TYPE_GEOPOLYGON:
			{				
			}
			break;
		case GEO_TYPE_GEOANNOTATION:
			{
			}
			break;
		case GEO_TYPE_GEORECT:
			{			
			}
			break;
		default:
			break;
		}
		return false;
	}
	//是否被多边形选取(该要素与多边形内区域有相交部分)
	//##ModelId=4829521C0109
	bool IsSelectedByPolygon(vector<SPo_DPoint *> *pPtrPointsList)
	{
		switch(m_nType)
		{
		case GEO_TYPE_GEOPOINT:
			{
			}
			break;
		case GEO_TYPE_GEOPOLYLINE:
			{
			}
			break;
		case GEO_TYPE_GEOPOLYGON:
			{				
			}
			break;
		case GEO_TYPE_GEOANNOTATION:
			{
			}
			break;
		case GEO_TYPE_GEORECT:
			{			
			}
			break;
		default:
			break;
		}
		return false;
	}
	//是否被折线缓冲区选取(该要素与折线缓冲区有相交部分)
	//##ModelId=4829521C0148
	bool IsSelectedByPolyglineBuffer(SPo_DPoint *pPoints,int nPointCount,float fTolerance/*选取距离的阈值*/)
	{
		switch(m_nType)
		{
		case GEO_TYPE_GEOPOINT:
			{
			}
			break;
		case GEO_TYPE_GEOPOLYLINE:
			{
			}
			break;
		case GEO_TYPE_GEOPOLYGON:
			{				
			}
			break;
		case GEO_TYPE_GEOANNOTATION:
			{
			}
			break;
		case GEO_TYPE_GEORECT:
			{			
			}
			break;
		default:
			break;
		}
		return false;
	}
	//是否被折线缓冲区选取(该要素与折线缓冲区有相交部分)
	//##ModelId=4829521C01C5
	bool IsSelectedByPolyglineBuffer(vector<SPo_DPoint *> *pPtrPointsList,float fTolerance/*选取距离的阈值*/)
	{
		switch(m_nType)
		{
		case GEO_TYPE_GEOPOINT:
			{
			}
			break;
		case GEO_TYPE_GEOPOLYLINE:
			{
			}
			break;
		case GEO_TYPE_GEOPOLYGON:
			{				
			}
			break;
		case GEO_TYPE_GEOANNOTATION:
			{
			}
			break;
		case GEO_TYPE_GEORECT:
			{			
			}
			break;
		default:
			break;
		}
		return false;
	}
	void PlnSetCentralPoint(SPo_DPoint sPoint,IPo_SpatialReference* pSpatialReference=NULL)
	{
		m_sdoGeometry.PlnSetCentralPoint(sPoint,pSpatialReference);
	}
	bool IsIntersect(double x1,double y1,double x2,double y2/*组成矩形的两个点坐标*/)
	{
		return m_sdoGeometry.IsIntersect(x1,y1,x2,y2);
	};
	bool PllHitTest(SPo_DPoint sPoint, POINT &ipHit/*捕获细节，x,y分别表示断点前后节点序号，必定相邻或者相等*/,SPo_DPoint2D &dptConn/*线路径上的捕获断点*/,double dTolerance/* = 0.0*/)
	{
		return m_sdoGeometry.PllHitTest(sPoint,ipHit,dptConn,dTolerance);
	};
	bool PllReverse()
	{
		return m_sdoGeometry.PllReverse();
	};
	//增加一个环的点数
	bool PlnAppendRingPoints(int iVal)
	{
		return m_sdoGeometry.PlnAppendRingPoints(iVal);
	};
	void PlnClearRings()
	{
		m_sdoGeometry.PlnClearRings();
	};
	bool PlnCloseAll()
	{
		return m_sdoGeometry.PlnCloseAll();
	};
	void RetrieveSpatialElemInfo(bool bCoordReset = true/*是否重因勾环按顺逆时针方向新组织坐标点*/)
	{
		m_sdoGeometry.RetrieveSpatialElemInfo(bCoordReset);
	}	
	//获取环的总个数
	//##ModelId=46AF583200FA
	int PlnGetRingsCount()
	{
		return m_sdoGeometry.PlnGetRingsCount();
	}
};
//brief
//     基本几何对象——几何对象基类接口。
//		
//		不管内部设置了何种空间参考系,几何对象内部存储的坐标全部是地理经纬度秒
//		x:经度秒;y纬度秒
//     用于获取和设置几何对象的相关信息。
//     与一个特定类型的几何对象关联，可经特定几何    对象指针转换为某一具体的几何对象。
//##ModelId=4B2B8A72005D
class IGeo_Geometry : public IPo_Unknown
{
  public:
    //brief
    //     获取几何对象类型
    // 
    //     可根据该类型利用该类型的几何对象指针将基本    几何对象转换为该类型的几何对象。
    //return
    //     几何对象的类型
    //##ModelId=4B2B8A72005F
    virtual int GetGeoType() = 0;

    //brief
    //     设置几何对象的空间参考系
    //return
    //     空间参考系设置成功返回true，否则返回false。
	//		内部坐标不进行任何转换
    //param
    //     pSpatialReference: 要设置的空间参考系。缺省    为NULL，表示使用点本身的空间参考系。
    //##ModelId=4B2B8A72006E
    virtual bool SetSpatialReference(IPo_SpatialReference* pSpatialReference) = 0;

    //brief
    //     获取几何对象的空间参考系
    //return
    //     空间参考系指针
    //##ModelId=4B2B8A720071
    virtual IPo_SpatialReference* GetSpatialReferencePtr() = 0;

    //brief
    //     获取几何对象的维度
    //return
    //     几何对象的维度
    //##ModelId=4B2B8A720073
    virtual char GetDimension() = 0;

    //brief
    //     获取几何对象的定位点个数
    //return
    //     几何对象的定位点个数
    //##ModelId=4B2B8A720075
    virtual int GetPointCount() = 0;

    //brief
    //     获取几何对象的定位点
    //     根据下标和指定空间参考系获取定位点坐标
    //     0<=nIndex<定位点个数，若输入其它值则返回    SPo_Point(0,0)。
    //return
    //     SPo_Point 定位点坐标
    //param
    //     nIndex: 定位点的下标
    //     pSpatialReference: 希望获取的定位点对应的空间参考系。缺省为NULL，表示使用几何对象本身
	//		取出的坐标要按照给出的pSpatialReference进行坐标转换
	//		即返回的坐标已经是pSpatialReference下的坐标
    // 的空间参考系。
    //##ModelId=4B2B8A720077
    virtual SPo_DPoint GetPoint(int nIndex, IPo_SpatialReference* pSpatialReference = NULL) = 0;

    //brief
    //     成批获取定位点坐标。
    //     根据给定的所需获得的定位点的个数和采样容限    值成批获取定位点坐标。
    //return
    //     实际获得的定位点个数(<= nPointCount)。
    //param
    //     nPointCount: 所需获取的定位点个数。
    //     pPoints: 输出参数，实际获得的定位点坐标。
    //     pSpatialReference: 希望获取的定位点对应的空    间参考系。缺省为NULL，表示使用几何对象本身
    // 的空间参考系。
	//		取出的坐标要按照给出的pSpatialReference进行坐标转换
	//		即返回的坐标已经是pSpatialReference下的坐标
    //     nTolerance: 采样的容限值。缺省为0，直接获取
    // 前nPointCount个定位点的坐标。(认为它是取坐标串的起始位置，从第nTolerance个坐标开始往后取)
    //##ModelId=4B2B8A72007B
    virtual int GetPoints(int nPointCount, SPo_DPoint* &pPoints) = 0;

    //brief
    //     设置几何对象的最小外接矩形
    //     根据给定的空间参考系设置几何对象的最小外接    矩形
    // /return
    //     最小外接矩形设置是否成功，若    pSpatialReference不为空，且坐标转换不成功，
    // 则返回false，设置成功则返回true。
    //param
    //     rect: 需设置的最小外接矩形,它是pSpatialReference下的坐标,内部进行了坐标转换
    //     pSpatialReference: 最小外接矩形对应的空间参    考系。缺省为NULL，表示使用几何对象本身的空    间参考系。
    //##ModelId=4B2B8A720081
    virtual bool SetMBR(SPo_DRect rect, IPo_SpatialReference* pSpatialReference = NULL) = 0;

    //brief
    //     获取几何对象的最小外接矩形
    //return
    //     几何对象的最小外接矩形
    //param
    //      nMode：获取方式。可能的取值为：
    //      PO_COMPUTE_OFF：不计算，直接返回当前值（缺     省参数设置）
    //      PO_COMPUTE_ON：重新计算
    //      PO_COMPUTE_ONCE：如果没有计算过，则计算；     否则直接返回当前值
    // 		取出的坐标要按照给出的pSpatialReference进行坐标转换
	//		即返回的坐标已经是pSpatialReference下的坐标
    //      pSpatialReference：希望获取的最小外接矩形     所对应的空间参考系。缺省为NULL，表示使用几
    // 何对象本身的空间参考系。
    //##ModelId=4B2B8A720085
    virtual SPo_DRect GetMBR(int nMode = GIS_COMPUTE_OFF, IPo_SpatialReference* pSpatialReference = NULL) = 0;

    //brief
    //     几何对象的复制
    // 
    //     根据给定的几何对象复制相关数据到本几何对象
    // 
    //return
    //     几何对象复制是否成功。
    // 
    //param
    //     pSourceGeo: 源几何对象
    // 
    //     备注:源几何对象与本几何对象的类型必须相同。
    //##ModelId=4B2B8A720089
    //virtual bool Clone(const IGeo_Geometry* pSourceGeo) = 0;// hls deleted 20110107

    //brief
    //     根据 XML 节点构造几何对象。
    //param
    //     szXML: XML 节点字符串
    //##ModelId=4B2B8A72008C
    virtual bool FromXML(const char* szXML) = 0;

    //brief
    //     把几何对象输出成 XML 格式的一个字符串。
    //param
    //     szXML: 输出XML字符串。
    //##ModelId=4B2B8A72008F
    virtual bool ToXML(char* szXML) = 0;

    //brief
    //     测试在指定容限允许的范围内，指定的点是否在    几何对象的范围内，亦即是否点中了该对象。
    //param
    //     sPoint: 指定的点，测试点,它是pSpatialReference下的坐标,内部转换后进行比较
    //     pSpatialReference: 测试点对应的空间参考系。    缺省为NULL，表示使用几何对象本身的空间参考    系。
    //     dTolerance: 阈值，容限值，单位与数据集的单    位相同
	//bSelected:是否已经被选取，如果为true，dTolerance要给值，函数要抓取几何对象的结构点handlepoint，返回值为点序号+1
	//如果为false，dTorlerance不一定要给值，函数要抓取几何对象，返回值为0（没抓住）1（抓住）
	//返回值为0时表示没有抓住对象也没有抓住结构点
    //##ModelId=4B2B8A720092
    virtual int HitTest(SPo_DPoint sPoint,bool bSelected/*是否已经被选取*/,IPo_SpatialReference* pSpatialReference = NULL, double dTolerance = 0.0) = 0;
	
    //brief
    //     是否定义了空的点集
    //return
    //     如果是空，返回true
    //##ModelId=4B2B8A720098
    virtual bool IsEmpty() = 0;

    //brief
    //     清空几何对象。
    //return
    //     清空成功，返回true
    //##ModelId=4B2B8A72009A
    virtual bool SetEmpty() = 0;

    //brief
    //     归档几何对象
    //##ModelId=4B2B8A72009C
    virtual bool Archive(IDS_DataBuffer* pDataBuffer, int iMode, int iType = 0) = 0;

    //brief
    //     获取几何对象的定位点的地址引用
    //     根据下标和指定空间参考系获取定位点坐标
    //     0<=nIndex<定位点个数，若输入其它值则返回    SPo_Point(0,0)。
    //return
    //     SPo_Point 定位点坐标
    //param
    //     nIndex: 定位点的下标
    //     pSpatialReference: 希望获取的定位点对应的空    间参考系。缺省为NULL，表示使用几何对象本身
    // 的空间参考系。如果空间参考系为空,直接给出内部坐标的地址引用,如果有值,则返回pSpatialReference下的坐标的地址
    //##ModelId=4B2B8A7200A1
    virtual SPo_DPoint* GetPointPref(int nIndex, IPo_SpatialReference* pSpatialReference = NULL) = 0;

	//brief
    //     
    //     清除全部定位点
    //     
    //return
    //     
    //param
    //     
    //##ModelId=4B2B8A7200A5
    virtual void ClearPoints() = 0;

    //
	//brief
    //     将几何对象内部数据全部以比特流的形式传出，用于数据调度和缓存，实现不同组件间数据交换
    //     
    //     
    //return
    //     
    //param
    //     ppBytes:用来存储传出的数据，它的内容规定为全部所需的几何对象数据及其数据量的大小，数据量大小按照提供的接口计算
    //   
    //##ModelId=4B2B8A7200A7
    virtual void ToBytes(PBYTE *ppBytes) = 0;

    //
	//brief
    //     将几何对象用外部比特流数据重新装载(由于该接口类是一个虚基类，几何对象在创建时和重新装载数据时类型必须一致)
    //     ##########@@@@@@@@@@@@@@@@@@@@@@!!!!!!!!!!!!!!!!!!!关闭不安全的不可靠的接口
    //     
    //return
    //     
    //param
    //     ppBytes：要重新装载的数据流
    //   
    //##ModelId=46D669CF00EA
    //virtual void FromBytes(PBYTE *ppBytes) = 0;

    //
	//brief
    //     计算几何数据量的字节数大小
    //     //得到存储几何数据需要的字节数总量(包含存储数据大小的4个字节)
    //     
    //return
    //     返回要用字节流存储该几何对象所需的字节数大小
    //param
    //     
    //   
    //##ModelId=4B2B8A7200AA
    virtual size_t WeightGeoDataSize() = 0;
	//brief
    //     获取几何对象细化的单元组信息，一个元组SPo_IPoint(x,y,z),它的含义详见Oracle Spatial Users' Guide-ElementInfo
    //     
    //     
    //return
    //     
    //param
    //     
    //   
    //##ModelId=4B2B8A7200AC
    virtual void RetrieveSpatialElemInfo(bool bCoordReset = true/*是否重因勾环按顺逆时针方向新组织坐标点*/) = 0;

	//获取基于OracleSpatial的基本几何信息
	//##ModelId=4B2B8A7200AF
	virtual LOG_SDOGEOMETRY GetLogOsGeometry() = 0;
	//引用基于OracleSpatial的基本几何信息
	//##ModelId=4B2B8A7200AF
	virtual LOG_BASEGEOMETRY *GetLogBaseGeometryRef() = 0;
	//获取Osgeometry中的m_gPoint中记录的点的指针
	//##ModelId=4B2B8A7200B1
	virtual SPo_DPoint *GetFirstOsGpoint() = 0;
	//////////////////////////////////////////////////////////////////////////
	//是否被单点选取
	//##ModelId=4829521B037A
	virtual bool IsSelectedByPoint(SPo_DPoint *pSel/*点选取的定位坐标*/,float fTolerance/*选取距离的阈值*/) = 0;
	//是否被圆选取(该要素与圆内区域有相交部分)
	//##ModelId=4829521C0000
	virtual bool IsSelectedByCircle(SPo_DPoint *pCenter/*圆选取的圆心点*/,SPo_DPoint *pPointOnCircle/*圆弧上的另一点*/) = 0;
	//是否被矩形选取(该要素与矩形内区域有相交部分)
	//##ModelId=4829521C004E
	virtual bool IsSelectedByRect(SPo_DPoint *pP1/*矩形对角线上的一点*/,SPo_DPoint *pP2/*矩形对角线上的另一点*/) = 0;
	//是否被多边形选取(该要素与多边形内区域有相交部分)
	//##ModelId=4829521C00AB
	virtual bool IsSelectedByPolygon(SPo_DPoint *pPoints,int nPointCount) = 0;
	//是否被多边形选取(该要素与多边形内区域有相交部分)
	//##ModelId=4829521C0109
	virtual bool IsSelectedByPolygon(vector<SPo_DPoint *> *pPtrPointsList) = 0;
	//是否被折线缓冲区选取(该要素与折线缓冲区有相交部分)
	//##ModelId=4829521C0148
	virtual bool IsSelectedByPolyglineBuffer(SPo_DPoint *pPoints,int nPointCount,float fTolerance/*选取距离的阈值*/) = 0;
	//是否被折线缓冲区选取(该要素与折线缓冲区有相交部分)
	//##ModelId=4829521C01C5
	virtual bool IsSelectedByPolyglineBuffer(vector<SPo_DPoint *> *pPtrPointsList,float fTolerance/*选取距离的阈值*/) = 0;
};

//brief
//     几何对象的创建接口
//     
//     
//return
//     创建成功返回true，失败false
//param
//     nType:几何对象的类型定义，参见...\common\geo_commondef.h
//     ppVal:传出创建的几何对象指针的地址
extern "C" __declspec(dllexport) bool CoCreateGeometryObject(int nType,void **ppVal);

//ppBytes的内容规定为全部所需的几何对象数据及其数据量的大小，数据量大小按照提供的接口计算
extern "C" __declspec(dllexport) IGeo_Geometry *CreateGeoObjectFrom1(PBYTE *ppBytes);

//由基于OracleSpatial的基本几何信息创建几何对象
extern "C" __declspec(dllexport) IGeo_Geometry *CreateGeometryIndirect(const LOG_SDOGEOMETRY *pLog);

extern "C" __declspec(dllexport) void Po_GeometryInstance();

extern "C" __declspec(dllexport) void Po_GeometryExitInstance();

#endif /* IGEO_GEOMETRY_H_HEADER_INCLUDED_B9066FDF */
