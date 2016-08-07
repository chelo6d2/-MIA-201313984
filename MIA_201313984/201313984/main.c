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


int metodoMkdisk(char *token)
{
    printf("Entro a mkdisk.\n");
    char size[100] = "-size";
    char unit[100] = "+unit";
    char path[200] = "-path";
    char name[200] = "-name";

    char comillas[2] = "\"";
    int control;

    int TamanioDeDisco;
    char unitLetra[5] = "m";
    char direccionPath[200] ;
    char direccionPath2[200];
    char direccionPath3[200];
    char nombredeldisco[20];


    while( token != NULL )
       {
          token = strtok(NULL, " :");
          if(token==NULL)
              break;


          char *estaSize;
          char *estaUnit;
          char *estaPath;
          char *estaName;

          estaSize = strstr(token,size);
          estaUnit = strstr(token,unit);
          estaPath = strstr(token,path);
          estaName = strstr(token,name);

          if(estaSize){
              control = 1;
          }else if(estaUnit){
              control = 2;
          }else if(estaPath){
              control = 3;
           }else if (estaName){
              control = 4;
          }else{
              control = 0;
          }

          switch (control) {
          //Validación de Tamaño mayor a 0
          case 1:
              token = strtok(NULL, " :");
              TamanioDeDisco = atoi(token);

              if(TamanioDeDisco > 0){
              }
              else{
                  printf("\nERROR. Tamanio de disco invalido.\n");
                  return -1;
              }
              break;
              //Validación de Unidad de tamaño
          case 2:
              token = strtok(NULL, " :");
              strcpy(unitLetra,token);
              if((strcmp(unitLetra,"m") == 0) || (strcmp(unitLetra,"k") == 0)){

              }
              else{
                  printf("\nERROR. Unidad invalida.\n");
                  return -1;
              }

              break;

        //Para el path
          case 3:

              token = strtok(NULL, " :");

              if(strstr(token,comillas)){
                   printf("\nEntro al if.\n");
                  strcpy(direccionPath,token+1);
                  token = strtok(NULL, "\"");
                  strcat(direccionPath," ");
                  strcat(direccionPath,token);
                  strcpy(direccionPath2,direccionPath);
                  strcpy(direccionPath3,direccionPath);
                    printf("%s\n",direccionPath);
                    printf("%s\n",direccionPath2);
                    printf("%s\n",direccionPath3);

              }else{
                   printf("\nEntro al else.\n");
                  strcpy(direccionPath,token);
                  strcpy(direccionPath2,token);
                  strcpy(direccionPath3,token);
                  printf("%s\n",direccionPath);
                  printf("%s\n",direccionPath2);
                  printf("%s\n",direccionPath3);
              }
              break;
          default:
              printf("\nERROR. parametro no valido\n");
              return -1;
              break;
          }
}

    /*CREAR EL PATH*/
    int numPalabras = 1;
    char *tem;
    tem = strtok(direccionPath,"/");
    while(tem!=NULL)
    {
        tem = strtok(NULL,"/");
        if(tem==NULL)
            break;
        numPalabras++;
    }

    char pathReal[200] = "/";
    char *temm;
    temm = strtok(direccionPath2,"/");
    strcat(pathReal,temm);
    strcat(pathReal,"/");

    //Pära crear la carpeta.
    while(numPalabras > 2)
    {
        temm = strtok(NULL,"/");
        strcat(pathReal,temm);
        strcat(pathReal,"/");
        mkdir(pathReal ,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        numPalabras--;
    }

    temm = strtok(NULL,"/");

    mbr *mbr1 = (mbr *)malloc(sizeof(mbr));
    FILE *archivo = fopen(direccionPath3,"wb");
    time_t tiempo = time(0);
            struct tm *tlocal = localtime(&tiempo);
            char output[128];
            strftime(output,128,"%d/%m/%y %H:%M:%S",tlocal);
    strcpy(mbr1->mbr_fecha_creacion,output);
    int random = rand();

    mbr1->mbr_disk_signature = random;
    mbr1->mbr_partition1 = (partition *)malloc(sizeof(partition));
    mbr1->mbr_partition2 = (partition *)malloc(sizeof(partition));
    mbr1->mbr_partition3 = (partition *)malloc(sizeof(partition));
    mbr1->mbr_partition4 = (partition *)malloc(sizeof(partition));
    strcpy(mbr1->mbr_partition1->part_type,"x");
    strcpy(mbr1->mbr_partition2->part_type,"x");
    strcpy(mbr1->mbr_partition3->part_type,"x");
    strcpy(mbr1->mbr_partition4->part_type,"x");
    mbr1->mbr_partition1->part_size = 0;
    mbr1->mbr_partition2->part_size = 0;
    mbr1->mbr_partition3->part_size = 0;
    mbr1->mbr_partition4->part_size = 0;

    //Cuando es en Kb
    if(strcmp(unitLetra,"k") == 0)
    {
        mbr1->mbr_tamanio = TamanioDeDisco*1024;
        fwrite(mbr1,sizeof(mbr),1,archivo);
        for(int i = 0; i < (500*TamanioDeDisco); i++)
            fputs("\\0",archivo);

    //Cuando es en Mb
    }else if(strcmp(unitLetra,"m") == 0)
    {
        mbr1->mbr_tamanio = TamanioDeDisco*1024*1024;
        fwrite(mbr1,sizeof(mbr),1,archivo);
        for(int i = 0; i < 2*(500*TamanioDeDisco*500); i++)
            fputs("\\0",archivo);

    }
    printf("\nSe creo el disco con exito.\n");
    fclose(archivo);

    mbr *mbrLeido = (mbr *)malloc(sizeof(mbr));

    //AQUI EL direccionPath3 ya no va a ser el path completo sino una combinacion del Path2 + el nombre de usuario que puede venir.
    FILE *barchivo1 = fopen(direccionPath3,"rb");
    fread(mbrLeido,sizeof(mbr),1,barchivo1);
    int t = sizeof(mbrLeido);
    fclose(barchivo1);
    return 1;
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



