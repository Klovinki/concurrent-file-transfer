File transfer using TCP Socket

Server:

`$ g++ -o server server.cpp`

`$ ./server <address> <port> <file_name>`

example:
`$ ./server 127.0.0.1 8080 tekst.png`

Client:

`$ python3 client.py <address> <port> <file_name>`

example:
`$ python3 client.py 127.0.0.1 8080 namatekst.png`
