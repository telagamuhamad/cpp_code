#include <iostream>
#include <stdlib.h>
using namespace std;


/* Definisi Type Data */
typedef struct{
	char data;
	int quanta;
} Infotype;
typedef struct tElmtlist *address;
typedef struct tElmtlist { 
	Infotype info;
	address next;
} ElmtList;
typedef struct {
	address First;
} List;

/* Definisi list : */
/* List kosong : First(L) = Nil dan Last(L) = Nil */
/* Setiap elemen dengan address P dapat diacu Info(P), Next(P), Prev(P) */
/* Elemen terakhir list: Last(L) */

/* Notasi Akses */
#define Info(P) (P)->info
#define Quanta(P) (P)->info.quanta
#define Data(P) (P)->info.data
#define Next(P) (P)->next
#define First(L) ((L).First)

#define Nil NULL

bool IsEmpty (List L)
/* Mengirim true jika list kosong. Lihat definisi di atas. */
{
	return (First(L)==Nil);
}

/****************** PEMBUATAN LIST KOSONG ******************/
void CreateEmpty (List *L)
/* I.S. L sembarang  */
/* F.S. Terbentuk list kosong. Lihat definisi di atas. */
{
	First(*L) = Nil;
}

/****************** Manajemen Memori ******************/
address alokasi (Infotype X)
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil. */
/* Misalnya: menghasilkan P, maka Info(P)=X, Next(P)=Nil, Prev(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil. */
{
	address P;
	P = (address) malloc(sizeof(ElmtList));
	if(P==NULL){
		return Nil;
	}else{
		Info(P) = X;
		Next(P) = Nil;
		return P;
	}
}
void Dealokasi (address P)
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */
{
	free(P);
}
address getLast(List L){

	address P = Next(First(L));
	while(Next(P)!=First(L)){
		P = Next(P);
	}
	return P;
}

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void InsVFirst (List *L, Infotype X)
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
{
	address P = alokasi(X);
	address Q = First(*L);
	if(P!=NULL){
		if(First(*L)==Nil){
			First(*L) = P;
			Next(P) = P;
		}
		else{
			address last = getLast(*L);
			Next(P) = First(*L);
			First(*L) = P;
			Next(last) = First(*L);
		}
	}
}
void SortedInsert(List *L, Infotype x){
	address P = alokasi(x);
	if(P!=NULL){
		if(IsEmpty(*L)){
			InsVFirst(&(*L),x);
		}
		else{
			if((int)Data(P) <= (int) Data(First(*L))){
				InsVFirst(&(*L),x);
			}
			else{
				address Q = Next(First(*L));
				address last = getLast(*L);
				address prevQ = First(*L);
				while(Q!=Next(last)){
					if((int)Data(P)<=(int)Data(Q)){
						break;
					}
					Q = Next(Q);
					prevQ = Next(prevQ);
				}
				Next(prevQ) = P;
				Next(P) = Q;
			}
		}
	}
}
void InsertFirst (List *L, address P)
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
{
	address Q = First(*L);
	if(P!=NULL){
		if(First(*L)==Nil){
			First(*L) = P;
			Next(P) = P;
		}
		else{
			address last = getLast(*L);
			Next(P) = First(*L);
			First(*L) = P;
			Next(last) = First(*L);
		}
	}
}
void InsVLast(List *L, Infotype X){
	address P = alokasi(X);
	if(P!=NULL){
		if(IsEmpty(*L)){
			InsVFirst(&(*L),X);
		}
		else{
			address last = getLast(*L);
			Next(last) = P;
			Next(P) = First(*L);
		}
	}
}
void InsertLast(List *L, address P){
	if(P!=NULL){
		if(IsEmpty(*L)){
			InsertFirst(&(*L),P);
		}
		else{
			address last = getLast(*L);
			Next(last) = P;
			Next(P) = First(*L);
		}
	}
}
void InsVAfter (List * L, address here, address newnode){
	if(newnode!=NULL){
		Next(newnode) = Next(here);
		Next(here) = newnode;
	}
} 
void DelVFirst(List *L, Infotype *X){
	address P = First(*L);
	address Q = First(*L);
	*X = Info(P);
	if(Next(P)==P){
		First(*L)=Nil;
		Dealokasi(Q);
	}
	else{
		address last = getLast(*L);
		First(*L) = Next(P);
		Next(last) = First(*L);
		Dealokasi(Q);
	}
}
void DeleteFirst(List *L, address *P){
	*P = First(*L);
	address Q = First(*L);
	if(Next(*P)==*P){
		First(*L)=Nil;
		Dealokasi(Q);
	}
	else{
		address last = getLast(*L);
		First(*L) = Next(*P);
		Next(last) = First(*L);
		Dealokasi(Q);
	}
}
void DelVLast(List *L, Infotype *X){
	address P = First(*L);
	address Q = First(*L);
	if(Next(P)==P){
		First(*L)=Nil;
	}
	else{
		while(Next(Next(Q))!=First(*L)){
			Q=Next(Q);
		}
		P = Next(Q);
		Next(Q) = First(*L);
	}	
	*X = Info(P);
	Dealokasi(P);
}
void DeleteLast(List *L, address *P){
	*P=First(*L);
	address Q = First(*L);
	if(Next(*P)==*P){
		First(*L)=Nil;
	}
	else{
		while(Next(Next(Q))!=First(*L)){
			Q=Next(Q);
		}
		*P = Next(Q);
		Next(Q) = First(*L);
	}	
	Dealokasi(*P);
}
void DeleteAfter (List *L, address *Pdel, address Prec)
/* I.S. List tidak kosong. Prec adalah anggota list  */
/* F.S. Menghapus Next(Prec): */
/*      Pdel adalah alamat elemen list yang dihapus  */
{
	*Pdel = Next(Prec);
	Next(Prec) = Next(*Pdel);
}
void DelP (List *L, address del)
/* I.S. Sembarang */
/* F.S. Jika ada elemen list beraddress P, dengan Info(P)=X  */
/* Maka P dihapus dari list dan di-dealokasi */
/* Jika tidak ada elemen list dengan Info(P)=X, maka list tetap */
/* List mungkin menjadi kosong karena penghapusan */
{	
	address P = del, Q = First(*L);
	if(P!=Nil){
		// searching element before P
		while(Next(Q)!=P && Q!=P){
			Q = Next(Q);
		}
		if(Q==P){
			DeleteFirst(&(*L),&P);
		}else{
			DeleteAfter(&(*L),&P,Q);
		}
		Dealokasi(P);
	}
}
int nbElmt(List L){
	address last = getLast(L);
	address P = First(L);
	int i=0;
	while(P!=last){
		i++;
		P = Next(P);
	}
	return i+1;
}
bool search(List L, address P){
	bool find=false;
	address last = getLast(L);
	address first = First(L);
	while(first!=last){
		if(P==first){
			find = true;
			break;
		}
		first = Next(first);
	}
	return find;
}