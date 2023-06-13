FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    libboost-all-dev \
    libopencv-dev \
    apt-utils

COPY . /app

WORKDIR /app

RUN rm -rf build && mkdir build && cd build && cmake .. && make

CMD ["./build/ImgProcessingPipe"]
