# Prototipo 3D

Esta carpeta documenta el diseño mecánico del nodo Hydor-Cualli. El gabinete
debe diseñarse después de definir el entorno de uso, porque un sensor de aire
necesita ventilación y un sensor de agua necesita separar la electrónica de la
sonda y de la humedad.

## Ficha del sitio de instalación

Completa una ficha por ubicación antes de modelar:

- Lugar y tipo de montaje: muro, poste, mesa, tubería, flotador u otro.
- Uso: interior, exterior protegido, intemperie o proximidad/inmersión en agua.
- Temperatura, lluvia, polvo, radiación solar y riesgo de condensación.
- Espacio disponible y medidas máximas del conjunto.
- Acceso a energía, orientación del cable USB y alcance de WiFi.
- Posición, longitud de cable y zona de contacto de las sondas.
- Frecuencia de limpieza, calibración y reemplazo de componentes.
- Método de fijación y herramientas disponibles.

## Requisitos iniciales del gabinete

- Separar la zona húmeda de la placa ESP8266 y sus conexiones.
- Mantener accesibles USB, botón de reinicio y jumper de selección.
- Incluir alivio de tensión para cables y espacio para conectores.
- Evitar que el MQ-135 quede encerrado; agregar ventilación protegida.
- Evitar que agua conducida por el cable llegue a la electrónica; orientar las
  entradas hacia abajo y prever un bucle de goteo.
- Diseñar tapa desmontable y puntos de fijación sin presionar la placa.
- Validar material, sellado y protección ambiental para el sitio real antes de
  declarar una clasificación IP.

## Estructura para los archivos de diseño

```text
docs/prototipo-3d/
|-- README.md
|-- sitios/          # fichas, fotos y medidas de cada ubicación
|-- cad/             # archivos fuente editables (STEP, FreeCAD, Fusion, etc.)
|-- exportaciones/   # STL/3MF listos para laminar
`-- pruebas/         # fotos, ajustes y resultados de prototipos
```

Al agregar un modelo indica versión, software usado, unidades, tolerancias,
material sugerido, orientación de impresión y hardware de montaje.

## Validación antes de instalar

1. Imprime una versión de ajuste y comprueba placa, sensores y conectores.
2. Confirma ventilación del MQ-135 y acceso de mantenimiento al TDS.
3. Revisa calentamiento, condensación, entrada de agua y esfuerzo en cables.
4. Haz una prueba de campo temporal y documenta lecturas y fallas.
5. Corrige el CAD, incrementa la versión y conserva fotos del resultado.
