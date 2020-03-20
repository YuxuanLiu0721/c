/* FILE: A3_solutions.c is where you will code your answers for Assignment 3.
 * 
 * Each of the functions below can be considered a start for you. They have 
 * the correct specification and are set up correctly with the header file to
 * be run by the tester programs.  
 *
 * You should leave all of the code as is, especially making sure not to change
 * any return types, function name, or argument lists, as this will break
 * the automated testing. 
 *
 * Your code should only go within the sections surrounded by
 * comments like "REPLACE EVERTHING FROM HERE... TO HERE.
 *
 * The assignment document and the header A3_solutions.h should help
 * to find out how to complete and test the functions. Good luck!
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "A3_provided_functions.h"

unsigned char*
bmp_open( char* bmp_filename,        unsigned int *width, 
          unsigned int *height,      unsigned int *bits_per_pixel, 
          unsigned int *padding,     unsigned int *data_size, 
          unsigned int *data_offset                                  )
{
  unsigned char *img_data=NULL;
  // REPLACE EVERYTHING FROM HERE
  FILE *bmpfile = fopen (bmp_filename,"rb");
  if(bmpfile == NULL){
     return NULL;
  }
  else{
      char b,m;
      fread (&b,1,1,bmpfile);
      fread (&m,1,1,bmpfile);
      unsigned int overallFileSize;
      fread(&overallFileSize,1,sizeof(unsigned int),bmpfile);
      *data_size = overallFileSize;
      rewind(bmpfile);
      img_data = (unsigned char*)malloc(overallFileSize*sizeof(char));
      if(fread(img_data,1,overallFileSize,bmpfile)!=overallFileSize){
         return NULL;
      }
      *width = *((unsigned int*)(img_data+18));
      *height = *((unsigned int*)(img_data+22));
      *bits_per_pixel =  *((unsigned short*)(img_data+28));
      int length = (*width)*(*bits_per_pixel)/8;
      if(length%4 ==0){
	      *padding = 0;
      }
      else{
	      *padding = 4-(length%4);
      }
      *data_offset =*(unsigned int*)(img_data+10);
  // TO HERE!  
  return img_data;  
}
}

void 
bmp_close( unsigned char **img_data )
{
  // REPLACE EVERYTHING FROM HERE
  free(*img_data);
  img_data=NULL;
  // TO HERE!  
}

unsigned char***  
bmp_scale( unsigned char*** pixel_array, unsigned char* header_data, unsigned int header_size,
           unsigned int* width, unsigned int* height, unsigned int num_colors,
           float scale )
{
  unsigned char*** new_pixel_array = NULL; 
  // REPLACE EVERYTHING FROM HERE
  *width = (unsigned int)((*width)*scale);
  *height = (unsigned int)((*height)*scale);
  new_pixel_array = (unsigned char***)malloc( sizeof(unsigned char**) * (*height));
  if( pixel_array == NULL ){
      return NULL;
  }
    for( int row=0; row<*height; row++ ){
    new_pixel_array[row] = (unsigned char**)malloc( sizeof(unsigned char*) * (*width) );
    for( int col=0; col<*width; col++ ){
      new_pixel_array[row][col] = (unsigned char*)malloc( sizeof(unsigned char) * (num_colors) );
    }
  }

  for( int row=0; row<*height; row++ )
    for( int col=0; col<*width; col++ )
      for( int color=0; color<num_colors; color++ )
        new_pixel_array[row][col][color] = pixel_array[(unsigned int)(row/scale)][(unsigned int)(col/scale)][color];
  unsigned int residue = ((*width)*num_colors)%4;
  unsigned int pdd = 4-residue;
  unsigned int padding =0;
  if(residue !=0){
	  padding = pdd;
  }
  
  *((unsigned int*)(header_data+2)) = (*height)*(num_colors*(*width)+padding + header_size) ;
  *((unsigned int*)(header_data+18)) = *width;
  *((unsigned int*)(header_data+22)) = *height;
  // TO HERE! 
  return new_pixel_array;
}         

int 
bmp_collage( char* background_image_filename,     char* foreground_image_filename, 
             char* output_collage_image_filename, int row_offset,                  
             int col_offset,                      float scale )
{
  // REPLACE EVERYTHING FROM HERE
  unsigned char* back_header_data;
  unsigned char* fore_header_data;
  unsigned int back_header_size;
  unsigned int back_height;
  unsigned int fore_height;
  unsigned int back_width;
  unsigned int fore_width;
  unsigned int fore_header_size;
  unsigned int back_num_colors;
  unsigned int fore_num_colors;
  unsigned char*** back_pixel_array=NULL;
  unsigned char*** fore_pixel_array=NULL;
  back_pixel_array=bmp_to_3D_array(background_image_filename,
                                   &back_header_data,
                                   &back_header_size,
                                   &back_width,
                                   &back_height,
                                   &back_num_colors);
  fore_pixel_array=bmp_to_3D_array(foreground_image_filename,
                                   &fore_header_data,
                                   &fore_header_size,
                                   &fore_width,
                                   &fore_height,
                                   &fore_num_colors);
  if(back_pixel_array==NULL||fore_pixel_array==NULL){
     return -1;
  }
  //rescale
  unsigned char ***scale_pixel_array = 
                bmp_scale(fore_pixel_array,
                          fore_header_data,
                          fore_header_size,
                          &fore_width,
                          &fore_height,
                          fore_num_colors,
                          scale);
  
  //find transparent and assign the value.
  for( int row=row_offset; row<fore_height+row_offset; row++ )
    for( int col=col_offset; col<fore_width+col_offset; col++ )
      for( int color=0; color<fore_num_colors; color++ )
        if(scale_pixel_array[row-row_offset][col-col_offset][color] != 0 ){
           back_pixel_array[row][col][color] = scale_pixel_array[row-row_offset][col-col_offset][color];
        }

  bmp_from_3D_array(output_collage_image_filename,
                      back_header_data,
                      back_header_size,
                      back_pixel_array,
                      back_width,
                      back_height,
                      back_num_colors);
  
  if(output_collage_image_filename==NULL){
     return -1;
  }
  bmp_close(*fore_pixel_array);
  bmp_close(*back_pixel_array);

  // TO HERE!
  return 0;
}              

