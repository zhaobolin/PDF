#ifndef SPO_TIME_H_HEADER_INCLUDED_BBD818CF
#define SPO_TIME_H_HEADER_INCLUDED_BBD818CF

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
// \brief 时间结构
// 
// 时间结构。含年、月、日、时、分、秒、毫秒信息。
//##ModelId=4427A58F03A9
struct SPo_Time
{
  public:
    // \brief 缺省构造器
    // 
    //  缺省构造器。年、月、日、时、分、秒、毫秒均为0。
    // 
    // \param 无
    //##ModelId=4427A6440271
    SPo_Time()
	{
		iYear = 0 ;
		iMonth = 0 ;
		iDay = 0 ;
		iHour = 0 ;
		iMinute = 0 ;
		iSecond = 0 ;
		iMillisecond = 0 ;
	};

    // \brief 构造器
    // 
    //  构造器。根据给定时间格式串进行初始化。串格式为"年-月-日-时-分-秒-毫秒"。
    // 
    // \param szTime：时间格式串
    //##ModelId=4427A664003E
    SPo_Time(const char *szTime)
	{
		iYear = 0 ;
		iMonth = 0 ;
		iDay = 0 ;
		iHour = 0 ;
		iMinute = 0 ;
		iSecond = 0 ;
		iMillisecond = 0 ;
		
		char *p_char = NULL ;
		
		iYear = (int)strtol(szTime, &p_char, 0) ;
		if (!p_char)
		{
			assert(false) ;
			return ;
		}
		p_char++ ;
		
		iMonth = (int)strtol(p_char, &p_char, 0) ;
		if (!p_char)
		{
			assert(false) ;
			return ;
		}
		p_char++ ;
		
		iDay = (int)strtol(p_char, &p_char, 0) ;
		if (!p_char)
		{
			assert(false) ;
			return ;
		}
		p_char++ ;
		
		iHour = (int)strtol(p_char, &p_char, 0) ;
		if (!p_char)
		{
			assert(false) ;
			return ;
		}
		p_char++ ;
		
		iMinute = (int)strtol(p_char, &p_char, 0) ;
		if (!p_char)
		{
			assert(false) ;
			return ;
		}
		p_char++ ;
		
		iSecond = (int)strtol(p_char, &p_char, 0) ;
		if (!p_char)
		{
			assert(false) ;
			return ;
		}
		p_char++ ;
		
		iMillisecond = (int)strtol(p_char, &p_char, 0) ;
	};


    // \brief 转换成时间格式串
    // 
    // 将时间结构中的信息转换成时间格式串。串格式为"年-月-日-时-分-秒-毫秒"。
    // 
    // \return 无
    // 
    // \param szTime：输出参数。时间格式串。
    //##ModelId=4427A6960167
    void ToString(char *szTime)
	{
		sprintf(szTime, "%d-%d-%d-%d-%d-%d-%d", iYear, iMonth, iDay, iHour, iMinute, iSecond,iMillisecond) ;
	};

    // \brief 等于操作符重载
    // 
    // 用于判断两个时间结构中时间信息是否相等。
    //##ModelId=4427A6D00109
    int operator==(const SPo_Time &right)
	{
		return (this->iYear == right.iYear && this->iMonth == right.iMonth && this->iDay == right.iDay
			&& this->iHour == right.iHour && this->iMinute == right.iMinute
			&& this->iSecond == right.iSecond && this->iMillisecond == right.iMillisecond) ;
	};

    // \brief 不等于操作符重载
    // 
    // 用于判断两个时间结构中时间信息是否不等。
    //##ModelId=4427A7050271
    int operator!=(const SPo_Time &right)
	{
		return !(*this == right) ;
	};

    //##ModelId=4427A5CE0232
    int iYear;

    //##ModelId=4427A5DB0242
    int iMonth;

    //##ModelId=4427A5EC02EE
    int iDay;

    //##ModelId=4427A5FE003E
    int iHour;

    //##ModelId=4427A60900DA
    int iMinute;

    //##ModelId=4427A6160222
    int iSecond;

    //##ModelId=4427A624008C
    int iMillisecond;

};



#endif /* SPO_TIME_H_HEADER_INCLUDED_BBD818CF */
