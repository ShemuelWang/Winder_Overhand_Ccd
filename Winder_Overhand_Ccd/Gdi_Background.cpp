
#include "stdafx.h"
#include "Gdi_Background.h"

CGdi_Background::CGdi_Background()
{
}

CGdi_Background::~CGdi_Background()
{
}

//���ñ���ͼƬ
void CGdi_Background::Set_Background(CString m_strBackground)
{

	HBITMAP hBitmap;

	//��ȡ�ⲿͼƬ
	hBitmap = (HBITMAP) ::LoadImage(
		NULL, 
		m_strBackground,
		IMAGE_BITMAP, 
		0, 
		0, 
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	

	if (hBitmap == NULL) 
	{
		AfxMessageBox ("���ر���ͼƬʧ��!");

		return;
	}
	
	CBitmap bmp;
	
	//HBITMAPת��CBitmap
	bmp.Attach(hBitmap);
	
	//��CBitmap���󴴽���ˢ
	m_Brush.CreatePatternBrush(&bmp);
	
	//�ͷ�CBitmap
	bmp.DeleteObject();
	
}

//��ȡ��ˢ
CBrush* CGdi_Background::Get_Brush()
{
	return &m_Brush;
}