#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>
#define TRUE 1

/*Marcelo Seisdedos
 *201313984
 * MIA Practica1
 * */

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


tabla *partitionTable;
void main(int argc, char *argv[])
{
    char texto1[100] ="";
    char texto2[100] ="";
    char texto3[100]="";
    partitionTable = (tabla *)malloc(sizeof(tabla));
    partitionTable->primero = (registro *)malloc(sizeof(registro));
    partitionTable->ultimo = (registro *)malloc(sizeof(registro));
    partitionTable->primero = NULL;
    partitionTable->ultimo = NULL;
    printf("Universidad de San Carlos de Guatemala\n");
    printf("Manejo e Implementacion de Archivos\n");
    printf("Marcelo Seisdedos. 201313984\n");
    printf("\n");
    printf("INGRESE UN COMANDO:\n");

    while(TRUE == 1){
    fgets(texto2,100,stdin);
    texto2[strlen(texto2)-1] = '\0';


    while(strstr(texto2,"\\")){
        char delimitador[2] = "\t\\";
        char *token;
        token = strtok(texto2,delimitador);
        strcat(texto3,token);
        fgets(texto2,100,stdin);
        texto2[strlen(texto2)-1] = '\0';
    }

    //para saltarme los comentarios.
    while(strstr(texto2,"#")){
        fgets(texto2,100,stdin);
        texto2[strlen(texto2)-1] = '\0';
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

int execScript(char *token){

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
              printf("\nError, exceso de comando\n");
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
        printf("\nScript no existe\n");
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
            execScript(tokenn);
        strcpy(cadenas,"");
        strcpy(cadenas3,"");
    }


}

int metodoMkdisk(char *token)
{
    char size[100] = "-size";
    char unit[100] = "-unit";
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
          token = strtok(NULL, " :");
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
              token = strtok(NULL, " :");
              TamanioDeDisco = atoi(token);

              if(TamanioDeDisco > 0){
              }
              else{
                  printf("\nERROR. Tamanio de disco invalido.\n");
                  return -1;
              }
              break;
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
          case 3:

              token = strtok(NULL, " :");

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
    printf("\nSe creo el disco.\n");
    fclose(archivo);

    mbr *mbrLeido = (mbr *)malloc(sizeof(mbr));
    FILE *barchivo1 = fopen(direccionPath3,"rb");
    fread(mbrLeido,sizeof(mbr),1,barchivo1);
    int t = sizeof(mbrLeido);
    fclose(barchivo1);


    return 1;
}

int metodoRmdisk(char *token)
{
    /*
     *     char controlSwitch[5];
                printf("\nsi: Eliminar disco \nno: No elimnar el disco\n");
                gets(controlSwitch);
                if(strcmp(controlSwitch,"si") == 0)
                {
                }
     * */

    char path[10] = "-path";
    char cadenaTomadaPath[200];
    char comillas[3] = "\"";
    char controlSwitch[5];
    int contad = 0;
    token = strtok(NULL, " :\"");
    while(token != NULL)
    {
        char *tempPath;
        tempPath = strstr(token,path);
        if(tempPath){
            /*
             *  token = strtok(NULL, "\"");
                strcat(cadenaTomadaPath," ");
                strcat(cadenaTomadaPath,token);
                printf("\nPath del disco a eliminar: %s",cadenaTomadaPa
             * */
            token = strtok(NULL, " :");
            if(strstr(token,comillas)){
                strcpy(cadenaTomadaPath,token+1);
                token = strtok(NULL, "\"");
                strcat(cadenaTomadaPath," ");
                strcat(cadenaTomadaPath,token);
                printf("\nPath del disco a eliminar: %s",cadenaTomadaPath);
            }else{
                strcpy(cadenaTomadaPath,token);
            }
        }
        token = strtok(NULL, " :\"");
        if(token==NULL){
             break;
        }

        else{
            contad = 1;
            printf("ERROR. Comando no valido.\n");
            break;
        }
    }

    if(contad == 0){
            printf( "%s\n", cadenaTomadaPath );

                printf("\nsi: Eliminar disco \nno: No elimnar el disco\n");
                gets(controlSwitch);
                if(strcmp(controlSwitch,"si") == 0)
                {
                    FILE *archivo = fopen(cadenaTomadaPath,"r");

                    if(archivo!= NULL){
                        remove(cadenaTomadaPath);
                        fclose(archivo);
                        printf("\nDisco eliminado exitosamente.\n");
                        return 1;
                    }else{
                        printf("\nERROR. Disco no existe.\n");
                    }

                }else{
                    printf("\nDisco no eliminado\n");
                }

       }else{
             printf("\nERROR. Comando no valido\n");
       }

}

int metodoFdisk(char *token)
{
    char size[100] = "-size";
    char unit[100] = "-unit";
    char path[200] = "-path";
    char type[10] = "-type";
    char fit[10] = "-fit";
    char vardelete[200] = "-delete";
    char name[10] = "-name";
    char add[10] = "-add";
    char comillas[3] = "\"";
    int tamanioParticion = 0;
    char letraUnit[100] = "k";
    char direccion[200]="";
    char letraType[100] = "p";
    char letraFit[100] = "wf";
    char letraDelete[100]="";
    char letraName[100]="";
    int tamanioAdd = 0;
    int controlSwitch;
    int accion = 0;
    while(token != NULL)
    {
        token = strtok(NULL, " :");
        if(token==NULL)
            break;

        if(strstr(token,size))
            controlSwitch = 1;
        else if(strstr(token,unit))
            controlSwitch = 2;
        else if(strstr(token,path))
            controlSwitch = 3;
        else if(strstr(token,type))
            controlSwitch = 4;
        else if(strstr(token,fit))
            controlSwitch = 5;
        else if(strstr(token,vardelete))
            controlSwitch = 6;
        else if(strstr(token,name))
            controlSwitch = 7;
        else if(strstr(token,add))
            controlSwitch = 8;
        else
            controlSwitch = 0;

        switch (controlSwitch) {
        case 1:
            token = strtok(NULL, " :");
            tamanioParticion = atoi(token);
            if(tamanioParticion <= 0)
            {
                printf("\nERROR. Tamanio de la particion invalido\n");
                return -1;
            }
            break;
        case 2:
            token = strtok(NULL, " :");
            strcpy(letraUnit,token);
            if(strcmp(letraUnit,"b") == 0 || (strcmp(letraUnit,"m") == 0) || (strcmp(letraUnit,"k") == 0)){

            }else{
                printf("\nERROR. Unidad no valida.\n");
                return -1;
            }
            break;
        case 3:
            token = strtok(NULL, " :");

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
            token = strtok(NULL, " :");
            strcpy(letraType,token);
            if(strcmp(letraType,"p") == 0 || (strcmp(letraType,"e") == 0) || (strcmp(letraType,"l") == 0))
                printf("");
            else{
                printf("\nERROR, Unidad invalida. Debe ser p, e, l.");
                return -1;
            }
            break;
        case 5:
            token = strtok(NULL, " :");
            strcpy(letraFit,token);
            if(strcmp(letraFit,"bf") == 0 || (strcmp(letraFit,"ff") == 0) || (strcmp(letraFit,"wf") == 0))
                printf("");
            else{
                printf("\nERROR. Unidad invalida. Debe ser bb, ff, wf");
                return -1;
            }
            break;
        case 6:
            token = strtok(NULL, " :");
            strcpy(letraDelete,token);
            if(strcmp(letraDelete,"fast") == 0 || (strcmp(letraDelete,"full") == 0)){
                printf("");
                accion = 1;
            }
            else{
                printf("\nERROR. Parametro invalido. Debe ser fast o full.");
                return -1;
            }
            break;
        case 7:
            token = strtok(NULL, " :");
            strcpy(letraName,token);
            break;
        case 8:
            token = strtok(NULL, " :");
            tamanioAdd = atoi(token);
            accion = 2;
            break;
        default:
            printf("Error, parametro no valido\n");
            return -1;
            break;
        }
    }

    FILE *archBinario = fopen(direccion,"r+b");
    mbr *estructmbr = (mbr *)malloc(sizeof(mbr));
    fseek(archBinario,0,SEEK_SET);
    fread(estructmbr,sizeof(mbr),1,archBinario);
    fclose(archBinario);

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

    int espacioLibreEnDisco = estructmbr->mbr_tamanio - estructmbr->mbr_partition1->part_size - estructmbr->mbr_partition2->part_size - estructmbr->mbr_partition3->part_size - estructmbr->mbr_partition4->part_size ;


    int ContadorExtendidas = 1;
    int primarias = 0;
    int acceso = 0;
    if(accion == 0){
        if(strcmp(letraType,"e") == 0){
            if(strcmp(estructmbr->mbr_partition1->part_type,"e") == 0 || strcmp(estructmbr->mbr_partition2->part_type,"e") == 0 || strcmp(estructmbr->mbr_partition3->part_type,"e") == 0 || strcmp(estructmbr->mbr_partition4->part_type,"e") == 0){
                ContadorExtendidas = 0;
                printf("\nERROR. Ya existe una particion extendida por lo que no puede crearse otra.\n");
                return -1;
            }else{
                if(espacioLibreEnDisco > 0 && espacioLibreEnDisco >= tama){
                    if(strcmp(estructmbr->mbr_partition1->part_type,"x") == 0){
                        if(strcmp(estructmbr->mbr_partition2->part_type,"x") == 0){
                            if(strcmp(estructmbr->mbr_partition3->part_type,"x") == 0){
                                if(strcmp(estructmbr->mbr_partition4->part_type,"x") == 0){
                                    mbr *mbrRd = (mbr *)malloc(sizeof(mbr));
                                    mbr *mbrRd2 = (mbr *)malloc(sizeof(mbr));
                                    mbr *mbrRd3 = (mbr *)malloc(sizeof(mbr));
                                    mbrRd2->mbr_partition1 = (partition *)malloc(sizeof(partition));
                                    FILE *barchivo1 = fopen(direccion,"r+b");
                                    fseek(barchivo1,0,SEEK_SET);
                                    fread(mbrRd,sizeof(mbr),1,barchivo1);
                                    mbrRd->mbr_partition1 = (partition *)malloc(sizeof(partition));
                                    mbrRd->mbr_partition1->part_size = tama;
                                    mbrRd->mbr_partition1->part_start = sizeof(mbrRd);
                                    strcpy(mbrRd->mbr_partition1->part_fit,letraFit);
                                    strcpy(mbrRd->mbr_partition1->part_name,letraName);
                                    strcpy(mbrRd->mbr_partition1->part_type,letraType);
                                    //HASTA AQUI SIRVE BIEN.
                                    /*
                                     * mbrLeido->mbr_partition1->part_status = 1;
                                    fseek(barchivo1,0,SEEK_SET);
                                    fwrite(mbrLeido,sizeof(mbr)+ sizeof( partition),1,barchivo1);
                                    fseek(barchivo1,0,SEEK_SET);
                                    fread(mbrLeido1,sizeof(mbr),1,barchivo1);
                                    ebr *ebrInicial = (ebr *)malloc(sizeof(eb
                                     * */
                                    mbrRd->mbr_partition1->part_status = 1;
                                    fseek(barchivo1,0,SEEK_SET);
                                    fwrite(mbrRd,sizeof(mbr)+ sizeof( partition),1,barchivo1);
                                    fseek(barchivo1,0,SEEK_SET);
                                    fread(mbrRd2,sizeof(mbr),1,barchivo1);
                                    ebr *ebrInicial = (ebr *)malloc(sizeof(ebr));
                                    ebr *ebrInicial2 = (ebr *)malloc(sizeof(ebr));
                                    strcpy(ebrInicial->part_fit,letraFit);
                                    strcpy(ebrInicial->part_name,letraName);
                                    ebrInicial->part_status = 1;
                                    ebrInicial->part_size = 0;
                                    ebrInicial->part_start = mbrRd->mbr_partition1->part_start;
                                    ebrInicial->part_next = -1;
                                    fseek(barchivo1,sizeof(mbr)+ sizeof( partition),SEEK_CUR);
                                    fwrite(ebrInicial,sizeof(ebr),1,barchivo1);
                                    fseek(barchivo1,0,SEEK_SET);
                                    fread(mbrRd3,sizeof(mbr),1,barchivo1);
                                    fseek(barchivo1,sizeof(mbr)+ sizeof( partition),SEEK_CUR);
                                    fread(ebrInicial2,sizeof(ebr),1,barchivo1);
                                    fclose(barchivo1);
                                    printf("\nSe creo particion extendida exitosamente.\n");
                                    acceso = 1;
                                }else{
                                    if(tama <= estructmbr->mbr_partition4->part_start){
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
                                        printf("\nSe creo particion extendida exitosamente.\n");
                                        acceso = 1;
                                    }
                                }
                            }else{
                                if(tama <= estructmbr->mbr_partition3->part_start){
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
                                    printf("\nSe creo particion extendida exitosamente.\n");
                                    acceso = 1;
                                }
                            }
                        }else{
                            if(tama <= estructmbr->mbr_partition2->part_start){
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
                                printf("\nSe creo particion extendida exitosamente.\n");
                                acceso = 1;
                            }
                        }
                    }

                    if(strcmp(estructmbr->mbr_partition2->part_type,"x") == 0 && acceso == 0){
                        if(strcmp(estructmbr->mbr_partition3->part_type,"x") == 0){
                            if(strcmp(estructmbr->mbr_partition4->part_type,"x") == 0){
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
                                printf("\nSe creo particion extendida exitosamente.\n");
                                acceso = 1;
                            }else{
                                if(tama <= (estructmbr->mbr_partition4->part_start - (estructmbr->mbr_partition1->part_size + sizeof(mbr)))){
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
                                    printf("\nSe creo particion extendida exitosamente.\n");
                                    acceso = 1;
                                }
                            }
                        }else{
                            if(tama <= (estructmbr->mbr_partition3->part_start - (estructmbr->mbr_partition1->part_size + sizeof(mbr)))){
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
                                printf("\nSe creo particion extendida exitosamente.\n");
                                acceso = 1;
                            }
                        }
                    }
                    if(strcmp(estructmbr->mbr_partition3->part_type,"x") == 0 && acceso == 0){
                        if(strcmp(estructmbr->mbr_partition4->part_type,"x") == 0){
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
                            printf("\nSe creo particion extendida exitosamente.\n");
                            acceso = 1;
                        }else{
                            if(tama <= (estructmbr->mbr_partition4->part_start - (estructmbr->mbr_partition2->part_start + estructmbr->mbr_partition2->part_size))){
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
                                printf("\nSe creo particion extendida exitosamente.\n");
                                acceso = 1;
                            }
                        }
                    }
                    if(strcmp(estructmbr->mbr_partition4->part_type,"x") == 0 && acceso == 0){
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
                        printf("\nSe creo particion extendida exitosamente.\n");
                        acceso = 1;
                    }
                }else{
                    printf("\nERROR. No hay espacio en el disco.\n");
                }
            }
        }else if(strcmp(letraType,"p") == 0){
            if(strcmp(estructmbr->mbr_partition1->part_type,"p") == 0 )
                primarias++;
            if(strcmp(estructmbr->mbr_partition2->part_type,"p") == 0 )
                primarias++;
            if(strcmp(estructmbr->mbr_partition3->part_type,"p") == 0 )
                primarias++;
            if(strcmp(estructmbr->mbr_partition4->part_type,"p") == 0 )
                primarias++;

            if(primarias < 3){
                if(espacioLibreEnDisco > 0 && espacioLibreEnDisco >= tama){
                    if(strcmp(estructmbr->mbr_partition1->part_type,"x") == 0){
                        if(strcmp(estructmbr->mbr_partition2->part_type,"x") == 0){
                            if(strcmp(estructmbr->mbr_partition3->part_type,"x") == 0){
                                if(strcmp(estructmbr->mbr_partition4->part_type,"x") == 0){
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
                                    printf("\nSe creo particion primaria exitosamente. \n");
                                    acceso = 1;
                                }else{
                                    if(tama <= estructmbr->mbr_partition4->part_start){
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
                                        printf("\nSe creo particion primaria exitosamente. \n");
                                        acceso = 1;
                                    }
                                }
                            }else{
                                if(tama <= estructmbr->mbr_partition3->part_start){
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
                                    printf("\nSe creo particion primaria exitosamente. \n");
                                    acceso = 1;
                                }
                            }
                        }else{
                            if(tama <= estructmbr->mbr_partition2->part_start){
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
                                printf("\nSe creo particion primaria exitosamente. \n");
                                acceso = 1;
                            }
                        }
                    }
                    if(strcmp(estructmbr->mbr_partition2->part_type,"x") == 0 && acceso == 0){
                        if(strcmp(estructmbr->mbr_partition3->part_type,"x") == 0){
                            if(strcmp(estructmbr->mbr_partition4->part_type,"x") == 0){
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
                                printf("\nSe creo particion primaria exitosamente. \n");
                                acceso = 1;
                            }else{
                                if(tama <= (estructmbr->mbr_partition4->part_start - (estructmbr->mbr_partition1->part_size + estructmbr->mbr_partition1->part_start))){
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
                                    printf("\nSe creo particion primaria exitosamente. \n");
                                    acceso = 1;
                                }
                            }
                        }else{
                            if(tama <= (estructmbr->mbr_partition3->part_start - (estructmbr->mbr_partition1->part_size +sizeof(mbr)))){
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
                                printf("\nSe creo particion primaria exitosamente. \n");
                                acceso = 1;
                            }
                        }
                    }
                    if(strcmp(estructmbr->mbr_partition3->part_type,"x") == 0 && acceso == 0){
                        if(strcmp(estructmbr->mbr_partition4->part_type,"x") == 0){
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
                            printf("\nSe creo particion primaria exitosamente. \n");
                            acceso = 1;
                        }else{
                            if(tama <= (estructmbr->mbr_partition4->part_start - (estructmbr->mbr_partition2->part_size + estructmbr->mbr_partition2->part_start))){
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
                                printf("\nSe creo particion primaria exitosamente. \n");
                                acceso = 1;
                            }
                        }
                    }
                    if(strcmp(estructmbr->mbr_partition4->part_type,"x") == 0 && acceso == 0){
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
                        printf("\nSe creo particion primaria exitosamente. \n");
                        acceso = 1;
                    }
                }else{
                    printf("\nERROR. No hay espacio disponible en el disco.\n");
                }
            }else{
                printf("\nERROR. Limite de particiones primarias excedido.\n");
            }

        }else if(strcmp(letraType,"l") == 0){

            if(strcmp(estructmbr->mbr_partition1->part_type,"e") == 0 || strcmp(estructmbr->mbr_partition2->part_type,"e") == 0 || strcmp(estructmbr->mbr_partition3->part_type,"e") == 0|| strcmp(estructmbr->mbr_partition4->part_type,"e") == 0){

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
                        printf("\nError, espacio insuficiente en la particion extendida para crear particion.\n");
                        return -1;
                    }
                }else{
                    printf("\nError, ya no hay espacio en la particion extendida para crear mas logicas\n");
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
                /*
                 *
                 * if(strcmp(mbrLeidoA->mbr_partition1->part_type,"e") == 0){
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

                 *
                 * */
                int varWhile = 0;
                int pos = 0;
                fseek(barchivo1,sizeof(mbr)+ sizeof( partition),SEEK_CUR);
                fread(ebrInicial2,sizeof(ebr),1,barchivo1);
                mbr *mbrLeido3 = (mbr *)malloc(sizeof(mbr));


                    int partSize = 0;
                    int pruebaSize = 0;


                while(varWhile != 1){

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
                        printf("\nSe creo particion logica exitosamente.\n");
                        varWhile = 1;
                        pos = 0;
                        break;
                    }else{
                        fseek(barchivo1,0,SEEK_SET);
                        fread(mbrLeido,sizeof(mbr),1,barchivo1);
                        fseek(barchivo1,sizeof(mbr)+ sizeof( partition) + sizeof(ebr),SEEK_CUR);
                        fread(ebrInicial2,sizeof(ebr),1,barchivo1);

                        partSize = ebrInicial2->part_start;
                        pruebaSize = ebrInicial2->part_size;
                        int tt = 0;
                        if(partSize != 0 && pruebaSize !=0){
                            tt = 1;
                        }

                        fseek(barchivo1,0,SEEK_SET);
                        fread(mbrLeido,sizeof(mbr),1,barchivo1);
                        fseek(barchivo1,sizeof(mbr)+ sizeof( partition),SEEK_CUR);
                        fread(ebrInicial22,sizeof(ebr),1,barchivo1);
                        if(tt == 0){
                            partSize = ebrInicial22->part_start;
                            pruebaSize = ebrInicial22->part_size;
                        }

                        for(int i = 1; i <= 1000; i++){

                            if(ebrInicial2->part_next == -1 && ebrInicial2->part_size == 0){

                                fseek(barchivo1,0,SEEK_SET);
                                fread(mbrLeido,sizeof(mbr),1,barchivo1);
                                fseek(barchivo1,sizeof(mbr)+ sizeof( partition) + (i - 1)*sizeof(ebr),SEEK_CUR);
                                fread(ebrInicial3,sizeof(ebr),1,barchivo1);
                                ebrInicial3->part_next = partSize + pruebaSize;
                                fseek(barchivo1,0,SEEK_SET);
                                fread(mbrLeido3,sizeof(mbr),1,barchivo1);
                                fseek(barchivo1,sizeof(mbr)+ sizeof( partition) + (i-1)*sizeof(ebr),SEEK_CUR);
                                fwrite(ebrInicial3,sizeof(ebr),1,barchivo1);

                                strcpy(ebrInicial2->part_fit,letraFit);
                                strcpy(ebrInicial2->part_name,letraName);
                                ebrInicial2->part_status = 1;
                                ebrInicial2->part_next = -1;
                                ebrInicial2->part_size = tama;
                                ebrInicial2->part_start = partSize + pruebaSize;
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
                                printf("\nSe creo particion logica exitosamente.\n");
                                varWhile = 1;
                                pos = i;
                                break;
                            }else{
                                fseek(barchivo1,0,SEEK_SET);
                                fread(mbrLeido,sizeof(mbr),1,barchivo1);
                                fseek(barchivo1,sizeof(mbr)+ sizeof( partition) + (i+1)*sizeof(ebr),SEEK_CUR);
                                fread(ebrInicial2,sizeof(ebr),1,barchivo1);
                                if(ebrInicial2->part_start != 0 && ebrInicial2->part_size != 0){
                                    partSize = ebrInicial2->part_start;
                                    pruebaSize = ebrInicial2->part_size;
                                }
                            }}}}
                FILE *barchivo11 = fopen(direccion,"r+b");
                mbr *mbrLeidoE = (mbr *)malloc(sizeof(mbr));
                fseek(barchivo11,0,SEEK_SET);
                fread(mbrLeidoE,sizeof(mbr),1,barchivo11);
                fseek(barchivo11,sizeof(mbr)+ sizeof( partition) + pos*sizeof(ebr),SEEK_CUR);
                fread(ebrInicial22,sizeof(ebr),1,barchivo11);
                fclose(barchivo11);
            }
            }else{
                printf("\nERROR en particion logica, no existe una particion extendida en el disco.\n");
            }

    }
    if(accion == 1){
             char controlSwitch[5];
                    printf("\nsi: Eliminar particion \nno: No elimnar el particion\n");
                    gets(controlSwitch);
                    if(strcmp(controlSwitch,"si") == 0)
                    {



        FILE *binario = fopen(direccion,"r+b");
        mbr *compro = (mbr *)malloc(sizeof(mbr));
        fseek(binario,0,SEEK_SET);
        fread(compro,sizeof(mbr),1,binario);
        int ai;

        if(binario!=NULL){
            fclose(binario);
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

                                printf("\nSe elimino particion logica exitosamente\n");
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
            //Aqui es para eliminar.
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
                    printf("\nSe elimino particion exitosamente.\n");
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
                    printf("\nSe elimino particion exitosamente.\n");
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
                    printf("\nSe elimino particion exitosamente.\n");
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
                    printf("\nSe elimino particion exitosamente.\n");
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
                    printf("\nSe elimino particion exitosamente\n");
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
                    printf("\nSe elimino particion exitosamente\n");
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
/*
 *
 *              mbr *mbrLeidoA = (mbr *)malloc(sizeof(mbr));
                FILE *barchivo1A = fopen(direccion,"r+b");
                ebr *ebrInicial2A = (ebr *)malloc(sizeof(ebr));
                fseek(barchivo1A,0,SEEK_SET);
                fread(mbrLeidoA,sizeof(mbr),1,barchivo1A);
                fseek(barchivo1A,sizeof(mbr)+ sizeof( partition),SEEK_CUR);
                fread(ebrInicial2A,sizeof(ebr),1,barchivo1A);
                int tam = 1;
 * */

                    fseek(barchivo1,0,SEEK_SET);
                    fwrite(mbrLeido,sizeof(mbr)+ sizeof( partition),1,barchivo1);
                    fseek(barchivo1,0,SEEK_SET);
                    fread(mbrLeido1,sizeof(mbr),1,barchivo1);
                    printf("\nSe elimino particion exitosamente.\n");
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
                    printf("\nSe elimino particion exitosamente.\n");
                    fclose(barchivo1);
                }
            }

        }else{
            printf("\nERROR. No existe el disco\n");
        }
    } else {
                        printf("\nNo se elimino la particion..\n");

                    }
    }

    if(accion == 2){
        if(tamaAdd < 0){
            /*SE QUITA*/
            if(strcmp(estructmbr->mbr_partition1->part_name,letraName) == 0){
                mbr *mbrLeido = (mbr *)malloc(sizeof(mbr));
                mbr *mbrLeido1 = (mbr *)malloc(sizeof(mbr));
                mbrLeido1->mbr_partition1 = (partition *)malloc(sizeof(partition));
                FILE *barchivo1 = fopen(direccion,"r+b");
                fseek(barchivo1,0,SEEK_SET);
                fread(mbrLeido,sizeof(mbr),1,barchivo1);
                int ao = mbrLeido->mbr_partition1->part_size + tamaAdd;
                if(ao < 0){
                    printf("\nERROR. Tamanio a quitar es mas grande que tamanio de particion.\n");
                }else{
                    mbrLeido->mbr_partition1->part_size = ao;
                }
                fseek(barchivo1,0,SEEK_SET);
                fwrite(mbrLeido,sizeof(mbr)+ sizeof( partition),1,barchivo1);
                fseek(barchivo1,0,SEEK_SET);
                fread(mbrLeido1,sizeof(mbr),1,barchivo1);
                fclose(barchivo1);
            }else if(strcmp(estructmbr->mbr_partition2->part_name,letraName) == 0){
                mbr *mbrLeido = (mbr *)malloc(sizeof(mbr));
                mbr *mbrLeido1 = (mbr *)malloc(sizeof(mbr));
                mbrLeido1->mbr_partition2 = (partition *)malloc(sizeof(partition));
                FILE *barchivo1 = fopen(direccion,"r+b");
                fseek(barchivo1,0,SEEK_SET);
                fread(mbrLeido,sizeof(mbr),1,barchivo1);
                int ao = mbrLeido->mbr_partition2->part_size + tamaAdd;
                if(ao < 0){
                    printf("\nERROR. Tamanio a quitar es mas grande que tamanio de particion.\n");
                }else{
                    mbrLeido->mbr_partition2->part_size = ao;
                }
                fseek(barchivo1,0,SEEK_SET);
                fwrite(mbrLeido,sizeof(mbr)+ sizeof( partition),1,barchivo1);
                fseek(barchivo1,0,SEEK_SET);
                fread(mbrLeido1,sizeof(mbr),1,barchivo1);
                fclose(barchivo1);
            }else if(strcmp(estructmbr->mbr_partition3->part_name,letraName) == 0){
                mbr *mbrLeido = (mbr *)malloc(sizeof(mbr));
                mbr *mbrLeido1 = (mbr *)malloc(sizeof(mbr));
                mbrLeido1->mbr_partition3 = (partition *)malloc(sizeof(partition));
                FILE *barchivo1 = fopen(direccion,"r+b");
                fseek(barchivo1,0,SEEK_SET);
                fread(mbrLeido,sizeof(mbr),1,barchivo1);
                int ao = mbrLeido->mbr_partition3->part_size + tamaAdd;
                if(ao < 0){
                    printf("\nERROR. Tamanio a quitar es mas grande que tamanio de particion.\n");
                }else{
                    mbrLeido->mbr_partition3->part_size = ao;
                }
                fseek(barchivo1,0,SEEK_SET);
                fwrite(mbrLeido,sizeof(mbr)+ sizeof( partition),1,barchivo1);
                fseek(barchivo1,0,SEEK_SET);
                fread(mbrLeido1,sizeof(mbr),1,barchivo1);
                fclose(barchivo1);
            }else if(strcmp(estructmbr->mbr_partition4->part_name,letraName) == 0){
                mbr *mbrLeido = (mbr *)malloc(sizeof(mbr));
                mbr *mbrLeido1 = (mbr *)malloc(sizeof(mbr));
                mbrLeido1->mbr_partition4 = (partition *)malloc(sizeof(partition));
                FILE *barchivo1 = fopen(direccion,"r+b");
                fseek(barchivo1,0,SEEK_SET);
                fread(mbrLeido,sizeof(mbr),1,barchivo1);
                int ao = mbrLeido->mbr_partition4->part_size + tamaAdd;
                if(ao < 0){
                    printf("\nERROR. Tamanio a quitar es mas grande que tamanio de particion.\n");
                }else{
                    mbrLeido->mbr_partition4->part_size = ao;
                }
                fseek(barchivo1,0,SEEK_SET);
                fwrite(mbrLeido,sizeof(mbr)+ sizeof( partition),1,barchivo1);
                fseek(barchivo1,0,SEEK_SET);
                fread(mbrLeido1,sizeof(mbr),1,barchivo1);
                fclose(barchivo1);
            }else{
                printf("\nERROR. La particion no existe.\n");
                return -1;
            }
        }else if(tamaAdd > 0){
            /*SE AGREGA TAMANIO A LA PARTICION*/
            if(strcmp(estructmbr->mbr_partition1->part_name,letraName) == 0){
                mbr *mbrLeido = (mbr *)malloc(sizeof(mbr));
                mbr *mbrLeido1 = (mbr *)malloc(sizeof(mbr));
                mbrLeido1->mbr_partition1 = (partition *)malloc(sizeof(partition));
                FILE *barchivo1 = fopen(direccion,"r+b");
                fseek(barchivo1,0,SEEK_SET);
                fread(mbrLeido,sizeof(mbr),1,barchivo1);
                int ao = mbrLeido->mbr_partition1->part_size + tamaAdd;
                if(ao > mbrLeido->mbr_tamanio){
                    printf("\nERROR. El tamanio a agregar es mas grande que la capacidad de la particion.\n");
                }else{
                        if(strcmp(estructmbr->mbr_partition2->part_type,"x") == 0){
                            if(strcmp(estructmbr->mbr_partition3->part_type,"x") == 0){
                                if(strcmp(estructmbr->mbr_partition4->part_type,"x") == 0){
                                    mbrLeido->mbr_partition1->part_size = ao;
                                }else{
                                    if(ao <= (estructmbr->mbr_partition4->part_start - estructmbr->mbr_partition1->part_size - sizeof(mbr))){
                                        mbrLeido->mbr_partition1->part_size = ao;
                                    }
                                }
                            }else{
                                if(ao <= (estructmbr->mbr_partition3->part_start - estructmbr->mbr_partition1->part_size - sizeof(mbr))){
                                    mbrLeido->mbr_partition1->part_size = ao;
                                }
                            }
                        }else{
                            if(ao <= (estructmbr->mbr_partition2->part_start - estructmbr->mbr_partition1->part_size - sizeof(mbr))){
                                mbrLeido->mbr_partition1->part_size = ao;
                            }
                        }
                }
                fseek(barchivo1,0,SEEK_SET);
                fwrite(mbrLeido,sizeof(mbr)+ sizeof( partition),1,barchivo1);
                fseek(barchivo1,0,SEEK_SET);
                fread(mbrLeido1,sizeof(mbr),1,barchivo1);
                fclose(barchivo1);
            }else if(strcmp(estructmbr->mbr_partition2->part_name,letraName) == 0){
                mbr *mbrLeido = (mbr *)malloc(sizeof(mbr));
                mbr *mbrLeido1 = (mbr *)malloc(sizeof(mbr));
                mbrLeido1->mbr_partition1 = (partition *)malloc(sizeof(partition));
                FILE *barchivo1 = fopen(direccion,"r+b");
                fseek(barchivo1,0,SEEK_SET);
                fread(mbrLeido,sizeof(mbr),1,barchivo1);
                int ao = mbrLeido->mbr_partition2->part_size + tamaAdd;

                if(ao > mbrLeido->mbr_tamanio){
                    printf("\nERROR. El tamanio a agregar es mas grande que la capacidad de la particion.\n");
                }else{

                    if(strcmp(estructmbr->mbr_partition1->part_type,"x") == 0){
                        int aa = estructmbr->mbr_partition2->part_start;
                        if(aa > 0){
                            if(aa >= tamaAdd){
                                mbrLeido->mbr_partition2->part_size + tamaAdd;
                                mbrLeido->mbr_partition2->part_start - tamaAdd;
                            }else{
                                printf("\nERROR. No hay espacio suficiente.\n");
                            }
                        }else{
                            printf("\nERROR. No hay espacio suficiente.\n");
                        }
                    }else{
                        if(strcmp(estructmbr->mbr_partition3->part_type,"x") == 0){
                            if(strcmp(estructmbr->mbr_partition4->part_type,"x") == 0){
                                mbrLeido->mbr_partition2->part_size = ao;
                            }else{
                                if(ao <= (estructmbr->mbr_partition4->part_start - estructmbr->mbr_partition2->part_size - estructmbr->mbr_partition2->part_start)){
                                    mbrLeido->mbr_partition2->part_size = ao;
                                }
                            }
                        }else{
                            if(ao <= (estructmbr->mbr_partition3->part_start - estructmbr->mbr_partition2->part_size - estructmbr->mbr_partition2->part_start )){
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
            }else if(strcmp(estructmbr->mbr_partition3->part_name,letraName) == 0){
                mbr *mbrLeido = (mbr *)malloc(sizeof(mbr));
                mbr *mbrLeido1 = (mbr *)malloc(sizeof(mbr));
                mbrLeido1->mbr_partition1 = (partition *)malloc(sizeof(partition));
                FILE *barchivo1 = fopen(direccion,"r+b");
                fseek(barchivo1,0,SEEK_SET);
                fread(mbrLeido,sizeof(mbr),1,barchivo1);
                int ao = mbrLeido->mbr_partition3->part_size + tamaAdd;
                if(ao > mbrLeido->mbr_tamanio){
                    printf("\nERROR. El tamanio a agregar es mas grande que la capacidad de la particion.\n");
                }else{

                }
                fseek(barchivo1,0,SEEK_SET);
                fwrite(mbrLeido,sizeof(mbr)+ sizeof( partition),1,barchivo1);
                fseek(barchivo1,0,SEEK_SET);
                fread(mbrLeido1,sizeof(mbr),1,barchivo1);
                fclose(barchivo1);
            }else if(strcmp(estructmbr->mbr_partition4->part_name,letraName) == 0){
                mbr *mbrLeido = (mbr *)malloc(sizeof(mbr));
                mbr *mbrLeido1 = (mbr *)malloc(sizeof(mbr));
                mbrLeido1->mbr_partition1 = (partition *)malloc(sizeof(partition));
                FILE *barchivo1 = fopen(direccion,"r+b");
                fseek(barchivo1,0,SEEK_SET);
                fread(mbrLeido,sizeof(mbr),1,barchivo1);
                int ao = mbrLeido->mbr_partition3->part_size + tamaAdd;
                if(ao > mbrLeido->mbr_tamanio){
                    printf("\nERROR. El tamanio a agregar es mas grande que la capacidad de la particion.\n");
                }else{
                    int aa = estructmbr->mbr_partition3->part_size + estructmbr->mbr_partition2->part_size + estructmbr->mbr_partition1->part_size;
                    int ts = estructmbr->mbr_tamanio - sizeof(mbr) - aa;
                    if(ts > tamaAdd){
                        if((estructmbr->mbr_partition3->part_start + estructmbr->mbr_partition3->part_size) == estructmbr->mbr_partition4->part_start){
                            printf("\ERROR. No hay espacio suficiente");
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
                printf("\ERROR. La particion no existe.\n");
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

    while(token!=NULL)
    {
        token = strtok(NULL, " :");
        if(token==NULL)
            break;

        char *estaPath;
        char *estaName;

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
            token = strtok(NULL, " :");
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
            token = strtok(NULL, " :");
            strcpy(guardoNombre,token);
            break;
        default:
            printf("\nError, comando no valido.\n");
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
                printf("\nNo se monto particion\n");
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
                printf("\nError, no existe esa particion en el disco.\n");
            }

        }

    }else{
        printf("\nError, disco no existe\n");
        printf("\nNo se monto la particion\n");
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
        token = strtok(NULL, " :");
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
            printf("\nError, comando no valido.\n");
            return -1;
            break;
        }
    }

    registro *aux = (registro *)malloc(sizeof(registro));
    registro *aux2 = (registro *)malloc(sizeof(registro));
    aux = tablaDeParticiones->primero;

    if(aux == NULL){
        printf("\nError, no existe ID en tabla de particiones\n");
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
            printf("\nError, no existe en tabla de particiones\n");
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
            printf("\nError, no existe ID en tabla de particiones\n");
        }


        aux = aux->siguiente;
    }

}


int metodoUnmount(char *token)
{
    printf("Entro a unmount.\n");

}

int metodoRep(char *token)
{
    printf("Entro a rep.\n");

}




