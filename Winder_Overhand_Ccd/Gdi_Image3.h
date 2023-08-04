#pragma once

/**********************************************************************

  * 文件名称: Gdi_Image3.h
  *
  * 摘	要: 更新在接近图像边缘时确定ROI
  * 
  * 当前版本: 3.0
  *
  * 作	者: 黄燚
  *
  * 完成日期: 2015年12月25日
  
/**********************************************************************/

#include "CV_Func_Pro.h"

#include "Gdi_Image2.h"

//自定义消息
/*#define WM_CLICK_CTRL WM_USER + 1

//自定义消息
#define WM_MOUSE_MOVE2 WM_USER + 2

//自定义USER_NMHDR
struct  USER_NMHDR
{
	NMHDR  nmhdr;

	UINT  top;
	
	UINT  bottom;

	UINT left;

	UINT right;
};
*/

class CGdi_Image3:public CWnd
{
public:

	CGdi_Image3(void);

	~CGdi_Image3(void);

	//关联对象与控件
	virtual BOOL SubclassDlgItem(UINT nID, CWnd* pParent);

	//显示OpenCV图像
	void Show(IPL v_Image);

	//清除坐标
	BOOL Clear();

protected:

	//显示OpenCV图像,不拉伸
	void Show_Direct(IPL v_Image);

	//缩放图像
	BOOL Zoom(const IPL v_Image, IPL *v_pTrans,int v_intWidth,int v_intHeight);

protected:

	//兼容DC,用于双缓冲
	CDC m_dcCompatible;

	//位图
	CBitmap m_Bitmap;

	//图像缓冲区
	BYTE *m_pImageBuf;

	//OpenCV显示的图像
	IPL m_Image;

	//消息结构体
	USER_NMHDR m_NMHDR;

	//消息结构体
	USER_NMHDR m_NMHDR2;

	//是否按下鼠标左键
	BOOL m_bDown;

	//是否按下鼠标左键
	BOOL m_bMoveDown;

	//移动的起始点X
	int m_intMoveHomeX;

	//移动的起始点Y
	int m_intMoveHomeY;


	//是否按下鼠标左键
	BOOL m_bAdjustDown;

protected:
	//{{AFX_MSG
	afx_msg void OnPaint();//绘图函数
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	//}}AFX_MSG

	//向类中添加消息映射必要的结构体和函数声明
	DECLARE_MESSAGE_MAP()
};

