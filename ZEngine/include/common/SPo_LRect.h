// SPo_LRect.h: interface for the SPo_LRect class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPO_LRECT_H__41FD0A60_BADF_4C49_B168_774906C10EFB__INCLUDED_)
#define AFX_SPO_LRECT_H__41FD0A60_BADF_4C49_B168_774906C10EFB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SPo_TplRect.h"

// 浮点型矩形结构
// 
// 浮点型矩形结构。包含上、下、左、右四个边界值，所有边界值为浮点型。结构本身不限定各个边界之间的大小关系（即不限定坐标系）。
//##ModelId=40C8F963006D
typedef SPo_TplRect<long> SPo_LRect;


#endif // !defined(AFX_SPO_LRECT_H__41FD0A60_BADF_4C49_B168_774906C10EFB__INCLUDED_)
