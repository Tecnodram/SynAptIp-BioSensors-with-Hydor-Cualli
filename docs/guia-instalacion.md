# Manual de Visual Studio Code, PlatformIO, Firebase y conexión

Este es el procedimiento canónico para repetir la instalación completa de
Hydor-Cualli en Windows. Explica cómo conectar GitHub, preparar Visual Studio
Code, crear Firebase, programar el ESP8266 y verificar las lecturas. No
publiques contraseñas WiFi, usuarios de sensor ni otras credenciales.

## 1. Aceptar la colaboración

1. Inicia sesión en GitHub.
2. Abre la invitación recibida para `gmork69/hydor-cualli`.
3. Selecciona **Accept invitation**.

La invitación permite colaborar en el repositorio original. Este proyecto usa
un fork propio para mantener firmware, documentación y diseño 3D en un solo
lugar, sin repetir manualmente la información en ambos repositorios.

## 2. Preparar GitHub en la computadora

Instala Git y GitHub CLI. Después, desde una terminal, inicia sesión:

```powershell
gh auth login
```

Selecciona GitHub.com, HTTPS y acceso mediante navegador. Verifica la cuenta:

```powershell
gh auth status
```

Nunca compartas la contraseña, el token ni el código temporal de acceso.

## 3. Clonar y configurar los repositorios

Clona tu fork y entra en la carpeta:

```powershell
git clone https://github.com/TU_USUARIO/TU_FORK.git
cd TU_FORK
```

Configura el repositorio comunitario como `upstream`:

```powershell
git remote add upstream https://github.com/gmork69/hydor-cualli.git
git remote -v
```

La configuración esperada es:

- `origin`: fork personal, usado para publicar ramas.
- `upstream`: repositorio fuente, usado solamente para consultar o recibir
  actualizaciones del código original.

Antes de comenzar una tarea:

```powershell
git switch main
git fetch upstream
git merge --ff-only upstream/main
git push origin main
git switch -c tipo/descripcion-corta
```

## 4. Abrir el proyecto en la misma ventana de VS Code

Desde VS Code selecciona **File > Open Workspace from File...** y abre
`hydor-cualli.code-workspace`. VS Code reutiliza esa ventana y sustituye el
proyecto que estaba visible; no crea una copia de los archivos.

Desde una terminal también puedes forzar que se reutilice la última ventana:

```powershell
code -r hydor-cualli.code-workspace
```

Si se ejecuta `code hydor-cualli.code-workspace` sin `-r`, VS Code puede abrir
otra ventana según su configuración. Ambas ventanas apuntan a la misma carpeta
y no duplican el repositorio.

Cuando aparezca la pregunta de confianza, revisa la ruta y selecciona
**Yes, I trust the authors** si corresponde a tu copia del proyecto.

## 5. Instalar PlatformIO

El espacio de trabajo recomienda automáticamente:

- PlatformIO IDE (`platformio.platformio-ide`).
- Markdown All in One (`yzhang.markdown-all-in-one`).

También se pueden instalar desde la terminal:

```powershell
code --install-extension platformio.platformio-ide
code --install-extension yzhang.markdown-all-in-one
```

Es normal que la primera inicialización de PlatformIO tarde varios minutos.
Espera a que aparezca el icono de PlatformIO en la barra lateral.

No es necesario instalar manualmente las librerías Arduino: PlatformIO lee
`platformio.ini` y descarga las versiones declaradas por el proyecto.

## 6. Conectar y reconocer el ESP8266

1. Conecta la placa con un cable USB que transmita datos.
2. Abre el Administrador de dispositivos de Windows.
3. Busca la placa en **Puertos (COM y LPT)** y anota el puerto, por ejemplo
   `COM6`. El número puede cambiar entre computadoras o conectores USB.
4. Si no aparece, prueba otro cable o instala el controlador correspondiente
   al conversor USB de la placa (CH340, CP210x o FTDI).

La presencia de un puerto COM confirma la interfaz serial, pero todavía no
demuestra que el firmware compile ni que los sensores estén bien cableados.

## 7. Crear Firebase de forma segura

1. En <https://console.firebase.google.com/> crea un proyecto.
2. En **Realtime Database**, crea la base en `us-central1` y selecciona modo
   bloqueado. La región no puede cambiarse después.
3. En **Authentication**, habilita correo/contraseña y crea un usuario
   exclusivo para el sensor. No reutilices tu contraseña personal.
4. Copia el UID de ese usuario y publica reglas equivalentes a estas:

```json
{
  "rules": {
    "sensor": {
      ".read": "auth != null",
      ".write": "auth != null && auth.uid === 'UID_DEL_SENSOR'"
    },
    "historial": {
      ".read": "auth != null",
      ".write": "auth != null && auth.uid === 'UID_DEL_SENSOR'"
    }
  }
}
```

5. En la descripción general selecciona **Agregar app → Web (`</>`)**. No es
   necesario habilitar Hosting. Copia el valor `apiKey` de la configuración.

La URL pública identifica la base, pero la API key, el usuario y la contraseña
se guardan localmente para mantener una práctica uniforme. Nunca publiques el
correo/contraseña del sensor ni el archivo `secrets.h`.

## 8. Preparar las credenciales locales

Usa el firmware con historial y copia la plantilla:

```powershell
Copy-Item firmware/esp8266-oficial-historial/include/secrets.example.h `
  firmware/esp8266-oficial-historial/include/secrets.h
```

Abre `include/secrets.h` y completa únicamente los valores entre comillas:

```cpp
#define WIFI_SSID1 "RED_WIFI"
#define WIFI_PASSWORD1 "PASSWORD_WIFI"
#define WIFI_SSID2 "RED_ALTERNATIVA_O_LA_MISMA"
#define WIFI_PASSWORD2 "PASSWORD_ALTERNATIVA_O_LA_MISMA"
#define FIREBASE_DATABASE_URL "https://PROYECTO-default-rtdb.firebaseio.com"
#define FIREBASE_API_KEY "API_KEY"
#define FIREBASE_USER_EMAIL "USUARIO_EXCLUSIVO_DEL_SENSOR"
#define FIREBASE_USER_PASSWORD "PASSWORD_EXCLUSIVA_DEL_SENSOR"
```

Confirma antes de continuar:

```powershell
git check-ignore firmware/esp8266-oficial-historial/include/secrets.h
```

El comando debe devolver la ruta del archivo. Si no devuelve nada, no hagas
commit y revisa `.gitignore`.

## 9. Compilar, cargar y observar

Abre `firmware/esp8266-oficial-historial` como proyecto PlatformIO y usa:

1. **Build** para compilar.
2. **Upload** para escribir el firmware en la placa.
3. **Monitor** a 115200 baudios para ver el diagnóstico.

Desde la terminal, ajustando el puerto si no es `COM6`:

```powershell
pio run --project-dir firmware/esp8266-oficial-historial -j 1
pio run --project-dir firmware/esp8266-oficial-historial `
  --target upload --upload-port COM6 -j 1
pio device monitor --port COM6 --baud 115200
```

El parámetro `-j 1` evita un bloqueo de archivos observado en Windows durante
la primera compilación. Una ejecución correcta debe mostrar conexión WiFi,
sincronización de hora, una lectura cada 30 segundos y
`historial guardado (push)`.

En Firebase deben aparecer `/sensor` y `/historial`.

## 10. Seleccionar aire o agua

El ESP8266 tiene una sola entrada analógica accesible, `A0`; por eso esta
versión mide un sensor a la vez. Desconecta siempre el USB antes de recablear.

- Aire: señal MQ-135 en `A0` y D7 abierto.
- Agua: señal TDS en `A0` y jumper `D7 → GND`.

No conectes juntas las dos salidas analógicas a `A0`. Mantén secos la placa,
el transmisor TDS y sus conectores; solamente la sonda entra al agua.

## 11. Desconectar y volver a conectar

Al retirar el USB, Firebase conserva `/sensor` y todo `/historial`; solamente
dejan de llegar registros nuevos. Al reconectar la misma placa, el firmware y
las credenciales permanecen grabados y el envío se reanuda automáticamente si
la red configurada está disponible.

El campo `estadoConexion` actual no puede detectar un corte repentino de
energía. Una mejora futura calculará el estado usando la antigüedad de la
última lectura.

## 12. Elegir el firmware

- `firmware/esp8266-oficial-base`: publica solamente la última lectura.
- `firmware/esp8266-oficial-historial`: conserva lecturas en `/historial`.

Para la instalación documentada se recomienda la versión con historial. La
versión base se conserva como referencia del proyecto original y todavía usa
su método de configuración original.

## 13. Solución rápida de problemas

- No aparece un COM: cambia el cable USB e instala CH340, CP210x o FTDI según
  el convertidor de la placa.
- El puerto está ocupado: cierra otros monitores seriales.
- Solo aparecen puntos al arrancar: revisa SSID y contraseña WiFi.
- WiFi conecta pero Firebase no escribe: revisa API key, URL, usuario,
  contraseña y UID de las reglas.
- PlatformIO informa un archivo en uso: cierra monitores y compila con `-j 1`.
- Caracteres extraños antes de `Conectando a red 1`: el mensaje de arranque del
  ESP8266 usa otra velocidad; puede ignorarse si después el texto es legible.

## 14. Publicar una contribución

Revisa y publica una rama pequeña:

```powershell
git status
git diff
git add RUTA_DE_LOS_ARCHIVOS
git diff --staged
git commit -m "tipo: descripcion breve"
git push -u origin NOMBRE_DE_LA_RAMA
```

Finalmente abre un Pull Request hacia
`Tecnodram/SynAptIp-BioSensors-with-Hydor-Cualli:main`, explica el hardware
probado y espera revisión antes de integrar el cambio. Solo se enviará una
contribución a `gmork69/hydor-cualli` cuando el equipo decida expresamente que
una mejora también debe incorporarse al proyecto fuente.
