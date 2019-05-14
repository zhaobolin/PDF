#ifndef IGEO_CURVE_H_HEADER_INCLUDED_B9D3394C
#define IGEO_CURVE_H_HEADER_INCLUDED_B9D3394C

#include "IGeo_Geometry.h"

class IGeo_Point;
class IGeo_Line;


//brief
//     ����
//##ModelId=4564FBB903B9
class IGeo_Curve : public IGeo_Geometry
{
  public:
    //brief
    //     �õ���ʼ��
    // 
    //param  
    //     pPoint:������ʼ��
    // 
    //return
    //     �ɹ����أ�����true
    //##ModelId=4565005D0203
    virtual bool GetFromPoint(IGeo_Point * pPoint) = 0;

    //brief
    //     ������ʼ��
    // 
    //param
    //     rPoint:��ʼ����Ϣ
    // 
    //return
    //     �ɹ�������true
    //##ModelId=4565092E0196
    virtual bool SetFromPoint(IGeo_Point& rPoint) = 0;

    //brief
    //     �õ�������
    // 
    //param
    //     pPoint:���ؽ�����
    // 
    //return
    //     �ɹ���ȡ������true
    //##ModelId=4565097D030D
    virtual bool GetToPoint(IGeo_Point * pPoint) = 0;

    //brief
    //     ���ý�����
    // 
    //param
    //     rPoint:����Ϣ
    // 
    //return
    //     �ɹ�������true
    //##ModelId=4565097D03B9
    virtual bool SetToPoint(IGeo_Point& rPoint) = 0;

    //brief
    //     �Ƿ���
    // 
    //return
    //     �����գ�����true
    //##ModelId=456509B700FA
    virtual bool IsClosed() = 0;

    //brief
    //     �õ����߳���
    // 
    //return
    //     ���߳���
    //##ModelId=456509CE00EA
    virtual double GetLength() = 0;

    //brief
    //     ��ȡ������
    // 
    //param
    //     fromDistance:����ʼ�����
    //     toDistance:����������
    //     asRatio:true,�����԰ٷֱȶ���
    //     outSubCurve:����������
    //return
    //     ��ȡ�ɹ�������true
    //##ModelId=45650A17029F
    virtual bool GetSubCurve(double fromDistance, double toDistance, bool asRatio, IGeo_Curve* outSubCurve) = 0;

    //brief
    //     �������ʼ��һ����������ߵķ���
    // 
    //param
    //     cExtent:�߶���չ��ʽ
    //     dDistance:��������ʼ��λ��
    //     asRatio:���밴�ٷֱȶ���,true
    //     dLength:���߳���
    //     pLine:���ط��߶���
    // 
    //return
    //     �ɹ�������true
    //##ModelId=45650C55007D
    virtual bool QueryNormal(
        //�߶���չ��ʽ
        poenumSegmentExtent cExtension, 
        //distance to from point
        double dDistance, bool bRatio, 
        //���߳���
        double dLength, IGeo_Line *pLine) = 0;

    //brief
    //     ��ȡ����λ�����ߵ�����
    // 
    //param
    //     cExtent:�߶���չ��ʽ
    //     dDistance:��������ʼ��λ��
    //     asRatio:���밴�ٷֱȶ���,true
    //     dLength:���߳���
    //     pLine:���ط��߶���
    // 
    //return
    //     �ɹ�������true
    //##ModelId=45650D28033C
    virtual bool QueryTangent(
        //�߶���չ��ʽ
        poenumSegmentExtent cExtension, 
        //distance to from point
        double dDistance, bool bRatio, 
        //���߳���
        double dLength, IGeo_Line *pLine) = 0;

    //brief
    //     ��ȡ������ʼ��ĳ���ĵ����
    // 
    //param
    //     cExtent:�߶���չ��ʽ
    //     dDistance:��������ʼ��λ��
    //     asRatio:���밴�ٷֱȶ���,true
    //     dLength:���߳���
    //     pPoint:���ص����
    // 
    //return
    //     �ɹ�������true
    //##ModelId=45650D700148
    virtual bool QueryPoint(
        //�߶���չ��ʽ
        poenumSegmentExtent cExtension, 
        //distance to from point
        double dDistance, bool bRatio, IGeo_Point *& pPoint) = 0;

    //brief
    //     ��������֪������������ϵĵ㣬������ĵ����ʼ��ľ��룬�����������ߵľ��룬�Ƿ��������Ҳ�
    // 
    //param
    //     cExtent:�߶���չ��ʽ
    //     pInPoint:�����
    //     pOutPoint:���ص�
    //     dDisAlongCurve:����������ʼ�����
    //     dDisFromCurve:ƫ�����߾���
    //     bRight:�������Ҳ࣬true
    // 
    //return
    //      �ɹ����أ�true
    //     
    //##ModelId=45650E75036B
    virtual bool QueryPointAndDistance(
        //�߶���չ��ʽ
        poenumSegmentExtent cExtension, IGeo_Point* pInPoint, IGeo_Point* pOutPoint, 
        //���������ʼ�����
        double dDisAlongCurve, 
        //��֪�������߾���
        double dDisFromCurve, 
        //��֪���������Ҳ���
        bool bRight) = 0;

    //brief
    //     �л��߶η���
    // 
    //return
    //     �ɹ��л�������true
    //##ModelId=45650FD001F4
    virtual bool ReverseDirection() = 0;

};



#endif /* IGEO_CURVE_H_HEADER_INCLUDED_B9D3394C */
