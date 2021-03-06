/**
 *	Trabalho 1 -  Métodos Iterativos para  Sitemas Lineares
 *
 *		Cálculo Numérico	SME-0104
 *		Prof.: Murilo Francisco Tomé
 *
 *		Eduardo Brunaldi dos Santos             8642515
 *		Jorge Ashkar Ferreira Simondi           8517081
 *		Victor Luiz da Silva Mariano Pereira    8602444
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gauss_seidel.h>

/**
 * Função para imprimir de forma mais legível uma matriz quadrada
 * @param A Matriz a ser impressa
 * @param n dimensão da matriz
 */
void imprime_matriz(long double **A, int n){
	int i;
	int j;

	for (i = 0; i < n; i++){
		for (j = 0; j < n; j++)
			printf("%Lf\t", A[i][j]);
		printf("\n");
	}
}

/**
 * Função para imprimir um vetor de forma mais legível
 * @param v vetor a ser impresso
 * @param n tamanho do vetor
 */
void imprime_vetor(long double *v, int n){
	int i;

	for (i = 0; i < n; i++)
		printf("%.16Lf\n", v[i]);
}

/**
 * Função para retornar a norma infinita de um vetor obtido pela subtração
 * de dois vetores
 * @param  xk Vetor x(k+1)
 * @param  x  Vetor x(k)
 * @param  n  Dimensão dos vetores
 * @return    norma do vetor obtido pela subtração
 */
long double norma_infinita(long double *xk, long double *x, int n){
	int i;
	long double maximo = 0;

	for(i = 0; i < n; i++)
		if(fabs(xk[i] - x[i]) > maximo)
			maximo = fabs(xk[i] - x[i]);

	return maximo;
}

/**
 * Função para resolver o sistema linear usando o método de gauss-seidel
 * @param A     Matriz de funções do sistema linear
 * @param b     Resultados das equações do sistema linear
 * @param x     Vetor contendo os resultados iniciais
 * @param n     Dimensão do sistema linear
 * @param e     Precisão
 * @param itmax Número máximo de iterações
 */
long double *gauss_seidel(long double **A, long double *b, long double *x, int n, long double e, int itmax){
	// Variáveis auxiliares
	long double somaL;
	long double somaU;
	long double *x_ant;

	// Iteradores
	int i;
	int j;
	int it = 0;

	// Alocando espaço da memória para o vetor auxiliar
	x_ant = malloc(sizeof(long double) * n);

	do{
		// Para toda iteração, atualiza o vetor x anterior
		for(i = 0; i < n; i++)
			x_ant[i] = x[i];

		for(i = 0; i < n; i++){
			somaL = 0;
			somaU = 0;
			// Somatório da parte de baixo da matriz
			for(j = 0; j < i; j++)
				somaL += A[i][j] * x[j];
			// Somatório da parte de cima da matriz
			for(j = i + 1; j < n; j++)
				somaU += A[i][j] * x[j];
			// Aproximação do x
			x[i] = (b[i] - somaL - somaU )/A[i][i];
		}

		// Calcula a norma infinita e compara com a tolerância
		if(norma_infinita(x, x_ant, n) <= e){
			// Se quiser imprimir o número de iterações necessários para
			// chegar na solução encontrada, só descomentar o próximo
			// comando 'printf()'. Se caso não imprimir o número de
			// iterações mesmo descomentando o comando, quer dizer que
			// o it chegou ao itmax.

			// printf("Numero de iteracoes: %d\n", it);

			free(x_ant);
			return x;
		}

		it++;
	}while(it < itmax);

	// Libera memória
	free(x_ant);
	return x;
}
