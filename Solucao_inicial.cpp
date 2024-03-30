#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include<iostream>
#include<conio.h>
#include <limits.h>
#include <bits/stdc++.h>
#include "util.h"
#include "Movimentos.h"
#include "Solucao_inicial.h"

using namespace std;

/* Constroi a solucao inicial de forma gulosa (escolhe os hubs conforme maior fluxo de entrada e saida)
n = tamanho da lista S
p = tamanho da lista H
S = lista de nos alocados
H = lista de hubs ativos
fluxo = matriz de fluxo da instancia
custo = matriz de custos da instancia
*/
void construcao_gulosa(int n, int p, int *s, int *H, double **fluxo, double **custo){
  	double v[n];

  	//inicializa os vetores v e s
	for (int k = 0; k < n; k++){
		v[k]=0;
		s[k]=k;
	}
	//calcula os fluxos dos nos
  	for (int i = 0; i<n; i++){
    	for (int j = 0; j<n; j++){
    		v[i]=v[i]+(fluxo[i][j])+(fluxo[j][i]);   // soma das demandas originadas e as demandas destinadas ao nó.
    	}
  	}
    for(int i = 0; i < n; i++)
        cout << v[i] << " ";
    cout << endl;

  	cria_vetor_h(v, n, p, H);      // p nós com maior fluxo

  	//aloca conforme menor distancia
	for(int i = 0; i < n; i++){
        if(not_in(H, i, p))
            s[i] = menor_indice(custo[i], n, H, p);// alocação nó não hub ao hub mais próximo//*min_element(custo[i], custo[i] + n);

	}
	for(int i = 0; i < n; i++)
        cout << s[i] << " ";
    cout << endl;
    for(int i = 0; i < p; i++)
        cout << H[i]<< " ";
}

