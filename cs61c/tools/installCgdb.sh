
cd /tmp
! ( test -d cgdb) && git clone https://github.com/cgdb/cgdb.git  
apt-get update
apt install automake -y
apt-get install flex -y
apt-get install texinfo -y
apt-get install libreadline-dev -y

cd cgdb
./autogen.sh
cd ..
build="qweasd13sdfx12esdui1_" # 随机文件名
mkdir $build
cd $build
../cgdb/configure --prefix=$PWD/../prefix
make -srj10
make install

cd cgdb
( test -e  /usr/local/bin/cgdb) && echo "rm -rf /usr/local/bin/cgdb" && rm -rf  /usr/local/bin/cgdb
mv ./cgdb  /usr/local/bin/
message="\n----------------  cgdb install error ---------------- " 
(test -e /usr/local/bin/cgdb ) && message="\n---------------- cgdb install successful     -----------" 
echo -e $message
cd /tmp
( test -d $build) && rm -rf $build


cd /tmp
! ( test -e tcl8.5.19) &&  wget http://archive.ubuntu.com/ubuntu/pool/universe/t/tcl8.5/tcl8.5_8.5.19.orig.tar.gz && \
 tar -xvf tcl8.5_8.5.19.orig.tar.gz
! ( test -e tk8.5.19) && wget http://archive.ubuntu.com/ubuntu/pool/universe/t/tk8.5/tk8.5_8.5.19.orig.tar.gz && \
tar -xvf tk8.5_8.5.19.orig.tar.gz

cd /usr/include
( test -e tcl8.5) && rm -rf tcl8.5

mkdir tcl8.5
cd tcl8.5
cp $installDIr/tk8.5.19/generic/* . -r
cp /$installDIr/tcl8.5.19/generic/* . 

cd /tmp
rm -rf tk8.5* tcl8.5*
