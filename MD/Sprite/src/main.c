#include <genesis.h>

#include "../../define.h"

#include "Sprite.h"

Sprite* Sprites[1];

static void JoyEvent(const u16 Joy, const u16 KeyChanged, const u16 KeyState)
{
}
static void VIntEvent()
{
}
static void FrameChanged(Sprite* Spr) 
{
	const AnimationFrame* AnimFrame = Spr->animation[Spr->animInd].frames[Spr->frameInd];
	KLog_U3("animInd = ", Spr->animInd, ", frameInd = ", Spr->frameInd, ", timer = ", AnimFrame->timer);
}

int main()
{
	//!< スプライト定義
	const SpriteDefinition* SprDef = &sprite;

	SYS_disableInts(); {
		SPR_init();

		//!< スプライトインスタンス
		for (u8 i = 0; i < COUNTOF(Sprites); ++i) {
			Sprite* Spr = SPR_addSprite(SprDef, 0/*X*/, 0/*Y*/, TILE_ATTR(PAL0, 0/*Pri*/, FALSE, FALSE));
			//!< [SPR_MIN_DEPTH(-0x8000), SPR_MAX_DEPTH(0x7fff)]
			SPR_setDepth(Spr, SPR_MIN_DEPTH);

			//!< VRAM上のメモリ確保を明示的に行いたい場合、-1 だと自動
			//SPR_setVRAMTileIndex(Spr, -1);

			//!< フレーム変化時のコールバック
			SPR_setFrameChangeCallback(Spr, FrameChanged);
			
			//!< ユーザが自由に使用できるメンバ u32
			Spr->data = 0xdeadbeef;

			Sprites[i] = Spr;
		}
		VDP_setPalette(PAL0, SprDef->palette->data);
		SPR_update();

		//!< アニメーション数、フレーム数、コリジョン等を列挙
		KLog_U1("numAnimation = ", SprDef->numAnimation);
		for(u8 i = 0;i < SprDef->numAnimation;++i) {
			const Animation* Anim = SprDef->animations[i];
			KLog_U1(" numFrame = ", Anim->numFrame);
			for (u8 j = 0; j < Anim->numFrame; ++j) {
				const AnimationFrame* AnimFrame = Anim->frames[j];
				KLog_U1("  timer = ", AnimFrame->timer);
				const Collision* Colli = AnimFrame->collision;
				if (NULL != Colli) {
					//!< BOX と CIRCLE のタイプが入れ替わっている？ バグ？
					switch (Colli->typeHit) {
					case COLLISION_TYPE_NONE:
						break;
					case COLLISION_TYPE_BOX:
						KLog_U3("   Hit Circle x = ", Colli->hit.circle.x, ", y = ", Colli->hit.circle.y, ", ray = ", Colli->hit.circle.ray);
						break;
					case COLLISION_TYPE_CIRCLE:
						KLog_U4("   Hit Box x = ", Colli->hit.box.x, ", y = ", Colli->hit.box.y, ", w = ", Colli->hit.box.w, ", h = ", Colli->hit.box.h);
						break;
					}
					//!< Attack は未対応？ 値が入ってこない…
					switch (Colli->typeAttack) {}
				}
			}
		}
	} SYS_enableInts();

	JOY_setEventHandler(JoyEvent);
	SYS_setVIntCallback(VIntEvent);

	//!<		符号.整数.少数
	//!< fix16	1.9.6			[-2097152.000, 2097151.000]
	//!< fix32	1.21.10			[-512.00, 511.00]
	V2f16 Pos; V2f16ZERO(Pos);
	u16 AnimIndex = 0;
	u16 KeyState = 0	, PrevState = 0;
	while (1) {
		if (PORT_TYPE_UNKNOWN != JOY_getPortType(PORT_1)) {
			PrevState = KeyState;
			KeyState = JOY_readJoypad(JOY_1);
			u16 KeyTrig = (KeyState ^ PrevState) & PrevState;
			const fix16 Speed = FIX16(2);
			if (KeyState & BUTTON_UP) { Pos.y = fix16Sub(Pos.y, Speed); }
			if (KeyState & BUTTON_DOWN) { Pos.y = fix16Add(Pos.y, Speed); }
			if (KeyState & BUTTON_LEFT) { Pos.x = fix16Sub(Pos.x, Speed); }
			if (KeyState & BUTTON_RIGHT) { Pos.x = fix16Add(Pos.x, Speed); }
			if (KeyTrig & BUTTON_A) {
				for (u8 i = 0; i < COUNTOF(Sprites); ++i) {
					++AnimIndex;
					AnimIndex %= SprDef->numAnimation;
					SPR_setAnim(Sprites[i], AnimIndex);
				}
			}
			for (u8 i = 0; i < COUNTOF(Sprites); ++i) {
				SPR_setPosition(Sprites[i], fix16ToInt(Pos.x), fix16ToInt(Pos.y));
			}
		}

		SPR_update();

		SYS_doVBlankProcess();
	}

	for (u8 i = 0; i < COUNTOF(Sprites); ++i) {
		SPR_releaseSprite(Sprites[i]);
	}
}
