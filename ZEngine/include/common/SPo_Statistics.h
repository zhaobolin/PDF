#ifndef SPO_STATISTICS_H_HEADER_INCLUDED_BBD8757D
#define SPO_STATISTICS_H_HEADER_INCLUDED_BBD8757D

// \brief 统计结果结构
// 
// 统计结果结构。可以包含的统计值有：总和、平均值、最小值、最大值。
//##ModelId=4427A5A403C8
struct SPo_Statistics
{
    // \brief 构造器
    // 
    // 构造器。所有统计值均初始化为无效。
    // 
    // \param 无
    //##ModelId=4427A8AC01F4
    SPo_Statistics()		
    {
		null_sum = true ;
		null_avg = true ;
		null_min = true ;
		null_max = true ;
    };

    // 总和
    //##ModelId=4427A808001F
    double sumval;

    // 平均值
    //##ModelId=4427A81E036B
    double avgval;

    // 最小值
    //##ModelId=4427A83300FA
    double minval;

    // 最大值
    //##ModelId=4427A849032C
    double maxval;

    // 总和统计值是否无效
    //##ModelId=4427A85B031C
    bool null_sum;

    // 平均值统计值是否无效
    //##ModelId=4427A8700261
    bool null_avg;

    // 最小值统计值是否无效
    //##ModelId=4427A883037A
    bool null_min;

    // 最大值统计值是否无效
    //##ModelId=4427A89301D4
    bool null_max;

};



#endif /* SPO_STATISTICS_H_HEADER_INCLUDED_BBD8757D */
