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

I'll talk about what this Docker image does so that you aren't just blindly building things. This should all be reflected pretty nicely in the Dockerfile. We begin by using `apt` to install `build-essential` and `wget`, the latter of which we use to install the [OFFICIAL binary installer for CMake](https://cmake.org/download/) -- these are precompiled binaries, so especially on your own machine, use caution and do your own research. Should be find on Docker since nothing is mounted. After that, the Dockerfile will copy grapph's source into the image, and initialize/use CMake to build the test executeables. Running a container with this image just executes the executeables. Right now, the only executeables are for testing `SetFunctions.h`, `grapph::Graph`, `grapph::Homomorphism`, and `grapph::FeatureGraph`.

Again, if any of this is causing problems for you that you can't resolve, open an issue or send me an email. Happy to help.
