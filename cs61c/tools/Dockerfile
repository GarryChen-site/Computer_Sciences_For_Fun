FROM ubuntu@sha256:bac6081102aae54ba4bcc714695b8f637e42768c7f376f374c428bab043ddc0f

RUN apt-get update && \
    apt-get install -y gcc gdb make gdbserver && \
    apt-get install -y git 

RUN echo "set auto-load safe-path /" >> /root/.gdbinit

RUN apt-get install bison flex -y && \
    apt-get install tcl-dev tk-dev -y

RUN apt-get install -y valgrind

RUN apt-get update && \
    apt-get install -y software-properties-common && \
    add-apt-repository ppa:deadsnakes/ppa && \
    apt-get install -y python3.8


COPY installCgdb.sh /

RUN chmod +x /installCgdb.sh

RUN /installCgdb.sh

RUN apt-get update && \
    apt-get install libcunit1 libcunit1-dev -y

RUN apt-get update && \
    apt-get install python3.8-dev -y