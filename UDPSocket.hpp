// UDPSocket.hpp - An OO representation of UDP connections

// Version: 0.4

#ifndef UDPSOCKET_HPP_INCLUDED
#define UDPSOCKET_HPP_INCLUDED

#include <string>

// Standard C header files, needed for the structures and system calls below (e.g. socket, recvfrom, sendto, ...)
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

// Represents a remote host + port number
struct ServAddr {
  struct sockaddr_in servaddr;
  ServAddr(const char*addr, int port) {
   bzero(&servaddr,sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_addr.s_addr=inet_addr(addr);
   servaddr.sin_port=htons(port);
  }
};

struct UDPSocket {
  int fd; // File descriptor, this is used by the library to identify the socket

  // Constructor: opens the socket for UDP
  UDPSocket() {
    fd=socket(AF_INET,SOCK_DGRAM,0);
  }

  // Alternate constructor: opens the socket for UDP, and binds it to a port for receiving packets
  UDPSocket(int port) :UDPSocket() {
    bind(port);
  }

  int bind(int port) {
    struct sockaddr_in servaddr;
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr.sin_port=htons(port);
    ::bind(fd,(struct sockaddr *)&servaddr,sizeof(servaddr));
  }

  // Sends a UDP packet to ServAddr object (remote host + port)
  int sendto(const char*data, size_t len, const ServAddr& a) {
    return ::sendto(
        fd,
        data, len,
        0,
        (struct sockaddr *)(void*)&a.servaddr,sizeof(a.servaddr)
        );
  }

  int send_basic_string(std::basic_string<char> s, const ServAddr& a) {
    return sendto(s.c_str(), s.length(), a);
  }

    int send_float(float s, const ServAddr& a) {
    std::stringstream ss;
      ss << s;
      ss.seekg(0, std::ios::end);
      int str_size = ss.tellg();
      ss.seekg(0, std::ios::beg);
    return send_basic_string(ss.str(), a);
  }

  // Wait for and obtain a UDP packet (returns the size of the data stored in BUF)
  int recvfrom(char*buf, size_t len) {
    return ::recvfrom(fd, buf, len,0,NULL,NULL);
  }

  // Wait for and obtain a UDP packet as a std::string
  std::basic_string<char> recv_string(size_t max_length = 10000) {
    char buf[max_length];
    int n;
    if ((n = recvfrom(buf, max_length)) >= 0) {
      return std::basic_string<char>(buf, n);
    } else {
      // It would be better to throw an exception here
      return std::basic_string<char>();
    }
  }

    int recv_float(float var) {

        return std::stoi(recv_string(100));
}

  // Destructor: closes the socket
  ~UDPSocket() {
    close(fd);
  }
};

// Example usage:

// Send a UDP packet with "hello" (5 bytes) as data, to host 10.3.3.7, port 20

// UDPSocket().sendto("hello", 5, ServAddr("10.3.3.7",20));


#endif // UDPSOCKET_HPP_INCLUDED

