#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM_NOME 30
#define TAM_COR 10
// ===== Definição da Struct =====

struct Territorio {
	char nome[TAM_NOME];
	char cor[TAM_COR];
	int tropas;
};


// ===== Função para limpar Buffer de entrada =====

void limparBufferEntrada () {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
};

// ===== Função cadastrar territorios =====
void cadastrarTerritorio (struct Territorio* tropa, int* total) {

};

// ===== Função para listar os Territorios cadastrados =====
void listarTerritorios () {

};

// ===== Função atacar =====
void atacar (struct Territorio* atacante, struct Territorio* defensor) {

};



// ===== Fução principal (main) =====

int main() {
	struct Territorio *tropas;
	int totalTerritorios = 0;
	int opcao, i;
	int idAtacante, idDefensor;

	tropas = (struct Territorio *) calloc(totalTerritorios, sizeof(struct Territorio));

	if (tropas == NULL) {
		printf("Erro: falha ao alocar memória.\n");
		return 1;
	};
	
	// ===== Iniciando cadastro de tropas =====
	int qtd_cad = 0;
	printf("Quantas tropas deseja cadastrar? ");
	fgets(qtd_cad, TAM_NOME, stdin);
	for (i = 0; i < qtd_cad; i++) {
		cadastrarTerritorio(tropas, totalTerritorios);
	};
};