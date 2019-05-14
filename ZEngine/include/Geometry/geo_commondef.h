#ifndef GEO_COMMONDEF_H_HEADER_INCLUDED_B93766E5
#define GEO_COMMONDEF_H_HEADER_INCLUDED_B93766E5


//##ModelId=4B0DE4BB02CE
const UINT16 PMC_TYPE_MSPDOT				= 0x0001; const char NMPMC_TYPE_MSPDOT[] = "��ͼԪ";
const UINT16 PMC_TYPE_MSPCIRC				= 0x0002; const char NMPMC_TYPE_MSPCIRC[] = "ԲͼԪ";
const UINT16 PMC_TYPE_MSPCIRCARC			= 0x0004; const char NMPMC_TYPE_MSPCIRCARC[] = "Բ��ͼԪ";
const UINT16 PMC_TYPE_MSPELLP				= 0x0008; const char NMPMC_TYPE_MSPELLP[] = "��ԲͼԪ";
const UINT16 PMC_TYPE_MSPRECT				= 0x0010; const char NMPMC_TYPE_MSPRECT[] = "����ͼԪ";
const UINT16 PMC_TYPE_MSPRNDRECT			= 0x0020; const char NMPMC_TYPE_MSPRNDRECT[] = "Բ�Ǿ���ͼԪ";
const UINT16 PMC_TYPE_MSPLINESTR			= 0x0040; const char NMPMC_TYPE_MSPLINESTR[] = "P������ͼԪ";
const UINT16 PMC_TYPE_MSPSPLINE				= 0x0080; const char NMPMC_TYPE_MSPSPLINE[] = "P��������ͼԪ";
const UINT16 PMC_TYPE_MSPPOLY				= 0x0100; const char NMPMC_TYPE_MSPPOLY[] = "P�Ͷ����ͼԪ";
const UINT16 PMC_TYPE_MSPPLPLG				= 0x0200; const char NMPMC_TYPE_MSPPLPLG[] = "P�Ͷ�����ͼԪ";
const UINT16 PMC_TYPE_MSGLINESTR			= 0x0400; const char NMPMC_TYPE_MSGLINESTR[] = "L������ͼԪ";
const UINT16 PMC_TYPE_MSGSPLINE				= 0x0800; const char NMPMC_TYPE_MSGSPLINE[] = "L��������ͼԪ";
const UINT16 PMC_TYPE_MSGPOLY				= 0x1000; const char NMPMC_TYPE_MSGPOLY[] = "A�Ͷ����ͼԪ";
const UINT16 PMC_TYPE_MSGPLPLG				= 0x2000; const char NMPMC_TYPE_MSGPLPLG[] = "A�Ͷ�����ͼԪ";
const UINT16 PMC_TYPE_TXT					= 0x4000; const char NMPMC_TYPE_TXT[] = "�ַ���";
const UINT16 PMC_TYPE_RAS					= 0x8000; const char NMPMC_TYPE_RAS[] = "λͼ";

#define PMC_TYPE_NULL 0
//�ر�ע��,�����Ҫ���������,����Ҫ�޸�_mmgLOG_PUBMAPCELL::m_uPubMapCellType������,����������ܴ洢�����ֵ

#define PMC_TYPE_MAPCELLALL PMC_TYPE_MSPDOT|PMC_TYPE_MSPCIRC|PMC_TYPE_MSPCIRCARC|PMC_TYPE_MSPELLP|PMC_TYPE_MSPRECT|PMC_TYPE_MSPRNDRECT|PMC_TYPE_MSPLINESTR|PMC_TYPE_MSPSPLINE|PMC_TYPE_MSPPOLY|PMC_TYPE_MSPPLPLG|PMC_TYPE_MSGLINESTR|PMC_TYPE_MSGSPLINE|PMC_TYPE_MSGPOLY|PMC_TYPE_MSGPLPLG|PMC_TYPE_TXT|PMC_TYPE_RAS

inline bool IsPubSymCellType(UINT16 utype)
{
	return utype==PMC_TYPE_MSPDOT||
		utype==PMC_TYPE_MSGLINESTR||utype==PMC_TYPE_MSPLINESTR||
		utype==PMC_TYPE_MSGSPLINE||utype==PMC_TYPE_MSPSPLINE||
		utype==PMC_TYPE_MSPCIRC||utype==PMC_TYPE_MSPCIRCARC||
		utype==PMC_TYPE_MSPELLP||utype==PMC_TYPE_MSPPOLY||
		utype==PMC_TYPE_MSGPOLY||utype==PMC_TYPE_MSPPLPLG||
		utype==PMC_TYPE_MSGPLPLG||utype==PMC_TYPE_MSPRECT||
		utype==PMC_TYPE_MSPRNDRECT;
}

inline const char *GetPmcTypeName(UINT16 dwPmcType)
{
	switch(dwPmcType) 
	{
	case PMC_TYPE_MSPDOT:return NMPMC_TYPE_MSPDOT;
	case PMC_TYPE_MSPCIRC:return NMPMC_TYPE_MSPCIRC;
	case PMC_TYPE_MSPCIRCARC: return NMPMC_TYPE_MSPCIRCARC;
	case PMC_TYPE_MSPELLP: return NMPMC_TYPE_MSPELLP;
	case PMC_TYPE_MSPRECT: return NMPMC_TYPE_MSPRECT;
	case PMC_TYPE_MSPRNDRECT: return NMPMC_TYPE_MSPRNDRECT;
	case PMC_TYPE_MSPLINESTR: return NMPMC_TYPE_MSPLINESTR;
	case PMC_TYPE_MSPSPLINE: return NMPMC_TYPE_MSPSPLINE;
	case PMC_TYPE_MSPPOLY: return NMPMC_TYPE_MSPPOLY;
	case PMC_TYPE_MSPPLPLG: return NMPMC_TYPE_MSPPLPLG;
	case PMC_TYPE_MSGLINESTR: return NMPMC_TYPE_MSGLINESTR;
	case PMC_TYPE_MSGSPLINE: return NMPMC_TYPE_MSGSPLINE;
	case PMC_TYPE_MSGPOLY: return NMPMC_TYPE_MSGPOLY;
	case PMC_TYPE_MSGPLPLG: return NMPMC_TYPE_MSGPLPLG;
	case PMC_TYPE_TXT: return NMPMC_TYPE_TXT;
	case PMC_TYPE_RAS: return NMPMC_TYPE_RAS;
	default:	break;
	}
	return NULL;
}
//����ϵͳ���ͣ�ͨ����
const byte PMC_CSYS_TYPE_MAPGEO = 1;//��ͼ����ĵ���γ������ϵ����λͨ����
const byte PMC_CSYS_TYPE_OBJPRT = 2;//����ͼ�����Ρ���ע��˵��ע�ǵȣ�����ϵ����Զ���ԭ����������Ϊ��������Ϊ������λͨ������
const byte PMC_CSYS_TYPE_PAGGLB = 3;//����ҳ������ϵ������ҳ�߾ࣩ������ҳ������Ͻ�Ϊԭ�㣬����Ϊ������λ���أ���һ��û������ԭ���U����ϵ
const byte PMC_CSYS_TYPE_MAPDVC = 4;//��ͼ�������ϵ��������Ϊ��λ����������Ļ����ӡ����ͼ������ϵ���ǵ�ͼ��������������豸��������


#define GEO_TYPE_UNKNOW				0x00000000	

#define GEO_TYPE_GEOPOINT			0x00000001	
#define GEO_TYPE_GEOMULTIPOINT		0x00000002	
#define GEO_TYPE_GEOANNOTATION		0x00000004	
#define GEO_TYPE_GEOMULTISURFACE	0x00000008	
#define GEO_TYPE_GEOELLIPSE			0x00000010	
#define GEO_TYPE_GEOSURFACE			0x00000020		
#define GEO_TYPE_GEORECT			0x00000040		
#define GEO_TYPE_GEOPOLYGON			0x00000080		
#define GEO_TYPE_GEOMULTILINESTRING 0x00000100		
#define GEO_TYPE_GEOLINESTRING		0x00000200	
#define GEO_TYPE_GEOPOLYLINE		0x00000400	
#define GEO_TYPE_GEOLINE			0x00000800	
#define GEO_TYPE_GEOCIRCULARARC		0x00001000	
#define GEO_TYPE_GEOELLIPTICARC		0x00002000	
#define GEO_TYPE_GEOBAZIERCURVE		0x00004000	
#define GEO_TYPE_GEOCOMPOSEOBJ		0x00008000	
#define GEO_TYPE_ALLTYPE			GEO_TYPE_GEOPOINT|GEO_TYPE_GEOMULTIPOINT|GEO_TYPE_GEOANNOTATION|GEO_TYPE_GEOMULTISURFACE|GEO_TYPE_GEOELLIPSE|GEO_TYPE_GEOSURFACE|GEO_TYPE_GEORECT|GEO_TYPE_GEOPOLYGON|GEO_TYPE_GEOMULTILINESTRING|GEO_TYPE_GEOLINESTRING|GEO_TYPE_GEOPOLYLINE|GEO_TYPE_GEOLINE|GEO_TYPE_GEOCIRCULARARC|GEO_TYPE_GEOELLIPTICARC|GEO_TYPE_GEOBAZIERCURVE

#define GEO_TYPE_GOS2POINT 2001
#define GEO_TYPE_GOS2POLYLINE 2002
#define GEO_TYPE_GOS2POLYGON 2003
#define GEO_TYPE_GOS2ANNOTATION 2004
#define GEO_TYPE_GOS2MULTIPOINT 2005
#define GEO_TYPE_GOS2MULTILINESTRING 2006
#define GEO_TYPE_GOS2MULTISURFACE 2007
#define GEO_TYPE_GOS3POINT 3001
#define GEO_TYPE_GOS3POLYLINE 3002
#define GEO_TYPE_GOS3POLYGON 3003
#define GEO_TYPE_GOS3ANNOTATION 3004
#define GEO_TYPE_GOS3MULTIPOINT 3005
#define GEO_TYPE_GOS3MULTILINESTRING 3006
#define GEO_TYPE_GOS3MULTISURFACE 3007

const int GEO_TYPES_GOS[] = {
GEO_TYPE_GOS2POINT,
GEO_TYPE_GOS2POLYLINE,
GEO_TYPE_GOS2POLYGON,
GEO_TYPE_GOS2ANNOTATION,
GEO_TYPE_GOS2MULTIPOINT,
GEO_TYPE_GOS2MULTILINESTRING,
GEO_TYPE_GOS2MULTISURFACE,
GEO_TYPE_GOS3POINT,
GEO_TYPE_GOS3POLYLINE,
GEO_TYPE_GOS3POLYGON,
GEO_TYPE_GOS3ANNOTATION,
GEO_TYPE_GOS3MULTIPOINT,
GEO_TYPE_GOS3MULTILINESTRING,
GEO_TYPE_GOS3MULTISURFACE
};

inline int GEO_TYPES_GOSCNT()
{
	return sizeof(GEO_TYPES_GOS)/sizeof(int);
}

//////////������Ƶļ��δ��࣬�ܹ�����ѹ�ǹ�ϵ
#define GEO_DRAWSTYLE_ANNO 0x01
#define GEO_DRAWSTYLE_POINT 0x02
#define GEO_DRAWSTYLE_LINE 0x04
#define GEO_DRAWSTYLE_AREA 0x08

#define GEO_DRAWSTYLE_ALLSUPPORT GEO_DRAWSTYLE_ANNO|GEO_DRAWSTYLE_POINT|GEO_DRAWSTYLE_LINE|GEO_DRAWSTYLE_AREA

int inline GTYPE_TO_DWSTYLE(int nGtype)
{
	switch(nGtype)
	{
	case GEO_TYPE_GEOANNOTATION:
	case GEO_TYPE_GOS2ANNOTATION:
	case GEO_TYPE_GOS3ANNOTATION:
		return GEO_DRAWSTYLE_ANNO;
		break;
	case GEO_TYPE_GEOPOINT:
	case GEO_TYPE_GEOMULTIPOINT:
	case GEO_TYPE_GOS2POINT:
	case GEO_TYPE_GOS2MULTIPOINT:
	case GEO_TYPE_GOS3POINT:
	case GEO_TYPE_GOS3MULTIPOINT:
		return GEO_DRAWSTYLE_POINT;
		break;
	case GEO_TYPE_GEOMULTILINESTRING:
	case GEO_TYPE_GEOLINESTRING:
	case GEO_TYPE_GEOPOLYLINE:
	case GEO_TYPE_GEOLINE:
	case GEO_TYPE_GEOCIRCULARARC:
	case GEO_TYPE_GEOELLIPTICARC:
	case GEO_TYPE_GEOBAZIERCURVE:
	case GEO_TYPE_GOS2POLYLINE:
	case GEO_TYPE_GOS2MULTILINESTRING:
	case GEO_TYPE_GOS3POLYLINE:
	case GEO_TYPE_GOS3MULTILINESTRING:
		return GEO_DRAWSTYLE_LINE;
		break;
	case GEO_TYPE_GEOMULTISURFACE:
	case GEO_TYPE_GEOELLIPSE:
	case GEO_TYPE_GEOSURFACE:
	case GEO_TYPE_GEORECT:
	case GEO_TYPE_GEOPOLYGON:
	case GEO_TYPE_GOS2POLYGON:
	case GEO_TYPE_GOS2MULTISURFACE:
	case GEO_TYPE_GOS3POLYGON:
	case GEO_TYPE_GOS3MULTISURFACE:
		return GEO_DRAWSTYLE_AREA;
		break;
	default:
		return GEO_DRAWSTYLE_POINT;
		break;
	}
}

#define INTERFACE_GEO_ENVELOPE				"INTERFACE_GEO_ENVELOPE"
#define INTERFACE_GEO_GEOMETRY				"INTERFACE_GEO_GEOMETRY"
#define INTERFACE_GEO_POINT					"INTERFACE_GEO_POINT"
#define INTERFACE_GEO_MULTIPOINT			"INTERFACE_GEO_MULTIPOINT"
#define INTERFACE_GEO_ANNOTATION			"INTERFACE_GEO_ANNOTATION"
#define INTERFACE_GEO_MULTISURFACE			"INTERFACE_GEO_MULTISURFACE"
#define INTERFACE_GEO_ELLIPSE				"INTERFACE_GEO_ELLIPSE"
#define INTERFACE_GEO_SURFACE				"INTERFACE_GEO_SURFACE"
#define INTERFACE_GEO_RECT					"INTERFACE_GEO_RECT"
#define INTERFACE_GEO_POLYGON				"INTERFACE_GEO_POLYGON"
#define INTERFACE_GEO_MULTILINESTRING		"INTERFACE_GEO_MULTILINESTRING"
#define INTERFACE_GEO_CURVE					"INTERFACE_GEO_CURVE"
#define INTERFACE_GEO_POLYCURVE				"INTERFACE_GEO_POLYCURVE"
#define INTERFACE_GEO_LINE					"INTERFACE_GEO_LINE"
#define INTERFACE_GEO_CIRCULARARC			"INTERFACE_GEO_CIRCULARARC"
#define INTERFACE_GEO_ELLIPTICARC			"INTERFACE_GEO_ELLIPTICARC"
#define INTERFACE_GEO_BAZIERCURVE			"INTERFACE_GEO_BAZIERCURVE"
#define INTERFACE_GEO_LINESTRING			"INTERFACE_GEO_LINESTRING"
#define INTERFACE_GEO_POLYLINE				"INTERFACE_GEO_POLYLINE"
#define INTERFACE_GEO_TRANSFORMATION		"INTERFACE_GEO_TRANSFORMATION"
#define INTERFACE_GEO_TRANSFORMA2D			"INTERFACE_GEO_TRANSFORMA2D"
#define INTERFACE_GEO_AFFINETRANSFORM2D		"INTERFACE_GEO_AFFINETRANSFORM2D" 

//brief,����ά�ȣ���㡢�ߡ����ά�ȷֱ�Ϊ0��1��2ά�ȡ�
//##ModelId=4B2B8A740242
enum tagpoenumGeometryDimension { 
    //0ά����㣻
	//##ModelId=4B2B8A740262
    GD_GEOMETRY0DIM = 1, 
    //1ά�����߶Σ�
	//##ModelId=4B2B8A740271
    GD_GEOMETRY1DIM = 2, 
    //2ά�������εȣ�
	//##ModelId=4B2B8A740280
    GD_GEOMETRY2DIM = 4, 
    //2.5ά������mesh��
	//##ModelId=4B2B8A740290
    GD_GEOMETRY25DIM = 5, 
    //��ά
	//##ModelId=4B2B8A740291
    GD_GEOMETRY3DIM = 6 };
	
	
	//##ModelId=4B2B8A7402AF
typedef tagpoenumGeometryDimension poenumGeometryDimension;


//brief ���δ���
//##ModelId=4B2B8A7402CE
enum tagpoenumGeometryError {  };

//���δ����typedef
//##ModelId=4B2B8A7402EF
typedef tagpoenumGeometryError poenumGeometryError;

// �������ͣ��㡢��㣻���ߴ����ߴ������ߡ��߶Ρ�Բ������Բ����Bazier���ߣ����桢�桢����Ρ���Բ�����Ρ�������ϡ����⼸��
//##ModelId=4B2B8A74030E
typedef enum tagpoenumGeoType { 
	GT_POINT = 0, 
		GT_MULTIPOINT = 1, 
		GT_MULTILINESTRING = 2, 
    // �ӵ㡣
    GT_LINESTRING = 3,
	GT_POLYLINE = 4,
	GT_LINE = 5, 
	GT_CIRCULARARC = 6, 
	GT_ELLIPTICARC = 7, 
	
	GT_BAZIERACURVE = 8, 
	GT_MULTISURFACE = 9,
	GT_SURFACE = 10,
	GT_POLYGON = 11, 
	GT_ELLIPSE = 12, 
	GT_RECT = 13,
	GT_ANNOTATION = 14,

	GT_UNKNOW = 99,
	GT_COMPOUND = 100, 
	GT_ALL = 1000 }poenumGeoType;


//
////##ModelId=4CF75BCB007F
inline poenumGeoType DwGtypeToiGeoType(int nDwGtype/*Ҫ�����ͣ�ע��GEO_DRAWSTYLE_ANNO����GEO_DRAWSTYLE_POINT����GEO_DRAWSTYLE_LINE����GEO_DRAWSTYLE_AREA*/)
{
	switch(nDwGtype)
	{
	case GEO_DRAWSTYLE_ANNO:
		{
			return GT_ANNOTATION;
		}
		break;
	case GEO_DRAWSTYLE_POINT:
		{
			return GT_POINT;
		}
		break;
	case GEO_DRAWSTYLE_LINE:
		{
			return GT_POLYLINE;
		}
		break;
	case GEO_DRAWSTYLE_AREA:
		{
			return GT_POLYGON;
		}
		break;
	default:
		return GT_UNKNOW;
		break;
	}
	return GT_UNKNOW;
};

inline int iGeoTypeToDwGtype(poenumGeoType iGeoType)
{
	switch(iGeoType)
	{
	case GT_ANNOTATION:
		{
			return GEO_DRAWSTYLE_ANNO;
		}
		break;
	case GT_POINT:
		{
			return GEO_DRAWSTYLE_POINT;
		}
		break;
	case GT_POLYLINE:
		{
			return GEO_DRAWSTYLE_LINE;
		}
		break;
	case GT_POLYGON:
		{
			return GEO_DRAWSTYLE_AREA;
		}
		break;
	default:
		return GEO_DRAWSTYLE_POINT;
		break;
	}
	return GEO_DRAWSTYLE_POINT;
};

//�߶���չ��ʽ
//##ModelId=4B2B8A74032D
enum tagpoenumSegmentExtent { ExtentTangentAtFrom = 1, ExtentEmbeddedAtFrom = 2, 
    //�������ߺ�Ƕ�뷽ʽ
    ExtentAtFrom = 3, ExtentTangentAtTo = 8, ExtentEmbeddedAtTo = 10, 
    //�������ߺ�Ƕ�뷽ʽ
	//##ModelId=4B2B8A74034C
    ExtentAtTo = 12, 
    //��������ͷ��չ
    ExtentTangents = 5, NoExtent = 0 };

//for geometry useage
//##ModelId=4B2B8A74035B
typedef tagpoenumSegmentExtent poenumSegmentExtent;
/////////////////Ԥ��������ε��ĵ������ȡ�����÷���/////////////////////////////////////////////////////////
template<class TYPE> inline void TplGS4XYInRect(CRect &rc,TYPE &x1,TYPE &y1,TYPE &x2,TYPE &y2,bool bSet=false,bool bYdown=true)
{
	if(bSet)
	{
		rc.left=min(x1,x2);rc.right=max(x1,x2);
		TYPE miny=min(y1,y2);TYPE maxy=max(y1,y2);
		if(bYdown){rc.top=miny;rc.bottom=maxy;}
		else{rc.top=maxy;rc.bottom=miny;}		
	}
	else
	{
		x1=rc.left;x2=rc.right;
		y1=rc.top;y2=rc.bottom;
	}
}
template<class TYPE> inline void TplGS4XYInRect(CRect *prc,TYPE &x1,TYPE &y1,TYPE &x2,TYPE &y2,bool bSet=false,bool bYdown=true)
{
	TplGS4XYInRect(*prc,x1,y1,x2,y2,bSet,bYdown);
}
template<class TYPE> inline void TplGS4XYInRect(Rect &rc,TYPE &x1,TYPE &y1,TYPE &x2,TYPE &y2,bool bSet=false,bool bYdown=true)
{
	if(bSet)
	{
		rc.X=min(x1,x2);rc.Width=max(x1,x2)-rc.X;
		TYPE miny=min(y1,y2);TYPE maxy=max(y1,y2);
		if(bYdown){rc.Y=miny;rc.Height=maxy-miny;}
		else{rc.Y=maxy;rc.Height=miny-maxy;}		
	}
	else
	{
		x1=rc.X;x2=rc.X+rc.Width;
		y1=rc.Y;y2=rc.Y+rc.Height;
	}
}
template<class TYPE> inline void TplGS4XYInRect(Rect *prc,TYPE &x1,TYPE &y1,TYPE &x2,TYPE &y2,bool bSet=false,bool bYdown=true)
{
	TplGS4XYInRect(*prc,x1,y1,x2,y2,bSet,bYdown);
}
template<class TYPE> inline void TplGS4XYInRect(RectF &rc,TYPE &x1,TYPE &y1,TYPE &x2,TYPE &y2,bool bSet=false,bool bYdown=true)
{
	if(bSet)
	{
		rc.X=min(x1,x2);rc.Width=max(x1,x2)-rc.X;
		TYPE miny=min(y1,y2);TYPE maxy=max(y1,y2);
		if(bYdown){rc.Y=miny;rc.Height=maxy-miny;}
		else{rc.Y=maxy;rc.Height=miny-maxy;}		
	}
	else
	{
		x1=rc.X;x2=rc.X+rc.Width;
		y1=rc.Y;y2=rc.Y+rc.Height;
	}
}
template<class TYPE> inline void TplGS4XYInRect(RectF *prc,TYPE &x1,TYPE &y1,TYPE &x2,TYPE &y2,bool bSet=false,bool bYdown=true)
{
	TplGS4XYInRect(*prc,x1,y1,x2,y2,bSet,bYdown);
}
template<class TYPEP,class TYPE> inline void TplGS4XYInRect(SPo_TplRect<TYPEP> &rc,TYPE &x1,TYPE &y1,TYPE &x2,TYPE &y2,bool bSet=false,bool bYdown=true)
{
	if(bSet)
	{
		rc.left=min(x1,x2);rc.right=max(x1,x2);
		TYPE miny=min(y1,y2);TYPE maxy=max(y1,y2);
		if(bYdown){rc.top=miny;rc.bottom=maxy;}
		else{rc.top=maxy;rc.bottom=miny;}		
	}
	else
	{
		x1=rc.left;x2=rc.right;
		y1=rc.top;y2=rc.bottom;
	}
}
template<class TYPEP,class TYPE> inline void TplGS4XYInRect(SPo_TplRect<TYPEP> *prc,TYPE &x1,TYPE &y1,TYPE &x2,TYPE &y2,bool bSet=false,bool bYdown=true)
{
	TplGS4XYInRect(*prc,x1,y1,x2,y2,bSet,bYdown);
}
////////Ϊ�˽�����նԶ�����з�ջ���������Ͳ�һ������Ҫ�������ɺ����ĵͼ��������ֽ������δ�����ͨ���Ե�ģ�廯
////////��ģ�廯����������ʾ��Ϊ����//////////////////////////////1
#define RPTR_INT	LPINT
#define RPTR_DWD	DWORD *
/////////////////////////////////////////////////
#define VRARR_INT			vector<INT>			
#define VRARR_DWD			vector<DWORD>
#define VRARR_PPTR_INT		vector<RPTR_INT>
#define VRARR_PPTR_DWD		vector<RPTR_DWD>

//////////////////////////////////////////////////////////////////////////
inline INT *TplGetRingRefInRings(LPINT plst,int iIndex){return &(plst[iIndex]);};
inline DWORD *TplGetRingRefInRings(RPTR_DWD plst,int iIndex){return &(plst[iIndex]);};

inline INT *TplGetRingRefInRings(VRARR_INT *plst,int iIndex){return (*plst).begin()+iIndex;};
inline DWORD *TplGetRingRefInRings(VRARR_DWD *plst,int iIndex){return (*plst).begin()+iIndex;};
inline INT *TplGetRingRefInRings(VRARR_PPTR_INT *plst,int iIndex){return *((*plst).begin()+iIndex);};
inline DWORD *TplGetRingRefInRings(VRARR_PPTR_DWD *plst,int iIndex){return *((*plst).begin()+iIndex);};

//RINGSLSTPTR֧������10�ֺ궨�壬TYPE֧��INT��DWORD
template<class RINGSLSTPTR,class TYPE> inline void TplGSRingPnumRingsList(RINGSLSTPTR pRingsList,int iIndex,TYPE &iv,bool bSet=false)
{
	if(bSet)
		*TplGetRingRefInRings(pRingsList,iIndex)=iv;
	else
		iv=(TYPE)(*TplGetRingRefInRings(pRingsList,iIndex));
}
////////Ϊ�˽�������괮������Ͳ�һ������Ҫ�������ɺ����ĵͼ��������ֽ����㴮����ͨ���Ե�ģ�廯
////////��ģ�廯����������ʾ��Ϊ����//////////////////////////////1
#define PPTR_POINT			POINT *
#define PPTR_CPoint			CPoint *
#define PPTR_Point			Point *
#define PPTR_PointF			PointF *
#define PPTR_SPo_DPoint		SPo_DPoint *
#define PPTR_SPo_FPoint		SPo_FPoint *
#define PPTR_SPo_IPoint		SPo_IPoint *
#define PPTR_SPo_DPoint2D	SPo_DPoint2D *
#define PPTR_SPo_FPoint2D	SPo_FPoint2D *
#define PPTR_SPo_IPoint2D	SPo_IPoint2D *
/////////////////////////////////////////////////
#define VPARR_POINT				vector<POINT>	
#define VPARR_CPoint			vector<CPoint>			
#define VPARR_Point				vector<Point>			
#define VPARR_PointF			vector<PointF>			
#define VPARR_SPo_DPoint		vector<SPo_DPoint>		
#define VPARR_SPo_FPoint		vector<SPo_FPoint>		
#define VPARR_SPo_IPoint		vector<SPo_IPoint>		
#define VPARR_SPo_DPoint2D		vector<SPo_DPoint2D>	
#define VPARR_SPo_FPoint2D		vector<SPo_FPoint2D>	
#define VPARR_SPo_IPoint2D		vector<SPo_IPoint2D>
#define VPARR_PPTR_POINT		vector<PPTR_POINT>	
#define VPARR_PPTR_CPoint		vector<PPTR_CPoint>			
#define VPARR_PPTR_Point		vector<PPTR_Point>			
#define VPARR_PPTR_PointF		vector<PPTR_PointF>			
#define VPARR_PPTR_SPo_DPoint	vector<PPTR_SPo_DPoint>		
#define VPARR_PPTR_SPo_FPoint	vector<PPTR_SPo_FPoint>		
#define VPARR_PPTR_SPo_IPoint	vector<PPTR_SPo_IPoint>		
#define VPARR_PPTR_SPo_DPoint2D	vector<PPTR_SPo_DPoint2D>	
#define VPARR_PPTR_SPo_FPoint2D	vector<PPTR_SPo_FPoint2D>	
#define VPARR_PPTR_SPo_IPoint2D	vector<PPTR_SPo_IPoint2D>	
//////////////////////////////////////////////////////////////////////////

inline POINT *TplGetPointRefInPoints(PPTR_POINT plst,int iIndex){return &(plst[iIndex]);};
inline CPoint *TplGetPointRefInPoints(PPTR_CPoint plst,int iIndex){return &(plst[iIndex]);};
inline Point *TplGetPointRefInPoints(PPTR_Point plst,int iIndex){return &(plst[iIndex]);};
inline PointF *TplGetPointRefInPoints(PPTR_PointF plst,int iIndex){return &(plst[iIndex]);};
inline SPo_DPoint *TplGetPointRefInPoints(PPTR_SPo_DPoint plst,int iIndex){return &(plst[iIndex]);};
inline SPo_FPoint *TplGetPointRefInPoints(PPTR_SPo_FPoint plst,int iIndex){return &(plst[iIndex]);};
inline SPo_IPoint *TplGetPointRefInPoints(PPTR_SPo_IPoint plst,int iIndex){return &(plst[iIndex]);};
inline SPo_DPoint2D *TplGetPointRefInPoints(PPTR_SPo_DPoint2D plst,int iIndex){return &(plst[iIndex]);};
inline SPo_FPoint2D *TplGetPointRefInPoints(PPTR_SPo_FPoint2D plst,int iIndex){return &(plst[iIndex]);};
inline SPo_IPoint2D *TplGetPointRefInPoints(PPTR_SPo_IPoint2D plst,int iIndex){return &(plst[iIndex]);};

inline POINT *TplGetPointRefInPoints(VPARR_POINT *plst,int iIndex){return (*plst).begin()+iIndex;};
inline CPoint *TplGetPointRefInPoints(VPARR_CPoint *plst,int iIndex){return (*plst).begin()+iIndex;};
inline Point *TplGetPointRefInPoints(VPARR_Point *plst,int iIndex){return (*plst).begin()+iIndex;};
inline PointF *TplGetPointRefInPoints(VPARR_PointF *plst,int iIndex){return (*plst).begin()+iIndex;};
inline SPo_DPoint *TplGetPointRefInPoints(VPARR_SPo_DPoint *plst,int iIndex){return (*plst).begin()+iIndex;};
inline SPo_FPoint *TplGetPointRefInPoints(VPARR_SPo_FPoint *plst,int iIndex){return (*plst).begin()+iIndex;};
inline SPo_IPoint *TplGetPointRefInPoints(VPARR_SPo_IPoint *plst,int iIndex){return (*plst).begin()+iIndex;};
inline SPo_DPoint2D *TplGetPointRefInPoints(VPARR_SPo_DPoint2D *plst,int iIndex){return (*plst).begin()+iIndex;};
inline SPo_FPoint2D *TplGetPointRefInPoints(VPARR_SPo_FPoint2D *plst,int iIndex){return (*plst).begin()+iIndex;};
inline SPo_IPoint2D *TplGetPointRefInPoints(VPARR_SPo_IPoint2D *plst,int iIndex){return (*plst).begin()+iIndex;};

inline POINT *TplGetPointRefInPoints(VPARR_PPTR_POINT *plst,int iIndex){return *((*plst).begin()+iIndex);};
inline CPoint *TplGetPointRefInPoints(VPARR_PPTR_CPoint *plst,int iIndex){return *((*plst).begin()+iIndex);};
inline Point *TplGetPointRefInPoints(VPARR_PPTR_Point *plst,int iIndex){return *((*plst).begin()+iIndex);};
inline PointF *TplGetPointRefInPoints(VPARR_PPTR_PointF *plst,int iIndex){return *((*plst).begin()+iIndex);};
inline SPo_DPoint *TplGetPointRefInPoints(VPARR_PPTR_SPo_DPoint *plst,int iIndex){return *((*plst).begin()+iIndex);};
inline SPo_FPoint *TplGetPointRefInPoints(VPARR_PPTR_SPo_FPoint *plst,int iIndex){return *((*plst).begin()+iIndex);};
inline SPo_IPoint *TplGetPointRefInPoints(VPARR_PPTR_SPo_IPoint *plst,int iIndex){return *((*plst).begin()+iIndex);};
inline SPo_DPoint2D *TplGetPointRefInPoints(VPARR_PPTR_SPo_DPoint2D *plst,int iIndex){return *((*plst).begin()+iIndex);};
inline SPo_FPoint2D *TplGetPointRefInPoints(VPARR_PPTR_SPo_FPoint2D *plst,int iIndex){return *((*plst).begin()+iIndex);};
inline SPo_IPoint2D *TplGetPointRefInPoints(VPARR_PPTR_SPo_IPoint2D *plst,int iIndex){return *((*plst).begin()+iIndex);};

template<class PNTSLSTPTR,class TYPE> inline void TplGetXYCoordPointsList(PNTSLSTPTR pPntsList,int iIndex,TYPE &gsx,TYPE &gsy){TplGetXYCoordPoint(*TplGetPointRefInPoints(pPntsList,iIndex),gsx,gsy);};
template<class PNTSLSTPTR,class TYPE> inline void TplSetXYCoordPointsList(PNTSLSTPTR pPntsList,int iIndex,TYPE &gsx,TYPE &gsy){TplSetXYCoordPoint(*TplGetPointRefInPoints(pPntsList,iIndex),gsx,gsy);};
//�˴�����ͬʱȡxyֵ�������ڷֱ����ȡx��ȡy�ĺ���ִ��Ч���ǵ���һ��ͬʱȡxy�������������ʶ�����Ч�ʸߵķ�ʽ
//����ǰ�����ʾ����ֵ////hls added 20111106
//�����ȡֵbSet=false,ȡ��ֵ����gsx��gsy����������bSet=true,gsx��gsyֵ��д��pDest��
template<class TYPE> inline void TplGetXYCoordPoint(PointF &pDest,TYPE &gsx,TYPE &gsy){gsx=(TYPE)(pDest.X);gsy=(TYPE)(pDest.Y);};
template<class TYPE> inline void TplGetXYCoordPoint(Point &pDest,TYPE &gsx,TYPE &gsy){gsx=(TYPE)(pDest.X);gsy=(TYPE)(pDest.Y);};
template<class TYPE> inline void TplGetXYCoordPoint(POINT &pDest,TYPE &gsx,TYPE &gsy){gsx=(TYPE)(pDest.x);gsy=(TYPE)(pDest.y);};
template<class TYPE> inline void TplGetXYCoordPoint(CPoint &pDest,TYPE &gsx,TYPE &gsy){gsx=(TYPE)(pDest.x);gsy=(TYPE)(pDest.y);};
template<class TYPE1,class TYPE2> inline void TplGetXYCoordPoint(SPo_TplPoint2D<TYPE1> &pDest,TYPE2 &gsx,TYPE2 &gsy){gsx=(TYPE2)(pDest.x);gsy=(TYPE2)(pDest.y);};
template<class TYPE1,class TYPE2> inline void TplGetXYCoordPoint(SPo_TplPoint<TYPE1> &pDest,TYPE2 &gsx,TYPE2 &gsy){gsx=(TYPE2)(pDest.x);gsy=(TYPE2)(pDest.y);};
////////////////////////��ʱʹ�õ��ָ��//////////////////////////////////////////////////
template<class TYPE> inline void TplGetXYCoordPoint(PointF *pDest,TYPE &gsx,TYPE &gsy){gsx=(TYPE)(pDest->X);gsy=(TYPE)(pDest->Y);};
template<class TYPE> inline void TplGetXYCoordPoint(Point *pDest,TYPE &gsx,TYPE &gsy){gsx=(TYPE)(pDest->X);gsy=(TYPE)(pDest->Y);};
template<class TYPE> inline void TplGetXYCoordPoint(POINT *pDest,TYPE &gsx,TYPE &gsy){gsx=(TYPE)(pDest->x);gsy=(TYPE)(pDest->y);};
template<class TYPE> inline void TplGetXYCoordPoint(CPoint *pDest,TYPE &gsx,TYPE &gsy){gsx=(TYPE)(pDest->x);gsy=(TYPE)(pDest->y);};
template<class TYPE1,class TYPE2> inline void TplGetXYCoordPoint(SPo_TplPoint2D<TYPE1> *pDest,TYPE2 &gsx,TYPE2 &gsy){gsx=(TYPE2)(pDest->x);gsy=(TYPE2)(pDest->y);};
template<class TYPE1,class TYPE2> inline void TplGetXYCoordPoint(SPo_TplPoint<TYPE1> *pDest,TYPE2 &gsx,TYPE2 &gsy){gsx=(TYPE2)(pDest->x);gsy=(TYPE2)(pDest->y);};

//�˴�����ͬʱȡxyֵ�������ڷֱ����ȡx��ȡy�ĺ���ִ��Ч���ǵ���һ��ͬʱȡxy�������������ʶ�����Ч�ʸߵķ�ʽ
//����ǰ�����ʾ����ֵ////hls added 20111106
//�����ȡֵbSet=false,ȡ��ֵ����gsx��gsy����������bSet=true,gsx��gsyֵ��д��pDest��
template<class TYPE> inline void TplSetXYCoordPoint(PointF &pDest,TYPE &gsx,TYPE &gsy){pDest.X=gsx;pDest.Y=gsy;};
template<class TYPE> inline void TplSetXYCoordPoint(Point &pDest,TYPE &gsx,TYPE &gsy){pDest.X=gsx;pDest.Y=gsy;};
template<class TYPE> inline void TplSetXYCoordPoint(POINT &pDest,TYPE &gsx,TYPE &gsy){pDest.x=gsx;pDest.y=gsy;};
template<class TYPE> inline void TplSetXYCoordPoint(CPoint &pDest,TYPE &gsx,TYPE &gsy){pDest.x=gsx;pDest.y=gsy;};
template<class TYPE1,class TYPE2> inline void TplSetXYCoordPoint(SPo_TplPoint2D<TYPE1> &pDest,TYPE2 &gsx,TYPE2 &gsy){pDest.x=gsx;pDest.y=gsy;};
template<class TYPE1,class TYPE2> inline void TplSetXYCoordPoint(SPo_TplPoint<TYPE1> &pDest,TYPE2 &gsx,TYPE2 &gsy){pDest.x=gsx;pDest.y=gsy;};
////////////////////////��ʱʹ�õ��ָ��//////////////////////////////////////////////////
template<class TYPE> inline void TplSetXYCoordPoint(PointF *pDest,TYPE &gsx,TYPE &gsy){pDest->X=gsx;pDest->Y=gsy;};
template<class TYPE> inline void TplSetXYCoordPoint(Point *pDest,TYPE &gsx,TYPE &gsy){pDest->X=gsx;pDest->Y=gsy;};
template<class TYPE> inline void TplSetXYCoordPoint(POINT *pDest,TYPE &gsx,TYPE &gsy){pDest->x=gsx;pDest->y=gsy;};
template<class TYPE> inline void TplSetXYCoordPoint(CPoint *pDest,TYPE &gsx,TYPE &gsy){pDest->x=gsx;pDest->y=gsy;};
template<class TYPE1,class TYPE2> inline void TplSetXYCoordPoint(SPo_TplPoint2D<TYPE1> *pDest,TYPE2 &gsx,TYPE2 &gsy){pDest->x=gsx;pDest->y=gsy;};
template<class TYPE1,class TYPE2> inline void TplSetXYCoordPoint(SPo_TplPoint<TYPE1> *pDest,TYPE2 &gsx,TYPE2 &gsy){pDest->x=gsx;pDest->y=gsy;};

#define PPTR_RECT RECT *
#define PPTR_CRect CRect *
#define PPTR_Rect Rect *
#define PPTR_RectF RectF *
#define PPTR_DRect SPo_DRect *
#define PPTR_FRect SPo_FRect *
#define PPTR_IRect SPo_IRect *
#define PPTR_LRect SPo_LRect *

template<class TYPE> inline void PtlGSXYMaxMinOfRect(PPTR_RECT pRect,TYPE &xmin,TYPE &ymin,TYPE &xmax,TYPE &ymax,bool bset=false)
{
	if(bset){pRect->left=xmin;pRect->right=xmax;pRect->top=ymin;pRect->bottom=ymax;}
	else{xmin=min(pRect->left,pRect->right);xmax=max(pRect->left,pRect->right);ymin=min(pRect->top,pRect->bottom);ymax=max(pRect->top,pRect->bottom);}
};
template<class TYPE> inline void PtlGSXYMaxMinOfRect(PPTR_CRect pRect,TYPE &xmin,TYPE &ymin,TYPE &xmax,TYPE &ymax,bool bset=false)
{
	if(bset){pRect->left=xmin;pRect->right=xmax;pRect->top=ymin;pRect->bottom=ymax;}
	else{xmin=min(pRect->left,pRect->right);xmax=max(pRect->left,pRect->right);ymin=min(pRect->top,pRect->bottom);ymax=max(pRect->top,pRect->bottom);}
};
template<class TYPE> inline void PtlGSXYMaxMinOfRect(PPTR_Rect pRect,TYPE &xmin,TYPE &ymin,TYPE &xmax,TYPE &ymax,bool bset=false)
{
	if(bset){pRect->X=xmin;pRect->Width=xmax-xmin;pRect->Y=ymin;pRect->Height=ymax-ymin;}
	else{xmin=pRect->X;xmax=xmin+pRect->Width;ymin=pRect->Y;ymax=ymin+pRect->Height;}
};
template<class TYPE> inline void PtlGSXYMaxMinOfRect(PPTR_RectF pRect,TYPE &xmin,TYPE &ymin,TYPE &xmax,TYPE &ymax,bool bset=false)
{
	if(bset){pRect->X=xmin;pRect->Width=xmax-xmin;pRect->Y=ymin;pRect->Height=ymax-ymin;}
	else{xmin=pRect->X;xmax=xmin+pRect->Width;ymin=pRect->Y;ymax=ymin+pRect->Height;}
};
template<class TYPE> inline void PtlGSXYMaxMinOfRect(PPTR_DRect pRect,TYPE &xmin,TYPE &ymin,TYPE &xmax,TYPE &ymax,bool bset=false)
{
	if(bset){pRect->left=xmin;pRect->right=xmax;pRect->top=ymin;pRect->bottom=ymax;}
	else{xmin=min(pRect->left,pRect->right);xmax=max(pRect->left,pRect->right);ymin=min(pRect->top,pRect->bottom);ymax=max(pRect->top,pRect->bottom);}
};
template<class TYPE> inline void PtlGSXYMaxMinOfRect(PPTR_FRect pRect,TYPE &xmin,TYPE &ymin,TYPE &xmax,TYPE &ymax,bool bset=false)
{
	if(bset){pRect->left=xmin;pRect->right=xmax;pRect->top=ymin;pRect->bottom=ymax;}
	else{xmin=min(pRect->left,pRect->right);xmax=max(pRect->left,pRect->right);ymin=min(pRect->top,pRect->bottom);ymax=max(pRect->top,pRect->bottom);}
};
template<class TYPE> inline void PtlGSXYMaxMinOfRect(PPTR_IRect pRect,TYPE &xmin,TYPE &ymin,TYPE &xmax,TYPE &ymax,bool bset=false)
{
	if(bset){pRect->left=xmin;pRect->right=xmax;pRect->top=ymin;pRect->bottom=ymax;}
	else{xmin=min(pRect->left,pRect->right);xmax=max(pRect->left,pRect->right);ymin=min(pRect->top,pRect->bottom);ymax=max(pRect->top,pRect->bottom);}
};
template<class TYPE> inline void PtlGSXYMaxMinOfRect(PPTR_LRect pRect,TYPE &xmin,TYPE &ymin,TYPE &xmax,TYPE &ymax,bool bset=false)
{
	if(bset){pRect->left=xmin;pRect->right=xmax;pRect->top=ymin;pRect->bottom=ymax;}
	else{xmin=min(pRect->left,pRect->right);xmax=max(pRect->left,pRect->right);ymin=min(pRect->top,pRect->bottom);ymax=max(pRect->top,pRect->bottom);}
};

//��ox��oyΪԲ�ģ���תһ���ĽǶȺ��ڲ�ת����ѡװ�����յѿ�������ϵΪ׼��
template <class TYPE1,class TYPE2> void TplP2RotateTrans(TYPE1 &ox,TYPE1 &oy,TYPE2 *pmodx,TYPE2 *pmody,double dAngHudu,bool bNewRadis=false,double dNewR=0,bool bDikar=false)
{
	double dx=0;double dy=0;
	dx=*pmodx-ox;dy=*pmody-oy;
	*pmodx = ox+dx*cos(dAngHudu)-dy*sin(dAngHudu);
	*pmody = oy+dx*sin(dAngHudu)+dy*cos(dAngHudu);
	if(bNewRadis)
	{
		double dang=GetAngleRad(ox,oy,*pmodx,*pmody);
		if(bDikar)dang=AngleRad_SCRTODCR(dang);

		SPo_DPoint2D dpr = GetPtFromPtAndLength(dNewR,SPo_DPoint2D(ox,oy),dang);
		*pmodx = dpr.x;
		*pmody = dpr.y;
	}
};

//brief
//     ���α任������������
//##ModelId=4B2B8A74037B
enum tagpoenumTransformDirection { 
    //brief
    //     ����
	//##ModelId=4B2B8A74039A
    FORWARD = 0, 
    //brief
    //     ����
	//##ModelId=4B2B8A7403A9
    REVERSE = 1 };

//##ModelId=4B2B8A7403B9
typedef tagpoenumTransformDirection poenumTransformDirection;

#include "GeometryCalculator.h"
#include "IGeo_Geometry.h"
#include "IGeo_Annotation.h"
#include "IGeo_Point.h"
#include "IGeo_Curve.h"
#include "IGeo_MultiLineString.h"
#include "IGeo_Surface.h"
#include "IGeo_MultiSurface.h"
#include "IGeo_Ellipse.h"
#include "IGeo_Rect.h"
#include "IGeo_Polygon.h"
#include "IGeo_Line.h"
#include "IGeo_CircularArc.h"
#include "IGeo_EllipticArc.h"
#include "IGeo_CircularArc.h"
#include "IGeo_BazierCurve.h"
#include "IGeo_PolyCurve.h"
#include "IGeo_LineString.h"
#include "IGeo_PolyLine.h"
#include "IGeo_MultiPoint.h"

////////////////����ͶӰת����ȫ������洢����������ʹ�ã���Լ����ת����������뱾���ڴ��ʱ��///////////////////////////////////////////////
PRJCOORIDATE CvsProCoord;
GEOCOORIDATE CvsGeoCoord;
///////////////////��ͼ���ݵĴӵ��������뵽��������(�ס����ס����׵����ⵥλ)��ת��///////////////////////////////////////////////////////
///////////////////IPo_ProjCoordSys *pPjs�Ѿ���ʼ���õ�ת��ͶӰ����ϵ����///////////////////////////////////////////////////////
///////////////////SPo_TplPoint2D<TYPE1> *pCio���Ǵ������Ҳ�Ǵ�������������������꣬��������������������ϵ����///////////////////////////////////////////////////////
///////////////////SPo_FPoint fDataOffsetScl����ת������������X��Y�ֱ���x��y����ƫ�ƣ�����Z����ת������Scale///////////////////////////////////////////////////////
template<class TYPE1> inline void CoordGeoToDataChart(IPo_ProjCoordSys *pPjs,SPo_TplPoint2D<TYPE1> *pCio,SPo_FPoint fDataOffsetScl)
{
	CvsGeoCoord.dL = pCio->x/3600;
	CvsGeoCoord.dB = pCio->y/3600;
	pPjs->Forward(1,&CvsGeoCoord,&CvsProCoord);
	pCio->x = (CvsProCoord.dY-fDataOffsetScl.y)/fDataOffsetScl.z;
	pCio->y = (CvsProCoord.dX-fDataOffsetScl.x)/fDataOffsetScl.z;	
}
///////////////////��ͼ���ݵĴӵ��������뵽��������(�ס����ס����׵����ⵥλ)��ת��///////////////////////////////////////////////////////
///////////////////IPo_ProjCoordSys *pPjs�Ѿ���ʼ���õ�ת��ͶӰ����ϵ����///////////////////////////////////////////////////////
///////////////////SPo_TplRect<TYPE1> *pRc���Ǵ������Ҳ�Ǵ�������������������꣬��������������������ϵ����///////////////////////////////////////////////////////
///////////////////SPo_FPoint fDataOffsetScl����ת������������X��Y�ֱ���x��y����ƫ�ƣ�����Z����ת������Scale///////////////////////////////////////////////////////
template<class TYPE1> inline void CoordGeoToDataChart(IPo_ProjCoordSys *pPjs,SPo_TplRect<TYPE1> *pRc,SPo_FPoint fDataOffsetScl)
{
	SPo_TplPoint2D<TYPE1> lt;SPo_TplPoint2D<TYPE1> rb;
	CoordGeoToDataChart(pPjs,&lt,fDataOffsetScl);CoordGeoToDataChart(pPjs,&rb,fDataOffsetScl);
	pRc->left = lt.x;pRc->top = lt.y;
	pRc->right = rb.x;pRc->bottom = rb.y;
}
///////////////////��ͼ���ݵĴ���������(�ס����ס����׵����ⵥλ)�������������ת��///////////////////////////////////////////////////////
///////////////////IPo_ProjCoordSys *pPjs�Ѿ���ʼ���õ�ת��ͶӰ����ϵ����///////////////////////////////////////////////////////
///////////////////SPo_TplPoint2D<TYPE1> *pCio���Ǵ������Ҳ�Ǵ���������������������ϵ���꣬�����������ĵ�������///////////////////////////////////////////////////////
///////////////////SPo_FPoint fDataOffsetScl����ת������������X��Y�ֱ���x��y����ƫ�ƣ�����Z����ת������Scale///////////////////////////////////////////////////////
template<class TYPE1> inline void CoordDataToGeoChart(IPo_ProjCoordSys *pPjs,SPo_TplPoint2D<TYPE1> *pCio,SPo_FPoint fDataOffsetScl)
{
	CvsProCoord.dY = (pCio->x)*fDataOffsetScl.z+fDataOffsetScl.y;
	CvsProCoord.dX = (pCio->y)*fDataOffsetScl.z+fDataOffsetScl.x;
	pPjs->Inverse(1,&CvsProCoord,&CvsGeoCoord);
	pCio->x = 3600*CvsGeoCoord.dL;
	pCio->y = 3600*CvsGeoCoord.dB;
}
///////////////////��ͼ���ݵĴ���������(�ס����ס����׵����ⵥλ)�������������ת��///////////////////////////////////////////////////////
///////////////////IPo_ProjCoordSys *pPjs�Ѿ���ʼ���õ�ת��ͶӰ����ϵ����///////////////////////////////////////////////////////
///////////////////SPo_TplRect<TYPE1> *pRc���Ǵ������Ҳ�Ǵ���������������������ϵ���꣬�����������ĵ�������///////////////////////////////////////////////////////
///////////////////SPo_FPoint fDataOffsetScl����ת������������X��Y�ֱ���x��y����ƫ�ƣ�����Z����ת������Scale///////////////////////////////////////////////////////
template<class TYPE1> inline void CoordDataToGeoChart(IPo_ProjCoordSys *pPjs,SPo_TplRect<TYPE1> *pRc,SPo_FPoint fDataOffsetScl)
{
	SPo_TplPoint2D<TYPE1> lt;SPo_TplPoint2D<TYPE1> rb;
	CoordDataToGeoChart(pPjs,&lt,fDataOffsetScl);CoordDataToGeoChart(pPjs,&rb,fDataOffsetScl);
	pRc->left = lt.x;pRc->top = lt.y;
	pRc->right = rb.x;pRc->bottom = rb.y;
}

//////////////////////
inline void GpDrawArcCustom(Graphics *pGp, Pen *pPen, RectF fRect, PointF ptStart, PointF ptEnd)
{
	//GDI+���ε����ĵ�
	PointF MiddleOfRect(fRect.X+fRect.Width/2,fRect.Y+fRect.Height/2);
	
	float sx = ptStart.X-MiddleOfRect.X;
	float sy = ptStart.Y-MiddleOfRect.Y;
	double sAngle = atan2(sy,sx);
	//�õ���ʼ��
	double sRealAngle = sAngle*180/PO_PI;
	
	float ex = ptEnd.X-MiddleOfRect.X;
	float ey = ptEnd.Y-MiddleOfRect.Y;
	double eAngle = atan2(ey,ex);
	//�õ���ֹ��
	double eRealAngle = eAngle*180/PO_PI;
	//�����ӹ���
	double SweepAngle=0;
	//��ʼ�Ǻͽ����Ƕ����ڻ������
	if(sRealAngle>=0&&eRealAngle>=0)
	{
		if(sRealAngle>eRealAngle)
		{
			SweepAngle = -(fabs(sRealAngle-eRealAngle));
		}
		else
		{
			SweepAngle = (fabs(sRealAngle-eRealAngle))-360;
		}		
	}
	//��ʼ�Ǻͽ����Ƕ�С����
	if(sRealAngle<0&&eRealAngle<0)
	{
		if(sRealAngle>eRealAngle)
		{
			SweepAngle = -(fabs(sRealAngle-eRealAngle));
		}
		else
		{
			SweepAngle = (fabs(sRealAngle-eRealAngle))-360;
		}		
	}
	
	//��ʼ�Ǻͽ����ǵķ����෴
	if(sRealAngle<0&&eRealAngle>0)
	{
		SweepAngle = eRealAngle-sRealAngle-360;	
	}
	if(sRealAngle>0&&eRealAngle<0)
	{
		SweepAngle =eRealAngle-sRealAngle;
	}
	
	pGp->DrawArc(pPen,fRect,sRealAngle,SweepAngle);
}

//\             /
// \           /
//  \         /
//   \---1---/
//   |\     /|   
//   | \   / |
//   |  \ /  |
//   4   \   2
//   |  / \  |
//   | /   \ |    
//   |/     \|
//   /---3---\
//  /         \
// /           \
///             \
//
//��ͼ��ʾ�������οռ�ֳ�4��������λ��ǵ㰴����4�����ֱ�
extern "C" __declspec(dllexport) int RbzSort4RgnPointers(int iIndex,PointF *pvPointers/*Ԥ���巵�ؽڵ����꣬����������nLocs��*/,SPo_DPoint *pLocations,int nLocs,SPo_DRect dRc);

//����ĳ�����ϱ�ָ���ֳɵĻ�����(���α�ע����Բ�Ǿ��α�ע)
extern "C" __declspec(dllexport) int RbzrGetDivsionSegs(int n);

//��������α�ע��4�����߷ֶ�λ��
extern "C" __declspec(dllexport) void GetRbz4RgnPosXY(vector<PointF> *pvedgepos,SPo_DRect dRc,SPo_DPoint *pLocations,int nLocs);

//�����Բ�Ǿ��α�ע��4�����߷ֶ�λ��
extern "C" __declspec(dllexport) void GetRbz4RgnPosXYRrc(GraphicsPath *pPath,SPo_DRect dRc,SPo_DPoint *pLocations,int nLocs);
//
extern "C" __declspec(dllexport) void DrawRbz4RgnPosXYRrc(CDC *pDC,SPo_DRect dRc,SPo_DPoint *pLocations,int nLocs);

#endif /* GEO_COMMONDEF_H_HEADER_INCLUDED_B93766E5 */
