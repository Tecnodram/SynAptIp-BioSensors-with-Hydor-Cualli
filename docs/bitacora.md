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
