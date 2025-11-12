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
// Função para Remover a Quebra de Linha que sobra depois do fgets
void removerQuebraLinha(char *str) {
    str[strcspn(str, "\n")] = 0;
};

// ===== Função para limpar Buffer de entrada =====
void limparBufferEntrada () {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
};

// ===== Função cadastrar territorios =====
void cadastrarTerritorio (struct Territorio* tropa, int* total, int qtd) {
	int i;
	for(i = 0; i < qtd; i++){
		printf("\n===== CADASTRANDO TERRITÓRIO %d =====\n", i+1);
		// Cadastro do Nome
		printf("Nome do território: ");
		fgets(tropa[i].nome, TAM_NOME, stdin);
		removerQuebraLinha(tropa[i].nome);
		// Cadastro da Cor do Exército
		printf("Cor do Exército: ");
		fgets(tropa[i].cor, TAM_COR, stdin);
		removerQuebraLinha(tropa[i].cor);
		// Cadastro do Número de Tropas
		printf("Número de Tropas: ");
		scanf("%d", &tropa[i].tropas);
		limparBufferEntrada();
		(*total)++;
	};
	
};

// ===== Função para listar os Territorios cadastrados =====
void listarTerritorios (struct Territorio* tropa, int* total) {
	int i;
	for (i = 0; i < *total; i++) {
		printf("%d. %s (Exército %s, Tropas: %d)\n", i+1, tropa[i].nome, tropa[i].cor, tropa[i].tropas);
	};
};

// ===== Função atacar =====
void atacar (struct Territorio* atacante, struct Territorio* defensor) {
	// função rand gera numeros de 1 ao 6 
	int dadoAtacante = (rand()%6)+1;
	int dadoDefensor = (rand()%6)+1;

	printf("=====================================\n");
	printf("======== RESULTADO DA BATALHA =======\n");
	printf("=====================================\n");
	printf("O atacante %s rolou um dado e tirou: %d\n", atacante->nome, dadoAtacante);
	printf("O defensor %s roulou um dado e tirou: %d\n", defensor->nome, dadoDefensor);

	// Verificação para ver se as tropas atacantes são da mesma cor das tropas defensoras
	if (strcmp(atacante->cor, defensor->cor) == 0){
		printf("ERRO: Você não pode atacar um território do seu próprio exército!");
		return;
	};

	// Verificação para ver se os territórios tem pelo menos 1 tropa
	if (atacante->tropas < 1 || defensor->tropas < 1) {
		printf("ERRO: Território com tropas insuficientes!\n");
        return;
	};

	// Verifica quem foi o vencedor do confronto
	if (dadoAtacante > dadoDefensor) {
		printf("VITÓRIA DO ATAQUE! O defensor perdeu 1 tropa.\n");
		defensor->tropas--;
		if (defensor->tropas == 0) {
			defensor->tropas = 1;
			strcpy(defensor->cor, atacante->cor);
			printf("CONQUISTA! O território %s foi dominado pelo Exército %s!\n", defensor->nome, atacante->cor);
		};
	} else {
		printf("VITÓRIA DO DEFENSOR! O atacante perdeu 1 tropa.\n");
		atacante->tropas--;
		if (atacante->tropas == 0) {
			atacante->tropas = 1;
			strcpy(atacante->cor, defensor->cor);
			printf("CONQUISTA! O território %s foi dominado pelo Exército %s!\n0", atacante->nome, defensor->cor);
		};
	};
};

// ===== Fução principal (main) =====

int main() {
	struct Territorio *tropas;
	int totalTerritorios = 0;
	int idAtacante, idDefensor;
	srand(time(NULL));

	// ===== Iniciando cadastro de tropas =====
	int qtd_cad;
	printf("Quantas tropas deseja cadastrar? ");
	scanf("%d",&qtd_cad);
	limparBufferEntrada();

	// Alocando memória 
	tropas = (struct Territorio *) calloc(qtd_cad, sizeof(struct Territorio));
	if (tropas == NULL) {
		printf("Erro: falha ao alocar memória.\n");
		return 1;
	};

	// Iniciando cadastro de Territorios
	printf("=====================================\n");
	printf("========== WAR ESTRUTURADO ==========\n");
	printf("=====================================\n");
	
	cadastrarTerritorio(tropas, &totalTerritorios, qtd_cad);
	listarTerritorios(tropas, &totalTerritorios);

	// Iniciando Fase de Ataque
	printf("=====================================\n");
	printf("==========  FASE DE ATAQUE ==========\n");
	printf("=====================================\n");

	do {
		printf("Escolha o território atacante (1 a %d, ou 0 para sair): ", totalTerritorios);
		scanf("%d", &idAtacante);
		limparBufferEntrada();
		if (idAtacante != 0){
			printf("Escola o território defensor (1 a %d): ", totalTerritorios);
			scanf("%d", &idDefensor);
			limparBufferEntrada();

			// Verifica se a entrada esta dentro dos numeros de indices disponiveis
			if (idAtacante < 1 || idAtacante > totalTerritorios || idDefensor < 1 || idDefensor > totalTerritorios) {
				printf("\nERRO: IDs de territorio invalidos!\n");
			  
			  // Verifica se o idAtacante é igual ao idDefensor
			} else if (idAtacante == idDefensor) {
				printf("\nERRO: Um territorio nao pode atacar a si mesmo!\n");
			} else {
				// Chama a função atacar (-1 usado pq indice começa em 0)
				atacar(&tropas[idAtacante - 1], &tropas[idDefensor - 1]);
				listarTerritorios(tropas, &totalTerritorios);
			};
		};
		printf("Pressione Enter para contiuar...");
		getchar();
		
	} while (idAtacante != 0);
	free(tropas);
};