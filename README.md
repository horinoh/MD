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
            - CIRCLE と Box の定義が入れ替わっている気がする
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
        Sprite = SPR_addSprite(&SpName, x, y, TILE_ATTR(PAL0, 0, FALSE, FALSE));
        ~~~
- サウンド
    ~~~
    WAV pcm "XXX.wav" PCM
    WAV _2adpcm "XXX.wav" 2ADPCM
    WAV _4pcm "XXX.wav" 4PCM
    WAV xgm "XXX.wav" XGM
    ~~~
    - PCM
        - 1チャンネル、8ビット、[8, 32]hz、SND_startPlay_PCM()
    - 2ADPCM
        - 2チャンネル、4ビット、 22050hz、SND_startPlay_2ADPCM()
    - 4PCM
        - 4チャンネル、8ビット、16khz、ボリューム、SND_startPlay_4PCM_ENV()
    - XGM
        - 4チャンネル、8ビット、14khz、SND_setPCM_XGM(), SND_startPlayPCM_XGM()
<!--
## VS Code からのビルド、実行
-->