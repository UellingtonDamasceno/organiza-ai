#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <locale.h>


#include <conio.h>


#define TRUE 1
#define FALSE 0

//========================STRUCT UTILIZADA=========================
typedef struct problema{

	double semestre;
	int problema;
	int ano;
	char titulo[250];
	char discritivo[500];

	double valor_de_ordem;
	struct problema *prox_problema;

}Problema;

//====================SESS?O DECLARA??O DE FUN??ES.==================
	int menu_principal();
	void recebe_nome();
	int verifica_se_vazio();
	int cont_linha();
	Problema* preencher_celula();
	Problema* insere_ordenado();
												void busca_simples();
												void busca_avancada();
			Problema* ler_ano();
			Problema* ler_semestre();
			Problema* ler_problema();
			Problema* ler_ti_e_dis();
												void gerar_arquivo();
	void imprimir_ordenado();
	int menu_buscar();
	void exibir_conteudo();

//====================FUN??ES DE DESING ACOPLADAS====================
	void gotoxy();
	void barra_sup();
	void pula_espaco();
	void barra_inf();
	int tentar_novamente();
	int deve_sair();
	void saindo();

int main(){
	char arquivo[50];
	int qtd_linhas = 0, i = 0;
	int repetir_menu_principal = FALSE;
	int repetir_arquivo = FALSE;
	Problema *novo_problema;
	Problema *l = NULL;

	//system("mode con:cols=105 lines=30");
	do{
		repetir_arquivo = FALSE;
		recebe_nome(arquivo);
		if(verifica_se_vazio(arquivo) == TRUE){
			if(tentar_novamente() == TRUE){
				repetir_arquivo = TRUE;
				system("cls");
			}
			else if(deve_sair() == TRUE)
				saindo();
			else{
				repetir_arquivo = TRUE;
				system("cls");
			}
		}
		else{
			qtd_linhas = cont_linha(arquivo);
			printf("Quantidade de linhas: %d\n", qtd_linhas);
			FILE *f1 = fopen(arquivo, "r");//Abre o arquivo no modo de leitura.
			for(i = 0; i < qtd_linhas; i++){
				novo_problema = preencher_celula(f1);
				l = insere_ordenado(l, novo_problema);
			}
			fclose(f1);//fecha o arquivo que foi aberno na linha 69.
			do{
				repetir_menu_principal = FALSE;
				switch(menu_principal()){
					case 1:{
						//exibir_conteudo(arquivo);
						imprimir_ordenado(l);
						repetir_menu_principal = TRUE;
						break;
					}
					case 2:{
						novo_problema = (Problema *) malloc(sizeof(Problema));
						novo_problema = ler_ano(novo_problema);
						novo_problema = ler_semestre(novo_problema);
						novo_problema = ler_problema(novo_problema);
						novo_problema = ler_ti_e_dis(novo_problema);
						repetir_menu_principal = TRUE;
						system("pause");
						break;
					}
					case 3:{
						switch(buscar_menu()){
							case 1:{
								printf("VOCE ESTA BUSCANDO POR ANO\n");
								repetir_menu_principal = TRUE;
								system("pause");
								break;
							}
							case 2:{
								printf("VOCE ESTA BUSCANDO POR SEMESTRE\n");
								repetir_menu_principal = TRUE;
								system("pause");
								break;
							}
							case 3:{
								printf("VOCE ESTA BUSCANDO POR PROBLEMA\n");
								repetir_menu_principal = TRUE;
								system("pause");
								break;
							}
							case 4:{
								repetir_menu_principal = TRUE;
								break;
							}
						}
						repetir_menu_principal = TRUE;
						break;
					}
					case 4:{
						printf("ARQUIVO GERDADO COM SUCESSO\n");
						repetir_menu_principal = TRUE;
						system("pause");
						break;
					}
					case 5:{
						repetir_arquivo = TRUE;
						system("cls");
						break;
					}
					case 6:{
						 if(deve_sair() == TRUE)
							saindo();
						else{
							repetir_menu_principal = TRUE;
							system("cls");
						}
						break;
					}
				}
			}while(repetir_menu_principal == TRUE);
		}
	}while(repetir_arquivo == TRUE);
}
//======================================================================================================================================================================================
void recebe_nome(char arquivo[]){
	barra_sup(32, 6, 16);
	pula_espaco(6, 0);
	printf("\t\t\t\xBA  DIGITE O NOME DO ARQUIVO:\t\t\t\xBA");
	printf("\n");
	barra_inf(47, FALSE);
	gotoxy(54, 3);//fun??o usada para mover o cursor.
	gets(arquivo);
	system("cls");
}
//======================================================================================================================================================================================
int verifica_se_vazio(char arquivo[]){//RESPONSAVEL POR VERIFICAR SE O ARQUIVO EXISTE E SE ELE ? VALIDO.

	FILE *numero_de_linha = fopen(arquivo, "r");//abre o arquivo em modo de leitrua para verificar quantas linhas tem;
	if(numero_de_linha == NULL){
		barra_sup(56,5,28);
		pula_espaco(7, 5);
		printf("\t\t\t\xBA\t    Arquivo nao encontrado ou nao er valido\t     \xBA\n");
		printf("\t\t\t\xBA\t\t\tTente novamente\t\t\t     \xBA\n");
		pula_espaco(7, 5);
		barra_inf(60, FALSE);
		return TRUE;
	}
	else
		return FALSE;
	fclose (numero_de_linha);
}
//======================================================================================================================================================================================
int cont_linha(char arq[]){
	char ch;//responsavel por receber todos caracteres (um de cada vez) do arquivo;
	int quant = 0;//serve para como um contador. pois, ? incrementado 1 a cada linha do arquivo.
	FILE *arquivo = fopen(arq, "r");

	while((ch = getc(arquivo))!= EOF){//Repita enquanto n?o chegar no final do arquivo.
		if (ch == '\n'){//se ch for igual ao caractere new line.
			quant++;//incremente 1 em quant.
		}
	}
	fclose(arquivo);
	return quant;
}
//======================================================================================================================================================================================
Problema* preencher_celula(FILE* pegar_no_arq){
	Problema *o;
	o = (Problema *) malloc(sizeof(Problema));

	fscanf(pegar_no_arq, "%lf", &o->semestre);
	fscanf(pegar_no_arq, "%lf", &o->problema);
	fscanf(pegar_no_arq, "%d\t", &o->ano);
	fscanf(pegar_no_arq, "%[^\t]s", o->titulo);
	fscanf(pegar_no_arq, "%[^\n]s", o->discritivo);
	o->valor_de_ordem = o->semestre + (o->problema /100);//nesse momento o valor do problema ? somado com o valor do semestre. e assim gerando um novo numero que vai ser utilado 
														//para a ordena??o. exemplo: semestre 2016.1 problema: 2 == valor de ordem = 2016.12;
	/*
	printf("Ano: %d\n", o->ano);
	printf("Problema: %.0lf\n", o->problema);
	printf("Semestre: %.1f\n", o->semestre);
	printf("Titulo: %s\n", o->titulo);
	printf("Discritivo: %s\n", o->discritivo);
	printf("ORDEM: %.2lf\n\n\n", o->valor_de_ordem);
	*/
	return o;
}
//==============================================================================================================================================================================
Problema* insere_ordenado(Problema* l, Problema* o_novo){
    Problema *p = l;
    Problema *a = l;
	int ja_inseriu = FALSE;
	
/*	printf("Ano: %d\n", o_novo->ano);
	printf("Problema: %.0lf\n", o_novo->problema);
	printf("Semestre: %.1f\n", o_novo->semestre);
	printf("Titulo: %s\n", o_novo->titulo);
	printf("Discritivo: %s\n", o_novo->discritivo);
	printf("ORDEM: %.2lf\n", o_novo->valor_de_ordem);
	printf("\n;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");*/
	
	if(p == NULL){//verifica se a lista esta vazia;
		l = (Problema *) malloc(sizeof(Problema)); //se tiver vazia, "l" tem o espa?o alocado dinamicamente.
		o_novo->prox_problema = NULL;//o novo elemento aponta para o NULL;
		l = o_novo; // l recebe o novo elemento. 
		//printf("lista estava vazia\n");
	}
	else{
		while(p != NULL && o_novo->valor_de_ordem < p->valor_de_ordem){
			a = p;
			p = p->prox_problema;
		}
		if(a == NULL){
			o_novo->prox_problema = p;
			a->prox_problema = o_novo;
		}
		o_novo->prox_problema = a->prox_problema;
		a->prox_problema = o_novo;
	 return l;
	}
	
	return l;
}
//======================================================================================================================================================================================
int menu_principal(){//Fun??o responsavel por gerar o menu pricipal.
	setlocale(LC_ALL, "C");
	int resposta = 0;
	do{
		barra_sup(18, 4, 9);
		pula_espaco(4, 0);
		printf("\t\t\t\xBA  VERIFICAR CONTEUDO_____(01)  \xBA\n");
		printf("\t\t\t\xBA  ADICIONAR PROBLEMA_____(02)  \xBA\n");
		printf("\t\t\t\xBA  BUSCAR NO ARQUIVO______(03)  \xBA\n");
		printf("\t\t\t\xBA  GERAR NOVO ARQUIVO_____(04)  \xBA\n");
		printf("\t\t\t\xBA  TENTAR OUTRO ARQUIVO___(05)  \xBA\n");
		pula_espaco(4, 0);
		printf("\t\t\t\xBA  SAIR___________________(06)  \xBA\n");
		pula_espaco(4, 0);
		barra_inf(31, TRUE);
		scanf("%d", &resposta);
		fflush(stdin);
		if (resposta < 1 || resposta > 6)
			printf("\nESCOLHA INVALIDA! TENTEN NOVAMENTE!\n");
	}while(resposta < 1 || resposta > 6);
	return resposta;
}
//=====================================================================================================================================================================================
void exibir_conteudo(char arquivo[]){//fun??o que ler o conteudo direto do arquivo. 
	setlocale(LC_ALL, "portuguese");
	char caracter, ch;
	FILE *ler = fopen (arquivo, "r");

	while((caracter = fgetc(ler))!= EOF){
		if (caracter == '\t')
			printf("\n");
		putchar(caracter);
	}
	printf("\n");
}
//=====================================================================================================================================================================================
Problema* ler_ano(Problema* o){
	
	int repetir = FALSE;
	do{
		repetir = FALSE;
		system("cls");
		barra_sup(40, FALSE, FALSE);
		printf("\t\t\t\xBA DIGITE O ANO DO PROBLEMA: \t\t \xBA\n");
		barra_inf(40, FALSE);
		gotoxy(53, 2);
		scanf("%d", &o->ano);
		fflush(stdin);
		printf("\n\n");
	
		if(o->ano < 2003 && o->ano > 1976){
			barra_sup(37, 1, 17);
			printf("\t\t\t\xBA   DESCULPAS! MAS, O CURSO NEM EXISTIA  \xBA\n");
			barra_inf(40, FALSE);
			repetir = TRUE;
			system("pause");
		}
		else if(o->ano < 1976){
			barra_sup(37, 1, 17);
			printf("\t\t\t\xBA   DESCULPAS! MAS, A UEFS NEM EXISTIA   \xBA\n");
			barra_inf(40, FALSE);
			system("pause");
			repetir = TRUE;
		}
		else if(o->ano > 2018){
			barra_sup(37, 1, 17);
			printf("\t\t\t\xBA   DESULPAS! MAS, VOCE ER DO FUTURO?    \xBA\n");
			barra_inf(40, FALSE);
			system("pause");
			repetir = TRUE;
		}
		else
			return o;
	}while(repetir == TRUE);
}
//=======================================================================================================================================================================================
Problema* ler_semestre(Problema* o){
	int repetir = FALSE;
	float s = 0;
	do{
		repetir = FALSE;
		barra_sup(40, FALSE, FALSE);
		printf("\t\t\t\xBA\t     QUAL E O SEMESTRE\t\t \xBA\n");
		pula_espaco(5, 1);
		printf("\t\t\t\xBA       %d.1    \t   %d.2        \xBA\n", o->ano, o->ano);
		barra_inf(40, TRUE);
		scanf("%lf", &o->semestre);
		fflush(stdin);

		s = (o->semestre - o->ano);
		
		if(s < 0.1 || s > 0.2){
			system("cls");
			barra_sup(37, 1, 17);
			printf("\t\t\t\xBA  SEMESTRE INVALIDO! TENTE NOVAMENTE !  \xBA\n");
			barra_inf(40, FALSE);
			repetir = TRUE;
			getch();
		}
		else
			return o;
	}while(repetir == TRUE);
}
//=======================================================================================================================================================================================
Problema* ler_problema(Problema *o){
	int repetir = FALSE;
	
	do{
		repetir = FALSE;
		barra_sup(40, FALSE, FALSE);
		printf("\t\t\t\xBA DIGITE O NUMERO DO PROBLEMA: \t\t \xBA\n");
		barra_inf(40, FALSE);
		gotoxy(57, 12);
		scanf("%d", &o->problema);
		fflush(stdin);
		if (o->problema < 1){
			barra_sup(40, 1, 17);
			printf("\t\t\t\xBA  O PROBLEMA NAO PODE SER NEGATIVO \xBA\n");
			barra_inf(40, FALSE);
			repetir = TRUE;
			getch();
		}
		else if(o->problema > 5){
			barra_sup(37, 1, 17);
			printf("\t\t\t\xBA   DESCULPA! MAS, TEM MUITOS PROBLEMAS  \xBA\n");
			barra_inf(40, FALSE);
			repetir = TRUE;
			getch();
		}
		else{
			o->valor_de_ordem = o->semestre + (o->problema/100);
			return o;
		}
	}while(repetir == TRUE);
}
//=======================================================================================================================================================================================
Problema* ler_ti_e_dis(Problema* o_novo){
	
	
	printf("\n\n");
	fflush(stdin);
	printf("TITULO DO PROBLEMA: ");
	gets(o_novo->titulo);
	fflush(stdin);
	printf("DISCRITIVO DO PROBLEMA: ");
	gets(o_novo->discritivo);
	
	system("cls");
	printf("Ano: %d\n", o_novo->ano);
	printf("Problema: %.0lf\n", o_novo->problema);
	printf("Semestre: %.1f\n", o_novo->semestre);
	printf("Titulo: %s\n", o_novo->titulo);
	printf("Discritivo: %s\n", o_novo->discritivo);
	
	system("pause");
}
//=====================================================================================================================================================================================
void imprimir_ordenado(Problema* l){
	Problema *o = l;
	int i = 0;
	//setlocale(LC_ALL, "");

	while(o->prox_problema != NULL){
		printf("============================================CELULA DE N %d====================================================\n\n", i+1);
		i++;
		printf("Ano: %d\n", o->ano);
		printf("Problema: %.0lf\n", o->problema);
		printf("Semestre: %.1f\n", o->semestre);
		printf("Titulo: %s\n", o->titulo);
		printf("Discritivo: %s\n", o->discritivo);
		o = o->prox_problema;
		printf("=============================================================================================================\n\n");
		system("pause");
	}
}
//=====================================================================================================================================================================================
int buscar_menu(){//Fun??o responsavel por gerar um menu de busca.
	int resposta = 0;
	do{
		barra_sup(19, 7, 9);
		pula_espaco(4, 0);
		printf("\t\t\t\xBA   BUSCAR POR ANO________(01)  \xBA\n");
		printf("\t\t\t\xBA   BUSCAR POR SEMESTRE___(02)  \xBA\n");
		printf("\t\t\t\xBA   BUSCAR POR PROBLEMA___(03)  \xBA\n");
		pula_espaco(4, 0);
		printf("\t\t\t\xBA   VOLTAR________________(04)  \xBA\n");
		barra_inf(31, TRUE);
		scanf("%d", &resposta);
		if (resposta < 1 || resposta > 4)
			printf("ESCOLHA INVALIDA! TENTE NOVAMENTE!\n");
	}while(resposta < 1 || resposta > 4);
	return resposta;
}
//=====================================================================================================================================================================================
void gotoxy(int x, int y){//Fun??o utilizada para selecionar o lugar que o cursor deve ficar no terminal com base na posi??o X e Y.
  COORD c;
  c.X = x - 1;
  c.Y = y - 1;
  SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), c);
}
//=====================================================================================================================================================================================
void barra_sup(int tamanho, int titulo, int meio){//Fun??o responsavel por fazer uma borda superior; EX: T-------------------T
	int i = 0;
	printf("\t\t\t\xC9");
	for(i = 0; i<tamanho; i++){
		if (i == meio){
			if(titulo == 1)
				printf("ERRO");
			else if(titulo == 2)
				printf("ERRO SINTATICO");
			else if(titulo == 3)
				printf("\xCD\xCD\xCDRELATORIO\xCD\xCD");
			else if(titulo == 4)
				printf("MENU PRINCIPAL");
			else if(titulo == 5)
				printf("AVISO");
			else if(titulo == 6)
				printf("CARREGAR ARQUIVO");
			else if(titulo == 7)
				printf("MENU DE BUSCA");
			else
				printf("\xCD");
		}
		else
			printf("\xCD");
	}
	printf("\xBB\n");
}
//========================================================================================================================================================================================
void pula_espaco(int tab, int espaco){//Fun??o responsabel por fazer dois tra?os separado. EX: "|            |"

	int i = 0;
	printf("\t\t\t\xBA");
	for (i = 0; i < tab; i++)
		printf("\t");
	if(espaco != 0){
		for(i = 0; i < espaco; i++)
			printf(" ");
	}
	printf("\xBA\n");
}
//========================================================================================================================================================================================
void barra_inf(int tamanho, int resposta){//Fun??o responsvel por fazer uma borda inferior. EX: |________________|
	int i = 0;
	printf("\t\t\t\xC8");
	for(i = 0; i < tamanho; i++)
		printf("\xCD");
	printf("\xBC\n");
	if(resposta == TRUE)
		printf("\t\t\t>>> ");
}
//======================================================================================================================================================================================
int tentar_novamente(){//responsavel por imprimir uma messagem de erro.
	int resposta = 0, i = 0;

	do{
		barra_sup(56, 5, 28);
		printf("\t\t\t\xBA\t      Gostaria e tentar com outro arquivo?\t     \xBA\n");
		pula_espaco(7, 5);
		printf("\t\t\t\xBA\t\tSIM___(01)           NAO___(02)\t\t     \xBA\n");
		barra_inf(60, TRUE);
		scanf("%d", &resposta);
		fflush(stdin);

		if (resposta == 1)
			return TRUE;
		else if(resposta == 2)
			return FALSE;
		else{
			system("cls");
			barra_sup(56, 5, 28);
			printf("\t\t\t\xBA\t\tEscolha invalida! Tente novamente!\t     \xBA\n");
			barra_inf(60, FALSE);
		}
	}while(resposta < 1 || resposta > 2);
}
//=====================================================================================================================================================================================
int deve_sair(){//Fun??o responsavel por gerar uma mensagem de saida.
	int resposta = 0;
	do{
		barra_sup(27, 5, 13);
		pula_espaco(4, 0);
		printf("\t\t\t\xBA    DESEJA REALMENTE SAIR?     \xBA\n");
		printf("\t\t\t\xBA    SIM___(01) | NAO___(02)    \xBA\n");
		pula_espaco(4, 0);
		barra_inf(31, TRUE);
		scanf("%d", &resposta);
		fflush(stdin);
		if (resposta == 1){
			return TRUE;
		}
		else if(resposta == 2){
			return FALSE;
		}
		else{
			printf("\nESCOLHA INVALIDA! TENTE NOVAMENTE!\n");
		}
	}while(resposta < 1 || resposta > 2);
}
//=====================================================================================================================================================================================
void saindo(){
	int  i = 0;

	system("cls");
	for (i = 0; i < 14; i++)//desce 14 linhas
		printf("\n");
	for (i = 0; i < 2; i++)//centraliza o texto
		printf("\t");
	barra_sup(28, 0, 0);
	for (i = 0; i < 5; i++)//centraliza o texto
		printf("\t");
	printf("\a\xBA\t>Ate a proxima<      \xBA\n");//mensagem de at? a proxima
	for (i = 0; i < 2; i++)
		printf("\t");
	barra_inf(28, FALSE);
	for (i = 0; i < 14; i++)
		printf("\n");
	system("exit");
}
