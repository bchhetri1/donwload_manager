/*The purpose of this program is create a daemon process.I will use fork to create another process and then end the original process. Before we ends the parent, process we need to make the child process leader ofthe */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/un.h>
#include <netinet/in.h>
#include "extract.c"
#include <errno.h>

#define _GNU_SOURCE

int download_server(){
				pid_t sid = 0;
				pid_t child = fork();
				
				if(child >0){
					exit(EXIT_SUCCESS);
				}
				else if(child < 0){
					exit(EXIT_SUCCESS);
				}
				else{
				

				umask(0);
				pid_t sid;
				sid = setsid();
				if(sid < 0){
					exit(EXIT_FAILURE);
				}
	
				if(chdir("/") < 0){
					exit(EXIT_FAILURE);
				}

				close(STDIN_FILENO);
				close(STDIN_FILENO);
				close(STDERR_FILENO);
				FILE* output = fopen("output.txt", "w+");
				int server_sock = socket(AF_INET, SOCK_STREAM, 0);
				int option = 1;
				setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
				if(server_sock==-1){
					fprintf(output, "exiting at socket\n");
					perror("The file can not be downloaded.socket\n");
					perror("error code: socket() failed\n");
					printf("an error: %d\n",errno);
					fclose(output);
					exit(EXIT_FAILURE);
				}


				struct sockaddr_in  server_addr;
				server_addr.sin_family = AF_INET;
				server_addr.sin_port = htons(4000);
				(server_addr.sin_addr).s_addr = htons(INADDR_ANY);
				
				int is_sock_bind = bind(server_sock,(struct sockaddr*)(&server_addr), sizeof(struct sockaddr));
				if(is_sock_bind == -1){
					fprintf(output, "exiting at bind\n");
					fclose(output);
					perror("The file can not be downloaded.bind\n");
					perror("error code: bind() failed\n");
					exit(EXIT_FAILURE);
				}

				int can_listen = listen(server_sock,128);
				if(can_listen == -1){
					fprintf(output, "exiting at listen\n");
					fclose(output);
					perror("The file can not be downloaded.listen\n");
					perror("error code: listen() failed\n");
					exit(EXIT_FAILURE);
				}
				
				struct sockaddr_in incoming;
				socklen_t addr_len = sizeof(struct sockaddr);
				printf("pid = %lu\n",getpid());
				printf("Hello World!\n");
				fprintf(output, "before accept\n");
				int is_accepted = accept(server_sock, (struct sockaddr*)&incoming, &addr_len);
				printf("hmjgakshgldfadhjkwq\n");
				fprintf(output, "after accept\n");
				if(is_accepted < 0){
					fprintf(output,"accept has problems\n");
					fclose(output);
					perror("The file can not be downloaded.accept\n");
					perror("error code: accept() failed\n");
					exit(EXIT_FAILURE);
				}
				fclose(output);	
			   	FILE *in = fopen("input.txt", "w+");
				if(in == NULL){
					perror("extract_information failed.\n");
					perror("error code: fopen\n");
					exit(EXIT_FAILURE);
				}

			   	while(is_accepted > 0){
					char buf[1024];
				        ssize_t r = read(is_accepted, buf, 1024);
		
					while(r > 0){
						write(fileno(in), buf, r);
						r = read(is_accepted, buf, 1024);
					}						
					
					char **array_folders;
					char **array_urls;
					char **array_times;
					close(is_accepted);	
					
					int did_extract = extract_information(array_folders, array_urls, array_times, in);
			   		//at the end
					if(did_extract < 0){
						perror("The file can not be downloaded.\n");
						exit(EXIT_FAILURE);
					}
		//		fclose(test);


					if(is_accepted < 0){
						perror("The file can not be downloaded.\n");
						perror("error code: accept() failed\n");
						exit(EXIT_FAILURE);
					}
	
			   }//while ends
				close(server_sock);

			}	//		}//else-ends
		
	
	return 0;}//main ends
int main(){
	download_server();
	return 0;
}
