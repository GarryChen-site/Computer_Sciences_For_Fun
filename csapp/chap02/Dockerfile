# Use an official Ubuntu image as a parent
FROM ubuntu:latest

# Set the working directory to /app


# Update package list and install necessary packages
RUN apt-get update && \
    apt-get install -y gcc gdb make && \
    apt-get install -y gcc-multilib g++-multilib

# Set environment variables for 32-bit compilation
ENV CC="gcc -m32"
ENV CXX="g++ -m32"
ENV LD="ld -m elf_i386"
ENV AS="as --32"

# Set environment variables for 64-bit compilation
ENV CC64="gcc -m64"
ENV CXX64="g++ -m64"
ENV LD64="ld -m elf_x86_64"
ENV AS64="as --64"

# Set the default command to run when the container starts

