#include <genesis.h>

#include "../../define.h"

int main()
{
	//!< ��ʉ𑜓x
	VDP_setScreenWidth320(); //!< 320 x 224, �X�v���C�g x 80
	//VDP_setScreenWidth256(); //!< 256 x 224, �X�v���C�g x 64

	//!< �X�N���[����
	VDP_setPlanSize(64, 32);

	//!< �E�C���h�E�� (BG_A��)
#if FALSE
	VDP_setWindowHPos(FALSE/*isRight*/, 3); //!< ������N�Z����
#else
	VDP_setWindowVPos(FALSE/*isDown*/, 5); //!< �ォ��N�Z����
#endif

	KLog("Hello World");

	for (u8 i = 0; i < 224 >> 3; ++i) {
		VDP_drawText("Hello World", 0, i);
	}

	//!< �킴�킴�^�C���Ŗ��߂�o�[�W����
#define PRI 0
#define FLIPV 1
#define FLIPH 1
#define ASCII_TOP 1408
	VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL0, PRI, FLIPV, 0, 'H' + ASCII_TOP), 1 + 16, 1);
	VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL0, PRI, FLIPV, 0, 'E' + ASCII_TOP), 2 + 16, 1);
	VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL0, PRI, FLIPV, 0, 'L' + ASCII_TOP), 3 + 16, 1);
	VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL0, PRI, FLIPV, 0, 'L' + ASCII_TOP), 4 + 16, 1);
	VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL0, PRI, FLIPV, 0, 'O' + ASCII_TOP), 5 + 16, 1);
	VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL0, PRI, 0, 0, ' ' + ASCII_TOP), 6 + 16, 1);
	VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL0, PRI, 0, FLIPH, 'W' + ASCII_TOP), 7 + 16, 1);
	VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL0, PRI, 0, FLIPH, 'O' + ASCII_TOP), 8 + 16, 1);
	VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL0, PRI, 0, FLIPH, 'R' + ASCII_TOP), 9 + 16, 1);
	VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL0, PRI, 0, FLIPH, 'L' + ASCII_TOP), 10 + 16, 1);
	VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL0, PRI, 0, FLIPH, 'D' + ASCII_TOP), 11 + 16, 1);
#undef ASCII_TOP
#undef FLIPH
#undef FLIPV
#undef PRI

	while (1) {
		SYS_doVBlankProcess();
	}
}