default: liblnkdlst.so

liblnkdlst.so: lnkdlst.c lnkdlst.h
	gcc -Wall -O3 -shared -fPIC -o liblnkdlst.so lnkdlst.c

clean:
	rm -f *~ liblnkdlst.so

install: default
	mv liblnkdlst.so /usr/local/lib/
	cp lnkdlst.h /usr/local/include/
	chown root:root /usr/local/lib/liblnkdlst.so
	chown root:root /usr/local/include/lnkdlst.h
	ldconfig

uninstall:
	rm -f /usr/local/lib/liblnkdlst.so /usr/local/include/lnkdlst.h
	ldconfig
