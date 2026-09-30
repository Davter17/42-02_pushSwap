# Push Swap

Implementacion en C del algoritmo push_swap de 42 School. Ordena una pila de numeros enteros usando dos pilas (A y B) con un conjunto limitado de operaciones, buscando el minimo numero de instrucciones.

## Algoritmo

Usa el **algoritmo de Turk** - un enfoque optimizado que consigue conteos de instrucciones casi optimos:
- **100 numeros**: ~600-700 instrucciones
- **500 numeros**: ~5500-6500 instrucciones

## Compilacion

```bash
make
```

Esto compila el binario `push_swap`. Requiere `cc` (compilador de C).

## Uso

```bash
./push_swap 4 67 3 87 70 15 100 2 69 1
```

Muestra la lista de instrucciones para ordenar los numeros.

## Tester Visual

Se incluye un visualizador web interactivo en la carpeta `tester/`.

### Instalacion

```bash
cd tester
npm install
npm run dev
```

Abre http://localhost:3000 en tu navegador.

### Caracteristicas

- **Visualizacion de barras**: Cada numero se muestra como una barra horizontal proporcional a su rango, formando una piramide al ordenarse
- **Velocidad ajustable**: Desde instantaneo (todos los pasos a la vez) hasta animacion lenta paso a paso
- **Tamano dinamico**: Las barras se redimensionan automaticamente segun el numero de elementos (1px para 500, 8px para 1)
- **Generacion aleatoria**: Genera 100 o 500 numeros aleatorios
- **Estadisticas en vivo**: Sigue el paso actual y el total de movimientos

## Operaciones

| Instruccion | Descripcion |
|-------------|-------------|
| `sa` | Intercambia los dos elementos superiores de la pila A |
| `sb` | Intercambia los dos elementos superiores de la pila B |
| `ss` | `sa` y `sb` al mismo tiempo |
| `pa` | Pasa el elemento superior de B a A |
| `pb` | Pasa el elemento superior de A a B |
| `ra` | Rota la pila A (desplaza hacia arriba) |
| `rb` | Rota la pila B (desplaza hacia arriba) |
| `rr` | `ra` y `rb` al mismo tiempo |
| `rra` | Rota inversa de la pila A (desplaza hacia abajo) |
| `rrb` | Rota inversa de la pila B (desplaza hacia abajo) |
| `rrr` | `rra` y `rrb` al mismo tiempo |

## Limpieza

```bash
make clean    # Elimina archivos objeto
make fclean   # Elimina binario y archivos objeto
make re       # Recompila
```
