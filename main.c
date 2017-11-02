#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct matriz{
	int numeroFilas, numeroColumnas;
	char** cuerpo;
}Matriz;

typedef struct universo{
	int tamanioUniverso;
	char** palabras;
}Universo;

Matriz * leerArchivoSopa(){
	Matriz *lectura;
	FILE *file;
	file=fopen("sopa.txt", "r");

	lectura = malloc(sizeof(Matriz));

	int i, j, letras=0, saltos=0;
	char a;
	while(fscanf(file, "%c", &a)!=EOF){
		if(a!=' ') letras++;
		if(a=='\n') saltos++;
	}
	lectura->numeroFilas = (letras-saltos)/(saltos+1);
	lectura->numeroColumnas = (letras-saltos)/lectura->numeroFilas;
	fclose(file);

	lectura->cuerpo = malloc(lectura->numeroFilas*sizeof(char*));
	for(i=0; i<lectura->numeroFilas; i++){
		lectura->cuerpo[i] = malloc(lectura->numeroColumnas*sizeof(char));
	}

	file=fopen("sopa.txt", "r");
	i=0; j=0;
	while(fscanf(file, "%c", &a)!=EOF){
		if(a!=' '&&a!='\n'){
			lectura->cuerpo[i][j]=a;
			j++;
		}
		if(a=='\n'){ 
			i++;
			j=0;
		}
	}
	fclose(file);
	return lectura;
}

Universo * leerUniverso(){
	Universo *lectura;
	int i;
	lectura = malloc(sizeof(Universo));
	char buffer[100];
	printf("tamanioUniverso=");
	scanf("%d",&(lectura->tamanioUniverso));
	printf("\n");
	lectura->palabras=malloc(lectura->tamanioUniverso*sizeof(char*));
	for(i=0; i<lectura->tamanioUniverso; i++){
		printf("%d.",i);
		scanf("%s",buffer);
		printf("\n");
		lectura->palabras[i]=malloc(sizeof(strlen(buffer))+1);
		strcpy(lectura->palabras[i],buffer);
	}
	return lectura;
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
	len = strlen(palabra);
	for(i=0; i<sopa.numeroColumnas; i++){
		for(j=0; j<sopa.numeroFilas; j++){
			if(palabra[0]==sopa.cuerpo[i][j]){
				for(k=0; k<8; k++){
					if((i + (len-1)*dir_y[k])<=sopa.numeroColumnas && (j + (len-1)*dir_x[k])<=sopa.numeroFilas){
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
	for(i=0; i<sopa.numeroColumnas; i++){
		for(j=0; j<sopa.numeroFilas; j++){
			printf("%c ", sopa.cuerpo[i][j]);
		}
		printf("\n");
	}
}

void mostrarPalabra(char palabra[], int dir){
	if(dir==-1) printf("%s\tNo se encuentra en la sopa.\n", palabra);
	if(dir==0) printf("%s\tHorizontal en direccion a v=(1,0).\n", palabra);
	if(dir==1) printf("%s\tDiagonal en direccion a v=(1,-1).\n", palabra);
	if(dir==2) printf("%s\tVertical en direccion a v=(0,-1).\n", palabra);
	if(dir==3) printf("%s\tDiagonal en direccion a v=(-1,-1).\n", palabra);
	if(dir==4) printf("%s\tHorizontal en direccion a v=(-1,0).\n", palabra);
	if(dir==5) printf("%s\tDiagonal en direccion a v=(-1,1).\n", palabra);
	if(dir==6) printf("%s\tVertical en direccion a v=(0,1).\n", palabra);
	if(dir==7) printf("%s\tDiagonal en direccion a v=(1,1).\n", palabra);

}
int main()
{
	int i, op;
	printf("Leer de archivo?\n1 - Si\n2 - No (Ingreso por teclado)\n");
	while(!(op==1||op==2)) scanf("%d",&op);
	if(op==1) freopen("ejemplo.in","r",stdin);
	Matriz * sopa = leerArchivoSopa();
	mostrarSopa(*sopa);
	Universo * a = leerUniverso();
	for(i=0; i<a->tamanioUniverso; i++){
		mostrarPalabra(a->palabras[i],estaEn(*sopa,a->palabras[i]));
	}
}