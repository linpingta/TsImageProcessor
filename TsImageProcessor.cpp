#include "TsImageProcessor.h"

TsImageProcess::TsImageProcess():l(0),h(0)
{
	image = NULL;
}

TsImageProcess::TsImageProcess( unsigned int** _image,unsigned int _w,unsigned int _h):l(_w),h(_h)
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

TsImageProcess::TsImageProcess( unsigned int _w,unsigned int _h):l(_w),h(_h)
{
	image = new unsigned int*[l]();
	for (int i = 0;i < l;++i)
	{
		image[i] = new unsigned int[h]();
	}
}

TsImageProcess::TsImageProcess( string filename )
{
	// TODO
}

TsImageProcess::~TsImageProcess()
{
	for (int i = 0;i < l;++i)
	{
		delete[] image[i];
	}
	delete[] image;
	image = NULL;
	l = 0;
	h = 0;
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
bool TsImageProcess::SetImage( unsigned int** inputImage,unsigned int _w,unsigned int _h)
{
	if (l != _w || h != _h)
	{
		return false;
	}

	for (int i = 0;i < l;++i)
	{
		for (int j = 0;j < h;++j)
		{
			image[i][j] = inputImage[i][j];
		}
	}
	return true;
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