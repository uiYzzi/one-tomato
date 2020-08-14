#!/bin/bash
cd `dirname $0`
mkdir -p build
find extract/opt -type f -print0 |xargs -0 md5sum >md5sums
mv md5sums extract/DEBIAN/md5sums
dpkg-deb -b extract/ build/
