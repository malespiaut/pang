#!/bin/sh

PREFIX=/usr/local/devkitPro/devkitGP2X
TARGET=arm-linux
PATH="$PREFIX/bin:$PREFIX/$TARGET/bin:$PATH"
export PATH
exec make $*
