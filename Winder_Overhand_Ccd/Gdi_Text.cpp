
#include "StdAfx.h"

#include "GDI_Text.h"

//消息映射
BEGIN_MESSAGE_MAP(CGdi_Text, CWnd)
   //{{AFX_MSG_MAP
   ON_WM_PAINT()//绘图函数
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

	//获取绘图设备DC
	CPaintDC dc(this); 
	
	//双缓冲绘图
	m_GDI.DB_Draw(dc.m_hDC);
		
}


BOOL CGdi_Text::SubclassDlgItem(UINT nID, CWnd* pParent)
{

	//调用子类,关联对象与控件
	CWnd::SubclassDlgItem(nID,pParent);

	//定义矩形框
	CRect rect;
	
	//获取窗口客户区的坐标
	this->GetClientRect(&rect);
	
	//设置控件尺寸
	m_GDI.Set_CTR_Size(rect.Width(),rect.Height());
	
	//参数为False代表不发送WN_ERASEBKGND消息
	Invalidate(FALSE);

	return TRUE;
}


void CGdi_Text::Set_BK_Color(Color m_Color)
{

	//设置背景颜色
	m_GDI.Set_BK_Color(m_Color);
	
	//参数为False代表不发送WN_ERASEBKGND消息
	Invalidate(FALSE);
}

//设置背景图片
void CGdi_Text::Set_BK_Image(CString m_strImage)
{

	//设置背景颜色
	m_GDI.Set_BK_Image(m_strImage);

	//参数为False代表不发送WN_ERASEBKGND消息
	Invalidate(FALSE);
}

void CGdi_Text::Set_Text_Color(Color m_Color)
{

	//设置字符串颜色
	m_GDI.Set_Text_Color(m_Color);

	//参数为False代表不发送WN_ERASEBKGND消息
	Invalidate(FALSE);
}


void CGdi_Text::Set_Text_Size(UINT m_Size)
{

	//设置字符串尺寸
	m_GDI.Set_Text_Size(m_Size);

	//参数为False代表不发送WN_ERASEBKGND消息
	Invalidate(FALSE);
}

void CGdi_Text::Set_Text_String(CString m_strData)
{
	//设置GDI显示的字符串
	m_GDI.Set_Text_String(m_strData);

	//参数为False代表不发送WN_ERASEBKGND消息
	Invalidate(FALSE);
}

void CGdi_Text::Set_Align(StringAlignment m_Align)
{

	//设置字符串对齐方式
	m_GDI.Set_Align(m_Align);
	
	//参数为False代表不发送WN_ERASEBKGND消息
	Invalidate(FALSE);
}

//设置边框颜色
void CGdi_Text::Set_Border_Color(Color m_Color)
{

	//设置边框颜色
	m_GDI.Set_Border_Color(m_Color);

	//参数为False代表不发送WN_ERASEBKGND消息
	Invalidate(FALSE);

}