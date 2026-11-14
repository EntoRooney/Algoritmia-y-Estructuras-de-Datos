# Pontificia Universidad Católica del Perú

## Algoritmia y Estructura de Datos

**Práctica de entrenamiento (tipo B)**

- **Duración sugerida:** 50 minutos.

### Indicaciones generales

- No puede utilizar apuntes, solo hojas sueltas en blanco.
- En cada función debe incluir, a modo de comentario, la forma de solución que utiliza. De no incluirse, pierde el derecho a reclamo en esa parte.
- Solo se permite `iostream`, `iomanip`, `climits`, `cstring`, `cmath`. No se permiten variables globales ni `string`.
- Si la implementación es diferente a la estrategia indicada, la pregunta no será corregida.

---

## Pregunta 1 (10 puntos)

Se realizó la maratón «Lima 42K» y se quiere medir qué tan desordenada fue la llegada. Cada corredor tiene un dorsal numerado según su orden de inscripción. Se tiene el arreglo con los dorsales **en el orden en que cruzaron la meta**.

Un **adelantamiento** es un par de corredores (posiciones `i < j` en el arreglo de llegada) tal que `dorsal[i] > dorsal[j]`: llegó antes uno con dorsal mayor que otro con dorsal menor.

### Ejemplo

```text
Dorsales en orden de llegada: 3 1 4 2
Adelantamientos: 3
Pares: (3,1), (3,2), (4,2)
Dorsales ordenados: 1 2 3 4
```

### a) (7 puntos)

Desarrolle un programa en C++ que, utilizando la estrategia de **divide y vencerás (recursivo)**, calcule el número total de adelantamientos con complejidad **O(n log n)**.

Los dorsales deben quedar ordenados de menor a mayor al terminar.

Para que su respuesta sea válida **no puede usar dos `for` anidados** para contar los pares.

### b) (3 puntos)

Un adelantamiento es **fuerte** si `dorsal[i] > 2 * dorsal[j]`, con `i < j`.

Calcule también el número de adelantamientos fuertes, manteniendo la complejidad **O(n log n)**, en la misma estrategia de divide y vencerás y sin una segunda función que recorra todos los pares.

### Salida esperada

Para cada caso de prueba, el programa debe imprimir:

```text
Adelantamientos: X
Adelantamientos fuertes: Y
Dorsales ordenados: ...
```

### Casos de prueba

| # | Dorsales en orden de llegada | Adelantamientos | Fuertes | Dorsales ordenados |
|---:|---|---:|---:|---|
| 1 | `3 1 4 2` | 3 | 1 | `1 2 3 4` |
| 2 | `1 2 3 4 5` | 0 | 0 | `1 2 3 4 5` |
| 3 | `5 4 3 2 1` | 10 | 4 | `1 2 3 4 5` |
| 4 | `7` | 0 | 0 | `7` |
| 5 | `4 3 3 1` | 5 | 3 | `1 3 3 4` |
| 6 | `8 3 6 1 9 2` | 9 | 7 | `1 2 3 6 8 9` |

---

## Análisis de los casos de prueba

- **Caso 2:** el arreglo ya está ordenado, por lo que debe dar 0.
- **Caso 3:** el máximo posible, `n(n-1)/2`.
- **Caso 4:** un solo elemento, que prueba el caso base.
- **Caso 5:** los empates. Un par igual **no** es adelantamiento, y por eso el `<=` en la comparación importa.
- **Caso 6:** un arreglo de tamaño par no potencia de 2, para ver que las mitades queden bien.
