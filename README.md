# TFG-AlgoritmosFCA
Trabajo de Fin de Grado en Ingeniería Informática y Matemáticas en la Universidad de Granada para el Estudio Experimental de Algoritmos de Cálculo de Retículos en el Análisis Formal de Conceptos.

En este reporitorio se encuentran el código original utilizado tanto para realizar la memoria como los experimentos y gráficos de mi TFG en Análisis Formal de Conceptos.

En la memoria revisamos primero algunos conceptos formales del FCA, revisamos los algoritmos desde un punto de vista teórico y comentamos los resultados de la experimentación.

La carpeta code contiene todo el código y materalia necesario para realizar los experimentos. 
Estos experimentos se pueden automatizar mediante el script de bash Experimentación.sh .
Si se desea, también se pueden probar los algoritmos de forma manual.
El archivo makefile compila todos los ficheros.

Hay dos formas de ejecutar el programa:
- Generando un dataset artificial introduciendo en la línea de comandos como parámetros el número de objetos, número de atributos y número de atributos por objeto
	$ ./bin/main 50 100 4 (crearía un contexto artifical con |G|=50 |M|=100 y |g'|=4, y ejecutaría los algoritmos sobre este contexto)
- Usando un conjunto de datos existente en un archivo .csv (con '1' y ',')
	$ ./bin/main /datasets/real-datasets/sponges.csv
