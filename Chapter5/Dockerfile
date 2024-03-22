# Use CentOS 8 as the base image
FROM alpine:latest

# Set working directory
WORKDIR /usr/src/app

# Install development tools and libraries
# Install build base and other dependencies
RUN apk add --update --no-cache \
    python3 \
    build-base \
    gsl-dev \
    fftw-dev \
    hdf5-dev \
    openmpi-dev \
    bash \
    git \
    openssh \
    g++ 

# Link relevant libraries/packages
RUN ln -s /usr/include/locale.h /usr/include/xlocale.h 

# # Install Vector Class Library
RUN git clone https://github.com/vectorclass/version2.git /usr/include/vectorclass \
 && rm -rf /usr/include/vectorclass/.git

# Copy the current directory contents into the container at /usr/src/app
RUN git clone https://gitlab.mpcdf.mpg.de/vrs/gadget4.git

# Set the working directory
WORKDIR /usr/src/app/gadget4

# Compile Gadget-4
RUN echo SYSTYPE='"Generic-gcc"'>Makefile.systype && make -j 8 DIR=examples/G2-galaxy

# Set the working directory
WORKDIR /usr/src/app/gadget4/examples/G2-galaxy

# Copy ICs
COPY galaxy_littleendian.dat param.txt .

# Run when the container launches
CMD ["bash"]