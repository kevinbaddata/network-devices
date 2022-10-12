// A simple example of using the adapter pattern
// to make a new interface for an existing class.
// The adapter pattern is a structural pattern.
// The adapter pattern is used to make a new interface
// for an existing class. The adapter pattern is used
// when you want to use an existing class, and its
// interface does not match the one you need.


#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <stdio.h>
#include <stdlib.h>

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0


int main(int argc, char const *argv[])
{
    struct ifaddrs *addresses;

    // check if getifaddrs() failed
    if (getifaddrs(&addresses) == -1) {
        printf("getifaddrs call failed\n");
        return EXIT_FAILURE;
    }

    while(addresses != NULL) {
        
        if (addresses->ifa_addr == NULL) { 
            addresses = addresses->ifa_next;

            // continue to the next iteration of the loop...
        }

        // ...

        // get the address family
        int family = addresses->ifa_addr->sa_family;
        if (family == AF_INET || family == AF_INET6) {

            printf("%s\t", addresses->ifa_name);
            
            switch (family) {
                case AF_INET:
                    printf("IPv4\t");
                    break;
                case AF_INET6:
                    printf("IPv6\t");
                    break;
            }
            
            // define a buffer to store the address
            char buffer[100];

            const int family_size = family == AF_INET ?
                sizeof(struct sockaddr_in) : sizeof(struct sockaddr_in6);
            getnameinfo(addresses->ifa_addr,
                    family_size, buffer, sizeof(buffer), 0, 0, NI_NUMERICHOST);
            printf("\t%s\n", buffer);

        }

        addresses = addresses->ifa_next;
    }

    // ...

    // free the linked list
    freeifaddrs(addresses);
    


    return EXIT_SUCCESS;
}

