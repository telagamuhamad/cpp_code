#include <iostream>
#include "Master.cpp"
#include <iomanip>
using namespace std;

void printInfo(List L){
	cout << endl;
	cout << "Data   >>" << endl;
	cout << endl;
	cout << "+-----------+-----------+" << endl;
	cout << "| Data      |    Quanta |" << endl;
	cout << "+-----------+-----------+" << endl;
	address Q = First(L);
	if(Q!=Nil){
		while(Next(Q)!=First(L)){
			cout << "| " << Data(Q) << setw(10) << "|" << setw(10) <<  Quanta(Q) << " |" << endl;
			Q = Next(Q);
		}
		cout << "| " << Data(Q) <<  setw(10)<< "|" << setw(10) <<  Quanta(Q) << " |" << endl;
	}
	cout << "+-----------+-----------+" << endl;
}
void InputData(List *L, int N){
	Infotype info;
	for(int i=0; i<N; i++){
		cout << "Simpul  #" << i+1 << endl;
		cout << "Data    #" << i+1 << " : "; cin >> info.data;
		cout << "Quanta  #" << i+1 << " : "; cin >> info.quanta;
		SortedInsert(&(*L),info);
		cout << endl;
	}
}
void ProsesData(List *L, int QProses){
	cout << endl;
	cout << "Proses  >>" << endl;
	cout << endl;
	cout << "+-----------+-----------+" << endl;
	cout << "| Data      |   Quantum |" << endl;
	cout << "+-----------+-----------+" << endl;
	bool stop=false;
	address Q = First(*L);
	int total=0;
	int i=1;
	while(stop!=true){
		Quanta(Q) = Quanta(Q)-QProses;
		if(Quanta(Q)<=0){
			cout << "| " << Data(Q) << setw(10) << "|" << setw(10) <<  QProses << " |" << " >> " << Data(Q) << " = " << Quanta(Q);
			cout << ". Dispose " << Data(Q) << endl;
			DelP(&(*L),Q);
		}
		else{
			cout << "| " << Data(Q) << setw(10) << "|" << setw(10) <<  QProses << " |" << " >> " << Data(Q) << " = " << Quanta(Q) << endl;
		}
		if(IsEmpty(*L)){
				total = total + QProses;
				stop=true;
		}
		else{
			cout << "| " << "Switch" << setw(5) << "|" << setw(10) <<  i << " |" << endl;
			total = total + QProses + i;
			Q = Next(Q);
		}
	}
	cout << "+-----------+-----------+" << endl;
	cout << "| " << "Total" << "     |" << setw(10) <<  total << " |" << endl;
	cout << "+-----------+-----------+" << endl;
}
int main(){
	List L;
	CreateEmpty(&L);
	int N;
	int Qproses;
	cout << "Jumlah Data        : "; cin >> N;
	cout << "Quantum per proses : "; cin >> Qproses;
	cout << endl;
	InputData(&L,N);
	printInfo(L);
	ProsesData(&L,Qproses);
	return 0;
}