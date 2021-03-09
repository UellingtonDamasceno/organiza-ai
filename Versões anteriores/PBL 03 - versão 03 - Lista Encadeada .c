#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <locale.h>
#define TRUE 1
#define FALSE 0
//====================SESSÃO DECLARAÇÃO DE FUNÇÕES.==================
	int menu_principal();
	void recebe_nome();
	int verifica_se_vazio();
	void carregar_conteudo();
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
//========================STRUCT UTILIZADA=========================

typedef struct info{
	
	float semestre;
	int problema;
	int ano;
	char titulo[500];
	char discritivo[500];
	
	struct info *prox_info;

}Problema;

int main(){
	char arquivo[50];
	int repetir_menu_principal = FALSE;
	int repetir_arquivo = FALSE;
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
		
			//system("pause");
			carregar_conteudo(arquivo);
			do{
				repetir_menu_principal = FALSE;
				switch(menu_principal()){
					case 1:{
						exibir_conteudo(arquivo);			
						repetir_menu_principal = TRUE;
						break;
					}
					case 2:{
						printf("ADICIONAR PROBLEMA\n");
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
	barra_inf(47);
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
		barra_inf(60);
		return TRUE;
	}
	else
		return FALSE;
	fclose (numero_de_linha);
}
//======================================================================================================================================================================================
void carregar_conteudo(char arq[]){
	//setlocale(LC_ALL, "portuguese");
	int cont_tamanho = 0;
	char ch;
	FILE *pegar_no_arq = fopen(arq, "r");
	
	Problema *o;
	while(ch = (fgetc(pegar_no_arq))!=EOF){
	o = (Problema*) malloc(sizeof(Problema));
	
	fscanf(pegar_no_arq, "%f", &o->semestre);
	fscanf(pegar_no_arq, "%d", &o->problema);
	fscanf(pegar_no_arq, "%d", &o->ano);
	fscanf(pegar_no_arq, "%[^\t]s", o->titulo);
	fscanf(pegar_no_arq, "%[^\n]s", o->discritivo);
	
	printf("Ano: %d\n", o->ano);
	printf("Problema: %d\n", o->problema);
	printf("Semestre: %.1f\n", o->semestre);
	printf("Titulo: %s\n", o->titulo);
	printf("Discritivo: %s\n", o->discritivo);	
	}
	fclose(pegar_no_arq);
	system("pause");
}	
//======================================================================================================================================================================================
int menu_principal(){//Função responsavel por gerar o menu pricipal.
	setlocale(LC_ALL, "C");
	int resposta = 0;
	do{
		barra_sup(18, 4, 9);
		pula_espaco(4, 0);
		printf("\t\t\t\xBA  VERIFCAR CONTEUDO______(01)  \xBA\n");
		printf("\t\t\t\xBA  ADICIONAR PROBLEMA_____(02)  \xBA\n");
		printf("\t\t\t\xBA  BUSCAR NO ARQUIVO______(03)  \xBA\n");
		printf("\t\t\t\xBA  GERAR NOVO ARQUIVO_____(04)  \xBA\n");
		printf("\t\t\t\xBA  TENTAR OUTRO ARQUIVO___(05)  \xBA\n");
		pula_espaco(4, 0);
		printf("\t\t\t\xBA  SAIR___________________(06)  \xBA\n");
		pula_espaco(4, 0);
		barra_inf(31);
		scanf("%d", &resposta);
		fflush(stdin);
		if (resposta < 1 || resposta > 6)
			printf("\nESCOLHA INVALIDA! TENTEN NOVAMENTE!\n");
	}while(resposta < 1 || resposta > 6);
	return resposta;
}
//=====================================================================================================================================================================================
int buscar_menu(){//Função responsavel por gerar um menu de busca.
	int resposta = 0;
	do{
		barra_sup(19, 7, 9);
		pula_espaco(4, 0);
		printf("\t\t\t\xBA   BUSCAR POR ANO________(01)  \xBA\n");
		printf("\t\t\t\xBA   BUSCAR POR SEMESTRE___(02)  \xBA\n");
		printf("\t\t\t\xBA   BUSCAR POR PROBLEMA___(03)  \xBA\n");
		pula_espaco(4, 0);
		printf("\t\t\t\xBA   VOLTAR________________(04)  \xBA\n");
		barra_inf(31);
		scanf("%d", &resposta);
		if (resposta < 1 || resposta > 4)
			printf("ESCOLHA INVALIDA! TENTE NOVAMENTE!");
	}while(resposta < 1 || resposta > 4);
	return resposta;
}
//=====================================================================================================================================================================================
void exibir_conteudo(char arquivo[]){
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
void gotoxy(int x, int y) {//Função utilizada para selecionar o lugar que o cursor deve ficar no terminal com base na posição X e Y.
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
				printf("ERRO SEMANTICO");
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
void barra_inf(int tamanho){//Função responsvel por fazer uma borda inferior. EX: |________________|
	int i = 0;
	printf("\t\t\t\xC8");
	for(i = 0; i < tamanho; i++)
		printf("\xCD");
	printf("\xBC\n");
}
//======================================================================================================================================================================================
int tentar_novamente(){//responsavel por imprimir uma messagem de erro. 
	int resposta = 0, i = 0;
	
	do{
		barra_sup(56, 5, 28);
		printf("\t\t\t\xBA\t      Gostaria e tentar com outro arquivo?\t     \xBA\n");
		pula_espaco(7, 5);
		printf("\t\t\t\xBA\t\tSIM___(01)           NAO___(02)\t\t     \xBA\n");
		barra_inf(60);
		printf("\t\t\t>>> ");
		scanf("%d", &resposta);
		fflush(stdin);
	
		if (resposta == 1)
			return TRUE;
		else if(resposta == 2)
			return FALSE;
		else{
			barra_sup(47, 5, 23);
			printf("\xBA\t\tEscolha invalida! Tente novamente!\t     \xBA\n");
			barra_inf(60);
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
		barra_inf(31);
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
	barra_inf(28);
	for (i = 0; i < 14; i++)
		printf("\n");
	system("exit");
}
