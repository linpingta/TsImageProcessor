#ifndef _TSTRACKHISTORYINFO
#define _TSTRACKHISTORYINFO

struct TsTrackHistoryInfo
{
	int centerX;    // ��ʷ��Ϣ����x
	int centerY;    // ��ʷ��Ϣ����y
	int length;     // ��ʷ��Ϣ����
	int height;      // ��ʷ��Ϣ�߶�
	int hori_move;  // ˮƽ����λ��
	int vert_move;  // ��ֱ����λ��

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