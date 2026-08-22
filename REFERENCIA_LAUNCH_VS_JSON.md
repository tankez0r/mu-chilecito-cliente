# Referencia Completa del launch.vs.json para MuMain en Visual Studio 2026

## 📄 Ubicación del Archivo

```
{raíz del repositorio}/.vs/launch.vs.json
```

---

## 📋 Estructura JSON Completa

El archivo `.vs/launch.vs.json` define los **perfiles de depuración e ejecución** que aparecen en el desplegable de "Startup Item" en Visual Studio 2026.

### Formato General

```json
{
  "version": "0.2.1",                           // Versión del esquema de VS
  "defaults": {},                               // Configuración por defecto (vacía aquí)
  "configurations": [                           // Array de perfiles
	{
	  "type": "default",                        // Tipo: "default" para ejecutables CMake
	  "project": "CMakeLists.txt",              // Archivo CMake raíz
	  "projectTarget": "Main",                  // Target CMake a ejecutar
	  "name": "Nombre del Perfil",              // Nombre que aparece en el desplegable
	  "args": "argumentos de línea de comandos",// Parámetros para el ejecutable
	  "workingDirectory": "${projectDir}/..."  // Directorio de trabajo
	}
  ]
}
```

---

## 🎯 Perfiles Disponibles en MuMain

### 1. Conexión a Servidor OpenMU Local (Recomendado)

```json
{
  "type": "default",
  "project": "CMakeLists.txt",
  "projectTarget": "Main",
  "name": "MuMain - Local OpenMU Server",
  "args": "connect /u127.0.0.1 /p44405",
  "workingDirectory": "${projectDir}/src/bin"
}
```

**Descripción:**
- Se conecta automáticamente a `127.0.0.1` (localhost) en puerto `44405`
- Directorio de trabajo: `src/bin/` (donde están los assets del juego)

**Uso:**
```
F5 → Conexión automática al servidor local
```

---

### 2. Editor de ImGui Activado (F12)

```json
{
  "type": "default",
  "project": "CMakeLists.txt",
  "projectTarget": "Main",
  "name": "MuMain - Editor Mode (F12)",
  "args": "connect /u127.0.0.1 /p44405 --editor",
  "workingDirectory": "${projectDir}/src/bin"
}
```

**Descripción:**
- Igual que el perfil anterior, pero compila y compila la librería C# de Red con la opción de editor habilitada
- Requiere que el preset CMake sea `windows-x86-mueditor` o `windows-x64-mueditor`

**Uso en juego:**
- Pulsa **F12** para toggle el editor de ImGui (mientras juegas)

**Nota:** Este perfil solo funciona si compilaste con:
```
cmake --preset windows-x86-mueditor  (o x64-mueditor)
```

---

### 3. Ejecución sin Argumentos (Modo Offline)

```json
{
  "type": "default",
  "project": "CMakeLists.txt",
  "projectTarget": "Main",
  "name": "MuMain - Default (No Args)",
  "args": "",
  "workingDirectory": "${projectDir}/src/bin"
}
```

**Descripción:**
- Inicia el cliente sin conectar automáticamente
- Acceso al menú principal (si la UI lo permite)

---

## 🔧 Desglose de Atributos

| Atributo | Tipo | Requerido | Descripción |
|----------|------|-----------|-------------|
| `type` | string | ✅ | Tipo de configuración: `"default"` para ejecutables CMake |
| `project` | string | ✅ | Ruta al archivo CMakeLists.txt principal |
| `projectTarget` | string | ✅ | Nombre del target CMake (`Main` en MuMain) |
| `name` | string | ✅ | Nombre legible que aparece en el desplegable de VS |
| `args` | string | ❌ | Argumentos de línea de comandos (vacío si no aplica) |
| `workingDirectory` | string | ❌ | Directorio de trabajo del proceso (por defecto: `${sourceDir}`) |

### Macros Disponibles en `workingDirectory`

- `${sourceDir}` → Raíz del repositorio (donde está `CMakeLists.txt` raíz)
- `${projectDir}` → Raíz del repositorio (alias de `${sourceDir}`)
- Rutas relativas: `src/bin/` (relativa a raíz)

---

## 📡 Parámetros de Conexión del Cliente

El ejecutable `Main.exe` acepta los siguientes argumentos:

```
connect /u<IP> /p<PUERTO>
```

| Argumento | Forma | Ejemplo | Descripción |
|-----------|-------|---------|-------------|
| Conexión | `connect` | `connect` | Activa modo de conexión |
| IP | `/u<IP>` | `/u127.0.0.1` | IP del servidor (127.0.0.1 = localhost) |
| Puerto | `/p<PUERTO>` | `/p44405` | Puerto del ConnectServer de OpenMU |

**Ejemplos:**

```bash
# Conectar a servidor local, puerto 44405 (OpenMU por defecto)
Main.exe connect /u127.0.0.1 /p44405

# Conectar a servidor remoto
Main.exe connect /u192.168.1.100 /p44405

# Sin argumentos (offline)
Main.exe
```

---

## 🗂️ Estructura de Directorios y Assets

### Ubicación de Assets (Recursos del Juego)

```
{raíz}
├── src/
│   ├── bin/                          ← Assets ORIGEN
│   │   ├── data/
│   │   ├── gfx/
│   │   ├── music/
│   │   ├── sfx/
│   │   └── ...
│   ├── CMakeLists.txt
│   └── source/
│       ├── App/
│       ├── Engine/
│       └── ...
│
├── out/
│   ├── build/
│   │   ├── windows-x86/
│   │   │   ├── Debug/
│   │   │   │   ├── Main.exe
│   │   │   │   ├── assets/          ← Assets COPIADOS (automático)
│   │   │   │   └── ... (DLLs, etc)
│   │   │   │
│   │   │   └── Release/
│   │   │       └── (similar a Debug)
│   │   │
│   │   ├── windows-x64/
│   │   │   └── (similar a x86)
│   │   │
│   │   └── windows-x86-mueditor/
│   │       └── (similar, con editor)
│   │
│   └── ...
│
├── CMakeLists.txt (raíz)
├── CMakePresets.json
└── .vs/
	└── launch.vs.json              ← ESTE ARCHIVO
```

**Nota:** Los assets se copian **automáticamente** desde `src/bin/` al directorio de output (e.g., `out/build/windows-x86/Debug/`) tras cada build exitoso.

---

## 🔄 Flujo de Depuración en Visual Studio 2026

### Paso a Paso

1. **Selecciona un preset/configuración CMake:**
   ```
   Barra de herramientas CMake → Desplegable "Select a Configuration"
   → Elige: windows-x86 (o tu preferencia)
   ```

2. **Reconstruye el proyecto:**
   ```
   Build → Build All  (Ctrl + Shift + B)
   ```
   - Si no has modificado nada desde la última build, puedes saltarle

3. **Selecciona un perfil de ejecución:**
   ```
   Barra de herramientas CMake → Desplegable "Startup Item"
   → Elige: "MuMain - Local OpenMU Server"
   ```

4. **Inicia el depurador:**
   ```
   Debug → Start Debugging  (F5)
   ó
   Debug → Start Without Debugging  (Ctrl+F5)
   ```

5. **El juego se lanza:**
   - Main.exe ejecuta con los argumentos: `connect /u127.0.0.1 /p44405`
   - Directorio de trabajo: `src/bin/` (assets disponibles)
   - El cliente intenta conectarse al servidor OpenMU

---

## ⚙️ Customización del `launch.vs.json`

### Ejemplo: Agregar un Perfil Personalizado

Si quieres conectar a un servidor remoto, edita `.vs/launch.vs.json` y agrega:

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

Guarda el archivo y VS recargará los perfiles automáticamente. El nuevo perfil aparecerá en el desplegable.

---

## ✅ Validación del `launch.vs.json`

**Checklist:**

- [ ] Archivo `.vs/launch.vs.json` existe
- [ ] JSON válido (sin comas faltantes, sin quotes desbalanceados)
- [ ] Al menos un `configuration` en el array
- [ ] Cada configuración tiene `name`, `type`, `project`, `projectTarget`
- [ ] `workingDirectory` apunta a `${projectDir}/src/bin` (donde están los assets)
- [ ] Los argumentos coinciden con el patrón: `connect /u<IP> /p<PUERTO>`

**Nota:** Si hay errores JSON, Visual Studio los mostrará en la ventana "Error List".

---

## 🆘 Troubleshooting

| Síntoma | Causa | Solución |
|---------|-------|----------|
| No aparecen perfiles en desplegable | JSON inválido | Verifica sintaxis con validador JSON online |
| Error "Target not found" | Target CMake incorrecto | Debe ser `Main` exactamente |
| Assets no encontrados | `workingDirectory` incorrecto | Debe apuntar a `${projectDir}/src/bin` |
| Conexión rechazada | Servidor no escuchando | Verifica OpenMU esté corriendo en 127.0.0.1:44405 |
| Proceso inicia y cierra | Argumentos inválidos | Revisa sintaxis: `connect /u127.0.0.1 /p44405` |

---

## 📚 Referencias

- [Documentación oficial de launch.vs.json (Microsoft Docs)](https://learn.microsoft.com/en-us/cpp/build/launch-vs-schema-reference)
- [CMakePresets.json en MuMain](https://github.com/sven-n/MuMain/blob/main/CMakePresets.json)
- [Repositorio MuMain](https://github.com/sven-n/MuMain)

---

## 🎮 Resumen Rápido para Comenzar

1. **Compilar:**
   ```
   Ctrl + Shift + B
   ```

2. **Seleccionar perfil:**
   ```
   Desplegable "Startup Item" → "MuMain - Local OpenMU Server"
   ```

3. **Ejecutar:**
   ```
   F5
   ```

¡El cliente debería conectar automáticamente a tu servidor OpenMU local!

