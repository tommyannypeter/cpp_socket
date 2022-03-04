CFLAGS = -std=c++11 -lstdc++

ifdef _WIN32
CFLAGS += -lws2_32
endif

server:
	gcc test_server.cc -I./ -o server $(CFLAGS)

client:
	gcc test_client.cc -I./ -o client $(CFLAGS)
