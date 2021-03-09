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
	double problema;
	int ano;
	char titulo[250];
	char discritivo[500];

	double valor_de_ordem;
	struct problema *prox_problema;

}Problema;

//====================SESSÃO DECLARAÇÃO DE FUNÇÕES.==================
	int menu_principal();
	void recebe_nome();
	int verifica_se_vazio();
	int cont_linha();
	Problema* preencher_celula();
	Problema* insere_ordenado();
	Problema* ler_ano();
	Problema* ler_semestre();
	Problema* ler_problema();
	Problema* ler_ti_e_dis();
	void listar_por_ano();
	void listar_por_semestre();
	void imprimir_ordenado();
	int menu_buscar();
	void exibir_conteudo();

//====================FUNÇÕES DE DESING ACOPLADAS====================
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
	Problema *novo_problema = NULL;
	Problema *l = NULL;

	//system("mode con:cols=105 lines=30");
	do{
		repetir_arquivo = FALSE;
		recebe_nome(arquivo);
		if(verifica_se_vazio(arquivo) == TRUE){
			if(tentar_novamente()){
				repetir_arquivo = TRUE;
				system("cls");
			}
			else if(deve_sair())
				saindo();
			else{
				repetir_arquivo = TRUE;
				system("cls");
			}
		}
		else{
			qtd_linhas = cont_linha(arquivo);
			FILE *f1 = fopen(arquivo, "r");//Abre o arquivo no modo de leitura.
			for(i = 0; i < qtd_linhas; i++){
				novo_problema = preencher_celula(f1);
				l = insere_ordenado(l, novo_problema);
			}
			fclose(f1);
			do{
				repetir_menu_principal = FALSE;
				switch(menu_principal()){
					case 1:{
						imprimir_ordenado(l);
						repetir_menu_principal = TRUE;
						break;
					}
					case 2:{
						int inserir_novo_prob = FALSE;
						do{
							inserir_novo_prob = FALSE;
							novo_problema = (Problema *) malloc(sizeof(Problema));
							
							novo_problema = ler_ano(novo_problema);
							novo_problema = ler_semestre(novo_problema);
							novo_problema = ler_problema(novo_problema);
							novo_problema = ler_ti_e_dis(novo_problema);
							
							l = insere_ordenado(l, novo_problema);
							switch(tentar_novamente()){
								case 0:{
									repetir_menu_principal = TRUE;
									break;
								}
								case 1:{
									inserir_novo_prob = TRUE;
									break;
								}
							}
						}while(inserir_novo_prob == TRUE);
						break;
					}
					case 3:{
						switch(buscar_menu()){
							case 1:{
								listar_por_ano(l);
								repetir_menu_principal = TRUE;
								system("pause");
								break;
							}
							case 2:{
								listar_por_semestre(l);
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
						 if(deve_sair())
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
	gotoxy(54, 3);//função usada para mover o cursor.
	gets(arquivo);
	system("cls");
}
//======================================================================================================================================================================================
int verifica_se_vazio(char arquivo[]){//RESPONSAVEL POR VERIFICAR SE O ARQUIVO EXISTE E SE ELE É VALIDO.

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
	int quant = 0;//serve para como um contador. pois, é incrementado 1 a cada linha do arquivo.
	FILE *arquivo = fopen(arq, "r");

	while((ch = getc(arquivo))!= EOF){//Repita enquanto não chegar no final do arquivo.
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
	o->valor_de_ordem = o->semestre + (o->problema /100);//nesse momento o valor do problema é somado com o valor do semestre. e assim gerando um novo numero que vai ser utilado 
														//para a ordenação. exemplo: semestre 2016.1 problema: 2 == valor de ordem = 2016.12;
	return o;
}
//==============================================================================================================================================================================
Problema* insere_ordenado(Problema* l, Problema* o_novo){
	
	if(l == NULL){//verifica se a lista esta vazia;
		l = (Problema *) malloc(sizeof(Problema)); //se tiver vazia, "l" tem o espaço alocado dinamicamente.
		l = o_novo;
		o_novo->prox_problema = NULL;
		return l;
	}
	if(l != NULL && o_novo->valor_de_ordem > l->valor_de_ordem){
		o_novo->prox_problema = l;
		l = o_novo;
		return l;
	}
	Problema* atual = l;
	Problema* anterior = l;
	while(atual != NULL){
		if(o_novo->valor_de_ordem > atual->valor_de_ordem)
			break;
		anterior = atual;
		atual = atual->prox_problema;
	}
	o_novo->prox_problema = atual;
	anterior->prox_problema = o_novo;
	return l;
}
//======================================================================================================================================================================================
int menu_principal(){//Função responsavel por gerar o menu pricipal.
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
	int resposta = 0;
	do{
		repetir = FALSE;
		barra_sup(40, FALSE, FALSE);
		printf("\t\t\t\xBA\t     QUAL E O SEMESTRE\t\t \xBA\n");
		pula_espaco(5, 1);
		printf("\t\t\t\xBA      %d_(1)  \t   %d_(2)      \xBA\n", o->ano, o->ano);
		barra_inf(40, TRUE);
		scanf("%d", &resposta);
		fflush(stdin);
		if(resposta == 1)
			o->semestre = o->ano + 0.1;
		else if(resposta == 2)
			o->semestre = o->ano + 0.2;
		else{
			system("cls");
			barra_sup(37, 1, 17);
			printf("\t\t\t\xBA  SEMESTRE INVALIDO! TENTE NOVAMENTE !  \xBA\n");
			barra_inf(40, FALSE);
			repetir = TRUE;
			getch();
		}
	}while(repetir == TRUE);
	return o;
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
		scanf("%lf", &o->problema);
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
			printf("%.2lf :: %lf ", o->valor_de_ordem, (o->problema/100));
			getch();
			return o;
		}
	}while(repetir == TRUE);
}
//=======================================================================================================================================================================================
Problema* ler_ti_e_dis(Problema* o){
	
	
	printf("\n\n");
	fflush(stdin);
	printf("TITULO DO PROBLEMA: ");
	gets(o->titulo);
	fflush(stdin);
	printf("DISCRITIVO DO PROBLEMA: ");
	gets(o->discritivo);
	
	system("cls");
	printf("Ano: %d\n", o->ano);
	printf("Problema: %.0lf\n", o->problema);
	printf("Semestre: %.1f\n", o->semestre);
	printf("Titulo: %s\n", o->titulo);
	printf("Discritivo: %s\n", o->discritivo);
	return o;

}
//=====================================================================================================================================================================================
void imprimir_ordenado(Problema* l){
	Problema *o = l->prox_problema;
	int i = 0;
	setlocale(LC_ALL, "");

	do{
		printf("============================================CELULA DE N %d====================================================\n\n", i+1);
		i++;
		printf("Ano: %d\n", o->ano);
		printf("Problema: %.0lf\n", o->problema);
		printf("Semestre: %.1f\n", o->semestre);
		printf("Titulo: %s\n", o->titulo);
		printf("Discritivo: %s\n", o->discritivo);
		o = o->prox_problema;
		printf("\n\n=============================================================================================================\n\n");
	}while(o != NULL);
}
//=====================================================================================================================================================================================
int buscar_menu(){//Função responsavel por gerar um menu de busca.
	int resposta = 0;
	do{
		barra_sup(19, 7, 9);
		pula_espaco(4, 0);
		printf("\t\t\t\xBA   LISTAR POR ANO________(01)  \xBA\n");
		printf("\t\t\t\xBA   LISTAR POR SEMESTRE___(02)  \xBA\n");
		printf("\t\t\t\xBA   LISTAR POR PROBLEMA___(03)  \xBA\n");
		pula_espaco(4, 0);
		printf("\t\t\t\xBA   VOLTAR________________(04)  \xBA\n");
		barra_inf(31, TRUE);
		scanf("%d", &resposta);
		if (resposta < 1 || resposta > 4){
			system("cls");
			barra_sup(27, 5, 14);
			printf("\t\t\t\xBA\tEscolha invalida!\t\xBA\n");
			printf("\t\t\t\xBA\tTente novamente! \t\xBA\n");
			barra_inf(31, FALSE);
		}
	}while(resposta < 1 || resposta > 4);
	return resposta;
}
//=====================================================================================================================================================================================
void listar_por_ano(Problema* l){
	int ano_digitado = 0, numero_de_problema = 0;;
	Problema* o = l->prox_problema;
	
	do{
		system("cls");
		printf("DIGITE O ANO DO PROBLEMA QUE DESEJA BUSCAR: ");
		scanf("%d", &ano_digitado);
		fflush(stdin);
		if(ano_digitado < 2003 || ano_digitado > 2018){
			barra_sup(32, 1, 16);
			printf("\t\t\t\xBA DIGITE UM VALOR ENTRE 2003 E 2018 \xBA\n");
			barra_inf(35, FALSE);
			getch();
		}
		else{
			while(o != NULL){
				if(o->ano == ano_digitado){
					printf("Ano: %d\n", o->ano);
					printf("Problema: %.0lf\n", o->problema);
					printf("Semestre: %.1f\n", o->semestre);
					printf("Titulo: %s\n", o->titulo);
					printf("Discritivo: %s\n\n", o->discritivo);
					numero_de_problema++;
					o = o->prox_problema;
				}
				else if(o->prox_problema == NULL && numero_de_problema == 0){
					printf("\t\t\t\xBA NENHUM PROBLEMA ENCONTRADO \xBA");
					o = NULL;
				}
				else
					o = o->prox_problema;
			}		
		}
	}while(ano_digitado < 2003 || ano_digitado > 2018);	
	
	getch();
}
//=====================================================================================================================================================================================
void listar_por_semestre(Problema* l){
	double semestre_digitado = 0;
	int repetir = FALSE;
	do{	
		repetir = FALSE;
		system("cls");
		printf("DIGITE O SEMESTRE: \n");
		printf("EX: 2017.1");
		gotoxy(20, 1);
		scanf("%lf", &semestre_digitado);
		fflush(stdin);
		printf("%lf", semestre_digitado);
		getch();
	}while(repetir == TRUE);
}
//=====================================================================================================================================================================================
void gotoxy(int x, int y){//Função utilizada para selecionar o lugar que o cursor deve ficar no terminal com base na posição X e Y.
  COORD c;
  c.X = x - 1;
  c.Y = y - 1;
  SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), c);
}
//=====================================================================================================================================================================================
void barra_sup(int tamanho, int titulo, int meio){//Função responsavel por fazer uma borda superior; EX: T-------------------T
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
void pula_espaco(int tab, int espaco){//Função responsabel por fazer dois traços separado. EX: "|            |"

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
void barra_inf(int tamanho, int resposta){//Função responsvel por fazer uma borda inferior. EX: |________________|
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
		printf("\t\t\t\xBA\t      Gostaria de tentar novamente ?\t\t     \xBA\n");
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
int deve_sair(){//Função responsavel por gerar uma mensagem de saida.
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
	printf("\a\xBA\t>Ate a proxima<      \xBA\n");//mensagem de até a proxima
	for (i = 0; i < 2; i++)
		printf("\t");
	barra_inf(28, FALSE);
	for (i = 0; i < 14; i++)
		printf("\n");
	system("exit");
}
