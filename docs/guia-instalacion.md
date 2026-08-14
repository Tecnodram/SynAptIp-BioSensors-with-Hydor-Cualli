# Guía de instalación y conexión

Esta guía explica cómo conectar Hydor-Cualli con GitHub, abrirlo en VS Code y
preparar PlatformIO para programar un ESP8266. No publiques contraseñas WiFi,
tokens de Firebase ni otras credenciales en GitHub.

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

## 6. Conectar y reconocer el ESP8266

1. Conecta la placa con un cable USB que transmita datos.
2. Abre el Administrador de dispositivos de Windows.
3. Busca la placa en **Puertos (COM y LPT)** y anota el puerto, por ejemplo
   `COM6`. El número puede cambiar entre computadoras o conectores USB.
4. Si no aparece, prueba otro cable o instala el controlador correspondiente
   al conversor USB de la placa (CH340, CP210x o FTDI).

La presencia de un puerto COM confirma la interfaz serial, pero todavía no
demuestra que el firmware compile ni que los sensores estén bien cableados.

## 7. Elegir el firmware

- `firmware/esp8266-oficial-base`: publica solamente la última lectura.
- `firmware/esp8266-oficial-historial`: conserva lecturas en `/historial`.

Abre la carpeta del firmware elegido como proyecto PlatformIO. Primero compila
con **Build**. Configura las credenciales localmente y revisa que no estén en
los cambios de Git antes de hacer un commit. Después conecta la placa, usa
**Upload** y abre el monitor serial a 115200 baudios.

## 8. Publicar una contribución

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
