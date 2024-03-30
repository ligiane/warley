#include <bits/stdc++.h>
#include "util.h"
#include "Solucao_inicial.h"
#include "CalculoFO.h"


using namespace std;

/*ALGORITMO 1
Troca de alocação
Algoritmo troca de alocacao implentado conforme pseudo codigo feito na sala, utilizando
como referencia o artigo e o pseudo codigo do artigo*/

double troca_de_alocacao(double Fo, int *S, int *H, int n, int p, double ****alfaa, double **custo, double **fluxo, int beta, double xi, double alpha, double delta){

    double f_novo;
    int hub_antigo;
    set<int> hubs;
    set<int>::iterator sit;


    Fo = calculaFO(alfaa, S, fluxo, n);

    //inicializa conjunto de hubs
    for(int i = 0; i < p; i++)
        hubs.insert(H[i]);

//  faz as operacoes de trocas de alocacao na lista s
    for(sit = hubs.begin(); sit != hubs.end(); sit++)
    {
        for(int i = 0; i < n; i++)
        {
        //  verifica se o i atual é hub, caso for, nao realiza a troca de alocacao pois ja é hub
            if(find(hubs.begin(), hubs.end(), i) == hubs.end())
            {
            //  troca a alocacao do no i pelo hub sit (variavel que aponta para lista de hubs) e verifica se ha melhora na FO
            //  caso haja, troca, senao, retorna ao hub antigo.
                hub_antigo = S[i];
                S[i] = *sit;

                f_novo = calculaFO(alfaa, S, fluxo, n);


                if(f_novo > Fo)
                {
                    Fo = f_novo;
                }
                else
                {
                    S[i] = hub_antigo;
                    hub_antigo = -1;
                }
            }
        }
    }

    return Fo;
}


//ALGORITMO 2
//Troca de Hub
// Esta função realiza os movimentos de troca de Hub e de alocacao e checa se há melhora
//da função objetivo
double troca_de_hub(double Fo, int *S, int *H, int n, int p, double ****alfaa, double **custo, double **fluxo, int beta, double xi, double alpha, double delta){

    double f_novo;
    int hub_antigo;
    vector<int> hubs;
    vector<int> nos;
    vector<int>::iterator sit, sit2, vit;

    Fo = calculaFO(alfaa, S, fluxo, n);

    //inicializa vetor hubs
    for(int i = 0; i < p; i++)
        hubs.push_back(H[i]);
    nos.clear();

    //ordena o vetor hubs
    sort(hubs.begin(), hubs.end());

    for(sit = hubs.begin(); sit != hubs.end(); sit++)
    {
        for(int i = 0; i < n; i++)
        {
            if(find(hubs.begin(), hubs.end(), i) == hubs.end())
            {
                hub_antigo = *sit; //hub antigo fica na variavel hub_antigo
                *sit = i;       //hub novo (antigo noh i) fica armazenado em *sit

                //guarda a lista antiga
                for(int g = 0; g < n; g++)
                    nos.push_back(S[g]);
                //realiza as trocas na lista S conforme a troca de hub (troca os valores S[i] correspondentes ao hub trocado pelo hub novo
                for(int j = 0; j < n; j++)
                {
                    if(S[j] == hub_antigo or j == i)
                    {
                        S[j] = i;
                    }
                }

                f_novo = calculaFO(alfaa, S, fluxo, n);
                sit2 = hubs.begin();
                for(int t = 0; t < p; t++)
                {
                    H[t] = *sit2;
                    sit2++;
                }
                //ordena e realiza os movimentos de troca de alocacao no novo hub e verifica se ha melhora da FO
                sort(H, H + p);

                f_novo = troca_de_alocacao(f_novo, S, H, n, p, alfaa, custo, fluxo, beta, xi, alpha, delta);

                //caso nao haja melhora, retorna ´à configuracao antiga
                if(f_novo > Fo)
                {
                    Fo = f_novo;
                }
                else
                {
                    for(int j = 0; j < n; j++)
                    {
                        if(S[j] == i)
                        {
                            S[j] = nos[j];
                        }
                    }

                    *sit = hub_antigo;
                    sit2 = hubs.begin();
                    for(int t = 0; t < p; t++)
                    {
                        H[t] = *sit2;
                        sit2++;
                    }
                }
                sort(H, H + p);


            }
            nos.clear();
        }
    }

	return Fo;
}



