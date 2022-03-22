#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DIM_X	2048
#define DIM_Y	2048

#define DIM_RAD	2048
#define DIM_THT 1024

#define M_INI	0
#define M_FIN	6

#define STEP_P	0.25

#define PI	3.1415926
#define GR_RAD	(PI/180.)

//float mat[DIM_X][DIM_Y];
//float data[DIM_RAD*DIM_THT*2+2];


main()
{

int	x_dim,y_dim,x_0,y_0,r_min,r_max,r_mx,count_rad, 
	count_tht,aux_x,aux_y,i,j,k,a,b,c,d,counter,nn[3],
	ndim=2,isign=1,cont_m,cont_p,x_max,y_max,answer,
	pgi,pgi1,ZERO=0,UN=1;

float	lnr,aa,bb,tht,tht_rad,radstep,thtstep,soma,
	a1,b1,c1,d1,sky,maximum=0.0,
	data1,vet_aux[DIM_RAD+2],
 	vet_aux_real[DIM_RAD+2],vet_aux_imag[DIM_RAD+2],
	freq_save,norma=0.0,pos_ang,inc_ang,x,y,x_inc,
	x_proj,y_proj,cosinc,cospos,sinpos,x_i,x_f,y_i,y_f,
	x1a,x2a,y1a,y2a;

float ** mat;

mat = (float **) malloc(DIM_X * sizeof(float *));
if(NULL == mat){
   free(mat);
   printf("Memory allocation failed while allocating for mat[]/n");
   exit(-1);
}

for( y = 0; y < DIM_X; y++)
{
  mat[(int)y] = (float *) malloc( DIM_Y * sizeof(float));
  
  if(NULL == mat[(int)y]){
    free(mat[(int)y]);
    printf("Memory allocation failed while allocating for mat[x][]/\n");
    exit(-1);
  }
 } 

 float * data;

 data = (float *) malloc((DIM_RAD*DIM_THT*2+2) * sizeof(float *));
 if(NULL == data){
   free(data);
   printf("Memory allocation failed while allocatinf for data[]/n");
   exit(-1);
 }
 
char	infile[80],outfile1[80],outfile2[80],outfile3[80],keyword[80],saving[80];

FILE	*fp_inp,*fp_out1,*fp_out2,*fp_out3;

void	fourn();

mat[0][0]=0.0;
pgi=1;pgi1=1;

puts(" ");
puts("------------------------");
puts("Direct Fourier Transform");
puts("------------------------");


do {
puts("--- waiting...");
/*   printf("infile : ");  */
   scanf("%s",infile);
   } while((fp_inp=fopen(infile,"r"))==NULL);

/* printf("keyword for output files : "); */
scanf("%s",keyword);

puts("--- reading image");

k=1;
fscanf(fp_inp,"%f",&data[k]);
do {
  k++;
   } while((fscanf(fp_inp,"%f",&data[k]))!=EOF);

k--;

if(data[1]==data[2] && data[1]>0.0) {
  x_dim=data[1];
  y_dim=data[2];
  printf("--- dimensions (read) : xdim=%d : ydim=%d\n",x_dim,y_dim);
  for(i=1;i<=x_dim;i++)
    for(j=1;j<=y_dim;j++) {
      mat[i][j]=data[(i-1)*y_dim+j+2];
      if(mat[i][j]>maximum) {
        maximum=mat[i][j];
        x_max=i;y_max=j;
        }
      }
  }
if(data[1]!=data[2] || (data[1]==0.0 && data[1]==0.0) || (data[1]<0.0)) {
  x_dim=sqrt(k);
  y_dim=sqrt(k);
  printf("--- dimensions (not read) : xdim=%d : ydim=%d\n",x_dim,y_dim);
  for(i=1;i<=x_dim;i++)
    for(j=1;j<=y_dim;j++) {
      mat[i][j]=data[(i-1)*y_dim+j];
      if(mat[i][j]>maximum) {
        maximum=mat[i][j];
        x_max=i;y_max=j;
        }
      }
  }

for(i=1;i<=DIM_RAD*DIM_THT*2+2;i++)
  data[i]=0.0;

/* printf("%d %d\n",x_dim,y_dim);
for(i=1;i<=x_dim;i++)
    for(j=1;j<=y_dim;j++)
      printf("%d %d %f\n",i,j,mat[i][j]); */

puts("--- transforming X x Y -> Theta x ln r");

for(i=1;;i++) {
/*  printf("X direction -> %d\n",x_dim);
  printf("Y direction -> %d\n",y_dim);
  printf("maximum (%d) in x=%d and y=%d\n",(int)maximum,x_max,y_max);
  printf("central (Xo,Yo) pixel : ");
  scanf("%d %d",&x_0,&y_0); */
  x_0=x_dim/2;
  y_0=y_dim/2;
  a=x_dim-x_0;
  b=y_dim-y_0;
  r_mx=x_0;
  if(y_0<r_mx)r_mx=y_0;
  if(a<r_mx)r_mx=a;
  if(b<r_mx)r_mx=b;
/*  printf("minimum(>1) and maximum(<%d) radii to analyse (in pixels) : ",x_dim/2); */
  scanf("%d %d",&r_min,&r_max);
/*  printf("position and inclination angles (in degrees) : ");
  scanf("%f %f",&pos_ang,&inc_ang); */
  pos_ang=0.0;
  inc_ang=0.0;

  cosinc=cos(inc_ang*GR_RAD);
  cospos=cos(pos_ang*GR_RAD);
  sinpos=sin(pos_ang*GR_RAD);
  radstep=2.*PI/STEP_P/DIM_RAD;
  thtstep=2.*PI/GR_RAD/DIM_THT;

  counter=0;

  x_i=0.0;x_f=x_dim+1.0;y_i=0.0;y_f=y_dim+1;

  count_tht=1;
  for(tht=0.0;count_tht<=DIM_THT;tht+=thtstep) {
    count_tht++;
    tht_rad=tht*GR_RAD;	
    count_rad=1;
    for(lnr=0.0;count_rad<=DIM_RAD;lnr+=radstep) {
      count_rad++;
      if(lnr>log((double)r_max) || lnr>log((double)r_mx) ||
              lnr<log((double)r_min) ) {
        data[++counter]=0.0;
        data[++counter]=0.0;
        continue;
        }

      x=exp(lnr)*cos(tht_rad);
      y=exp(lnr)*sin(tht_rad);
      x_inc=x*cosinc;
      x_proj=x_inc*cospos+y*sinpos;
      y_proj=y*cospos-x_inc*sinpos;

      aa=x_proj;
      bb=y_proj;

      a=(int)x_proj+x_0;
      b=(int)y_proj+y_0;

      data[++counter]=mat[a][b];
      norma+=data[counter];
      data[++counter]=0.0;
    }
  }

/*  printf("\nAre the values right (y=1/n=2) ? ");
  scanf("%d",&answer); */
  answer=1;
  if(answer==1)break;
}

nn[1]=DIM_THT;	
nn[2]=DIM_RAD;

sprintf(saving,"gal.parm%s",keyword);
fp_out3=fopen(saving,"w");
fprintf(fp_out3,"%s\n",infile);
fprintf(fp_out3,"%s\n",keyword);
fprintf(fp_out3,"%d %d\n",r_min,r_max);

puts("--- calculating 2DFFT");

fourn(data,nn,ndim,isign);

for(i=1;i<=counter;i++) 
  data[i]=data[i]/norma;

for(cont_m=M_INI;cont_m<=M_FIN;cont_m++) {
  counter=cont_m*DIM_RAD*2;
  sprintf(outfile1,"%sm%1d.rip",keyword,cont_m);
  sprintf(outfile2,"%sm%1d.dat",keyword,cont_m);
  fp_out1=fopen(outfile1,"w");
  fprintf(fp_out1,"%d\n",x_dim/2);
  fprintf(fp_out1,"%e\n",norma);
  fp_out2=fopen(outfile2,"w");
  for(cont_p=0;cont_p<DIM_RAD/2;cont_p++) {
    for(i=1;i<=2;i++)
      ++counter;

    vet_aux_real[cont_p+(DIM_RAD/2)+1]=data[counter-1];
    vet_aux_imag[cont_p+(DIM_RAD/2)+1]=data[counter];
    vet_aux[cont_p+DIM_RAD/2+1]=sqrt(pow(data[counter],2.0)+pow(data[counter-1],2.0));
    }

  for(i=1;i<=2;i++)
    ++counter;

  vet_aux_real[DIM_RAD+1]=data[counter-1];
  vet_aux_imag[DIM_RAD+1]=data[counter];
  vet_aux[DIM_RAD+1]=vet_aux[1]=sqrt(pow(data[counter],2.0)+pow(data[counter-1],2.0));

  for(cont_p=(-1)*(DIM_RAD/2)+1;cont_p<=-1;cont_p++) {
    for(i=1;i<=2;i++)
      ++counter;

    vet_aux_real[cont_p+(DIM_RAD/2)+1]=data[counter-1];
    vet_aux_imag[cont_p+(DIM_RAD/2)+1]=data[counter];
    vet_aux[cont_p+(DIM_RAD/2)+1]=sqrt(pow(data[counter],2.0)+pow(data[counter-1],2.0));
    }

    for(j=1;j<=DIM_RAD+1;j++) {
      freq_save=(-1)*STEP_P*DIM_RAD/2+(j-1)*STEP_P;
      if(freq_save>=-50.0 && freq_save<=50.0) {
        fprintf(fp_out2,"%f %e\n",freq_save,vet_aux[j]);
        fprintf(fp_out1,"%e\n",vet_aux_real[j]);
        fprintf(fp_out1,"%e\n",vet_aux_imag[j]);
        }
      }

    fclose(fp_out1);
    fclose(fp_out2);
    }
puts(" ");
}
