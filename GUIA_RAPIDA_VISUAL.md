# MuMain: Guía Visual Rápida (VS 2026)

## 🎯 Flujo Completo en 5 Pasos

```
┌─────────────────────────────────────────────────────────────┐
│  1. VERIFICAR REQUISITOS                                    │
│     ✓ VS 2026 (C++, .NET workloads)                        │
│     ✓ .NET SDK 10.0+                                        │
│     ✓ CMake 3.25+                                           │
│     ✓ Submódulos inicializados                              │
└──────────────────────┬──────────────────────────────────────┘
					   ↓
┌─────────────────────────────────────────────────────────────┐
│  2. CONFIGURAR CMAKE                                        │
│     → Ventana Output (Ctrl+Alt+O) → CMake                  │
│     → Barra CMake: Select a Configuration                   │
│     → Elegir: windows-x86  (o tu preferencia)              │
└──────────────────────┬──────────────────────────────────────┘
					   ↓
┌─────────────────────────────────────────────────────────────┐
│  3. COMPILAR                                                │
│     → Build → Build All  (Ctrl+Shift+B)                    │
│     → Esperar a que termine sin errores críticos            │
│     → Assets se copian automáticamente a out/build/...      │
└──────────────────────┬──────────────────────────────────────┘
					   ↓
┌─────────────────────────────────────────────────────────────┐
│  4. SELECCIONAR PERFIL DE EJECUCIÓN                         │
│     → Barra CMake: Startup Item (desplegable)               │
│     → Elegir: "MuMain - Local OpenMU Server"               │
│     → (Verificar que launch.vs.json existe)                │
└──────────────────────┬──────────────────────────────────────┘
					   ↓
┌─────────────────────────────────────────────────────────────┐
│  5. EJECUTAR                                                │
│     → F5  (Debug con breakpoints)                           │
│     → Ctrl+F5  (Sin debug, más rápido)                      │
│     → El cliente conecta a 127.0.0.1:44405                 │
│     → ¡A jugar! 🎮                                         │
└─────────────────────────────────────────────────────────────┘
```

---

## ⚡ Comandos Rápidos

### Terminal PowerShell (Developer Command Prompt)

```powershell
# Navegar a la raíz del proyecto
cd C:\path\to\MuMain

# OPCIÓN 1: Compilación rápida (sin debug)
cmake --preset windows-x86
cmake --build out/build/windows-x86 --config Release

# OPCIÓN 2: Compilación con debug
cmake --preset windows-x86
cmake --build out/build/windows-x86 --config Debug

# OPCIÓN 3: Con editor ImGui
cmake --preset windows-x86-mueditor
cmake --build out/build/windows-x86-mueditor --config Debug

# Ejecutar después de compilar
cd out/build/windows-x86/Debug
.\Main.exe connect /u127.0.0.1 /p44405
```

---

## 🎮 Uso de Perfiles en VS 2026

### Ubicación Visual en la Interfaz

```
Visual Studio 2026
│
├─── Barra de Herramientas (arriba)
│    ├─── [CMake] [💾 Build All] [▶ Debug]
│    │
│    ├─── Desplegable 1: "Select a Configuration"
│    │    └─── ✓ windows-x86
│    │         ✓ windows-x86-mueditor
│    │         ✓ windows-x64
│    │         ✓ windows-x64-mueditor
│    │
│    └─── Desplegable 2: "Startup Item"  ← AQUÍ con launch.vs.json
│         └─── ✓ MuMain - Local OpenMU Server
│             ✓ MuMain - Editor Mode (F12)
│             ✓ MuMain - Default (No Args)
│
└─── Panel Lateral: CMake Project Outline
	 └─── Main (Ejecutable)
```

### Acciones Comunes

| Tarea | Atajo | Menú |
|-------|-------|------|
| Compilar todo | `Ctrl+Shift+B` | Build → Build All |
| Ejecutar (Debug) | `F5` | Debug → Start Debugging |
| Ejecutar (Sin Debug) | `Ctrl+F5` | Debug → Start Without Debugging |
| Pausar | `Alt+Break` | Debug → Break All |
| Parar | `Shift+F5` | Debug → Stop Debugging |
| Siguiente línea | `F10` | Debug → Step Over |
| Entrar en función | `F11` | Debug → Step Into |
| Salir de función | `Shift+F11` | Debug → Step Out |

---

## 📂 Estructura de Directorios

```
MuMain/
│
├── CMakeLists.txt           ← CMake raíz
├── CMakePresets.json        ← Definición de presets (x86, x64, editor)
│
├── .vs/
│   └── launch.vs.json       ← CREADO: Perfiles de ejecución (tú aquí)
│
├── src/
│   ├── CMakeLists.txt
│   ├── bin/                 ← ASSETS del juego (gráficos, música, datos)
│   │   ├── data/
│   │   ├── gfx/
│   │   ├── music/
│   │   └── sfx/
│   └── source/              ← Código fuente C++
│       ├── App/Platform/Windows/Winmain.cpp   (entry point)
│       ├── Engine/
│       └── ...
│
├── src/ThirdParty/
│   ├── SDL/                 ← Librería gráfica
│   ├── SDL_mixer/           ← Audio
│   └── imgui/               ← Editor (cuando ENABLE_EDITOR=ON)
│
├── out/build/               ← SALIDA después de compilar
│   ├── windows-x86/
│   │   ├── Debug/
│   │   │   ├── Main.exe     ← El cliente compilado
│   │   │   ├── assets/      ← Assets copiados (automático)
│   │   │   └── (DLLs, .obj files, etc)
│   │   └── Release/
│   │       └── (similar)
│   │
│   └── windows-x64/
│       └── (similar a x86)
│
└── (otros archivos)
```

---

## 🔗 Parámetros de Conexión

### Sintaxis del Cliente

```bash
Main.exe [connect [/u<IP>] [/p<PUERTO>]] [--editor]
```

### Ejemplos

| Comando | Efecto |
|---------|--------|
| `Main.exe` | Inicia sin conectar (menú principal) |
| `Main.exe connect` | Conecta a servidor por defecto (no especificado) |
| `Main.exe connect /u127.0.0.1` | Conecta a localhost, puerto por defecto |
| `Main.exe connect /u127.0.0.1 /p44405` | Conecta a localhost:44405 (OpenMU) |
| `Main.exe connect /u192.168.1.100 /p44405` | Conecta a servidor remoto |
| `Main.exe connect /u127.0.0.1 /p44405 --editor` | Conexión + Editor ImGui (F12) |

---

## 🔀 Cambiar Configuración

### Cambiar de x86 a x64

1. **En VS 2026:**
   ```
   Barra CMake → Select a Configuration → windows-x64
   ```

2. **Recompila:**
   ```
   Ctrl+Shift+B
   ```

3. **Ejecuta:**
   ```
   F5
   ```

### Cambiar a Release (Optimizado)

El desplegable "Startup Item" mostrará automáticamente:
- `x86 Debug`
- `x86 Release`
- `x64 Debug`
- `x64 Release`

Selecciona `Release` para mayor velocidad (sin símbolos de debug).

### Incluir Editor ImGui

1. Cambia el preset a `windows-x86-mueditor` (o x64-mueditor)
2. Recompila
3. En juego, pulsa **F12** para activar/desactivar el editor

---

## 🆘 Diagnóstico Rápido

### El juego no inicia

```powershell
# 1. ¿Está compilado?
Test-Path "out/build/windows-x86/Debug/Main.exe"

# 2. ¿Existen assets?
Test-Path "out/build/windows-x86/Debug/assets"

# 3. ¿Escucha OpenMU?
Test-NetConnection 127.0.0.1 -Port 44405
```

### El juego inicia pero no conecta

```powershell
# 1. ¿Escucha OpenMU?
Get-NetTCPConnection -LocalPort 44405

# 2. ¿Firewall permite?
netsh advfirewall show allprofiles

# 3. Intenta manual:
cd "out/build/windows-x86/Debug"
.\Main.exe connect /u127.0.0.1 /p44405
```

---

## 📝 Checklist Final

Antes de decir "¡No funciona!":

- [ ] ¿Instalaste .NET SDK 10.0+?
- [ ] ¿Iniciaste los submódulos? (`git submodule update --init --recursive`)
- [ ] ¿Compilaste exitosamente? (Ctrl+Shift+B sin errores críticos)
- [ ] ¿OpenMU escucha en 127.0.0.1:44405?
- [ ] ¿Existe `.vs/launch.vs.json`?
- [ ] ¿Permisos de Firewall para Main.exe?
- [ ] ¿Assets en `src/bin/` o copiados a `out/build/.../Debug/`?

---

## 🎯 Resumen de un Vistazo

```
ANTES (Primera vez):
1. git submodule update --init --recursive
2. (Espera a que CMake cache se genere)

CADA VEZ que compilas:
1. Ctrl+Shift+B
2. F5 (o Ctrl+F5)

CUANDO ALGO FALLA:
1. Revisa Output → CMake y Output → Build
2. Limpia: CMake → Delete Cache and Reconfigure
3. Intenta desde PowerShell directamente
```

---

## 📚 Documentos Relacionados

- **GUIA_COMPILACION_MUMAIN_VS2026.md** - Guía detallada paso a paso
- **REFERENCIA_LAUNCH_VS_JSON.md** - Referencia completa del archivo launch.vs.json
- **TROUBLESHOOTING_COMPILACION.md** - Soluciones a errores específicos

---

**Buena suerte compilando MuMain. Si todo falla, siempre puedes borrar la carpeta `out/` y empezar de cero:** 😄

```powershell
Remove-Item -Recurse "out/" -Force
# Luego: Ctrl+Shift+B (reconstruir todo desde cero)
```

