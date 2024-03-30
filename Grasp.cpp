#include <bits/stdc++.h>
#include "util.h"
#include "BuscaLocal.h"
#include "CalculoFO.h"
#include "Solucao_inicial.h"

using namespace std;




void construcao_parcialmente_gulosa(double **fluxo, double **custo, int *s, int n, int *H, int p){

    double gt, alpha = 0.6, gmax, gmin;
    vector<double> soma_fluxos, soma_fluxos_auxiliar, resultado, temp;
    vector<double>::iterator D_it;
    vector<int> LRC, hubs, s_aux, Hubs_indices_corretos;
    vector<int>::iterator it;
    int i, j, random, indice, k = n;

    for(i = 0; i < n; i++)
        s_aux.push_back(s[i]);

    for (i = 0; i < n; i++){
        soma_fluxos.push_back(0);
        for (j = 0; j < n; j++){
            soma_fluxos[i]+= (fluxo[i][j])+(fluxo[j][i]);   // soma das demandas originadas e as demandas destinadas ao nó.
        }
    }
    for (j = 0; j < (int)soma_fluxos.size(); j++)
            temp.push_back(soma_fluxos[j]);


    while(k){
        for (j = 0; j < (int) soma_fluxos.size(); j++)
            soma_fluxos_auxiliar.push_back(soma_fluxos[j]);

        sort(soma_fluxos_auxiliar.begin(), soma_fluxos_auxiliar.end());

        gmax = soma_fluxos_auxiliar.back();
        gmin = soma_fluxos_auxiliar.front();
        gt = gmax - alpha*(gmax - gmin);

        for (i = 0; i < (int) soma_fluxos.size(); i++){
            if(soma_fluxos[i] >= gt){
                LRC.push_back(i);
            }

        }

        random = rand() % LRC.size();
        indice = LRC[random];
        hubs.push_back(indice);
        Hubs_indices_corretos.push_back(find(temp.begin(), temp.end(), soma_fluxos[indice]) - temp.begin());
        D_it = find(soma_fluxos.begin(), soma_fluxos.end(), soma_fluxos[indice]);
        resultado.push_back(soma_fluxos[indice]);
        soma_fluxos.erase(D_it);
        soma_fluxos_auxiliar.clear();
        LRC.clear();
        k--;
    }

    //alocar de acordo com menor distancia ao hub
    for(int i = 0; i < p; i++){
        H[i] = Hubs_indices_corretos[i];
    }

    for (int k = 0; k < n; k++){
		s[k]=k;
	}
    for(int i = 0; i < n; i++){
        if(not_in(H, i, p)){
            s[i] = menor_indice(custo[i], n, H, p);// alocação nó não hub ao hub mais próximo//*min_element(custo[i], custo[i] + n);
        }
	}
}

double GRASP(int *S, int *H, int n, int p, double ****alfaa, double **custo, double **fluxo, int beta, double xi, double alpha, double delta, int GRASPmax){
    int it = 0;
    double Fo = 0, FoAtual = 0;
    int *s, *h;
    s = (int*) calloc(n, sizeof(int));
    h = (int*) calloc(p, sizeof(int));
    if(!s or !h){
        cout << "Erro ao alocar memoria na funcao GRASP\n";
        return -1;
    }
    for(int i = 0; i < n; i++)
        s[i] = S[i];
    for(int i = 0; i < p; i++)
        h[i] = H[i];
    for(int i = 0; i < n; i++)
            cout << S[i] << " ";
        cout << endl;
    while(++it < GRASPmax){
        construcao_parcialmente_gulosa(fluxo, custo, S, n, H, p);
        FoAtual = busca_local(S, H, n, p, alfaa, custo, fluxo, beta, xi, alpha, delta);
        if(FoAtual > Fo){
            for(int i = 0; i < n; i++)
                S[i] = s[i];
            for(int i = 0; i < p; i++)
                H[i] = h[i];
            Fo = FoAtual;
        }
    }
    free(s);
    free(h);
    return Fo;
}
