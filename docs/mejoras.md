# Mejoras planeadas

## Medición de aire y agua en el mismo ciclo

La versión actual usa un ESP8266, que expone una sola entrada analógica `A0`.
El pin D7 solo indica si el firmware debe interpretar A0 como aire o agua; no
conmuta eléctricamente las señales.

La mejora recomendada es conservar el ESP8266 y agregar un ADS1115:

```text
TDS AOUT ----> ADS1115 A0
MQ-135 AOUT -> ADS1115 A1
ADS1115 SDA --> ESP8266 D2 (GPIO4)
ADS1115 SCL --> ESP8266 D1 (GPIO5)
ADS1115 GND --> GND común
ADS1115 VDD --> 3V3
```

### Lista de compra

- Un módulo ADS1115 de 16 bits y cuatro canales con interfaz I²C.
- Cables Dupont y conectores con alivio de tensión.
- Multímetro.
- Resistencias de precisión para divisores de tensión, valores por definir
  después de medir las salidas reales.
- Capacitores cerámicos de desacoplo de 100 nF.
- DS18B20 impermeable y resistencia de 4.7 kΩ para compensación TDS.
- BME280 o SHT31 para registrar temperatura y humedad del aire.
- Opcional: borneras, placa perforada o PCB para una conexión permanente.

### Verificaciones antes de conectar

- Identificar el modelo exacto de cada módulo y medir su salida mínima/máxima.
- Aunque el ADS1115 ofrezca rangos de ganancia de hasta ±6.144 V, sus entradas
  no deben superar físicamente sus rieles de alimentación. Alimentado a 3.3 V,
  cualquier salida mayor requiere acondicionamiento o divisor.
- Confirmar tierra común y no conectar juntas las dos salidas analógicas.
- Verificar que el calentador del MQ-135 reciba la alimentación indicada por
  su fabricante sin cargar el regulador del ESP8266.

El ADS1115 multiplexa sus canales; no toma ambas muestras en el mismo
microsegundo. Para variables ambientales lentas, leerlas consecutivamente en
el mismo ciclo representa una medición prácticamente simultánea.

### Cambios de firmware

1. Añadir la librería ADS1115 a `platformio.ini`.
2. Sustituir `analogRead(A0)` por lecturas de A0 y A1 del ADS1115.
3. Mantener filtros y calibraciones independientes.
4. Incorporar temperatura del agua y temperatura/humedad del aire.
5. Escribir una entrada conjunta en Firebase:

```json
{
  "timestamp": "2026-08-13 20:30:00",
  "agua_ppm": 108.7,
  "aire_indice": 102.9,
  "temperatura_agua_c": 25.1,
  "temperatura_aire_c": 24.8,
  "humedad_relativa_pct": 48.2
}
```

6. Actualizar reglas y tablero sin eliminar compatibilidad con el historial.

## Alternativa ESP32

Un ESP32 ofrece varios canales ADC. Durante WiFi deben seleccionarse canales
ADC1; ADC2 comparte recursos con el controlador WiFi. También se requiere
verificar niveles de tensión y calibrar cada entrada.

## Estado de conexión real

Firebase conserva el último valor cuando el equipo pierde energía. El tablero
debe considerar desconectado un nodo si `timestamp` no cambia durante un plazo
configurable, en lugar de confiar solamente en `estadoConexion`.

## Calidad de datos

- Guardar lecturas crudas y calibradas.
- Añadir versión de firmware y factores de calibración a cada sesión.
- Detectar valores imposibles y saltos bruscos sin borrar el dato original.
- Exportar CSV para análisis y conservar zona horaria explícita.
- Añadir identificador de nodo y ubicación no sensible.

## Prototipo 3D

El gabinete debe separar la electrónica de la zona húmeda, mantener ventilado
el MQ-135 y permitir retirar/calibrar ambas sondas. Los requisitos mecánicos se
mantienen en [prototipo-3d/README.md](prototipo-3d/README.md).
