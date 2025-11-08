win-args = -Wl,-Bstatic -Iinclude/win/ -Linclude/win/ -lraylib -lpthread -Wl,-Bdynamic -lopengl32 -lgdi32 -lwinmm

ubuntu-args = -Wl,-Bstatic -Iinclude/linux/ -Linclude/linux/ -lraylib -Wl,-Bdynamic -lGL -lm -lpthread -lrt -lX11

korui = src/korui/korui.c src/korui/korui.h

testenv = src/testenv/korui_test.c

build-all : ubuntu_test windows_test

ubuntu_test : build/korui_test

windows_test : build/korui_test.exe

build/korui_test : $(korui) $(testenv)
	mkdir -p build
	gcc $(korui) $(testenv) $(ubuntu-args) -o build/korui_test

build/korui_test.exe : $(korui) $(testenv)
	mkdir -p build
	x86_64-w64-mingw32-gcc $(korui) $(testenv) $(win-args) -o build/korui_test.exe