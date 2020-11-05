#include <stdio.h>
#include <math.h>
#include <ctype.h>

double * lightcalc(int,int);

int main(void) {
  
  int weapons[3]={1060,1060,1060},armour,slots=5,light,range[3],target,targetbuffer[9],seasoncap=1060,i,j,k,n,auxilliary;
  char temp;
  float delta;
  //Target
  printf("\n░█─── ▀█▀ ░█▀▀█ ░█─░█ ▀▀█▀▀ 　 ░█▀▀▀█ ░█▀▀▀█ ░█─── ░█──░█ ░█▀▀▀ ░█▀▀█\n░█─── ░█─ ░█─▄▄ ░█▀▀█ ─░█── 　 ─▀▀▀▄▄ ░█──░█ ░█─── ─░█░█─ ░█▀▀▀ ░█▄▄▀\n░█▄▄█ ▄█▄ ░█▄▄█ ░█─░█ ─░█── 　 ░█▄▄▄█ ░█▄▄▄█ ░█▄▄█ ──▀▄▀─ ░█▄▄▄ ░█─░█\n");
  i=0;
  while(i==0){
    printf("\nSelect mode:\n\n1.\tGarden Contest\n2.\tCustom value\n3.\tCustom range (n<10 encounters)\n\t->\t");
    scanf("%d",&j);
    switch(j){
      case 1:
        targetbuffer[0]=890;
        targetbuffer[1]=900;
        targetbuffer[2]=910;
        targetbuffer[3]=920;
        n=4;
        printf("Light targets set to 890, 900, 910, and 920.\n");
        i++;
        break;
      case 2:
        printf("Enter target light:\n\t->\t");
        scanf("%d",&targetbuffer[0]);
        n=1;
        i++;
        break;
      case 3:
        printf("Enter range lower bound:\n\t->\t");
        scanf("%d",&range[0]);
        printf("Enter range upper bound:\n\t->\t");
        scanf("%d",&range[1]);
        printf("Enter number of encounters:\n\t->\t");
        scanf("%d",&n);
        range[2]=(range[1]-range[0])/(n-1);
        printf("Encounters -> %d\nRange step size -> %d\n",n,range[2]);
        printf("\nLight targets set to ");
        for(k=0;k<n;k++){
          targetbuffer[k]=range[0]+k*range[2];
          if(k==n-1)printf("and %d.\n",targetbuffer[k]);
          else printf("%d, ",targetbuffer[k]);
        }        
        i++;
        break;
      default:
        printf("\nFormat error. Enter '1','2', or '3':\n");
        break;
    } 
  }
  //Weapons
  i=0;
  while(i==0){
    printf("\nAssuming 1060 weapons. Is this true? (Y/N)\n\t->\t");
    scanf("%s",&temp);
    switch(tolower(temp)){
      case 'y':
        i++;
        break;
      case 'n':
        printf("\nKINETIC light:\n\t->\t");
        scanf("%d",&weapons[0]);
        printf("\nENERGY light:\n\t->\t");
        scanf("%d",&weapons[1]);
        printf("\nPOWER light:\n\t->\t");
        scanf("%d",&weapons[2]);
        i++;
        break;
      default:
        printf("\nFormat error. Enter 'y' or 'n':\n");
        break;
    }
  }
  i=0;
  while(i<3){
    light+=weapons[i];
    i++;
  }

  double *output;
  printf("Encounter\t|\tTarget\t||\tNormal\t|\tClass\t|\tMask\t|\tBoth\t|");
  for(j=0;j<n;j++){
    output = lightcalc(light,targetbuffer[j]);
    printf("\n\t%d\t\t|\t%d\t\t||",j+1,targetbuffer[j]);
    for(i=0;i<4;i++){
      if(*(output+i)>seasoncap){
        printf("\t!@#~\t|");
        continue;
      }
      if(*(output+i)<1000)printf("\t%g\t\t|",*(output+i));
      else printf("\t%g\t|",*(output+i));
    }
  } 
  printf("\n\nKey:\nNormal\t-\tAverage light of all 5 armour slots required to hit target.\nClass\t-\tAverage light of 4 armour slots (excluding 21 light class item) required to hit target.\nMask\t-\tAverage light of 4 armour slots (excluding 0 light FOTL mask) required to hit target.\nBoth\t-\tAverage light of 3 armour slots (excluding Class & Mask) required to hit target.\n!@#~\t-\tAverage light required is above current power cap (%d).\n\n",seasoncap);

return 0;
}

double * lightcalc(int light, int target){
  static double output[4];
  //no auxillary light reduction
  output[0]=((8*target)-light)/5;

  //collections class item 21 light
  output[2]=((8*target)-(light+21))/4;

  //fotl mask 0 light
  output[1]=((8*target)-light)/4;  

  //both
  output[3]=((8*target)-(light+21))/3;

  return output;
}
