# MD

## ビルド
- [Java](https://www.java.com/ja/download/ie_manual.jsp)
    - インストールしておく
- [SGDK](https://github.com/Stephane-D/SGDK)
    - 解凍して SGDK-master を Cドライブ直下に配置
    - 環境変数 GDK, GDK_WIN を作成しておく
        ~~~
        GDK = C:/SGDK-master
        GDK_WIN = C:\SGDK-master
        ~~~
    - ビルド
      ~~~
      %GDK_WIN%\bin\make -f %GDK_WIN%\makefile.gen
      ~~~
    
    ## 実行
    - [エミュレータ](https://www.emulator-zone.com/doc.php/genesis/fusion.html)
        - インストールして環境変数 Path に通しておく
            ~~~
            $Fusion out\rom.bin
            ~~~
    - [エミュレータ(Debug)](https://gendev.spritesmind.net/page-gdb.html)
        - インストールして環境変数 Path に通しておく
        - rom.bin を読み込む
            - コマンドラインから指定する場合は rom.bin のフルパス指定じゃないとダメみたい
                ~~~
                $gens <Fullpath of rom.bin>
                ~~~
        - デバッグ
            - Option - Debug... - Active Development Features にチェック
                - GDB は有効にしても上手くいかなかった
            - 以下のようにプログラムに記述しておく
                ~~~
                KLog("XXX");
                ~~~
            - gens - CPU - Debug - Messages からログ出力が確認できる

## Visual Studio からのビルド、実行
- Create a New Project - Makefile Project 
    - プロジェクトを右クリック - Property - NMake
        - Build command line
            ~~~
            %GDK_WIN%\bin\make -f %GDK_WIN%\makefile.gen $(Configuration)
            ~~~
        - Clean command line
            ~~~
            %GDK_WIN%\bin\make -f %GDK_WIN%\makefile.gen clean
            ~~~
        - プロジェクトを右クリック - Property - VC++ Directories - Public Include Directories
            ~~~
            %GDK_WIN%\inc
            ~~~
        - プロジェクトを右クリック - Property - Debugging
            - Command
                - Release
                    ~~~
                    C:\Fusion364\Fusion
                    ~~~
                - Debug
                    ~~~
                    C:\GensKMod\gens
                    ~~~
            - Command Arguments
                - Release
                    ~~~
                    out\rom.bin
                    ~~~
                - Debug 
                    ~~~
                    $(ProjectDir)\out\rom.bin
                ~~~ 
            - Debugger Type - Script にしておくと余計な例外が出ない
     - Source Files 右クリック - Add - New Item - main.c を追加
        - **拡張子は.cppではなく、.cに変更すること**、.cpp だと Makefile に認識されない

## リソース
- BG
    - XXX.res
        - MAP は TILESET を必要とする
        ~~~
        TILESET TileName "XXX.png" BEST ALL
        MAP BGName "XXX.png" TileName BEST
        ~~~
- スプライト
    - XXX.res
        - 名前 SpName は任意
        - ここでは 4 x 4 セル (32 x 32)
        - FAST は圧縮方式
        - アニメーション、ここでは秒間 5 フレーム
        - コリジョン CIRCLE, BOX, サイズはスプライトの 75%
        ~~~
        SPRITE SpName "XXX.png" 4 4 FAST 5 BOX
        ~~~
    - XXX.png
        - 16色で保存すること
        - 黒が透明色
        - 縦に並べていく
        - 横に並べた場合はアニメーション番号が振られる
    - コードから使う例
        ~~~
        #include "XXX.h"
        VDP_setPalleteColors(PAL0, SpName.palette->data, 16);
        Sprite = SPR_addSprite(&SpName, X, y, TILE_ATTR(PAL0, 0, 0, 0));
        ~~~
- サウンド
    ~~~
    WAV pcm "XXX.wav" PCM
    WAV _2adpcm "XXX.wav" 2ADPCM
    WAV _4pcm "XXX.wav" 4PCM
    WAV xgm "XXX.wav" XGM
    ~~~
    ~~~
    const u8 Loop = TRUE;

    //!< [ PCM ]
    //!<    SOUND_RATE_8000, 11025, 13400, 16000, 22050, 32000
    //!<    SOUND_PAN_LEFT, SOUND_PAN_RIGHT, SOUND_PAN_CENTER
    SND_startPlay_PCM(pcm, sizeof(pcm), SOUND_RATE_8000, SOUND_PAN_CENTER, Loop);

    //!< [ 2ADPCM ]
    //!<    SOUND_PCM_CH_AUTO, 1, 2
    SND_startPlay_2ADPCM(_2adpcm, sizeof(_2adpcm), SOUND_PCM_CH_AUTO, Loop);

    //!< [ 4PCM ]
    //!<    SOUND_PCM_CH_AUTO, 1, 2, 3, 4
    SND_startPlay_4PCM(_4pcm, sizeof(_4pcm), SOUND_PCM_CH_AUTO, Loop);

    //!< [ XGM ]
    const u16 i = 64; /* [64, 255] サウンドドライバで[0, 63]は予約されている */
    XGM_setPCM(i, xgm, sizeof(xgm)); 
    
    const u8 Pri = 15; /* 低 [0, 15] 高 */
    //!<    SOUND_PCM_CH1, 2, 3, 4
    XGM_startPlayPCM(i, Pri, SOUND_PCM_CH1);
    ~~~
<!--
## VS Code からのビルド、実行
-->