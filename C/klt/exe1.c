#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mycamera.h"
#include <wiringPi.h>

#include "pnmio.h"
#include "klt.h"

#define dbg 0
#define dbg1 1
#define dbg2 0
#  define PIN_SW 5 //BCM24 	PIN 18, GPIO.5, IOB_79	T9


int main(void) {
	
	 
 
	char h[3];
	int i,j,m,n;
	//for(i=n;i<=m+n-1;i++) {
		//ky[i]=0;
	char *r;
	char *g;
	char *b;
	char *pr;
	char *pg;
	char *pb;
	char *prwr;
 	char *pgwr;
 	char *pbwr;


	char *ptest;
	int row, col;
	int *phh;
	int *pxx;
	int *pyy;
	int c;
	int hh[2];
	int flag = 1;
	int flag1 = 1;
	char	ir_sw = 0;
	
	//klt variables from example1.c
	unsigned char *img1,*img2,*img3;
	KLT_TrackingContext tc1,tc2,tc3;
	KLT_FeatureList fl1,fl2,fl3;
	int nFeatures = 10;
	int ncols, nrows;
	int rowsdn,rows,offset,endofline;
	wiringPiSetup();
	
	pinMode(PIN_SW, INPUT);

	if(dbg1==1) {
		char a[2];
		a[0]=100;
		a[1]=125;
		a[2]=255;
		printf("%d %d %d 0x%x 0x%x 0x%x\n",a[0],a[1],a[2],&a[0],&a[1],&a[2]);
		ptest = &a[0];
		printf("0x%x 0x%x\n",*ptest,ptest);
		ptest++;
		printf("0x%x 0x%x\n",*ptest,ptest);
		ptest++;
		printf("0x%x 0x%x\n",*ptest,ptest);
	}
	char *cmd;
 	char date_cmd[] = "date";
	char cam_cmd[60];
	char frame_suf[8];
	char *pframe_suf;
	pframe_suf = &frame_suf[0];
	
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
		char cam_pre[] = "sudo raspistill  -e bmp -vf -h 128 -w 128 -t 285 -o thumb";
		char s3[] = "thumb";
		printf("%s %d\n",cam_pre,sizeof(cam_pre));
		sprintf(pframe_suf, "%04d.bmp",count);
		
		strcat(cam_pre,pframe_suf);
		printf("%s %d\n",cam_pre,sizeof(cam_pre));
		if(dbg == 1) printf("%s\n",cam_pre);
		while (flag1) {
			if (digitalRead(PIN_SW)) {
				ir_sw |= 0x1;
				//printf("ir_sw= 0x%x no nut\n",ir_sw);
				//printf("\n");
			}	
			else {
				ir_sw = 0x0;
				printf("ir_sw= 0x%x nut coming\n",ir_sw);
		
				cmd = (char *)&cam_pre;
				system(cmd);
				flag1 = 0;
		}
	}
		char s4[] = "thumb";
		strcat(s4,pframe_suf);
		printf("%s %d \n",s4,sizeof(s4));
		//if(dbg == 1) printf("%s\n",s3);
		inp = fopen("thumb0000.bmp","rb+");
		if(inp==NULL)
		{
			printf("Error opening first file");
		}	 
		 
		fread(&head,1,sizeof(head),inp);
		if(dbg == 1) {
			printf("%x ",head.type);
			printf("%u ",head.size);	
			printf("dec offset %u hex offset %x ",head.offset,head.offset);
		}
		fread(&headInfo,1,sizeof(headInfo),inp);
		if(dbg == 1) {
			printf("bits %d ",headInfo.bits);
			printf("%d ",headInfo.width);
			printf("%d ",headInfo.height);
			printf("\n");
		}
		//allocate memory to store the r g b pixel
		pr = (char *)malloc(headInfo.width*headInfo.height);
		ncols = 80;//number of cols to be extracted
		nrows = 50;//number of rows to be extracted
		prwr = (char *)malloc(ncols*nrows);
		pgwr = (char *)malloc(ncols*nrows);
		pbwr = (char *)malloc(ncols*nrows);
		pg = (char *)malloc(headInfo.width*headInfo.height);
		pb = (char *)malloc( headInfo.width*headInfo.height);
		
		//printf("%d\n",sizeof(char *));
		printf("%d\n",headInfo.width*headInfo.height);
		printf("pr= 0x%x pg= 0x%x pb= 0x%x \n",pr,pg,pb);
		//now reading the img 1 row of 129 cols
		for (j = 0; j < headInfo.height; j++) {
			for (i = 0; i <headInfo.width ; i++) {
			
				fread(&my_record,sizeof(struct rec),1,inp);
				*pr = my_record.raw_buf[0];			
				*pg = my_record.raw_buf[1];				
				*pb = my_record.raw_buf[2];				
				//printf("%d %d %d %d %d\n",i,j,*pr,*pg,*pb);
				pr++;
				pg++;
				pb++;
			}
		}
		printf("pr= 0x%x pg= 0x%x pb= 0x%x \n",pr,pg,pb);
		//befor free the memory need to restore the pointers
		pr = pr - headInfo.width*headInfo.height;
		pg = pg - headInfo.width*headInfo.height;
		pb = pb - headInfo.width*headInfo.height;
		printf("pr= 0x%x pg= 0x%x pb= 0x%x \n",pr,pg,pb);
		offset = 30;
		endofline = headInfo.width - offset - ncols;

		rows = 18;
		rowsdn = (headInfo.width * rows) + offset;
		printf("pr= 0x%x pg= 0x%x pb= 0x%x prwr=0x%x \n",pr,pg,pb,prwr);
		pr = pr + rowsdn; //rows + 1 lines dn + offset
		pg = pg + rowsdn; //rows + 1 lines dn + offset
		pb = pb + rowsdn; //rows + 1 lines dn + offset
		printf("pr= 0x%x pg= 0x%x pb= 0x%x prwr=0x%x \n",pr,pg,pb,prwr);
		for (j = 0; j < nrows;j++) {
			for (i = 0; i < ncols ; i++) {
				*prwr = *pr;
				pr++;
				prwr++;
				*pgwr = *pg;
				pg++;
				pgwr++;	
				*pbwr = *pb;
				pb++;
				pbwr++;			
			}
			pr = pr + endofline;//headInfo.width - offset - ncols
			pr = pr + offset;
			pg = pg + endofline;//headInfo.width - offset - ncols
			pg = pg + offset;
			pb = pb + endofline;//headInfo.width - offset - ncols
			pb = pb + offset;
		}
		printf("pr= 0x%x pg= 0x%x pb= 0x%x prwr=0x%x \n",pr,pg,pb,prwr);
		pr = pr - rowsdn - ((ncols*nrows)+(endofline*nrows)+(offset*nrows));
		prwr = prwr - (ncols*nrows);
		pg = pg - rowsdn - ((ncols*nrows)+(endofline*nrows)+(offset*nrows));
		pgwr = pgwr - (ncols*nrows);
		pb = pb - rowsdn - ((ncols*nrows)+(endofline*nrows)+(offset*nrows));
		pbwr = pbwr - (ncols*nrows);
		printf("%d %d %d %d %d %d \n",pr,rowsdn,(ncols*nrows),(endofline*nrows),prwr,(offset*nrows));
		//pg = pg - headInfo.width*headInfo.height;
		//pb = pb - headInfo.width*headInfo.height;
		printf("pr= 0x%x pg= 0x%x pb= 0x%x prwr=0x%x \n",pr,pg,pb,prwr);
		
		tc1 = KLTCreateTrackingContext();
		KLTPrintTrackingContext(tc1);
		fl1 = KLTCreateFeatureList(nFeatures);
		tc2 = KLTCreateTrackingContext();
		KLTPrintTrackingContext(tc2);
		fl2 = KLTCreateFeatureList(nFeatures);
		tc3 = KLTCreateTrackingContext();
		KLTPrintTrackingContext(tc3);
		fl3 = KLTCreateFeatureList(nFeatures);
		
		img1 = prwr;
		img2 = pgwr;
		img3 = pbwr;
		
		KLTSelectGoodFeatures(tc1, img1, ncols, nrows, fl1);
		KLTSelectGoodFeatures(tc2, img2, ncols, nrows, fl2);
		KLTSelectGoodFeatures(tc3, img3, ncols, nrows, fl3);
		printf("\nIn first image:\n");
		for (i = 0 ; i < fl1->nFeatures ; i++)  {
			printf("Feature #%d:  (%f,%f) with value of %d\n",
			i, fl1->feature[i]->x, fl1->feature[i]->y,
			fl1->feature[i]->val);
			printf("Feature #%d:  (%f,%f) with value of %d\n",
			i, fl2->feature[i]->x, fl2->feature[i]->y,
			fl2->feature[i]->val);
			printf("Feature #%d:  (%f,%f) with value of %d\n",
			i, fl3->feature[i]->x, fl3->feature[i]->y,
			fl3->feature[i]->val);
		}

		KLTWriteFeatureListToPPM(fl1, img1, ncols, nrows, "feat1r.ppm");
		KLTWriteFeatureList(fl1, "feat1r.txt", "%3d");
		KLTWriteFeatureListToPPM(fl2, img2, ncols, nrows, "feat1g.ppm");
		KLTWriteFeatureList(fl2, "feat1g.txt", "%3d");
		KLTWriteFeatureListToPPM(fl3, img3, ncols, nrows, "feat1b.ppm");
		KLTWriteFeatureList(fl3, "feat1b.txt", "%3d");
		pgmWriteFile("thumb0000r.pgm",prwr,ncols,nrows);
		pgmWriteFile("thumb0000g.pgm",pgwr,ncols,nrows);
		pgmWriteFile("thumb0000b.pgm",pbwr,ncols,nrows);
		//pgmWriteFile("thumb0000.pgm",pr,headInfo.width,headInfo.height);
		if(dbg == 1) {
			for (i = 0; i <headInfo.width ; i++) {
				for (j = 0; j < headInfo.height; j++) {
					printf("%d %d %d %d %d\n",i,j,pr[i,j],pg[i,j],pb[i,j]);
				}
			}
		}
				
		
		 
		fclose(inp);
		free(prwr);
		free(pgwr);
		free(pbwr);
		free(pr);
		free(pg);
		free(pb);

		cmd = (char *)&date_cmd;
		system(cmd);
		flag1 = 1;		
		//count++;
		//if(count == 5) flag = 0;
	}

	return 0;
}
