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

<!--
    - [エミュレータ(GDB)](https://gendev.spritesmind.net/page-gdb.html)
        - インストールして環境変数 Path に通しておく
        - Option - Debug... - 以下にチェック
            ~~~
            Blue Screen pause
            Single instance
            use GDB
            ~~~
        - rom.bin を読み込む
        - GDB
            ~~~
            $%GDK_WIN%\bin\gdb
            ~~~
            ~~~
            (gdb)file rom.out
            (gdb)target remote localhost:6868
            (gdb)// 以降は通常のGDB操作
            ~~~
-->

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
                ~~~
                C:\Fusion364\Fusion
                ~~~
            - Command Arguments
                ~~~
                out\rom.bin
                ~~~ 
            - Debugger Type
                ~~~
                Script //にしておくと余計な例外が出ない
                ~~~ 
     - Source Files 右クリック - Add - New Item - main.c を追加
        - **拡張子は.cppではなく、.cに変更すること**、.cpp だと Makefile に認識されない

## リソース
- スプライト
    - XXX.res
        - 4 x 4 セル (32 x 32) の場合
        - 名前 SpName は任意
        ~~~
        SPRITE SpName "XXX.png" 4 4 BEST
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