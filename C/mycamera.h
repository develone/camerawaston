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

