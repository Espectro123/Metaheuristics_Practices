#include <iostream>
#include <utility>
#include <fstream>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

//Variables glovales
int** matriz_flujo; // Matriz de flujo
int** matriz_localizacion; //Matriz de localizaciones
unsigned short TAM_MATRICES; //Tama�o de las matrices. Normalmente son iguales. Deben leerse de un fichero

using namespace std;

//Lectura de archivos
void lectura_Fichero(char* archivo){


	int contador = 0;
	int limite = 0;
	short numero;
	char vacio;


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

int funcion_Objetivo(int* telomero){


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

int* generar_solucion_aleatoria(){

	int* solucion;
	solucion = new int[TAM_MATRICES];

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


	return solucion;
}

void imprimeVector(int* vector){

	for(int i = 0; i < TAM_MATRICES; i++){

		cout << vector[i] << " ";

	}

}


//El contenido del vector es de localizacion
//El indice es el flujo
int* gredy(){


	int vector_flujo[TAM_MATRICES];
	int vector_localizacion[TAM_MATRICES];
	int* solucion = new int[TAM_MATRICES];
	int flujo_maximo = 0;
	int distancia_centrica = 999999;
	int coordenada_loc = 0;
	int coordenada_flujo = 0;

		for(int i = 0; i < TAM_MATRICES; i++){

			vector_flujo[i] = 0;
			vector_localizacion[i] = 0;

			for(int j = 0; j < TAM_MATRICES; j++){

				vector_flujo[i] += matriz_flujo[i][j];
				vector_localizacion[i] += matriz_localizacion[i][j];

			}

		}


		for(int i = 0; i < TAM_MATRICES; i++){
			for(int j = 0; j < TAM_MATRICES; j++){

					if(vector_localizacion[j] < distancia_centrica && vector_localizacion[j] != -1){

						distancia_centrica = vector_localizacion[j];
						coordenada_loc = j;
					}

					if(vector_flujo[j] > flujo_maximo && vector_flujo[j] != -1){

						flujo_maximo = vector_flujo[j];
						coordenada_flujo = j;

					}

			}

			vector_localizacion[coordenada_loc] = -1;
			vector_flujo[coordenada_flujo] = -1;
			solucion[coordenada_flujo] = coordenada_loc;
			coordenada_loc = 0;
			coordenada_flujo = 0;
			distancia_centrica = 999999;
			flujo_maximo = 0;

		}

		return solucion;

}

int main(int argc, char** argv){

if(argc < 2){

	cout << "Se necesitan mas argumentos. 3 argumentos necesarios: " << endl;
	cout << "1º Archivo" << endl;
	exit(-1);

}


int* vector_gredy;
int valor_gredy;

lectura_Fichero(argv[1]);
semilla = atoi(argv[2]);

srand(semilla);

vector_gredy = gredy();
valor_gredy = funcion_Objetivo(vector_gredy);

cout << "El vector gredy es: " << endl;
imprimeVector(vector_gredy); cout << endl;
cout << "El valor del vector gredy es: " << valor_gredy << endl;


delete vector_gredy;

}
