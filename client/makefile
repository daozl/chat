objs=client.o start.o cmd.o handle.o secret_password.o thread.o

client:$(objs)
	gcc $(objs) -o client -lpthread
client.o:client.c
	gcc -c client.c
start.o:start.c
	gcc -c start.c
cmd.o:cmd.c
	gcc -c cmd.c
handle.o:handle.c
	gcc -c handle.c
secret_password.o:secret_password.c
	gcc -c secret_password.c
thread.o:thread.c
	gcc -c thread.c

.PHONY:clean
clean:
	rm client $(objs)


