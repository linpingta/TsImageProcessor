#ifndef _H_TSIMAGEPROCESSOR_INCLUDED_
#define _H_TSIMAGEPROCESSOR_INCLUDED_

#include <string>
using namespace std;

#include "TsFunction.h"
#include "TsPoint.h"
#include "TsRect.h"

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
	unsigned int l;              // image width
	unsigned int h;				 // image height
public:
	TsImageProcess();
	TsImageProcess(unsigned int**,unsigned int,unsigned int);
	TsImageProcess(unsigned int,unsigned int);
	TsImageProcess(string filename);
	~TsImageProcess();
public:
	bool SetImage(unsigned int**,unsigned int,unsigned int); // set image value with image has already allocated
	unsigned int** GetRectImage(TsRect<int>);
};

class A{};



#endif