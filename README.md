# Hydor-Cualli 💧🌬️

Proyecto comunitario de **monitoreo ambiental**: cada nodo mide **calidad de
agua (TDS)** y **calidad de aire (MQ-135)** y publica sus datos para verlos en
un tablero compartido.

Aquí vive el **firmware** que cada participante carga a su ESP. Empezamos por el
nodo más sencillo —el mismo que ya conoces— y de ahí vamos creciendo.

---

## ¿Cuál firmware uso?

| Carpeta | Qué hace | Para quién |
|---|---|---|
| [`firmware/esp8266-oficial-base`](firmware/esp8266-oficial-base/) | El original del colectivo, tal cual. Publica a Firebase la última lectura. | Empezar / lo que ya conocías |
| [`firmware/esp8266-oficial-historial`](firmware/esp8266-oficial-historial/) | Igual, pero además **llena el historial** del tablero. | Que tu historial deje de salir vacío |

> Cada carpeta trae su propio **LEEME.md** con el cableado y el paso a paso.

---

## Cómo empezar (resumen)

1. Instala **VSCode** y su extensión **PlatformIO IDE** (una sola vez).
2. **Descarga este proyecto** (botón verde `Code → Download ZIP`, o `git clone`).
3. Abre en VSCode la carpeta del firmware que elegiste.
4. Edita **solo el bloque "CONFIGURA ESTO"** en `src/main.cpp`:
   tu **WiFi** y los datos de **Firebase**.
5. Conecta tu ESP por **USB**, da **Upload** (→) y abre el **Monitor Serial** (115200).

> **Por ahora cada quien usa su propio Firebase.** Crea un proyecto gratis en
> [firebase.google.com](https://firebase.google.com), activa la **Realtime
> Database** y copia su **URL (host)** y un **token**; eso es lo que pegas en
> "CONFIGURA ESTO". Más adelante, cuando veamos qué nodos van bien, los
> juntamos en un servidor central (ahí entra la API).

---

## ¿Algo no jala?

Abre un **Issue** aquí en GitHub (es como dejar un recado, no necesitas saber
de código): describe qué placa tienes, qué firmware usaste y qué te aparece en
el Monitor Serial. Alguien del equipo te ayuda.

---

## Créditos

- **Proyecto y código original:** **Emily Acosta** — idea, firmware y desarrollo
  del sistema Hydor-Cualli.
- **Mejora del historial y empaquetado del repo:** Adrian Del Río — ADRA-Tech ([@gmork69](https://github.com/gmork69)).

Gracias a toda la comunidad que sostiene el proyecto. 💧🌬️

---

## En camino

- ESP32 (2 sensores a la vez) y ESP8266 + ADS1115.
- Servidor central propio (para guardar el histórico completo, permanente).
- Página web para elegir tu hardware y descargar lo tuyo.

---

## Construcción del prototipo 3D

El gabinete y los soportes se diseñarán de acuerdo con el lugar real de
instalación: interior, exterior, cuerpo de agua, tubería o estación fija.
Consulta la [guía del prototipo 3D](docs/prototipo-3d/README.md) para registrar
medidas, requisitos ambientales, mantenimiento y archivos de fabricación.

## Trabajo colaborativo

Antes de proponer cambios, consulta [CONTRIBUTING.md](CONTRIBUTING.md). El
archivo `hydor-cualli.code-workspace` permite abrir el proyecto completo en
VS Code y recomienda las extensiones necesarias para firmware y documentación.
