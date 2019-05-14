#ifndef SPO_STATISTICS_H_HEADER_INCLUDED_BBD8757D
#define SPO_STATISTICS_H_HEADER_INCLUDED_BBD8757D

// \brief ͳ�ƽ���ṹ
// 
// ͳ�ƽ���ṹ�����԰�����ͳ��ֵ�У��ܺ͡�ƽ��ֵ����Сֵ�����ֵ��
//##ModelId=4427A5A403C8
struct SPo_Statistics
{
    // \brief ������
    // 
    // ������������ͳ��ֵ����ʼ��Ϊ��Ч��
    // 
    // \param ��
    //##ModelId=4427A8AC01F4
    SPo_Statistics()		
    {
		null_sum = true ;
		null_avg = true ;
		null_min = true ;
		null_max = true ;
    };

    // �ܺ�
    //##ModelId=4427A808001F
    double sumval;

    // ƽ��ֵ
    //##ModelId=4427A81E036B
    double avgval;

    // ��Сֵ
    //##ModelId=4427A83300FA
    double minval;

    // ���ֵ
    //##ModelId=4427A849032C
    double maxval;

    // �ܺ�ͳ��ֵ�Ƿ���Ч
    //##ModelId=4427A85B031C
    bool null_sum;

    // ƽ��ֵͳ��ֵ�Ƿ���Ч
    //##ModelId=4427A8700261
    bool null_avg;

    // ��Сֵͳ��ֵ�Ƿ���Ч
    //##ModelId=4427A883037A
    bool null_min;

    // ���ֵͳ��ֵ�Ƿ���Ч
    //##ModelId=4427A89301D4
    bool null_max;

};



#endif /* SPO_STATISTICS_H_HEADER_INCLUDED_BBD8757D */
