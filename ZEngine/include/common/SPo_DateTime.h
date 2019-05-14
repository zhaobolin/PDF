#ifndef SPO_DATETIME_H_HEADER_INCLUDED_B8924F4B
#define SPO_DATETIME_H_HEADER_INCLUDED_B8924F4B


//---------added by hls
#define SHOW_TIME12 1
#define SHOW_TIME24 2

//##ModelId=476DC9C903C8
struct SPo_DateTime
{
public:
    //##ModelId=476DCA190232
    DATE Date;

	SPo_DateTime(bool bCurrentTime = false/*是否构造当前时间*/)
	{
		Date = 0;
		if(bCurrentTime)
		{
			COleDateTime odt = COleDateTime::GetCurrentTime();
			Date = odt.m_dt;			
		}
	};
	/////////////////////////////////////inherit from COleDateTime,F1 to see desc of COleDateTime
	SPo_DateTime( const VARIANT& varSrc )
	{
		COleDateTime odt(varSrc);
		Date = odt.m_dt;
	};
	SPo_DateTime( DATE dtSrc )
	{
		Date = dtSrc;
	};
	SPo_DateTime( time_t timeSrc )
	{
		COleDateTime odt(timeSrc);
		Date = odt.m_dt;
	};
	SPo_DateTime( const SYSTEMTIME& systimeSrc )
	{
		COleDateTime odt(systimeSrc);
		Date = odt.m_dt;
	};
	SPo_DateTime( const FILETIME& filetimeSrc )
	{
		COleDateTime odt(filetimeSrc);
		Date = odt.m_dt;
	};
	SPo_DateTime( int nYear, int nMonth, int nDay, int nHour, int nMin, int nSec )
	{
		COleDateTime odt(nYear,nMonth,nDay,nHour,nMin,nSec);
		Date = odt.m_dt;
	};
	SPo_DateTime( WORD wDosDate, WORD wDosTime )
	{
		COleDateTime odt(wDosDate, wDosTime);
		Date = odt.m_dt;
	};
	//
	DATE GetCurrentTime()
	{		
		COleDateTime odt = COleDateTime::GetCurrentTime();
		Date = odt.m_dt;
		return Date;
	};

	BOOL GetAsSystemTime( SYSTEMTIME& sysTime ) const
	{
		COleDateTime odt(Date);
		return odt.GetAsSystemTime(sysTime);
	};
	int GetYear( ) const
	{
		COleDateTime odt(Date);
		return odt.GetYear();
	};
	int GetMonth( ) const
	{
		COleDateTime odt(Date);
		return odt.GetMonth();
	};
	int GetDay( ) const
	{
		COleDateTime odt(Date);
		return odt.GetDay();
	};
	int GetHour( ) const
	{
		COleDateTime odt(Date);
		return odt.GetHour();
	};
	int GetMinute( ) const
	{
		COleDateTime odt(Date);
		return odt.GetMinute();
	};
	int GetSecond( ) const
	{
		COleDateTime odt(Date);
		return odt.GetSecond();
	};
	int GetDayOfWeek( ) const
	{
		COleDateTime odt(Date);
		return odt.GetDayOfWeek();
	};
	int GetDayOfYear( ) const
	{
		COleDateTime odt(Date);
		return odt.GetDayOfYear();
	};
	int SetDateTime( int nYear, int nMonth, int nDay, int nHour, int nMin, int nSec )
	{
		COleDateTime odt(Date);
		int ival = odt.SetDateTime(nYear,nMonth,nDay,nHour,nMin,nSec);
		Date = odt.m_dt;
		return ival;
	};
	int SetDate( int nYear, int nMonth, int nDay )
	{
		COleDateTime odt(Date);
		int ival = odt.SetDate(nYear,nMonth,nDay);
		Date = odt.m_dt;
		return ival;
	};
	int SetTime( int nHour, int nMin, int nSec )
	{
		COleDateTime odt(Date);
		int ival = odt.SetTime(nHour,nMin,nSec);
		Date = odt.m_dt;
		return ival;
	};
	BOOL ParseDateTime( LPCTSTR lpszDate, DWORD dwFlags = 0, LCID lcid = LANG_USER_DEFAULT )
	{
		COleDateTime odt(Date);
		BOOL bval = odt.ParseDateTime(lpszDate,dwFlags,lcid);
		Date = odt.m_dt;
		return bval;
	};	

	CString Format( DWORD dwFlags = 0, LCID lcid = LANG_USER_DEFAULT )
	{
		COleDateTime odt(Date);
		return odt.Format(dwFlags,lcid);
	};
	
	CString Format( LPCTSTR lpszFormat ) const
	{
		COleDateTime odt(Date);
		return odt.Format(lpszFormat);
	};
	
	CString Format( UINT nFormatID ) const
	{
		COleDateTime odt(Date);
		return odt.Format(nFormatID);
	};
	////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	//SPo_DateTime Dtm;
    //##ModelId=476DCA4C03D8
    CString ToString(int mode)
	{
		CString str;
		
		if(mode == SHOW_TIME12)
		{
			str.Format("%d-%.2d-%.2d %.2d:%.2d:%.2d %s",this->GetYear(),this->GetMonth(),
				this->GetDay(),this->GetHour(),this->GetMinute(),this->GetSecond(),
				this->GetHour()>11?"PM":"AM");
		}
		else//SHOW_TIME24
		{
			str.Format("%d-%.2d-%.2d %.2d:%.2d:%.2d",this->GetYear(),this->GetMonth(),
				this->GetDay(),this->GetHour(),this->GetMinute(),this->GetSecond());
		}
		return str;
	};
	void Serialize(CArchive &ar)
	{
		if(ar.IsStoring())
		{
			ar << Date;
		}
		else
		{
			ar >> Date;
		}
	};
};



#endif /* SPO_DATETIME_H_HEADER_INCLUDED_B8924F4B */
