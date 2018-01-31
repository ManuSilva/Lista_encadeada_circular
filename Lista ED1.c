#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct contato {
	char nome[100];
	char fone[15];
	struct contato *ant, *prox;
}Tcontato;

typedef struct indice {
	char letra;
	struct indice *ant, *prox;
	Tcontato *inicio;
}Tindice;

Tindice * procurarLetra(Tindice * ind, char letra) {
	Tindice * aux = ind;
	while (aux->letra <= letra) {
		if (aux->letra == letra) {
			return aux;
		}else if (aux->prox == ind) {
			break;
		}
		else {
			aux = aux->prox;
		}
	}
	return NULL;
}
Tindice * criarLetra(char letra) {
	Tindice * novo;
	novo = (Tindice *)malloc(sizeof(Tindice));
	novo->letra = letra;
	novo->ant = NULL;
	novo->prox = NULL;
	novo->inicio = NULL;
	return novo;
}
Tcontato * criarNo(char nome[]) {
	Tcontato * novo;
	novo = (Tcontato *)malloc(sizeof(Tcontato));
	strcpy(novo->nome, nome);
	printf("Informe o telefone: ");
	gets(novo->fone);
	fflush(stdin);
	novo->ant = NULL;
	novo->prox = NULL;
	return novo;
}


Tcontato * buscaContatoDoIndice(Tcontato *l, char nome[]) {
	Tcontato* aux = l;
	do {
		if (strcmp(nome, aux->nome) == 0) {
			return aux;
		}
		else {
			aux = aux->prox;
		}
	} while (aux != l);
	return NULL;
}
Tcontato * busca(Tindice  *l, char nome[]) {
	char letra = toupper(nome[0]);
	Tindice * noIndice;
	noIndice = procurarLetra(l, letra);
	if (noIndice == NULL) {//N achou o indice da letra
		return NULL;
	}
	else{
		return buscaContatoDoIndice(noIndice->inicio, nome);
	}
}

void cadastrar(Tindice ** l, char nome[]) {
	Tindice * noIndice, * novoIndice, *x;
	Tcontato *novoNo, * no;
	char letra = toupper(nome[0]);
	
	////////agenda vazia/////////
	if (*l == NULL) {
		novoIndice = criarLetra(letra);//cria o indice
		(*l)= novoIndice;
		novoIndice->ant = novoIndice;
		novoIndice->prox = novoIndice;
		novoNo = criarNo(nome);//Criar o N� do contato
		(*l)->inicio = novoNo;
		novoNo->prox = novoNo;
		novoNo->ant = novoNo;
		printf("Novo contato inserido\n");
	}
	else {
		////////agenda Tem pelo menos uma letra////////
		noIndice = procurarLetra(*l, letra);
		///////////Indice n existe//////////
		if (noIndice == NULL) { //Indice n existe
			noIndice = *l;
			if (noIndice->letra > letra) {
				printf("/tIndice no inicio\n");
				novoIndice = criarLetra(letra);//cria o indice no inicio
				novoIndice->ant = (*l)->ant;
				novoIndice->prox = *l;
				(*l)->ant->prox = novoIndice;
				(*l) = novoIndice;
				x = novoIndice;
				printf("Letra antes: %c\n", x->ant->letra);
				printf("Letra antes: %c\n", x->prox->letra);
				novoNo = criarNo(nome);//Criar o N� do contato no inicio
				novoIndice->inicio = novoNo;
				novoNo->prox = novoNo;
				novoNo->ant = novoNo;
				printf("Novo contato inserido\n");
			}
			else {
				do{
					printf("noIndice->prox->letra: %c\n", noIndice->prox->letra);
					printf("letra: %c\n", letra);
					if (noIndice->prox->letra > letra) {
						printf("/tIndice no meio\n");
						novoIndice = criarLetra(letra);//cria o indice no meio
						novoIndice->prox = noIndice->prox;
						novoIndice->ant = noIndice;
						novoIndice->ant->prox = novoIndice;
						novoIndice->prox->ant = novoIndice;
						x = novoIndice;
						printf("Letra antes: %c\n", x->ant->letra);
						printf("Letra antes: %c\n", x->prox->letra);
						novoNo = criarNo(nome);//Criar o N� do contato no inicio
						novoIndice->inicio = novoNo;
						novoNo->prox = novoNo;
						novoNo->ant = novoNo;
						printf("Novo contato inserido\n");
						
						return;
					}
					else {
						noIndice = noIndice->prox;
						printf("noIndiceLoop: %c\n", noIndice->letra);
						printf("*l: %c\n", (*l)->letra);
					}
				}while (noIndice != *l);
				printf("/tIndice no final\n");
				printf("noIndice: %c\n", noIndice->letra);
				novoIndice = criarLetra(letra);//cria o indice no final
				novoIndice->prox = noIndice;
				novoIndice->ant = noIndice->ant;
				noIndice->ant->prox = novoIndice;
				noIndice->ant = novoIndice;
				x = novoIndice;
				printf("Letra antes: %c\n", x->ant->letra);
				printf("Letra depois: %c\n", x->prox->letra);
				novoNo = criarNo(nome);//Criar o N� do contato no inicio
				novoIndice->inicio = novoNo;
				novoNo->prox = novoNo;
				novoNo->ant = novoNo;
				printf("Novo contato inserido\n");
			}
		}
		///////////Indice ja existe//////////
		else {
			no = buscaContatoDoIndice(noIndice->inicio, nome);
			if (no != NULL) {
				printf("Esse contato j� existe\n");
			}
			else{
				no = noIndice->inicio;
				if (strcmp(no,nome)>0) { 
					printf("Inser��o no inicio");
					novoNo = criarNo(nome);//Criar o N� do contato no inicio
					novoNo->prox = no;
					novoNo->ant = no->ant;
					no->ant->prox = novoNo;
					no->ant = novoNo;
					noIndice->inicio = novoNo;
				}
				else {
					do{
						if (strcmp(no->prox->nome,nome)>0) { //Inserss�o no meio
							printf("Inser��o no meio");
							novoNo = criarNo(nome);//Criar o N� do contato no meio
							novoNo->prox = no->prox;
							novoNo->ant = no;
							novoNo->ant->prox = novoNo;
							novoNo->prox->ant = novoNo;
							printf("Novo contato inserido\n");;
							return;
						}
						else {
							no = no->prox;
						}
					} while (no!= noIndice->inicio);//ACABA APONTANDO PARA O PRIMEIRO
					printf("Inser��o no final");
					novoNo = criarNo(nome);//Criar o N� do contato no final
					novoNo->prox = no;
					novoNo->ant = no->ant;
					no->ant->prox = novoNo;
					no->ant = novoNo;
					printf("Novo contato inserido\n");;
				}
			}
		}
	}
}
void exibirContato(Tindice  *l, char nome[]) {
	Tcontato * aux;
	if (l==NULL){
		printf("Agenda Vazia");
	}
	else{
		aux = busca(l, nome);
		if (aux==NULL){
			printf("Contato n�o encontrado");
		}
		else {
			printf("Nome: %s\n", aux->nome);
			printf("Telefone: %s\n\n", aux->fone);
		}
	}
}
void alterarDados(Tindice  *l,char nome[]) {
	Tcontato * aux;
	if (l == NULL) {
		printf("Agenda Vazia");
	}
	else {
		aux = busca(l, nome);
		if (aux == NULL) {
			printf("Contato n�o encontrado");
		}
		else {
			printf("Informe o novo telefone: ");
			gets(aux->fone);
			fflush(stdin);
			printf("Telefone alterado");
		}
	}
}
void exibirLetra(Tindice *l, char letra) {
	Tindice * noIndice;
	Tcontato * aux;
	char let = toupper(letra);
	if (l == NULL) {
		printf("Agenda Vazia");
	}
	else {
		noIndice = procurarLetra(l, let);
		if (noIndice == NULL) {
			printf("Letra n�o encontrada");
		}else{
			aux = noIndice->inicio;
			do{
				printf("Nome: %s\n", aux->nome);
				printf("Telefone: %s\n\n", aux->fone);
				aux = aux->prox;
			} while (aux != noIndice->inicio);
		}
	}
}
void exibirTudo(Tindice  *l) {
	Tindice * i;
	Tcontato * x;
	if (l == NULL) {
		printf("Agenda vazia\n");
	}
	else {
		i = l;
		do {
			x = i->inicio;
			do
			{
				printf("Nome: %s\n", x->nome);
				printf("Telefone: %s\n\n", x->fone);
				x = x->prox;
			} while (x != i->inicio);
			i = i->prox;
		} while (i != l);
	}
}
void remover(Tindice ** l, char nome[]) {
	Tcontato * del;
	Tindice * noIndice;
	char letra = toupper(nome[0]);
	if (*l == NULL) {
		printf("Agenda vazia\n");
	}
	else {
		del = busca(*l, nome);
		noIndice = procurarLetra(*l, letra);
		if (del == NULL) {
			printf("Contato n�o encontrado\n");
		}
		//Se tiver apenas um n� na determinda letra//
		else if(del->prox==del) {//Se tiver apenas um n� na determinda letra
			free(del);
			//Remover indice da agenda//
			if (noIndice->prox==noIndice){//A agenda s� tem uma letra
				free(noIndice);
				*l = NULL;
				printf("Contato Removido\n");
			}
			else if (noIndice == *l){	  //A letra esta no primeiro indice
				*l = noIndice->prox;
				(*l)->prox = *l;
				(*l)->ant = *l;
				free(noIndice);
				printf("Contato Removido\n");
			}
			else if (noIndice->prox == *l) {//a letra esta no ultimo indice
				(*l)->ant = noIndice->ant;
				noIndice->ant->prox = *l;
				free(noIndice);
				printf("Contato Removido\n");
			}
			else {							//a letra esta no meio
				(*l)->prox = noIndice->prox;
				noIndice->prox->ant=noIndice->ant;
				free(noIndice);
				printf("Contato Removido\n");
			}
		}
		//Mais de um n� na determinda letra, n precia desalocar o indice//
		else if (noIndice->inicio == del) { //o contato esta no inicio
			noIndice->inicio = del->prox;
			noIndice->inicio->prox = noIndice->inicio;
			noIndice->inicio->ant = noIndice->inicio;
			free(del);
			printf("Contato Removido\n");
		}
		else if (del->prox == noIndice->inicio) {//o contato esta no final
			noIndice->inicio->ant = del->ant;
			del->ant->prox = noIndice->inicio;
			free(del);
			printf("Contato Removido\n");
		}
		else {									//O contato esta no meio
			noIndice->inicio->prox =del->prox;
			del->prox->ant = del->ant;
			free(del);
			printf("Contato Removido\n");
		}
	}
}
void removerTudo(Tindice  ** l) {
	Tindice * i;
	Tcontato * x;
	if (l == NULL) {
		printf("Agenda vazia\n");
	}
}

int main() {
	Tindice * agenda = NULL;
	char nome[100],op, letra;
	do {
		printf("\t\tEscolha uma op��o\n\n");
		printf("1 - Inserir novo contato\n");
		printf("2 - Exibir toda agenda\n");
		printf("3 - Exibir um contato\n");
		printf("4 - Alterar telefone\n");
		printf("5 - Exibir os contatos de uma letra \n");
		printf("6 - Remover coontato \n");
		printf("7 - Sair do Programa\n");
		op = getche();
		printf("\n");
		fflush(stdin);
		printf("\n");
		switch (op) {
		case '1':printf("Informe o nome do novo contato:");
			gets(nome);
			fflush(stdin);
			cadastrar(&agenda, nome);
			break;
		case '2':exibirTudo(agenda);
			break;
		case '3':printf("Informe o nome do contato que deseja exibir:");
			gets(nome);
			fflush(stdin);
			exibirContato(agenda, nome);
			break;
		case '4':printf("Informe o nome do contato que deseja alterar:");
			gets(nome);
			fflush(stdin);
			alterarDados(agenda, nome);
			break;
		case '5':printf("Informe a letra:");
			scanf("%c", &letra);
			fflush(stdin);
			exibirLetra(agenda, letra);
			break;
		case '6':printf("Informe o nome do contato que deseja remover:");
			gets(nome);
			fflush(stdin);
			remover(&agenda, nome);
			break;
		case '7':exit;
			break;
		default: printf("Opcao Invalida \n");
		}
	} while (op != '7');
	
	return 0;
}