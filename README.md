# cpp_socket

This is a socket module written in c++.

# Usage

## Prepare `Socket`

Prepare `SocketConfig` before using `Socket`.

`SocketConfig` is defined as below:

```c++
struct SocketConfig {
    std::string host = "127.0.0.1";
    uint16_t port;
    int max_connection_num = 1;
    int buffer_size = 16384;
};
```

Then put `SocketConfig` as input argument of `Socket`.

```c++
Socket(SocketConfig config);
```

# API of `Socket`
```c++
void wait_for_connection();
void send_string(std::string str);
std::string receive_string();
void close_server();
```

## Test

To be added.
