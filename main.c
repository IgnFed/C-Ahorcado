#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

void  _Menu(),
      _RegistrarUsuario(),
      _IniciarJuego(),
      _LeerRanking(),
      _PalabraAleatoria(),
      _EmpezarAdivinaciones(),
      _Graficos(),
      _ModificarPuntaje(),
      _ComprobarExistenciaArchivos(),
      _PantallaCompleta(),
      _ElejirOpcion(),
      _OrdenarRanking();

int   _NumeroAleatorio();

/*-----------------------------VARIABLES GLOBALES---------------------------*/

// PERMITE SABER SI EL USUARIO ANTES DE INICIAR EL JUEGO SE REGISTRO
int registrado = 0,
    puntajeJugadorActual = 0,
    longMaxPalabra = 15, // En lo que a la longitud de la palabra se refiere
    longMaxArchivo = 200, //En lo que al ranking se refiere [puntos, nombre]

    cantidadPalabrasArchivo = 88; //SI SE QUIERE AGREGAR PALABRAS, MODIFICAR ESTE NUMERO
                                  //RECOMENDABLE, BORRAR EL ARCHIVO "palabras.txt",
                                  //CAMBIAR ESTE NUMERO A LA CANTIDAD DE PALABRAS QUE DESEE AGREGAR
                                  //E IR A LA FUNCION _ComrpobarExistenciaArchivos() y agregar desde ah�, siguiendo la
                                  // indicaci�n que hay dentro de esa funcion



char nombreJugadorActual[30], // ME PERMITE MANTENER EL NOMBRE DEL JUGADOR CUANDO SE REGISTRE EN TODO EL PROGRAMA
     palabraAleatoria[15], // ABRO EL ARCHIVO DE PALABRAS Y ASIGNO UNA ALEATORIA A ESTA VARIABLE
                            // LUEGO LA USO EN LA FUNCION _IniciarJuego()

    archivoRanking[20] = "ranking.txt",
    archivoPalabras[20]= "palabras.txt";


/*--------------------------------------------------------------------------*/


/*----------------------------------------ESTRUCTURA GLOBAL---------------------------*/

struct Jugador{

  int  puntaje;
  char nombre[30];
};

/*-------------------------------------------------------------------------------*/


int main()
{

  _PantallaCompleta();
  _ComprobarExistenciaArchivos();

  _ElejirOpcion();
  getchar();
  return 0;
}

/*-----------------ELEJIR OPCION-------------------*/
_ElejirOpcion(){

  int opcion;

  do{

    system("CLS");
    _Menu(opcion);
    puntajeJugadorActual= 0;

    printf("Ingrese una Opcion: ");scanf("%d", &opcion);fflush(stdin);

      while(opcion == 2 && registrado == 0){
        printf("Necesita Crear un usuario antes de Jugar (Opcion 1): ");scanf("%d", &opcion);fflush(stdin);
      }

  }while( opcion < 1 || opcion > 4 );

  switch(opcion){
    case 1:
      _RegistrarUsuario();
      break;
    case 2:
      _IniciarJuego();
      break;
    case 3:
      _LeerRanking();
      break;
    case 4:
      exit(0);
      break;
  }
}
/*------------------------------------------------------*/


/*--------------------------MENU---------------------------*/
_Menu(){
  printf("\n================_MENU_==================");
  printf("\n|\t\t\t\t\t|\n| OPCION 1: Ingresar Usuario/Modificar\t|\n|\t\t\t\t\t");
  printf("|\n|\t\t\t\t\t|\n| OPCION 2: Jugar\t\t\t|\n|\t\t\t\t\t");
  printf("|\n|\t\t\t\t\t|\n| OPCION 3: Rankings\t\t\t|\n|\t\t\t\t\t");
  printf("|\n|\t\t\t\t\t|\n| OPCION 4: Salir\t\t\t|\n|\t\t\t\t\t|\n");
  printf("=========================================\n\n");
  if(registrado == 1)printf("JUGADOR ACTUAL: %s\n\n", nombreJugadorActual);
}
/*------------------------------------------------------------*/


/*--------------------REGISTRAR USUARIO--------------------*/
_RegistrarUsuario(){

  char cambiarJugador;

  do{

  if(registrado == 0){
    system("CLS");
    printf("\n\n\t [30 O MENOS LETRAS] Ingresa el nombre del jugador: ");gets(nombreJugadorActual);
    //NombreJugadorActual ES VARIABLE GLOBAL
    strupr(nombreJugadorActual);

  }
  else{
    system("CLS");
    printf("\n\n\t Quiere cambiar su nombre de jugador? [y/n]: ");scanf("%c", &cambiarJugador);fflush(stdin);
    if(tolower(cambiarJugador) == 'y'){
      system("CLS");
      printf("\n\n\t [30 O MENOS LETRAS] Ingresa el nuevo nombre del jugador: ");gets(nombreJugadorActual);
      strupr(nombreJugadorActual);

      //NombreJugadorActual ES VARIABLE GLOBAL
    }

  }

  }while(strlen(nombreJugadorActual) > 30 || strlen(nombreJugadorActual) == 0 || strcmpi(nombreJugadorActual, " ")==0);
  if(registrado == 0 || cambiarJugador == 'y'){
    printf("\n\t  REGISTRADO!!\n\n");
    system("PAUSE");
  }

  /*fprintf(file, "%d %s\n", pj.puntaje, pj.nombre);

  fclose(file);*/

  registrado = 1;

  _ElejirOpcion();
}
/*------------------------------------------------------------*/


/*------------------INICIAR EL JUEGO--------------------------*/
_IniciarJuego(){
  int intentos, aciertos, letraEncontrada, letraExistente;
  char letra, nuevoJuego='y', palAux[longMaxPalabra];
  //MIENTRAS NUEVO JUEGO SEA DISTINTO DE n
  while(tolower(nuevoJuego) == 'y'){

    intentos = 0;
    aciertos = 0;

    // PALABRA ALEATORIA GUARDADA EN UNA VARIABLE GLOBAL
    _PalabraAleatoria();
    //PASO LA PALABRA ALEATORIA A MINUSCULA
    strupr(palabraAleatoria);

    //A UNA PALABRA AUXILIAR, LA LLENO DE GUIONES PARA LUEGO IR REEMPLAZANDO Y MOSTRANDO LOS ACIERTOS
    for(int i = 1; i <= strlen(palabraAleatoria); i++) palAux[i-1] = '_';

    //MIENTRAS LOS INTENTOS SEAN MENORES A 10 O LOS ACIERTOS SEN DISTINTOS DE LA LONGITUD DE LA PALABRA
    while(1)
    {

      letraEncontrada = 0;
      system("CLS");
      _Graficos(intentos);


        // DIBUJO LOS GUIONES - - -
        for(int i = 0; i < strlen(palabraAleatoria); i++){
          printf("   %c ", palAux[i]);
        }

      // LANZO UN MENSAJE SI SE INGRESA UNA LETRA QUE YA EXIST�A
      if(letraExistente == 1)
      {
        printf("\n\nLa letra ya se descubrio, Ingrese una distinta.\n");
        system("PAUSE");
      }

      do{
        system("CLS");
        _Graficos(intentos);

        // DIBUJO LOS GUIONES - - -
        for(int i = 0; i < strlen(palabraAleatoria); i++){
          printf("   %c ", palAux[i]);
        }
        //  SI INGRESA UN CARACTER NO VALIDO, MUESTRA ESTE MENSAJE
        printf("\n\n[SOLO LETRAS]  Ingresa una Letra: ");scanf("%c", &letra);fflush(stdin);
        // TRANSFORMO LA LETR INGRESADA A MINUSCULA
        letra = toupper(letra);

      }while((letra < 65 || letra > 90) && (letra<97 || letra >122 ));
      ////

      letraExistente=0;

      // COMPRUEBO SI LA LETRA QUE INGRESA EL USUARIO YA SE DESCUBRI�

      for(int i= 0; i < strlen(palabraAleatoria); i++)
          if(letra == palAux[i]){
            letraExistente=1;
            break;
          }

      // SOLO SI letraExistente = 0 ENTONCES ES CUANDO LOS ACIERTOS O LOS INTENTOS AUMENTAN

      if(letraExistente==0){

        for(int i = 0; i<strlen(palabraAleatoria); i++)

          if(letra == palabraAleatoria[i]){
            palAux[i] = letra;
            aciertos++;
            puntajeJugadorActual +=100;
            letraEncontrada = 1;
          }

        if(letraEncontrada == 0 && letraExistente == 0)
        {
          intentos++;
          if(puntajeJugadorActual > 0)puntajeJugadorActual -=10;
        }
      }
      if(aciertos == strlen(palabraAleatoria)) break;
      if(intentos == 10) break;
    }
    if(aciertos == strlen(palabraAleatoria)){
      system("CLS");
      printf("\n    GANASTE!!! LA PALABRA ERA: %s\n\n", palabraAleatoria);
      printf("    TU PUNTAJE: %d\n\n", puntajeJugadorActual);
      system("PAUSE");
      printf("     Quieres jugar de nuevo? [y/n]: ");
      scanf("%c", &nuevoJuego);fflush(stdin);
      nuevoJuego=tolower(nuevoJuego);
      while (nuevoJuego != 'y' && nuevoJuego != 'n')
      {
        printf("     Quieres jugar de nuevo? [y/n]: ");
        scanf("%c", &nuevoJuego);fflush(stdin);
        nuevoJuego = tolower(nuevoJuego);
      }
    }
    else{
      system("CLS");
      printf("\n    PERDISTE!!! LA PALABRA ERA: %s\n\n", palabraAleatoria);
      printf("    TU PUNTAJE: %d\n\n", puntajeJugadorActual);
      _ModificarPuntaje();
      system("PAUSE");
      break;
    }
  }
  _ElejirOpcion();
}
/*------------------------------------------------------*/


/*------------------LEER RANKING-------------------------------*/
_LeerRanking(){
  struct Jugador jugador[longMaxArchivo];
  int idx;

  system("CLS");
  printf("\n=========================RANKING======================\n\n");
  FILE *file;
  file = fopen(archivoRanking, "r");
  idx = 0;
  if(file == NULL) _ComprobarExistenciaArchivos(); //COMRPUEBO QUE EL ARCHIVO EXISTA

  // SI EL NOMBRE DEL JUGADOR ES ENCONTRADO, pjEncontrado cambia a 1
  fseek(file, 0, SEEK_END); //POSICIONO EL CURSOR AL FINAL DEL ARCHIVO

  while(!feof(file)){
    if(ftell(file) == 0){ //SI EL ARCHIVO EST� VACIO{...}
      printf("\n==|====================RANKING VACIO======================\n");
      printf("\n--|-----------------------------------------------\n");
      break;
    }
    if(idx == 0)rewind(file); //SI NO EST� VACIO, POSICIONO EL CURSOR NUEVAMENTE EN EL INICIO
    fscanf(file, "%d %s", &jugador[idx].puntaje, &jugador[idx].nombre);
    fflush(stdin);
    printf("\n  |    NOMBRE: %s    ", jugador[idx].nombre);
    printf("  PUNTAJE: %d    \n",jugador[idx].puntaje);
    printf("--|-----------------------------------------------\n");
    idx++;
  }
  fclose(file);
  printf("\n");
  system("PAUSE");
  _ElejirOpcion();

}

/*-------------------------------------------------------------------*/



/*--------------MODIFICAR PUNTAJE----Y AGREGAR---------------------------*/

_ModificarPuntaje(){

  struct Jugador jugador[longMaxArchivo];
  int pjEncontrado, idx, idxPjEncontrado;

  pjEncontrado = 0; // Para verificar si existe el jugador actual
  idx = 0;
  idxPjEncontrado = -1; //El indice del jugador encontrado

  FILE *file;
  file = fopen(archivoRanking, "r"); //Modo lectura
  if(file == NULL) _ComprobarExistenciaArchivos(); //COMRPUEBO QUE EL ARCHIVO EXISTA

  while(!feof(file)){
    fscanf(file, "%d %s", &jugador[idx].puntaje, &jugador[idx].nombre);
    fflush(stdin);

    if(strcmpi(nombreJugadorActual, jugador[idx].nombre ) == 0){
      pjEncontrado = 1;  // SI EL NOMBRE DEL JUGADOR ES ENCONTRADO, pjEncontrado cambia a 1
      idxPjEncontrado = idx;
    }
    idx++;
  }
  fclose(file);

  if(pjEncontrado == 1){ //Si efectivamente, el jugador ya existe
    if(jugador[idxPjEncontrado].puntaje < puntajeJugadorActual){ //Si el puntaje del jugador actual es m�s alto
                                                                  //que el del jugador existente

      file = fopen(archivoRanking, "w"); //Modo Escritura
      jugador[idxPjEncontrado].puntaje = puntajeJugadorActual; //Reemplazo el puntaje del jugador anitguo en la
                                                                //posicion en la que existia anteriormente
                                                                //Por el puntaje nuevo (siendo este m�s alto)
      for(int i = 0; i < idx; i++){
        fprintf(file, "\n%d %s", jugador[i].puntaje, jugador[i].nombre);//Voy guardando los nombres y el nuevo puntaje
        fflush(stdin);
      }
      fclose(file);
    }
  }

  else{

    file = fopen(archivoRanking, "a"); //Modo adici�n
    fseek(file, 0, SEEK_END); //POSICIONO EL CURSOR AL FINAL DEL ARCHIVO
    if(ftell(file) == 0){//SI ES 0, EL ARCHIVO EST� VAC�O
      fprintf(file, "%d %s", puntajeJugadorActual, nombreJugadorActual ); //Unicamente agrego el nuevo jugador
      fclose(file);
    }                                                   //El cual no exist�a
    else{
      rewind(file);
      fprintf(file, "\n%d %s", puntajeJugadorActual, nombreJugadorActual ); //PRIMERO TABULO Y LUEGO AGREGO
      fflush(stdin);
      fclose(file);
    }
  }
}


/*----------------NUMERO ALEATORIO---------------------*/
_NumeroAleatorio(){
  int n;
  srand(time(0));
  n = rand()%cantidadPalabrasArchivo;
  return n;
}
/*-------------------------------------------------*/

/*----------------PALABRA ALEATORIA---------------------*/
_PalabraAleatoria(){

  int indice[cantidadPalabrasArchivo], numRandom, i = 0;
  char palabra[cantidadPalabrasArchivo][longMaxPalabra];

  FILE *file;
  file = fopen(archivoPalabras, "r");
  numRandom = _NumeroAleatorio();

  while(!feof(file)){

    fscanf(file, "%d %s", &indice[i], &palabra[i]);
    fflush(stdin);
    i++;
  }

  while(strlen(palabra[numRandom]) > 15 )
    numRandom = _NumeroAleatorio();
  strcpy(palabraAleatoria, palabra[numRandom]);

  fclose(file);
}

/*------------------------------------------------------*/

/*--------------GENERAR GR�FICOS-------------------------*/
_Graficos(int fallos){

    switch(fallos)
    {

      case 0:
          printf("||--------\n");
          printf("||\n||\n||\n||\n||\n");
          break;
      case 1:
          printf("||--------\n||\t0\n");
          printf("||\n||\n||\n||\n||\n");
          break;
      case 2:
          printf("||--------\n||\tO\n");
          printf("||\t|\n||\n||\n||\n||\n");
          break;

      case 3:
        printf("||--------\n||\tO\n");
        printf("||\t|\n||\t|\n||\n||\n||\n");
        break;
      case 4:
        printf("||--------\n||\tO\n");
        printf("||\t|\n||\t|\n||     /\n||\n||\n");
        break;
      case 5:
        printf("||--------\n||\tO\n");
        printf("||\t|\n||\t|\n||     /\n||    /\n||\n");
        break;
      case 6:
        printf("||--------\n||\tO\n");
        printf("||\t|\n||\t|\n||     / \\\n||    /\n||\n");
        break;
      case 7:
        printf("||--------\n||\tO\n");
        printf("||\t|\n||\t|\n||     / \\\n||    /   \\\n||\n");
        break;
      case 8:
        printf("||--------\n||\tO\n");
        printf("||     /|\n||\t|\n||     / \\\n||    /   \\\n||\n");
        break;
      case 9:
        printf("||--------\n||\tO\n");
        printf("||     /|\\\n||\t|\n||     / \\\n||    /   \\\n||\n");
  }
  printf("\nPUNTAJE: %d\n", puntajeJugadorActual);

}
/*-----------------------------------------------------*/


/*----------------COMPROBAR EXISTENCIA ARCHIVOS--------------------*/
_ComprobarExistenciaArchivos(){

  char seriePalabras[100][100]={"Dinamarca","Monterrey","Binario","Sororidad","Sonriente","Sopa","Yogurt","Pinocho","Youtube","Facebook","Numerico","Serenidad","Mantequilla",
  "Robotica","Sentimentalismo","Metabolismo","Marioneta","Marionetista",
"Cuarentena","Notepadd","Visual","Visualizacion","Virtual","Virtualizacion","Locacion",
"Localizacion","Monetizacion", "Mercurio","Saturno","Jupiter","Marte","Miercoles","Jueves",
"Venus","Moribundo","Diez","Mortal","Combate","Gimnasio","Gimnasia","Secreto",
"Verter","Vertedero","Vertex","Zoom","Salon","Solitario","Zopenco","Zoo",
"Suma","Resta","Multiplicacion","Division","Secretaria",
"Pais","Pizza","Pino","Piquete","detenerBucle"}; // Se pueden seguir agregando palabras, siempre y cuando "detenerBucle" Se mantenga al final;
                  // SI UNA PALABRA ES AGREGADA, AUMENTAR LA VARIABLE GLOBAL cantidadPalabrasArchivo en 1
                  // SI UNA PALABRA ES REMOVIDA, DISMINUIR LA VARIABLE GLOBAL cantidadPalabrasArchivo en 1

  int idx;
  idx = 0;

  FILE *file;
  file = fopen(archivoRanking, "r");
  if(file == NULL){
    fclose(file);
    file = fopen(archivoRanking, "w");
    fclose(file);
  }

  file = fopen(archivoPalabras, "r");
  if(file == NULL){
    fclose(file);
    file = fopen(archivoPalabras, "w");
    while(strcmpi(seriePalabras[idx], "detenerBucle")!=0){
      fprintf(file, "%d %s\n", idx+1,seriePalabras[idx]);
      idx++;
    }
    fclose(file);
  }
}
/*-----------------------------------------------------*/


/*---------------------PANTALLA COMPLETA------------------------*/

_PantallaCompleta(){
  keybd_event(VK_MENU,0x38,0, 0);
  keybd_event(VK_RETURN,0x1c,0,0);
  keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0);
  keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);
}


/*-----------------------------------------------------*/
