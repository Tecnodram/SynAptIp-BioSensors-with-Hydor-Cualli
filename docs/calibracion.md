# Calibración de los sensores

El sistema ya transmite lecturas, pero eso no implica que estén calibradas. La
conversión TDS actual y el valor relativo del MQ-135 deben tratarse como datos
experimentales hasta completar los procedimientos siguientes.

## Materiales para calibrar TDS

- Solución patrón de 1413 µS/cm, equivalente aproximadamente a 707 ppm con
  factor TDS 0.5, preferiblemente con certificado y fecha de caducidad.
- Agua destilada para enjuague.
- Termómetro calibrado; mejora recomendada: sonda DS18B20 impermeable.
- Vasos limpios con tapa y etiquetas.
- Papel absorbente para secar sin frotar los electrodos.
- Medidor EC/TDS comercial calibrable para comparación independiente.
- Una segunda solución patrón para verificar un punto distinto.

## Procedimiento TDS

1. Confirma marca y modelo del módulo; el procedimiento del SEN0244 no debe
   asumirse automáticamente para otro circuito.
2. Lleva la solución patrón a 25 °C o registra su temperatura real.
3. Enjuaga la sonda con agua destilada y elimina el exceso sin frotar.
4. Sumerge únicamente la sonda, lejos del fondo y las paredes, y elimina
   burbujas con movimiento suave.
5. Espera estabilidad y registra al menos tres repeticiones.
6. Ajusta el factor para reproducir el valor certificado de la solución.
7. Enjuaga y verifica con una segunda solución sin reajustar.
8. Calcula error absoluto, error porcentual, media y desviación estándar.
9. Repite la verificación periódicamente y después de almacenamiento largo.

DFRobot recomienda 1413 µS/cm o 707 ppm a 25 °C para el SEN0244. El TDS se
infiere de la conductividad y el factor depende de la composición de las sales;
por ello dos aguas con igual conductividad no necesariamente tienen la misma
masa real de sólidos disueltos.

El firmware necesita una fase posterior para incorporar compensación de
temperatura, factor persistente y comandos de calibración. Hasta entonces, no
uses sus ppm para certificar potabilidad.

## Materiales para caracterizar el MQ-135

- Fuente de 5 V estable capaz de alimentar el calentador.
- Multímetro para verificar alimentación y salida analógica.
- Sensor de temperatura y humedad BME280 o SHT31.
- Cronómetro y espacio ventilado de referencia.
- Para ppm defendibles: cámara de gases, regulador, flujo controlado, gases
  patrón certificados y un instrumento específico de referencia.
- Alternativa de campo: acceso a una estación o instrumento de referencia para
  realizar colocación conjunta.

## Procedimiento MQ-135 como índice relativo

1. Verifica que la salida del módulo no exceda el rango de la entrada ADC.
2. Acondiciona el sensor nuevo durante al menos 48 horas con calentamiento
   estable, siguiendo la ficha del fabricante.
3. Colócalo en aire relativamente limpio y sin fuentes cercanas.
4. Registra lectura cruda, temperatura y humedad durante varias horas.
5. Calcula una línea base robusta, conservando mediana y dispersión.
6. Expresa cambios posteriores respecto a esa línea base, no como ppm de un
   gas específico.
7. Repite la línea base periódicamente para detectar deriva.

El MQ-135 responde a varios gases y también cambia con temperatura y humedad.
Sin gas patrón o instrumento de referencia, debe reportarse como indicador
relativo de gases/calidad del aire.

## Calibración del MQ-135 contra referencia

1. Define primero el contaminante objetivo; un MQ-135 no es selectivo.
2. Coloca sensor y referencia juntos y bajo las mismas condiciones.
3. Registra suficientes días para cubrir variaciones de concentración,
   temperatura y humedad.
4. Alinea tiempos y calcula una ecuación de corrección con parte de los datos.
5. Valida la ecuación con datos separados.
6. Reporta sesgo, MAE, RMSE, repetibilidad, rango y condiciones ambientales.
7. Verifica nuevamente la calibración durante y después del estudio.

## Seguridad y alcance

- No uses MQ-135 como alarma certificada de gas, CO o incendio.
- No uses TDS como prueba única de agua potable.
- No sumerjas el transmisor TDS ni sus conectores.
- Documenta número de serie, solución, lote, temperatura, fecha y operador.
- Conserva datos crudos además de los valores corregidos.

Consulta las fuentes técnicas y científicas en
[referencias-bibliograficas.md](referencias-bibliograficas.md).
