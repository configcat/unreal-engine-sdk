FROM ubuntu:22.04

ENV DEBIAN_FRONTEND noninteractive

RUN \
  apt-get update && \
  apt-get -y upgrade

RUN \
  apt-get -y --no-install-recommends install git g++ wget curl zip vim pkg-config tar cmake unzip ca-certificates build-essential

# Download Android NDK
RUN \
  wget https://dl.google.com/android/repository/android-ndk-r25c-linux.zip && \
  unzip android-ndk-r25c-linux.zip && \
  rm -rf android-ndk-r25c-linux.zip

ENV ANDROID_NDK_HOME /android-ndk-r25c

RUN git clone https://github.com/microsoft/vcpkg
WORKDIR vcpkg
RUN ./bootstrap-vcpkg.sh

ENV PATH "/vcpkg:$PATH"
ENV VCPKG_ROOT "/vcpkg"

WORKDIR /project