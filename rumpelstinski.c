// Sopa de letras
// Joaquin Manuel - Ignacio Seret

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Representamos a la sopa de letras como una estructura Matriz que consta de dos
// variables enteras, que representan la cantidad de Filas y Columnas respectivamente;
// y una matriz de dos dimensiones (de tipo char**) que guarda la sopa de letras.
typedef struct matriz{
	int numeroFilas, numeroColumnas;
	char** cuerpo;
}Matriz;

// Representamos al universo de palabras como una estructura Universo que consta de una
// variable entera, que representan la cantidad de palabras; y una matriz de dos dimensiones
// (de tipo char**) que guarda las palabras a encontrar.
typedef struct universo{
	int tamanioUniverso;
	char** palabras;
}Universo;

// leerSopa : None -> Matriz *
// leerSopa pide por stdin la cantidad de filas y columnas de la sopa, para luego pedir el
// ingreso de todas las filas en su correspondiente orden. Luego, pide memoria para almacenar
// estos datos en una estructura de tipo Matriz. La funcion retorna la direccion donde se
// encuentra la Matriz con los datos.
Matriz * leerSopa(){
	Matriz *lectura;
	int i,j,col=10,fil=20;
	char buffer[100];
	printf("numeroColumnas=");
	scanf("%d",&col);
	printf("numeroFilas=");
	scanf("%d",&fil);
	lectura = malloc(sizeof(Matriz));
	lectura->numeroFilas=fil;
	lectura->numeroColumnas=col;
	lectura->cuerpo = malloc(fil*sizeof(char*));
	printf("Ingrese las filas sin espacios. Presione enter para una nueva fila.\n");
	for(i=0; i<fil; i++){
		lectura->cuerpo[i] = malloc((col+1)*sizeof(char));
		scanf("%s",buffer);
		for(j=0; j<col; j++) lectura->cuerpo[i][j] = toupper(buffer[j]);
		lectura->cuerpo[i][col]='\0';
	}
	return lectura;
}

// leerUniverso : None -> Universo *
// leerUniverso pide por stdin la cantidad de palabras del mismo, para luego pedir el
// ingreso de todas ellas en su correspondiente orden. Luego, pide memoria para almacenar
// estos datos en una estructura de tipo Universo. La funcion retorna la direccion donde se
// encuentra el Universo con los datos.
Universo * leerUniverso(){
	Universo *lectura;
	int i, j;
	lectura = malloc(sizeof(Universo));
	char buffer[100];
	printf("tamanioUniverso=");
	scanf("%d",&(lectura->tamanioUniverso));
	lectura->palabras=malloc(lectura->tamanioUniverso*sizeof(char*));
	for(i=0; i<lectura->tamanioUniverso; i++){
		printf("%d.",i);
		scanf("%s",buffer);
		lectura->palabras[i]=malloc(sizeof(char)*(strlen(buffer)+1));
		for(j=0;j<strlen(buffer);j++) buffer[j]=toupper(buffer[j]);
		strcpy(lectura->palabras[i],buffer);
	}
	return lectura;
}

// pertenece : int, int, Matriz -> int
// pertenece toma como argumentos dos enteros que representan una posicion
// y una estructura de tipo Matriz. En caso que la posicion pertenezca a la
// Matriz, retorna 1. Caso contrario, retorna 0.
 
int pertenece(int y, int x, Matriz sopa){
	if(x>=sopa.numeroColumnas || x<0) return 0;
	if(y>=sopa.numeroFilas || y<0) return 0;
	return 1;
}

// estaEnDir : Matriz, string, int, int, int, int -> int
// estaEnDir toma como argumentos una estructura de tipo Matriz, una palabra (string) y cuatro enteros
// que representan una posicion (x,y) en la matriz y un vector v=(Dx,Dy) que es la direccion en la que
// se quiere buscar la palabra. Retorna 1 si la palabra se encuentra en direccion a v con su primer
// letra en el punto (x,y). Caso contrario, retorna 0.
int estaEnDir(Matriz sopa, char palabra[], int y, int x, int Dy, int Dx){
	int i, len;
	x+=Dx;
	y+=Dy;
	len = strlen(palabra);
	for(i=1; i<len; i++){
		if(palabra[i]!=sopa.cuerpo[y][x]){
			return 0;
		}
		x+=Dx;
		y+=Dy;
	}
	return 1;
}

// estaEn : Matriz, string -> int
// estaEn toma como argumentos una estructura de tipo Matriz y una palabra (string). La funcion busca
// la palabra en la Matriz. En caso que la encuentre, retorna un entero del 0 al 7 que representa la
// direccion en la que esta la palabra. En caso que la palabra no este en la Matriz, se retorna -1.
int estaEn(Matriz sopa, char palabra[]){
	int dir_y[8]={0,1,1,1,0,-1,-1,-1}, dir_x[8]={1,1,0,-1,-1,-1,0,1}, i, j, k, len;
	len = strlen(palabra)-1;
	for(i=0; i<sopa.numeroFilas; i++){
		for(j=0; j<sopa.numeroColumnas; j++){
			if(palabra[0]==sopa.cuerpo[i][j]){
				for(k=0; k<8; k++){
					if(pertenece((i + len*dir_y[k]),(j + len*dir_x[k]),sopa)==1){
						if(estaEnDir(sopa,palabra,i,j,dir_y[k],dir_x[k])) return k;
					}
				}
			}
		}
	}
	return -1;
}

// mostrarSopa : Matriz -> None
// mostrarSopa toma una estructura de tipo matriz y la imprime en pantalla.
void mostrarSopa(Matriz sopa){
	int i,j;
	for(i=0; i<sopa.numeroFilas; i++){
		for(j=0; j<sopa.numeroColumnas; j++){
			printf("%c ", sopa.cuerpo[i][j]);
		}
		printf("\n");
	}
}

// mostrasPalabra : string, int -> None
// mostrarPalabra toma una palabra (string) y un entero que corresponde con la salida de la funcion
// estaEn; imprimiendo en pantalla si la palabra se encontro o no y, en caso positivo, la direccion
// en la que se encontro.
void mostrarPalabra(char palabra[], int dir){
	switch(dir){
		case -1: printf("%s\tNo se encuentra en la sopa.\n", palabra); break;
		case 0: printf("%s\tHorizontal en direccion a v=(1,0).\n", palabra); break;
		case 1: printf("%s\tDiagonal en direccion a v=(1,-1).\n", palabra); break;
		case 2: printf("%s\tVertical en direccion a v=(0,-1).\n", palabra); break;
		case 3: printf("%s\tDiagonal en direccion a v=(-1,-1).\n", palabra); break;
		case 4: printf("%s\tHorizontal en direccion a v=(-1,0).\n", palabra); break;
		case 5: printf("%s\tDiagonal en direccion a v=(-1,1).\n", palabra); break;
		case 6: printf("%s\tVertical en direccion a v=(0,1).\n", palabra); break;
		case 7: printf("%s\tDiagonal en direccion a v=(1,1).\n", palabra); break;
	}
}