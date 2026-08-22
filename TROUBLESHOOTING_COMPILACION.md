# Solución de Problemas en la Compilación de MuMain en VS 2026

## 🔧 Problemas Comunes y Soluciones

---

## 1. Error: "CMake cache generation failed"

### Síntomas
- Ventana Output → CMake muestra errores
- "CMake failed to configure"
- Rojo en la barra de estado de CMake

### Causas Posibles
- Submódulos Git no inicializados (SDL, SDL_mixer, imgui)
- .NET SDK no detectado
- MSVC/C++ Tools no instalados

### Soluciones

**Opción A: Inicializar submódulos mediante VS**
1. Menú: **Git → Manage Branches**
2. Verifica que estés en la rama `main`
3. Menú: **Git → Fetch → Initialize Repository**
4. Terminal integrada: `git submodule update --init --recursive`
5. Recarga CMake: Menú **CMake → Delete Cache and Reconfigure**

**Opción B: Terminal PowerShell**
```powershell
cd C:\path\to\MuMain

# Inicializar submódulos
git submodule update --init --recursive

# Verificar submódulos
git submodule status
# Ejemplo output:
# -abcd1234... src/ThirdParty/SDL
# -efgh5678... src/ThirdParty/SDL_mixer
# -ijkl9012... src/ThirdParty/imgui
```

**Opción C: Verificar .NET SDK**
```powershell
dotnet --version
# Debe retornar 10.0 o superior

# Si falta, instala desde:
# https://dotnet.microsoft.com/download
```

---

## 2. Error: "MSVC compiler not found"

### Síntomas
- "cl.exe no encontrado"
- "CMAKE_CXX_COMPILER not set"

### Solución
1. Abre **Developer Command Prompt for VS 2026**
2. Navega a la raíz del proyecto
3. Ejecuta:
   ```powershell
   cmake --preset windows-x86
   cmake --build out/build/windows-x86 --config Debug
   ```
   VS detectará automáticamente MSVC desde Developer Command Prompt.

---

## 3. Error: "Ninja: command not found"

### Síntomas
- "The dependency target of this file does not exist"
- "Ninja Multi-Config generator not found"

### Solución
VS 2026 incluye Ninja. Si aún así falla:

```powershell
# Instala Ninja mediante chocolatey o manualmente
choco install ninja
# o descarga desde: https://github.com/ninja-build/ninja/releases

# Verifica
ninja --version
```

---

## 4. Error: "DLL not found" (Runtime)

### Síntomas
- "VCRUNTIME140.dll not found"
- "Cannot find DLL" durante ejecución

### Solución
1. Instala **Visual C++ Redistributable** para tu arquitectura:
   - [x86 Redistribuible Visual C++](https://support.microsoft.com/es-es/help/2977003)
   - [x64 Redistribuible Visual C++](https://support.microsoft.com/es-es/help/2977003)

2. O compila con `/MT` (static libc) en lugar de `/MD`:
   - Edita `CMakeLists.txt` en `src/`:
   ```cmake
   # Agregar antes de add_library(MuClient ...)
   set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
   ```

---

## 5. Error: "Assets not found" o "Cannot find file"

### Síntomas
- Pantalla negra en ejecución
- "Asset directory not found"
- Crash al cargar texturas

### Causas
- Assets no copiados desde `src/bin/`
- `workingDirectory` incorrecto en `launch.vs.json`
- Assets no existen en `src/bin/`

### Solución

**Paso 1: Verificar que assets existen**
```
{raíz}/src/bin/
├── data/
├── gfx/
├── music/
├── sfx/
└── ... otros directorios
```

Si está vacío, el repositorio no incluye assets completos (es normal en forks).

**Paso 2: Copiar assets manualmente (si tienes)**
```powershell
# Después de compilar, copia assets a:
Copy-Item -Recurse "src/bin/*" "out/build/windows-x86/Debug/"
```

**Paso 3: Verificar `launch.vs.json`**
```json
{
  "workingDirectory": "${projectDir}/src/bin"  // ← Debe apuntar aquí
}
```

---

## 6. Error: "Connection refused" (Servidor no accesible)

### Síntomas
- Cliente inicia pero no conecta
- "Unable to connect to 127.0.0.1:44405"
- Timeout de conexión

### Solución

**Paso 1: Verificar que OpenMU está corriendo**
```powershell
# En otra terminal, verifica el puerto
netstat -ano | findstr :44405
# Debe mostrar: TCP 127.0.0.1:44405 LISTENING

# O usa PowerShell:
Get-NetTCPConnection -LocalPort 44405
```

**Paso 2: Verificar firewall**
1. Menú de inicio → **Firewall de Windows Defender**
2. "Permitir una aplicación..." → Agregar `Main.exe`
3. Marcar "Privado" en la lista

**Paso 3: Probar con `telnet`**
```powershell
Test-NetConnection 127.0.0.1 -Port 44405 -Verbose
# Debe retornar: TcpTestSucceeded : True
```

---

## 7. Error: "Native AOT compilation failed"

### Síntomas
- Error en compilación de la librería C#
- "Failed to compile MUnique.OpenMU.Network"
- .NET compiler error durante CMake build

### Solución

**Paso 1: Verificar .NET SDK**
```powershell
dotnet --version
dotnet workload list
```

**Paso 2: Instalar workload Native AOT**
```powershell
dotnet workload install wasi-experimental
dotnet workload install wasi-sdk
```

**Paso 3: Limpiar caché y reconstruir**
```powershell
# Eliminar directorios intermedios
Remove-Item -Recurse "out/build" -Force
Remove-Item -Recurse ".vs" -Force (excepto launch.vs.json)

# Reconfigura
cmake --preset windows-x86
```

---

## 8. Error: "ImGui editor not working" (F12 no hace nada)

### Síntomas
- Compilas con `windows-x86-mueditor`
- Pulsa F12 en juego pero no aparece el editor

### Causas
- `ENABLE_EDITOR` no está activado en CMakePresets
- Compilaste con preset incorrecto

### Solución

```powershell
# Asegúrate de compilar con el preset correcto:
cmake --preset windows-x86-mueditor  # o windows-x64-mueditor

cmake --build out/build/windows-x86-mueditor --config Debug

# Luego en VS, selecciona el preset correcto
# Barra de herramientas CMake → Select a Configuration → windows-x86-mueditor
```

---

## 9. Error: "Git submodule out of sync"

### Síntomas
- "Submodule at ... is not initialized"
- `src/ThirdParty/SDL` está vacío

### Solución

```powershell
cd C:\path\to\MuMain

# Reinicializar todos los submódulos
git submodule deinit -f --all
git submodule update --init --recursive

# Verificar cada uno
cd src/ThirdParty/SDL
git status
# Debe mostrar "nothing to commit, working tree clean"
```

---

## 10. Error: "Main.exe has exited with code -1"

### Síntomas
- Ejecutable inicia y cierra inmediatamente
- Sin mensajes de error
- Ocurre en Debug y Release

### Causas
- `workingDirectory` incorrecto
- Assets faltantes
- Inicialización OpenGL falla
- Librería .NET AOT no encontrada

### Solución

**Paso 1: Ejecutar desde línea de comandos**
```powershell
cd "out/build/windows-x86/Debug"
.\Main.exe
# Ver output directo en terminal
```

**Paso 2: Ejecutar desde terminal del Developer Prompt**
```powershell
# Abre "Developer Command Prompt for VS 2026"
cd C:\path\to\MuMain\out\build\windows-x86\Debug
Main.exe connect /u127.0.0.1 /p44405
```

**Paso 3: Verificar logs (si la aplicación escribe)**
```
C:\path\to\MuMain\out\build\windows-x86\Debug\*.log
```

---

## 11. Error: "Linker error: unresolved external symbol"

### Síntomas
- "LNK2001: unresolved external symbol"
- "LNK1120: X unresolved externals"

### Causas
- Librería C# Native AOT no compilada correctamente
- Librería .NET no enlazada

### Solución

```powershell
# Limpia y recompila todo
cmake --preset windows-x86
cmake --build out/build/windows-x86 --config Debug --verbose

# Verifica que en el output aparezca:
# "Compiling .NET library for Native AOT..."
# "Linking X.obj files..."
```

---

## 12. Error: "Port 44405 already in use"

### Síntomas
- No puedes iniciar el servidor OpenMU
- "Address already in use"

### Solución

**Opción A: Cerrar proceso anterior**
```powershell
Get-Process | Where-Object {$_.Path -match "OpenMU|MuMain"}
# Luego:
Stop-Process -Name "OpenMU" -Force
```

**Opción B: Usar puerto diferente**
1. Edita `launch.vs.json`:
   ```json
   "args": "connect /u127.0.0.1 /p44406"  // Cambia port de 44405 a 44406
   ```
2. Configura OpenMU para escuchar en el mismo puerto

---

## 🔍 Checklist de Diagnóstico Rápido

Si nada funciona, copia y ejecuta este script:

```powershell
# 1. Verificar .NET
Write-Host "=== .NET SDK ===" -ForegroundColor Green
dotnet --version

# 2. Verificar CMake
Write-Host "=== CMake ===" -ForegroundColor Green
cmake --version

# 3. Verificar Ninja
Write-Host "=== Ninja ===" -ForegroundColor Green
ninja --version

# 4. Verificar submódulos
Write-Host "=== Submódulos ===" -ForegroundColor Green
cd src/ThirdParty/SDL
if (Test-Path CMakeLists.txt) { Write-Host "✓ SDL" } else { Write-Host "✗ SDL" }
cd ../SDL_mixer
if (Test-Path CMakeLists.txt) { Write-Host "✓ SDL_mixer" } else { Write-Host "✗ SDL_mixer" }
cd ../..

# 5. Verificar puerto OpenMU
Write-Host "=== Puerto OpenMU ===" -ForegroundColor Green
Test-NetConnection 127.0.0.1 -Port 44405 -Verbose
```

---

## 📞 Si Aún Tienes Problemas

1. **Revisa los logs más recientes:**
   - Menú: **View → Output** (Ctrl+Alt+O)
   - Selecciona cada opción de "Show output from:"
	 - CMake
	 - Build
	 - Debug

2. **Busca mensajes de error exactos** en los logs

3. **Descarga la última versión de Visual Studio 2026** con las workloads más recientes

4. **Considera reportar en el repositorio:** https://github.com/sven-n/MuMain/issues

---

## 📚 Recursos Adicionales

- [Visual Studio CMake Documentation](https://learn.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio)
- [CMakePresets Esquema](https://cmake.org/cmake/help/latest/manual/cmake-presets.7.html)
- [.NET Native AOT Deployment](https://learn.microsoft.com/en-us/dotnet/core/deploying/native-aot/)
- [OpenMU Documentation](https://github.com/MUnique/OpenMU) (si es necesario configurar servidor)

---

Espero que esto te ayude. Si encuentras un problema no listado aquí, **abre un issue en el repositorio MuMain** con los logs completos. 🎮

