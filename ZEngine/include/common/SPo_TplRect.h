#ifndef SPO_TPLRECT_H_HEADER_INCLUDED_B9A1D13B
#define SPO_TPLRECT_H_HEADER_INCLUDED_B9A1D13B

#include "SPo_IPoint.h"

const double SPLITRATIO = 0.55;


// ģ���;���
//##ModelId=465E3A30004E
template <class TYPE> class SPo_TplRect
{
public:
    //##ModelId=40C8F9A102FD
    TYPE left;
	
    //##ModelId=40C8F9A102FE
    TYPE right;
	
    //##ModelId=40C8F9A102FF
    TYPE top;
	
    //##ModelId=40C8F9A10300
    TYPE bottom;
public:
    // \brief ������
    // 
    // �������������ݲ�����ʼ�������ĸ��߽�ֵ��
    // 
    // \param iLeft����߽�ֵ
    // \param iTop���ϱ߽�ֵ
    // \param iRight���ұ߽�ֵ
    // \param iBottom���±߽�ֵ
    //##ModelId=44277F3502EE
    SPo_TplRect(TYPE x1 = 0, TYPE y1 = 0, TYPE x2 = 0, TYPE y2 = 0)
	{
		left	= min(x1,x2) ;
		top		= min(y1,y2) ;
		right	= max(x1,x2) ;
		bottom	= max(y1,y2) ;
	};
	//��д������ʼ������
	template <class TYPE1> SPo_TplRect(const SPo_TplRect<TYPE1> &other)
	{
		left = (TYPE)(other.left);
		right = (TYPE)(other.right);
		top = (TYPE)(other.top);
		bottom = (TYPE)(other.bottom);
	};
	//��д������ʼ������
	SPo_TplRect(const RECT &other)
	{
		left = other.left;
		right = other.right;
		top = other.top;
		bottom = other.bottom;
	};
	//��������
	~SPo_TplRect()
	{
	}
    // \brief ��ȡ���εĿ�ȡ�
    // 
    // ��ȡ���εĿ�ȡ�
    // 
    // \return ���εĿ��
    // 
    // \param ��
    //##ModelId=44277FB5002E
    TYPE GetWidth()
	{
		return (right > left ) ? right - left : left - right ;
	};

    // \brief ��ȡ���εĸ߶ȡ�
    // 
    // ��ȡ���εĸ߶ȡ�
    // 
    // \return ���εĸ߶�,һ����Ϊy���귽���������
    // 
    // \param ��
    //##ModelId=44277FB5002F
    TYPE GetHeight()
	{
		return (top > bottom ) ? top - bottom : bottom - top ;
	};

    // \brief ��ȡ���ε����ĵ�
    // 
    // ��ȡ���ε����ĵ�
    // 
    // \return ���ε����ĵ�
    // 
    // \param ��
    //##ModelId=44277FB50030
    SPo_TplPoint<TYPE> GetCenterPoint()
	{
		SPo_TplPoint<TYPE> point (0, 0, 0) ;
		
		SPo_TplRect rect = *this ;
		rect.NormalizeRect () ;
		
		point.x = rect.left + (TYPE)(rect.GetWidth()) / 2  ;
		point.y = rect.bottom + (TYPE)(rect.GetHeight()) / 2 ;
		
		
		return point ;
	};

	TYPE CenterX()
	{
		return (left+right)/2;
	};

	TYPE CenterY()
	{
		return (top+bottom)/2;
	};


    // \brief ���ι��
    // 
    // �Ծ��ν��й�񻯴���������֤��������ֵ�У�left <= right, bottom <= top��
    // 
    // \return ��
    // 
    // \param ��
    // 
    // \note �÷�����Ϊ�����������Ƶġ���������������ԣ�top ����ֵҪ���� bottom ����ֵ����������Ļ���꣬top ����ֵҪС��
    // bottom ����ֵ���ڴ���ʱҪ�ر�ע�⡣
    //##ModelId=44277FB50031
    void NormalizeRect()
	{
		TYPE value ;
		
		if (left > right)
		{
            value = right ;
            right = left;
            left = value ;
		}
		
		if (bottom > top)
		{
            value = bottom ;
            bottom = top ;
            top = value ;
		}
	};

    // \brief ���η�����
    // 
    // �Ծ��ν��з����񻯴���������֤��������ֵ�У�left <= right, bottom >= top��
    // 
    // \return ��
    // 
    // \param ��
    // 
    // \note �÷�����Ϊ��Ļ�������Ƶġ���������������ԣ�top ����ֵҪ���� bottom ����ֵ����������Ļ���꣬top ����ֵҪС��
    // bottom ����ֵ���ڴ���ʱҪ�ر�ע�⡣
    //##ModelId=44277FB50032
    void ReserveNormalizeRect()
	{
		TYPE value ;
		
		if (left > right )
		{
            value = right ;
            right = left;
            left = value ;
		}
		
		if (bottom < top)
		{
            value = bottom ;
            bottom = top ;
            top = value ;
		}
	};
    // \brief ��ֵ����
    // 
    // ���������νṹ����ֵ������ǰ���νṹ
    // 
    // \return ��ǰ���νṹ������
    // 
    // \param right����ֵ�����Ҳ�����
    //##ModelId=44277FB50040
    SPo_TplRect<TYPE> operator=(const SPo_TplRect<TYPE> &right)
	{
		this->left		= right.left ;
		this->right		= right.right ;
		this->top		= right.top ;
		this->bottom	= right.bottom ;
		
		return *this ;
	};

    // \brief ����-������ת����ֵ����
    // 
    // ������windows���ε���ֵ������ǰ���νṹ
    // 
    // \return ��ǰ���νṹ������
    // 
    // \param right��ת����ֵ�����Ҳ�����
    //##ModelId=44277FB50042
    SPo_TplRect<TYPE> operator=(const RECT &right)
	{
		this->left		= right.left ;
		this->right		= right.right ;
		this->top		= right.top ;
		this->bottom	= right.bottom ;
		
		return *this ;
	};
    // \brief ����-������ת����ֵ����
    // 
    // ������windows���ε���ֵ������ǰ���νṹ
    // 
    // \return ��ǰ���νṹ������
    // 
    // \param right��ת����ֵ�����Ҳ�����
    //##ModelId=44277FB50042	
//    SPo_TplRect<TYPE> operator=(const Rect &right)
//	{
//		this->left		= min(right.GetLeft(),right.GetRight());
//		this->right		= max(right.GetLeft(),right.GetRight());
//		this->top		= max(right.GetTop(),right.GetBottom());
//		this->bottom	= min(right.GetTop(),right.GetBottom());
//		
//		return *this ;
//	};
    // \brief ����-������ת����ֵ����
    // 
    // ������windows���ε���ֵ������ǰ���νṹ
    // 
    // \return ��ǰ���νṹ������
    // 
    // \param right��ת����ֵ�����Ҳ�����
    //##ModelId=44277FB50042
//    SPo_TplRect<TYPE> operator=(const RectF &right)
//	{
//		this->left		= min(right.GetLeft(),right.GetRight());
//		this->right		= max(right.GetLeft(),right.GetRight());
//		this->top		= max(right.GetTop(),right.GetBottom());
//		this->bottom	= min(right.GetTop(),right.GetBottom());
//		
//		return *this ;
//	};
	//��ԭ�����λ�����ƫ�Ƶ�
	template <class TYPE2> void OffsetPoint(TYPE2 dx,TYPE2 dy)
	{
		left+=dx;right+=dx;
		bottom+=dy;top+=dy;
	};
    // \brief �������
    // 
    // �жϸ������νṹ����ֵ�Ƿ��뵱ǰ���νṹ����ֵ���
    // 
    // \return �����ȣ��򷵻�1�����򣬷���0��
    // 
    // \param right����������Ҳ�����
    //##ModelId=44277FB50044
	bool operator==(const SPo_TplRect<TYPE> &right)
	{
		if (	(this->left	== right.left ) &&
            (this->right	== right.right) &&  
            (this->top	== right.top)   && 
            (this->bottom	== right.bottom) ) 
            return 1 ;
		else
            return 0 ;
	};
	//�ھ�������Χ�ڵ���ͬ
	bool AcurateEqual(const SPo_TplRect<TYPE> &right)
	{
		SPo_TplRect<TYPE> me=*this;
		SPo_TplRect<TYPE> ot=right;
		me.NormalizeRect();ot.NormalizeRect();
		if( fabs((double)(me.left)-(double)(ot.left))<DDVAL_CBT_MIAOACURATE&&
			fabs((double)(me.right)-(double)(ot.right))<DDVAL_CBT_MIAOACURATE&&
			fabs((double)(me.top)-(double)(ot.top))<DDVAL_CBT_MIAOACURATE&&
			fabs((double)(me.bottom)-(double)(ot.bottom))<DDVAL_CBT_MIAOACURATE)
			return true;
		else 
			return false;
	}
    // \brief ���������
    // 
    // �жϸ������νṹ����ֵ�Ƿ��뵱ǰ���νṹ����ֵ�����
    // 
    // \return �������ȣ��򷵻�1�����򣬷���0��
    // 
    // \param right������������Ҳ�����
    //##ModelId=44277FB50046
    bool operator!=(const SPo_TplRect<TYPE> &right)
	{
		if ( *this == right )
            return 0 ;
		else 
            return 1 ;
	};
    // \brief �жϵ��ھ�����
    // 
    // �ж�ĳ�����Ƿ����ڸþ��������ڡ�
    // 
    // \return ������ھ����⣬�򷵻�false��������ھ�����1,���ߵ��ھ��α߽���2������true��
    // 
    // \param dx�����жϵĵ��xֵ
    // \param dy�����жϵĵ��yֵ
    // \param iTolerance���жϵ����ֵ��ȱʡΪ0������ȷ�жϡ�
    // 
    // \note���÷������ܶԾ����и����ã����Ծ��ν��й�񻯴�������ʹ��left < right, bottom < top��
    //##ModelId=44277FB50048
    template<class TYPE2,class TYPE3> int PtInRect(TYPE2 x, TYPE3 y, TYPE iTolerance = 0)
	{
		if (   (x < (left - iTolerance))
            || (x > (right + iTolerance))
            || (y < (min(bottom,top)  - iTolerance))
            || (y > (max(bottom,top) + iTolerance)) )
		{
            return 0 ;
		}
		else if ( (x > (left - iTolerance))
            && (x < (right + iTolerance) )
            && (y > (min(bottom,top)  - iTolerance) )
            && (y < (max(bottom,top) + iTolerance)) )
		{
            return 1 ;
		}			
		else
		{
            return 2 ;
		}
	};
	template<class TYPE2> int PtInRect(SPo_TplPoint<TYPE2> pt,TYPE2 iRolerance = 0)
	{
		return PtInRect(pt.x,pt.y,iRolerance);
	}
	int PtInRect(POINT pt,TYPE iRolerance = 0)
	{
		return PtInRect(pt.x,pt.y,iRolerance);
	}
    // \brief �ж����������Ƿ��ཻ
    // 
    // �жϸ��������Ƿ��뵱ǰ�����ཻ��
    // 
    // \return ����ཻ���򷵻�1�����򣬷���0��
    // 
    // \param pRect�����жϾ��ε�ָ��
    // \param iTolerance���жϵ����ֵ��ȱʡΪ0������ȷ�жϡ�
    //##ModelId=44277FB5006D
    template<class TYPE2> bool IsIntersect(SPo_TplRect<TYPE2>* pRect, TYPE iTolerance = 0)
	{
		SPo_TplRect<TYPE> rect1;SPo_TplRect<TYPE2> rect2;
		rect1 = *this;
		rect2 = *pRect;
		rect1.NormalizeRect();
		rect2.NormalizeRect();
		if (rect1.left < (rect2.right + iTolerance) && rect1.right > (rect2.left - iTolerance)
            && rect1.bottom < (rect2.top + iTolerance) && rect1.top > (rect2.bottom - iTolerance))
		{
            return 1 ;
		}
		else
            return 0 ;
	};
    // \brief �ж����������Ƿ��ཻ
    // 
    // �жϸ��������Ƿ��뵱ǰ�����ཻ��
    // 
    // \return ����ཻ���򷵻�1�����򣬷���0��
    // 
    // \param pRect�����жϾ��ε�ָ��
    // \param iTolerance���жϵ����ֵ��ȱʡΪ0������ȷ�жϡ�
    //##ModelId=44277FB5006D
    template<class TYPE2> bool IsIntersect(TYPE2 x1,TYPE2 y1,TYPE x2,TYPE y2, TYPE iTolerance = 0)
	{
		SPo_TplRect<TYPE> rect1;SPo_TplRect<TYPE2> rect2(x1,y1,x2,y2);
		rect1 = *this;
		rect1.NormalizeRect();
		rect2.NormalizeRect();
		if (rect1.left < (rect2.right + iTolerance) && rect1.right > (rect2.left - iTolerance)
            && rect1.bottom < (rect2.top + iTolerance) && rect1.top > (rect2.bottom - iTolerance))
		{
            return 1 ;
		}
		else
            return 0 ;
	};
    // \brief �ж����������Ƿ��ཻ
    // 
    // �жϸ��������Ƿ��뵱ǰ�����ཻ��
    // 
    // \return ����ཻ���򷵻�1�����򣬷���0��
    // 
    // \param pRect�����жϾ��ε�ָ��
    // \param iTolerance���жϵ����ֵ��ȱʡΪ0������ȷ�жϡ�
    //##ModelId=44277FB5006D
    bool IsIntersect(RECT* pRect, TYPE iTolerance = 0)
	{
		SPo_TplRect<TYPE> rect1;SPo_TplRect<TYPE> rect2(pRect->left,pRect->top,pRect->right,pRect->bottom);
		rect1 = *this;
		rect1.NormalizeRect();
		rect2.NormalizeRect();
		if (rect1.left < (rect2.right + iTolerance) && rect1.right > (rect2.left - iTolerance)
            && rect1.bottom < (rect2.top + iTolerance) && rect1.top > (rect2.bottom - iTolerance))
		{
            return 1 ;
		}
		else
            return 0 ;
	};
    // \brief �жϵ�ǰ�����Ƿ񱻸������ΰ���
    // 
    // �жϵ�ǰ�����Ƿ񱻸������ΰ�����
    // 
    // \return ������������򷵻�1�����򣬷���0��
    // 
    // \param pRect�����жϾ��ε�ָ��
    // \param iTolerance���жϵ����ֵ��ȱʡΪ0������ȷ�жϡ�
    //##ModelId=442781E702FD
    template<class TYPE2> bool IsWithin(SPo_TplRect<TYPE2>* pRect, TYPE iTolerance = 0)
	{
		SPo_TplRect<TYPE> rect1; SPo_TplRect<TYPE2> rect2;
		rect1 = *this;
		rect2 = *pRect;
		rect1.NormalizeRect();
		rect2.NormalizeRect();
		
		if (rect1.left > (rect2.left - iTolerance) && rect1.right < (rect2.right + iTolerance)
            && rect1.bottom > (rect2.bottom - iTolerance) && rect1.top < (rect2.top + iTolerance))
		{
            return 1 ;
		}
		else
            return 0 ;
	};

    // \brief �жϵ�ǰ�����Ƿ�����һ�������
    // 
    // �жϵ�ǰ�����Ƿ�����һ�������
    // 
    // \return ����غϣ��򷵻�1�����򣬷���0��
    // 
    // \param pRect����һ���νṹ��ָ��
    // \param iTolerance���жϵ����ֵ��ȱʡΪ0������ȷ�жϡ�
    //##ModelId=44278245009C
	template<class TYPE2> bool IsEqual(SPo_TplRect<TYPE2> *pRect, TYPE iTolerance = 0)
	{
		if (abs(this->left	- pRect->left ) <= iTolerance &&
            abs(this->right	- pRect->right) <= iTolerance &&  
            abs(this->top - pRect->top) <= iTolerance && 
            abs(this->bottom - pRect->bottom) <= iTolerance) 
            return 1 ;
		else
            return 0 ;
	};

    // \brief �����������εĽ���
    // 
    // �����������εĽ���������������浽���ṹ�С���������β��ཻ���򱾽ṹ����SPo_TplRect(0,0,0,0)��
    // 
    // \return �Ƿ����ཻ����,���ཻ�ķ���true,û���ཻ���ַ���false
    // 
    // \param pRect1�����󽻾���1��ָ��
    // \param pRect2�����󽻾���2��ָ��
    // 
    // \note �������ǹ�񻯵ģ���ԭ���������󽻾��β���Ӱ�졣
    //##ModelId=4427829900BB
    template<class TYPE2,class TYPE3> bool Intersect(SPo_TplRect<TYPE2>* pRect1, SPo_TplRect<TYPE3>* pRect2)
	{
		assert(pRect1) ;
		assert(pRect2) ;
		bool bval = false;
		if (pRect1 && pRect2)
		{
			SPo_TplRect<TYPE2> rect1;
			SPo_TplRect<TYPE3> rect2;
			
			rect1 = *pRect1;
			rect2 = *pRect2;
			rect1.NormalizeRect();
			rect2.NormalizeRect();
			
			if (rect1.left > rect2.right || rect1.right < rect2.left
                || rect1.bottom > rect2.top || rect1.top < rect2.bottom)
			{
                left = 0 ;
                right = 0 ;
                
                top = 0 ;
                bottom = 0 ;
			}
			else
			{				
                left = (rect1.left > rect2.left ) ? rect1.left : rect2.left ; // ȡ��ֵ
                right = ( rect1.right < rect2.right ) ? rect1.right : rect2.right ; // ȡСֵ
                
                top = ( rect1.top < rect2.top ) ? rect1.top : rect2.top ; // ȡСֵ
                bottom = ( rect1.bottom > rect2.bottom ) ? rect1.bottom : rect2.bottom ; // ȡ��ֵ
				bval = true;
			}
		}
		return bval;
	};


    // \brief �����������εĽ���
    // 
    // �����������εĽ���������������浽���ṹ�С���������β��ཻ���򱾽ṹ����SPo_TplRect(0,0,0,0)��
    // 
    // \return ��
    // 
    // \param pRect1�����󽻾���1��ָ��
    // \param pRect2�����󽻾���2��ָ��
    // 
    // \note �������ǹ�񻯵ģ���ԭ���������󽻾��β���Ӱ�졣
    //##ModelId=4427829900BB
    template<class TYPE> bool Intersect(SPo_TplRect<TYPE>* pRect1, RECT *pRect2)
	{
		assert(pRect1) ;
		assert(pRect2) ;
		bool bval = false;
		if (pRect1 && pRect2)
		{
			SPo_TplRect<TYPE> rect1;
			SPo_TplRect<TYPE> rect2;
			
			rect1 = *pRect1;
			rect2.left = pRect2->left;rect2.right=pRect2->right;rect2.bottom=pRect2->bottom;rect2.top=pRect2->top;
			
			rect1.NormalizeRect();
			rect2.NormalizeRect();
			
			if (rect1.left > rect2.right || rect1.right < rect2.left
                || rect1.bottom > rect2.top || rect1.top < rect2.bottom)
			{
                left = 0 ;
                right = 0 ;
                
                top = 0 ;
                bottom = 0 ;
			}
			else
			{				
                left = (rect1.left > rect2.left ) ? rect1.left : rect2.left ; // ȡ��ֵ
                right = ( rect1.right < rect2.right ) ? rect1.right : rect2.right ; // ȡСֵ
                
                top = ( rect1.top < rect2.top ) ? rect1.top : rect2.top ; // ȡСֵ
                bottom = ( rect1.bottom > rect2.bottom ) ? rect1.bottom : rect2.bottom ; // ȡ��ֵ
				bval = true;
			}
		}
		return bval;
	};
    // \brief �����������εĲ���
    // 
    // �����������εĲ���������������浽���ṹ�С�
    // 
    // \return ��
    // 
    // \param pRect1�����󲢾���1��ָ��
    // \param pRect2�����󲢾���2��ָ��
    // 
    // \note �������ǹ�񻯵ģ���ԭ���������󲢾��β���Ӱ�졣
    //##ModelId=44277FB50070
    template<class TYPE2,class TYPE3> void Union(SPo_TplRect<TYPE2>* pRect1, SPo_TplRect<TYPE3>* pRect2)
	{
		assert(pRect1) ;
		assert(pRect2) ;
		
		if (pRect1 && pRect2)
		{
			SPo_TplRect<TYPE2> rect1;
			SPo_TplRect<TYPE3> rect2;
			
			rect1 = *pRect1;
			rect2 = *pRect2;
			rect1.NormalizeRect();
			rect2.NormalizeRect();
			
			left = ( rect1.left < rect2.left ) ? rect1.left : rect2.left ; // ȡ��ֵ
			right = ( rect1.right > rect2.right ) ? rect1.right : rect2.right ; // ȡСֵ
			
			top = ( rect1.top > rect2.top ) ? rect1.top : rect2.top ; // ȡ��ֵ
			bottom = ( rect1.bottom < rect2.bottom ) ? rect1.bottom : rect2.bottom ; // ȡСֵ
		}
	};
	//////////////////////////////////////////////////////////
	template <class TYPE2> void Union(SPo_TplRect<TYPE2> *pRect2)
	{
		assert(pRect2);
		
		NormalizeRect();
		SPo_TplRect<TYPE2> rect2 = *pRect2;
		rect2.NormalizeRect();
		left = min(left,rect2.left);
		right = max(right,rect2.right);
		top = max(top,rect2.top);
		bottom = min(bottom,rect2.bottom);
	};

	///////////////////////////////////////////////////////
	void Union(RECT *pRect2)
	{
		assert(pRect2);

		NormalizeRect();

		left = min(left,pRect2->left);
		right = max(right,pRect2->right);
		top = max(top,max(pRect2->top,pRect2->bottom));
		bottom = min(bottom,min(pRect2->bottom,pRect2->top));
	};
	///////////////////////////////////////////////////////
	template<class XYTYPE> void Union(XYTYPE x1,XYTYPE y1,XYTYPE x2,XYTYPE y2)
	{
		left = min(left,min(x1,x2));
		right = max(right,max(x1,x2));
		top = max(top,max(y1,y2));
		bottom = min(bottom,min(y1,y2));
	}
//	void Union(Rect *pRect2)
//	{
//		assert(pRect2);
//
//		NormalizeRect();
//
//		left = min(left,min(pRect2->GetLeft(),pRect2->GetRight()));
//		right = max(right,max(pRect2->GetLeft(),pRect2->GetRight()));
//		top = max(top,max(pRect2->GetTop(),pRect2->GetBottom()));
//		bottom = min(bottom,min(pRect2->GetTop(),pRect2->GetBottom()));
//	};
	///////////////////////////////////////////////////////
//	void Union(RectF *pRect2)
//	{
//		assert(pRect2);
//		
//		NormalizeRect();
//		
//		left = min(left,min(pRect2->GetLeft(),pRect2->GetRight()));
//		right = max(right,max(pRect2->GetLeft(),pRect2->GetRight()));
//		top = max(top,max(pRect2->GetTop(),pRect2->GetBottom()));
//		bottom = min(bottom,min(pRect2->GetTop(),pRect2->GetBottom()));
//	};
    // \brief ��������
    // 
    // ���㵱ǰ������������εĲ���������������浽����ṹ�С�
    // 
    // \return ����ṹ
    // 
    // \param right�����������Ҳ�������
    // 
    // \note �������ǹ�񻯵ģ���ԭ���������󲢾��β���Ӱ�졣
    //##ModelId=442783170128
	SPo_TplRect<TYPE> operator+(const SPo_TplRect<TYPE> &right)
	{
		SPo_TplRect<TYPE> this_rect, right_rect;
		this_rect = *this;
		right_rect = right;
		
		this_rect.NormalizeRect();
		right_rect.NormalizeRect();
		
		return SPo_TplRect(( this_rect.left < right_rect.left ) ? this_rect.left :right_rect.left, // ȡСֵ
			( this_rect.top > right_rect.top ) ? this_rect.top :right_rect.top,// ȡ��ֵ
			( this_rect.right > right_rect.right ) ? this_rect.right : right_rect.right,// ȡ��ֵ
			( this_rect.bottom < right_rect.bottom ) ? this_rect.bottom : right_rect.bottom);// ȡСֵ

	};
	

    // \brief ������ֵ����
    // 
    //  ���㵱ǰ������������εĲ���������������浽��ǰ�ṹ�С�
    // 
    // \return ��ǰ�ṹ������
    // 
    // \param right��������ֵ�����Ҳ�������
    // 
    // \note �������ǹ�񻯵ģ���ԭ���Ҳ��������β���Ӱ�졣
    //##ModelId=44278374033C
    SPo_TplRect<TYPE> operator+=(const SPo_TplRect<TYPE> &right)
	{
		SPo_TplRect<TYPE> this_rect, right_rect;
		this_rect = *this;
		right_rect = right;
		
		this_rect.NormalizeRect();
		right_rect.NormalizeRect();

		this->left = ( this_rect.left < right_rect.left ) ? this_rect.left : right_rect.left ; // ȡСֵ
		this->right = ( this_rect.right > right_rect.right ) ? this_rect.right : right_rect.right ; // ȡ��ֵ
		
		this->top = ( this_rect.top > right_rect.top ) ? this_rect.top :right_rect.top ; // ȡ��ֵ
		this->bottom = ( this_rect.bottom < right_rect.bottom ) ? this_rect.bottom : right_rect.bottom ; // ȡСֵ
		
		return *this ;
	};
	

    // \brief ��������
    // 
    // ���㵱ǰ������������εĽ���������������浽����ṹ�С���������β��ཻ�������ṹ����SGIS_Rect(0,0,0,0)��
    // 
    // \return ����ṹ
    // 
    // \param right�����������Ҳ�������
    // 
    // \note �������ǹ�񻯵ģ���ԭ���������󽻾��β���Ӱ�졣
    //##ModelId=442783C90167
    SPo_TplRect<TYPE> operator&(const SPo_TplRect<TYPE> &right)
	{
		SPo_TplRect<TYPE> this_rect, right_rect, rect_result ;
		this_rect = *this;
		right_rect = right;
		
		this_rect.NormalizeRect();
		right_rect.NormalizeRect();
		
		if (this_rect.left > right_rect.right || this_rect.right < right_rect.left
            || this_rect.bottom > right_rect.top || this_rect.top < right_rect.bottom)
		{
			rect_result.left = 0 ;
			rect_result.right = 0 ;
			
			rect_result.top = 0 ;
			rect_result.bottom = 0 ;
		}
		else
		{				
			rect_result.left = ( this_rect.left > right.left ) ? this_rect.left : right_rect.left ; // ȡ��ֵ
			rect_result.right = ( this_rect.right < right.right ) ? this_rect.right : right_rect.right ; // ȡСֵ
			
			rect_result.top = ( this_rect.top < right.top ) ? this_rect.top :right_rect.top ; // ȡСֵ
			rect_result.bottom = ( this_rect.bottom > right.bottom ) ? this_rect.bottom : right_rect.bottom ; // ȡ��ֵ
		}
		
		return rect_result ;
	};

    // \brief ������ֵ����
    // 
    // ���㵱ǰ������������εĽ���������������浽��ǰ�ṹ�С���������β��ཻ����ǰ�ṹ����SGIS_Rect(0,0,0,0)��
    // 
    // \return ��ǰ�ṹ������
    // 
    // \param right��������ֵ�����Ҳ�������
    // 
    // \note �������ǹ�񻯵ģ���ԭ���Ҳ��������β���Ӱ�졣
    //##ModelId=4427841902FD
    SPo_TplRect<TYPE> operator&=(const SPo_TplRect<TYPE> &right)
	{
		SPo_TplRect<TYPE> right_rect;
		
		right_rect = right;
		right_rect.NormalizeRect();
		this->NormalizeRect();
		
		if (this->left > right_rect.right || this->right < right_rect.left
            || this->bottom > right_rect.top || this->top < right_rect.bottom)
		{
			this->left = 0 ;
			this->right = 0 ;
			
			this->top = 0 ;
			this->bottom = 0 ;
		}
		else
		{				
			this->left = ( this->left > right.left ) ? this->left : right_rect.left ; // ȡ��ֵ
			this->right = ( this->right < right.right ) ? this->right : right_rect.right ; // ȡСֵ
			
			this->top = ( this->top < right.top ) ? this->top :right_rect.top ; // ȡСֵ
			this->bottom = ( this->bottom > right.bottom ) ? this->bottom : right_rect.bottom ; // ȡ��ֵ
		}
		
		return *this ;
	};

    // \brief ����������
    // 
    // �жϵ�ǰ�����Ƿ���һ���ΰ�����
    // 
    // \return ������������򷵻�1�����򣬷���0��
    // 
    // \param right�����������Ҳ�����
    //##ModelId=4427845103C8
    bool operator<(const SPo_TplRect<TYPE> &right)
	{
		SPo_TplRect<TYPE> this_rect, right_rect;
		this_rect = *this;
		right_rect = right;
		
		this_rect.NormalizeRect();
		right_rect.NormalizeRect();
		
		if (this_rect.left > right_rect.left && this_rect.right < right_rect.right
            && this_rect.bottom > right_rect.bottom && this_rect.top < right_rect.top)
		{
            return 1 ;
		}
		else
            return 0 ;
	};

    // \brief ������/�غ�����
    // 
    // �жϵ�ǰ�����Ƿ���һ���ΰ���(���Ա߽����غ�)��
    // 
    // \return ������������򷵻�1�����򣬷���0��
    // 
    // \param right�����������Ҳ�����
    //##ModelId=4427848403D8
    bool  operator<=(const SPo_TplRect<TYPE> &right)
	{
		SPo_TplRect<TYPE>  this_rect, right_rect;
		this_rect = *this;
		right_rect = right;
		
		this_rect.NormalizeRect();
		right_rect.NormalizeRect();
		
		if (this_rect.left >= right_rect.left && this_rect.right <= right_rect.right
            && this_rect.bottom >= right_rect.bottom && this_rect.top <= right_rect.top)
		{
            return 1 ;
		}
		else
            return 0 ;
	};

	//ycc add for R-tree 2007-12-3
	template<class TYPE2> bool Contains(const SPo_TplRect<TYPE2> &right)
	{
		SPo_TplRect<TYPE> rc;
		rc.bottom = right.bottom;rc.top = right.top;
		rc.left = right.left;rc.right = right.right;
		return rc <= *this;
	}

	TYPE GetArea()
	{
		return 1 * GetWidth() * GetHeight() ;
	};

	template<class TYPE2,class TYPE3> void SplitRtree(SPo_TplRect<TYPE2> &r0,SPo_TplRect<TYPE3> & r1) const
	{
		this->NormalizeRect();
		double range;
		//r0 = r1 = *this;	 ////////////////
		r0.left = left;r1.left = left;
		r0.right = right;r1.right=right;
		r0.top = top;r1.top=top;
		r0.bottom=bottom;r1.bottom=bottom;
		// Split in the widest direction
		if ((right - left) > (top - bottom)) {
			// X direction
			range = right - left;
			
			r0.right = left + (long) (range * SPLITRATIO +.5);
			r1.left = right - (long) (range * SPLITRATIO +.5);
		} else {
			// Y direction
			range = top - bottom;
			
			r0.top = bottom + (long) (range * SPLITRATIO +.5);
			r1.bottom = top - (long) (range * SPLITRATIO +.5);
		}

	}
	//�жϾ��������㶨���ֱ�߶��Ƿ��ཻ
	template<class TYPE2> bool RectIntersectLine(TYPE2 *px1,TYPE2 *py1,TYPE2 *px2,TYPE2 *py2)
	{
		double rxmin = left;		double rymin = (top<bottom?top:bottom);
		double rxmax = right;		double rymax = (bottom>top?bottom:top);
		
		bool bxval = true;				bool byval = true;
		int i31 = 0;					int i32 = 0;//������ֵ������������ߣ�1�������м�0�������ұ�1
		
		if(*px1<rxmin)						i31 = -1;
		else if(*px1>=rxmin&&*px1<=rxmax)	i31 = 0;
		else if(*px1>rxmax)					i31 = 1;
		
		if(*px2<rxmin)						i32 = -1;
		else if(*px2>=rxmin&&*px2<=rxmax)	i32 = 0;
		else if(*px2>rxmax)					i32 = 1;
		
		if(i32*i31>0)	bxval = false;//x���䲻�ཻ
		
		if(*py1<rymin)						i31 = -1;
		else if(*py1>=rymin&&*py1<=rymax)	i31 = 0;
		else if(*py1>rymax)					i31 = 1;
		
		if(*py2<rymin)						i32 = -1;
		else if(*py2>=rymin&&*py2<=rymax)	i32 = 0;
		else if(*py2>rymax)					i32 = 1;
		
		if(i32*i31>0)	byval = false;//y���䲻�ཻ
		
		return bxval&&byval;
	};
	//����Խ��߳���
	TYPE GetInvAx()
	{
		double w = GetWidth();
		double h = GetHeight();
		double ax = sqrt(w*w+h*h);
		return (TYPE)ax;
	};
	//hls added 20100520
	size_t BytesSerializeSize()
	{
		return sizeof(left)+sizeof(right)+sizeof(top)+sizeof(bottom);
	};
	size_t BytesSerialize(bool bRead,PBYTE *ppBytes)
	{
		size_t pos = 0;

		pos += _cbrw(bRead,&left,sizeof(left),1,(*ppBytes)+pos);
		pos += _cbrw(bRead,&right,sizeof(right),1,(*ppBytes)+pos);
		pos += _cbrw(bRead,&top,sizeof(top),1,(*ppBytes)+pos);
		pos += _cbrw(bRead,&bottom,sizeof(bottom),1,(*ppBytes)+pos);

		return pos;
	};
	//ycc add end 2007-12-3
	//���л�����
	void Serialize(CArchive &ar)
	{
		double dl = left;double dr = right;double dt = top;double db = bottom;
		if(ar.IsStoring())
		{
			ar << dl;ar << dr;ar << dt;ar << db;
		}
		else
		{
			ar >> dl;ar >> dr;ar >> dt;ar >> db;
			left = (TYPE)dl;right = (TYPE)dr;top = (TYPE)dt;bottom = (TYPE)db;
		}
	};
};

//////////////////////////////////////////////////////////////////////////
// \brief �����������εĽ���
// 
// �����������εĽ���������������浽���ṹ�С���������β��ཻ���򱾽ṹ����SPo_TplRect(0,0,0,0)��
// 
// \return �Ƿ����ཻ����,���ཻ�ķ���true,û���ཻ���ַ���false
// 
// \param pRect1�����󽻾���1��ָ��
// \param pRect2�����󽻾���2��ָ��
// 
// \note �������ǹ�񻯵ģ���ԭ���������󽻾��β���Ӱ�졣
//##ModelId=4427829900BB
template<class TYPE> inline bool SpoRectIntersect(SPo_TplRect<TYPE>* pRect1, RECT *pRect2)
{
	assert(pRect1) ;
	assert(pRect2) ;
	if (pRect1 && pRect2)
	{
		SPo_TplRect<TYPE> rect1;
		SPo_TplRect<TYPE> rect2;
		
		rect1 = *pRect1;
		rect2.left = pRect2->left;rect2.right=pRect2->right;rect2.bottom=pRect2->bottom;rect2.top=pRect2->top;
		
		rect1.NormalizeRect();
		rect2.NormalizeRect();
		
		if (rect1.left > rect2.right || rect1.right < rect2.left
			|| rect1.bottom > rect2.top || rect1.top < rect2.bottom)
		{
			return false;
		}
		else
		{	
			return true;
		}
	}
	return false;
};
template<class TYPE> inline bool SpoRectIntersect(SPo_TplRect<TYPE>* pRect1, SPo_TplRect<TYPE> *pRect2)
{
	assert(pRect1) ;
	assert(pRect2) ;
	if (pRect1 && pRect2)
	{
		SPo_TplRect<TYPE> rect1;
		SPo_TplRect<TYPE> rect2;
		
		rect1 = *pRect1;
		rect2.left = pRect2->left;rect2.right=pRect2->right;rect2.bottom=pRect2->bottom;rect2.top=pRect2->top;
		
		rect1.NormalizeRect();
		rect2.NormalizeRect();
		
		if (rect1.left > rect2.right || rect1.right < rect2.left
			|| rect1.bottom > rect2.top || rect1.top < rect2.bottom)
		{
			return false;
		}
		else
		{	
			return true;
		}
	}
	return false;
};

template<class TYPE1,class TYPE2> inline bool SpoRectIntersect(TYPE1 x11,TYPE1 y11,TYPE1 x12,TYPE1 y12,TYPE2 x21,TYPE2 y21,TYPE2 x22,TYPE2 y22, double iTolerance = 0)
{
	double minx1=min(x11,x12);
	double maxx1=max(x11,x12);
	double miny1=min(y11,y12);
	double maxy1=max(y11,y12);

	double minx2=min(x21,x22);
	double maxx2=max(x21,x22);
	double miny2=min(y21,y22);
	double maxy2=max(y21,y22);

	if (minx1 < (maxx2 + iTolerance) && maxx1 > (minx2 - iTolerance)
		&& miny1 < (maxy2 + iTolerance) && maxy1 > (miny2 - iTolerance))
		return 1 ;
	else
		return 0 ;
};

#endif /* SPO_TPLRECT_H_HEADER_INCLUDED_B9A1D13B */
