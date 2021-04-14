#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <string>
#include <iostream>
#define MAX 650
#define MAX_RES 23
#define TAM_BUFFER 100

using namespace std;

char *PalabrasReservadas[MAX_RES] = {"si","entonces","sino","entero","decimal","logico","texto","char","mientras","haga","repita",
"hasta","var","como","verdadero","falso","declare","inicie","termine","lea","imprima","rompa","nop"};
char *p;
char tokenSimbolos[MAX];
char auxWord[MAX];	//Una variable auxiliar para guardar dos veces la palabra(token) que se vaya formando
string tokenNumeros[MAX];
string tokenIdentificadores[MAX];
string tokenReservadas[MAX];
string tokensNoValidos[MAX];
bool esNumero=true;
bool esIdentificador = true;

//Variables auxiliares para guardar en Tokens
int auxTR=0;
int auxTI=0;
int auxTN=0;
int auxTNV=0;

//Los diferentes procedimientos que se desarrollaran en el programa y llamaran en su momento desde el metodo main()
bool verificarNumero(char palabra[]);
bool verificarIdentificador(char palabra[]);
bool verificarReservada(char palabra[]);
void imprimirTokenNumeros();
void imprimirTokenSimbolos();
void imprimirTokenReservadas();
void imprimirTokenIdentificadores();
void imprimirIdentificadoresNoValidos();

Analiza::Analiza(char *unNombreFichero, int una_traza){
	entrada= fopen(unNombreFichero, "r+");
	if((entrada==NULL)){
		cout<<"No se puede abrir el archivo"<<endl;
		system("pause");
		exit(-2);
	}
	
	if(una_traza) traza=1;
	else traza =0;
	n1=1; // se inicializa el contador de línea
	pBuffer=0;//Se inicializa la posicion del buffer
}

Analiza::~Analiza(){
	fclose(entrada);
}

char Analiza::siguienteToken(void){
	char car;
	while((car=((pBuffer>0)? buffer[--pBuffer]:getc(entrada)))!=EOF){
		if(car==' ') continue;
		if(car=='\n'){++n1; continue;}
		break;
	}
	
	if(traza) cout<<"ANALIZADOR LEXICO: Lee el token "<<car<<endl;
	
	switch(car){
		case' ': // Palabra reservada
		return(car);
		}
		
		if(islower(car)) return(car);//variable
		else if (isdigit(car)) return(car);//constante
		else{
			cout<<"Error Lexico: Token Desconocido "<<endl;
			system("pause");
			exit(-4);
		}
		return(car);
}

void Analiza::devuelveToken(char token){
	if(pBuffer>TAM_BUFFER){
		cout<<"Error: Desbordamiento del buffer del analizador lexico "<<endl;
		system("pause");
		exit(-5);
	}else{
		buffer[pBuffer++]=token;
		if(existeTraza())
		cout<<"ANALIZADOR LEXICO: Recibe en buffer el token "<<token<<endl;
		system("pause");
	}
}

int main(int argc, char** argv){
	int traza;
	char token;
	
	Analiza obj("commandos.txt",1);
	
	if(obj.existeTraza())
	cout<<"INICIO DE ANALISIS"<<endl;
	
	while((token=obj.siguienteToken())!='}')
	cout<<token<<endl;
	
	system("pause");
	return 0;
}
