#include "TsImageProcessor.h"
#include "TsConstantVariable.h"
#include "TsObjectProbabilityInfo.h"

#include <fstream>
#include <list>
#include <queue>
using namespace std;

#define MFC_SAVE_BMP
#ifdef MFC_SAVE_BMP
#include <afx.h>
#include <shlwapi.h>
#pragma comment(lib,"Shlwapi.lib") 
#endif

TsImageProcess::TsImageProcess():l(0),h(0),allocateL(l),allocateH(h)
{
	image = NULL;
}

TsImageProcess::TsImageProcess( unsigned int** _image,unsigned int _w,unsigned int _h):l(_w),h(_h),allocateL(l),allocateH(h)
{
	image = new unsigned int*[l]();
	for (int i = 0;i < l;++i)
	{
		image[i] = new unsigned int[h]();
	}

	for (int i = 0;i < l;++i)
	{
		for (int j = 0;j < h;++j)
		{
			image[i][j] = _image[i][j];
		}
	}
}

TsImageProcess::TsImageProcess( unsigned int _w,unsigned int _h):l(_w),h(_h),allocateL(l),allocateH(h)
{
	image = new unsigned int*[l]();
	for (int i = 0;i < l;++i)
	{
		image[i] = new unsigned int[h]();
	}
}

TsImageProcess::TsImageProcess( string filename )
{
	LoadBmp(filename);
}

TsImageProcess::~TsImageProcess()
{
	if (image)
	{
		for (int i = 0;i < allocateL;++i)
		{
			delete[] image[i];
		}
		delete[] image;
		image = NULL;
	}

	l = 0;
	h = 0;
	allocateL = l;
	allocateH = h;
}

void TsImageProcess::Init(unsigned int _l,unsigned int _h)
{
	l = _l;
	h = _h;
	allocateL = l;
	allocateH = h;
	image = new unsigned int*[l]();
	for (int i = 0;i < l;++i)
	{
		image[i] = new unsigned int[h]();
	}
}

void TsImageProcess::Release()
{
	if (image)
	{
		for (int i = 0;i < allocateL;++i)
		{
			delete[] image[i];
		}
		delete[] image;
		image = NULL;
	}

	l = 0;
	h = 0;
	allocateL = l;
	allocateH = h;
}

//************************************
// Method:    SetImage
// FullName:  TsImageProcess::SetImage
// Access:    public 
// Returns:   bool
// Qualifier: because TsImageProcess a(I1,w1,h1) will be called every interval so it will 
// call new ** many times and it costs a lot of time.
// Parameter: unsigned int ** inputImage
// Parameter: unsigned int _w
// Parameter: unsigned int _h
//************************************
void TsImageProcess::SetImage( unsigned int** inputImage,unsigned int _l,unsigned int _h)
{
	//image = inputImage;
	l = _l;
	h = _h;
	for (int i = 0;i < l;++i)
	{
		for (int j = 0;j < h;++j)
		{
			image[i][j] = inputImage[i][j];
		}
	}
}


//************************************
// Method:    GetRectImage
// FullName:  GetRectImage
// Access:    public 
// Returns:   unsigned int**
// Qualifier: Get part image from original image, while user should be aware about memory release of the return value.
// Parameter: TsRect<int> rectRegion
//************************************
unsigned int** TsImageProcess::GetRectImage(TsRect<int> rectRegion)
{
	int partL = rectRegion.GetLength();
	int partH = rectRegion.GetHeight();
	TsPoint<int> tmpPoint;
	tmpPoint = rectRegion.GetLeftUpCorner();

	if (partL < 0 || partH < 0)
	{
		return NULL;
	}

	if (TsFunction::BeInLimitaion<int>(tmpPoint.x,0, l - 1) == false ||
		TsFunction::BeInLimitaion<int>(tmpPoint.y,0, h - 1) == false)
	{
		return NULL;
	}

	unsigned int** partImage = new unsigned int*[partL]();
	for (int i = 0;i < partL;++i)
	{
		partImage[i] = new unsigned int[partH]();
	}
	for (int i = 0;i < partL;++i)
	{
		for (int j = 0;j < partH;++j)
		{
			partImage[i][j] = image[tmpPoint.x + i][tmpPoint.y + j];
		}
	}

	return partImage;
}

unsigned int TsImageProcess::GetLength() const
{
	return l;
}

unsigned int TsImageProcess::GetHeight() const
{
	return h;
}

unsigned int** TsImageProcess::GetImage()
{
	return image;
}

//************************************
// Method:    LoadBmp
// FullName:  TsImageProcess::LoadBmp
// Access:    public 
// Returns:   void
// Qualifier: Load bmp file with filename
// Parameter: string filename
//************************************
void TsImageProcess::LoadBmp(string filename)
{
	// TODO
}

//************************************
// Method:    LoadMatrix
// FullName:  TsImageProcess::LoadMatrix
// Access:    public 
// Returns:   void
// Qualifier: Load bmp file matrix from txt.
// Parameter: string filename
// Parameter: unsigned int l
// Parameter: unsigned int h
//************************************
void TsImageProcess::LoadMatrix(string filename)
{
	if (l == 0 || h == 0)
	{
		return;
	}

	ifstream fin;
	fin.open(filename.c_str());

	for (int i = 0;i < l;++i)
	{
		for (int j = 0;j < h;++j)
		{
			fin >> image[i][j];
		}
	}
	fin.close();
}

//************************************
// Method:    SaveBmp
// FullName:  TsImageProcess::SaveBmp
// Access:    public 
// Returns:   void
// Qualifier: Save image to bmpFilename and label it with countNum
// Parameter: string bmpFilename
// Parameter: int countNum
//************************************
void TsImageProcess::SaveBmp(string bmpFilename,int countNum)
{
#ifdef MFC_SAVE_BMP
	l = l/4;
	l = l*4;

	BYTE *pBits = new BYTE[l * h];

	char aCurrentDirectory[200];
	GetCurrentDirectory(200,aCurrentDirectory);
	string strCurrentDirectory = aCurrentDirectory;
	strCurrentDirectory.append("/");
	strCurrentDirectory.append(bmpFilename);

	CString str1;
	str1.Format(_T("%d.bmp"),countNum);   
	CString str = strCurrentDirectory.c_str();
	str += str1;

	CString strTest1;
	strTest1.Format(_T("%d.txt"),countNum);
	CString strTest = strCurrentDirectory.c_str();
	strTest += strTest1;

	for (int i = 0; i < l; ++i)
	{
		for (int j = 0; j < h; j++)
		{
			pBits[j * l + i] = image[l - i - 1][h - j - 1];
		}
	}

	BITMAPFILEHEADER hdr;   
	BITMAPINFOHEADER bih;   
	RGBQUAD   rgbQuad[256];         

	bih.biBitCount=8;   
	bih.biClrImportant=0;   
	bih.biClrUsed=0;   
	bih.biCompression=BI_RGB;   
	bih.biHeight=h;   
	bih.biPlanes=1;   
	bih.biSize=sizeof(BITMAPINFOHEADER);   
	bih.biSizeImage=0;   
	bih.biWidth=l;   
	bih.biXPelsPerMeter=0;   
	bih.biYPelsPerMeter=0;   

	for(int i=0;   i<256;   i++)   
	{   
		rgbQuad[i].rgbBlue  =   (BYTE)i;   
		rgbQuad[i].rgbGreen =   (BYTE)i;   
		rgbQuad[i].rgbRed   =   (BYTE)i;   
		rgbQuad[i].rgbReserved   =   0;   
	}   

	//Fill   in   the   fields   of   the   file   header     
	hdr.bfType=   (WORD)0x4D42; //   is   always   "BM"   
	hdr.bfSize=   (DWORD)(sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)        
		+ sizeof(RGBQUAD)*256 + h*l);   
	hdr.bfReserved1   =   0;   
	hdr.bfReserved2   =   0;   
	hdr.bfOffBits=   (DWORD)(sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)   
		+sizeof(RGBQUAD)*256);   

	CFile   mfile;   
	if (mfile.Open( str,   CFile::modeWrite|CFile::modeCreate) == FALSE)
	{
		delete []pBits;
		pBits = NULL;
		return;
	}

	//   Write   the   file   header     
	mfile.Write(   &hdr,   sizeof(hdr)   );			   //写文件头   
	mfile.Write(   &bih,   sizeof(bih)   );			   //写信息头   
	mfile.Write((LPSTR)rgbQuad,sizeof(RGBQUAD)*256);   //写调色板   
	mfile.Write(pBits,h * l);                          //写数据   
	mfile.Close();   

	delete []pBits;
	pBits = NULL;
#endif
}

void TsImageProcess::MedianFilter()
{
	int i,j,k,r,q,p;
	int s[9],temp;
	for(i = 0;i < l;i++)
		for(j = 0;j < h;j++)
			if ((i == 0)||(j == 0)||(i == l-1)||(j == h-1))		 //图像边缘处理
				image[i][j] = 0;
			else
			{ 
				for(k = -1;k <= 1;k++)                        //在3*3模版内作中值滤波
					for(r = -1;r <= 1;r++)
						s[(k + 1) * 3 + r + 1]=image[i + k][j + r];
				for(q = 0;q < 9;q++)
					for(p = 0;p < q;p++)
						if(s[q] <= s[p]) 
						{
							temp = s[q];
							s[q] = s[p];
							s[p] = temp;
						}
						image[i][j] = s[4];              //取中间值
			}
}

TsImageProcess& TsImageProcess::GetRectImageProcessor( TsRect<int> inputRect )
{
	unsigned int** tmpImage = GetRectImage(inputRect);
	unsigned int length = inputRect.GetLength();
	unsigned int height = inputRect.GetHeight();
	TsImageProcess returnValue;
	returnValue.SetImage(tmpImage,length,height);
	return returnValue; 
}

void TsImageProcess::BinaryImage( int threshold )
{
	for (int i = 0;i < l;++i)
	{
		for (int j = 0;j < h;++j)
		{
			image[i][j] = (image[i][j] > threshold) ? TsConstantVariable::kMaxGrayValue : TsConstantVariable::kMinGrayValue;
		}
	}
}

//************************************
// Method:    GetThresholdWithOtsu
// FullName:  TsImageProcess::GetThresholdWithOtsu
// Access:    public 
// Returns:   int
// Qualifier: Get threshold of current image
//************************************
int TsImageProcess::GetThresholdWithOtsu()
{
	float Weight_All=0,Mean_All = 0;	// 图像总重量
	float Weight_b=0,Weight_f;			// Otsu的背景和前景比重
	float Mean_b=0,Mean_f=0;			// Otsu的前景和背景的均值
	float tempS,maxS=0;					// 当前类间方差，最大类间方差
	int maxThreshold = 0;					// 取得最大类间方差时候的阈值
	int *temphisto;						// 直方图
	temphisto = new int[256];
	/************************************************************************/
	/* 直方图统计		                                                    */
	/************************************************************************/
	for(int i = 0;i<256;i++)
	{
		temphisto[i] = 0;
	}	// 直方图清零

	for (int i =0;i<l;i++)
	{
		for (int j = 0;j<h;j++)
		{
			if (image[i][j] > 255 || image[i][j] < 0)
			{
				continue;
			}
			temphisto[image[i][j]]++;	// 直方图对应位置+1
		}
	}
	for (int i = 0;i<256;i++)		// 统计直方图总重量
	{
		Weight_All+=temphisto[i];
		Mean_All+=i*temphisto[i];
	}
	/************************************************************************/
	/* Otsu方法：最大类间方差法计算                                         */
	/************************************************************************/
	for(int i =0 ;i < TsConstantVariable::kMaxGrayValue;i++)			// 注意，阈值实际上是i+1
	{
		// 计算当前阈值下的最大类间方差
		Weight_b += temphisto[i];		// 每次只增加一个当前的值，就可以获得背景重量(不知比重)
		Weight_f = Weight_All-Weight_b;

		Mean_b += i*temphisto[i];
		Mean_f = Mean_All-Mean_b;

		tempS = (Weight_b/Weight_All)*(Weight_f/Weight_All)*(Mean_b/Weight_b-Mean_f/Weight_f)*(Mean_b/Weight_b-Mean_f/Weight_f);
		if (tempS>maxS)
		{
			maxThreshold = i+1;
			maxS = tempS;
		}
	}
	delete []temphisto;
	return maxThreshold;
}

void TsImageProcess::SetImageLabel(int m,int n,queue<TsPoint<int>>& position,int label,int& count,float& seaDistanceForAll,float& grayForAll )
{
		seaDistanceForAll = 0;
		grayForAll = 0.0;
		count = 0;

		while (!position.empty())
		{
			position.pop();
		}

		image[m][n] = label;
		position.push(TsPoint<int>(m,n));

		TsPoint<int> tmpPosition;

		while (!position.empty())
		{
			tmpPosition = position.front();
			position.pop();
			++count;

			// 考虑当前元素的上下左右
			if (tmpPosition.x > 0 && image[tmpPosition.x - 1][tmpPosition.y] == TsConstantVariable::kMaxGrayValue)
			{
				position.push(TsPoint<int>(tmpPosition.x - 1,tmpPosition.y));
				image[tmpPosition.x - 1][tmpPosition.y] = label;
			}
			if (tmpPosition.x < l - 1 && image[tmpPosition.x + 1][tmpPosition.y] == TsConstantVariable::kMaxGrayValue)
			{
				position.push(TsPoint<int>(tmpPosition.x + 1,tmpPosition.y));
				image[tmpPosition.x + 1][tmpPosition.y] = label;
			}
			if (tmpPosition.y > 0 && image[tmpPosition.x][tmpPosition.y - 1] == TsConstantVariable::kMaxGrayValue)
			{
				position.push(TsPoint<int>(tmpPosition.x,tmpPosition.y - 1));
				image[tmpPosition.x][tmpPosition.y - 1] = label;
			}
			if (tmpPosition.y < h - 1 && image[tmpPosition.x][tmpPosition.y + 1] == TsConstantVariable::kMaxGrayValue)
			{
				position.push(TsPoint<int>(tmpPosition.x,tmpPosition.y + 1));
				image[tmpPosition.x][tmpPosition.y + 1] = label;
			}

			seaDistanceForAll += abs(tmpPosition.y);
			grayForAll += image[tmpPosition.x][tmpPosition.y];
		}
}

TsSquareRect<int> TsImageProcess::GetBoundaryFromBinaryImage(int label)
{
	TsSquareRect<int> boundary;

	int minX = l - 1,maxX = 0,minY = h - 1, maxY = 0;
	for (int i = 0;i < l;++i)
	{
		for (int j = 0;j < h;++j)
		{
			if (image[i][j] == label && i < minX) 
			{
				minX = i;
			}

			if (image[i][j] == label && i > maxX)
			{
				maxX = i;
			}
		}
	}

	for (int j = 0;j < h;++j)
	{
		for (int i = 0;i < l;++i)
		{
			if (image[i][j] == label && j < minY) 
			{
				minY = j;
			}

			if (image[i][j] == label && j > maxY)
			{
				maxY = j;
			}
		}
	}

	boundary.SetRect(minX,maxX,minY,maxY);
	return boundary;
}

//************************************
// Method:    SetImageWithRect
// FullName:  TsImageProcess::SetImageWithRect
// Access:    public 
// Returns:   void
// Qualifier: Get rectRegion from originalImage
// Parameter: TsImageProcess originalImage
// Parameter: TsRect<int> rectRegion
//************************************
void TsImageProcess::SetImageWithRect( TsImageProcess originalImageProcessor,TsRect<int> rectRegion)
{
	l = rectRegion.GetLength();
	h = rectRegion.GetHeight();
	TsPoint<int> leftUpCorner = rectRegion.GetLeftUpCorner();
	unsigned int** originalImage = originalImageProcessor.GetImage();
	for (int i = 0;i < l;++i)
	{
		for (int j = 0;j < h;++j)
		{
			image[i][j] = originalImage[i + leftUpCorner.x][j + leftUpCorner.y];
		}
	}
}

void TsImageProcess::SetBlockImageWithSingleValue( unsigned int value,unsigned int partLength,unsigned int partHeight )
{
	l = partLength;
	h = partHeight;
	for (int i = 0;i < l;++i)
	{
		for (int j = 0;j < h;++j)
		{
			image[i][j] = value;
		}
	}
}

TsPoint<int> TsImageProcess::GetImageGrayBoundary()
{
	int minGrayValue = TsConstantVariable::kMaxGrayValue;
	int maxGrayValue = 0;

	for (int i = 0;i < l;++i)
	{
		for (int j = 0;j < h;++j)
		{
			if (image[i][j] < 0 || image[i][j] > TsConstantVariable::kMaxGrayValue)
			{
				continue;
			}

			if (minGrayValue > image[i][j])
			{
				minGrayValue = image[i][j];
			}
			if (maxGrayValue < image[i][j])
			{
				maxGrayValue = image[i][j];
			}
		}
	}

	return TsPoint<int>(minGrayValue,maxGrayValue);
}

void TsImageProcess::SetPointValueInImage( unsigned int value,unsigned int m,unsigned int n)
{
	if (!TsFunction::BeInLimitaion<int>(m,0,l - 1) ||
		!TsFunction::BeInLimitaion<int>(n,0,h - 1))
	{
		return;
	}

	image[m][n] = value;
}


