PROJECT=penta-file

.PHONY: all clean preprocess

all: build/$(PROJECT)
	
build/$(PROJECT): build/Makefile
	make --directory=build
	DIRECTORY
build/Makefile: build/$(PROJECT).pro qt-preprocess
	qmake -o build/Makefile build/$(PROJECT).pro

qt-preprocess: build/$(PROJECT).pro
	sed -i '/^INCLUDEPATH.*/a \\nQT += widgets' "build/$(PROJECT).pro"

build/$(PROJECT).pro: src/* include/*
	mkdir -p build
	qmake -project -o build/$(PROJECT).pro

clear:
	rm -rf build/moc
	rm -rf build/obj
	rm -rf build/rcc
	rm -rf build/bin
	rm -f  build/.qmake.stash

full-build:
	qmake -o build/Makefile build/$(PROJECT).pro
	make --directory=build

run:
	./build/bin/$(PROJECT)