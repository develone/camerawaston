#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mycamera.h"
#define dbg 1
#define dbg1 1
#define dbg2 0
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
			/*
            for(ii=0;ii<mm+nn-1;ii++)

                        printf("\n The Value of output yy=[%d]=%d",ii,yy[ii]);
                        */
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
	double *phor;
	double *pver;
	char *ptest;
	int row, col;
	int *phh;
	int *pxx;
	int *pyy;
	int c;
	int hh[2];
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
		char cam_pre[] = "raspistill  -e bmp  -h 128 -w 128 -t 275 -o thumb";
		sprintf(pframe_suf, "%04d.bmp",count);
		strcat(cam_pre,pframe_suf);
		if(dbg == 1) printf("%s\n",cam_pre);
		cmd = (char *)&cam_pre;
		system(cmd);
		char s3[] = "thumb";
		strcat(s3,pframe_suf);
		if(dbg == 1) printf("%s\n",s3);
		inp = fopen(s3,"rb+");
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
		pg = (char *)malloc(headInfo.width*headInfo.height);
		pb = (char *)malloc( headInfo.width*headInfo.height);
		phor = (double *)malloc( headInfo.width*headInfo.height);
		pver = (double *)malloc( headInfo.width*headInfo.height);
		psum = (double *)malloc( headInfo.width*headInfo.height);
		//printf("%d\n",sizeof(char *));
		printf("%d\n",headInfo.width*headInfo.height);
		printf("pr= 0x%x pg= 0x%x pb= 0x%x \n",pr,pg,pb);
 		for (i = 0; i <headInfo.width ; i++) {
			for (j = 0; j < headInfo.height; j++) {
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
		pg = pg - headInfo.width*headInfo.height;
		pb = pb - headInfo.width*headInfo.height;
		if(dbg == 1) {
			for (i = 0; i <headInfo.width ; i++) {
				for (j = 0; j < headInfo.height; j++) {
					printf("%d %d %d %d %d\n",i,j,pr[i,j],pg[i,j],pb[i,j]);
				}
			}
		}
		fclose(inp);		
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
			c = conv(pxx,phh,pyy,i,j,m,n);
			
		}
		 

		free(pr);
		free(pg);
		free(pb);
		free(phor);
		free(pver);
		free(psum);
		cmd = (char *)&date_cmd;
		system(cmd);		
		count++;
		if(count == 5) flag = 0;
	}

	return 0;
}
