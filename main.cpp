#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <conio.h>
#include <limits.h>
#include <time.h>
#include "util.h"
#include "Movimentos.h"
#include "Solucao_inicial.h"
#include "BuscaLocal.h"
#include "CalculoFO.h"
#include "Grasp.h"

#include <fstream>
#include <vector>


using namespace std;

#define inf 10e10 /// Parametro usado para representar um numero suficientemente grande


int main(int argc, char* argv[]) {
	try {
		/**============================
		 *  Leitura dos dados
		 *=============================== */
		ifstream arq("5.3");
		if (!arq.is_open()) {
			cout << "Error openning file: " << "10.3" << endl;
			arq.close();
			exit(EXIT_FAILURE);
		}
		clock_t inicio_CPU,       // clock no inicio da aplicacao do metodo
	            fim_CPU;
	    inicio_CPU = clock();
		int n; // Quantidade de nós
		int p; // Quantidade de hubs a serem ativados
		int GRASPmax = 30;
		int **lambda;
		double tempo, fotimo;
		double xi, alpha, delta;
		double beta = 25095; //parametro retirado do artigo
		double **custo;
		double **fluxo;
		double ****alfaa;
		arq >> n;
		double codx[n];
		double cody[n];
		for (int i=0; i<n; i++){
			arq >> codx[i];
			arq >> cody[i];
		}

		//cria matrizes e vetores que serao usados
		custo = cria_matriz_double(n, n); //cria a matriz de custos
		fluxo = cria_matriz_double(n, n); //cria a matriz de fluxo
        alfaa = cria_matriz_4D__double(n, n, n, n); //cria a matriz 4D de cobertura
        lambda = cria_matriz_int(n, n); //cria a matriz de lambda

		for (int i = 0; i < n; i++){ //Coletar custos AP
	  		for (int j = 0; j < n; j++){
	    		custo[i][j] = 0.001 * sqrt((codx[i] - codx[j]) * (codx[i] - codx[j])  + (cody[i] - cody[j]) * (cody[i] - cody[j]));
	  			cout << custo[i][j] <<  " ";
			  }
			  cout << endl;
		}
		cout << endl;
		for (int i = 0; i <  n; i++){ //Coletar demanda AP
	  		for (int j = 0; j < n; j++){
	    		arq >> fluxo[i][j];
	    		cout << fluxo[i][j] <<  " ";
	  		}
	  		cout << endl;
		}
		cout << endl;
		//coleta numero de hubs
		arq >> p;

		//coleta as taxas de transferencia chi, alfa e delta
		arq >> xi;
		arq >> alpha;
		arq >> delta;

        //cria os vetores S e H que representarão a solução
		int *s, *h;
		s = cria_vetor(n);
		h = cria_vetor(p);

        //aloca gulosamente a solucao inicial
		construcao_gulosa(n, p, s, h, fluxo, custo);

        //cria a matriz de cobertura
        cria_matriz_a_4(n, xi, alpha, delta, beta, lambda, custo, alfaa);

        //calcula valor de funcao objetivo antes da heuristica, imprime e usa a metaheuristica GRASP
		fotimo = calculaFO(alfaa, s, fluxo, n);
		cout << "Antes dos movimentos: " << fotimo << endl;
		fotimo = GRASP(s, h, n, p, alfaa, custo, fluxo, beta, xi, alpha, delta, GRASPmax);
		cout << "Depois dos movimentos: " << fotimo << endl;

		//imprime a solucao final encontrada
		for(int i = 0; i < n; i++)
            cout << s[i] << " ";
        cout << endl;

		fotimo = 0;
		fim_CPU = clock();
		tempo=double(fim_CPU - inicio_CPU)/(CLOCKS_PER_SEC);
		//printf("\n %10.6f %10.4f", fotimo, double(fim_CPU - inicio_CPU)/(CLOCKS_PER_SEC));
	}
	catch(int erro) {
		cerr << "Error: " << endl;
	}
	return 0;
}

