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
	int menu_buscar();
	void exibir_conteudo();
//====================FUNÇÕES DE DESING ACOPLADAS====================
	void gotoxy();
	void barra_sup();
	void pula_espaco();
	void barra_inf();
	int mensagem_saida();
//========================STRUCTS UTILIZADAS=========================
typedef struct arvore *Arvore;
struct arvore{

	int ano;
	int semestre;
	int problema;
	char titulo[80];
	char discritivo[250];
	
	Arvore *folha_esquerda;
	Arvore *folha_direita;

};	

int main(){
	char arquivo[50];
	int repetir_menu_principal = FALSE;
	
	recebe_nome(arquivo);
	
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
				repetir_menu_principal = mensagem_saida();	
				break;
			}
			default:{
				printf("ALGO DE ERRADO NAO ESTA CERTO!\n");
				printf("SE VOCE ESTA VENDO ESSA MENSAGEM VOCE ER FODA.\n");
				printf("ACREDITE NAO ERA PARA VOCE ESTA VENDO ESSA MENSAGEM\n");
				printf("VAMOS SER AMIG@S!\n MANDA UM EMAIL PARA MIM.\n");
				printf("EMAIL: UELLINGTON99@GMAIL.COM\n");
				printf("ASSUNTO: ESTER EGG - SEU NOME\n");
				printf("APROVEITA E ME DIZ COMO CHEGOU ATE AKI\n");
				printf("PS: NAO VALE PELO CODIGO FONTE.\n");
				printf("\n\nPOR QUESTAO DE SEGURANCA O SOFTWARE SERA FINALIZADO\n");
				system("exit");
				break;
			}
		}
	}while(repetir_menu_principal == TRUE);
}
//======================================================================================================================================================================================
void recebe_nome(char arquivo[50]){
	barra_sup(32, 6, 16);
	pula_espaco(6);
	printf("\t\t\t\xBA  DIGITE O NOME DO ARQUIVO:\t\t\t\xBA");
	printf("\n");
	barra_inf(47);
	gotoxy(54, 3);//função usada para mover o cursor.
	gets(arquivo);
	system("cls");
}
//======================================================================================================================================================================================
int menu_principal(){
	setlocale(LC_ALL, "C");
	int resposta = 0;
	do{
		barra_sup(18, 4, 9);
		pula_espaco(4);
		printf("\t\t\t\xBA  VERIFCAR CONTEUDO______(01)  \xBA\n");
		printf("\t\t\t\xBA  ADICIONAR PROBLEMA_____(02)  \xBA\n");
		printf("\t\t\t\xBA  BUSCAR NO ARQUIVO______(03)  \xBA\n");
		printf("\t\t\t\xBA  GERAR NOVO ARQUIVO_____(04)  \xBA\n");
		pula_espaco(4);
		printf("\t\t\t\xBA  SAIR___________________(05)  \xBA\n");
		pula_espaco(4);
		barra_inf(31);
		scanf("%d", &resposta);
		fflush(stdin);
		if (resposta < 1 || resposta > 5)
			printf("\nESCOLHA INVALIDA! TENTEN NOVAMENTE!\n");
	}while(resposta < 1 || resposta > 5);
	return resposta;
}
//=====================================================================================================================================================================================
int buscar_menu(){
	int resposta = 0;
	do{
		barra_sup(24, 7, 12);
		pula_espaco(4);
		printf("\t\t\t\xBA   BUSCAR POR ANO________(01)  \xBA\n");
		printf("\t\t\t\xBA   BUSCAR POR SEMESTRE___(02)  \xBA\n");
		printf("\t\t\t\xBA   BUSCAR POR PROBLEMA___(03)  \xBA\n");
		pula_espaco(4);
		printf("\t\t\t\xBA   VOLTAR________________(04)  \xBA\n");
		barra_inf(31);
		scanf("%d", &resposta);
		if (resposta < 1 || resposta > 4)
			printf("ESCOLHA INVALIDA! TENTE NOVAMENTE!");
	}while(resposta < 1 || resposta > 4);
	return resposta;
}
//=====================================================================================================================================================================================
void exibir_conteudo(char arquivo[50]){
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
void gotoxy(int x, int y) {
  COORD c;
  c.X = x - 1;
  c.Y = y - 1;
  SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), c);
}
//=====================================================================================================================================================================================
void barra_sup(int tamanho, int titulo, int meio){
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
				printf("SUB-MENU");
			else				
				printf("\xCD");
		}
		else
			printf("\xCD");
	}
	printf("\xBB\n");
}
//========================================================================================================================================================================================
void pula_espaco(int tamanho){
	
	int i = 0;
	
	printf("\t\t\t\xBA");
	for (i = 0; i , i < tamanho; i++)
		printf("\t");
	printf("\xBA\n");
}
//========================================================================================================================================================================================
void barra_inf(int tamanho){
	int i = 0;
	printf("\t\t\t\xC8");
	for(i = 0; i < tamanho; i++)
		printf("\xCD");
	printf("\xBC\n");
}
//======================================================================================================================================================================================
int mensagem_saida(){
	int i = 0, resposta = 0;
	do{
		barra_sup(27, 5, 13);
		pula_espaco(4);
		printf("\t\t\t\xBA    DESEJA REALMENTE SAIR?     \xBA\n");
		printf("\t\t\t\xBA    SIM___(01) | NAO___(02)    \xBA\n");
		pula_espaco(4);
		barra_inf(31);
		scanf("%d", &resposta);
		fflush(stdin);
		if (resposta == 1){
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
		return 0;
		}
		else if(resposta == 2){
			return TRUE;
		}
		else{
			printf("\nESCOLHA INVALIDA! TENTE NOVAMENTE!\n");
		}
	}while(resposta < 1 || resposta > 2);
}
