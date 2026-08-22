# JSON Puro: Configuración launch.vs.json Completa para MuMain

## Archivo `.vs/launch.vs.json`: Especificación Técnica

Este documento contiene la estructura JSON exacta del archivo `launch.vs.json` utilizado en MuMain para Visual Studio 2026.

---

## ✅ JSON Válido (Copiar Directamente)

```json
{
  "version": "0.2.1",
  "defaults": {},
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
	  "name": "MuMain - Local OpenMU Server (x86 Debug)",
	  "args": "connect /u127.0.0.1 /p44405",
	  "workingDirectory": "${projectDir}/src/bin"
	},
	{
	  "type": "default",
	  "project": "CMakeLists.txt",
	  "projectTarget": "Main",
	  "name": "MuMain - Local OpenMU Server (x64 Debug)",
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
	{
	  "type": "default",
	  "project": "CMakeLists.txt",
	  "projectTarget": "Main",
	  "name": "MuMain - Default (No Args)",
	  "args": "",
	  "workingDirectory": "${projectDir}/src/bin"
	}
  ]
}
```

---

## 🔧 Personalizar para Diferentes Servidores

### Patrón 1: Servidor Remoto

```json
{
  "type": "default",
  "project": "CMakeLists.txt",
  "projectTarget": "Main",
  "name": "MuMain - Servidor Remoto (192.168.1.100:44405)",
  "args": "connect /u192.168.1.100 /p44405",
  "workingDirectory": "${projectDir}/src/bin"
}
```

### Patrón 2: Servidor con Puerto Personalizado

```json
{
  "type": "default",
  "project": "CMakeLists.txt",
  "projectTarget": "Main",
  "name": "MuMain - Servidor Local (Puerto 5000)",
  "args": "connect /u127.0.0.1 /p5000",
  "workingDirectory": "${projectDir}/src/bin"
}
```

### Patrón 3: Desarrollo Local (Sin Conexión)

```json
{
  "type": "default",
  "project": "CMakeLists.txt",
  "projectTarget": "Main",
  "name": "MuMain - Development (Offline)",
  "args": "",
  "workingDirectory": "${projectDir}/src/bin"
}
```

### Patrón 4: Múltiples Servidores Simultáneamente

```json
{
  "configurations": [
	{
	  "type": "default",
	  "project": "CMakeLists.txt",
	  "projectTarget": "Main",
	  "name": "Server A (Dev) - 127.0.0.1:44405",
	  "args": "connect /u127.0.0.1 /p44405",
	  "workingDirectory": "${projectDir}/src/bin"
	},
	{
	  "type": "default",
	  "project": "CMakeLists.txt",
	  "projectTarget": "Main",
	  "name": "Server B (Staging) - 192.168.1.100:44405",
	  "args": "connect /u192.168.1.100 /p44405",
	  "workingDirectory": "${projectDir}/src/bin"
	},
	{
	  "type": "default",
	  "project": "CMakeLists.txt",
	  "projectTarget": "Main",
	  "name": "Server C (Production) - prod.example.com:44405",
	  "args": "connect /uprod.example.com /p44405",
	  "workingDirectory": "${projectDir}/src/bin"
	}
  ]
}
```

---

## 📋 Sintaxis y Validación

### Estructura Raíz

| Clave | Tipo | Requerido | Descripción |
|-------|------|-----------|-------------|
| `version` | string | ✅ | Versión del esquema (ej: `"0.2.1"`) |
| `defaults` | object | ❌ | Configuración por defecto (vacío `{}`) |
| `configurations` | array | ✅ | Array de perfiles de ejecución |

### Estructura de Cada Configuración

| Clave | Tipo | Requerido | Descripción | Ejemplo |
|-------|------|-----------|-------------|---------|
| `type` | string | ✅ | Tipo: `"default"` para CMake | `"default"` |
| `project` | string | ✅ | Archivo CMakeLists.txt | `"CMakeLists.txt"` |
| `projectTarget` | string | ✅ | Target CMake a ejecutar | `"Main"` |
| `name` | string | ✅ | Nombre legible en VS | `"MuMain - Local"` |
| `args` | string | ❌ | Argumentos CLI | `"connect /u127.0.0.1 /p44405"` |
| `workingDirectory` | string | ❌ | Directorio de trabajo | `"${projectDir}/src/bin"` |

---

## 🔒 Validación JSON

### Puntos Críticos

1. **Comillas dobles obligatorias:**
   ```json
   ✅ CORRECTO:  "name": "MuMain - Local"
   ❌ INCORRECTO: 'name': 'MuMain - Local'
   ```

2. **Sin comas finales:**
   ```json
   ✅ CORRECTO:
   {
	 "name": "MuMain",
	 "args": "connect /u127.0.0.1 /p44405"
   }

   ❌ INCORRECTO:
   {
	 "name": "MuMain",
	 "args": "connect /u127.0.0.1 /p44405",  ← Coma colgante
   }
   ```

3. **Escapes en rutas:**
   ```json
   ✅ CORRECTO:  "workingDirectory": "${projectDir}/src/bin"
   ✅ CORRECTO:  "workingDirectory": "${projectDir}\\src\\bin"
   ❌ INCORRECTO: "workingDirectory": "${projectDir}\src\bin"
   ```

### Validar Online

Copia el JSON a: https://jsonlint.com/

---

## 🎯 Argumentos del Cliente (Sintaxis)

### Formato General

```
Main.exe [connect] [/u<IP>] [/p<PUERTO>] [--editor]
```

### Componentes

| Componente | Formato | Ejemplo | Descripción |
|-----------|---------|---------|-------------|
| Conexión | `connect` | `connect` | Activa modo conexión (opcional) |
| IP | `/u<IP>` | `/u127.0.0.1` | IP del servidor |
| Puerto | `/p<NUM>` | `/p44405` | Puerto (números solo) |
| Editor | `--editor` | `--editor` | Activa editor ImGui (F12) |

### Ejemplos de Argumentos Válidos

```
ARGS: ""
→ Sin argumentos, menú principal offline

ARGS: "connect"
→ Conectar a servidor predeterminado

ARGS: "connect /u127.0.0.1"
→ Conectar a localhost, puerto por defecto

ARGS: "connect /u127.0.0.1 /p44405"
→ Conectar a localhost:44405 (ESTÁNDAR OpenMU)

ARGS: "connect /u192.168.1.100 /p44405"
→ Conectar a servidor remoto

ARGS: "connect /u127.0.0.1 /p44405 --editor"
→ Conectar a localhost:44405, editor activado
```

---

## 📂 Macros de Ruta Disponibles

| Macro | Significado | Ejemplo Expandido |
|-------|-----------|-------------------|
| `${sourceDir}` | Raíz del repositorio | `C:\Users\User\MuMain` |
| `${projectDir}` | Raíz del repositorio | `C:\Users\User\MuMain` |
| `${workspaceRoot}` | Raíz del workspace en VS | `C:\Users\User\MuMain` |

### Rutas Comunes

```json
// Assets del juego (recomendado)
"workingDirectory": "${projectDir}/src/bin"
→ C:\Users\User\MuMain\src\bin

// Directorio de compilación (Debug)
"workingDirectory": "${projectDir}/out/build/windows-x86/Debug"
→ C:\Users\User\MuMain\out\build\windows-x86\Debug

// Raíz del proyecto
"workingDirectory": "${projectDir}"
→ C:\Users\User\MuMain
```

---

## 🔄 Comportamiento en Visual Studio 2026

### Cómo Lee VS el `launch.vs.json`

1. VS abre la carpeta raíz del repositorio
2. Lee `.vs/launch.vs.json` automáticamente
3. Cada `configuration` aparece en el desplegable "Startup Item"
4. Al seleccionar un perfil y pulsar F5:
   - VS ejecuta el target CMake especificado (`projectTarget`)
   - Con los argumentos en `args`
   - Desde el directorio en `workingDirectory`

### Actualización Automática

- Si editas `.vs/launch.vs.json` y guardas, VS recarga los perfiles **automáticamente**
- No necesita reiniciar VS

### Orden de Aparición

Los perfiles aparecen en el desplegable en el mismo orden que en el JSON.

---

## 🛠️ Troubleshooting JSON

### Error: "Invalid JSON"

```powershell
# Validar desde PowerShell
$json = Get-Content ".vs/launch.vs.json" -Raw
$json | ConvertFrom-Json  # Si falla, mira el error
```

### Error: "Profile not found"

```json
// Verificar que "projectTarget" existe en CMakeLists.txt
"projectTarget": "Main"  // Debe existir un add_executable(Main ...)
```

### Error: "Working directory not found"

```json
// Verificar que la ruta existe
"workingDirectory": "${projectDir}/src/bin"
// src/bin debe existir, aunque esté vacío
```

---

## 📝 Plantilla Minimalista

```json
{
  "version": "0.2.1",
  "defaults": {},
  "configurations": [
	{
	  "type": "default",
	  "project": "CMakeLists.txt",
	  "projectTarget": "Main",
	  "name": "MuMain",
	  "args": "connect /u127.0.0.1 /p44405",
	  "workingDirectory": "${projectDir}/src/bin"
	}
  ]
}
```

---

## 📚 Referencias Oficiales

- [Documentación de launch.vs.json (Microsoft)](https://learn.microsoft.com/en-us/cpp/build/launch-vs-schema-reference)
- [CMake Projects in Visual Studio](https://learn.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio)
- [JSON Specification](https://www.json.org/)

---

## ✅ Verificación Final

Checklist antes de usar:

- [ ] JSON válido (sin errores en validador)
- [ ] Archivo ubicado en `.vs/launch.vs.json` (exactamente)
- [ ] `type` es `"default"`
- [ ] `project` es `"CMakeLists.txt"`
- [ ] `projectTarget` existe en CMakeLists.txt (`Main`)
- [ ] `workingDirectory` apunta a `${projectDir}/src/bin`
- [ ] `args` tiene formato: `"connect /u<IP> /p<PUERTO>"`
- [ ] Sin comas finales en objetos/arrays
- [ ] Comillas dobles en todo

---

**Archivo `launch.vs.json` listo para usar en MuMain + Visual Studio 2026.** ✔️

