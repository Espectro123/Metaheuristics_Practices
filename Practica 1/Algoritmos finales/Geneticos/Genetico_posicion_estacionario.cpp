#include <iostream>
#include <utility>
#include <fstream>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <ctime>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>

using namespace std;


/***** GENERADOR DE NUMEROS PSEUDOALETORIOS *****/

/* used in random number generator below */
#define MASK 2147483647
#define PRIME 65539
#define SCALE 0.4656612875e-9
int Seed =  77337733;
/*******************************************************************/
/*  Rand genera un numero real pseudoaleatorio entre 0 y 1,        */
/*  excluyendo el 1.						   */
/*  Randint genera un numero entero entre low y high, ambos 	   */
/*  incluidos.	   						   */
/*  Randfloat genera un numero real entre low y high, incluido low */
/*  y no incluido high                                             */
/*******************************************************************/

#define Rand()  (( Seed = ( (Seed * PRIME) & MASK) ) * SCALE )

#define Randint(low,high) ( (int) (low + (high-(low)+1) * Rand()))

#define Randfloat(low,high) ( (low + (high-(low))*Rand()))




//Variables glovales del algoritmo
/************************************************************************************************************************************************/
int** matriz_flujo; // Matriz de flujo
int** matriz_localizacion; //Matriz de localizaciones
unsigned short TAM_MATRICES; //Tama�o de las matrices. Normalmente son iguales. Deben leerse de un fichero
/************************************************************************************************************************************************/
int contador_evaulaciones = 0;
void destructor(){

	//Destruyo la memoria dinamica
	for(int i = 0; i < TAM_MATRICES; i++){
		delete[] matriz_flujo[i];
		delete[] matriz_localizacion[i];
	}
	delete[] matriz_flujo;
	delete[] matriz_localizacion;

}

class Individuo{

	private:

		unsigned short tam; //Determina el tama�o del vector solucion
		unsigned short* cromosoma; //Vector solucion del individuo
		unsigned short valor; // Valor del vector solucion
		bool evaluado; //Si esta a false el individuo no ha sido evaluado, por lo que  tiene que ser evaluado

		//Funcion objetivo del problema.
		int funcion_Objetivo(unsigned short* telomero){

			unsigned short resultado = 0;
			int contador = 0;
			int indice = 0;

			for(int i = 0; i < TAM_MATRICES; i++){
				for(int j = 0; j < TAM_MATRICES; j++){

					resultado += matriz_flujo[i][j] * matriz_localizacion[telomero[i]][telomero[j]];

				}
			}


			return resultado;

		}


		int checkMove(unsigned short* vector,int r,int s){

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

	public:

		Individuo(){

			tam = TAM_MATRICES;
			cromosoma = new unsigned short[TAM_MATRICES];
			valor = 0;
			evaluado = false;

		}

		~Individuo(){
			delete[] cromosoma;
		}

		//Constructor que inicializa el individuo con el tama�o del problema
		Individuo(unsigned short* cromosoma, unsigned int tam){

			this->tam = tam;

			this->cromosoma = new unsigned short[this->tam];

			for(int i = 0; i < this->tam; i++){

				this->cromosoma[i] = cromosoma[i];

			}

			evaluado = false;
			valor = 0;

		}

		void setInicio(unsigned short* cromosoma, unsigned short tam){

			this->tam = tam;
			this->cromosoma = new unsigned short[this->tam];

			for(int i = 0; i < this->tam; i++){

				this->cromosoma[i] = cromosoma[i];

			}

			evaluado = false;
			valor = 0;


		}

		void swap(Individuo cambio){


			unsigned short valor_aux = this->valor;
			unsigned short* adn = new unsigned short[this->tam];
			bool evaluado_aux = this->evaluado;
			for(int i = 0; i < this->tam; i++){

				adn[i] = this->cromosoma[i];

			}


			this->valor = cambio.getValor();
			this->evaluado = cambio.getEstado();
			for(int i = 0; i < this->tam; i++){

				this->cromosoma[i] = cambio.getPermutacion(i);

			}

			cambio.setValor(valor_aux);
			cambio.setCromosoma(adn);
			cambio.setEstado(evaluado_aux);


		}

		//Metodo que evalua el cromosoma (vector de permtaciones)
		void evaluar(){

			if(!evaluado){
				contador_evaulaciones++;
				valor = funcion_Objetivo(cromosoma);
				evaluado = true;

			}

		}

		//Devuelve true si el que llama al metodo es mejor que el parametro
		bool torneo(Individuo individuo){

			bool respuesta = false;

			if(valor <= individuo.getValor()) respuesta = true;


			return respuesta;
		}

		void setValor(unsigned short valor_aux){

			this->valor = valor_aux;

		}

		void setCromosoma(unsigned short* cromosoma){

			for(int i = 0; i < this->tam; i++){

				this->cromosoma[i] = cromosoma[i];

			}

		}

		void setEstado(bool estado){

			this->evaluado = estado;

		}
		//Devuelve el valor del vector permtacion del individuo. Calidad de la solucion.
		unsigned short getValor(){

			return valor;

		}

		void setPermutacion(int coordenada,unsigned short valor){

			this->cromosoma[coordenada] = valor;

		}

		unsigned short getValorConst()const{

			return valor;

		}

		//Devuele true si necesita ser evaluado de nuevo y false en caso contrario
		bool getEstado(){

			return evaluado;

		}

		bool getEstadoConst()const{

			return evaluado;

		}

		//Obtiene el valor de una posicion del vector solucion
		unsigned short getPermutacion(int posicion){

			return cromosoma[posicion];

		}

		unsigned short getPermutacionConst(int posicion)const{

			return cromosoma[posicion];

		}

		//Devuelve el puntero al vector solucion
		unsigned short* getCromosoma(){

			return cromosoma;

		}

		unsigned short* getCromosomaConst()const{

			return cromosoma;

		}

		//Obtiene el tama�o del vector solucuion
		unsigned short getTam(){

			return tam;

		}

		unsigned short getTamConst()const{

			return tam;

		}

		//Sobrecarga de igualda de operadores
		void operator=(const Individuo &hijo){

			tam       = hijo.getTamConst();
			this->valor     = hijo.getValorConst();
			this->evaluado  = hijo.getEstadoConst();

			for(int i = 0; i < tam; i++){

				this->cromosoma[i] = hijo.getPermutacionConst(i);

			}

		}

		//Cruza dos individuos aleatoriamente
		//El parametro es un padre. El objeto que llama al metodo es otro.
		//El metodo devulve el cromosoma del hijo.
		unsigned short* cruce_aleatorio(Individuo &individuo){

			Individuo descendencia;
			unsigned short* cromosoma_descendencia = new unsigned short[TAM_MATRICES];
			vector<unsigned short> vector_de_repetidos;
			vector<unsigned short> restos;
			bool existe = false;
			bool existe_2 = false;
			int aleatorio = 0;

			//Rellena el vector solucion con los repetidos de ambos vector_de_repetidos
			//Crea el vector de restos.
			for(int i = 0; i < TAM_MATRICES; i++){

				cromosoma_descendencia[i] = TAM_MATRICES + 1;

				//Introduzco la coincidencia en el vector descendencia
				if(individuo.getPermutacion(i) == this->cromosoma[i]){

					cromosoma_descendencia[i] = this->cromosoma[i];

				}else{

					for(int j = 0; j < restos.size(); j++){

						if(this->cromosoma[i] == restos[j]){
							existe = true;
						}

						if(individuo.getPermutacion(i) == restos[j]){
							existe_2 = true;
						}

					}

					if(!existe) restos.push_back(cromosoma[i]);
					if(!existe_2) restos.push_back(individuo.getPermutacion(i));
					existe = false;
					existe_2 = false;
				}

			}

			for(int j = 0; j < TAM_MATRICES; j++){

				//No ha sido rellenado
				if(cromosoma_descendencia[j] == TAM_MATRICES + 1){

					aleatorio = rand()%restos.size(); // Obtengo una posicion aleatoria del vector
					cromosoma_descendencia[j] = restos[aleatorio]; // asigno dicha posicion
					restos.erase(restos.begin()+aleatorio); // Borro el elemento usado

				}

			}



			return cromosoma_descendencia;

		}

		//Cruza dos individuos siguiendo el algoritmo POX de las diapositivas
		//El parametro es un padre. El objeto que llama al metodo es otro.
		//tam_subcadena define el tama�o de la subcadena. Por defecto su valor es 8.
		//cuanto mas peque�o sea mas grande sera la subcadena
		unsigned short* cruce_PMX(Individuo &individuo,int tam_subcadena = 8){

			int subcadena = tam/tam_subcadena; //Tama�o de la subcadena

			int mitad_subcadena = subcadena /2; //Mitad del tama�o de la subcadena. Auxiliar.
			int mitad_tam = tam/2; // Mitad del tama�o del vector. Auxiliar

			int primer_trozo = ((mitad_tam) - (mitad_subcadena));
			int segundo_trozo = ((mitad_tam) + (mitad_subcadena));

			short unsigned* hijo = new unsigned short[tam]; // Cromosoma del futuro hijo
			int vector_auxiliar[subcadena];

			bool bandera = false;


			//Primera mitad antes de la subcadena central
			for(int i = 0; i < primer_trozo; i++){

				for(int j = primer_trozo; j < segundo_trozo && !bandera; j++){

					if(cromosoma[i] == individuo.getPermutacion(j)){

						hijo[i] = cromosoma[j];
						bandera = true;

					}

				}

				if(!bandera) hijo[i] = cromosoma[i];
				else bandera = false;

			}

			//Cadena central
			for(int i = primer_trozo; i < segundo_trozo; i++){

				hijo[i] = individuo.getPermutacion(i);

			}


			//Segunda mitad despues de la subcadena central
			for(int i = segundo_trozo; i < tam; i++){

				for(int j = primer_trozo; j < segundo_trozo && !bandera; j++){

					if(cromosoma[i] == individuo.getPermutacion(j)){

						hijo[i] = cromosoma[j];
						bandera = true;

					}

				}

				if(!bandera) hijo[i] = cromosoma[i];
				else bandera = false;

			}

			return hijo;
		}

		//Se aplica sobre el propio objeto. Provoca una mutacion con un porcentage de posibiidad del 0,1%
		void mutar(int gen_a_mutar){

			int aleatorio = Randint(0,TAM_MATRICES-1);
			unsigned short aux = 0;

				aux = this->cromosoma[gen_a_mutar];
				cromosoma[gen_a_mutar] = cromosoma[aleatorio];
				cromosoma[aleatorio] = aux;
				evaluado = false;

		}

};


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

unsigned short* generar_solucion_aleatoria(){

	unsigned short* solucion;
	solucion = new unsigned short[TAM_MATRICES];

	vector<unsigned short> auxiliar;

	unsigned short contador = 0;
	unsigned short aleatorio = 0;

	//Creo el vector por defecto
	for(unsigned short i = 0; i < TAM_MATRICES; i++){

			auxiliar.push_back(i);
			contador++;

	}

	//Probar este algoritmo
	for(unsigned short i = 0; i < TAM_MATRICES; i++){

		aleatorio = rand()%contador; //Obtengo un numero aleatorio entre 0 y contador

		solucion[i] = auxiliar[aleatorio]; //Asigno al vector solucion un valor aleatorio.

		auxiliar.erase(auxiliar.begin()+aleatorio); //Borro la posicion usada

		contador--; //Reduzco el intervalor para generar el numero aleatorio
	}


	return solucion;
}

//Funciona que ordena de mejor a peor los individuos de una poblacion
void ordenar_poblacion(vector<Individuo> &poblacion,unsigned short tam){


	Individuo aux;

		for(int i = 0; i < tam; i++){
			for(int j = 0; j < tam; j++){

				if(poblacion[i].getValor() < poblacion[j].getValor() && i != j){

					aux = poblacion[i];
					poblacion[i] = poblacion[j];
					poblacion[j] = aux;

				}
			}
		}

}

/*

Main del programa
Argumentos:
1º archivo
2º Semilla
3º Numero de iteraciones
4º Tamaño de poblacion
5º probabilidad de cruce
*/

int main(int argc, char** argv){

unsigned t0, t1;


if(argc < 7){

	cout << "Se necesitan mas argumentos. 4 Argumentos necesarios. Orden: " << endl;
	cout << "1º Archivo" << endl;
	cout << "2º Semilla aleatoria" << endl;
	cout << "Numero de iteraciones" << endl;
	cout << "Tamaño de poblacion" << endl;
	cout << "Probabilidad de cruce" << endl;
	cout << "Probabilidad de mutacion" << endl;
	exit(-1);

}

lectura_Fichero(argv[1]);

t0 = clock();

double time;
int semilla = atoi(argv[2]);
int numero_de_iteraciones = atoi(argv[3]);
int tamanio_poblacion = atoi(argv[4]);
float probabilidad_de_cruce = atof(argv[5]);
float probabilidad_de_mutacion = atof(argv[6]);

int numero_de_cruces = probabilidad_de_cruce * (tamanio_poblacion/2); // Numero de cruces por poblacion
int numero_de_mutaciones = (TAM_MATRICES * tamanio_poblacion) * probabilidad_de_mutacion; //Numero de mutaciones por poblacion
int hijo_aleatorio = 0;
int gen_aleatorio = 0;
int contador = 0;
bool bandera = true;
 //Igualo al tamaño de la poblacion ya que hare ese numero de evaulaciones antes del for
Individuo Mejor_acutal;

//Creo una pobalcion de individuos
vector<Individuo> poblacion;
poblacion.reserve(tamanio_poblacion);

vector<Individuo> hijos;
hijos.reserve(2);

//Creo una poblacion de soluciones aleatorias del problemas y las evaluo.
for(int i = 0; i < tamanio_poblacion; i++){

	unsigned short* cromosoma;

	srand(semilla+(i*3));

	cromosoma = generar_solucion_aleatoria();

	poblacion[i].setInicio(cromosoma,TAM_MATRICES);
	poblacion[i].evaluar();

}

ordenar_poblacion(poblacion,tamanio_poblacion);
Mejor_acutal = poblacion[0];



//Blucle principal. Repite el modelo estacionario.
//Modelo estacionario
//Operador de posicion (aleatorio) empleado
//Numero de iteraciones: 50.000
//Probabilidad de cruce: 0.7 -> 70% de la poblacion
//Probabilidad de mutacion: 0.001

for(int i = 0; i < numero_de_iteraciones && bandera; i++){



	for(int j = 0; j < 2; j++){

		unsigned short* adn;
		adn = poblacion[j].cruce_aleatorio(poblacion[j+1]); // cruzo los dos mejores padres
		hijos[j].setInicio(adn,TAM_MATRICES); // Creo el nuevo hijo

	}



	for(int j = 0; j < numero_de_mutaciones; j++){

		gen_aleatorio = Randint(0,TAM_MATRICES-1);
		hijo_aleatorio = Randint(0,tamanio_poblacion-1);
		if(hijo_aleatorio == 0 || hijo_aleatorio == 1)hijos[hijo_aleatorio].mutar(gen_aleatorio);
    	else poblacion[hijo_aleatorio].mutar(gen_aleatorio);
	}



	//evaluo los nuevos hijos y los sustituyo por los peores padres
	//En el caso de que los hijos sean mejores
	for(int j = 0; j < 2; j++){

		hijos[j].evaluar();
		poblacion[j].evaluar();

		if(hijos[j].getValor() < poblacion[tamanio_poblacion-j-1].getValor()){


			poblacion[tamanio_poblacion-j-1] = hijos[j];


		}

		//Condicion de parada del algoritmo. Parametrizar en el futuro.
	}



	if(contador_evaulaciones >= 50000){
		bandera = false;
	}

	ordenar_poblacion(poblacion,tamanio_poblacion);


}

t1 = clock();

time = (double(t1-t0)/CLOCKS_PER_SEC);

cout << "--------------------------------------------------------------------------------" << endl;
cout << poblacion[0].getValor() << " " << time << endl;
cout << "----------------------------------------------------------------------------------" << endl;

destructor();

}
