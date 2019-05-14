#ifndef IGEO_GEOMETRY_H_HEADER_INCLUDED_B9066FDF
#define IGEO_GEOMETRY_H_HEADER_INCLUDED_B9066FDF

class IPo_SpatialReference;
class IDS_DataBuffer;
#include "geo_commondef.h"
#include "..\common\IPo_Unknown.h"

//Oracle Spatial �ж���ļ�������
//---00	δ֪����	�û��Զ���
//---01	������	���ζ������1����
//---02	������	���ζ�����ֱ�߶λ��߶����
//---03	�����	���ζ������һ���Ķ����
//---04	�����ͼ���	�ɰ����������͵ļ�����
//---05	�����	�����ĳ���
//---06	�����	�����ߵĳ���
//---07	��������	�������εĳ���
//---08 ��ʱ��ʾע������
//---��2001��ʾ��ά�����е�һ����;3002��ʾ��ά�����е�һ��
//ֱ��
//��Po_GeometryObject�еļ��ζ�������ת��Po_Gde�У�OracleSpatial���ļ��ζ�������
//##ModelId=46EDE88800AB
extern "C" __declspec(dllexport) int POGEO_TYPE3_OSPTGEO(int pogeotype);

//��Po_Gde�У�OracleSpatial���ļ��ζ�������ת��Po_GeometryObject�еļ��ζ�������
//##ModelId=46EDE88800BB
extern "C" __declspec(dllexport) int OSPTGEO_TYPE3_POGEO(int osptgeotype);

struct LOG_SDOGEOMETRY;
class IGeo_Geometry;
struct LOG_SDOGEOMETRY;


//##ModelId=4B2B8A7103D8
struct LOG_SDOGEOMETRY
{
	//���ζ��������룬����Oracle Spatial�����������
	//##ModelId=4B2B8A7103DA
	int m_nSrid;
	//OracleSpatial �ļ��ζ������ʹ���
	//##ModelId=4B2B8A720000
	int      m_nGtype;              //��������	
	//��Ҫ�ؼ�¼�����ꣻ��Ҫ�ر�������Ҫ�ؼ�¼�����********
	//##ModelId=4B2B8A720002
	SPo_DPoint  m_gPoint;
	//���ζ�������㴮����,�洢�������ݡ�//��Ҫ�ر�������Ҫ�غ���Ҫ�ؼ�¼�����괮
	//##ModelId=4B2B8A720021
	vector<SPo_DPoint> m_dpsOrdinates; 
public:
	//�洢ͼԪ����
	//##ModelId=4B2B8A7102D1
	vector<SPo_IPoint> m_ipsElmInfos;
	
	//��յ�����ɵ�����������������������ǵĵ����ֱ�3��6��
	//9��20��58��Ҳ���Ը��ݴ�����õ���������
	//##ModelId=4B2B8A7102F1
	vector<int> m_ivRingFrameCntLst;
	
	//##ModelId=4B2B8A7102FE
	SPo_DRect m_rMBR;
	
	//##ModelId=4B2B8A720025
	LOG_SDOGEOMETRY()
	{
		m_nGtype=0;m_nSrid=0;//�������Ĭ��ֵ���0
	};
	//##ModelId=4B2B8A720026
	~LOG_SDOGEOMETRY(){};

	//��д������ʼ������
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
    // \brief �������
    // 
    // \return �����ȣ��򷵻�1�����򣬷���0��
    // 
    // \param right����������Ҳ�����
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
	
    // \brief ���������
    // 
    // \return �������ȣ��򷵻�1�����򣬷���0��
    // 
    // \param right������������Ҳ�����
    //##ModelId=4B2B8A720030
    bool operator!=(const LOG_SDOGEOMETRY &right)
	{return !(*this == right) ;};
	
    
    // \brief ��ֵ����
    // 
    // \return ��ǰ��ṹ������
    // 
    // \param right����ֵ�����Ҳ�����
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
	bool IsIntersect(double x1,double y1,double x2,double y2/*��ɾ��ε�����������*/)
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
			//if(!(m_pSpref == pSpatialReference || (pSpatialReference == NULL)))//����ϵ��ͶӰ��ͬ����Ҫ��������ת��
			//{
			//	//֮��������ת����д����.
			//	
			//}
			pval->Offset(dOffsetPoint);
		}
	};
	bool PllHitTest(SPo_DPoint sPoint, POINT &ipHit/*����ϸ�ڣ�x,y�ֱ��ʾ�ϵ�ǰ��ڵ���ţ��ض����ڻ������*/,SPo_DPoint2D &dptConn/*��·���ϵĲ���ϵ�*/,double dTolerance/* = 0.0*/)
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
				
				return true;// ipt+1;//ץס�˽ṹ�㣬���ص����+1
			}
		}
		if(pstCount>1)//��û���ҵ��ϵ�
		{
			SPo_DPoint *pPreOrd=NULL;SPo_DPoint*pCurOrd=NULL;
			for(ipt=0;ipt<pstCount-1;ipt++)
			{
				pPreOrd = m_dpsOrdinates.begin()+ipt;pCurOrd = m_dpsOrdinates.begin()+ipt+1;
				if(CalDistancePointLine(sPoint.x,sPoint.y,pPreOrd->x,pPreOrd->y,pCurOrd->x,pCurOrd->y)<=dTolerance)//�����ˣ���
				{//�����ˣ���ֱ��m_dpsOrdinates[ipt];m_dpsOrdinates[ipt+1]���ϵĺ͵�sPoint��ֱ�Ĵ���
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
			int iflag = 0;int nCnt = (nPts/2);//ѭ������
			for(int i = 0;i<nCnt;i++,iflag++)
			{//iflag �� nPts-iflag-1�����滻
				dPtTemp = *(m_dpsOrdinates.begin()+iflag);
				*(m_dpsOrdinates.begin()+iflag) = *(m_dpsOrdinates.begin()+(nPts-iflag-1));
				*(m_dpsOrdinates.begin()+(nPts-iflag-1)) = dPtTemp;
			}
			return true;
		}
		return false;
	};
	//����һ�����ĵ���
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
		case GIS_COMPUTE_ON:// 1002�����¼���
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
		case GIS_COMPUTE_ONCE://1003�����û�м����������㣻  ����ֱ�ӷ��ص�ǰֵ
			if( m_rMBR.bottom == 0&&
				m_rMBR.top == 0&&
				m_rMBR.left == 0&&
				m_rMBR.right == 0)
			{
				m_rMBR = GetMBR(GIS_COMPUTE_ON,pSpatialReference);
			}
			break;
		default://GIS_COMPUTE_OFF//��1001���������������㣬ֱ�ӷ��ص�ǰֵ��ȱ     ʡ�������ã�
			break;
		}
		//if(!(m_pSpref == pSpatialReference || (pSpatialReference == NULL)))//����ϵ��ͶӰ��ͬ����Ҫ��������ת��
		//{
		
		//}
		return m_rMBR;
	};
	SPo_DRect *GetMBRref(int nMode  = GIS_COMPUTE_OFF , IPo_SpatialReference* pSpatialReference  = NULL)
	{
		//	switch(nMode) 
		//	{
		//	case GIS_COMPUTE_ON:// 1002�����¼���
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
		//	case GIS_COMPUTE_ONCE://1003�����û�м����������㣻  ����ֱ�ӷ��ص�ǰֵ
		//		if( m_rMBR.bottom == 0&&
		//			m_rMBR.top == 0&&
		//			m_rMBR.left == 0&&
		//			m_rMBR.right == 0)
		//		{
		//			m_rMBR = GetMBR(GIS_COMPUTE_ON,pSpatialReference);
		//		}
		//		break;
		//	default://GIS_COMPUTE_OFF//��1001���������������㣬ֱ�ӷ��ص�ǰֵ��ȱ     ʡ�������ã�
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
		else if((m_nGtype%1000)==3)/////////////////////////////////hls added 20080620Ϊ�洢�����������޸�
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
		else if((m_nGtype%1000)==3)/////////////////////////////////hls added 20080620Ϊ�洢�����������޸�
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
		GetMBR(GIS_COMPUTE_ON);/////���¼�����Ӿ���
		return pos;
	};

	//##ModelId=4B2B8A720042
	size_t ToBytes(PBYTE * ppBytes)
	{
		size_t pos = 0;	size_t dtsize = 0;
		pos += _cwrite(&dtsize,sizeof(size_t),1,(*ppBytes)+pos);	
		pos += _cwrite(&m_nGtype,sizeof(int),1,(*ppBytes)+pos);
		pos += _cwrite(&m_nSrid,sizeof(int),1,(*ppBytes)+pos);
		if((m_nGtype%1000) == 1)//ȫ��������ά����
		{
			pos += _cwrite(&m_gPoint.x,sizeof(double),1,(*ppBytes)+pos);
			pos += _cwrite(&m_gPoint.y,sizeof(double),1,(*ppBytes)+pos);
			pos += _cwrite(&m_gPoint.z,sizeof(double),1,(*ppBytes)+pos);
		}
		else if((m_nGtype%1000)==3)/////////////////////////////////hls added 20080620Ϊ�洢�����������޸�
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
			if(pSpatialReference&&(pProjCoordSys = pSpatialReference->GetProjCoordSysPtr())&&(ppParameters = pProjCoordSys->GetParameters()))//ָ���˿ռ�ο�ϵ����Ҫ��������ת��
			{	//֮��������ת����д����.-----����ת��
				PRJCOORIDATE ProCoord;/*ͶӰ����*/					GEOCOORIDATE GeoCoord;/*��������*/
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
			//if(!(m_pSpref == pSpatialReference || (pSpatialReference == NULL)))//����ϵ��ͶӰ��ͬ����Ҫ��������ת��
			//{
			//	//֮��������ת����д����.
			//	
			//}
		}
		return pval;
	};
	int GetPoints(int nPointCount, SPo_DPoint* & pPoints, IPo_SpatialReference* pSpatialReference = NULL, int nTolerance = 0)
	{
		int len = m_dpsOrdinates.size();	if(!(nTolerance<len))		return 0;//ȡֵ����û���� ����
		
		int returncnt = ((returncnt = len-nTolerance)>nPointCount?nPointCount:returncnt);//���ظ���ȡС
		
		if(returncnt<1)						return 0;
		//�������Ѿ�����
		
		for(int i = 0;i<returncnt;i++)
		{
			pPoints[i] = m_dpsOrdinates[nTolerance + i];
		}
		
		return static_cast<int>(returncnt);
	};
	unsigned int HitTest(SPo_DPoint sPoint, bool bSelected/*�Ƿ��Ѿ���ѡȡ*/,double dTolerance=0)
	{
		int pstCount = m_dpsOrdinates.size();
		if(pstCount==0)	return 0;
		int ipt = 0;
		if(bSelected)//Ҫץȡ�ṹ��
		{
			for(ipt=0;ipt<pstCount;ipt++)
			{
				if((m_dpsOrdinates[ipt].x+dTolerance>=sPoint.x&&sPoint.x>=m_dpsOrdinates[ipt].x-dTolerance)&&
					(m_dpsOrdinates[ipt].y+dTolerance>=sPoint.y&&sPoint.y>=m_dpsOrdinates[ipt].y-dTolerance))
					return ipt+1;//ץס�ˣ����ص����+1
			}
			return 0;//û��ץס
		}
		else//Ҫץȡ������
		{
			int nType = this->GetGeoType();
			switch(nType)
			{
			case GEO_TYPE_GEOPOINT:
				{				
					SPo_DPoint ptTgt = m_dpsOrdinates[0];
					//ѡ�����������򣿣������ٶȿ�(��ά��)
					return ((m_dpsOrdinates[0].x+dTolerance>=sPoint.x&&sPoint.x>=m_dpsOrdinates[0].x-dTolerance)&&
						(m_dpsOrdinates[0].y+dTolerance>=sPoint.y&&sPoint.y>=m_dpsOrdinates[0].y-dTolerance));
					//ѡ��Բ�����򣿣�����ȷ���������(��ά��)
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
						
						int iPtor = 0;int i=0;			int lwP=0;//��¼�봹�������ӳ�ʱ��ߵĽ������
						
						for(int r=0;r<rgncount;r++)
						{	////////
							for(i=1;i<m_ivRingFrameCntLst[r];i++)
							{
								ppre = m_dpsOrdinates.begin()+iPtor+i-1;	pthp = m_dpsOrdinates.begin()+iPtor+i;
								if(!(pthp->x==ppre->x&&pthp->y==ppre->y))//�����м���غϽ��,���ǰһ�㲻���ں�һ��;
								{
									if(((sPoint.x-pthp->x==0)&&(sPoint.y-pthp->y==0))||((sPoint.x-ppre->x==0)&&(sPoint.y-ppre->y==0)))
										return true;//��ڵ��غ�,����������Ϊ���ڲ�//20160803
									else
									{
										if ( pthp->x == ppre->x || // p1p2 �� y=p0.yƽ�� 
											sPoint.x < min(ppre->x, pthp->x) || // ������p1p2�ӳ����� 
											sPoint.x >= max(ppre->x, pthp->x) ) // ������p1p2�ӳ����� 
											continue; 						
										if ((pthp->x-ppre->x)*((pthp->y-ppre->y)*(sPoint.x-ppre->x)-(pthp->x-ppre->x)*(sPoint.y-ppre->y))<0) 
											lwP++; // ֻͳ�Ƶ��߽��� 
									}
								}
							}
							////////
							iPtor += m_ivRingFrameCntLst[r];
						}				
						return (lwP%2)==1?true:false;	//����������true//����ż����false
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
						for(ipt=0;ipt<pstCount;ipt++)//��������ע�ǵ������������񣬲ο���Ҫ�صĲ��񷽷�
						{
							if((m_dpsOrdinates[ipt].x+dTolerance>=sPoint.x&&sPoint.x>=m_dpsOrdinates[ipt].x-dTolerance)&&
								(m_dpsOrdinates[ipt].y+dTolerance>=sPoint.y&&sPoint.y>=m_dpsOrdinates[ipt].y-dTolerance))
								return 1;//ץס�ˣ�����1
						}
						return 0;//û��ץס
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
	//    ��ȡ���ζ���Ķ�λ�����
	////return
	//    ���ζ���Ķ�λ�����
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
			//���¼�����Ӿ���
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
		
		if(scnt>=2&&(m_nGtype == GEO_TYPE_GOS2POINT||m_nGtype == GEO_TYPE_GOS3POINT))///////////////����ǵ�Ҫ��
			return false;
		
		if(scnt==0)//��һ����Ӽ�������
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
	void RetrieveSpatialElemInfo(bool bCoordReset = true/*�Ƿ����򹴻���˳��ʱ�뷽������֯�����*/)
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
		
				if(m_dpsOrdinates.size()<4)	return ;//����ζ�λ�����>=4
				
				PlnCloseAll();//�պϻ�
				int ringcnt = m_ivRingFrameCntLst.size();
				if(ringcnt==0)	return ;
				bool *bPositive = new bool[ringcnt];//�Ƿ�˳ʱ�뷽�������
				SPo_DRect *pMBRs = new SPo_DRect[ringcnt];//������Ӿ���
				bool *bExtRing = new bool[ringcnt];//���л��������ͱ�־�����boolֵ��1003�����⻷��2003�����ڻ�
				for(int mmm=0;mmm<ringcnt;mmm++)
					bExtRing[mmm]=true;//��ʼ����Ϊ�������⻷����������ż����(include 0)�����⻷�����������������ڻ�

				int iPtor = 0;/*���������������*/	int iRingIndex = 0;	int ii=0;int jj=0;
				vector<int>::iterator itr = m_ivRingFrameCntLst.begin();
				//==============�������л�����Ӿ���*******
				for(itr = m_ivRingFrameCntLst.begin(),iRingIndex = 0;itr!=m_ivRingFrameCntLst.end();itr++,iRingIndex++)
				{
					//�������괮�еĵ�itr����
					for(int i=0;i<(*itr);i++)//
					{
						//=====================================������Ӿ���--------***********************************
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
				//============================�������Ӿ��η��ڵ�һ��==========********************************
				int maxMBRindex = 0;
				for(ii=0;ii<ringcnt;ii++)
				{
					for(jj=0;jj<ringcnt;jj++)
					{
						pMBRs[jj].IsWithin(&pMBRs[ii])?maxMBRindex=ii:maxMBRindex=jj;
					}
				}
				if(maxMBRindex>0)//�������������������Ӿ��ε��⻷���ڵ�һ��==========********************************
				{
				}
				//======================================����˳������ʱ�뷽��------******************************
				for(itr = m_ivRingFrameCntLst.begin(),iRingIndex = 0,iPtor = 0;itr!=m_ivRingFrameCntLst.end();itr++,iRingIndex++)
				{
					double anglesum = 0;
					//�������괮�еĵ�itr����
					for(int i=0;i<(*itr);i++)//
					{
						if(i>1)
						{
							//����m_dpsOrdinates[iPtor+i-2],m_dpsOrdinates[iPtor+i-1],m_dpsOrdinates[iPtor+i]
							anglesum += GetDirAngle3(m_dpsOrdinates[iPtor+i-2].x,m_dpsOrdinates[iPtor+i-2].y,
													 m_dpsOrdinates[iPtor+i-1].x,m_dpsOrdinates[iPtor+i-1].y,
													 m_dpsOrdinates[iPtor+i].x,m_dpsOrdinates[iPtor+i].y);
						}
					}
					bPositive[iRingIndex] = (anglesum<(((*itr)-2)*PO_PI)?false:true);
					
					iPtor += (*itr);
				}
				//==========================================����iRingIndex�����������ǵ������ڻ������⻷***************	
				//�Կ�ʼ����Ϊ�������⻷����������ż���ζ����⻷�����������������ڻ�
				for(ii = 0;ii<ringcnt/*iRingIndex*/;ii++)
				{
					for(jj=0;jj<ringcnt/*iRingIndex*/;jj++)
					{
						if(ii==jj)	continue;
						pMBRs[ii].IsWithin(&pMBRs[jj])?(bExtRing[ii]=(!bExtRing[ii])):0;
					}
				}//=====================================================================================***************
				//==========================================�������⻷���괮˳��ͬʱ�����Ԫ����Ϣ*******************
				iPtor = 0;/*���������������*/SPo_DPoint dptemp;
				for(ii=0;ii<iRingIndex;ii++)//������
				{
					if(bExtRing[ii])//���⻷,���������ʱ������(�������괮Ҫ���µ���)
					{
						if(bPositive[ii])//ż���α�ʾ�⻷,���������ʱ������(�������괮Ҫ���µ���)
						{
							//if(!bCoordReset)	//���������

							for(jj=0;bCoordReset&&(jj<m_ivRingFrameCntLst[ii]/2);jj++)//m_ivRingFrameCntLst[ii]��ii�����������
							{
								dptemp = m_dpsOrdinates[iPtor+jj];
								m_dpsOrdinates[iPtor+jj].x = m_dpsOrdinates[iPtor+m_ivRingFrameCntLst[ii]-jj-1].x;
								m_dpsOrdinates[iPtor+jj].y = m_dpsOrdinates[iPtor+m_ivRingFrameCntLst[ii]-jj-1].y;
								//*(m_dpsOrdinates[iPtor+jj]) = *(m_dpsOrdinates[iPtor+m_ivRingFrameCntLst[ii]-jj-1]);

								(m_dpsOrdinates[iPtor+m_ivRingFrameCntLst[ii]-jj-1]) = dptemp;
							}
						}			
					}
					else//���ڻ�
					{
						if(!bPositive[ii])//�����α�ʾ�ڻ�,�������˳ʱ������(�������괮Ҫ���µ���)
						{
							//if(!bCoordReset)	//���������
							for(jj=0;bCoordReset&&(jj<m_ivRingFrameCntLst[ii]/2);jj++)//m_ivRingFrameCntLst[ii]��ii�����������
							{
								dptemp = m_dpsOrdinates[iPtor+jj];
								m_dpsOrdinates[iPtor+jj].x = m_dpsOrdinates[iPtor+m_ivRingFrameCntLst[ii]-jj-1].x;
								m_dpsOrdinates[iPtor+jj].y = m_dpsOrdinates[iPtor+m_ivRingFrameCntLst[ii]-jj-1].y;
								//*(m_dpsOrdinates[iPtor+jj]) = *(m_dpsOrdinates[iPtor+m_ivRingFrameCntLst[ii]-jj-1]);
								m_dpsOrdinates[iPtor+m_ivRingFrameCntLst[ii]-jj-1] = dptemp;
							}
						}
					}
					//==============================���һ��Ԫ��
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
					*Iptref = SPo_IPoint(1,2,1);//��Ϊ��ֱ�߶ε��ߴ�
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
			m_ivRingFrameCntLst.clear();//���
			int ptscnt = m_dpsOrdinates.size();
			SPo_DPoint ptCloser;
			int ecnt = 0;
			for(vector<SPo_DPoint>::iterator itr = m_dpsOrdinates.begin();itr!=m_dpsOrdinates.end();itr++)
			{
				ecnt ++;//δ��տ�ʼ����
				
				if(ecnt == 1)	ptCloser = ((*itr));//���
				else
				{
					if(ptCloser == ((*itr))&&ecnt>2)//�ҵ�һ����յ�
					{
						int icnt = 0;
						m_ivRingFrameCntLst.push_back(icnt);
						int *ivalref = (m_ivRingFrameCntLst.end()-1);
						*ivalref = ecnt;
						ecnt = 0;
					}
				}
			}
			if(ecnt>0)//��δ��յĶ������
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
				//if(!(m_pSpref == pSpatialReference || (pSpatialReference == NULL)))//����ϵ��ͶӰ��ͬ����Ҫ��������ת��
				//{
				//	//��sPoint���������ת��,�浽ptval��
				//	//...
				//}
				//else//�ռ�ο�ϵ��ָ������ͬ
				//{
				//}
				m_dpsOrdinates.push_back(tval);
				SPo_DPoint *pntref = (m_dpsOrdinates.end()-1);
				*pntref = tval;
				setval = true;
			}
			else//����������
			{
				tval = m_dpsOrdinates[1];
				//if(!(m_pSpref == pSpatialReference || (pSpatialReference == NULL)))//����ϵ��ͶӰ��ͬ����Ҫ��������ת��
				//{
				//	//��sPoint���������ת��,�浽ptval��
				//	//...
				//}
				//else//�ռ�ο�ϵ��ָ������ͬ
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
		
		if(iIndex == 0)//Ҫ���õ�һ��
		{
			if(ptcnt==0)//ԭ��û�е�
			{
				//if(!(m_pSpref == pSpatialReference || (pSpatialReference == NULL)))//����ϵ��ͶӰ��ͬ����Ҫ��������ת��
				//{
				//	//��sPoint���������ת��,�浽ptval��
				//	//...
				//}
				m_dpsOrdinates.push_back(sPoint);
				SPo_DPoint *pntref = (m_dpsOrdinates.end()-1);
				*pntref = sPoint;
				setval = true;
			}
			else//ԭ����һ��������
			{			
				SPo_DPoint *ptval = &(m_dpsOrdinates[0]);
				*ptval = sPoint;
				//if(!(m_pSpref == pSpatialReference || (pSpatialReference == NULL)))//����ϵ��ͶӰ��ͬ����Ҫ��������ת��
				//{
				//	//��sPoint���������ת��,�浽ptval��
				//	//...
				//}
				setval = true;	
			}
			///������Ӿ���
			m_rMBR.bottom = m_rMBR.top = sPoint.y;
			m_rMBR.right = m_rMBR.left = sPoint.x;
		}
		else if(iIndex == 1)//Ҫ���õڶ���
		{
			if(ptcnt==0)//ԭ��û�е�
			{
				SPo_DPoint	spt;
				m_dpsOrdinates.push_back(spt);//����һ��Ĭ�ϵ�
				//�ڶ���ķ����
				SPo_DPoint *ptval = &sPoint;
				//if(!(m_pSpref == pSpatialReference || (pSpatialReference == NULL)))//����ϵ��ͶӰ��ͬ����Ҫ��������ת��
				//{
				//	//��sPoint���������ת��,�浽ptval��
				//	//...
				//}
				m_dpsOrdinates.push_back(*ptval);
				SPo_DPoint *pntref = (m_dpsOrdinates.end()-1);
				*pntref = (*ptval);
				setval = true;
			}
			else if(ptcnt == 1)//ԭ����һ����
			{
				//�ڶ���ķ����
				SPo_DPoint *ptval = &sPoint;
				//if(!(m_pSpref == pSpatialReference || (pSpatialReference == NULL)))//����ϵ��ͶӰ��ͬ����Ҫ��������ת��
				//{
				//	//��sPoint���������ת��,�浽ptval��
				//	//...
				//}
				m_dpsOrdinates.push_back(*ptval);
				SPo_DPoint *pntref = (m_dpsOrdinates.end()-1);
				*pntref = (*ptval);
				
				setval = true;
			}
			else//��������������
			{			
				SPo_DPoint *ptval = &(m_dpsOrdinates[1]);
				*ptval = sPoint;
				//if(!(m_pSpref == pSpatialReference || (pSpatialReference == NULL)))//����ϵ��ͶӰ��ͬ����Ҫ��������ת��
				//{
				//	//��sPoint���������ת��,�浽ptval��
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
    // \brief ��ֵ����
    // 
    // \return ��ǰ��ṹ������
    // 
    // \param right����ֵ�����Ҳ�����
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
	//���㼸�����������ֽ�����С
	size_t GetBytesLength()
	{
		return m_sdoGeometry.GetBytesLength();
	};
	//ppBytes�����ݹ涨Ϊȫ������ļ��ζ������ݼ����������Ĵ�С����������С�����ṩ�Ľӿڼ���
	//##ModelId=46D66A84036B
	size_t ToBytes(PBYTE * ppBytes)
	{
		int gtype = POGEO_TYPE3_OSPTGEO(m_nType);//�ڲ���������תΪOracle Spatial ����
		m_sdoGeometry.m_nGtype = gtype;
		return m_sdoGeometry.ToBytes(ppBytes);
	}
	//ppBytes�����ݹ涨Ϊȫ������ļ��ζ������ݼ����������Ĵ�С����������С�����ṩ�Ľӿڼ���
	//##ModelId=46D66A84036D
	size_t FromBytes(PBYTE * ppBytes)
	{
		size_t szpos = m_sdoGeometry.FromBytes(ppBytes);
		m_nType = OSPTGEO_TYPE3_POGEO(m_sdoGeometry.m_nGtype);//Oracle Spatial ����תΪ�ڲ���������
		return szpos;
	}
	//���ȫ����λ��
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
	//���ڲ�������
	////brief
	//    ��ȡ���ζ�������
	//
	//    �ɸ��ݸ��������ø����͵ļ��ζ���ָ�뽫����    
	//���ζ���ת��Ϊ�����͵ļ��ζ���
	////return
	//    ���ζ��������
	//##ModelId=464AC3550178
	int GetGeoType()
	{
		return m_nType;
	}

	//���ڲ�������
	////brief
	//    ��ȡ���ζ������С��Ӿ���
	////return
	//    ���ζ������С��Ӿ���
	////param
	//     nMode����ȡ��ʽ�����ܵ�ȡֵΪ��
	//     PO_COMPUTE_OFF�������㣬ֱ�ӷ��ص�ǰֵ��ȱ     
	//ʡ�������ã�
	//     PO_COMPUTE_ON�����¼���
	//     PO_COMPUTE_ONCE�����û�м����������㣻     
	//����ֱ�ӷ��ص�ǰֵ
	//
	//     pSpatialReference��ϣ����ȡ����С��Ӿ���     
	//����Ӧ�Ŀռ�ο�ϵ��ȱʡΪNULL����ʾʹ�ü�     
	//�ζ�����Ŀռ�ο�ϵ��
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
	//    ��ȡ���ζ���Ķ�λ��
	//    �����±��ָ���ռ�ο�ϵ��ȡ��λ������
	//    0<=nIndex<��λ�����������������ֵ�򷵻�    
	//SPo_Point(0,0)��
	////return
	//    SPo_Point ��λ������
	////param
	//    nIndex: ��λ����±�
	//    pSpatialReference: ϣ����ȡ�Ķ�λ���Ӧ�Ŀ�    
	//��ο�ϵ��ȱʡΪNULL����ʾʹ�ü��ζ�����    
	//�Ŀռ�ο�ϵ��
	//##ModelId=464AC3550188
	SPo_DPoint GetPoint(int nIndex, IPo_SpatialReference* pSpatialReference = NULL)
	{
		return m_sdoGeometry.GetPoint(nIndex,pSpatialReference);
	};

	//brief
    //     ��ȡ���ζ���Ķ�λ��ĵ�ַ����
    //     �����±��ָ���ռ�ο�ϵ��ȡ��λ������
    //     0<=nIndex<��λ�����������������ֵ�򷵻�    SPo_Point(0,0)��
    //return
    //     SPo_Point ��λ������
    //param
    //     nIndex: ��λ����±�
    //     pSpatialReference: ϣ����ȡ�Ķ�λ���Ӧ�Ŀ�    ��ο�ϵ��ȱʡΪNULL����ʾʹ�ü��ζ�����
    // �Ŀռ�ο�ϵ��
    //##ModelId=46AF5833030D
    SPo_DPoint *GetPointPref(int nIndex, IPo_SpatialReference* pSpatialReference = NULL)
	{
		return m_sdoGeometry.GetPointPref(nIndex,pSpatialReference);		
	}

	////brief
	//    ��ȡ���ζ���Ķ�λ�����
	////return
	//    ���ζ���Ķ�λ�����
	//##ModelId=464AC3550196
	int GetPointCount()
	{
		return m_sdoGeometry.GetPointCount();
	}
	//brief
    //     ������ȡ��λ�����ꡣ
    //     ���ݸ����������õĶ�λ��ĸ����Ͳ�������    ֵ������ȡ��λ�����ꡣ
    //return
    //     ʵ�ʻ�õĶ�λ�����(<= nPointCount)��
    //param
    //     nPointCount: �����ȡ�Ķ�λ�������
    //     pPoints: ���������ʵ�ʻ�õĶ�λ�����ꡣ
    //     pSpatialReference: ϣ����ȡ�Ķ�λ���Ӧ�Ŀ�    ��ο�ϵ��ȱʡΪNULL����ʾʹ�ü��ζ�����
    // �Ŀռ�ο�ϵ��
	//		ȡ��������Ҫ���ո�����pSpatialReference��������ת��
	//		�����ص������Ѿ���pSpatialReference�µ�����
    //     nTolerance: ����������ֵ��ȱʡΪ0��ֱ�ӻ�ȡ
    // ǰnPointCount����λ������ꡣ(��Ϊ����ȡ���괮����ʼλ�ã��ӵ�nTolerance�����꿪ʼ����ȡ)
    //##ModelId=456253CB003E
    int GetPoints(int nPointCount, SPo_DPoint* & pPoints, IPo_SpatialReference* pSpatialReference = NULL, int nTolerance = 0)
	{
		return m_sdoGeometry.GetPoints(nPointCount,pPoints,pSpatialReference,nTolerance);
	};
	
	////brief
	//    �Ƿ����˿յĵ㼯
	////return
	//    ����ǿգ�����true
	//##ModelId=464AC35501A7
	bool IsEmpty()
	{
		return m_sdoGeometry.IsEmpty();
	}

	////brief
	//    ��ռ��ζ���
	////return
	//    ��ճɹ�������true
	//##ModelId=464AC35501A9
	bool SetEmpty()
	{
		return m_sdoGeometry.SetEmpty();
	}

	//���ڲ�������
	////brief
	//    ���ü��ζ������С��Ӿ���
	//    ���ݸ����Ŀռ�ο�ϵ���ü��ζ������С���    ����
	///return
	//    ��С��Ӿ��������Ƿ�ɹ�����    
	//pSpatialReference��Ϊ�գ�������ת�����ɹ���    
	//�򷵻�false�����óɹ��򷵻�true��
	////param
	//    rect: �����õ���С��Ӿ���
	//    pSpatialReference: ��С��Ӿ��ζ�Ӧ�Ŀռ��    
	//��ϵ��ȱʡΪNULL����ʾʹ�ü��ζ�����Ŀ�    ��ο�ϵ��
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
    //     ������ָ����������ķ�Χ�ڣ�ָ���ĵ��Ƿ���    ���ζ���ķ�Χ�ڣ��༴�Ƿ�����˸ö���
    //param
    //     sPoint: ָ���ĵ㣬���Ե�,����pSpatialReference�µ�����,�ڲ�ת������бȽ�
    //     pSpatialReference: ���Ե��Ӧ�Ŀռ�ο�ϵ��    ȱʡΪNULL����ʾʹ�ü��ζ�����Ŀռ�ο�    ϵ��
    //     dTolerance: ��ֵ������ֵ����λ�����ݼ��ĵ�    λ��ͬ
	//bSelected:�Ƿ��Ѿ���ѡȡ�����Ϊtrue��dToleranceҪ��ֵ������Ҫץȡ���ζ���Ľṹ��handlepoint������ֵΪ�����+1
	//���Ϊfalse��dTorlerance��һ��Ҫ��ֵ������Ҫץȡ���ζ��󣬷���ֵΪ0��ûץס��1��ץס��
	//����ֵΪ0ʱ��ʾû��ץס����Ҳû��ץס�ṹ��
    //##ModelId=456253CB030D
    int HitTest(SPo_DPoint sPoint, bool bSelected/*�Ƿ��Ѿ���ѡȡ*/,double dTolerance=0)
	{
		return m_sdoGeometry.HitTest(sPoint,bSelected,dTolerance);
	};
	//�Ƿ񱻵���ѡȡ
	//##ModelId=4829521B037A
	bool IsSelectedByPoint(SPo_DPoint *pSel/*��ѡȡ�Ķ�λ����*/,float fTolerance/*ѡȡ�������ֵ*/)
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
	//�Ƿ�Բѡȡ(��Ҫ����Բ���������ཻ����)
	//##ModelId=4829521C0000
	bool IsSelectedByCircle(SPo_DPoint *pCenter/*Բѡȡ��Բ�ĵ�*/,SPo_DPoint *pPointOnCircle/*Բ���ϵ���һ��*/)
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
	//�Ƿ񱻾���ѡȡ(��Ҫ����������������ཻ����)
	//##ModelId=4829521C004E
	bool IsSelectedByRect(SPo_DPoint *pP1/*���ζԽ����ϵ�һ��*/,SPo_DPoint *pP2/*���ζԽ����ϵ���һ��*/)
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
				//hls added 20091205//�ж�1��2���㶼����
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
	//�Ƿ񱻶����ѡȡ(��Ҫ�����������������ཻ����)
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
	//�Ƿ񱻶����ѡȡ(��Ҫ�����������������ཻ����)
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
	//�Ƿ����߻�����ѡȡ(��Ҫ�������߻��������ཻ����)
	//##ModelId=4829521C0148
	bool IsSelectedByPolyglineBuffer(SPo_DPoint *pPoints,int nPointCount,float fTolerance/*ѡȡ�������ֵ*/)
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
	//�Ƿ����߻�����ѡȡ(��Ҫ�������߻��������ཻ����)
	//##ModelId=4829521C01C5
	bool IsSelectedByPolyglineBuffer(vector<SPo_DPoint *> *pPtrPointsList,float fTolerance/*ѡȡ�������ֵ*/)
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
	bool IsIntersect(double x1,double y1,double x2,double y2/*��ɾ��ε�����������*/)
	{
		return m_sdoGeometry.IsIntersect(x1,y1,x2,y2);
	};
	bool PllHitTest(SPo_DPoint sPoint, POINT &ipHit/*����ϸ�ڣ�x,y�ֱ��ʾ�ϵ�ǰ��ڵ���ţ��ض����ڻ������*/,SPo_DPoint2D &dptConn/*��·���ϵĲ���ϵ�*/,double dTolerance/* = 0.0*/)
	{
		return m_sdoGeometry.PllHitTest(sPoint,ipHit,dptConn,dTolerance);
	};
	bool PllReverse()
	{
		return m_sdoGeometry.PllReverse();
	};
	//����һ�����ĵ���
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
	void RetrieveSpatialElemInfo(bool bCoordReset = true/*�Ƿ����򹴻���˳��ʱ�뷽������֯�����*/)
	{
		m_sdoGeometry.RetrieveSpatialElemInfo(bCoordReset);
	}	
	//��ȡ�����ܸ���
	//##ModelId=46AF583200FA
	int PlnGetRingsCount()
	{
		return m_sdoGeometry.PlnGetRingsCount();
	}
};
//brief
//     �������ζ��󡪡����ζ������ӿڡ�
//		
//		�����ڲ������˺��ֿռ�ο�ϵ,���ζ����ڲ��洢������ȫ���ǵ���γ����
//		x:������;yγ����
//     ���ڻ�ȡ�����ü��ζ���������Ϣ��
//     ��һ���ض����͵ļ��ζ���������ɾ��ض�����    ����ָ��ת��Ϊĳһ����ļ��ζ���
//##ModelId=4B2B8A72005D
class IGeo_Geometry : public IPo_Unknown
{
  public:
    //brief
    //     ��ȡ���ζ�������
    // 
    //     �ɸ��ݸ��������ø����͵ļ��ζ���ָ�뽫����    ���ζ���ת��Ϊ�����͵ļ��ζ���
    //return
    //     ���ζ��������
    //##ModelId=4B2B8A72005F
    virtual int GetGeoType() = 0;

    //brief
    //     ���ü��ζ���Ŀռ�ο�ϵ
    //return
    //     �ռ�ο�ϵ���óɹ�����true�����򷵻�false��
	//		�ڲ����겻�����κ�ת��
    //param
    //     pSpatialReference: Ҫ���õĿռ�ο�ϵ��ȱʡ    ΪNULL����ʾʹ�õ㱾��Ŀռ�ο�ϵ��
    //##ModelId=4B2B8A72006E
    virtual bool SetSpatialReference(IPo_SpatialReference* pSpatialReference) = 0;

    //brief
    //     ��ȡ���ζ���Ŀռ�ο�ϵ
    //return
    //     �ռ�ο�ϵָ��
    //##ModelId=4B2B8A720071
    virtual IPo_SpatialReference* GetSpatialReferencePtr() = 0;

    //brief
    //     ��ȡ���ζ����ά��
    //return
    //     ���ζ����ά��
    //##ModelId=4B2B8A720073
    virtual char GetDimension() = 0;

    //brief
    //     ��ȡ���ζ���Ķ�λ�����
    //return
    //     ���ζ���Ķ�λ�����
    //##ModelId=4B2B8A720075
    virtual int GetPointCount() = 0;

    //brief
    //     ��ȡ���ζ���Ķ�λ��
    //     �����±��ָ���ռ�ο�ϵ��ȡ��λ������
    //     0<=nIndex<��λ�����������������ֵ�򷵻�    SPo_Point(0,0)��
    //return
    //     SPo_Point ��λ������
    //param
    //     nIndex: ��λ����±�
    //     pSpatialReference: ϣ����ȡ�Ķ�λ���Ӧ�Ŀռ�ο�ϵ��ȱʡΪNULL����ʾʹ�ü��ζ�����
	//		ȡ��������Ҫ���ո�����pSpatialReference��������ת��
	//		�����ص������Ѿ���pSpatialReference�µ�����
    // �Ŀռ�ο�ϵ��
    //##ModelId=4B2B8A720077
    virtual SPo_DPoint GetPoint(int nIndex, IPo_SpatialReference* pSpatialReference = NULL) = 0;

    //brief
    //     ������ȡ��λ�����ꡣ
    //     ���ݸ����������õĶ�λ��ĸ����Ͳ�������    ֵ������ȡ��λ�����ꡣ
    //return
    //     ʵ�ʻ�õĶ�λ�����(<= nPointCount)��
    //param
    //     nPointCount: �����ȡ�Ķ�λ�������
    //     pPoints: ���������ʵ�ʻ�õĶ�λ�����ꡣ
    //     pSpatialReference: ϣ����ȡ�Ķ�λ���Ӧ�Ŀ�    ��ο�ϵ��ȱʡΪNULL����ʾʹ�ü��ζ�����
    // �Ŀռ�ο�ϵ��
	//		ȡ��������Ҫ���ո�����pSpatialReference��������ת��
	//		�����ص������Ѿ���pSpatialReference�µ�����
    //     nTolerance: ����������ֵ��ȱʡΪ0��ֱ�ӻ�ȡ
    // ǰnPointCount����λ������ꡣ(��Ϊ����ȡ���괮����ʼλ�ã��ӵ�nTolerance�����꿪ʼ����ȡ)
    //##ModelId=4B2B8A72007B
    virtual int GetPoints(int nPointCount, SPo_DPoint* &pPoints) = 0;

    //brief
    //     ���ü��ζ������С��Ӿ���
    //     ���ݸ����Ŀռ�ο�ϵ���ü��ζ������С���    ����
    // /return
    //     ��С��Ӿ��������Ƿ�ɹ�����    pSpatialReference��Ϊ�գ�������ת�����ɹ���
    // �򷵻�false�����óɹ��򷵻�true��
    //param
    //     rect: �����õ���С��Ӿ���,����pSpatialReference�µ�����,�ڲ�����������ת��
    //     pSpatialReference: ��С��Ӿ��ζ�Ӧ�Ŀռ��    ��ϵ��ȱʡΪNULL����ʾʹ�ü��ζ�����Ŀ�    ��ο�ϵ��
    //##ModelId=4B2B8A720081
    virtual bool SetMBR(SPo_DRect rect, IPo_SpatialReference* pSpatialReference = NULL) = 0;

    //brief
    //     ��ȡ���ζ������С��Ӿ���
    //return
    //     ���ζ������С��Ӿ���
    //param
    //      nMode����ȡ��ʽ�����ܵ�ȡֵΪ��
    //      PO_COMPUTE_OFF�������㣬ֱ�ӷ��ص�ǰֵ��ȱ     ʡ�������ã�
    //      PO_COMPUTE_ON�����¼���
    //      PO_COMPUTE_ONCE�����û�м����������㣻     ����ֱ�ӷ��ص�ǰֵ
    // 		ȡ��������Ҫ���ո�����pSpatialReference��������ת��
	//		�����ص������Ѿ���pSpatialReference�µ�����
    //      pSpatialReference��ϣ����ȡ����С��Ӿ���     ����Ӧ�Ŀռ�ο�ϵ��ȱʡΪNULL����ʾʹ�ü�
    // �ζ�����Ŀռ�ο�ϵ��
    //##ModelId=4B2B8A720085
    virtual SPo_DRect GetMBR(int nMode = GIS_COMPUTE_OFF, IPo_SpatialReference* pSpatialReference = NULL) = 0;

    //brief
    //     ���ζ���ĸ���
    // 
    //     ���ݸ����ļ��ζ�����������ݵ������ζ���
    // 
    //return
    //     ���ζ������Ƿ�ɹ���
    // 
    //param
    //     pSourceGeo: Դ���ζ���
    // 
    //     ��ע:Դ���ζ����뱾���ζ�������ͱ�����ͬ��
    //##ModelId=4B2B8A720089
    //virtual bool Clone(const IGeo_Geometry* pSourceGeo) = 0;// hls deleted 20110107

    //brief
    //     ���� XML �ڵ㹹�켸�ζ���
    //param
    //     szXML: XML �ڵ��ַ���
    //##ModelId=4B2B8A72008C
    virtual bool FromXML(const char* szXML) = 0;

    //brief
    //     �Ѽ��ζ�������� XML ��ʽ��һ���ַ�����
    //param
    //     szXML: ���XML�ַ�����
    //##ModelId=4B2B8A72008F
    virtual bool ToXML(char* szXML) = 0;

    //brief
    //     ������ָ����������ķ�Χ�ڣ�ָ���ĵ��Ƿ���    ���ζ���ķ�Χ�ڣ��༴�Ƿ�����˸ö���
    //param
    //     sPoint: ָ���ĵ㣬���Ե�,����pSpatialReference�µ�����,�ڲ�ת������бȽ�
    //     pSpatialReference: ���Ե��Ӧ�Ŀռ�ο�ϵ��    ȱʡΪNULL����ʾʹ�ü��ζ�����Ŀռ�ο�    ϵ��
    //     dTolerance: ��ֵ������ֵ����λ�����ݼ��ĵ�    λ��ͬ
	//bSelected:�Ƿ��Ѿ���ѡȡ�����Ϊtrue��dToleranceҪ��ֵ������Ҫץȡ���ζ���Ľṹ��handlepoint������ֵΪ�����+1
	//���Ϊfalse��dTorlerance��һ��Ҫ��ֵ������Ҫץȡ���ζ��󣬷���ֵΪ0��ûץס��1��ץס��
	//����ֵΪ0ʱ��ʾû��ץס����Ҳû��ץס�ṹ��
    //##ModelId=4B2B8A720092
    virtual int HitTest(SPo_DPoint sPoint,bool bSelected/*�Ƿ��Ѿ���ѡȡ*/,IPo_SpatialReference* pSpatialReference = NULL, double dTolerance = 0.0) = 0;
	
    //brief
    //     �Ƿ����˿յĵ㼯
    //return
    //     ����ǿգ�����true
    //##ModelId=4B2B8A720098
    virtual bool IsEmpty() = 0;

    //brief
    //     ��ռ��ζ���
    //return
    //     ��ճɹ�������true
    //##ModelId=4B2B8A72009A
    virtual bool SetEmpty() = 0;

    //brief
    //     �鵵���ζ���
    //##ModelId=4B2B8A72009C
    virtual bool Archive(IDS_DataBuffer* pDataBuffer, int iMode, int iType = 0) = 0;

    //brief
    //     ��ȡ���ζ���Ķ�λ��ĵ�ַ����
    //     �����±��ָ���ռ�ο�ϵ��ȡ��λ������
    //     0<=nIndex<��λ�����������������ֵ�򷵻�    SPo_Point(0,0)��
    //return
    //     SPo_Point ��λ������
    //param
    //     nIndex: ��λ����±�
    //     pSpatialReference: ϣ����ȡ�Ķ�λ���Ӧ�Ŀ�    ��ο�ϵ��ȱʡΪNULL����ʾʹ�ü��ζ�����
    // �Ŀռ�ο�ϵ������ռ�ο�ϵΪ��,ֱ�Ӹ����ڲ�����ĵ�ַ����,�����ֵ,�򷵻�pSpatialReference�µ�����ĵ�ַ
    //##ModelId=4B2B8A7200A1
    virtual SPo_DPoint* GetPointPref(int nIndex, IPo_SpatialReference* pSpatialReference = NULL) = 0;

	//brief
    //     
    //     ���ȫ����λ��
    //     
    //return
    //     
    //param
    //     
    //##ModelId=4B2B8A7200A5
    virtual void ClearPoints() = 0;

    //
	//brief
    //     �����ζ����ڲ�����ȫ���Ա���������ʽ�������������ݵ��Ⱥͻ��棬ʵ�ֲ�ͬ��������ݽ���
    //     
    //     
    //return
    //     
    //param
    //     ppBytes:�����洢���������ݣ��������ݹ涨Ϊȫ������ļ��ζ������ݼ����������Ĵ�С����������С�����ṩ�Ľӿڼ���
    //   
    //##ModelId=4B2B8A7200A7
    virtual void ToBytes(PBYTE *ppBytes) = 0;

    //
	//brief
    //     �����ζ������ⲿ��������������װ��(���ڸýӿ�����һ������࣬���ζ����ڴ���ʱ������װ������ʱ���ͱ���һ��)
    //     ##########@@@@@@@@@@@@@@@@@@@@@@!!!!!!!!!!!!!!!!!!!�رղ���ȫ�Ĳ��ɿ��Ľӿ�
    //     
    //return
    //     
    //param
    //     ppBytes��Ҫ����װ�ص�������
    //   
    //##ModelId=46D669CF00EA
    //virtual void FromBytes(PBYTE *ppBytes) = 0;

    //
	//brief
    //     ���㼸�����������ֽ�����С
    //     //�õ��洢����������Ҫ���ֽ�������(�����洢���ݴ�С��4���ֽ�)
    //     
    //return
    //     ����Ҫ���ֽ����洢�ü��ζ���������ֽ�����С
    //param
    //     
    //   
    //##ModelId=4B2B8A7200AA
    virtual size_t WeightGeoDataSize() = 0;
	//brief
    //     ��ȡ���ζ���ϸ���ĵ�Ԫ����Ϣ��һ��Ԫ��SPo_IPoint(x,y,z),���ĺ������Oracle Spatial Users' Guide-ElementInfo
    //     
    //     
    //return
    //     
    //param
    //     
    //   
    //##ModelId=4B2B8A7200AC
    virtual void RetrieveSpatialElemInfo(bool bCoordReset = true/*�Ƿ����򹴻���˳��ʱ�뷽������֯�����*/) = 0;

	//��ȡ����OracleSpatial�Ļ���������Ϣ
	//##ModelId=4B2B8A7200AF
	virtual LOG_SDOGEOMETRY GetLogOsGeometry() = 0;
	//���û���OracleSpatial�Ļ���������Ϣ
	//##ModelId=4B2B8A7200AF
	virtual LOG_BASEGEOMETRY *GetLogBaseGeometryRef() = 0;
	//��ȡOsgeometry�е�m_gPoint�м�¼�ĵ��ָ��
	//##ModelId=4B2B8A7200B1
	virtual SPo_DPoint *GetFirstOsGpoint() = 0;
	//////////////////////////////////////////////////////////////////////////
	//�Ƿ񱻵���ѡȡ
	//##ModelId=4829521B037A
	virtual bool IsSelectedByPoint(SPo_DPoint *pSel/*��ѡȡ�Ķ�λ����*/,float fTolerance/*ѡȡ�������ֵ*/) = 0;
	//�Ƿ�Բѡȡ(��Ҫ����Բ���������ཻ����)
	//##ModelId=4829521C0000
	virtual bool IsSelectedByCircle(SPo_DPoint *pCenter/*Բѡȡ��Բ�ĵ�*/,SPo_DPoint *pPointOnCircle/*Բ���ϵ���һ��*/) = 0;
	//�Ƿ񱻾���ѡȡ(��Ҫ����������������ཻ����)
	//##ModelId=4829521C004E
	virtual bool IsSelectedByRect(SPo_DPoint *pP1/*���ζԽ����ϵ�һ��*/,SPo_DPoint *pP2/*���ζԽ����ϵ���һ��*/) = 0;
	//�Ƿ񱻶����ѡȡ(��Ҫ�����������������ཻ����)
	//##ModelId=4829521C00AB
	virtual bool IsSelectedByPolygon(SPo_DPoint *pPoints,int nPointCount) = 0;
	//�Ƿ񱻶����ѡȡ(��Ҫ�����������������ཻ����)
	//##ModelId=4829521C0109
	virtual bool IsSelectedByPolygon(vector<SPo_DPoint *> *pPtrPointsList) = 0;
	//�Ƿ����߻�����ѡȡ(��Ҫ�������߻��������ཻ����)
	//##ModelId=4829521C0148
	virtual bool IsSelectedByPolyglineBuffer(SPo_DPoint *pPoints,int nPointCount,float fTolerance/*ѡȡ�������ֵ*/) = 0;
	//�Ƿ����߻�����ѡȡ(��Ҫ�������߻��������ཻ����)
	//##ModelId=4829521C01C5
	virtual bool IsSelectedByPolyglineBuffer(vector<SPo_DPoint *> *pPtrPointsList,float fTolerance/*ѡȡ�������ֵ*/) = 0;
};

//brief
//     ���ζ���Ĵ����ӿ�
//     
//     
//return
//     �����ɹ�����true��ʧ��false
//param
//     nType:���ζ�������Ͷ��壬�μ�...\common\geo_commondef.h
//     ppVal:���������ļ��ζ���ָ��ĵ�ַ
extern "C" __declspec(dllexport) bool CoCreateGeometryObject(int nType,void **ppVal);

//ppBytes�����ݹ涨Ϊȫ������ļ��ζ������ݼ����������Ĵ�С����������С�����ṩ�Ľӿڼ���
extern "C" __declspec(dllexport) IGeo_Geometry *CreateGeoObjectFrom1(PBYTE *ppBytes);

//�ɻ���OracleSpatial�Ļ���������Ϣ�������ζ���
extern "C" __declspec(dllexport) IGeo_Geometry *CreateGeometryIndirect(const LOG_SDOGEOMETRY *pLog);

extern "C" __declspec(dllexport) void Po_GeometryInstance();

extern "C" __declspec(dllexport) void Po_GeometryExitInstance();

#endif /* IGEO_GEOMETRY_H_HEADER_INCLUDED_B9066FDF */
