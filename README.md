# C++ Qt penta-file

## Dependencies

* `g++`
* `make`
* `qmake`
* `qtdeclarative5-dev`

## Setup Procedure

To initialize (only necessary once):

```bash
mkdir -p build
qmake -project -o build/penta-file.pro
sed -i '/^INCLUDEPATH.*/a \\nQT += widgets' build/penta-file.pro
```

## Build Procedure

To build after init in one command:

```bash
make full-build
```

To run:

```bash
make run
```

To clean:

```bash
make clean

## Developing Procedure

Don't forget to add your source files to the SOURCES var in build/penta-file.pro