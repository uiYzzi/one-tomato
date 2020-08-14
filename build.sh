#!/bin/bash
cd `dirname $0`
mkdir -p build
qmake ./one-tomato.pro -spec linux-g++ CONFIG+=qtquickcompiler -o build/
cd build/
make
cd ..
mv build/one-tomato dabao/extract/opt/apps/top.yzzi.tomato/files/
rm -rf build
sh dabao/dabao.sh
mv dabao/build/* outdeb/
rm -rf dabao/build
