#ifndef IGEO_TRANSFORMATION_H_HEADER_INCLUDED_B9D31A67
#define IGEO_TRANSFORMATION_H_HEADER_INCLUDED_B9D31A67

//brief
//     变换抽象类接口
//##ModelId=456A59BC02BF
class IGeo_Transformation
{
  public:
    //brief
    //     转换数值
    //param
    //     enumDirection:正向、逆向
    //     iCount:值个数
    //     pdFromMs:输入数值
    //     pdToMs:输出数值
    //return
    //     转换成功，返回true
    //##ModelId=456A5A0601A5
    virtual bool TransformMsFF(poenumTransformDirection enumDirection, int iCount, double *pdFromMs, double *pdToMs) = 0;

    //brief
    //     转换数值
    //param
    //     enumDirection:正向、逆向
    //     iCount:值个数
    //     pdFromMs:输入数值
    //     piToMs:输出数值
    //return
    //     转换成功，返回true
    //##ModelId=456A5B3B01E4
    virtual bool TransformMsFI(poenumTransformDirection enumDirection, int iCount, double *pdFromMs, int *piToMs) = 0;

    //brief
    //     转换数值
    //param
    //     enumDirection:正向、逆向
    //     iCount:值个数
    //     piFromMs:输入数值
    //     pdToMs:输出数值
    //return
    //     转换成功，返回true
    //##ModelId=456A5BA2009C
    virtual bool TransformMsIF(poenumTransformDirection enumDirection, int iCount, int *piFromMs, double *pdToMs) = 0;

    //brief
    //     转换数值
    //param
    //     enumDirection:正向、逆向
    //     iCount:值个数
    //     piFromMs:输入数值
    //     piToMs:输出数值
    //return
    //     转换成功，返回true
    //##ModelId=456A5BD600AB
    virtual bool TransformMsII(poenumTransformDirection enumDirection, int iCount, int *piFromMs, int *piToMs) = 0;

};



#endif /* IGEO_TRANSFORMATION_H_HEADER_INCLUDED_B9D31A67 */
