
//ֻ����һ��
#pragma once

/**********************************************************************

  * �ļ�����: User_Func_Pro.h
  *
  * ժ	Ҫ  : �ṩһЩ���õ�ȫ�ֺ���,���Թ������ļ�ʹ��
  * 
  * ��	��  : ��ľ��
  * 
  * ��ǰ�汾: 2.0
  *
  * �������: 2018��8��24��
  
/**********************************************************************/

//��ѧ������
#include "math.h"

#ifndef PI

//����Բ����
#define PI 3.14159265358979

#endif

#ifndef USER_ZERO

#define USER_ZERO 0.000000001

#endif


/************************************************************
// ��������:AfxMessageBox2
// ��������:��дAfxMessageBox,�ܹ�ֱ����ʾ��������
// �������:����1ΪҪ��ʾ����������
// �������:���������
// ����ֵ  :�޷���ֵ
/************************************************************/
inline void AfxMessageBox2(int v_intData)
{
	CString t_strData;
	
	t_strData.Format("%d",v_intData);
	
	AfxMessageBox(t_strData);
}

/************************************************************
// ��������:AfxMessageBox2
// ��������:��дAfxMessageBox,�ܹ�ֱ����ʾ3λ��������
// �������:����1ΪҪ��ʾ�ĸ���������
// �������:���������
// ����ֵ  :�޷���ֵ
/************************************************************/
inline void AfxMessageBox2(double v_douData)
{
	CString t_strData;
	
	t_strData.Format("%.6f", v_douData);
	
	AfxMessageBox(t_strData);
}


/************************************************************
// ��������:OutputDebugString2
// ��������:��дOutputDebugString,�ܹ��ڵ��Ի��������������
// �������:����1ΪҪ��ʾ����������
// �������:���������
// ����ֵ  :�޷���ֵ
/************************************************************/
inline void OutputDebugString2(int v_intData)
{
	CString t_strData;
	
	t_strData.Format("%d", v_intData);
	
	OutputDebugString(t_strData);
}


/************************************************************
// ��������:OutputDebugString2
// ��������:��дOutputDebugString,�ܹ��ڵ��Ի������������������
// �������:����1ΪҪ��ʾ�ĸ���������
// �������:���������
// ����ֵ  :�޷���ֵ
/************************************************************/
inline void OutputDebugString2(double v_douData)
{
	CString t_strData;
	
	t_strData.Format("%.6f", v_douData);
	
	OutputDebugString(t_strData);
}

/************************************************************
// ��������:Do_Events
// ��������:������ǰ�̵߳Ŀ���Ȩ,������Ϣѭ��;��Ҫ����ȡ���Ѿ���ʼ���߳�,
            ��Do_Events ����֮ǰ,�����ٴα��������ֵĴ������,������������Ԥ�ϵĽ��
// �������:����1ΪҪ��ʾ�ĸ���������
// �������:���������
// ����ֵ  :�޷���ֵ
/************************************************************/
inline void Do_Events()
{
	//��Ϣ�ṹ
	MSG t_msg;

	//Ϊһ����Ϣ����߳���Ϣ���У���������Ϣ����ָ���Ľṹ;PM_REMOVE��ʾPeekMessage�������Ϣ�Ӷ����������
	while( ::PeekMessage(&t_msg,NULL,0,0,PM_REMOVE) )
	{
		//����Ӧ�˵�,��ݼ�,�Ӵ��ڰ�ť,��������ť
		if (t_msg.message == WM_COMMAND)
		{
			continue;
		}
		
		//����Ӧ���水��
		if (t_msg.message == WM_LBUTTONDOWN || t_msg.message == WM_LBUTTONUP || t_msg.message == WM_LBUTTONDBLCLK)
		{
			continue;
		}
		
		//����Ӧ���̰���
		if (t_msg.message == WM_KEYDOWN || t_msg.message == WM_KEYUP)
		{
			continue;
		}

		//���������Ϣת��Ϊ�ַ���Ϣ
		::TranslateMessage(&t_msg);

		//�ַ�һ����Ϣ�����ڳ���
		::DispatchMessage(&t_msg);
	}
}

/************************************************************
// ��������:Load_Path
// ��������:��ȡ��ǰ��������·��,�������������������������ƺͺ�׺,·�����֧��260���ַ�������D:\����\Debug\
// �������:���������
// �������:���������
// ����ֵ  :���س���ĵ�ǰ·��
/************************************************************/
inline CString Load_Path()
{
	CString t_strPath;

	//����·��
	char t_Full[_MAX_PATH];
	
	//��ȡ�������
	int t_intCount = sizeof(t_Full) / sizeof(char);

	//��ȡ�����·��,�����������ƺͺ�׺
	GetModuleFileName(NULL, t_Full, t_intCount);
	
	CString t_strData;

	t_strData.Format("%s",t_Full);

	t_strPath = t_strData;
	
	while (t_strData.Find("\\") >= 0)
	{
		int m_index = t_strData.Find("\\");

		t_strData = t_strData.Mid(m_index+1);
	}
	
	t_strPath = t_strPath.Left(t_strPath.GetLength() - t_strData.GetLength());
	
	return t_strPath;
}

/************************************************************
// ��������:Is_File_Exist
// ��������:�ж��ļ��Ƿ����.�ж��ļ�ʱ��Ҫ������׺��,Ҳ���������ж��ļ����Ƿ����,
            ���������ж��������Ƿ����.�ж��ļ���ʱ,����������Ҫ���ļ�����.����"D:\\����",��������ҵ�,"D:\\����\\",����Ҳ���
// �������:����1Ϊ������ļ�·��
// �������:���������
// ����ֵ  :�����ļ��Ƿ����,TRUE��ʾ�ļ�����;FALSE��ʾ�ļ�������
/************************************************************/
inline BOOL Is_File_Exist(CString v_strPath)
{
	//�ļ����Խṹ��
	WIN32_FIND_DATA  t_FindFileData; 
	
	//�����ļ��Ƿ����
	HANDLE t_hFind = FindFirstFile(v_strPath, &t_FindFileData); 
	
	//�ļ�������
	if (t_hFind == INVALID_HANDLE_VALUE) 
	{
		return FALSE; 
	}
	else 
	{ 
		//�ļ����ڣ��رվ��
		FindClose(t_hFind);
		
		return TRUE; 	
	} 
	
	return FALSE; 
}





/************************************************************
// ��������:Get_Time
// ��������:��ȡ��ǰʱ��
// �������:���������
// �������:���������
// ����ֵ  :���ص�ǰʱ����ַ���������������ʱ����
/************************************************************/
inline CString Get_Time()
{
	CTime t_CurrentTime;
	
	//��ȡ��ǰʱ��
	t_CurrentTime = CTime::GetCurrentTime();
	
	CString t_strData;
	
	t_strData = t_CurrentTime.Format("%Y_%m_%d_%H_%M_%S");
	
	return t_strData;
}

/************************************************************
// ��������:Get_Time
// ��������:��ȡ��ǰʱ��,���ص�������,��,��,ʱ,��,����
// �������:���������
// �������:����1Ϊ���,����2Ϊ�·�,����3Ϊ���ڣ�����4ΪСʱ������5Ϊ���ӣ�����6Ϊ�룬����7Ϊ���ڼ�,1��ʾ�����գ�2��ʾ����һ
// ����ֵ  :ִ�гɹ�����TRUE,ִ��ʧ�ܷ���FALSE
/************************************************************/
inline BOOL Get_Time(int& v_Year,int& v_Mon,int& v_Day,int& v_Hour,int& v_Min,int& v_Second,int& v_Week)
{
	CTime t_CurrentTime;

	//��ȡ��ǰʱ��
	t_CurrentTime = CTime::GetCurrentTime();

	//��ȡ���
	v_Year = t_CurrentTime.GetYear();

	//��ȡ�·�
	v_Mon = t_CurrentTime.GetMonth();

	//��ȡ����
	v_Day = t_CurrentTime.GetDay();

	//��ȡСʱ
	v_Hour = t_CurrentTime.GetHour();

	//��ȡ����
	v_Min = t_CurrentTime.GetMinute();

	//��ȡ��
	v_Second = t_CurrentTime.GetSecond();

	//��ȡ���ڼ�
	v_Week = t_CurrentTime.GetDayOfWeek();

	return TRUE;
}


/************************************************************
// ��������:Set_CTR_Pos
// ��������:���ÿؼ���λ�úʹ�С
// �������:��1������Ϊ�����ڶ���,һ��Ϊthisָ��
            ��2������ΪҪ���õĿؼ�ID��
			��3������Ϊ���Ͻǵ�ˮƽ����
			��4������Ϊ���ϽǵĴ�ֱ����
			��5������Ϊ���½ǵ�ˮƽ����
			��6������Ϊ���½ǵĴ�ֱ����
// �������:���������
// ����ֵ  :ִ�гɹ�����TRUE,ִ��ʧ�ܷ���FALSE
/************************************************************/
inline void Set_CTR_Pos(CWnd* v_CWnd,UINT v_intID, int v_intLeft,int v_intTop,int v_intRight,int v_intBottom)
{
	//��ȡ�ؼ�����ָ��
	CWnd *t_pWnd = v_CWnd->GetDlgItem(v_intID);

	if (t_pWnd == NULL)
	{
		return;
	}
	
	//��������
	CRect t_rect;
	
	t_rect.left = v_intLeft;
	
	t_rect.right = v_intRight;
	
	t_rect.top = v_intTop;
	
	t_rect.bottom = v_intBottom;
	
	t_pWnd->MoveWindow(t_rect);
}

/************************************************************
// ��������:Set_Control_Postion
// ��������:���ÿؼ���λ�úʹ�С
// �������:��1������Ϊ�����ڶ���,һ��Ϊthisָ��
            ��2������ΪҪ���õĿؼ�ID��
			��3������Ϊ���Ͻǵ�ˮƽ����
			��4������Ϊ���ϽǵĴ�ֱ����
			��5������Ϊ���½ǵ�ˮƽ����
			��6������Ϊ���½ǵĴ�ֱ����
// �������:���������
// ����ֵ  :ִ�гɹ�����TRUE,ִ��ʧ�ܷ���FALSE
/************************************************************/
inline void Set_Control_Postion(CWnd* v_CParentWnd,UINT v_intID, int v_intLeft,int v_intTop,int v_intRight,int v_intBottom)
{
	Set_CTR_Pos(v_CParentWnd,v_intID,v_intLeft,v_intTop,v_intRight,v_intBottom);
}

/************************************************************
// ��������:Hex_To_Ten
// ��������:ʮ��������ת��ʮ������
// �������:��1������Ϊ�����ʮ��������,�ַ�������
// �������:��2������Ϊ������޷���ʮ������
// ����ֵ  :ִ�гɹ�����TRUE,ִ��ʧ�ܷ���FALSE
/************************************************************/
inline BOOL Hex_To_Ten(CString v_strData,DWORD& v_dwData)
{
	v_strData.MakeUpper();

	v_strData.MakeReverse();

	int t_intLength = v_strData.GetLength();

	if (t_intLength <= 0 || t_intLength > 8)
	{
		AfxMessageBox("���ݳ�����Χ");
		return FALSE;
	}

	v_dwData = 0;

	char t_char;

	int t_intData = 1;

	int i;

	for (i = 0; i < t_intLength; i++, t_intData *= 16)
	{
		t_char = v_strData.GetAt(i);

		if(!( (t_char >= '0' && t_char <= '9') || (t_char >= 'A' && t_char <= 'F') ))
		{
			AfxMessageBox("���ݸ�ʽ����ȷ");
			
			return FALSE;

		}//if(!( (t_char >= '0' && t_char <= '9') || (t_char >= 'A' && t_char <= 'F') ))

		if (t_char >= '0' && t_char <= '9')
		{
			v_dwData += (t_char-'0') * t_intData;
		}
		else
		{
			v_dwData += (t_char-'A'+10) * t_intData;

		}//if (t_char >= '0' && t_char <= '9')
		
	}//for (i = 0; i < t_intLength; i++, t_intData *= 16)

	return TRUE;
}

/************************************************************
// ��������:Ten_To_Hex
// ��������:ʮ������ת��ʮ��������
// �������:��1������Ϊ������޷���ʮ������
// �������:��2������Ϊ�����ʮ��������,�ַ�������
// ����ֵ  :ִ�гɹ�����TRUE,ִ��ʧ�ܷ���FALSE
/************************************************************/
inline BOOL Ten_To_Hex(DWORD v_dwData,CString& v_strData)
{
	CString t_strData,t_strNum2,t_strNum16;

	t_strData.Empty();

	v_strData.Empty();

	t_strNum2.Empty();

	t_strNum16.Empty();

	//10������ת��2����
	while (v_dwData >= 2)
	{
		t_strNum2.Format("%d",v_dwData % 2);

		t_strData += t_strNum2;

		v_dwData = v_dwData/2;
	}

	t_strNum2.Format("%d",v_dwData);

	t_strData += t_strNum2;

	//2���Ƶ�˳���෴

	int m_intHex;

	CString m_strHex;

	int i;

	//����2���Ƶ�����λ��
	for (i = 0; i < v_strData.GetLength(); i++)
	{
		m_strHex = v_strData.GetAt(i);

		switch(i%4)
		{
		case 0:
			{
				m_intHex = atoi(m_strHex);

				break;
			}
		case 1:
			{
				m_intHex += atoi(m_strHex)*2;

				break;
			}
		case 2:
			{
				m_intHex += atoi(m_strHex)*4;

				break;
			}
		case 3:
			{
				m_intHex += atoi(m_strHex)*8;

				break;
			}
		}//switch(i%4)

		if (i%4 == 3 || i == v_strData.GetLength()-1 )
		{
			if(m_intHex<10)
			{
				t_strNum16.Format("%d",m_intHex);
			}

			if(m_intHex==10)
			{
				t_strNum16 = ":";
			}

			if(m_intHex==11)
			{
				t_strNum16 = ";";
			}

			if(m_intHex==12)
			{
				t_strNum16 = "<";
			}

			if(m_intHex==13)
			{
				t_strNum16 = "=";
			}

			if(m_intHex==14)
			{
				t_strNum16 = ">";
			}

			if(m_intHex==15)
			{
				t_strNum16 = "?";
			}

			v_strData += t_strNum16;

		}//if (i%4 == 3 || i == v_strData.GetLength()-1 )

	}//for (i = 0; i < v_strData.GetLength(); i++)

	while (v_strData.GetLength() < 8)
	{
		v_strData += "0";
	}

	//�ߵ�˳��
	v_strData.MakeReverse();

	return TRUE;
}


/************************************************************
// ��������:Square
// ��������:��ȡƽ����
// �������:��1������Ϊ����ĸ���������
// �������:���������
// ����ֵ  :���ظ��������ݵ�ƽ����
/************************************************************/
inline double Square(double v_douData)
{
	return v_douData * v_douData;
}

/************************************************************
// ��������:Sqrt
// ��������:���ؿ�������
// �������:��1������Ϊ����ĸ���������
// �������:���������
// ����ֵ  :���ظ��������ݵĿ�����,�ӽ�0�ĸ������Կ���,���Ϊ0
/************************************************************/
inline double Sqrt(double v_douData)
{
	//�ж��Ƿ���0���
	if (v_douData < 0)
	{
		//����������0����
		if (v_douData < -USER_ZERO)
		{
			AfxMessageBox("�������ܿ���");
		}

		return 0;
	}

	return sqrt(v_douData);
}

/************************************************************
// ��������:Rad_to_Angle
// ��������:����ת���Ƕ�
// �������:��1������Ϊ����Ļ���
// �������:���������
// ����ֵ  :����ת����ĽǶ�
/************************************************************/
inline double Rad_to_Angle(double v_douRad)
{
	return v_douRad * 180.0 / PI;
}

//
/************************************************************
// ��������:Angle_to_Rad
// ��������:�Ƕ�ת������
// �������:��1������Ϊ����ĽǶ�
// �������:���������
// ����ֵ  :����ת����Ļ���
/************************************************************/
inline double Angle_to_Rad(double v_douAngle)
{
	return v_douAngle * PI / 180.0;
}

class CINI  
{
public:

	//���캯��
	CINI();

	//��������
	virtual ~CINI();

	//���������ĵ���ĳ��ѡ���ֵ
	BOOL Set_Item(CString v_strItem,CString v_strData);

	//���������ĵ���ĳ��ѡ���ֵ
	BOOL Set_Item(CString v_strItem,double v_douData);

	//���������ĵ���ĳ��ѡ���ֵ
	BOOL Set_Item(CString v_strItem,int v_intData);

	//���������ĵ���ĳ��ѡ���ֵ,����ָ����ֵ
	BOOL Set_Item(CString v_strSection,CString v_strItem,CString v_strData);

	//���������ĵ���ĳ��ѡ���ֵ,����ָ����ֵ
	BOOL Set_Item(CString v_strSection,CString v_strItem,double v_douData);

	//���������ĵ���ĳ��ѡ���ֵ,����ָ����ֵ
	BOOL Set_Item(CString v_strSection,CString v_strItem,int v_intData);


	//��ȡ�����ĵ���ĳ��ѡ���ֵ
	CString  Get_Item(CString v_strItem);

	//��ȡ�����ĵ���ĳ��ѡ���ֵ
	int  Get_Item_Int(CString v_strItem);

	//��ȡ�����ĵ���ĳ��ѡ���ֵ
	double  Get_Item_Double(CString v_strItem);


	//��ȡ�����ĵ���ĳ��ѡ���ֵ,����ָ����ֵ
	CString  Get_Item(CString v_strSection,CString v_strItem);

	//��ȡ�����ĵ���ĳ��ѡ���ֵ
	int  Get_Item_Int(CString v_strSection,CString v_strItem);

	//��ȡ�����ĵ���ĳ��ѡ���ֵ
	double  Get_Item_Double(CString v_strSection,CString v_strItem);


	//����Ĭ�ϵ�·���Ͷ�ֵ
	BOOL Init_INI(CString v_strPath,CString v_strSection);

	//��ȡӦ�ó�������·��
	CString Load_Path();

private:

	//����Ini·��
	CString m_strPath;

	//Ĭ�϶�ȡ�Ķ�ֵ
	CString m_strSection;

	//��ȡ�����ݻ�����,���ó���500
	char m_DataBuf[501];

};

class CCount_Time  
{

public:

	//���캯��
	CCount_Time();

	//�����������麯��
	virtual ~CCount_Time();

	//���ƹ��캯��
	CCount_Time(const CCount_Time& v_other);

	//���ظ�ֵ����
	CCount_Time& operator=(const CCount_Time& v_other);

	//��ʼ��ʱ
	void Begin_Count();

	//������ʱ,���ؿ�ʼ��ʱ�������ʱ֮���ʱ�䳤��,��λΪ����
	double End_Count(BOOL v_bReCount = FALSE);

private:

	//64λ����
	LARGE_INTEGER m_litmp;

	//ʱ��Ƶ��
	double m_douFreq;

	//���ڻ�ȡ����ʱ�̵��ʱ���,��ʼ��ʱ
	LONGLONG m_QPart1;

	//���ڻ�ȡ����ʱ�̵��ʱ���,��ֹ��ʱ
	LONGLONG m_QPart2;

	//���صļ�ʱ���,��λ΢��
	double m_douMinus;

	//���صļ�ʱ���,��λ����
	double m_douTime;

};

//�������ļ�����
class CUser_File  
{
public:

	//���캯��
	CUser_File();

	//��������
	virtual ~CUser_File();

	//�ж��ļ����Ƿ����
	BOOL Is_Exist(CString v_strPath);

	//�����ļ���
	BOOL Copy_Folder(CString v_strPath,CString v_strNew);

	//ɾ���ļ���
	BOOL Delete_Folder(CString v_strPath);

	//�����ļ���
	BOOL Create_Folder(CString v_strPath);

	//�������ļ�
	BOOL Rename_File(CString v_strPath,CString v_strNew);

	//��ȡ�ļ�������������ļ�
	void Load_Foder_File(CString v_strFoder,CStringArray& v_Array);

};



//֧�ֵ��������
#define TXT_MAXROW 1000000

class CTXT_IO  
{

	//�ⲿ�ɵ��ú���
public:

	CTXT_IO();

	virtual ~CTXT_IO();

	//��TXT�ĵ���������ȡ
	BOOL Open_File(CString v_strPath);

	//ͨ���Ի���ѡ��TXT�ĵ�
	BOOL Open_Dialog_File();

	//����һ��ѡ���TXT�ĵ�
	BOOL Open_Last_File();

	//����ӹ��ĵ�
	BOOL Save_File(CString v_strPath);

	//������һ��ѡ���TXT�ĵ�
	BOOL Save_Last_File();

	//����ӹ��ĵ�����������Ƿ��޸Ĺ������û���޸Ĺ���������
	BOOL Save_File_Check(CString v_strPath);

	//�½�TXT�ĵ�������д��
	BOOL Create_File(CString v_strPath);

	//ɾ���ļ�
	BOOL Delete_File(CString v_strPath);

	//�������ļ�
	BOOL Rename_File(CString v_strPath,CString v_strNewName);


	//����һ��,��������iRow������������к���
	BOOL Insert_Row(int v_intRow);

	//�ڳ�ʽ���������һ��
	BOOL Add_Row();

	//ɾ��һ��
	BOOL Remove_Row(int v_intRow);

	//ɾ����������
	BOOL Remove_All();

	//��ȡ�ļ��ڴ��е���������
	BOOL Get_All_Data(CStringArray& v_CStringArray);

	//�����������ݵ��ļ��ڴ�
	BOOL Set_All_Data(CStringArray& v_CStringArray);

	//��ȡ��Ԫ������,0��0�е����ݲ���ȡ
	BOOL Get_Cell(int v_intRow,int v_intCol,CString& v_strData);

	//���õ�Ԫ������,0��0�е����ݲ�����
	BOOL Set_Cell(int v_intRow,int v_intCol,CString v_strData);


	//��ȡ������
	int Get_Row_Count();

	//����������
	BOOL Set_Col_Count(int v_intData);

	//�����Ƿ��޸Ĺ�
	BOOL Is_Data_Change();

	//��ȡ��ʽ����
	CString Get_Pro_Name();

protected:

	//��ȡTXT�ĵ�
	BOOL Read(CStdioFile& v_ReadFile);

	//д��TXT�ĵ�
	BOOL Write(CStdioFile& v_WriteFile,CStringArray& v_CStringArray);

	//����ĵ���������·��
	BOOL Check_Path(CString& v_strPath);

private:

	//��ʽ����
	CString	     m_ProName;

	//�ַ�������
	CStringArray m_CStringArray;

	//������
	int          m_intCountRow;

	//������,�����ж��ļ���ʽ�Ƿ���ȷ
	int          m_intCountCol;

	//�����Ƿ��޸Ĺ���ÿ�δ�������³�ʽ�����ͳ�ʽ���÷��޸����ݺ�Ϊ�棬
	BOOL         m_bDataChange;

};


class CMuti_Thread  
{
public:

	//���캯��
	CMuti_Thread();

	//��������
	virtual ~CMuti_Thread();

	//�����߳�
	BOOL Create(AFX_THREADPROC v_pThClass,LPVOID v_pParam,int nPriority = THREAD_PRIORITY_NORMAL);

	//�ر��߳�
	BOOL Destroy();

	//�߳��Ƿ�ִ����
	BOOL Is_Run();

protected:

	//������ǰ�̵߳Ŀ���Ȩ,������Ϣѭ��;��Ҫ����ȡ���Ѿ���ʼ���߳�
	void Do_Events();

protected:

	//�߳��Ƿ����б�־λ
	BOOL m_bRun;

	//�������߳�ָ�����
	CWinThread* m_pThread;
};



class CEvent1  
{
public:

	//���캯��
	CEvent1();

	//��������
	virtual ~CEvent1();

	//�����¼�
	BOOL Create(BOOL v_bJogReset=TRUE,BOOL v_bStatus=FALSE);

	//�ر��¼�,�ͷ��¼����;�ر��¼�ǰ,��Ҫ���˳��ȴ��¼����߳�
	BOOL Destroy();

	//����,ʹ�¼���ɷ�/����״̬
	BOOL Lock();

	//����,ʹ�¼����/����״̬
	BOOL Unlock();

	//�ȴ��¼�������,��Զ�ȴ�
	DWORD Wait();

	//�ȴ��¼�������,�ȴ�һ����ʱ��
	DWORD Wait(int v_intMiliSecond);

public:

	//�¼����
	HANDLE m_hEvent;

};

class CUser_Signal  
{
public:

	//���캯��
	CUser_Signal();

	//��������
	virtual ~CUser_Signal();

	//���߳�
public:

	//��ʼ���ź�,���캯���������
	BOOL Init(BOOL v_bValue);

	//����״̬
	BOOL Set_Event();

	//����״̬,���ҵȴ������߳��޸������ź�һ��;���̷߳�������,���ҵȴ�����
	BOOL Set_Event_Wait(int v_MiliSecond = 4000);

	//�Ǽ���״̬,���ҵȴ������߳��޸������ź�һ��;���̷߳�������,���ҵȴ�����
	BOOL Reset_Event_Wait(int v_MiliSecond= 4000);

	//�Ǽ���״̬
	BOOL Reset_Event();

	//����״̬,���ҵȴ������߳��޸������ź�һ��;���̷߳�������,���ҵȴ�����,���������߳���Ϣ
	BOOL Set_Event_Wait2(int v_MiliSecond = 4000);

	//�Ǽ���״̬,���ҵȴ������߳��޸������ź�һ��;���̷߳�������,���ҵȴ�����,���������߳���Ϣ
	BOOL Reset_Event_Wait2(int v_MiliSecond= 4000);

	//�ź��Ƿ�ı�,�����߳�ʹ��,��ǰͬ���ź�
	BOOL Is_Change();

	//�����߳�
public:

	//�Ƿ񼤻�״̬,��������,�����߳̽���ʱ�ж�
	BOOL Is_Set_Event();

	//�Ƿ�Ǽ���״̬,��������,�����߳̽���ʱ�ж�
	BOOL Is_Reset_Event();

	//ʹ�����ź�һ��,�����߳��������
	BOOL Make_Event_Same();

protected:

	//һ��ʱ����,���̵߳ȴ��ź�
	BOOL Wait_User_Sinagle(const volatile BOOL& v_bSinagle,BOOL v_bValue,int v_MiliSecond);

	//������ǰ�̵߳Ŀ���Ȩ,������Ϣѭ��;��Ҫ����ȡ���Ѿ���ʼ���߳�
	void Do_Events();

protected:

	//��ʼֵ,�ױ����
	volatile BOOL m_bPre;

	//��ǰֵ,�ױ����
	volatile BOOL m_bNow;
};



//��׼�ѿ�������ϵ,�����ض���,Χ��Բ����ת�Ƕ�A���λ��,�Ƕ���ˮƽ����Ϊ0��,��ʱ��Ϊ��
BOOL Rotate_Point3(double v_douCenterX,double v_douCenterY,double v_douAngle,double *v_douX,double *v_douY);

//��ȡD��ʣ��ռ�
DWORD Get_Disk_Space();

//��ȡ����ʣ��ռ�
DWORD Get_Disk_Space2(CString v_strPath);