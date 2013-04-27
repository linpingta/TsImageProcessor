#ifndef _OBJECTPROBABILITYINFO_
#define _OBJECTPROBABILITYINFO_

#include "TsPoint.h"
#include "TsSquareRect.h"

struct TsProbability
{
	float probability;
	float areaProbability;
	float seaSurfaceProbability;
	float lengthToWidthProbability;
	float colorProbability;
};

struct TsObjectProbabilityInfo
{
	TsProbability probInfo;
	TsSquareRect<int> targetInfo;
	TsSquareRect<int> targetRealInfo;

	float areaEmptyToFull;
	float lengthToWidth;
	float seaSurfaceDistance;
	float averageGray;	
	TsPoint<int> grayBoundary;

	int count;
	int threshold;
	int k;
};

#endif