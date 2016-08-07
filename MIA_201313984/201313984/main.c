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
typedef struct
{
    int part_status;
    char part_type[100];
    char part_fit[100];
    int part_start;
    int part_size;
    char part_name[25];
} partition;

//Struct del MBR
typedef struct
{
    int mbr_tamanio;
    char mbr_fecha_creacion[128];
    int mbr_disk_signature;
    partition *mbr_partition1;
    partition *mbr_partition2;
    partition *mbr_partition3;
    partition *mbr_partition4;
} mbr;

//Struct del EBR
typedef struct
{
    int part_status;
    char part_fit[100];
    int part_start;
    int part_size;
    int part_next;
    char part_name[25];
} ebr;

//Struct de lso Registros
typedef struct
{
    char path[100];
    char id[10];
    char name[100];
    struct registro *siguiente;
    struct registro *anterior;
} registro;

//Struct de mi tabla de particiones
typedef struct
{
    registro *primero;
    registro *ultimo;
} tabla;

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

    while(TRUE == 1)
    {
        fgets(texto2,100,stdin);
        texto2[strlen(texto2)-1] = '\0';

        while(strstr(texto2,"\\"))
        {
            char delimitador[2] = "\t\\";
            char *token;
            token = strtok(texto2,delimitador);
            strcat(texto3,token);
            fgets(texto2,100,stdin);
            texto2[strlen(texto2)-1] = '\0';

        }

        //para saltarme los comentarios.
        while(strstr(texto2,"#"))
        {
            fgets(texto2,100,stdin);
            texto2[strlen(texto2)-1] = '\0';
        }
        int temporal1 = 0;
        while(strstr(texto2,"\t") && temporal1==0)
        {
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

        printf("Token: ");
        printf("%s\n",token);


        estaSize = strstr(token,size);
        estaUnit = strstr(token,unit);
        estaPath = strstr(token,path);
        estaName = strstr(token,name);



        if(estaSize)
        {
            control = 1;
        }
        else if(estaUnit)
        {
            control = 2;
        }
        else if(estaPath)
        {
            control = 3;
        }
        else if (estaName)
        {
            control = 4;
        }
        else
        {
            control = 0;
        }

        switch (control)
        {
        //Validación de Tamaño mayor a 0
        case 1:
            token = strtok(NULL, " ::");
            TamanioDeDisco = atoi(token);

            if(TamanioDeDisco > 0)
            {
            }
            else
            {
                printf("\nERROR. Tamanio de disco invalido.\n");
                return -1;
            }
            break;
        //Validación de Unidad de tamaño
        case 2:
            token = strtok(NULL, " ::");
            strcpy(unitLetra,token);
            if((strcmp(unitLetra,"m") == 0) || (strcmp(unitLetra,"k") == 0))
            {

            }
            else
            {
                printf("\nERROR. Unidad invalida.\n");
                return -1;
            }

            break;

        //Para el path
        case 3:

            token = strtok(NULL, " ::");

            if(strstr(token,comillas))
            {
                //printf("\nEntro al if.\n");
                strcpy(direccionPath,token+1);
                token = strtok(NULL, "\"");
                strcat(direccionPath," ");
                strcat(direccionPath,token);
                strcpy(direccionPath2,direccionPath);
                strcpy(direccionPath3,direccionPath);
                /* printf("\ndireccionPath.\n");
                 printf("%s\n",direccionPath);
                 printf("\ndireccionPath2.\n");
                 printf("%s\n",direccionPath2);
                 printf("\ndireccionPath3.\n");
                 printf("%s\n",direccionPath3);
                */
            }
            else
            {
                //printf("\nEntro al else.\n");
                strcpy(direccionPath,token);
                strcpy(direccionPath2,token);
                strcpy(direccionPath3,token);
                /*printf("\ndireccionPath.\n");
                printf("%s\n",direccionPath);
                printf("\ndireccionPath2.\n");
                printf("%s\n",direccionPath2);
                printf("\ndireccionPath3.\n");
                printf("%s\n",direccionPath3);
                */
            }
            break;

        //Para el nombre
        case 4:
            /* token = strtok(NULL, " :");
             strcpy(nombredeldisco,token);
             char *search = ".";
             token = strtok(nombredeldisco, search);
             strcpy(pruebanombre,token);
             printf("\Nombre del disco: \n");
             printf("%s\n",pruebanombre);
             token = strtok(NULL, search);
             strcpy(pruebaextension,token);
             printf("\Nombre del extensión: \n");
             printf("%s\n",pruebaextension);
            */
            // este codigo está bueno
            token = strtok(NULL, " ::");
            strcpy(nombredeldisco,token);
            printf("\Nombre del disco: \n");
            printf("%s\n",nombredeldisco);

            //PRUEBA USANDO OTRO TOK
            char* mitoken1 = token;
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
                    printf("%s\n", mitoken1);
                }
                free(tofree);
            }
            //Verifico si la extensión está correcta

            printf("Extension: \n");
            printf("%s\n", extensionNombre);

            if(strcmp(extensionNombre,"dsk") == 0)
            {
                printf("\nEntro al if. Es igual a dsk");
            }
            else
            {
                printf("\nEntro al else. No es igual a dsk.");
                //not ok. tiene que salirse
                printf("\nERROR. Extension del disco incorrecta. Debe ser .dsk\n");
                return -1;
                break;
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

    //numPalabras++;

    char pathReal[200] = "/";
    char *temm;
    temm = strtok(direccionPath2,"/");
    strcat(pathReal,temm);
    strcat(pathReal,"/");
    // printf("Path Real\n");
    // printf("%s\n",pathReal);


    //Pära crear la carpeta.
    while(numPalabras > 2)
    {
        temm = strtok(NULL,"/");
        strcat(pathReal,temm);
        strcat(pathReal,"/");
        mkdir(pathReal ,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        numPalabras--;
        printf("Path Real\n");
        printf("%s\n",pathReal);
    }

    //Hasta aca en path real me muestra el path con las carpetas ya creadas.
    printf("Path Real ya terminado. \n");
    printf("%s\n",pathReal);

    //Aqui guardo el nombre del disco :)
    /*temm = strtok(NULL,"/");
     printf("temml\n");
    printf("%s\n",temm);
    */
    printf("direccionPath3\n");
    printf("%s\n",direccionPath3);

    mbr *mbr1 = (mbr *)malloc(sizeof(mbr));
    strcat(direccionPath3,nombredeldisco);
    printf("Path donde voy a crear el disco");
    printf("%s\n",direccionPath3);
    //AQUI CREO EL ARCHIVO. TENGO QUE MANDARLE EL PATH CORRECTO. pathReal + nombredelDisco

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
    }
    else if(strcmp(unitLetra,"m") == 0)
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


int metodoRmdisk(char *token)
{
    printf("Entro a rmdisk.\n");
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
    printf( "%s\n", cadenaTomadaPath );



    while(token != NULL)
    {
        char *tempPath;
        tempPath = strstr(token,path);
        if(tempPath)
        {
            /*
             *  token = strtok(NULL, "\"");
                strcat(cadenaTomadaPath," ");
                strcat(cadenaTomadaPath,token);
                printf("\nPath del disco a eliminar: %s",cadenaTomadaPa
             * */
            token = strtok(NULL, " :");
            if(strstr(token,comillas))
            {
                strcpy(cadenaTomadaPath,token+1);
                token = strtok(NULL, "\"");
                strcat(cadenaTomadaPath," ");
                strcat(cadenaTomadaPath,token);
                printf("\nPath del disco a eliminar: %s",cadenaTomadaPath);
            }
            else
            {
                strcpy(cadenaTomadaPath,token);
            }
        }
        token = strtok(NULL, " :\"");
        if(token==NULL)
        {
            break;
        }

        else
        {
            contad = 1;
            printf("ERROR. Comando no valido.\n");
            break;
        }
    }

    if(contad == 0)
    {
        printf("La cadena es:");
        printf( "%s", cadenaTomadaPath );
        printf(".Fin de cadena");
        printf("\nsi: Eliminar disco \nno: No elimnar el disco\n");
        fgets(controlSwitch,5,stdin);
        printf( "Control switch: ");
        printf( "%s\n", controlSwitch );
        controlSwitch[strlen(controlSwitch)-1] = '\0';
        if(strcmp(controlSwitch,"si") == 0)
        {

            char prueba[200] = "\"";
            strcat(cadenaTomadaPath,prueba);
            strcat(prueba,cadenaTomadaPath);
            printf( "Mi prueba: ");

            printf( "%s\n", prueba );

            FILE *archivo = fopen("/home/chelo/aa/hola.dsk","r");

            //FILE *archivo = fopen(prueba,"r");

            if(archivo== NULL)
            {
                remove(cadenaTomadaPath);
                fclose(archivo);
                printf("\nDisco eliminado exitosamente.\n");
                return 1;
            }
            else
            {
                printf("\nERROR. Disco no existe.\n");
            }

        }
        else
        {
            printf("\nDisco no eliminado\n");
        }

    }
    else
    {
        printf("\nERROR. Comando no valido\n");
    }

}


int metodoFdisk(char *token)
{
    printf("Entro a fdisk.\n");

}

int metodoMount(char *token)
{
    printf("Entro a mount.\n");

}

int metodoUnmount(char *token)
{
    printf("Entro a unmount.\n");

}

int metodoRep(char *token)
{
    printf("Entro a rep.\n");

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




