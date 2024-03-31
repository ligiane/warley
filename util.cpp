#include<bits/stdc++.h>
#include "util.h"

using namespace std;

void embaralha_vetor(int *vetor, int n)
{
  int aux, j1, j2;
  srand((unsigned) time(NULL));
  for (int i=0; i < n; i++){
    j1 = rand() % (n);
    j2 = rand() % (n);
    while (j1 == j2) j2 = rand() % (n);
    aux = vetor[j1];
    vetor[j1] = vetor[j2];
    vetor[j2] = aux;
  }
}

int **cria_matriz_int(int nlinhas, int ncolunas)
{
  register int i;
  int **matriz;

  matriz = (int **) malloc(nlinhas*sizeof(int *));
  if (!matriz) {
        printf("Falta memoria para alocar a matriz de ponteiros\n");
        exit(1);
  }
  for (i=0; i < nlinhas; i++) {
    matriz[i] = (int *) malloc(ncolunas*sizeof(int));
    if (!matriz[i]){
      printf("Falta memoria para alocar a matriz de ponteiros.\n");
      exit(1);
    }
  }
  return matriz;
}


double** cria_matriz_double(int nlinhas, int ncolunas)
{
  register int i;
  double **matriz;

  matriz = (double **) malloc(nlinhas*sizeof(double *));
  if (!matriz) {
        printf("Falta memoria para alocar a matriz de ponteiros\n");
        exit(1);
  }
  for (i=0; i < nlinhas; i++) {
    matriz[i] = (double *) malloc(ncolunas*sizeof(double));
    if (!matriz[i]){
      printf("Falta memoria para alocar a matriz de ponteiros.\n");
      exit(1);
    }
  }
  return matriz;
}

double ****cria_matriz_4D__double(int nlinhas, int ncolunas, int n3dimensao, int n4dimensao)
{
  register int i;
  double ****matriz;

  matriz = (double ****) malloc(nlinhas*sizeof(double ***));
  if (!matriz) {
        printf("Falta memoria para alocar a matriz de ponteiros\n");
        exit(1);
  }
  for (i=0; i < nlinhas; i++){
        matriz[i] = (double ***) malloc(ncolunas*sizeof(double**));
        if (!matriz[i]){
          printf("Falta memoria para alocar a matriz de ponteiros.\n");
          exit(1);
        }
    for (int j=0; j < ncolunas; j++){
            matriz[i][j] = (double **) malloc(n3dimensao*sizeof(double*));
            if (!matriz[i][j]){
              printf("Falta memoria para alocar a matriz de ponteiros.\n");
              exit(1);
            }
        for (int k=0; k < n3dimensao; k++){
            matriz[i][j][k] = (double *) malloc(n4dimensao*sizeof(double));
            if (!matriz[i][j][k]){
              printf("Falta memoria para alocar a matriz de ponteiros.\n");
              exit(1);
            }
        }
     }
   }
  return matriz;
}

void free_matriz_double(double **matriz, int nlinhas) {
    for (int i = 0; i < nlinhas; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

void atualiza_vetor(int *s_star, int *s, int n)
{
   for (int j=0; j < n; j++) s_star[j] = s[j];
}

/* cria memoria para um vetor de tam posicoes */
int *cria_vetor(int tam)
{
  int *vetor;

  vetor = (int *) malloc(tam*sizeof(int));
  if (!vetor){
  	printf("Falta memoria para alocar o vetor de ponteiros");
    exit(1);
  }
  return vetor;
}




void imprime_vetor(int *s, int n)
{
    for (int j=0; j < n; j++)
	   printf("s[%2d]=%d \n",j,s[j]);
}


void inicializa_vetor(int *vetor, int tam)
{
    for (int j=0; j<tam; j++) vetor[j] = 0;
}


void inicializa_vetor_int(int *vetor, int tam)
{
    for (int j=0; j<tam; j++) vetor[j] = j;
}

void libera_vetor(int *vetor)
{
  free(vetor);
}

void libera_matriz_double(double **matriz, int nlinhas)
{
  register int i;

  for (i=nlinhas-1; i >= 0; i--)
    free((double *) matriz[i]);
  free((double *) matriz);
}

void embaralha_hub_e_naohub(int *vetor, int n, int p)
{
  int *haux = cria_vetor(p);
  int *nhaux = cria_vetor(n-p);
  for (int i = 0; i < p; i++){
		haux[i]=int(vetor[i]);
  }
  embaralha_vetor(haux, p);
  for (int i = 0; i < n-p; i++){
		nhaux[i]=int(vetor[p+i]);
  }
  for (int i = 0; i < p; i++){
		vetor[i]=haux[i];
  }
  embaralha_vetor(nhaux, n-p);
  for (int i = p; i < n; i++){
		vetor[i]=nhaux[i-p];
  }
  libera_vetor(haux);
  libera_vetor(nhaux);
}

int menor_indice(double *custo, int n, int *h, int p){
	double menor = pow(10, 10);
	int indice = -1;
	for(int i = 0; i < n; i++){
		if(custo[i] > 0 and custo[i] < menor){
            if(!not_in(h, i, p)){
                menor = custo[i];
                indice = i;
            }
		}
	}
	return indice;
}
void cria_matriz_a(double **a, int n, double **custo, int beta, double xi, double alpha, double delta, int *S){
    set<int> H;
    set<int>::iterator it;
    int lista[n], cont = 0, p;
    for(int i = 0; i < n; i++){
        H.insert(S[i]);
        lista[i] = -1;
    }
    p = H.size();
    for(it = H.begin(); it != H.end(); it++){
        lista[cont] = *it;
        cont++;
    }

	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
                    a[i][j]= 0;

	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++){
            if(not_in(lista, i, p) && not_in(lista, j, p))
                if((xi*custo[i][S[i]] + alpha*custo[S[i]][S[j]] + delta*custo[S[j]][j]) <= beta){ //condicional que checa a cobertura do fluxo de i para j
                    a[i][j] = 1;
                    //cout << "Ir de " << i << " para " << j << " passando por " << S[i] << " e " << S[j] << " eh: " << (xi*custo[i][S[i]] + alpha*custo[S[i]][S[j]] + delta*custo[S[j]][j]) << endl;
                    //cout << "Os valores de custo de " << i << " para " << S[i] << ", " << S[i] << " para " << S[j] << " e de " << S[j] << " para " << j <<" sao: " << custo[i][S[i]] <<   ", " <<custo[S[i]][S[j]] << " e " << custo[S[j]][j] << endl;
                }


		}
    //getchar();
}

void cria_vetor_h(double *soma_de_fluxos, int n, int p, int *H){
    int indice;
    if(H == NULL)
        return;
    double maior = 0;
    for(int j = 0; j < p; j++){
        for(int i = 0; i < n; i++){
            if(soma_de_fluxos[i] > maior){
                maior = soma_de_fluxos[i];
                indice = i;
            }
        }
        H[j] = indice;
        maior = 0;
        soma_de_fluxos[indice] = 0;
    }
}

bool not_in(int *lista, int valor, int tamanho){

    for(int i = 0; i < tamanho; i++){
        if(lista[i] == valor)
            return false;
    }
    return true;
}

void cria_matriz_a_4(int n, double chi, double alf, double delta, int b, int** lambda, double** d, double**** alfaa) {
    // faz o c�lculo dos alfas e dos lambdas.
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                for (int m = 0; m < n; m++) {
                    if (chi * d[i][k] + alf * d[k][m] + delta * d[m][j] <= b) {
                        alfaa[i][j][k][m] = 1;
                    }
                    else {
                        alfaa[i][j][k][m] = 0;
                    }
                    if (alfaa[i][j][k][m] == 1) {
                        lambda[i][j] = 1;
                        //break;
                    }
                    if (lambda[i][j] != 1) {
                        lambda[i][j] = 0;
                        //break;
                    }
                }
            }

        }
    }

}

void cria_matriz_z(int **z, double ****alfaa, int *s, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if(i != s[i] and j != s[j])
                z[i][j] = alfaa[i][j][s[i]][s[j]];       // Z[i][j] recebe o valor de alfaa[i][j][k][m]
            else
                z[i][j] = 0;
        }
    }
}
