#include <genesis.h>

#define COUNTOF(x) (sizeof(x) / sizeof(x[0]))

int main()
{
	u16 x = 0, y = 0;

	switch (JOY_getPortType(PORT_1)) {
	case PORT_TYPE_MENACER:
		VDP_drawText("PORT : MENACER", x, y++);
		JOY_setSupport(PORT_1, JOY_SUPPORT_MENACER);
		break;
	case PORT_TYPE_JUSTIFIER:
		VDP_drawText("PORT : JUSTIFIER_BOTH", x, y++);
		JOY_setSupport(PORT_1, JOY_SUPPORT_JUSTIFIER_BOTH);
		break;
	case PORT_TYPE_MOUSE:
		VDP_drawText("PORT : MOUSE", x, y++);
		JOY_setSupport(PORT_1, JOY_SUPPORT_MOUSE);
		break;
	case PORT_TYPE_TEAMPLAYER:
		VDP_drawText("PORT : TEAMPLAYER", x, y++);
		JOY_setSupport(PORT_1, JOY_SUPPORT_TEAMPLAYER);
		break;
	case PORT_TYPE_PAD:
		VDP_drawText("PORT : PAD", x, y++);
		break;
	case PORT_TYPE_EA4WAYPLAY:
		VDP_drawText("PORT : EA4WAYPLAY", x, y++);
		break;
	default:
	case PORT_TYPE_UKNOWN:
		VDP_drawText("PORT : UNKNOWN", x, y++);
		break;
	}

	for (u8 i = JOY_1; i < JOY_NUM; i++) {
		switch (JOY_getJoypadType(i)) {
		case JOY_TYPE_PAD3:
			VDP_drawText("PAD : PAD3", x, y++);
			break;
		case JOY_TYPE_PAD6:
			VDP_drawText("PAD : PAD6", x, y++);
			break;
		case JOY_TYPE_TRACKBALL:
			VDP_drawText("PAD : TRACKBALL", x, y++);
			break;
		case JOY_TYPE_MOUSE:
			VDP_drawText("PAD : MOUSE", x, y++);
			break;
		case JOY_TYPE_MENACER:
			VDP_drawText("PAD : MENACER", x, y++);
			break;
		case JOY_TYPE_JUSTIFIER:
			VDP_drawText("PAD : JUSTIFIER", x, y++);
			break;
		case JOY_TYPE_PHASER:
			VDP_drawText("PAD : PHASER", x, y++);
			break;
		default:
			break;
		}
	}

	while (1) {
		SYS_doVBlankProcess();
		VDP_waitVSync();

		char KeyStateStr[2];
		u16 PrevState = 0, KeyState = 0;
		if (PORT_TYPE_UNKNOWN != JOY_getPortType(PORT_1)) {
			PrevState = KeyState;
			KeyState = JOY_readJoypad(JOY_1);
			u16 KeyTrig = (KeyState ^ PrevState) & PrevState;

			(KeyState & BUTTON_UP) ? VDP_drawText("+", 1 + x, 0 + y) : VDP_drawText("-", 1 + x, 0 + y);
			(KeyState & BUTTON_RIGHT) ? VDP_drawText("+", 2 + x, 1 + y) : VDP_drawText("-", 2 + x, 1 + y);
			(KeyState & BUTTON_DOWN) ? VDP_drawText("+", 1 + x, 2 + y) : VDP_drawText("-", 1 + x, 2 + y);
			(KeyState & BUTTON_LEFT) ? VDP_drawText("+", 0 + x, 1 + y) : VDP_drawText("-", 0 + x, 1 + y);
			if (KeyTrig & BUTTON_UP) VDP_drawText("@", 1 + x, 0 + y);
			if (KeyTrig & BUTTON_RIGHT) VDP_drawText("@", 2 + x, 1 + y);
			if (KeyTrig & BUTTON_DOWN) VDP_drawText("@", 1 + x, 2 + y);
			if (KeyTrig & BUTTON_LEFT) VDP_drawText("@", 0 + x, 1 + y);

			(KeyState & BUTTON_START) ? VDP_drawText("+", 4 + x, 2 + y) : VDP_drawText("-", 4 + x, 2 + y);
			if (KeyTrig & BUTTON_START) VDP_drawText("@", 4 + x, 2 + y);

			(KeyState & BUTTON_MODE) ? VDP_drawText("+", 8 + x, 0 + y) : VDP_drawText("-", 8 + x, 0 + y);
			if (KeyTrig & BUTTON_MODE) VDP_drawText("@", 8 + x, 0 + y);

			(KeyState & BUTTON_X) ? VDP_drawText("+", 6 + x, 1 + y) : VDP_drawText("-", 6 + x, 1 + y);
			(KeyState & BUTTON_Y) ? VDP_drawText("+", 7 + x, 1 + y) : VDP_drawText("-", 7 + x, 1 + y);
			(KeyState & BUTTON_Z) ? VDP_drawText("+", 8 + x, 1 + y) : VDP_drawText("-", 8 + x, 1 + y);
			if (KeyTrig & BUTTON_X) VDP_drawText("@", 6 + x, 1 + y);
			if (KeyTrig & BUTTON_Y) VDP_drawText("@", 7 + x, 1 + y);
			if (KeyTrig & BUTTON_Z) VDP_drawText("@", 8 + x, 1 + y);

			(KeyState & BUTTON_A) ? VDP_drawText("+", 6 + x, 2 + y) : VDP_drawText("-", 6 + x, 2 + y);
			(KeyState & BUTTON_B) ? VDP_drawText("+", 7 + x, 2 + y) : VDP_drawText("-", 7 + x, 2 + y);
			(KeyState & BUTTON_C) ? VDP_drawText("+", 8 + x, 2 + y) : VDP_drawText("-", 8 + x, 2 + y);
			if (KeyTrig & BUTTON_A) VDP_drawText("@", 6 + x, 2 + y);
			if (KeyTrig & BUTTON_B) VDP_drawText("@", 7 + x, 2 + y);
			if (KeyTrig & BUTTON_C) VDP_drawText("@", 8 + x, 2 + y);

			intToHex(KeyState, KeyStateStr, COUNTOF(KeyStateStr));
			VDP_drawText(KeyStateStr, 0, 3 + y);
		}
	}
}