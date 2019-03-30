#include "impv.hpp"

int valu(int a[][38], int at[][19]){
	int i, j;
	int b=0;
	for(i=0; i<19; i++){
		for(j=0; j<19; j++){
			b += a[i][j]*at[i][j] + a[i+19][j+19]*at[i][j];
		}
	}
	return 8*b;
}

int mono_valu(int *p, int *as){
	int i;
	int b=0;
	for(i=0; i<19; i++){
		b += p[i]*as[i] + p[i+19]*as[i];
	}
	return 1*b;
}

int comp(int a[][38], int au[][38], int at[][19], int g, int *h){
	int b=0;
	int i, j, ii, jj, kk, k;
	for(i=0; i<38; i++){
		for(j=0; j<g; j++){
			/* TODO trace d'une matrice: gain tps */
			k = h[j];
			if(k/19 == i/19){
				ii = i%19;
				kk = k%19;
				b += at[ii][kk]*(au[i][k]-a[i][k]);
				b += at[kk][ii]*(au[k][i]-a[k][i]);
			}
		}
	}
	for(i=0; i<g; i++){
		for(j=0; j<g; j++){
			/* tiers exclu */
			ii = h[i];
			jj = h[j];
			if(ii/19==jj/19)
				b -= at[ii%19][jj%19]*(au[ii][jj]-a[ii][jj]);
		}
	}
	return 8*b;
}

int mono_comp(int *p, int *pu, int *as, int g, int *h){
	int b=0;
	int i;
	for(i=0; i<g; i++){
		b += (pu[h[i]]-p[h[i]]) * as[h[i]%19] ;
		//cout <<"comp"<<h[i]<<":"<<i<<endl;
	}
	return 1*b;
}

void copy(int a[][38], int au[][38], int *o, int *ou, int *p, int *pu){
	int i, j;
	for(i=0; i<38; i++){
		for(j=0; j<38; j++)
			au[i][j] = a[i][j];
		ou[i] = o[i];
		pu[i] = p[i];
	}
}

void prmu(int au[38][38], int *o, int *pu, int c, int d){
	if(c==d)
		return;
	int i, j;
	for(i=0; i<38; i++){
		j=au[i][c];
		au[i][c]=au[i][d];
		au[i][d]=j;
	}
	for(i=0; i<38; i++){
		j=au[c][i];
		au[c][i]=au[d][i];
		au[d][i]=j;
	}
	j=o[c];
	o[c]=o[d];
	o[d]=j;
	j=pu[c];
	pu[c]=pu[d];
	pu[d]=j;
}

void scla(char *b, int *o){
	int i;
	char j;
	for(i=0; i<38; i++){
		for(j=0; j<126; j++){
			if(b[j]==o[i]){
				cout << j;
				break;
			}
		}
		if(i<18){
			if(i==5  || i==11){
				cout << endl;
			}else{
				cout << " ";
			}
		}else if(i==18){
			cout << "\n\n";
		}else{
			if(i==24 || i==30){
				cout << endl;
			}else{
				cout << " ";
			}
		}
	}
	cout << endl;

}
int impv(int a[][38], int at[][19], int *as, char *bbb){
	int au[38][38], auu[38][38];  /* copie */ //{{{
	int o[38];  /* ordre */
	int ou[38], ouu[38];
	int p[38];  /* fréquence par touche */
	int pu[38], puu[38];
	int i, j, k, l; /* boucles diverses */
	int va, vb, vc, vd, ve, vf, vg, vh, vi, vj; /* permutations */
	int lettres=0; /* nb total de lettres */
	for(i=0; i<38; i++){
		o[i]=i;
		p[i]=0;
		for(j=0; j<38; j++)
			p[i] += (a[i][j]+a[j][i])/2;
		lettres += p[i];
		cout << p[i] << endl;
		/* TODO créer p aint */
		/* TODO retourner p ou o */
	}
	int b=valu(a,at) + mono_valu(p,as);
	int bu, buu, bp; /* coût auxiliaire */
	int g;
	int h[8];
	int ameliore;
	int randpool[238];
	copy(a,au,o,ou,p,pu);
	srand (time(NULL));
	for(k=0; k<230; k++){
		randpool[k] = k%30;
	}
	//}}}
	for(k=0; k<100; k++){ //{{{
		va=rand()%38;
		vb=rand()%38;
		vc=rand()%38;
		vd=rand()%38;
		ve=rand()%38;
		vf=rand()%38;
		vg=rand()%38;
		vh=rand()%38;
		vi=rand()%38;
		vj=rand()%38;
		prmu(au,ou,pu,va,vb);
		prmu(au,ou,pu,vb,vc);
		prmu(au,ou,pu,vc,vd);
		prmu(au,ou,pu,vd,ve);
		prmu(au,ou,pu,ve,vf);
		prmu(au,ou,pu,vf,vg);
		prmu(au,ou,pu,vg,vh);
		prmu(au,ou,pu,vh,vi);
		prmu(au,ou,pu,vi,vj);
		if (k<100 || valu(au,at)+mono_valu(pu,as) < b) {
			prmu(a,o,p,va,vb);
			prmu(a,o,p,vb,vc);
			prmu(a,o,p,vc,vd);
			prmu(a,o,p,vd,ve);
			prmu(a,o,p,ve,vf);
			prmu(a,o,p,vf,vg);
			prmu(a,o,p,vg,vh);
			prmu(a,o,p,vh,vi);
			prmu(a,o,p,vi,vj);
			b = valu(au,at)+mono_valu(pu,as);
			cout << "rand" << b << endl;
		}else{
			prmu(au,ou,pu,vi,vj);
			prmu(au,ou,pu,vh,vi);
			prmu(au,ou,pu,vg,vh);
			prmu(au,ou,pu,vf,vg);
			prmu(au,ou,pu,ve,vf);
			prmu(au,ou,pu,vd,ve);
			prmu(au,ou,pu,vc,vd);
			prmu(au,ou,pu,vb,vc);
			prmu(au,ou,pu,va,vb);
		}
		va=rand()%38;
		vb=rand()%38;
		vc=rand()%38;
		vd=rand()%38;
		ve=rand()%38;
		vf=rand()%38;
		vg=rand()%38;
		vh=rand()%38;
		prmu(au,ou,pu,va,vb);
		prmu(au,ou,pu,vb,vc);
		prmu(au,ou,pu,vd,ve);
		prmu(au,ou,pu,ve,vf);
		prmu(au,ou,pu,vf,vg);
		prmu(au,ou,pu,vg,vh);
		if (k<100 || valu(au,at)+mono_valu(pu,as) < b) {
			prmu(a,o,p,va,vb);
			prmu(a,o,p,vb,vc);
			prmu(a,o,p,vd,ve);
			prmu(a,o,p,ve,vf);
			prmu(a,o,p,vf,vg);
			prmu(a,o,p,vg,vh);
			b = valu(au,at)+mono_valu(pu,as);
			cout << "rand" << b << endl;
		}else{
			prmu(au,ou,pu,vg,vh);
			prmu(au,ou,pu,vf,vg);
			prmu(au,ou,pu,ve,vf);
			prmu(au,ou,pu,vd,ve);
			prmu(au,ou,pu,vb,vc);
			prmu(au,ou,pu,va,vb);
		}
		va=rand()%38;
		vb=rand()%38;
		vc=rand()%38;
		vd=rand()%38;
		ve=rand()%38;
		vf=rand()%38;
		prmu(au,ou,pu,va,vb);
		prmu(au,ou,pu,vc,vd);
		prmu(au,ou,pu,ve,vf);
		if (k<121 || valu(au,at)+mono_valu(pu,as) < b) {
			prmu(a,o,p,va,vb);
			prmu(a,o,p,vc,vd);
			prmu(a,o,p,ve,vf);
			b = valu(au,at)+mono_valu(pu,as);
			cout << "rand" << b << endl;
		}else{
			prmu(au,ou,pu,ve,vf);
			prmu(au,ou,pu,vc,vd);
			prmu(au,ou,pu,va,vb);
		}
	} //}}}


	do{
		bp=b;
		if(true){ cout << "\e[0mMODE RAPIDE" << endl; //{{{

			g=2;
			for(va=0; va<38; va++){
				h[0]=va;
				for(vb=va; vb<38; vb++){
					if(va==vb)
						continue;
					h[1]=vb;
					prmu(au,ou,pu,va,vb);
					bu = comp(a,au,at,g,h) + mono_comp(p,pu,as,g,h);
					//if(bu!=valu(au,at)+mono_valu(pu,as)-valu(a,at)-mono_valu(p,as))
						//cout<<"bug"<<endl;
					if(bu<0){
						prmu(a,o,p,va,vb);
						b = valu(a,at) + mono_valu(p,as);
						cout << b << "->" << bu;
						cout << " e:" << va << "/" << vb << endl;
					}else{
						prmu(au,ou,pu,va,vb);
					}
				}
			}
		}
		for(va=0; va<38; va++){
			for(vb=0; vb<38; vb++){
				if(a[va][vb]!=au[va][vb])
					cout << "gros bug" << endl;
			}
		} //}}}
		if(false){ cout << "\e[034mMODE RANDOM" << endl; //{{{
			for(k=0; k<200000; k++){
				va=rand()%38;
				vb=rand()%38;
				vc=rand()%38;
				vd=rand()%38;
				ve=rand()%38;
				vf=rand()%38;
				vg=rand()%38;
				vh=rand()%38;
				vi=rand()%38;
				vj=rand()%38;
				prmu(au,ou,pu,va,vb);
				prmu(au,ou,pu,vb,vc);
				prmu(au,ou,pu,vc,vd);
				prmu(au,ou,pu,vd,ve);
				prmu(au,ou,pu,ve,vf);
				prmu(au,ou,pu,vf,vg);
				prmu(au,ou,pu,vg,vh);
				prmu(au,ou,pu,vh,vi);
				prmu(au,ou,pu,vi,vj);
				if (valu(au,at)+mono_valu(pu,as) < b) {
					prmu(a,o,p,va,vb);
					prmu(a,o,p,vb,vc);
					prmu(a,o,p,vc,vd);
					prmu(a,o,p,vd,ve);
					prmu(a,o,p,ve,vf);
					prmu(a,o,p,vf,vg);
					prmu(a,o,p,vg,vh);
					prmu(a,o,p,vh,vi);
					prmu(a,o,p,vi,vj);
					b = valu(au,at)+mono_valu(pu,as);
					cout << "rand" << b << endl;
				}else{
					prmu(au,ou,pu,vi,vj);
					prmu(au,ou,pu,vh,vi);
					prmu(au,ou,pu,vg,vh);
					prmu(au,ou,pu,vf,vg);
					prmu(au,ou,pu,ve,vf);
					prmu(au,ou,pu,vd,ve);
					prmu(au,ou,pu,vc,vd);
					prmu(au,ou,pu,vb,vc);
					prmu(au,ou,pu,va,vb);
				}
				va=rand()%38;
				vb=rand()%38;
				vc=rand()%38;
				vd=rand()%38;
				ve=rand()%38;
				vf=rand()%38;
				vg=rand()%38;
				vh=rand()%38;
				prmu(au,ou,pu,va,vb);
				prmu(au,ou,pu,vb,vc);
				prmu(au,ou,pu,vd,ve);
				prmu(au,ou,pu,ve,vf);
				prmu(au,ou,pu,vf,vg);
				prmu(au,ou,pu,vg,vh);
				if (valu(au,at)+mono_valu(pu,as) < b) {
					prmu(a,o,p,va,vb);
					prmu(a,o,p,vb,vc);
					prmu(a,o,p,vd,ve);
					prmu(a,o,p,ve,vf);
					prmu(a,o,p,vf,vg);
					prmu(a,o,p,vg,vh);
					b = valu(au,at)+mono_valu(pu,as);
					cout << "rand" << b << endl;
				}else{
					prmu(au,ou,pu,vg,vh);
					prmu(au,ou,pu,vf,vg);
					prmu(au,ou,pu,ve,vf);
					prmu(au,ou,pu,vd,ve);
					prmu(au,ou,pu,vb,vc);
					prmu(au,ou,pu,va,vb);
				}
				va=rand()%38;
				vb=rand()%38;
				vc=rand()%38;
				vd=rand()%38;
				ve=rand()%38;
				vf=rand()%38;
				prmu(au,ou,pu,va,vb);
				prmu(au,ou,pu,vc,vd);
				prmu(au,ou,pu,ve,vf);
				if (valu(au,at)+mono_valu(pu,as) < b) {
					prmu(a,o,p,va,vb);
					prmu(a,o,p,vc,vd);
					prmu(a,o,p,ve,vf);
					b = valu(au,at)+mono_valu(pu,as);
					cout << "rand" << b << endl;
				}else{
					prmu(au,ou,pu,ve,vf);
					prmu(au,ou,pu,vc,vd);
					prmu(au,ou,pu,va,vb);
				}
			} //}}}
		}
		if(false){ cout << "\e[033mMODE MOYEN" << endl; //{{{
			g=3;
			for(va=0; va<38; va++){
				h[0]=va;
				for(vb=va+1; vb<38; vb++){
					h[1]=vb;
					for(vc=va+1; vc<38; vc++){
						if(vc==vb)
							continue;
						h[2]=vc;
						prmu(au,ou,pu,va,vb);
						prmu(au,ou,pu,vb,vc);
						bu = comp(a,au,at,g,h) + mono_comp(p,pu,as,g,h);
						//if(bu!=valu(au,at)+mono_valu(pu,as)-valu(a,at)-mono_valu(p,as))
							//cout<<"bug"<<endl;
						if(bu<0){
							prmu(a,o,p,va,vb);
							prmu(a,o,p,vb,vc);
							for(ve=0; ve<38; ve++){
								for(vf=0; vf<38; vf++){
									if(a[ve][vf]!=au[ve][vf])
										cout << "bug"<<ve<<vf<<endl;
								}
							}
							b = valu(a,at)+mono_valu(p,as);
							cout << b << "->" << bu;
							cout <<" e:"<<va<<"/"<<vb<<"/"<<vc<< endl;
						}else{
							prmu(au,ou,pu,vb,vc);
							prmu(au,ou,pu,va,vb);
						}
					}
				}
			}
		}
		for(va=0; va<38; va++){
			for(vb=0; vb<38; vb++){
				if(a[va][vb]!=au[va][vb])
					cout << "gros bug" << endl;
			}
		} //}}}
		if(false){ cout << "\e[031mMODE LENT" << endl; //{{{
			g=4;
			for(va=0; va<38; va++){
				h[0]=va;
				for(vb=va+1; vb<38; vb++){
					h[1]=vb;
					for(vc=va+1; vc<38; vc++){
						if(vc==vb)
							continue;
						h[2]=vc;
						for(vd=va+1; vd<38; vd++){
							if(vd==vb || vd==vc)
								continue;
							h[3]=vd;
							prmu(au,ou,pu,va,vb);
							prmu(au,ou,pu,vb,vc);
							prmu(au,ou,pu,vc,vd);
							bu = comp(a,au,at,g,h) + mono_comp(p,pu,as,g,h);
							//if(bu!=valu(au,at)+mono_valu(pu,as)-valu(a,at)-mono_valu(p,as))
								//cout<<"bug"<<endl;
							if(bu<0){
								prmu(a,o,p,va,vb);
								prmu(a,o,p,vb,vc);
								prmu(a,o,p,vc,vd);
								for(ve=0; ve<38; ve++){
									for(vf=0; vf<38; vf++){
										if(a[ve][vf]!=au[ve][vf])
											cout << "bug"<<ve<<vf<<endl;
									}
								}
								b = valu(a,at) + mono_valu(p,as);
								cout << "+:" << b << "->" << bu << " e:" << va << "/" << vb << "/" << vc << "/" << vd << endl;
							}else{
								prmu(au,ou,pu,vc,vd);
								prmu(au,ou,pu,vb,vc);
								prmu(au,ou,pu,va,vb);
							}
						}
					}
				}
			}
		}
		for(va=0; va<38; va++){
			for(vb=0; vb<38; vb++){
				if(a[va][vb]!=au[va][vb])
					cout << "gros bug" << endl;
			}
		} //}}}
		if(false){ cout << "\e[035mMODE LENT bis" << endl; //{{{
			g=4;
			for(va=0; va<38; va++){
				h[0]=va;
				for(vb=va+1; vb<38; vb++){
					h[1]=vb;
					for(vc=va+1; vc<38; vc++){
						if(vc==vb)
							continue;
						h[2]=vc;
						for(vd=va+1; vd<38; vd++){
							if(vd==vb || vd==vc)
								continue;
							h[3]=vd;
							prmu(au,ou,pu,va,vb);
							prmu(au,ou,pu,vc,vd);
							bu = comp(a,au,at,g,h) + mono_comp(p,pu,as,g,h);
							//if(bu!=valu(au,at)+mono_valu(pu,as)-valu(a,at)-mono_valu(p,as))
								//cout<<"bug"<<endl;
							if(bu<0){
								prmu(a,o,p,va,vb);
								prmu(a,o,p,vc,vd);
								b = valu(a,at) + mono_valu(p,as);
								cout << "+:" << b << "->" << bu << " e:" << va << "/" << vb << "/" << vc << "/" << vd << endl;
							}else{
								prmu(au,ou,pu,vc,vd);
								prmu(au,ou,pu,va,vb);
							}
						}
					}
				}
			}
		}
		for(va=0; va<38; va++){
			for(vb=0; vb<38; vb++){
				if(a[va][vb]!=au[va][vb])
					cout << "gros bug" << endl;
			}
		} //}}}
		if(b==bp){ cout << "\e[034mMODE RANDOM bis" << endl; //{{{
			 /* random + corrections */

			for(k=0; k<2000; k++){
				copy(a,auu,o,ouu,p,puu);
				j = randpool[k%230];
				for(i=0; i<=j; i++){
					va=rand()%38;
					vb=rand()%38;
					prmu(auu,ouu,puu,va,vb);
				}
				buu = valu(auu,at) + mono_valu(puu,as);

				copy(auu,au,ouu,ou,puu,pu);
				g=2;
				do{
					ameliore = 0;
					for(va=0; va<38; va++){ /* mode rapide x2000 */
						h[0]=va;
						for(vb=va+1; vb<38; vb++){
							h[1]=vb;
							prmu(au,ou,pu,va,vb);
							bu = comp(auu,au,at,g,h) + mono_comp(puu,pu,as,g,h);
							if(bu<0){
								ameliore++;
								prmu(auu,ouu,puu,va,vb);
								buu = valu(auu,at) + mono_valu(puu,as);
							}else{
								prmu(au,ou,pu,va,vb);
							}
						}
					}
				}while(ameliore>15);
				if(buu<b){
					do{
						ameliore = 0;
						for(va=0; va<38; va++){ /* mode rapide x2000 */
							h[0]=va;
							for(vb=va+1; vb<38; vb++){
								h[1]=vb;
								prmu(au,ou,pu,va,vb);
								bu = comp(auu,au,at,g,h) + mono_comp(puu,pu,as,g,h);
								if(bu<0){
									ameliore++;
									prmu(auu,ouu,puu,va,vb);
									buu = valu(auu,at) + mono_valu(puu,as);
								}else{
									prmu(au,ou,pu,va,vb);
								}
							}
						}
					}while(ameliore>0);
					copy(auu,a,ouu,o,puu,p);
					cout << "~/"<<b<<"/"<<buu<<"/~ ("<<j<<")" << endl;
					//scla(bbb,o);
					b = buu;
					for(i=0; i<30; i++){
						l = rand()%200; /* laisser les 30 derniers = au moins 1 de chaque */
						if(randpool[l] == j)
							randpool[rand()%200] = rand()%30; /* pas de monopole */
						else
							randpool[l] = j;
					}
				}
			}
		}
		copy(a,au,o,ou,p,pu);
		scla(bbb,o);
//}}}

		if(false){ cout << "\e[032mMODE META" << endl; //{{{
			g=6;
			 /* 8
				* 6 2
				* 5 3
				* 4 4
				* 4 2 2
				* 3 3 2
				* 2 2 2 2
				*
				* */
			for(va=0; va<38; va++){
				if(p[va]*90<lettres)
					continue;
				h[0]=va;
				cout << va << endl;
				for(vb=va+1; vb<38; vb++){
					if(p[vb]*90<lettres)
						continue;
					h[1]=vb;
					for(vc=va+1; vc<38; vc++){
						if(p[vc]*90<lettres || vb==vc)
							continue;
						h[2]=vc;
						for(vd=va+1; vd<38; vd++){
							if(p[vd]*90<lettres || vb==vd || vc==vd)
								continue;
							h[3]=vd;
							for(ve=va+1; ve<38; ve++){
								if(p[ve]*90<lettres || vb==ve || vc==ve || vd==ve)
									continue;
								h[4]=ve;
								for(vf=va+1; vf<38; vf++){
									if(p[vf]*90<lettres || vb==vf || vc==vf || vd==vf || ve==vf)
										continue;
									h[5]=vf;
									prmu(au,ou,pu,va,vb);
									prmu(au,ou,pu,vb,vc);
									prmu(au,ou,pu,vc,vd);
									prmu(au,ou,pu,vd,ve);
									prmu(au,ou,pu,ve,vf);
									bu = comp(a,au,at,g,h) + mono_comp(p,pu,as,g,h);
									if(bu<0){
										// permuter a
										prmu(a,o,p,va,vb);
										prmu(a,o,p,vb,vc);
										prmu(a,o,p,vc,vd);
										prmu(a,o,p,vd,ve);
										prmu(a,o,p,ve,vf);
										b = valu(a,at) + mono_valu(p,as);
										cout <<"a:"<<b<<"->"<<bu<<" e:"<<va<<"/"<<vb<<"/"<<vc<<"/"<<vd<<"/"<<ve<<"/"<<vf<<endl;
									}else{
										// depermuter au
										prmu(au,ou,pu,ve,vf);
										prmu(au,ou,pu,vd,ve);
										prmu(au,ou,pu,ve,vf);
										bu = comp(a,au,at,g,h) + mono_comp(p,pu,as,g,h);
										if(bu<0){
											// permuter a
											prmu(a,o,p,va,vb);
											prmu(a,o,p,vb,vc);
											prmu(a,o,p,vc,vd);
											prmu(a,o,p,ve,vf);
											b = valu(a,at) + mono_valu(p,as);
											cout <<"b:"<<b<<"->"<<bu<<" e:"<<va<<"/"<<vb<<"/"<<vc<<"/"<<vd<<"/"<<ve<<"/"<<vf<<endl;
										}else{
											// depermuter au
											prmu(au,ou,pu,ve,vf);
											prmu(au,ou,pu,vc,vd);
											prmu(au,ou,pu,vd,ve);
											prmu(au,ou,pu,ve,vf);
											bu = comp(a,au,at,g,h) + mono_comp(p,pu,as,g,h);
											if(bu<0){
												// permuter a
												prmu(a,o,p,va,vb);
												prmu(a,o,p,vb,vc);
												prmu(a,o,p,vd,ve);
												prmu(a,o,p,ve,vf);
												b = valu(a,at) + mono_valu(p,as);
												cout <<"d:"<<b<<"->"<<bu<<" e:"<<va<<"/"<<vb<<"/"<<vc<<"/"<<vd<<"/"<<ve<<"/"<<vf<<endl;
											}else{
												// depermuter au
												prmu(au,ou,pu,ve,vf);
												prmu(au,ou,pu,vd,ve);
												prmu(au,ou,pu,vb,vc);
												prmu(au,ou,pu,vc,vd);
												prmu(au,ou,pu,ve,vf);
												bu = comp(a,au,at,g,h) + mono_comp(p,pu,as,g,h);
												if(bu<0){
													// permuter a
													prmu(a,o,p,va,vb);
													prmu(a,o,p,vc,vd);
													prmu(a,o,p,ve,vf);
													b = valu(a,at) + mono_valu(p,as);
													cout <<"c:"<<b<<"->"<<bu<<" e:"<<va<<"/"<<vb<<"/"<<vc<<"/"<<vd<<"/"<<ve<<"/"<<vf<<endl;
												}else{
													// depermuter au
													prmu(au,ou,pu,ve,vf);
													prmu(au,ou,pu,vc,vd);
													prmu(au,ou,pu,va,vb);
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		for(va=0; va<38; va++){
			for(vb=0; vb<38; vb++){
				if(a[va][vb]!=au[va][vb])
					cout << "gros bug" << endl;
			}
		} //}}}

		if(false){ cout << "\e[035mMODE TRES LENT bis" << endl; //{{{
			g=5;
			for(va=0; va<38; va++){
				h[0]=va;
				cout << va << endl;
				for(vb=va+1; vb<38; vb++){
					h[1]=vb;
					for(vc=va+1; vc<38; vc++){
						if(vc==vb)
							continue;
						h[2]=vc;
						for(vd=va+1; vd<38; vd++){
							if(vd==vb || vd==vc)
								continue;
							h[3]=vd;
							for(ve=va+1; ve<38; ve++){
								if(ve==vb || ve==vc || ve==vd)
									continue;
								h[4]=ve;
								prmu(au,ou,pu,va,vb);
								prmu(au,ou,pu,vb,vc);
								prmu(au,ou,pu,vd,ve);
								bu = comp(a,au,at,g,h) + mono_comp(p,pu,as,g,h);
								//if(bu!=valu(au,at)+mono_valu(pu,as)-valu(a,at)-mono_valu(p,as))
									//cout<<"bug"<<endl;
								if(bu<0){
									prmu(a,o,p,va,vb);
									prmu(a,o,p,vb,vc);
									prmu(a,o,p,vd,ve);
									b = valu(a,at) + mono_valu(p,as);
									cout << "+:" << b << "->" << bu << " e:" << va << "/" << vb << "/" << vc << "/" << vd << endl;
								}else{
									prmu(au,ou,pu,vd,ve);
									prmu(au,ou,pu,vb,vc);
									prmu(au,ou,pu,va,vb);
								}
							}
						}
					}
				}
			}
		}
		for(va=0; va<38; va++){
			for(vb=0; vb<38; vb++){
				if(a[va][vb]!=au[va][vb])
					cout << "gros bug" << endl;
			}
		} //}}}

		if(false){ cout << "\e[031mMODE TRES LENT" << endl; //{{{
			g=5;
			for(va=0; va<38; va++){
				h[0]=va;
				cout << va << endl;
				for(vb=va+1; vb<38; vb++){
					h[1]=vb;
					for(vc=va+1; vc<38; vc++){
						if(vc==vb)
							continue;
						h[2]=vc;
						for(vd=va+1; vd<38; vd++){
							if(vd==vb || vd==vc)
								continue;
							h[3]=vd;
							for(ve=va+1; ve<38; ve++){
								if(ve==vb || ve==vc || ve==vd)
									continue;
								h[4]=ve;
								prmu(au,ou,pu,va,vb);
								prmu(au,ou,pu,vb,vc);
								prmu(au,ou,pu,vc,vd);
								prmu(au,ou,pu,vd,ve);
								bu = comp(a,au,at,g,h) + mono_comp(p,pu,as,g,h);
								//if(bu!=valu(au,at)+mono_valu(pu,as)-valu(a,at)-mono_valu(p,as))
								//cout<<"bug"<<endl;
								if(bu<0){
									prmu(a,o,p,va,vb);
									prmu(a,o,p,vb,vc);
									prmu(a,o,p,vc,vd);
									prmu(a,o,p,vd,ve);
									b = valu(a,at) + mono_valu(p,as);
									cout << "+:" << b << "->" << bu << " e:" << va << "/" << vb << "/" << vc << "/" << vd << endl;
								}else{
									prmu(au,ou,pu,vd,ve);
									prmu(au,ou,pu,vc,vd);
									prmu(au,ou,pu,vd,ve);
									bu = comp(a,au,at,g,h) + mono_comp(p,pu,as,g,h);
									//if(bu!=valu(au,at)+mono_valu(pu,as)-valu(a,at)-mono_valu(p,as))
									//cout<<"bug"<<endl;
									if(bu<0){
										prmu(a,o,p,va,vb);
										prmu(a,o,p,vb,vc);
										prmu(a,o,p,vd,ve);
										b = valu(a,at) + mono_valu(p,as);
										cout << "+:" << b << "->" << bu << " e:" << va << "/" << vb << "/" << vc << "/" << vd << endl;
									}else{
										prmu(au,ou,pu,vd,ve);
										prmu(au,ou,pu,vb,vc);
										prmu(au,ou,pu,va,vb);
									}
								}
							}
						}
					}
				}
			}
		}
		for(va=0; va<38; va++){
			for(vb=0; vb<38; vb++){
				if(a[va][vb]!=au[va][vb])
					cout << "gros bug" << endl;
			}
		}
		//}}}

		if(false){
			g=6;
			scla(bbb,o);
			cout << "\e[032mMODE META LENT" << endl;
			 /* 8
				* 6 2
				* 5 3
				* 4 4
				* 4 2 2
				* 3 3 2
				* 2 2 2 2
				*
				* */
			for(va=0; va<38; va++){
				if(p[va]*150<lettres)
					continue;
				h[0]=va;
				cout << va << endl;
				for(vb=va+1; vb<38; vb++){
					if(p[vb]*150<lettres)
						continue;
					h[1]=vb;
					for(vc=va+1; vc<38; vc++){
						if(p[vc]*150<lettres || vb==vc)
							continue;
						h[2]=vc;
						for(vd=va+1; vd<38; vd++){
							if(p[vd]*150<lettres || vb==vd || vc==vd)
								continue;
							h[3]=vd;
							for(ve=va+1; ve<38; ve++){
								if(p[ve]*150<lettres || vb==ve || vc==ve || vd==ve)
									continue;
								h[4]=ve;
								for(vf=va+1; vf<38; vf++){
									if(p[vf]*150<lettres || vb==vf || vc==vf || vd==vf || ve==vf)
										continue;
									h[5]=vf;
									prmu(au,ou,pu,va,vb);
									prmu(au,ou,pu,vb,vc);
									prmu(au,ou,pu,vc,vd);
									prmu(au,ou,pu,vd,ve);
									prmu(au,ou,pu,ve,vf);
									bu = comp(a,au,at,g,h) + mono_comp(p,pu,as,g,h);
									if(bu<0){
										// permuter a
										prmu(a,o,p,va,vb);
										prmu(a,o,p,vb,vc);
										prmu(a,o,p,vc,vd);
										prmu(a,o,p,vd,ve);
										prmu(a,o,p,ve,vf);
										b = valu(a,at) + mono_valu(p,as);
										cout <<"a:"<<b<<"->"<<bu<<" e:"<<va<<"/"<<vb<<"/"<<vc<<"/"<<vd<<"/"<<ve<<"/"<<vf<<endl;
									}else{
										// depermuter au
										prmu(au,ou,pu,ve,vf);
										prmu(au,ou,pu,vd,ve);
										prmu(au,ou,pu,ve,vf);
										bu = comp(a,au,at,g,h) + mono_comp(p,pu,as,g,h);
										if(bu<0){
											// permuter a
											prmu(a,o,p,va,vb);
											prmu(a,o,p,vb,vc);
											prmu(a,o,p,vc,vd);
											prmu(a,o,p,ve,vf);
											b = valu(a,at) + mono_valu(p,as);
											cout <<"b:"<<b<<"->"<<bu<<" e:"<<va<<"/"<<vb<<"/"<<vc<<"/"<<vd<<"/"<<ve<<"/"<<vf<<endl;
										}else{
											// depermuter au
											prmu(au,ou,pu,ve,vf);
											prmu(au,ou,pu,vc,vd);
											prmu(au,ou,pu,vd,ve);
											prmu(au,ou,pu,ve,vf);
											bu = comp(a,au,at,g,h) + mono_comp(p,pu,as,g,h);
											if(bu<0){
												// permuter a
												prmu(a,o,p,va,vb);
												prmu(a,o,p,vb,vc);
												prmu(a,o,p,vd,ve);
												prmu(a,o,p,ve,vf);
												b = valu(a,at) + mono_valu(p,as);
												cout <<"d:"<<b<<"->"<<bu<<" e:"<<va<<"/"<<vb<<"/"<<vc<<"/"<<vd<<"/"<<ve<<"/"<<vf<<endl;
											}else{
												// depermuter au
												prmu(au,ou,pu,ve,vf);
												prmu(au,ou,pu,vd,ve);
												prmu(au,ou,pu,vb,vc);
												prmu(au,ou,pu,vc,vd);
												prmu(au,ou,pu,ve,vf);
												bu = comp(a,au,at,g,h) + mono_comp(p,pu,as,g,h);
												if(bu<0){
													// permuter a
													prmu(a,o,p,va,vb);
													prmu(a,o,p,vc,vd);
													prmu(a,o,p,ve,vf);
													b = valu(a,at) + mono_valu(p,as);
													cout <<"c:"<<b<<"->"<<bu<<" e:"<<va<<"/"<<vb<<"/"<<vc<<"/"<<vd<<"/"<<ve<<"/"<<vf<<endl;
												}else{
													// depermuter au
													prmu(au,ou,pu,ve,vf);
													prmu(au,ou,pu,vc,vd);
													prmu(au,ou,pu,va,vb);
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		for(va=0; va<38; va++){
			for(vb=0; vb<38; vb++){
				if(a[va][vb]!=au[va][vb])
					cout << "gros bug" << endl;
			}
		}

		if(false){
			g=8;
			scla(bbb,o);
			cout << "\e[036mMODE SUPER META" << endl;
			 /* 8
				* 6 2
				* 5 3
				* 4 4
				* 4 2 2
				* 3 3 2
				* 2 2 2 2
				*
				* */
			for(va=0; va<38; va++){
				if(p[va]*30<lettres)
					continue;
				h[0]=va;
				cout << va << endl;
				for(vb=va+1; vb<38; vb++){
					if(p[vb]*30<lettres)
						continue;
					h[1]=vb;
					for(vc=va+1; vc<38; vc++){
						if(p[vc]*30<lettres || vb==vc)
							continue;
						h[2]=vc;
						for(vd=va+1; vd<38; vd++){
							if(p[vd]*30<lettres || vb==vd || vc==vd)
								continue;
							h[3]=vd;
							for(ve=va+1; ve<38; ve++){
								if(p[ve]*30<lettres || vb==ve || vc==ve || vd==ve)
									continue;
								h[4]=ve;
								for(vf=va+1; vf<38; vf++){
									if(p[vf]*30<lettres || vb==vf || vc==vf || vd==vf || ve==vf)
										continue;
									h[5]=vf;
									for(vg=va+1; vg<38; vg++){
										if(p[vg]*30<lettres || vb==vg || vc==vg || vd==vg || ve==vg || vf==vg)
											continue;
										h[6]=vg;
										for(vh=va+1; vh<38; vh++){
											if(p[vh]*30<lettres || vb==vh || vc==vh || vd==vh || ve==vh || vf==vh || vg==vh)
												continue;
											h[7]=vh;
											prmu(au,ou,pu,va,vb);
											prmu(au,ou,pu,vb,vc);
											prmu(au,ou,pu,vc,vd);
											prmu(au,ou,pu,vd,ve);
											prmu(au,ou,pu,ve,vf);
											prmu(au,ou,pu,vf,vg);
											prmu(au,ou,pu,vg,vh);
											bu = comp(a,au,at,g,h) + mono_comp(p,pu,as,g,h);
											if(bu<0){
												// permuter a
												prmu(a,o,p,va,vb);
												prmu(a,o,p,vb,vc);
												prmu(a,o,p,vc,vd);
												prmu(a,o,p,vd,ve);
												prmu(a,o,p,ve,vf);
												prmu(a,o,p,vf,vg);
												prmu(a,o,p,vg,vh);
												b = valu(a,at) + mono_valu(p,as);
												cout << "a:" << b << "->" << bu << " e:" << va << "/" << vb << "/" << vc << "/" << vd << endl;
											}else{
												// depermuter au
												 /* je concatene plusieurs operations pour gagner du temps
													* TODO verifier que c'est optimal ouou trouver une meilleure version */
												prmu(au,ou,pu,vg,vh);
												prmu(au,ou,pu,vf,vg);
												prmu(au,ou,pu,vg,vh);
												bu = comp(a,au,at,g,h) + mono_comp(p,pu,as,g,h);
												if(bu<0){
													// permuter a
													prmu(a,o,p,va,vb);
													prmu(a,o,p,vb,vc);
													prmu(a,o,p,vc,vd);
													prmu(a,o,p,vd,ve);
													prmu(a,o,p,ve,vf);
													prmu(a,o,p,vg,vh);
													b = valu(a,at) + mono_valu(p,as);
													cout << "b:" << b << "->" << bu << " e:" << va << "/" << vb << "/" << vc << "/" << vd << endl;
												}else{
													// depermuter au
													prmu(au,ou,pu,vg,vh);
													prmu(au,ou,pu,ve,vf);
													prmu(au,ou,pu,vf,vg);
													prmu(au,ou,pu,vg,vh);
													bu = comp(a,au,at,g,h) + mono_comp(p,pu,as,g,h);
													if(bu<0){
														// permuter a
														prmu(a,o,p,va,vb);
														prmu(a,o,p,vb,vc);
														prmu(a,o,p,vc,vd);
														prmu(a,o,p,vd,ve);
														prmu(a,o,p,vf,vg);
														prmu(a,o,p,vg,vh);
														b = valu(a,at) + mono_valu(p,as);
														cout << "c:" << b << "->" << bu << " e:" << va << "/" << vb << "/" << vc << "/" << vd << endl;
													}else{
														// depermuter au
														prmu(au,ou,pu,vg,vh);
														prmu(au,ou,pu,vf,vg);
														prmu(au,ou,pu,vd,ve);
														prmu(au,ou,pu,ve,vf);
														prmu(au,ou,pu,vf,vg);
														prmu(au,ou,pu,vg,vh);
														bu = comp(a,au,at,g,h) + mono_comp(p,pu,as,g,h);
														if(bu<0){
															// permuter a
															prmu(a,o,p,va,vb);
															prmu(a,o,p,vb,vc);
															prmu(a,o,p,vc,vd);
															prmu(a,o,p,ve,vf);
															prmu(a,o,p,vf,vg);
															prmu(a,o,p,vg,vh);
															b = valu(a,at) + mono_valu(p,as);
															cout << "d:" << b << "->" << bu << " e:" << va << "/" << vb << "/" << vc << "/" << vd << endl;
														}else{
															// depermuter au
															prmu(au,ou,pu,vg,vh);
															prmu(au,ou,pu,vf,vg);
															prmu(au,ou,pu,vg,vh);
															bu = comp(a,au,at,g,h) + mono_comp(p,pu,as,g,h);
															if(bu<0){
																// permuter a
																prmu(a,o,p,va,vb);
																prmu(a,o,p,vb,vc);
																prmu(a,o,p,vc,vd);
																prmu(a,o,p,ve,vf);
																prmu(a,o,p,vg,vh);
																b = valu(a,at) + mono_valu(p,as);
																cout << "e:" << b << "->" << bu << " e:" << va << "/" << vb << "/" << vc << "/" << vd << endl;
															}else{
																// depermuter au
																prmu(au,ou,pu,vg,vh);
																prmu(au,ou,pu,ve,vf);
																prmu(au,ou,pu,vc,vd);
																prmu(au,ou,pu,vb,vc);
																//debut
																prmu(au,ou,pu,vc,vd);
																prmu(au,ou,pu,ve,vf);
																prmu(au,ou,pu,vg,vh);
																bu = comp(a,au,at,g,h) + mono_comp(p,pu,as,g,h);
																if(bu<0){
																	// permuter a
																	prmu(a,o,p,va,vb);
																	prmu(a,o,p,vc,vd);
																	prmu(a,o,p,ve,vf);
																	prmu(a,o,p,vg,vh);
																	b = valu(a,at) + mono_valu(p,as);
																	cout << "e:" << b << "->" << bu << " e:" << va << "/" << vb << "/" << vc << "/" << vd << endl;
																}else{
																	// depermuter au
																	prmu(au,ou,pu,vg,vh);
																	prmu(au,ou,pu,ve,vf);
																	prmu(au,ou,pu,vd,ve);
																	prmu(au,ou,pu,vf,vg);
																	prmu(au,ou,pu,vg,vh);
																	bu = comp(a,au,at,g,h) + mono_comp(p,pu,as,g,h);
																	if(bu<0){
																		// permuter a
																		prmu(a,o,p,va,vb);
																		prmu(a,o,p,vc,vd);
																		prmu(a,o,p,vd,ve);
																		prmu(a,o,p,vf,vg);
																		prmu(a,o,p,vg,vh);
																		b = valu(a,at) + mono_valu(p,as);
																		cout << "e:" << b << "->" << bu << " e:" << va << "/" << vb << "/" << vc << "/" << vd << endl;
																	}else{
																		prmu(au,ou,pu,vg,vh);
																		prmu(au,ou,pu,vf,vg);
																		prmu(au,ou,pu,vd,ve);
																		prmu(au,ou,pu,vc,vd);
																		prmu(au,ou,pu,va,vb);
																		// depermuter au
																	}
																}
																//fin
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}while(b<bp);
	scla(bbb,o);
	for(i=0; i<200; i++)
		cout << " "<<i<<":"<<randpool[i]<<endl;
	return 0;
}
