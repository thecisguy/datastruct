CFLAGS =-std=c11 -pipe -Wall -fdiagnostics-color=auto \
	-march=native -O3 -shared -fPIC -Werror
LDFLAGS=

default: libdatastruct.so

libdatastruct.so: lnkdlst.o priqueue.o
	gcc $(CFLAGS) $(LDFLAGS) -o libdatastruct.so lnkdlst.o priqueue.o

lnkdlst.o: lnkdlst.c lnkdlst.h
	gcc $(CFLAGS) -c -o lnkdlst.o lnkdlst.c

lnkdlst.o: priqueue.c priqueue.h lnkdlst.h
	gcc $(CFLAGS) -c -o lnkdlst.o lnkdlst.c

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
