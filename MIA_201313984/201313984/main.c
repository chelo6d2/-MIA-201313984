#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>
#define TRUE 1

/*Marcelo Seisdedos
 *201313984
 * MIA Proyecto 1
 * 2do Semestre 2016
 * */

//Struct de la partición.
typedef struct{
    int part_status;
    char part_type[100];
    char part_fit[100];
    int part_start;
    int part_size;
    char part_name[25];
}partition;

//Struct del MBR
typedef struct{
    int mbr_tamanio;
    char mbr_fecha_creacion[128];
    int mbr_disk_signature;
    partition *mbr_partition1;
    partition *mbr_partition2;
    partition *mbr_partition3;
    partition *mbr_partition4;
}mbr;

//Struct del EBR
typedef struct{
    int part_status;
    char part_fit[100];
    int part_start;
    int part_size;
    int part_next;
    char part_name[25];
}ebr;

//Struct de lso Registros
typedef struct{
    char path[100];
    char id[10];
    char name[100];
    struct registro *siguiente;
    struct registro *anterior;
}registro;

//Struct de mi tabla de particiones
typedef struct{
    registro *primero;
    registro *ultimo;
}tabla;

//Tabla para mount umount
tabla *partitionTable;

void main()
{
    char texto1[100] ="";
    char texto2[100] ="";
    char texto3[100]="";
    partitionTable = (tabla *)malloc(sizeof(tabla));
    partitionTable->primero = (registro *)malloc(sizeof(registro));
    partitionTable->ultimo = (registro *)malloc(sizeof(registro));
    partitionTable->primero = NULL;
    partitionTable->ultimo = NULL;
    printf("Universidad de San Carlos de Guatemala.\n");
    printf("Manejo e Implementacion de Archivos.\n");
    printf("Proyecto Fase 1. \n");
    printf("Marcelo Seisdedos. 201313984\n");
    printf("\n");
    printf("INGRESE UN COMANDO:\n");

      while(TRUE == 1){
    fgets(texto2,100,stdin);

    while(strstr(texto2,"\\")){
        char delimitador[2] = "\t\\";
        char *token;
        token = strtok(texto2,delimitador);
        strcat(texto3,token);
    fgets(texto2,100,stdin);
    }

    //para saltarme los comentarios.
    while(strstr(texto2,"#")){
    fgets(texto2,100,stdin);
    }
    int temporal1 = 0;
    while(strstr(texto2,"\t") && temporal1==0){
        char delimitador[2] = "\t";
        char *token;
        token = strtok(texto2,delimitador);
        strcat(texto3,token);
        temporal1 = 1;
    }

    if(strcmp(texto3,"") == 0)
        strcpy(texto1,texto2);
    else
    strcpy(texto1,texto3);

    //Para salirme del programa.
    if(strcmp(texto1,"exit") == 0)
        break;

    //Para pasar a minusculas.
    char *textminuscula;
    for(textminuscula = texto1; *textminuscula; textminuscula++)
    *textminuscula = tolower((unsigned char)*textminuscula);

    /*SEPARO LAS CADENAS*/
    char delimitador[2] = " ";
    char *token;

    token = strtok(texto1,delimitador);

    if(strcmp("mkdisk",token) == 0)
        metodoMkdisk(token);
    if(strcmp("rmdisk",token) == 0)
        metodoRmdisk(token);
    if(strcmp("fdisk",token) == 0)
        metodoFdisk(token);
    if(strcmp("mount",token) == 0)
        metodoMount(token);
    if(strcmp("unmount",token) == 0)
        metodoUnmount(token);
    if(strcmp("rep",token) == 0)
        metodoRep(token);
    if(strcmp("exec",token) == 0)
        execScript(token);
}
}

int metodoMkdisk(char *token){
    printf("Entro a mkdisk.\n");

}

int metodoRmdisk(char *token){
    printf("Entro a rmdisk.\n");

 }

int metodoFdisk(char *token){
    printf("Entro a fdisk.\n");

}

int metodoMount(char *token){
    printf("Entro a mount.\n");

}

int metodoUnmount(char *token){
    printf("Entro a unmount.\n");

}

int metodoRep(char *token){
    printf("Entro a rep.\n");

}

int execScript(char *token){
    printf("Entro a exec.\n");

}



