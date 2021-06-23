#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <pthread.h>
pthread_mutex_t mutex;
char queue[20][80]; 
int front=-1, rear=-1;
int put (char val[80]) { 
	if (rear >= 19) { 
		if (!(rear-front)) { 
			return -1; 
		}  
	memcpy (&queue[0], &queue[front], rear-front+1); 
	rear=rear-front; 
	front = 0; 
	} 
	strcpy(queue[++rear],val); 
}

char *get() { 
	static char temp[80];
	strcpy(temp, queue[front]);
	queue[front++]; 
	return temp;
	
}
void print_queue () { 
	int i; 
	for (i = front+1; i <rear+1; i++) printf("%s\n", queue[i]); 
}

void find_dir(char argv[]);
void search_keyword(char filename[100], char word[100]);
void *threaded_task(void *t){
	if(front==rear) pthread_exit(0);
	char *message;
 	pthread_mutex_lock(&mutex);
	message = (char *)t;
		search_keyword(queue[front+1],message);
	get();
	pthread_mutex_unlock(&mutex);
	return 0;
}
int main(int argc, char* argv[]){
	int result;
	find_dir(argv[3]);

	int num_threads = atoi(argv[2]);
	pthread_t thread[num_threads];
	while(1){
		if(front == rear) break;
		for(int i =0; i<num_threads; i++){
			if(front == rear) break;
			pthread_create(&thread[i], NULL, threaded_task, (void *)argv[4]);
		}
		for(int i=0; i<num_threads; i++){
			pthread_join(thread[i],(void*)&result);
		}
	}	
		return 0;
}
void find_dir(char path_name[100]){
	DIR *dir_info;
	struct dirent *dir_entry;
	char path[50];
	char addpath[50];
	char newpath[50];
	dir_info = opendir(path_name);
	if(dir_info != NULL){
		while(dir_entry = readdir(dir_info)){
			strcpy(path, path_name);
			if( dir_entry->d_type == DT_DIR) {
				if(strcmp(dir_entry->d_name,".")!=0&&strcmp(dir_entry->d_name,"..")!=0 ){
					strcpy(addpath,"");
					sprintf(addpath,"%s/%s",path,dir_entry->d_name);
					find_dir(addpath);
				}	
			} else {
				strcpy(addpath,"");
				sprintf(addpath,"%s/%s",path,dir_entry->d_name);
				//printf("Path: %s\n",path);
				put(addpath);
			}			
			
		 
		}
		closedir(dir_info);
	}
}

void search_keyword(char filename[100], char word[100]){
	FILE *fp;
	char line[100];
	int num=0;
	char result[1024];
	fp = fopen(filename,"r");
	if(fp == NULL){
		printf("%s\n",filename);
		printf("File Open fail\n");
		exit(1);
	}
	while(fgets(line,1024,fp)!=NULL){
		num++;
		if(strstr(line, word)!=NULL){
			sprintf(result,"%s:%d:%s",filename,num,line);
			//result[strlen(result)-1] = '\0';
			printf("%s\n",result);
		}
	}
	fclose(fp);

	
}





