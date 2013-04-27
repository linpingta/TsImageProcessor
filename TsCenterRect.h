#ifndef _TSCENTERRECT_
#define _TSCENTERRECT_

#include "TsPoint.h"
//#include "TsRect.h"

//class TsRect;

template<class T>
class TsCenterRect
{
public:
	void SetRect(TsPoint<T>,T,T);
	void SetCenter(TsPoint<T>);
	void SetLength(T);
	void SetHeight(T);
	TsPoint<T> GetCenter();
	T GetLength();
	T GetHeight();
	//TsRect<T> TransferToRect();
private:
	TsPoint<T> center;
	T length;
	T height;
};

template<class T>
void TsCenterRect<T>::SetRect( TsPoint<T> center,T length,T height)
{
	this->center = center;
	this->length = length;
	this->height = height;
}

template<class T>
T TsCenterRect<T>::GetHeight()
{
	return height;
}

template<class T>
T TsCenterRect<T>::GetLength()
{
	return length;
}

template<class T>
TsPoint<T> TsCenterRect<T>::GetCenter()
{
	return center;
}

template<class T>
void TsCenterRect<T>::SetHeight( T height )
{
	this->height = height;
}

template<class T>
void TsCenterRect<T>::SetLength( T length )
{
	this->length = length;
}

template<class T>
void TsCenterRect<T>::SetCenter( TsPoint<T> center )
{
	this->center = center;
}

//template<class T>
//TsRect<T> TsCenterRect<T>::TransferToRect()
//{
//	TsRect<T> returnValue;
//	returnValue.SetLeftUpCorner(center.x - length / 2,center.y - height / 2);
//	returnValue.SetLength(length);
//	returnValue.SetHeight(height);
//	return returnValue;
//}

#endif