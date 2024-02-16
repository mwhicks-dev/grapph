FROM ubuntu:focal

WORKDIR /
RUN apt-get update
RUN apt-get install build-essential -y
RUN apt-get install wget -y
RUN wget -qO- "https://cmake.org/files/v3.28/cmake-3.28.3-linux-x86_64.tar.gz" | tar --strip-components=1 -xz -C /usr/local

RUN mkdir /grapph
COPY . /grapph
WORKDIR /grapph
RUN cmake .
RUN cmake --build .

ENTRYPOINT ./graph_test && ./set_func_test && ./homomorphism_test
