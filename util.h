
void embaralha_vetor(int *vetor, int n);

double** cria_matriz_double(int nlinhas, int ncolunas);

void atualiza_vetor(int *s_star, int *s, int n);

int* cria_vetor(int tam);

void imprime_vetor(int *s, int n);

void inicializa_vetor(int *vetor, int tam);

void inicializa_vetor_int(int *vetor, int tam);

void libera_vetor(int *vetor);

void libera_matriz_double(double **matriz, int nlinhas);

void embaralha_hub_e_naohub(int *vetor, int n, int p);

int **cria_matriz_int(int nlinhas, int ncolunas);

double ****cria_matriz_4D__double(int nlinhas, int ncolunas, int n3dimensao, int n4dimensao);

void cria_matriz_a(double **a, int n, double **custo, int beta, double xi, double alpha, double delta, int *S);

int menor_indice(double *custo, int n, int *h, int p);

void cria_vetor_h(double *soma_de_fluxos, int n, int p, int *H);

bool not_in(int *lista, int valor, int tamanho);

void free_matriz_double(double **matriz, int nlinhas);

void cria_matriz_a_4(int n, double chi, double alf, double delta, int b, int** lambda, double** d, double**** alfaa);

void cria_matriz_z(int **z, double ****alfaa, int *s, int n);
