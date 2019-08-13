#include<stdio.h>
typedef struct
{
    unsigned char  Red;
    unsigned char  Green;
    unsigned char  Blue;

} pixel;
#pragma pack(2) /*2 byte packing */
typedef struct
{
unsigned short int type;
unsigned int size;
unsigned short int reserved1,reserved2;
unsigned int offset;


}header;


typedef struct
{
   unsigned int size;
   int width,height;
   unsigned short int bits;

   unsigned int compression;
   unsigned int pixelsize;
   int xresolution,yresolution;
   unsigned int ncolors;
   unsigned int importantcolors;

}headerInfo;

void main()
{

 
   header head;
   headerInfo headInfo;
 int counter=0;
   FILE *leftpixel;
   leftpixel = fopen("left.bmp","rb+");
   if(leftpixel==NULL)
   {
      printf("Error opening first file");

   }


fread(&head,1,sizeof(head),leftpixel);
printf("%x ",head.type);
printf("%u ",head.size);
printf("dec offset %u hex offset %x",head.offset,head.offset);
printf("\n");
fread(&headInfo,1,sizeof(headInfo),leftpixel);
printf("size %d ",headInfo.size);
printf("size 0x%x ",headInfo.size);
printf("bits %d ",headInfo.bits);
printf("compress %d ",headInfo.compression);
printf("compress 0x%x ",headInfo.compression);
printf("pixelsize %d ",headInfo.pixelsize);
printf("colors %d ",headInfo.ncolors);
printf("%d ",headInfo.width);
printf("%d ",headInfo.height);
printf("%d ",sizeof(unsigned char));
printf("\n");

fseek(leftpixel,54,SEEK_SET);
pixel im[480][640];

int i,j;

          for (i = 0; i < 480; i++) {
        for (j = 0; j < 640; j++) {

           fread(&im[i][j], sizeof(unsigned char),headInfo.pixelsize, leftpixel);
 if(im[i][j].Red>(im[i][j].Green+im[i][j].Blue))
 //printf("0x%x \n",im[i][j]);
         {
counter++;
 

         }    
}
}




    printf("counter =%d ", counter); 

    printf("\n");
    /*
    for(i=0;i<256;i++) {
		for(j=0;j<256;j++) {
			printf("0x%x " ,im[i][j]);
		}
	}
	printf("\n");
	*/ 
}  
