FROM ubuntu:20.04

RUN apt-get update && \
    apt-get install -y gcc gdb make gdbserver && \
    apt-get install -y git 

RUN echo "set auto-load safe-path /" >> /root/.gdbinit

RUN apt-get install bison flex -y && \
    apt-get install tcl-dev tk-dev -y

RUN apt-get install -y valgrind


COPY installCgdb.sh /

RUN chmod +x /installCgdb.sh

RUN /installCgdb.sh