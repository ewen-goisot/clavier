#include <fstream>
#include <iostream>
#include <fstream>
using namespace std;


void link(int a[38][38], char* b){
	int i, j;
	char c, d, cc;
	for(i=0; i<38; i++)
		for(j=0; j<38; j++)
			a[i][j] = 0;
	ifstream f("data/text.txt", ios::in);
	if(f){
		f.get(cc);
		cc=b[(unsigned char)cc];
		f.get(c);
		c=b[(unsigned char)c];
		if(false){
			// c==-1
			f.get(c);
			c=b[(unsigned char)c];
			cout << "impossible";
		}
		while(f.get(d)){
			d=b[(unsigned char)d];
			if(d==-1){
				cout << "\n\e[031mNT:" << (int)d << "\e[0m" << " ";
				//break;
			}
			if(cc>=0 && cc<38 && d>=0 && d<38)
				++a[cc][d]; /* trigramme troue */
			else
				cout << "ccx" << cc << ":"<< d << " ";
			if(c>=0 && c<38 && d>=0 && d<38)
				a[c][d] += 4;
			else
				cout << "cx" << c << ":"<< d << " ";
			cc=c;
			c=d;
		}
		f.close();
	}
	for(i=0; i<38; i++){
		cout << endl;
		for(c=0; c<128; c++)
			if(b[c]==i){
				cout << c << ":";
				break;
			}
		for(j=0; j<38; j++)
			cout << a[i][j] << " ";
	}

}
void pain(int at[19][19], int as[19]){
	int i, j;
	ifstream f("data/pain.txt", ios::in);  // on ouvre en lecture
	if(f){
		for(i=0; i<19; i++){
			cout << endl;
			for(j=0; j<19; j++){
				if(j%6==0 && j<18)
					cout << endl;
				else
					cout << "\t";
				f >> at[i][j];
				cout << at[i][j];
			}
		}
		for(i=0; i<19; i++)
			f >> as[i];
		f.close();
	}else{
		cout << "fichier inexistant" << endl;
		for(i=0; i<19; i++)
			for(j=0; j<19; j++)
				at[i][j] = 0;
		for(i=0; i<19; i++)
			as[i]=0;
	}
}
