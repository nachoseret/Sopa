// Sopa de letras
// Ignacio Seret - Joaquin Manuel

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "rumpelstinski.c"

void clear(){
	system("clear"); // Cambiar clear por cls si se quiere correrlo en Windows
}

int main()
{
	int i, op;
	clear();
	printf("Sopa de letras\nJoaquin Manuel - Ignacio Seret\nLeer de archivo?\n1 - Si\n2 - No (Ingreso por teclado)\n");
	scanf("%d",&op);
	while(!(op==1||op==2)){
		clear();
		printf("Sopa de letras\nJoaquin Manuel - Ignacio Seret\nLeer de archivo?\n1 - Si\n2 - No (Ingreso por teclado)\n");
		printf("Ingrese una opcion valida.\n");
		scanf("%d",&op);
	}
	if(op==1){
		char * nombreArchivo;
		nombreArchivo = malloc(sizeof(char)*100);
		printf("Nombre del archivo=");
		scanf("%s",nombreArchivo);
		if(freopen(nombreArchivo,"r",stdin)==NULL){
			printf("Archivo no encontrado.\n");
			return 0;
		}
		free(nombreArchivo);
	}
	clear();
	Matriz * sopa = leerSopa();
	clear();
	mostrarSopa(*sopa);
	Universo * a = leerUniverso();
	printf("\n");
	clear();
	mostrarSopa(*sopa);
	for(i=0; i<a->tamanioUniverso; i++){
		mostrarPalabra(a->palabras[i],estaEn(*sopa,a->palabras[i]));
	}
	return 0;
}