#ifndef IGEO_TRANSFORMATION_H_HEADER_INCLUDED_B9D31A67
#define IGEO_TRANSFORMATION_H_HEADER_INCLUDED_B9D31A67

//brief
//     �任������ӿ�
//##ModelId=456A59BC02BF
class IGeo_Transformation
{
  public:
    //brief
    //     ת����ֵ
    //param
    //     enumDirection:��������
    //     iCount:ֵ����
    //     pdFromMs:������ֵ
    //     pdToMs:�����ֵ
    //return
    //     ת���ɹ�������true
    //##ModelId=456A5A0601A5
    virtual bool TransformMsFF(poenumTransformDirection enumDirection, int iCount, double *pdFromMs, double *pdToMs) = 0;

    //brief
    //     ת����ֵ
    //param
    //     enumDirection:��������
    //     iCount:ֵ����
    //     pdFromMs:������ֵ
    //     piToMs:�����ֵ
    //return
    //     ת���ɹ�������true
    //##ModelId=456A5B3B01E4
    virtual bool TransformMsFI(poenumTransformDirection enumDirection, int iCount, double *pdFromMs, int *piToMs) = 0;

    //brief
    //     ת����ֵ
    //param
    //     enumDirection:��������
    //     iCount:ֵ����
    //     piFromMs:������ֵ
    //     pdToMs:�����ֵ
    //return
    //     ת���ɹ�������true
    //##ModelId=456A5BA2009C
    virtual bool TransformMsIF(poenumTransformDirection enumDirection, int iCount, int *piFromMs, double *pdToMs) = 0;

    //brief
    //     ת����ֵ
    //param
    //     enumDirection:��������
    //     iCount:ֵ����
    //     piFromMs:������ֵ
    //     piToMs:�����ֵ
    //return
    //     ת���ɹ�������true
    //##ModelId=456A5BD600AB
    virtual bool TransformMsII(poenumTransformDirection enumDirection, int iCount, int *piFromMs, int *piToMs) = 0;

};



#endif /* IGEO_TRANSFORMATION_H_HEADER_INCLUDED_B9D31A67 */
