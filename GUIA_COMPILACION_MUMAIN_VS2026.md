# Guía de Compilación de MuMain en Visual Studio 2026

## 📋 Resumen Rápido

El cliente **MuMain** es un fork de Season 5.2/6.3 con soporte **Native AOT** (compilación a código nativo) para la librería de red en C#. Este documento te guiará paso a paso para compilarlo en **Visual Studio 2026** y configurarlo para conectar a un servidor OpenMU local.

---

## 🔧 Requisitos Previos Confirmados

Verifica que tienes instalado:

1. **Visual Studio 2026** con cargas de trabajo:
   - ✅ _Desarrollo para el escritorio con C++_ (CMake Tools para Windows + MSVC)
   - ✅ _Desarrollo de escritorio de .NET_ (para compilar la librería C# con Native AOT)

2. **.NET SDK 10.0 o superior**
   - Verifica en terminal: `dotnet --version`

3. **CMake 3.25 o superior**
   - El proyecto ya define esto en `CMakePresets.json`

---

## 🚀 Paso 1: Verificar la Configuración de CMake en Visual Studio 2026

### 1.1 Abrir el Proyecto CMake

- **Ya deberías tener la carpeta raíz abierta** en Visual Studio 2026
- VS detectará automáticamente el archivo `CMakePresets.json` en la raíz

### 1.2 Confirmar la Generación del Caché de CMake

1. Abre la ventana **Output** (Salida):
   - Menú: **View → Output** o `Ctrl + Alt + O`
   - En el desplegable de "Show output from", selecciona: `CMake`

2. Verificar que el caché se genere correctamente:
   - Deberías ver mensajes como:
	 ```
	 The C compiler identification is MSVC
	 The CXX compiler identification is MSVC
	 Configuring for 64-bit (x64) build
	 ```

3. Si hay **errores de submódulos**, VS puede resolver automáticamente:
   - Git integrado en VS → **Git Changes → Initialize Repository** (si es necesario)
   - O ejecuta en terminal: `git submodule update --init --recursive`

### 1.3 Seleccionar el Preset/Configuración de Compilación

En la barra de herramientas de CMake:

1. **Selecciona la arquitectura y modo:**
   - `windows-x86` → Build x86 sin Editor
   - `windows-x86-mueditor` → Build x86 **con Editor ImGui** (activable con F12 en juego)
   - `windows-x64` → Build x64 sin Editor
   - `windows-x64-mueditor` → Build x64 **con Editor ImGui**

2. **Selecciona la configuración de compilación:**
   - `Debug` → Con símbolos de depuración (más lento, útil para debugging)
   - `Release` → Optimizado, sin símbolos (más rápido para jugar)

**Recomendación para comenzar:** `windows-x86` + `Debug`

---

## 🛠️ Paso 2: Compilar el Proyecto

### 2.1 Compilación Completa

Opción A - Menú Visual Studio:
```
Build → Build All   (o Ctrl + Shift + B)
```

Opción B - Terminal integrada de VS:
```powershell
cmake --build out/build/windows-x86 --config Debug
```

### 2.2 Monitorear la Compilación

- **Ventana Output** → Campo "Show output from" selecciona `Build`
- Deberías ver:
  1. Compilación de SDL3 (ThirdParty/SDL)
  2. Compilación de SDL3_mixer (ThirdParty/SDL_mixer)
  3. Compilación del motor (MuClient static lib)
  4. Compilación de la librería C# Native AOT (MUnique.OpenMU.Network)
  5. Compilación del ejecutable Main (Main.exe)
  6. **Copia de assets** del directorio `src/bin/` al directorio de salida

### 2.3 Ubicación de los Binarios

Los binarios compilados estarán en:

```
out/build/windows-x86/
├── Debug/
│   ├── Main.exe
│   ├── assets/          (copiados automáticamente desde src/bin/)
│   ├── bin/             (DLLs de Windows)
│   └── ...
└── Release/
	├── Main.exe
	├── assets/
	└── ...
```

**Los assets se copian automáticamente** tras cada compilación (si el caché está actualizado).

---

## 🎮 Paso 3: Configuración del Perfil de Inicio (`launch.vs.json`)

Ya he creado el archivo `.vs/launch.vs.json` con múltiples perfiles de ejecución.

### 3.1 Perfiles Disponibles

En Visual Studio 2026, abre el desplegable "Startup Item" (junto a Build All):

| Perfil | Descripción | Argumentos |
|--------|-------------|-----------|
| **MuMain - Local OpenMU Server** | Conexión a `127.0.0.1:44405` | `connect /u127.0.0.1 /p44405` |
| **MuMain - Editor Mode (F12)** | Igual que arriba, pero con editor de ImGui activable con F12 | `connect /u127.0.0.1 /p44405 --editor` |
| **MuMain - Default (No Args)** | Sin argumentos (modo offline / menú principal) | _(vacío)_ |

### 3.2 Cómo Usar los Perfiles

1. **Selecciona un perfil** en el desplegable "Startup Item"
2. Pulsa **F5** o **Debug → Start Debugging**
3. El juego se lanzará con los argumentos configurados

### 3.3 Estructura del `launch.vs.json` Creado

```json
{
  "version": "0.2.1",
  "configurations": [
	{
	  "type": "default",
	  "project": "CMakeLists.txt",
	  "projectTarget": "Main",
	  "name": "MuMain - Local OpenMU Server",
	  "args": "connect /u127.0.0.1 /p44405",
	  "workingDirectory": "${projectDir}/src/bin"
	},
	{
	  "type": "default",
	  "project": "CMakeLists.txt",
	  "projectTarget": "Main",
	  "name": "MuMain - Editor Mode (F12)",
	  "args": "connect /u127.0.0.1 /p44405 --editor",
	  "workingDirectory": "${projectDir}/src/bin"
	},
	// ... más perfiles
  ]
}
```

**Notas:**
- `workingDirectory`: Apunta a `src/bin` (donde están los assets del juego: gráficos, música, datos)
- `args`: Argumentos de línea de comandos: `connect /u<IP> /p<PUERTO>`

---

## 📡 Paso 4: Verificar Conectividad con el Servidor OpenMU Local

### 4.1 Prerequisitos del Servidor

Antes de ejecutar el cliente, asegúrate de que:

1. **Servidor OpenMU está corriendo** en local:
   - Servicio ConnectServer escuchando en `127.0.0.1:44405`
   - (O en el puerto que hayas configurado)

2. **Firewall de Windows** permite conexiones en loopback (normalmente permitido por defecto)

### 4.2 Ejecución del Cliente

Con el perfil de inicio **"MuMain - Local OpenMU Server"** seleccionado:

1. Pulsa **F5** o **Debug → Start Debugging**
2. El juego debería:
   - Inicializar OpenGL
   - Cargar los assets desde `src/bin/`
   - Intentar conectar a `127.0.0.1:44405`
   - Mostrar la pantalla de login si la conexión es exitosa

### 4.3 Solución de Problemas de Conexión

| Problema | Causa Probable | Solución |
|----------|---|---|
| "Connection refused" | Servidor no escuchando en 44405 | Verificar que OpenMU está corriendo |
| "Timeout" | Firewall bloqueando | Permitir Main.exe en Windows Defender |
| Pantalla negra (sin error) | Assets no encontrados | Verificar que assets están en mismo directorio que Main.exe |
| "Asset file not found" | Assets no fueron copiados tras build | Recompilar (`Ctrl + Shift + B`) |

---

## 🔍 Paso 5: Alternativas de Compilación Avanzadas

### 5.1 Compilación desde Terminal (PowerShell)

```powershell
# Configurar para x86 Debug
cmake --preset windows-x86

# Compilar Debug
cmake --build out/build/windows-x86 --config Debug

# Compilar Release (más rápido en ejecución)
cmake --build out/build/windows-x86 --config Release

# Para x64
cmake --preset windows-x64
cmake --build out/build/windows-x64 --config Debug
```

### 5.2 Compilación con Editor (ImGui)

```powershell
# Configurar con Editor habilitado (x86)
cmake --preset windows-x86-mueditor

# Compilar
cmake --build out/build/windows-x86-mueditor --config Debug

# El editor se activa en juego con F12
```

---

## ✅ Checklist Final de Compilación

- [ ] Visual Studio 2026 con **C++ Development** y **.NET Development**
- [ ] .NET SDK 10.0+ instalado
- [ ] CMake caché generado (sin errores en Output → CMake)
- [ ] Preset seleccionado: `windows-x86` (recomendado para empezar)
- [ ] Compilación exitosa: `Ctrl + Shift + B` sin errores críticos
- [ ] Archivo `launch.vs.json` creado en `.vs/`
- [ ] Perfil de inicio seleccionado: _"MuMain - Local OpenMU Server"_
- [ ] Servidor OpenMU corriendo en `127.0.0.1:44405`
- [ ] Ejecutar: F5 → Juego debe conectar y mostrar login

---

## 📚 Referencias

- **Repositorio:** https://github.com/sven-n/MuMain.git
- **CMakePresets.json:** Define los presets de compilación (x86, x64, con/sin Editor)
- **launch.vs.json:** Define los perfiles de ejecución/debug (ubicado en `.vs/`)
- **Assets:** Ubicados en `src/bin/`, copiados automáticamente tras build

---

## 🆘 Soporte Adicional

Si encuentras problemas:

1. **Errores de CMake:** Revisa la ventana Output → CMake
2. **Errores de compilación:** Output → Build (busca `error C`)
3. **Errores de runtime:** Output → Debug (busca excepciones)
4. **Reiniciar CMake cache:** Menú CMake → Delete Cache

¡A jugar! 🎮

