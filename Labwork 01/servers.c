#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#define SIZE 1024
#define localhost "127.0.0.1"
#define port 3306
#define IP_PROTOCOL 0
void create(int file){
  FILE *document;
  char *filename = "receives.txt";
  char bf[SIZE];
  document = fopen(filename, "w");
  while (1) {
    int n = recv(file, bf, SIZE, 0);
    if (n <= 0){
      break;
    }
    fprintf(document, "%s", bf);
    bzero(bf, SIZE);
  }
  return;
}
int main(int argc, char* argv[]){
  int file;
  int new_file;
  socklen_t size_of_address;
  char bf[SIZE];
  struct sockaddr_in ad, new_server_addr;
  size_of_address = sizeof(new_server_addr);
  file = socket(AF_INET, SOCK_STREAM, IP_PROTOCOL);
  if (file < 0)
        printf("\nFile not received!!\n");
    else
        printf("\nFile %d received\n", file);
  ad.sin_family = AF_INET;
  ad.sin_port = port;
  ad.sin_addr.s_addr = INADDR_ANY;
  if(bind(file, (struct sockaddr*)&ad, sizeof(ad))<0) {
    printf("Fail to bind\n");
  }
  printf("Binding successfully.\n");
  listen(file, 0);
  new_file = accept(file, (struct sockaddr*)&new_server_addr, &size_of_address);
  create(new_file);
  printf("Data written successfully.\n");
  return 0;
}
