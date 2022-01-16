#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#define SIZE 1024
#define localhost "127.0.0.1"
#define port 3306
#define IP_PROTOCOL 0
#define NET_BUF_SIZE 32
#define cipherKey 'S'
#define sendrecvflag 0
void sending(FILE *document, int file){
  char buf[SIZE] = {0};
  while(fgets(buf, SIZE, document) != NULL) {
    if (send(file, buf, sizeof(buf), 0) == -1) {
      printf("Sending error.\n");
    }
    bzero(buf, SIZE);
  }
}
int main(int argc, char* argv[])
{
	int file;
	struct sockaddr_in addr_of_server;
	char *filename="test.txt";
	FILE* document;
	file = socket(AF_INET, SOCK_STREAM, IP_PROTOCOL);

	if (file < 0)
		printf("\nFile not received!!\n");
	else
		printf("\nFile %d received\n", file);

	int addrlen = sizeof(addr_of_server);
	addr_of_server.sin_family = AF_INET;
	addr_of_server.sin_port = port;
	addr_of_server.sin_addr.s_addr = inet_addr(localhost);
	if (connect(file, (struct sockaddr*)&addr_of_server, addrlen)==-1){
		printf("Socket error\n");
	}
	printf("\n---------Data Received---------\n");
	document = fopen(filename, "r");
  	if (document == NULL) {
    		printf("File reading error.\n");
  	}
  	sending(document, file);
  	printf("File sent successfully.\n");
  	close(file);
	return 0;
}

