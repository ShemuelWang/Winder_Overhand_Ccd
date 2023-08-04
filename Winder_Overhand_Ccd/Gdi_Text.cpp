
#include "StdAfx.h"

#include "GDI_Text.h"

//��Ϣӳ��
BEGIN_MESSAGE_MAP(CGdi_Text, CWnd)
   //{{AFX_MSG_MAP
   ON_WM_PAINT()//��ͼ����
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()


CGdi_Text::CGdi_Text()
{

}


CGdi_Text::~CGdi_Text()
{
	
}


void CGdi_Text::OnPaint() 
{

	//��ȡ��ͼ�豸DC
	CPaintDC dc(this); 
	
	//˫�����ͼ
	m_GDI.DB_Draw(dc.m_hDC);
		
}


BOOL CGdi_Text::SubclassDlgItem(UINT nID, CWnd* pParent)
{

	//��������,����������ؼ�
	CWnd::SubclassDlgItem(nID,pParent);

	//������ο�
	CRect rect;
	
	//��ȡ���ڿͻ���������
	this->GetClientRect(&rect);
	
	//���ÿؼ��ߴ�
	m_GDI.Set_CTR_Size(rect.Width(),rect.Height());
	
	//����ΪFalse��������WN_ERASEBKGND��Ϣ
	Invalidate(FALSE);

	return TRUE;
}


void CGdi_Text::Set_BK_Color(Color m_Color)
{

	//���ñ�����ɫ
	m_GDI.Set_BK_Color(m_Color);
	
	//����ΪFalse��������WN_ERASEBKGND��Ϣ
	Invalidate(FALSE);
}

//���ñ���ͼƬ
void CGdi_Text::Set_BK_Image(CString m_strImage)
{

	//���ñ�����ɫ
	m_GDI.Set_BK_Image(m_strImage);

	//����ΪFalse��������WN_ERASEBKGND��Ϣ
	Invalidate(FALSE);
}

void CGdi_Text::Set_Text_Color(Color m_Color)
{

	//�����ַ�����ɫ
	m_GDI.Set_Text_Color(m_Color);

	//����ΪFalse��������WN_ERASEBKGND��Ϣ
	Invalidate(FALSE);
}


void CGdi_Text::Set_Text_Size(UINT m_Size)
{

	//�����ַ����ߴ�
	m_GDI.Set_Text_Size(m_Size);

	//����ΪFalse��������WN_ERASEBKGND��Ϣ
	Invalidate(FALSE);
}

void CGdi_Text::Set_Text_String(CString m_strData)
{
	//����GDI��ʾ���ַ���
	m_GDI.Set_Text_String(m_strData);

	//����ΪFalse��������WN_ERASEBKGND��Ϣ
	Invalidate(FALSE);
}

void CGdi_Text::Set_Align(StringAlignment m_Align)
{

	//�����ַ������뷽ʽ
	m_GDI.Set_Align(m_Align);
	
	//����ΪFalse��������WN_ERASEBKGND��Ϣ
	Invalidate(FALSE);
}

//���ñ߿���ɫ
void CGdi_Text::Set_Border_Color(Color m_Color)
{

	//���ñ߿���ɫ
	m_GDI.Set_Border_Color(m_Color);

	//����ΪFalse��������WN_ERASEBKGND��Ϣ
	Invalidate(FALSE);

}