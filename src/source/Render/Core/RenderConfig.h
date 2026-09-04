#pragma once

// DXP-08: Core Profile GL context flip, read once at startup (Winmain creates the
// GL context immediately after InitRenderConfig() runs, before anything else can
// observe this). true = core 3.3 (default since DXP-08 Stage G), false = compatibility
// profile (rollback path). Set CoreProfile=0 in config.ini [Render] to opt back into
// compatibility.
extern bool g_CoreProfile;

// GLP-08: optional ceiling on the requested core-profile GL context version, read from
// config.ini [Render] MaxGLVersion (e.g. "4.3"). 0 = no cap (try the highest core context
// available -- Winmain.cpp's descending {4,5}->{4,3}->{3,3} attempt loop starts at the top).
// Rollback path for a driver that mishandles that loop. Ignored when g_CoreProfile is false.
extern int g_MaxGLVersionMajor;
extern int g_MaxGLVersionMinor;

// Fixed-function alpha test (GL_ALPHA_TEST/glAlphaFunc) state, mirrored for shader-side
// `discard` (DXP-01). g_AlphaRef is what shaders should test against: -1.0f means alpha
// test is currently disabled (no discard), otherwise it's the active GL_GREATER threshold.
// g_AlphaFuncRef is the last threshold passed to SetAlphaFuncRef(), independent of whether
// alpha test is currently enabled — reapplied to g_AlphaRef the next time it's enabled.
extern float g_AlphaRef;
extern float g_AlphaFuncRef;

// Vsync flag mirroring SDL's actual swap interval (ZzzOpenglUtil.cpp's EnableVSync/
// DisableVSync call SDL_GL_SetSwapInterval). Default true matches EnableVSync()'s
// unconditional call at boot (Winmain.cpp).
extern bool g_VSyncEnabled;

// config.ini [Render] FPSLimit: 0 = no override (default VSync/monitor-refresh pacing,
// see Winmain.cpp's boot-time InitVSync/EnableVSync sequence). A positive value means the
// user opted into an explicit target framerate (e.g. 120 on a 60Hz display via DSR/borderless,
// or just to run uncapped-from-the-monitor) - Winmain.cpp disables VSync and calls
// SetTargetFps(g_FPSLimitOverride) after that sequence when this is set.
extern int g_FPSLimitOverride;

// Debug diagnostic (2026-08-28, chasing a user-reported "black screen flash when casting
// skills" too fast to screenshot by hand): when true, PlatformSwapBuffers() (Winmain.cpp)
// samples a small center patch of every presented frame and, if its average brightness
// craters right after a normal frame, saves a full-frame BMP + a MuError.log line on its
// own -- no human needs to catch the flash in time. Off by default (a readback every frame
// has a real cost); toggle at runtime with the "$blackframe on"/"$blackframe off" debug
// console commands (muConsoleDebug.cpp) rather than shipping it always-on.
extern bool g_BlackFrameDetectEnabled;

// DXP-08a Category 1: CPU-tracked mirror of the FFP "current color" any glColor* call used
// to set (RGBA, 0-1 range). Under Core Profile glColor* no-ops and glGetFloatv(GL_CURRENT_
// COLOR, ...) is itself an illegal call, so callers that used to rely on reading back the
// ambient FFP color state now write here instead. Default {1,1,1,1} matches GL's own default.
extern float g_CurrentColor[4];

void InitRenderConfig();

// Shared closed-form perspective projection builder (GL's post-divide NDC z convention,
// [-1,1]). `f` is the caller's precomputed `1/tan(fovY/2)`; `out` is row-major matching this
// codebase's existing GlobalUBO layout (same layout the old glGetFloatv-derived matrices used).
void BuildPerspectiveProjection(float f, float aspect, float zNear, float zFar, float out[16]);
