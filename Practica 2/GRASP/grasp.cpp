#include <iostream>
#include <utility>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <ctime>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>

//Generador de numeros aleatorios
#define MASK 2147483647
#define PRIME 65539
#define SCALE 0.4656612875e-9
#define Rand()  (( Seed = ( (Seed * PRIME) & MASK) ) * SCALE )
#define Randint(low,high) ( (int) (low + (high-(low)+1) * Rand()))
#define Randfloat(low,high) ( (low + (high-(low))*Rand()))

using namespace std;

//Variables glovales
int evaulaciones = 0;
int** matriz_flujo;
int** matriz_localizacion;
int TAM_MATRICES = 0;
const int MAX_ITER = 50000;
int Seed = 3;

void lectura_Fichero(char* archivo){


	int contador = 0;
	int limite = 0;
	int numero = 0;
	char vacio = ' ';


	ifstream entrada;
	entrada.open(archivo);

	if(!entrada.is_open()){

		cout << "No se ha encontrado el archivo: "<< archivo << " " << endl;
		exit(-1);

	}

	//Tama�o del problema
	entrada >> TAM_MATRICES;



	cout << "El tamanio del problema es: " << TAM_MATRICES << endl;



	//Creo la matriz de flujo
	matriz_flujo = new int *[TAM_MATRICES];
    for(int i = 0; i < TAM_MATRICES; i++) matriz_flujo[i] = new int[TAM_MATRICES];



    //Creo la matriz de localizaciones
    matriz_localizacion = new int *[TAM_MATRICES];
    for(int i = 0; i < TAM_MATRICES; i++) matriz_localizacion[i] = new int[TAM_MATRICES];



	//Relleno la matriz de localizaciones con los datos leido del fichero
	for(int i = 0; i < TAM_MATRICES; i++){

		for(int j = 0; j < TAM_MATRICES; j++){

			entrada >> numero;
			matriz_localizacion[i][j] = numero;

		}

	}

	//Elimino el salto de linea que separa las dos matrices
	entrada >> vacio;



	//Relleno la matriz de flujo con los datos leidos del fichero.
	for(int k = 0; k < TAM_MATRICES; k++){

		for(int l = 0; l < TAM_MATRICES; l++){

			entrada >> numero;
			matriz_flujo[k][l] = numero;


		}

	}

	//Termino la lectura y cierro el archivo
	entrada.close();


}

//Funcion objetivo del problema
int funcion_Objetivo(vector<int> &telomero){

	evaulaciones++;

	int resultado = 0;
	int contador = 0;
	int indice = 0;

		for(int i = 0; i < TAM_MATRICES; i++){
			for(int j = 0; j < TAM_MATRICES; j++){

				resultado += matriz_flujo[i][j] * matriz_localizacion[telomero[i]][telomero[j]];

			}
		}

	return resultado;
}

//Operador de intercambio para la busquedad de vecinos
vector<int> intercambio(vector<int> vector_permutacion,int r, int s){

	vector<int> respuesta; respuesta.resize(TAM_MATRICES);
	int auxiliar = 0;
	respuesta = vector_permutacion;
	auxiliar = respuesta[r];
	respuesta[r] = respuesta[s];
	respuesta[s] = auxiliar;
	return respuesta;

}

//Genera una solucion aleatoria del problema
void generar_solucion_aleatoria(vector<int> &solucion){

	//vector<int> solucion; solucion.resize(TAM_MATRICES);
	vector<int> auxiliar;

	int contador = 0;
	int aleatorio = 0;

	//Creo el vector por defecto
	for(int i = 0; i < TAM_MATRICES; i++){

			auxiliar.push_back(i);
			contador++;

	}


	//Probar este algoritmo
	for(int i = 0; i < TAM_MATRICES; i++){

		aleatorio = rand()%contador; //Obtengo un numero aleatorio entre 0 y contador

		solucion[i] = auxiliar[aleatorio]; //Asigno al vector solucion un valor aleatorio.

		auxiliar.erase(auxiliar.begin()+aleatorio); //Borro la posicion usada

		contador--; //Reduzco el intervalor para generar el numero aleatorio
	}

}

//Calcula el coste de la nueva solucion cuando se realiza un unico intercambio r-s
int factorizacion(vector<int> &vector,int r,int s){

	int ganancia = 0;

	evaulaciones++;

	for(int k = 0; k < TAM_MATRICES; k++){

		if(k != r && k != s){

			ganancia += (

			matriz_flujo[r][k] *
			(matriz_localizacion[vector[s]][vector[k]] - matriz_localizacion[vector[r]][vector[k]])
			+
			matriz_flujo[s][k] *
			(matriz_localizacion[vector[r]][vector[k]] - matriz_localizacion[vector[s]][vector[k]])
			+
			matriz_flujo[k][r] *
			(matriz_localizacion[vector[k]][vector[s]] - matriz_localizacion[vector[k]][vector[r]])
			+
			matriz_flujo[k][s] *
			(matriz_localizacion[vector[k]][vector[r]] - matriz_localizacion[vector[k]][vector[s]])

			);

		}


	}

    return ganancia;

}
//Imprime un vector
void imprimir_vector(vector<int> &vector){

	for(int i = 0; i < TAM_MATRICES; i++){

		cout << vector[i] << " ";

	}

	cout << endl;

}

vector<int> gredy_aleatorio(){




}

//Busqueda local
//Implementa el algoritmo de la busqueda_local
vector<int> busqueda_local(vector<int> vector_permutacion,int iteraciones,int& coste){

	bool dlb[TAM_MATRICES];
	bool mejora = true;
	int valor_factorizacion = 0;
	coste = funcion_Objetivo(vector_permutacion);

	//Inicializo la mascara a false
	for(int i = 0; i < TAM_MATRICES; i++) dlb[i] = false;

	while(mejora){

		for(int i = 0; i < TAM_MATRICES; i++){

			if(dlb[i] == false){

				mejora = false;

				for(int j = 0; j < TAM_MATRICES; j++){

					valor_factorizacion = factorizacion(vector_permutacion,i,j);

					if(valor_factorizacion < 0){

						vector_permutacion = intercambio(vector_permutacion,i,j);
						dlb[i] = false; dlb[j] = false;
						mejora = true;
						coste = coste + valor_factorizacion;

					}
				}

				if(!mejora) dlb[i] = true;

			}
		}
	}

	return vector_permutacion;

}


vector<int> GRASP(){

	vector<int> solucion; solucion.resize(TAM_MATRICES);
    vector<int> mejor_solucion; mejor_solucion.resize(TAM_MATRICES);
	int coste = 0;
	int mejor_coste = 0;

    while(evaulaciones <= 50000){

        solucion = gredy_aleatorio(solucion);
        solucion = busquedad_local(solucion,50000,coste);

		//Solo para la primera iteracion
		if(mejor_coste == 0){

			mejor_coste = coste;
			mejor_solucion = solucion;

		}

        if(coste < mejor_coste){

            mejor_solucion = solucion;
            mejor_coste = coste;

        }

    }




}


int main(int argc, char** argv){

    if(argc < 2){

        cout << "Se requiere el archivo de datos" << endl;
        exit(-1);

    }

	vector<int> solucion; solucion.resize(TAM_MATRICES);

	solucion = GRASP();

	cout << "El vector solucion es: ";
	imprimir_vector(solucion);
	cout << " Con coste: " << funcion_Objetivo(solucion) << endl;

}
