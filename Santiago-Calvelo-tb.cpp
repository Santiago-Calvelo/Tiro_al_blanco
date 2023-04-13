#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void print_results(char j[9][20], int points[9][4], int player, double tiros, double contC, double contE, int participantes, char posicion[100]) {
    printf("%s\n", j[player]);
    for (int i = 0; i < tiros; i++) {
        if      (posicion[i] == 'c' || posicion[i] == 'C') printf("\tc: %d\n", points[player][0]);
        else if (posicion[i] == 'm' || posicion[i] == 'M') printf("\tm: %d\n", points[player][1]);
        else if (posicion[i] == 'b' || posicion[i] == 'B') printf("\tb: %d\n", points[player][2]);
        else if (posicion[i] == 'f' || posicion[i] == 'F') printf("\tf: %d\n", points[player][3]); 
    }
    int tp = points[player][0] + points[player][1] + points[player][2] + points[player][3];
    double edad = (contE * 100) / participantes;
    printf("\tPuntos totales: %d\n", tp);
    printf("El porcentaje de tiros centrados del jugador es: %.2f\n", (contC * 100) / tiros);
    printf("El porcentaje de menores de edad es: %.2f\n", edad);
}

void game(char j[9][20], int points[9][4]) {
    int participantes = 0;
    char posicion[100];
    char n, p;
    int e;
    double contE = 0.0;
    bool jugadores_ingresados[9] = { false };



    while (1) {
        printf("Lista de jugadores: ");
        for (int i = 0; i < 9; i++) {
            if (!jugadores_ingresados[i]) printf("%s ", j[i]);
        }
        printf("\n");

        printf("Ingrese su inicial: ");
        scanf(" %c", &n);
        getchar();

        int player = -1;
        for (int i = 0; i < 9; i++) { if (j[i][0] == n || j[i][0]+32 == n) player = i; }
        if (player == -1) printf("Ingrese una inicial valida, %d\n", player);
        else if (jugadores_ingresados[player]) printf("Este jugador ya participo\n");
        else {
 
            printf("Ingrese su edad: ");
            scanf(" %d", &e);
            getchar();
        
            if (e < 18) contE++;
            jugadores_ingresados[player] = true;
            participantes++;
            int i = 0;

            double tiros = 0.0;
            double contC = 0.0;
            while (1) {
                int repetido = 0;
                printf("Las posiciones validas son C, M, B, F\n");
                printf("Ingrese la posicion: ");
                scanf(" %c", &p);
                getchar();

                for (int j = 0; j < tiros; j++) { 
                  if (posicion[j] == p) { repetido = 1; break; } 
                }
                if (repetido == 0) posicion[i] = p;

                i++;
                if      (p == 'c' || p == 'C') { points[player][0] += 100; tiros++; contC++; }
                else if (p == 'm' || p == 'M') { points[player][1] += 50; tiros++; }
                else if (p == 'b' || p == 'B') { points[player][2] += 10; tiros++; }
                else if (p == 'f' || p == 'F') { points[player][3] -= 10; tiros++; }
                else                           printf("Ingrese una posicion valida\n");
            
                printf("Deseas seguir ingresando datos? s/n\n");

                char choice;
                scanf(" %c", &choice);
                getchar(); 

                if (choice == 'n' || choice == 'N') {
                    print_results(j,points,player,tiros,contC,contE,participantes,posicion);
                    break;
                }
            }

            if (participantes >= 9) break;
        }
    }

}

void new_valor(char j[9][20]) {
    char  c[100];
    
    printf("Los nombres ya ingresados son: ");
    for (int i = 0; i < 9; i++) if (j[i] != '\0') printf("%s ", j[i]);
    printf("\n");

    while (1) {
        int repetido = 0;
        printf("Ingrese el nombre del 4to jugador: ");
        fgets(c, 100, stdin);

        for (int i = 0; i < 9; i++) { 
            if (j[i][0] == c[0] || j[i][0] == c[0]-32) { repetido = 1; break; } 
        }

        if (repetido) printf("La inicial ya esta cargada\n"); 
        else { 
			strcpy(j[3], c);
			printf("La inicial se cargo correctamente\n"); 
			break; 
		}
    }
   
}

int main(void) {
    char j[9][20] = {"Ana", "Francisco", "Santiago", "\0", "Ignacio", "Diego", "Guido", "Hector", "Nahuel"};
    int points[9][4] = {0};
    
    new_valor(j);
    game(j,points);
}
