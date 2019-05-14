#ifndef SPO_PAGEVIEWPARAMAGENT_H_HEADER_INCLUDED_B054E5B6
#define SPO_PAGEVIEWPARAMAGENT_H_HEADER_INCLUDED_B054E5B6

//##ModelId=4FAB451103B9
#include "Spo_pageviewparam.h"
////
class SPo_PageViewParamAgent
{
	//页面起始位置；逻辑象素坐标
	//##ModelId=4B49E7FE005F
	float m_startX;//不带缩放，保持不变,缩放前的坐标
	//##ModelId=4B49E7FE006D
	float m_startY;//不带缩放，保持不变,缩放前的坐标
	//页面缩放倍数；
	//##ModelId=4B49E7FE009C
	float m_zoomP;
	//页面大小；像素单位；
	//##ModelId=4B49E7FE007E
	int m_UpageX;//不带缩放，保持不变,缩放前的坐标
	//##ModelId=4B49E7FE007F
	int m_UpageY;//不带缩放，保持不变,缩放前的坐标
	//页面窗口指针
	CView *m_pView;
public:
	SPo_PageViewParamAgent(CView *pView=NULL,float fStartX=0,float fStartY=0,int fUpageX=0,int fUpageY=0,float fZoomP=1)
	{
		m_pView = pView;m_startX = fStartX;m_startY = fStartY;m_UpageX = fUpageX;m_UpageY = fUpageY;m_zoomP = fZoomP;
	};
	SPo_PageViewParamAgent(SPo_PageViewParam &sp)//重写拷贝初始化函数
	{
		this->m_startX = sp.m_startX;
		this->m_startY = sp.m_startY;
		this->m_UpageX = sp.m_UpageX;
		this->m_UpageY = sp.m_UpageY;
		this->m_zoomP = sp.m_zoomP;
		this->m_pView = sp.m_pView;
	}
	//获取纸张缩放比例系数
	float GetZoomScale(bool bPrinting)
	{
		if(bPrinting)	
			return 1.0f;
		else
			return m_zoomP;
	}
	//从设备坐标象素到1：1无缩放时的页面象素逻辑坐标的转化
	template<class XYTYPE> SPo_DPoint2D DpToUp(XYTYPE ptX,XYTYPE ptY,bool bPrinting)
	{
		CPoint cpt(ptX,ptY);
		DPtoLP(&cpt);
		SPo_DPoint2D dPt = LpToUp(cpt.x,cpt.y,bPrinting);
		return dPt;
	}
	//从最终页面的逻辑坐标转换到1：1无缩放时的页面象素逻辑坐标
	SPo_DPoint2D LpToUp(double x,double y,bool bPrinting)
	{
		if(bPrinting)
			return SPo_DPoint2D(x,y);
		else
			return SPo_DPoint2D((x-m_startX)/m_zoomP,(y-m_startY)/m_zoomP);
	}
	//从1：1无缩放时的页面象素逻辑坐标到设备坐标象素的转换
	POINT UpToDp(float fX,float fY,bool bPrinting)
	{
		SPo_DPoint2D dPt = UpToLp(fX,fY,bPrinting);
		POINT lpt;lpt.x = (long)(dPt.x);lpt.y = (long)(dPt.y);
		LPtoDP(&lpt);
		return lpt;
	}
	//从1：1无缩放时的页面象素逻辑坐标到设备坐标象素的转换
	POINT UpToDp(SPo_FPoint pt,bool bPrinting)
	{
		SPo_DPoint2D dPt = UpToLp(pt.x,pt.y,bPrinting);
		POINT lpt;lpt.x = (long)(dPt.x);lpt.y = (long)(dPt.y);
		LPtoDP(&lpt);
		return lpt;
	}
	//从1：1无缩放时的页面象素逻辑坐标转换到最终页面的逻辑坐标
	SPo_DPoint2D UpToLp(double x,double y,bool bPrinting)
	{
		if(bPrinting)
			return SPo_DPoint2D(x,y);
		else
			return SPo_DPoint2D(m_startX+x*m_zoomP,m_startY+y*m_zoomP);
	}
	//从1：1无缩放时的页面象素逻辑坐标转换到最终(PDF/EPS)页面的逻辑坐标
	SPo_DPoint2D UpToLpEdc(double x,double y,bool bPrinting)
	{
		if(m_pView==NULL)return SPo_DPoint2D(x,y);

		double ftDpiX = 0;double ftDpiY = 0;double ftDpiXEdc = 7200/INCH_TO_CM;double ftDpiYEdc = 7200/INCH_TO_CM;bool bYup = false;
		CDC *pDC = m_pView->GetDC();
		GetDeviceDpi(pDC,ftDpiX,ftDpiY,bYup);
		
		m_pView->ReleaseDC(pDC);
		
		return SPo_DPoint2D(dValCF(x*ftDpiXEdc/ftDpiX),dValCF((m_UpageY-y)*ftDpiYEdc/ftDpiY));
	}
	//从实际厘米转换到最终页面象素坐标
	SPo_DPoint2D CmToLp(double x,double y,bool bPrinting)
	{
		if(m_pView==NULL)return SPo_DPoint2D(x,y);

		double fDpix = 0;double fDpiy = 0;bool bYup = false;
		CDC *pDC = m_pView->GetDC();
		GetDeviceDpi(pDC,fDpix,fDpiy,bYup);
		
		SPo_DPoint2D dptU(x*0.01*fDpix,y*0.01*fDpiy);
		SPo_DPoint2D dptC = UpToLp(dptU.x,dptU.y,bPrinting);
		m_pView->ReleaseDC(pDC);
		return dptC;
	}
	//从最终页面象素坐标转换成实际厘米坐标
	SPo_DPoint2D LpToCm(double x,double y,bool bPrinting)
	{
		if(m_pView==NULL)return SPo_DPoint2D(x,y);

		double fDpix = 0;double fDpiy = 0;bool bYup = false;
		CDC *pDC = m_pView->GetDC();
		GetDeviceDpi(pDC,fDpix,fDpiy,bYup);
		
		SPo_DPoint2D dptU = LpToUp(x,y,bPrinting);
		SPo_DPoint2D dptcm(dptU.x*100/fDpix,dptU.y*100/fDpiy);
		m_pView->ReleaseDC(pDC);
		return dptcm;
	}
	//从实际厘米转换到原始1：1页面象素坐标
	SPo_DPoint2D CmToUp(double x,double y,bool bPrinting)
	{
		if(m_pView==NULL)return SPo_DPoint2D(x,y);

		double fDpix = 0;double fDpiy = 0;bool bYup = false;
		CDC *pDC = m_pView->GetDC();
		GetDeviceDpi(pDC,fDpix,fDpiy,bYup);
		
		SPo_DPoint2D dptU(x*0.01*fDpix,y*0.01*fDpiy);
		m_pView->ReleaseDC(pDC);
		return dptU;
	}
	//从原始1：1页面象素坐标转换成实际厘米坐标
	SPo_DPoint2D UpToCm(double x,double y,bool bPrinting)
	{
		if(m_pView==NULL)return SPo_DPoint2D(x,y);

		double fDpix = 0;double fDpiy = 0;bool bYup = false;
		CDC *pDC = m_pView->GetDC();
		GetDeviceDpi(pDC,fDpix,fDpiy,bYup);
		
		SPo_DPoint2D dptcm(x*100/fDpix,y*100/fDpiy);
		m_pView->ReleaseDC(pDC);
		return dptcm;
	}
	//从设备坐标到逻辑坐标(象素)
	void DPtoLP(LPPOINT pPoints,int nCount = 1)
	{	
		if(m_pView==NULL)return ;
		CDC *pDC = m_pView->GetDC();
		m_pView->OnPrepareDC(pDC, NULL);
		pDC->DPtoLP(pPoints,nCount);
		m_pView->ReleaseDC(pDC);
	}
	//
	void DPtoLP(LPRECT pRect)
	{
		if(m_pView==NULL)return ;
		CDC *pDC = m_pView->GetDC();
		m_pView->OnPrepareDC(pDC, NULL);
		pDC->DPtoLP(pRect);
		m_pView->ReleaseDC(pDC);
	}
	//
	void LPtoDP(LPPOINT pPoints,int nCount = 1)
	{
		if(m_pView==NULL)return ;
		CDC *pDC = m_pView->GetDC();
		m_pView->OnPrepareDC(pDC, NULL);
		pDC->LPtoDP(pPoints,nCount);
		m_pView->ReleaseDC(pDC);
	}
	//
	void LPtoDP(LPRECT pRect)
	{
		if(m_pView==NULL)return ;
		CDC *pDC = m_pView->GetDC();
		m_pView->OnPrepareDC(pDC, NULL);
		pDC->LPtoDP(pRect);
		m_pView->ReleaseDC(pDC);
	}
	//从设备坐标象素到1：1无缩放时的页面象素逻辑坐标的转化
	template<class XYTYPE> SPo_DRect DpToUp(XYTYPE x1,XYTYPE y1,XYTYPE x2,XYTYPE y2,bool bPrinting)
	{
		RECT lrc;
		lrc.left = min(x1,x2);
		lrc.right = max(x1,x2);
		lrc.top = min(y1,y2);
		lrc.bottom = max(y1,y2);
		DPtoLP(&lrc);
		SPo_DRect dRcr = LpToUp(SPo_DRect(lrc.left,lrc.top,lrc.right,lrc.bottom),bPrinting);
		return dRcr;
	}
	//从最终页面的逻辑坐标转换到1：1无缩放时的页面象素逻辑坐标
	SPo_DRect LpToUp(SPo_DRect tRc,bool bPrinting)
	{
		SPo_DPoint2D dptLT = LpToUp(tRc.left,tRc.top,bPrinting);
		SPo_DPoint2D dptRB = LpToUp(tRc.right,tRc.bottom,bPrinting);
		SPo_DRect rRc(dptLT.x,dptLT.y,dptRB.x,dptRB.y);
		return rRc;
	}
	//从1：1无缩放时的页面象素逻辑坐标到设备坐标象素的转换
	RECT UpToDp(SPo_DRect rc,bool bPrinting)
	{
		SPo_DRect dRc = UpToLp(rc,bPrinting);
		RECT lrc;
		lrc.left = (long)(dRc.left);
		lrc.right = (long)(dRc.right);
		lrc.top = (long)min(dRc.top,dRc.bottom);
		lrc.bottom = (long)max(dRc.top,dRc.bottom);
		LPtoDP(&lrc);
		return lrc;
	}
	//从1：1无缩放时的页面象素逻辑坐标转换到最终页面的逻辑坐标
	SPo_DRect UpToLp(SPo_DRect tRc,bool bPrinting)
	{
		SPo_DPoint2D dptLT = UpToLp(tRc.left,tRc.top,bPrinting);
		SPo_DPoint2D dptRB = UpToLp(tRc.right,tRc.bottom,bPrinting);
		SPo_DRect rRc(dptLT.x,dptLT.y,dptRB.x,dptRB.y);
		return rRc;
	}
	//从1：1无缩放时的页面象素逻辑坐标转换到最终(PDF/EPS)页面的逻辑坐标
	SPo_DRect UpToLpEdc(SPo_DRect tRc,bool bPrinting)
	{
		SPo_DPoint2D lb = UpToLpEdc(tRc.left,max(tRc.bottom,tRc.top),bPrinting);
		SPo_DPoint2D rt = UpToLpEdc(tRc.right,min(tRc.bottom,tRc.top),bPrinting);
		
		return SPo_DRect(lb.x,rt.y,rt.x,lb.y);
	}
	//从1：1无缩放时的页面象素逻辑坐标转换到另一个设备坐标面的逻辑坐标
	//##ModelId=4B49E7FE01B9
	SPo_DRect UpToLp2(SPo_DRect tRc,bool bPrinting,HDC hdc2)
	{
		SPo_DPoint2D dptLT = UpToLp2(tRc.left,tRc.top,bPrinting,hdc2);
		SPo_DPoint2D dptRB = UpToLp2(tRc.right,tRc.bottom,bPrinting,hdc2);
		SPo_DRect rRc(dptLT.x,dptLT.y,dptRB.x,dptRB.y);
		return rRc;
	}
	//从1：1无缩放时的页面象素逻辑坐标转换到另一个设备坐标面的逻辑坐标
	SPo_DPoint2D UpToLp2(double x,double y,bool bPrinting,HDC hdc2)
	{
		if(m_pView==NULL)return SPo_DPoint2D(x,y);
		
		double ftDpiX = 0;double ftDpiY = 0;bool bYup = false;double ftDpiX2 = 0;double ftDpiY2 = 0;bool bYup2 = false;
		CDC *pDC = m_pView->GetDC();
		GetDeviceDpi(pDC,ftDpiX,ftDpiY,bYup);
		m_pView->ReleaseDC(pDC);
		
		Graphics Gp2(hdc2);
		GetDeviceDpi(&Gp2,ftDpiX2,ftDpiY2,bYup2);
		Gp2.ReleaseHDC(hdc2);
		
		return SPo_DPoint2D(dValCF(x*ftDpiX2/ftDpiX),dValCF((m_UpageY-y)*ftDpiY2/ftDpiY));
	}
	//从1：1无缩放时的页面象素逻辑坐标到设备坐标象素的转换
	SPo_FRect UpToDpF(SPo_FRect rc,bool bPrinting)
	{
		RECT cRc = UpToDp(SPo_DRect(rc.left,rc.top,rc.right,rc.bottom),bPrinting);
		return SPo_FRect((float)(cRc.left),(float)(cRc.top),(float)(cRc.right),(float)(cRc.bottom));
	}
	//从1：1无缩放时的页面象素逻辑坐标转换到最终页面的逻辑坐标
	SPo_FRect UpToLpF(SPo_FRect tRc,bool bPrinting)
	{
		SPo_DPoint2D dptLT = UpToLp(tRc.left,tRc.top,bPrinting);
		SPo_DPoint2D dptRB = UpToLp(tRc.right,tRc.bottom,bPrinting);
		SPo_FRect rRc((float)(dptLT.x),(float)(dptLT.y),(float)(dptRB.x),(float)(dptRB.y));
		return rRc;
	}
	//从实际厘米转换到最终页面象素坐标
	SPo_DRect CmToLp(SPo_DRect tRc,bool bPrinting)
	{
		SPo_DPoint2D dptLT = CmToLp(tRc.left,tRc.top,bPrinting);
		SPo_DPoint2D dptRB = CmToLp(tRc.right,tRc.bottom,bPrinting);
		SPo_DRect rRc(dptLT.x,dptLT.y,dptRB.x,dptRB.y);
		return rRc;
	}
	//从最终页面象素坐标转换成实际厘米坐标
	SPo_DRect LpToCm(SPo_DRect tRc,bool bPrinting)
	{
		SPo_DPoint2D dptLT = LpToCm(tRc.left,tRc.top,bPrinting);
		SPo_DPoint2D dptRB = LpToCm(tRc.right,tRc.bottom,bPrinting);
		SPo_DRect rRc(dptLT.x,dptLT.y,dptRB.x,dptRB.y);
		return rRc;
	}
	//从实际厘米转换到原始1：1页面象素坐标
	SPo_DRect CmToUp(SPo_DRect tRc,bool bPrinting)
	{
		SPo_DPoint2D dptLT = CmToUp(tRc.left,tRc.top,bPrinting);
		SPo_DPoint2D dptRB = CmToUp(tRc.right,tRc.bottom,bPrinting);
		SPo_DRect rRc(dptLT.x,dptLT.y,dptRB.x,dptRB.y);
		return rRc;
	}
	//从原始1：1页面象素坐标转换成实际厘米坐标
	SPo_DRect UpToCm(SPo_DRect tRc,bool bPrinting)
	{
		SPo_DPoint2D dptLT = UpToCm(tRc.left,tRc.top,bPrinting);
		SPo_DPoint2D dptRB = UpToCm(tRc.right,tRc.bottom,bPrinting);
		SPo_DRect rRc(dptLT.x,dptLT.y,dptRB.x,dptRB.y);
		return rRc;
	}
};


#endif /* SPO_PAGEVIEWPARAMAGENT_H_HEADER_INCLUDED_B054E5B6 */
