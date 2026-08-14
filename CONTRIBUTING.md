# Colaborar en Hydor-Cualli

## Preparación

1. Acepta la invitación del repositorio en GitHub.
2. Clona tu fork o el repositorio donde tienes permisos.
3. Abre `hydor-cualli.code-workspace` en VS Code.
4. Instala las extensiones recomendadas cuando VS Code las muestre.

Nunca subas contraseñas WiFi, tokens de Firebase ni otros secretos. Antes de
hacer un commit, revisa `git diff --staged`.

## Flujo recomendado

```bash
git switch main
git pull --ff-only upstream main
git switch -c tipo/descripcion-corta
```

Usa prefijos como `docs/`, `firmware/`, `3d/` o `fix/`. Haz cambios pequeños,
pruébalos y luego publica la rama:

```bash
git add README.md docs/ firmware/
git commit -m "docs: describe instalacion del prototipo"
git push -u origin tipo/descripcion-corta
```

Finalmente abre un Pull Request hacia
`Tecnodram/SynAptIp-BioSensors-with-Hydor-Cualli:main`. Describe el hardware
probado, el resultado y cualquier limitación conocida.

## Remotos

La configuración recomendada es:

- `origin`: tu fork bajo la cuenta `Tecnodram`.
- `upstream`: el repositorio fuente `gmork69/hydor-cualli`, usado solamente
  para consultar y traer actualizaciones del proyecto original.

Verifica la configuración con `git remote -v`. No hagas `push --force` sobre
ramas compartidas ni publiques documentación en `upstream`. Toda la
documentación ampliada de este proyecto se mantiene en `origin`.
