FROM centos:latest

#YUM Update and packages
RUN yum fs filter nodocs false
RUN yum -y update
RUN yum -y install man man-pages gcc-c++ bzip2 make valgrind

#GCC 9.1.0
RUN curl http://gnu.mirror.iweb.com/gcc/gcc-9.1.0/gcc-9.1.0.tar.gz -o gcc-9.1.0.tar.gz
RUN tar zxf gcc-9.1.0.tar.gz
RUN cd gcc-9.1.0
RUN ./contrib/download_prerequisites
RUN ./configure --disable-multilib --enable-languages=c,c++
RUN make -j 4
RUN make install
RUN cd ..
RUN rm -Rf gcc-9.1.0*

#GDB 8.3
RUN curl http://ftp.gnu.org/gnu/gdb/gdb-8.3.tar.gz -o gdb-8.3.tar.gz
RUN tar zxf gdb-8.3.tar.gz
RUN cd gdb-8.3
RUN ./configure
RUN make
RUN make install
RUN cd ..
RUN rm -Rf gdb-8.3*

#List versions
RUN gcc --version
RUN gdb --version
RUN ar --version
RUN valgrind --version


#Environmental Variables
RUN echo "export LD_LIBRARY_PATH=/usr/local/lib:/usr/lib:/usr/local/lib64:/usr/lib64" >> ~/.bashrc

#Setting working directory
WORKDIR /home/app