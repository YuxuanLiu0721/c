#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
void Print_row(int row,int height,int level){
            if(level==1){
                for(int b=0;b<height*2-1;b=b+1){
                      if(abs(b-(height-1))<=row){
                         printf("*");
                      }
                      else{
                         printf(" ");
                      }
                  }
             }
             else{
                  if(row<height/2){
                     for (int a=0; a<height/2; a=a+1){
                          printf(" ");
                     }
                     Print_row(row,height/2,level-1);
                     for (int a=0; a<height/2; a=a+1){
                          printf(" ");
                     }
                  }
                  else{
                       Print_row(row-height/2,height/2,level-1);
                       printf(" ");
                       Print_row(row-height/2,height/2,level-1);
                       
                  }
             }
          
}
void helper(int height,int level){
     for(int a=0;a<height;a=a+1){        
         Print_row (a,height,level);
         printf("\n");
     }

}     
void Print_bottom(int height,int level){
     for(int row=height-1;row>=0;row=row-1){
         Print_row(row,height+1,level);
         printf("\n");
     }
}
bool Power (int n){
     if(n%2!=0){
       return false;
     }
     else{
        if(n/2==1){
       return true;
        }
        else{
           Power(n/2);
        }
     }
}
int power(int n, int m){
    if(m==0){
       return 1;
    }
    else{
         return n*power(n,m-1);
    }
}
   
void main (int argc, char*argv[]){
     if (argc!=3){
         printf("ERROR:Wrong number of arguments. Two required.\n");
      }
      else{
           int height=atoi(argv[1]);
           int level=atoi(argv[2]);
           if(height<0||height%2==0){
           printf("ERROR:Bad argument. Height must be positive odd integer\n");
           }
           else{
                if(Power (height+1)!=true||height< power(2,(level-1))){
                   printf("ERROR:Height does not allow evenly dividing requested number of levels.\n" );
                }
                else{                 
                    helper(height/2+1,level);
                    Print_bottom(height/2,level);
                }
           }
      }

}
          
