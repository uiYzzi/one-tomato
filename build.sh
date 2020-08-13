#!/bin/bash
cd `dirname $0`
mkdir -p build
qmake ./one-tomato.pro -spec linux-g++ CONFIG+=qtquickcompiler -o build/
cd build/
make
