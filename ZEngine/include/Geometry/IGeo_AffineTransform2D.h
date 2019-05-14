#ifndef IGEO_AFFINETRANSFORM2D_H_HEADER_INCLUDED_B9D3677E
#define IGEO_AFFINETRANSFORM2D_H_HEADER_INCLUDED_B9D3677E
#include "IGeo_Transformation.h"
class IGeo_Point;
class IGeo_Line;
class IGeo_Envelope;

/// \brief ����任
//##ModelId=442B79B60251
class IGeo_AffineTransform2D : public IGeo_Transformation
{
  public:
    //brief
    //     �Ƿ��巴��
    //return
    //     ��������˷���true
    //##ModelId=456A5CB80251
    virtual bool IsReflective() = 0;

    //brief
    //     �õ���ת�Ƕ�
    //##ModelId=456A5D040157
    virtual double GetRotation() = 0;

    //brief
    //     �ƶ���ʼ��
    //param
    //     rPoint:�µĳ�ʼ��
    //##ModelId=456A5D2701B5
    virtual bool MoveOrigin(IGeo_Point& rPoint) = 0;

    //brief
    //     �õ��ռ�ο�ϵ
    //##ModelId=456A5D8E02AF
    virtual IGeo_SpatialReference GetSpatialReference() = 0;

    //brief
    //     ���ÿռ�ο�ϵ
    //param
    //     rSpatialRef:�¿ռ�ο�ϵ
    //return
    //     ���óɹ�����true
    //##ModelId=456A5DCC005D
    virtual bool SetSpatialReference(IGeo_SpatialReference &rSpatialRef) = 0;

    //brief
    //     �õ�x������ϵ��
    //##ModelId=456A5E310177
    virtual double GetXScale() = 0;

    //brief
    //      �õ�y��������ϵ��
    //##ModelId=456A5E5C02EE
    virtual double GetYScale() = 0;

    //brief
    //     �õ�x����ƽ��ֵ
    //##ModelId=456A5E810109
    virtual double GetXTranslation() = 0;

    //brief
    //     �õ�y����ƽ��ֵ
    //##ModelId=456A5EAC037A
    virtual double GetYTranlation() = 0;

    //brief
    //     �ɿ��Ƶ�Ӱ�䶨��任
    //param  
    //     iPoints:���Ƶ����
    //     pFromPoints:������Ƶ�
    //     pToPoints:ת������Ƶ�
    //return
    //     ����ɹ�����true
    //##ModelId=456A7F4F02FD
    virtual bool DefineFromControlPoints(int iPoints, IGeo_Point* pFromPoints, IGeo_Point* pToPoints) = 0;

    //brief
    //     �ɷ���Ӱ�䶨��任
    //param
    //     pFromEnvelope:�������
    //     pToEnvelope:�������
    //return
    //     ����任�ɹ�����true
    //##ModelId=456A8046006D
    virtual bool DefineFromEnvelope(IGeo_Envelope* pFromEnvelope, IGeo_Envelope* pToEnvelope) = 0;

    //brief
    //     �ɷ��䶨��任
    //param
    //     rLine:��������
    //return
    //     ����任�ɹ�����true
    //##ModelId=456A80F700BB
    virtual bool DefineReflection(IGeo_Line &rLine) = 0;

    //brief
    //     �õ����Ƶ����
    //param
    //     iIndex:����
    //     pdFromError:��Ӧ������ʼ�����
    //     pdToError:  ��Ӧ����Ӱ������
    //return
    //     ȡֵ�ɹ�����true
    //##ModelId=456A81680186
    virtual bool GetControlPointError(int iIndex, doube *pdFromError, double *pdToError) = 0;

    //brief
    //     �ڱ任�м����ƶ�����
    //param
    //     dx\dy:x��y����ƫ����
    //return
    //     ���óɹ�����true
    //##ModelId=456A827200AB
    virtual bool Move(double dx, double dy) = 0;

    //brief
    //     �ڱ任�м�����ת����
    //param
    //     dAngle:��ת�Ƕ�
    //return
    //     ���óɹ�����true
    //##ModelId=456A82ED0251
    virtual bool Rotate(double dAngle) = 0;

    //brief
    //     �ڱ任��������������
    //param
    //     dx\dy:x��y������������
    //##ModelId=456A83480177
    virtual bool Scale(double dx, double dy) = 0;

    //brief
    //     �ڱ��任֮ǰ��Ӧ����һ�任
    //param
    //     rOtherTransform:��һ�任
    //return
    //     ���óɹ�����true
    //##ModelId=456A83CE02FD
    virtual Boolean PreMultiply(IGeo_AffineTransform2D& rOtherTransform) = 0;

    //brief
    //     �ڱ��任֮����Ӧ����һ�任
    //param
    //     rOtherTransform:��һ�任
    //return
    //     ���óɹ�����true
    //##ModelId=456A84730109
    virtual bool PostMultiply(IGeo_AffineTransform2D &rOtherTransform) = 0;

    //brief
    //     �ڱ任����������ϵ�任
    //param
    //     rOtherSpatialRef:Ӱ������ϵ
    //return
    //     Ӱ��ɹ�����true
    //##ModelId=456A84A60000
    virtual bool Project(IGeo_SpatialReference &rOtherSpatialRef) = 0;

    //brief
    //     ����任
    //param
    //     ��
    //return
    //     ����ɹ�����true
    //##ModelId=456A852900FA
    virtual bool Reset() = 0;

};



#endif /* IGEO_AFFINETRANSFORM2D_H_HEADER_INCLUDED_B9D3677E */
