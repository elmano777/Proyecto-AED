# Proyecto Reservaciones AED
## Estructura de Datos: Treap (Heap + Árbol Binario)

### Integrantes:
- Rolandito
- Tamy Flores
- D

## Descripción del Proyecto

Este proyecto implementa un **sistema de gestión de reservas** utilizando la estructura de datos **Treap** (Tree + Heap). Un Treap combina las propiedades de un árbol binario de búsqueda (BST) con las de un heap, donde cada nodo tiene una clave (key) y una prioridad (priority).

### Arquitectura del Sistema

- **Backend**: C++ con Crow Framework (API REST)
- **Frontend**: Angular (repositorio separado: [cpp_front](https://github.com/elmano777/cpp_front.git))
- **Estructura de Datos**: Treap para almacenamiento eficiente de reservas

## Funcionalidades Principales

### 1. **Agregar Reserva** (`POST /reservations`)
- Inserta una nueva reserva en el Treap
- Genera automáticamente una prioridad aleatoria
- Clave única: `datetime_clientName`
- **Endpoint**: `POST http://localhost:8081/reservations`
- **Body**: `{"datetime": "2024-01-15 14:30", "client": "Juan Pérez"}`

### 2. **Eliminar Reserva** (`DELETE /reservations/{key}`)
- Elimina una reserva específica del Treap
- Reestructura el árbol manteniendo las propiedades del Treap
- **Endpoint**: `DELETE http://localhost:8081/reservations/{key}`

### 3. **Mostrar Estructura del Árbol** (`GET /reserva/tree`)
- Devuelve la estructura completa del Treap en formato JSON
- Útil para visualización en el frontend
- **Endpoint**: `GET http://localhost:8081/reserva/tree`

### 4. **Listar Reservas** (`GET /reservations`)
- Obtiene todas las reservas ordenadas (inorder)
- Ordenamiento de menor a mayor por fecha/hora
- **Endpoint**: `GET http://localhost:8081/reservations`

## Estructura del Proyecto

```
proyecto_cpp/
├── main.cpp                          # Punto de entrada, configuración Crow
├── CMakeLists.txt                    # Configuración de compilación
├── src/
│   ├── models/
│   │   ├── Treap.h/.cpp              # Implementación del Treap
│   │   └── TreapNode.h/.cpp          # Nodo del Treap
│   ├── controllers/
│   │   └── ReservationController.h/.cpp  # Lógica de negocio
│   └── routes/
│       └── reservationRoutes.h/.cpp  # Definición de endpoints REST
└── README.md
```

## Cómo Ejecutar el Proyecto

### Prerrequisitos
- CMake 3.31 o superior
- Compilador C++ compatible con C++20
- Crow Framework
- OpenSSL
- ZLIB

### En Visual Studio Code

1. **Instalar extensiones**:
   - CMake Tools
   - C/C++ Extension Pack

2. **Configurar y compilar**:
   ```bash
   # En la terminal de VSCode
   mkdir build
   cd build
   cmake ..
   make
   ```

3. **Ejecutar**:
   ```bash
   ./proyecto_cpp
   ```

### En CLion

1. **Abrir el proyecto** en CLion
2. **Configurar CMake** automáticamente
3. **Build y Run** con el botón ▶️

### En Terminal

```bash
# Crear directorio de build
mkdir build && cd build

# Configurar con CMake
cmake ..

# Compilar
make

# Ejecutar
./proyecto_cpp
```

## API Endpoints

| Método | Endpoint | Descripción | Body |
|--------|----------|-------------|------|
| `POST` | `/reservations` | Crear nueva reserva | `{"datetime": "2024-01-15 14:30", "client": "Juan Pérez"}` |
| `GET` | `/reservations` | Listar todas las reservas | - |
| `DELETE` | `/reservations/{key}` | Eliminar reserva específica | - |
| `GET` | `/reserva/tree` | Obtener estructura del Treap | - |

## Ejemplos de Uso

### Crear una Reserva
```bash
curl -X POST http://localhost:8081/reservations \
  -H "Content-Type: application/json" \
  -d '{"datetime": "2024-01-15 14:30", "client": "Juan Pérez"}'
```

### Listar Reservas
```bash
curl http://localhost:8081/reservations
```

### Eliminar Reserva
```bash
curl -X DELETE "http://localhost:8081/reservations/2024-01-15%2014:30_Juan%20P%C3%A9rez"
```

### Ver Estructura del Árbol
```bash
curl http://localhost:8081/reserva/tree
```

## Características del Treap

### Ventajas
- **Búsqueda eficiente**: O(log n) promedio
- **Inserción eficiente**: O(log n) promedio
- **Eliminación eficiente**: O(log n) promedio
- **Auto-balanceado**: Las prioridades mantienen el árbol balanceado

### Propiedades
- **Propiedad BST**: Para cualquier nodo, todos los nodos del subárbol izquierdo tienen claves menores
- **Propiedad Heap**: Para cualquier nodo, su prioridad es mayor que la de sus hijos

## Frontend

El frontend está desarrollado en Angular y se encuentra en el repositorio separado:
- **URL**: https://github.com/elmano777/cpp_front.git
- **Tecnología**: Angular 19.2.13
- **Puerto**: 4200 (por defecto)

### Ejecutar Frontend
```bash
# Clonar el repositorio del frontend
git clone https://github.com/elmano777/cpp_front.git
cd cpp_front

# Instalar dependencias
npm install

# Ejecutar servidor de desarrollo
ng serve
```

## Notas Técnicas

- **Puerto del Backend**: 8081
- **CORS**: Habilitado
- **Formato de Clave**: `datetime_clientName`
- **Prioridades**: Generadas aleatoriamente (1-1000)
- **Ordenamiento**: Las reservas se ordenan cronológicamente usando inorder traversal
