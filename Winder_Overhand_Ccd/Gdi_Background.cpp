
#include "stdafx.h"
#include "Gdi_Background.h"

CGdi_Background::CGdi_Background()
{
}

CGdi_Background::~CGdi_Background()
{
}

//设置背景图片
void CGdi_Background::Set_Background(CString m_strBackground)
{

	HBITMAP hBitmap;

	//读取外部图片
	hBitmap = (HBITMAP) ::LoadImage(
		NULL, 
		m_strBackground,
		IMAGE_BITMAP, 
		0, 
		0, 
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	

	if (hBitmap == NULL) 
	{
		AfxMessageBox ("加载背景图片失败!");

		return;
	}
	
	CBitmap bmp;
	
	//HBITMAP转换CBitmap
	bmp.Attach(hBitmap);
	
	//用CBitmap对象创建画刷
	m_Brush.CreatePatternBrush(&bmp);
	
	//释放CBitmap
	bmp.DeleteObject();
	
}

//获取画刷
CBrush* CGdi_Background::Get_Brush()
{
	return &m_Brush;
}