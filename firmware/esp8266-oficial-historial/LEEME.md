# Firmware CON HISTORIAL — ESP8266

Es **idéntico al base**, con un solo cambio: además de publicar la última
lectura, guarda **cada lectura en `/historial`**. Así el "Historial" del
tablero por fin se llena para todos.

> Es el primer aporte del colectivo sobre el firmware original. Si algo
> falla, siempre puedes volver a la [versión base](../esp8266-oficial-base/).

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

> ⚠️ Mueve **juntos** el cable de datos y el jumper.

## Cómo cargarlo (VSCode + PlatformIO)
1. Abre **esta carpeta** en VSCode (con la extensión PlatformIO instalada).
2. Copia `include/secrets.example.h` como `include/secrets.h`.
3. Edita solamente `include/secrets.h` con tus redes WiFi, URL y API key de
   Firebase, y el correo/contraseña del usuario exclusivo del sensor.
   `secrets.h` está excluido de Git y nunca debe publicarse.
4. Conecta el ESP por USB y da **Upload** (la flechita →).
5. Abre el **Monitor Serial** a **115200**. Debe aparecer, cada 30 s,
   `[Firebase] historial guardado (push).`

## ¿Qué cambió exactamente respecto al base?
Solo el bloque marcado **"LA MODIFICACIÓN: HISTORIAL"** dentro de `loop()`:
donde antes solo se hacía `setFloat()` (que pisa el valor), ahora además se
hace `pushJSON()` a `/historial` con la forma `{ tipo, valor, timestamp }`
que el dashboard ya sabe leer. Nada más se tocó.
