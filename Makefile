all:
	cc -c supergud.c -fPIC -o supergud.o `pkg-config --cflags openssl`
	cc -shared -o libsupergud.so supergud.o
	cc -o supergud supergud.o  main.c `pkg-config --libs openssl` 
