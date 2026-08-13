# Firmware BASE — ESP8266 (como nos lo dieron)

Es el firmware original del colectivo, **tal cual**. Publica a Firebase
la última lectura de tu sensor. **No** guarda historial (cada lectura pisa
la anterior; por eso el "Historial" del tablero sale vacío).

> ¿Quieres que el historial se llene? Usa la carpeta hermana
> [`esp8266-oficial-historial`](../esp8266-oficial-historial/).

## Qué necesitas
- NodeMCU **ESP8266**
- Sensor **TDS** (agua) y/o **MQ-135** (aire)
- Un **cable/jumper** para elegir el modo
- Cable **USB**

## Cableado
- El **cable de datos** del sensor que vas a medir → pin **A0**.
- El **jumper de modo** en el pin **D7**:
  - **D7 conectado a G (GND)** → modo **AGUA** (TDS).
  - **D7 suelto (sin conectar)** → modo **AIRE** (MQ-135).
- Alimentación: TDS a 3V3, MQ-135 a Vin/5V, ambos a GND.

> ⚠️ Mueve **juntos** el cable de datos y el jumper: si el TDS está en A0,
> D7 debe ir a G; si el MQ-135 está en A0, D7 va suelto.

## Cómo cargarlo (VSCode + PlatformIO)
1. Abre **esta carpeta** en VSCode (con la extensión PlatformIO instalada).
2. Abre `src/main.cpp` y edita **solo el bloque "CONFIGURA ESTO"**:
   tu WiFi y los datos de **tu propio** proyecto de Firebase (gratis).
3. Conecta el ESP por USB y da **Upload** (la flechita →).
4. Abre el **Monitor Serial** a **115200** para ver las lecturas.

*(También se puede con Arduino IDE: instala la librería "Firebase ESP8266
Client" de Mobizt v4.3.19 y la placa "NodeMCU 1.0 (ESP-12E)".)*
