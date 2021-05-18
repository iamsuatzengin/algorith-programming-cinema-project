#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KOLTUK_SAYISI 50
int hasilat = 0; // toplam hasilat

typedef struct{
	int matine; // matine numaralarý -> 1, 2, 3, 4, 5 
	int koltukDurumu; // 0-> bos , 1->dolu
	int fiyat;
}Red, Green, Blue;

typedef enum{
	ogrenci = 0,
	tam = 1
}Ucret;

void menu(Red *red, Green *green, Blue *blue);
void rezervasyonMenu(Red *red, Green *green, Blue *blue);
int ucretTipiSorgusu();
void hasilatBilgileri();
void salonBilgileri(Red *red, Green *green, Blue *blue);
void rezervasyonRed(Red *red);
void rezervasyonGreen(Green *green);
void rezervasyonBlue(Blue *blue);

int girisYap(){
	char kullaniciAdi[20], sifre[20], kullaniciAdiDosya[20], sifreDosya[20];
	printf("\n\t Kullanici Adi: ");
	fflush(stdin);
	scanf("%s", kullaniciAdi);
	printf("\t Sifre: ");
	fflush(stdin);
	scanf("%s", sifre);
	
	FILE *login = fopen("sifre.txt", "r+");
	if(login == NULL){
		FILE *login = fopen("sifre.txt", "w");
		fprintf(login, "%s %s", kullaniciAdi, sifre);
		fclose(login);
		return 1;
	}
	int c;
	while(c != EOF){
		c = fscanf(login, "%s %s", kullaniciAdiDosya, sifreDosya);
		if (c != EOF){
			if(strcmp(kullaniciAdiDosya, kullaniciAdi) == 0 && strcmp(sifreDosya, sifre) == 0){
				return 1;
			}
			else{
				return 0;
			}
		}
	}
}
int main(){
	Red *red;
	Green *green;
	Blue *blue;
	
	red = (Red *)calloc(KOLTUK_SAYISI, sizeof(Red));
	green = (Green *)calloc(KOLTUK_SAYISI, sizeof(Green));
	blue = (Blue *)calloc(KOLTUK_SAYISI, sizeof(Blue));
	while(1){
		int giris = girisYap();
		if(giris){
			printf("\n\t Giris Basarili!\n");
			menu(red, green, blue);	
		}
		else{
			printf("\n\t Kullanici adi veya sifre yanlis!\n\t Tekrar deneyiniz!");
			girisYap();
		}
	}
	return 0;
}

void menu(Red *red, Green *green, Blue *blue){
	printf("\n\t---- SINEMA OTOMASYONU ----\n\n");
	printf("\t(1)-Rezervasyon Yap \n\t(2)-Salon Bilgilerini Goster \n\t(3)-Hasilat Bilgilerini Goster \n\t(0)-Cikis\n\n\tIslem: ");
	int secim;
	while(1){
		scanf("%d", &secim);
		switch(secim){
			case 0:
				printf("\n\tProgramdan cikiliyor..!\n");
				exit(0);
			case 1:
				rezervasyonMenu(red, green, blue);
				break;
			case 2:
				salonBilgileri(red, green, blue);
				break;
			case 3:
				hasilatBilgileri();
				menu(red, green, blue);
				break;
			default:
				printf("\tYanlis Secim!!");
				break;
		}
	}
}
void rezervasyonMenu(Red *red, Green *green, Blue *blue){
	while(1){
		int islem;
		printf("\n\t Lutfen Salon Seciniz");
		printf("\n\t (1)-Red salonu \n\t (2)-Green salonu \n\t (3)-Blue salonu \n\t (4)-Ana Menu \n\t Islem :");
		scanf("%d", &islem);
		if(islem == 1){
			rezervasyonRed(red);
		}
		else if(islem == 2){
			rezervasyonGreen(green);
		}
		else if(islem == 3){
			rezervasyonBlue(blue);
		}
		else if(islem == 4){
			menu(red, green, blue);
		}
		else{
			printf("\n\t Gecersiz islem !");
		}	
	}
}
int ucretTipiSorgusu(){
	int ucretSecim;
	Ucret ucret;
	printf("\n\t Ucret Tipini Seciniz: ");
	printf("\n\t (0)-Ogrenci ucret secimi \n\t (1)-Tam ucret secimi \n\t Islem: ");
	scanf("%d", &ucretSecim);
	if(ucretSecim == 0){
		return ogrenci;
	}
	else {
		return tam;
	}	
}
void hasilatBilgileri(){
	FILE *hasilatDosyasi = fopen("hasilat.txt", "r");
	if(hasilatDosyasi == NULL){
		printf("Dosya okunamadi!!");
		exit(1);
	}
	fscanf(hasilatDosyasi, "%d", &hasilat);
	printf("\n\tTOPLAM HASILAT : %d\n\n", hasilat);
	fclose(hasilatDosyasi);
}
void salonBilgileri(Red *red, Green *green, Blue *blue){
	int i,j;
	int izleyiciToplamRed1 = 0, izleyiciToplamRed2=0, izleyiciToplamRed3=0, izleyiciToplamRed4=0, izleyiciToplamRed5=0;
	int izleyiciToplamGreen1 = 0, izleyiciToplamGreen2=0, izleyiciToplamGreen3=0, izleyiciToplamGreen4=0, izleyiciToplamGreen5=0;
	int izleyiciToplamBlue1 = 0, izleyiciToplamBlue2=0, izleyiciToplamBlue3=0, izleyiciToplamBlue4=0, izleyiciToplamBlue5=0;
	FILE *redFile = fopen("red.txt", "r");
	FILE *greenFile = fopen("green.txt", "r");
	FILE *blueFile = fopen("blue.txt", "r");
	if(redFile == NULL){
		printf("Dosya acilamadi!!");
		exit(1);
	}
	if(greenFile == NULL){
		printf("Dosya acilamadi!!");
		exit(1);
	}
	if(blueFile == NULL){
		printf("Dosya acilamadi!!");
		exit(1);
	}
	
	while(1){
		int salonIslem;
		printf("\n\t Bilgilerini gormek istediginiz salonu seciniz. \n");
		printf("\n\t (1)-Red salonu \n\t (2)-Green salonu \n\t (3)-Blue salonu \n\t (4)-Ana Menu \n\t Islem :");
		scanf("%d", &salonIslem);
		if(salonIslem == 1){
			int matineNum, koltukDurumu, koltukNumara;
			printf("\n\t RED SALONU");
			while(!feof(redFile)){
				fscanf(redFile, "%d %d %d", &matineNum, &koltukNumara, &koltukDurumu);
				if(matineNum == 1){
					izleyiciToplamRed1 += koltukDurumu;	
				}
				else if(matineNum == 2){
					izleyiciToplamRed2 += koltukDurumu;
				} 
				else if(matineNum == 3){
					izleyiciToplamRed3 += koltukDurumu;
				}
				else if(matineNum == 4){
					izleyiciToplamRed4 += koltukDurumu;
				}
				else{
					izleyiciToplamRed5 += koltukDurumu;
				}
			}
			printf("\n\t 1-nolu matinede %d kisi vardir.", izleyiciToplamRed1);
			printf("\n\t 2-nolu matinede %d kisi vardir.", izleyiciToplamRed2);
			printf("\n\t 3-nolu matinede %d kisi vardir.", izleyiciToplamRed3);
			printf("\n\t 4-nolu matinede %d kisi vardir.", izleyiciToplamRed4);
			printf("\n\t 5-nolu matinede %d kisi vardir.\n", izleyiciToplamRed5);
		}
		else if(salonIslem == 2){
			int matineNum, koltukDurumu, koltukNumara;
			printf("\n\t GREEN SALONU");
			while(!feof(greenFile)){
				fscanf(greenFile, "%d %d %d", &matineNum, &koltukNumara, &koltukDurumu);
				if(matineNum == 1){
					izleyiciToplamGreen1 += koltukDurumu;
				}
				else if(matineNum == 2){
					izleyiciToplamGreen2 += koltukDurumu;
				}
				else if(matineNum == 3){
					izleyiciToplamGreen3 += koltukDurumu;
				}
				else if(matineNum == 4){
					izleyiciToplamGreen4 += koltukDurumu;
				}
				else{
					izleyiciToplamGreen5 += koltukDurumu;
				} 
			}
			printf("\n\t 1-nolu matinede %d kisi vardir.", izleyiciToplamGreen1);
			printf("\n\t 2-nolu matinede %d kisi vardir.", izleyiciToplamGreen2);
			printf("\n\t 3-nolu matinede %d kisi vardir.", izleyiciToplamGreen3);
			printf("\n\t 4-nolu matinede %d kisi vardir.", izleyiciToplamGreen4);
			printf("\n\t 5-nolu matinede %d kisi vardir.\n", izleyiciToplamGreen5);
		}
		else if(salonIslem == 3){
			int matineNum, koltukDurumu, koltukNumara;
			printf("\n\t BLUE SALONU");
			while(!feof(blueFile)){
				fscanf(blueFile, "%d %d %d", &matineNum, &koltukNumara, &koltukDurumu);
				if(matineNum == 1){
					izleyiciToplamBlue1 += koltukDurumu;
				}
				else if(matineNum == 2){
					izleyiciToplamBlue2 += koltukDurumu;
				}
				else if(matineNum == 3){
					izleyiciToplamBlue3 += koltukDurumu;
				}
				else if(matineNum == 4){
					izleyiciToplamBlue4 += koltukDurumu;
				}
				else{
					izleyiciToplamBlue5 += koltukDurumu;
				}
			}
			printf("\n\t 1-nolu matinede %d kisi vardir.", izleyiciToplamBlue1);
			printf("\n\t 2-nolu matinede %d kisi vardir.", izleyiciToplamBlue2);
			printf("\n\t 3-nolu matinede %d kisi vardir.", izleyiciToplamBlue3);
			printf("\n\t 4-nolu matinede %d kisi vardir.", izleyiciToplamBlue4);
			printf("\n\t 5-nolu matinede %d kisi vardir.\n", izleyiciToplamBlue5);
		}
		else if(salonIslem == 4){
			menu(red, green, blue);
		}
		else{
			printf("\n\t Gecersiz islem !");
		}	
	}
	fclose(redFile);
	fclose(greenFile);
	fclose(blueFile);
}

void rezervasyonRed(Red *red){
	FILE *redFile = fopen("red.txt", "a");
	if(redFile == NULL){
		printf("Dosya acilamadi!");
		exit(1);
	}

	int i, matineSecim, koltukNum;
	printf("\n\t Matine Seciniz (1, 2, 3, 4, 5) :");
	scanf("%d", &matineSecim);
	int rezUcret = ucretTipiSorgusu();
	
	for(i=0;i<KOLTUK_SAYISI;i++){
		if(red[i].koltukDurumu != 0){
			continue;
		}
		else{
			red[i].koltukDurumu = 1;
			koltukNum = i+1;
			red[i].matine = matineSecim;
			if(rezUcret == ogrenci){
				red[i].fiyat = 20;
				hasilat += red[i].fiyat;
			}
			else{ // tam ucret
				red[i].fiyat = 30;
				hasilat += red[i].fiyat;
			}
			break;
		}
	}
	printf("\n\t Koltuk numarasi: %d \n\t Matine: %d \n\t Ucret: %d \n\t",koltukNum, red[koltukNum-1].matine, red[koltukNum-1].fiyat);
	fprintf(redFile, "%d %d %d\n", red[koltukNum-1].matine, koltukNum, red[koltukNum-1].koltukDurumu);
	FILE *hasilatDosyasi = fopen("hasilat.txt", "w+");
	fprintf(hasilatDosyasi, "%d", hasilat);
	
	fclose(hasilatDosyasi);
	fclose(redFile);
}
void rezervasyonGreen(Green *green){
	FILE *greenFile = fopen("green.txt", "a");
	if(greenFile == NULL){
		printf("Dosya acilamadi!");
		exit(1);
	}
	
	int i, matineSecim, koltukNum;
	printf("\n\t Matine Seciniz (1, 2, 3, 4, 5) :");
	scanf("%d", &matineSecim);
	int rezUcret = ucretTipiSorgusu();
	
	for(i=0;i<KOLTUK_SAYISI;i++){
		if(green[i].koltukDurumu != 0){
			continue;
		}
		else{
			green[i].koltukDurumu = 1;
			koltukNum = i+1;
			green[i].matine = matineSecim;
			if(rezUcret == ogrenci){
				green[i].fiyat = 20;
				hasilat += green[i].fiyat;
			}
			else{ // tam ucret
				green[i].fiyat = 30;
				hasilat += green[i].fiyat;
			}
			break;
		}
	}
	printf("\n\t Koltuk numarasi: %d \n\t Matine: %d \n\t Ucret: %d \n\t",koltukNum, green[koltukNum-1].matine, green[koltukNum-1].fiyat);
	fprintf(greenFile, "%d %d %d\n", green[koltukNum-1].matine, koltukNum, green[koltukNum-1].koltukDurumu);
	FILE *hasilatDosyasi = fopen("hasilat.txt", "w+");
	fprintf(hasilatDosyasi, "%d", hasilat);
	
	fclose(hasilatDosyasi);
	fclose(greenFile);
}
void rezervasyonBlue(Blue *blue){
	FILE *blueFile = fopen("blue.txt", "a");
	if(blueFile == NULL){
		printf("Dosya acilamadi!");
		exit(1);
	}
	
	int i, matineSecim, koltukNum;
	printf("\n\t Matine Seciniz (1, 2, 3, 4, 5) :");
	scanf("%d", &matineSecim);
	int rezUcret = ucretTipiSorgusu();
	
	for(i=0;i<KOLTUK_SAYISI;i++){
		if(blue[i].koltukDurumu != 0){
			continue;
		}
		else{
			blue[i].koltukDurumu = 1;
			koltukNum = i+1;
			blue[i].matine = matineSecim;
			if(rezUcret == ogrenci){
				blue[i].fiyat = 20;
				hasilat += blue[i].fiyat;
			}
			else{ // tam ucret
				blue[i].fiyat = 30;
				hasilat += blue[i].fiyat;
			}
			break;
		}
	}
	printf("\n\t Koltuk numarasi: %d \n\t Matine: %d \n\t Ucret: %d \n\t",koltukNum, blue[koltukNum-1].matine, blue[koltukNum-1].fiyat);
	fprintf(blueFile, "%d %d %d\n", blue[koltukNum-1].matine, koltukNum, blue[koltukNum-1].koltukDurumu);
	FILE *hasilatDosyasi = fopen("hasilat.txt", "w+");
	fprintf(hasilatDosyasi, "%d", hasilat);
	
	fclose(hasilatDosyasi);
	fclose(blueFile);
}

