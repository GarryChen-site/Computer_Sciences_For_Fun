FROM ubuntu:latest

RUN apt-get update && \
    apt-get install -y gcc gdb make gdbserver && \
    apt-get install -y gcc-multilib g++-multilib && \
    apt-get install -y git 

RUN echo "set auto-load safe-path /" >> /root/.gdbinit


COPY installCgdb.sh /

RUN chmod +x /installCgdb.sh

RUN /installCgdb.sh