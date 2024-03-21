#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <err.h>


// TODOS



// Create socket to listen for connections using socket func 
int create_socket()
{
  int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_fd < 0)
  {
    perror("ERROR opening socket");
    exit(EXIT_FAILURE);
  }
  return socket_fd;
}

// Set up server address structure
struct sockaddr_in prepare_server_address(int portnumber)
{
  struct sockaddr_in server_address;
  memset(&server_address, 0, sizeof(server_address));
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = INADDR_ANY;
  server_address.sin_port = htons(portnumber);
}


// Bind socket to address and port 
void bind_socket(int socket_fd, struct sockaddr_in server_address)
{
  if (bind(socket_fd(struct sockaddr *)&server_address, sizeof(server_address)) < 0)
  {
    perror("ERROR on binding");
    exit(EXIT_FAILURE);
  }
}

// Listen to connections



// Accept connections



// Fork for concurrent connections 



// Handshake would go here



// Read clients message 



// Send back a message



// Consider closing logic and close connnection/listening socket 
