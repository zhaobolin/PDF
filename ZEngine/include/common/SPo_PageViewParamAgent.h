#ifndef SPO_PAGEVIEWPARAMAGENT_H_HEADER_INCLUDED_B054E5B6
#define SPO_PAGEVIEWPARAMAGENT_H_HEADER_INCLUDED_B054E5B6

//##ModelId=4FAB451103B9
#include "Spo_pageviewparam.h"
////
class SPo_PageViewParamAgent
{
	//ҳ����ʼλ�ã��߼���������
	//##ModelId=4B49E7FE005F
	float m_startX;//�������ţ����ֲ���,����ǰ������
	//##ModelId=4B49E7FE006D
	float m_startY;//�������ţ����ֲ���,����ǰ������
	//ҳ�����ű�����
	//##ModelId=4B49E7FE009C
	float m_zoomP;
	//ҳ���С�����ص�λ��
	//##ModelId=4B49E7FE007E
	int m_UpageX;//�������ţ����ֲ���,����ǰ������
	//##ModelId=4B49E7FE007F
	int m_UpageY;//�������ţ����ֲ���,����ǰ������
	//ҳ�洰��ָ��
	CView *m_pView;
public:
	SPo_PageViewParamAgent(CView *pView=NULL,float fStartX=0,float fStartY=0,int fUpageX=0,int fUpageY=0,float fZoomP=1)
	{
		m_pView = pView;m_startX = fStartX;m_startY = fStartY;m_UpageX = fUpageX;m_UpageY = fUpageY;m_zoomP = fZoomP;
	};
	SPo_PageViewParamAgent(SPo_PageViewParam &sp)//��д������ʼ������
	{
		this->m_startX = sp.m_startX;
		this->m_startY = sp.m_startY;
		this->m_UpageX = sp.m_UpageX;
		this->m_UpageY = sp.m_UpageY;
		this->m_zoomP = sp.m_zoomP;
		this->m_pView = sp.m_pView;
	}
	//��ȡֽ�����ű���ϵ��
	float GetZoomScale(bool bPrinting)
	{
		if(bPrinting)	
			return 1.0f;
		else
			return m_zoomP;
	}
	//���豸�������ص�1��1������ʱ��ҳ�������߼������ת��
	template<class XYTYPE> SPo_DPoint2D DpToUp(XYTYPE ptX,XYTYPE ptY,bool bPrinting)
	{
		CPoint cpt(ptX,ptY);
		DPtoLP(&cpt);
		SPo_DPoint2D dPt = LpToUp(cpt.x,cpt.y,bPrinting);
		return dPt;
	}
	//������ҳ����߼�����ת����1��1������ʱ��ҳ�������߼�����
	SPo_DPoint2D LpToUp(double x,double y,bool bPrinting)
	{
		if(bPrinting)
			return SPo_DPoint2D(x,y);
		else
			return SPo_DPoint2D((x-m_startX)/m_zoomP,(y-m_startY)/m_zoomP);
	}
	//��1��1������ʱ��ҳ�������߼����굽�豸�������ص�ת��
	POINT UpToDp(float fX,float fY,bool bPrinting)
	{
		SPo_DPoint2D dPt = UpToLp(fX,fY,bPrinting);
		POINT lpt;lpt.x = (long)(dPt.x);lpt.y = (long)(dPt.y);
		LPtoDP(&lpt);
		return lpt;
	}
	//��1��1������ʱ��ҳ�������߼����굽�豸�������ص�ת��
	POINT UpToDp(SPo_FPoint pt,bool bPrinting)
	{
		SPo_DPoint2D dPt = UpToLp(pt.x,pt.y,bPrinting);
		POINT lpt;lpt.x = (long)(dPt.x);lpt.y = (long)(dPt.y);
		LPtoDP(&lpt);
		return lpt;
	}
	//��1��1������ʱ��ҳ�������߼�����ת��������ҳ����߼�����
	SPo_DPoint2D UpToLp(double x,double y,bool bPrinting)
	{
		if(bPrinting)
			return SPo_DPoint2D(x,y);
		else
			return SPo_DPoint2D(m_startX+x*m_zoomP,m_startY+y*m_zoomP);
	}
	//��1��1������ʱ��ҳ�������߼�����ת��������(PDF/EPS)ҳ����߼�����
	SPo_DPoint2D UpToLpEdc(double x,double y,bool bPrinting)
	{
		if(m_pView==NULL)return SPo_DPoint2D(x,y);

		double ftDpiX = 0;double ftDpiY = 0;double ftDpiXEdc = 7200/INCH_TO_CM;double ftDpiYEdc = 7200/INCH_TO_CM;bool bYup = false;
		CDC *pDC = m_pView->GetDC();
		GetDeviceDpi(pDC,ftDpiX,ftDpiY,bYup);
		
		m_pView->ReleaseDC(pDC);
		
		return SPo_DPoint2D(dValCF(x*ftDpiXEdc/ftDpiX),dValCF((m_UpageY-y)*ftDpiYEdc/ftDpiY));
	}
	//��ʵ������ת��������ҳ����������
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
	//������ҳ����������ת����ʵ����������
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
	//��ʵ������ת����ԭʼ1��1ҳ����������
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
	//��ԭʼ1��1ҳ����������ת����ʵ����������
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
	//���豸���굽�߼�����(����)
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
	//���豸�������ص�1��1������ʱ��ҳ�������߼������ת��
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
	//������ҳ����߼�����ת����1��1������ʱ��ҳ�������߼�����
	SPo_DRect LpToUp(SPo_DRect tRc,bool bPrinting)
	{
		SPo_DPoint2D dptLT = LpToUp(tRc.left,tRc.top,bPrinting);
		SPo_DPoint2D dptRB = LpToUp(tRc.right,tRc.bottom,bPrinting);
		SPo_DRect rRc(dptLT.x,dptLT.y,dptRB.x,dptRB.y);
		return rRc;
	}
	//��1��1������ʱ��ҳ�������߼����굽�豸�������ص�ת��
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
	//��1��1������ʱ��ҳ�������߼�����ת��������ҳ����߼�����
	SPo_DRect UpToLp(SPo_DRect tRc,bool bPrinting)
	{
		SPo_DPoint2D dptLT = UpToLp(tRc.left,tRc.top,bPrinting);
		SPo_DPoint2D dptRB = UpToLp(tRc.right,tRc.bottom,bPrinting);
		SPo_DRect rRc(dptLT.x,dptLT.y,dptRB.x,dptRB.y);
		return rRc;
	}
	//��1��1������ʱ��ҳ�������߼�����ת��������(PDF/EPS)ҳ����߼�����
	SPo_DRect UpToLpEdc(SPo_DRect tRc,bool bPrinting)
	{
		SPo_DPoint2D lb = UpToLpEdc(tRc.left,max(tRc.bottom,tRc.top),bPrinting);
		SPo_DPoint2D rt = UpToLpEdc(tRc.right,min(tRc.bottom,tRc.top),bPrinting);
		
		return SPo_DRect(lb.x,rt.y,rt.x,lb.y);
	}
	//��1��1������ʱ��ҳ�������߼�����ת������һ���豸��������߼�����
	//##ModelId=4B49E7FE01B9
	SPo_DRect UpToLp2(SPo_DRect tRc,bool bPrinting,HDC hdc2)
	{
		SPo_DPoint2D dptLT = UpToLp2(tRc.left,tRc.top,bPrinting,hdc2);
		SPo_DPoint2D dptRB = UpToLp2(tRc.right,tRc.bottom,bPrinting,hdc2);
		SPo_DRect rRc(dptLT.x,dptLT.y,dptRB.x,dptRB.y);
		return rRc;
	}
	//��1��1������ʱ��ҳ�������߼�����ת������һ���豸��������߼�����
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
	//��1��1������ʱ��ҳ�������߼����굽�豸�������ص�ת��
	SPo_FRect UpToDpF(SPo_FRect rc,bool bPrinting)
	{
		RECT cRc = UpToDp(SPo_DRect(rc.left,rc.top,rc.right,rc.bottom),bPrinting);
		return SPo_FRect((float)(cRc.left),(float)(cRc.top),(float)(cRc.right),(float)(cRc.bottom));
	}
	//��1��1������ʱ��ҳ�������߼�����ת��������ҳ����߼�����
	SPo_FRect UpToLpF(SPo_FRect tRc,bool bPrinting)
	{
		SPo_DPoint2D dptLT = UpToLp(tRc.left,tRc.top,bPrinting);
		SPo_DPoint2D dptRB = UpToLp(tRc.right,tRc.bottom,bPrinting);
		SPo_FRect rRc((float)(dptLT.x),(float)(dptLT.y),(float)(dptRB.x),(float)(dptRB.y));
		return rRc;
	}
	//��ʵ������ת��������ҳ����������
	SPo_DRect CmToLp(SPo_DRect tRc,bool bPrinting)
	{
		SPo_DPoint2D dptLT = CmToLp(tRc.left,tRc.top,bPrinting);
		SPo_DPoint2D dptRB = CmToLp(tRc.right,tRc.bottom,bPrinting);
		SPo_DRect rRc(dptLT.x,dptLT.y,dptRB.x,dptRB.y);
		return rRc;
	}
	//������ҳ����������ת����ʵ����������
	SPo_DRect LpToCm(SPo_DRect tRc,bool bPrinting)
	{
		SPo_DPoint2D dptLT = LpToCm(tRc.left,tRc.top,bPrinting);
		SPo_DPoint2D dptRB = LpToCm(tRc.right,tRc.bottom,bPrinting);
		SPo_DRect rRc(dptLT.x,dptLT.y,dptRB.x,dptRB.y);
		return rRc;
	}
	//��ʵ������ת����ԭʼ1��1ҳ����������
	SPo_DRect CmToUp(SPo_DRect tRc,bool bPrinting)
	{
		SPo_DPoint2D dptLT = CmToUp(tRc.left,tRc.top,bPrinting);
		SPo_DPoint2D dptRB = CmToUp(tRc.right,tRc.bottom,bPrinting);
		SPo_DRect rRc(dptLT.x,dptLT.y,dptRB.x,dptRB.y);
		return rRc;
	}
	//��ԭʼ1��1ҳ����������ת����ʵ����������
	SPo_DRect UpToCm(SPo_DRect tRc,bool bPrinting)
	{
		SPo_DPoint2D dptLT = UpToCm(tRc.left,tRc.top,bPrinting);
		SPo_DPoint2D dptRB = UpToCm(tRc.right,tRc.bottom,bPrinting);
		SPo_DRect rRc(dptLT.x,dptLT.y,dptRB.x,dptRB.y);
		return rRc;
	}
};


#endif /* SPO_PAGEVIEWPARAMAGENT_H_HEADER_INCLUDED_B054E5B6 */
