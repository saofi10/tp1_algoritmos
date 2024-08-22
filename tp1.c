#include "tp1.h"
#include <stdlib.h>

bool is_prime(int x){
    if (x < 2) return false;
    for (int i = 2; i*i <= x; i++){ //optimizacion para no recorrer todos los numeros (solo hasta la raiz cuadrada)
        if (x % i == 0) return false;
    }
    return true;
}

int storage_capacity(float d, float v){ 
    if (v == 0) return 0; //si el volumen del producto es 0, no entra nada
    if (d == 0) return 0; //si el volumen del deposito es 0, no entra nada
    if (d < 0 || v < 0) return 0; //si alguno es negativo no entra nada
    if (d < v) return 0; //si el volumen del deposito es menor al del producto no entra nada
    int quantity =  (int)(d / v);
    
    return quantity;
}

void swap(int *x, int *y) {
    if (x == NULL || y == NULL) { //si son null no hago nada
        return;
    }
    int aux = *x;
    *x = *y;
    *y = aux;
    return;
}

int array_max(const int *array, int length) {
    if (length == 0) return 0; //asegurarse de que tenga al menso un elemento porque sino no accederia a la posicion 0

    int aux_max= array[0];
    for (int i = 1; i < length; i++){
        if (array[i] > aux_max) {aux_max = array[i];}
    }
    return aux_max;
}

void array_map(int *array, int length, int f(int)) {
     if (array == NULL || f == NULL) {
        return;  // asegurarse de que no sea null pq sino tira error, algo de q trata de saltar a la direccion 0x0, la prueba de map de arreglo sin funcion
    }
    for (int i = 0; i < length; i++){
        array[i] = f(array[i]);
    }
    return;
}

int *copy_array(const int *array, int length) {
    if (array == NULL) {
        return NULL;
    }
    int *new_array = (int *)malloc(length * sizeof(int));
    for (int i = 0; i < length; i++){
        new_array[i] = array[i];
    }
    return new_array;
}

int **copy_array_of_arrays(const int **array_of_arrays, const int *array_lengths, int array_amount) {
    if (array_of_arrays == NULL || array_lengths == NULL) {
        return NULL;
    }

    int **new_array = (int **)malloc(array_amount * sizeof(int *));
    if (new_array == NULL) {
        return NULL; // Por si falla en la asignación de memoria
    }

    for (int i = 0; i < array_amount; i++) {
        if (array_of_arrays[i] == NULL) { //si es null no tengo que hacer nada y sigo con el siguiente
            new_array[i] = NULL;
            continue;
        }
        new_array[i] = copy_array(array_of_arrays[i], array_lengths[i]);
        if (new_array[i] == NULL) {
            /// Manejo de error si copy array falla
            for (int j = 0; j < i; j++) { 
                free(new_array[j]);  //o sea como asigne memoria, si era null tengo que liberarla
            }
            free(new_array);
            return NULL;
        }
    }

    return new_array;
}


void free_array_of_arrays(int **array_of_arrays, int *array_lenghts, int array_amount){
    if (array_of_arrays == NULL) { //si es null no tengo que hacer nada
        return;
    }
    for (int i = 0; i < array_amount; i++){
        if (array_of_arrays[i] != NULL){ //si es null no tengo que liberar memoria
        free(array_of_arrays[i]);
        }
    }
    free(array_of_arrays); //libero el array grande
    free(array_lenghts); //libero el array de longitudes ???? claro para eso me lo pasaba 
    return;
}

void bubble_sort(int *array, int length){
    if (array == NULL || length <= 0) { //chequear que no sea null y que no tenga longitud 0 o menor
        return;
    }
    for(int i=0; i<length;i++){
        for(int j=0;j<length-1-i;j++){
            if(array[j]>array[j+1]){
                swap(&array[j],&array[j+1]);
            }
        }

    }
    return;
}

bool array_equal(const int *array1, int length1, const int *array2, int length2){

    if (array1==NULL && array2==NULL)return true;
    if (array1==NULL || array2==NULL)return false;
    if (length1!=length2)return false; //descarto casos rapido
    for (int i = 0; i < length1; i++){
        if (array1[i] != array2[i]) return false;
    }
    return true;
}

bool integer_anagrams(const int *array1, int length1,
                      const int *array2, int length2){
    if (array1==NULL || array2==NULL)return false;
    if (length1!=length2)return false; //descarto casos rapido
    int *array1_copy = copy_array(array1, length1);
    int *array2_copy = copy_array(array2, length2);
    if (array1_copy == NULL || array2_copy == NULL) { //si no se pudo copiar, no se puede comparar y me salgo
        free(array1_copy);
        free(array2_copy);
        return false;
    }
    bubble_sort(array1_copy, length1); //reutilizo funciones previas
    bubble_sort(array2_copy, length2);
    bool result = array_equal(array1_copy, length1, array2_copy, length2);
    free(array1_copy);
    free(array2_copy); //liberar memoria ya sea que los arreglos sean anagramas o no !!!
    return result;
}
