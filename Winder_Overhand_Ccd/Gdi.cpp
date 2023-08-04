
#include "stdafx.h"

#include "GDI.h"

CGDI:: CGDI()
{
	//初始化CGDI
	GdiplusStartup(&m_gdiplusToken, &m_gdiplusStartupInput, NULL);

	//背景颜色默认黑色
	m_BkColor = Color(255,0,0,0);

	//字符串颜色默认为白色
	m_TextColor = Color(255,255,255,255);

	//图元颜色默认为白色
	m_MetaColor = Color(255,255,255,255);

	//控件宽度
	m_CtrWidth = 200;
	
	//控件高度
	m_CtrHeight = 150;

	//默认不显示边框
	m_bShowBorder = FALSE;

	//边框颜色
	m_BorderColor = Color(255,255,255,255);

	//边框宽度默认为2
	m_BorderWidth = 2;

	//字符串尺寸
	m_TextSize = 20;

	//默认缩放倍数
	m_douTimes = 1;

	//文本对齐方式默认为居中对齐
	m_TextAlign = StringAlignmentCenter;

	//背景图片指针
	m_pBkImage = NULL;
}

CGDI::  ~CGDI() 
{
	//如果之前有指向背景图片,先释放
	if (m_pBkImage != NULL)
	{
		delete m_pBkImage;
		m_pBkImage = NULL;
	}

	//释放CGDI
	GdiplusShutdown(m_gdiplusToken);

}

void CGDI:: Relate_CTR(CWnd *v_pWnd)
{
	//定义矩形框
	CRect t_Rect;
	
	//获取窗口客户区的坐标
	v_pWnd->GetClientRect(&t_Rect);
	
	//设置控件尺寸
	Set_CTR_Size(t_Rect.Width(),t_Rect.Height());
}

void CGDI::Set_CTR_Size(UINT v_intWidth,UINT v_intHeight)
{
	//设置控件尺寸
	if (v_intWidth == 0 || v_intHeight == 0)
	{
		AfxMessageBox("控件尺寸出错!");
		return;
	}
	
	//控件的宽度
	m_CtrWidth = v_intWidth;
	
	//控件的高度
	m_CtrHeight = v_intHeight;
}

void CGDI::Set_BK_Color(Color v_Color)
{
	m_BkColor = v_Color;
}

void CGDI::Set_BK_Image(CString v_strBkImage)
{
	//转换成COM数据格式
    BSTR t_BSTR = v_strBkImage.AllocSysString(); 
	
	//临时指针
	Gdiplus::Image *t_pBkImage;
	
	//指向原来的图片，用于释放
	t_pBkImage = m_pBkImage;
	
	//加载图片,堆分配，需要手动释放
	m_pBkImage = new Gdiplus::Bitmap(t_BSTR);
	
	//如果之前有指向背景图片,先释放
	if (t_pBkImage != NULL)
	{
		delete t_pBkImage;
		t_pBkImage = NULL;
	}
}

void CGDI::Set_Border_Color(Color v_Color)
{
	m_BorderColor = v_Color;

	m_bShowBorder = TRUE;
}

void CGDI::Set_Border_Width(UINT v_intWidth)
{
	m_BorderWidth = v_intWidth;

	//如果边框设置为0,则不显示边框
	if (v_intWidth == 0)
	{
		m_bShowBorder = FALSE;
	}
	else
	{
		m_bShowBorder = TRUE;
	}
}

void  CGDI::DB_Draw(HDC v_HDC)
{
	//控件尺寸不正确
	if(m_CtrWidth == 0 || m_CtrHeight == 0)
	{
		return;
	}

	//字符串尺寸不正确
	if (m_TextSize == 0)
	{
		return;
	}

	//创建虚拟画布
	Bitmap t_Bitmap(m_CtrWidth,m_CtrHeight);

	//虚拟画布导入虚拟设备中，后面的画图都在虚拟设备上
	Graphics t_VirtualGraphics(&t_Bitmap);

	//虚拟设备清除所有图形
	t_VirtualGraphics.Clear(m_BkColor);

	//绘制背景图片
	Draw_BK_Image(&t_VirtualGraphics);

	//绘制字符串
	Draw_Text(&t_VirtualGraphics);
	
	//绘示边框
	Draw_Border(&t_VirtualGraphics);

	//控件的设备上下文，包含显示器绘制属性信息的Windows 数据结构
	Graphics t_Graphics(v_HDC);
	
	//显示画布
	t_Graphics.DrawImage(&t_Bitmap,0,0);
}

void CGDI::Set_Text_Color(Color v_Color)
{
	//设置字符串颜色
	m_TextColor = v_Color;
}

void CGDI::Set_Text_Size(UINT v_intSize)
{
	//设置字符串尺寸
	m_TextSize = v_intSize;
}

void CGDI::Set_Text_String(CString v_strData)
{
	//设置字符串内容
	m_TextString = v_strData;
}

void CGDI::Set_Align(StringAlignment v_Align)
{
	//设置文本对齐方式
	m_TextAlign = v_Align;
}

//双缓冲绘图,显示图形
void CGDI::DB_Draw_CAD(HDC v_HDC)
{
	//控件尺寸不正确
	if(m_CtrWidth <= 0 || m_CtrHeight <= 0)
	{
		return;
	}
	
	//创建虚拟画布
	Bitmap t_Bitmap(m_CtrWidth,m_CtrHeight);

	//虚拟画布导入虚拟设备中，后面的画图都在虚拟设备上
	Graphics t_VirtualGraphics(&t_Bitmap);
	
	//虚拟设备清除所有图形
	t_VirtualGraphics.Clear(m_BkColor);
	
	//显示背景图片
	Draw_BK_Image(&t_VirtualGraphics);
	
	//显示边框
	Draw_Border(&t_VirtualGraphics);
	
	//显示画布,左上角坐标
	Graphics t_Graphics(v_HDC);
	
	t_Graphics.DrawImage(&t_Bitmap,0,0);
}

void CGDI::Set_Meta_Color(Color v_Color)
{
	m_MetaColor = v_Color;
}



void CGDI::Set_Times(double v_douTimes)
{
	if (v_douTimes <= 0.01)
	{
		AfxMessageBox("缩放倍数超出范围");
		return;
	}

	m_douTimes = v_douTimes;
}

void CGDI::Clear()
{
	
}

void  CGDI::Draw_Border(Graphics *v_bmpGraphics)
{
	//显示边框
	if (m_bShowBorder)
	{
		//设置控件尺寸
		if (m_CtrWidth <= 0 || m_CtrHeight <= 0)
		{
			return;
		}

		Draw_Rectange(v_bmpGraphics,0,0,m_CtrWidth,m_CtrHeight,m_BorderColor);
	}
}

void CGDI::Draw_BK_Image(Graphics *v_bmpGraphics)
{
	//设置控件尺寸
	if (m_CtrWidth <= 0 || m_CtrHeight <= 0)
	{
		return;
	}
	
	if (m_pBkImage == NULL)
	{
		return;
	}
	
	//创建高速缓存位图
	CachedBitmap t_CachedBitmap(m_pBkImage,v_bmpGraphics);

	//显示高速位图
	v_bmpGraphics->DrawCachedBitmap(&t_CachedBitmap,0,0);

	//虚拟设备绘制图片
  // bmpGraphics->DrawImage(m_pBkImage,0,0,m_pBkImage->GetWidth(),m_pBkImage->GetHeight());
}

void  CGDI::Draw_Text(Graphics *v_bmpGraphics)
{
	//字符串字体
	FontFamily t_FontFamily(L"微软雅黑");
	
	//字符串颜色
	SolidBrush t_SolidBrush(m_TextColor);
	
	//字符串格式
	Gdiplus::Font t_Font(&t_FontFamily,(float)m_TextSize,FontStyleRegular,UnitPixel);
	
	//转换成字符串数组
	BSTR t_BSTR = m_TextString.AllocSysString(); 
	
	//字符串左上角位置
	PointF t_PointF(0,(float)(m_CtrHeight/2.0-m_TextSize/1.6));
	
	//字符串对齐方式
	StringFormat t_StringFormat;                         
	
	//水平居中对齐
	t_StringFormat.SetAlignment(m_TextAlign); 
	
	//绘制字符串
	v_bmpGraphics->DrawString(t_BSTR,-1,&t_Font,t_PointF,&t_StringFormat,&t_SolidBrush);
	
	//不释放会造成内存泄露
	SysFreeString(t_BSTR);
}

void CGDI::Draw_Text(Graphics *v_bmpGraphics,double v_douX,double v_douY,CString v_strText,Color v_Color)
{
	//字符串字体
	FontFamily t_FontFamily(L"微软雅黑");

	//字符串颜色
	SolidBrush t_SolidBrush(v_Color);

	//字符串格式
	Gdiplus::Font t_Font(&t_FontFamily,(float)m_TextSize,FontStyleRegular,UnitPixel);

	//转换成字符串数组
	BSTR t_BSTR = v_strText.AllocSysString(); 

	//字符串左上角位置
	PointF t_PointF((float)v_douX,(float)v_douY);

	//字符串对齐方式
	StringFormat t_StringFormat;                         

	//水平居中对齐
	t_StringFormat.SetAlignment(m_TextAlign); 

	//绘制字符串
	v_bmpGraphics->DrawString(t_BSTR,-1,&t_Font,t_PointF,&t_StringFormat,&t_SolidBrush);

	//不释放会造成内存泄露
	SysFreeString(t_BSTR);
}

void CGDI::Draw_Line(Graphics *v_bmpGraphics,int v_intX1,int v_intY1,int v_intX2,int v_intY2)
{
	//定义画笔
	Pen t_Pen(m_MetaColor);

	//设置宽度
	t_Pen.SetWidth(float(m_BorderWidth));
	
	//画直线
	v_bmpGraphics->DrawLine(&t_Pen, v_intX1, v_intY1, v_intX2, v_intY2);
}

void CGDI::Draw_Line(Graphics *v_bmpGraphics,int v_intX1,int v_intY1,int v_intX2,int v_intY2,Color v_Color)
{
	//定义画笔
	Pen t_Pen(v_Color);
	
	//设置宽度
	t_Pen.SetWidth(float(m_BorderWidth));
	
	//画直线
	v_bmpGraphics->DrawLine(&t_Pen, v_intX1, v_intY1, v_intX2, v_intY2);
}

void CGDI:: Draw_Arc(Graphics *v_bmpGraphics,double v_douRaius,double v_douCenterX,double v_douCenterY,double v_douStartAngle,double v_douEndAngle)
{
	//定义画笔
	Pen t_Pen(m_MetaColor);
	
	//设置宽度
	t_Pen.SetWidth(float(m_BorderWidth));
	
	//画圆弧
	Rect t_Rect((int)(v_douCenterX - v_douRaius),(int)(v_douCenterY - v_douRaius),(int)(v_douRaius * 2),(int)(v_douRaius * 2));
	
	double Angle_Dis = v_douEndAngle - v_douStartAngle;
	
	if(Angle_Dis < 0) 
	{
		Angle_Dis += 360;
	}
	
	v_bmpGraphics->DrawArc(&t_Pen,t_Rect,(float)(360 - v_douEndAngle),(float)(Angle_Dis));
}

void CGDI:: Draw_Arc(Graphics *v_bmpGraphics,double v_douRaius,double v_douCenterX,double v_douCenterY,double v_douStartAngle,double v_douEndAngle,Color v_Color)
{
	//定义画笔
	Pen t_Pen(v_Color);

	//设置宽度
	t_Pen.SetWidth(float(m_BorderWidth));

	//画圆弧
	Rect t_Rect((int)(v_douCenterX - v_douRaius),(int)(v_douCenterY - v_douRaius),(int)(v_douRaius * 2),(int)(v_douRaius * 2));

	double Angle_Dis = v_douEndAngle - v_douStartAngle;

	if(Angle_Dis < 0) 
	{
		Angle_Dis += 360;
	}

	v_bmpGraphics->DrawArc(&t_Pen,t_Rect,(float)(360 - v_douEndAngle),(float)(Angle_Dis));
}

void CGDI::Draw_Rectange(Graphics *v_bmpGraphics,int v_intX1,int v_intY1,int v_intWidth,int v_intHeight,Color v_Color)
{
	//定义画笔
	Pen t_Pen(v_Color);
	
	//设置宽度
	t_Pen.SetWidth(float(m_BorderWidth));
	
	//画矩形
	v_bmpGraphics->DrawRectangle(&t_Pen, 
		(int)(v_intX1 + m_BorderWidth / 2),
		(int)(v_intY1 + m_BorderWidth / 2),
		(int)(v_intWidth - m_BorderWidth),
		(int)(v_intHeight - m_BorderWidth));
}