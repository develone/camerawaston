#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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


int main(void) {
	//int ky = [1,2,1; 0,0, 0; -1, -2 ,-1];
	//int kx = [1 ,0 ,-1; 2,0,-2; 1, 0 ,-1];
	char h[3];
	int i,j;
	char *r;
	char *g;
	char *b;
	char *cmd;
	//char s[];
	//          0123456789012345678901234567890123456789012345678901234567 
	//char s2[70] = "raspistill -e bmp -vf -h 128 -w 128 -t 275 -o framethumb";
	char s1[] = "date";
	
	char nd[8];
	char *pe;
	pe = &nd;
	int flag;
	flag = 1;
	int count;
	count = 0;
	FILE *inp;
	struct rec
	{
		char raw_buf[3];
	};
	struct rec my_record; 
	header head;
	headerInfo headInfo;
	
		
	
	while (flag == 1) {
		//          0123456789012345678901234567890123456789012345678901234567
		char s[] = "raspistill -e bmp -vf -h 128 -w 128 -t 275 -o thumb";
		sprintf(pe, "%04d.bmp",count);
		strcat(s,pe);
		printf("%s\n",s);
		cmd = (char *)&s;
		system(cmd);
		char s3[] = "thumb";
		strcat(s3,pe);
		printf("%s\n",s3);
		inp = fopen(s3,"rb+");
		if(inp==NULL)
		{
			printf("Error opening first file");
		}	 
		 
		fread(&head,1,sizeof(head),inp);
		
		printf("%x ",head.type);
		printf("%u ",head.size);	
		printf("dec offset %u hex offset %x ",head.offset,head.offset);
		fread(&headInfo,1,sizeof(headInfo),inp);
 
		printf("bits %d ",headInfo.bits);
		printf("%d ",headInfo.width);
		printf("%d ",headInfo.height);

		printf("\n");
		
		
		
		
 		for (i = 0; i < 128; i++) {
			for (j = 0; j < 128; j++) {
				fread(&my_record,sizeof(struct rec),1,inp);
				r = (char *)my_record.raw_buf[0];
			
				g = (char *)my_record.raw_buf[1];
				
				b = (char *)my_record.raw_buf[2];
				
				printf("%d %d %d %d %d\n",i,j,r,g,b);
				r++;
				g++;
				b++;
			}
		}
		
		fclose(inp);
		
 
		cmd = (char *)&s1;
		system(cmd);		
		count++;
		if(count == 5) flag = 0;
	}
	return 0;
}
