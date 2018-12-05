#!/bin/bash


#Compilacion:
#g++ Genetico_posicion.cpp -o genetico_1
#g++ Genetico_PMX.cpp -o genetico_2
#g++ Genetico_posicion_estacionario.cpp -o genetico_3
#g++ Genetico_PMX_estacionario.cpp -o genetico_4

# Parametros:
# 1º Ruta de archivo
# 2º Semilla aleatoria
# 3º Numero de evaulaciones
# 4º Tamaño de la poblacion
# 5º Probabilidad de cruce
# 6º Probabilidad de mutacion
# Parametros:     1º          2º   3º   4º 5º   6º



./genetico_1 data/chr20b.dat  777 50000 50 0.7 0.001 >> Archivo_1
./genetico_1 data/chr22a.dat  777 50000 50 0.7 0.001 >> Archivo_1
./genetico_1 data/els19.dat   777 50000 50 0.7 0.001 >> Archivo_1
./genetico_1 data/esc32b.dat  777 50000 50 0.7 0.001 >> Archivo_1
./genetico_1 data/kra30b.dat  777 50000 50 0.7 0.001 >> Archivo_1
./genetico_1 data/lipa90b.dat 777 50000 50 0.7 0.001 >> Archivo_1
./genetico_1 data/nug25.dat   777 50000 50 0.7 0.001 >> Archivo_1
./genetico_1 data/sko56.dat   777 50000 50 0.7 0.001 >> Archivo_1
./genetico_1 data/sko64.dat   777 50000 50 0.7 0.001 >> Archivo_1
./genetico_1 data/sko72.dat   777 50000 50 0.7 0.001 >> Archivo_1
./genetico_1 data/sko100a.dat 777 50000 50 0.7 0.001 >> Archivo_1
./genetico_1 data/sko100b.dat 777 50000 50 0.7 0.001 >> Archivo_1
./genetico_1 data/sko100c.dat 777 50000 50 0.7 0.001 >> Archivo_1
./genetico_1 data/sko100d.dat 777 50000 50 0.7 0.001 >> Archivo_1
./genetico_1 data/sko100e.dat 777 50000 50 0.7 0.001 >> Archivo_1
./genetico_1 data/tai30b.dat  777 50000 50 0.7 0.001 >> Archivo_1
./genetico_1 data/tai50b.dat  777 50000 50 0.7 0.001 >> Archivo_1
./genetico_1 data/tai60a.dat  777 50000 50 0.7 0.001 >> Archivo_1
./genetico_1 data/tai256c.dat 777 50000 50 0.7 0.001 >> Archivo_1
./genetico_1 data/tho150.dat  777 50000 50 0.7 0.001 >> Archivo_1

./genetico_2 data/chr20b.dat  777 50000 50 0.7 0.001 >> Archivo_2
./genetico_2 data/chr22a.dat  777 50000 50 0.7 0.001 >> Archivo_2
./genetico_2 data/els19.dat   777 50000 50 0.7 0.001 >> Archivo_2
./genetico_2 data/esc32b.dat  777 50000 50 0.7 0.001 >> Archivo_2
./genetico_2 data/kra30b.dat  777 50000 50 0.7 0.001 >> Archivo_2
./genetico_2 data/lipa90b.dat 777 50000 50 0.7 0.001 >> Archivo_2
./genetico_2 data/nug25.dat   777 50000 50 0.7 0.001 >> Archivo_2
./genetico_2 data/sko56.dat   777 50000 50 0.7 0.001 >> Archivo_2
./genetico_2 data/sko64.dat   777 50000 50 0.7 0.001 >> Archivo_2
./genetico_2 data/sko72.dat   777 50000 50 0.7 0.001 >> Archivo_2
./genetico_2 data/sko100a.dat 777 50000 50 0.7 0.001 >> Archivo_2
./genetico_2 data/sko100b.dat 777 50000 50 0.7 0.001 >> Archivo_2
./genetico_2 data/sko100c.dat 777 50000 50 0.7 0.001 >> Archivo_2
./genetico_2 data/sko100d.dat 777 50000 50 0.7 0.001 >> Archivo_2
./genetico_2 data/sko100e.dat 777 50000 50 0.7 0.001 >> Archivo_2
./genetico_2 data/tai30b.dat  777 50000 50 0.7 0.001 >> Archivo_2
./genetico_2 data/tai50b.dat  777 50000 50 0.7 0.001 >> Archivo_2
./genetico_2 data/tai60a.dat  777 50000 50 0.7 0.001 >> Archivo_2
./genetico_2 data/tai256c.dat 777 50000 50 0.7 0.001 >> Archivo_2
./genetico_2 data/tho150.dat  777 50000 50 0.7 0.001 >> Archivo_2

./genetico_3 data/chr20b.dat  777 50000 50 0.7 0.001 >> Archivo_3
./genetico_3 data/chr22a.dat  777 50000 50 0.7 0.001 >> Archivo_3
./genetico_3 data/els19.dat   777 50000 50 0.7 0.001 >> Archivo_3
./genetico_3 data/esc32b.dat  777 50000 50 0.7 0.001 >> Archivo_3
./genetico_3 data/kra30b.dat  777 50000 50 0.7 0.001 >> Archivo_3
./genetico_3 data/lipa90b.dat 777 50000 50 0.7 0.001 >> Archivo_3
./genetico_3 data/nug25.dat   777 50000 50 0.7 0.001 >> Archivo_3
./genetico_3 data/sko56.dat   777 50000 50 0.7 0.001 >> Archivo_3
./genetico_3 data/sko64.dat   777 50000 50 0.7 0.001 >> Archivo_3
./genetico_3 data/sko72.dat   777 50000 50 0.7 0.001 >> Archivo_3
./genetico_3 data/sko100a.dat 777 50000 50 0.7 0.001 >> Archivo_3
./genetico_3 data/sko100b.dat 777 50000 50 0.7 0.001 >> Archivo_3
./genetico_3 data/sko100c.dat 777 50000 50 0.7 0.001 >> Archivo_3
./genetico_3 data/sko100d.dat 777 50000 50 0.7 0.001 >> Archivo_3
./genetico_3 data/sko100e.dat 777 50000 50 0.7 0.001 >> Archivo_3
./genetico_3 data/tai30b.dat  777 50000 50 0.7 0.001 >> Archivo_3
./genetico_3 data/tai50b.dat  777 50000 50 0.7 0.001 >> Archivo_3
./genetico_3 data/tai60a.dat  777 50000 50 0.7 0.001 >> Archivo_3
./genetico_3 data/tai256c.dat 777 50000 50 0.7 0.001 >> Archivo_3
./genetico_3 data/tho150.dat  777 50000 50 0.7 0.001 >> Archivo_3

./genetico_4 data/chr20b.dat  777 50000 50 0.7 0.001 >> Archivo_4
./genetico_4 data/chr22a.dat  777 50000 50 0.7 0.001 >> Archivo_4
./genetico_4 data/els19.dat   777 50000 50 0.7 0.001 >> Archivo_4
./genetico_4 data/esc32b.dat  777 50000 50 0.7 0.001 >> Archivo_4
./genetico_4 data/kra30b.dat  777 50000 50 0.7 0.001 >> Archivo_4
./genetico_4 data/lipa90b.dat 777 50000 50 0.7 0.001 >> Archivo_4
./genetico_4 data/nug25.dat   777 50000 50 0.7 0.001 >> Archivo_4
./genetico_4 data/sko56.dat   777 50000 50 0.7 0.001 >> Archivo_4
./genetico_4 data/sko64.dat   777 50000 50 0.7 0.001 >> Archivo_4
./genetico_4 data/sko72.dat   777 50000 50 0.7 0.001 >> Archivo_4
./genetico_4 data/sko100a.dat 777 50000 50 0.7 0.001 >> Archivo_4
./genetico_4 data/sko100b.dat 777 50000 50 0.7 0.001 >> Archivo_4
./genetico_4 data/sko100c.dat 777 50000 50 0.7 0.001 >> Archivo_4
./genetico_4 data/sko100d.dat 777 50000 50 0.7 0.001 >> Archivo_4
./genetico_4 data/sko100e.dat 777 50000 50 0.7 0.001 >> Archivo_4
./genetico_4 data/tai30b.dat  777 50000 50 0.7 0.001 >> Archivo_4
./genetico_4 data/tai50b.dat  777 50000 50 0.7 0.001 >> Archivo_4
./genetico_4 data/tai60a.dat  777 50000 50 0.7 0.001 >> Archivo_4
./genetico_4 data/tai256c.dat 777 50000 50 0.7 0.001 >> Archivo_4
./genetico_4 data/tho150.dat  777 50000 50 0.7 0.001 >> Archivo_4


