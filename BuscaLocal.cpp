#include <bits/stdc++.h>
#include "BuscaLocal.h"
#include "Movimentos.h"
#include "CalculoFO.h"

using namespace std;
//ALGORITMO 3
//Busca local
double busca_local(int *S, int *H, int n, int p, double ****alfaa, double **custo, double **fluxo, int beta, double xi, double alpha, double delta){
	double Fo, FoAtual;
	int max_iter = 2;
	Fo = 0;
	//realiza os movimentos de troca de hub e troca de alocacao buscando um otimo local
	while(--max_iter){
		FoAtual = troca_de_hub(Fo, S, H, n, p, alfaa, custo, fluxo, beta, xi, alpha, delta);
		if(FoAtual > Fo){
            Fo = FoAtual;
		}
	}
	return Fo;
}
