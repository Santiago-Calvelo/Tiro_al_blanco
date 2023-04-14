#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void print_results(char j[9][20], int points[9][4], int player, int tiros, int contC, int contE, int participantes, char posicion[100], int tp) {
    // imprimo el nombre del jugador
    printf("%s\n", j[player]);
    // imprimo todos los puntajes que realizo
    for (int i = 0; i < tiros; i++) {
        if      (posicion[i] == 'c' || posicion[i] == 'C') printf("\tc: %d\n", points[player][0]);
        else if (posicion[i] == 'm' || posicion[i] == 'M') printf("\tm: %d\n", points[player][1]);
        else if (posicion[i] == 'b' || posicion[i] == 'B') printf("\tb: %d\n", points[player][2]);
        else if (posicion[i] == 'f' || posicion[i] == 'F') printf("\tf: %d\n", points[player][3]); 
    }
    
    // calculo el % de menores de edad en base de la cantidad de menores * 100 sobre la cantidad de participantes totales
    double edad = (contE * 100) / participantes;
    // calculo el % de tiros centrados en base de la cantidad de tiros centrados * 100 sobre la cantidad de tiros totalales
    double tc = (contC * 100) / tiros;
    // imprimo los puntos totales
    printf("\tPuntos totales: %d\n", tp);
    // imprimo el % de tiros centrados
    printf("El porcentaje de tiros centrados del jugador es: %.2f\n", tc);
    // imprimo el % de menores de edad que participan en el juego
    printf("El porcentaje de menores de edad es: %.2f\n", edad);
}

void game(char j[9][20], int points[9][4]) {
    // declaro todas las variables que se usaran en el juego
    int participantes = 0; // se encarga de verificar que jueguen todos los jugadores y sirve para calcular el % de menores de edad
    char posicion[100]; // se encargara de almacenar todas las posiciones usadas en un juego 
    char n, p; // se encargaran de almacenar la inicial del jugador (n), y de almacenar la posicion usada en el momento (p)
    int e; // almacena de forma temporal la edad
    int contE = 0; // cuenta la cantidad de menores de edad
    bool jugadores_ingresados[9] = { false }; // almacena true(1) si el jugador ya jugó
    int max = 0; // almacena el puntaje máximo
    int tp = 0; // cuenta la cantidad de puntos totales y lo almacena


    while (1) {
        // imprimo la lista de jugadores que aún no jugaron, para que el usuario sepa quienes jugaron y quienes no
        printf("Lista de jugadores: ");
        for (int i = 0; i < 9; i++) {
            // revisa cada valor del array jugadores_ingresados, en caso de true(1) lo niega y eso hace que no se ejecute el if, en caso false(0) lo niega y se ejecuta
            if (!jugadores_ingresados[i]) printf("%s ", j[i]);
        }
        // imprimo un enter para mantener una interfaz más clara
        printf("\n");

        // le solicito al usuario la inicial del jugador que va a ingresar los tiros
        printf("Ingrese su inicial: ");
        scanf(" %c", &n);
        // esto borra el '\n' que queda luego del scanf, sin esto se rompe (NO TOCAR)
        getchar();

        // declaro una variable que servira para saber que jugador participa y si no existe el jugador
        int player = -1;
        // el for recorre el array la misma cantidad jugadores que hay y compara sus iniciales con la inicial elegida, si exist se guarda el indice
        for (int i = 0; i < 9; i++) { if (j[i][0] == n || j[i][0]+32 == n) player = i; }
        // si no existe el jugador dentro del array player queda en -1 y entra al if
        if (player == -1) printf("Ingrese una inicial valida\n");
        // si jugadores_ingresados subíndice player es true significa que ya participo y el programa nuevamente la inicial
        else if (jugadores_ingresados[player]) printf("Este jugador ya participo\n");
        else {
            
            // solicito la edad del jugador
            printf("Ingrese su edad: ");
            scanf(" %d", &e);
            // esto borra el '\n' que queda luego del scanf, sin esto se rompe (NO TOCAR)
            getchar();

            // en caso de que el jugador sea menor de edad sumo la cantidad de menores
            if (e < 18) contE++;
            // hago que jugadores_ingresados[player] sea igual a true para que al volver a solicitar jugadores este no aparezca
            jugadores_ingresados[player] = true;
            // sumo a la cantidad de participantes que jugaron
            participantes++;
            // declaro i para poder recorrer el array posicion
            int i = 0;

            // declaro tiros que contara todos los tiros realizados y contC que contara unicamente los tiros centrados
            int tiros = 0;
            int contC = 0;
            while (1) {
                // la variable repetido se encargara de no almacenar posiciones que ya existen, asi no se imprime doble
                bool repetido = false;
                // se le informa al usuario cuales son las posiciones que puede ingresar y se le solicita que ingrese una
                printf("Las posiciones validas son C, M, B, F\n");
                printf("Ingrese la posicion: ");
                scanf(" %c", &p);
                // esto borra el '\n' que queda luego del scanf, sin esto se rompe (NO TOCAR)
                getchar();
                
                // se revisa que no exista p dentro del array posicion
                for (int j = 0; j < tiros; j++) { 
                  if (posicion[j] == p) { repetido = true; break; } 
                }
                // si no existe dentro del array se almacena
                if (!repetido) posicion[i] = p;

                // sumo a i para luego guardar en otra posicion
                i++;

                // reviso en que posicion cayó el dardo y sumo dependiendo de ello en la matriz encargada de almacenar
                // agregarle el subindice player me permite identificar los puntajes de cada jugador
                if      (p == 'c' || p == 'C') { points[player][0] += 100; tiros++; contC++; }
                else if (p == 'm' || p == 'M') { points[player][1] += 50; tiros++; }
                else if (p == 'b' || p == 'B') { points[player][2] += 10; tiros++; }
                else if (p == 'f' || p == 'F') { points[player][3] -= 10; tiros++; }
                else                           printf("Ingrese una posicion valida\n");

                // sumo todos los puntajes para tener el total
                tp = points[player][0] + points[player][1] + points[player][2] + points[player][3];
                
                // le pregunto al usuario si desea seguir ingresando tiros para el mismo jugador
                printf("Deseas seguir ingresando datos? s/n\n");
                
                // almaceno su respuesta
                char choice;
                scanf(" %c", &choice);
                // esto borra el '\n' que queda luego del scanf, sin esto se rompe (NO TOCAR)
                getchar(); 

                // en caso de que no, llamo a la funcion para imprimir todo y finalizo el while(1) secundario
                if (choice == 'n' || choice == 'N') {
                    print_results(j,points,player,tiros,contC,contE,participantes,posicion,tp);
                    break;
                }
            }
            // reviso si tp(puntaje total) es mayor a max y en caso de que si lo guardo en max
            if(max < tp) max = tp;

            // cuando todos los participantes jugaron imprimo el máximo y finaliza el while(1) principal
            if (participantes == 9) {
                printf("El maximo de puntos fue: %d\n",max);
                break;
            }
        }
    }

}

void new_valor(char j[9][20]) {
    // c se encargara de almacenar de forma temporal el nuevo nombre
    char  c[100];
    

    // imprimo los nombres ya ingresados para evitar que el usuario repita
    printf("Los nombres ya ingresados son: ");
    for (int i = 0; i < 9; i++) if (j[i] != '\0') printf("%s ", j[i]);
    printf("\n");

    while (1) {
        bool repetido = false;

        // le solicito al usuario que ingrese el nuevo nombre
        printf("Ingrese el nombre del 4to jugador sin repetir iniciales: ");
        fgets(c, 100, stdin);

        // reviso que el usuario haya comprendido que no debe repetir y en caso de repeticiones le asigno a repetido el valor true(1)
        for (int i = 0; i < 9; i++) { 
            if (j[i][0] == c[0] || j[i][0] == c[0]-32) { repetido = true; break; } 
        }

        // si repétido es true(1) el while infinito continua hasta que repetido sea false(0)
        if (repetido) printf("La inicial ya esta cargada\n"); 
        else {

            // strcpy es una función de la libreria strings que copia una string en otra
			strcpy(j[3], c);
			printf("La inicial se cargo correctamente\n"); 
			break; 
		}
    }
   
}

int main(void) {
    // declaro los jugadores que participaran, excepto el nombre del 4to jugador
    char j[9][20] = {"Ana", "Francisco", "Santiago", "\0", "Ignacio", "Diego", "Guido", "Hector", "Nahuel"};
    // points es la matriz encargada de guardar los puntajes
    int points[9][4] = {0};
    
    // llamo a la funcion encargada de ingresar el nombre del 4to
    new_valor(j);
    // una vez ingresar el nombre del 4to jugador llamo a la funcion encargada de realizar el juego
    game(j,points);
}