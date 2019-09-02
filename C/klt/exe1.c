#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mycamera.h"
#include <wiringPi.h>

#include "pnmio.h"
#include "klt.h"

#define dbg 1
#define dbg1 1
#define dbg2 0
#  define PIN_SW 5 //BCM24 	PIN 18, GPIO.5, IOB_79	T9
int x[128],h[128],y[128];
int conv(int *xx,int *hh,int *yy, int ii,int jj, int mm,int nn) {
            // padding of zeors

            for(ii=mm;ii<=mm+nn-1;ii++)

                        xx[ii]=0;

            for(ii=nn;ii<=mm+nn-1;ii++)

                        hh[ii]=0;



            /* convolution operation */

            for(ii=0;ii<mm+nn-1;ii++)

            {          

                        yy[ii]=0;

                        for(jj=0;jj<=ii;jj++)

                        {

                                    yy[ii]=yy[ii]+(xx[jj]*hh[ii-jj]);
                                    printf("ii=%d jj=%d ii-jj=%d yy=%d xx=%d hh=%d\n",ii,jj,ii-jj,yy[ii],xx[jj],hh[ii-jj]);

                        }

            }



            //displaying the o/p
			
            for(ii=0;ii<mm+nn-1;ii++)

                        printf("\n The Value of output yy=[%d]=%d",ii,yy[ii]);
                        
            return 0;

}

int main(void) {
	/*
	 * ky & kx are need to be convolution with the image
	 * to compute the SobelFilter.
	*/
	double ky[3][3] = { {1.0,2.0,1.0}, {0.0,0.0,0.0},{-1.0,-2.0,-1.0} };
	 
	double kx[3][3] = { {1.0 ,0.0 ,-1.0}, {2.0,0.0,-2.0}, {1.0, 0.0 ,-1.0} };
	double *pky;
	double *pkx;
	double *psum;
	pky = &ky[0][0];
	pkx = &kx[0][0];
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
	double *phor;
	double *pver;
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
	unsigned char *img1;
	KLT_TrackingContext tc;
	KLT_FeatureList fl;
	int nFeatures = 100;
	int ncols, nrows;
	
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
	if(dbg1 == 1) {
		printf("ky=%d kx=%d \n", sizeof(ky),sizeof(kx));
		printf("ky=0x%0x kx=0x%x \n",&ky[0][0],&kx[0][0]);
		for (i = 0; i <3;i++) {
			for (j = 0; j < 3; j++) {
				printf("%d %d ky=%5.1f\n",i,j,*pky);
				pky++;
				//printf("%d %d %5.1f\n",i,j,ky[i][j]);
			}
		}
		pky = pky - 9;
		for (i = 0; i <3;i++) {
			for (j = 0; j < 3; j++) {
				printf("%d %d kx=%5.1f\n",i,j,*pkx);
				pkx++;				
				//printf("%d %d %5.1f \n",i,j,kx[i][j]);
			}
		}
		pkx = pkx - 9;
	}	
	while (flag == 1) {
		//                0123456789012345678901234567890123456789012345678901234567
		char cam_pre[] = "sudo raspistill  -e bmp -vf -h 128 -w 128 -t 300 -o thumb";
		char s3[] = "thumb";
		printf("%s %d\n",cam_pre,sizeof(cam_pre));
		sprintf(pframe_suf, "%04d.bmp",count);
		
		strcat(cam_pre,pframe_suf);
		printf("%s %d\n",cam_pre,sizeof(cam_pre));
		if(dbg == 1) printf("%s\n",cam_pre);
		while (flag1) {
			if (digitalRead(PIN_SW)) {
				ir_sw |= 0x1;
				printf("ir_sw= 0x%x no nut\n",ir_sw);
				printf("\n");
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
		prwr = (char *)malloc(50*50);
		pg = (char *)malloc(headInfo.width*headInfo.height);
		pb = (char *)malloc( headInfo.width*headInfo.height);
		phor = (double *)malloc( headInfo.width*headInfo.height);
		pver = (double *)malloc( headInfo.width*headInfo.height);
		psum = (double *)malloc( headInfo.width*headInfo.height);
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
		//befor free the memory need to restore the pointers
		pr = pr - headInfo.width*headInfo.height;
		pr = pr + 2492; //19 lines dn + 60
		for (j = 20; j <70;j++) {
			for (i = 60; i <110 ; i++) {
				*prwr = *pr;
				pr++;
				prwr++;
			}
			pr = pr + 18;//110 -128 end of row
			pr = pr + 60;
		}
		pr = pr - 2492 - ((50*50)+(78*50));
		prwr = prwr - (50*50);
		pg = pg - headInfo.width*headInfo.height;
		pb = pb - headInfo.width*headInfo.height;
		ncols = 50;
		nrows = 50;
		
		tc = KLTCreateTrackingContext();
		KLTPrintTrackingContext(tc);
		fl = KLTCreateFeatureList(nFeatures);

		img1 = prwr;
		
		KLTSelectGoodFeatures(tc, img1, ncols, nrows, fl);
		printf("\nIn first image:\n");
		for (i = 0 ; i < fl->nFeatures ; i++)  {
			printf("Feature #%d:  (%f,%f) with value of %d\n",
			i, fl->feature[i]->x, fl->feature[i]->y,
			fl->feature[i]->val);
		}

		KLTWriteFeatureListToPPM(fl, img1, ncols, nrows, "feat1.ppm");
		KLTWriteFeatureList(fl, "feat1.txt", "%3d");

		pgmWriteFile("thumb0000.pgm",prwr,50,50);
		//pgmWriteFile("thumb0000.pgm",pr,headInfo.width,headInfo.height);
		if(dbg == 1) {
			for (i = 0; i <headInfo.width ; i++) {
				for (j = 0; j < headInfo.height; j++) {
					printf("%d %d %d %d %d\n",i,j,pr[i,j],pg[i,j],pb[i,j]);
				}
			}
		}
				
		if(dbg2 == 1) {
			hh[0] = 1;
			hh[1] = 0;
			hh[2] = 1;
			phh = &hh[0];
			pxx = &x[0];
			pyy = &y[0];
			for(i=0;i<headInfo.width-4;i++) {
				x[i] = (int)pr[0,i];
				//pxx++;
				printf("%d \n",x[i]);
				//for(j=0;j<headInfo.height;j++) {
				//}
			}
			//printf("\n");
			//pxx = pxx - headInfo.width; 
			m = 128;
			n = 3;
			i = 0;
			j = 0;
			//c = conv(pxx,phh,pyy,i,j,m,n);
			
		}
		 
		fclose(inp);
		free(prwr);
		free(pr);
		free(pg);
		free(pb);
		free(phor);
		free(pver);
		free(psum);
		cmd = (char *)&date_cmd;
		system(cmd);
		flag1 = 1;		
		//count++;
		//if(count == 5) flag = 0;
	}

	return 0;
}
