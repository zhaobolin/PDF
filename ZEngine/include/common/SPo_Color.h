#ifndef SPO_COLOR_H_HEADER_INCLUDED_B6C42E90
#define SPO_COLOR_H_HEADER_INCLUDED_B6C42E90

#include "commondef.h"
#include "iocommondef.h"
//按照红绿蓝透明度定义的颜色
//##ModelId=493BDCA4009C
struct SPo_Color
{
private:
    //##ModelId=493BDCC1000F
	unsigned char av;
	unsigned char rv;
	unsigned char gv;
	unsigned char bv;
	// ccolor sequenec abgr/////////////////////
    // 颜色的a =255时最饱和，0时最透明
    //##ModelId=493BDCCC0232
public: 
	SPo_Color(BYTE a,BYTE r,BYTE g,BYTE b):av(a),rv(r),gv(g),bv(b){};
	
	SPo_Color(BYTE r=0,BYTE g=0,BYTE b=0):av(255),rv(r),gv(g),bv(b){};
	
	SPo_Color(COLORREF cr):av(255),rv(GetRValue(cr)),gv(GetGValue(cr)),bv(GetBValue(cr)){};

	SPo_Color(Color gpr):av(gpr.GetA()),rv(gpr.GetR()),gv(gpr.GetG()),bv(gpr.GetB()){};

	void FromGcColor(COLORREF c,bool bOp255=true)
	{
		av=bOp255?255:0;
		rv=GetRValue(c);
		gv=GetGValue(c);
		bv=GetBValue(c);
	};
	
	void FromGpColor(Color p)
	{
		av=p.GetA();
		rv=p.GetR();
		gv=p.GetG();
		bv=p.GetB();
	};

	SPo_Color GetReverseColor()
	{
		SPo_Color rcl(255,255-rv,255-gv,255-bv);
		return rcl;
	}
	// \brief 相等运算
    // 
    // 判断给定点结构的数值是否与当前点结构的数值相等
    // 
    // \return 如果相等，则返回1；否则，返回0。
    // 
    // \param right：相等运算右操作数
    //##ModelId=44278F0A02FD
    bool operator==(const SPo_Color &right)
	{
		return (av==right.av)&&(rv==right.rv)&&(gv==right.gv)&&(bv==right.bv);
	};    
    // \brief 不相等运算
    // 
    // 判断给定点结构的数值是否与当前点结构的数值不相等
    // 
    // \return 如果不相等，则返回1；否则，返回0。
    // 
    // \param right：不相等运算右操作数
    //##ModelId=44278EC3007D
    bool operator!=(const SPo_Color &right)
	{
		return (*this)==right?false:true;
	};	

public:
	BYTE GetR()
	{
		return rv;
	}
	BYTE GetG()
	{
		return gv;
	}
	BYTE GetB()
	{
		return bv;
	}
	BYTE GetAlpha()
	{
		return av;
	}
	BYTE GetA()
	{
		return GetAlpha();
	}
	
	SPo_Color GetRevRGB()
	{		
		return SPo_Color(255,255-GetR(),255-GetG(),255-GetB());
	}
	COLORREF GetColorREF()
	{
		return RGB(GetR(),GetG(),GetB());
	}
	Color GetColorGp()
	{
		return Color(GetA(),GetR(),GetG(),GetB());
	}
	CString Format()
	{
		CString strFmt;
		strFmt.Format("A(%d)R(%d)G(%d)B(%d)",GetAlpha(),GetR(),GetG(),GetB());
		return strFmt;
	}
	void FromString(const char *pzString)
	{
		if(pzString)
		{
			sscanf(pzString,"A(%d)R(%d)G(%d)B(%d)",&av,&rv,&gv,&bv);
		}
	}
	void Serialize(CArchive& ar)
	{
		if(ar.IsStoring())
		{
			ar << av;ar << rv;ar << gv;ar << bv;
		}
		else
		{
			ar >> av;ar >> rv;ar >> gv;ar >> bv;
		}
	}
	//和另一个比较，相同返回0，不同返回1
	bool CompareColor(SPo_Color other)
	{
		return !((*this)==other);
	}
	
	//文档读写二进制流函数,输入数据指针和读写标识，输出正确读写的字节数。
	size_t BytesSerialize(PBYTE *ppBytes,bool bRead=true)
	{
		size_t pos = 0;
		if(bRead)
		{
			pos += _cread(&av,sizeof(av),1,(*ppBytes)+pos);
			pos += _cread(&rv,sizeof(rv),1,(*ppBytes)+pos);
			pos += _cread(&gv,sizeof(gv),1,(*ppBytes)+pos);
			pos += _cread(&bv,sizeof(bv),1,(*ppBytes)+pos);
		}
		else
		{
			pos += _cwrite(&av,sizeof(av),1,(*ppBytes)+pos);
			pos += _cwrite(&rv,sizeof(rv),1,(*ppBytes)+pos);
			pos += _cwrite(&gv,sizeof(gv),1,(*ppBytes)+pos);
			pos += _cwrite(&bv,sizeof(bv),1,(*ppBytes)+pos);
		}
	}
	//文档用二进制流表示所需的字节数计算函数
	size_t BytesSerializeSize()
	{
		return sizeof(av)+sizeof(rv)+sizeof(gv)+sizeof(bv);
	}
};

struct SPo_CMYKColor 
{
	BYTE c;
	BYTE m;
	BYTE y;
	BYTE k;
	SPo_CMYKColor(BYTE cc=0,BYTE mm=0,BYTE yy=0,BYTE kk=0):c(cc),m(mm),y(yy),k(kk)
	{		
	}
	// \brief 相等运算
    // 
    // 判断给定点结构的数值是否与当前点结构的数值相等
    // 
    // \return 如果相等，则返回1；否则，返回0。
    // 
    // \param right：相等运算右操作数
    //##ModelId=44278F0A02FD
    bool operator==(const SPo_CMYKColor &right)
	{
		return !(c - right.c || m - right.m || y - right.y||k - right.k) ;
	};    
    // \brief 不相等运算
    // 
    // 判断给定点结构的数值是否与当前点结构的数值不相等
    // 
    // \return 如果不相等，则返回1；否则，返回0。
    // 
    // \param right：不相等运算右操作数
    //##ModelId=44278EC3007D
    bool operator!=(const SPo_CMYKColor &right)
	{
		return !(*this == right) ;
	};
	
	void Serialize(CArchive& ar)
	{
		if(ar.IsStoring())
		{
			ar << c;ar << m;ar << y;ar << k;
		}
		else
		{
			ar >> c;ar >> m;ar >> y;ar >> k;
		}
	}
public:
	//文档读写二进制流函数,输入数据指针和读写标识，输出正确读写的字节数。
	size_t BytesSerialize(PBYTE *ppBytes,bool bRead=true)
	{
		size_t pos = 0;
		if(bRead)
		{
			pos += _cread(&c,sizeof(c),1,(*ppBytes)+pos);
			pos += _cread(&m,sizeof(m),1,(*ppBytes)+pos);
			pos += _cread(&y,sizeof(y),1,(*ppBytes)+pos);
			pos += _cread(&k,sizeof(k),1,(*ppBytes)+pos);
		}
		else
		{
			pos += _cwrite(&c,sizeof(c),1,(*ppBytes)+pos);
			pos += _cwrite(&m,sizeof(m),1,(*ppBytes)+pos);
			pos += _cwrite(&y,sizeof(y),1,(*ppBytes)+pos);
			pos += _cwrite(&k,sizeof(k),1,(*ppBytes)+pos);
		}
	}
	//文档用二进制流表示所需的字节数计算函数
	size_t BytesSerializeSize()
	{
		return sizeof(c)+sizeof(m)+sizeof(y)+sizeof(k);
	}
};

#endif /* SPO_COLOR_H_HEADER_INCLUDED_B6C42E90 */
