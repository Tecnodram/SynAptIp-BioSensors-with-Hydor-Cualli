# Bitácora técnica

Este documento registra la preparación, pruebas y resultados del nodo sin
guardar contraseñas, tokens ni otros datos sensibles.

## 2026-08-13 — Preparación inicial

### Repositorio y colaboración

- Se creó el fork `Tecnodram/SynAptIp-BioSensors-with-Hydor-Cualli` a partir de
  `gmork69/hydor-cualli`.
- `origin` apunta al repositorio de Tecnodram y recibe todos los cambios nuevos.
- `upstream` conserva la vinculación con el proyecto fuente y tiene el envío
  deshabilitado localmente para evitar publicaciones accidentales.
- Se añadieron la guía de instalación, el flujo de contribución y la sección
  para el futuro prototipo 3D.

### Entorno de desarrollo

- VS Code 1.120.0 instalado.
- PlatformIO IDE 3.3.4 instalado.
- PlatformIO Core 6.1.19 inicializado.
- Plataforma Espressif 8266 4.2.1 instalada.
- Placa de compilación: NodeMCU 1.0 (ESP-12E Module), identificador
  `nodemcuv2`.
- Librería Firebase ESP8266 Client 4.3.19 instalada desde `platformio.ini`.

### Detección USB

- Windows detectó una interfaz FTDI `VID_0403/PID_6001` como `COM6`.
- El número de puerto es específico de esta computadora y puede cambiar al
  mover la placa a otro conector USB.

### Compilación del firmware con historial

Proyecto probado:

```text
firmware/esp8266-oficial-historial
```

La primera ejecución paralela encontró un bloqueo temporal de archivo de
Windows mientras se generaba `libESP8266SdFat.a`. La compilación se repitió con
un solo proceso y terminó correctamente:

```powershell
pio run --project-dir firmware/esp8266-oficial-historial -j 1
```

Resultado:

- Estado: `SUCCESS`.
- RAM: 32,844 de 81,920 bytes (40.1%).
- Flash: 544,303 de 1,044,464 bytes (52.1%).
- Todavía no se cargó firmware a la placa.
- Todavía no se configuraron ni publicaron credenciales WiFi/Firebase.

### Siguiente prueba

Preparar credenciales locales excluidas de Git, volver a compilar, cargar el
firmware por el puerto detectado y validar el arranque mediante el monitor
serial a 115200 baudios.

## 2026-08-13 — Firebase y autenticación

- Se creó el proyecto Firebase `SynAptIp Hydor Cualli` en el plan Spark.
- Se creó Realtime Database en `us-central1`, inicialmente vacía y en modo
  bloqueado.
- Se habilitó autenticación por correo/contraseña y se creó un usuario
  exclusivo para el sensor. No se registran aquí su correo, contraseña ni UID.
- Se publicaron reglas que permiten escribir en `/sensor` y `/historial`
  solamente al UID del sensor y leer únicamente a usuarios autenticados.
- El firmware con historial dejó de usar el token heredado. Ahora admite API
  key, URL de base de datos y usuario Firebase mediante
  `include/secrets.h`, excluido de Git.
- Se añadió `include/secrets.example.h` como plantilla pública sin datos reales.
- La compilación de la nueva autenticación terminó correctamente: 40.2% de RAM
  y 52.1% de flash. La placa todavía no ha sido programada.

## 2026-08-13 — Primera conexión completa del sensor

- Se completó localmente `include/secrets.h`; Git confirmó que el archivo está
  ignorado y no se publicó ninguna credencial.
- El firmware autenticado se compiló correctamente con 40.2% de RAM y 52.1%
  de flash.
- PlatformIO identificó el dispositivo de `COM6` como un ESP8266EX y cargó
  548,576 bytes. La escritura y su hash fueron verificados correctamente.
- El monitor serial confirmó conexión WiFi y sincronización de hora.
- El jumper D7 estaba abierto, por lo que el firmware inició en modo aire.
- Se observaron lecturas relativas de 105.47 y 105.40, separadas por 30 segundos.
- Firebase confirmó `historial guardado (push)` después de cada lectura.
- Resultado: comunicación ESP8266 → WiFi → Firebase Realtime Database validada.
