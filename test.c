#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "rumpelstinski.c"

void perteneceTest(){
	Matriz sopa;
	sopa.numeroColumnas=3;
	sopa.numeroFilas=4;
	assert(pertenece(0,0,sopa));
	assert(pertenece(1,1,sopa));
	assert(pertenece(2,2,sopa));
	assert(pertenece(3,2,sopa));
	assert(!pertenece(3,3,sopa));
	assert(!pertenece(-1,3,sopa));
	assert(!pertenece(-100,100,sopa));
	assert(!pertenece(100,100,sopa));
	printf("Los test de pertenece se han ejecutado exitosamente.\n");
}

void estaEnDirTest(){
	Matriz sopa;
	int i, col=3, fil=4;
	sopa.numeroColumnas=col;
	sopa.numeroFilas=fil;
	sopa.cuerpo=malloc(sizeof(char*)*fil);
	for(i=0;i<fil;i++) sopa.cuerpo[i] = malloc((col+1)*sizeof(char));
	sopa.cuerpo[0]="ABC";
	sopa.cuerpo[1]="DEF";
	sopa.cuerpo[2]="GHI";
	sopa.cuerpo[3]="JKL";
	assert(estaEnDir(sopa,"LIFC",3,2,-1,0));
	assert(estaEnDir(sopa,"ABC",0,0,0,1));
	assert(!estaEnDir(sopa,"DEF",0,0,1,0));
	printf("Los test de estaEnDir se han ejecutado exitosamente.\n");
}

void estaEnTest(){
	Matriz sopa;
	int i, col=3, fil=4;
	sopa.numeroColumnas=col;
	sopa.numeroFilas=fil;
	sopa.cuerpo=malloc(sizeof(char*)*fil);
	for(i=0;i<fil;i++) sopa.cuerpo[i] = malloc((col+1)*sizeof(char));
	sopa.cuerpo[0]="ABC";
	sopa.cuerpo[1]="DEF";
	sopa.cuerpo[2]="GHI";
	sopa.cuerpo[3]="JKL";
	assert(estaEn(sopa,"ABC")==0);
	assert(estaEn(sopa,"LHD")==5);
	assert(estaEn(sopa,"ADG")==2);
	assert(estaEn(sopa,"FED")==4);
	assert(estaEn(sopa,"R")==-1);
	assert(estaEn(sopa,"HOLA")==-1);
	assert(estaEn(sopa,"ABCDEFGH")==-1);
	printf("Los test de estaEn se han ejecutado exitosamente.\n");
}
int main(){
	perteneceTest();
	estaEnDirTest();
	estaEnTest();
	printf("Todos los test de han ejecutado exitosamente.\n");
	return 0;
}