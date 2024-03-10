Parser=parser
DEBUG=debug
HTTP_SERVER=http_server
cc=g++

.PHONY:all
all:$(Parser) $(DEBUG) $(HTTP_SERVER)

$(Parser):parser.cc
	$(cc) -o $@ $^ -std=c++11 -lboost_system -lboost_filesystem
$(DEBUG):debug.cc
	$(cc) -o $@ $^ -ljsoncpp -std=c++11
$(HTTP_SERVER):http_server.cc
	$(cc) -o $@ $^ -ljsoncpp -std=c++11 -lpthread

.PHONY:clean
clean:
	rm -f parser http_server debug