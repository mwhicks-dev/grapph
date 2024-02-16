# grapph

C++ graph encoding library. Feel free to put feature requests or bug reports you find into Issues. I will definitely fix the bugs, and will implement features as I see fit.

## build instructions

### Libary Build

Use the specified Makefile for this: `make clean lib`

This library is written strictly in C++ STL, so all you will need is `build-essential` or your OS equivalent.

### Testing Build

Docker:

```
docker build -t grapph_test .

docker run grapph_test
```

This isn't done with testing because I think CMake is kind of ugly looking, so you'll need to redo this every time you want to test. Just change the Dockerfile to test against your relevant specs and stuff, which might be different from your system.
