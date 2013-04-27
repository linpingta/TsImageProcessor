#ifndef _TSTRACKHISTORYINFO
#define _TSTRACKHISTORYINFO

struct TsTrackHistoryInfo
{
	int centerX;    // 历史信息中心x
	int centerY;    // 历史信息中心y
	int length;     // 历史信息长度
	int height;      // 历史信息高度
	int hori_move;  // 水平方向位移
	int vert_move;  // 竖直方向位移

	TsTrackHistoryInfo()
	{
		centerX = 0;
		centerY = 0;
		length = 0;
		height = 0;
		hori_move = 0;
	}
};

#endif