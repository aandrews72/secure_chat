#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <err.h>


// Make a socket and returns its file descriptor
int create_socket() 
{
  int socket_fd = socket(AF_INET, SOCK_STREAM, 0);      // For IPv4 & TCP
  if (socket_fd < 0)
  {
    perror("ERROR opening socket");
    exit(EXIT_FAILURE);
  }
  return socket_fd;
}


// Get the server address and ready the connection
struct sockaddr_in get_server_address(char *hostname, int portnumber)
{
  struct hostent *server;
  struct sockaddr_in server_address;

  memset(&server_address, 0, sizeof(server_address));
  server = gethostbyname(hostname);

  if (server == NULL)
  {
    fprintf(stderr, "ERROR no host by that name\n");
    exit(EXIT_FAILURE);
  }

  server_address.sin_family = AF_INET;    // Set family to IPv4
  memcpy(&server_address.sin_addr.s_addr, server->h_addr, server->h_length);
  server_address.sin_port = htons(portnumber);

  return server_address;
}


// Connect to server 
void connect_to_server(int socket_fd)
{
  if (connect(socket_fd, (struct sockaddr *) &get_server_address, sizeof(get_server_address)) < 0)
  {
    perror("ERROR establishing connection");
    exit(EXIT_FAILURE);
  }
}


// Establish handshake



// Communicate with server 



// Main to set up and run client
