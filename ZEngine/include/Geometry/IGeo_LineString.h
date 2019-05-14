#ifndef IGEO_LINESTRING_H_HEADER_INCLUDED_B9D37EEB
#define IGEO_LINESTRING_H_HEADER_INCLUDED_B9D37EEB
#include "IGeo_PolyCurve.h"
class IPo_SpatialReference;
class IGeo_Geometry;


//brief
//     �ߴ�����ӿ�
// 
// ���߶Ρ�Բ���ߡ���Բ�ߡ�Bazier����ɵ��ߴ�����ͬ��ArcInfo��Path�����ߵ������ǣ���ɳɷֿ�����԰������Բ����Bazier��������Ϊ���ߵĳ��ࡣ
// ���Լ���ߴ���ʼ����ĩ����ͬ����ΪArcInfo�еĻ���
//##ModelId=442B2F4E0128
class IGeo_LineString : public IGeo_PolyCurve
{
  public:
    //brief
    //     ��������Ӽ��ζ���
    // 
    //     ���ݸ��������ʹ���һ�����ζ���Ϊ�ߴ����Ӹü��ζ���
    // 
    //return
    //     �������ӵļ��ζ����ָ�롣
    // 
    //param
    //     nElementType: ���ӵļ��ζ�������͡�
    // ��ע : �û�Ӧ���ݼ��ζ������ͣ�������ֵǿ��ת��Ϊ��Ӧ��GeoXXXָ�롣
    //##ModelId=456258D203C8
    virtual IGeo_Geometry* CreateElement(poenumGeoType nElementType) = 0;

    //brief
    //     ��ȡ�ߴ��м��ζ���ĸ�����
    // 
    //return
    //     ���ζ���ĸ�����
    //##ModelId=456258D30000
    virtual int GetElementCount() = 0;

    //brief
    //     ��ȡ���ζ���
    //     �����±��ȡ���ζ����ָ�롣
    // 
    //return
    //     ָ���±��Ӧ�ļ��ζ����ָ�롣
    // 
    //param
    //     nIndex: �����ȡ�ļ��ζ�����±ꡣ
    //     ��ע : �û�Ӧ���ݼ��ζ������ͣ�������ֵǿ��ת��Ϊ��Ӧ��GeoXXXָ�롣
    //##ModelId=456258D30010
    virtual IGeo_Geometry* GetElementPtr(int nIndex) = 0;

    //brief
    //     ��ȡ���ζ���
    //     ���ݸ������ȡ���ζ����ָ�롣
    // 
    //return
    //     ��ȡ���ζ����ָ�롣
    // 
    //param
    //     sPoint: ����㡣
    //     dTolerance: ��ѡȡ��ֵ��
    //     pSpatialReference: �������Ӧ�Ŀռ�ο�ϵ��ȱʡΪNULL����ʾʹ�ü��ζ�����Ŀռ�ο�ϵ��
    //     ��ע : �û�Ӧ���ݼ��ζ������ͣ�������ֵǿ��ת��Ϊ��Ӧ��GeoXXXָ�롣
    //##ModelId=456258D3002E
    virtual IGeo_Geometry* GetElementPtr(SPo_DPoint sPoint, double dTolerance = 0.0, IPo_SpatialReference* pSpatialReference = NULL) = 0;

    //brief
    //     ��ȡ���ζ���
    //     ���ݸ������ȡ���ζ����ָ�롣
    // 
    //return
    //     ָ���±��Ӧ�ļ��ζ����ָ�롣
    // 
    //param
    //     pPoint: ��������
    //     dTolerance: ��ѡȡ��ֵ��
    //     ��ע : �û�Ӧ���ݼ��ζ������ͣ�������ֵǿ��ת��Ϊ��Ӧ��GeoXXXָ�롣
    //##ModelId=456258D3007D
    virtual IGeo_Geometry* GetElementPtr(const IGeo_Geometry* pPoint, double dTolerance = 0.0) = 0;

    //brief
    //     ɾ�����ζ���
    //     �����±�λ��ɾ�����ζ���
    // 
    //return
    //     ɾ���ɹ����򷵻�true�����򷵻�false��
    // 
    //param
    //     nIndex: �豻ɾ���ļ��ζ�����±�λ�á�
    //     ��ע : 0<=nIndex<���ζ���������������ζ�����±꽫�����䶯�����ζ��������1��
    //##ModelId=456258D300BB
    virtual bool DeleteElement(int nIndex) = 0;

    //brief
    //     �ø����ļ��ζ����滻���������ļ��ζ���
    // 
    //return
    //     �ɹ�����true�� ���򷵻�false
    // 
    //param
    //     pGeo �����滻���������ļ��ζ���
    //     nIndex ��Ҫ���滻�ļ��ζ��������
    //##ModelId=456258D300EA
    virtual bool ReplaceElement(IGeo_Geometry* pElement, int nIndex) = 0;

    //brief
    //     ��Ӽ��ζ���
    //     ��������һ�����ζ���
    // 
    //return
    //     �ɹ�����true�� ���򷵻�false
    // 
    //param
    //     pGeo : ���ӵļ��ζ���
    //##ModelId=456258D30119
    virtual IGeo_Geometry* AddElement(IGeo_Geometry* pGeo) = 0;

};

typedef IGeo_LineString IGeo_PathString;//Ϊ������Line�ӿ������������������

#endif /* IGEO_LINESTRING_H_HEADER_INCLUDED_B9D37EEB */
