import socket
import sys


def write_file(client_socket , filename):
    ## Open the file in write mode ("w")
    fp = open(filename, "wb")
    if(fp == None) : ## Check if file opening failed
        print("[-]Error in creating file."); ## Print error message
        exit(1); ## Exit the program

    ## Loop to continuously receive data
    while True:
        ## Receive data from the client socket (client_socket) into the buffer
        ## recv returns the number of bytes received, 0 if connection closed, -1 on error
        n = client_socket.recv(1024)
        if(not n): ## If connection closed (n=0) or error (n<0)
            break; ## Exit the loop

        ## Write the received data (as a string) from the buffer to the file
        ## Potential Issue: recv doesn't guarantee null-termination. If n == SIZE,
        ## fprintf might read past the end of valid data. Using fwrite(buffer, 1, n, fp);
        ## would be safer.
        fp.write(n)

    return

def start_client(host, port, file_name):
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    print("Server socket created. ")
    try:
        client_socket.connect((host, port))
        print(f"Connecting to {host}:{port}...")
        print("Connected to server!")

        write_file(client_socket , file_name)
        print("Data written in the text file")

        client_socket.close()
        print("\nConnection closed")

    except ConnectionRefusedError:
        print("[ERROR] Unable to connect to the server.")

if __name__ == "__main__":
    if len(sys.argv) != 4:
        print("Usage: python client.py <host> <port> <file_name>")
    else:
        start_client(sys.argv[1], int(sys.argv[2]), str(sys.argv[3]))