import socket

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect(('localhost', 13579))
print(client.recv(1024))
client.sendall("I'm here!")
client.close()
