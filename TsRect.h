#ifndef _H_TSRECT_INCLUDED_
#define _H_TSRECT_INCLUDED_

#include "TsPoint.h"
//#include "TsCenterRect.h"

//class TsCenterRect;

template<class T>
class TsRect
{
public:
	TsRect();
	TsRect(TsPoint<T>,T,T);
	void SetRect(TsPoint<T>,T,T);
	void SetLeftUpCorner(TsPoint<T>);
	void SetLength(T);
	void SetHeight(T);
	TsPoint<T> GetLeftUpCorner();
	T GetLength();
	T GetHeight();
	//TsCenterRect<T> TransferToCenterRect();
private:
	TsPoint<T> leftUpCorner;
	T length;
	T height;
};

template<class T>
TsRect<T>::TsRect()
{
	;
}

template<class T>
TsRect<T>::TsRect(TsPoint<T> _leftUpCorner,T _l,T _h)
{
	leftUpCorner = _leftUpCorner;
	length = _l;
	height = _h;
}

template<class T>
void TsRect<T>::SetRect( TsPoint<T> leftUpCorner,T length,T height)
{
	this->leftUpCorner = leftUpCorner;
	this->length = length;
	this->height = height;
}

template<class T>
T TsRect<T>::GetHeight()
{
	return height;
}

template<class T>
T TsRect<T>::GetLength()
{
	return length;
}

template<class T>
TsPoint<T> TsRect<T>::GetLeftUpCorner()
{
	return leftUpCorner;
}

template<class T>
void TsRect<T>::SetHeight( T height )
{
	this->height = height;
}

template<class T>
void TsRect<T>::SetLength( T length )
{
	this->length = length;
}

template<class T>
void TsRect<T>::SetLeftUpCorner( TsPoint<T> leftUpCorner )
{
	this->leftUpCorner = leftUpCorner;
}

//template<class T>
//TsCenterRect<T> TsRect<T>::TransferToCenterRect()
//{
//	TsCenterRect<T> returnValue;
//	returnValue.SetCenter(leftUpCorner.x + length / 2,leftUpCorner.y + height / 2);
//	returnValue.SetLength(length);
//	returnValue.SetHeight(height);
//	return returnValue;
//}

#endif