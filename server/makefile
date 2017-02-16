objs = server.o start.o sql_handle.o cmd.o
server:$(objs)
	gcc $(objs) -o server -lsqlite3
server.o:server.c
	gcc -c server.c
start.o:start.c
	gcc -c start.c
sql_handle.o:sql_handle.c
	gcc -c sql_handle.c
cmd.o:cmd.c
	gcc -c cmd.c

.PHONY:clean
clean:
	-rm server $(objs)
