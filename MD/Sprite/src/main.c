#include <genesis.h>

#include "../../define.h"

#include "SpriteData.h"

Sprite* Sprites[80];

static void JoyEvent(const u16 Joy, const u16 KeyChanged, const u16 KeyState)
{
}
static void VIntEvent()
{
}

int main()
{
	SYS_disableInts(); {
		VDP_clearPlane(BG_A, 0);
		VDP_clearPlane(BG_B, 0);

		SPR_initEx(0);
		for (u8 i = 0; i < 16; ++i) {
			Sprite* Spr = SPR_addSprite(&SpriteData, 0, 0, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, 0));
			SPR_setPosition(Spr, 0, 0);
			//!< [SPR_MIN_DEPTH(-0x8000), SPR_MAX_DEPTH(0x7fff)]
			//SPR_setDepth(Spr, SPR_MIN_DEPTH);
			SPR_setFrame(Spr, 0);
			//!< VRAM上のメモリ確保を明示的に行いたい場合、-1 だと自動
			//SPR_setVRAMTileIndex(Spr, -1);

			Sprites[i] = Spr;
		}

		SPR_update();
		VDP_setPalette(PAL0, SpriteData.palette->data);
	} SYS_enableInts();

	JOY_setEventHandler(JoyEvent);
	SYS_setVIntCallback(VIntEvent);

	u16 x = 0, y = 0;
	u16 KeyState = 0, PrevState = 0;
	while (1) {
		if (PORT_TYPE_UNKNOWN != JOY_getPortType(PORT_1)) {
			PrevState = KeyState;
			KeyState = JOY_readJoypad(JOY_1);
			u16 KeyTrig = (KeyState ^ PrevState) & PrevState;
			if (KeyState & BUTTON_UP) { --y; }
			if (KeyState & BUTTON_DOWN) { ++y; }
			if (KeyState & BUTTON_LEFT) { --x; }
			if (KeyState & BUTTON_RIGHT) { ++x; }
		}

		for (u8 i = 0; i < 16; ++i) {
			Sprite* Spr = Sprites[i];
			SPR_setPosition(Spr, x + (i << 4), y + (i << 3));
			SPR_setFrame(Spr, 0);
		}
		SPR_update();

		SYS_doVBlankProcess();
	}
}