#ifndef SPO_TIME_H_HEADER_INCLUDED_BBD818CF
#define SPO_TIME_H_HEADER_INCLUDED_BBD818CF

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
// \brief ʱ��ṹ
// 
// ʱ��ṹ�����ꡢ�¡��ա�ʱ���֡��롢������Ϣ��
//##ModelId=4427A58F03A9
struct SPo_Time
{
  public:
    // \brief ȱʡ������
    // 
    //  ȱʡ���������ꡢ�¡��ա�ʱ���֡��롢�����Ϊ0��
    // 
    // \param ��
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

    // \brief ������
    // 
    //  �����������ݸ���ʱ���ʽ�����г�ʼ��������ʽΪ"��-��-��-ʱ-��-��-����"��
    // 
    // \param szTime��ʱ���ʽ��
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


    // \brief ת����ʱ���ʽ��
    // 
    // ��ʱ��ṹ�е���Ϣת����ʱ���ʽ��������ʽΪ"��-��-��-ʱ-��-��-����"��
    // 
    // \return ��
    // 
    // \param szTime�����������ʱ���ʽ����
    //##ModelId=4427A6960167
    void ToString(char *szTime)
	{
		sprintf(szTime, "%d-%d-%d-%d-%d-%d-%d", iYear, iMonth, iDay, iHour, iMinute, iSecond,iMillisecond) ;
	};

    // \brief ���ڲ���������
    // 
    // �����ж�����ʱ��ṹ��ʱ����Ϣ�Ƿ���ȡ�
    //##ModelId=4427A6D00109
    int operator==(const SPo_Time &right)
	{
		return (this->iYear == right.iYear && this->iMonth == right.iMonth && this->iDay == right.iDay
			&& this->iHour == right.iHour && this->iMinute == right.iMinute
			&& this->iSecond == right.iSecond && this->iMillisecond == right.iMillisecond) ;
	};

    // \brief �����ڲ���������
    // 
    // �����ж�����ʱ��ṹ��ʱ����Ϣ�Ƿ񲻵ȡ�
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
