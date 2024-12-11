FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    qt6-base-dev \
    libgtest-dev \
    libcurl4-openssl-dev \
    libgdal-dev \
    libglew-dev \
    libglfw3-dev \
    libglu1-mesa-dev \
    libglm-dev \
    nlohmann-json3-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . /app

# compiling using maxing number of processor available
# and shows detailed output for debugging purposes
RUN mkdir -p build && \
    cd build && \
    cmake -DCMAKE_VERBOSE_MAKEFILE=ON .. && \
    make -j$(nproc) VERBOSE=1


CMD ["/app/build/cute-gis"]
