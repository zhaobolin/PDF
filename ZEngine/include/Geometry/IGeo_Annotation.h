#ifndef IGEO_ANNOTATION_H_HEADER_INCLUDED_B9D1C9CB
#define IGEO_ANNOTATION_H_HEADER_INCLUDED_B9D1C9CB
#include "IGeo_Geometry.h"

// 注记接口
//##ModelId=462E080301D4
class IGeo_Annotation : public IGeo_Geometry
{
  public:
	virtual void AddPoint(SPo_DPoint sPoint, IPo_SpatialReference* pSpatialReference = NULL) = 0;
    //##ModelId=462E08B90232
    virtual const char * GetTextString() = 0;

    //##ModelId=462E094802AF
    virtual bool SetTextString(const char *pzText) = 0;

    //##ModelId=462E097A037A
    virtual LOGFONT GetLogFont() = 0;

    //##ModelId=462E099F005D
    virtual bool SetLogFont(LOGFONT lgfont) = 0;

    //##ModelId=462E0D450196
    virtual bool SetLogFont(const char *lfFaceName = "宋体", LONG lfHeight = 16, LONG lfWidth = 0, BYTE lfCharSet = 134, LONG lfEscapement = 0, LONG lfOrientation = 0, LONG lfWeight = 700, BYTE lfItalic = 0, BYTE lfUnderline = 0, BYTE lfStrikeOut = 0, BYTE lfOutPrecision = 1, BYTE lfClipPrecesion = 2, BYTE lfQuality = 2, BYTE lfPitchAndFamily = 34) = 0;

    //##ModelId=462E09C7004E
    virtual COLORREF GetTextColor() = 0;

    //##ModelId=462E09E00290
    virtual bool SetTextColor(COLORREF color) = 0;

    // 设置字体大小单位 FUN_POUND 1002 磅；FUN_NUMBER 1001 字号。
    //##ModelId=462E0A600203
    virtual bool SetFontSizeUnit(int fun) = 0;

    // 获取字体大小单位 FUN_POUND 1002 磅；FUN_NUMBER 1001 字号。
    //##ModelId=462E0A6D002E
    virtual int GetFontSizeUnit() = 0;

};



#endif /* IGEO_ANNOTATION_H_HEADER_INCLUDED_B9D1C9CB */
