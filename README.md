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

Script to run N clients at the same time (non-blocking):

`$ bash script.sh <address> <port> <file_name> <N>`

example (run 1000 clients at the same time):

`$ bash script.sh 127.0.0.1 8080 received_file.png 1000`
