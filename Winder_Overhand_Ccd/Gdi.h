
//头文件只编译一次
#pragma once

/**********************************************************************

  * 文件名称: GDI.h
  *
  * 摘	要: GDI+绘图类
  * 
  * 当前版本: 2.0
  *
  * 作	者: 林木松
  *
  * 完成日期: 2015年3月25日
  
/**********************************************************************/

#ifndef ULONG_PTR

#define ULONG_PTR ULONG 

//添加GDI头文件
#include <gdiplus.h>

//使用GDIplus命名空间
using namespace Gdiplus;

//GDI+链接库
#pragma comment(lib, "gdiplus.lib")

#endif


//图形设备接口
class CGDI  
{

//外部可调用函数
public:

	//构造函数
	CGDI();

	//虚函数，析构函数
	~CGDI();

	//关联控件
	void Relate_CTR(CWnd *v_pWnd);

	//设置控件尺寸
	void Set_CTR_Size(UINT v_intWidth,UINT v_intHeight);

	//设置背景色
	void Set_BK_Color(Color v_Color);

	//设置背景图片
	void Set_BK_Image(CString v_strBkImage);

	//设置边框颜色
	void Set_Border_Color(Color v_Color);

	//设置边框宽度
	void Set_Border_Width(UINT v_intWidth);


public:
	
	//双缓冲,绘制字符串
	void DB_Draw(HDC v_HDC);

	//设置字符串颜色
	void Set_Text_Color(Color v_Color);
	
	//设置字符串尺寸
	void Set_Text_Size(UINT v_intSize);
	
	//设置字符串内容
	void Set_Text_String(CString v_strData);

	//设置文本的对齐方式
	void Set_Align(StringAlignment v_Align);

public:

	//双缓冲绘图图形
	void DB_Draw_CAD(HDC v_HDC);

	//设置图元颜色
	void Set_Meta_Color(Color v_Color);

	//设置缩放倍数
	void Set_Times(double v_douTimes);

	//清空图像
	void Clear();

protected:

	//绘制边框
	void Draw_Border(Graphics *v_bmpGraphics);

	//绘示背景图片
	void Draw_BK_Image(Graphics *v_bmpGraphics);

	//绘制字符串
	void Draw_Text(Graphics *v_bmpGraphics);

	//绘制直线
	void Draw_Text(Graphics *v_bmpGraphics,double v_douX,double v_douY,CString v_strText,Color v_Color);

	//绘制直线
	void Draw_Line(Graphics *v_bmpGraphics,int v_intX1,int v_intY1,int v_intX2,int v_intY2);
	
	//绘制直线,可以自定义颜色
	void Draw_Line(Graphics *v_bmpGraphics,int v_intX1,int v_intY1,int v_intX2,int v_intY2,Color v_Color);

	//绘制圆弧
	void Draw_Arc(Graphics *v_bmpGraphics,double v_douRaius,double v_douCenterX,double v_douCenterY,double v_douStartAngle,double v_douEndAngle);

	//绘制圆弧
	void Draw_Arc(Graphics *v_bmpGraphics,double v_douRaius,double v_douCenterX,double v_douCenterY,double v_douStartAngle,double v_douEndAngle,Color v_Color);

	//绘制矩形
	void Draw_Rectange(Graphics *v_bmpGraphics,int v_intX1,int v_intY1,int v_intWidth,int v_intHeight,Color v_Color);

protected:

	//GDI结构
	GdiplusStartupInput m_gdiplusStartupInput;

	//无符号长整型
    ULONG_PTR m_gdiplusToken;

	//控件的宽度
	UINT m_CtrWidth;

	//控件的高度
	UINT m_CtrHeight;

	//背景颜色
	Color m_BkColor;

	//背景图片
	Gdiplus::Bitmap* m_pBkImage;

	//边框颜色
	Color m_BorderColor;

	//边框宽度
	UINT m_BorderWidth;

	//是否显示边框
	BOOL m_bShowBorder;


	//字符串
protected:
	
	//字符串内容
	CString m_TextString;
	
	//字符串颜色
	Color m_TextColor;
	
	//字符串尺寸
	UINT m_TextSize;
	
	//文本的对齐方式
	StringAlignment m_TextAlign;
	

	//图形链表
protected:

	//图形颜色
	Color m_MetaColor;

	//缩放倍数
	double m_douTimes;
};
