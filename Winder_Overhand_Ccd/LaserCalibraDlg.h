#pragma once

#include "EntryDlg.h"
// CLaserCalibraDlg �Ի���

class CLaserCalibraDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLaserCalibraDlg)

public:
	CLaserCalibraDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLaserCalibraDlg();

		//����UI�ؼ����
	BOOL Set_UI_Type();

	//���þ�̬�ı��ؼ��ķ��
	BOOL Set_Gdi_Text_Type(CGdi_Text *v_gdiText,UINT v_uID);


	//���̺߳���-ͼ������߳�
	static UINT Image_Detection_Thread(LPVOID v_lpParameter);
	BOOL Image_Detection_Func();

	//��ȡ�����״̬
	int Read_Input(WORD v_wdBitNum);

	BOOL Input_Int_Data(CString v_strCameraName,CString v_strItem,int v_douMin,int v_douMax);

	//��ʾ����
	BOOL Show_Data();


	//���ֱ��
	BOOL Check_Line(IPL v_Frame, IPL v_Rgb,CString v_strCameraName,double *v_douPos);

	
	//����ͼƬ
	BOOL Save_Image(IPL v_Rgb, CString v_strCameraName);

public:

	//�������ָ��
	CCV_Hik_Camera *m_pOuterTopCam;

	//�������ָ��
	CCV_Hik_Camera *m_pInnerTopCam;

	//�������ָ��
	CCV_Hik_Camera *m_pOuterBottomCam;

	//�������ָ��
	CCV_Hik_Camera *m_pInnerBottomCam;

private:

		//��̬�ı��ؼ�����
	CGdi_Text *m_pgdiText;

	//�Զ�������
	CFont m_Font;

	//�Զ�������
	CFont m_Font2;

	//��ť����
	CButtonST *m_Btn;



	/****************ͼ��****************/

	//�����������֡,��ͨ��
	IPL m_OuterTopFrame;

	//�����������֡,��ͨ��
	IPL m_InnerTopFrame;

	//�����������֡,��ͨ��
	IPL m_OuterBottomFrame;

	//�����������֡,��ͨ��
	IPL m_InnerBottomFrame;


	//�����������ͼ��,��ͨ��
	IPL m_OuterTopPyr;

	//�����������ͼ��,��ͨ��
	IPL m_InnerTopPyr;

	//�����������ͼ��,��ͨ��
	IPL m_OuterBottomPyr;

	//�����������ͼ��,��ͨ��
	IPL m_InnerBottomPyr;



	//���������ʾ��ͼ��,��ͨ��
	IPL m_OuterTopRgb;

	//���������ʾ��ͼ��,��ͨ��
	IPL m_InnerTopRgb;

	//���������ʾ��ͼ��,��ͨ��
	IPL m_OuterBottomRgb;

	//���������ʾ��ͼ��,��ͨ��
	IPL m_InnerBottomRgb;


	//���Ƶ����Ͼ��ο�
	int m_intOuterTopLeft;

	int m_intOuterTopRight;

	int m_intOuterTopTop;

	int m_intOuterTopBottom;

	//���Ƶ����Ͼ��ο�
	int m_intInnerTopLeft;

	int m_intInnerTopRight;

	int m_intInnerTopTop;

	int m_intInnerTopBottom;

	
	//���Ƶ����¾��ο�
	int m_intOuterBottomLeft;

	int m_intOuterBottomRight;

	int m_intOuterBottomTop;

	int m_intOuterBottomBottom;

	
	//���Ƶ����¾��ο�
	int m_intInnerBottomLeft;

	int m_intInnerBottomRight;

	int m_intInnerBottomTop;

	int m_intInnerBottomBottom;

	BOOL m_bShowBaseLine;

	//�Ƿ����
	BOOL m_bMirrorMachine;

	//ͼ��ؼ�,�������
	CGdi_Image3 m_gdiOuterTop;

	//ͼ��ؼ�,�������
	CGdi_Image3 m_gdiInnerTop;

	//ͼ��ؼ�,�������
	CGdi_Image3 m_gdiOuterBottom;

	//ͼ��ؼ�,�������
	CGdi_Image3 m_gdiInnerBottom;


	//���̶߳���-ͼ������߳�
	CMuti_Thread m_DetectionThread;

	//���߳�ͬ������-ͼ����
	CUser_Signal m_sigDetection;


	//�������������źŵĵ�ƽ,�����ж�������,��ʼ��Ϊ_BIT_OFF
	int m_intPosTriggerSig;

	//��ǰ�����������յı��,Ĭ��Ϊ0
	int m_intPosTriggerIndex;


	//�������������źŵĵ�ƽ,�����ж�������,��ʼ��Ϊ_BIT_OFF
	int m_intNegTriggerSig;

	//��ǰ�����������յı��,Ĭ��Ϊ0
	int m_intNegTriggerIndex;

private:

	//����ͼƬ
	CGdi_Background m_gdiBackground;

	//��̬�ı��ؼ�����
	CGdi_Text m_gdiText;

	//���봰��ʱ��
	CString m_strCurrentTime;

	BOOL t_bRet ; 


// �Ի�������
	enum { IDD = IDD_LASER_CALIBRA_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
