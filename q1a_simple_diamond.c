#include<stdio.h>
#include<stdlib.h>

void main(int argc, char*argv[])
{     
      if (argc!=2){
         printf("Wrong number of arguments. One required.\n");
      }
      else{
           int height=atoi(argv[1]);
           if(height<0||height%2==0){
           printf("Bad argument. Height must be positive odd integer.\n");
           }
           else{
                int a;
                int b;
                for(a=0;a<height;a=a+1){
                    for(b=0;b<height;b=b+1){
                        if (a>height/2){
                            if (abs(b-height/2)<=a-2*(a-height/2)){      
                                 printf("*");
                            }
                            else{
                                 printf(" ");
                            }
                        }
                        else{
                             if (abs(b-height/2)<=a){
                                 printf("*");
                             }
                             else{
                                 printf(" ");
                             }
                        }
                    }
                 printf("\n"); 
                 }
            }
       }
}
       
