#pragma once

#include "EntryDlg.h"
// CLaserCalibraDlg 对话框

class CLaserCalibraDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLaserCalibraDlg)

public:
	CLaserCalibraDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLaserCalibraDlg();

		//设置UI控件风格
	BOOL Set_UI_Type();

	//设置静态文本控件的风格
	BOOL Set_Gdi_Text_Type(CGdi_Text *v_gdiText,UINT v_uID);


	//多线程函数-图像检测的线程
	static UINT Image_Detection_Thread(LPVOID v_lpParameter);
	BOOL Image_Detection_Func();

	//获取输入点状态
	int Read_Input(WORD v_wdBitNum);

	BOOL Input_Int_Data(CString v_strCameraName,CString v_strItem,int v_douMin,int v_douMax);

	//显示数据
	BOOL Show_Data();


	//检测直线
	BOOL Check_Line(IPL v_Frame, IPL v_Rgb,CString v_strCameraName,double *v_douPos);

	
	//保存图片
	BOOL Save_Image(IPL v_Rgb, CString v_strCameraName);

public:

	//外上相机指针
	CCV_Hik_Camera *m_pOuterTopCam;

	//内上相机指针
	CCV_Hik_Camera *m_pInnerTopCam;

	//外下相机指针
	CCV_Hik_Camera *m_pOuterBottomCam;

	//内下相机指针
	CCV_Hik_Camera *m_pInnerBottomCam;

private:

		//静态文本控件对象
	CGdi_Text *m_pgdiText;

	//自定义字体
	CFont m_Font;

	//自定义字体
	CFont m_Font2;

	//按钮对象
	CButtonST *m_Btn;



	/****************图像****************/

	//外上相机数据帧,单通道
	IPL m_OuterTopFrame;

	//内上相机数据帧,单通道
	IPL m_InnerTopFrame;

	//外下相机数据帧,单通道
	IPL m_OuterBottomFrame;

	//内下相机数据帧,单通道
	IPL m_InnerBottomFrame;


	//外上相机缩放图像,单通道
	IPL m_OuterTopPyr;

	//内上相机缩放图像,单通道
	IPL m_InnerTopPyr;

	//外下相机缩放图像,单通道
	IPL m_OuterBottomPyr;

	//内下相机缩放图像,单通道
	IPL m_InnerBottomPyr;



	//外上相机显示的图像,三通道
	IPL m_OuterTopRgb;

	//内上相机显示的图像,三通道
	IPL m_InnerTopRgb;

	//外下相机显示的图像,三通道
	IPL m_OuterBottomRgb;

	//内下相机显示的图像,三通道
	IPL m_InnerBottomRgb;


	//绘制的外上矩形框
	int m_intOuterTopLeft;

	int m_intOuterTopRight;

	int m_intOuterTopTop;

	int m_intOuterTopBottom;

	//绘制的内上矩形框
	int m_intInnerTopLeft;

	int m_intInnerTopRight;

	int m_intInnerTopTop;

	int m_intInnerTopBottom;

	
	//绘制的外下矩形框
	int m_intOuterBottomLeft;

	int m_intOuterBottomRight;

	int m_intOuterBottomTop;

	int m_intOuterBottomBottom;

	
	//绘制的内下矩形框
	int m_intInnerBottomLeft;

	int m_intInnerBottomRight;

	int m_intInnerBottomTop;

	int m_intInnerBottomBottom;

	BOOL m_bShowBaseLine;

	//是否镜像机
	BOOL m_bMirrorMachine;

	//图像控件,外上相机
	CGdi_Image3 m_gdiOuterTop;

	//图像控件,内上相机
	CGdi_Image3 m_gdiInnerTop;

	//图像控件,外下相机
	CGdi_Image3 m_gdiOuterBottom;

	//图像控件,内下相机
	CGdi_Image3 m_gdiInnerBottom;


	//多线程对象-图像检测的线程
	CMuti_Thread m_DetectionThread;

	//多线程同步对象-图像检测
	CUser_Signal m_sigDetection;


	//阳极触发拍照信号的电平,用于判定上升沿,初始化为_BIT_OFF
	int m_intPosTriggerSig;

	//当前阳极触发拍照的编号,默认为0
	int m_intPosTriggerIndex;


	//阴极触发拍照信号的电平,用于判定上升沿,初始化为_BIT_OFF
	int m_intNegTriggerSig;

	//当前阴极触发拍照的编号,默认为0
	int m_intNegTriggerIndex;

private:

	//背景图片
	CGdi_Background m_gdiBackground;

	//静态文本控件对象
	CGdi_Text m_gdiText;

	//进入窗口时间
	CString m_strCurrentTime;

	BOOL t_bRet ; 


// 对话框数据
	enum { IDD = IDD_LASER_CALIBRA_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDestroy();
	afx_msg void OnStnClickedImage1(NMHDR* pNMHDR,LRESULT* pResult);
	afx_msg void OnStnClickedImage2(NMHDR* pNMHDR,LRESULT* pResult);
	afx_msg void OnStnClickedImage3(NMHDR* pNMHDR,LRESULT* pResult);
	afx_msg void OnStnClickedImage4(NMHDR* pNMHDR,LRESULT* pResult);
	

	afx_msg void OnBnClickedRun();
	afx_msg void OnBnClickedStop();
	afx_msg void OnBnClickedSetRoi1();
	afx_msg void OnBnClickedSetRoi2();
	afx_msg void OnBnClickedSetRoi3();
	afx_msg void OnBnClickedSetRoi4();


	afx_msg void OnStnClickedRoi9();
	afx_msg void OnStnClickedRoi1();
	afx_msg void OnStnClickedRoi5();
	afx_msg void OnStnClickedRoi2();
	afx_msg void OnStnClickedRoi3();
	afx_msg void OnStnClickedRoi4();
	afx_msg void OnStnClickedRoi6();
	afx_msg void OnStnClickedRoi7();
	afx_msg void OnStnClickedRoi8();
	afx_msg void OnStnClickedRoi10();
	afx_msg void OnStnClickedRoi11();
	afx_msg void OnStnClickedRoi12();
	afx_msg void OnStnClickedRoi13();
	afx_msg void OnStnClickedRoi14();
	afx_msg void OnStnClickedRoi15();
	afx_msg void OnStnClickedRoi16();
	afx_msg void OnBnClickedCheck();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedCheck4();
	//afx_msg void OnBnClickedLoad1();

	//afx_msg void OnBnClickedSave();

	//afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//afx_msg void OnMouseLeave();
};
