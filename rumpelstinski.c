#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct matriz{
	int numeroFilas, numeroColumnas;
	char** cuerpo;
}Matriz;

typedef struct universo{
	int tamanioUniverso;
	char** palabras;
}Universo;

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

int pertenece(int y, int x, Matriz sopa){
	if(x>=sopa.numeroColumnas || x<0) return 0;
	if(y>=sopa.numeroFilas || y<0) return 0;
	return 1;
}

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

void mostrarSopa(Matriz sopa){
	int i,j;
	for(i=0; i<sopa.numeroFilas; i++){
		for(j=0; j<sopa.numeroColumnas; j++){
			printf("%c ", sopa.cuerpo[i][j]);
		}
		printf("\n");
	}
}

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