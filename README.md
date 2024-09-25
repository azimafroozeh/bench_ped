# BtrBlocks

## Building

### Install Dependencies

- BtrBlocks: tbb, boost dynamic_bitset
- Build system: make, cmake
- Other formats: bz2 
- AWS: ssl, curl

On Ubuntu:
``` sh
apt install \
    libtbb2 libtbb-dev libboost-dev \
    cmake make \
    libbz2-1.0 libbz2-dev \
    libssl3 libssl-dev \
    libcurl4 libcurl4-openssl-dev \
    zlib1g-dev
```

### Compile 

``` sh
mkdir build
cmake . -B build
cd build
make
```

This creates binaries for different experiments in the `build` directory.

