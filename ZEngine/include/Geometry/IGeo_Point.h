#ifndef IGEO_POINT_H_HEADER_INCLUDED_B9D30AB5
#define IGEO_POINT_H_HEADER_INCLUDED_B9D30AB5
#include "IGeo_Geometry.h"
class IPo_SpatialReference;

//brief
//     �������ζ���--�����ӿ�
//##ModelId=442B2E28008C
class IGeo_Point : public IGeo_Geometry
{
  public:
    //brief
    //     ���ö�λ�㡣
    //     ���ݸ����Ŀռ�ο�ϵ���ö�λ�㡣
    //return
    //      ��λ�����óɹ�������true; ��     pSpatialReference��Ϊ�գ�������ת�����ɹ�    ���򷵻�false��
    //param
    //      sPoint: �����õĶ�λ�㡣
    //      pSpatialReference: ��λ���Ӧ�Ŀռ�ο�ϵ     ��ȱʡΪNULL����ʾʹ�õ㱾��Ŀռ�ο�ϵ��
    //##ModelId=4562578F0148
    virtual bool SetPoint(SPo_DPoint sPoint, IPo_SpatialReference* pSpatialReference = NULL, 
        // Ҫ���õ������������,�����ʵ���,�ڲ�ֻ����һ��������,����������,0���������һ��,1��������ڶ��㼴���������.
        int iIndex = 0) = 0;

    /// \brief ���÷���㡣
    /// 
    /// ���ݸ����Ŀռ�ο�ϵ���÷���㡣
    /// 
    /// \return ��������óɹ����򷵻�true����pSpatialReference��Ϊ�գ�������ת�����ɹ����򷵻�false��
    /// 
    /// \param sPoint: �����õķ���㡣
    /// \param pSpatialReference: ������Ӧ�Ŀռ�ο�ϵ��ȱʡΪNULL����ʾʹ�õ㱾��Ŀռ�ο�ϵ��
    /// 
    //##ModelId=4563EF6F0280
    virtual SPo_DPoint GetPoint(int iIndex = 0, IPo_SpatialReference* pSpatialReference = NULL) = 0;

    //brief
    //     ���÷���㡣
    //     ���ݸ����Ŀռ�ο�ϵ���÷���㡣
    //return
    //     ��������óɹ����򷵻�true����    pSpatialReference��Ϊ�գ�������ת�����ɹ���    �򷵻�false��
    //param
    //     sPoint: �����õķ���㡣
    //     pSpatialReference: ������Ӧ�Ŀռ�ο�ϵ��    ȱʡΪNULL����ʾʹ�õ㱾��Ŀռ�ο�ϵ��
    //##ModelId=4562578F0177
    virtual bool SetDirectionPoint(SPo_DPoint sPoint, IPo_SpatialReference* pSpatialReference = NULL) = 0;

    //brief
    //     ��ȡ����㡣
    //     ���ݸ����Ŀռ�ο�ϵ��ȡ���������ꡣ
    //return
    //     ���������ꡣ
    //param
    //      pSpatialReference: ϣ������ȡ�ķ�����Ӧ     �Ŀռ�ο�ϵ��ȱʡΪNULL����ʾʹ�õ㱾���
    // �ռ�ο�ϵ��
    //      ��ע : ��pSpatialReference��Ϊ�գ�������ת     �����ɹ����򷵻�SGIS_Point(0,0)��
    //##ModelId=4562578F01B5
    virtual SPo_DPoint GetDirectionPoint(IPo_SpatialReference* pSpatialReference = NULL) = 0;

    //brief
    //     ����������������ľ��룬��λ��õ����    �ĵ�λ��ͬ��
    //return
    //     �ɹ����ص������������ľ��룬���򷵻ظ�    ֵ��
    //param
    //     pGeo: ��������
    //##ModelId=4562578F01D4
//    virtual double GetDistanceTo(const IGeo_Geometry* pGeo) = 0;

    //brief
    //     ��ȡIDֵ�������û����
    //return
    //     IDֵ
    //##ModelId=4563FB7C030D
    virtual unsigned long GetID() = 0;

    //brief
    //     ����IDֵ�������û����
    //param
    //     lValue:IDֵ
    //return
    //     ���óɹ�����true
    //##ModelId=4563FBAB001F
    virtual bool SetID(unsigned long lValue) = 0;

    //brief
    //     ��ȡMeasureֵ���������綯̬�ֶεȷ���
    //param
    //     ��
    //return
    //     Measureֵ
    //##ModelId=4563FBFC00CB
    virtual double GetM() = 0;

    //brief
    //     ����Measureֵ���������綯̬�ֶεȷ���
    //param
    //     dM:Measureֵ
    //return
    //     ���óɹ�����true
    //##ModelId=4563FC3A038A
    virtual bool SetM(double dM) = 0;

};



#endif /* IGEO_POINT_H_HEADER_INCLUDED_B9D30AB5 */
