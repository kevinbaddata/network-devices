#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>

int main(int argc, char const *argv[])
{

  struct* ifaddrs address;


  if (getifaddrs(&address) == -1) {
    perror("getifaddrs");
    exit(EXIT_FAILURE);
  }

  while(address != NULL)
    {
        int family = address->ifa_addr->sa_family;

        if(family == AF_INET || family == AF_INET6)
        {
            printf("%s: ", address->ifa_name);
            printf("%s", family == AF_INET ? "IPv4" : "IPv6");

            char ap[100];

            const int family_size = family == AF_INET ? 
            sizeof(struct sockaddr_in) : sizeof(struct sockaddr_in6);
            getnameinfo(address->ifa_addr,
            family_size, ap, sizeof(ap), 0, 0, 0x00000002);
            printf("\t%s\n", ap);
        }

        address = address->ifa_next;
    //...
    }
    //...

    //release memory...
    freeifaddrs(address);  

  
  return 0;
}
