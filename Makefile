all:
	#gcc -o test1 $(mysql_config --cflags) test1.c $(mysql_config --libs)
	#gcc test1.c `mysql_config --cflags --libs`
	g++ d_t_arg.c `mysql_config --cflags --libs`
clean:
	rm test1.o -f
	rm result_pr.o -f
