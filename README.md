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

## VS Code からのビルド、実行
- a