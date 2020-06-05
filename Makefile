.PHONY: linux win clean

win : aoi.dll
linux: aoi.so

LUA_INCLUDE = ./include
LUA_LIB = ./ -llua53

CFLAGS = $(CFLAG)
CFLAGS += -g -std=c99 -Wall -fPIC --shared -I$(LUA_INCLUDE)
LDFLAGS = -L$(LUA_LIB)

aoi.dll : aoi.c
	gcc $(CFLAGS) -o $@ $^ $(LDFLAGS)

aoi.so : aoi.c
	gcc $(CFLAGS) -o $@ $^

clean :
	rm aoi.dll aoi.so
