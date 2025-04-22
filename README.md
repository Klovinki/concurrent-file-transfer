File transfer using TCP Socket

Server:

`$ g++ -o server server.cpp`

`$ ./server <address> <port> <file>`

example:
`$ ./server 127.0.0.1 8080 tekst.txt`

Client:

`$ python3 client.py <address> <port>`

example:
`$ python3 client.py 127.0.0.1 8080`
