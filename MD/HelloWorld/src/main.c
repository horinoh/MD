#include <genesis.h>

#include "../../define.h"

int main()
{
	//!< 画面解像度
	VDP_setScreenWidth320(); //!< 320 x 224, スプライト x 80
	//VDP_setScreenWidth256(); //!< 256 x 224, スプライト x 64

	//!< スクロール面
	VDP_setPlanSize(64, 32);

	//!< ウインドウ面 (BG_A上)
#if FALSE
	VDP_setWindowHPos(FALSE/*isRight*/, 3); //!< 左からNセル分
#else
	VDP_setWindowVPos(FALSE/*isDown*/, 5); //!< 上からNセル分
#endif

	KLog("Hello World");

	for (u8 i = 0; i < 224 >> 3; ++i) {
		VDP_drawText("Hello World", 0, i);
	}

	//!< わざわざタイルで埋めるバージョン
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