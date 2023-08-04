
//只编译一次
#pragma once

/**********************************************************************

  * 文件名称: User_Func_Pro.h
  *
  * 摘	要  : 提供一些常用的全局函数,可以供所有文件使用
  * 
  * 作	者  : 林木松
  * 
  * 当前版本: 2.0
  *
  * 完成日期: 2018年8月24日
  
/**********************************************************************/

//数学函数库
#include "math.h"

#ifndef PI

//定义圆周率
#define PI 3.14159265358979

#endif

#ifndef USER_ZERO

#define USER_ZERO 0.000000001

#endif


/************************************************************
// 函数名称:AfxMessageBox2
// 功能描述:改写AfxMessageBox,能够直接显示整型数据
// 输入参数:参数1为要显示的整型数据
// 输出参数:无输出参数
// 返回值  :无返回值
/************************************************************/
inline void AfxMessageBox2(int v_intData)
{
	CString t_strData;
	
	t_strData.Format("%d",v_intData);
	
	AfxMessageBox(t_strData);
}

/************************************************************
// 函数名称:AfxMessageBox2
// 功能描述:改写AfxMessageBox,能够直接显示3位浮点数据
// 输入参数:参数1为要显示的浮点型数据
// 输出参数:无输出参数
// 返回值  :无返回值
/************************************************************/
inline void AfxMessageBox2(double v_douData)
{
	CString t_strData;
	
	t_strData.Format("%.6f", v_douData);
	
	AfxMessageBox(t_strData);
}


/************************************************************
// 函数名称:OutputDebugString2
// 功能描述:改写OutputDebugString,能够在调试画面输出整型数据
// 输入参数:参数1为要显示的整型数据
// 输出参数:无输出参数
// 返回值  :无返回值
/************************************************************/
inline void OutputDebugString2(int v_intData)
{
	CString t_strData;
	
	t_strData.Format("%d", v_intData);
	
	OutputDebugString(t_strData);
}


/************************************************************
// 函数名称:OutputDebugString2
// 功能描述:改写OutputDebugString,能够在调试画面输出浮点型型数据
// 输入参数:参数1为要显示的浮点型数据
// 输出参数:无输出参数
// 返回值  :无返回值
/************************************************************/
inline void OutputDebugString2(double v_douData)
{
	CString t_strData;
	
	t_strData.Format("%.6f", v_douData);
	
	OutputDebugString(t_strData);
}

/************************************************************
// 函数名称:Do_Events
// 功能描述:交出当前线程的控制权,进入消息循环;主要用于取消已经开始的线程,
            在Do_Events 返回之前,不能再次被其他部分的代码调用,否则会产生不可预料的结果
// 输入参数:参数1为要显示的浮点型数据
// 输出参数:无输出参数
// 返回值  :无返回值
/************************************************************/
inline void Do_Events()
{
	//消息结构
	MSG t_msg;

	//为一个消息检查线程消息队列，并将该消息放于指定的结构;PM_REMOVE表示PeekMessage处理后，消息从队列里清除掉
	while( ::PeekMessage(&t_msg,NULL,0,0,PM_REMOVE) )
	{
		//不响应菜单,快捷键,子窗口按钮,工具栏按钮
		if (t_msg.message == WM_COMMAND)
		{
			continue;
		}
		
		//不响应界面按键
		if (t_msg.message == WM_LBUTTONDOWN || t_msg.message == WM_LBUTTONUP || t_msg.message == WM_LBUTTONDBLCLK)
		{
			continue;
		}
		
		//不响应键盘按键
		if (t_msg.message == WM_KEYDOWN || t_msg.message == WM_KEYUP)
		{
			continue;
		}

		//将虚拟键消息转换为字符消息
		::TranslateMessage(&t_msg);

		//分发一个消息给窗口程序
		::DispatchMessage(&t_msg);
	}
}

/************************************************************
// 函数名称:Load_Path
// 功能描述:获取当前程序所在路径,包括驱动器，不包括程序名称和后缀,路径最高支持260个字符，例如D:\程序\Debug\
// 输入参数:无输入参数
// 输出参数:无输出参数
// 返回值  :返回程序的当前路径
/************************************************************/
inline CString Load_Path()
{
	CString t_strPath;

	//程序路径
	char t_Full[_MAX_PATH];
	
	//获取数组个数
	int t_intCount = sizeof(t_Full) / sizeof(char);

	//获取程序的路径,包括程序名称和后缀
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
// 函数名称:Is_File_Exist
// 功能描述:判断文件是否存在.判断文件时，要包括后缀名,也可以用于判断文件夹是否存在,
            不能用于判断驱动器是否存在.判断文件夹时,最后的名称需要是文件夹名.例如"D:\\测试",这个可以找到,"D:\\测试\\",这个找不到
// 输入参数:参数1为输入的文件路径
// 输出参数:无输出参数
// 返回值  :返回文件是否存在,TRUE表示文件存在;FALSE表示文件不存在
/************************************************************/
inline BOOL Is_File_Exist(CString v_strPath)
{
	//文件属性结构体
	WIN32_FIND_DATA  t_FindFileData; 
	
	//查找文件是否存在
	HANDLE t_hFind = FindFirstFile(v_strPath, &t_FindFileData); 
	
	//文件不存在
	if (t_hFind == INVALID_HANDLE_VALUE) 
	{
		return FALSE; 
	}
	else 
	{ 
		//文件存在，关闭句柄
		FindClose(t_hFind);
		
		return TRUE; 	
	} 
	
	return FALSE; 
}





/************************************************************
// 函数名称:Get_Time
// 功能描述:获取当前时间
// 输入参数:无输入参数
// 输出参数:无输出参数
// 返回值  :返回当前时间的字符串，包括年月日时分秒
/************************************************************/
inline CString Get_Time()
{
	CTime t_CurrentTime;
	
	//获取当前时间
	t_CurrentTime = CTime::GetCurrentTime();
	
	CString t_strData;
	
	t_strData = t_CurrentTime.Format("%Y_%m_%d_%H_%M_%S");
	
	return t_strData;
}

/************************************************************
// 函数名称:Get_Time
// 功能描述:获取当前时间,返回单个的年,月,日,时,分,星期
// 输入参数:无输入参数
// 输出参数:参数1为年份,参数2为月份,参数3为日期，参数4为小时，参数5为分钟，参数6为秒，参数7为星期几,1表示是周日，2表示是周一
// 返回值  :执行成功返回TRUE,执行失败返回FALSE
/************************************************************/
inline BOOL Get_Time(int& v_Year,int& v_Mon,int& v_Day,int& v_Hour,int& v_Min,int& v_Second,int& v_Week)
{
	CTime t_CurrentTime;

	//获取当前时间
	t_CurrentTime = CTime::GetCurrentTime();

	//获取年份
	v_Year = t_CurrentTime.GetYear();

	//获取月份
	v_Mon = t_CurrentTime.GetMonth();

	//获取日期
	v_Day = t_CurrentTime.GetDay();

	//获取小时
	v_Hour = t_CurrentTime.GetHour();

	//获取分钟
	v_Min = t_CurrentTime.GetMinute();

	//获取秒
	v_Second = t_CurrentTime.GetSecond();

	//获取星期几
	v_Week = t_CurrentTime.GetDayOfWeek();

	return TRUE;
}


/************************************************************
// 函数名称:Set_CTR_Pos
// 功能描述:设置控件的位置和大小
// 输入参数:第1个参数为父窗口对象,一般为this指针
            第2个参数为要设置的控件ID号
			第3个参数为左上角的水平坐标
			第4个参数为左上角的垂直坐标
			第5个参数为右下角的水平坐标
			第6个参数为右下角的垂直坐标
// 输出参数:无输出参数
// 返回值  :执行成功返回TRUE,执行失败返回FALSE
/************************************************************/
inline void Set_CTR_Pos(CWnd* v_CWnd,UINT v_intID, int v_intLeft,int v_intTop,int v_intRight,int v_intBottom)
{
	//获取控件对象指针
	CWnd *t_pWnd = v_CWnd->GetDlgItem(v_intID);

	if (t_pWnd == NULL)
	{
		return;
	}
	
	//定义区域
	CRect t_rect;
	
	t_rect.left = v_intLeft;
	
	t_rect.right = v_intRight;
	
	t_rect.top = v_intTop;
	
	t_rect.bottom = v_intBottom;
	
	t_pWnd->MoveWindow(t_rect);
}

/************************************************************
// 函数名称:Set_Control_Postion
// 功能描述:设置控件的位置和大小
// 输入参数:第1个参数为父窗口对象,一般为this指针
            第2个参数为要设置的控件ID号
			第3个参数为左上角的水平坐标
			第4个参数为左上角的垂直坐标
			第5个参数为右下角的水平坐标
			第6个参数为右下角的垂直坐标
// 输出参数:无输出参数
// 返回值  :执行成功返回TRUE,执行失败返回FALSE
/************************************************************/
inline void Set_Control_Postion(CWnd* v_CParentWnd,UINT v_intID, int v_intLeft,int v_intTop,int v_intRight,int v_intBottom)
{
	Set_CTR_Pos(v_CParentWnd,v_intID,v_intLeft,v_intTop,v_intRight,v_intBottom);
}

/************************************************************
// 函数名称:Hex_To_Ten
// 功能描述:十六进制数转换十进制数
// 输入参数:第1个参数为输入的十六进制数,字符串类型
// 输出参数:第2个参数为输出的无符号十进制数
// 返回值  :执行成功返回TRUE,执行失败返回FALSE
/************************************************************/
inline BOOL Hex_To_Ten(CString v_strData,DWORD& v_dwData)
{
	v_strData.MakeUpper();

	v_strData.MakeReverse();

	int t_intLength = v_strData.GetLength();

	if (t_intLength <= 0 || t_intLength > 8)
	{
		AfxMessageBox("数据超出范围");
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
			AfxMessageBox("数据格式不正确");
			
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
// 函数名称:Ten_To_Hex
// 功能描述:十进制数转换十六进制数
// 输入参数:第1个参数为输入的无符号十进制数
// 输出参数:第2个参数为输出的十六进制数,字符串类型
// 返回值  :执行成功返回TRUE,执行失败返回FALSE
/************************************************************/
inline BOOL Ten_To_Hex(DWORD v_dwData,CString& v_strData)
{
	CString t_strData,t_strNum2,t_strNum16;

	t_strData.Empty();

	v_strData.Empty();

	t_strNum2.Empty();

	t_strNum16.Empty();

	//10进制先转换2进制
	while (v_dwData >= 2)
	{
		t_strNum2.Format("%d",v_dwData % 2);

		t_strData += t_strNum2;

		v_dwData = v_dwData/2;
	}

	t_strNum2.Format("%d",v_dwData);

	t_strData += t_strNum2;

	//2进制的顺序相反

	int m_intHex;

	CString m_strHex;

	int i;

	//遍历2进制的所有位数
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

	//颠倒顺序
	v_strData.MakeReverse();

	return TRUE;
}


/************************************************************
// 函数名称:Square
// 功能描述:获取平方数
// 输入参数:第1个参数为输入的浮点型数据
// 输出参数:无输出参数
// 返回值  :返回浮点型数据的平方数
/************************************************************/
inline double Square(double v_douData)
{
	return v_douData * v_douData;
}

/************************************************************
// 函数名称:Sqrt
// 功能描述:重载开根函数
// 输入参数:第1个参数为输入的浮点型数据
// 输出参数:无输出参数
// 返回值  :返回浮点型数据的开根数,接近0的负数可以开根,结果为0
/************************************************************/
inline double Sqrt(double v_douData)
{
	//判定是否与0相等
	if (v_douData < 0)
	{
		//负数不是在0附近
		if (v_douData < -USER_ZERO)
		{
			AfxMessageBox("负数不能开根");
		}

		return 0;
	}

	return sqrt(v_douData);
}

/************************************************************
// 函数名称:Rad_to_Angle
// 功能描述:弧度转换角度
// 输入参数:第1个参数为输入的弧度
// 输出参数:无输出参数
// 返回值  :返回转换后的角度
/************************************************************/
inline double Rad_to_Angle(double v_douRad)
{
	return v_douRad * 180.0 / PI;
}

//
/************************************************************
// 函数名称:Angle_to_Rad
// 功能描述:角度转换弧度
// 输入参数:第1个参数为输入的角度
// 输出参数:无输出参数
// 返回值  :返回转换后的弧度
/************************************************************/
inline double Angle_to_Rad(double v_douAngle)
{
	return v_douAngle * PI / 180.0;
}

class CINI  
{
public:

	//构造函数
	CINI();

	//析构函数
	virtual ~CINI();

	//设置配置文档中某个选项的值
	BOOL Set_Item(CString v_strItem,CString v_strData);

	//设置配置文档中某个选项的值
	BOOL Set_Item(CString v_strItem,double v_douData);

	//设置配置文档中某个选项的值
	BOOL Set_Item(CString v_strItem,int v_intData);

	//设置配置文档中某个选项的值,可以指定段值
	BOOL Set_Item(CString v_strSection,CString v_strItem,CString v_strData);

	//设置配置文档中某个选项的值,可以指定段值
	BOOL Set_Item(CString v_strSection,CString v_strItem,double v_douData);

	//设置配置文档中某个选项的值,可以指定段值
	BOOL Set_Item(CString v_strSection,CString v_strItem,int v_intData);


	//获取配置文档中某个选项的值
	CString  Get_Item(CString v_strItem);

	//获取配置文档中某个选项的值
	int  Get_Item_Int(CString v_strItem);

	//获取配置文档中某个选项的值
	double  Get_Item_Double(CString v_strItem);


	//获取配置文档中某个选项的值,可以指定段值
	CString  Get_Item(CString v_strSection,CString v_strItem);

	//获取配置文档中某个选项的值
	int  Get_Item_Int(CString v_strSection,CString v_strItem);

	//获取配置文档中某个选项的值
	double  Get_Item_Double(CString v_strSection,CString v_strItem);


	//设置默认的路径和段值
	BOOL Init_INI(CString v_strPath,CString v_strSection);

	//读取应用程序所在路径
	CString Load_Path();

private:

	//保存Ini路径
	CString m_strPath;

	//默认读取的段值
	CString m_strSection;

	//读取的数据缓冲区,可用长度500
	char m_DataBuf[501];

};

class CCount_Time  
{

public:

	//构造函数
	CCount_Time();

	//析构函数，虚函数
	virtual ~CCount_Time();

	//复制构造函数
	CCount_Time(const CCount_Time& v_other);

	//重载赋值符号
	CCount_Time& operator=(const CCount_Time& v_other);

	//开始计时
	void Begin_Count();

	//结束计时,返回开始计时与结束计时之间的时间长度,单位为毫秒
	double End_Count(BOOL v_bReCount = FALSE);

private:

	//64位整数
	LARGE_INTEGER m_litmp;

	//时钟频率
	double m_douFreq;

	//用于获取两个时刻点的时间差,起始计时
	LONGLONG m_QPart1;

	//用于获取两个时刻点的时间差,终止计时
	LONGLONG m_QPart2;

	//返回的计时结果,单位微秒
	double m_douMinus;

	//返回的计时结果,单位毫秒
	double m_douTime;

};

//基本的文件操作
class CUser_File  
{
public:

	//构造函数
	CUser_File();

	//析构函数
	virtual ~CUser_File();

	//判断文件夹是否存在
	BOOL Is_Exist(CString v_strPath);

	//复制文件夹
	BOOL Copy_Folder(CString v_strPath,CString v_strNew);

	//删除文件夹
	BOOL Delete_Folder(CString v_strPath);

	//创建文件夹
	BOOL Create_Folder(CString v_strPath);

	//重命名文件
	BOOL Rename_File(CString v_strPath,CString v_strNew);

	//读取文件夹里面的所有文件
	void Load_Foder_File(CString v_strFoder,CStringArray& v_Array);

};



//支持的最大行数
#define TXT_MAXROW 1000000

class CTXT_IO  
{

	//外部可调用函数
public:

	CTXT_IO();

	virtual ~CTXT_IO();

	//打开TXT文档，用来读取
	BOOL Open_File(CString v_strPath);

	//通过对话框选择TXT文档
	BOOL Open_Dialog_File();

	//打开上一次选择的TXT文档
	BOOL Open_Last_File();

	//保存加工文档
	BOOL Save_File(CString v_strPath);

	//保存上一次选择的TXT文档
	BOOL Save_Last_File();

	//保存加工文档，检查数据是否修改过，如果没有修改过，不保存
	BOOL Save_File_Check(CString v_strPath);

	//新建TXT文档，用来写入
	BOOL Create_File(CString v_strPath);

	//删除文件
	BOOL Delete_File(CString v_strPath);

	//重命名文件
	BOOL Rename_File(CString v_strPath,CString v_strNewName);


	//插入一行,插入行在iRow，其他后面的行后置
	BOOL Insert_Row(int v_intRow);

	//在程式的最后增加一行
	BOOL Add_Row();

	//删除一行
	BOOL Remove_Row(int v_intRow);

	//删除所有数据
	BOOL Remove_All();

	//读取文件内存中的所有数据
	BOOL Get_All_Data(CStringArray& v_CStringArray);

	//设置所有数据到文件内存
	BOOL Set_All_Data(CStringArray& v_CStringArray);

	//读取单元格数据,0行0列的数据不读取
	BOOL Get_Cell(int v_intRow,int v_intCol,CString& v_strData);

	//设置单元格数据,0行0列的数据不设置
	BOOL Set_Cell(int v_intRow,int v_intCol,CString v_strData);


	//读取总行数
	int Get_Row_Count();

	//设置总列数
	BOOL Set_Col_Count(int v_intData);

	//数据是否修改过
	BOOL Is_Data_Change();

	//获取程式名称
	CString Get_Pro_Name();

protected:

	//读取TXT文档
	BOOL Read(CStdioFile& v_ReadFile);

	//写入TXT文档
	BOOL Write(CStdioFile& v_WriteFile,CStringArray& v_CStringArray);

	//检查文档并且增加路径
	BOOL Check_Path(CString& v_strPath);

private:

	//程式名称
	CString	     m_ProName;

	//字符串数组
	CStringArray m_CStringArray;

	//总行数
	int          m_intCountRow;

	//总列数,用来判断文件格式是否正确
	int          m_intCountCol;

	//数据是否修改过，每次打开软件和新程式，发送程式后，置否。修改数据后为真，
	BOOL         m_bDataChange;

};


class CMuti_Thread  
{
public:

	//构造函数
	CMuti_Thread();

	//析构函数
	virtual ~CMuti_Thread();

	//创建线程
	BOOL Create(AFX_THREADPROC v_pThClass,LPVOID v_pParam,int nPriority = THREAD_PRIORITY_NORMAL);

	//关闭线程
	BOOL Destroy();

	//线程是否执行中
	BOOL Is_Run();

protected:

	//交出当前线程的控制权,进入消息循环;主要用于取消已经开始的线程
	void Do_Events();

protected:

	//线程是否运行标志位
	BOOL m_bRun;

	//工作者线程指针对象
	CWinThread* m_pThread;
};



class CEvent1  
{
public:

	//构造函数
	CEvent1();

	//析构函数
	virtual ~CEvent1();

	//创建事件
	BOOL Create(BOOL v_bJogReset=TRUE,BOOL v_bStatus=FALSE);

	//关闭事件,释放事件句柄;关闭事件前,需要先退出等待事件的线程
	BOOL Destroy();

	//加锁,使事件变成非/激活状态
	BOOL Lock();

	//解锁,使事件变成/激活状态
	BOOL Unlock();

	//等待事件被激活,永远等待
	DWORD Wait();

	//等待事件被激活,等待一定的时间
	DWORD Wait(int v_intMiliSecond);

public:

	//事件句柄
	HANDLE m_hEvent;

};

class CUser_Signal  
{
public:

	//构造函数
	CUser_Signal();

	//析构函数
	virtual ~CUser_Signal();

	//主线程
public:

	//初始化信号,构造函数里面调用
	BOOL Init(BOOL v_bValue);

	//激活状态
	BOOL Set_Event();

	//激活状态,并且等待辅助线程修改两个信号一致;主线程发出命令,并且等待返回
	BOOL Set_Event_Wait(int v_MiliSecond = 4000);

	//非激活状态,并且等待辅助线程修改两个信号一致;主线程发出命令,并且等待返回
	BOOL Reset_Event_Wait(int v_MiliSecond= 4000);

	//非激活状态
	BOOL Reset_Event();

	//激活状态,并且等待辅助线程修改两个信号一致;主线程发出命令,并且等待返回,不处理主线程消息
	BOOL Set_Event_Wait2(int v_MiliSecond = 4000);

	//非激活状态,并且等待辅助线程修改两个信号一致;主线程发出命令,并且等待返回,不处理主线程消息
	BOOL Reset_Event_Wait2(int v_MiliSecond= 4000);

	//信号是否改变,辅助线程使用,提前同步信号
	BOOL Is_Change();

	//辅助线程
public:

	//是否激活状态,立即返回,辅助线程进入时判断
	BOOL Is_Set_Event();

	//是否非激活状态,立即返回,辅助线程进入时判断
	BOOL Is_Reset_Event();

	//使两个信号一致,辅助线程最后设置
	BOOL Make_Event_Same();

protected:

	//一定时间内,主线程等待信号
	BOOL Wait_User_Sinagle(const volatile BOOL& v_bSinagle,BOOL v_bValue,int v_MiliSecond);

	//交出当前线程的控制权,进入消息循环;主要用于取消已经开始的线程
	void Do_Events();

protected:

	//初始值,易变变量
	volatile BOOL m_bPre;

	//当前值,易变变量
	volatile BOOL m_bNow;
};



//标准笛卡尔坐标系,输入特定点,围绕圆心旋转角度A后的位置,角度以水平向右为0度,逆时针为正
BOOL Rotate_Point3(double v_douCenterX,double v_douCenterY,double v_douAngle,double *v_douX,double *v_douY);

//获取D盘剩余空间
DWORD Get_Disk_Space();

//获取磁盘剩余空间
DWORD Get_Disk_Space2(CString v_strPath);