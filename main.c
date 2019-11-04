#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <process.h>


/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void delay(int x)
{
    clock_t start_time = clock();
    while (clock() < start_time + x);

}

struct Goktasi
{
 COORD kord;
};

int sayac=0;
int s1;
int nesneSayisi=0;
COORD c;
int levelDurum;
int toplamNesne=0;

struct Goktasi goktaslari[50];
void duvarlariCiz()
{
    COORD dKonum;


    for(int i = 1;i<=51;i++)
    {
        dKonum.X=19;
        dKonum.Y=i;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),dKonum );
        printf("%c",186);
        dKonum.X=71;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),dKonum );
        printf("%c",186);
    }
}

void goktaslariYerlestir()
{
    system("cls");
    duvarlariCiz();
    for(int i=0;i<nesneSayisi;i++)
    {
        COORD kord=goktaslari[i].kord;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),kord );
        printf("O");
    }
    oyuncuYerlestir();
    oyunBilgisiYerlestir();
}

void oyunBilgisiYerlestir()
{
    COORD kordinasyon;
    kordinasyon.X=130;
    kordinasyon.Y=10;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),kordinasyon);
    printf("Skor\tLevel\tGoktasi Sayisi");
    kordinasyon.Y=12;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),kordinasyon);
    printf("%d\t%d\t%d",toplamNesne,11-levelDurum,nesneSayisi);
}


struct oyunDurumu{
int seviye;
int nthTur;
};

struct oyunDurumu newGame;

void oyunBitti()
{
    system("cls");
    COORD kordinasyon;
    kordinasyon.X=30;
    kordinasyon.Y=10;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),kordinasyon);
    printf("Oyun Bitti. Birazdan Yeniden Yonlendirileceksiniz.");
    delay(5000);
    nesneSayisi=0;
    sayac=0;
    toplamNesne=0;
    baslangic();
}

void goktaslariKordinatDegistir()
{

        for(int i=0;i<nesneSayisi;i++)
        {
            if(goktaslari[i].kord.Y<=50)
            {
                goktaslari[i].kord.Y++;
                if((goktaslari[i].kord.Y==c.Y)&&(goktaslari[i].kord.X==c.X)) oyunBitti();
            }
            else
            {
                nesneSil(i);
            }
        }
}

void nesneSil(int nthObject)
{
    for(int k=nthObject;k<nesneSayisi-1;k++)
    {
        goktaslari[k]=goktaslari[k+1];
    }
    nesneSayisi--;
    toplamNesne++;
}



void oyuncuYerlestir()
{
      SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c );
			printf("%c",127);
}

void baslangic()
{
    system("cls");
    COORD kordinasyon;
    kordinasyon.X=30;
    kordinasyon.Y=10;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),kordinasyon);
    printf("Tum Ogeleri Gorebilmek Icin Tam Ekran Moduna Geciniz");
    kordinasyon.X=30;
    kordinasyon.Y=12;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),kordinasyon);
    printf("Oyun Oynarken Durdurmak veya Devam Etmek Icin Enter Tusunu Kullanabilirsiniz.");
    kordinasyon.X=30;
    kordinasyon.Y=14;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),kordinasyon);
    printf("Baslamak Icin Space Tusuna Basiniz,Cikmak Icin Escape Tusuna Basiniz");
    int karakter=getch();
    switch(karakter)
    {
        case 32:
            newGame.seviye=10;
            s1=9;
            return;
            break;
        case 27:
            exit(0);
            break;
        default:
            baslangic();
            break;
    }
}

void seviyeBul()
{
    int sayi=sayac/100;
    levelDurum=10-sayi;
    newGame.seviye=levelDurum;
}

void yeniGoktasi()
{
    s1++;
    if (sayac<1000) sayac++;
    seviyeBul();
    if ((s1>=newGame.seviye)&&(nesneSayisi<=30))
    {
        int rnd=rand()%50+20;
        goktaslari[nesneSayisi].kord.X=rnd;
        goktaslari[nesneSayisi].kord.Y=1;
        s1=0;
        nesneSayisi++;

    }
}

void Duraklat()
{
    COORD kordinasyon;
    kordinasyon.X=30;
    kordinasyon.Y=14;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),kordinasyon);
    printf("Oyun Duarklatildi");
    kordinasyon.X=30;
    kordinasyon.Y=16;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),kordinasyon);
    printf("Devam Etmek Icin Enter Tusuna Basiniz.");
    int karakter=getch();
    switch(karakter)
    {
        case 13:
            return;
            break;
        default:
      //      baslangic();
            break;
    }

}

int main(int argc, char *argv[]) {
baslangic();
yeniGoktasi();
int a=0;
c.X=40;
c.Y=51;
oyuncuYerlestir();
int tur=0;
	while(1)
	{
	    tur++;
	    if(tur>40)
        {
            yeniGoktasi();
            goktaslariKordinatDegistir();
            goktaslariYerlestir();
            tur=0;
        }

        delay(2);

        if(kbhit())
        {
			a=getch();
			switch(a)
			{
				case 77:
					if(c.X<70) c.X++;
					break;
        /*        case 80:
                    c.Y++;
                    break;*/
                case 75:
                    if (c.X>20)c.X--;
                    break;
         /*       case 72:
                    c.Y--;
                    break;*/
                case 13:
                    Duraklat();
                    break;
                case 27:
                    exit(0);
                    break;
                default:
                    oyuncuYerlestir();
                    break;
			}
        }
	}

	return 0;
}
