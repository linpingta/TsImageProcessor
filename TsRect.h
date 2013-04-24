#ifndef _H_TSRECT_INCLUDED_
#define _H_TSRECT_INCLUDED_

#include "TsPoint.h"

template<class T>
class TsRect
{
public:
	void SetRect(TsPoint<T>,T,T);
	void SetLeftUpCorner(TsPoint<T>);
	void SetLength(T);
	void SetHeight(T);
	TsPoint<T> GetLeftUpCorner();
	T GetLength();
	T GetHeight();
private:
	TsPoint<T> leftUpCorner;
	T length;
	T height;
};

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

#endif