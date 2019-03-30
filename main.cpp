#include <iostream>
using namespace std;

#include "read.cpp"
#include "impv.cpp"

int main(){
	cout<<"test"<<endl;
	int i, j;
/*
	int** a;
	a = new int*[38];
	for(i=0; i<38; i++)
		a[i]=new int[38];
*/
	int a[38][38];
	int at[19][19];
	int as[19];
	char b[256];  /* d'une lettre vers un petit nombre */
	for(i=0; i<256; i++)
		b[i]=-1;
	for(i=0; i<26; i++)
		b[0x61+i]=(i*17)%26;
	for(i=0; i<7; i++)
		b[0x30+i]=i+26;
	b[0x20]=33;
	b[0x22]=34;
	b[0x27]=35;
	b[0x2c]=36;
	b[0x2e]=37;




/*	int** at;
	at = new int*[19];
	for(i=0; i<19; i++)
		at[i]=new int[19];
*/
	pain(at, as);
	link(a, b);
	cout << "ici" << endl;
	//impv(a,at,as,b);
	int k=0;
	int l;
	for(i=0; i<38; i++){
		for(j=0; j<38; j++){
			k+=a[i][j];
		}
	}
	for(i=0; i<38; i++){
		l=0;
		for(j=0; j<38; j++){
			l+= a[i][j];
		}
		for(j=0; j<128; j++){
			if(b[j]==i){
				cout << (char)j << ":" << 100*((float)l) / (float)k << endl;
				break;
			}
		}
	}
	impv(a,at,as,b);
/*
	for(i=0; i<38; i++)
		delete[] a[i];
		*/
	//delete[] a;
	/*
	for(i=0; i<19; i++)
		delete[] aa[i];
	delete[] aa;
*/



	return 0;





}
