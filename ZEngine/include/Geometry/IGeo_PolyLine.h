#ifndef IGEO_POLYLINE_H_HEADER_INCLUDED_B9D32CC6
#define IGEO_POLYLINE_H_HEADER_INCLUDED_B9D32CC6
#include "IGeo_PolyCurve.h"
class IPo_SpatialReference;
class IGeo_Geometry;

//brief
//     ���߼��ζ���ӿ�
//     ������һϵ�е����Ӷ��ɣ����������β��վ͹��������Polygon�ı߽�
//##ModelId=442B4B58006D
class IGeo_PolyLine : public IGeo_PolyCurve
{
  public:
    //brief
    //     ��Ӷ��㡣
    //     ���ݸ����Ŀռ�ο�ϵ��Ӷ��㡣
    // 
    //return
    //     ��ӳɹ����򷵻�true�����򷵻�false��
    // 
    //param
    //     sPoint: ����ӵĶ������ꡣ
    //     pSpatialReference: ����ӵĶ��������Ӧ�Ŀռ�ο�ϵ��ȱʡΪNULL����ʾʹ�����߱���Ŀռ�ο�ϵ��
    //##ModelId=456259700213
    virtual bool AddPoint(SPo_DPoint sPoint, IPo_SpatialReference* pSpatialReference = NULL) = 0;

    //brief
    //     ��Ӷ��㡣
    //     ���ݸ����Ŀռ�ο�ϵ��Ӷ��㡣
    // 
    //return
    //     ��ӳɹ����򷵻�true�����򷵻�false��
    // 
    //param
    //     pPoint: ����ӵĶ��㣭�����
    //##ModelId=456259700251
    virtual bool AddPoint(const IGeo_Geometry* pPoint) = 0;

    //brief
    //     �������ߵĶ������ꡣ
    //     ���ݸ����Ŀռ�ο�ϵ����ָ���±�Ķ������ꡣ
    // 
    //return
    //     ���óɹ����򷵻�true�����򷵻�false��
    // 
    //param
    //     nIndex: ����������Ķ�����±ꡣ
    //     sPoint: �����õĶ������ꡣ
    //     pSpatialReference: �����õĶ��������Ӧ�Ŀռ�ο�ϵ��ȱʡΪNULL����ʾʹ�����߱���Ŀռ�ο�ϵ��
    //##ModelId=456259700271
    virtual bool SetPoint(int nIndex, SPo_DPoint sPoint, IPo_SpatialReference* pSpatialReference = NULL) = 0;

    //brief
    //     �������ߵĶ������ꡣ
    //     ���ݸ����Ŀռ�ο�ϵ����ָ���±�Ķ������ꡣ
    // 
    //return
    //     ���óɹ����򷵻�true�����򷵻�false��
    // 
    //param
    //     nIndex: ����������Ķ�����±ꡣ
    //     pPoint: �����õĶ��㣭�����
    //##ModelId=4562597002BF
    virtual bool SetPoint(int nIndex, const IGeo_Geometry* pPoint) = 0;

    //brief
    //     �滻���������ɸ����㡣
    //     �ø��������ߵ����ж����滻��������ָ���±귶Χ�Ķ��㡣
    // 
    //return
    //     �滻�ɹ����򷵻�true�����򷵻�false��
    // 
    //param
    //     nBeginIndex: ���滻�������ʼ�±�λ�á�
    //     nEndIndex: ���滻�������ֹ�±�λ�á�
    //     pPolyLine: �����滻��������ߡ�
    //     ��ע :
    // 0<=nBeginIndex,nEndIndex<�������;�滻����ʱ���·����ڴ�;�滻����󣬺���������±꽫�����䶯���������Ҳ���ı䡣
    //##ModelId=4562597002EE
    virtual bool ReplacePointsByIndex(int nBeginIndex, int nEndIndex, const IGeo_Geometry* pPolyLine) = 0;

    //brief
    //     ɾ�����㡣
    //     �����±�λ��ɾ�����㡣
    // 
    //return
    //     ɾ���ɹ����򷵻�true�����򷵻�false��
    // 
    //param
    //     nIndex: �豻ɾ���Ķ�����±�λ�á�
    //##ModelId=45625970033C
    virtual bool DeletePoint(int nIndex) = 0;

    //brief
    //     ɾ�����㡣
    //     ���ݸ����ĵ�����Ϳռ�����ϵɾ�����㡣
    // 
    //return
    //     ɾ���ɹ����򷵻�true�����򷵻�false��
    // 
    //param
    //     sPoint: �豻ɾ���Ķ���λ�á�
    //     pSpatialReference: �������Ӧ�Ŀռ�ο�ϵ��ȱʡΪNULL����ʾʹ�ö���α���Ŀռ�ο�ϵ��
    //            dTolerance: ��ֵ���Ե�ΪԲ�ģ���ֵΪ�뾶��Բ�ڵĶ�����ɾ����
    //##ModelId=45625970035B
    virtual bool DeletePoint(SPo_DPoint * sPoint, IPo_SpatialReference* pSpatialReference = NULL, double dTolerance = 0.0) = 0;

    //brief
    //     �����߷�ա�
    //     �����ߵķ�գ�ʹ����β�������
    // 
    //return
    //     ���߷�ճɹ����򷵻�true�����򷵻�false��
    //##ModelId=4562597003BA
    virtual bool Close() = 0;

    //brief
    //     ��Ӷ��㡣
    //     ���ݸ����Ŀռ�ο�ϵ���±�λ�ã����±�λ�ú���Ӷ��㡣
    // 
    // 
    //return
    //     ��ӳɹ����򷵻�true�����򷵻�false��
    // 
    //param
    //     nIndex: ����Ӷ�����±�λ�á�
    //     sPoint: ����ӵĶ������ꡣ
    //     pSpatialReference: ����ӵĶ��������Ӧ�Ŀռ�ο�ϵ��ȱʡΪNULL����ʾʹ�����߶�����Ŀռ�ο�ϵ��
    //     ��ע : 0<iIndex<�����������Ӷ���ʱ���·����ڴ棻����������±꽫�����䶯�����������1�����ı���ĩ���
    //##ModelId=45625971009C
    virtual bool InsertPoint(int nIndex, SPo_DPoint sPoint, IPo_SpatialReference* pSpatialReference = NULL) = 0;

    //brief
    //     ��Ӷ��㡣
    //     ���ݸ����ĵ㼸�ζ�����±�λ�ã����±�λ�ú���Ӷ��㡣
    // 
    // 
    //return
    //     ��ӳɹ����򷵻�true�����򷵻�false��
    // 
    //param
    //     nIndex: ����Ӷ�����±�λ�á�
    //     pPoint: ����ӵĶ���ĵ����
    // 
    //     ��ע : 0<iIndex<�����������Ӷ���ʱ���·����ڴ棻����������±꽫�����䶯�����������1�����ı���ĩ���
    //##ModelId=4562597100EA
    virtual bool InsertPoint(int nIndex, const IGeo_Geometry* pPoint) = 0;

};



#endif /* IGEO_POLYLINE_H_HEADER_INCLUDED_B9D32CC6 */
