#!/usr/bin/env python

import socket
import sys

TCP_IP = '0.0.0.0'
TCP_PORT = 1025
BUFFER_SIZE = 1024

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((TCP_IP, TCP_PORT))
s.listen(1)

conn, addr = s.accept()
print 'Connection address:', addr
while 1:
    data = conn.recv(BUFFER_SIZE)
    if not data: break
    sys.stdout.write(data)
conn.close()
