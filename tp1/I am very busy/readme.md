## Explicación de mi solución aplicando algoritmos Golosos

La idea detrás de este problema es ver la aplicación de la **técnica de diseño de algoritmos** llamada **algoritmos golosos** a un problema de optimización, esta técnica consiste en que en cada paso del algoritmo se tiene que elegir la opción que genera el **mejor resultado** para ese momento, sin tener en cuenta lo que pueda ocurrir o lo que esa decisión pueda generar más adelante.

Primero, realizamos la **entrada de datos**, luego **ordenamos el arreglo de actividades** con repecto a el momento en el que la actividad termina de menor a mayor, luego aplicamos el algoritmo **goloso** que consiste en elegir la **próxima actividad que se pueda realizar que termine lo antes posible**, esto según las demostraciones vistas en clase es un **algoritmo óptimo**, es decir genera una **solución válida y siempre es la mejor solución**.

Esto se puede lograr simplemente con **recorrer el arreglo de actividades** y elegir la **próxima actividad cuyo tiempo de finalización sea menor o igual a la actividad actual** que se está recorriendo es decir según la definición del problema la próxima actividad que se pueda realizar.