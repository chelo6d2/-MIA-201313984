#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>
#define TRUE 1

//ultimo



typedef struct{
    int part_status;
    char part_type[100];
    char part_fit[100];
    int part_start;
    int part_size;
    char part_name[25];
}partition;

typedef struct{
    int mbr_tamanio;
    char mbr_fecha_creacion[128];
    int mbr_disk_signature;
    partition *mbr_partition1;
    partition *mbr_partition2;
    partition *mbr_partition3;
    partition *mbr_partition4;
}mbr;

typedef struct{
    int part_status;
    char part_fit[100];
    int part_start;
    int part_size;
    int part_next;
    char part_name[25];
}ebr;

typedef struct{
    char path[100];
    char id[10];
    char name[100];
    struct registro *siguiente;
    struct registro *anterior;
}registro;

typedef struct{
    registro *primero;
    registro *ultimo;
}tabla;


tabla *tablaDeParticiones;
void main(int argc, char *argv[])
{
    char cadenas[100]="";
    char cadenas2[100]="";
    char cadenas3[100]="";
    tablaDeParticiones = (tabla *)malloc(sizeof(tabla));
    tablaDeParticiones->primero = (registro *)malloc(sizeof(registro));
    tablaDeParticiones->ultimo = (registro *)malloc(sizeof(registro));
    tablaDeParticiones->primero = NULL;
    tablaDeParticiones->ultimo = NULL;
    printf("Universidad de San Carlos de Guatemala.\n");
    printf("Manejo e Implementacion de Archivos.\n");
    printf("Proyecto Fase 1. \n");
    printf("Marcelo Seisdedos. 201313984\n");
    printf("\n");
    printf("INGRESE UN COMANDO:\n");




    while(TRUE == 1){
    gets(cadenas2);


    while(strstr(cadenas2,"#")){
        gets(cadenas2);
    }

    while(strstr(cadenas2,"\\")){
        char delimitador[2] = "\t\\";
        char *token;
        token = strtok(cadenas2,delimitador);
        strcat(cadenas3,token);
        gets(cadenas2);
    }

    int jaja = 0;
    while(strstr(cadenas2,"\t") && jaja==0){
        char delimitador[2] = "\t";
        char *token;
        token = strtok(cadenas2,delimitador);
        strcat(cadenas3,token);
        jaja = 1;
    }

    if(strcmp(cadenas3,"") == 0)
        strcpy(cadenas,cadenas2);
    else
    strcpy(cadenas,cadenas3);




    if(strcmp(cadenas,"exit") == 0)
        break;
    /*PASO TODO A MINUSCULAS*/
    char *s;
    for(s = cadenas; *s; s++)
    *s = tolower((unsigned char)*s);

    /*SEPARO LAS CADENAS*/
    char delimitador[2] = " ";
    char *token;


    token = strtok(cadenas,delimitador);

    char mkdisk[10] = "mkdisk";
    char rmdisk[10] = "rmdisk";
    char fdisk[10] = "fdisk";
    char mount[10] = "mount";
    char unmount[10] = "umount";
    char rep[10] = "rep";
    char exec[10] = "exec";
    if(strcmp(mkdisk,token) == 0)
         metodoMkdisk(token);
    if(strcmp(rmdisk,token) == 0)
        metodoRmdisk(token);
    if(strcmp(fdisk,token) == 0)
        metodoFdisk(token);
    if(strcmp(mount,token) == 0)
        metodoMount(token);
    if(strcmp(unmount,token) == 0)
        metodoUnmount(token);
    if(strcmp(rep,token) == 0)
        metodoRep(token);
    if(strcmp(exec,token) == 0)
        metodoExec(token);
}
}

int metodoExec(char *token){

    char path[100] = "";
    int veces = 0;

    while( token != NULL )
       {
          token = strtok(NULL, " ");
          if(token==NULL)
              break;
          if(veces == 0){
            strcpy(path,token);
            veces++;
          }
          else{
              printf("\nERROR. Exceso de comando\n");
              return -1;
          }
       }

    FILE *fp1;
    char *c1;
    char cad[100] = "";
    char cadenas[200];
    char cadenas3[200];
    fp1=fopen(path, "r");
    if(fp1 == NULL)
    {
        printf("\nERROR. Script no existe\n");
        return -1;
    }
    int aa = 0;
    int jaja = 0;
    while(c1=fgets(cad,100,fp1)){
    aa = 0;
    jaja = 0;

        while(strstr(c1,"#")){
            printf(c1);
            aa = 1;
            c1=fgets(cad,100,fp1);
        }

        while(strstr(c1,"\\")){
            char delimitador[2] = "\\";
            char *token;
            token = strtok(c1,delimitador);
            strcat(cadenas3,token);
            c1=fgets(cad,100,fp1);
        }


        while(strstr(c1,"\t")){
            char delimitador[2] = "\t";
            char *token;
            token = strtok(c1,delimitador);
            strcat(cadenas3,token);
            jaja = 1;
        }

        if(strstr(c1,"\n")){
            char delimitador[2] = "\n";
            char *token;
            token = strtok(c1,delimitador);
            strcat(cadenas3,token);
            jaja = 1;
        }

        if(strcmp(cadenas3,"") == 0)
            strcpy(cadenas,c1);
        else
        strcpy(cadenas,cadenas3);

        /*PASO TODO A MINUSCULAS*/
        char *s;
        for(s = cadenas; *s; s++)
        *s = tolower((unsigned char)*s);
        puts(cadenas);

        /*SEPARO LAS CADENAS*/
        char delimitador[2] = " ";
        char *tokenn;


        tokenn = strtok(cadenas,delimitador);

        char mkdisk[10] = "mkdisk";
        char rmdisk[10] = "rmdisk";
        char fdisk[10] = "fdisk";
        char mount[10] = "mount";
        char unmount[10] = "unmount";
        char rep[10] = "rep";
        char exec[10] = "exec";
        if(strcmp(mkdisk,tokenn) == 0)
             metodoMkdisk(tokenn);
        if(strcmp(rmdisk,tokenn) == 0)
            metodoRmdisk(tokenn);
        if(strcmp(fdisk,tokenn) == 0)
            metodoFdisk(tokenn);
        if(strcmp(mount,tokenn) == 0)
            metodoMount(tokenn);
        if(strcmp(unmount,tokenn) == 0)
            metodoUnmount(tokenn);
        if(strcmp(rep,tokenn) == 0)
            metodoRep(tokenn);
        if(strcmp(exec,tokenn) == 0)
            metodoExec(tokenn);
        strcpy(cadenas,"");
        strcpy(cadenas3,"");
    }


}

int  metodoMkdisk(char *token)
{
    char size[100] = "-size";
    char unit[100] = "+unit";
    char path[200] = "-path";
    char name[200] = "-name";
    char comillas[2] = "\"";
    int control;

    int TamanioDeDisco;
    char unitLetra[5] = "m";
    char direccionPath[200]="";
    char direccionPath2[200]="";
    char direccionPath3[200]="";
    char direccionPath4[200]="";
    char nombredeldisco[20]="";
    char pruebanombre[20];
    char pruebaextension[20];
    char extensionNombre[20]="";

    char pathCrearDisco[200];

    while( token != NULL )
       {
          token = strtok(NULL, " ::");
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
          }else if(estaName){
              control = 4;
          }else{
              control = 0;
          }

          switch (control) {
          case 1:
              token = strtok(NULL, " ::");
              TamanioDeDisco = atoi(token);

              if(TamanioDeDisco > 0){
              }
              else{
                  printf("\nERROR. Tamaño de disco no valido. Debe ser mayor a 0.\n");
                  return -1;
              }
              break;
          case 2:
              token = strtok(NULL, " ::");
              strcpy(unitLetra,token);
              if((strcmp(unitLetra,"m") == 0) || (strcmp(unitLetra,"k") == 0)){

              }
              else{
                  printf("\nERROR. Unidad no valida. Debe ser k o m\n");
                  return -1;
              }

              break;
          case 3:

              token = strtok(NULL, " ::");

              if(strstr(token,comillas)){
                  strcpy(direccionPath,token+1);
                  token = strtok(NULL, "\"");
                  strcat(direccionPath," ");
                  strcat(direccionPath,token);
                  strcpy(direccionPath2,direccionPath);
                  strcpy(direccionPath3,direccionPath);
              }else{
                  strcpy(direccionPath,token);
                  strcpy(direccionPath2,token);
                  strcpy(direccionPath3,token);
              }
              break;

          case 4:
              token = strtok(NULL, " ::");
              strcpy(nombredeldisco,token);
              //printf("\Nombre del disco: \n");
              //printf("%s\n",nombredeldisco);

              //PRUEBA USANDO OTRO TOK
              char* mitoken1 = token;
              char* mitoken2 = token;
              char* string;
              char* tofree;

               string = strdup(nombredeldisco);
               if (string != NULL)
                           {
                               tofree = string;
                               int i=0;
                               while ((mitoken1 = strsep(&string, ".")) != NULL)
                               {
                                   i++;
                                   //En la primer corrida encuentro el nombre, en la segunda la extensión.
                                   if(i==2)
                                   {
                                       strcpy(extensionNombre,mitoken1);

                                   }
                //                   printf("%s\n", mitoken1);
                               }
                               free(tofree);
                           }

               strcat(direccionPath3,mitoken2);

               //Verifico si la extensión está correcta

                  //       printf("Extension: \n");
                    //     printf("%s\n", extensionNombre);

                         if(strcmp(extensionNombre,"dsk") == 0)
                         {
                      //       printf("\nEntro al if. Es igual a dsk");
                         }
                         else
                         {
                        //     printf("\nEntro al else. No es igual a dsk.");
                             //not ok. tiene que salirse
                             printf("\nERROR. Extension del disco incorrecta. Debe ser .dsk\n");
                             return -1;
                             break;
                         }
                         break;
          default:
              printf("\nERROR. Parametro no valido\n");
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
    while(numPalabras > 2)
    {
        temm = strtok(NULL,"/");
        strcat(pathReal,temm);
        strcat(pathReal,"/");
        mkdir(pathReal ,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        numPalabras--;
    }

    temm = strtok(NULL,"/");
    //char direccionPath4[200];

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

    if(strcmp(unitLetra,"k") == 0)
    {
        mbr1->mbr_tamanio = TamanioDeDisco*1024;
        fwrite(mbr1,sizeof(mbr),1,archivo);
        for(int i = 0; i < (500*TamanioDeDisco); i++)
            fputs("\\0",archivo);


    }else if(strcmp(unitLetra,"m") == 0)
    {
        mbr1->mbr_tamanio = TamanioDeDisco*1024*1024;
        fwrite(mbr1,sizeof(mbr),1,archivo);
        for(int i = 0; i < 2*(500*TamanioDeDisco*500); i++)
            fputs("\\0",archivo);

    }

    fclose(archivo);

    mbr *mbrLeido = (mbr *)malloc(sizeof(mbr));
    FILE *barchivo1 = fopen(direccionPath3,"rb");
    fread(mbrLeido,sizeof(mbr),1,barchivo1);
    int t = sizeof(mbrLeido);
    fclose(barchivo1);
    printf("\n**Disco creado exitosamente**");


    return 1;
}

int  metodoMkdisk2(char *token)
{
    char size[100] = "-size";
    char unit[100] = "+unit";
    char path[200] = "-path";
    char comillas[2] = "\"";
    int control;

    int TamanioDeDisco;
    char unitLetra[5] = "m";
    char direccionPath[200];
    char direccionPath2[200];
    char direccionPath3[200];


    while( token != NULL )
       {
          token = strtok(NULL, " ::");
          if(token==NULL)
              break;


          char *estaSize;
          char *estaUnit;
          char *estaPath;

          estaSize = strstr(token,size);
          estaUnit = strstr(token,unit);
          estaPath = strstr(token,path);

          if(estaSize){
              control = 1;
          }else if(estaUnit){
              control = 2;
          }else if(estaPath){
              control = 3;
          }else{
              control = 0;
          }

          switch (control) {
          case 1:
              token = strtok(NULL, " ::");
              TamanioDeDisco = atoi(token);

              if(TamanioDeDisco > 0){
              }
              else{
                  printf("\nERROR. Tamaño de disco no valido. Debe ser mayor a 0.\n");
                  return -1;
              }
              break;
          case 2:
              token = strtok(NULL, " ::");
              strcpy(unitLetra,token);
              if((strcmp(unitLetra,"m") == 0) || (strcmp(unitLetra,"k") == 0)){

              }
              else{
                  printf("\nERROR. Unidad no valida. Debe ser k o m\n");
                  return -1;
              }

              break;
          case 3:

              token = strtok(NULL, " ::");

              if(strstr(token,comillas)){
                  strcpy(direccionPath,token+1);
                  token = strtok(NULL, "\"");
                  strcat(direccionPath," ");
                  strcat(direccionPath,token);
                  strcpy(direccionPath2,direccionPath);
                  strcpy(direccionPath3,direccionPath);
              }else{
                  strcpy(direccionPath,token);
                  strcpy(direccionPath2,token);
                  strcpy(direccionPath3,token);
              }
              break;
          default:
              printf("\nERROR. Parametro no valido\n");
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

    if(strcmp(unitLetra,"k") == 0)
    {
        mbr1->mbr_tamanio = TamanioDeDisco*1024;
        fwrite(mbr1,sizeof(mbr),1,archivo);
        for(int i = 0; i < (500*TamanioDeDisco); i++)
            fputs("\\0",archivo);


    }else if(strcmp(unitLetra,"m") == 0)
    {
        mbr1->mbr_tamanio = TamanioDeDisco*1024*1024;
        fwrite(mbr1,sizeof(mbr),1,archivo);
        for(int i = 0; i < 2*(500*TamanioDeDisco*500); i++)
            fputs("\\0",archivo);

    }

    fclose(archivo);

    mbr *mbrLeido = (mbr *)malloc(sizeof(mbr));
    FILE *barchivo1 = fopen(direccionPath3,"rb");
    fread(mbrLeido,sizeof(mbr),1,barchivo1);
    int t = sizeof(mbrLeido);
    fclose(barchivo1);
    printf("\n**Disco creado exitosamente**");


    return 1;
}


int metodoRmdisk(char *token)
{
    char path[10] = "-path";
    char tomandoPath[200];
    char comillas[3] = "\"";

    char desicion[5];

    int k = 0;
    token = strtok(NULL, " ::\"");
    while(token != NULL)
    {
        char *estaPath;
        estaPath = strstr(token,path);
        if(estaPath){
            token = strtok(NULL, " ::");

            if(strstr(token,comillas)){
              strcpy(tomandoPath,token+1);
            token = strtok(NULL, "\"");
            strcat(tomandoPath," ");
            strcat(tomandoPath,token);
            printf("\nCAAAAAAAAAADENA   : %s\n",tomandoPath);
            }else{
                strcpy(tomandoPath,token);
            }
        }
        token = strtok(NULL, " =\"");
        if(token==NULL){
             break;
        }

        else{
            k = 1;
            printf("ERROR, Comando no valido.\n");
            break;
        }
    }

    if(k == 0){
            printf( "%s\n", tomandoPath );

                printf("\nsi: Eliminar disco \nno: No elimnar el disco\n");
                gets(desicion);
                if(strcmp(desicion,"si") == 0)
                {
                    FILE *archivo = fopen(tomandoPath,"r");

                    if(archivo!= NULL){
                        remove(tomandoPath);
                        fclose(archivo);
                        printf("\n**Disco eliminado exitosamente**\n");
                        return 1;
                    }else{
                        printf("\nERROR. Disco no existe.\n");
                    }

                }else{
                    printf("\n**Disco no eliminado**\n");
                }

       }else{
             printf("\nError, comando no valido\n");
       }

}

int metodoFdisk(char *token)
{
    char size[100] = "-size";
    char unit[100] = "+unit";
    char path[200] = "-path";
    char type[10] = "+type";
    char fit[10] = "+fit";
    char deletee[200] = "+delete";
    char name[10] = "-name";
    char add[10] = "+add";
    char comillas[3] = "\"";

    int tamanioParticion = 0;
    char letraUnit[100] = "k";
    char direccion[200];
    char letraType[100] = "p";
    char letraFit[100] = "wf";
    char letraDelete[100];
    char letraName[100];
    int tamanioAdd = 0;

    int control;
    int accion = 0;
    while(token != NULL)
    {
        token = strtok(NULL, " ::");
        if(token==NULL)
            break;

        if(strstr(token,size))
            control = 1;
        else if(strstr(token,unit))
            control = 2;
        else if(strstr(token,path))
            control = 3;
        else if(strstr(token,type))
            control = 4;
        else if(strstr(token,fit))
            control = 5;
        else if(strstr(token,deletee))
            control = 6;
        else if(strstr(token,name))
            control = 7;
        else if(strstr(token,add))
            control = 8;
        else
            control = 0;

        switch (control) {
        case 1:
            token = strtok(NULL, " ::");
            tamanioParticion = atoi(token);
            if(tamanioParticion <= 0)
            {
                printf("\ERROR. Tamaño de la particion no valido. Debe ser mayor a 0.\n");
                return -1;
            }
            break;
        case 2:
            token = strtok(NULL, " ::");
            strcpy(letraUnit,token);
            if(strcmp(letraUnit,"b") == 0 || (strcmp(letraUnit,"m") == 0) || (strcmp(letraUnit,"k") == 0)){

            }else{
                printf("\nERROR. Unidad no valida. Debe ser b, m, k.\n");
                return -1;
            }
            break;
        case 3:
            token = strtok(NULL, " ::");

            if(strstr(token,comillas)){
                strcpy(direccion,token+1);
                token = strtok(NULL, "\"");
                strcat(direccion," ");
                strcat(direccion,token);
            }else{
                strcpy(direccion,token);
            }

            /*COMPROBANDO SI EXISTE EL DISCO*/
            FILE *archivoDisco = fopen(direccion,"rb");
            if(archivoDisco==NULL){
                printf("\nERROR. El disco no existe.\n");
                return -1;
            }else{
                close(archivoDisco);
            }
            break;
        case 4:
            token = strtok(NULL, " ::");
            strcpy(letraType,token);
            if(strcmp(letraType,"p") == 0 || (strcmp(letraType,"e") == 0) || (strcmp(letraType,"l") == 0))
                printf("");
            else{
                printf("\nERROR. Tipo de particion incorrecto. Debe ser P, E, L.");
                return -1;
            }
            break;
        case 5:
            token = strtok(NULL, " ::");
            strcpy(letraFit,token);
            if(strcmp(letraFit,"bf") == 0 || (strcmp(letraFit,"ff") == 0) || (strcmp(letraFit,"wf") == 0))
                printf("");
            else{
                printf("\nERROR. Ajuste incorrecto, debe ser BF; FF; WF");
                return -1;
            }
            break;
        case 6:
            token = strtok(NULL, " ::");
            strcpy(letraDelete,token);
            if(strcmp(letraDelete,"fast") == 0 || (strcmp(letraDelete,"full") == 0)){
                printf("");
                accion = 1;
            }
            else{
                printf("\nERROR. Debe ser fast o full.");
                return -1;
            }
            break;
        case 7:
            token = strtok(NULL, " :");
            strcpy(letraName,token);
            break;
        case 8:
            token = strtok(NULL, " ::");
            tamanioAdd = atoi(token);
            accion = 2;
            break;
        default:
            printf("ERROR. Parametro no valido.\n");
            return -1;
            break;
        }
    }


    FILE *binario = fopen(direccion,"r+b");
    mbr *compro = (mbr *)malloc(sizeof(mbr));
    fseek(binario,0,SEEK_SET);
    fread(compro,sizeof(mbr),1,binario);
    fclose(binario);

    int tama = 0;
    if(strcmp(letraUnit,"b") == 0)
    {
        tama = tamanioParticion;
    }else if(strcmp(letraUnit,"k") == 0){
        tama = tamanioParticion * 1024;
    }else if(strcmp(letraUnit,"m") == 0){
        tama = tamanioParticion * 1024 * 1024;
    }

    int tamaAdd = 0;
    if(strcmp(letraUnit,"b") == 0)
    {
        tamaAdd = tamanioAdd;
    }else if(strcmp(letraUnit,"k") == 0){
        tamaAdd = tamanioAdd * 1024;
    }else if(strcmp(letraUnit,"m") == 0){
        tamaAdd = tamanioAdd * 1024 * 1024;
    }

    int espacioLibreEnDisco = compro->mbr_tamanio - compro->mbr_partition1->part_size - compro->mbr_partition2->part_size - compro->mbr_partition3->part_size - compro->mbr_partition4->part_size ;


    int extendidas = 1;
    int primarias = 0;
    int acceso = 0;
    if(accion == 0){
       //Para crear las extendidas.
        if(strcmp(letraType,"e") == 0){
            if(strcmp(compro->mbr_partition1->part_type,"e") == 0 || strcmp(compro->mbr_partition2->part_type,"e") == 0 || strcmp(compro->mbr_partition3->part_type,"e") == 0 || strcmp(compro->mbr_partition4->part_type,"e") == 0){
                extendidas = 0;
                printf("\nERROR. Ya existe una particion extendida en el disco.\n");
                return -1;
            }else{
                if(espacioLibreEnDisco > 0 && espacioLibreEnDisco >= tama){
                    if(strcmp(compro->mbr_partition1->part_type,"x") == 0){
                        if(strcmp(compro->mbr_partition2->part_type,"x") == 0){
                            if(strcmp(compro->mbr_partition3->part_type,"x") == 0){
                                if(strcmp(compro->mbr_partition4->part_type,"x") == 0){
                                    mbr *mbrLeido = (mbr *)malloc(sizeof(mbr));
                                    mbr *mbrLeido1 = (mbr *)malloc(sizeof(mbr));
                                    mbr *mbrLeido2 = (mbr *)malloc(sizeof(mbr));
                                    mbrLeido1->mbr_partition1 = (partition *)malloc(sizeof(partition));
                                    FILE *barchivo1 = fopen(direccion,"r+b");
                                    fseek(barchivo1,0,SEEK_SET);
                                    fread(mbrLeido,sizeof(mbr),1,barchivo1);
                                    mbrLeido->mbr_partition1 = (partition *)malloc(sizeof(partition));
                                    mbrLeido->mbr_partition1->part_size = tama;
                                    mbrLeido->mbr_partition1->part_start = sizeof(mbrLeido);
                                    strcpy(mbrLeido->mbr_partition1->part_fit,letraFit);
                                    strcpy(mbrLeido->mbr_partition1->part_name,letraName);
                                    strcpy(mbrLeido->mbr_partition1->part_type,letraType);
                                    mbrLeido->mbr_partition1->part_status = 1;

                                    fseek(barchivo1,0,SEEK_SET);
                                    fwrite(mbrLeido,sizeof(mbr)+ sizeof( partition),1,barchivo1);
                                    fseek(barchivo1,0,SEEK_SET);
                                    fread(mbrLeido1,sizeof(mbr),1,barchivo1);

                                    ebr *ebrInicial = (ebr *)malloc(sizeof(ebr));
                                    ebr *ebrInicial2 = (ebr *)malloc(sizeof(ebr));
                                    strcpy(ebrInicial->part_fit,letraFit);
                                    strcpy(ebrInicial->part_name,letraName);
                                    ebrInicial->part_status = 1;
                                    ebrInicial->part_size = 0;
                                    ebrInicial->part_start = mbrLeido->mbr_partition1->part_start;
                                    ebrInicial->part_next = -1;


                                    fseek(barchivo1,sizeof(mbr)+ sizeof( partition),SEEK_CUR);
                                    fwrite(ebrInicial,sizeof(ebr),1,barchivo1);

                                    fseek(barchivo1,0,SEEK_SET);
                                    fread(mbrLeido2,sizeof(mbr),1,barchivo1);

                                    fseek(barchivo1,sizeof(mbr)+ sizeof( partition),SEEK_CUR);
                                    fread(ebrInicial2,sizeof(ebr),1,barchivo1);

                                    fclose(barchivo1);
                                    printf("\n**Particion extendida creada con exito.**\n");
                                    acceso = 1;
                                }else{
                                    if(tama <= compro->mbr_partition4->part_start){
                                        mbr *mbrLeido = (mbr *)malloc(sizeof(mbr));
                                        mbr *mbrLeido1 = (mbr *)malloc(sizeof(mbr));
                                        mbr *mbrLeido2 = (mbr *)malloc(sizeof(mbr));
                                        mbrLeido1->mbr_partition1 = (partition *)malloc(sizeof(partition));
                                        FILE *barchivo1 = fopen(direccion,"r+b");
                                        fseek(barchivo1,0,SEEK_SET);
                                        fread(mbrLeido,sizeof(mbr),1,barchivo1);
                                        mbrLeido->mbr_partition1 = (partition *)malloc(sizeof(partition));
                                        mbrLeido->mbr_partition1->part_size = tama;
                                        mbrLeido->mbr_partition1->part_start = sizeof(mbrLeido);
                                        strcpy(mbrLeido->mbr_partition1->part_fit,letraFit);
                                        strcpy(mbrLeido->mbr_partition1->part_name,letraName);
                                        strcpy(mbrLeido->mbr_partition1->part_type,letraType);
                                        mbrLeido->mbr_partition1->part_status = 1;

                                        fseek(barchivo1,0,SEEK_SET);
                                        fwrite(mbrLeido,sizeof(mbr)+ sizeof( partition),1,barchivo1);
                                        fseek(barchivo1,0,SEEK_SET);
                                        fread(mbrLeido1,sizeof(mbr),1,barchivo1);
                                        ebr *ebrInicial = (ebr *)malloc(sizeof(ebr));
                                        ebr *ebrInicial2 = (ebr *)malloc(sizeof(ebr));
                                        strcpy(ebrInicial->part_fit,letraFit);
                                        strcpy(ebrInicial->part_name,letraName);
                                        ebrInicial->part_status = 1;
                                        ebrInicial->part_size = 0;
                                        ebrInicial->part_start = mbrLeido->mbr_partition1->part_start;
                                        ebrInicial->part_next = -1;


                                        fseek(barchivo1,sizeof(mbr)+ sizeof( partition),SEEK_CUR);
                                        fwrite(ebrInicial,sizeof(ebr),1,barchivo1);

                                        fseek(barchivo1,0,SEEK_SET);
                                        fread(mbrLeido2,sizeof(mbr),1,barchivo1);

                                        fseek(barchivo1,sizeof(mbr)+ sizeof( partition),SEEK_CUR);
                                        fread(ebrInicial2,sizeof(ebr),1,barchivo1);
                                        fclose(barchivo1);
                                        printf("\n**Particion extendida creada con exito.**\n");
                                        acceso = 1;
                                    }
                                }
                            }else{
                                if(tama <= compro->mbr_partition3->part_start){
                                    mbr *mbrLeido = (mbr *)malloc(sizeof(mbr));
                                    mbr *mbrLeido1 = (mbr *)malloc(sizeof(mbr));
                                    mbr *mbrLeido2 = (mbr *)malloc(sizeof(mbr));
                                    mbrLeido1->mbr_partition1 = (partition *)malloc(sizeof(partition));
                                    FILE *barchivo1 = fopen(direccion,"r+b");
                                    fseek(barchivo1,0,SEEK_SET);
                                    fread(mbrLeido,sizeof(mbr),1,barchivo1);
                                    mbrLeido->mbr_partition1 = (partition *)malloc(sizeof(partition));
                                    mbrLeido->mbr_partition1->part_size = tama;
                                    mbrLeido->mbr_partition1->part_start = sizeof(mbrLeido);
                                    strcpy(mbrLeido->mbr_partition1->part_fit,letraFit);
                                    strcpy(mbrLeido->mbr_partition1->part_name,letraName);
                                    strcpy(mbrLeido->mbr_partition1->part_type,letraType);
                                    mbrLeido->mbr_partition1->part_status = 1;

                                    fseek(barchivo1,0,SEEK_SET);
                                    fwrite(mbrLeido,sizeof(mbr)+ sizeof( partition),1,barchivo1);
                                    fseek(barchivo1,0,SEEK_SET);
                                    fread(mbrLeido1,sizeof(mbr),1,barchivo1);
                                    ebr *ebrInicial = (ebr *)malloc(sizeof(ebr));
                                    ebr *ebrInicial2 = (ebr *)malloc(sizeof(ebr));
                                    strcpy(ebrInicial->part_fit,letraFit);
                                    strcpy(ebrInicial->part_name,letraName);
                                    ebrInicial->part_status = 1;
                                    ebrInicial->part_size = 0;
                                    ebrInicial->part_start = mbrLeido->mbr_partition1->part_start;
                                    ebrInicial->part_next = -1;


                                    fseek(barchivo1,sizeof(mbr)+ sizeof( partition),SEEK_CUR);
                                    fwrite(ebrInicial,sizeof(ebr),1,barchivo1);

                                    fseek(barchivo1,0,SEEK_SET);
                                    fread(mbrLeido2,sizeof(mbr),1,barchivo1);

                                    fseek(barchivo1,sizeof(mbr)+ sizeof( partition),SEEK_CUR);
                                    fread(ebrInicial2,sizeof(ebr),1,barchivo1);
                                    fclose(barchivo1);
                                    printf("\n**Particion extendida creada con exito.**\n");
                                    acceso = 1;
                                }
                            }
                        }else{
                            if(tama <= compro->mbr_partition2->part_start){
                                mbr *mbrLeido = (mbr *)malloc(sizeof(mbr));
                                mbr *mbrLeido1 = (mbr *)malloc(sizeof(mbr));
                                mbr *mbrLeido2 = (mbr *)malloc(sizeof(mbr));
                                mbrLeido1->mbr_partition1 = (partition *)malloc(sizeof(partition));
                                FILE *barchivo1 = fopen(direccion,"r+b");
                                fseek(barchivo1,0,SEEK_SET);
                                fread(mbrLeido,sizeof(mbr),1,barchivo1);
                                mbrLeido->mbr_partition1 = (partition *)malloc(sizeof(partition));
                                mbrLeido->mbr_partition1->part_size = tama;
                                mbrLeido->mbr_partition1->part_start = sizeof(mbrLeido);
                                strcpy(mbrLeido->mbr_partition1->part_fit,letraFit);
                                strcpy(mbrLeido->mbr_partition1->part_name,letraName);
                                strcpy(mbrLeido->mbr_partition1->part_type,letraType);
                                mbrLeido->mbr_partition1->part_status = 1;

                                fseek(barchivo1,0,SEEK_SET);
                                fwrite(mbrLeido,sizeof(mbr)+ sizeof( partition),1,barchivo1);
                                fseek(barchivo1,0,SEEK_SET);
                                fread(mbrLeido1,sizeof(mbr),1,barchivo1);
                                ebr *ebrInicial = (ebr *)malloc(sizeof(ebr));
                                ebr *ebrInicial2 = (ebr *)malloc(sizeof(ebr));
                                strcpy(ebrInicial->part_fit,letraFit);
                                strcpy(ebrInicial->part_name,letraName);
                                ebrInicial->part_status = 1;
                                ebrInicial->part_size = 0;
                                ebrInicial->part_start = mbrLeido->mbr_partition1->part_start;
                                ebrInicial->part_next = -1;


                                fseek(barchivo1,sizeof(mbr)+ sizeof( partition),SEEK_CUR);
                                fwrite(ebrInicial,sizeof(ebr),1,barchivo1);

                                fseek(barchivo1,0,SEEK_SET);
                                fread(mbrLeido2,sizeof(mbr),1,barchivo1);

                                fseek(barchivo1,sizeof(mbr)+ sizeof( partition),SEEK_CUR);
                                fread(ebrInicial2,sizeof(ebr),1,barchivo1);
                                fclose(barchivo1);
                                printf("\n**Particion extendida creada con exito.**\n");
                                acceso = 1;
                            }
                        }
                    }

                    if(strcmp(compro->mbr_partition2->part_type,"x") == 0 && acceso == 0){
                        if(strcmp(compro->mbr_partition3->part_type,"x") == 0){
                            if(strcmp(compro->mbr_partition4->part_type,"x") == 0){
                                mbr *mbrLeido = (mbr *)malloc(sizeof(mbr));
                                mbr *mbrLeido1 = (mbr *)malloc(sizeof(mbr));
                                mbr *mbrLeido2 = (mbr *)malloc(sizeof(mbr));
                                mbrLeido1->mbr_partition2 = (partition *)malloc(sizeof(partition));
                                FILE *barchivo1 = fopen(direccion,"r+b");
                                fseek(barchivo1,0,SEEK_SET);
                                fread(mbrLeido,sizeof(mbr),1,barchivo1);
                                mbrLeido->mbr_partition2 = (partition *)malloc(sizeof(partition));
                                mbrLeido->mbr_partition2->part_size = tama;
                                mbrLeido->mbr_partition2->part_start = sizeof(mbrLeido) + mbrLeido->mbr_partition1->part_size;
                                strcpy(mbrLeido->mbr_partition2->part_fit,letraFit);
                                strcpy(mbrLeido->mbr_partition2->part_name,letraName);
                                strcpy(mbrLeido->mbr_partition2->part_type,letraType);
                                mbrLeido->mbr_partition2->part_status = 1;

                                fseek(barchivo1,0,SEEK_SET);
                                fwrite(mbrLeido,sizeof(mbr)+ sizeof( partition),1,barchivo1);
                                fseek(barchivo1,0,SEEK_SET);
                                fread(mbrLeido1,sizeof(mbr),1,barchivo1);
                                ebr *ebrInicial = (ebr *)malloc(sizeof(ebr));
                                ebr *ebrInicial2 = (ebr *)malloc(sizeof(ebr));
                                strcpy(ebrInicial->part_fit,letraFit);
                                strcpy(ebrInicial->part_name,letraName);
                                ebrInicial->part_size = 0;
                                ebrInicial->part_start = mbrLeido->mbr_partition2->part_start;
                                ebrInicial->part_next = -1;


                                fseek(barchivo1,sizeof(mbr)+ sizeof( partition),SEEK_CUR);
                                fwrite(ebrInicial,sizeof(ebr),1,barchivo1);

                                fseek(barchivo1,0,SEEK_SET);
                                fread(mbrLeido2,sizeof(mbr),1,barchivo1);

                                fseek(barchivo1,sizeof(mbr)+ sizeof( partition),SEEK_CUR);
                                fread(ebrInicial2,sizeof(ebr),1,barchivo1);
                                fclose(barchivo1);
                                printf("\n**Particion extendida creada con exito.**\n");
                                acceso = 1;
                            }else{
                                if(tama <= (compro->mbr_partition4->part_start - (compro->mbr_partition1->part_size + sizeof(mbr)))){
                                    mbr *mbrLeido = (mbr *)malloc(sizeof(mbr));
                                    mbr *mbrLeido1 = (mbr *)malloc(sizeof(mbr));
                                    mbr *mbrLeido2 = (mbr *)malloc(sizeof(mbr));
                                    mbrLeido1->mbr_partition2 = (partition *)malloc(sizeof(partition));
                                    FILE *barchivo1 = fopen(direccion,"r+b");
                                    fseek(barchivo1,0,SEEK_SET);
                                    fread(mbrLeido,sizeof(mbr),1,barchivo1);
                                    mbrLeido->mbr_partition2 = (partition *)malloc(sizeof(partition));
                                    mbrLeido->mbr_partition2->part_size = tama;
                                    mbrLeido->mbr_partition2->part_start = sizeof(mbrLeido) + mbrLeido->mbr_partition1->part_size;
                                    strcpy(mbrLeido->mbr_partition2->part_fit,letraFit);
                                    strcpy(mbrLeido->mbr_partition2->part_name,letraName);
                                    strcpy(mbrLeido->mbr_partition2->part_type,letraType);
                                    mbrLeido->mbr_partition2->part_status = 1;

                                    fseek(barchivo1,0,SEEK_SET);
                                    fwrite(mbrLeido,sizeof(mbr)+ sizeof( partition),1,barchivo1);
                                    fseek(barchivo1,0,SEEK_SET);
                                    fread(mbrLeido1,sizeof(mbr),1,barchivo1);
                                    ebr *ebrInicial = (ebr *)malloc(sizeof(ebr));
                                    ebr *ebrInicial2 = (ebr *)malloc(sizeof(ebr));
                                    strcpy(ebrInicial->part_fit,letraFit);
                                    strcpy(ebrInicial->part_name,letraName);
                                    ebrInicial->part_status = 1;
                                    ebrInicial->part_size = 0;
                                    ebrInicial->part_start = mbrLeido->mbr_partition2->part_start;
                                    ebrInicial->part_next = -1;


                                    fseek(barchivo1,sizeof(mbr)+ sizeof( partition),SEEK_CUR);
                                    fwrite(ebrInicial,sizeof(ebr),1,barchivo1);

                                    fseek(barchivo1,0,SEEK_SET);
                                    fread(mbrLeido2,sizeof(mbr),1,barchivo1);

                                    fseek(barchivo1,sizeof(mbr)+ sizeof( partition),SEEK_CUR);
                                    fread(ebrInicial2,sizeof(ebr),1,barchivo1);
                                    fclose(barchivo1);
                                    printf("\n**Particion extendida creada con exito.**\n");
                                    acceso = 1;
                                }
                            }
                        }else{
                            if(tama <= (compro->mbr_partition3->part_start - (compro->mbr_partition1->part_size + sizeof(mbr)))){
                                mbr *mbrLeido = (mbr *)malloc(sizeof(mbr));
                                mbr *mbrLeido1 = (mbr *)malloc(sizeof(mbr));
                                mbr *mbrLeido2 = (mbr *)malloc(sizeof(mbr));
                                mbrLeido1->mbr_partition2 = (partition *)malloc(sizeof(partition));
                                FILE *barchivo1 = fopen(direccion,"r+b");
                                fseek(barchivo1,0,SEEK_SET);
                                fread(mbrLeido,sizeof(mbr),1,barchivo1);
                                mbrLeido->mbr_partition2 = (partition *)malloc(sizeof(partition));
                                mbrLeido->mbr_partition2->part_size = tama;
                                mbrLeido->mbr_partition2->part_start = sizeof(mbrLeido) + mbrLeido->mbr_partition1->part_size;
                                strcpy(mbrLeido->mbr_partition2->part_fit,letraFit);
                                strcpy(mbrLeido->mbr_partition2->part_name,letraName);
                                strcpy(mbrLeido->mbr_partition2->part_type,letraType);
                                mbrLeido->mbr_partition2->part_status = 1;

                                fseek(barchivo1,0,SEEK_SET);
                                fwrite(mbrLeido,sizeof(mbr)+ sizeof( partition),1,barchivo1);
                                fseek(barchivo1,0,SEEK_SET);
                                fread(mbrLeido1,sizeof(mbr),1,barchivo1);
                                ebr *ebrInicial = (ebr *)malloc(sizeof(ebr));
                                ebr *ebrInicial2 = (ebr *)malloc(sizeof(ebr));
                                strcpy(ebrInicial->part_fit,letraFit);
                                strcpy(ebrInicial->part_name,letraName);
                                ebrInicial->part_status = 1;
                                ebrInicial->part_size = 0;
                                ebrInicial->part_start = mbrLeido->mbr_partition2->part_start;
                                ebrInicial->part_next = -1;


                                fseek(barchivo1,sizeof(mbr)+ sizeof( partition),SEEK_CUR);
                                fwrite(ebrInicial,sizeof(ebr),1,barchivo1);

                                fseek(barchivo1,0,SEEK_SET);
                                fread(mbrLeido2,sizeof(mbr),1,barchivo1);

                                fseek(barchivo1,sizeof(mbr)+ sizeof( partition),SEEK_CUR);
                                fread(ebrInicial2,sizeof(ebr),1,barchivo1);
                                fclose(barchivo1);
                                printf("\n**Particion extendida creada con exito.**\n");
                                acceso = 1;
                            }
                        }
                    }
                    if(strcmp(compro->mbr_partition3->part_type,"x") == 0 && acceso == 0){
                        if(strcmp(compro->mbr_partition4->part_type,"x") == 0){
                            mbr *mbrLeido = (mbr *)malloc(sizeof(mbr));
                            mbr *mbrLeido1 = (mbr *)malloc(sizeof(mbr));
                            mbr *mbrLeido2 = (mbr *)malloc(sizeof(mbr));
                            mbrLeido1->mbr_partition3 = (partition *)malloc(sizeof(partition));
                            FILE *barchivo1 = fopen(direccion,"r+b");
                            fseek(barchivo1,0,SEEK_SET);
                            fread(mbrLeido,sizeof(mbr),1,barchivo1);
                            mbrLeido->mbr_partition3 = (partition *)malloc(sizeof(partition));
                            mbrLeido->mbr_partition3->part_size = tama;
                            mbrLeido->mbr_partition3->part_start = sizeof(mbrLeido) + (mbrLeido->mbr_partition2->part_start + mbrLeido->mbr_partition2->part_size);
                            strcpy(mbrLeido->mbr_partition3->part_fit,letraFit);
                            strcpy(mbrLeido->mbr_partition3->part_name,letraName);
                            strcpy(mbrLeido->mbr_partition3->part_type,letraType);
                            mbrLeido->mbr_partition3->part_status = 1;

                            fseek(barchivo1,0,SEEK_SET);
                            fwrite(mbrLeido,sizeof(mbr)+ sizeof( partition),1,barchivo1);
                            fseek(barchivo1,0,SEEK_SET);
                            fread(mbrLeido1,sizeof(mbr),1,barchivo1);
                            ebr *ebrInicial = (ebr *)malloc(sizeof(ebr));
                            ebr *ebrInicial2 = (ebr *)malloc(sizeof(ebr));
                            strcpy(ebrInicial->part_fit,letraFit);
                            strcpy(ebrInicial->part_name,letraName);
                            ebrInicial->part_status = 1;
                            ebrInicial->part_size = 0;
                            ebrInicial->part_start = mbrLeido->mbr_partition3->part_start;
                            ebrInicial->part_next = -1;


                            fseek(barchivo1,sizeof(mbr)+ sizeof( partition),SEEK_CUR);
                            fwrite(ebrInicial,sizeof(ebr),1,barchivo1);

                            fseek(barchivo1,0,SEEK_SET);
                            fread(mbrLeido2,sizeof(mbr),1,barchivo1);

                            fseek(barchivo1,sizeof(mbr)+ sizeof( partition),SEEK_CUR);
                            fread(ebrInicial2,sizeof(ebr),1,barchivo1);
                            fclose(barchivo1);
                            printf("\n**Particion extendida creada con exito.**\n");
                            acceso = 1;
                        }else{
                            if(tama <= (compro->mbr_partition4->part_start - (compro->mbr_partition2->part_start + compro->mbr_partition2->part_size))){
                                mbr *mbrLeido = (mbr *)malloc(sizeof(mbr));
                                mbr *mbrLeido1 = (mbr *)malloc(sizeof(mbr));
                                mbr *mbrLeido2 = (mbr *)malloc(sizeof(mbr));
                                mbrLeido1->mbr_partition3 = (partition *)malloc(sizeof(partition));
                                FILE *barchivo1 = fopen(direccion,"r+b");
                                fseek(barchivo1,0,SEEK_SET);
                                fread(mbrLeido,sizeof(mbr),1,barchivo1);
                                mbrLeido->mbr_partition3 = (partition *)malloc(sizeof(partition));
                                mbrLeido->mbr_partition3->part_size = tama;
                                mbrLeido->mbr_partition3->part_start = sizeof(mbrLeido) + (mbrLeido->mbr_partition2->part_start + mbrLeido->mbr_partition2->part_size);
                                strcpy(mbrLeido->mbr_partition3->part_fit,letraFit);
                                strcpy(mbrLeido->mbr_partition3->part_name,letraName);
                                strcpy(mbrLeido->mbr_partition3->part_type,letraType);
                                mbrLeido->mbr_partition3->part_status = 1;

                                fseek(barchivo1,0,SEEK_SET);
                                fwrite(mbrLeido,sizeof(mbr)+ sizeof( partition),1,barchivo1);
                                fseek(barchivo1,0,SEEK_SET);
                                fread(mbrLeido1,sizeof(mbr),1,barchivo1);
                                ebr *ebrInicial = (ebr *)malloc(sizeof(ebr));
                                ebr *ebrInicial2 = (ebr *)malloc(sizeof(ebr));
                                strcpy(ebrInicial->part_fit,letraFit);
                                strcpy(ebrInicial->part_name,letraName);
                                ebrInicial->part_status = 1;
                                ebrInicial->part_size = 0;
                                ebrInicial->part_start = mbrLeido->mbr_partition3->part_start;

                                fseek(barchivo1,sizeof(mbr)+ sizeof( partition),SEEK_CUR);
                                fwrite(ebrInicial,sizeof(ebr),1,barchivo1);

                                fseek(barchivo1,0,SEEK_SET);
                                fread(mbrLeido2,sizeof(mbr),1,barchivo1);

                                fseek(barchivo1,sizeof(mbr)+ sizeof( partition),SEEK_CUR);
                                fread(ebrInicial2,sizeof(ebr),1,barchivo1);
                                fclose(barchivo1);
                                printf("\n**Particion extendida creada con exito.**\n");
                                acceso = 1;
                            }
                        }
                    }
                    if(strcmp(compro->mbr_partition4->part_type,"x") == 0 && acceso == 0){
                        mbr *mbrLeido = (mbr *)malloc(sizeof(mbr));
                        mbr *mbrLeido1 = (mbr *)malloc(sizeof(mbr));
                        mbr *mbrLeido2 = (mbr *)malloc(sizeof(mbr));
                        mbrLeido1->mbr_partition4 = (partition *)malloc(sizeof(partition));
                        FILE *barchivo1 = fopen(direccion,"r+b");
                        fseek(barchivo1,0,SEEK_SET);
                        fread(mbrLeido,sizeof(mbr),1,barchivo1);
                        mbrLeido->mbr_partition4 = (partition *)malloc(sizeof(partition));
                        mbrLeido->mbr_partition4->part_size = tama;
                        mbrLeido->mbr_partition4->part_start = sizeof(mbrLeido) + mbrLeido->mbr_partition3->part_start + mbrLeido->mbr_partition3->part_size;
                        strcpy(mbrLeido->mbr_partition4->part_fit,letraFit);
                        strcpy(mbrLeido->mbr_partition4->part_name,letraName);
                        strcpy(mbrLeido->mbr_partition4->part_type,letraType);
                        mbrLeido->mbr_partition4->part_status = 1;

                        fseek(barchivo1,0,SEEK_SET);
                        fwrite(mbrLeido,sizeof(mbr)+ sizeof( partition),1,barchivo1);
                        fseek(barchivo1,0,SEEK_SET);
                        fread(mbrLeido1,sizeof(mbr),1,barchivo1);
                        ebr *ebrInicial = (ebr *)malloc(sizeof(ebr));
                        ebr *ebrInicial2 = (ebr *)malloc(sizeof(ebr));
                        strcpy(ebrInicial->part_fit,letraFit);
                        strcpy(ebrInicial->part_name,letraName);
                        ebrInicial->part_status = 1;
                        ebrInicial->part_size = 0;
                        ebrInicial->part_start = mbrLeido->mbr_partition4->part_start;
                        ebrInicial->part_next = -1;


                        fseek(barchivo1,sizeof(mbr)+ sizeof( partition),SEEK_CUR);
                        fwrite(ebrInicial,sizeof(ebr),1,barchivo1);

                        fseek(barchivo1,0,SEEK_SET);
                        fread(mbrLeido2,sizeof(mbr),1,barchivo1);

                        fseek(barchivo1,sizeof(mbr)+ sizeof( partition),SEEK_CUR);
                        fread(ebrInicial2,sizeof(ebr),1,barchivo1);
                        fclose(barchivo1);
                        printf("\n**Particion extendida creada con exito.**\n");
                        acceso = 1;
                    }
                }else{
                    printf("\nERROR. No hay espacio.\n");
                }
            }

            //Para crear las primarias.
        }else if(strcmp(letraType,"p") == 0){
            if(strcmp(compro->mbr_partition1->part_type,"p") == 0 )
                primarias++;
            if(strcmp(compro->mbr_partition2->part_type,"p") == 0 )
                primarias++;
            if(strcmp(compro->mbr_partition3->part_type,"p") == 0 )
                primarias++;
            if(strcmp(compro->mbr_partition4->part_type,"p") == 0 )
                primarias++;

            if(primarias < 3){
                if(espacioLibreEnDisco > 0 && espacioLibreEnDisco >= tama){
                    if(strcmp(compro->mbr_partition1->part_type,"x") == 0){
                        if(strcmp(compro->mbr_partition2->part_type,"x") == 0){
                            if(strcmp(compro->mbr_partition3->part_type,"x") == 0){
                                if(strcmp(compro->mbr_partition4->part_type,"x") == 0){
                                    mbr *mbrLeido = (mbr *)malloc(sizeof(mbr));
                                    mbr *mbrLeido1 = (mbr *)malloc(sizeof(mbr));
                                    mbrLeido1->mbr_partition1 = (partition *)malloc(sizeof(partition));
                                    FILE *barchivo1 = fopen(direccion,"r+b");
                                    fseek(barchivo1,0,SEEK_SET);
                                    fread(mbrLeido,sizeof(mbr),1,barchivo1);
                                    mbrLeido->mbr_partition1 = (partition *)malloc(sizeof(partition));
                                    mbrLeido->mbr_partition1->part_size = tama;
                                    mbrLeido->mbr_partition1->part_start = sizeof(mbrLeido);
                                    strcpy(mbrLeido->mbr_partition1->part_fit,letraFit);
                                    strcpy(mbrLeido->mbr_partition1->part_name,letraName);
                                    strcpy(mbrLeido->mbr_partition1->part_type,letraType);
                                    mbrLeido->mbr_partition1->part_status = 1;

                                    fseek(barchivo1,0,SEEK_SET);
                                    fwrite(mbrLeido,sizeof(mbr)+ sizeof( partition),1,barchivo1);
                                    fseek(barchivo1,0,SEEK_SET);
                                    fread(mbrLeido1,sizeof(mbr),1,barchivo1);
                                    fclose(barchivo1);
                                    printf("\n**Particion primaria creada con exito.**\n");
                                    acceso = 1;
                                }else{
                                    if(tama <= compro->mbr_partition4->part_start){
                                        mbr *mbrLeido = (mbr *)malloc(sizeof(mbr));
                                        mbr *mbrLeido1 = (mbr *)malloc(sizeof(mbr));
                                        mbrLeido1->mbr_partition1 = (partition *)malloc(sizeof(partition));
                                        FILE *barchivo1 = fopen(direccion,"r+b");
                                        fseek(barchivo1,0,SEEK_SET);
                                        fread(mbrLeido,sizeof(mbr),1,barchivo1);
                                        mbrLeido->mbr_partition1 = (partition *)malloc(sizeof(partition));
                                        mbrLeido->mbr_partition1->part_size = tama;
                                        mbrLeido->mbr_partition1->part_start = sizeof(mbrLeido);
                                        strcpy(mbrLeido->mbr_partition1->part_fit,letraFit);
                                        strcpy(mbrLeido->mbr_partition1->part_name,letraName);
                                        strcpy(mbrLeido->mbr_partition1->part_type,letraType);
                                        mbrLeido->mbr_partition1->part_status = 1;

                                        fseek(barchivo1,0,SEEK_SET);
                                        fwrite(mbrLeido,sizeof(mbr)+ sizeof( partition),1,barchivo1);
                                        fseek(barchivo1,0,SEEK_SET);
                                        fread(mbrLeido1,sizeof(mbr),1,barchivo1);
                                        fclose(barchivo1);
                                        printf("\n**Particion primaria creada con exito.**\n");
                                        acceso = 1;
                                    }
                                }
                            }else{
                                if(tama <= compro->mbr_partition3->part_start){
                                    mbr *mbrLeido = (mbr *)malloc(sizeof(mbr));
                                    mbr *mbrLeido1 = (mbr *)malloc(sizeof(mbr));
                                    mbrLeido1->mbr_partition1 = (partition *)malloc(sizeof(partition));
                                    FILE *barchivo1 = fopen(direccion,"r+b");
                                    fseek(barchivo1,0,SEEK_SET);
                                    fread(mbrLeido,sizeof(mbr),1,barchivo1);
                                    mbrLeido->mbr_partition1 = (partition *)malloc(sizeof(partition));
                                    mbrLeido->mbr_partition1->part_size = tama;
                                    mbrLeido->mbr_partition1->part_start = sizeof(mbrLeido);
                                    strcpy(mbrLeido->mbr_partition1->part_fit,letraFit);
                                    strcpy(mbrLeido->mbr_partition1->part_name,letraName);
                                    strcpy(mbrLeido->mbr_partition1->part_type,letraType);
                                    mbrLeido->mbr_partition1->part_status = 1;

                                    fseek(barchivo1,0,SEEK_SET);
                                    fwrite(mbrLeido,sizeof(mbr)+ sizeof( partition),1,barchivo1);
                                    fseek(barchivo1,0,SEEK_SET);
                                    fread(mbrLeido1,sizeof(mbr),1,barchivo1);
                                    fclose(barchivo1);
                                    printf("\n**Particion primaria creada con exito.**\n");
                                    acceso = 1;
                                }
                            }
                        }else{
                            if(tama <= compro->mbr_partition2->part_start){
                                mbr *mbrLeido = (mbr *)malloc(sizeof(mbr));
                                mbr *mbrLeido1 = (mbr *)malloc(sizeof(mbr));
                                mbrLeido1->mbr_partition1 = (partition *)malloc(sizeof(partition));
                                FILE *barchivo1 = fopen(direccion,"r+b");
                                fseek(barchivo1,0,SEEK_SET);
                                fread(mbrLeido,sizeof(mbr),1,barchivo1);
                                mbrLeido->mbr_partition1 = (partition *)malloc(sizeof(partition));
                                mbrLeido->mbr_partition1->part_size = tama;
                                mbrLeido->mbr_partition1->part_start = sizeof(mbrLeido);
                                strcpy(mbrLeido->mbr_partition1->part_fit,letraFit);
                                strcpy(mbrLeido->mbr_partition1->part_name,letraName);
                                strcpy(mbrLeido->mbr_partition1->part_type,letraType);
                                mbrLeido->mbr_partition1->part_status = 1;

                                fseek(barchivo1,0,SEEK_SET);
                                fwrite(mbrLeido,sizeof(mbr)+ sizeof( partition),1,barchivo1);
                                fseek(barchivo1,0,SEEK_SET);
                                fread(mbrLeido1,sizeof(mbr),1,barchivo1);
                                fclose(barchivo1);
                                printf("\n**Particion primaria creada con exito.**\n");
                                acceso = 1;
                            }
                        }
                    }
                    if(strcmp(compro->mbr_partition2->part_type,"x") == 0 && acceso == 0){
                        if(strcmp(compro->mbr_partition3->part_type,"x") == 0){
                            if(strcmp(compro->mbr_partition4->part_type,"x") == 0){
                                mbr *mbrLeido = (mbr *)malloc(sizeof(mbr));
                                mbr *mbrLeido1 = (mbr *)malloc(sizeof(mbr));
                                mbrLeido1->mbr_partition2 = (partition *)malloc(sizeof(partition));
                                FILE *barchivo1 = fopen(direccion,"r+b");
                                fseek(barchivo1,0,SEEK_SET);
                                fread(mbrLeido,sizeof(mbr),1,barchivo1);
                                mbrLeido->mbr_partition2 = (partition *)malloc(sizeof(partition));
                                mbrLeido->mbr_partition2->part_size = tama;
                                mbrLeido->mbr_partition2->part_start = sizeof(mbrLeido) + mbrLeido->mbr_partition1->part_size;
                                strcpy(mbrLeido->mbr_partition2->part_fit,letraFit);
                                strcpy(mbrLeido->mbr_partition2->part_name,letraName);
                                strcpy(mbrLeido->mbr_partition2->part_type,letraType);
                                mbrLeido->mbr_partition2->part_status = 1;

                                fseek(barchivo1,0,SEEK_SET);
                                fwrite(mbrLeido,sizeof(mbr)+ sizeof( partition),1,barchivo1);
                                fseek(barchivo1,0,SEEK_SET);
                                fread(mbrLeido1,sizeof(mbr),1,barchivo1);
                                fclose(barchivo1);
                                printf("\n**Particion primaria creada con exito.**\n");
                                acceso = 1;
                            }else{
                                if(tama <= (compro->mbr_partition4->part_start - (compro->mbr_partition1->part_size + compro->mbr_partition1->part_start))){
                                    mbr *mbrLeido = (mbr *)malloc(sizeof(mbr));
                                    mbr *mbrLeido1 = (mbr *)malloc(sizeof(mbr));
                                    mbrLeido1->mbr_partition2 = (partition *)malloc(sizeof(partition));
                                    FILE *barchivo1 = fopen(direccion,"r+b");
                                    fseek(barchivo1,0,SEEK_SET);
                                    fread(mbrLeido,sizeof(mbr),1,barchivo1);
                                    mbrLeido->mbr_partition2 = (partition *)malloc(sizeof(partition));
                                    mbrLeido->mbr_partition2->part_size = tama;
                                    mbrLeido->mbr_partition2->part_start = sizeof(mbrLeido) + mbrLeido->mbr_partition1->part_size;
                                    strcpy(mbrLeido->mbr_partition2->part_fit,letraFit);
                                    strcpy(mbrLeido->mbr_partition2->part_name,letraName);
                                    strcpy(mbrLeido->mbr_partition2->part_type,letraType);
                                    mbrLeido->mbr_partition2->part_status = 1;

                                    fseek(barchivo1,0,SEEK_SET);
                                    fwrite(mbrLeido,sizeof(mbr)+ sizeof( partition),1,barchivo1);
                                    fseek(barchivo1,0,SEEK_SET);
                                    fread(mbrLeido1,sizeof(mbr),1,barchivo1);
                                    fclose(barchivo1);
                                    printf("\n**Particion primaria creada con exito.**\n");
                                    acceso = 1;
                                }
                            }
                        }else{
                            if(tama <= (compro->mbr_partition3->part_start - (compro->mbr_partition1->part_size +sizeof(mbr)))){
                                mbr *mbrLeido = (mbr *)malloc(sizeof(mbr));
                                mbr *mbrLeido1 = (mbr *)malloc(sizeof(mbr));
                                mbrLeido1->mbr_partition2 = (partition *)malloc(sizeof(partition));
                                FILE *barchivo1 = fopen(direccion,"r+b");
                                fseek(barchivo1,0,SEEK_SET);
                                fread(mbrLeido,sizeof(mbr),1,barchivo1);
                                mbrLeido->mbr_partition2 = (partition *)malloc(sizeof(partition));
                                mbrLeido->mbr_partition2->part_size = tama;
                                mbrLeido->mbr_partition2->part_start = sizeof(mbrLeido) + mbrLeido->mbr_partition1->part_size;
                                strcpy(mbrLeido->mbr_partition2->part_fit,letraFit);
                                strcpy(mbrLeido->mbr_partition2->part_name,letraName);
                                strcpy(mbrLeido->mbr_partition2->part_type,letraType);
                                mbrLeido->mbr_partition2->part_status = 1;

                                fseek(barchivo1,0,SEEK_SET);
                                fwrite(mbrLeido,sizeof(mbr)+ sizeof( partition),1,barchivo1);
                                fseek(barchivo1,0,SEEK_SET);
                                fread(mbrLeido1,sizeof(mbr),1,barchivo1);
                                fclose(barchivo1);
                                printf("\n**Particion primaria creada con exito.**\n");
                                acceso = 1;
                            }
                        }
                    }
                    if(strcmp(compro->mbr_partition3->part_type,"x") == 0 && acceso == 0){
                        if(strcmp(compro->mbr_partition4->part_type,"x") == 0){
                            mbr *mbrLeido = (mbr *)malloc(sizeof(mbr));
                            mbr *mbrLeido1 = (mbr *)malloc(sizeof(mbr));
                            mbrLeido1->mbr_partition3 = (partition *)malloc(sizeof(partition));
                            FILE *barchivo1 = fopen(direccion,"r+b");
                            fseek(barchivo1,0,SEEK_SET);
                            fread(mbrLeido,sizeof(mbr),1,barchivo1);
                            mbrLeido->mbr_partition3 = (partition *)malloc(sizeof(partition));
                            mbrLeido->mbr_partition3->part_size = tama;
                            mbrLeido->mbr_partition3->part_start = sizeof(mbrLeido) + (mbrLeido->mbr_partition2->part_start + mbrLeido->mbr_partition2->part_size);
                            strcpy(mbrLeido->mbr_partition3->part_fit,letraFit);
                            strcpy(mbrLeido->mbr_partition3->part_name,letraName);
                            strcpy(mbrLeido->mbr_partition3->part_type,letraType);
                            mbrLeido->mbr_partition3->part_status = 1;

                            fseek(barchivo1,0,SEEK_SET);
                            fwrite(mbrLeido,sizeof(mbr)+ sizeof( partition),1,barchivo1);
                            fseek(barchivo1,0,SEEK_SET);
                            fread(mbrLeido1,sizeof(mbr),1,barchivo1);
                            fclose(barchivo1);
                            printf("\n**Particion primaria creada con exito.**\n");
                            acceso = 1;
                        }else{
                            if(tama <= (compro->mbr_partition4->part_start - (compro->mbr_partition2->part_size + compro->mbr_partition2->part_start))){
                                mbr *mbrLeido = (mbr *)malloc(sizeof(mbr));
                                mbr *mbrLeido1 = (mbr *)malloc(sizeof(mbr));
                                mbrLeido1->mbr_partition3 = (partition *)malloc(sizeof(partition));
                                FILE *barchivo1 = fopen(direccion,"r+b");
                                fseek(barchivo1,0,SEEK_SET);
                                fread(mbrLeido,sizeof(mbr),1,barchivo1);
                                mbrLeido->mbr_partition3 = (partition *)malloc(sizeof(partition));
                                mbrLeido->mbr_partition3->part_size = tama;
                                mbrLeido->mbr_partition3->part_start = sizeof(mbrLeido) + (mbrLeido->mbr_partition2->part_start + mbrLeido->mbr_partition2->part_size);
                                strcpy(mbrLeido->mbr_partition3->part_fit,letraFit);
                                strcpy(mbrLeido->mbr_partition3->part_name,letraName);
                                strcpy(mbrLeido->mbr_partition3->part_type,letraType);
                                mbrLeido->mbr_partition3->part_status = 1;

                                fseek(barchivo1,0,SEEK_SET);
                                fwrite(mbrLeido,sizeof(mbr)+ sizeof( partition),1,barchivo1);
                                fseek(barchivo1,0,SEEK_SET);
                                fread(mbrLeido1,sizeof(mbr),1,barchivo1);
                                fclose(barchivo1);
                                printf("\n**Particion primaria creada con exito.**\n");
                                acceso = 1;
                            }
                        }
                    }
                    if(strcmp(compro->mbr_partition4->part_type,"x") == 0 && acceso == 0){
                        mbr *mbrLeido = (mbr *)malloc(sizeof(mbr));
                        mbr *mbrLeido1 = (mbr *)malloc(sizeof(mbr));
                        mbrLeido1->mbr_partition4 = (partition *)malloc(sizeof(partition));
                        FILE *barchivo1 = fopen(direccion,"r+b");
                        fseek(barchivo1,0,SEEK_SET);
                        fread(mbrLeido,sizeof(mbr),1,barchivo1);
                        mbrLeido->mbr_partition4 = (partition *)malloc(sizeof(partition));
                        mbrLeido->mbr_partition4->part_size = tama;
                        mbrLeido->mbr_partition4->part_start = sizeof(mbrLeido) + mbrLeido->mbr_partition3->part_start + mbrLeido->mbr_partition3->part_size;
                        strcpy(mbrLeido->mbr_partition4->part_fit,letraFit);
                        strcpy(mbrLeido->mbr_partition4->part_name,letraName);
                        strcpy(mbrLeido->mbr_partition4->part_type,letraType);
                        mbrLeido->mbr_partition4->part_status = 1;

                        fseek(barchivo1,0,SEEK_SET);
                        fwrite(mbrLeido,sizeof(mbr)+ sizeof( partition),1,barchivo1);
                        fseek(barchivo1,0,SEEK_SET);
                        fread(mbrLeido1,sizeof(mbr),1,barchivo1);
                        fclose(barchivo1);
                        printf("\n**Particion primaria creada con exito.**\n");
                        acceso = 1;
                    }
                }else{
                    printf("\nERROR. No hay espacio.\n");
                }
            }else{
                printf("\nERROR. Limite de particiones primarias permitidas excedido.\n");
            }

            //Para las lógicas.
        }else if(strcmp(letraType,"l") == 0){

            if(strcmp(compro->mbr_partition1->part_type,"e") == 0 || strcmp(compro->mbr_partition2->part_type,"e") == 0 || strcmp(compro->mbr_partition3->part_type,"e") == 0|| strcmp(compro->mbr_partition4->part_type,"e") == 0){

                int tamDeExtendida = 0;
                int espacioDeLogicas = 0;
                int extenndidaEmpieza = 0;
                mbr *mbrLeidoA = (mbr *)malloc(sizeof(mbr));
                FILE *barchivo1A = fopen(direccion,"r+b");

                fseek(barchivo1A,0,SEEK_SET);
                fread(mbrLeidoA,sizeof(mbr),1,barchivo1A);

                ebr *ebrInicial2A = (ebr *)malloc(sizeof(ebr));
                fseek(barchivo1A,sizeof(mbr)+ sizeof( partition),SEEK_CUR);
                fread(ebrInicial2A,sizeof(ebr),1,barchivo1A);

                if(ebrInicial2A->part_size != 0 && ebrInicial2A->part_start != 0){
                    espacioDeLogicas += ebrInicial2A->part_size;
                    for(int i = 0; i <= 1000; i++){

                            fseek(barchivo1A,0,SEEK_SET);
                            fread(mbrLeidoA,sizeof(mbr),1,barchivo1A);
                            fseek(barchivo1A,sizeof(mbr)+ sizeof( partition) + (i+1)*sizeof(ebr),SEEK_CUR);
                            fread(ebrInicial2A,sizeof(ebr),1,barchivo1A);
                            if(ebrInicial2A->part_size == 0 && ebrInicial2A->part_start == 0)
                                break;
                            if(ebrInicial2A->part_start != 0 && ebrInicial2A->part_size != 0){
                               espacioDeLogicas += ebrInicial2A->part_size;
                            }
                    }
                }

                if(strcmp(mbrLeidoA->mbr_partition1->part_type,"e") == 0){
                    tamDeExtendida = mbrLeidoA->mbr_partition1->part_size;
                    extenndidaEmpieza = mbrLeidoA->mbr_partition1->part_start + mbrLeidoA->mbr_partition1->part_size;
                }else if(strcmp(mbrLeidoA->mbr_partition2->part_type,"e") == 0){
                    tamDeExtendida = mbrLeidoA->mbr_partition2->part_size;
                    extenndidaEmpieza = mbrLeidoA->mbr_partition1->part_start + mbrLeidoA->mbr_partition2->part_size;
                }else if(strcmp(mbrLeidoA->mbr_partition3->part_type,"e") == 0){
                    tamDeExtendida = mbrLeidoA->mbr_partition3->part_size;
                    extenndidaEmpieza = mbrLeidoA->mbr_partition1->part_start + mbrLeidoA->mbr_partition3->part_size;
                }else if(strcmp(mbrLeidoA->mbr_partition4->part_type,"e") == 0){
                    tamDeExtendida = mbrLeidoA->mbr_partition4->part_size;
                    extenndidaEmpieza = mbrLeidoA->mbr_partition1->part_start + mbrLeidoA->mbr_partition4->part_size;
                }

                int res = tamDeExtendida - espacioDeLogicas;
                if(res > 0){
                    if(res >= tama){

                    }else{
                        printf("\nERROR. Tamaño de la particion logica mayor a tamaño disponible en la extendida.\n");
                        return -1;
                    }
                }else{
                    printf("\nERROR. Ya no hay espacio en partición para crear la partición logica.\n");
                    return -1;
                }

                fclose(barchivo1A);

                mbr *mbrLeido = (mbr *)malloc(sizeof(mbr));
                FILE *barchivo1 = fopen(direccion,"r+b");

                fseek(barchivo1,0,SEEK_SET);
                fread(mbrLeido,sizeof(mbr),1,barchivo1);

                ebr *ebrInicial2 = (ebr *)malloc(sizeof(ebr));
                ebr *ebrInicial3 = (ebr *)malloc(sizeof(ebr));
                ebr *ebrInicial22 = (ebr *)malloc(sizeof(ebr));
int control = 0;
int pos = 0;
fseek(barchivo1,sizeof(mbr)+ sizeof( partition),SEEK_CUR);
fread(ebrInicial2,sizeof(ebr),1,barchivo1);
mbr *mbrLeido3 = (mbr *)malloc(sizeof(mbr));


int partSize = 0;
int sizzze = 0;


                while(control != 1){

                    if(ebrInicial2->part_next == -1 && ebrInicial2->part_size == 0){
                        strcpy(ebrInicial2->part_fit,letraFit);
                        strcpy(ebrInicial2->part_name,letraName);
                        ebrInicial2->part_status = 1;
                        ebrInicial2->part_next = -1;
                        ebrInicial2->part_size = tama;
                        ebrInicial2->part_start = extenndidaEmpieza;
                        fseek(barchivo1,0,SEEK_SET);
                        fread(mbrLeido3,sizeof(mbr),1,barchivo1);
                        fseek(barchivo1,sizeof(mbr)+ sizeof( partition),SEEK_CUR);
                        fwrite(ebrInicial2,sizeof(ebr),1,barchivo1);

                        ebr *ebrInicialSIGUIENTE = (ebr *)malloc(sizeof(ebr));
                        ebrInicialSIGUIENTE->part_next = -1;
                        fseek(barchivo1,0,SEEK_SET);
                        fread(mbrLeido3,sizeof(mbr),1,barchivo1);
                        fseek(barchivo1,sizeof(mbr)+ sizeof( partition) + sizeof(ebr),SEEK_CUR);
                        fwrite(ebrInicialSIGUIENTE,sizeof(ebr),1,barchivo1);

                        fclose(barchivo1);
                        printf("\n**Particion logica creada con exito.**\n");
                        control = 1;
                        pos = 0;
                        break;
                    }else{
                        fseek(barchivo1,0,SEEK_SET);
                        fread(mbrLeido,sizeof(mbr),1,barchivo1);
                        fseek(barchivo1,sizeof(mbr)+ sizeof( partition) + sizeof(ebr),SEEK_CUR);
                        fread(ebrInicial2,sizeof(ebr),1,barchivo1);

                        partSize = ebrInicial2->part_start;
                        sizzze = ebrInicial2->part_size;
                        int tt = 0;
                        if(partSize != 0 && sizzze !=0){
                            tt = 1;
                        }

                        fseek(barchivo1,0,SEEK_SET);
                        fread(mbrLeido,sizeof(mbr),1,barchivo1);
                        fseek(barchivo1,sizeof(mbr)+ sizeof( partition),SEEK_CUR);
                        fread(ebrInicial22,sizeof(ebr),1,barchivo1);
                        if(tt == 0){
                            partSize = ebrInicial22->part_start;
                            sizzze = ebrInicial22->part_size;
                        }

                        for(int i = 1; i <= 1000; i++){

                            if(ebrInicial2->part_next == -1 && ebrInicial2->part_size == 0){

                                fseek(barchivo1,0,SEEK_SET);
                                fread(mbrLeido,sizeof(mbr),1,barchivo1);
                                fseek(barchivo1,sizeof(mbr)+ sizeof( partition) + (i - 1)*sizeof(ebr),SEEK_CUR);
                                fread(ebrInicial3,sizeof(ebr),1,barchivo1);
                                ebrInicial3->part_next = partSize + sizzze;
                                fseek(barchivo1,0,SEEK_SET);
                                fread(mbrLeido3,sizeof(mbr),1,barchivo1);
                                fseek(barchivo1,sizeof(mbr)+ sizeof( partition) + (i-1)*sizeof(ebr),SEEK_CUR);
                                fwrite(ebrInicial3,sizeof(ebr),1,barchivo1);

                                strcpy(ebrInicial2->part_fit,letraFit);
                                strcpy(ebrInicial2->part_name,letraName);
                                ebrInicial2->part_status = 1;
                                ebrInicial2->part_next = -1;
                                ebrInicial2->part_size = tama;
                                ebrInicial2->part_start = partSize + sizzze;
                                fseek(barchivo1,0,SEEK_SET);
                                fread(mbrLeido3,sizeof(mbr),1,barchivo1);
                                fseek(barchivo1,sizeof(mbr)+ sizeof( partition) + i*sizeof(ebr),SEEK_CUR);
                                fwrite(ebrInicial2,sizeof(ebr),1,barchivo1);

                                ebr *ebrInicialSIGUIENTE = (ebr *)malloc(sizeof(ebr));
                                ebrInicialSIGUIENTE->part_next = -1;
                                fseek(barchivo1,0,SEEK_SET);
                                fread(mbrLeido3,sizeof(mbr),1,barchivo1);
                                fseek(barchivo1,sizeof(mbr)+ sizeof( partition) + (i+1)*sizeof(ebr),SEEK_CUR);
                                fwrite(ebrInicialSIGUIENTE,sizeof(ebr),1,barchivo1);


                                fclose(barchivo1);
                                printf("\n**Particion logica creada con exito.**\n");
                                control = 1;
                                pos = i;
                                break;
                            }else{
                                fseek(barchivo1,0,SEEK_SET);
                                fread(mbrLeido,sizeof(mbr),1,barchivo1);
                                fseek(barchivo1,sizeof(mbr)+ sizeof( partition) + (i+1)*sizeof(ebr),SEEK_CUR);
                                fread(ebrInicial2,sizeof(ebr),1,barchivo1);
                                if(ebrInicial2->part_start != 0 && ebrInicial2->part_size != 0){
                                    partSize = ebrInicial2->part_start;
                                    sizzze = ebrInicial2->part_size;
                                }
                            }
                        }
                    }
                }

                FILE *barchivo11 = fopen(direccion,"r+b");
                mbr *mbrLeidoE = (mbr *)malloc(sizeof(mbr));
                fseek(barchivo11,0,SEEK_SET);
                fread(mbrLeidoE,sizeof(mbr),1,barchivo11);
                fseek(barchivo11,sizeof(mbr)+ sizeof( partition) + pos*sizeof(ebr),SEEK_CUR);
                fread(ebrInicial22,sizeof(ebr),1,barchivo11);

                fclose(barchivo11);
            }
            }else{
                printf("\nERROR. No existe particion extendida en el disco.\n");
            }

    }


    //Para el comando Delete.
    if(accion == 1){
        FILE *binario = fopen(direccion,"r+b");
        mbr *compro = (mbr *)malloc(sizeof(mbr));
        fseek(binario,0,SEEK_SET);
        fread(compro,sizeof(mbr),1,binario);
        int ai;

        if(binario!=NULL){
            fclose(binario);
            /**---------------------------------------------------------------------------------------------------------------**/
            if(strcmp(compro->mbr_partition1->part_type,"e") == 0){
                ai = 1;
            }else if(strcmp(compro->mbr_partition2->part_type,"e") == 0){
                ai = 1;
            }else if(strcmp(compro->mbr_partition3->part_type,"e") == 0){
                ai = 1;
            }else if(strcmp(compro->mbr_partition4->part_type,"e") == 0){
                ai = 1;
            }
            if(ai == 1){
                mbr *mbrLeidoA = (mbr *)malloc(sizeof(mbr));
                FILE *barchivo1A = fopen(direccion,"r+b");
                ebr *ebrInicial2A = (ebr *)malloc(sizeof(ebr));
                fseek(barchivo1A,0,SEEK_SET);
                fread(mbrLeidoA,sizeof(mbr),1,barchivo1A);
                fseek(barchivo1A,sizeof(mbr)+ sizeof( partition),SEEK_CUR);
                fread(ebrInicial2A,sizeof(ebr),1,barchivo1A);
                int tam = 1;

                if(ebrInicial2A->part_start != 0){
                    for(int i = 0; i <= 1000; i++){

                            fseek(barchivo1A,0,SEEK_SET);
                            fread(mbrLeidoA,sizeof(mbr),1,barchivo1A);
                            fseek(barchivo1A,sizeof(mbr)+ sizeof( partition) + (i)*sizeof(ebr),SEEK_CUR);
                            fread(ebrInicial2A,sizeof(ebr),1,barchivo1A);
                            if(ebrInicial2A->part_size == 0 && ebrInicial2A->part_start == 0){

                                break;
                            }

                            if(strcmp(ebrInicial2A->part_name,letraName) == 0){
                                printf("\n**Particion logica eliminada con exito.**\n");
                                ebrInicial2A->part_size = 0;
                                fseek(barchivo1A,0,SEEK_SET);
                                fread(mbrLeidoA,sizeof(mbr),1,barchivo1A);
                                fseek(barchivo1A,sizeof(mbr)+ sizeof( partition) + (i)*sizeof(ebr),SEEK_CUR);
                                fwrite(ebrInicial2A,sizeof(ebr),1,barchivo1A);
                                fclose(barchivo1A);

                                mbr *mbrLeidoA = (mbr *)malloc(sizeof(mbr));
                                FILE *barchivo1A = fopen(direccion,"r+b");
                                ebr *ebrInicial2A = (ebr *)malloc(sizeof(ebr));
                                fseek(barchivo1A,0,SEEK_SET);
                                fread(mbrLeidoA,sizeof(mbr),1,barchivo1A);
                                fseek(barchivo1A,sizeof(mbr)+ sizeof( partition) + (i)*sizeof(ebr),SEEK_CUR);
                                fread(ebrInicial2A,sizeof(ebr),1,barchivo1A);
                                fclose(barchivo1A);
                                break;
                            }
                    }

                }
            }
            /**---------------------------------------------------------------------------------------------------------------**/
            if(strcmp(compro->mbr_partition1->part_name,letraName) == 0){
                if(strcmp(letraDelete,"full") == 0){
                    mbr *mbrLeido = (mbr *)malloc(sizeof(mbr));
                    mbr *mbrLeido1 = (mbr *)malloc(sizeof(mbr));
                    mbrLeido1->mbr_partition1 = (partition *)malloc(sizeof(partition));
                    FILE *barchivo1 = fopen(direccion,"r+b");
                    fseek(barchivo1,0,SEEK_SET);
                    fread(mbrLeido,sizeof(mbr),1,barchivo1);
                    mbrLeido->mbr_partition1 = (partition *)malloc(sizeof(partition));
                    mbrLeido->mbr_partition1->part_size = 0;
                    mbrLeido->mbr_partition1->part_start = 0;
                    strcpy(mbrLeido->mbr_partition1->part_fit,"");
                    strcpy(mbrLeido->mbr_partition1->part_name,"");
                    strcpy(mbrLeido->mbr_partition1->part_type,"x");

                    fseek(barchivo1,0,SEEK_SET);
                    fwrite(mbrLeido,sizeof(mbr)+ sizeof( partition),1,barchivo1);
                    fseek(barchivo1,0,SEEK_SET);
                    fread(mbrLeido1,sizeof(mbr),1,barchivo1);
                    printf("\n**Particion eliminada con éxito.**\n");
                    fclose(barchivo1);
                }else if(strcmp(letraDelete,"fast") == 0){
                    mbr *mbrLeido = (mbr *)malloc(sizeof(mbr));
                    mbr *mbrLeido1 = (mbr *)malloc(sizeof(mbr));
                    mbrLeido1->mbr_partition1 = (partition *)malloc(sizeof(partition));
                    FILE *barchivo1 = fopen(direccion,"r+b");
                    fseek(barchivo1,0,SEEK_SET);
                    fread(mbrLeido,sizeof(mbr),1,barchivo1);
                    mbrLeido->mbr_partition1 = (partition *)malloc(sizeof(partition));
                    mbrLeido->mbr_partition1->part_size = 0;
                    mbrLeido->mbr_partition1->part_start = 0;
                    strcpy(mbrLeido->mbr_partition1->part_fit,"");
                    strcpy(mbrLeido->mbr_partition1->part_name,"");
                    strcpy(mbrLeido->mbr_partition1->part_type,"x");

                    fseek(barchivo1,0,SEEK_SET);
                    fwrite(mbrLeido,sizeof(mbr)+ sizeof( partition),1,barchivo1);
                    fseek(barchivo1,0,SEEK_SET);
                    fread(mbrLeido1,sizeof(mbr),1,barchivo1);
                    printf("\n**Particion eliminada con éxito.**\n");
                    fclose(barchivo1);
                }
            }else if(strcmp(compro->mbr_partition2->part_name,letraName) == 0){
                if(strcmp(letraDelete,"full") == 0){
                    mbr *mbrLeido = (mbr *)malloc(sizeof(mbr));
                    mbr *mbrLeido1 = (mbr *)malloc(sizeof(mbr));
                    mbrLeido1->mbr_partition2 = (partition *)malloc(sizeof(partition));
                    FILE *barchivo1 = fopen(direccion,"r+b");
                    fseek(barchivo1,0,SEEK_SET);
                    fread(mbrLeido,sizeof(mbr),1,barchivo1);
                    mbrLeido->mbr_partition2 = (partition *)malloc(sizeof(partition));
                    mbrLeido->mbr_partition2->part_size = 0;
                    mbrLeido->mbr_partition2->part_start = 0;
                    strcpy(mbrLeido->mbr_partition2->part_fit,"");
                    strcpy(mbrLeido->mbr_partition2->part_name,"");
                    strcpy(mbrLeido->mbr_partition2->part_type,"x");

                    fseek(barchivo1,0,SEEK_SET);
                    fwrite(mbrLeido,sizeof(mbr)+ sizeof( partition),1,barchivo1);
                    fseek(barchivo1,0,SEEK_SET);
                    fread(mbrLeido1,sizeof(mbr),1,barchivo1);
                    printf("\n**Particion eliminada con éxito.**\n");
                    fclose(barchivo1);
                }else if(strcmp(letraDelete,"fast") == 0){
                    mbr *mbrLeido = (mbr *)malloc(sizeof(mbr));
                    mbr *mbrLeido1 = (mbr *)malloc(sizeof(mbr));
                    mbrLeido1->mbr_partition2 = (partition *)malloc(sizeof(partition));
                    FILE *barchivo1 = fopen(direccion,"r+b");
                    fseek(barchivo1,0,SEEK_SET);
                    fread(mbrLeido,sizeof(mbr),1,barchivo1);
                    mbrLeido->mbr_partition2 = (partition *)malloc(sizeof(partition));
                    mbrLeido->mbr_partition2->part_size = 0;
                    mbrLeido->mbr_partition2->part_start = 0;
                    strcpy(mbrLeido->mbr_partition2->part_fit,"");
                    strcpy(mbrLeido->mbr_partition2->part_name,"");
                    strcpy(mbrLeido->mbr_partition2->part_type,"x");

                    fseek(barchivo1,0,SEEK_SET);
                    fwrite(mbrLeido,sizeof(mbr)+ sizeof( partition),1,barchivo1);
                    fseek(barchivo1,0,SEEK_SET);
                    fread(mbrLeido1,sizeof(mbr),1,barchivo1);
                    printf("\n**Particion eliminada con éxito.**\n");
                    fclose(barchivo1);
                }
            }else if(strcmp(compro->mbr_partition3->part_name,letraName) == 0){
                if(strcmp(letraDelete,"full") == 0){
                    mbr *mbrLeido = (mbr *)malloc(sizeof(mbr));
                    mbr *mbrLeido1 = (mbr *)malloc(sizeof(mbr));
                    mbrLeido1->mbr_partition3 = (partition *)malloc(sizeof(partition));
                    FILE *barchivo1 = fopen(direccion,"r+b");
                    fseek(barchivo1,0,SEEK_SET);
                    fread(mbrLeido,sizeof(mbr),1,barchivo1);
                    mbrLeido->mbr_partition3 = (partition *)malloc(sizeof(partition));
                    mbrLeido->mbr_partition3->part_size = 0;
                    mbrLeido->mbr_partition3->part_start = 0;
                    strcpy(mbrLeido->mbr_partition3->part_fit,"");
                    strcpy(mbrLeido->mbr_partition3->part_name,"");
                    strcpy(mbrLeido->mbr_partition3->part_type,"x");

                    fseek(barchivo1,0,SEEK_SET);
                    fwrite(mbrLeido,sizeof(mbr)+ sizeof( partition),1,barchivo1);
                    fseek(barchivo1,0,SEEK_SET);
                    fread(mbrLeido1,sizeof(mbr),1,barchivo1);
                    printf("\n**Particion eliminada con éxito.**\n");
                    fclose(barchivo1);
                }else if(strcmp(letraDelete,"fast") == 0){
                    mbr *mbrLeido = (mbr *)malloc(sizeof(mbr));
                    mbr *mbrLeido1 = (mbr *)malloc(sizeof(mbr));
                    mbrLeido1->mbr_partition3 = (partition *)malloc(sizeof(partition));
                    FILE *barchivo1 = fopen(direccion,"r+b");
                    fseek(barchivo1,0,SEEK_SET);
                    fread(mbrLeido,sizeof(mbr),1,barchivo1);
                    mbrLeido->mbr_partition3 = (partition *)malloc(sizeof(partition));
                    mbrLeido->mbr_partition3->part_size = 0;
                    mbrLeido->mbr_partition3->part_start = 0;
                    strcpy(mbrLeido->mbr_partition3->part_fit,"");
                    strcpy(mbrLeido->mbr_partition3->part_name,"");
                    strcpy(mbrLeido->mbr_partition3->part_type,"x");

                    fseek(barchivo1,0,SEEK_SET);
                    fwrite(mbrLeido,sizeof(mbr)+ sizeof( partition),1,barchivo1);
                    fseek(barchivo1,0,SEEK_SET);
                    fread(mbrLeido1,sizeof(mbr),1,barchivo1);
                    printf("\n**Particion eliminada con éxito.**\n");
                    fclose(barchivo1);
                }
            }else if(strcmp(compro->mbr_partition4->part_name,letraName) == 0){
                if(strcmp(letraDelete,"full") == 0){
                    mbr *mbrLeido = (mbr *)malloc(sizeof(mbr));
                    mbr *mbrLeido1 = (mbr *)malloc(sizeof(mbr));
                    mbrLeido1->mbr_partition4 = (partition *)malloc(sizeof(partition));
                    FILE *barchivo1 = fopen(direccion,"r+b");
                    fseek(barchivo1,0,SEEK_SET);
                    fread(mbrLeido,sizeof(mbr),1,barchivo1);
                    mbrLeido->mbr_partition4 = (partition *)malloc(sizeof(partition));
                    mbrLeido->mbr_partition4->part_size = 0;
                    mbrLeido->mbr_partition4->part_start = 0;
                    strcpy(mbrLeido->mbr_partition4->part_fit,"");
                    strcpy(mbrLeido->mbr_partition4->part_name,"");
                    strcpy(mbrLeido->mbr_partition4->part_type,"x");

                    fseek(barchivo1,0,SEEK_SET);
                    fwrite(mbrLeido,sizeof(mbr)+ sizeof( partition),1,barchivo1);
                    fseek(barchivo1,0,SEEK_SET);
                    fread(mbrLeido1,sizeof(mbr),1,barchivo1);
                    printf("\n**Particion eliminada con éxito.**\n");
                    fclose(barchivo1);
                }else if(strcmp(letraDelete,"fast") == 0){
                    mbr *mbrLeido = (mbr *)malloc(sizeof(mbr));
                    mbr *mbrLeido1 = (mbr *)malloc(sizeof(mbr));
                    mbrLeido1->mbr_partition4 = (partition *)malloc(sizeof(partition));
                    FILE *barchivo1 = fopen(direccion,"r+b");
                    fseek(barchivo1,0,SEEK_SET);
                    fread(mbrLeido,sizeof(mbr),1,barchivo1);
                    mbrLeido->mbr_partition4 = (partition *)malloc(sizeof(partition));
                    mbrLeido->mbr_partition4->part_size = 0;
                    mbrLeido->mbr_partition4->part_start = 0;
                    strcpy(mbrLeido->mbr_partition4->part_fit,"");
                    strcpy(mbrLeido->mbr_partition4->part_name,"");
                    strcpy(mbrLeido->mbr_partition4->part_type,"x");

                    fseek(barchivo1,0,SEEK_SET);
                    fwrite(mbrLeido,sizeof(mbr)+ sizeof( partition),1,barchivo1);
                    fseek(barchivo1,0,SEEK_SET);
                    fread(mbrLeido1,sizeof(mbr),1,barchivo1);
                    printf("\n**Particion eliminada con éxito.**\n");
                    fclose(barchivo1);
                }
            }

        }else{
            printf("\nERROR. No existe el disco.\n");
        }
    }

    //Para agregar o quitar tamaño.
    if(accion == 2){
        if(tamaAdd < 0){
            /*SE QUITA*/
            if(strcmp(compro->mbr_partition1->part_name,letraName) == 0){
                mbr *mbrLeido = (mbr *)malloc(sizeof(mbr));
                mbr *mbrLeido1 = (mbr *)malloc(sizeof(mbr));
                mbrLeido1->mbr_partition1 = (partition *)malloc(sizeof(partition));
                FILE *barchivo1 = fopen(direccion,"r+b");
                fseek(barchivo1,0,SEEK_SET);
                fread(mbrLeido,sizeof(mbr),1,barchivo1);
                int ao = mbrLeido->mbr_partition1->part_size + tamaAdd;
                if(ao < 0){
                    printf("\nERROR. Tamaño a quitar es mayor que el tamaño de la particion.\n");
                }else{
                    mbrLeido->mbr_partition1->part_size = ao;
                    printf("\n**Espacio quitado con éxito**\n");
                }
                fseek(barchivo1,0,SEEK_SET);
                fwrite(mbrLeido,sizeof(mbr)+ sizeof( partition),1,barchivo1);
                fseek(barchivo1,0,SEEK_SET);
                fread(mbrLeido1,sizeof(mbr),1,barchivo1);
                fclose(barchivo1);
            }else if(strcmp(compro->mbr_partition2->part_name,letraName) == 0){
                mbr *mbrLeido = (mbr *)malloc(sizeof(mbr));
                mbr *mbrLeido1 = (mbr *)malloc(sizeof(mbr));
                mbrLeido1->mbr_partition2 = (partition *)malloc(sizeof(partition));
                FILE *barchivo1 = fopen(direccion,"r+b");
                fseek(barchivo1,0,SEEK_SET);
                fread(mbrLeido,sizeof(mbr),1,barchivo1);
                int ao = mbrLeido->mbr_partition2->part_size + tamaAdd;
                if(ao < 0){
                    printf("\nERROR. Tamaño a quitar es mayor que el tamaño de la particion.\n");
                }else{
                    mbrLeido->mbr_partition2->part_size = ao;
                    printf("\n**Espacio quitado con éxito**\n");
                }
                fseek(barchivo1,0,SEEK_SET);
                fwrite(mbrLeido,sizeof(mbr)+ sizeof( partition),1,barchivo1);
                fseek(barchivo1,0,SEEK_SET);
                fread(mbrLeido1,sizeof(mbr),1,barchivo1);
                fclose(barchivo1);
            }else if(strcmp(compro->mbr_partition3->part_name,letraName) == 0){
                mbr *mbrLeido = (mbr *)malloc(sizeof(mbr));
                mbr *mbrLeido1 = (mbr *)malloc(sizeof(mbr));
                mbrLeido1->mbr_partition3 = (partition *)malloc(sizeof(partition));
                FILE *barchivo1 = fopen(direccion,"r+b");
                fseek(barchivo1,0,SEEK_SET);
                fread(mbrLeido,sizeof(mbr),1,barchivo1);
                int ao = mbrLeido->mbr_partition3->part_size + tamaAdd;
                if(ao < 0){
                    printf("\nERROR. Tamaño a quitar es mayor que el tamaño de la particion.\n");
                }else{
                    mbrLeido->mbr_partition3->part_size = ao;
                    printf("\n**Espacio quitado con éxito**\n");
                }
                fseek(barchivo1,0,SEEK_SET);
                fwrite(mbrLeido,sizeof(mbr)+ sizeof( partition),1,barchivo1);
                fseek(barchivo1,0,SEEK_SET);
                fread(mbrLeido1,sizeof(mbr),1,barchivo1);
                fclose(barchivo1);
            }else if(strcmp(compro->mbr_partition4->part_name,letraName) == 0){
                mbr *mbrLeido = (mbr *)malloc(sizeof(mbr));
                mbr *mbrLeido1 = (mbr *)malloc(sizeof(mbr));
                mbrLeido1->mbr_partition4 = (partition *)malloc(sizeof(partition));
                FILE *barchivo1 = fopen(direccion,"r+b");
                fseek(barchivo1,0,SEEK_SET);
                fread(mbrLeido,sizeof(mbr),1,barchivo1);
                int ao = mbrLeido->mbr_partition4->part_size + tamaAdd;
                if(ao < 0){
                    printf("\nERROR. Tamaño a quitar es mayor que el tamaño de la particion.\n");
                }else{
                    mbrLeido->mbr_partition4->part_size = ao;
                    printf("\n**Espacio quitado con éxito**\n");
                }
                fseek(barchivo1,0,SEEK_SET);
                fwrite(mbrLeido,sizeof(mbr)+ sizeof( partition),1,barchivo1);
                fseek(barchivo1,0,SEEK_SET);
                fread(mbrLeido1,sizeof(mbr),1,barchivo1);
                fclose(barchivo1);
            }else{
                printf("\nERROR. Particion no existe en el disco.\n");
                return -1;
            }
        }else if(tamaAdd > 0){
            /*SE AGREGA TAMANIO A LA PARTICION*/
            if(strcmp(compro->mbr_partition1->part_name,letraName) == 0){
                mbr *mbrLeido = (mbr *)malloc(sizeof(mbr));
                mbr *mbrLeido1 = (mbr *)malloc(sizeof(mbr));
                mbrLeido1->mbr_partition1 = (partition *)malloc(sizeof(partition));
                FILE *barchivo1 = fopen(direccion,"r+b");
                fseek(barchivo1,0,SEEK_SET);
                fread(mbrLeido,sizeof(mbr),1,barchivo1);
                int ao = mbrLeido->mbr_partition1->part_size + tamaAdd;
                if(ao > mbrLeido->mbr_tamanio){
                    printf("\nERROR. Tamaño a agregar supera la capacidad maxima de la particion.\n");
                }else{
                        if(strcmp(compro->mbr_partition2->part_type,"x") == 0){
                            if(strcmp(compro->mbr_partition3->part_type,"x") == 0){
                                if(strcmp(compro->mbr_partition4->part_type,"x") == 0){
                                    mbrLeido->mbr_partition1->part_size = ao;
                                    printf("\n**Espacio agregado con éxito**\n");
                                }else{
                                    if(ao <= (compro->mbr_partition4->part_start - compro->mbr_partition1->part_size - sizeof(mbr))){
                                        mbrLeido->mbr_partition1->part_size = ao;
                                        printf("\n**Espacio agregado con éxito**\n");
                                    }
                                }
                            }else{
                                if(ao <= (compro->mbr_partition3->part_start - compro->mbr_partition1->part_size - sizeof(mbr))){
                                    mbrLeido->mbr_partition1->part_size = ao;
                                    printf("\n**Espacio agregado con éxito**\n");
                                }
                            }
                        }else{
                            if(ao <= (compro->mbr_partition2->part_start - compro->mbr_partition1->part_size - sizeof(mbr))){
                                mbrLeido->mbr_partition1->part_size = ao;
                                printf("\n**Espacio agregado con éxito**\n");
                            }
                        }
                }
                fseek(barchivo1,0,SEEK_SET);
                fwrite(mbrLeido,sizeof(mbr)+ sizeof( partition),1,barchivo1);
                fseek(barchivo1,0,SEEK_SET);
                fread(mbrLeido1,sizeof(mbr),1,barchivo1);
                fclose(barchivo1);
            }else if(strcmp(compro->mbr_partition2->part_name,letraName) == 0){
                mbr *mbrLeido = (mbr *)malloc(sizeof(mbr));
                mbr *mbrLeido1 = (mbr *)malloc(sizeof(mbr));
                mbrLeido1->mbr_partition1 = (partition *)malloc(sizeof(partition));
                FILE *barchivo1 = fopen(direccion,"r+b");
                fseek(barchivo1,0,SEEK_SET);
                fread(mbrLeido,sizeof(mbr),1,barchivo1);
                int ao = mbrLeido->mbr_partition2->part_size + tamaAdd;

                if(ao > mbrLeido->mbr_tamanio){
                    printf("\nERROR. Tamaño a agregar supera la capacidad maxima de la particion.\n");
                }else{

                    if(strcmp(compro->mbr_partition1->part_type,"x") == 0){
                        int aa = compro->mbr_partition2->part_start;
                        if(aa > 0){
                            if(aa >= tamaAdd){
                                mbrLeido->mbr_partition2->part_size + tamaAdd;
                                mbrLeido->mbr_partition2->part_start - tamaAdd;
                            }else{
                                printf("\nERROR. No hay espacio.\n");
                            }
                        }else{
                            printf("\nERROR.No hay espacio.\n");
                        }
                    }else{
                        if(strcmp(compro->mbr_partition3->part_type,"x") == 0){
                            if(strcmp(compro->mbr_partition4->part_type,"x") == 0){
                                mbrLeido->mbr_partition2->part_size = ao;
                            }else{
                                if(ao <= (compro->mbr_partition4->part_start - compro->mbr_partition2->part_size - compro->mbr_partition2->part_start)){
                                    mbrLeido->mbr_partition2->part_size = ao;
                                }
                            }
                        }else{
                            if(ao <= (compro->mbr_partition3->part_start - compro->mbr_partition2->part_size - compro->mbr_partition2->part_start )){
                                mbrLeido->mbr_partition2->part_size = ao;
                            }
                        }
                    }

                }
                fseek(barchivo1,0,SEEK_SET);
                fwrite(mbrLeido,sizeof(mbr)+ sizeof( partition),1,barchivo1);
                fseek(barchivo1,0,SEEK_SET);
                fread(mbrLeido1,sizeof(mbr),1,barchivo1);
                fclose(barchivo1);
            }else if(strcmp(compro->mbr_partition3->part_name,letraName) == 0){
                mbr *mbrLeido = (mbr *)malloc(sizeof(mbr));
                mbr *mbrLeido1 = (mbr *)malloc(sizeof(mbr));
                mbrLeido1->mbr_partition1 = (partition *)malloc(sizeof(partition));
                FILE *barchivo1 = fopen(direccion,"r+b");
                fseek(barchivo1,0,SEEK_SET);
                fread(mbrLeido,sizeof(mbr),1,barchivo1);
                int ao = mbrLeido->mbr_partition3->part_size + tamaAdd;
                if(ao > mbrLeido->mbr_tamanio){
                    printf("\nERROR. Tamaño a agregar supera la capacidad maxima de la particion.\n");
                }else{

                }
                fseek(barchivo1,0,SEEK_SET);
                fwrite(mbrLeido,sizeof(mbr)+ sizeof( partition),1,barchivo1);
                fseek(barchivo1,0,SEEK_SET);
                fread(mbrLeido1,sizeof(mbr),1,barchivo1);
                fclose(barchivo1);
            }else if(strcmp(compro->mbr_partition4->part_name,letraName) == 0){
                mbr *mbrLeido = (mbr *)malloc(sizeof(mbr));
                mbr *mbrLeido1 = (mbr *)malloc(sizeof(mbr));
                mbrLeido1->mbr_partition1 = (partition *)malloc(sizeof(partition));
                FILE *barchivo1 = fopen(direccion,"r+b");
                fseek(barchivo1,0,SEEK_SET);
                fread(mbrLeido,sizeof(mbr),1,barchivo1);
                int ao = mbrLeido->mbr_partition3->part_size + tamaAdd;
                if(ao > mbrLeido->mbr_tamanio){
                    printf("\nERROR. Tamaño a agregar supera la capacidad maxima de la particion.\n");
                }else{
                    int aa = compro->mbr_partition3->part_size + compro->mbr_partition2->part_size + compro->mbr_partition1->part_size;
                    int ts = compro->mbr_tamanio - sizeof(mbr) - aa;
                    if(ts > tamaAdd){
                        if((compro->mbr_partition3->part_start + compro->mbr_partition3->part_size) == compro->mbr_partition4->part_start){
                            printf("\ERROR. No hay espacio");
                        }else{
                            mbrLeido->mbr_partition4->part_start - tamaAdd;
                            mbrLeido->mbr_partition4->part_size + tamaAdd;
                        }
                    }
                }
                fseek(barchivo1,0,SEEK_SET);
                fwrite(mbrLeido,sizeof(mbr)+ sizeof( partition),1,barchivo1);
                fseek(barchivo1,0,SEEK_SET);
                fread(mbrLeido1,sizeof(mbr),1,barchivo1);
                fclose(barchivo1);

            }else{
                printf("\nERROR. Particion no existe.\n");
                return -1;
            }
        }
    }
}

int metodoMount(char *token)
{
    char path[10] = "-path";
    char name[10] = "-name";
    char comillas[3] = "\"";

    char guadoPath1[100];
    char guardoNombre[100];
    int control;
    int prueba=0;
    while(token!=NULL)
    {
        token = strtok(NULL, " ::");
        if(token==NULL){
            if(prueba==0){
                printCola(tablaDeParticiones);
            }
            break;
        }

        char *estaPath;
        char *estaName;

        prueba++;
        estaPath = strstr(token,path);
        estaName = strstr(token,name);

        if(estaPath)
            control = 1;
        else if(estaName)
            control = 2;
        else
            control = 0;

        switch (control){
        case 1:
            token = strtok(NULL, " ::");
            if(strstr(token,comillas)){
                strcpy(guadoPath1,token+1);
                token = strtok(NULL, "\"");
                strcat(guadoPath1," ");
                strcat(guadoPath1,token);
            }else{
                strcpy(guadoPath1,token);
            }
            break;
        case 2:
            token = strtok(NULL, " ::");
            strcpy(guardoNombre,token);
            break;
        default:
            printf("\nERROR. Comando no valido.\n");
            break;
        }
    }

    FILE *archivo = fopen(guadoPath1,"r+b");
    mbr *compro = (mbr *)malloc(sizeof(mbr));


    if(archivo!=NULL){
        fseek(archivo,0,SEEK_SET);
        fread(compro,sizeof(mbr),1,archivo);
        fclose(archivo);

        if(strcmp(compro->mbr_partition1->part_name,guardoNombre) == 0){
            agregarATabla(tablaDeParticiones,guadoPath1,guardoNombre);
        }else if(strcmp(compro->mbr_partition2->part_name,guardoNombre) == 0){
            agregarATabla(tablaDeParticiones,guadoPath1,guardoNombre);
        }else if(strcmp(compro->mbr_partition3->part_name,guardoNombre) == 0){
            agregarATabla(tablaDeParticiones,guadoPath1,guardoNombre);
        }else if(strcmp(compro->mbr_partition4->part_name,guardoNombre) == 0){
            agregarATabla(tablaDeParticiones,guadoPath1,guardoNombre);
        }else{
            /*MONTAR LOGICAS*/
            if(strcmp(guardoNombre,"px") == 0)
                printf("\nERROR. No se monto particion\n");
            mbr *mbrLeidoA = (mbr *)malloc(sizeof(mbr));
            FILE *barchivo1A = fopen(guadoPath1,"r+b");
            ebr *ebrInicial2A = (ebr *)malloc(sizeof(ebr));
            fseek(barchivo1A,0,SEEK_SET);
            fread(mbrLeidoA,sizeof(mbr),1,barchivo1A);
            fseek(barchivo1A,sizeof(mbr)+ sizeof( partition),SEEK_CUR);
            fread(ebrInicial2A,sizeof(ebr),1,barchivo1A);
            int tam = 1;

            if(ebrInicial2A->part_size != 0 && ebrInicial2A->part_start != 0){
                for(int i = 0; i <= 1000; i++){

                        fseek(barchivo1A,0,SEEK_SET);
                        fread(mbrLeidoA,sizeof(mbr),1,barchivo1A);
                        fseek(barchivo1A,sizeof(mbr)+ sizeof( partition) + (i)*sizeof(ebr),SEEK_CUR);
                        fread(ebrInicial2A,sizeof(ebr),1,barchivo1A);
                        if(ebrInicial2A->part_size == 0 && ebrInicial2A->part_start == 0)
                            break;
                        if(strcmp(ebrInicial2A->part_name,guardoNombre) == 0){
                             agregarATabla(tablaDeParticiones,guadoPath1,guardoNombre);
                            break;
                        }
                }

            }else{
                printf("\nERROR. No existe esa particion en el disco.\n");
            }

        }

    }else{
        printf("\nERROR. Disco no existe\n");
        printf("No se monto la particion\n");
    }


}

char *aa = "";
int metodoUnmount(char *token)
{
    char id[10] = "-id";

    char guardoId[100];
    int control;

    while(token!=NULL)
    {
        token = strtok(NULL, " ::");
        if(token==NULL)
            break;

        char *estaId;

        estaId = strstr(token,id);

        if(estaId)
            control = 1;
        else
            control = 0;

        switch (control){
        case 1:
            token = strtok(NULL, "=");
            strcpy(guardoId,token);
            break;
        default:
            printf("\nERROR. Comando no valido.\n");
            return -1;
            break;
        }
    }

    registro *aux = (registro *)malloc(sizeof(registro));
    registro *aux2 = (registro *)malloc(sizeof(registro));
    aux = tablaDeParticiones->primero;

    if(aux == NULL){
        printf("\nERROR. No existe ID en tabla de particiones.\n");
        return -1;
    }
    while(aux != NULL){

        if(strcmp(aux->id,guardoId) == 0){

            mbr *mbrLeidoA = (mbr *)malloc(sizeof(mbr));
            FILE *barchivo1A = fopen(aux->path,"r+b");
            ebr *ebrInicial2A = (ebr *)malloc(sizeof(ebr));
            fseek(barchivo1A,0,SEEK_SET);
            fread(mbrLeidoA,sizeof(mbr),1,barchivo1A);
            fseek(barchivo1A,sizeof(mbr)+ sizeof( partition),SEEK_CUR);
            fread(ebrInicial2A,sizeof(ebr),1,barchivo1A);
            int siEsExtendida;
            if(strcmp(mbrLeidoA->mbr_partition1->part_type,"e") == 0 && strcmp(aux->name,mbrLeidoA->mbr_partition1->part_name)==0){
                siEsExtendida = 1 ;
            }else if(strcmp(mbrLeidoA->mbr_partition2->part_type,"e") == 0 && strcmp(aux->name,mbrLeidoA->mbr_partition2->part_name)==0){
                siEsExtendida = 1 ;
            }else if(strcmp(mbrLeidoA->mbr_partition3->part_type,"e") == 0 && strcmp(aux->name,mbrLeidoA->mbr_partition3->part_name)==0){
                siEsExtendida = 1 ;
            }else if(strcmp(mbrLeidoA->mbr_partition4->part_type,"e") == 0 && strcmp(aux->name,mbrLeidoA->mbr_partition4->part_name)==0){
                siEsExtendida = 1 ;
            }
            if(siEsExtendida == 1){
                if(ebrInicial2A->part_size != 0 && ebrInicial2A->part_start != 0){
                    for(int i = 1; i <= 1000; i++){

                        registro *recorre = (registro *)malloc(sizeof(registro));
                        recorre = tablaDeParticiones->primero;

                        while(recorre!=NULL){

                            if(strcmp(recorre->name,ebrInicial2A->part_name) == 0){
                                metodoUnmount2(recorre->id);
                                printf("\nSi esta en la tabla la logica que contiene la extendida\n");
                                printf(recorre->name);
                            }

                            recorre = recorre->siguiente;
                        }
                            fseek(barchivo1A,0,SEEK_SET);
                            fread(mbrLeidoA,sizeof(mbr),1,barchivo1A);
                            fseek(barchivo1A,sizeof(mbr)+ sizeof( partition) + (i)*sizeof(ebr),SEEK_CUR);
                            fread(ebrInicial2A,sizeof(ebr),1,barchivo1A);
                            if(ebrInicial2A->part_size == 0 && ebrInicial2A->part_start == 0)
                                break;

                    }
                }
            }

    }
aux = aux->siguiente;
    }

        aux = tablaDeParticiones->primero;
        if(aux == NULL){
            printf("\nERROR. No existe en tabla de particiones\n");
            return -1;
        }

    while(aux!=NULL){

        if(strcmp(aux->id,guardoId) == 0){

            if(aux == tablaDeParticiones->primero && aux == tablaDeParticiones->ultimo){
                /*desmontar logicas*/
                tablaDeParticiones->primero = NULL;
                tablaDeParticiones->ultimo = NULL;
                return 1;
            }else if(aux == tablaDeParticiones->ultimo){
                aux2 = aux->anterior;
                aux2->siguiente = NULL;
                tablaDeParticiones->ultimo = aux2;
                return 1;
            }else if(aux == tablaDeParticiones->primero && aux->siguiente != NULL){
                aux = aux->siguiente;
                aux->anterior = NULL;
                tablaDeParticiones->primero = aux;
                return 1;
            }else{
                registro *aux3 = (registro *)malloc(sizeof(registro));
                aux3 = aux->anterior;
                aux3->siguiente = aux->siguiente;
                registro *aux4 = (registro *)malloc(sizeof(registro));
                aux4 = aux->siguiente;
                aux4->anterior = aux->anterior;
                return 1;
            }
        }

        if(strcmp(aux->id,guardoId) != 0 && aux == tablaDeParticiones->ultimo){
            printf("\nERROR. No existe ID en tabla de particiones\n");
        }


        aux = aux->siguiente;
    }

}

int metodoUnmount2(char *token)
{
    registro *aux = (registro *)malloc(sizeof(registro));
    registro *aux2 = (registro *)malloc(sizeof(registro));
    aux = tablaDeParticiones->primero;

    while(aux != NULL){

        if(strcmp(aux->id,token) == 0){
            if(aux == tablaDeParticiones->primero && aux == tablaDeParticiones->ultimo){
                /*desmontar logicas*/
                tablaDeParticiones->primero = NULL;
                tablaDeParticiones->ultimo = NULL;
                return 1;
            }else if(aux == tablaDeParticiones->ultimo){
                aux2 = aux->anterior;
                aux2->siguiente = NULL;
                tablaDeParticiones->ultimo = aux2;
                return 1;
            }else if(aux == tablaDeParticiones->primero && aux->siguiente != NULL){
                aux = aux->siguiente;
                aux->anterior = NULL;
                tablaDeParticiones->primero = aux;
                return 1;
            }else{
                registro *aux3 = (registro *)malloc(sizeof(registro));
                aux3 = aux->anterior;
                aux3->siguiente = aux->siguiente;
                registro *aux4 = (registro *)malloc(sizeof(registro));
                aux4 = aux->siguiente;
                aux4->anterior = aux3;
                return 1;
            }
        }

        if(strcmp(aux->id,token) != 0 && aux == tablaDeParticiones->ultimo){
            printf("\nERROR. No existe ID en tabla de particiones\n");
        }

        aux = aux->siguiente;
    }

}

int metodoRep(char *token)
{
    char path[10] = "-path";
    char name[10] = "-name";
    char id[10] = "-id";
    char comillas[3] = "\"";
    char tipoe[10] = "";
    char tipop[10] = "";

    char guadoPath1[100] = "";
    char guardoNombre[100] = "";
    char guardoId[100] = "";
    int control;

    while(token!=NULL)
    {
        printf( " %s\n", token );

        token = strtok(NULL, " ::");
        if(token==NULL)
            break;

        char *estaPath;
        char *estaName;
        char *estaId;

        estaPath = strstr(token,path);
        estaName = strstr(token,name);
        estaId = strstr(token,id);

        if(estaPath)
            control = 1;
        else if(estaName)
            control = 2;
        else if(estaId)
            control = 3;
        else
            control = 0;

        switch (control){
        case 1:
            token = strtok(NULL, " ::");

            if(strstr(token,comillas)){
                strcpy(guadoPath1,token+1);
                token = strtok(NULL, "\"");
                strcat(guadoPath1," ");
                strcat(guadoPath1,token);
                printf("\nCAAAAAAAAAADENA   : %s\n",guadoPath1);
            }else{
                strcpy(guadoPath1,token);
            }
            break;
        case 2:
            token = strtok(NULL, " ::");
            strcpy(guardoNombre,token);
            break;
        case 3:
            token = strtok(NULL, " ::");
            strcpy(guardoId,token);
            break;
        default:
            printf("\nERROR. Comando no valido.\n");
            return -1;
            break;
        }
    }

    if(strcmp(guadoPath1,"") != 0 && strcmp(guardoId,"") != 0 && strcmp(guardoNombre,"") != 0){
        registro *aux = (registro *)malloc(sizeof(registro));
        aux = tablaDeParticiones->primero;
        int siEstaEnLista;
        mbr *mbrLeido = (mbr *)malloc(sizeof(mbr));

        while(aux != NULL){

            if(strcmp(aux->id,guardoId) == 0){

                siEstaEnLista = 1;
                break;
            }

            aux = aux->siguiente;
        }

        if(siEstaEnLista == 1){
            FILE *barchivo1 = fopen(aux->path,"r+b");
            if(barchivo1==NULL){
                printf("\ERROR. Path incorrecto.\n");
                   return -1;
            }
            fseek(barchivo1,0,SEEK_SET);
            fread(mbrLeido,sizeof(mbr),1,barchivo1);
            fclose(barchivo1);

            if(strcmp(guardoNombre,"mbr") == 0){

                char *trAbre = "<tr>\n";
                char *trCierra = "</tr>\n";
                char *tdAbre = "<td>";
                char *tdCierra = "</td>\n";
                FILE *dotMBR = fopen("archivosMBR.dot","w");
                char *inicio = "digraph{ subgraph html { abc [shape=none, margin=0, label=<<TABLE BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\" CELLPADDING=\"4\">";
                fprintf(dotMBR,"%s",inicio);
                char *encabezado = "<tr><td><font color=\"red\">NOMBRE</font></td><td><font color=\"red\">VALOR</font></td></tr>\n";
                fprintf(dotMBR,"%s",encabezado);

                fprintf(dotMBR,"%s",trAbre);
                fprintf(dotMBR,"%s",tdAbre);
                fprintf(dotMBR,"%s","mbr_tamaño");
                fprintf(dotMBR,"%s",tdCierra);
                fprintf(dotMBR,"%s",tdAbre);
                fprintf(dotMBR,"%d",mbrLeido->mbr_tamanio);
                fprintf(dotMBR,"%s",tdCierra);
                fprintf(dotMBR,"%s",trCierra);



                fprintf(dotMBR,"%s",trAbre);
                fprintf(dotMBR,"%s",tdAbre);
                fprintf(dotMBR,"%s","mbr_fecha_creacion");
                fprintf(dotMBR,"%s",tdCierra);
                fprintf(dotMBR,"%s",tdAbre);
                fprintf(dotMBR,"%s",mbrLeido->mbr_fecha_creacion);
                fprintf(dotMBR,"%s",tdCierra);
                fprintf(dotMBR,"%s",trCierra);

                fprintf(dotMBR,"%s",trAbre);
                fprintf(dotMBR,"%s",tdAbre);
                fprintf(dotMBR,"%s","mbr_disk_signature");
                fprintf(dotMBR,"%s",tdCierra);
                fprintf(dotMBR,"%s",tdAbre);
                fprintf(dotMBR,"%d",mbrLeido->mbr_disk_signature);
                fprintf(dotMBR,"%s",tdCierra);
                fprintf(dotMBR,"%s",trCierra);

                if(strcmp(mbrLeido->mbr_partition1->part_type,"x") != 0){
                    fprintf(dotMBR,"%s",trAbre);
                    fprintf(dotMBR,"%s",tdAbre);
                    fprintf(dotMBR,"%s","part_status_1");
                    fprintf(dotMBR,"%s",tdCierra);
                    fprintf(dotMBR,"%s",tdAbre);
                    fprintf(dotMBR,"%d",mbrLeido->mbr_partition1->part_status);
                    fprintf(dotMBR,"%s",tdCierra);
                    fprintf(dotMBR,"%s",trCierra);

                    if(strstr(mbrLeido->mbr_partition1->part_type,"e")){
                        strcpy(tipoe,"e");
                    }else if(strstr(mbrLeido->mbr_partition1->part_type,"p")){
                        strcpy(tipop,"p");
                    }


                    fprintf(dotMBR,"%s",trAbre);
                    fprintf(dotMBR,"%s",tdAbre);
                    fprintf(dotMBR,"%s","part_type_1");
                    fprintf(dotMBR,"%s",tdCierra);
                    fprintf(dotMBR,"%s",tdAbre);
                    fprintf(dotMBR,"%s",mbrLeido->mbr_partition1->part_type);
                    fprintf(dotMBR,"%s",tdCierra);
                    fprintf(dotMBR,"%s",trCierra);

                    fprintf(dotMBR,"%s",trAbre);
                    fprintf(dotMBR,"%s",tdAbre);
                    fprintf(dotMBR,"%s","part_fit_1");
                    fprintf(dotMBR,"%s",tdCierra);
                    fprintf(dotMBR,"%s",tdAbre);
                    fprintf(dotMBR,"%s",mbrLeido->mbr_partition1->part_fit);
                    fprintf(dotMBR,"%s",tdCierra);
                    fprintf(dotMBR,"%s",trCierra);

                    fprintf(dotMBR,"%s",trAbre);
                    fprintf(dotMBR,"%s",tdAbre);
                    fprintf(dotMBR,"%s","part_start_1");
                    fprintf(dotMBR,"%s",tdCierra);
                    fprintf(dotMBR,"%s",tdAbre);
                    fprintf(dotMBR,"%d",mbrLeido->mbr_partition1->part_start);
                    fprintf(dotMBR,"%s",tdCierra);
                    fprintf(dotMBR,"%s",trCierra);

                    fprintf(dotMBR,"%s",trAbre);
                    fprintf(dotMBR,"%s",tdAbre);
                    fprintf(dotMBR,"%s","part_size_1");
                    fprintf(dotMBR,"%s",tdCierra);
                    fprintf(dotMBR,"%s",tdAbre);
                    fprintf(dotMBR,"%d",mbrLeido->mbr_partition1->part_size);
                    fprintf(dotMBR,"%s",tdCierra);
                    fprintf(dotMBR,"%s",trCierra);

                    fprintf(dotMBR,"%s",trAbre);
                    fprintf(dotMBR,"%s",tdAbre);
                    fprintf(dotMBR,"%s","part_name_1");
                    fprintf(dotMBR,"%s",tdCierra);
                    fprintf(dotMBR,"%s",tdAbre);
                    fprintf(dotMBR,"%s",mbrLeido->mbr_partition1->part_name);
                    fprintf(dotMBR,"%s",tdCierra);
                    fprintf(dotMBR,"%s",trCierra);

                }
                if(strcmp(mbrLeido->mbr_partition2->part_type,"x") != 0){
                    fprintf(dotMBR,"%s",trAbre);
                    fprintf(dotMBR,"%s",tdAbre);
                    fprintf(dotMBR,"%s","part_status_2");
                    fprintf(dotMBR,"%s",tdCierra);
                    fprintf(dotMBR,"%s",tdAbre);
                    fprintf(dotMBR,"%d",mbrLeido->mbr_partition2->part_status);
                    fprintf(dotMBR,"%s",tdCierra);
                    fprintf(dotMBR,"%s",trCierra);
                    if(strstr(mbrLeido->mbr_partition2->part_type,"e")){
                        strcpy(tipoe,"e");
                    }else if(strstr(mbrLeido->mbr_partition2->part_type,"p")){
                        strcpy(tipop,"p");
                    }
                    fprintf(dotMBR,"%s",trAbre);
                    fprintf(dotMBR,"%s",tdAbre);
                    fprintf(dotMBR,"%s","part_type_2");
                    fprintf(dotMBR,"%s",tdCierra);
                    fprintf(dotMBR,"%s",tdAbre);
                    fprintf(dotMBR,"%s",mbrLeido->mbr_partition2->part_type);
                    fprintf(dotMBR,"%s",tdCierra);
                    fprintf(dotMBR,"%s",trCierra);

                    fprintf(dotMBR,"%s",trAbre);
                    fprintf(dotMBR,"%s",tdAbre);
                    fprintf(dotMBR,"%s","part_fit_2");
                    fprintf(dotMBR,"%s",tdCierra);
                    fprintf(dotMBR,"%s",tdAbre);
                    fprintf(dotMBR,"%s",mbrLeido->mbr_partition2->part_fit);
                    fprintf(dotMBR,"%s",tdCierra);
                    fprintf(dotMBR,"%s",trCierra);

                    fprintf(dotMBR,"%s",trAbre);
                    fprintf(dotMBR,"%s",tdAbre);
                    fprintf(dotMBR,"%s","part_start_2");
                    fprintf(dotMBR,"%s",tdCierra);
                    fprintf(dotMBR,"%s",tdAbre);
                    fprintf(dotMBR,"%d",mbrLeido->mbr_partition2->part_start);
                    fprintf(dotMBR,"%s",tdCierra);
                    fprintf(dotMBR,"%s",trCierra);

                    fprintf(dotMBR,"%s",trAbre);
                    fprintf(dotMBR,"%s",tdAbre);
                    fprintf(dotMBR,"%s","part_size_2");
                    fprintf(dotMBR,"%s",tdCierra);
                    fprintf(dotMBR,"%s",tdAbre);
                    fprintf(dotMBR,"%d",mbrLeido->mbr_partition2->part_size);
                    fprintf(dotMBR,"%s",tdCierra);
                    fprintf(dotMBR,"%s",trCierra);

                    fprintf(dotMBR,"%s",trAbre);
                    fprintf(dotMBR,"%s",tdAbre);
                    fprintf(dotMBR,"%s","part_name_2");
                    fprintf(dotMBR,"%s",tdCierra);
                    fprintf(dotMBR,"%s",tdAbre);
                    fprintf(dotMBR,"%s",mbrLeido->mbr_partition2->part_name);
                    fprintf(dotMBR,"%s",tdCierra);
                    fprintf(dotMBR,"%s",trCierra);
                }
                if(strcmp(mbrLeido->mbr_partition3->part_type,"x") != 0){
                    fprintf(dotMBR,"%s",trAbre);
                    fprintf(dotMBR,"%s",tdAbre);
                    fprintf(dotMBR,"%s","part_status_3");
                    fprintf(dotMBR,"%s",tdCierra);
                    fprintf(dotMBR,"%s",tdAbre);
                    fprintf(dotMBR,"%d",mbrLeido->mbr_partition3->part_status);
                    fprintf(dotMBR,"%s",tdCierra);
                    fprintf(dotMBR,"%s",trCierra);

                    if(strstr(mbrLeido->mbr_partition3->part_type,"e")){
                        strcpy(tipoe,"e");
                    }else if(strstr(mbrLeido->mbr_partition3->part_type,"p")){
                        strcpy(tipop,"p");
                    }

                    fprintf(dotMBR,"%s",trAbre);
                    fprintf(dotMBR,"%s",tdAbre);
                    fprintf(dotMBR,"%s","part_type_3");
                    fprintf(dotMBR,"%s",tdCierra);
                    fprintf(dotMBR,"%s",tdAbre);
                    fprintf(dotMBR,"%s",mbrLeido->mbr_partition3->part_type);
                    fprintf(dotMBR,"%s",tdCierra);
                    fprintf(dotMBR,"%s",trCierra);

                    fprintf(dotMBR,"%s",trAbre);
                    fprintf(dotMBR,"%s",tdAbre);
                    fprintf(dotMBR,"%s","part_fit_3");
                    fprintf(dotMBR,"%s",tdCierra);
                    fprintf(dotMBR,"%s",tdAbre);
                    fprintf(dotMBR,"%s",mbrLeido->mbr_partition3->part_fit);
                    fprintf(dotMBR,"%s",tdCierra);
                    fprintf(dotMBR,"%s",trCierra);

                    fprintf(dotMBR,"%s",trAbre);
                    fprintf(dotMBR,"%s",tdAbre);
                    fprintf(dotMBR,"%s","part_start_3");
                    fprintf(dotMBR,"%s",tdCierra);
                    fprintf(dotMBR,"%s",tdAbre);
                    fprintf(dotMBR,"%d",mbrLeido->mbr_partition3->part_start);
                    fprintf(dotMBR,"%s",tdCierra);
                    fprintf(dotMBR,"%s",trCierra);

                    fprintf(dotMBR,"%s",trAbre);
                    fprintf(dotMBR,"%s",tdAbre);
                    fprintf(dotMBR,"%s","part_size_3");
                    fprintf(dotMBR,"%s",tdCierra);
                    fprintf(dotMBR,"%s",tdAbre);
                    fprintf(dotMBR,"%d",mbrLeido->mbr_partition3->part_size);
                    fprintf(dotMBR,"%s",tdCierra);
                    fprintf(dotMBR,"%s",trCierra);

                    fprintf(dotMBR,"%s",trAbre);
                    fprintf(dotMBR,"%s",tdAbre);
                    fprintf(dotMBR,"%s","part_name_3");
                    fprintf(dotMBR,"%s",tdCierra);
                    fprintf(dotMBR,"%s",tdAbre);
                    fprintf(dotMBR,"%s",mbrLeido->mbr_partition3->part_name);
                    fprintf(dotMBR,"%s",tdCierra);
                    fprintf(dotMBR,"%s",trCierra);
                }
                if(strcmp(mbrLeido->mbr_partition4->part_type,"x") != 0){
                    fprintf(dotMBR,"%s",trAbre);
                    fprintf(dotMBR,"%s",tdAbre);
                    fprintf(dotMBR,"%s","part_status_4");
                    fprintf(dotMBR,"%s",tdCierra);
                    fprintf(dotMBR,"%s",tdAbre);
                    fprintf(dotMBR,"%d",mbrLeido->mbr_partition4->part_status);
                    fprintf(dotMBR,"%s",tdCierra);
                    fprintf(dotMBR,"%s",trCierra);

                    fprintf(dotMBR,"%s",trAbre);
                    fprintf(dotMBR,"%s",tdAbre);
                    fprintf(dotMBR,"%s","part_type_4");
                    fprintf(dotMBR,"%s",tdCierra);
                    fprintf(dotMBR,"%s",tdAbre);
                    fprintf(dotMBR,"%s",mbrLeido->mbr_partition4->part_type);
                    fprintf(dotMBR,"%s",tdCierra);
                    fprintf(dotMBR,"%s",trCierra);

                    if(strstr(mbrLeido->mbr_partition4->part_type,"e")){
                        strcpy(tipoe,"e");
                    }else if(strstr(mbrLeido->mbr_partition4->part_type,"p")){
                        strcpy(tipop,"p");
                    }
                    fprintf(dotMBR,"%s",trAbre);
                    fprintf(dotMBR,"%s",tdAbre);
                    fprintf(dotMBR,"%s","part_fit_4");
                    fprintf(dotMBR,"%s",tdCierra);
                    fprintf(dotMBR,"%s",tdAbre);
                    fprintf(dotMBR,"%s",mbrLeido->mbr_partition4->part_fit);
                    fprintf(dotMBR,"%s",tdCierra);
                    fprintf(dotMBR,"%s",trCierra);

                    fprintf(dotMBR,"%s",trAbre);
                    fprintf(dotMBR,"%s",tdAbre);
                    fprintf(dotMBR,"%s","part_start_4");
                    fprintf(dotMBR,"%s",tdCierra);
                    fprintf(dotMBR,"%s",tdAbre);
                    fprintf(dotMBR,"%d",mbrLeido->mbr_partition4->part_start);
                    fprintf(dotMBR,"%s",tdCierra);
                    fprintf(dotMBR,"%s",trCierra);

                    fprintf(dotMBR,"%s",trAbre);
                    fprintf(dotMBR,"%s",tdAbre);
                    fprintf(dotMBR,"%s","part_size_4");
                    fprintf(dotMBR,"%s",tdCierra);
                    fprintf(dotMBR,"%s",tdAbre);
                    fprintf(dotMBR,"%d",mbrLeido->mbr_partition4->part_size);
                    fprintf(dotMBR,"%s",tdCierra);
                    fprintf(dotMBR,"%s",trCierra);

                    fprintf(dotMBR,"%s",trAbre);
                    fprintf(dotMBR,"%s",tdAbre);
                    fprintf(dotMBR,"%s","part_name_4");
                    fprintf(dotMBR,"%s",tdCierra);
                    fprintf(dotMBR,"%s",tdAbre);
                    fprintf(dotMBR,"%s",mbrLeido->mbr_partition4->part_name);
                    fprintf(dotMBR,"%s",tdCierra);
                    fprintf(dotMBR,"%s",trCierra);
                }

                fprintf(dotMBR,"%s","</TABLE>>];}");
                fclose(dotMBR);

                if(strcmp(tipoe,"e") == 0){
                    mbr *mbrLeidoA = (mbr *)malloc(sizeof(mbr));
                    FILE *barchivo1A = fopen(aux->path,"r+b");
                    int u = 0;
                    fseek(barchivo1A,0,SEEK_SET);
                    fread(mbrLeidoA,sizeof(mbr),1,barchivo1A);

                    ebr *ebrInicial2A = (ebr *)malloc(sizeof(ebr));
                    fseek(barchivo1A,sizeof(mbr)+ sizeof( partition),SEEK_CUR);
                    fread(ebrInicial2A,sizeof(ebr),1,barchivo1A);

                    if(ebrInicial2A->part_start != 0){
                        for(int i = 0; i <= 1000; i++){

                                fseek(barchivo1A,0,SEEK_SET);
                                fread(mbrLeidoA,sizeof(mbr),1,barchivo1A);
                                fseek(barchivo1A,sizeof(mbr)+ sizeof( partition) + (i)*sizeof(ebr),SEEK_CUR);
                                fread(ebrInicial2A,sizeof(ebr),1,barchivo1A);
                                if(ebrInicial2A->part_size == 0 && ebrInicial2A->part_start == 0)
                                    break;
                                if(ebrInicial2A->part_start != 0 && ebrInicial2A->part_size != 0){
                                    char *trAbre = "<tr>\n";
                                    char *trCierra = "</tr>\n";
                                    char *tdAbre = "<td>";
                                    char *tdCierra = "</td>\n";
                                    FILE *dotMBR = fopen("archivosMBR.dot","a");
                                    char *inicio = "\n\nsubgraph html";
                                    fprintf(dotMBR,"%s",inicio);
                                    fprintf(dotMBR,"%d",i);
                                    char *inicio2 = " { abc";
                                    fprintf(dotMBR,"%s",inicio2);
                                    fprintf(dotMBR,"%d",(i + 1));
                                    char *inicio22 = " [shape=none, margin=0, label=<<TABLE BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\" CELLPADDING=\"4\">";
                                    fprintf(dotMBR,"%s",inicio22);
                                    char *encabezado = "<tr><td><font color=\"red\">NOMBRE</font></td><td><font color=\"red\">VALOR</font></td></tr>\n";
                                    fprintf(dotMBR,"%s",encabezado);

                                        fprintf(dotMBR,"%s",trAbre);
                                        fprintf(dotMBR,"%s",tdAbre);
                                        fprintf(dotMBR,"%s","part_status_");
                                        fprintf(dotMBR,"%d",(i + 1));
                                        fprintf(dotMBR,"%s",tdCierra);
                                        fprintf(dotMBR,"%s",tdAbre);
                                        fprintf(dotMBR,"%d",ebrInicial2A->part_status);
                                        fprintf(dotMBR,"%s",tdCierra);
                                        fprintf(dotMBR,"%s",trCierra);

                                        fprintf(dotMBR,"%s",trAbre);
                                        fprintf(dotMBR,"%s",tdAbre);
                                        fprintf(dotMBR,"%s","part_fit_");
                                        fprintf(dotMBR,"%d",(i + 1));
                                        fprintf(dotMBR,"%s",tdCierra);
                                        fprintf(dotMBR,"%s",tdAbre);
                                        fprintf(dotMBR,"%s",ebrInicial2A->part_fit);
                                        fprintf(dotMBR,"%s",tdCierra);
                                        fprintf(dotMBR,"%s",trCierra);

                                        fprintf(dotMBR,"%s",trAbre);
                                        fprintf(dotMBR,"%s",tdAbre);
                                        fprintf(dotMBR,"%s","part_start_");
                                        fprintf(dotMBR,"%d",(i + 1));
                                        fprintf(dotMBR,"%s",tdCierra);
                                        fprintf(dotMBR,"%s",tdAbre);
                                        fprintf(dotMBR,"%d",ebrInicial2A->part_start);
                                        fprintf(dotMBR,"%s",tdCierra);
                                        fprintf(dotMBR,"%s",trCierra);

                                        fprintf(dotMBR,"%s",trAbre);
                                        fprintf(dotMBR,"%s",tdAbre);
                                        fprintf(dotMBR,"%s","part_size_");
                                        fprintf(dotMBR,"%d",(i + 1));
                                        fprintf(dotMBR,"%s",tdCierra);
                                        fprintf(dotMBR,"%s",tdAbre);
                                        fprintf(dotMBR,"%d",ebrInicial2A->part_size);
                                        fprintf(dotMBR,"%s",tdCierra);
                                        fprintf(dotMBR,"%s",trCierra);

                                        fprintf(dotMBR,"%s",trAbre);
                                        fprintf(dotMBR,"%s",tdAbre);
                                        fprintf(dotMBR,"%s","part_next_");
                                        fprintf(dotMBR,"%d",(i + 1));
                                        fprintf(dotMBR,"%s",tdCierra);
                                        fprintf(dotMBR,"%s",tdAbre);
                                        fprintf(dotMBR,"%d",ebrInicial2A->part_next);
                                        fprintf(dotMBR,"%s",tdCierra);
                                        fprintf(dotMBR,"%s",trCierra);

                                        fprintf(dotMBR,"%s",trAbre);
                                        fprintf(dotMBR,"%s",tdAbre);
                                        fprintf(dotMBR,"%s","part_name_");
                                        fprintf(dotMBR,"%d",(i + 1));
                                        fprintf(dotMBR,"%s",tdCierra);
                                        fprintf(dotMBR,"%s",tdAbre);
                                        fprintf(dotMBR,"%s",ebrInicial2A->part_name);
                                        fprintf(dotMBR,"%s",tdCierra);
                                        fprintf(dotMBR,"%s",trCierra);
                                        fprintf(dotMBR,"%s","</TABLE>>];}");
                                        fprintf(dotMBR,"%s","");
                                        fclose(dotMBR);
                                }


                        }
                    }
/*
                    if(ebrInicial2A->part_size != 0 && ebrInicial2A->part_start != 0){
                        for(int i = 0; i <= 1000; i++){

                                fseek(barchivo1A,0,SEEK_SET);
                                fread(mbrLeidoA,sizeof(mbr),1,barchivo1A);
                                fseek(barchivo1A,sizeof(mbr)+ sizeof( partition) + (i)*sizeof(ebr),SEEK_CUR);
                                fread(ebrInicial2A,sizeof(ebr),1,barchivo1A);
                                if(ebrInicial2A->part_size == 0 && ebrInicial2A->part_start == 0)
                                    break;
                                if(ebrInicial2A->part_start != 0 && ebrInicial2A->part_size != 0){
                                    char *trAbre = "<tr>\n";
                                    char *trCierra = "</tr>\n";
                                    char *tdAbre = "<td>";
                                    char *tdCierra = "</td>\n";
                                    FILE *dotMBR = fopen("archivosMBR.dot","a");
                                    char *inicio = "\n\nsubgraph html";
                                    fprintf(dotMBR,"%s",inicio);
                                    fprintf(dotMBR,"%d",i);
                                    char *inicio2 = " { abc";
                                    fprintf(dotMBR,"%s",inicio2);
                                    fprintf(dotMBR,"%d",(i + 1));
                                    char *inicio22 = " [shape=none, margin=0, label=<<TABLE BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\" CELLPADDING=\"4\">";
                                    fprintf(dotMBR,"%s",inicio22);
                                    char *encabezado = "<tr><td><font color=\"red\">NOMBRE</font></td><td><font color=\"red\">VALOR</font></td></tr>\n";
                                    fprintf(dotMBR,"%s",encabezado);

                                        fprintf(dotMBR,"%s",trAbre);
                                        fprintf(dotMBR,"%s",tdAbre);
                                        fprintf(dotMBR,"%s","part_status_");
                                        fprintf(dotMBR,"%d",(i + 1));
                                        fprintf(dotMBR,"%s",tdCierra);
                                        fprintf(dotMBR,"%s",tdAbre);
                                        fprintf(dotMBR,"%d",ebrInicial2A->part_status);
                                        fprintf(dotMBR,"%s",tdCierra);
                                        fprintf(dotMBR,"%s",trCierra);

                                        fprintf(dotMBR,"%s",trAbre);
                                        fprintf(dotMBR,"%s",tdAbre);
                                        fprintf(dotMBR,"%s","part_fit_");
                                        fprintf(dotMBR,"%d",(i + 1));
                                        fprintf(dotMBR,"%s",tdCierra);
                                        fprintf(dotMBR,"%s",tdAbre);
                                        fprintf(dotMBR,"%s",ebrInicial2A->part_fit);
                                        fprintf(dotMBR,"%s",tdCierra);
                                        fprintf(dotMBR,"%s",trCierra);

                                        fprintf(dotMBR,"%s",trAbre);
                                        fprintf(dotMBR,"%s",tdAbre);
                                        fprintf(dotMBR,"%s","part_start_");
                                        fprintf(dotMBR,"%d",(i + 1));
                                        fprintf(dotMBR,"%s",tdCierra);
                                        fprintf(dotMBR,"%s",tdAbre);
                                        fprintf(dotMBR,"%d",ebrInicial2A->part_start);
                                        fprintf(dotMBR,"%s",tdCierra);
                                        fprintf(dotMBR,"%s",trCierra);

                                        fprintf(dotMBR,"%s",trAbre);
                                        fprintf(dotMBR,"%s",tdAbre);
                                        fprintf(dotMBR,"%s","part_size_");
                                        fprintf(dotMBR,"%d",(i + 1));
                                        fprintf(dotMBR,"%s",tdCierra);
                                        fprintf(dotMBR,"%s",tdAbre);
                                        fprintf(dotMBR,"%d",ebrInicial2A->part_size);
                                        fprintf(dotMBR,"%s",tdCierra);
                                        fprintf(dotMBR,"%s",trCierra);

                                        fprintf(dotMBR,"%s",trAbre);
                                        fprintf(dotMBR,"%s",tdAbre);
                                        fprintf(dotMBR,"%s","part_next_");
                                        fprintf(dotMBR,"%d",(i + 1));
                                        fprintf(dotMBR,"%s",tdCierra);
                                        fprintf(dotMBR,"%s",tdAbre);
                                        fprintf(dotMBR,"%d",ebrInicial2A->part_next);
                                        fprintf(dotMBR,"%s",tdCierra);
                                        fprintf(dotMBR,"%s",trCierra);

                                        fprintf(dotMBR,"%s",trAbre);
                                        fprintf(dotMBR,"%s",tdAbre);
                                        fprintf(dotMBR,"%s","part_name_");
                                        fprintf(dotMBR,"%d",(i + 1));
                                        fprintf(dotMBR,"%s",tdCierra);
                                        fprintf(dotMBR,"%s",tdAbre);
                                        fprintf(dotMBR,"%s",ebrInicial2A->part_name);
                                        fprintf(dotMBR,"%s",tdCierra);
                                        fprintf(dotMBR,"%s",trCierra);
                                        fprintf(dotMBR,"%s","</TABLE>>];}");
                                        fprintf(dotMBR,"%s","");
                                        fclose(dotMBR);
                                }


                        }
                    }*/
                }


                //Generar pdf del MBR
                /*
                 *       system("dot -Tpng GraficaSupermercado.dot -o GraficaSupermercado.png ");
                         system("gnome-open GraficaSupermercado.dot &");
                         system("gnome-open GraficaSupermercado.png &");

                 * */
                if(strstr(guadoPath1,"jpg")){
                    FILE *dotMBR1 = fopen("archivosMBR.dot","a");
                    fprintf(dotMBR1,"%s","}");
                    fclose(dotMBR1);
                    char prueba[100];
                    strcpy(prueba,guadoPath1);
                    char ja[100] = "dot -Tjpg archivosMBR.dot -o ";
                    char ja2[100] = "gnome-open ";
                    char ja3[100] = " &";
                    strcat(ja,guadoPath1);
                    strcat(ja2,prueba);
                    strcat(ja2, ja3);
                    printf("\n");
                    system(ja);
                    system(ja2);
                }else if(strstr(guadoPath1,"pdf")){
                    FILE *dotMBR1 = fopen("archivosMBR.dot","a");
                    fprintf(dotMBR1,"%s","}");
                    fclose(dotMBR1);
                    char prueba[100];
                    strcpy(prueba,guadoPath1);
                    char ja[100] = "dot -Tpdf archivosMBR.dot -o ";
                    char ja2[100] = "gnome-open ";
                    char ja3[100] = " &";
                    strcat(ja,guadoPath1);
                    strcat(ja2,prueba);
                    strcat(ja2, ja3);
                    printf("\n");
                    printf("%sja2: ",ja2);
                    system(ja);
                    system(ja2);
                }



            }else if(strcmp(guardoNombre,"disk") == 0){

                FILE *dotMBR = fopen("archivosDISK.dot","w");
                char *inicio = "digraph html { abc [shape=none, margin=0, label=<<TABLE BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\" CELLPADDING=\"4\">\n<TR>\n<TD ROWSPAN=\"3\"><FONT COLOR=\"red\">MBR</FONT><BR/></TD>\n";
                fprintf(dotMBR,"%s",inicio);

                int tamanioOcupado = mbrLeido->mbr_tamanio - mbrLeido->mbr_partition1->part_size - mbrLeido->mbr_partition2->part_size - mbrLeido->mbr_partition3->part_size - mbrLeido->mbr_partition4->part_size;
                int cont = 1;
                int ya1;
                int ya2;
                int ya3;
                int ya4;
                while(cont < 5){
                    int ta;
                    if(tamanioOcupado == 0){

                        mbr *mbrLeidoA = (mbr *)malloc(sizeof(mbr));
                        FILE *barchivo1A = fopen(aux->path,"r+b");
                        ebr *ebrInicial2A = (ebr *)malloc(sizeof(ebr));
                        fseek(barchivo1A,0,SEEK_SET);
                        fread(mbrLeidoA,sizeof(mbr),1,barchivo1A);
                        fseek(barchivo1A,sizeof(mbr)+ sizeof( partition),SEEK_CUR);
                        fread(ebrInicial2A,sizeof(ebr),1,barchivo1A);
                        int tam = 1;

                        if(ebrInicial2A->part_size != 0 && ebrInicial2A->part_start != 0){
                            for(int i = 0; i <= 1000; i++){

                                    fseek(barchivo1A,0,SEEK_SET);
                                    fread(mbrLeidoA,sizeof(mbr),1,barchivo1A);
                                    fseek(barchivo1A,sizeof(mbr)+ sizeof( partition) + (i)*sizeof(ebr),SEEK_CUR);
                                    fread(ebrInicial2A,sizeof(ebr),1,barchivo1A);
                                    if(ebrInicial2A->part_size == 0 && ebrInicial2A->part_start == 0)
                                        break;
                                    if(ebrInicial2A->part_start != 0 && ebrInicial2A->part_size != 0){
                                         tam += i;
                                    }
                            }

                        }

                        if(mbrLeido->mbr_partition1->part_size > 0 && strcmp(mbrLeido->mbr_partition1->part_type,"e") == 0 && ya1 != 1 && cont == 1){
                            char *ju = "<TD COLSPAN=\"";
                            char *ju2 = "\">EXTENDIDA</TD>\n";
                            ta = 1;
                            ya1 = 1;
                            fprintf(dotMBR,"%s",ju);
                            fprintf(dotMBR,"%d",tam*2);
                            fprintf(dotMBR,"%s",ju2);
                        }else if(mbrLeido->mbr_partition2->part_size > 0 && strcmp(mbrLeido->mbr_partition2->part_type,"e") == 0 && ya2 != 1 && cont == 2){
                            char *ju = "<TD COLSPAN=\"";
                            char *ju2 = "\">EXTENDIDA</TD>\n";
                            ta = 1;
                            ya1 = 1;
                            fprintf(dotMBR,"%s",ju);
                            fprintf(dotMBR,"%d",tam*2);
                            fprintf(dotMBR,"%s",ju2);
                        }else if(mbrLeido->mbr_partition3->part_size > 0 && strcmp(mbrLeido->mbr_partition3->part_type,"e") == 0 && ya3 != 1 && cont == 3){
                            char *ju = "<TD COLSPAN=\"";
                            char *ju2 = "\">EXTENDIDA</TD>\n";
                            ta = 1;
                            ya1 = 1;
                            fprintf(dotMBR,"%s",ju);
                            fprintf(dotMBR,"%d",tam*2);
                            fprintf(dotMBR,"%s",ju2);
                        }else if(mbrLeido->mbr_partition4->part_size > 0 && strcmp(mbrLeido->mbr_partition4->part_type,"e") == 0 && ya4 != 1 && cont == 4){
                            char *ju = "<TD COLSPAN=\"";
                            char *ju2 = "\">EXTENDIDA</TD>\n";
                            ta = 1;
                            ya1 = 1;
                            fprintf(dotMBR,"%s",ju);
                            fprintf(dotMBR,"%d",tam*2);
                            fprintf(dotMBR,"%s",ju2);
                        }

                        if(cont == 4 && ta == 1){
                            fprintf(dotMBR,"%s","</TR>");
                            fprintf(dotMBR,"%s","<TR>");
                            fprintf(dotMBR,"%s","<TD>");
                            fprintf(dotMBR,"%s","EBR");
                            fprintf(dotMBR,"%s","</TD>");

                            mbr *mbrLeidoA = (mbr *)malloc(sizeof(mbr));
                            FILE *barchivo1A = fopen(aux->path,"r+b");
                            ebr *ebrInicial2A = (ebr *)malloc(sizeof(ebr));
                            fseek(barchivo1A,0,SEEK_SET);
                            fread(mbrLeidoA,sizeof(mbr),1,barchivo1A);
                            fseek(barchivo1A,sizeof(mbr)+ sizeof( partition),SEEK_CUR);
                            fread(ebrInicial2A,sizeof(ebr),1,barchivo1A);

                            if(ebrInicial2A->part_size != 0 && ebrInicial2A->part_start != 0){
                                for(int i = 0; i <= 1000; i++){

                                        fseek(barchivo1A,0,SEEK_SET);
                                        fread(mbrLeidoA,sizeof(mbr),1,barchivo1A);
                                        fseek(barchivo1A,sizeof(mbr)+ sizeof( partition) + (i)*sizeof(ebr),SEEK_CUR);
                                        fread(ebrInicial2A,sizeof(ebr),1,barchivo1A);
                                        if(ebrInicial2A->part_size == 0 && ebrInicial2A->part_start == 0)
                                            break;
                                        if(ebrInicial2A->part_start != 0 && ebrInicial2A->part_size != 0){

                                        }


                                }

                            }

                            fseek(barchivo1A,0,SEEK_SET);
                            fread(mbrLeidoA,sizeof(mbr),1,barchivo1A);
                            fseek(barchivo1A,sizeof(mbr)+ sizeof( partition),SEEK_CUR);
                            fread(ebrInicial2A,sizeof(ebr),1,barchivo1A);

                            if(ebrInicial2A->part_start != 0){
                                for(int i = 0; i <= 1000; i++){

                                        fseek(barchivo1A,0,SEEK_SET);
                                        fread(mbrLeidoA,sizeof(mbr),1,barchivo1A);
                                        fseek(barchivo1A,sizeof(mbr)+ sizeof( partition) + (i)*sizeof(ebr),SEEK_CUR);
                                        fread(ebrInicial2A,sizeof(ebr),1,barchivo1A);
                                        if(ebrInicial2A->part_size == 0 && ebrInicial2A->part_start == 0){


                                        break;
                                        }
                                        if(ebrInicial2A->part_start != 0 && ebrInicial2A->part_size != 0){
                                            if(i!=0){
                                                fprintf(dotMBR,"%s","<TD>");
                                                fprintf(dotMBR,"%s","EBR");
                                                fprintf(dotMBR,"%s","</TD>");
                                            }

                                            fprintf(dotMBR,"%s","<TD>");
                                            fprintf(dotMBR,"%s","Logica");
                                            fprintf(dotMBR,"%s","</TD>");

                                        }


                                }

                        }else{
                                fprintf(dotMBR,"%s","<TD>");
                                fprintf(dotMBR,"%s","Vacio");
                                fprintf(dotMBR,"%s","</TD>");
                            }
                        }

                        if(mbrLeido->mbr_partition1->part_size > 0 && strcmp(mbrLeido->mbr_partition1->part_type,"p") == 0 && ya1 != 1 && cont == 1){
                            char *ju = "<TD ROWSPAN=\"3\">PRIMARIA</TD>\n";
                            fprintf(dotMBR,"%s",ju);
                            ya1 = 1;
                        }
                        if(mbrLeido->mbr_partition2->part_size > 0 && strcmp(mbrLeido->mbr_partition2->part_type,"p") == 0 && ya2 != 1 && cont == 2){
                            char *ju = "<TD ROWSPAN=\"3\">PRIMARIA</TD>\n";
                            fprintf(dotMBR,"%s",ju);
                            ya2 = 2;
                        }
                        if(mbrLeido->mbr_partition3->part_size > 0 && strcmp(mbrLeido->mbr_partition3->part_type,"p") == 0 && ya3 != 1 && cont == 3){
                            char *ju = "<TD ROWSPAN=\"3\">PRIMARIA</TD>\n";
                            fprintf(dotMBR,"%s",ju);
                            ya3 = 1;
                        }
                        if(mbrLeido->mbr_partition4->part_size > 0 && strcmp(mbrLeido->mbr_partition4->part_type,"p") == 0 && ya4 != 1 && cont == 4){
                            char *ju = "<TD ROWSPAN=\"3\">PRIMARIA</TD>\n";
                            fprintf(dotMBR,"%s",ju);
                            ya4 = 1;
                        }

                        if(cont == 4)
                            fprintf(dotMBR,"%s","</TR>");

                    }else if(tamanioOcupado > 0){
                        mbr *mbrLeidoA = (mbr *)malloc(sizeof(mbr));
                        FILE *barchivo1A = fopen(aux->path,"r+b");
                        ebr *ebrInicial2A = (ebr *)malloc(sizeof(ebr));
                        fseek(barchivo1A,0,SEEK_SET);
                        fread(mbrLeidoA,sizeof(mbr),1,barchivo1A);
                        fseek(barchivo1A,sizeof(mbr)+ sizeof( partition),SEEK_CUR);
                        fread(ebrInicial2A,sizeof(ebr),1,barchivo1A);
                        int tam = 1;

                        if(ebrInicial2A->part_size != 0 && ebrInicial2A->part_start != 0){
                            for(int i = 0; i <= 1000; i++){

                                    fseek(barchivo1A,0,SEEK_SET);
                                    fread(mbrLeidoA,sizeof(mbr),1,barchivo1A);
                                    fseek(barchivo1A,sizeof(mbr)+ sizeof( partition) + (i)*sizeof(ebr),SEEK_CUR);
                                    fread(ebrInicial2A,sizeof(ebr),1,barchivo1A);
                                    if(ebrInicial2A->part_size == 0 && ebrInicial2A->part_start == 0)
                                        break;
                                    if(ebrInicial2A->part_start != 0 && ebrInicial2A->part_size != 0){
                                         tam += i;
                                    }
                            }

                        }

                        if(mbrLeido->mbr_partition1->part_size > 0 && strcmp(mbrLeido->mbr_partition1->part_type,"e") == 0 && ya1 != 1 && cont == 1){
                            char *ju = "<TD COLSPAN=\"";
                            char *ju2 = "\">EXTENDIDA</TD>\n";
                            ta = 1;
                            ya1 = 1;
                            fprintf(dotMBR,"%s",ju);
                            fprintf(dotMBR,"%d",tam*2);
                            fprintf(dotMBR,"%s",ju2);
                        }else if(mbrLeido->mbr_partition2->part_size > 0 && strcmp(mbrLeido->mbr_partition2->part_type,"e") == 0 && ya2 != 1 && cont == 2){
                            char *ju = "<TD COLSPAN=\"";
                            char *ju2 = "\">EXTENDIDA</TD>\n";
                            ta = 1;
                            ya1 = 1;
                            fprintf(dotMBR,"%s",ju);
                            fprintf(dotMBR,"%d",tam*2);
                            fprintf(dotMBR,"%s",ju2);
                        }else if(mbrLeido->mbr_partition3->part_size > 0 && strcmp(mbrLeido->mbr_partition3->part_type,"e") == 0 && ya3 != 1 && cont == 3){
                            char *ju = "<TD COLSPAN=\"";
                            char *ju2 = "\">EXTENDIDA</TD>\n";
                            ta = 1;
                            ya1 = 1;
                            fprintf(dotMBR,"%s",ju);
                            fprintf(dotMBR,"%d",tam*2);
                            fprintf(dotMBR,"%s",ju2);
                        }else if(mbrLeido->mbr_partition4->part_size > 0 && strcmp(mbrLeido->mbr_partition4->part_type,"e") == 0 && ya4 != 1 && cont == 4){
                            char *ju = "<TD COLSPAN=\"";
                            char *ju2 = "\">EXTENDIDA</TD>\n";
                            ta = 1;
                            ya1 = 1;
                            fprintf(dotMBR,"%s",ju);
                            fprintf(dotMBR,"%d",tam*2);
                            fprintf(dotMBR,"%s",ju2);
                        }

                        if(cont == 4 && ta == 1){
                            fprintf(dotMBR,"%s","</TR>");
                            fprintf(dotMBR,"%s","<TR>");
                            fprintf(dotMBR,"%s","<TD>");
                            fprintf(dotMBR,"%s","EBR");
                            fprintf(dotMBR,"%s","</TD>");

                            mbr *mbrLeidoA = (mbr *)malloc(sizeof(mbr));
                            FILE *barchivo1A = fopen(aux->path,"r+b");
                            ebr *ebrInicial2A = (ebr *)malloc(sizeof(ebr));
                            fseek(barchivo1A,0,SEEK_SET);
                            fread(mbrLeidoA,sizeof(mbr),1,barchivo1A);
                            fseek(barchivo1A,sizeof(mbr)+ sizeof( partition),SEEK_CUR);
                            fread(ebrInicial2A,sizeof(ebr),1,barchivo1A);

                            if(ebrInicial2A->part_size != 0 && ebrInicial2A->part_start != 0){
                                for(int i = 0; i <= 1000; i++){

                                        fseek(barchivo1A,0,SEEK_SET);
                                        fread(mbrLeidoA,sizeof(mbr),1,barchivo1A);
                                        fseek(barchivo1A,sizeof(mbr)+ sizeof( partition) + (i)*sizeof(ebr),SEEK_CUR);
                                        fread(ebrInicial2A,sizeof(ebr),1,barchivo1A);
                                        if(ebrInicial2A->part_size == 0 && ebrInicial2A->part_start == 0)
                                            break;
                                        if(ebrInicial2A->part_start != 0 && ebrInicial2A->part_size != 0){

                                        }


                                }

                            }

                            fseek(barchivo1A,0,SEEK_SET);
                            fread(mbrLeidoA,sizeof(mbr),1,barchivo1A);
                            fseek(barchivo1A,sizeof(mbr)+ sizeof( partition),SEEK_CUR);
                            fread(ebrInicial2A,sizeof(ebr),1,barchivo1A);

                            if(ebrInicial2A->part_size != 0 && ebrInicial2A->part_start != 0){
                                for(int i = 0; i <= 1000; i++){

                                        fseek(barchivo1A,0,SEEK_SET);
                                        fread(mbrLeidoA,sizeof(mbr),1,barchivo1A);
                                        fseek(barchivo1A,sizeof(mbr)+ sizeof( partition) + (i)*sizeof(ebr),SEEK_CUR);
                                        fread(ebrInicial2A,sizeof(ebr),1,barchivo1A);
                                        if(ebrInicial2A->part_size == 0 && ebrInicial2A->part_start == 0){


                                        break;
                                        }
                                        if(ebrInicial2A->part_start != 0 && ebrInicial2A->part_size != 0){
                                            if(i!=0){
                                                fprintf(dotMBR,"%s","<TD>");
                                                fprintf(dotMBR,"%s","EBR");
                                                fprintf(dotMBR,"%s","</TD>");
                                            }

                                            fprintf(dotMBR,"%s","<TD>");
                                            fprintf(dotMBR,"%s","Logica");
                                            fprintf(dotMBR,"%s","</TD>");

                                        }


                                }

                        }else{
                                fprintf(dotMBR,"%s","<TD>");
                                fprintf(dotMBR,"%s","Vacio");
                                fprintf(dotMBR,"%s","</TD>");
                            }
                        }

                        if(mbrLeido->mbr_partition1->part_size > 0 && strcmp(mbrLeido->mbr_partition1->part_type,"p") == 0 && ya1 != 1 && cont == 1){
                            char *ju = "<TD ROWSPAN=\"3\">PRIMARIA</TD>\n";
                            fprintf(dotMBR,"%s",ju);
                            ya1 = 1;
                        }
                        if(mbrLeido->mbr_partition2->part_size > 0 && strcmp(mbrLeido->mbr_partition2->part_type,"p") == 0 && ya2 != 1 && cont == 2){
                            char *ju = "<TD ROWSPAN=\"3\">PRIMARIA</TD>\n";
                            fprintf(dotMBR,"%s",ju);
                            ya2 = 2;
                        }
                        if(mbrLeido->mbr_partition3->part_size > 0 && strcmp(mbrLeido->mbr_partition3->part_type,"p") == 0 && ya3 != 1 && cont == 3){
                            char *ju = "<TD ROWSPAN=\"3\">PRIMARIA</TD>\n";
                            fprintf(dotMBR,"%s",ju);
                            ya3 = 1;
                        }
                        if(mbrLeido->mbr_partition4->part_size > 0 && strcmp(mbrLeido->mbr_partition4->part_type,"p") == 0 && ya4 != 1 && cont == 4){
                            char *ju = "<TD ROWSPAN=\"3\">PRIMARIA</TD>\n";
                            fprintf(dotMBR,"%s",ju);
                            ya4 = 1;
                        }

                        if(cont == 4)
                            fprintf(dotMBR,"%s","</TR>");
                    }
                    cont++;
                }


                fprintf(dotMBR,"%s","</TABLE>>];}");
                fclose(dotMBR);

                /*
                 * FILE *dotMBR1 = fopen("archivosMBR.dot","a");
                    fprintf(dotMBR1,"%s","}");
                    fclose(dotMBR1);
                    char prueba[50];
                    strcpy(prueba,guadoPath1);
                    char ja[50] = "dot -Tpdf archivosMBR.dot -o ";
                    char ja2[100] = "gnome-open ";
                    strcat(ja,guadoPath1);
                    strcat(ja2,prueba);
                    strcat(ja2, ja3);
                    printf("\n");
                    printf("%sja2: ",ja2);
                    system(ja);
                    system(ja2);
                 *
                 * */


                if(strstr(guadoPath1,"jpg")){
                    FILE *dotMBR1 = fopen("archivosDISK.dot","a");
                    fclose(dotMBR1);
                    char prueba[100];
                    strcpy(prueba,guadoPath1);
                    char ja[100] = "dot -Tjpg archivosDISK.dot -o ";
                    char ja2[100] = "gnome-open ";
                    char ja3[100] = " &";
                    strcat(ja,guadoPath1);
                    strcat(ja2,prueba);
                    strcat(ja2, ja3);
                    printf("\n");
                    system(ja);
                    system(ja2);

                }else if(strstr(guadoPath1,"pdf")){
                    FILE *dotMBR1 = fopen("archivosDISK.dot","a");
                    fclose(dotMBR1);
                    char prueba[100];
                    strcpy(prueba,guadoPath1);
                    char ja[100] = "dot -Tpdf archivosDISK.dot -o ";
                    char ja2[100] = "gnome-open ";
                    char ja3[100] = " &";
                    strcat(ja,guadoPath1);
                    strcat(ja2,prueba);
                    strcat(ja2, ja3);
                    printf("\n");
                    system(ja);
                    system(ja2);

                }
            }else{
                printf("\nERROR. Definir mbr o disk.\n");
            }
        }else{
            printf("\nParticion no esta montada\n");
        }

    }
}

int agregarATabla(tabla *t, char path [100],char nombre[100]){

    registro *aux = (registro *)malloc(sizeof(registro));
    strcpy(aux->path,path);
    strcpy(aux->name,nombre);
    aux->siguiente = NULL;
    aux->anterior = NULL;


    if(t->primero == NULL){

        strcpy(aux->id,"vda1");

        t->primero = aux;
        t->ultimo = aux;
        printf("\n**Se monto particion con exito**.\n");


    }else{

        int aa = 0;
        int bb = 0;
        int cc = 0;
        int dd = 0;
        int ee = 0;
        int ff = 0;
        int gg = 0;
        int hh = 0;
        int ii = 0;
        int jj = 0;
        int kk = 0;
        int ll = 0;
        int mm = 0;
        int nn = 0;
        int oo = 0;
        int pp = 0;
        int qq = 0;
        int rr = 0;
        int ss = 0;
        int tt = 0;
        int uu = 0;
        int vv = 0;
        int ww = 0;
        int xx = 0;
        int yy = 0;
        int zz = 0;


        int ingresar;

        registro *verificarSiExiste = (registro *)malloc(sizeof(registro));
        verificarSiExiste = t->primero;
        int siExiste;

        char vd1[5] = "";
        char vd2[5] = "";
        char vd3[5] = "";
        char vd4[5] = "";
        char vd5[5] = "";
        char vd6[5] = "";
        char vd7[5] = "";
        char vd8[5] = "";
        char vd9[5] = "";
        char vd10[5] = "";
        char vd11[5] = "";
        char vd12[5] = "";


        while(verificarSiExiste!=NULL){


            if(strstr(verificarSiExiste->name,nombre) && strstr(verificarSiExiste->path,path)){
                printf("\n**La particion ya esta montada**\n");
                return -1;
            }


            if(strstr(verificarSiExiste->id,"vda")){
                aa = 1;
            }else if(strstr(verificarSiExiste->id,"vdb")){
                bb = 1;
            }else if(strstr(verificarSiExiste->id,"vdc")){
                cc = 1;
            }else if(strstr(verificarSiExiste->id,"vdd")){
                dd = 1;
            }else if(strstr(verificarSiExiste->id,"vde")){
                ee = 1;
            }else if(strstr(verificarSiExiste->id,"vdf")){
                ff = 1;
            }else if(strstr(verificarSiExiste->id,"vdg")){
                gg = 1;
            }else if(strstr(verificarSiExiste->id,"vdh")){
                hh = 1;
            }else if(strstr(verificarSiExiste->id,"vdi")){
                ii = 1;
            }else if(strstr(verificarSiExiste->id,"vdj")){
                jj = 1;
            }else if(strstr(verificarSiExiste->id,"vdk")){
                kk = 1;
            }else if(strstr(verificarSiExiste->id,"vdl")){
                ll = 1;
            }else if(strstr(verificarSiExiste->id,"vdm")){
                mm = 1;
            }else if(strstr(verificarSiExiste->id,"vdn")){
                nn = 1;
            }else if(strstr(verificarSiExiste->id,"vdo")){
                oo = 1;
            }else if(strstr(verificarSiExiste->id,"vdp")){
                pp = 1;
            }else if(strstr(verificarSiExiste->id,"vdq")){
                qq = 1;
            }else if(strstr(verificarSiExiste->id,"vdr")){
                rr = 1;
            }else if(strstr(verificarSiExiste->id,"vds")){
                ss = 1;
            }else if(strstr(verificarSiExiste->id,"vdt")){
                tt = 1;
            }else if(strstr(verificarSiExiste->id,"vdu")){
                uu = 1;
            }else if(strstr(verificarSiExiste->id,"vdv")){
                vv = 1;
            }else if(strstr(verificarSiExiste->id,"vdw")){
                ww = 1;
            }else if(strstr(verificarSiExiste->id,"vdx")){
                xx = 1;
            }else if(strstr(verificarSiExiste->id,"vdy")){
                yy = 1;
            }else if(strstr(verificarSiExiste->id,"vdz")){
                zz = 1;
            }


            if(strstr(verificarSiExiste->path,path)){

                if(strstr(verificarSiExiste->id,"vda1")){
                    strcpy(vd1,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vda2")){
                    strcpy(vd2,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vda3")){
                    strcpy(vd3,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vda4")){
                    strcpy(vd4,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vda5")){
                    strcpy(vd5,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vda6")){
                    strcpy(vd6,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vda7")){
                    strcpy(vd7,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vda8")){
                    strcpy(vd8,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vda9")){
                    strcpy(vd9,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vda10")){
                    strcpy(vd10,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vda11")){
                    strcpy(vd11,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vda12")){
                    strcpy(vd12,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdb1")){
                    strcpy(vd1,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdb2")){
                    strcpy(vd2,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdb3")){
                    strcpy(vd3,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdb4")){
                    strcpy(vd4,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdb5")){
                    strcpy(vd5,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdb6")){
                    strcpy(vd6,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdb7")){
                    strcpy(vd7,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdb8")){
                    strcpy(vd8,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdb9")){
                    strcpy(vd9,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdb10")){
                    strcpy(vd10,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdb11")){
                    strcpy(vd11,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdb12")){
                    strcpy(vd12,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdc1")){
                    strcpy(vd1,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdc2")){
                    strcpy(vd2,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdc3")){
                    strcpy(vd3,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdc4")){
                    strcpy(vd4,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdc5")){
                    strcpy(vd5,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdc6")){
                    strcpy(vd6,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdc7")){
                    strcpy(vd7,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdc8")){
                    strcpy(vd8,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdc9")){
                    strcpy(vd9,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdc10")){
                    strcpy(vd10,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdc11")){
                    strcpy(vd11,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdc12")){
                    strcpy(vd12,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdd1")){
                    strcpy(vd1,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdd2")){
                    strcpy(vd2,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdd3")){
                    strcpy(vd3,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdd4")){
                    strcpy(vd4,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdd5")){
                    strcpy(vd5,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdd6")){
                    strcpy(vd6,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdd7")){
                    strcpy(vd7,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdd8")){
                    strcpy(vd8,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdd9")){
                    strcpy(vd9,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdd10")){
                    strcpy(vd10,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdd11")){
                    strcpy(vd11,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdd12")){
                    strcpy(vd12,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vde1")){
                    strcpy(vd1,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vde2")){
                    strcpy(vd2,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vde3")){
                    strcpy(vd3,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vde4")){
                    strcpy(vd4,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vde5")){
                    strcpy(vd5,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vde6")){
                    strcpy(vd6,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vde7")){
                    strcpy(vd7,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vde8")){
                    strcpy(vd8,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vde9")){
                    strcpy(vd9,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vde10")){
                    strcpy(vd10,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vde11")){
                    strcpy(vd11,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vde12")){
                    strcpy(vd12,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdf1")){
                    strcpy(vd1,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdf2")){
                    strcpy(vd2,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdf3")){
                    strcpy(vd3,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdf4")){
                    strcpy(vd4,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdf5")){
                    strcpy(vd5,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdf6")){
                    strcpy(vd6,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdf7")){
                    strcpy(vd7,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdf8")){
                    strcpy(vd8,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdf9")){
                    strcpy(vd9,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdf10")){
                    strcpy(vd10,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdf11")){
                    strcpy(vd11,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdf12")){
                    strcpy(vd12,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdg1")){
                    strcpy(vd1,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdg2")){
                    strcpy(vd2,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdg3")){
                    strcpy(vd3,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdg4")){
                    strcpy(vd4,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdg5")){
                    strcpy(vd5,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdg6")){
                    strcpy(vd6,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdg7")){
                    strcpy(vd7,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdg8")){
                    strcpy(vd8,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdg9")){
                    strcpy(vd9,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdg10")){
                    strcpy(vd10,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdg11")){
                    strcpy(vd11,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdg12")){
                    strcpy(vd12,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdh1")){
                    strcpy(vd1,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdh2")){
                    strcpy(vd2,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdh3")){
                    strcpy(vd3,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdh4")){
                    strcpy(vd4,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdh5")){
                    strcpy(vd5,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdh6")){
                    strcpy(vd6,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdh7")){
                    strcpy(vd7,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdh8")){
                    strcpy(vd8,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdh9")){
                    strcpy(vd9,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdh10")){
                    strcpy(vd10,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdh11")){
                    strcpy(vd11,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdh12")){
                    strcpy(vd12,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdi1")){
                    strcpy(vd1,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdi2")){
                    strcpy(vd2,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdi3")){
                    strcpy(vd3,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdi4")){
                    strcpy(vd4,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdi5")){
                    strcpy(vd5,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdi6")){
                    strcpy(vd6,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdi7")){
                    strcpy(vd7,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdi8")){
                    strcpy(vd8,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdi9")){
                    strcpy(vd9,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdi10")){
                    strcpy(vd10,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdi11")){
                    strcpy(vd11,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdi12")){
                    strcpy(vd12,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdj1")){
                    strcpy(vd1,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdj2")){
                    strcpy(vd2,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdj3")){
                    strcpy(vd3,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdj4")){
                    strcpy(vd4,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdj5")){
                    strcpy(vd5,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdj6")){
                    strcpy(vd6,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdj7")){
                    strcpy(vd7,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdj8")){
                    strcpy(vd8,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdj9")){
                    strcpy(vd9,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdj10")){
                    strcpy(vd10,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdj11")){
                    strcpy(vd11,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdj12")){
                    strcpy(vd12,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdk1")){
                    strcpy(vd1,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdk2")){
                    strcpy(vd2,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdk3")){
                    strcpy(vd3,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdk4")){
                    strcpy(vd4,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdk5")){
                    strcpy(vd5,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdk6")){
                    strcpy(vd6,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdk7")){
                    strcpy(vd7,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdk8")){
                    strcpy(vd8,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdk9")){
                    strcpy(vd9,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdk10")){
                    strcpy(vd10,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdk11")){
                    strcpy(vd11,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdk12")){
                    strcpy(vd12,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdl1")){
                    strcpy(vd1,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdl2")){
                    strcpy(vd2,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdl3")){
                    strcpy(vd3,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdl4")){
                    strcpy(vd4,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdl5")){
                    strcpy(vd5,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdl6")){
                    strcpy(vd6,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdl7")){
                    strcpy(vd7,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdl8")){
                    strcpy(vd8,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdl9")){
                    strcpy(vd9,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdl10")){
                    strcpy(vd10,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdl11")){
                    strcpy(vd11,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdl12")){
                    strcpy(vd12,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdm1")){
                    strcpy(vd1,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdm2")){
                    strcpy(vd2,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdm3")){
                    strcpy(vd3,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdm4")){
                    strcpy(vd4,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdm5")){
                    strcpy(vd5,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdm6")){
                    strcpy(vd6,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdm7")){
                    strcpy(vd7,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdm8")){
                    strcpy(vd8,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdm9")){
                    strcpy(vd9,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdm10")){
                    strcpy(vd10,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdm11")){
                    strcpy(vd11,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdm12")){
                    strcpy(vd12,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdn1")){
                    strcpy(vd1,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdn2")){
                    strcpy(vd2,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdn3")){
                    strcpy(vd3,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdn4")){
                    strcpy(vd4,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdn5")){
                    strcpy(vd5,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdn6")){
                    strcpy(vd6,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdn7")){
                    strcpy(vd7,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdn8")){
                    strcpy(vd8,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdn9")){
                    strcpy(vd9,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdn10")){
                    strcpy(vd10,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdn11")){
                    strcpy(vd11,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdn12")){
                    strcpy(vd12,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdo1")){
                    strcpy(vd1,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdo2")){
                    strcpy(vd2,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdo3")){
                    strcpy(vd3,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdo4")){
                    strcpy(vd4,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdo5")){
                    strcpy(vd5,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdo6")){
                    strcpy(vd6,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdo7")){
                    strcpy(vd7,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdo8")){
                    strcpy(vd8,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdo9")){
                    strcpy(vd9,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdo10")){
                    strcpy(vd10,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdo11")){
                    strcpy(vd11,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdo12")){
                    strcpy(vd12,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdp1")){
                    strcpy(vd1,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdp2")){
                    strcpy(vd2,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdp3")){
                    strcpy(vd3,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdp4")){
                    strcpy(vd4,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdp5")){
                    strcpy(vd5,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdp6")){
                    strcpy(vd6,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdp7")){
                    strcpy(vd7,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdp8")){
                    strcpy(vd8,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdp9")){
                    strcpy(vd9,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdp10")){
                    strcpy(vd10,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdp11")){
                    strcpy(vd11,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdp12")){
                    strcpy(vd12,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdq1")){
                    strcpy(vd1,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdq2")){
                    strcpy(vd2,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdq3")){
                    strcpy(vd3,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdq4")){
                    strcpy(vd4,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdq5")){
                    strcpy(vd5,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdq6")){
                    strcpy(vd6,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdq7")){
                    strcpy(vd7,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdq8")){
                    strcpy(vd8,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdq9")){
                    strcpy(vd9,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdq10")){
                    strcpy(vd10,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdq11")){
                    strcpy(vd11,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdq12")){
                    strcpy(vd12,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdr1")){
                    strcpy(vd1,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdr2")){
                    strcpy(vd2,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdr3")){
                    strcpy(vd3,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdr4")){
                    strcpy(vd4,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdr5")){
                    strcpy(vd5,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdr6")){
                    strcpy(vd6,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdr7")){
                    strcpy(vd7,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdr8")){
                    strcpy(vd8,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdr9")){
                    strcpy(vd9,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdr10")){
                    strcpy(vd10,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdr11")){
                    strcpy(vd11,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdr12")){
                    strcpy(vd12,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vds1")){
                    strcpy(vd1,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vds2")){
                    strcpy(vd2,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vds3")){
                    strcpy(vd3,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vds4")){
                    strcpy(vd4,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vds5")){
                    strcpy(vd5,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vds6")){
                    strcpy(vd6,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vds7")){
                    strcpy(vd7,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vds8")){
                    strcpy(vd8,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vds9")){
                    strcpy(vd9,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vds10")){
                    strcpy(vd10,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vds11")){
                    strcpy(vd11,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vds12")){
                    strcpy(vd12,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdt1")){
                    strcpy(vd1,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdt2")){
                    strcpy(vd2,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdt3")){
                    strcpy(vd3,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdt4")){
                    strcpy(vd4,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdt5")){
                    strcpy(vd5,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdt6")){
                    strcpy(vd6,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdt7")){
                    strcpy(vd7,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdt8")){
                    strcpy(vd8,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdt9")){
                    strcpy(vd9,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdt10")){
                    strcpy(vd10,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdt11")){
                    strcpy(vd11,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdt12")){
                    strcpy(vd12,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdu1")){
                    strcpy(vd1,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdu2")){
                    strcpy(vd2,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdu3")){
                    strcpy(vd3,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdu4")){
                    strcpy(vd4,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdu5")){
                    strcpy(vd5,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdu6")){
                    strcpy(vd6,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdu7")){
                    strcpy(vd7,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdu8")){
                    strcpy(vd8,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdu9")){
                    strcpy(vd9,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdu10")){
                    strcpy(vd10,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdu11")){
                    strcpy(vd11,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdu12")){
                    strcpy(vd12,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdv1")){
                    strcpy(vd1,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdv2")){
                    strcpy(vd2,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdv3")){
                    strcpy(vd3,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdv4")){
                    strcpy(vd4,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdv5")){
                    strcpy(vd5,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdv6")){
                    strcpy(vd6,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdv7")){
                    strcpy(vd7,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdv8")){
                    strcpy(vd8,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdv9")){
                    strcpy(vd9,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdv10")){
                    strcpy(vd10,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdv11")){
                    strcpy(vd11,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdv12")){
                    strcpy(vd12,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdw1")){
                    strcpy(vd1,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdw2")){
                    strcpy(vd2,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdw3")){
                    strcpy(vd3,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdw4")){
                    strcpy(vd4,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdw5")){
                    strcpy(vd5,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdw6")){
                    strcpy(vd6,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdw7")){
                    strcpy(vd7,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdw8")){
                    strcpy(vd8,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdw9")){
                    strcpy(vd9,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdw10")){
                    strcpy(vd10,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdw11")){
                    strcpy(vd11,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdw12")){
                    strcpy(vd12,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdx1")){
                    strcpy(vd1,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdx2")){
                    strcpy(vd2,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdx3")){
                    strcpy(vd3,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdx4")){
                    strcpy(vd4,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdx5")){
                    strcpy(vd5,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdx6")){
                    strcpy(vd6,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdx7")){
                    strcpy(vd7,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdx8")){
                    strcpy(vd8,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdx9")){
                    strcpy(vd9,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdx10")){
                    strcpy(vd10,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdx11")){
                    strcpy(vd11,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdx12")){
                    strcpy(vd12,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdy1")){
                    strcpy(vd1,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdy2")){
                    strcpy(vd2,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdy3")){
                    strcpy(vd3,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdy4")){
                    strcpy(vd4,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdy5")){
                    strcpy(vd5,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdy6")){
                    strcpy(vd6,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdy7")){
                    strcpy(vd7,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdy8")){
                    strcpy(vd8,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdy9")){
                    strcpy(vd9,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdy10")){
                    strcpy(vd10,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdy11")){
                    strcpy(vd11,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdy12")){
                    strcpy(vd12,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdz1")){
                    strcpy(vd1,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdz2")){
                    strcpy(vd2,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdz3")){
                    strcpy(vd3,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdz4")){
                    strcpy(vd4,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdz5")){
                    strcpy(vd5,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdz6")){
                    strcpy(vd6,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdz7")){
                    strcpy(vd7,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdz8")){
                    strcpy(vd8,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdz9")){
                    strcpy(vd9,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdz10")){
                    strcpy(vd10,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdz11")){
                    strcpy(vd11,verificarSiExiste->id);
                }else if(strstr(verificarSiExiste->id,"vdz12")){
                    strcpy(vd12,verificarSiExiste->id);
                }
                siExiste = 1;
                //break;
            }

            verificarSiExiste = verificarSiExiste->siguiente;
        }

        if(siExiste == 1){

            if(strstr(vd1,"vda1") || strstr(vd2,"vda2") || strstr(vd3,"vda3") || strstr(vd4,"vda4") || strstr(vd5,"vda5") || strstr(vd6,"vda6") || strstr(vd7,"vda7") || strstr(vd8,"vda8") || strstr(vd9,"vda9") || strstr(vd10,"vda10") || strstr(vd11,"vda11") || strstr(vd12,"vda12")){
                if(strcmp(vd1,"") == 0){
                    strcpy(aux->id,"vda1");
                    ingresar = 1;
                }else if(strcmp(vd2,"") == 0){
                    strcpy(aux->id,"vda2");
                    ingresar = 1;
                }else if(strcmp(vd3,"") == 0){
                    strcpy(aux->id,"vda3");
                    ingresar = 1;
                }else if(strcmp(vd4,"") == 0){
                    strcpy(aux->id,"vda4");
                    ingresar = 1;
                }else if(strcmp(vd5,"") == 0){
                    strcpy(aux->id,"vda5");
                    ingresar = 1;
                }else if(strcmp(vd6,"") == 0){
                    strcpy(aux->id,"vda6");
                    ingresar = 1;
                }else if(strcmp(vd7,"") == 0){
                    strcpy(aux->id,"vda7");
                    ingresar = 1;
                }else if(strcmp(vd8,"") == 0){
                    strcpy(aux->id,"vda8");
                    ingresar = 1;
                }else if(strcmp(vd9,"") == 0){
                    strcpy(aux->id,"vda9");
                    ingresar = 1;
                }else if(strcmp(vd10,"") == 0){
                    strcpy(aux->id,"vda10");
                    ingresar = 1;
                }else if(strcmp(vd11,"") == 0){
                    strcpy(aux->id,"vda11");
                    ingresar = 1;
                }else if(strcmp(vd12,"") == 0){
                    strcpy(aux->id,"vda12");
                    ingresar = 1;
                }else{
                    printf("\nERROR. No se pudo agregar\n");
                }
            }else if(strstr(vd1,"vdb1") || strstr(vd2,"vdb2") || strstr(vd3,"vdb3") || strstr(vd4,"vdb4") || strstr(vd5,"vdb5") || strstr(vd6,"vdb6") || strstr(vd7,"vdb7") || strstr(vd8,"vdb8") || strstr(vd9,"vdb9") || strstr(vd10,"vdb10") || strstr(vd11,"vdb11") || strstr(vd12,"vdb12")){
                if(strcmp(vd1,"") == 0){
                    strcpy(aux->id,"vdb1");
                    ingresar = 1;
                }else if(strcmp(vd2,"") == 0){
                    strcpy(aux->id,"vdb2");
                    ingresar = 1;
                }else if(strcmp(vd3,"") == 0){
                    strcpy(aux->id,"vdb3");
                    ingresar = 1;
                }else if(strcmp(vd4,"") == 0){
                    strcpy(aux->id,"vdb4");
                    ingresar = 1;
                }else if(strcmp(vd5,"") == 0){
                    strcpy(aux->id,"vdb5");
                    ingresar = 1;
                }else if(strcmp(vd6,"") == 0){
                    strcpy(aux->id,"vdb6");
                    ingresar = 1;
                }else if(strcmp(vd7,"") == 0){
                    strcpy(aux->id,"vdb7");
                    ingresar = 1;
                }else if(strcmp(vd8,"") == 0){
                    strcpy(aux->id,"vdb8");
                    ingresar = 1;
                }else if(strcmp(vd9,"") == 0){
                    strcpy(aux->id,"vdb9");
                    ingresar = 1;
                }else if(strcmp(vd10,"") == 0){
                    strcpy(aux->id,"vdb10");
                    ingresar = 1;
                }else if(strcmp(vd11,"") == 0){
                    strcpy(aux->id,"vdb11");
                    ingresar = 1;
                }else if(strcmp(vd12,"") == 0){
                    strcpy(aux->id,"vdb12");
                    ingresar = 1;
                }else{
                    printf("\nERROR. No se pudo agregar\n");
                }
            }else if(strstr(vd1,"vdc1") || strstr(vd2,"vdc2") || strstr(vd3,"vdc3") || strstr(vd4,"vdc4") || strstr(vd5,"vdc5") || strstr(vd6,"vdc6") || strstr(vd7,"vdc7") || strstr(vd8,"vdc8") || strstr(vd9,"vdc9") || strstr(vd10,"vdc10") || strstr(vd11,"vdc11") || strstr(vd12,"vdc12")){
                if(strcmp(vd1,"") == 0){
                    strcpy(aux->id,"vdc1");
                    ingresar = 1;
                }else if(strcmp(vd2,"") == 0){
                    strcpy(aux->id,"vdc2");
                    ingresar = 1;
                }else if(strcmp(vd3,"") == 0){
                    strcpy(aux->id,"vdc3");
                    ingresar = 1;
                }else if(strcmp(vd4,"") == 0){
                    strcpy(aux->id,"vdc4");
                    ingresar = 1;
                }else if(strcmp(vd5,"") == 0){
                    strcpy(aux->id,"vdc5");
                    ingresar = 1;
                }else if(strcmp(vd6,"") == 0){
                    strcpy(aux->id,"vdc6");
                    ingresar = 1;
                }else if(strcmp(vd7,"") == 0){
                    strcpy(aux->id,"vdc7");
                    ingresar = 1;
                }else if(strcmp(vd8,"") == 0){
                    strcpy(aux->id,"vdc8");
                    ingresar = 1;
                }else if(strcmp(vd9,"") == 0){
                    strcpy(aux->id,"vdc9");
                    ingresar = 1;
                }else if(strcmp(vd10,"") == 0){
                    strcpy(aux->id,"vdc10");
                    ingresar = 1;
                }else if(strcmp(vd11,"") == 0){
                    strcpy(aux->id,"vdc11");
                    ingresar = 1;
                }else if(strcmp(vd12,"") == 0){
                    strcpy(aux->id,"vdc12");
                    ingresar = 1;
                }else{
                    printf("\nERROR. No se pudo agregar\n");
                }
            }else if(strstr(vd1,"vdd1") || strstr(vd2,"vdd2") || strstr(vd3,"vdd3") || strstr(vd4,"vdd4") || strstr(vd5,"vdd5") || strstr(vd6,"vdd6") || strstr(vd7,"vdd7") || strstr(vd8,"vdd8") || strstr(vd9,"vdd9") || strstr(vd10,"vdd10") || strstr(vd11,"vdd11") || strstr(vd12,"vdd12")){
                if(strcmp(vd1,"") == 0){
                    strcpy(aux->id,"vdd1");
                    ingresar = 1;
                }else if(strcmp(vd2,"") == 0){
                    strcpy(aux->id,"vdd2");
                    ingresar = 1;
                }else if(strcmp(vd3,"") == 0){
                    strcpy(aux->id,"vdd3");
                    ingresar = 1;
                }else if(strcmp(vd4,"") == 0){
                    strcpy(aux->id,"vdd4");
                    ingresar = 1;
                }else if(strcmp(vd5,"") == 0){
                    strcpy(aux->id,"vdd5");
                    ingresar = 1;
                }else if(strcmp(vd6,"") == 0){
                    strcpy(aux->id,"vdd6");
                    ingresar = 1;
                }else if(strcmp(vd7,"") == 0){
                    strcpy(aux->id,"vdd7");
                    ingresar = 1;
                }else if(strcmp(vd8,"") == 0){
                    strcpy(aux->id,"vdd8");
                    ingresar = 1;
                }else if(strcmp(vd9,"") == 0){
                    strcpy(aux->id,"vdd9");
                    ingresar = 1;
                }else if(strcmp(vd10,"") == 0){
                    strcpy(aux->id,"vdd10");
                    ingresar = 1;
                }else if(strcmp(vd11,"") == 0){
                    strcpy(aux->id,"vdd11");
                    ingresar = 1;
                }else if(strcmp(vd12,"") == 0){
                    strcpy(aux->id,"vdd12");
                    ingresar = 1;
                }else{
                    printf("\nERROR. No se pudo agregar\n");
                }
            }else if(strstr(vd1,"vde1") || strstr(vd2,"vde2") || strstr(vd3,"vde3") || strstr(vd4,"vde4") || strstr(vd5,"vde5") || strstr(vd6,"vde6") || strstr(vd7,"vde7") || strstr(vd8,"vde8") || strstr(vd9,"vde9") || strstr(vd10,"vde10") || strstr(vd11,"vde11") || strstr(vd12,"vde12")){
                if(strcmp(vd1,"") == 0){
                    strcpy(aux->id,"vde1");
                    ingresar = 1;
                }else if(strcmp(vd2,"") == 0){
                    strcpy(aux->id,"vde2");
                    ingresar = 1;
                }else if(strcmp(vd3,"") == 0){
                    strcpy(aux->id,"vde3");
                    ingresar = 1;
                }else if(strcmp(vd4,"") == 0){
                    strcpy(aux->id,"vde4");
                    ingresar = 1;
                }else if(strcmp(vd5,"") == 0){
                    strcpy(aux->id,"vde5");
                    ingresar = 1;
                }else if(strcmp(vd6,"") == 0){
                    strcpy(aux->id,"vde6");
                    ingresar = 1;
                }else if(strcmp(vd7,"") == 0){
                    strcpy(aux->id,"vde7");
                    ingresar = 1;
                }else if(strcmp(vd8,"") == 0){
                    strcpy(aux->id,"vde8");
                    ingresar = 1;
                }else if(strcmp(vd9,"") == 0){
                    strcpy(aux->id,"vde9");
                    ingresar = 1;
                }else if(strcmp(vd10,"") == 0){
                    strcpy(aux->id,"vde10");
                    ingresar = 1;
                }else if(strcmp(vd11,"") == 0){
                    strcpy(aux->id,"vde11");
                    ingresar = 1;
                }else if(strcmp(vd12,"") == 0){
                    strcpy(aux->id,"vde12");
                    ingresar = 1;
                }else{
                    printf("\nERROR. No se pudo agregar\n");
                }
            }else if(strstr(vd1,"vdf1") || strstr(vd2,"vdf2") || strstr(vd3,"vdf3") || strstr(vd4,"vdf4") || strstr(vd5,"vdf5") || strstr(vd6,"vdf6") || strstr(vd7,"vdf7") || strstr(vd8,"vdf8") || strstr(vd9,"vdf9") || strstr(vd10,"vdf10") || strstr(vd11,"vdf11") || strstr(vd12,"vdf12")){
                if(strcmp(vd1,"") == 0){
                    strcpy(aux->id,"vdf1");
                    ingresar = 1;
                }else if(strcmp(vd2,"") == 0){
                    strcpy(aux->id,"vdf2");
                    ingresar = 1;
                }else if(strcmp(vd3,"") == 0){
                    strcpy(aux->id,"vdf3");
                    ingresar = 1;
                }else if(strcmp(vd4,"") == 0){
                    strcpy(aux->id,"vdf4");
                    ingresar = 1;
                }else if(strcmp(vd5,"") == 0){
                    strcpy(aux->id,"vdf5");
                    ingresar = 1;
                }else if(strcmp(vd6,"") == 0){
                    strcpy(aux->id,"vdf6");
                    ingresar = 1;
                }else if(strcmp(vd7,"") == 0){
                    strcpy(aux->id,"vdf7");
                    ingresar = 1;
                }else if(strcmp(vd8,"") == 0){
                    strcpy(aux->id,"vdf8");
                    ingresar = 1;
                }else if(strcmp(vd9,"") == 0){
                    strcpy(aux->id,"vdf9");
                    ingresar = 1;
                }else if(strcmp(vd10,"") == 0){
                    strcpy(aux->id,"vdf10");
                    ingresar = 1;
                }else if(strcmp(vd11,"") == 0){
                    strcpy(aux->id,"vdf11");
                    ingresar = 1;
                }else if(strcmp(vd12,"") == 0){
                    strcpy(aux->id,"vdf12");
                    ingresar = 1;
                }else{
                    printf("\nERROR. No se pudo agregar\n");
                }
            }else if(strstr(vd1,"vdg1") || strstr(vd2,"vdg2") || strstr(vd3,"vdg3") || strstr(vd4,"vdg4") || strstr(vd5,"vdg5") || strstr(vd6,"vdg6") || strstr(vd7,"vdg7") || strstr(vd8,"vdg8") || strstr(vd9,"vdg9") || strstr(vd10,"vdg10") || strstr(vd11,"vdg11") || strstr(vd12,"vdg12")){
                if(strcmp(vd1,"") == 0){
                    strcpy(aux->id,"vdg1");
                    ingresar = 1;
                }else if(strcmp(vd2,"") == 0){
                    strcpy(aux->id,"vdg2");
                    ingresar = 1;
                }else if(strcmp(vd3,"") == 0){
                    strcpy(aux->id,"vdg3");
                    ingresar = 1;
                }else if(strcmp(vd4,"") == 0){
                    strcpy(aux->id,"vdg4");
                    ingresar = 1;
                }else if(strcmp(vd5,"") == 0){
                    strcpy(aux->id,"vdg5");
                    ingresar = 1;
                }else if(strcmp(vd6,"") == 0){
                    strcpy(aux->id,"vdg6");
                    ingresar = 1;
                }else if(strcmp(vd7,"") == 0){
                    strcpy(aux->id,"vdg7");
                    ingresar = 1;
                }else if(strcmp(vd8,"") == 0){
                    strcpy(aux->id,"vdg8");
                    ingresar = 1;
                }else if(strcmp(vd9,"") == 0){
                    strcpy(aux->id,"vdg9");
                    ingresar = 1;
                }else if(strcmp(vd10,"") == 0){
                    strcpy(aux->id,"vdg10");
                    ingresar = 1;
                }else if(strcmp(vd11,"") == 0){
                    strcpy(aux->id,"vdg11");
                    ingresar = 1;
                }else if(strcmp(vd12,"") == 0){
                    strcpy(aux->id,"vdg12");
                    ingresar = 1;
                }else{
                    printf("\nERROR. No se pudo agregar\n");
                }
            }else if(strstr(vd1,"vdh1") || strstr(vd2,"vdh2") || strstr(vd3,"vdh3") || strstr(vd4,"vdh4") || strstr(vd5,"vdh5") || strstr(vd6,"vdh6") || strstr(vd7,"vdh7") || strstr(vd8,"vdh8") || strstr(vd9,"vdh9") || strstr(vd10,"vdh10") || strstr(vd11,"vdh11") || strstr(vd12,"vdh12")){
                if(strcmp(vd1,"") == 0){
                    strcpy(aux->id,"vdh1");
                    ingresar = 1;
                }else if(strcmp(vd2,"") == 0){
                    strcpy(aux->id,"vdh2");
                    ingresar = 1;
                }else if(strcmp(vd3,"") == 0){
                    strcpy(aux->id,"vdh3");
                    ingresar = 1;
                }else if(strcmp(vd4,"") == 0){
                    strcpy(aux->id,"vdh4");
                    ingresar = 1;
                }else if(strcmp(vd5,"") == 0){
                    strcpy(aux->id,"vdh5");
                    ingresar = 1;
                }else if(strcmp(vd6,"") == 0){
                    strcpy(aux->id,"vdh6");
                    ingresar = 1;
                }else if(strcmp(vd7,"") == 0){
                    strcpy(aux->id,"vdh7");
                    ingresar = 1;
                }else if(strcmp(vd8,"") == 0){
                    strcpy(aux->id,"vdh8");
                    ingresar = 1;
                }else if(strcmp(vd9,"") == 0){
                    strcpy(aux->id,"vdh9");
                    ingresar = 1;
                }else if(strcmp(vd10,"") == 0){
                    strcpy(aux->id,"vdh10");
                    ingresar = 1;
                }else if(strcmp(vd11,"") == 0){
                    strcpy(aux->id,"vdh11");
                    ingresar = 1;
                }else if(strcmp(vd12,"") == 0){
                    strcpy(aux->id,"vdh12");
                    ingresar = 1;
                }else{
                    printf("\nERROR. No se pudo agregar\n");
                }
            }else if(strstr(vd1,"vdi1") || strstr(vd2,"vdi2") || strstr(vd3,"vdi3") || strstr(vd4,"vdi4") || strstr(vd5,"vdi5") || strstr(vd6,"vdi6") || strstr(vd7,"vdi7") || strstr(vd8,"vdi8") || strstr(vd9,"vdi9") || strstr(vd10,"vdi10") || strstr(vd11,"vdi11") || strstr(vd12,"vdi12")){
                if(strcmp(vd1,"") == 0){
                    strcpy(aux->id,"vdi1");
                    ingresar = 1;
                }else if(strcmp(vd2,"") == 0){
                    strcpy(aux->id,"vdi2");
                    ingresar = 1;
                }else if(strcmp(vd3,"") == 0){
                    strcpy(aux->id,"vdi3");
                    ingresar = 1;
                }else if(strcmp(vd4,"") == 0){
                    strcpy(aux->id,"vdi4");
                    ingresar = 1;
                }else if(strcmp(vd5,"") == 0){
                    strcpy(aux->id,"vdi5");
                    ingresar = 1;
                }else if(strcmp(vd6,"") == 0){
                    strcpy(aux->id,"vdi6");
                    ingresar = 1;
                }else if(strcmp(vd7,"") == 0){
                    strcpy(aux->id,"vdi7");
                    ingresar = 1;
                }else if(strcmp(vd8,"") == 0){
                    strcpy(aux->id,"vdi8");
                    ingresar = 1;
                }else if(strcmp(vd9,"") == 0){
                    strcpy(aux->id,"vdi9");
                    ingresar = 1;
                }else if(strcmp(vd10,"") == 0){
                    strcpy(aux->id,"vdi10");
                    ingresar = 1;
                }else if(strcmp(vd11,"") == 0){
                    strcpy(aux->id,"vdi11");
                    ingresar = 1;
                }else if(strcmp(vd12,"") == 0){
                    strcpy(aux->id,"vdi12");
                    ingresar = 1;
                }else{
                    printf("\nERROR. No se pudo agregar\n");
                }
            }else if(strstr(vd1,"vdj1") || strstr(vd2,"vdj2") || strstr(vd3,"vdj3") || strstr(vd4,"vdj4") || strstr(vd5,"vdj5") || strstr(vd6,"vdj6") || strstr(vd7,"vdj7") || strstr(vd8,"vdj8") || strstr(vd9,"vdj9") || strstr(vd10,"vdj10") || strstr(vd11,"vdj11") || strstr(vd12,"vdj12")){
                if(strcmp(vd1,"") == 0){
                    strcpy(aux->id,"vdj1");
                    ingresar = 1;
                }else if(strcmp(vd2,"") == 0){
                    strcpy(aux->id,"vdj2");
                    ingresar = 1;
                }else if(strcmp(vd3,"") == 0){
                    strcpy(aux->id,"vdj3");
                    ingresar = 1;
                }else if(strcmp(vd4,"") == 0){
                    strcpy(aux->id,"vdj4");
                    ingresar = 1;
                }else if(strcmp(vd5,"") == 0){
                    strcpy(aux->id,"vdj5");
                    ingresar = 1;
                }else if(strcmp(vd6,"") == 0){
                    strcpy(aux->id,"vdj6");
                    ingresar = 1;
                }else if(strcmp(vd7,"") == 0){
                    strcpy(aux->id,"vdj7");
                    ingresar = 1;
                }else if(strcmp(vd8,"") == 0){
                    strcpy(aux->id,"vdj8");
                    ingresar = 1;
                }else if(strcmp(vd9,"") == 0){
                    strcpy(aux->id,"vdj9");
                    ingresar = 1;
                }else if(strcmp(vd10,"") == 0){
                    strcpy(aux->id,"vdj10");
                    ingresar = 1;
                }else if(strcmp(vd11,"") == 0){
                    strcpy(aux->id,"vdj11");
                    ingresar = 1;
                }else if(strcmp(vd12,"") == 0){
                    strcpy(aux->id,"vdj12");
                    ingresar = 1;
                }else{
                    printf("\nERROR. No se pudo agregar\n");
                }
            }else if(strstr(vd1,"vdk1") || strstr(vd2,"vdk2") || strstr(vd3,"vdk3") || strstr(vd4,"vdk4") || strstr(vd5,"vdk5") || strstr(vd6,"vdk6") || strstr(vd7,"vdk7") || strstr(vd8,"vdk8") || strstr(vd9,"vdk9") || strstr(vd10,"vdk10") || strstr(vd11,"vdk11") || strstr(vd12,"vdk12")){
                if(strcmp(vd1,"") == 0){
                    strcpy(aux->id,"vdk1");
                    ingresar = 1;
                }else if(strcmp(vd2,"") == 0){
                    strcpy(aux->id,"vdk2");
                    ingresar = 1;
                }else if(strcmp(vd3,"") == 0){
                    strcpy(aux->id,"vdk3");
                    ingresar = 1;
                }else if(strcmp(vd4,"") == 0){
                    strcpy(aux->id,"vdk4");
                    ingresar = 1;
                }else if(strcmp(vd5,"") == 0){
                    strcpy(aux->id,"vdk5");
                    ingresar = 1;
                }else if(strcmp(vd6,"") == 0){
                    strcpy(aux->id,"vdk6");
                    ingresar = 1;
                }else if(strcmp(vd7,"") == 0){
                    strcpy(aux->id,"vdk7");
                    ingresar = 1;
                }else if(strcmp(vd8,"") == 0){
                    strcpy(aux->id,"vdk8");
                    ingresar = 1;
                }else if(strcmp(vd9,"") == 0){
                    strcpy(aux->id,"vdk9");
                    ingresar = 1;
                }else if(strcmp(vd10,"") == 0){
                    strcpy(aux->id,"vdk10");
                    ingresar = 1;
                }else if(strcmp(vd11,"") == 0){
                    strcpy(aux->id,"vdk11");
                    ingresar = 1;
                }else if(strcmp(vd12,"") == 0){
                    strcpy(aux->id,"vdk12");
                    ingresar = 1;
                }else{
                    printf("\nERROR. No se pudo agregar\n");
                }
            }else if(strstr(vd1,"vdl1") || strstr(vd2,"vdl2") || strstr(vd3,"vdl3") || strstr(vd4,"vdl4") || strstr(vd5,"vdl5") || strstr(vd6,"vdl6") || strstr(vd7,"vdl7") || strstr(vd8,"vdl8") || strstr(vd9,"vdl9") || strstr(vd10,"vdl10") || strstr(vd11,"vdl11") || strstr(vd12,"vdl12")){
                if(strcmp(vd1,"") == 0){
                    strcpy(aux->id,"vdl1");
                    ingresar = 1;
                }else if(strcmp(vd2,"") == 0){
                    strcpy(aux->id,"vdl2");
                    ingresar = 1;
                }else if(strcmp(vd3,"") == 0){
                    strcpy(aux->id,"vdl3");
                    ingresar = 1;
                }else if(strcmp(vd4,"") == 0){
                    strcpy(aux->id,"vdl4");
                    ingresar = 1;
                }else if(strcmp(vd5,"") == 0){
                    strcpy(aux->id,"vdl5");
                    ingresar = 1;
                }else if(strcmp(vd6,"") == 0){
                    strcpy(aux->id,"vdl6");
                    ingresar = 1;
                }else if(strcmp(vd7,"") == 0){
                    strcpy(aux->id,"vdl7");
                    ingresar = 1;
                }else if(strcmp(vd8,"") == 0){
                    strcpy(aux->id,"vdl8");
                    ingresar = 1;
                }else if(strcmp(vd9,"") == 0){
                    strcpy(aux->id,"vdl9");
                    ingresar = 1;
                }else if(strcmp(vd10,"") == 0){
                    strcpy(aux->id,"vdl10");
                    ingresar = 1;
                }else if(strcmp(vd11,"") == 0){
                    strcpy(aux->id,"vdl11");
                    ingresar = 1;
                }else if(strcmp(vd12,"") == 0){
                    strcpy(aux->id,"vdl12");
                    ingresar = 1;
                }else{
                    printf("\nERROR. No se pudo agregar\n");
                }
            }else if(strstr(vd1,"vdm1") || strstr(vd2,"vdm2") || strstr(vd3,"vdm3") || strstr(vd4,"vdm4") || strstr(vd5,"vdm5") || strstr(vd6,"vdm6") || strstr(vd7,"vdm7") || strstr(vd8,"vdm8") || strstr(vd9,"vdm9") || strstr(vd10,"vdm10") || strstr(vd11,"vdm11") || strstr(vd12,"vdm12")){
                if(strcmp(vd1,"") == 0){
                    strcpy(aux->id,"vdm1");
                    ingresar = 1;
                }else if(strcmp(vd2,"") == 0){
                    strcpy(aux->id,"vdm2");
                    ingresar = 1;
                }else if(strcmp(vd3,"") == 0){
                    strcpy(aux->id,"vdm3");
                    ingresar = 1;
                }else if(strcmp(vd4,"") == 0){
                    strcpy(aux->id,"vdm4");
                    ingresar = 1;
                }else if(strcmp(vd5,"") == 0){
                    strcpy(aux->id,"vdm5");
                    ingresar = 1;
                }else if(strcmp(vd6,"") == 0){
                    strcpy(aux->id,"vdm6");
                    ingresar = 1;
                }else if(strcmp(vd7,"") == 0){
                    strcpy(aux->id,"vdm7");
                    ingresar = 1;
                }else if(strcmp(vd8,"") == 0){
                    strcpy(aux->id,"vdm8");
                    ingresar = 1;
                }else if(strcmp(vd9,"") == 0){
                    strcpy(aux->id,"vdm9");
                    ingresar = 1;
                }else if(strcmp(vd10,"") == 0){
                    strcpy(aux->id,"vdm10");
                    ingresar = 1;
                }else if(strcmp(vd11,"") == 0){
                    strcpy(aux->id,"vdm11");
                    ingresar = 1;
                }else if(strcmp(vd12,"") == 0){
                    strcpy(aux->id,"vdm12");
                    ingresar = 1;
                }else{
                    printf("\nERROR. No se pudo agregar\n");
                }
            }else if(strstr(vd1,"vdn1") || strstr(vd2,"vdn2") || strstr(vd3,"vdn3") || strstr(vd4,"vdn4") || strstr(vd5,"vdn5") || strstr(vd6,"vdn6") || strstr(vd7,"vdn7") || strstr(vd8,"vdn8") || strstr(vd9,"vdn9") || strstr(vd10,"vdn10") || strstr(vd11,"vdn11") || strstr(vd12,"vdn12")){
                if(strcmp(vd1,"") == 0){
                    strcpy(aux->id,"vdn1");
                    ingresar = 1;
                }else if(strcmp(vd2,"") == 0){
                    strcpy(aux->id,"vdn2");
                    ingresar = 1;
                }else if(strcmp(vd3,"") == 0){
                    strcpy(aux->id,"vdn3");
                    ingresar = 1;
                }else if(strcmp(vd4,"") == 0){
                    strcpy(aux->id,"vdn4");
                    ingresar = 1;
                }else if(strcmp(vd5,"") == 0){
                    strcpy(aux->id,"vdn5");
                    ingresar = 1;
                }else if(strcmp(vd6,"") == 0){
                    strcpy(aux->id,"vdn6");
                    ingresar = 1;
                }else if(strcmp(vd7,"") == 0){
                    strcpy(aux->id,"vdn7");
                    ingresar = 1;
                }else if(strcmp(vd8,"") == 0){
                    strcpy(aux->id,"vdn8");
                    ingresar = 1;
                }else if(strcmp(vd9,"") == 0){
                    strcpy(aux->id,"vdn9");
                    ingresar = 1;
                }else if(strcmp(vd10,"") == 0){
                    strcpy(aux->id,"vdn10");
                    ingresar = 1;
                }else if(strcmp(vd11,"") == 0){
                    strcpy(aux->id,"vdn11");
                    ingresar = 1;
                }else if(strcmp(vd12,"") == 0){
                    strcpy(aux->id,"vdn12");
                    ingresar = 1;
                }else{
                    printf("\nERROR. No se pudo agregar\n");
                }
            }else if(strstr(vd1,"vdo1") || strstr(vd2,"vdo2") || strstr(vd3,"vdo3") || strstr(vd4,"vdo4") || strstr(vd5,"vdo5") || strstr(vd6,"vdo6") || strstr(vd7,"vdo7") || strstr(vd8,"vdo8") || strstr(vd9,"vdo9") || strstr(vd10,"vdo10") || strstr(vd11,"vdo11") || strstr(vd12,"vdo12")){
                if(strcmp(vd1,"") == 0){
                    strcpy(aux->id,"vdo1");
                    ingresar = 1;
                }else if(strcmp(vd2,"") == 0){
                    strcpy(aux->id,"vdo2");
                    ingresar = 1;
                }else if(strcmp(vd3,"") == 0){
                    strcpy(aux->id,"vdo3");
                    ingresar = 1;
                }else if(strcmp(vd4,"") == 0){
                    strcpy(aux->id,"vdo4");
                    ingresar = 1;
                }else if(strcmp(vd5,"") == 0){
                    strcpy(aux->id,"vdo5");
                    ingresar = 1;
                }else if(strcmp(vd6,"") == 0){
                    strcpy(aux->id,"vdo6");
                    ingresar = 1;
                }else if(strcmp(vd7,"") == 0){
                    strcpy(aux->id,"vdo7");
                    ingresar = 1;
                }else if(strcmp(vd8,"") == 0){
                    strcpy(aux->id,"vdo8");
                    ingresar = 1;
                }else if(strcmp(vd9,"") == 0){
                    strcpy(aux->id,"vdo9");
                    ingresar = 1;
                }else if(strcmp(vd10,"") == 0){
                    strcpy(aux->id,"vdo10");
                    ingresar = 1;
                }else if(strcmp(vd11,"") == 0){
                    strcpy(aux->id,"vdo11");
                    ingresar = 1;
                }else if(strcmp(vd12,"") == 0){
                    strcpy(aux->id,"vdo12");
                    ingresar = 1;
                }else{
                    printf("\nERROR. No se pudo agregar\n");
                }
            }

            if(ingresar == 1){
                t->primero->anterior = aux;
                aux->siguiente = t->primero;
                t->primero = aux;
                printf("\n**Se monto particion con exito.**\n");
            }


        }else{

            if(aa == 0){
                strcpy(aux->id,"vda1");
                ingresar = 1;
            }else if(bb == 0){
                strcpy(aux->id,"vdb1");
                ingresar = 1;
            }else if(cc == 0){
                strcpy(aux->id,"vdc1");
                ingresar = 1;
            }else if(dd == 0){
                strcpy(aux->id,"vdd1");
                ingresar = 1;
            }else if(ee == 0){
                strcpy(aux->id,"vde1");
                ingresar = 1;
            }else if(ff == 0){
                strcpy(aux->id,"vdf1");
                ingresar = 1;
            }else if(gg == 0){
                strcpy(aux->id,"vdg1");
                ingresar = 1;
            }else if(hh == 0){
                strcpy(aux->id,"vdh1");
                ingresar = 1;
            }else if(ii == 0){
                strcpy(aux->id,"vdi1");
                ingresar = 1;
            }else if(jj == 0){
                strcpy(aux->id,"vdj1");
                ingresar = 1;
            }else if(kk == 0){
                strcpy(aux->id,"vdk1");
                ingresar = 1;
            }else if(ll == 0){
                strcpy(aux->id,"vdl1");
                ingresar = 1;
            }else if(mm == 0){
                strcpy(aux->id,"vdm1");
                ingresar = 1;
            }else if(nn == 0){
                strcpy(aux->id,"vdn1");
                ingresar = 1;
            }else if(oo == 0){
                strcpy(aux->id,"vdo1");
                ingresar = 1;
            }else if(pp == 0){
                strcpy(aux->id,"vdp1");
                ingresar = 1;
            }

            if(ingresar == 1){
                t->primero->anterior = aux;
                aux->siguiente = t->primero;
                t->primero = aux;
                printf("\n**Se monto particion con exito**.\n");
              // imprimirMount(tablaDeParticionese);
              //  imprimirMount2(tablaDeParticiones);
                //printCola(tablaDeParticiones);
            }
        }
    }
}

void imprimirMount(tabla *t){
        registro *aux;
        aux = t->primero;

        printf("\nMontadas: ");

        while( aux != NULL )
        {
            printf("%s\nId: ",aux->name);
            printf("%s. Nombre: ",aux->path);
            printf("%s. Path: ",aux->id);
            aux = aux->siguiente;
        }
}

void imprimirMount2(tabla *t){
        registro *aux;
        aux = tablaDeParticiones->primero;


        printf("\nMontadas: ");
         if(t->primero!=NULL){
            printf("%s\nId: ",t->primero->id);
            printf("%s. Nombre: ",t->primero->name);
            printf("%s. Path: ",t->primero->path);
            aux = t->primero->siguiente;
            while(aux!=NULL){
                printf("%s\nId: ",t->primero->id);
                printf("%s. Nombre: ",t->primero->name);
                printf("%s. Path: ",t->primero->path);
                t = t->primero->siguiente;
            }
        }

}

void printCola(tabla *q){
    registro *aux;
    aux=q->primero;
    //printf("\nMontadas: ");

    while(aux!=NULL){
        printf("%s, ",aux->id);
        printf("%s, ",aux->name);
        printf("%s.",aux->path);
        printf("\n");
        aux=aux->siguiente;
    }
}






