#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mycamera.h"

int main(void) {
	//int ky = [1,2,1; 0,0, 0; -1, -2 ,-1];
	//int kx = [1 ,0 ,-1; 2,0,-2; 1, 0 ,-1];
	char h[3];
	int i,j;
	char *r;
	char *g;
	char *b;
	char *cmd;
 	char date_cmd[] = "date";
	char cam_cmd[60];
	char frame_suf[8];
	char *pframe_suf;
	pframe_suf = &frame_suf;
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
		//                0123456789012345678901234567890123456789012345678901234567
		char cam_pre[] = "raspistill -n -e bmp -vf -h 128 -w 128 -t 275 -o thumb";
		sprintf(pframe_suf, "%04d.bmp",count);
		strcat(cam_pre,pframe_suf);
		 
		printf("%s\n",cam_pre);
		cmd = (char *)&cam_pre;
		system(cmd);
		char s3[] = "thumb";
		strcat(s3,pframe_suf);
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
		
		cmd = (char *)&date_cmd;
		system(cmd);		
		count++;
		if(count == 5) flag = 0;
	}
	return 0;
}
