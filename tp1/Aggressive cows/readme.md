## Explicación de mi solución

Primero, realizamos la **entrada de datos**, luego **ordenamos el arreglo de posiciones** de establos de menor a mayor, luego aplicamos el algoritmo de **busqueda binaria** a la máxima distancia mínima entre dos vacas.

La **implementación que realicé** es algo así, **si para una** determinada **distancia mínima es posible colocar a todas las vacas en un establo**, entonces probamos con una **distancia mínima mas grande** porque estamos buscando la máxima distancia mínima, en cambio **si no entraron todas** las vacas en un establo para esa distancia mínima tenemos que **probar una distancia más chica**, esto es simplemente **aplicar búsqueda binaria a la máxima distancia mínima**. 

Ahora, el ejercicio tiene una **última vuelta de tuerca** y es que la **complejidad** del algoritmo **de búsqueda binaria es mayor a log(n) si se empieza la búsqueda por un elemento que no sea el elemento del medio**, por lo tanto hay que entender cual seria el **elemento del medio en el contexto de este problema**. Entonces el elemento del medio equivale a la **media entre la máxima posición de un establo y la mínima posición de un establo**.