comp		=gcc
compflags	=-std=c99 -Wall
path		=bin
obj			=	\
			$(path)/main.o	\
			$(path)/generator.o	\
			$(path)/receiver.o	\
			$(path)/queue.o

default : check_bin $(path)/firstTask

check_bin :
	@ if [ ! -d $(path) ]; then mkdir $(path); fi

$(path)/firstTask : $(obj)
	$(comp) $(compflags) -o $(path)/firstTask $(obj) -lpthread

$(path)/%.o : %.c
	$(comp) $(compflags) -c $< -o $@

clean :
	rm -f $(path)/*
