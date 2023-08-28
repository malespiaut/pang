#!/bin/sh

CONFIG_SHELL=/bin/sh
export CONFIG_SHELL
#PREFIX=/usr/local/devkitPro/devkitGP2X
PREFIX=$GP2XDEV
TARGET=gp2x
export PATH="$PATH:$GP2XDEV/bin"


PATH="$PREFIX:$PREFIX/bin:$PREFIX/$TARGET/bin:$PATH"
export PATH
if [ -f "$PREFIX/$TARGET/bin/sdl-config" ]; then
    SDL_CONFIG="$PREFIX/$TARGET/bin/sdl-config"
    export SDL_CONFIG
fi
cache=cross-config.cache
sh configure --cache-file="$cache" \
	--target=$TARGET --host=$TARGET --build=i386-linux --prefix=$PREFIX \
	$*
status=$?
rm -f "$cache"
exit $status
