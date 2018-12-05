/*
Enrique Casale Linde
kicalin@gmail.com
*/
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

//Destruye la memoria dinamica de las matrices
void destructor(){

    for(int i = 0; i < TAM_MATRICES; i++){

        delete[] matriz_flujo[i];
        delete[] matriz_localizacion[i];

    }

    delete[] matriz_flujo;
    delete[] matriz_localizacion;

}

//Lee el archivo pasado por parametro
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

//Funcion objetivo del problema
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

//Intercambia la permutacion r por la s
void intercambio(int* vector_permutacion,int r, int s){

	int auxiliar = 0;
	auxiliar = vector_permutacion[r];
	vector_permutacion[r] = vector_permutacion[s];
	vector_permutacion[s] = auxiliar;


}

//Implementa la factorizacion. Comprueba si un cambio sera beneficioso
int checkMove(int* vector,int r,int s){

	int ganancia = 0;

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

//Implementa el algoritmo de la busqueda_local
int* busqueda_local(int* vector_permutacion,int iteraciones){

	bool dont_look_this_bits[TAM_MATRICES]; // Mascara de bits

    for(int i = 0; i < TAM_MATRICES; i++){
        dont_look_this_bits[i] = false;
    }

	int comprobar_ganancia = 0;
	bool bandera = false;
    bool bandera_for = true;
    int contador_de_estado = 0;
    int contador_evaulaciones = 0;

		for(int i = 0; i < iteraciones && bandera_for; i++){

			for(int j = 0; j < TAM_MATRICES && bandera_for; j++){

				if(dont_look_this_bits[j] == false){

					bandera = false;

					for(int k = 0; k < TAM_MATRICES; k++){

						comprobar_ganancia = checkMove(vector_permutacion,j,k);
                        			contador_evaulaciones++;

						if(comprobar_ganancia <= 0){
							
							dont_lock_this_bits[j] = true;
							intercambio(vector_permutacion,j,k);
							bandera = true;

						}

					}

					if(!bandera) dont_look_this_bits[j] = true;
					comprobar_ganancia = 0;

				}else{

                    contador_de_estado++;

                }

                if(contador_de_estado == TAM_MATRICES -1 || contador_evaulaciones >= 50000){
                    bandera_for = false;
                }

			}

            contador_de_estado = 0;

		}

        cout << "Se han hecho: " << contador_evaulaciones << endl;

	return vector_permutacion;

}

//Genera un vector permutacion sin repetidos aleatorio
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

//Imprime un vector
void imprimeVector(int* vector){

	for(int i = 0; i < TAM_MATRICES; i++){

		cout << vector[i] << " ";

	}

}


int main(int argc, char** argv){

    //Compruebo que esten todos los parametros
    if(argc < 4){

        cout << "Se necesitan mas argumentos. 3 argumentos necesarios." << endl;
        cout << "1º Archivo" << endl;
        cout << "2º Numero de iteraciones de la busqueda_local" << endl;
        cout << "3º Semilla" << endl;
        exit(-1);

    }

    int* vector_local;
    int valor_local = 0;

    //Leo el archivo
    lectura_Fichero(argv[1]);

    int numero_de_iteraciones = atoi(argv[2]);
    int semilla = atoi(argv[3]);

    //Inicializo la semilla para la funcion rand()
    srand(semilla);

    //Llamo a la busqueda local y obtengo el vector soluciond de la misma.
    //Comienza con un vector aleatorio
    vector_local = busqueda_local(generar_solucion_aleatoria(),numero_de_iteraciones);

    //Obtengo el valor del vector obtenido llamando a la funcion objetivo
    valor_local = funcion_Objetivo(vector_local);

    cout << "El vector local es: " << endl;
    imprimeVector(vector_local); cout << endl;
    cout << "El valor del vector local es: " << valor_local << endl;

    //Borro la memoria dinamica
    delete vector_local;
    destructor();

}
