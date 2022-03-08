#include <iostream>
#include <fstream>
#include <stdio.h>
#include <graphics.h>
#include <winbgim.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <cmath>
using namespace std;
ifstream f("date.in");

void meniu();
struct punct
{
    int x;
    int y;
    int info;
};

struct operatie
{
    int x;
    int y;
    char simbol[2];
};

punct vector1[10], vector2[10], vector3[10];
int n, lungime=0;
int scalar;
operatie opv,egalv,deinmultit;

void meniuVectori();
void meniuMatrice();
void meniu();

punct a[10][10],b[10][10], c[10][10];
operatie op, egal;
int cmax,c1,c2, ok1,ok2,ok3,egalX,_x, _y,L1,L2;
int windowWidth=1550, windowHeight=600;
long det=0;
char rezultatChar[50]="";

void coordonateVector(punct vector[10], int x, int y)
{
    char str[10]="";
    int x1=x;
    for(int i=1; i<=n; i++)
    {
        vector[i].x=x1;
        vector[i].y=y;
        int a=vector[i].info;
        int lung=0;
        if(a==0)
            lung=1;
        else
        {
            if(a<0)
            {
                a=-a;
                lung++;
            }
            while(a>0)
            {
                lung++;
                a=a/10;
            }
        }
        x1=x1+33+ 23*lung;
    }
}

void citireVector(int &n,int &scalar)
{
    FILE *fptr;
    if ((fptr = fopen("dateIntrare.txt","r")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }
    fscanf(fptr,"%d", &n);
    for(int i=1; i<=n; i++)
    {
        fscanf(fptr,"%d", &vector1[i].info);
    }
    for(int i=1; i<=n; i++)
    {
        fscanf(fptr,"%d",&vector2[i].info);
    }
    fscanf(fptr,"%d",&scalar);
    fclose(fptr);
}


void coordonateOperatiev(operatie &opv)
{
    opv.y=vector1[1].y + 50;
    opv.x=vector1[n].x/2;
}

void coordonateEgalv(operatie &egalv)
{
    strcpy(egal.simbol,"=");
    egalv.x=vector1[n].x/2;
    egalv.y=vector2[1].y + 50;
}

void afisareVector(punct vector[10],int start)
{
    char str[10]="";
    for(int i=1; i<=n; i++)
    {
        itoa(vector[i].info,str,10);
        settextstyle(4,HORIZ_DIR,3);
        outtextxy(vector[i].x,vector[i].y,str);
        line(vector[i].x-10,start-10,vector[i].x-10,start+45);   //liniile verticale
        //rectangle(vector[i].x-10, vector[i].y, vector[i].x+40, vector[i].y+40);
    }
    int a=vector[n].info;
    int lung=0;
    if(a==0)
        lung=1;
    else
    {
        if(a<0)
        {
            a=-a;
            lung++;
        }
        while(a>0)
        {
            lung++;
            a=a/10;
        }
    }

    int coord=vector[n].x + lung*20;
    if(vector[n].info>=0)
        coord=coord+30;

    line(vector[1].x-10,start-10,coord,start-10);
    line(vector[1].x-10,start+45,coord,start+45);
    line(coord,start-10,coord,start+45);

}

void adunare(punct vector1[10], punct vector2[10], punct vector3[10])
{
    strcpy(opv.simbol, "+");
    coordonateOperatiev(opv);
    afisareVector(vector1,25);

    settextstyle(4,HORIZ_DIR,3);
    outtextxy(opv.x,opv.y,opv.simbol);

    afisareVector(vector2,115);

    for(int i=1; i<=n; i++)
        vector3[i].info=vector1[i].info + vector2[i].info;
    coordonateVector(vector3,30,210);

    strcpy(egalv.simbol, "=");
    coordonateEgalv(egalv);
    settextstyle(4,HORIZ_DIR,3);
    outtextxy(egalv.x,egalv.y,egalv.simbol);

    afisareVector(vector3,205);

    for(int i=1; i<=n; i++)
    {

    settextstyle(4,HORIZ_DIR,4);
    setcolor(14);
    char str1[10]="",str2[10]="",str3[10]="";
    itoa(vector1[i].info,str1,10);
    itoa(vector2[i].info,str2,10);
    itoa(vector3[i].info,str3,10);

    getch();
    outtextxy(vector1[i].x, vector1[i].y, str1);
    outtextxy(vector2[i].x, vector2[i].y, str2);

    setcolor(13);
    outtextxy(vector3[i].x, vector3[i].y, str3);

    getch();

    cleardevice();

    setcolor(15);
    afisareVector(vector1,25);
    afisareVector(vector2,115);

    outtextxy(opv.x,opv.y,opv.simbol);
    outtextxy(egalv.x,egalv.y,egalv.simbol);

    afisareVector(vector3,205);
    }
    FILE *fptr;
    fptr = fopen("date.txt","w");
    if(fptr == NULL)
    {
        printf("Error!");
        exit(1);
    }

    for(int i=1; i<=n; i++)
        fprintf(fptr," %d",vector3[i].info);
    fclose(fptr);

    getch();
    cleardevice();
    meniuVectori();
}

void scadere(punct vector1[10], punct vector2[10], punct vector3[10])
{
    strcpy(opv.simbol, "-");
    coordonateOperatiev(opv);
    afisareVector(vector1,25);

    settextstyle(4,HORIZ_DIR,3);
    outtextxy(opv.x,opv.y,opv.simbol);

    afisareVector(vector2,115);

    for(int i=1; i<=n; i++)
        vector3[i].info=vector1[i].info - vector2[i].info;
    coordonateVector(vector3,30,210);

    strcpy(egalv.simbol, "=");
    coordonateEgalv(egalv);
    settextstyle(4,HORIZ_DIR,3);
    outtextxy(egalv.x,egalv.y,egalv.simbol);

    afisareVector(vector3,205);

    for(int i=1; i<=n; i++)
    {

    settextstyle(4,HORIZ_DIR,4);
    setcolor(14);
    char str1[10]="",str2[10]="",str3[10]="";
    itoa(vector1[i].info,str1,10);
    itoa(vector2[i].info,str2,10);
    itoa(vector3[i].info,str3,10);

    getch();
    outtextxy(vector1[i].x, vector1[i].y, str1);
    outtextxy(vector2[i].x, vector2[i].y, str2);

    setcolor(13);
    outtextxy(vector3[i].x, vector3[i].y, str3);

    getch();

    cleardevice();

    setcolor(15);
    afisareVector(vector1,25);
    afisareVector(vector2,115);

    outtextxy(opv.x,opv.y,opv.simbol);
    outtextxy(egalv.x,egalv.y,egalv.simbol);

    afisareVector(vector3,205);
    }
    FILE *fptr;
    fptr = fopen("date.txt","w");
    if(fptr == NULL)
    {
        printf("Error!");
        exit(1);
    }

    for(int i=1; i<=n; i++)
        fprintf(fptr," %d",vector3[i].info);
    fclose(fptr);

    getch();
    cleardevice();
    meniuVectori();


}

void sumaElemente(punct vector[10])
{
    char sir[100]="";
    int suma=0;
    afisareVector(vector,25);
    for(int i=1; i<=n; i++)
    {
        suma=suma+vector[i].info;
        settextstyle(4,HORIZ_DIR,4);
        setcolor(14);
    char str[10]="";
    itoa(vector[i].info,str,10);

    getch();
    outtextxy(vector[i].x, vector[i].y, str);

    getch();
    strcat(sir,str);
    if(i!=n)
        strcat(sir," + ");
    else strcat(sir, " = ");

    cleardevice();

    setcolor(15);
    afisareVector(vector,25);

    outtextxy(25,100,sir);
    }
    getch();
    char s[10]="";
    itoa(suma,s,10);
    strcat(sir,s);
    outtextxy(25,100,sir);

    FILE *fptr;
    fptr = fopen("date.txt","w");
    if(fptr == NULL)
    {
        printf("Error!");
        exit(1);
    }

        fprintf(fptr," %d",suma);
    fclose(fptr);

    getch();
    cleardevice();
    meniuVectori();
}

void produsElemente(punct vector[10])
{
 char sir[100]="";
    int produs=1;
    afisareVector(vector,25);
    for(int i=1; i<=n; i++)
    {
        produs=produs*vector[i].info;
        settextstyle(4,HORIZ_DIR,4);
        setcolor(14);
    char str[10]="";
    itoa(vector[i].info,str,10);

    getch();
    outtextxy(vector[i].x, vector[i].y, str);

    getch();
    strcat(sir,str);
    if(i!=n)
        strcat(sir," x ");
    else strcat(sir, " = ");

    cleardevice();

    setcolor(15);
    afisareVector(vector,25);

    outtextxy(25,100,sir);
    }
    getch();
    char p[10]="";
    itoa(produs,p,10);
    strcat(sir,p);
    outtextxy(25,100,sir);
    FILE *fptr;
    fptr = fopen("date.txt","w");
    if(fptr == NULL)
    {
        printf("Error!");
        exit(1);
    }

        fprintf(fptr," %d",produs);
    fclose(fptr);

    getch();
    cleardevice();
    meniuVectori();
}

void produsScalar(punct vectorprim[10],punct vectorsec[10])
{
    int produs=1;
    char sir[100]="";

    strcpy(op.simbol, "x");
    coordonateOperatiev(op);
    afisareVector(vectorprim,25);

    afisareVector(vectorsec,115);

    settextstyle(4,HORIZ_DIR,3);
    outtextxy(op.x,op.y,op.simbol);

    strcpy(egal.simbol, "=");
    coordonateEgalv(egal);
    settextstyle(4,HORIZ_DIR,3);
    outtextxy(egal.x,egal.y,egal.simbol);


    for(int i=1; i<=n; i++)
    {

    settextstyle(4,HORIZ_DIR,4);
    setcolor(14);

    char str1[10]="", str2[10]="";
    itoa(vector1[i].info,str1,10);
    itoa(vector2[i].info,str2,10);

    produs=produs + (vectorprim[i].info * vectorsec[i].info);
    strcat(sir,str1);
    strcat(sir," x ");
    strcat(sir,str2);
    if(i!=n)
        strcat(sir," + ");
    else strcat(sir," ");


    getch();
    outtextxy(vectorprim[i].x, vectorprim[i].y, str1);
    outtextxy(vectorsec[i].x, vectorsec[i].y, str2);

    setcolor(15);

    getch();

    cleardevice();

    afisareVector(vectorprim,25);
    afisareVector(vectorsec,115);

    outtextxy(opv.x,opv.y,opv.simbol);
    outtextxy(egalv.x,egalv.y,egalv.simbol);

    outtextxy(25,200,sir);
    }
    strcat(sir, "= ");
    char str[10]="";
    itoa(produs,str,10);
    strcat(sir,str);
    outtextxy(25,200,sir);

    FILE *fptr;
    fptr = fopen("date.txt","w");
    if(fptr == NULL)
    {
        printf("Error!");
        exit(1);
    }

        fprintf(fptr," %d",produs);
    fclose(fptr);

    getch();
    cleardevice();
    meniuVectori();
}

void inmultireCuScalar(punct vector[10], int scalar)
{
    coordonateVector(vector,30,30);
    afisareVector(vector,25);


    int a=vector[n].info;
    int lung=0;
    if(a==0)
        lung=1;
    else
    {
        if(a<0)
        {
            a=-a;
            lung++;
        }
        while(a>0)
        {
            lung++;
            a=a/10;
        }
    }

    int coord=vector[n].x + lung*30;
    coordonateEgalv(egalv);
    egalv.y=95;

    char str[100]="", sir[100]="X ";
    itoa(scalar,str,10);
    strcat(sir,str);
    settextstyle(4,HORIZ_DIR,3);
    outtextxy(coord+30,30,sir);
    outtextxy(egalv.x,egalv.y,egalv.simbol);

    for(int i=1; i<=n; i++)
        vector3[i].info=0;

    coordonateVector(vector3,30,150);
    afisareVector(vector3,145);
    for(int j=1; j<=n; j++)
            outtextxy(vector3[j].x,vector3[j].y,"?");
    getch();
    for(int i=1; i<=n; i++)
    {
        char numar1[10]="",rezultat[10]="";

        settextstyle(4,HORIZ_DIR,4);
        itoa(vector[i].info,numar1,10);

        setcolor(10);
        outtextxy(vector[i].x,vector[i].y,numar1);
        settextstyle(4,HORIZ_DIR,3);
        outtextxy(coord+30,30,sir);
        getch();

        setcolor(15);
        for(int j=i+1; j<=n; j++)
            outtextxy(vector3[j].x,vector3[j].y,"?");
        vector3[i].info=vector[i].info*scalar;

        cleardevice();
        setcolor(15);
        afisareVector(vector,25);
        outtextxy(egalv.x,egalv.y,egalv.simbol);
        outtextxy(coord+30,30,sir);


        coordonateVector(vector3,30,150);
        afisareVector(vector3,145);
        itoa(vector3[i].info,rezultat,10);
        settextstyle(4,HORIZ_DIR,4);
        setcolor(10);
        outtextxy(vector3[i].x,vector3[i].y,rezultat);

        settextstyle(4,HORIZ_DIR,4);
        setcolor(15);
        for(int j=i+1; j<=n; j++)              //afisare casute cu semnul intrebarii
            outtextxy(vector3[j].x,vector3[j].y,"?");

        getch();

        cleardevice();
        setcolor(15);
        afisareVector(vector,25);
        outtextxy(egalv.x,egalv.y,egalv.simbol);
        outtextxy(coord+30,30,sir);
        afisareVector(vector3,145);
        settextstyle(4,HORIZ_DIR,4);
        setcolor(15);
        for(int j=i+1; j<=n; j++)              //afisare casute cu semnul intrebarii
            outtextxy(vector3[j].x,vector3[j].y,"?");
        getch();

    }
    FILE *fptr;
    fptr = fopen("date.txt","w");
    if(fptr == NULL)
    {
        printf("Error!");
        exit(1);
    }

    for(int i=1; i<=n; i++)
        fprintf(fptr," %d",vector3[i].info);
    fclose(fptr);

    getch();
    cleardevice();
    meniuVectori();
}

void shiftareLaStanga(punct vector[10])
{
    int aux;
    aux=vector[1].info;
    coordonateVector(vector,30,30);
    afisareVector(vector, 25);

    char str[10];

    getch();

    settextstyle(4, HORIZ_DIR,5);
    line(vector[1].x+10 ,vector[1].y +50 ,vector[1].x+10,150);
    line(vector[1].x+10,150,vector[1].x+10-3,150-7);
    line(vector[1].x+10,150,vector[1].x+10+3,150-7);

    getch();

    settextstyle(4, HORIZ_DIR,3);
    itoa(vector[1].info,str,10);
    outtextxy(25,vector[1].y+150,str);
    getch();
    cleardevice();
    afisareVector(vector1,25);
    outtextxy(25,vector[1].y+150,str);
    for(int i=1; i<n; i++)
    {
        afisareVector(vector,25);
        outtextxy(25,vector[1].y+150,str);
        getch();
        setcolor(15);
        settextstyle(4, HORIZ_DIR,5);
        line(vector[i+1].x+10,vector[i+1].y+50, vector[i+1].x+10,100);
        line(vector[i+1].x+10,100,vector[i].x+10,100);
        line(vector[i].x+10 ,vector[i].y +50 ,vector[i].x+10,100);
        line(vector[i].x+10,vector[i].y+50,vector[i].x+10-3,vector[i].y+50+7);
        line(vector[i].x+10,vector[i].y+50,vector[i].x+10+3,vector[i].y+50+7);

        getch();
        vector[i].info=vector[i+1].info;
        coordonateVector(vector1,30,30);
        afisareVector(vector,25);

        cleardevice();
    }

    afisareVector(vector,25);

    outtextxy(25,vector[1].y+150,str);
    getch();
    line(50,vector[1].y+150 + 10,vector[n].x+10,vector[n].y+150 + 10);
    line(vector[n].x+10,vector[n].y+150 + 10,vector[n].x+10,vector[n].y+50);
    line(vector[n].x+10,vector[n].y+50,vector[n].x+10-3,vector[n].y+50+7);
    line(vector[n].x+10,vector[n].y+50,vector[n].x+10+3,vector[n].y+50+7);


    vector[n].info=aux;

    getch();
    afisareVector(vector,25);

    getch();

    cleardevice();
    afisareVector(vector,25);

    FILE *fptr;
    fptr = fopen("date.txt","w");
    if(fptr == NULL)
    {
        printf("Error!");
        exit(1);
    }

    for(int i=1; i<=n; i++)
        fprintf(fptr," %d",vector[i].info);
    fclose(fptr);


    getch();
    cleardevice();
    meniuVectori();
}

void shiftareLaDreapta(punct vector[10])
{
    int aux;
    aux=vector[n].info;
    coordonateVector(vector,30,30);
    afisareVector(vector, 25);

    char str[10];

    getch();

    settextstyle(4, HORIZ_DIR,5);
    line(vector[n].x+10 ,vector[n].y +50 ,vector[n].x+10,150);
    line(vector[n].x+10,150,vector[n].x+10-3,150-7);
    line(vector[n].x+10,150,vector[n].x+10+3,150-7);

    getch();

    settextstyle(4, HORIZ_DIR,3);
    itoa(vector[n].info,str,10);
    outtextxy(vector[n].x,vector[n].y+150,str);
    getch();
    cleardevice();
    afisareVector(vector1,25);
    outtextxy(vector[n].x,vector[n].y+150,str);
    for(int i=n-1; i>=1; i--)
    {
        afisareVector(vector,25);
        outtextxy(vector[n].x,vector[n].y+150,str);
        getch();
        setcolor(15);
        settextstyle(4, HORIZ_DIR,5);
        line(vector[i+1].x+10,vector[i+1].y+50, vector[i+1].x+10,100);
        line(vector[i+1].x+10,100,vector[i].x+10,100);
        line(vector[i].x+10 ,vector[i].y +50 ,vector[i].x+10,100);
        line(vector[i+1].x+10,vector[i].y+50,vector[i+1].x+10-3,vector[i].y+50+7);
        line(vector[i+1].x+10,vector[i].y+50,vector[i+1].x+10+3,vector[i].y+50+7);

        getch();
        vector[i+1].info=vector[i].info;
        coordonateVector(vector1,30,30);
        afisareVector(vector,25);

        cleardevice();
    }

    afisareVector(vector,25);

    outtextxy(vector[n].x,vector[n].y+150,str);
    getch();
    line(50,vector[1].y+150 + 10,vector[n].x-10,vector[n].y+150 + 10);  //linia orizontala
    line(50,vector[1].y+150 + 10,50,vector[1].y+50);  //linia verticala
    line(50,vector[1].y+50,50-3,vector[1].y+50+7);    //linie sageata stanga
    line(50,vector[1].y+50,50+3,vector[1].y+50+7);      //linie sageata dreapta


    vector[1].info=aux;

    getch();
    afisareVector(vector,25);

    getch();

    cleardevice();
    afisareVector(vector,25);

    FILE *fptr;
    fptr = fopen("date.txt","w");
    if(fptr == NULL)
    {
        printf("Error!");
        exit(1);
    }

    for(int i=1; i<=n; i++)
        fprintf(fptr," %d",vector[i].info);
    fclose(fptr);

    getch();
    cleardevice();
    meniuVectori();
}

void selectionSortCrescator(punct vector[10])
{

    coordonateVector(vector,30,30);
    afisareVector(vector,25);

    getch();
    for(int i=1; i<n; i++)
    {
        cleardevice();
        setcolor(15);
        afisareVector(vector,25);
        settextstyle(4, HORIZ_DIR,4);
        setcolor(14);
        line(vector[i].x+10 ,vector[i].y +50 ,vector[i].x+10,100);   //sageata pentru primul element comparat
        line(vector[i].x+10,vector[i].y+50,vector[i].x+10-3,vector[i].y+50+7);
        line(vector[i].x+10,vector[i].y+50,vector[i].x+10+3,vector[i].y+50+7);

        settextstyle(4, HORIZ_DIR,2);
        char elem1[10]="";
        itoa(vector[i].info,elem1,10);


        for(int j=i+1; j<=n; j++)
        {
            char sir[100]="Se compara ",altsir[100]="",elem2[10]="";

            itoa(vector[j].info,elem2,10);
            strcat(sir,elem1);
            strcat(sir," cu ");
            strcat(sir,elem2);
            strcat(sir,".");

            getch();
            settextstyle(4, HORIZ_DIR,4);
            setcolor(13);
            line(vector[j].x+10,vector[j].y +50,vector[j].x+10,100);     //sageata pentru al 2 lea elem comparat
            line(vector[j].x+10,vector[j].y+50,vector[j].x+10-3,vector[i].y+50+7);  //linii din sageata
            line(vector[j].x+10,vector[j].y+50,vector[j].x+10+3,vector[i].y+50+7);      //linii din sageata

            settextstyle(4, HORIZ_DIR,2);
            setcolor(15);
            outtextxy(30,150,sir);

            if(vector[j].info<vector[i].info)
            {
                getch();
                setcolor(15);
                settextstyle(4, HORIZ_DIR,2);
                strcat(altsir,elem1);
                strcat(altsir," > ");
                strcat(altsir,elem2);
                strcat(altsir,", asadar cele doua elemente se interschimba.");
                outtextxy(30,200,altsir);

                getch();
                settextstyle(4, HORIZ_DIR,4);
                setcolor(10);

                line(vector[i].x+10 ,vector[i].y +50 ,vector[i].x+10,100);   //sageata pentru primul element comparat
                line(vector[i].x+10,vector[i].y+50,vector[i].x+10-3,vector[i].y+50+7);
                line(vector[i].x+10,vector[i].y+50,vector[i].x+10+3,vector[i].y+50+7);

                line(vector[i].x+10,100,vector[j].x+10,100);  //linie orizontala de la cele doua elemente

                line(vector[j].x+10 ,vector[j].y +50 ,vector[j].x+10,100);   //sageata pentru al 2 lea elem comparat
                line(vector[j].x+10,vector[j].y+50,vector[j].x+10-3,vector[i].y+50+7);  //linii din sageata
                line(vector[j].x+10,vector[j].y+50,vector[j].x+10+3,vector[i].y+50+7);      //linii din sageata

                swap(vector[i].info,vector[j].info);
                coordonateVector(vector,30,30);
                //setcolor(15);
                //afisareVector(vector,25);
            }
            else
            {
                getch();
                setcolor(15);
                settextstyle(4, HORIZ_DIR,2);
                strcat(altsir,elem1);
                strcat(altsir," < ");
                strcat(altsir,elem2);
                strcat(altsir,", deci se trece la pasul urmator");
                outtextxy(30,200,altsir);
            }
            getch();
                setcolor(15);
                cleardevice();
                afisareVector(vector,25);
                settextstyle(4, HORIZ_DIR,4);
                setcolor(14);
                line(vector[i].x+10 ,vector[i].y +50 ,vector[i].x+10,100);   //sageata pentru elementul cu care se compara
                line(vector[i].x+10,vector[i].y+50,vector[i].x+10-3,vector[i].y+50+7);
                line(vector[i].x+10,vector[i].y+50,vector[i].x+10+3,vector[i].y+50+7);

        }
    }
    cleardevice();
    setcolor(15);
    settextstyle(4, HORIZ_DIR,2);
    outtextxy(30,150,"Acesta este vectorul sortat.");
    afisareVector(vector,25);


    FILE *fptr;
    fptr = fopen("date.txt","w");
    if(fptr == NULL)
    {
        printf("Error!");
        exit(1);
    }

    for(int i=1; i<=n; i++)
        fprintf(fptr," %d",vector[i].info);
    fclose(fptr);

    getch();
    cleardevice();
    meniuVectori();

  }

void selectionSortDescrescator(punct vector[10])
{

    coordonateVector(vector,30,30);
    afisareVector(vector,25);

    getch();
    for(int i=1; i<n; i++)
    {
        cleardevice();
        setcolor(15);
        afisareVector(vector,25);
        settextstyle(4, HORIZ_DIR,4);
        setcolor(14);
        line(vector[i].x+10 ,vector[i].y +50 ,vector[i].x+10,100);   //sageata pentru primul element comparat
        line(vector[i].x+10,vector[i].y+50,vector[i].x+10-3,vector[i].y+50+7);
        line(vector[i].x+10,vector[i].y+50,vector[i].x+10+3,vector[i].y+50+7);


        for(int j=i+1; j<=n; j++)
        {
            char elem1[10]="",sir[100]="Se compara ",altsir[100]="",elem2[10]="";
            itoa(vector[i].info,elem1,10);
            itoa(vector[j].info,elem2,10);
            strcat(sir,elem1);
            strcat(sir," cu ");
            strcat(sir,elem2);
            strcat(sir,".");

            getch();
            settextstyle(4, HORIZ_DIR,4);
            setcolor(13);
            line(vector[j].x+10,vector[j].y +50,vector[j].x+10,100);     //sageata pentru al 2 lea elem comparat
            line(vector[j].x+10,vector[j].y+50,vector[j].x+10-3,vector[i].y+50+7);  //linii din sageata
            line(vector[j].x+10,vector[j].y+50,vector[j].x+10+3,vector[i].y+50+7);      //linii din sageata

            settextstyle(4, HORIZ_DIR,2);
            setcolor(15);
            outtextxy(30,150,sir);

            if(vector[j].info>vector[i].info)
            {
                getch();
                setcolor(15);
                settextstyle(4, HORIZ_DIR,2);
                strcat(altsir,elem1);
                strcat(altsir," < ");
                strcat(altsir,elem2);
                strcat(altsir,", asadar cele doua elemente se interschimba.");
                outtextxy(30,200,altsir);

                getch();
                settextstyle(4, HORIZ_DIR,4);
                setcolor(10);

                line(vector[i].x+10 ,vector[i].y +50 ,vector[i].x+10,100);   //sageata pentru primul element comparat
                line(vector[i].x+10,vector[i].y+50,vector[i].x+10-3,vector[i].y+50+7);
                line(vector[i].x+10,vector[i].y+50,vector[i].x+10+3,vector[i].y+50+7);

                line(vector[i].x+10,100,vector[j].x+10,100);  //linie orizontala de la cele doua elemente

                line(vector[j].x+10 ,vector[j].y +50 ,vector[j].x+10,100);   //sageata pentru al 2 lea elem comparat
                line(vector[j].x+10,vector[j].y+50,vector[j].x+10-3,vector[i].y+50+7);  //linii din sageata
                line(vector[j].x+10,vector[j].y+50,vector[j].x+10+3,vector[i].y+50+7);      //linii din sageata

                swap(vector[i].info,vector[j].info);
                coordonateVector(vector,30,30);
            }
            else
            {
                getch();
                setcolor(15);
                settextstyle(4, HORIZ_DIR,2);
                strcat(altsir,elem1);
                strcat(altsir," > ");
                strcat(altsir,elem2);
                strcat(altsir,", deci se trece la pasul urmator");
                outtextxy(30,200,altsir);
            }
            getch();
                setcolor(15);
                cleardevice();
                afisareVector(vector,25);
                settextstyle(4, HORIZ_DIR,4);
                setcolor(14);
                line(vector[i].x+10 ,vector[i].y +50 ,vector[i].x+10,100);   //sageata pentru elementul cu care se compara
                line(vector[i].x+10,vector[i].y+50,vector[i].x+10-3,vector[i].y+50+7);
                line(vector[i].x+10,vector[i].y+50,vector[i].x+10+3,vector[i].y+50+7);

        }
    }
    cleardevice();
    setcolor(15);
    settextstyle(4, HORIZ_DIR,2);
    outtextxy(30,150,"Acesta este vectorul sortat.");
    afisareVector(vector,25);


    FILE *fptr;
    fptr = fopen("date.txt","w");
    if(fptr == NULL)
    {
        printf("Error!");
        exit(1);
    }

    for(int i=1; i<=n; i++)
        fprintf(fptr," %d",vector[i].info);
    fclose(fptr);

    getch();
    cleardevice();
    meniuVectori();

  }


void bubbleSortCrescator(punct vector[10])
{

    coordonateVector(vector,30,30);
    afisareVector(vector,25);

    getch();

    int ok=0;
    while(ok==0)
    {
        ok=1;
        for(int i=1; i<=n-1; i++)
        {
            settextstyle(4, HORIZ_DIR,2);
            char elem1[10]="",elem2[10]="",sir[100]="Se compara ",altsir[100]="";
            itoa(vector[i].info,elem1,10);
            itoa(vector[i+1].info,elem2,10);

            strcat(sir,elem1);
            strcat(sir," cu ");
            strcat(sir,elem2);
            strcat(sir,".");
            outtextxy(30,150,sir);


            settextstyle(4, HORIZ_DIR,4);
            setcolor(14);
            line(vector[i].x+10 ,vector[i].y +50 ,vector[i].x+10,100);   //sageata pentru primul element comparat
            line(vector[i].x+10,vector[i].y+50,vector[i].x+10-3,vector[i].y+50+7);
            line(vector[i].x+10,vector[i].y+50,vector[i].x+10+3,vector[i].y+50+7);

            line(vector[i+1].x+10 ,vector[i+1].y +50 ,vector[i+1].x+10,100);   //sageata pentru primul element comparat
            line(vector[i+1].x+10,vector[i+1].y+50,vector[i+1].x+10-3,vector[i+1].y+50+7);
            line(vector[i+1].x+10,vector[i+1].y+50,vector[i+1].x+10+3,vector[i+1].y+50+7);

            if(vector[i].info>vector[i+1].info)
            {
                getch();
                setcolor(15);
                settextstyle(4, HORIZ_DIR,2);
                strcat(altsir,elem1);
                strcat(altsir," > ");
                strcat(altsir,elem2);
                strcat(altsir,", asadar cele doua elemente se interschimba.");
                outtextxy(30,200,altsir);


                setcolor(10);
                settextstyle(4, HORIZ_DIR,4);
                line(vector[i].x+10 ,vector[i].y +50 ,vector[i].x+10,100);   //sageata pentru primul element comparat
                line(vector[i].x+10,vector[i].y+50,vector[i].x+10-3,vector[i].y+50+7);
                line(vector[i].x+10,vector[i].y+50,vector[i].x+10+3,vector[i].y+50+7);

                line(vector[i+1].x+10 ,vector[i+1].y +50 ,vector[i+1].x+10,100);   //sageata pentru primul element comparat
                line(vector[i+1].x+10,vector[i+1].y+50,vector[i+1].x+10-3,vector[i+1].y+50+7);
                line(vector[i+1].x+10,vector[i+1].y+50,vector[i+1].x+10+3,vector[i+1].y+50+7);

                line(vector[i].x+10,100,vector[i+1].x+10,100);  //linie orizontala de la cele doua elemente

                swap(vector[i].info,vector[i+1].info);
                ok=0;
            }
            else
            {
                getch();
                setcolor(15);
                settextstyle(4, HORIZ_DIR,2);
                strcat(altsir,elem1);
                strcat(altsir," < ");
                strcat(altsir,elem2);
                strcat(altsir,", deci se trece la pasul urmator");
                outtextxy(30,200,altsir);
            }
            getch();
            setcolor(15);
            cleardevice();
            coordonateVector(vector,30,30);
            afisareVector(vector,25);
            getch();
        }
    }
    settextstyle(4, HORIZ_DIR,2);
    outtextxy(30,150,"Acesta este vectorul sortat.");
    afisareVector(vector,25);

    FILE *fptr;
    fptr = fopen("date.txt","w");
    if(fptr == NULL)
    {
        printf("Error!");
        exit(1);
    }

    for(int i=1; i<=n; i++)
        fprintf(fptr," %d",vector[i].info);
    fclose(fptr);


    getch();
    cleardevice();
    meniuVectori();
}

void bubbleSortDescrescator(punct vector[10])
{


    coordonateVector(vector,30,30);
    afisareVector(vector,25);

    getch();

    int ok=0;
    while(ok==0)
    {
        ok=1;
        for(int i=1; i<=n-1; i++)
        {
            settextstyle(4, HORIZ_DIR,2);
            char elem1[10]="",elem2[10]="",sir[100]="Se compara ",altsir[100]="";
            itoa(vector[i].info,elem1,10);
            itoa(vector[i+1].info,elem2,10);

            strcat(sir,elem1);
            strcat(sir," cu ");
            strcat(sir,elem2);
            strcat(sir,".");
            outtextxy(30,150,sir);


            settextstyle(4, HORIZ_DIR,4);
            setcolor(14);
            line(vector[i].x+10 ,vector[i].y +50 ,vector[i].x+10,100);   //sageata pentru primul element comparat
            line(vector[i].x+10,vector[i].y+50,vector[i].x+10-3,vector[i].y+50+7);
            line(vector[i].x+10,vector[i].y+50,vector[i].x+10+3,vector[i].y+50+7);

            line(vector[i+1].x+10 ,vector[i+1].y +50 ,vector[i+1].x+10,100);   //sageata pentru al doilea element comparat
            line(vector[i+1].x+10,vector[i+1].y+50,vector[i+1].x+10-3,vector[i+1].y+50+7);
            line(vector[i+1].x+10,vector[i+1].y+50,vector[i+1].x+10+3,vector[i+1].y+50+7);

            if(vector[i].info<vector[i+1].info)
            {
                getch();
                setcolor(15);
                settextstyle(4, HORIZ_DIR,2);
                strcat(altsir,elem1);
                strcat(altsir," < ");
                strcat(altsir,elem2);
                strcat(altsir,", asadar cele doua elemente se interschimba.");
                outtextxy(30,200,altsir);


                setcolor(10);
                settextstyle(4, HORIZ_DIR,4);
                line(vector[i].x+10 ,vector[i].y +50 ,vector[i].x+10,100);   //sageata pentru primul element comparat
                line(vector[i].x+10,vector[i].y+50,vector[i].x+10-3,vector[i].y+50+7);
                line(vector[i].x+10,vector[i].y+50,vector[i].x+10+3,vector[i].y+50+7);

                line(vector[i+1].x+10 ,vector[i+1].y +50 ,vector[i+1].x+10,100);   //sageata pentru primul element comparat
                line(vector[i+1].x+10,vector[i+1].y+50,vector[i+1].x+10-3,vector[i+1].y+50+7);
                line(vector[i+1].x+10,vector[i+1].y+50,vector[i+1].x+10+3,vector[i+1].y+50+7);

                line(vector[i].x+10,100,vector[i+1].x+10,100);  //linie orizontala de la cele doua elemente

                swap(vector[i].info,vector[i+1].info);
                ok=0;
            }
            else
            {
                getch();
                setcolor(15);
                settextstyle(4, HORIZ_DIR,2);
                strcat(altsir,elem1);
                strcat(altsir," > ");
                strcat(altsir,elem2);
                strcat(altsir,", deci se trece la pasul urmator");
                outtextxy(30,200,altsir);
            }
            getch();
            setcolor(15);
            cleardevice();
            coordonateVector(vector,30,30);
            afisareVector(vector,25);
            getch();
        }
    }
    settextstyle(4, HORIZ_DIR,2);
    outtextxy(30,150,"Acesta este vectorul sortat.");
    afisareVector(vector,25);

    FILE *fptr;
    fptr = fopen("date.txt","w");
    if(fptr == NULL)
    {
        printf("Error!");
        exit(1);
    }

    for(int i=1; i<=n; i++)
        fprintf(fptr," %d",vector[i].info);
    fclose(fptr);

    getch();
    cleardevice();
    meniuVectori();
}



int numarCifre(int x)
{
    int nr=0;
    if(x == 0)
        x=1;
    while(x)
    {
        nr++;
        x/=10;
    }
    return nr;
}

void celMaiLungNumarColoana(punct a[10][10],int n, int &cmax, int k)
{
    int c,aux;
    cmax=0;
    for(int i=1; i<=n ; i++)
    {
        aux=a[i][k].info;
        c=0;
        if(aux == 0)
            aux=1;
        while(aux)
        {
            c++;
            aux/=10;
        }
        if(c > cmax)
            cmax=c;
    }
}

void celMaiLungNumarColoanaCoordonate(punct a[10][10],int n, int &_x, int &_y, int k)
{
    celMaiLungNumarColoana(a,n, cmax, k);
    for(int i=1; i<=n; i++)
        if(numarCifre(a[i][k].info) == cmax)//am gasit cel mai lung numar
        {
            _x=a[i][k].x;
            _y=a[i][k].y;

            i=n+1;//break
        }
}

void elipsa(punct a[10][10], int &c1, int &c2)
{
    setlinestyle(0, 0, 3);
    if(n%2 == 0) // N - PAR
    {
        celMaiLungNumarColoana(a,n, cmax, 1); // cel mai lung nr de pe prima coloana
        //parcurg prima coloana ca sa gasesc nr cel mai lung
        for(int i=1; i<=n; i++)
            if(numarCifre(a[i][1].info) == cmax)// si il iau ca reper
                ellipse(a[i][1].x, a[n/2+1][1].y - 10, 90, 270, 20, (n/2)*50) ; // stg

        celMaiLungNumarColoana(a,n, cmax, n); // cel mai lung numar de pe ultima coloana
        for(int i=1; i<=n; i++)
            if(numarCifre(a[i][n].info) == cmax)
                if(a[i][n].info > 0)
                {
                    c1 = a[i][n].x + cmax*20;
                    c2=a[n/2][n].y + 50;
                }
                else
                {
                    c1 = a[i][n].x + cmax*20 + 20;//spatiu in plus pentru minus
                    c2=a[n/2][n].y + 50;
                }
        ellipse(c1, c2-10, 270, 90, 20, (n/2)*50);//drp
    }
    else
    {
        celMaiLungNumarColoana(a,n, cmax, 1); // cel mai lung nr de pe prima coloana
        //parcurg prima coloana ca sa gasesc nr cel mai lung
        for(int i=1; i<=n; i++)
            if(numarCifre(a[i][1].info) == cmax) // si il iau ca reper
                ellipse(a[i][1].x, a[n/2+1][1].y + 10, 90, 270, 20, (n/2)*50 + 20) ; // stg

        celMaiLungNumarColoana(a,n, cmax, n); // cel mai lung numar de pe ultima coloana
        for(int i=1; i<=n; i++)
            if(numarCifre(a[i][n].info) == cmax)
                if(a[i][n].info > 0)
                {
                    c1 = a[i][n].x + cmax*20;
                    c2=a[n/2][n].y + 50;
                }
                else
                {
                    c1 = a[i][n].x + cmax*20 + 20;
                    c2=a[n/2][n].y + 25;
                }
        ellipse(c1, c2 + 10, 270, 90, 20, (n/2)*50 + 20);//drp
    }
}

void coordonateMatrice(punct a[10][10], int x, int y) // x,y = de unde sa inceapa afisarea matricii
{
    char str[20];
    int x1=x;
    for(int i=1; i<=n ; i++)
    {
        for(int j=1; j<=n; j++)
        {
            itoa(a[i][j].info,str,10);
            settextstyle(4, HORIZ_DIR, 5);
            a[i][j].x=x1;
            a[i][j].y=y;

            celMaiLungNumarColoana(a,n, cmax, j);

            x1=x1+30*cmax;
        }
        y=y+50;
        x1=x;
    }
    elipsa(a, c1, c2);
}

void coordonateMatriceInversa(punct a[10][10], int val, int x, int y) // x,y = de unde sa inceapa afisarea matricii
{
    char str[10];
    int x1=x;
    for(int i=1; i<=val; i++)
    {
        for(int j=1; j<=val; j++)
        {
            itoa(a[i][j].info,str,10);
            settextstyle(4, HORIZ_DIR, 5);
            a[i][j].x=x1;
            a[i][j].y=y;

            celMaiLungNumarColoana(a, val, cmax, j);

            x1=x1+30*cmax;
        }
        y=y+50;
        x1=x;
    }
    //elipsa2(a, c1, c2);
}

void aranjare(punct a[10][10], int n)
{
    for(int j=1; j<=n; j++)
    {
        celMaiLungNumarColoana(a,n, cmax, j);
        if(cmax > 1)
            for(int i=1; i<=n; i++)
            {
                if(numarCifre(a[i][j].info) == cmax-1 && cmax == 4)
                    a[i][j].x = a[i][j].x + 0.5 * (cmax-1) * 20 - 20;
                else if(numarCifre(a[i][j].info) != cmax)
                    a[i][j].x = a[i][j].x + 0.5 * (cmax-1) * 20;
            }
    }
}

void coordonateMatriceDeterminant(punct a[10][10], int x, int y) // x,y = de unde sa inceapa afisarea matricii
{
    char str[10];
    int x1=x;
    for(int i=1; i<=n ; i++)
    {
        for(int j=1; j<=n; j++)
        {
            itoa(a[i][j].info,str,10);
            settextstyle(4, HORIZ_DIR, 5);
            a[i][j].x=x1;
            a[i][j].y=y;

            celMaiLungNumarColoana(a,n, cmax, j);

            x1=x1+30*cmax + 100;
        }
        y=y+50;
        x1=x;
    }
    aranjare(a, n);
}

void coordonateOperatie(operatie &op)
{
    op.x=c1 + 40;
    op.y=c2 - 50;
}

void coordonateEgal(operatie &egal)
{
    strcpy(egal.simbol, "=");
    egal.x=c1+50;
    if(n%2 == 0)
        egal.y=c2-50;
    else
        egal.y=c2-50;
}

void citireMatrice(punct a[10][10])
{
    f>>n;
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
            f>>a[i][j].info;
}

void afisareMatrice(punct a[10][10], int n)
{
    char str[20];
    for(int i=1; i<=n ; i++)
        for(int j=1; j<=n; j++)
        {
            itoa(a[i][j].info,str,10);
            settextstyle(4, HORIZ_DIR, 3);
            outtextxy(a[i][j].x,a[i][j].y,str);
        }

    elipsa(a, c1, c2);

}

void afisareMatriceFaraElipsa(punct a[10][10], int n) // pt det
{
    char str[20];
    for(int i=1; i<=n ; i++)
        for(int j=1; j<=n; j++)
        {
            itoa(a[i][j].info,str,10);
            settextstyle(4, HORIZ_DIR, 3);
            outtextxy(a[i][j].x,a[i][j].y,str);
        }
}

void Adunare(punct a[10][10], punct b[10][10])
{
//sterge parantezele puse de coordonateMatrice()
    setcolor(15);
    cleardevice();

    //afisare initiala
    afisareMatrice(a,n);

    settextstyle(1, HORIZ_DIR, 7);
    strcpy(op.simbol, "+");

    outtextxy(op.x, op.y, op.simbol); // pun op.simbol
    afisareMatrice(b,n);
    settextstyle(1, HORIZ_DIR, 7);
    outtextxy(egal.x, egal.y, egal.simbol);

    afisareMatrice(a,n);

    settextstyle(1, HORIZ_DIR, 7);
    outtextxy(op.x, op.y, op.simbol);

    afisareMatrice(b,n);


    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
            c[i][j].info = a[i][j].info + b[i][j].info;
    coordonateMatrice(c, egal.x+100, 30);
    aranjare(c, n);
    afisareMatrice(c,n);

    settextstyle(1, HORIZ_DIR, 7);
    outtextxy(egal.x, egal.y, egal.simbol);

    //swapbuffers();

    for(int i=1; i<=n ; i++)
        for(int j=1; j<=n; j++)
        {
            setcolor(15);
            getch();
            cleardevice();
            setbkcolor(BLACK);
            afisareMatrice(a,n);

            settextstyle(1, HORIZ_DIR, 7);
            outtextxy(op.x, op.y, op.simbol);

            afisareMatrice(b,n);

            settextstyle(1, HORIZ_DIR, 7);
            outtextxy(egal.x, egal.y, egal.simbol);

            afisareMatrice(c,n);


            char str[10];
            itoa(a[i][j].info,str,10);
            settextstyle(4, HORIZ_DIR, 4);
            setcolor(9);
            outtextxy(a[i][j].x,a[i][j].y,str);

            char str2[10];
            itoa(b[i][j].info,str2,10);
            settextstyle(4, HORIZ_DIR, 4);
            setcolor(14);
            outtextxy(b[i][j].x,b[i][j].y,str2);

            char str3[10];
            itoa(c[i][j].info,str3,10);
            settextstyle(4, HORIZ_DIR, 4);
            setcolor(10);
            outtextxy(c[i][j].x,c[i][j].y,str3);
            //swapbuffers();
        }

    getch();
    cleardevice();
    meniuMatrice();
}

void Scadere(punct a[10][10], punct b[10][10])
{
    setcolor(15);
    cleardevice();
    //afisare initiala
    afisareMatrice(a,n);

    settextstyle(1, HORIZ_DIR, 2);
    strcpy(op.simbol, "-");

    outtextxy(op.x, op.y, op.simbol); // pun op.simbol
    afisareMatrice(b,n);
    settextstyle(1, HORIZ_DIR, 7);
    outtextxy(egal.x, egal.y, egal.simbol);

    afisareMatrice(a,n);

    settextstyle(1, HORIZ_DIR, 7);
    outtextxy(op.x, op.y, op.simbol);

    afisareMatrice(b,n);

    //calculez matricea rezultat
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
            c[i][j].info = a[i][j].info - b[i][j].info;

    coordonateMatrice(c, egal.x+100, 30);

    aranjare(c,n);
    afisareMatrice(c,n);

    settextstyle(1, HORIZ_DIR, 7);
    outtextxy(egal.x, egal.y, egal.simbol);
    //swapbuffers();
    for(int i=1; i<=n ; i++)
    {

        for(int j=1; j<=n; j++)
        {
            setcolor(15);
            getch();
            cleardevice();
            setbkcolor(BLACK);
            afisareMatrice(a,n);

            settextstyle(1, HORIZ_DIR, 7);
            outtextxy(op.x, op.y, op.simbol);

            afisareMatrice(b,n);

            settextstyle(1, HORIZ_DIR, 7);
            outtextxy(egal.x, egal.y, egal.simbol);

            afisareMatrice(c,n);


            char str[10];
            itoa(a[i][j].info,str,10);
            settextstyle(4, HORIZ_DIR, 4);
            setcolor(9);
            outtextxy(a[i][j].x,a[i][j].y,str);

            char str2[10];
            itoa(b[i][j].info,str2,10);
            settextstyle(4, HORIZ_DIR, 4);
            setcolor(14);
            outtextxy(b[i][j].x,b[i][j].y,str2);

            char str3[10];
            itoa(c[i][j].info,str3,10);
            settextstyle(4, HORIZ_DIR, 4);
            setcolor(10);
            outtextxy(c[i][j].x,c[i][j].y,str3);

        }

    }
    //swapbuffers();
    getch();
    cleardevice();
    meniuMatrice();

}

void Inmultire(punct a[10][10], punct b[10][10])
{
    //AFISARE INITIALA
    afisareMatrice(a,n);

    settextstyle(1, HORIZ_DIR, 2);
    strcpy(op.simbol, "x");

    outtextxy(op.x, op.y, op.simbol); // pun op.simbol
    afisareMatrice(b,n);
    settextstyle(1, HORIZ_DIR, 7);
    outtextxy(egal.x, egal.y, egal.simbol);

    afisareMatrice(a,n);

    settextstyle(1, HORIZ_DIR, 7);
    outtextxy(op.x, op.y, op.simbol);

    afisareMatrice(b,n);

    //CALCULEAZA
    int k=0, counter=1, s=0,p=0;
    for(int i=1; i<=n; i++)
    {
        k=0;
        p=0;
        counter=1;
        while(counter <= n)//ia fiecare linie din a[][] de n ori
        {
            k++;
            s=0;
            for(int j=1; j<=n; j++) // liniile din a[][]
            {
                s = s + a[i][j].info * b[j][k].info;

            }
            c[i][++p].info = s;
            counter++;
        }
    }

    coordonateMatrice(c, egal.x+100, 30);
    aranjare(c,n);
    afisareMatrice(c,n);

    settextstyle(1, HORIZ_DIR, 7);
    outtextxy(egal.x, egal.y, egal.simbol);

    //PUNE DREPTUNGHIURILE SI FACE LINIA DE SUB
    for(int i=1; i<=n; i++)
    {
        k=0;
        p=0;

        for(int j=1; j<=n; j++)
        {
            setcolor(15);
            getch();
            cleardevice();
            setbkcolor(BLACK);
            afisareMatrice(a,n);

            settextstyle(1, HORIZ_DIR, 7);
            outtextxy(op.x, op.y, op.simbol);

            afisareMatrice(b,n);

            settextstyle(1, HORIZ_DIR, 7);
            outtextxy(egal.x, egal.y, egal.simbol);

            afisareMatrice(c,n);

            k++;//muta coloanele din b[][]
            setcolor(9);
            celMaiLungNumarColoanaCoordonate(a, n, _x, _y, 1);
            rectangle(_x, a[i][1].y - 5, a[i][n].x + numarCifre(a[i][n].info) * 20, a[i][n].y + 30);

            setcolor(14);
            celMaiLungNumarColoanaCoordonate(b, n, _x, _y, k);
            celMaiLungNumarColoana(b,n,cmax, k);
            rectangle(_x, b[1][k].y - 5, _x + cmax*20, b[n][k].y + 30);



            char str3[10];
            itoa(c[i][j].info,str3,10);
            settextstyle(4, HORIZ_DIR, 4);
            setcolor(10);
            outtextxy(c[i][j].x,c[i][j].y,str3);


            ///LINIA EXPLICITA
            char s1[10],s2[10],s3[100];
            strcpy(s3, "");
            for(int l=1; l<=n; l++)
            {
                itoa(a[i][l].info, s1, 10);
                itoa(b[l][k].info, s2, 10);

                strcat(s3, s1);
                strcat(s3, "*");
                strcat(s3, s2);
                if(l < n) // sa nu puna un + in plus
                    strcat(s3, " + ");
            }
            strcat(s3, " = ");
            char ss[10]="";
            itoa(c[i][j].info, ss, 10);
            strcat(s3, ss);
            strcat(s3, " ;) ");
            outtextxy(a[n][1].x, a[n][1].y + 75, s3);

            //swapbuffers();
        }
    }
    getch();
    cleardevice();
    meniuMatrice();
}

void transpusaMatriceiAfisare(punct a[10][10])
{
    punct c[10][10];
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
            c[i][j].info = a[j][i].info;

    afisareMatrice(a,n);

    settextstyle(1, HORIZ_DIR, 7);
    strcpy(op.simbol, "~");
    outtextxy(op.x, op.y, op.simbol); // pun op.simbol

    coordonateMatrice(c, op.x+100, 30);

    aranjare(c,n);
    afisareMatrice(c,n);

    settextstyle(1, HORIZ_DIR, 5);
    operatie t;
    strcpy(t.simbol, "t");
    celMaiLungNumarColoana(c,n, cmax, 1);
    //dc nu afiseaza t
    for(int i=1; i<=n; i++)
        if(numarCifre(c[i][1].info) == cmax)
        {
            t.x=c[i][1].x - 50;
            t.y=c[1][1].y;
            i=n+1;//break
        }
    outtextxy(t.x, t.y, t.simbol);

    //dreptunghiuri
    for(int i=1; i<=n; i++)
    {
        setcolor(15);
        getch();
        cleardevice();

        afisareMatrice(a,n);

        settextstyle(1, HORIZ_DIR, 7);
        strcpy(op.simbol, "~");
        outtextxy(op.x, op.y, op.simbol); // pun op.simbol

        coordonateMatrice(c, op.x+100, 30);

        aranjare(c,n);
        afisareMatrice(c,n);

        settextstyle(1, HORIZ_DIR, 5);
        outtextxy(t.x, t.y, t.simbol);

        setcolor(14);
        celMaiLungNumarColoanaCoordonate(a,n,_x,_y,1);
        rectangle(_x, a[i][1].y - 5, a[i][n].x +  numarCifre(a[i][n].info) * 20, a[i][n].y + 30);

        celMaiLungNumarColoana(c,n, cmax, i);
        celMaiLungNumarColoanaCoordonate(c,n, _x, _y, i);//coordonatele celui mai lung nr de pe coloana i

        rectangle(_x, c[1][i].y, _x + cmax*20, c[n][i].y + 30);
        setcolor(15);
    }
    getch();
    cleardevice();
    meniuMatrice();
}

void transpusaMatriceiValoare(punct a[10][10], punct c[10][10])
{
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
            c[i][j].info=a[j][i].info;
}

void liniiDeterminant(punct a[10][10])
{
    char str2[10];
    setcolor(10);
    getch();

    line(a[1][1].x, a[1][1].y, a[2][2].x, a[2][2].y);

    int rez=0;
    char s[50],s1[10],s2[10],s3[10];
    strcpy(s, "");
    itoa(a[1][1].info, s1, 10);
    strcat(s, " + ");
    strcat(s, s1);
    strcat(s, " * ");
    itoa(a[2][2].info, s2, 10);
    strcat(s, s2);
    strcat(s, " * ");

    line(a[2][2].x, a[2][2].y, a[3][3].x, a[3][3].y);

    itoa(a[3][3].info, s3, 10);
    strcat(s, s3);
    outtextxy(egalX + 50, 100, s);
    rez=a[1][1].info*a[2][2].info*a[3][3].info;

    setcolor(15);
    for(int i=1; i<=n ; i++)
        for(int j=1; j<=n; j++)
        {
            itoa(a[i][j].info,str2,10);
            settextstyle(4, HORIZ_DIR, 3);
            outtextxy(a[i][j].x,a[i][j].y,str2);
        }
    setcolor(10);
    getch();

    line(a[2][1].x, a[2][1].y, a[3][2].x, a[3][2].y);

    strcpy(s, "");
    itoa(a[2][1].info, s1, 10);
    strcat(s, " + ");
    strcat(s, s1);
    strcat(s, " * ");
    itoa(a[3][2].info, s2, 10);
    strcat(s, s2);
    strcat(s, " * ");

    line(a[3][2].x, a[3][2].y, a[n][3].x, a[n][3].y+50);

    itoa(a[1][3].info, s3, 10);
    strcat(s, s3);
    outtextxy(egalX + 50, 150, s);
    rez=rez + a[2][1].info*a[3][2].info*a[1][3].info;

    setcolor(15);
    for(int i=1; i<=n ; i++)
        for(int j=1; j<=n; j++)
        {
            itoa(a[i][j].info,str2,10);
            settextstyle(4, HORIZ_DIR, 3);
            outtextxy(a[i][j].x,a[i][j].y,str2);
        }
    setcolor(10);
    getch();

    line(a[3][1].x, a[3][1].y, a[3][2].x, a[3][2].y+50);

    strcpy(s, "");
    itoa(a[3][1].info, s1, 10);
    strcat(s, " + ");
    strcat(s, s1);
    strcat(s, " * ");
    itoa(a[1][2].info, s2, 10);
    strcat(s, s2);
    strcat(s, " * ");

    line(a[3][2].x, a[3][2].y+50, a[n][3].x, a[n][3].y+100);

    itoa(a[2][3].info, s3, 10);
    strcat(s, s3);
    outtextxy(egalX + 50, 200, s);
    rez=rez + a[3][1].info*a[1][2].info*a[2][3].info;

    setcolor(15);
    for(int i=1; i<=n ; i++)
        for(int j=1; j<=n; j++)
        {
            itoa(a[i][j].info,str2,10);
            settextstyle(4, HORIZ_DIR, 3);
            outtextxy(a[i][j].x,a[i][j].y,str2);
        }
    char str[10];
    for(int j=1; j<=n; j++)
    {
        itoa(a[1][j].info, str, 10);
        celMaiLungNumarColoana(a,n, cmax, j);
        outtextxy(a[1][j].x, a[n][j].y + 50, str);
    }
    for(int j=1; j<=n; j++)
    {
        itoa(a[2][j].info, str, 10);
        outtextxy(a[2][j].x, a[n][j].y + 100, str);
    }




    setcolor(12);
    getch();

    line(a[1][n].x, a[1][n].y, a[2][2].x, a[2][2].y);

    strcpy(s, "");
    itoa(a[1][n].info, s1, 10);
    strcat(s, " - ");
    strcat(s, s1);
    strcat(s, " * ");
    itoa(a[2][2].info, s2, 10);
    strcat(s, s2);
    strcat(s, " * ");

    line(a[2][2].x, a[2][2].y, a[n][1].x, a[n][1].y);

    itoa(a[n][1].info, s3, 10);
    strcat(s, s3);
    outtextxy(egalX + 50, 250, s);
    rez=rez - a[1][3].info*a[2][2].info*a[3][1].info;

    setcolor(15);
    for(int i=1; i<=n ; i++)
        for(int j=1; j<=n; j++)
        {
            itoa(a[i][j].info,str2,10);
            settextstyle(4, HORIZ_DIR, 3);
            outtextxy(a[i][j].x,a[i][j].y,str2);
        }
    setcolor(12);
    getch();

    line(a[2][3].x, a[2][3].y, a[n][2].x, a[n][2].y);

    strcpy(s, "");
    strcat(s, " - ");
    itoa(a[2][3].info, s1, 10);
    strcat(s, s1);
    strcat(s, " * ");
    itoa(a[n][2].info, s2, 10);
    strcat(s, s2);
    strcat(s, " * ");

    line(a[n][2].x, a[n][2].y, a[n][1].x, a[n][1].y+50);

    itoa(a[1][1].info, s3, 10);
    strcat(s, s3);
    outtextxy(egalX + 50, 300, s);
    rez=rez - a[2][3].info*a[3][2].info*a[1][1].info;

    setcolor(15);
    for(int i=1; i<=n ; i++)
        for(int j=1; j<=n; j++)
        {
            itoa(a[i][j].info,str2,10);
            settextstyle(4, HORIZ_DIR, 3);
            outtextxy(a[i][j].x,a[i][j].y,str2);
        }
    setcolor(12);
    getch();

    line(a[n][n].x, a[n][n].y, a[3][2].x, a[3][2].y+50);

    strcpy(s, "");
    strcat(s, " - ");
    itoa(a[n][n].info, s1, 10);
    strcat(s, s1);
    strcat(s, " * ");
    itoa(a[1][2].info, s2, 10);
    strcat(s, s2);
    strcat(s, " * ");

    line(a[3][2].x, a[3][2].y+50, a[n][1].x, a[n][1].y+100);

    itoa(a[2][1].info, s3, 10);
    strcat(s, s3);
    strcat(s, " = ");
    rez=rez - a[3][3].info*a[1][2].info*a[2][1].info;
    char rezChar[20]="";
    itoa(rez, rezChar, 10);
    strcat(s, rezChar);
    outtextxy(egalX + 50, 350, s);


    setcolor(15);
    for(int i=1; i<=n ; i++)
        for(int j=1; j<=n; j++)
        {
            itoa(a[i][j].info,str2,10);
            settextstyle(4, HORIZ_DIR, 3);
            outtextxy(a[i][j].x,a[i][j].y,str2);
        }
    for(int j=1; j<=n; j++)
    {
        itoa(a[1][j].info, str, 10);
        celMaiLungNumarColoana(a,n, cmax, j);
        outtextxy(a[1][j].x, a[n][j].y + 50, str);
    }
    for(int j=1; j<=n; j++)
    {
        itoa(a[2][j].info, str, 10);
        outtextxy(a[2][j].x, a[n][j].y + 100, str);
    }
}

void determinantMatriceAfisare(punct a[10][10])
{
    coordonateMatriceDeterminant(a, 50, 50);
    char str2[10];
    for(int i=1; i<=n ; i++)
        for(int j=1; j<=n; j++)
        {
            itoa(a[i][j].info,str2,10);
            settextstyle(4, HORIZ_DIR, 3);
            outtextxy(a[i][j].x,a[i][j].y,str2);
        }

    celMaiLungNumarColoana(a,n, cmax, 1);
    for(int i=1; i<=n; i++)
        if(numarCifre(a[i][1].info) == cmax || cmax == 0)
            line(a[i][1].x - 25, a[1][1].y, a[i][1].x - 25, a[n][1].y + 30);
    celMaiLungNumarColoana(a,n, cmax, n);
    setlinestyle(0,0,3);
    for(int i=1; i<=n; i++)
        if(numarCifre(a[i][n].info) == cmax || cmax == 0)
            line(a[i][n].x + (cmax+1)*25, a[1][n].y, a[i][n].x + (cmax+1)*25, a[n][n].y + 30);

    //egal
    celMaiLungNumarColoana(a,n, cmax, n);
    for(int i=1; i<=n; i++)
        if(numarCifre(a[i][n].info) == cmax)
        {
            //outtextxy(a[i][n].x + cmax*20 + 50, 100, "=");
            outtextxy(a[i][n].x + cmax*20 + 50, (a[n][n].y + 50)/2, "=");
            egalX=a[i][n].x + cmax*20 + 50;
            i=n+1;
        }
    if(n == 3)
    {
        getch();
        char str[10];
        for(int j=1; j<=n; j++)
        {
            itoa(a[1][j].info, str, 10);
            outtextxy(a[1][j].x, a[n][j].y + 50, str);
        }
        getch();
        for(int j=1; j<=n; j++)
        {
            itoa(a[2][j].info, str, 10);
            outtextxy(a[2][j].x, a[n][j].y + 100, str);
        }
        liniiDeterminant(a);
    }
    else if(n == 2)
    {
        int rez=0;
        char rezChar[20]="",s1[10],s2[10];
        rez = a[1][1].info*a[2][2].info - (a[1][2].info*a[2][1].info);
        itoa(rez, rezChar, 10);
        getch();
        setcolor(10);
        line(a[1][1].x, a[1][1].y, a[2][2].x, a[2][2].y);
        itoa(a[1][1].info, s1, 10);
        setcolor(15);
        outtextxy(a[1][1].x, a[1][1].y, s1);

        setcolor(12);
        getch();
        line(a[1][2].x, a[1][2].y, a[2][1].x, a[2][1].y);
        itoa(a[1][2].info, s2, 10);
        setcolor(15);
        outtextxy(a[1][2].x, a[1][2].y, s2);
        setcolor(15);
        getch();
        outtextxy(egalX + 50, (a[n][n].y + 50)/2, rezChar);
    }
    else
    {
        int rez=0;
        char rezChar[20]="";
        rez = a[1][1].info;
        itoa(rez, rezChar, 10);
        outtextxy(egalX + 50, 100, rezChar);
    }
    getch();
    cleardevice();
    meniuMatrice();
}

void determinantMatriceValoare(punct a[10][10], int val, long &det)
{
    det=0;
    int l, c, ok;
    long detAux;
    punct x[10][10];

    if(val == 4)
    {
        //despart matricea mare si formez 4 matrici mai mici
        for(int i=1; i<=n; i++)//parcurge prima coloana a[][] si despart in matrici mai mici
        {
            l=1;
            for(int i1=1; i1<=n; i1++)//ultimele 2 foruri formeaza cate o matrice micsorata dupa linia i
            {
                c=1;
                ok=0;
                for(int j1=1; j1<=n; j1++)
                    if(i1!=i && j1!=1) // iau toate elem de pe prima coloana
                    {
                        x[l][c].info=a[i1][j1].info;
                        ok=1;
                        c++;
                    }
                if(ok==1)//am folosit linia l
                    l++;
            }
            l--;
            c--;
            /*
                iau ficare matrice mica, sii calculez det., il inmultesc cu a[i][1] (elem dupa care
                s-a separat matricea) si cu -1 la i+j
                si fac suma din toate nr astea si ala e det de ordin 4
            */
            //det matricii mici
            detAux=0;
            detAux=x[1][1].info*x[2][2].info*x[3][3].info + x[2][1].info*x[3][2].info*x[1][3].info + x[3][1].info*x[1][2].info*x[2][3].info;
            detAux=detAux-( x[1][3].info*x[2][2].info*x[3][1].info + x[2][3].info*x[3][2].info*x[1][1].info + x[3][3].info*x[1][2].info*x[2][1].info );


            //inmultesc detAux cu elem de pe I coloana si cu -1 la i+1
            det = det + detAux * a[i][1].info * pow(-1, i+1);
        }
    }
    else if(val == 3)
    {
        det=a[1][1].info*a[2][2].info*a[3][3].info + a[2][1].info*a[3][2].info*a[1][3].info + a[3][1].info*a[1][2].info*a[2][3].info;
        det=det-( a[1][3].info*a[2][2].info*a[3][1].info + a[2][3].info*a[3][2].info*a[1][1].info + a[3][3].info*a[1][2].info*a[2][1].info );
    }
    else if(val == 2)
        det=a[1][1].info*a[2][2].info - a[1][2].info*a[2][1].info;
    else if(val == 1)
        det=a[1][1].info;
}

void InmultireMatriceScalar(punct a[10][10], int sc)
{
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
            a[i][j].info = a[i][j].info*sc;
}

void Inversa(punct a[10][10])
{
    int l,c,ok,x_start,x_final;
    long rezultat=0;
    char indice1[2], indice2[2],elem[10]="", rezultatChar[100]="", str1[50], str2[50];
    punct x[10][10], aStelat[10][10], d[10][10];


    determinantMatriceValoare(a, n, det);
    if(det == 0)
    {
        setcolor(4);
        outtextxy(100, 100, "NU EXISTA INVERSA MATRICII");
    }
    else
    {
        coordonateMatrice(a, 125, 50);
        aranjare(a,n);
        afisareMatrice(a,n);

        celMaiLungNumarColoanaCoordonate(a,n, x_start, _y, 1);
        celMaiLungNumarColoanaCoordonate(a,n, x_final, _y, n);
        celMaiLungNumarColoana(a,n, cmax, n);
        x_final=x_final + cmax*20;

        settextstyle(4, HORIZ_DIR, 4);
        outtextxy(x_start - 110, a[n/2][1].y, " A=");

        for(int i=1; i<=n; i++) // parcurge fiecare elem din a[][]
        {
            for(int j=1; j<=n; j++)
            {
                getch();

                cleardevice();
                settextstyle(4, HORIZ_DIR, 4);
                outtextxy(x_start - 110, a[n/2][1].y, " A=");
                afisareMatrice(a,n);

                celMaiLungNumarColoanaCoordonate(a,n, _x, _y, j);
                celMaiLungNumarColoana(a,n, cmax, j);
                setcolor(14);
                if(cmax > 1)
                    rectangle(_x - 5, a[1][j].y - 5, _x + cmax*20, a[n][j].y + 30);// |
                else
                    rectangle(a[i][j].x - 5, a[1][j].y - 5, a[n][j].x + 20 + 5, a[n][j].y + 30);// |

                rectangle(x_start - 5, a[i][1].y - 5, x_final, a[i][n].y + 30);// -
                setcolor(15);


                //parcurg a[][] si bag in c[][] matricea ramasa
                l=1;
                for(int i1=1; i1<=n; i1++)
                {
                    c=1;
                    ok=0;
                    for(int j1=1; j1<=n; j1++)
                        if(i1!=i && j1!=j)
                        {
                            x[l][c].info=a[i1][j1].info;
                            ok=1;
                            c++;
                        }
                    if(ok==1)//am folosit linia l
                        l++;
                }
                l--;
                c--;

                //afisez det
                coordonateMatriceInversa(x, l, a[1][n].x + 300, 50);
                aranjare(x, l);
                //afisareMatrice(x, l);
                afisareMatriceFaraElipsa(x, l);

                //linii verticale pt det
                celMaiLungNumarColoanaCoordonate(x, l, _x, _y, 1);
                line(_x - 5, x[1][1].y, _x - 5, x[l][1].y + 30);
                celMaiLungNumarColoanaCoordonate(x, l, _x, _y, l);
                celMaiLungNumarColoana(x, l, cmax, l);
                line(_x + 20*cmax + 5, x[1][l].y, _x + 20*cmax + 5, x[l][1].y + 30);

                settextstyle(4, HORIZ_DIR, 2);
                strcpy(elem, "");
                itoa(i, indice1, 10);
                itoa(j, indice2, 10);
                strcat(elem, "A");
                strcat(elem, indice1);
                strcat(elem, indice2);
                strcat(elem, " = ");

                celMaiLungNumarColoanaCoordonate(x, l, _x, _y, 1);
                if(l%2 == 0)
                    _y=x[l/2][1].y + 20;
                else
                    _y=x[l/2+1][1].y ;
                setcolor(14);
                outtextxy( _x - 100, _y, elem); // A11, A12
                setcolor(15);

                //produsul dintre determinant si numar
                celMaiLungNumarColoana(x, l, cmax, l);
                for(int k=1; k<=l; k++)
                    if(numarCifre(x[k][l].info) == cmax)//caut cel mai lung nr de pe ultima coloana din x[][]
                    {

                        strcpy(rezultatChar, "");
                        strcat(rezultatChar, "x (-1)^(");
                        itoa(i, str1, 10);
                        itoa(j, str2, 10);
                        strcat(rezultatChar, str1);
                        strcat(rezultatChar, "+");
                        strcat(rezultatChar, str2);
                        strcat(rezultatChar, ") = ");

                        //calculez rezultat in int
                        det=0;
                        determinantMatriceValoare(x, l, det);

                        rezultat = det*(pow(-1, i+j)); // elementele din A*

                        itoa(rezultat, str1, 10);
                        strcat(rezultatChar, str1);

                        outtextxy(x[k][l].x + numarCifre(x[k][l].info)*20 + 20, _y, rezultatChar);

                        k=l+1;//break
                    }

                d[i][j].info=rezultat;//asta e A* netransups, il transpun mai tarziu
            }
        }
        //swapbuffers();

        getch();
        cleardevice();
        //swapbuffers();
        coordonateMatrice(a, 125, 50);
        int ok2=0;
        //caut nr neg
        for(int i=1; i<=n; i++)
            for(int j=1; j<=n; j++)
                if(a[i][j].info < 0 )
                {
                    ok2=1;
                    j=n+1;
                    i=n+1;
                }
        if(ok2 == 0)
            aranjare(a,n);
        afisareMatrice(a,n);

        settextstyle(4, HORIZ_DIR, 4);
        setcolor(14);
        outtextxy(x_start - 110, a[n/2][1].y, " A= ");
        setcolor(15);

        transpusaMatriceiValoare(d, aStelat);

        celMaiLungNumarColoana(a,n, cmax, n);
        for(int i=1; i<=n; i++)
        {
            if(numarCifre(a[i][n].info) == cmax)
            {
                setcolor(14);
                outtextxy(a[i][n].x + cmax*20 + 25, _y, "A*= " );
                coordonateMatrice(aStelat, a[i][n].x + cmax*20 + 125, 50);
                //outtextxy(x_start - 110, a[n/2][1].y + 200, "A*= " );
                //coordonateMatrice(aStelat, 125, 400);

                i=n+1;//break}
            }
        }
        setcolor(15);

        afisareMatrice(aStelat,n);
        //swapbuffers();
        getch();
        cleardevice();

        char s[100], s1[20]="", s2[20]="";
        strcat(s, "A^(-1) = A* x 1/det(A) = ");
        outtextxy(10, 200, s);

        coordonateMatrice(aStelat, 410, 150);
        afisareMatrice(aStelat,n);

        determinantMatriceValoare(a, n, det);
        itoa(det, s1, 10);
        strcat(s2, " x 1 / ");
        strcat(s2, s1);
        if(c1 > 1200) // daca nu incape in fereastra
            outtextxy(aStelat[n][1].x, aStelat[n][1].y + 60, s2);
        else
            outtextxy(c1+30, 200, s2);

        //swapbuffers();
    }
    getch();
    cleardevice();
    meniuMatrice();
}

int elemNegative(punct a[10][10], int n)
{
    int ok=0;
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
            if(a[i][j].info < 0)
            {
                ok=1;
                i=n+1;//break
                j=n+1;//break;
            }
    return ok;
}

void sumaElementelorDeSubDP(punct a[10][10], int n)
{

    coordonateMatrice(a, 150, 30);
    if(elemNegative(a, n) == 0)//nu aranjez matrici cu elem negative
        aranjare(a,n);
    outtextxy(20, a[n/2][1].y, "A=");
    afisareMatrice(a,n);

    char s[20],s1[50];
    int suma=0;
    strcpy(s1, "");
    strcat(s1, "S = ");

    for(int i=1; i<=n; i++)//coloreaza diagonala principala
    {
        getch();
        //delay(1000);
        setcolor(13);
        itoa(a[i][i].info, s, 10);
        outtextxy(a[i][i].x, a[i][i].y, s);
    }

    setcolor(15);
    strcpy(s, "");
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
            if(i>j)
            {
                getch();
                //delay(1000);
                setcolor(14);
                strcpy(s, "");
                itoa(a[i][j].info, s, 10);
                outtextxy(a[i][j].x, a[i][j].y, s);

                strcat(s1, s);
                if(j!=n-1)//mai am elem de adunat
                    strcat(s1, " + ");
                else
                    strcat(s1, " = ");
                outtextxy(a[n][1].x, a[n][1].y + 100, s1);
                suma+=a[i][j].info;
            }
    getch();
    itoa(suma,s, 10);
    strcat(s1, s);
    outtextxy(a[n][1].x, a[n][1].y+100, s1);

    getch();
    cleardevice();
    meniuMatrice();
}

void operatieColoane(punct a[10][10], int n, int C1, int C2, char op[2])
{
    int ok;
    coordonateMatrice(a, 150, 30);
    if(elemNegative(a, n) == 0)//nu aranjez matrici cu elem negative
        aranjare(a,n);
    afisareMatrice(a,n);

    int x1,x2,y1,y2,a1,b1,a2,b2;
    celMaiLungNumarColoanaCoordonate(a,n, _x, _y, n);
    celMaiLungNumarColoana(a,n, cmax, n);
    //coordonate linii pentru egal
    if(n%2 == 0)
    {
        x1=_x + cmax*20 + 60;
        y1=a[n/2][1].y;
        x2=_x + cmax*20 + 60;
        y2=a[n/2][1].y + 20;
        a1=x1 + 130;
        b1=y1;
        a2=x2 + 130;
        b2=y2;
        outtextxy(a[1][1].x - 110, y1, "A=");
    }
    else
    {
        x1=_x + cmax*20 + 60;
        y1=a[n/2][1].y + 40;
        x2=_x + cmax*20 + 60;
        y2=a[n/2][1].y + 20 + 40;
        a1=x1 + 130;
        b1=y1;
        a2=x2 + 130;
        b2=y2;
        outtextxy(a[1][1].x - 110, y1, "A=");
    }

    //setlinestyle(0, 0, 3);
    line(x1,y1,a1,b1);
    line(x2,y2,a2,b2);

    char coloana1[10],coloana2[10],s[20]="";
    itoa(C1, coloana1, 10);
    itoa(C2, coloana2, 10);
    strcat(s, "C");
    strcat(s, coloana1);
    strcat(s, " ");
    strcat(s, op);
    strcat(s, " ");
    strcat(s, "C");
    strcat(s, coloana2);
    outtextxy(x1, y1-25, s);

    setcolor(14);
    celMaiLungNumarColoanaCoordonate(a,n, _x, _y, C1);
    celMaiLungNumarColoana(a,n, cmax, C1);
    ok=0;
    for(int i=1; i<=n; i++)
    {
        if(numarCifre(a[i][C1].info) == cmax && a[i][C1].info < 0)//caut nr cel mai lung si vad daca e negativ
        {
            rectangle(_x, a[1][C1].y - 5, _x +  cmax * 20 + 10, a[n][C1].y + 30); // pun spatiu in plus pentru " - "
            ok=1;// am desenat dreptunghi deja
        }
    }
    if(ok == 0)//coloana mea nu are numere negative
        rectangle(_x, a[1][C1].y - 5, _x +  cmax * 20, a[n][C1].y + 30); // pun spatiu in plus pentru " - "

    //fac operatia
    if(op == "+")
        for(int i=1; i<=n; i++)
            a[i][C1].info = a[i][C1].info + a[i][C2].info;
    if(op == "-")
        for(int i=1; i<=n; i++)
            a[i][C1].info = a[i][C1].info - a[i][C2].info;

    setcolor(13);
    celMaiLungNumarColoana(a,n, cmax, C2);
    celMaiLungNumarColoanaCoordonate(a,n, _x, _y, C2);
    ok=0;
    for(int i=1; i<=n; i++)
    {
        if(numarCifre(a[i][C1].info) == cmax && a[i][C1].info < 0)//caut nr cel mai lung si vad daca e negativ
        {
            rectangle(_x, a[1][C1].y - 5, _x +  cmax * 20 + 10, a[n][C1].y + 30); // pun spatiu in plus pentru " - "
            ok=1;// am desenat dreptunghi deja
        }
    }
    if(ok == 0)//coloana mea nu are numere negative, fac dreptunghiul normal
        rectangle(_x, a[1][C1].y - 5, _x +  cmax * 20, a[n][C1].y + 30);

    setcolor(15);

    getch();
    coordonateMatrice(a, a1 + 50, 30);
    if(elemNegative(a, n) == 0)//nu aranjez matrici cu elem negative
        aranjare(a,n);
    afisareMatrice(a,n);

    //colorez coloanele din dreapta
    strcpy(s, "");
    setcolor(14);
    for(int i=1; i<=n; i++)
    {
        itoa(a[i][C1].info, s, 10);
        outtextxy(a[i][C1].x, a[i][C1].y, s);
    }
    strcpy(s, "");
    setcolor(13);
    for(int i=1; i<=n; i++)
    {
        itoa(a[i][C2].info, s, 10);
        outtextxy(a[i][C2].x, a[i][C2].y, s);
    }

    getch();
    cleardevice();
    meniuMatrice();
}

void operatieLinii(punct a[10][10], int n, int L1, int L2, char op[2])
{
    int ok;
    coordonateMatrice(a, 150, 30);
    if(elemNegative(a, n) == 0)//nu aranjez matrici cu elem negative
        aranjare(a,n);
    if(n%2 == 0)
        outtextxy(20, a[n/2][1].y + 30, "A=");
    else
        outtextxy(20, a[n/2][1].y + 50, "A=");
    afisareMatrice(a,n);

    int x1,x2,y1,y2,a1,b1,a2,b2;
    celMaiLungNumarColoanaCoordonate(a,n, _x, _y, n);
    celMaiLungNumarColoana(a,n, cmax, n);

    //coordonate linii pentru egal
    if(n%2 == 1)
    {
        x1=_x + cmax*20 + 60;
        y1=a[n/2][1].y + 50;
        x2=_x + cmax*20 + 60;
        y2=a[n/2][1].y + 80;
        a1=x1 + 130;
        b1=y1;
        a2=x2 + 130;
        b2=y2;
    }
    else
    {
        x1=_x + cmax*20 + 60;
        y1=a[n/2][1].y + 30;
        x2=_x + cmax*20 + 60;
        y2=a[n/2][1].y + 60;
        a1=x1 + 130;
        b1=y1;
        a2=x2 + 130;
        b2=y2;
    }

    line(x1,y1,a1,b1);
    line(x2,y2,a2,b2);

    char linie1[10],linie2[10],s[20]="";
    itoa(L1, linie1, 10);
    itoa(L2, linie2, 10);
    strcat(s, "L");
    strcat(s, linie1);
    strcat(s, " ");
    strcat(s, op);
    strcat(s, " ");
    strcat(s, "L");
    strcat(s, linie2);
    outtextxy(x1, y1-25, s);

    //fac operatia
    if(op == "+")
        for(int j=1; j<=n; j++)
            a[L1][j].info = a[L1][j].info + a[L2][j].info;
    if(op == "-")
        for(int j=1; j<=n; j++)
            a[L1][j].info = a[L1][j].info - a[L2][j].info;


    setcolor(14);
    celMaiLungNumarColoanaCoordonate(a,n, _x, _y, 1);
    rectangle(_x, a[L1][1].y - 5, a[L1][n].x + numarCifre(a[L1][n].info)*20, a[L1][n].y + 30);


    setcolor(13);
    celMaiLungNumarColoanaCoordonate(a,n, _x, _y, 1);
    rectangle(_x, a[L2][1].y - 5, a[L2][n].x + numarCifre(a[L2][n].info)*20, a[L2][n].y + 30);

    setcolor(15);

    getch();
    coordonateMatrice(a, a1 + 50, 30);
    if(elemNegative(a, n) == 0)//nu aranjez matrici cu elem negative
        aranjare(a,n);
    afisareMatrice(a,n);

    //colorez liniile din dreapta
    strcpy(s, "");
    setcolor(14);
    for(int j=1; j<=n; j++)
    {
        itoa(a[L1][j].info, s, 10);
        outtextxy(a[L1][j].x, a[L1][j].y, s);
    }
    strcpy(s, "");
    setcolor(13);
    for(int j=1; j<=n; j++)
    {
        itoa(a[L2][j].info, s, 10);
        outtextxy(a[L2][j].x, a[L2][j].y, s);
    }
    setcolor(15);

    getch();
    cleardevice();
    meniuMatrice();
}

void operatieLinii2(punct a[10][10], int n)
{
    int ok;
    char op[2];

    coordonateMatrice(a, 150, 30);
    if(elemNegative(a, n) == 0)//nu aranjez matrici cu elem negative
        aranjare(a,n);
    if(n%2 == 0)
        outtextxy(20, a[n/2][1].y + 30, "A=");
    else
        outtextxy(20, a[n/2][1].y + 50, "A=");
    afisareMatrice(a,n);

    int x1,x2,y1,y2,a1,b1,a2,b2;
    celMaiLungNumarColoanaCoordonate(a,n, _x, _y, n);
    celMaiLungNumarColoana(a,n, cmax, n);

    //coordonate linii pentru egal
    if(n%2 == 1)
    {
        x1=_x + cmax*20 + 60;
        y1=a[n/2][1].y + 50;
        x2=_x + cmax*20 + 60;
        y2=a[n/2][1].y + 80;
        a1=x1 + 130;
        b1=y1;
        a2=x2 + 130;
        b2=y2;
    }
    else
    {
        x1=_x + cmax*20 + 60;
        y1=a[n/2][1].y + 30;
        x2=_x + cmax*20 + 60;
        y2=a[n/2][1].y + 60;
        a1=x1 + 130;
        b1=y1;
        a2=x2 + 130;
        b2=y2;
    }

    line(x1,y1,a1,b1);
    line(x2,y2,a2,b2);

    char linie1[10],linie2[10],s[20]="";
    itoa(L1, linie1, 10);
    itoa(L2, linie2, 10);
    strcat(s, "L");
    strcat(s, linie1);
    strcat(s, " ");
    strcat(s, op);
    strcat(s, " ");
    strcat(s, "L");
    strcat(s, linie2);
    outtextxy(x1, y1-25, s);

    //fac operatia
    if(op == "+")
        for(int j=1; j<=n; j++)
            a[L1][j].info = a[L1][j].info + a[L2][j].info;
    if(op == "-")
        for(int j=1; j<=n; j++)
            a[L1][j].info = a[L1][j].info - a[L2][j].info;


    setcolor(14);
    celMaiLungNumarColoanaCoordonate(a,n, _x, _y, 1);
    rectangle(_x, a[L1][1].y - 5, a[L1][n].x + numarCifre(a[L1][n].info)*20, a[L1][n].y + 30);


    setcolor(13);
    celMaiLungNumarColoanaCoordonate(a,n, _x, _y, 1);
    rectangle(_x, a[L2][1].y - 5, a[L2][n].x + numarCifre(a[L2][n].info)*20, a[L2][n].y + 30);

    setcolor(15);

    getch();
    coordonateMatrice(a, a1 + 50, 30);
    if(elemNegative(a, n) == 0)//nu aranjez matrici cu elem negative
        aranjare(a,n);
    afisareMatrice(a,n);

    //colorez liniile din dreapta
    strcpy(s, "");
    setcolor(14);
    for(int j=1; j<=n; j++)
    {
        itoa(a[L1][j].info, s, 10);
        outtextxy(a[L1][j].x, a[L1][j].y, s);
    }
    strcpy(s, "");
    setcolor(13);
    for(int j=1; j<=n; j++)
    {
        itoa(a[L2][j].info, s, 10);
        outtextxy(a[L2][j].x, a[L2][j].y, s);
    }
    setcolor(15);

    getch();
    cleardevice();
    meniuMatrice();
}


void meniuSortare()
{
    int mijx,mijy;
    char matriceoperatii[4][50];
    strcpy(matriceoperatii[0],"Bubble Sort crescator");
    strcpy(matriceoperatii[1],"Bubble Sort descrescator");
    strcpy(matriceoperatii[2],"Selection Sort crescator");
    strcpy(matriceoperatii[3],"Selection Sort descrescator");
    readimagefile("pozafundal.jpg",0,0,getmaxx(),getmaxy());
    mijx=getmaxx()/2;
    mijy=getmaxy()/2;
    settextstyle(BOLD_FONT,HORIZ_DIR,5);
    setbkcolor(COLOR(194,205,193));
    setcolor(BLACK);
    setlinestyle(0,0,3);
    for(int i=0; i<4; i++)
    {
        int a=textwidth(matriceoperatii[i]);
        int b=textheight(matriceoperatii[i]);
        outtextxy(mijx-a/2,getmaxy()/4*i+20,matriceoperatii[i]);
        rectangle(mijx-a/2-3,getmaxy()/4*i+20,mijx-a/2+a,getmaxy()/4*i+b+20);
    }

    do
    {
    if(ismouseclick(WM_LBUTTONDOWN))
    {
        int x,y;
        clearmouseclick(WM_LBUTTONDOWN);
        x=mousex();
        y=mousey();
        for(int i=0; i<4; i++)
        {
            int a=textwidth(matriceoperatii[i]);
            int b=textheight(matriceoperatii[i]);
            if(x>=mijx-a/2 && x<=mijx-a/2+a && y>=getmaxy()/4*i+20 && y<=getmaxy()/4*i+b+20)
                switch(i)
            {
            case 0:
                {

                    setbkcolor(COLOR(0,0,0));
                    settextstyle(4,HORIZ_DIR,9);
                    setlinestyle(0,0,1);
                    citireVector(n,scalar);
                    coordonateVector(vector1,30,30);
                    coordonateVector(vector2,30,120);
                    cleardevice();
                    setcolor(WHITE);
                    bubbleSortCrescator(vector1);
                }
                break;
            case 1:
                {
                    setbkcolor(COLOR(0,0,0));
                        settextstyle(4,HORIZ_DIR,9);
                        setlinestyle(0,0,1);
                        citireVector(n,scalar);
                        coordonateVector(vector1,30,30);
                        coordonateVector(vector2,30,120);
                        cleardevice();
                        setcolor(WHITE);
                        bubbleSortDescrescator(vector1);
                     break;
                }
                case 2:
                    {
                        setbkcolor(COLOR(0,0,0));
                        settextstyle(4,HORIZ_DIR,9);
                        setlinestyle(0,0,1);
                        citireVector(n,scalar);
                        coordonateVector(vector1,30,30);
                        coordonateVector(vector2,30,120);
                        cleardevice();
                        setcolor(WHITE);
                        selectionSortCrescator(vector1);
                        break;
                    }
            case 3:
                {
                    setbkcolor(COLOR(0,0,0));
                    settextstyle(4,HORIZ_DIR,9);
                    setlinestyle(0,0,1);
                    citireVector(n,scalar);
                    coordonateVector(vector1,30,30);
                    coordonateVector(vector2,30,120);
                    cleardevice();
                    setcolor(WHITE);
                    selectionSortDescrescator(vector1);
                   break;
                }
                }

            }
        }
    }
   while(1);
}

void meniuShiftare()
{
    int mijx,mijy;
    char matriceoperatii[2][50];
    strcpy(matriceoperatii[0],"Shiftare la dreapta");
    strcpy(matriceoperatii[1],"Shiftare la stanga");
    readimagefile("pozafundal.jpg",0,0,getmaxx(),getmaxy());
    mijx=getmaxx()/2;
    mijy=getmaxy()/2;
    settextstyle(BOLD_FONT,HORIZ_DIR,6);
    setbkcolor(COLOR(194,205,193));
    setcolor(BLACK);
    setlinestyle(0,0,3);
    for(int i=0; i<2; i++)
    {
        int a=textwidth(matriceoperatii[i]);
        int b=textheight(matriceoperatii[i]);
        outtextxy(mijx-a/2,getmaxy()/3*(i+1),matriceoperatii[i]);
        rectangle(mijx-a/2-3,getmaxy()/3*(i+1),mijx-a/2+a,getmaxy()/3*(i+1)+b);
    }

    do
    {
    if(ismouseclick(WM_LBUTTONDOWN))
    {
        int x,y;
        clearmouseclick(WM_LBUTTONDOWN);
        x=mousex();
        y=mousey();
        for(int i=0; i<2; i++)
        {
            int a=textwidth(matriceoperatii[i]);
            int b=textheight(matriceoperatii[i]);
            if(x>=mijx-a/2 && x<=mijx-a/2+a && y>=getmaxy()/3*(i+1) && y<=getmaxy()/3*(i+1)+b)
                switch(i)
            {
            case 0:
                {

                    setbkcolor(COLOR(0,0,0));
                    settextstyle(4,HORIZ_DIR,9);
                    setlinestyle(0,0,1);
                    citireVector(n,scalar);
                    coordonateVector(vector1,30,30);
                    coordonateVector(vector2,30,120);
                    cleardevice();
                    setcolor(WHITE);
                    shiftareLaDreapta(vector1);
                }
                break;
            case 1:
                {
                    setbkcolor(COLOR(0,0,0));
                        settextstyle(4,HORIZ_DIR,9);
                        setlinestyle(0,0,1);
                        citireVector(n,scalar);
                        coordonateVector(vector1,30,30);
                        coordonateVector(vector2,30,120);
                        cleardevice();
                        setcolor(WHITE);
                        shiftareLaStanga(vector1);
                     break;
                }

                }

            }
        }
    }
   while(1);
}
void meniu();

void meniuVectori()
{

    int mijx,mijy;
    char butonfisier[10]="Fisier";
    char matriceoperatii[10][50];
    strcpy(matriceoperatii[0],"Sortare");
    strcpy(matriceoperatii[1],"Shiftare");
    strcpy(matriceoperatii[2],"Adunare");
    strcpy(matriceoperatii[3],"Scadere");
    strcpy(matriceoperatii[4],"Inmultire cu scalar");
    strcpy(matriceoperatii[5],"Suma elementelor");
    strcpy(matriceoperatii[6],"Produsul elementelor");
    strcpy(matriceoperatii[7],"Produs scalar");
    strcpy(matriceoperatii[9],"Inapoi");
    cleardevice();
    readimagefile("pozafundal.jpg",0,0,getmaxx(),getmaxy());
    mijx=getmaxx()/2;
    mijy=getmaxy()/2;
    settextstyle(BOLD_FONT,HORIZ_DIR,5);
    setbkcolor(COLOR(194,205,193));
    setcolor(BLACK);
    setlinestyle(0,0,3);


    int fisiera=textwidth(butonfisier);
    int fisierb=textheight(butonfisier);
    outtextxy(30,20,butonfisier);
    rectangle(30,20,30+fisiera,20+fisierb);

     int a2=textwidth(matriceoperatii[9]);
    int b2=textheight(matriceoperatii[9]);
    outtextxy(windowWidth - textwidth("Inapoi") - 50, 0,matriceoperatii[9]);
    rectangle(1350, 0, 1550, textheight("Inapoi"));

    for(int i=0; i<8; i++)
    {
        int a=textwidth(matriceoperatii[i]);
        int b=textheight(matriceoperatii[i]);
        outtextxy(mijx-a/2,getmaxy()/8*i+20,matriceoperatii[i]);
        rectangle(mijx-a/2-3,getmaxy()/8*i+20,mijx-a/2+a,getmaxy()/8*i+b+20);
    }

    do
    {
    if(ismouseclick(WM_LBUTTONDOWN))
    {
        int x,y;
        clearmouseclick(WM_LBUTTONDOWN);
        x=mousex();
        y=mousey();
        for(int i=0; i<8; i++)
        {
            int a=textwidth(matriceoperatii[i]);
            int b=textheight(matriceoperatii[i]);
            if(x>=30 && x<=30 +fisiera && y>=20 && y<=20+fisierb)
            {
                system("notepad.exe dateIntrare.txt");

                break;

            }
             if(x>1350&&x<1550 && y>0 && y<textheight("Inapoi"))
            {
                cleardevice();
                meniu();
                break;
            }
            if(x>=mijx-a/2 && x<=mijx-a/2+a && y>=getmaxy()/8*i+20 && y<=getmaxy()/8*i+b+20)
                switch(i)
            {
            case 0:
                {

                    meniuSortare();
                }
                break;
            case 1:
                {
                    meniuShiftare();
                  break;
                }

                case 2:
                    {
                        setbkcolor(COLOR(0,0,0));
                        settextstyle(4,HORIZ_DIR,9);
                        setlinestyle(0,0,1);
                        citireVector(n,scalar);
                        coordonateVector(vector1,30,30);
                        coordonateVector(vector2,30,120);
                        cleardevice();
                        setcolor(WHITE);
                        adunare(vector1,vector2,vector3);
                        break;
                    }
            case 3:
                {
                    setbkcolor(COLOR(0,0,0));
                    settextstyle(4,HORIZ_DIR,9);
                    setlinestyle(0,0,1);
                    citireVector(n,scalar);
                    coordonateVector(vector1,30,30);
                    coordonateVector(vector2,30,120);
                    cleardevice();
                    setcolor(WHITE);
                    scadere(vector1,vector2,vector3);
                   break;
                }

            case 4:
                {
                setbkcolor(COLOR(0,0,0));
                    settextstyle(4,HORIZ_DIR,9);
                    setlinestyle(0,0,1);
                    citireVector(n,scalar);
                    coordonateVector(vector1,30,30);
                    coordonateVector(vector2,30,120);
                    cleardevice();
                    setcolor(WHITE);
                inmultireCuScalar(vector1,scalar);
                break;
                }
            case 5:

                {
                setbkcolor(COLOR(0,0,0));
                    settextstyle(4,HORIZ_DIR,9);
                    setlinestyle(0,0,1);
                    citireVector(n,scalar);
                    coordonateVector(vector1,30,30);
                    coordonateVector(vector2,30,120);
                    cleardevice();
                    setcolor(WHITE);
                sumaElemente(vector1);
                break;
                }
            case 6:
                {
                    setbkcolor(COLOR(0,0,0));
                    settextstyle(4,HORIZ_DIR,9);
                    setlinestyle(0,0,1);
                    citireVector(n,scalar);
                    coordonateVector(vector1,30,30);
                    coordonateVector(vector2,30,120);
                    cleardevice();
                    setcolor(WHITE);
            produsElemente(vector1);
                break;
                }
            case 7:
                {
                setbkcolor(COLOR(0,0,0));
                    settextstyle(4,HORIZ_DIR,9);
                    setlinestyle(0,0,1);
                    citireVector(n,scalar);
                    coordonateVector(vector1,30,30);
                    coordonateVector(vector2,30,120);
                    cleardevice();
                    setcolor(WHITE);
                produsScalar(vector1,vector2);
                break;
                }

            }
        }
    }
    }
   while(1);

}

void meniu();

void meniuMatrice()
{

    int mijx,mijy;
    char matriceoperatii[11][150];
    strcpy(matriceoperatii[0],"Adunare");
    strcpy(matriceoperatii[1],"Scadere");
    strcpy(matriceoperatii[3],"Inmultire");
    strcpy(matriceoperatii[2],"Transpusa matricei");
    strcpy(matriceoperatii[4],"Inversa Matricei");
    strcpy(matriceoperatii[5],"Determinant matrice");
    strcpy(matriceoperatii[6],"Operatii linii");
    strcpy(matriceoperatii[7],"Operatii coloane");
    strcpy(matriceoperatii[8],"Suma elementelor de sub diagonala principala");
    strcpy(matriceoperatii[9],"Inapoi");
    cleardevice();
    readimagefile("pozafundal.jpg",0,0,getmaxx(),getmaxy());
    mijx=getmaxx()/2;
    mijy=getmaxy()/2;
    settextstyle(BOLD_FONT,HORIZ_DIR,5);
    setbkcolor(COLOR(194,205,193));
    setcolor(BLACK);
    setlinestyle(0,0,3);

    //INAPOI
    int a2=textwidth(matriceoperatii[9]);
    int b2=textheight(matriceoperatii[9]);
    outtextxy(windowWidth - textwidth("Inapoi") - 50, 0,matriceoperatii[9]);
    rectangle(1350, 0, 1550, textheight("Inapoi"));

    for(int i=0; i<9; i++)
    {
        int a=textwidth(matriceoperatii[i]);
        int b=textheight(matriceoperatii[i]);
        outtextxy(mijx-a/2,getmaxy()/9*i+20,matriceoperatii[i]);
        rectangle(mijx-a/2-3,getmaxy()/9*i+20,mijx-a/2+a,getmaxy()/9*i+b+20);
    }

    char butonfisier[10]="Fisier";
    int fisiera=textwidth(butonfisier);
    int fisierb=textheight(butonfisier);
    outtextxy(30,20,butonfisier);
    rectangle(30,20,30+fisiera,20+fisierb);

    do
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            int x,y;
            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex();
            y=mousey();
            for(int i=0; i<10; i++)
            {
                if(x>=30 && x<=30 +fisiera && y>=20 && y<=20+fisierb)
                {
                    system("notepad.exe dateIntrare.txt");

                    break;

                }
                if(x>1350&&x<1550 && y>0 && y<textheight("Inapoi"))
            {
                cleardevice();
                meniu();
                break;
            }
                int a1=textwidth(matriceoperatii[i]);
                int b1=textheight(matriceoperatii[i]);
                if(x>=mijx-a1/2 && x<=mijx-a1/2+a1 && y>=getmaxy()/9*i+20 && y<=getmaxy()/9*i+b1+20)
                    switch(i)
                    {
                    case 0:
                        setbkcolor(0);
                        citireMatrice(a);
                        coordonateMatrice(a,50,30);

                        coordonateOperatie(op);

                        citireMatrice(b);
                        coordonateMatrice(b, op.x + 100, 30);

                        coordonateEgal(egal);
                        cleardevice();//sterge parantezele puse de coordonateMatrice()

                        aranjare(a,n);
                        aranjare(b,n);
                        Adunare(a,b);
                        break;
                    case 1:
                        setbkcolor(0);
                        citireMatrice(a);
                        coordonateMatrice(a,50,30);

                        coordonateOperatie(op);

                        citireMatrice(b);
                        coordonateMatrice(b, op.x + 100, 30);

                        coordonateEgal(egal);
                        cleardevice();//sterge parantezele puse de coordonateMatrice()

                        aranjare(a,n);
                        aranjare(b,n);
                        Scadere(a,b);
                        break;
                    case 2:
                        setbkcolor(0);
                        citireMatrice(a);
                        coordonateMatrice(a,50,30);

                        coordonateOperatie(op);

                        citireMatrice(b);
                        coordonateMatrice(b, op.x + 100, 30);

                        coordonateEgal(egal);
                        cleardevice();//sterge parantezele puse de coordonateMatrice()

                        aranjare(a,n);
                        aranjare(b,n);
                        setcolor(15);
                        transpusaMatriceiAfisare(a);
                        getch();
                        break;
                    case 3:
                        setbkcolor(0);
                        citireMatrice(a);
                        coordonateMatrice(a,50,30);

                        coordonateOperatie(op);

                        citireMatrice(b);
                        coordonateMatrice(b, op.x + 100, 30);

                        coordonateEgal(egal);
                        cleardevice();//sterge parantezele puse de coordonateMatrice()

                        aranjare(a,n);
                        aranjare(b,n);

                        setcolor(15);
                        //AFISARE INITIALA
                        afisareMatrice(a,n);

                        settextstyle(1, HORIZ_DIR, 2);
                        strcpy(op.simbol, "x");

                        outtextxy(op.x, op.y, op.simbol); // pun op.simbol
                        afisareMatrice(b,n);
                        settextstyle(1, HORIZ_DIR, 7);
                        outtextxy(egal.x, egal.y, egal.simbol);

                        afisareMatrice(a,n);

                        settextstyle(1, HORIZ_DIR, 7);
                        outtextxy(op.x, op.y, op.simbol);

                        afisareMatrice(b,n);
                        //setbkcolor(0);
                        //apel
                        Inmultire(a,b);
                        break;
                    case 4:
                        setbkcolor(0);
                        citireMatrice(a);
                        coordonateMatrice(a,50,30);

                        coordonateOperatie(op);

                        coordonateEgal(egal);
                        cleardevice();//sterge parantezele puse de coordonateMatrice()

                        aranjare(a,n);
                        setcolor(15);
                        Inversa(a);
                        break;
                    case 5:
                        setbkcolor(0);
                        citireMatrice(a);
                        coordonateMatrice(a,50,30);

                        coordonateOperatie(op);

                        coordonateEgal(egal);
                        cleardevice();//sterge parantezele puse de coordonateMatrice()

                        aranjare(a,n);
                        setcolor(15);
                        determinantMatriceAfisare(a);
                        break;
                    case 6:
                        setbkcolor(0);
                        citireMatrice(a);
                        coordonateMatrice(a,50,30);

                        coordonateOperatie(op);

                        citireMatrice(b);
                        coordonateMatrice(b, op.x + 100, 30);

                        coordonateEgal(egal);
                        cleardevice();//sterge parantezele puse de coordonateMatrice()

                        aranjare(a,n);
                        aranjare(b,n);

                        setcolor(15);
                        operatieLinii(a,n,1,2,"+");
                        break;
                    case 7:
                        setbkcolor(0);
                        citireMatrice(a);
                        coordonateMatrice(a,50,30);

                        coordonateOperatie(op);

                        citireMatrice(b);
                        coordonateMatrice(b, op.x + 100, 30);

                        coordonateEgal(egal);
                        cleardevice();//sterge parantezele puse de coordonateMatrice()

                        aranjare(a,n);
                        aranjare(b,n);

                        setcolor(15);
                        operatieColoane(a,n,1,2,"+");

                        break;
                    case 8:
                        setbkcolor(0);
                        citireMatrice(a);
                        coordonateMatrice(a,50,30);

                        cleardevice();//sterge parantezele puse de coordonateMatrice()

                        aranjare(a,n);

                        setcolor(15);
                        sumaElementelorDeSubDP(a,n);
                        break;
                    }
            }

        }
    }
    while(1);

}


void meniu()
{
    int mijx,mijy;
    char matrice[2][10]={"Matrice","Vectori"};

    readimagefile("pozafundal.jpg",0,0,getmaxx(),getmaxy());
    mijx=getmaxx()/2;
    mijy=getmaxy()/2;
    settextstyle(BOLD_FONT,HORIZ_DIR,9);
    setbkcolor(COLOR(194,205,193));
    setcolor(BLACK);
    setlinestyle(0,0,3);
    for(int i=0; i<2; i++)
    {
        int a=textwidth(matrice[i]);
        int b=textheight(matrice[i]);
        outtextxy(mijx-a/2,getmaxy()/3*(i+1)-10,matrice[i]);
        rectangle(mijx-a/2-3,getmaxy()/3*(i+1)-10,mijx-a/2+a,getmaxy()/3*(i+1)+b-10);
    }

    do
    {
    if(ismouseclick(WM_LBUTTONDOWN))
    {
        int x,y;
        clearmouseclick(WM_LBUTTONDOWN);
        x=mousex();
        y=mousey();
        for(int i=0; i<2; i++)
        {
            int a=textwidth(matrice[i]);
            int b=textheight(matrice[i]);
            if(x>=mijx-a/2 && x<=mijx-a/2+a && y>=getmaxy()/3*(1+i)-10 && y<=getmaxy()/3*(i+1)+b-10)
                switch(i)
            {
            case 0:
                meniuMatrice();
                break;
            case 1:
                meniuVectori();
                break;
            }
        }
    }
    }
   while(1);
}


int main()
{
    int gd=DETECT, gm, left=1000, top=1000, right=2150, bottom=3000, x=300, y=150;
    //initgraph(&gd, &gm, "c:\\TC\\BGI");

    initwindow(1500, 600);


    meniu();

    //citireVector(vector1,n);
    coordonateVector(vector1,30,30);
    //afisareVector(vector1,25);



    //citireVector(vector2,n);
    //coordonateVector(vector2,30,120);
    //afisareVector(vector2,95);

    //adunare(vector1,vector2,vector3);
    //scadere(vector1,vector2,vector3);
     //inmultireCuScalar(vector2,3);



     //sumaElemente(vector1);
     //produsElemente(vector1);
     //produsScalar(vector1,vector2);
     //shiftareLaStanga(vector1);
     //shiftareLaDreapta(vector1);

     //selectionSortCrescator(vector1);
     //selectionSortDescrescator(vector1);
        //bubbleSortCrescator(vector1);
        //bubbleSortDescrescator(vector1);


    getch();
    closegraph();
    f.close();

    int val;
    val=MessageBoxW(0, L" Vrei sa vezi fisierul in care a fost salvat rezultatul?",L"Fisier",MB_YESNO | MB_ICONQUESTION);
    if(val==IDYES)
        system("notepad.exe date.txt");


    return 0;
}


