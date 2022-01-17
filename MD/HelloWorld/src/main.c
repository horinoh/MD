#include <genesis.h>

int main()
{
	KLog("Hello World");
	VDP_drawText("Hello World", 1, 1);

#define PRI 0
#define FLIPV 1
#define FLIPH 1
#define ASCII_TOP 1408
	VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL0, PRI, FLIPV, 0, 'H' + ASCII_TOP), 1, 2);
	VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL0, PRI, FLIPV, 0, 'E' + ASCII_TOP), 2, 2);
	VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL0, PRI, FLIPV, 0, 'L' + ASCII_TOP), 3, 2);
	VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL0, PRI, FLIPV, 0, 'L' + ASCII_TOP), 4, 2);
	VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL0, PRI, FLIPV, 0, 'O' + ASCII_TOP), 5, 2);
	VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL0, PRI, 0, 0, ' ' + ASCII_TOP), 6, 2);
	VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL0, PRI, 0, FLIPH, 'W' + ASCII_TOP), 7, 2);
	VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL0, PRI, 0, FLIPH, 'O' + ASCII_TOP), 8, 2);
	VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL0, PRI, 0, FLIPH, 'R' + ASCII_TOP), 9, 2);
	VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL0, PRI, 0, FLIPH, 'L' + ASCII_TOP), 10, 2);
	VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL0, PRI, 0, FLIPH, 'D' + ASCII_TOP), 11, 2);
#undef ASCII_TOP
#undef FLIPH
#undef FLIPV
#undef PRI

	while (1) {
		SYS_doVBlankProcess();
	}
}