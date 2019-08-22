#include<stdio.h>


int x[15],h[15],y[15];
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
                                    printf("%d %d %d %d %d %d\n",ii,jj,ii-jj,yy[ii],xx[jj],hh[ii-jj]);

                        }

            }



            //displaying the o/p

            for(ii=0;ii<mm+nn-1;ii++)

                        printf("\n The Value of output y[%d]=%d",ii,yy[ii]);
            return 0;

}

main()
{               int i,j,m,n;
                int *x1,*h1,*y1;
                int c;

                printf("\n enter value for m");        
                scanf("%d",&m); 
                printf("\n enter value for n");
                scanf("%d",&n);

                printf("Enter values for i/p x(n):\n");

                for(i=0;i<m;i++)                           
                           scanf("%d",&x[i]);   
             

               printf("Enter Values for i/p h(n) \n");
               for(i=0;i<n; i++)         
                           scanf("%d",&h[i]);
            x1 = &x[0];
            h1 = &h[0];
            y1 = &y[0];
            c = conv(x1, h1,y1,i,j,m,n);

 }
