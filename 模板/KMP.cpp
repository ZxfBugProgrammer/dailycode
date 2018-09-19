#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring> 

using namespace std;

void Get_fail(char *P, int *f){
	int m = strlen(P);
	f[0] = 0; f[1] = 0;
	for(int i=1; i<m; i++){
		int j = f[i];
		while(j && P[i] != P[j]) j=f[j];
		f[i+1] = (P[i] == P[j] ? j + 1 : 0);
	}
}

int KMP(char *P,char *T,int *f){
	int n = strlen(T), m = strlen(P);
	Get_fail(P,f);
	int j = 0;
	for(int i = 0; i < n; i++){
		while(j && P[j] != T[i]) j=f[j];
		if(P[j] == T[i]) j++;
		if(j == m)
			return i - m + 1;	
	}
	return -1;
}

int main(){
	char P[1000], T[1000];
	int f[1000];
	cin >> P >> T;
	cout << KMP(P,T,f) << endl;
	return 0;
}
