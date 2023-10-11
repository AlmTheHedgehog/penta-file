# C++ Qt penta-file

## Dependencies

* `g++`
* `make`
* `qmake`
* `qtdeclarative5-dev`

## Build Procedure

To initialize (only necessary once):

```bash
mkdir -p build
qmake -project -o build/penta-file.pro
sed -i '/^INCLUDEPATH.*/a \\nQT += widgets' build/penta-file.pro
```

To build:

```bash
qmake -o build/Makefile build/penta-file.pro
make --directory=build
```

To run:

```bash
./build/penta-file
```

To clean:

```bash
make --directory=build distclean
```

