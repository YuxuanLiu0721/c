#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void main(int argc,char*argv[]){
     if(argc!=2){
	     printf("ERROR:Wrong number of arguments.");
     }
     else{
         FILE*fp=fopen(argv[1],"r");
         if(fp==NULL){
	     printf("Error:no file.");
         }
         else{
              size_t sz;
              fseek(fp,0L,SEEK_END);
              sz=ftell(fp);
              rewind(fp);
              char file_data_array[sz+1];
              fread(file_data_array,1,sz+1,fp);
              char*content=file_data_array;
              char* key1="<a href=\"/wiki/";
              char* key2="title=\"";
              char* key3="</a>";
              char* p1=NULL;
              char* p2=NULL;
              char* p3=NULL;
	      while(content!=NULL){
                    p1=strstr(content,key1);
		    p2=strstr(content,key2);
		    p3=strstr(content,key3);
		    if(p1!=NULL&&p2!=NULL&&p3!=NULL){
	               for(int a=0;a<p1-p2;a++){
		           if(p1[15+a]=='\"'){
	                      printf("\n");
                              break;
		           }
		           else{
		                printf("%c",p1[15+a]);
		           }
	               }
	            content=p1+1;
		    }
		    else if(p1!=NULL){
                            content=p1+1;
		    }
		    else{
	                 exit(0);
		    }
            }     
        }
     }	 
} 
