CXX=	g++ $(CFLAGS)
CFLAGS= -g
CLIENT= hello.o
SERVER= goodbye.o

all: hello goodbye

hello: $(CLIENT)
	$(CXX) -o hello $(CLIENT)

goodbye: $(SERVER)
	$(CXX) -o goodbye $(SERVER)
