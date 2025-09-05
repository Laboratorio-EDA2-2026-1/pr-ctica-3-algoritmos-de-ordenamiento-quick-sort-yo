#include <stdio.h>
#include <stdlib.h>

/*
 Formato de entrada:
   m
   t1 v1
   t2 v2
   ...
   tm vm

 Donde:
   ti ∈ {0,1}  (0=tuerca, 1=tornillo)
   vi es el "tamaño" (entero) de esa pieza

 El programa separa las piezas en dos arreglos (tuercas y tornillos).
 Requisito: debe haber la misma cantidad de tuercas que de tornillos.
*/

/* 
 * Prototipos sugeridos de funciones auxiliares
 * --------------------------------------------
 * Estas NO están implementadas, solo son guías:
 *
 * int partir_tuercas(int tuercas[], int bajo, int alto, int tornilloPivote);
 *   -> Reorganiza las tuercas comparándolas con un tornillo pivote.
 *
 * int partir_tornillos(int tornillos[], int bajo, int alto, int tuercaPivote);
 *   -> Reorganiza los tornillos comparándolos con una tuerca pivote.
 *
 * La idea: usarlas de forma recursiva, estilo quicksort.
 */

/*
 * FUNCIÓN PRINCIPAL A IMPLEMENTAR
 *
 * Objetivo: reordenar ambos arreglos (tuercas y tornillos) de manera que
 *           al final ambos queden en el mismo orden.
 *
 * Reglas:
 * - Solo se permite comparar tuerca vs tornillo.
 * - No está permitido comparar tuerca vs tuerca ni tornillo vs tornillo.
 *
 */
// Función auxiliar la cual reorganiza las tuercas usando un tornillo pivote
int partir_tuercas(int tuercas[], int bajo, int alto, int tornilloPivote) {
    int i = bajo, temp;
    for (int j = bajo; j < alto; j++) {
        if (tuercas[j] < tornilloPivote) {
            temp = tuercas[i];
            tuercas[i] = tuercas[j];
            tuercas[j] = temp;
            i++;
        } else if (tuercas[j] == tornilloPivote) {
            temp = tuercas[j];
            tuercas[j] = tuercas[alto];
            tuercas[alto] = temp;
            j--;
        }
    }
    temp = tuercas[i];
    tuercas[i] = tuercas[alto];
    tuercas[alto] = temp;
    return i;
}

// Función auxiliar la cual reorganiza los tornillos usando una tuerca pivote
int partir_tornillos(int tornillos[], int bajo, int alto, int tuercaPivote) {
    int i = bajo, temp;
    for (int j = bajo; j < alto; j++) {
        if (tornillos[j] < tuercaPivote) {
            temp = tornillos[i];
            tornillos[i] = tornillos[j];
            tornillos[j] = temp;
            i++;
        } else if (tornillos[j] == tuercaPivote) {
            temp = tornillos[j];
            tornillos[j] = tornillos[alto];
            tornillos[alto] = temp;
            j--;
        }
    }
    temp = tornillos[i];
    tornillos[i] = tornillos[alto];
    tornillos[alto] = temp;
    return i;
}

void emparejar_tuercas_y_tornillos(int tuercas[], int tornillos[], int n) {
    // Escribe aquí tu función
    //
    // Sugerencia: define una función recursiva como:
    // void emparejar_recursivo(int tuercas[], int tornillos[], int bajo, int alto);
    //
    // Dentro de ella puedes llamar a:
    //   int indicePivote = partir_tuercas(tuercas, bajo, alto, tornillos[alto]);
    //   partir_tornillos(tornillos, bajo, alto, tuercas[indicePivote]);
    //
    // Y luego hacer llamadas recursivas en los subarreglos.
    int bajo = 0;
    int alto = n - 1;

    int pilaBajo[100], pilaAlto[100];
    int tope = 0;

    pilaBajo[tope] = bajo;
    pilaAlto[tope] = alto;
    tope++;

    while (tope > 0) {
        tope--;
        bajo = pilaBajo[tope];
        alto = pilaAlto[tope];

        if (bajo < alto) {
            int indiceTuerca = partir_tuercas(tuercas, bajo, alto, tornillos[alto]);
            partir_tornillos(tornillos, bajo, alto, tuercas[indiceTuerca]);

            // Simulamos la recursión con la pila
            pilaBajo[tope] = bajo;
            pilaAlto[tope] = indiceTuerca - 1;
            tope++;

            pilaBajo[tope] = indiceTuerca + 1;
            pilaAlto[tope] = alto;
            tope++;
        }
    }
}

/* Imprime un arreglo lineal */
void imprimir_arreglo(const char *etiqueta, int arr[], int n) {
    printf("%s: ", etiqueta);
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(void) {
    int m;  // número total de pares provistos en la entrada
    if (scanf("%d", &m) != 1 || m <= 0) {
        fprintf(stderr, "Error: m inválido.\n");
        return 1;
    }

    int *tuercas   = (int *)malloc(m * sizeof(int));
    int *tornillos = (int *)malloc(m * sizeof(int));
    if (!tuercas || !tornillos) {
        fprintf(stderr, "Error: memoria insuficiente.\n");
        free(tuercas); free(tornillos);
        return 1;
    }

    int n_tuercas = 0, n_tornillos = 0;

    for (int i = 0; i < m; i++) {
        int tipo, valor;
        if (scanf("%d %d", &tipo, &valor) != 2) {
            fprintf(stderr, "Error: entrada inválida en la línea %d.\n", i + 2);
            free(tuercas); free(tornillos);
            return 1;
        }
        if (tipo == 0) {           // tuerca
            tuercas[n_tuercas++] = valor;
        } else if (tipo == 1) {    // tornillo
            tornillos[n_tornillos++] = valor;
        } else {
            fprintf(stderr, "Error: tipo debe ser 0 (tuerca) o 1 (tornillo).\n");
            free(tuercas); free(tornillos);
            return 1;
        }
    }

    if (n_tuercas != n_tornillos) {
        fprintf(stderr, "Error: cantidad desigual de tuercas (%d) y tornillos (%d).\n",
                n_tuercas, n_tornillos);
        free(tuercas); free(tornillos);
        return 1;
    }

    int n = n_tuercas; // número de parejas

    // Llamada a la función a implementar
    emparejar_tuercas_y_tornillos(tuercas, tornillos, n);

    // Mostrar resultados como dos arreglos lineales
    imprimir_arreglo("Tuercas", tuercas, n);
    imprimir_arreglo("Tornillos", tornillos, n);

    free(tuercas);
    free(tornillos);
    return 0;
}
