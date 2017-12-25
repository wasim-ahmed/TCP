// Server side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#define PORT 8080


int main(int argc, char const *argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address,cli_address;
    int opt = 1;
    int addrlen = sizeof(address);
    int cli_addrlen = sizeof(cli_address);
    char buffer[1024] = {0};
    char *hello = "Hello from server";

	char clntName[INET_ADDRSTRLEN];
	FILE *output;

      
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
      
    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
      
    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address, 
                                 sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *)&cli_address, 
                       (socklen_t*)&cli_addrlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }


	printf("Client ip address:%s",inet_ntoa(cli_address.sin_addr));
	printf("\t");
	printf("Client port:%d",ntohs(cli_address.sin_port));
	printf("\n");


/*

if(inet_ntop(AF_INET,&cli_address.sin_addr.s_addr,clntName,sizeof(clntName))!=NULL){
   output = fopen("output.txt","a+");  
   fprintf(output,"%s%c%d",clntName,'/',ntohs(cli_address.sin_port));  
   fclose(output);
} else {
   printf("Unable to get address\n"); // i just fixed this to printf .. i had it as print before
}

*/

    valread = read( new_socket , buffer, 1024);
    printf("%s\n",buffer );
    send(new_socket , hello , strlen(hello) , 0 );
    printf("Hello message sent\n");
    return 0;
}


