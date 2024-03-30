
#include <bits/stdc++.h>
#include "util.h"
#include "CalculoFO.h"

using namespace std;

double calculaFO(double ****alfaa, int *s, double **fluxo, int n){

	int **z;
	double Total = 0;

	z = cria_matriz_int(n, n);
	cria_matriz_z(z, alfaa, s, n);



	for (int i = 0; i < n; i++)
	{
        for (int j = 0; j < n; j++)
        {
            Total+= fluxo[i][j] * z[i][j];
        }
    }
	return Total;
}


