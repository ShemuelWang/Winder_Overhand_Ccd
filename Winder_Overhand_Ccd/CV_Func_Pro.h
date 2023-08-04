#pragma once

#pragma comment(lib, "CV_Func_Pro.lib")

#ifndef DLL_IN
#define DLL_IN _declspec(dllimport)
#endif

#ifndef ULONG_PTR
#define ULONG_PTR ULONGLONG
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment(lib, "gdiplus.lib")
#endif

#ifndef PI
#define PI 3.14159265358979
#endif

class IplImagePro
{
public:
	IplImagePro(){imageData = NULL;};
	~IplImagePro(){};
public:
	int nChannels;
	int width;
	int height;
	int widthStep;
	BYTE *imageData;
	BYTE **at;
};
typedef IplImagePro* IPL;

struct CvScalar
{
	int val[3];
};
CvScalar DLL_IN cvScalar( int val0,int val1 = 0,int val2 = 0);
#define CV_RGB( r, g, b )  cvScalar( (b), (g), (r))
BOOL DLL_IN Release_Image(IPL *v_pImage);
BOOL DLL_IN Create_Image(IPL *v_pImage,int v_intWidth,int v_intHeight,int v_intChannels);
BOOL DLL_IN Create_Image(IPL *v_pImage,const IPL v_Format);
BOOL DLL_IN Read_Image(IPL *v_pImage,LPCSTR v_strPath = "");
BOOL DLL_IN Write_Image(const IPL v_Image,LPCSTR  v_strPath);
BOOL DLL_IN Copy_Image(const IPL v_Image,IPL* v_pCloneImage);
BOOL DLL_IN Rgb_To_Gray(const IPL v_Rgb,IPL *v_pGray);
BOOL DLL_IN Gray_To_Rgb(const IPL v_Gray,IPL *v_pRgb);
BOOL DLL_IN Access_Channel(const IPL v_Image,IPL *v_pChannel,int v_intNum);
BOOL DLL_IN Set_Color(const IPL v_Image,CvScalar v_bkColor = CV_RGB(0,0,0));
BOOL DLL_IN ROI(IPL v_Image, IPL *v_pROI,int v_intLeft,int v_intTop,int v_intWidth,int v_intHeight);
BOOL DLL_IN Zoom(const IPL v_Image, IPL *v_pTrans,double v_douScaleX = 0.5,double v_douScaleY = 0.5);
BOOL DLL_IN Pyr_Up(const IPL v_Image, IPL *v_pPyr);
BOOL DLL_IN Pyr_Up(const IPL v_Image, IPL *v_pPyr,int v_intTop,int v_intHeight);
BOOL DLL_IN Rotate180(const IPL v_Image,IPL *v_Rotate);
BOOL DLL_IN FlipX(const IPL v_Image,IPL *v_Flip);
BOOL DLL_IN Copy_To_Block(const IPL v_SrcImage,const IPL v_DstImage,int v_intRow,int v_intCol);
BOOL DLL_IN Add_Image(const IPL v_Image,int v_intAdd, IPL *v_pResult);
BOOL DLL_IN Get_Avge_Gray(const IPL v_Image,int v_intLeft,int v_intTop,int v_intWidth,int v_intHeight,double *v_douAvge,double *v_douSharp);
BOOL DLL_IN Check_Aveg_Gray_In_Range(IPL v_Image,int v_intLeft,int v_intTop,int v_intWidth,int v_intHeight,int v_intDir,int v_intTransition,double v_douChosen,int v_intShift,int v_intMinGray,int v_intMaxGray);
BOOL DLL_IN Calculate_Average_Point(double *v_pdouCoor,int v_intCount,double *v_douAver);


//��ȡһά��Ե,ֻ���ڻ�ȡƽ�������ҰX�����ƽ�������ҰY��ı�Ե
//����v_Image������ͼ��,��ͨ��
//����v_intLeft:���������
//����v_intTop :���������
//����v_intWidth:������
//����v_intHeight:����߶�
//����v_intDir:�ұߵķ���,0=�����ң�1=���ҵ���2=���ϵ��£�3=���µ���
//����v_intTransition:�ұߵļ���,1=�ڵ��ף�2=�׵���
//����v_intAmpThresh:��Ե��С�Աȶ�
//����v_intEdgeRate:��Ե��ͱ���
//����v_douMinSroce:��Ե�������С����
//����v_intSpace:�ұߵļ��,ֻ��ȡ������Ĳ��ֱ�Ե��
//����v_intNearSize:�����ĸ���
//����v_intVagueSize:ģ�������ߴ�
BOOL DLL_IN Measure_Postin(IPL v_Image,int v_intLeft,int v_intTop,int v_intWidth,int v_intHeight,int v_intDir,int v_intTransition,int v_intAmpThresh,int v_intEdgeRate,double v_douMinSroce,int v_intNearSize,double *v_douRet,int v_intSpace = 4,int v_intVagueSize = 0);
BOOL DLL_IN Measure_Postin_Ex(IPL v_Image,int v_intLeft,int v_intTop,int v_intWidth,int v_intHeight,int v_intDir,int v_intTransition,int v_intAmpThresh,int v_intEdgeRate,double v_douMinSroce,int v_intNearSize,double *v_douRet,int v_intSpace,int v_intVagueSize,int v_intGrayDiff,int v_intAreaSize,double v_douSimilar);

//������άֱ��,���ϵ���,0=Ĭ�ϱ�Ե(��Ҫ�޸�Ϊƽ���Աȶ�����,���ǵ�������),1=��һ����Ե,2=���һ����Ե
BOOL DLL_IN Measure_Slope_TB(IPL v_Image,int v_intLeft,int v_intTop,int v_intWidth,int v_intHeight,int v_intTransition,int v_intAmpThresh,int v_intEdgeRate,double v_douMinSroce,int v_intNearSize,double *v_douLineA,double *v_douLineB,double *v_douLineC,int v_intSpace,int v_intVagueSize,double v_douStandardAngle,int v_intChosenLine = 0);


void DLL_IN Draw_Text(const IPL v_Image,CString v_strText,UINT v_TextSize = 20,CvScalar v_Color = CV_RGB(255,0,0),int v_intCoorX = 0,int v_intCoorY = 0);
void DLL_IN Draw_Line(const IPL v_Image,int v_intX1,int v_intY1,int v_intX2,int v_intY2,int v_intThinkness = 1,CvScalar v_Color = CV_RGB(255,0,0));
void DLL_IN Draw_Circle(const IPL v_Image,double v_douCenterX,double v_douCenterY,double v_douRadius,int v_intThinkness = 1,CvScalar v_Color = CV_RGB(255,0,0));
void DLL_IN Draw_Rect(const IPL v_Image,int v_intX,int v_intY,int v_intWidth,int v_intHeight,int v_intThinkness = 1,CvScalar v_Color = CV_RGB(255,0,0));
void DLL_IN Draw_Rect2(const IPL v_Image,double v_douMidX,double v_douMidY,double v_douWidth,double v_douHeight,double v_douAngle = 0,int v_intThinkness = 1,CvScalar v_Color = CV_RGB(255,0,0));
void DLL_IN Draw_Point(const IPL v_Image,double *v_douX,double *v_douY,int v_intCount,CvScalar v_Color = CV_RGB(255,0,0));


class  DLL_IN CImage_Bmp
{
public:
	CImage_Bmp(void);
	~CImage_Bmp(void);
	BOOL Open_File(LPCSTR v_strPath);
	BOOL Open_File();
	BOOL Save_File(LPCSTR v_strPath,BYTE *v_pImageData,int v_intWidth,int v_intHeight,int v_intWidthStep,int v_intChannels);
	BYTE* Get_Image_Data();
	int Get_Width();
	int Get_Width_Setp();
	int Get_Height();
private:
	tagBITMAPFILEHEADER m_FileHeader;
	tagBITMAPINFOHEADER m_InfoHeader;
	BYTE *m_pImageData;
	int m_intWidthStep;
};