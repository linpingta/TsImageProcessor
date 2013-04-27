#ifndef _H_TSIMAGEPROCESSOR_INCLUDED_
#define _H_TSIMAGEPROCESSOR_INCLUDED_

#include <string>
#include <list>
using namespace std;

#include "TsFunction.h"
#include "TsPoint.h"
#include "TsRect.h"
#include "TsCenterRect.h"
#include "TsObjectProbabilityInfo.h"

/************************************************************************/
/* TsImageProcess                                                                     
*  target : Image Process Of Gray Image , coming from project of object tracking
*  author : linpingta  chut1987@gmail.com 
*  version : 1.0            
*/
/************************************************************************/

class A;

class TsImageProcess
{
private:
	unsigned int** image;		 // image source
	unsigned int l;              // image length
	unsigned int h;				 // image height
public:
	TsImageProcess();
	TsImageProcess(unsigned int**,unsigned int,unsigned int);
	TsImageProcess(unsigned int,unsigned int);
	TsImageProcess(string filename);
	~TsImageProcess();
public:
	void SetImage(unsigned int**,unsigned int,unsigned int); // set image value with image has already allocated
	unsigned int** GetRectImage(TsRect<int>);
	TsImageProcess& GetRectImageProcessor(TsRect<int>);
	unsigned int** GetImage();
	unsigned int GetLength();
	unsigned int GetHeight();
	void LoadBmp(string);
	void LoadMatrix(string);
	void SaveBmp(string,int);
	void MedianFilter();
	void BinaryImage(int);
	int GetThresholdWithOtsu();
	list<TsObjectProbabilityInfo> GetLinkObjectsFromImage(int,int);
};

class A{};



#endif