#include <unistd.h>
#include <cstring>
#include <cassert>
#include <iostream>

void clienthandle(int socket) {
  char buffer[256];
  const char responseMsq[] = "I've got your message";
  memset(buffer, 0, sizeof(buffer));

  assert(read(socket, buffer, 255) != -1 && "Error during reading");
  std::cout << "Here is the client's message: " << buffer << '\n';

  assert(write(socket, responseMsq, sizeof(responseMsq)));
}
