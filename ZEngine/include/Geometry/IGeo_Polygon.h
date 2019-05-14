#ifndef IGEO_POLYGON_H_HEADER_INCLUDED_B9D3434F
#define IGEO_POLYGON_H_HEADER_INCLUDED_B9D3434F
#include "IGeo_Geometry.h"
#include "..\common\SPo_DPoint.h"
class IPo_SpatialReference;
class IGeo_PolyLine;

	//������״����
#define PLNSTYLE_SGLANY 1
		//������״�໷
#define PLNSTYLE_MLTANY 2
		//�������
#define PLNSTYLE_SPZDBX 3
		//ƽ���ı���
#define PLNSTYLE_SPXSBX 4

#define NM_PLNSTYLE_SGLANY "���������"
#define NM_PLNSTYLE_MLTANY "�໷�����"
#define NM_PLNSTYLE_SPZDBX "�������"
#define NM_PLNSTYLE_SPXSBX "ƽ���ı���"
//brief
//     ����Σ����������������������
//##ModelId=442B2F260128
class IGeo_Polygon : public IGeo_Geometry
{
  public:
	//��ȡ��iIndex����������(�ڻ��⻷��)
	//##ModelId=46F8B0990167
    virtual PO_GEORING_TYPE GetRingTypeOf(int iIndex) = 0;
	//��ȡ�����ܸ���
	//##ModelId=46AF55160251
    virtual int GetRingsCount() = 0;
	//��ȡ��index�����Ľڵ����
	//##ModelId=46AF55160253
    virtual int GetRingPointsCountOfIndex(int iIndex) = 0;

    //brief
    //     ���ö�����ڵ㡣
    //     ���ݸ����Ŀռ�ο�ϵ���ڵ��������ö�����ڵ㡣
    //return
    //     �ڵ����óɹ����򷵻�true�����򷵻�false��
    //param
    //      sPoint: �����õ��ڵ����ꡣ
    //      pSpatialReference: �����õ��ڵ������Ӧ��     �ռ�ο�ϵ��ȱʡΪNULL����ʾʹ�ö���α���
    // �Ŀռ�ο�ϵ��
    //##ModelId=45625BBE000F
    virtual bool SetCentralPoint(SPo_DPoint sPoint, IPo_SpatialReference* pSpatialReference = NULL) = 0;

    //brief
    //     ��ȡ����ε��ڵ㡣
    //return
    //     ������ڵ㣻����Ҫ���¼����ڵ㣬�Ҽ��㲻�ɹ����򷵻�SPo_Point (0,0)��
    //param
    //      nMode : ��ȡ��ʽ�����ܵ�ȡֵΪ��
    //      PO_COMPUTE_OFF�������㣬ֱ�ӷ��ص�ǰֵ��ȱʡ�������ã���
    //      PO_COMPUTE_ON�����¼��㣻
    //      PO_COMPUTE_ONCE�����û�м����������㣻     ����ֱ�ӷ��ص�ǰֵ��
    //      pSpatialReference��ϣ����ȡ���ڵ�����Ӧ��     �ռ�ο�ϵ��ȱʡΪNULL����ʾʹ�ö���α���
    // �Ŀռ�ο�ϵ��
    //##ModelId=45625BBE004E
    virtual SPo_DPoint GetCentralPoint(int nMode = GIS_COMPUTE_OFF, IPo_SpatialReference* pSpatialReference = NULL) = 0;

    //brief
    //     ����������ڵ㡣
    //return
    //     �����ɹ����򷵻ض�����ڵ㣬���򷵻�    SPo_Point (0,0)��
    //##ModelId=45625BBE007D
    virtual bool CreateCentralPoint() = 0;

    //brief
    //      ������������ߴ���ա�
    //param
    //      ��
    //return
    //      ��ճɹ�����true
    //��������ΪҪ���еĲ�������
    // 1.���ظ���ŵĸ�����¼����ջ�����������������������һ���ظ��������غϡ�
    // 2.�������붴��������򣬵�����ǰ����������Ϊ�ڣ����뵺�ı�ʾ�պ��෴��
    //##ModelId=45625BBE00FA
    virtual bool CloseAll() = 0;

    //brief
    //     ��ȡ�⻷��Ŀ
    //param
    //     ��
    //return
    //     �⻷��Ŀ 
    //##ModelId=45654C0503D8
    virtual int GetExteriorRingCount() = 0;

    //brief
    //     ��ȡָ�����ߴ��������ڻ���Ŀ
    //param
    //     rRing:ָ�����ߴ�
    //return
    //     �ڻ���Ŀ
    //##ModelId=45654C4F006D
    virtual int GetInteriorRingCount(IGeo_PolyLine* rRing) = 0;

    //brief
    //     ����ָ���ڻ����⻷
    //param
    //     rInterRing:ָ���ڻ�
    //return
    //     �⻷���ߴ�
    //##ModelId=45654CC60148
    virtual IGeo_PolyLine* FindExteriorRing(IGeo_PolyLine* rInterRing) = 0;

    //brief
    //     ��ȡ�����⻷
    //param
    //     ��
    //return
    //     �����⻷����
    //##ModelId=45654D2D0109
    virtual bool GetExteriorRings(IGeo_PolyLine* pExteriorRing) = 0;

    //brief
    //      ����ָ���⻷�������ڻ�
    //param
    //      rExteriorRing:ָ���⻷
    //      pInteriorRings:�����ڻ�
    //return
    //      �ɹ�true
    //##ModelId=45654D7A036B
    virtual bool GetInteriorRings(IGeo_PolyLine* rExteriorRing, IGeo_PolyLine* pInteriorRings) = 0;

    //brief
    //     ��ͼ�α���ʼĩ��
    //param
    //     ��
    //return
    //     �򻯳ɹ�����true
    //##ModelId=45654DC80177
    virtual bool SimplifyPreserveFromTo() = 0;
    //##ModelId=465558DC0157
    virtual bool AddPoint(SPo_DPoint sPoint, IPo_SpatialReference *pSpatialReference) = 0;
	//��ȡ�ڲ��洮��Ϣ���Ա����ⲿ�ٿ�
	virtual vector<int> *GetRingsFramePtr() = 0;
};



#endif /* IGEO_POLYGON_H_HEADER_INCLUDED_B9D3434F */
