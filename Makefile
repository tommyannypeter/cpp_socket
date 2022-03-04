CFLAGS = -std=c++11 -lstdc++

ifeq ($(OS), Windows_NT)
CFLAGS += -lws2_32
endif

slave:
	gcc test_slave.cc -I./ -o slave $(CFLAGS)

server:
	gcc test_server.cc -I./ -o server $(CFLAGS)

client:
	gcc test_client.cc -I./ -o client $(CFLAGS)
