PROJECT=penta-file

.PHONY: all clean preprocess

all: build/$(PROJECT)
	
build/$(PROJECT): build/Makefile
	make --directory=build
	
build/Makefile: build/$(PROJECT).pro qt-preprocess
	qmake -o build/Makefile build/$(PROJECT).pro

qt-preprocess: build/$(PROJECT).pro
	sed -i '/^INCLUDEPATH.*/a \\nQT += widgets' "build/$(PROJECT).pro"

build/$(PROJECT).pro: src/main.cpp src/mainwidget.cpp include/mainwidget.h
	mkdir -p build
	qmake -project -o build/$(PROJECT).pro

clean:
	rm -rf build/
	rm -f .qmake.stash

