# Makefile for echo client and server

CXX=			g++ $(CCFLAGS)

ECHO-SERVER=		queue.o message.o echo-server.o server.o
MESSAGE=				queue.o
MYQUEUE=				message.o
ECHO-CLIENT=		echo-client.o client.o
OBJS =			$(ECHO-SERVER) $(ECHO-CLIENT) $(MYQUEUE)

LIBS= -pthread

CCFLAGS= -g -std=c++11 

all:	echo-server echo-client

message:$(MESSAGE)
	$(CXX) -o message $(MESSAGE) $(LIBS)

echo-server:$(ECHO-SERVER)
	$(CXX) -o server $(ECHO-SERVER) $(LIBS)

echo-client:$(ECHO-CLIENT)
	$(CXX) -o client $(ECHO-CLIENT) $(LIBS)

myqueue:$(MYQUEUE)
	$(CXX) -o myqueue $(MYQUEUE) $(LIBS)

clean:
	rm -f $(OBJS) $(OBJS:.o=.d)

realclean:
	rm -f $(OBJS) $(OBJS:.o=.d) server client message myqueue


# These lines ensure that dependencies are handled automatically.
%.d:	%.cc
	$(SHELL) -ec '$(CC) -M $(CPPFLAGS) $< \
		| sed '\''s/\($*\)\.o[ :]*/\1.o $@ : /g'\'' > $@; \
		[ -s $@ ] || rm -f $@'

include	$(OBJS:.o=.d)
