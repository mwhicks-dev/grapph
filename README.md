# grapph

C++ graph abstraction library. Feel free to put feature requests or bug reports you find into Issues. I will definitely fix the bugs, and will implement features as I or other users need them. If you have anything specific you don't want to put into an issue, shoot me an email at mason@hicksm.dev and I'll get back to you when I can.

## build instructions

### Libary Build

Use the specified Makefile target for this: `make clean lib`. This will compile a copy of `libgrapph` in the `bin/` directory among other things, and you should then be able to use it just like any other C++ library.

grapph is written strictly in C++ STL, so all you will need is `build-essential` or your OS equivalent to compile. Everything has been developed and tested in focal Ubuntu.

### Testing Build

Docker:

```
docker build -t grapph_test .

docker run grapph_test
```

This isn't done with testing because I think CMake is kind of ugly looking, so you'll need to redo this every time you want to test. Just change the Dockerfile to test against your relevant specs and stuff, which might be different from your system.
