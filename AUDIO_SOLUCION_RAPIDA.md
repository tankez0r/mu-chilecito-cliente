# 🔊 SOLUCIÓN RÁPIDA: SIN SONIDO (MuMain)

## ⚡ Los 3 Problemas Más Comunes

### Problema #1: Faltan los Archivos de Música/Audio

**Síntoma:** Sin sonido en absoluto

**Verificar:**
```powershell
Test-Path "src/bin/music"   # ¿Existe la carpeta?
ls "src/bin/music"          # ¿Contiene archivos?
```

**Solución:**
- La carpeta `src/bin/` debe contener archivos `.mp3` y `.ogg`
- Si no existen, **el repositorio no incluye los assets de audio**
- Obtén los archivos de audio de:
  - Otro cliente MuMain compilado
  - La carpeta del cliente original Si tienes una copia

### Problema #2: Assets No Copiados Tras Compilación

**Síntoma:** Archivos existen pero sin sonido

**Verificar:**
```powershell
Test-Path "out/build/windows-x86/Debug/assets/music"
ls "out/build/windows-x86/Debug/assets/music"
```

**Solución Rápida:**
```powershell
Copy-Item -Path "src/bin/*" -Destination "out/build/windows-x86/Debug/assets" -Recurse -Force
```

### Problema #3: SDL_mixer Error de Compilación

**Síntoma:** Compiló pero sin sonido, Output muestra errores

**Verificar:**
```powershell
git submodule status  # ¿SDL_mixer inicializado?
```

**Solución:**
```powershell
git submodule update --init --recursive
Remove-Item -Recurse "out/build" -Force
cmake --preset windows-x86
cmake --build out/build/windows-x86 --config Debug
```

---

## ✅ Checklist Ultra-Rápido

- [ ] ¿`src/bin/music/` existe y tiene archivos?
- [ ] ¿`out/build/.../Debug/assets/music/` tiene archivos?
- [ ] ¿SDL_mixer compiló sin errores? (revisar Output)
- [ ] ¿Los archivos son MP3 u OGG?
- [ ] ¿El volumen del juego > 0?

---

## 🎯 Lo Más Probable

**90% de los casos:** Los archivos de audio no están en `src/bin/` porque el repositorio no los incluye.

**Solución:** Obtén un cliente MuMain compilado correctamente y copia su carpeta `bin/`.

```powershell
# Desde otro cliente MuMain
Copy-Item -Path "C:\OtherClient\bin\*" -Destination "F:\mu-online\MuMain-main-cliente\src\bin" -Recurse -Force

# Luego recompila
cd F:\mu-online\MuMain-main-cliente
cmake --build out/build/windows-x86 --config Debug

# Copia assets a output
Copy-Item -Path "src/bin/*" -Destination "out/build/windows-x86/Debug/assets" -Recurse -Force

# ¡Listo!
```

---

## 📖 Para Más Detalles

→ Lee: `SOLUCION_PROBLEMAS_AUDIO.md`

(7 problemas diferentes con soluciones detalladas)

---

**TL;DR:** Copia `src/bin/` desde un cliente MuMain existente que tenga sonido. ✅

