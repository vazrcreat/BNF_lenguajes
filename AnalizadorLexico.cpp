#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <string>
#include <ctype.h>
#include <fstream>
#include <iostream>
#define MAX 650
#define MAX_RES 23
#define TAM_BUFFER 100

class Analiza{
	char *nombreFichero; //Nombre del fichero fuente
	FILE* entrada; //Fichero de entrada
	int n1; //Numero de linea
	int traza; //control de traza
	char buffer[TAM_BUFFER]; //Buffer auxiliar de caracteres
	int pBuffer; // Posicion en el buffer
	
	public:
		Analiza(char *unNombreFichero, int una_traza=0);
		~Analiza(void);
		char siguienteToken(void);
		void devuelveToken(char token);
		int lineaActual(void){return n1;};
		int existeTraza(void){if(traza) return 1; else return 0;};
};

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
		case' ':
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
