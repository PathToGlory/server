#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <assert.h>
#include <stdlib.h>
#include <cstring>

void clienthandle(int socket);

int main() {
  auto sockfd = socket(AF_INET, SOCK_STREAM, 0);
  assert(sockfd != -1 && "Error during socket initialization");

  sockaddr_in serv_addr;
  memset(&serv_addr, 0, sizeof(serv_addr));
  short port = 9999;

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(port);

  assert(bind(sockfd, reinterpret_cast<sockaddr*>(&serv_addr), sizeof(serv_addr)) != -1 &&
         "Error during binding socket and server structre");

  listen(sockfd, 5);

  sockaddr_in client_addr;
  auto clientLen = sizeof(client_addr);

  while (1) {
    auto newsockfd = accept(sockfd, reinterpret_cast<sockaddr*>(&client_addr), &clientLen);
    assert(newsockfd != -1 && "Error during accepting connection");

    auto pid = fork();
    assert(pid != -1 && "Error on fork");

    // This is the client process
    if (pid == 0) {
      close(sockfd);
      clienthandle(newsockfd);
      exit(0);
    } else {
      close(newsockfd);
    }
  }
}
