  #include <dos.h>
#include <stdlib.h>
#include <iostream>
#include <conio.h>

void clearscreen(){
union REGS inregs,outregs;
inregs.x.ax=0x0600;
inregs.h.bh=0x07;
inregs.x.cx=0;
inregs.x.dx=0x184F;
int86(0x10,&inregs,&outregs);
}

void setscreen(){
union REGS inregs,outregs;
inregs.x.ax=0x12;
int86(0x10,&inregs,&outregs);
}

void callcursor(){
union REGS inregs,outregs;
inregs.h.ah = 0x02; 
inregs.h.bh = 0;
inregs.h.dl = 0x05;
inregs.h.dh = 0x08;
int86(0x10,&inregs,&outregs);
}

void drawcolumn(int inputr,int inputc,int a3, int a4){

union REGS inregs,outregs;

unsigned int a5,a6,a7;
a5=a3;
a6=a4;


inregs.x.dx=a5;
inputc=inputc-1;

if(inputc > 0){
int i=a4*inputc;
a7=i+a4;
}

do {
while(a6 <= a7){
 inregs.x.cx=a6;
 inregs.h.ah=0x0c;
 inregs.h.al=0x06;
 int86(0x10,&inregs,&outregs);
 a6=a6+1;}
  
a6=a4;
inputr=inputr-1;
a5=a5+a3;
inregs.x.dx=a5;
}
while(inputr>0);
}

void drawrow(int inputr,int inputc,int a3,int a4){
union REGS inregs,outregs;

unsigned int a5,a6,a7;
a5=a3;
a6=a4; 

inregs.x.cx=a6;
inputr=inputr-1;

if(inputr>0){
   int j=a3*inputr;
   a7=j+a3;
}

do{
   do{
    inregs.x.dx=a5;
    inregs.h.ah=0x0c;
    inregs.h.al=0x06;
    int86(0x10,&inregs,&outregs);
    a5=a5+1;
    }
    while(a5 <= a7);
    a5=a3;
    inputc=inputc-1;
    a6=a6+a4;
    inregs.x.cx=a6;
}
while(inputc > 0);
}

void takeinput(int inputr,int inputc){

int vertical=inputc+1;
int v=480;
int horizontal=inputr+1;
int h=640;

int a3=v/horizontal;
int a4=h/vertical;
clearscreen();
setscreen();
drawcolumn(inputr,inputc,a3,a4);
drawrow(inputr,inputc,a3,a4);
}




  
int main(){

int inputr;
int inputc;

cout<<"Welcome to the Grid Program\n";
cout<<"Please input the number of horizontal lines(0-99):";
cin>>inputr;
if(inputr<0 || inputr > 99){
cout<<"Wrong parameters, please restart program.";}
cout<<"Please input the number of vertical lines(0-99):";
cin>>inputc;
if(inputc<0 || inputc >99){
cout<< "Wrong paremeters,please restart program.";}
cout<<"Now I am going to draw your "<<inputr<<" x "<<inputc<<" grid"<<endl;
cout<<"Please wait patiently." ;
cout<<"For drawing press a button";

getch();
takeinput(inputr,inputc);
return 0;
}





