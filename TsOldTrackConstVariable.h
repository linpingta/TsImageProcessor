#ifndef _TSOLDTRACKCONSTVARIABLE_H_INCLUDED_
#define _TSOLDTRACKCONSTVARIABLE_H_INCLUDED_

static class TsOldTrackConstVariable{
public:
	static const int kLine = 512;
	static const float kMaxDeltaProb;
	static const float kStandardLengthToWidth;
	static const float kStandardAreaRatio;
	static const int kMaxGrayValue;
	static const float PI;
};

const float TsOldTrackConstVariable::kMaxDeltaProb = 3.0;
const float TsOldTrackConstVariable::kStandardLengthToWidth = 5.0;
const float TsOldTrackConstVariable::kStandardAreaRatio = static_cast<float>(1.0 / 3);
const int TsOldTrackConstVariable::kMaxGrayValue = 255;
const float TsOldTrackConstVariable::PI = 3.1415926;

#endif
