FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive 

RUN apt-get update && apt-get install -y sudo build-essential git zip cmake curl unzip tar vim clang pkg-config libc++-dev

ENV CC=clang
ENV CXX=clang++

WORKDIR /home
RUN git clone https://github.com/Microsoft/vcpkg.git

WORKDIR /home/vcpkg
RUN ./bootstrap-vcpkg.sh

# ./vcpkg install configcat --triplet=x64-linux-unreal --editable
# ./vcpkg remove configcat:x64-linux-unreal