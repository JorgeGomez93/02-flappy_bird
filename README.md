Descripción detallada de lo que se hizo en cada clase para cada uno de los cambios realizados:

### **1. Implementación del Estado de Pausa (PauseState)**
- **Descripción:** Se agregó un nuevo estado para pausar el juego y reanudarlo cuando el usuario presione la tecla "P".
- **Clases Modificadas:**
  - **PauseState.hpp:** Declaración de la clase `PauseState`, que gestiona el comportamiento del juego en estado de pausa.
  - **PauseState.cpp:** Implementación de la lógica del estado de pausa, incluyendo la detección de la tecla "P" para pausar y reanudar el juego.
  - **Game.cpp:** Integración del nuevo estado de pausa en el flujo principal del juego.
  - **PlayingState.hpp:** Ajustes para permitir la transición al estado de pausa desde el estado de juego.
  - **PlayingState.cpp:** Implementación de la lógica para manejar la transición entre el estado de juego y el estado de pausa.
  - **Makefile:** Inclusión de los nuevos archivos `PauseState.hpp` y `PauseState.cpp` en el proceso de compilación.

### **2. Implementación de Modos de Juego (Normal y Difícil)**
- **Descripción:** Se utilizó el patrón Estrategia para implementar dos modos de juego: Normal y Difícil. Se modificó el menú inicial para permitir la selección de modos y se ajustaron diversas mecánicas en el modo difícil.
- **Clases Modificadas:**
  - **TitleScreenState.cpp:** Se añadió la opción de seleccionar el modo de juego (Normal o Difícil) en el menú inicial.
  - **BaseState.hpp:** Se ajustó la estructura base de los estados para acomodar los cambios de modo de juego.
  - **StateMachine.hpp:** Adaptación de la máquina de estados para manejar la transición entre modos de juego.
  - **StateMachine.cpp:** Implementación de la lógica para cambiar entre los diferentes modos de juego.
  - **PlayingState.hpp:** Se añadió la lógica para diferenciar las mecánicas del modo Normal y Difícil.
  - **PlayingState.cpp:** Implementación de las mecánicas específicas para cada modo de juego.
  - **CountDownState.hpp:** Ajustes para iniciar correctamente el modo de juego seleccionado.
  - **CountDownState.cpp:** Implementación de la lógica de cuenta regresiva para ambos modos de juego.

### **3. Modo Difícil - Movimiento Horizontal del Pájaro**
- **Descripción:** En el modo difícil, se añadió la funcionalidad para mover el pájaro horizontalmente usando las teclas "A" y "D".
- **Clases Modificadas:**
  - **Bird.hpp:** Declaración de nuevas variables y métodos para manejar el movimiento horizontal del pájaro.
  - **Bird.cpp:** Implementación de la lógica que permite mover el pájaro hacia la izquierda y derecha cuando se presionan las teclas "A" y "D".
  - **PlayingState.cpp:** Ajustes en la lógica de juego para habilitar el movimiento horizontal del pájaro en el modo difícil.

### **4. Modo Difícil - Variabilidad en la Distancia y Espacio entre Troncos**
- **Descripción:** En el modo difícil, se ajustaron las distancias y alturas de los troncos para hacer el juego más desafiante.
- **Clases Modificadas:**
  - **Settings.hpp:** Definición de nuevas constantes para la variabilidad en la distancia y altura de los troncos en el modo difícil.
  - **PlayingState.cpp:** Implementación de la lógica que utiliza las nuevas constantes para generar troncos con variabilidad en distancia y espacio.
  - **World.hpp:** Declaración de métodos y variables relacionadas con la generación de troncos con variabilidad.
  - **World.cpp:** Implementación de la generación de troncos con variabilidad en el modo difícil.

### **5. Modo Difícil - Power-Up de Invulnerabilidad (Gusano)**
- **Descripción:** Se agregó un power-up (gusano) que permite al pájaro atravesar troncos temporalmente, cambiando su apariencia y la música del juego.
- **Clases Modificadas:**
  - **Settings.hpp:** Se definió la frecuencia de aparición del power-up de invulnerabilidad.
  - **Settings.cpp:** Implementación de la lógica para manejar la frecuencia y condiciones de aparición del power-up.
  - **World.hpp:** Declaración de métodos y variables para manejar la generación y detección del power-up de invulnerabilidad.
  - **World.cpp:** Implementación de la lógica para generar el power-up en el mundo del juego y detectar cuando el pájaro lo recoge.
  - **LogPair.hpp:** Ajustes para permitir que los troncos interactúen correctamente con el pájaro cuando está en modo invulnerable.
  - **LogPair.cpp:** Implementación de la lógica que permite al pájaro atravesar los troncos sin morir cuando está en modo invulnerable.
  - **Bird.hpp:** Declaración de variables y métodos para cambiar la apariencia del pájaro al recolectar el power-up.
  - **Bird.cpp:** Implementación del cambio de apariencia del pájaro y la lógica para manejar el estado de invulnerabilidad.
  - **PlayingState.hpp:** Declaración de variables y métodos para gestionar el estado de invulnerabilidad en el contexto del juego.
  - **PlayingState.cpp:** Implementación de la lógica que maneja el cambio de música y las interacciones del pájaro cuando está en modo invulnerable.
