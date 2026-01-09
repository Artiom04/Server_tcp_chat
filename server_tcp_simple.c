
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>  
#include <sys/socket.h> 
#include <netinet/in.h>

void error(char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]) {
     int sockfd, newsockfd1, newsockfd2;
     int portno, clilen1, clilen2;
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr1, cli_addr2;
     int n, counter;
     pid_t pid;

     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }

     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) {
        error("ERROR opening socket");
     }

     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);

     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0)
              error("ERROR on binding");

     listen(sockfd,5);

     do {
          clilen1 = sizeof(cli_addr1);
	        clilen2 = sizeof(cli_addr2);

	        newsockfd1 = accept(sockfd, (struct sockaddr*) &cli_addr1, (socklen_t *)&clilen1);
          newsockfd2 = accept(sockfd, (struct sockaddr*) &cli_addr2, (socklen_t *)&clilen2);

          if ( newsockfd1 < 0 || newsockfd2 < 0){
          error("Error not accept");
          }

          pid = fork();

          if(pid == 0){
	          close(sockfd);
	          bzero(buffer, 256);

	          n = read(newsockfd1,buffer, strlen(buffer));
            if (n < 0) {
            	error("ERROR reading from socket");
            }

	          if(strncmp(buffer,"QUIT",4) == 0)break;

	          n = write(newsockfd2, buffer, strlen(buffer));
	          if (n < 0) {
              		error("ERROR writing to socket");
            }

	          bzero(buffer,256);

	          n = read(newsockfd2,buffer, strlen(buffer));
            if (n < 0) {
            		error("ERROR reading from socket");
            }

	          if(strncmp(buffer,"QUIT",4) == 0)break;

	          n = write(newsockfd1, buffer, strlen(buffer));
	          if (n < 0) {
              		error("ERROR writing to socket");
            }

	          
          }else{

            close(newsockfd1);
            close(newsockfd2);
          }

          close(newsockfd1);
          close(newsockfd2);
          return 0;

        }while (1);
        return 0;
}
    
