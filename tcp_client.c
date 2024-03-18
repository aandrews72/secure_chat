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
    perror("ERROR opening socket\n");
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
    perror("ERROR no host by that name\n");
    exit(EXIT_FAILURE);
  }

  server_address.sin_family = AF_INET;    // Set family to IPv4
  memcpy(&server_address.sin_addr.s_addr, server->h_addr, server->h_length);
  server_address.sin_port = htons(portnumber);

  return server_address;
}


// Connect to server 
void connect_to_server(int socket_fd, struct sockaddr_in servr_address)
{
  if (connect(socket_fd, (struct sockaddr *) &get_server_address, sizeof(get_server_address)) < 0)
  {
    perror("ERROR establishing connection\n");
    exit(EXIT_FAILURE);
  }
}


// Establish handshake
// TODO: find a way to establish a handshake in a secure manner
// consider OpenSSL?


// Communicate with server 
void communicate(int socket_fd)
{
  // Change after we get server running, this is just placeholder code
  // TODO: Get input, dynamically allocate space to store it based on its size 
  //       maybe set a char limit to stop buffer overflows
  //       create error handling for reads and writes
  char *message = "Test";
  int message_length = strlen(message);
  char buffer[1024];
  
  // Send message length
  write(socket_fd, &message_length, sizeof(message_length));
  
  // Sned message
  write(socket_fd, message, message_length);

  // Receive message from server
  memset(buffer, 0, 1024);
  read(socket_fd, buffer, 1023);
  printf("Response: %s\n", buffer);
}


// Main to set up and run client
int main(int argc, char *argv[])
{
  int socket_fd;
  struct sockaddr_in server_address;

  if (argc < 3)
  {
    fprintf(stderr, "usage %s hostname port\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  socket_fd = create_socket();
  server_address = get_server_address(argv[1], atoi(argv[2]));

  // TODO: establish handshake

  communicate(socket_fd);

  close(socket_fd);
  return 0;

}
