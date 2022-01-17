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
        - 4 x 4 セル (32 x 32) の場合
        - 名前 SpName は任意
        ~~~
        SPRITE SpName "XXX.png" 4 4 FAST
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
<!--
## VS Code からのビルド、実行
-->