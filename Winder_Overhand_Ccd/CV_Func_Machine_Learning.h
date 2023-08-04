#pragma once

#include "CV_Func_Pro.h"

#pragma comment(lib, "CV_Func_Machine_Learning.lib")

#ifndef DLL_IN
#define DLL_IN _declspec(dllimport)
#endif

#ifndef USER_ZERO
#define USER_ZERO 0.000000001
#endif

//ֱ��ͼ�ķ�Χ
#ifndef _HISTOTRAM_RANGE
#define _HISTOTRAM_RANGE 256
#endif

//����ȱ�ݸ���
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
	//���캯��
	MatPro() {matData = NULL;};

	//��������
	~MatPro(){};

public:

	//������
	int width;

	//����߶�
	int height;

	//��������
	double *matData;

	//�����ÿһ��Ԫ��,���к���
	double **at;
};

typedef MatPro* Mat2;

// ��ֵ��ͼ��
BOOL DLL_IN Threshold(const IPL v_Image,IPL *v_pBinary,int v_intMin = 127,int v_intMax = 255);

// ��ֵ��ͼ��
BOOL DLL_IN Threshold_Roi(const IPL v_Image,IPL *v_pBinary,int v_intLeft,int v_intTop,int v_intWidth,int v_intHeight,int v_intMin = 127,int v_intMax = 255);

//����ƽ����
double DLL_IN Square2(double v_douData);

//�ͷž���
BOOL DLL_IN Release_Mat(Mat2 *v_pMat);

//��������
BOOL DLL_IN Create_Mat(Mat2 *v_pMat,int v_intWidth,int v_intHeight);

//����1=�����ͼ��,��ͨ��
//����2=���ڻ��Ƶ�ͼ��,��ͨ��,���������
//����3=ROI ���
//����4=ROI �ϵ�
//����5=ROI ���
//����6=ROI �߶�
//����7=����ͼ�� ����Ϊ��,���������빦��
//����8=ȱ���������ֵ����
//����9=ȱ���������ֵ����
//����10=ȱ������������С,��λ:����
//����11=�����ȱ������,0Ϊû��ȱ��,1Ϊ��ȱ��
//����12=�����ȱ�����
int DLL_IN Find_Surface(const IPL v_Gray,IPL v_Rgb,int v_intLeft,int v_intTop,int v_intWidth,int v_intHeight,IPL v_Mask,int v_intThresholdMin,int v_intThresholdMax,int v_intArea,int *v_intSurfaceType,double *v_douSurfaceArea);


//��ģ��ץ���㷨
//����:0=���⼫��;1=�Ӻڵ���;2=�׵���
//��Ե���ͣ�0=ȡ�м�Ҷ�;1=ȡ�������ĵ�;2=ȡ����һ����Ե;3=ȡ�Ҳ��һ����Ե
BOOL DLL_IN Measure_Tank(IPL v_Image,int v_intLeft,int v_intTop,int v_intWidth,int v_intHeight,double *v_douRet,int *v_intNgType,int v_intTransition = 0,int v_intBoderType = 0,int v_intThreshold = 10);



class DLL_IN CCv_Model
{
public:
	CCv_Model(void);
	~CCv_Model(void);

	//����ģ��
	//����(����) v_Image�����ڴ���ģ���ͼ��;��ͨ��,ͼ���ȷ�Χ(0,1000],ͼ��߶ȷ�Χ(0,1000]
	//����(����) v_douSimilar:���ƶ�,��Χ(0,1]
	//����ִ�гɹ�����1,ִ��ʧ�ܷ���0,�����ظ���
	int Create_Model(IPL v_Image,double v_douSimilar);

	//����ƥ���㷨-����
	int Match_Multiple_Fast(IPL v_Image,int v_intLeft,int v_intTop,int v_intHeight,double *v_douPos,double *v_douSimilar,int *v_intCount,int v_intLevel,int v_intMaxCount);

	//����ƥ���㷨-ˮƽ
	int Match_Horizontal_Multiple_Fast(IPL v_Image,int v_intLeft,int v_intTop,int v_intWidth,double *v_douPos,double *v_douSimilar,int *v_intCount,int v_intLevel,int v_intMaxCount);

	//��ȡģ����
	int Get_Width();

	//��ȡģ��߶�
	int Get_Height();

private:

	//�������ٵ���ѵȼ�
	int Get_Best_Level(int v_intSize);

	//��ȡ���ųߴ�
	int Get_Scale_Size(int v_intLevel);

	//ȫͼƥ��-����
	int Match_Full(IPL v_Image,IPL v_Model,double *v_douPos,double *v_douSimilar,int *v_intCount);

	//ȫͼƥ��-ˮƽ
	int Match_Horizontal_Full(IPL v_Image,IPL v_Model,double *v_douPos,double *v_douSimilar,int *v_intCount);

	//�ֲ�ƥ��-����
	int Match_Roi(IPL v_Image,IPL v_Model,double *v_douPos,double *v_douSimilar);

	//�ֲ�ƥ��-ˮƽ
	int Match_Horizontal_Roi(IPL v_Image,IPL v_Model,double *v_douPos,double *v_douSimilar);

private:

	//ģ��ͼ��
	IPL m_ModelImage;

	//���ƶ�
	double m_douSimilar;

	//����ƥ�����100��
	int m_intMaxMatchCount;

	//���ĻҶȲ�
	int m_intMaxGrayDiff;
};



// �鲢����
template <class T>
BOOL Merge_Sort(T v_tArray[], int v_intCount,int v_intLevel,BOOL v_bDecrease = FALSE)
{
	//ֻ��һ������,��������;û������,ֱ�ӷ���
	if (v_intCount <= 1)
	{
		return TRUE;
	}

	//���ڹ鲢�������ʱ�ڴ�,����Ƶ�������ڴ��ʱ��
	T *t_ptMemory = new T[v_intCount];

	int t_intLevel = v_intLevel;

	int t_intMidNum;

	int t_intEndNum;

	//���д���
	int t_intRunTimes = 0;

	while(t_intLevel <= v_intCount)
	{
		t_intLevel *= 2;

		//�������������кϲ�
		for (int i = 0; i < v_intCount; i += t_intLevel)
		{
			//�����β��ų������鷶Χ��ȡ�������һ��Ԫ����Ϊ�������
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
				//�ϲ����ڵ�������������
				Merge_Array(v_tArray,i, t_intMidNum,t_intEndNum ,t_ptMemory,v_bDecrease);
			}
			else
			{
				//�ϲ����ڵ�������������
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

//�ⲿ������
// �ϲ�������������,������������λ��ͬһ��������
template <class T>
void Merge_Array(T v_tArray[],int v_intBeginNum,int v_intMidNum,int v_intEndNum, T v_tMemory[],BOOL v_bDecrease)
{
	//��ʱ����ֻ��Ϊ�˱���Ƶ�������ڴ�

	//��һ�������е���ʼ���
	int i = v_intBeginNum;

	//�ڶ��������е���ʼ���
	int j = v_intMidNum + 1; 

	//��ʱ���鵱ǰָ���������
	int k = v_intBeginNum;  

	if (v_bDecrease)
	{
		//�ݼ�
		while (i <= v_intMidNum && j <= v_intEndNum)  
		{  
			//��ȡ���ݴ��Ԫ��
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
		//����
		while (i <= v_intMidNum && j <= v_intEndNum)  
		{  
			//��ȡ���ݴ��Ԫ��
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

	//�����һ�������л���ʣ��Ԫ��,��䵽����������
	while (i <= v_intMidNum) 
	{
		v_tMemory[k++] = v_tArray[i++];  
	}

	//����ڶ��������л���ʣ��Ԫ��,��䵽����������
	while (j <= v_intEndNum)  
	{
		v_tMemory[k++] = v_tArray[j++];  
	}
}




// �鲢����
template <class T,class T2>
BOOL Merge_Sort2(T v_tArray[],T2 v_tRelevance[], int v_intCount,int v_intLevel,BOOL v_bDecrease  = FALSE)
{
	//ֻ��һ������,��������;û������,ֱ�ӷ���
	if (v_intCount <= 1)
	{
		return TRUE;
	}

	//���ڹ鲢�������ʱ�ڴ�,����Ƶ�������ڴ��ʱ��
	T *t_ptMemory = new T[v_intCount];

	T2 *t_ptReleMemo = new T2[v_intCount];

	int t_intLevel = v_intLevel;

	int t_intMidNum;

	int t_intEndNum;

	//���д���
	int t_intRunTimes = 0;

	while(t_intLevel <= v_intCount)
	{
		t_intLevel *= 2;

		//�������������кϲ�
		for (int i = 0; i < v_intCount; i += t_intLevel)
		{
			//�����β��ų������鷶Χ��ȡ�������һ��Ԫ����Ϊ�������
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
				//�ϲ����ڵ�������������
				Merge_Array2(v_tArray,v_tRelevance,i, t_intMidNum,t_intEndNum ,t_ptMemory,t_ptReleMemo,v_bDecrease);
			}
			else
			{
				//�ϲ����ڵ�������������
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


//�ⲿ������
// �ϲ�������������,������������λ��ͬһ��������
template <class T,class T2>
void Merge_Array2(T v_tArray[],T2 v_tRelevance[],int v_intBeginNum,int v_intMidNum,int v_intEndNum, T v_tMemory[],T2 v_tReleMemo[],BOOL v_bDecrease)
{
	//��ʱ����ֻ��Ϊ�˱���Ƶ�������ڴ�

	//��һ�������е���ʼ���
	int i = v_intBeginNum;

	//�ڶ��������е���ʼ���
	int j = v_intMidNum + 1; 

	//��ʱ���鵱ǰָ���������
	int k = v_intBeginNum;  

	if (v_bDecrease)
	{
		//�ݼ�
		while (i <= v_intMidNum && j <= v_intEndNum)  
		{  
			//��ȡ���ݴ��Ԫ��
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
		//����
		while (i <= v_intMidNum && j <= v_intEndNum)  
		{  
			//��ȡ���ݴ��Ԫ��
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

	//�����һ�������л���ʣ��Ԫ��,��䵽����������
	while (i <= v_intMidNum) 
	{
		v_tReleMemo[k] = v_tRelevance[i];

		v_tMemory[k++] = v_tArray[i++];  
	}

	//����ڶ��������л���ʣ��Ԫ��,��䵽����������
	while (j <= v_intEndNum)  
	{
		v_tReleMemo[k] = v_tRelevance[j];

		v_tMemory[k++] = v_tArray[j++];  
	}
}


//������������
template <class T>
void Swap(T v_T1,T v_T2)
{
	T t_T = v_T1;

	v_T1 = v_T2;

	v_T2 = t_T;
}





//ͼԪ�ṹ
class CvMeta
{
public:

	CvMeta()
	{
		//�к�
		m_RowNum = 0;

		//��ʼ��
		m_StartCol = 0;

		//������
		m_EndCol = 0;

		//��־��
		m_Label = 0;
	};

	~CvMeta()
	{

	};

	//�������캯��
	CvMeta(const CvMeta &v_Other)
	{
		this->m_RowNum = v_Other.m_RowNum;

		this->m_StartCol = v_Other.m_StartCol;

		this->m_EndCol = v_Other.m_EndCol;

		this->m_Label = v_Other.m_Label;
	};

	//��ֵ����
	CvMeta& operator =(const CvMeta &v_Other)
	{
		this->m_RowNum = v_Other.m_RowNum;

		this->m_StartCol = v_Other.m_StartCol;

		this->m_EndCol = v_Other.m_EndCol;

		this->m_Label = v_Other.m_Label;

		return *this;
	};

public:

	//�к�
	int m_RowNum;

	//��ʼ��
	int m_StartCol;

	//������
	int m_EndCol;

	//��־��
	int m_Label;
};

//����ڵ�
class CvNode 
{
public:
	//���캯��
	CvNode(){ m_pNextNode = NULL;};

	//��������
	~CvNode(){};

	//�ڵ���Ϣ
	CvMeta m_Meta;

	//ָ����һ���ڵ�
	CvNode *m_pNextNode;
};

class DLL_IN CCV_List
{
public:

	//���캯��
	CCV_List();

	//��������
	virtual ~CCV_List();

	//��ӽڵ�
	BOOL Add(CvMeta *v_pMeta);

	//����ڵ㣬��ǰ�ڵ�ȫ������
	BOOL Insert(int v_intNum,CvMeta *v_pMeta);

	//ɾ���ڵ�
	BOOL Remove(int v_intNum);

	//ɾ�����нڵ�
	BOOL Remove_All();

	//��ȡ�ڵ��ͼԪ��Ϣ
	BOOL Get(int v_intNum,CvMeta *v_pMeta);

	//���ýڵ��ͼԪ��Ϣ
	BOOL Set(int v_intNum,CvMeta *v_pMeta);

	//��ȡ������
	int Get_Length();

	//��������,�Ḵ��ͼ���Ⱥ͸߶�
	BOOL Copy_From(CCV_List* v_pSourceList);

	//��������,��ͷ��ʼ��ȡ�ڵ�
	BOOL Reset();

	// ��ȡ��ǰ�ڵ��ͼԪ��Ϣ,�Զ�ָ����һ���ڵ�
	BOOL Get_Auto(CvMeta *v_pMeta);

	// ���õ�ǰ�ڵ��ͼԪ��Ϣ,�Զ�ָ����һ���ڵ�
	BOOL Set_Auto(CvMeta *v_pMeta);

	// ʹ����ͼԪ�滻һ������ͼԪ
	BOOL Replace(int v_intNum,CvMeta *v_pMeta,int v_ReplacedCount);


public:

	//ָ����һ������
	CCV_List* m_pNextList;

	//ͼ����
	int m_intWidth;

	//ͼ��߶�
	int m_intHeight;

protected:

	//������
	int m_intLength;

	//����ͷ
	CvNode *m_pHead;

	//�����β
	CvNode *m_pEnd;

	//��ǰѡ��Ľڵ�
	CvNode *m_pChosen;
};

//�����г̱�������
typedef CCV_List* RunList;

class DLL_IN CCV_Shape
{
public:

	CCV_Shape(void);

	~CCV_Shape(void);

	//���ƹ��캯��
	CCV_Shape(const CCV_Shape &v_Other);

	//���ظ�ֵ�����
	CCV_Shape& operator= (const CCV_Shape &v_Other);

	//���ú���
public:

	// ��ȡָ���Ҷȵ���״
	BOOL Find(const IPL v_Image,int v_Min = 127,int v_Max = 255);

	// ��ֵͼ��,Ȼ�󱣴��һ����������
	BOOL Threshold_To_Region(const IPL v_Image,int v_Min = 127,int v_Max = 255);

	// ��ֵͼ��,Ȼ�󱣴��һ����������
	BOOL Threshold_To_Region_Roi(const IPL v_Image,int v_intLeft,int v_intTop,int v_intWidth,int v_intHeight,int v_Min = 127,int v_Max = 255);

	// ��ֵͼ��,Ȼ�󱣴��һ����������,֧����ͨ������趨
	BOOL Threshold_To_Region_Roi_Dis(const IPL v_Image,int v_intLeft,int v_intTop,int v_intWidth,int v_intHeight,int v_Min = 127,int v_Max = 255,int v_intDis = 10);

	// ��ֵͼ��,Ȼ�󱣴��һ����������,��������ͼ��
	BOOL Threshold_To_Region_Mask(const IPL v_Image,int v_Min = 127,int v_Max = 255,const IPL v_Mask = NULL);

	// ��ȡ��ͨ��
	BOOL Connection();

	// ��ȡ��ͨ��,֧����ͨ������趨
	BOOL Connection_Dis(int v_intWidth,int v_intHeight);


	// ɸѡ��״
	BOOL Select(CString v_strType,double v_Min,double v_Max);

	// ��ʾ��״������ֵ
	BOOL Show(CString v_strType);

	// ������״,Ĭ��Ϊ����
	BOOL Sort(CString v_strType,BOOL v_bDown = TRUE);

	// �����״�ڲ��Ŀ׶�
	BOOL Fill_Up();

	// �����״�ڲ��Ŀ׶�,ֻ���Ҷ�ֵ��ָ����Χ�ڵ�����
	BOOL Fill_Up_Gray(const IPL v_Image,double v_douOffest = 10.0);

	// ��ȡ͹��
	BOOL Convex();

	// ��ȡ��״���������򣬰���ƽ����Ӿ��Σ���С��Ӿ���,��С���Բ
	BOOL Trans(CString v_strType);

	// ��״�Ƿ�Ϊ��
	BOOL Is_Empty();

	// ��ͼ����ɸѡ���򲿷ֵ�ͼ��,���һ�������Ǳ���ɫ
	BOOL Reduce_Domain(const IPL v_Image,IPL* v_Reduce,CvScalar v_BackColor = CV_RGB(0,0,0));

	// ��͸���������
	BOOL Alpha(const IPL v_Image,double v_Pellucidity = 0.5,CvScalar v_Scalar = CV_RGB(255,0,0));

	// ��͸���������,���ӳߴ����Ź���
	BOOL Alpha_Ex(const IPL v_Image,int v_intSize,double v_Pellucidity = 0.5,CvScalar v_Scalar = CV_RGB(255,0,0));

	// ͨ�����γߴ�ָ�����
	BOOL Partition_Rectangle(int v_intWidth);

	// ��ʽ����״����,��֤���е��г��붼��ͼ��Χ��
	BOOL Format_Run_List();

	//����ͼ��ߴ�
	BOOL Set_Size(int v_intWidth,int v_intHeight);

	//��ȡͼ��ߴ�
	BOOL Get_Size(int *v_intWidth,int *v_intHeight);

	// 8�������任,������
	BOOL Distance_Transform_Chessboard(CCV_Shape &v_Other,double *v_douMaxDis);

	// �Ǽܻ�,��Ҫ����ÿһ����״����
	BOOL Skeleton();

	// �Ǽܻ�,ͨ��ˮƽ����
	BOOL Skeleton_Horizontal();

	//������С������ı���
	BOOL Mini_Area_Quad();

	//��ȡ��С����������ı��ε��ĸ�����,����->����->����->����
	BOOL Get_Mini_Quad(CvPoint **v_pPoint);

	//��ȡ�г������
	int Get_Run_List_Count();

	//���л������ж�
	//�����ROI������ǰ������,����TRUE
	//�����ROI������ǰ������,����FALSE
	BOOL Hit_Or_Miss(int v_intLeft,int v_intTop,int v_intWidth,int v_intHeight,BOOL v_bAble);

	//��ȡ��״����
public:

	// ��ȡ��״���ϵĸ���
	int Get_Count();

	//��ȡͼ����
	int Get_Image_Width();

	//��ȡͼ��߶�
	int Get_Image_Height();

	// ��ȡ��״�����
	BOOL Get_Area(double *v_Area);

	// ��ȡ��״���ܳ�
	BOOL Get_Length(double *v_Length);

	// ��ȡ��״������
	BOOL Get_Gravity(double *v_Row,double *v_Col);

	//��ȡ��������
	BOOL Get_Anisometry(double *v_douAnisometry);

	// ��ȡ��״�����ƽ�о���
	BOOL Get_Parallel_Rect(double *v_MidX,double *v_MidY,double *v_Width,double *v_Height);

	// ��ȡ��״�����ƽ�о���
	BOOL Get_Parallel_Rect(int *v_intTop,int *v_intLeft,int *v_intBottom,int *v_intRight);

	// ��ȡ��ת�Ƕ�
	BOOL Get_Angle(double *v_Angle);

	// ��ȡ��С���εĲ���
	BOOL Get_Mini_Rect(double *v_MidX,double *v_MidY,double *v_Width,double *v_Height,double *v_Angle);

	// ��ȡ��״������ͼ��
	BOOL Get_Region_Image(IPL *v_Image,BOOL v_bColor = FALSE);

	// ��ȡ��״��������Եͼ��
	BOOL Get_Contour_Image(IPL *v_Image,BOOL v_bColor = FALSE);

	// ��ȡ��״�������
	BOOL Get_Region(int *v_pintPointCount,int **v_pintRow,int **v_pintCol);

	// ������״�������
	BOOL Set_Region(int v_pintPointCount,int *v_pintRow,int *v_pintCol,int v_intBkWidth = 1280,int v_intBkHeight = 960);

	// ��ȡ������״��������
	BOOL Get_Contour(int *v_pintPointCount,int **v_pintRow,int **v_pintCol);

	// ��ȡ������״��������
	BOOL Get_Contour3(int *v_pintUpCount,int **v_pintUpRow,int **v_pintUpCol,
		int *v_pintDownCount,int **v_pintDownRow,int **v_pintDownCol,
		int *v_pintLeftCount,int **v_pintLeftRow,int **v_pintLeftCol,
		int *v_pintRightCount,int **v_pintRightRow,int **v_pintRightCol);


	// ��������״�����ȡ����,��Ŵ�0��ʼ
	BOOL Get_Object(CCV_Shape &v_Ohter,int v_intIndex);

	// ��ȡ���������״
	BOOL Get_Max_Area();

	//��ȡ������״�����ض������Զ��
	BOOL Get_Far_Point(double v_douCenterRow,double v_douCenterCol,double *v_douFarRow,double *v_douFarCol);

	//��ȡ�����ƽ���߶�
	BOOL Get_Aver_High(double *v_douHeight);

	// ��ȡ��״��ƽ�����
	BOOL Get_Aver_Width(double *v_douWidth);

	// ��ȡ��״�Ŀ�Ⱦ�����
	BOOL Get_Width_Variance(double *v_douVariance);


	//��ȡ�����ƽ���Ҷ�
	BOOL Get_Aver_Gray(const IPL v_Image,double *v_douAverGray);

	//��ȡ����ı�׼��,������
	BOOL Get_Standard_Deviation(const IPL v_Image,double *v_douStaDev);

	//��ȡ����ı�׼��,ֻͳ�Ʊ�ƽ���Ҷȴ������
	BOOL Get_Standard_Deviation_White(const IPL v_Image,double *v_douStaDev);

	//��ȡ����ı�׼��,ֻͳ�Ʊ�ƽ���Ҷ�С������
	BOOL Get_Standard_Deviation_Black(const IPL v_Image,double *v_douStaDev);

	//��ȡ�����Ķ���,����ж��,ȡ���·��Ǹ�,������
	BOOL Get_Left_Down_Conner(int *v_intRow,int *v_intCol);

	//��ȡ���ҵ�Ķ���,����ж��,ȡ���·��Ǹ�,������
	BOOL Get_Right_Down_Conner(int *v_intRow,int *v_intCol);

	// ��ȡ��Χ�ڵ������,������
	BOOL Get_Range_Left_Conner(int v_intBeginRow,int v_intEndRow,int *v_intCol);

	// ��ȡ��Χ�ڵ����ҵ�,������
	BOOL Get_Range_Right_Conner(int v_intBeginRow,int v_intEndRow,int *v_intCol);

	//��������
public:

	//�ϲ�
	BOOL Union();

	//����
	BOOL Union2(CCV_Shape &v_Other);

	//����,��������뵱ǰһ��
	BOOL Intersection(CCV_Shape &v_Other);

	//�
	BOOL Difference(CCV_Shape &v_Other);

	//����
	BOOL Complement();

	//�ƶ�,�ƶ�֮��һ����Ҫ��ʽ���г�����
	BOOL Move(int v_intRow,int v_intCol);

	//��̬ѧ,��̬ѧ֮��,һ����Ҫ��ʽ���г�����
public:

	//����ṹԪ����
	BOOL Dilation(CvMeta *v_pMeta,int v_MetaCount);

	//����ṹԪ��ʴ
	BOOL Erosion(CvMeta *v_pMeta,int v_MetaCount);

	//��������
	BOOL Dilation_Rect(int v_intWidth,int v_intHeight);

	//���θ�ʴ
	BOOL Erosion_Rect(int v_intWidth,int v_intHeight);

	//Բ������,ֱ��Ϊ����
	BOOL Dilation_Circle(int v_intDiameter);

	//Բ�θ�ʴ,ֱ��Ϊ����
	BOOL Erosion_Circle(int v_intDiameter);

	//���ο�����
	BOOL Opening_Rect(int v_intWidth,int v_intHeight);

	//���α����㣬һ����Ҫ��������״
	BOOL Closing_Rect(int v_intWidth,int v_intHeight);

	//Բ�ο�����,ֱ��Ϊ����
	BOOL Opening_Circle(int v_intDiameter);

	//Բ�α�����,ֱ��Ϊ������һ����Ҫ��������״
	BOOL Closing_Circle(int v_intDiameter);

	//��������
public:

	//������������ƽ�еľ�������
	BOOL Gen_Rect1(int v_intRow1,int v_intCol1,int v_intRow2,int v_intCol2,int v_intBkWidth = 1280,int v_intBkHeight = 960);

	//��������Ƕȵľ�������,��ˮƽ�ҷ���Ϊ0��,��ʱ��Ϊ������,��Χ[0,180),(���ĵ�Ϊ����ʱ,��Ⱥ͸߶�Ϊ����)
	BOOL Gen_Rect2(double v_douRow,double v_douCol,double v_douWidth,double v_douHeight,double v_douAngle,int v_intBkWidth = 1280,int v_intBkHeight = 960);

	//����Բ������
	BOOL Gen_Circle(double v_douCenterX,double v_douCenterY,double v_douRadius,int v_intBkWidth = 1280,int v_intBkHeight = 960);

	//��״����
private:

	// ��ȡ������״������
	BOOL Get_Gravity(RunList v_List,double *v_douRow,double *v_douCol);

	// ��ȡ������״�����
	BOOL Get_Area(RunList v_List,int *v_Result);

	//��ȡ�����ƽ���߶�
	BOOL Get_Aver_High(RunList v_List,double *v_Result);

	//��ȡ�����ƽ�����
	BOOL Get_Aver_Width(RunList v_List,double *v_Result);

	// ��ȡ����Ŀ�Ⱦ�����
	BOOL Get_Width_Variance(RunList v_List,double *v_Result);

	// ��ȡ������״���ܳ�(����������)
	BOOL Get_Length(RunList v_List,double *v_Result);

	// ��ȡ������״��ƽ�п��
	BOOL Get_Parallel_Width(RunList v_List,int *v_Result);

	// ��ȡ������״��ƽ�и߶�
	BOOL Get_Parallel_Height(RunList v_List,int *v_Result);

	// ��ȡ������״���ĸ�����
	BOOL Get_Conner_Point(RunList v_List,int *v_Top,int *v_Bottom,int *v_Left,int *v_Right);

	// ��ȡ������״�������
	BOOL Get_Left_Down_Conner(RunList v_List,int *v_intRow,int *v_intCol);

	// ��ȡ������״�����ҵ�
	BOOL Get_Right_Down_Conner(RunList v_List,int *v_intRow,int *v_intCol);

	// ��ȡ������״�ķ�Χ�ڵ������
	BOOL Get_Range_Left_Conner(RunList v_List,int v_intBeginRow,int v_intEndRow,int *v_intCol);

	// ��ȡ������״�ķ�Χ�ڵ����ҵ�
	BOOL Get_Range_Right_Conner(RunList v_List,int v_intBeginRow,int v_intEndRow,int *v_intCol);

	// ��ȡ������״�Ľ�����
	BOOL Get_Compactness(RunList v_List,double *v_Result);

	// ��ȡ������״�ĸ�������
	BOOL Get_Anisometry(RunList v_List,double *v_Result);

	// ��ȡ������״��Բ�Ķ�
	BOOL Get_Circularity(RunList v_List,double *v_Result);

	// ��ȡ������״�ľ��ζ�
	BOOL Get_Rectangularity(RunList v_List,double *v_Result);

	// ��ȡ������״�ľ��α���
	BOOL Get_Rectangularity_Ex(RunList v_List,double *v_Result);

	// ��ȡ������״��͹��
	BOOL Get_Convexty(RunList v_List,double *v_Result);

	// ��ȡ������״�Ŀ�����
	BOOL Get_Emptiness(RunList v_List,double *v_Result);

	// ��ȡ������״����ת�Ƕ�,��ˮƽ�ҷ���Ϊ0��,��ʱ��Ϊ������,��Χ[-45,45]
	BOOL Get_Angle(RunList v_List,double *v_Result);

	//��ȡ��С���ľ���
	BOOL Get_Mini_Distance(double v_douRow[],double v_douCol[],int v_intCount,int v_intIndex,double *v_Result);

	//��ȡ��С����������ı��ε��������
	BOOL Get_Mini_Quad_Ness(RunList v_List,double *v_Result);

	//��ȡ������״����С����������ı���
	BOOL Get_Mini_Quad(RunList v_List,RunList v_ListResult,CvPoint v_Point[4]);

	//����,������������Ľ���
	BOOL Intersection(RunList v_List,RunList v_List2,RunList v_ListResult);

	//��������
private:

	// �ͷ�����Ŀռ�
	BOOL Release_List(RunList *v_List);

	// ��ȡ������״��������,�޸�Ϊ4����
	BOOL Get_Contour(RunList v_List,RunList v_ListResult);

	// ��ȡ������״��������,8����
	BOOL Get_Contour2(RunList v_List,RunList v_ListResult);

	// ��ȡ������״��������,�޸�Ϊ4����
	BOOL Get_Contour3(RunList v_List,RunList v_ListUp,RunList v_ListDown,RunList v_ListLeft,RunList v_ListRight);

	// ��ȡ�г�����Ĳ���,��������ͼ���ⲿ���г�,��ʱ��ɾ��
	BOOL Complement2(RunList v_List,RunList v_ListResult,int v_intOuterWidth,int v_intOuterHeight);

	// ��ȡ��״�Ĺ�һ����
	BOOL Get_Norma_Moments(RunList v_List,double *v_douM00,double *v_douM01,double *v_douM10,double *v_douM02,double *v_douM11,double *v_douM20);

	// ���㵥����״��͹��
	BOOL Get_Convex(RunList v_List,CvPoint **v_pPoint,int *v_intCount);

	// ���㵥����״���������,����Ҫ�����г���,��ԭ������״�󲢼�
	BOOL Get_Fill(RunList v_List,RunList v_ListResult);

	// ��ȡ������״����С��Ӿ���
	BOOL Get_Mini_Rect(RunList v_List,RunList v_ListResult,double *v_MidX,double *v_MidY,double *v_Width,double *v_Height,double *v_douRad);

	// �г̱��������󲢼�,ʹ�ù鲢����
	BOOL Run_Array_Union(CvMeta *v_pMeta,int v_intCount,int v_intLevel,RunList v_List);

	// ����ͼ�εĶ���,�����г�������
	BOOL Get_Conner_List(CvPoint *v_pPoint,int v_intCount,RunList v_ListResult);

	//��ȡ�������ֱ��һ�㷽��
	BOOL Get_Line(double v_douX1,double v_douY1,double v_douX2,double v_douY2,double *v_douA,double *v_douB,double *v_douC);

private:

	//�г̱���
	RunList m_List;

	//ͼ����,��Find������������
	int m_intWidth;

	//ͼ��߶�,��Find������������
	int m_intHeight;

	//������
	static const int m_intMaxDis = 65535;

	//���������ɫ������
	CvScalar *m_pcvFillColor;

	//��ɫ����
	static const int m_intColorCount = 24;
};


//�ӳ���ת��ģ��
class DLL_IN CWinder_Angle_View
{
public:
	CWinder_Angle_View(void);
	~CWinder_Angle_View(void);

	//��������ֱ���X�Ͳ���λ��X
	BOOL Set_Camera_Resolution(int v_intResolution,int v_intOffsetX);

	//����0Ȧ�����ص��������ص�����ÿ����1mm��������ı仯��
	BOOL Set_Pixel_Dis_Derivative(double v_douPixelDis,double v_douDerivative);

	//���õ�оÿһȦ�ĺ�ȱ仯,��λmm��������
	//Զ�����Ϊ��������������������
	//�������Ϊ�����������������С
	BOOL Set_Prismatic_Layer_Thickness(double v_douThickness);

	//��ȡ�ض�Ȧ�������ص���,�������մ���
	double Get_Chosen_Layer_Pixel_Dis(int v_intTriIndex);

	//��ȡ�ض�Ȧ��,ӳ���ı�Եλ��,�������մ����ͳ�ʼ�ı�Ե����λ��
	double Get_Chosen_Layer_Boder_Pos(int v_intTriIndex,double v_douSrcPos);

private:

	//��������,��λ����
	double m_douOpticalAxis;

	//0Ȧ�����ص���
	double m_douPixelDisBasic;

	//�������ص����ĵ���
	double m_douPixelDisDeriva;

	//��оÿһ��ĺ��
	double m_douLayerThickness;
};

