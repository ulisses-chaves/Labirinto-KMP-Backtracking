// Nome: Ulisses Chaves Silva
// Número do EP: 03
// Data: 18/07/18
// Disciplina: Algoritmos e Estruturas de Dados

#include <stdio.h>
#include <stdlib.h>

struct Pos {
	int x;
	int y; };

struct Caminho {
	char cor;
	int x;
	int y; };

const int p = 7;

// A função kmpPrePro recebe um vetor
// padrao[0..n-1]. É o pre-processamento
// do kmp. Devolve o vetor pi quando o 
// padrao for verificado.

int *kmpPrePro (char *padrao, int n) {
	int k = -1;
	int i = 1;
	int *pi = (int*) malloc (n*sizeof (int*));
	if (!pi)
		return NULL;
	pi[0] = k;
	for (i = 1; i < n; i++) {
		while (k > -1 && padrao[k + 1] != padrao[i]) k = pi[k];
		if (padrao[i] == padrao[k + 1]) k++;
		pi[i] = k; }
	return pi;
}

// A função kmp recebe duas strings 
// caminho[0..n - 1] e padrao[0..m - 1].
// Devolve um numero qualquer >= 0 se 
// houver um padrao ou -1 se não houver.
            	
int kmp (char *caminho, int n, char *padrao, int m) {
	int i;
	int *pi = kmpPrePro (padrao, m);
	int k = -1;
	if (!pi) return -1;
	for (i = 0; i < n; i++) {
		while (k > -1 && padrao[k+1] != caminho[i]) k = pi[k];
		if (caminho[i] == padrao[k+1]) k++;
		if (k == m - 1) {
			free (pi);
			return i - k; }
	}
	free (pi);
	return -1;
}

// A função backtracking recebe uma struct Pos e
// uma matriz mapaAux[0..tamanho-1][0..tamanho-1].
// Devolve um inteiro que corresponde ao backtrack
// que irá ser executado.

int backtracking (Pos personagem, char **mapaAux, int tamanho) {
	if (personagem.x != 0 && mapaAux[personagem.x - 1][personagem.y] == 's' ) {
		mapaAux[personagem.x][personagem.y] = 'd';
		return 1;
	} else {
		if (personagem.y != tamanho - 1 && mapaAux[personagem.x][personagem.y + 1] == 's') {
			mapaAux[personagem.x][personagem.y] = 'd';
			return 2;
		} else {
			if (personagem.x != tamanho - 1 &&  mapaAux[personagem.x + 1][personagem.y] == 's') {
				mapaAux[personagem.x][personagem.y] = 'd';
				return 3;
			} else {				
				if (personagem.y != 0 && mapaAux[personagem.x][personagem.y - 1] == 's') {
					mapaAux[personagem.x][personagem.y] = 'd';
					return 4;
				}
			}
		}
	}
	return 0;
}

// A função esquerda recebe uma struct Pos e
// duas matrizes mapa e mapaAux. Devolve 1 se
// o personagem conseguiu realizar o movimento
// ou 0 se não conseguiu.

int esquerda (Pos personagem, char **mapa, char **mapaAux) {
	if (personagem.y != 0 && mapa[personagem.x][personagem.y - 1] != '0'&& mapaAux[personagem.x][personagem.y - 1] != 's' && mapaAux[personagem.x][personagem.y - 1] != 'd') {
		mapaAux[personagem.x][personagem.y] = 's';
		return 1; }	
	return 0;
}

// A função baixo recebe uma struct Pos e
// duas matrizes mapa e mapaAux. Devolve 1 se
// o personagem conseguiu realizar o movimento
// ou 0 se não conseguiu.

int baixo (Pos personagem, char **mapa, char **mapaAux, int tamanho) {
	if (personagem.x != tamanho - 1 && mapa[personagem.x + 1][personagem.y] != '0'&& mapaAux[personagem.x + 1][personagem.y] != 's' && mapaAux[personagem.x + 1][personagem.y] != 'd') {
		mapaAux[personagem.x][personagem.y] = 's';
		return 1; }
	return 0;
}

// A função direita recebe uma struct Pos e
// duas matrizes mapa e mapaAux. Devolve 1 se
// o personagem conseguiu realizar o movimento
// ou 0 se não conseguiu.

int direita (Pos personagem, char **mapa, char **mapaAux, int tamanho) {
	if (personagem.y != tamanho - 1 && mapa[personagem.x][personagem.y + 1] != '0'&& mapaAux[personagem.x][personagem.y + 1] != 's' && mapaAux[personagem.x][personagem.y + 1] != 'd') {
		mapaAux[personagem.x][personagem.y] = 's';
		return 1; }
	return 0;
}

// A função cima recebe uma struct Pos e
// duas matrizes mapa e mapaAux. Devolve 1 se
// o personagem conseguiu realizar o movimento
// ou 0 se não conseguiu.

int cima (Pos personagem, char **mapa, char **mapaAux) {
	if (personagem.x != 0 && mapa[personagem.x - 1][personagem.y] != '0' && mapaAux[personagem.x - 1][personagem.y] != 's' && mapaAux[personagem.x - 1][personagem.y] != 'd') {
		mapaAux[personagem.x][personagem.y] = 's';
		return 1; }
	return 0;	
}

// A função start recebe duas structs Pos e uma Caminho e recebe duas
// matrizes mapa e mapaAux, ambas [0..tamanho - 1][0..tamanho - 1]. Ela
// salva e realiza os movimentos do personagem. Devolve 1 se conseguir 
// achar a saida ou 0 se não houver mais backtrack para ser executado.

int start (Pos personagem, Pos saida, char **mapa, char **mapaAux, Caminho *caminho, int tamanho) {
	int indice = 0;
	mapaAux[0][0] = 's';
	caminho[indice].x = personagem.x;
	caminho[indice].y = personagem.y;
	caminho[indice].cor = mapa[personagem.x][personagem.y];
	while (personagem.x != saida.x || personagem.y != saida.y) {
		if (cima (personagem, mapa, mapaAux) == 1) {
			personagem.x = personagem.x - 1;
			indice++;
			caminho[indice].x = personagem.x;
			caminho[indice].y = personagem.y;
			caminho[indice].cor = mapa[personagem.x][personagem.y];
		} else {
			if (direita (personagem, mapa, mapaAux, tamanho) == 1) {
				personagem.y = personagem.y + 1;
				indice++;
				caminho[indice].x = personagem.x;
				caminho[indice].y = personagem.y;
				caminho[indice].cor = mapa[personagem.x][personagem.y];
			} else {
				if (baixo (personagem, mapa, mapaAux, tamanho) == 1) {
					personagem.x = personagem.x + 1;
					indice++;
					caminho[indice].x = personagem.x;
					caminho[indice].y = personagem.y;
					caminho[indice].cor = mapa[personagem.x][personagem.y];
				} else {
					if (esquerda (personagem, mapa, mapaAux) == 1) {
						personagem.y = personagem.y - 1;
						indice++;
						caminho[indice].x = personagem.x;
						caminho[indice].y = personagem.y;
						caminho[indice].cor = mapa[personagem.x][personagem.y];
					} else {
						int resposta = backtracking (personagem, mapaAux, tamanho);
						switch (resposta) {
							case 1:
								personagem.x = personagem.x - 1;
								caminho[indice].x = 0;
								caminho[indice].y = 0;
								caminho[indice].cor = '\0';
								indice--;
								break;
							case 2:
								personagem.y = personagem.y + 1;
								caminho[indice].x = 0;
								caminho[indice].y = 0;
								caminho[indice].cor = '\0';
								indice--;
								break;
							case 3:
								personagem.x = personagem.x + 1;
								caminho[indice].x = 0;
								caminho[indice].y = 0;
								caminho[indice].cor = '\0';
								indice--;
								break;
							case 4:
								personagem.y = personagem.y - 1;
								caminho[indice].x = 0;
								caminho[indice].y = 0;
								caminho[indice].cor = '\0';
								indice--;
								break;
							default:
								return 0;
						}
					}
				}
			}
		}
	}
	return 1;
}

int main () {
	FILE *file;
	file = fopen ("labirinto.txt", "r");     
	int tamanho, i, j, contador = 0;         
	fscanf (file, "%i", &tamanho);           
	Pos personagem;                          
	fscanf (file, "%i", &personagem.x);      
	fscanf (file, "%i", &personagem.y);
	Pos saida;
	fscanf (file, "%i", &saida.x);
	fscanf (file, "%i", &saida.y);
	fflush (stdin);
	char aux;
	char **mapa;
	mapa = (char**) malloc (tamanho*sizeof (char *));
	for (i = 0; i < tamanho; ++i)
		mapa[i] = (char*) malloc (tamanho*sizeof (char *));
	char **mapaAux;
	mapaAux = (char**) malloc (tamanho*sizeof (char *));
	for (i = 0; i < tamanho; ++i)
		mapaAux[i] = (char*) malloc (tamanho*sizeof (char *));
	for (i = 0; i < tamanho; i++) {
		for (j = 0; j < tamanho; j++) {
			fscanf(file, "%c", &aux);
			fscanf(file, "%c", &mapa[i][j]);
		}
	}
	for (i = 0; i < tamanho; ++i){
		for (j = 0; j < tamanho; ++j) mapaAux[i][j] = mapa[i][j];
	}
	Caminho *caminho;
	caminho = (Caminho*) malloc (tamanho*tamanho*sizeof (Caminho*));
	char cadeia[p];
	for (i = 0; i < p; i++) {
		if (i == 0) {
			fscanf (file, "%c", &aux);
			i = 0; 
		}
		fscanf (file, "%c", &cadeia[i]);
		if (cadeia[i] == 'a' || cadeia[i] == 'v' || cadeia[i] == 'r' || cadeia[i] == 'l')
			contador++;
	}
	char padrao[contador];
	for (i = 0; i < contador; i++)
		padrao[i] = cadeia[i];
	if (start (personagem, saida, mapa, mapaAux, caminho, tamanho) == 1) {
		printf ("Caminho:\n");
		int contadorFinal = 0;
		for (i = 0; i < tamanho*tamanho; ++i) {
			if (caminho[i].cor == 'r' || caminho[i].cor == 'l' || caminho[i].cor == 'a' || caminho[i].cor == 'v')
				contadorFinal++;
		}
		for (i = 0; i < contadorFinal; ++i)
			printf ("(%d %d) %c\n", caminho[i].x, caminho[i].y, caminho[i].cor);
		char caminhoFinal[contadorFinal];
		for (i = 0; i < contadorFinal; ++i)
			caminhoFinal[i] = caminho[i].cor;
		if (kmp(caminhoFinal, contadorFinal, padrao, contador) >= 0)
			printf ("Esse caminho leva a saida."); 
		else printf ("Esse caminho leva ao dragao.");
	} else printf ("Nao ha caminho ate a saida.");
	free (caminho);
	free (mapa);
	free (mapaAux);
}
