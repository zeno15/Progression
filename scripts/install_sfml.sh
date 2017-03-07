#!/bin/bash


set -ev

if [[ "$CXX" = "clang++"]] then
	wget http://www.sfml-dev.org/files/SFML-2.4.2-osx-clang.tar.gz --no-check-certificate
	tar -xzvf SFML-2.4.2-osx-clang.tar.gz
	mv SFML-2.4.2-osx-clang $HOME/SFML
elif [[ "$CXX" = "g++"]] then
	wget http://www.sfml-dev.org/files/SFML-2.4.2-linux-gcc-64-bit.tar.gz --no-check-certificate
	tar -xzvf SFML-2.4.2-linux-gcc-64-bit.tar.gz
	mv SFML-2.4.2-linux-gcc-64-bit $HOME/SFML
fi

ls $HOME