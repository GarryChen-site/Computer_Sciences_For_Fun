
FROM ubuntu:20.04

# this is for timezone config
ENV DEBIAN_FRONTEND=noninteractive 
ENV TZ=Asia/Shanghai
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt-get update
#-y is for accepting yes when the system asked us for installing the package
RUN apt-get install -y build-essential cmake git openssh-server gdb pkg-config valgrind systemd-coredump