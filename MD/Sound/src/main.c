#include <genesis.h>

#include "../../define.h"

#include "Sound.h"

//!< [64, 255] サウンドドライバで [0, 63] は予約されている
const u16 XGMIndex = 64;

static void JoyEvent(const u16 Joy, const u16 KeyChanged, const u16 KeyState)
{
	const u8 Loop = FALSE;

	if (KeyChanged & KeyState & BUTTON_UP) {
		//!< [ PCM ]
		SND_startPlay_PCM(pcm, sizeof(pcm), SOUND_RATE_8000, SOUND_PAN_CENTER, Loop);
	}
	if (KeyChanged & KeyState & BUTTON_DOWN) {
		//!< [ 2ADPCM ]
		SND_startPlay_2ADPCM(_2adpcm, sizeof(_2adpcm), SOUND_PCM_CH_AUTO, Loop);
	}
	if (KeyChanged & KeyState & BUTTON_LEFT) {
		//!< [ 4PCM ]
		SND_startPlay_4PCM(_4pcm, sizeof(_4pcm), SOUND_PCM_CH_AUTO, Loop);
	}
	if (KeyChanged & KeyState & BUTTON_RIGHT) {
		//!< [ XGM ]
		XGM_setPCM(XGMIndex, xgm, sizeof(xgm));
		XGM_setLoopNumber(0);
		const u8 Pri = 0; /* 低 [0, 15] 高 */
		XGM_startPlayPCM(XGMIndex, Pri, SOUND_PCM_CH1);
	}

	//!< レジューム
	if (KeyChanged & KeyState & BUTTON_A) {
		//!< [ XGM ]
		XGM_resumePlay();
	}
	//!< ポーズ
	if (KeyChanged & KeyState & BUTTON_B) {
		//!< [ XGM ]
		XGM_pausePlay();
	}
	//!< ストップ
	if (KeyChanged & KeyState & BUTTON_C) {
		//!< [ PCM ]
		SND_stopPlay_PCM();
		//!< [ 2ADPCM ]
		if (SND_isPlaying_2ADPCM(SOUND_PCM_CH1_MSK)) { SND_stopPlay_2ADPCM(SOUND_PCM_CH1); }
		if (SND_isPlaying_2ADPCM(SOUND_PCM_CH2_MSK)) { SND_stopPlay_2ADPCM(SOUND_PCM_CH2); }
		//!< [ 4PCM ]
		if (SND_isPlaying_4PCM(SOUND_PCM_CH1_MSK)) { SND_stopPlay_4PCM(SOUND_PCM_CH1); }
		if (SND_isPlaying_4PCM(SOUND_PCM_CH2_MSK)) { SND_stopPlay_4PCM(SOUND_PCM_CH2); }
		if (SND_isPlaying_4PCM(SOUND_PCM_CH3_MSK)) { SND_stopPlay_4PCM(SOUND_PCM_CH3); }
		if (SND_isPlaying_4PCM(SOUND_PCM_CH4_MSK)) { SND_stopPlay_4PCM(SOUND_PCM_CH4); }
		//!< [ XGM ]
		XGM_stopPlay();
	}
}

int main()
{
	JOY_setEventHandler(JoyEvent);

	while (1) {
		SYS_doVBlankProcess();
	}
}