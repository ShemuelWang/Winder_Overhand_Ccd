#pragma once


// CEntryDlg �Ի���

class CEntryDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEntryDlg)

public:
	CEntryDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CEntryDlg();

	//�趨 �������ķ�Χ
	BOOL Set_Double_Range(double v_douMin,double v_douMax,double *v_pdouInput);

	//�趨 ���͵ķ�Χ
	BOOL Set_Int_Range(int v_intMin,int v_intMax,int *v_pintInput);

private:

	//����ͼƬ
	CGdi_Background m_gdiBackground;

	//�Զ�������
	CFont m_Font;


	//��������,1=����,2=������
	int m_intType;

	//���͵���Сֵ
	int m_intMin;

	//���͵����ֵ
	int m_intMax;

	//�����������ݵ�ָ��
	int *m_pintInput;


	//�������Сֵ
	double m_douMin;

	//��������ֵ
	double m_douMax;

	//���ظ������ݵ�ָ��
	double *m_pdouInput;

// �Ի�������
	enum { IDD = IDD_ENTRY_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnStnClickedItem1();
	afx_msg void OnBnClickedOk();
};
