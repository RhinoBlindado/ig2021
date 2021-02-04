[:es: Español](#informática-gráfica) | [:gb: English](#computer-graphics)

---
# Informática Gráfica #
##  :books: Curso 2020-2021, Grado en Ingeniería Informática, ETSIIT UGR.

### :pushpin: Introducción
Las prácticas de la asignatura se dividieron en 5 distintas partes, las cuales eran acumulativas, era necesario tener una práctica anterior para poder realizar correctamente la siguiente. 

Consistieron en una introducción propiamente a los gráficos por computadora, haciendo uso de OpenGL y la integración con el IDE Qt, desde realizar objetos básicos, objetos más complejos por medio de un perfil de puntos hasta iluminación, materiales e interacción con la cámara. 

Para mayor detalles de las prácticas y los objetivos a cumplir, ver `guionPractica.pdf`.

### :gear: Compilación
  * Las prácticas fueron realizadas con el IDE Qt, es posible cargar el proyecto en el IDE por medio del archivo `esqueleto_qt.pro`. De ser así, para mantener el funcionamiento correcto, se debe configurar Qt para que el proyecto se compile dentro de una carpeta en `/practicas/`, por ejemplo, dentro de la ruta `/practicas/build/`.
  * La compilación por medio de `makefile` está en WIP.

### :link: Contenido
#### :triangular_ruler: Práctica 1: Modelado y Dibujado de Objetos 3D Simples
De manera introductoria, se realizaron distintos métodos de dibujado y la creación de un objeto básico.

  * **Creación ```classCube.*```:** Realización de la clase de la primitiva cubo.
  * **Modificación ```object3d.*```:** Adición de métodos de dibujado (Líneas, Relleno y "Ajedrez").
  * **Modificación ```glwidget.*```:** Adición de eventos para cambiar entre los modos de dibujado, los objetos y declaración del objeto cubo.
    
#### :arrows_clockwise: Práctica 2: PLY y Modelos Poligonales
Se realizan más objetos básicos por la técnica de revolución por un eje además de la importación de modelos con el formato `*.ply`.

  * **Creación `classObjectRevolution.*`:** Clase virtual que contiene los métodos de revolución y de generación de triángulos.
  * **Creación `classCone.*`:** Clase para el objeto Cono con distintos parámetros para su creación, hereda de `classObjectRevolution.*`
  * **Creación `classCylinder.*`:** Clase para el objeto Cilindro con distintos parámetros para su creación, hereda de ``classObjectRevolution.*``
  * **Creación `classSphere.*`:** Clase para el objeto Esfera con distintos parámetros para creación, heredad de `classObjectRevolution.*`
  * **Creación `classObjectPly.*`:** Clase para dibujar objetos con el formato `*.ply`, acepta modelos normales como modelos por revolución por medio de un perfil, hereda de `classObjectRevolution.*` 
  * **Adición `file_ply_stl.*`:** Clase provista por el profesor para cargar los archivos `*.ply` en el programa.
  * **Modificación ```glwidget.*```:** Adición de eventos para cambiar entre los objetos y declaración de nuevos objetos.

#### :mechanical_arm: Práctica 3: Modelos Jerárquicos
Se realizó un objeto jerárquico, esto es un objeto compuesto de distintos objetos más sencillos que se comportan como uno solo. Se le añadieron tres ángulos de libertad, es decir, animación tanto por tecla como automática haciendo uso de Qt.

  * **Creación `classTelescope.*`:** Clase para el objeto jerárquico, en este caso se trata de un telescopio casero. 
  * **Creación `classTelescope_part_*.*`:** Subclases que contienen distintas partes del telescopio.
  * **Modificación ```glwidget.*```:** Adición de eventos para cambiar entre los objetos y declaración de nuevos objetos. Así como clases para restringir el movimiento y una conexión con Qt para realizar la animación automática.
  * **Modificación `window.cc`:** Adición de un temporizador para la animación así como una conexión por medio de un `slot` a OpenGL.

#### :bulb: Práctica 4: Iluminación y Texturas
Se crearon dos luces, se realizó el algoritmo para calcular las normales de los objetos, tanto las normales de los triángulos, como para los vértices. Se cargó una textura y se mapeo a distintos objetos.

  * **Creación `classLights.*`:** Creación de clase auxiliar para contener la configuración de las luces.
  * **Creación `classChessboard.*`:** Creación de clase de un tablero para mapear una textura.
  * **Creación `classCylinderTextured.*`:** Creación de una clase para el cilindro de manera que se le pueda asignar fácilmente una textura.
  * **Creación `classSphereTextured.*`:** Creación de una clase para la esfera de manera que se le pueda asignar fácilmente una textura.
  * **Modificación `object3d.*`:** Adición de métodos para realizar el dibujado con iluminación, iluminación con texturas, la carga de texturas y el cálculo de normales.
  * **Modificación `glwidget.*`:** Adición de los nuevos métodos de dibujado así como iluminación, creación de un tipo de dato para alojar los materiales.
  * **Modificación `window.*`:** Adición de código para cargar la textura en memoria y enviarla a `glwidget`.
  * **Modificación de todos los objetos:** Adición de cálculo de las normales.

#### :camera_flash: Práctica 5: Interacción y Cámara
Esta última práctica se centró en realizar aumentar la interactividad por medio del uso de la cámara por medio del ratón, además, poder realizar la selección de un triángulo de un modelo y dibujarlo. Finalmente, también se añadió la posibilidad de cambiar de tipos de proyección, de la normal perspectiva a la paralela u ortogonal.

  * **Creación `classScene.*`:** Clase para dibujar un objeto PLY varias veces y realizar la selección a nivel de objetos y no de triángulos.
  * **Modificación `object3d.*`:** Adición del método de dibujado para seleccionar un triángulo en particular, se hace uso de máscaras de bits para generar un color único por triángulo.
  * **Modificación `glwidget.*`:** Adición de métodos para mover la cámara y realizar zoom con el ratón asi como también realizar los cambios de proyección y el método para realizar la selección de triángulos por medio de un búfer auxiliar.
  * **Modificación `window.*`:** Adición de código para generar una interfaz gráfica más amigable para interactuar con el programa.

#### :heavy_plus_sign: Ejercicios Adicionales
Se realizaron, además, distintos ejercicios (ver `practicas/docs/` y `practicas/object3d.*`) que añadieron funcionalidades adicionales al programa:
  * **Ejercicio 2 - Triángulo Mayor y Menor:** Dado un modelo, determinar cuál es el triángulo que posee la menor área y cual posee la mayor área.
  * **Ejercicio 4 - Volumen de un Modelo:** Dado un modelo, aproximar su volumen.
  * **Ejercicio 5 - Eliminación de un Triángulo:** Dado un modelo y un triángulo que posee, eliminarlo sin que se afecte la topología.
  * **Ejercicio 7 - Modelo jerárquico de una cámara:** Crear un modelo jerárquico como el de la figura.
  * **Ejercicio 2B de Examen Ordinario 18-19**: Determinar si un objeto cumple con el Teorema de Euler para poliedros.
---
# Computer Graphics #
## :books: 2020-2021 Course, Computer Science Engineering Degree, ETSIIT UGR.
### :pushpin: Introduction


### :gear: Compilation

### :link: Contents
#### :triangular_ruler: Practice 1: Modelling and rendering of simple 3D objects
#### :arrows_clockwise: Practice 2: PLY and polygonal models
#### :mechanical_arm: Practice 3: Hierarchical models
#### :bulb: Practice 4: Lighting and texturing
#### :camera_flash: Practice 5: Interaction and camera
#### :heavy_plus_sign: Additional Exercises
