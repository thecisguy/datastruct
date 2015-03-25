# makefile
# 
# Copyright (C) 2014-2015 - Blake Lowe
#
# This file is part of datastruct.
# 
# datastruct is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# datastruct is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with datastruct. If not, see <http://www.gnu.org/licenses/>.

CFLAGS =-std=c11 -pipe -Wall -fdiagnostics-color=auto \
	-march=native -O3 -shared -fPIC -Werror -D_POSIX_C_SOURCE=200809L
LDFLAGS=

default: libdatastruct.so

all: default

libdatastruct.so: lnkdlst.o priqueue.o vectr.o
	gcc $(CFLAGS) -o libdatastruct.so lnkdlst.o priqueue.o vectr.o $(LDFLAGS)

lnkdlst.o: lnkdlst.c lnkdlst.h
	gcc $(CFLAGS) -c -o lnkdlst.o lnkdlst.c

priqueue.o: priqueue.c priqueue.h lnkdlst.h
	gcc $(CFLAGS) -c -o priqueue.o priqueue.c
	
vectr.o: vectr.c vectr.h
	gcc $(CFLAGS) -c -o vectr.o vectr.c

clean:
	rm -f *~ libdatastruct.so *.o

install: libdatastruct.so lnkdlst.h
	mv libdatastruct.so /usr/local/lib/
	cp lnkdlst.h /usr/local/include/
	chown root:root /usr/local/lib/libdatastruct.so
	chown root:root /usr/local/include/lnkdlst.h
	ldconfig

uninstall:
	rm -f /usr/local/lib/libdatastruct.so /usr/local/include/lnkdlst.h
	ldconfig
