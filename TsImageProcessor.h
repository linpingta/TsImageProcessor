#ifndef _H_TSIMAGEPROCESSOR_INCLUDED_
#define _H_TSIMAGEPROCESSOR_INCLUDED_

#include <string>
#include <list>
#include <queue>
using namespace std;

#include "TsFunction.h"
#include "TsPoint.h"
#include "TsRect.h"
#include "TsCenterRect.h"
#include "TsSquareRect.h"
#include "TsObjectProbabilityInfo.h"

/************************************************************************/
/* TsImageProcess                                                                     
*  target : Image Process Of Gray Image , coming from project of object tracking
*  author : linpingta  chut1987@gmail.com 
*  version : 1.0            
*/
/************************************************************************/

class TsImageProcess
{
private:
	unsigned int** image;		 // image source
	unsigned int l;              // image length
	unsigned int h;				 // image height
	unsigned int allocateL;      // store image length for deletion
	unsigned int allocateH;      // store image height for deletion
public:
	TsImageProcess();
	TsImageProcess(unsigned int**,unsigned int,unsigned int);
	TsImageProcess(unsigned int,unsigned int);
	TsImageProcess(string filename);
	~TsImageProcess();
public:
	void SetImage(unsigned int**,unsigned int,unsigned int); // set image value with image has already allocated
	void SetImageWithRect(TsImageProcess,TsRect<int>);
	void SetBlockImageWithSingleValue(unsigned int,unsigned int,unsigned int);
	void SetPointValueInImage(unsigned int,unsigned int,unsigned int);
	unsigned int** GetRectImage(TsRect<int>);
	TsImageProcess& GetRectImageProcessor(TsRect<int>);
	unsigned int** GetImage();
	unsigned int GetLength() const;
	unsigned int GetHeight() const;
	void LoadBmp(string);
	void LoadMatrix(string);
	void SaveBmp(string,int);
	void MedianFilter();
	void BinaryImage(int);
	int GetThresholdWithOtsu();
	void SetImageLabel(int m,int n,queue<TsPoint<int>>& position,int label,int& count,float& seaDistanceForAll,float& grayForAll );
	TsSquareRect<int> GetBoundaryFromBinaryImage(int);
	TsPoint<int> GetImageGrayBoundary();
};

#endif