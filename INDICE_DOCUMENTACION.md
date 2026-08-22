# 📚 ÍNDICE DE DOCUMENTACIÓN: MuMain + Visual Studio 2026

## 🎯 Propósito de Esta Suite Documental

He creado una **suite completa de documentación** para compilar **MuMain** (cliente de Season 5.2/6.3 con Native AOT) en **Visual Studio 2026** y configurarlo para conectar a un servidor OpenMU local.

---

## 📋 Documentos Creados (7 Archivos)

### 1️⃣ **GUIA_COMPILACION_MUMAIN_VS2026.md**
   - 📖 **Tipo:** Guía step-by-step completa
   - 🎯 **Para:** Primera vez compilando
   - ⏱️ **Duración:** 15-20 minutos
   - 📌 **Contenido:**
	 - Verificación de requisitos
	 - Configuración de CMake en VS 2026
	 - Proceso de compilación detallado
	 - Configuración del perfil de inicio
	 - Verificación de conectividad
	 - Troubleshooting básico
   - ✅ **Recomendación:** **LEE ESTO PRIMERO**

---

### 2️⃣ **REFERENCIA_LAUNCH_VS_JSON.md**
   - 🔧 **Tipo:** Referencia técnica
   - 🎯 **Para:** Entender launch.vs.json en profundidad
   - ⏱️ **Duración:** 10 minutos
   - 📌 **Contenido:**
	 - Ubicación y estructura del archivo
	 - Formato JSON completo
	 - Descripción de cada perfil
	 - Parámetros de conexión
	 - Macros de ruta disponibles
	 - Ejemplo de customización
	 - Troubleshooting JSON
   - ✅ **Recomendación:** Después de compilar la primera vez

---

### 3️⃣ **JSON_LAUNCH_VS_ESPECIFICACION.md**
   - 📄 **Tipo:** Especificación pura JSON
   - 🎯 **Para:** Copiar/pegar y personalizar
   - ⏱️ **Duración:** 5 minutos
   - 📌 **Contenido:**
	 - JSON válido listo para usar
	 - Tablas de sintaxis y validación
	 - Patrones para diferentes servidores
	 - Ejemplos de uso avanzado
	 - Validador PowerShell
   - ✅ **Recomendación:** Cuando necesites agregar servidores

---

### 4️⃣ **TROUBLESHOOTING_COMPILACION.md**
   - 🆘 **Tipo:** Solución de problemas
   - 🎯 **Para:** Cuando algo no funciona
   - ⏱️ **Duración:** 5-15 minutos (según el error)
   - 📌 **Contenido:**
	 - 12 problemas comunes con soluciones
	 - Diagnosis de errores específicos
	 - Scripts PowerShell de diagnóstico
	 - Checklist de validación
	 - Recursos adicionales
   - ✅ **Recomendación:** Tu mejor amigo cuando falla

---

### 5️⃣ **GUIA_RAPIDA_VISUAL.md**
   - ⚡ **Tipo:** Referencia visual
   - 🎯 **Para:** Flujos visuales y rápidos
   - ⏱️ **Duración:** 5 minutos
   - 📌 **Contenido:**
	 - Diagramas ASCII del flujo completo
	 - Comandos PowerShell organizados
	 - Interfaz visual de VS 2026
	 - Atajos de teclado
	 - Estructura de directorios
	 - Checklist final
   - ✅ **Recomendación:** Consulta rápida visual

---

### 6️⃣ **CHEAT_SHEET.md**
   - 🎯 **Tipo:** Hoja de trucos/referencia rápida
   - 🎯 **Para:** Acceso frecuente a comandos
   - ⏱️ **Duración:** 2 minutos
   - 📌 **Contenido:**
	 - Atajos VS 2026
	 - Comandos PowerShell esenciales
	 - Ubicaciones clave
	 - Parámetros de ejecución
	 - Pro tips
	 - Resumen ultra-rápido
   - ✅ **Recomendación:** Imprime o guarda como favorito

---

### 7️⃣ **.vs/launch.vs.json** (ARCHIVO TÉCNICO)
   - ⚙️ **Tipo:** Configuración de Visual Studio 2026
   - 🎯 **Para:** Definir perfiles de ejecución
   - 📌 **Ubicación:** `.vs/launch.vs.json` (raíz del repo)
   - 📌 **Contenido:**
	 - 5 perfiles predefinidos:
	   1. MuMain - Local OpenMU Server
	   2. MuMain - Local OpenMU Server (x86 Debug)
	   3. MuMain - Local OpenMU Server (x64 Debug)
	   4. MuMain - Editor Mode (F12)
	   5. MuMain - Default (No Args)
   - ✅ **Recomendación:** Personalizar según necesidad

---

## 🗺️ MAPA DE LECTURA SEGÚN SITUACIÓN

### 📍 Si Eres Completo Principiante
```
1. GUIA_COMPILACION_MUMAIN_VS2026.md    ← COMIENZA AQUÍ (15 min)
   └─→ Sigue paso a paso

2. GUIA_RAPIDA_VISUAL.md                ← Después (5 min)
   └─→ Comprende el flujo visual

3. CHEAT_SHEET.md                       ← Consulta rápida
   └─→ Para comandos frecuentes

4. TROUBLESHOOTING_COMPILACION.md       ← Cuando algo falla
   └─→ Busca tu error específico
```

### 📍 Si Entiendes CMake/C++
```
1. GUIA_RAPIDA_VISUAL.md                ← Resumen rápido (5 min)
   └─→ Entiende el flujo

2. JSON_LAUNCH_VS_ESPECIFICACION.md     ← Tech specs (5 min)
   └─→ Personaliza perfiles

3. CHEAT_SHEET.md                       ← Para después
   └─→ Referencia rápida

4. TROUBLESHOOTING_COMPILACION.md       ← Si algo falla
   └─→ Diagnosis
```

### 📍 Si Solo Necesitas Compilar Rápido
```
1. CHEAT_SHEET.md                       ← Aquí está todo (2 min)

2. TROUBLESHOOTING_COMPILACION.md       ← Si algo falla
```

### 📍 Si Algo No Funciona
```
1. TROUBLESHOOTING_COMPILACION.md       ← INMEDIATAMENTE
   └─→ Busca el error específico

2. GUIA_RAPIDA_VISUAL.md                ← Para diagnosis visual

3. GUIA_COMPILACION_MUMAIN_VS2026.md    ← Si todo falla, reinicia
```

---

## 🎯 MATRIZ DE DECISIÓN

```
¿Cuál es tu situación?

┌─ ¿Primera vez compilando?
│  ├─ Sí → GUIA_COMPILACION_MUMAIN_VS2026.md
│  └─ No → ¿Necesitas recordar comandos?
│
├─ ¿Necesitas recordar comandos?
│  ├─ Sí → CHEAT_SHEET.md
│  └─ No → ¿Algo está fallando?
│
├─ ¿Algo está fallando?
│  ├─ Sí → TROUBLESHOOTING_COMPILACION.md
│  └─ No → ¿Necesitas personalizar perfiles?
│
└─ ¿Necesitas personalizar perfiles?
   ├─ Sí → JSON_LAUNCH_VS_ESPECIFICACION.md
   └─ No → ¡Listo! Prueba F5 en VS 2026
```

---

## 📂 ESTRUCTURA DE ARCHIVOS CREADOS

```
{raíz del repo}/
│
├── .vs/
│   └── launch.vs.json                 ← ARCHIVO CRÍTICO
│                                       (Creado y listo para usar)
│
├── GUIA_COMPILACION_MUMAIN_VS2026.md  ← Paso a paso completo
├── REFERENCIA_LAUNCH_VS_JSON.md       ← Referencia técnica
├── JSON_LAUNCH_VS_ESPECIFICACION.md   ← Especificación JSON pura
├── TROUBLESHOOTING_COMPILACION.md     ← Solución de errores
├── GUIA_RAPIDA_VISUAL.md              ← Flujo visual
├── CHEAT_SHEET.md                     ← Atajos y comandos
├── INDICE_DOCUMENTACION.md            ← Este archivo
│
├── (Estructura original del proyecto)
├── CMakeLists.txt
├── CMakePresets.json
├── src/
├── out/build/
└── ...
```

---

## ⚡ QUICK START (30 seg)

Si **solo quieres** que funcione ahora:

```powershell
cd C:\path\to\MuMain
git submodule update --init --recursive
cmake --preset windows-x86
cmake --build out/build/windows-x86 --config Debug
cd out/build/windows-x86/Debug
.\Main.exe connect /u127.0.0.1 /p44405
```

**Pero:** Lee `GUIA_COMPILACION_MUMAIN_VS2026.md` después para entender todo.

---

## 🔑 PUNTOS CRÍTICOS

### El Archivo `.vs/launch.vs.json`
- ✅ **Ya está creado** en `.vs/launch.vs.json`
- ✅ **5 perfiles** listos para usar
- ✅ **Personalizable** (puedes editar y agregar más)
- ✅ **Sin reinicio necesario** (VS recarga automáticamente)

### Los Requisitos Previos
- ✅ Visual Studio 2026 (C++ + .NET workloads)
- ✅ .NET SDK 10.0+
- ✅ CMake 3.25+
- ✅ Submódulos inicializados

### El Flujo Mínimo
1. Compilar: `Ctrl+Shift+B`
2. Seleccionar perfil: Desplegable "Startup Item"
3. Ejecutar: `F5`

---

## 📊 COMPARATIVA DE DOCUMENTOS

| Documento | Tipo | Nivel | Duración | Mejor Para |
|-----------|------|-------|----------|-----------|
| GUIA_COMPILACION_MUMAIN_VS2026.md | Tutorial | Principiante | 15-20 min | Primera compilación |
| REFERENCIA_LAUNCH_VS_JSON.md | Referencia | Intermedio | 10 min | Entender internals |
| JSON_LAUNCH_VS_ESPECIFICACION.md | Spec | Intermedio/Avanzado | 5 min | Personalizar |
| TROUBLESHOOTING_COMPILACION.md | Guía | Todos | 5-15 min | Cuando falla |
| GUIA_RAPIDA_VISUAL.md | Visual | Todos | 5 min | Consult rápida |
| CHEAT_SHEET.md | Referencia | Todos | 2 min | Búsquedas frecuentes |

---

## ✅ CHECKLIST DE DOCUMENTACIÓN

He completado:
- ✅ Guía paso a paso (`GUIA_COMPILACION_MUMAIN_VS2026.md`)
- ✅ Referencia técnica (`REFERENCIA_LAUNCH_VS_JSON.md`)
- ✅ Especificación JSON (`JSON_LAUNCH_VS_ESPECIFICACION.md`)
- ✅ Troubleshooting (`TROUBLESHOOTING_COMPILACION.md`)
- ✅ Guía visual (`GUIA_RAPIDA_VISUAL.md`)
- ✅ Cheat sheet (`CHEAT_SHEET.md`)
- ✅ Archivo configuración (`.vs/launch.vs.json`)
- ✅ Este índice (`INDICE_DOCUMENTACION.md`)

---

## 🎓 APRENDIZAJE PROGRESIVO

### Hora 1: Comprención
- Leer: `GUIA_COMPILACION_MUMAIN_VS2026.md`
- Resultado: Entiendes qué hace cada paso

### Hora 2: Práctica
- Ejecutar: Los comandos de la guía
- Compilar y ejecutar: La primera vez
- Resultado: Tienes ejecutable compilado

### Hora 3: Referencia
- Guardar: `CHEAT_SHEET.md` como favorito
- Consultar: `TROUBLESHOOTING_COMPILACION.md` si algo falla
- Resultado: Sabés dónde buscar cuando necesitas

---

## 🚀 SIGUIENTES PASOS

1. **Ahora:** Lee esta página (acabas de hacerlo ✅)
2. **Siguiente:** Abre `GUIA_COMPILACION_MUMAIN_VS2026.md`
3. **Después:** Sigue los pasos paso a paso
4. **Cuando falle:** Consulta `TROUBLESHOOTING_COMPILACION.md`
5. **Luego:** Guarda `CHEAT_SHEET.md` como referencia

---

## 📞 ACCESO RÁPIDO A SECCIONES

### Por Problema
- **CMake no funciona:** TROUBLESHOOTING sección 1, 2
- **No compila:** TROUBLESHOOTING sección 11
- **No conecta:** TROUBLESHOOTING sección 6
- **Comando rápido:** CHEAT_SHEET.md

### Por Tecnología
- **CMake:** GUIA_COMPILACION sección 1, REFERENCIA sección…
- **launch.vs.json:** JSON_LAUNCH_VS_ESPECIFICACION.md (todo)
- **PowerShell:** CHEAT_SHEET.md sección "Terminal PowerShell"
- **Visual Studio:** GUIA_RAPIDA_VISUAL.md sección "Interfaz"

### Por Audiencia
- **Principiante:** GUIA_COMPILACION_MUMAIN_VS2026.md
- **Intermedio:** GUIA_RAPIDA_VISUAL.md + JSON_LAUNCH_VS_ESPECIFICACION.md
- **Avanzado:** CHEAT_SHEET.md + TROUBLESHOOTING_COMPILACION.md

---

## 📈 ROADMAP DE DOCUMENTACIÓN

Lo que tienes ahora:
- ✅ Compilación en VS 2026
- ✅ Configuración launch.vs.json
- ✅ Solución de problemas

Lo que podrías agregar (opcional):
- 📝 Desarrollo y debugging (breakpoints, inspeccionar memoria)
- 📝 Integración con OpenMU (protocolo de conexión)
- 📝 Optimización y profiling
- 📝 Cross-compilation (Linux/Mac desde Windows)

---

## 💬 PREGUNTAS FRECUENTES DE ESTA SUITE

**P: ¿Por qué tantos documentos?**
R: Cada persona aprende diferente. Algunos necesitan paso a paso, otros solo comandos, otros visual. Está cubierto.

**P: ¿Tengo que leer todos?**
R: No. Lee el mapeo según tu situación (ver arriba).

**P: ¿El launch.vs.json ya está creado?**
R: ✅ Sí, está en `.vs/launch.vs.json` listo para usar.

**P: ¿Puedo personalizar launch.vs.json?**
R: ✅ Sí, es un JSON normal. Edita directamente y VS recarga automáticamente.

**P: ¿Dónde están los assets?**
R: En `src/bin/` y se copian automáticamente a `out/build/.../Debug/` tras compilar.

---

## 📚 ÍNDICE ALFABÉTICO DE TEMAS

- **Assets:** GUIA_COMPILACION sección 2.3, TROUBLESHOOTING sección 5
- **CMake Presets:** GUIA_COMPILACION sección 1.3, JSON_LAUNCH sección completa
- **Compilación:** GUIA_COMPILACION sección 2, CHEAT_SHEET sección PowerShell
- **Conexión:** GUIA_COMPILACION sección 4, TROUBLESHOOTING sección 6
- **Debug:** REFERENCIA_LAUNCH sección 4, CHEAT_SHEET sección Atajos
- **Editor ImGui:** GUIA_COMPILACION sección alternativa, TROUBLESHOOTING sección 8
- **Errores:** TROUBLESHOOTING_COMPILACION.md (todo)
- **Ejecutable:** GUIA_COMPILACION sección 2.3, GUIA_RAPIDA_VISUAL sección ubicaciones
- **Firewall:** TROUBLESHOOTING sección 6
- **Hardware requerido:** GUIA_COMPILACION sección Requisitos previos
- **IP/Puerto:** JSON_LAUNCH_VS_ESPECIFICACION sección Parámetros
- **launch.vs.json:** REFERENCIA_LAUNCH_VS_JSON.md (todo)
- **Perfiles:** JSON_LAUNCH_VS_ESPECIFICACION sección Patrones
- **Permisos:** TROUBLESHOOTING sección 2
- **PowerShell:** CHEAT_SHEET sección Terminal
- **Recompilación:** CHEAT_SHEET sección Workflow
- **Serialización JSON:** JSON_LAUNCH_VS_ESPECIFICACION sección Validación
- **Servidor remoto:** JSON_LAUNCH_VS_ESPECIFICACION sección Patrón 1
- **Submódulos Git:** GUIA_COMPILACION sección 1.2, TROUBLESHOOTING sección 9
- **Troubleshooting:** TROUBLESHOOTING_COMPILACION.md (todo)
- **Visual Studio:** GUIA_RAPIDA_VISUAL sección Ubicación Visual
- **VS 2026:** GUIA_COMPILACION sección completa

---

## 🎯 RESUMEN FINAL

**Tienes TODO lo que necesitas para:**
- ✅ Compilar MuMain en VS 2026
- ✅ Configurar conexión a servidor local
- ✅ Debuggear y desarrollar
- ✅ Resolver problemas rápidamente
- ✅ Personalizar configuración

**Siguiente paso:** Abre `GUIA_COMPILACION_MUMAIN_VS2026.md` y sigue paso a paso.

---

**Documentación completa y lista.**
**Estado: ✅ READY TO USE**
**Fecha: 2025**

¡Buena suerte! 🚀

