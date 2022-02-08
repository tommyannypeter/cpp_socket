import socket

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect(("localhost", 13579))
client.sendall("I'm here!")
print("py recv: ", client.recv(1024))
client.close()
