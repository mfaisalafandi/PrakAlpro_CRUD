#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

struct Mahasiswa {
	char nim[11], nama_lengkap[80], alamat[100], no_hp[15];
	int ipk;
};
struct Mahasiswa Mhs[255];

void explode(char text[100], char data[5][100], char separator){
	int i, firstI = 0, secondI = 0;
	memset(data[0], 0, sizeof(data[0]));
	for(i=0; i<strlen(text); i++)
	{
		if(text[i] == separator)
		{
			firstI += 1; secondI = 0;
			memset(data[firstI], 0, sizeof(data[firstI]));
		}
		else if(text[i] != '\n' || text[i] != '\0')
		{
			data[firstI][secondI] = text[i];
			secondI++;
		}
	}
}

void Menu (int *pilih) {
	system ("cls");
	printf ("=======================================================\n");
	printf ("                  Pemrosesan Data Text\n");
	printf ("=======================================================\n");
	printf ("1. Simpan/Tambah Data\n");
	printf ("2. Lihat Data\n");
	printf ("3. Edit Data\n");
	printf ("4. Delete Data\n");
	printf ("==========================================\n");
	printf ("=> "); scanf ("%d", pilih);
}

void addDataMhs(char *nim, char *nama_lengkap, int *ipk, char *alamat, char *no_hp) {
	char gabung[255] = "", str_ipk[10];
	FILE *fptr = fopen("storage/data_mhs.dat", "a");
	itoa(*ipk, str_ipk, 10);
	strcat(gabung, nim); strcat(gabung, "#"); strcat(gabung, nama_lengkap); strcat(gabung, "#"); strcat(gabung, str_ipk); strcat(gabung, "#"); strcat(gabung, alamat); strcat(gabung, "#"); strcat(gabung, no_hp); strcat(gabung, "\n");
	fputs(gabung, fptr);
	fclose(fptr);
}

void readDataMhs() {
	system("cls");
	printf("Lihat Data \n");
	printf("==================\n\n");
	char buffer[255], data[5][100];
	FILE *fptr = fopen("storage/data_mhs.dat", "r");
	
	int i=0;
	while(fgets(buffer, sizeof(buffer), fptr) != NULL) {
		explode(buffer, data, '#');
		
		printf("%d. NIM : %s | Nama Lengkap : %s \n", ++i, data[0], data[1]);
		printf("\tIPK : %s | Alamat : %s \n", data[2], data[3]);
		printf("\tNo. HP : %s \n\n", data[4]);
	}
	fclose(fptr);
	
	if(i == 0) printf("Data Masih Kosong!!!\n");
}

void editProses(char *nim, char *nama_lengkap, int *ipk, char *alamat, char *no_hp, int baris) {
	char str_ipk[10];
	char buffer[255], data[5][100];
	
	FILE *fptr = fopen("storage/data_mhs.dat", "r");
	int i = 0;
	while(fgets(buffer, sizeof(buffer), fptr) != NULL) {
		explode(buffer, data, '#');
		strcpy(Mhs[i].nim, data[0]);
		strcpy(Mhs[i].nama_lengkap, data[1]);
		Mhs[i].ipk = atoi(data[2]);
		strcpy(Mhs[i].alamat, data[3]);
		strcpy(Mhs[i].no_hp, data[4]);
		i++;
	}
	fclose(fptr);
	
	strcpy(Mhs[baris].nim, nim);
	strcpy(Mhs[baris].nama_lengkap, nama_lengkap);
	Mhs[baris].ipk = *ipk;
	strcpy(Mhs[baris].alamat, alamat);
	strcpy(Mhs[baris].no_hp, no_hp);
	
	fptr = fopen("storage/data_mhs.dat", "w"); fclose(fptr);
	int j;
	fptr = fopen("storage/data_mhs.dat", "a");
	for(j=0; j<i; j++) {
		char gabung[255] = "";
		itoa(Mhs[j].ipk, str_ipk, 10);
		strcat(gabung, Mhs[j].nim); strcat(gabung, "#"); strcat(gabung, Mhs[j].nama_lengkap); strcat(gabung, "#"); strcat(gabung, str_ipk); strcat(gabung, "#"); strcat(gabung, Mhs[j].alamat); strcat(gabung, "#"); strcat(gabung, Mhs[j].no_hp);
		if(baris == j) strcat(gabung, "\n");
		fputs(gabung, fptr);
	}
	fclose(fptr);
}

void editDataMhs() {
	system("cls"); 
	printf("Edit Data \n");
	printf("==================\n\n");
	char nim[10];
	char buffer[255], data[5][100];
	bool isThere = false;
	FILE *fptr = fopen("storage/data_mhs.dat", "r");
	
	printf("Masukkan NIM Mahasiswa yang ingin Diedit : "); scanf("%s", &nim);
	
	int i = 0;
	while(fgets(buffer, sizeof(buffer), fptr) != NULL) {
		explode(buffer, data, '#');
		i++;
		if(strcmp(data[0], nim) == 0) {
			isThere = true;
			break;
		}
	}
	fclose(fptr);
	
	fflush(stdin);
	if(i != 0) {
		char nama_lengkap[80], alamat[100], no_hp[15];
		int ipk;
		
		printf("\nNama Lengkap : "); gets(nama_lengkap); fflush(stdin);
		printf("IPK          : "); scanf("%d", &ipk); fflush(stdin);
		printf("Alamat       : "); gets(alamat); fflush(stdin);
		printf("No. HP       : "); gets(no_hp); fflush(stdin);
		
		editProses(&nim[0], &nama_lengkap[0], &ipk, &alamat[0], &no_hp[0], (i-1));
	} else {
		printf("\nMahasiswa dengan NIM tersebut tidak ditemukan!!!\n");
	}
}

void deleteDataMhs(char nim[10]) {
	char str_ipk[10];
	char buffer[255], data[5][100];
	
	FILE *fptr = fopen("storage/data_mhs.dat", "r");
	int i = 0;
	int baris = -1;
	while(fgets(buffer, sizeof(buffer), fptr) != NULL) {
		explode(buffer, data, '#');
		strcpy(Mhs[i].nim, data[0]);
		strcpy(Mhs[i].nama_lengkap, data[1]);
		Mhs[i].ipk = atoi(data[2]);
		strcpy(Mhs[i].alamat, data[3]);
		strcpy(Mhs[i].no_hp, data[4]);
		if(strcmp(data[0], nim) == 0) {
			baris = i;
		}
		i++;
	}
	fclose(fptr);
	
	if(baris != -1) {
		fptr = fopen("storage/data_mhs.dat", "w"); fclose(fptr);
		int j;
		fptr = fopen("storage/data_mhs.dat", "a");
		for(j=0; j<i; j++) {
			if(baris != j) {
				char gabung[255] = "";
				itoa(Mhs[j].ipk, str_ipk, 10);
				strcat(gabung, Mhs[j].nim); strcat(gabung, "#"); strcat(gabung, Mhs[j].nama_lengkap); strcat(gabung, "#"); strcat(gabung, str_ipk); strcat(gabung, "#"); strcat(gabung, Mhs[j].alamat); strcat(gabung, "#"); strcat(gabung, Mhs[j].no_hp);
				fputs(gabung, fptr);
			}
		}
		fclose(fptr);
	} else printf("\nMahasiswa dengan NIM tersebut tidak ditemukan!!!\n");
}

int main () {
	int pilih;
	char ulang;
	
	do {
		Menu(&pilih);
		if (pilih == 1) {
			FILE *fptr;
			fptr = fopen("storage/data_mhs.dat", "r");
			if(fptr == NULL) {
				printf("File Tidak Tersedia!!!\n");
				fptr = fopen("storage/data_mhs.dat", "w");
				printf("File Sudah Dibuatkan Oleh Sistem \n\n");
			}
			
			char nim[10], nama_lengkap[80], alamat[100], no_hp[15];
			int ipk;
			char buffer[255], data[5][100];
			bool isThere = false;
			
			do {
				isThere = false;
				system("cls");
				printf("Simpan/Tambah Data \n");
				printf("==================\n\n");
				printf("NIM          : "); scanf("%s", nim); fflush(stdin);
				printf("Nama Lengkap : "); gets(nama_lengkap); fflush(stdin);
				printf("IPK          : "); scanf("%d", &ipk); fflush(stdin);
				printf("Alamat       : "); gets(alamat); fflush(stdin);
				printf("No. HP       : "); gets(no_hp); fflush(stdin);
				
				while(fgets(buffer, sizeof(buffer), fptr) != NULL) {
					explode(buffer, data, '#');
					if(strcmp(data[0], nim) == 0) {
						isThere = true;
						printf("\nNIM yang ingin digunakan sudah terpakai!! \n");
						printf("Gunakan NIM lainnya!!!\n\n");
						system("pause");
						system("cls");
					}
				}
				fclose(fptr);
			} while (isThere == true);
			addDataMhs(&nim[0], &nama_lengkap[0], &ipk, &alamat[0], &no_hp[0]);
		}
		else if (pilih == 2) {  
			readDataMhs();
		}
		else if (pilih == 3) {
			editDataMhs();
		}
		else if (pilih == 4) {
			char nim[10];
			printf("\nMasukkan NIM yang ingin Dihapus Datanya : "); scanf("%s", nim);
			deleteDataMhs(nim);
		}
		else {
			printf("\nMenu tidak tersedia!!!\n");
		}
		printf ("\nTekan y untuk kembali ke MENU? "); scanf ("%s", &ulang);
	}
	while (ulang == 'y' || ulang == 'Y');
	
	return 0;
}
