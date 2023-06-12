CFLAGS = -std=c++11 -lstdc++

ifeq ($(OS), Windows_NT)
CFLAGS += -lws2_32
endif

test_slave:
	gcc test_slave.cc -I./ -o slave $(CFLAGS)

test_server:
	gcc test_server.cc -I./ -o server $(CFLAGS)

test_client:
	gcc test_client.cc -I./ -o client $(CFLAGS)
