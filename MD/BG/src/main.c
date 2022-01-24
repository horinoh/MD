#include <genesis.h>

#include "../../define.h"

#include "BG.h"

int main()
{
	VDP_setScreenWidth320();

#if FALSE
	//!< ウインドウ面 (BG_A)
	//VDP_setWindowHPos(FALSE/*isRight*/, 3);
	VDP_setWindowVPos(FALSE/*isDown*/, 5);
#endif

	Map* BG_A_Map = NULL;
	Map* BG_B_Map = NULL;
	SYS_disableInts(); {
		PAL_setPalette(PAL0, palette.data, DMA);

		VDP_loadTileSet(&bga_tileset, TILE_USERINDEX, DMA);
		VDP_loadTileSet(&bgb_tileset, TILE_USERINDEX + bga_tileset.numTile, DMA);

		BG_A_Map = MAP_create(&bga_map, BG_A, TILE_ATTR_FULL(0, FALSE, FALSE, FALSE, TILE_USERINDEX));
		//BG_B_Map = MAP_create(&bgb_map, BG_B, TILE_ATTR_FULL(0, FALSE, FALSE, FALSE, TILE_USERINDEX + bga_tileset.numTile));

	} SYS_enableInts();

	V2f16 Pos; V2f16ZERO(Pos);
	u16 KeyState = 0;
	while (1) {
		if (PORT_TYPE_UNKNOWN != JOY_getPortType(PORT_1)) {
			KeyState = JOY_readJoypad(JOY_1);
			const fix16 Speed = FIX16(10);
			if (KeyState & BUTTON_UP) { Pos.y = fix16Sub(Pos.y, Speed); }
			if (KeyState & BUTTON_DOWN) { Pos.y = fix16Add(Pos.y, Speed); }
			if (KeyState & BUTTON_LEFT) { Pos.x = fix16Sub(Pos.x, Speed); }
			if (KeyState & BUTTON_RIGHT) { Pos.x = fix16Add(Pos.x, Speed); }
		}

		if (NULL != BG_A_Map) {
			MAP_scrollTo(BG_A_Map, fix16ToInt(Pos.x), fix16ToInt(Pos.y));
		}
		if (NULL != BG_B_Map) {
			MAP_scrollTo(BG_B_Map, fix16ToInt(Pos.x) >> 2, fix16ToInt(Pos.y) >> 2);
		}

		SYS_doVBlankProcess();
	}

	if (NULL != BG_A_Map) {
		MEM_free(BG_A_Map);
	}
	if (NULL != BG_B_Map) {
		MEM_free(BG_B_Map);
	}
}