/*Autor: Enrique Casale Linde
Correo: enriquex@correo.ugr.es
Universidad: Universidad de Granada
*/

/*Esquema de enfriamiento:

T + 1 = T / T + beta * T
beta = T0 - Tf / M * T0*Tf

M = Nº de enfriamientos ( 50.000 / max_vecinos)
Tf = temperatura final cercana a 0 (10^-3)
T0 = U * C(S0) / -ln(o)
C(S0) = Coste de la solucion inicial
o = [0,1] (Probabilidad de aceptar una solucion peor que la inicial)
U = o
max_vecinos = 10 * N
max_exitos = 0.1 * max_vecinos



------------------------------------------------------------------------------------------
Esquema de enfriamiento opcional:

T + 1 = alpha * T
alpha = [0.9,0.99]

*/

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

using namespace std;

#define MASK 2147483647
#define PRIME 65539
#define SCALE 0.4656612875e-9
#define Rand()  (( Seed = ( (Seed * PRIME) & MASK) ) * SCALE )
#define Randint(low,high) ( (int) (low + (high-(low)+1) * Rand()))
#define Randfloat(low,high) ( (low + (high-(low))*Rand()))



//Variables glovales
//--------------------------------------------------------------------------------------------------------------------//
/**/

int evaulaciones = 0;
int** matriz_flujo;
int** matriz_localizacion;
int TAM_MATRICES = 0;
const int MAX_ITER = 50000;
int Seed = 3;
//--------------------------------------------------------------------------------------------------------------------//

//Funciones
//--------------------------------------------------------------------------------------------------------------------//
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


//Funcion de enfriamiento simulado
/*
Parametros:

1º iteraciones
2º temperatura final
3º solucion_nueva
4º coste de la solucion_nueva
5º constante

*/

vector<int> enfriamiento_simulado(int iteraciones,float temperatura_final,float constante){


	vector<int> mejor_solucion;  mejor_solucion.resize(TAM_MATRICES);
	vector<int> solucion_actual; solucion_actual.resize(TAM_MATRICES);

	generar_solucion_aleatoria(solucion_actual);
	int coste = funcion_Objetivo(solucion_actual);
	mejor_solucion = solucion_actual;

	float temperatura_inicial = (constante * coste) / (-1*log(constante));
	float beta = (temperatura_inicial - temperatura_final) / (iteraciones * temperatura_final * temperatura_inicial);
	float temperatura_actual = temperatura_inicial;
	int max_vecinos = 10 * TAM_MATRICES;
	int max_exitos = 0.1 * max_vecinos;


	int coste_siguiente = 0;
	int diferencia = 0;
	int rand_r = 0;
	int rand_s = 0;
	int exitos = 0;
	int mejor_coste = coste;
	float aleatorio = 0;
	float operacion = 0;
	int contador_exitos = 0;

	cout << endl;


	for(int i = 0; i < iteraciones && evaulaciones <= 50000 && temperatura_actual >= temperatura_final; i++){

		exitos = 0;
		cout << "Iteracion: " << i << endl;

		for(int j = 0; j < max_vecinos && exitos <= max_exitos; j++){


			rand_r = Randint(0,TAM_MATRICES-1);
			rand_s = Randint(0,TAM_MATRICES-1);

			while(rand_r == rand_s){

				rand_r = Randint(0,TAM_MATRICES-1);
				rand_s = Randint(0,TAM_MATRICES-1);

			}

			coste_siguiente = factorizacion(solucion_actual,rand_r,rand_s);
			diferencia = (coste + coste_siguiente) - coste;

			operacion = exp((-1*diferencia)/(i * temperatura_actual));
			aleatorio = Randfloat(0,1);


			if((diferencia < 0) || (aleatorio <= operacion)){

				exitos++;
				solucion_actual = intercambio(solucion_actual,rand_r,rand_s);
				coste = coste + coste_siguiente;
				contador_exitos++;
				//cout << "Coste: " << coste << " " << "Mejor costes: " << mejor_coste << endl;

				if(mejor_coste > coste){


					cout << "Aqui" << endl;
					mejor_solucion = solucion_actual;
					mejor_coste = coste;

				}
			}

		}
		exitos = 0;
		//cout << "temperatura_actual: " << temperatura_actual << " ";
		temperatura_actual = temperatura_actual / (1 + beta * temperatura_actual);
		//temperatura_actual = 0.99*temperatura_actual;
		//cout << "temperatura nueva: " << temperatura_actual << "Evaula: " << evaulaciones << endl;

	}

	cout << "Contador: " << contador_exitos << endl;

	return mejor_solucion;

}

void destruir(){

	for(int i = 0; i < TAM_MATRICES; i++){
		delete[] matriz_flujo[i];
		delete[] matriz_localizacion[i];
	}
	delete[] matriz_flujo;
	delete[] matriz_localizacion;


}


//--------------------------------------------------------------------------------------------------------------------//

int main(int argc, char** argv){

if(argc < 2){

	cout << "Se necesita un archivo de entrada" << endl;
	exit(-1);

}

char* archivo = argv[1];
int coste = 0;
lectura_Fichero(archivo);

vector<int> resultado; resultado.reserve(TAM_MATRICES);

for(int i = 0; i < TAM_MATRICES; i++){
	for(int j = 0; j < TAM_MATRICES; j++){

		cout << matriz_flujo[i][j] << " ";

	}
	cout << endl;
}


resultado = enfriamiento_simulado(50000,pow(10,-3),0.3);

cout << endl;

imprimir_vector(resultado);

cout << endl;

cout << "coste: " << funcion_Objetivo(resultado) << endl;


destruir();

}
