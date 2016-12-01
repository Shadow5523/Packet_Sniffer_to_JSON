#include<stdio.h>
#include<jansson.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>

void error(char *msg);

int main(){
  json_error_t err;
  json_t *top, *level1, *level2, *level3;
  const char *packet_num;
  const char *header;
  const char *element;
  FILE *file;

  if((file = fopen("./log.json", "r")) == NULL)
    error("unable to create file");
  
  top = json_loadf(file, 0, &err);
  if(!top)
    error("json_loadf() error!");

  json_object_foreach(top, packet_num, level1){
    printf("%s : \n", packet_num);
    
    json_object_foreach(level1, header, level2){
      printf(" %-5s : \n", header);
      
      json_object_foreach(level2, element, level3){
	printf("  %-8s ", element);
	printf(": %-12s \n", json_string_value(level3));
	
      }
      printf("\n");
    }
    printf("\n");
  }

}




void error(char *msg){
  fprintf(stderr, "%s : %s\n", msg, strerror(errno));
  exit(1);

}
