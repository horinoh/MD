#include <genesis.h>

#include "../../define.h"

#include "BG.h"

int main()
{
	Map* BG_A_Map = NULL;
	Map* BG_B_Map = NULL;

	//!< ウインドウ面 (BG_A)
	{
#if FALSE
		VDP_setWindowHPos(FALSE/*isRight*/, 3); //!< 左からNセル分
#else
		VDP_setWindowVPos(FALSE/*isDown*/, 5); //!< 上からNセル分
#endif
	}

	SYS_disableInts(); {
		VDP_setPaletteColors(0, palette.data, sizeof(palette.data));

		VDP_loadTileSet(&bga_tileset, TILE_USERINDEX, DMA);
		VDP_loadTileSet(&bga_tileset, TILE_USERINDEX + bga_tileset.numTile, DMA);

		BG_A_Map = MAP_create(&bga_map, BG_A, TILE_ATTR_FULL(0, FALSE, FALSE, FALSE, TILE_USERINDEX));
		BG_B_Map = MAP_create(&bgb_map, BG_B, TILE_ATTR_FULL(0, FALSE, FALSE, FALSE, TILE_USERINDEX + bga_tileset.numTile));

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

		MAP_scrollTo(BG_A_Map, fix16ToInt(Pos.x), fix16ToInt(Pos.y));
		MAP_scrollTo(BG_B_Map, fix16ToInt(Pos.x) >> 1, fix16ToInt(Pos.y) >> 1);

		SYS_doVBlankProcess();
	}

	MEM_free(BG_B_Map);
	MEM_free(BG_A_Map);
}