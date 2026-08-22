# 🔊 SOLUCIÓN DE PROBLEMAS DE AUDIO (Sin Sonido en MuMain)

## 🎯 Diagnóstico: ¿Por Qué No Tiene Sonido?

Compilaste MuMain pero **no escuchas sonido**. Aquí están las causas más comunes y soluciones.

---

## ✅ CHECKLIST Rápido de Diagnóstico

Verifica estos puntos **antes de nada:**

```powershell
# 1. ¿Existe la carpeta src/bin/music?
Test-Path "src/bin/music"

# 2. ¿Contiene archivos de audio (MP3, OGG)?
Get-ChildItem "src/bin/music" -Recurse | Where-Object {$_.Extension -match '\.(mp3|ogg|wav)$'}

# 3. ¿Se copiaron los assets al directorio de salida?
Test-Path "out/build/windows-x86/Debug/assets/music"
Get-ChildItem "out/build/windows-x86/Debug/assets/music" | Measure-Object | Select-Object Count

# 4. ¿SDL_mixer se compiló correctamente?
# (Verificar en Output → Build que no hay errores de SDL_mixer)

# 5. ¿El código intenta reproducir sonido?
# (Buscar Mix_PlayChannel, Mix_LoadMUS)
```

---

## 🔍 Problema 1: Archivos de Audio Faltantes

### Síntomas
- ✓ Compilación exitosa
- ✓ Juego se ejecuta
- ✓ **Pero: Sin sonido en absoluto**
- ✓ Carpeta `src/bin/music/` **no existe** o está **vacía**

### Causa
El repositorio MuMain descargado **no incluye los archivos de audio** (música y efectos de sonido).

### Solución

**Opción A: Obtener Assets del Repositorio Original**

1. Si tienes otro cliente MuMain compilado, copia la carpeta `bin/` completa:
   ```powershell
   # Desde un cliente MuMain existente:
   Copy-Item -Recurse "C:\path\to\other\client\bin\*" "src/bin\"
   ```

2. O descarga los assets desde el repositorio oficial (si están disponibles)

**Opción B: Crear Estructura de Carpetas Vacía (Por Ahora)**

Si no tienes assets, al menos crea la estructura:
```powershell
# Crear carpetas de audio
New-Item -ItemType Directory -Path "src/bin/music" -Force
New-Item -ItemType Directory -Path "src/bin/sfx" -Force
New-Item -ItemType Directory -Path "src/bin/data" -Force
New-Item -ItemType Directory -Path "src/bin/gfx" -Force
```

El juego buscará archivos en esas carpetas. Sin ellos, no hay sonido pero no crasheará.

---

## 🔍 Problema 2: Assets No Copiados Tras Compilación

### Síntomas
- ✓ Archivos de audio **existen** en `src/bin/`
- ✓ Compraste exitosamente
- ✓ **Pero: No hay sonido**
- ✓ La carpeta `out/build/windows-x86/Debug/assets/` **no contiene music/**

### Causa
Los assets **no se copiaron** automáticamente al directorio de compilación. Esto sucede si:
1. La compilación fue interrumpida
2. El caché de CMake no se actualizó
3. Los archivos son muy grandes y la copia falla silenciosamente

### Solución

**Paso 1: Verificar que Assets Existen**
```powershell
Get-ChildItem "src/bin/" -Recurse | Measure-Object | Select-Object Count
# Debe retornar un número > 10
```

**Paso 2: Copiar Manualmente**
```powershell
# Copia desde src/bin hacia el directorio de compilación
$sourceDir = "src/bin"
$destDir = "out/build/windows-x86/Debug/assets"

# Asegúrate de que existe el destino
New-Item -ItemType Directory -Path $destDir -Force | Out-Null

# Copia recursivamente
Copy-Item -Path "$sourceDir/*" -Destination $destDir -Recurse -Force

# Verifica
Get-ChildItem $destDir -Recurse | Measure-Object | Select-Object Count
```

**Paso 3: Verificar Archivo CMakeLists.txt**
```cmake
# En src/CMakeLists.txt, lines ~280-300, debe existir una copia automática.
# Si no está, busca:
add_custom_command(
  OUTPUT "${ASSETS_STAMP}"
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ...
)
```

---

## 🔍 Problema 3: SDL_mixer No Compiló Correctamente

### Síntomas
- ✓ src/bin/music/ tiene archivos
- ✓ Assets copiados correctamente
- ✓ **Pero: Sin sonido**
- ✓ Output → Build muestra **errores de SDL_mixer**

### Causa
SDL_mixer no se compiló correctamente. Posibles razones:
1. Submódulo SDL_mixer no inicializado
2. Error durante compilación de SDL_mixer (DRMP3, Vorbis)
3. Falta de bibliotecas necesarias en Windows

### Solución

**Paso 1: Verificar Submódulo**
```powershell
git submodule status
# Debe mostrar algo como:
# -abc1234...  src/ThirdParty/SDL_mixer
# Si hay un - al inicio, el submódulo no está inicializado

# Inicializar
git submodule update --init --recursive
```

**Paso 2: Limpiar y Recompilar**
```powershell
# Elimina el caché de compilación
Remove-Item -Recurse "out/build" -Force

# Reconfigura CMake
cmake --preset windows-x86

# Recompila (observa los errores de SDL_mixer en Output → Build)
cmake --build out/build/windows-x86 --config Debug

# Si aún falla, revisa específicamente los errores OUTPUT
```

**Paso 3: Verificar Configuración en CMakeLists.txt**

En `src/CMakeLists.txt`, líneas ~28-45:

```cmake
set(SDLMIXER_MP3 ON)                    # ← Debe estar ON
set(SDLMIXER_MP3_DRMP3 ON)              # ← Debe estar ON
set(SDLMIXER_VORBIS_STB ON)             # ← Debe estar ON
set(SDLMIXER_VENDORED ON)               # ← Debe estar ON
```

Si alguno está OFF, la compilación de audio no incluirá ese formato.

---

## 🔍 Problema 4: Volumen del Juego en 0 (Software)

### Síntomas
- ✓ SDL_mixer compiló correctamente
- ✓ Assets copiados
- ✓ **Pero: Volumen aún en 0**

### Causa
El código del juego está inicializando el volumen a 0 o no está inicializando SDL_mixer.

### Solución

Busca en el código dónde se inicializa SDL_mixer:

```bash
grep -r "Mix_OpenAudio" src/source/
grep -r "Mix_Volume" src/source/
grep -r "Mix_PlayChannel" src/source/
```

Verifica que:
1. `Mix_OpenAudio()` se llama durante la inicialización
2. El volumen no está forzado a 0
3. `Mix_PlayChannel()` se llama correctamente

---

## 🔍 Problema 5: Formato de Audio No Soportado

### Síntomas
- ✓ SDL_mixer compiló
- ✓ Archivo de audio existe (ej: `.oga`, `.ogg`)
- ✓ **Pero: No se reproduce**

### Causa
El archivo de audio está en un formato que SDL_mixer no puede reproducir.

### Solución

**SDL_mixer soporta estos formatos** (en MuMain configurado):
- ✅ **MP3** (vía DRMP3)
- ✅ **OGG Vorbis** (vía STB Vorbis)
- ❌ FLAC (deshabilitado)
- ❌ Opus (deshabilitado)
- ❌ Módulos/MOD (deshabilitado)
- ❌ MIDI (deshabilitado)

**Verifica formatos:**
```powershell
Get-ChildItem "src/bin/music" -Recurse | Select-Object Extension | Group-Object Extension
```

Si encuentras otros formatos (`.wav`, `.flac`, `.ogg` con Vorbis):

**Opción A: Convertir a MP3/OGG Vorbis**
```bash
# Convertir WAV a OGG Vorbis (requiere ffmpeg instalado)
ffmpeg -i input.wav -codec:a libvorbis -q:a 4 output.ogg

# Convertir WAV a MP3
ffmpeg -i input.wav -codec:a libmp3lame -q:a 4 output.mp3
```

**Opción B: Habilitar Más Formatos en CMakeLists.txt**

Si necesitas FLAC:
```cmake
set(SDLMIXER_FLAC ON)  # En src/CMakeLists.txt línea ~40
```

Luego recompila.

---

## 🔍 Problema 6: Missing Windows Audio API

### Síntomas
- ✓ Windows 10/11
- ✓ SDL_mixer compiló
- ✓ **Pero: Sin sonido en absoluto**
- ✓ Output → Build muestra **errores de linkage Audio**

### Causa
Faltan las bibliotecas de audio de Windows (WinMM, DirectSound).

### Solución

El SDL_mixer debería vincular automáticamente. Si no:

**Opción A: En CMakeLists.txt**
```cmake
# Agregar después de add_subdirectory(ThirdParty/SDL_mixer ...)

if(WIN32)
  target_link_libraries(SDL3_mixer PUBLIC
	winmm              # Windows Multimedia
	# dsound           # DirectSound (opcional)
  )
endif()
```

**Opción B: Reinstalar Visual Studio**
- Asegúrate de tener **Windows SDK** 10.0 o superior
- Menu: Visual Studio Installer → Modify → Under SDK, selecciona Windows 10 (or 11) SDK

---

## 🔍 Problema 7: Archivos de Audio Corruptos

### Síntomas
- ✓ Archivos de audio existen
- ✓ SDL_mixer compiló
- ✓ **Pero: Crash al reproducir sonido**
- ✓ Output muestra: **"Invalid audio file"**

### Causa
Los archivos de audio están corruptos o incompletos.

### Solución

```powershell
# Verifica integridad de archivos MP3
Get-ChildItem "src/bin/music" -Filter "*.mp3" -Recurse | ForEach-Object {
  $size = $_.Length
  if ($size -lt 1000) {
	Write-Host "⚠ Archivo pequeño/corrupido: $($_.FullName) ($size bytes)"
  }
}

# Verifica que los archivos no estén vacíos
Get-ChildItem "src/bin/music" -Recurse | Where-Object {$_.Length -eq 0}
```

Si encuentras archivos corruptos, reemplázalos por copias correctas.

---

## 🎯 Checklist de Solución Paso a Paso

1. ✅ **¿Assets Existen?**
   ```powershell
   Test-Path "src/bin/music"
   ```

2. ✅ **¿Assets se Copiaron?**
   ```powershell
   Test-Path "out/build/windows-x86/Debug/assets/music"
   Get-ChildItem "out/build/windows-x86/Debug/assets/music" | Measure-Object
   ```

3. ✅ **¿SDL_mixer Compiló sin Errores?**
   - Output → Build, busca "SDL_mixer"
   - No debe haber `error:`

4. ✅ **¿Los Formatos son Correctos?**
   - `.mp3` ✅
   - `.ogg` ✅
   - Otros: ❌

5. ✅ **¿El Juego Intenta Reproducir?**
   ```bash
   grep -r "Mix_PlayChannel\|Mix_PlayMusic" src/source/
   ```

6. ✅ **¿Volumen > 0?**
   - En juego, verifica ajustes de volumen (si existen)
   - O en código: `Mix_Volume(-1, 128)` (no 0)

---

## 📊 Tabla de Diagnóstico Rápido

| Síntoma | Causa Probable | Solución |
|---------|---|---|
| Sin sonido, sin assets | Assets faltantes | Copiar desde otro cliente o crear estructura |
| Sin sonido, assets existen | No copiados | `Copy-Item "src/bin /*" "out/.../Debug/assets" -Recurse` |
| Crash al reproducir | Archivo corrupido | Reemplazar archivos de audio |
| SDL_mixer error en build | Submódulo no inicializado | `git submodule update --init --recursive` |
| Formato no soportado | FLAC/Opus/etc no habilitados | Convertir a OGG MP3, o habilitar en CMake |
| Windows audio missing | WinMM no vinculado | Agregar en CMakeLists.txt |

---

## 🔧 Comandos Rápidos Para Copiar Assets

```powershell
# Copia automática (recomendado después de compilar)
Copy-Item -Path "src/bin/*" -Destination "out/build/windows-x86/Debug/assets" -Recurse -Force

# Copia con log
$sourceDir = "src/bin"
$destDir = "out/build/windows-x86/Debug/assets"
Copy-Item -Path "$sourceDir/*" -Destination $destDir -Recurse -Force -Verbose

# Verifica la copia
Compare-Object -ReferenceObject (Get-ChildItem -Path $sourceDir -Recurse) -DifferenceObject (Get-ChildItem -Path $destDir -Recurse) -Property Name
```

---

## 🎮 Test Final: Verificar Que Funciona

Una vez hayas vuelto a compilar tras resolver el problema:

```powershell
# 1. Compila
cmake --build out/build/windows-x86 --config Debug

# 2. Copia assets (si es necesario manualmente)
Copy-Item -Path "src/bin/*" -Destination "out/build/windows-x86/Debug/assets" -Recurse -Force

# 3. Ejecuta
cd "out/build/windows-x86/Debug"
.\Main.exe connect /u127.0.0.1 /p44405

# 4. En juego, verifica volumen y reproduce sonido
```

---

## 📞 Recursos Adicionales

- **SDL_mixer Docs:** https://github.com/libsdl-org/SDL_mixer
- **FFmpeg (Convertir audio):** https://ffmpeg.org/
- **CMakePresets.json** en raíz (verificar configuración de SDL_mixer)

---

## ✅ Estado Final

Si seguiste estos pasos, **deberías tener sonido** en MuMain.

Si aún no funciona:
1. **Descarga los assets** de un cliente MuMain existente
2. **Verifica formatos** (MP3/OGG Vorbis)
3. **Reconstruye completamente** (limpia `out/`, reconfigura, recompila)

¡Buena suerte! 🔊

