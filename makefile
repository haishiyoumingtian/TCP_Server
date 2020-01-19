OBJ = main.o pthread.o tcp.o server.o
TAR = App/app

SOURCE = Source/

$(TAR): $(OBJ)
	g++ $(OBJ) -lpthread -o  $(TAR)

main.o:$(SOURCE)main.cpp 
	g++ $(SOURCE)main.cpp -c -I Header

pthread.o:$(SOURCE)pthread.cpp 
	g++ $(SOURCE)pthread.cpp -c -I Header

tcp.o:$(SOURCE)tcp.cpp 
	g++ $(SOURCE)tcp.cpp -c -I Header

server.o:$(SOURCE)server.cpp 
	g++ $(SOURCE)server.cpp -c -I Header

clean:
	rm -rf $(OBJ) $(TAR)