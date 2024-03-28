#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
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

  return server_address;
}


// Bind socket to address and port 
void bind_socket(int socket_fd, struct sockaddr_in server_address)
{
  if (bind(socket_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
  {
    perror("ERROR on binding");
    exit(EXIT_FAILURE);
  }
}

// Listen to connections
void listening(int socket_fd, int log)
{
  if (listen(socket_fd, 5) < 0)
  {
    perror("ERROR on listen");
    exit(EXIT_FAILURE);
  }
}


// Accept connections
void accept_connections(int socket_fd)
{
  struct sockaddr_in client_address;
  socklen_t client_len = sizeof(client_address);

  while (1)
  {
    int new_socket_fd = accept(socket_fd, (struct sockaddr *)&client_address, &client_len);
    if (new_socket_fd < 0)
    {
      perror("ERROR on accept");
      exit(EXIT_FAILURE);
    }

    int message_size;
    int n = read(new_socket_fd, &message_size, sizeof(message_size));
    if (n < 0)
    {
      perror("ERROR reading from socket");
      close(new_socket_fd);
      exit(EXIT_FAILURE);
    }

    char *buffer = (char *)malloc(message_size + 1);
    if (buffer == NULL)
    {
      perror("ERROR allocating memory for message\n");
      close(new_socket_fd);
      exit(EXIT_FAILURE);
    }

    memset(buffer, 0, message_size + 1);

    n = read(new_socket_fd, buffer, message_size);
    if (n < 0)
    {
      perror("ERROR reading message from socket");
      free(buffer);
      close(new_socket_fd);
      exit(EXIT_FAILURE);
    }

    buffer[message_size] = '\0';
    printf("Message from client: %s\n", buffer);

    // Fill in response logic


  }
}

// main function
