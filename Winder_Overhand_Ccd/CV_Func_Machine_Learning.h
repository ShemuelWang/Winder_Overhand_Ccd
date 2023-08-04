#pragma once

#include "CV_Func_Pro.h"

#pragma comment(lib, "CV_Func_Machine_Learning.lib")

#ifndef DLL_IN
#define DLL_IN _declspec(dllimport)
#endif

#ifndef USER_ZERO
#define USER_ZERO 0.000000001
#endif

//直方图的范围
#ifndef _HISTOTRAM_RANGE
#define _HISTOTRAM_RANGE 256
#endif

//最多的缺陷个数
#ifndef _MAX_DEFECT_COUNT
#define _MAX_DEFECT_COUNT 10
#endif


typedef struct CvPoint
{
	int x;
	int y;
}
CvPoint;

struct MatPro
{
	//构造函数
	MatPro() {matData = NULL;};

	//析构函数
	~MatPro(){};

public:

	//矩阵宽度
	int width;

	//矩阵高度
	int height;

	//矩阵数据
	double *matData;

	//矩阵的每一个元素,先行后列
	double **at;
};

typedef MatPro* Mat2;

// 二值化图像
BOOL DLL_IN Threshold(const IPL v_Image,IPL *v_pBinary,int v_intMin = 127,int v_intMax = 255);

// 二值化图像
BOOL DLL_IN Threshold_Roi(const IPL v_Image,IPL *v_pBinary,int v_intLeft,int v_intTop,int v_intWidth,int v_intHeight,int v_intMin = 127,int v_intMax = 255);

//计算平方数
double DLL_IN Square2(double v_douData);

//释放矩阵
BOOL DLL_IN Release_Mat(Mat2 *v_pMat);

//创建矩阵
BOOL DLL_IN Create_Mat(Mat2 *v_pMat,int v_intWidth,int v_intHeight);

//参数1=输入的图像,单通道
//参数2=用于绘制的图像,三通道,可以输入空
//参数3=ROI 左点
//参数4=ROI 上点
//参数5=ROI 宽度
//参数6=ROI 高度
//参数7=掩码图像 输入为空,不采用掩码功能
//参数8=缺陷区域的阈值下限
//参数9=缺陷区域的阈值上限
//参数10=缺陷区域的面积大小,单位:像素
//参数11=输出的缺陷类型,0为没有缺陷,1为有缺陷
//参数12=输出的缺陷面积
int DLL_IN Find_Surface(const IPL v_Gray,IPL v_Rgb,int v_intLeft,int v_intTop,int v_intWidth,int v_intHeight,IPL v_Mask,int v_intThresholdMin,int v_intThresholdMax,int v_intArea,int *v_intSurfaceType,double *v_douSurfaceArea);


//超模糊抓边算法
//极性:0=任意极性;1=从黑到白;2=白到黑
//边缘类型：0=取中间灰度;1=取方差最大的点;2=取左侧第一条边缘;3=取右侧第一条边缘
BOOL DLL_IN Measure_Tank(IPL v_Image,int v_intLeft,int v_intTop,int v_intWidth,int v_intHeight,double *v_douRet,int *v_intNgType,int v_intTransition = 0,int v_intBoderType = 0,int v_intThreshold = 10);



class DLL_IN CCv_Model
{
public:
	CCv_Model(void);
	~CCv_Model(void);

	//创建模板
	//参数(输入) v_Image：用于创建模板的图像;单通道,图像宽度范围(0,1000],图像高度范围(0,1000]
	//参数(输入) v_douSimilar:相似度,范围(0,1]
	//函数执行成功返回1,执行失败返回0,出错返回负数
	int Create_Model(IPL v_Image,double v_douSimilar);

	//快速匹配算法-纵向
	int Match_Multiple_Fast(IPL v_Image,int v_intLeft,int v_intTop,int v_intHeight,double *v_douPos,double *v_douSimilar,int *v_intCount,int v_intLevel,int v_intMaxCount);

	//快速匹配算法-水平
	int Match_Horizontal_Multiple_Fast(IPL v_Image,int v_intLeft,int v_intTop,int v_intWidth,double *v_douPos,double *v_douSimilar,int *v_intCount,int v_intLevel,int v_intMaxCount);

	//获取模板宽度
	int Get_Width();

	//获取模板高度
	int Get_Height();

private:

	//计算提速的最佳等级
	int Get_Best_Level(int v_intSize);

	//获取缩放尺寸
	int Get_Scale_Size(int v_intLevel);

	//全图匹配-纵向
	int Match_Full(IPL v_Image,IPL v_Model,double *v_douPos,double *v_douSimilar,int *v_intCount);

	//全图匹配-水平
	int Match_Horizontal_Full(IPL v_Image,IPL v_Model,double *v_douPos,double *v_douSimilar,int *v_intCount);

	//局部匹配-纵向
	int Match_Roi(IPL v_Image,IPL v_Model,double *v_douPos,double *v_douSimilar);

	//局部匹配-水平
	int Match_Horizontal_Roi(IPL v_Image,IPL v_Model,double *v_douPos,double *v_douSimilar);

private:

	//模板图像
	IPL m_ModelImage;

	//相似度
	double m_douSimilar;

	//最多的匹配个数100个
	int m_intMaxMatchCount;

	//最大的灰度差
	int m_intMaxGrayDiff;
};



// 归并排序
template <class T>
BOOL Merge_Sort(T v_tArray[], int v_intCount,int v_intLevel,BOOL v_bDecrease = FALSE)
{
	//只有一个数据,不用排序;没有数据,直接返回
	if (v_intCount <= 1)
	{
		return TRUE;
	}

	//用于归并排序的临时内存,减少频繁分配内存的时间
	T *t_ptMemory = new T[v_intCount];

	int t_intLevel = v_intLevel;

	int t_intMidNum;

	int t_intEndNum;

	//运行次数
	int t_intRunTimes = 0;

	while(t_intLevel <= v_intCount)
	{
		t_intLevel *= 2;

		//将二个有序数列合并
		for (int i = 0; i < v_intCount; i += t_intLevel)
		{
			//如果结尾编号超出数组范围，取数组最后一个元素作为结束编号
			if (i + t_intLevel < v_intCount)
			{
				t_intEndNum = i + t_intLevel - 1;
			}
			else
			{
				t_intEndNum = v_intCount - 1;
			}

			t_intMidNum = i + t_intLevel / 2 - 1;

			if (t_intMidNum > t_intEndNum)
			{
				if (t_intRunTimes % 2 == 0)
				{
					for (int k = i; k <= t_intEndNum; k++)
					{
						t_ptMemory[k] = v_tArray[k];
					}
				}
				else
				{
					for (int k = i; k <= t_intEndNum; k++)
					{
						v_tArray[k] = t_ptMemory[k];
					}
				}

				continue;
			}

			if (t_intRunTimes % 2 == 0)
			{
				//合并相邻的两个有序序列
				Merge_Array(v_tArray,i, t_intMidNum,t_intEndNum ,t_ptMemory,v_bDecrease);
			}
			else
			{
				//合并相邻的两个有序序列
				Merge_Array(t_ptMemory,i, t_intMidNum,t_intEndNum ,v_tArray,v_bDecrease);
			}
		}

		t_intRunTimes++;
	}

	if (t_intRunTimes % 2 != 0)
	{
		for (int i = 0; i < v_intCount; i++)
		{
			v_tArray[i] = t_ptMemory[i];
		}
	}

	delete[] t_ptMemory;

	t_ptMemory = NULL;

	return TRUE;
}

//外部不调用
// 合并两个有序序列,两个有序序列位于同一个数组中
template <class T>
void Merge_Array(T v_tArray[],int v_intBeginNum,int v_intMidNum,int v_intEndNum, T v_tMemory[],BOOL v_bDecrease)
{
	//临时数组只是为了避免频繁分配内存

	//第一部分序列的起始编号
	int i = v_intBeginNum;

	//第二部分序列的起始编号
	int j = v_intMidNum + 1; 

	//临时数组当前指向的数组编号
	int k = v_intBeginNum;  

	if (v_bDecrease)
	{
		//递减
		while (i <= v_intMidNum && j <= v_intEndNum)  
		{  
			//获取数据大的元素
			if (v_tArray[i] >= v_tArray[j]) 
			{
				v_tMemory[k++] = v_tArray[i++];
			}
			else  
			{
				v_tMemory[k++] = v_tArray[j++];  
			}
		}
	}
	else
	{	
		//递增
		while (i <= v_intMidNum && j <= v_intEndNum)  
		{  
			//获取数据大的元素
			if (v_tArray[i] <= v_tArray[j]) 
			{
				v_tMemory[k++] = v_tArray[i++];
			}
			else  
			{
				v_tMemory[k++] = v_tArray[j++];  
			}
		}
	}

	//如果第一部分序列还有剩余元素,填充到结果数组最后
	while (i <= v_intMidNum) 
	{
		v_tMemory[k++] = v_tArray[i++];  
	}

	//如果第二部分序列还有剩余元素,填充到结果数组最后
	while (j <= v_intEndNum)  
	{
		v_tMemory[k++] = v_tArray[j++];  
	}
}




// 归并排序
template <class T,class T2>
BOOL Merge_Sort2(T v_tArray[],T2 v_tRelevance[], int v_intCount,int v_intLevel,BOOL v_bDecrease  = FALSE)
{
	//只有一个数据,不用排序;没有数据,直接返回
	if (v_intCount <= 1)
	{
		return TRUE;
	}

	//用于归并排序的临时内存,减少频繁分配内存的时间
	T *t_ptMemory = new T[v_intCount];

	T2 *t_ptReleMemo = new T2[v_intCount];

	int t_intLevel = v_intLevel;

	int t_intMidNum;

	int t_intEndNum;

	//运行次数
	int t_intRunTimes = 0;

	while(t_intLevel <= v_intCount)
	{
		t_intLevel *= 2;

		//将二个有序数列合并
		for (int i = 0; i < v_intCount; i += t_intLevel)
		{
			//如果结尾编号超出数组范围，取数组最后一个元素作为结束编号
			if (i + t_intLevel < v_intCount)
			{
				t_intEndNum = i + t_intLevel - 1;
			}
			else
			{
				t_intEndNum = v_intCount - 1;
			}

			t_intMidNum = i + t_intLevel / 2 - 1;

			if (t_intMidNum > t_intEndNum)
			{
				if (t_intRunTimes % 2 == 0)
				{
					for (int k = i; k <= t_intEndNum; k++)
					{
						t_ptMemory[k] = v_tArray[k];

						t_ptReleMemo[k] = v_tRelevance[k];
					}
				}
				else
				{
					for (int k = i; k <= t_intEndNum; k++)
					{
						v_tArray[k] = t_ptMemory[k];

						v_tRelevance[k] = t_ptReleMemo[k];
					}
				}

				continue;
			}

			if (t_intRunTimes % 2 == 0)
			{
				//合并相邻的两个有序序列
				Merge_Array2(v_tArray,v_tRelevance,i, t_intMidNum,t_intEndNum ,t_ptMemory,t_ptReleMemo,v_bDecrease);
			}
			else
			{
				//合并相邻的两个有序序列
				Merge_Array2(t_ptMemory,t_ptReleMemo,i, t_intMidNum,t_intEndNum ,v_tArray,v_tRelevance,v_bDecrease);
			}
		}

		t_intRunTimes++;
	}

	if (t_intRunTimes % 2 != 0)
	{
		for (int i = 0; i < v_intCount; i++)
		{
			v_tArray[i] = t_ptMemory[i];

			v_tRelevance[i] = t_ptReleMemo[i];
		}
	}

	delete[] t_ptMemory;

	t_ptMemory = NULL;

	delete[] t_ptReleMemo;

	t_ptReleMemo = NULL;

	return TRUE;
}


//外部不调用
// 合并两个有序序列,两个有序序列位于同一个数组中
template <class T,class T2>
void Merge_Array2(T v_tArray[],T2 v_tRelevance[],int v_intBeginNum,int v_intMidNum,int v_intEndNum, T v_tMemory[],T2 v_tReleMemo[],BOOL v_bDecrease)
{
	//临时数组只是为了避免频繁分配内存

	//第一部分序列的起始编号
	int i = v_intBeginNum;

	//第二部分序列的起始编号
	int j = v_intMidNum + 1; 

	//临时数组当前指向的数组编号
	int k = v_intBeginNum;  

	if (v_bDecrease)
	{
		//递减
		while (i <= v_intMidNum && j <= v_intEndNum)  
		{  
			//获取数据大的元素
			if (v_tArray[i] >= v_tArray[j]) 
			{
				v_tReleMemo[k] = v_tRelevance[i];

				v_tMemory[k++] = v_tArray[i++];
			}
			else  
			{
				v_tReleMemo[k] = v_tRelevance[j];

				v_tMemory[k++] = v_tArray[j++];  
			}
		}
	}
	else
	{	
		//递增
		while (i <= v_intMidNum && j <= v_intEndNum)  
		{  
			//获取数据大的元素
			if (v_tArray[i] <= v_tArray[j]) 
			{
				v_tReleMemo[k] = v_tRelevance[i];

				v_tMemory[k++] = v_tArray[i++];
			}
			else  
			{
				v_tReleMemo[k] = v_tRelevance[j];

				v_tMemory[k++] = v_tArray[j++];  
			}
		}
	}

	//如果第一部分序列还有剩余元素,填充到结果数组最后
	while (i <= v_intMidNum) 
	{
		v_tReleMemo[k] = v_tRelevance[i];

		v_tMemory[k++] = v_tArray[i++];  
	}

	//如果第二部分序列还有剩余元素,填充到结果数组最后
	while (j <= v_intEndNum)  
	{
		v_tReleMemo[k] = v_tRelevance[j];

		v_tMemory[k++] = v_tArray[j++];  
	}
}


//交换两个数据
template <class T>
void Swap(T v_T1,T v_T2)
{
	T t_T = v_T1;

	v_T1 = v_T2;

	v_T2 = t_T;
}





//图元结构
class CvMeta
{
public:

	CvMeta()
	{
		//行号
		m_RowNum = 0;

		//起始列
		m_StartCol = 0;

		//结束列
		m_EndCol = 0;

		//标志码
		m_Label = 0;
	};

	~CvMeta()
	{

	};

	//拷贝构造函数
	CvMeta(const CvMeta &v_Other)
	{
		this->m_RowNum = v_Other.m_RowNum;

		this->m_StartCol = v_Other.m_StartCol;

		this->m_EndCol = v_Other.m_EndCol;

		this->m_Label = v_Other.m_Label;
	};

	//赋值函数
	CvMeta& operator =(const CvMeta &v_Other)
	{
		this->m_RowNum = v_Other.m_RowNum;

		this->m_StartCol = v_Other.m_StartCol;

		this->m_EndCol = v_Other.m_EndCol;

		this->m_Label = v_Other.m_Label;

		return *this;
	};

public:

	//行号
	int m_RowNum;

	//起始列
	int m_StartCol;

	//结束列
	int m_EndCol;

	//标志码
	int m_Label;
};

//定义节点
class CvNode 
{
public:
	//构造函数
	CvNode(){ m_pNextNode = NULL;};

	//析构函数
	~CvNode(){};

	//节点信息
	CvMeta m_Meta;

	//指向下一个节点
	CvNode *m_pNextNode;
};

class DLL_IN CCV_List
{
public:

	//构造函数
	CCV_List();

	//析构函数
	virtual ~CCV_List();

	//添加节点
	BOOL Add(CvMeta *v_pMeta);

	//插入节点，当前节点全部后移
	BOOL Insert(int v_intNum,CvMeta *v_pMeta);

	//删除节点
	BOOL Remove(int v_intNum);

	//删除所有节点
	BOOL Remove_All();

	//获取节点的图元信息
	BOOL Get(int v_intNum,CvMeta *v_pMeta);

	//设置节点的图元信息
	BOOL Set(int v_intNum,CvMeta *v_pMeta);

	//获取链表长度
	int Get_Length();

	//复制链表,会复制图像宽度和高度
	BOOL Copy_From(CCV_List* v_pSourceList);

	//重置链表,从头开始获取节点
	BOOL Reset();

	// 获取当前节点的图元信息,自动指向下一个节点
	BOOL Get_Auto(CvMeta *v_pMeta);

	// 设置当前节点的图元信息,自动指向下一个节点
	BOOL Set_Auto(CvMeta *v_pMeta);

	// 使用新图元替换一段连续图元
	BOOL Replace(int v_intNum,CvMeta *v_pMeta,int v_ReplacedCount);


public:

	//指向下一个链表
	CCV_List* m_pNextList;

	//图像宽度
	int m_intWidth;

	//图像高度
	int m_intHeight;

protected:

	//链表长度
	int m_intLength;

	//链表头
	CvNode *m_pHead;

	//链表结尾
	CvNode *m_pEnd;

	//当前选择的节点
	CvNode *m_pChosen;
};

//声明行程编码链表
typedef CCV_List* RunList;

class DLL_IN CCV_Shape
{
public:

	CCV_Shape(void);

	~CCV_Shape(void);

	//复制构造函数
	CCV_Shape(const CCV_Shape &v_Other);

	//重载赋值运算符
	CCV_Shape& operator= (const CCV_Shape &v_Other);

	//常用函数
public:

	// 获取指定灰度的形状
	BOOL Find(const IPL v_Image,int v_Min = 127,int v_Max = 255);

	// 阈值图像,然后保存成一个整体区域
	BOOL Threshold_To_Region(const IPL v_Image,int v_Min = 127,int v_Max = 255);

	// 阈值图像,然后保存成一个整体区域
	BOOL Threshold_To_Region_Roi(const IPL v_Image,int v_intLeft,int v_intTop,int v_intWidth,int v_intHeight,int v_Min = 127,int v_Max = 255);

	// 阈值图像,然后保存成一个整体区域,支持连通距离的设定
	BOOL Threshold_To_Region_Roi_Dis(const IPL v_Image,int v_intLeft,int v_intTop,int v_intWidth,int v_intHeight,int v_Min = 127,int v_Max = 255,int v_intDis = 10);

	// 阈值图像,然后保存成一个整体区域,增加掩码图像
	BOOL Threshold_To_Region_Mask(const IPL v_Image,int v_Min = 127,int v_Max = 255,const IPL v_Mask = NULL);

	// 获取连通域
	BOOL Connection();

	// 获取连通域,支持连通距离的设定
	BOOL Connection_Dis(int v_intWidth,int v_intHeight);


	// 筛选形状
	BOOL Select(CString v_strType,double v_Min,double v_Max);

	// 显示形状的特性值
	BOOL Show(CString v_strType);

	// 排序形状,默认为降序
	BOOL Sort(CString v_strType,BOOL v_bDown = TRUE);

	// 填充形状内部的孔洞
	BOOL Fill_Up();

	// 填充形状内部的孔洞,只填充灰度值在指定范围内的区域
	BOOL Fill_Up_Gray(const IPL v_Image,double v_douOffest = 10.0);

	// 获取凸包
	BOOL Convex();

	// 获取形状的特征区域，包括平行外接矩形，最小外接矩形,最小外接圆
	BOOL Trans(CString v_strType);

	// 形状是否为空
	BOOL Is_Empty();

	// 从图像中筛选区域部分的图像,最后一个参数是背景色
	BOOL Reduce_Domain(const IPL v_Image,IPL* v_Reduce,CvScalar v_BackColor = CV_RGB(0,0,0));

	// 半透明填充区域
	BOOL Alpha(const IPL v_Image,double v_Pellucidity = 0.5,CvScalar v_Scalar = CV_RGB(255,0,0));

	// 半透明填充区域,增加尺寸缩放功能
	BOOL Alpha_Ex(const IPL v_Image,int v_intSize,double v_Pellucidity = 0.5,CvScalar v_Scalar = CV_RGB(255,0,0));

	// 通过矩形尺寸分割区域
	BOOL Partition_Rectangle(int v_intWidth);

	// 格式化形状链表,保证所有的行程码都在图像范围内
	BOOL Format_Run_List();

	//设置图像尺寸
	BOOL Set_Size(int v_intWidth,int v_intHeight);

	//获取图像尺寸
	BOOL Get_Size(int *v_intWidth,int *v_intHeight);

	// 8邻域距离变换,待完善
	BOOL Distance_Transform_Chessboard(CCV_Shape &v_Other,double *v_douMaxDis);

	// 骨架化,需要增加每一个形状计算
	BOOL Skeleton();

	// 骨架化,通过水平方向
	BOOL Skeleton_Horizontal();

	//计算最小面积的四边形
	BOOL Mini_Area_Quad();

	//获取最小面积的任意四边形的四个顶点,左上->右上->右下->左下
	BOOL Get_Mini_Quad(CvPoint **v_pPoint);

	//获取行程码个数
	int Get_Run_List_Count();

	//击中击不中判定
	//输入的ROI区域有前景像素,返回TRUE
	//输入的ROI区域有前景像素,返回FALSE
	BOOL Hit_Or_Miss(int v_intLeft,int v_intTop,int v_intWidth,int v_intHeight,BOOL v_bAble);

	//获取形状特性
public:

	// 获取形状集合的个数
	int Get_Count();

	//获取图像宽度
	int Get_Image_Width();

	//获取图像高度
	int Get_Image_Height();

	// 获取形状的面积
	BOOL Get_Area(double *v_Area);

	// 获取形状的周长
	BOOL Get_Length(double *v_Length);

	// 获取形状的重心
	BOOL Get_Gravity(double *v_Row,double *v_Col);

	//获取各向异性
	BOOL Get_Anisometry(double *v_douAnisometry);

	// 获取形状的外接平行矩形
	BOOL Get_Parallel_Rect(double *v_MidX,double *v_MidY,double *v_Width,double *v_Height);

	// 获取形状的外接平行矩形
	BOOL Get_Parallel_Rect(int *v_intTop,int *v_intLeft,int *v_intBottom,int *v_intRight);

	// 获取旋转角度
	BOOL Get_Angle(double *v_Angle);

	// 获取最小矩形的参数
	BOOL Get_Mini_Rect(double *v_MidX,double *v_MidY,double *v_Width,double *v_Height,double *v_Angle);

	// 获取形状的区域图像
	BOOL Get_Region_Image(IPL *v_Image,BOOL v_bColor = FALSE);

	// 获取形状的轮廓边缘图像
	BOOL Get_Contour_Image(IPL *v_Image,BOOL v_bColor = FALSE);

	// 获取形状的区域点
	BOOL Get_Region(int *v_pintPointCount,int **v_pintRow,int **v_pintCol);

	// 设置形状的区域点
	BOOL Set_Region(int v_pintPointCount,int *v_pintRow,int *v_pintCol,int v_intBkWidth = 1280,int v_intBkHeight = 960);

	// 获取单个形状的轮廓点
	BOOL Get_Contour(int *v_pintPointCount,int **v_pintRow,int **v_pintCol);

	// 获取单个形状的轮廓点
	BOOL Get_Contour3(int *v_pintUpCount,int **v_pintUpRow,int **v_pintUpCol,
		int *v_pintDownCount,int **v_pintDownRow,int **v_pintDownCol,
		int *v_pintLeftCount,int **v_pintLeftRow,int **v_pintLeftCol,
		int *v_pintRightCount,int **v_pintRightRow,int **v_pintRightCol);


	// 从其他形状链表获取对象,编号从0开始
	BOOL Get_Object(CCV_Shape &v_Ohter,int v_intIndex);

	// 获取面积最大的形状
	BOOL Get_Max_Area();

	//获取单个形状距离特定点的最远点
	BOOL Get_Far_Point(double v_douCenterRow,double v_douCenterCol,double *v_douFarRow,double *v_douFarCol);

	//获取区域的平均高度
	BOOL Get_Aver_High(double *v_douHeight);

	// 获取形状的平均宽度
	BOOL Get_Aver_Width(double *v_douWidth);

	// 获取形状的宽度均方差
	BOOL Get_Width_Variance(double *v_douVariance);


	//获取区域的平均灰度
	BOOL Get_Aver_Gray(const IPL v_Image,double *v_douAverGray);

	//获取区域的标准差,待测试
	BOOL Get_Standard_Deviation(const IPL v_Image,double *v_douStaDev);

	//获取区域的标准差,只统计比平均灰度大的像素
	BOOL Get_Standard_Deviation_White(const IPL v_Image,double *v_douStaDev);

	//获取区域的标准差,只统计比平均灰度小的像素
	BOOL Get_Standard_Deviation_Black(const IPL v_Image,double *v_douStaDev);

	//获取最左点的顶点,如果有多个,取最下方那个,待完善
	BOOL Get_Left_Down_Conner(int *v_intRow,int *v_intCol);

	//获取最右点的顶点,如果有多个,取最下方那个,待完善
	BOOL Get_Right_Down_Conner(int *v_intRow,int *v_intCol);

	// 获取范围内的最左点,待完善
	BOOL Get_Range_Left_Conner(int v_intBeginRow,int v_intEndRow,int *v_intCol);

	// 获取范围内的最右点,待完善
	BOOL Get_Range_Right_Conner(int v_intBeginRow,int v_intEndRow,int *v_intCol);

	//集合运算
public:

	//合并
	BOOL Union();

	//并集
	BOOL Union2(CCV_Shape &v_Other);

	//交集,结果个数与当前一致
	BOOL Intersection(CCV_Shape &v_Other);

	//差集
	BOOL Difference(CCV_Shape &v_Other);

	//补集
	BOOL Complement();

	//移动,移动之后，一般需要格式化行程链表
	BOOL Move(int v_intRow,int v_intCol);

	//形态学,形态学之后,一般需要格式化行程链表
public:

	//任意结构元膨胀
	BOOL Dilation(CvMeta *v_pMeta,int v_MetaCount);

	//任意结构元腐蚀
	BOOL Erosion(CvMeta *v_pMeta,int v_MetaCount);

	//矩形膨胀
	BOOL Dilation_Rect(int v_intWidth,int v_intHeight);

	//矩形腐蚀
	BOOL Erosion_Rect(int v_intWidth,int v_intHeight);

	//圆形膨胀,直径为奇数
	BOOL Dilation_Circle(int v_intDiameter);

	//圆形腐蚀,直径为奇数
	BOOL Erosion_Circle(int v_intDiameter);

	//矩形开运算
	BOOL Opening_Rect(int v_intWidth,int v_intHeight);

	//矩形闭运算，一般需要先联合形状
	BOOL Closing_Rect(int v_intWidth,int v_intHeight);

	//圆形开运算,直径为奇数
	BOOL Opening_Circle(int v_intDiameter);

	//圆形闭运算,直径为奇数，一般需要先联合形状
	BOOL Closing_Circle(int v_intDiameter);

	//创建区域
public:

	//创建与坐标轴平行的矩形区域
	BOOL Gen_Rect1(int v_intRow1,int v_intCol1,int v_intRow2,int v_intCol2,int v_intBkWidth = 1280,int v_intBkHeight = 960);

	//创建任意角度的矩形区域,以水平右方向为0度,逆时针为正方向,范围[0,180),(中心点为整数时,宽度和高度为奇数)
	BOOL Gen_Rect2(double v_douRow,double v_douCol,double v_douWidth,double v_douHeight,double v_douAngle,int v_intBkWidth = 1280,int v_intBkHeight = 960);

	//创建圆形区域
	BOOL Gen_Circle(double v_douCenterX,double v_douCenterY,double v_douRadius,int v_intBkWidth = 1280,int v_intBkHeight = 960);

	//形状特征
private:

	// 获取单个形状的重心
	BOOL Get_Gravity(RunList v_List,double *v_douRow,double *v_douCol);

	// 获取单个形状的面积
	BOOL Get_Area(RunList v_List,int *v_Result);

	//获取区域的平均高度
	BOOL Get_Aver_High(RunList v_List,double *v_Result);

	//获取区域的平均宽度
	BOOL Get_Aver_Width(RunList v_List,double *v_Result);

	// 获取区域的宽度均方差
	BOOL Get_Width_Variance(RunList v_List,double *v_Result);

	// 获取单个形状的周长(包括内轮廓)
	BOOL Get_Length(RunList v_List,double *v_Result);

	// 获取单个形状的平行宽度
	BOOL Get_Parallel_Width(RunList v_List,int *v_Result);

	// 获取单个形状的平行高度
	BOOL Get_Parallel_Height(RunList v_List,int *v_Result);

	// 获取单个形状的四个顶点
	BOOL Get_Conner_Point(RunList v_List,int *v_Top,int *v_Bottom,int *v_Left,int *v_Right);

	// 获取单个形状的最左点
	BOOL Get_Left_Down_Conner(RunList v_List,int *v_intRow,int *v_intCol);

	// 获取单个形状的最右点
	BOOL Get_Right_Down_Conner(RunList v_List,int *v_intRow,int *v_intCol);

	// 获取单个形状的范围内的最左点
	BOOL Get_Range_Left_Conner(RunList v_List,int v_intBeginRow,int v_intEndRow,int *v_intCol);

	// 获取单个形状的范围内的最右点
	BOOL Get_Range_Right_Conner(RunList v_List,int v_intBeginRow,int v_intEndRow,int *v_intCol);

	// 获取单个形状的紧密性
	BOOL Get_Compactness(RunList v_List,double *v_Result);

	// 获取单个形状的各向异性
	BOOL Get_Anisometry(RunList v_List,double *v_Result);

	// 获取单个形状的圆心度
	BOOL Get_Circularity(RunList v_List,double *v_Result);

	// 获取单个形状的矩形度
	BOOL Get_Rectangularity(RunList v_List,double *v_Result);

	// 获取单个形状的矩形比例
	BOOL Get_Rectangularity_Ex(RunList v_List,double *v_Result);

	// 获取单个形状的凸性
	BOOL Get_Convexty(RunList v_List,double *v_Result);

	// 获取单个形状的空心率
	BOOL Get_Emptiness(RunList v_List,double *v_Result);

	// 获取单个形状的旋转角度,以水平右方向为0度,逆时针为正方向,范围[-45,45]
	BOOL Get_Angle(RunList v_List,double *v_Result);

	//获取最小重心距离
	BOOL Get_Mini_Distance(double v_douRow[],double v_douCol[],int v_intCount,int v_intIndex,double *v_Result);

	//获取最小面积的任意四边形的面积比例
	BOOL Get_Mini_Quad_Ness(RunList v_List,double *v_Result);

	//获取单个形状的最小面积的任意四边形
	BOOL Get_Mini_Quad(RunList v_List,RunList v_ListResult,CvPoint v_Point[4]);

	//交集,计算两个区域的交集
	BOOL Intersection(RunList v_List,RunList v_List2,RunList v_ListResult);

	//基本运算
private:

	// 释放链表的空间
	BOOL Release_List(RunList *v_List);

	// 获取单个形状的轮廓点,修改为4邻域
	BOOL Get_Contour(RunList v_List,RunList v_ListResult);

	// 获取单个形状的轮廓点,8邻域
	BOOL Get_Contour2(RunList v_List,RunList v_ListResult);

	// 获取单个形状的轮廓点,修改为4邻域
	BOOL Get_Contour3(RunList v_List,RunList v_ListUp,RunList v_ListDown,RunList v_ListLeft,RunList v_ListRight);

	// 获取行程链表的补集,可以增加图像外部的行程,暂时不删除
	BOOL Complement2(RunList v_List,RunList v_ListResult,int v_intOuterWidth,int v_intOuterHeight);

	// 获取形状的归一化矩
	BOOL Get_Norma_Moments(RunList v_List,double *v_douM00,double *v_douM01,double *v_douM10,double *v_douM02,double *v_douM11,double *v_douM20);

	// 计算单个形状的凸包
	BOOL Get_Convex(RunList v_List,CvPoint **v_pPoint,int *v_intCount);

	// 计算单个形状的填充区域,还需要排序行程码,与原来的形状求并集
	BOOL Get_Fill(RunList v_List,RunList v_ListResult);

	// 获取单个形状的最小外接矩形
	BOOL Get_Mini_Rect(RunList v_List,RunList v_ListResult,double *v_MidX,double *v_MidY,double *v_Width,double *v_Height,double *v_douRad);

	// 行程编码数组求并集,使用归并排序
	BOOL Run_Array_Union(CvMeta *v_pMeta,int v_intCount,int v_intLevel,RunList v_List);

	// 根据图形的顶点,生成行程码链表
	BOOL Get_Conner_List(CvPoint *v_pPoint,int v_intCount,RunList v_ListResult);

	//获取两个点的直线一般方程
	BOOL Get_Line(double v_douX1,double v_douY1,double v_douX2,double v_douY2,double *v_douA,double *v_douB,double *v_douC);

private:

	//行程编码
	RunList m_List;

	//图像宽度,在Find函数里面设置
	int m_intWidth;

	//图像高度,在Find函数里面设置
	int m_intHeight;

	//最大距离
	static const int m_intMaxDis = 65535;

	//用于填充颜色的数组
	CvScalar *m_pcvFillColor;

	//颜色个数
	static const int m_intColorCount = 24;
};


//视场角转换模块
class DLL_IN CWinder_Angle_View
{
public:
	CWinder_Angle_View(void);
	~CWinder_Angle_View(void);

	//设置相机分辨率X和裁切位置X
	BOOL Set_Camera_Resolution(int v_intResolution,int v_intOffsetX);

	//设置0圈的像素当量和像素当量的每增加1mm工作距离的变化量
	BOOL Set_Pixel_Dis_Derivative(double v_douPixelDis,double v_douDerivative);

	//设置电芯每一圈的厚度变化,单位mm，有正负
	//远离相机为正数，即工作距离增大
	//靠近相机为负数，即工作距离减小
	BOOL Set_Prismatic_Layer_Thickness(double v_douThickness);

	//获取特定圈数的像素当量,输入拍照次数
	double Get_Chosen_Layer_Pixel_Dis(int v_intTriIndex);

	//获取特定圈数,映射后的边缘位置,输入拍照次数和初始的边缘像素位置
	double Get_Chosen_Layer_Boder_Pos(int v_intTriIndex,double v_douSrcPos);

private:

	//光轴中心,单位像素
	double m_douOpticalAxis;

	//0圈的像素当量
	double m_douPixelDisBasic;

	//设置像素当量的导数
	double m_douPixelDisDeriva;

	//电芯每一层的厚度
	double m_douLayerThickness;
};

