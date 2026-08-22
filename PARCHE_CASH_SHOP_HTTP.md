# Parche: Cash Shop por HTTP en vez de FTP muerto

Este documento es para el agente (Claude u otro) que se encarga de compilar el
cliente en esta PC. Da contexto de qué se cambió, por qué, y qué hace falta
verificar después de compilar.

## Rama

`cash-shop-http-catalog` (creada sobre `main`, con un commit).

## Contexto

El servidor (OpenMU, en otra máquina/sesión) ya tiene armado un Cash Shop
funcional: catálogo editable desde el panel de administración web, protocolo
de compra implementado, y un botón "Publicar catálogo" que genera los
archivos `IBSCategory.txt` / `IBSPackage.txt` / `IBSProduct.txt` que este
cliente necesita para mostrar productos en la tienda in-game.

El problema: el cliente descarga esos 3 archivos apuntando a
`image.webzen.com` (el dominio original de Webzen, muerto desde hace años),
y encima el código tiene un bug que ignora el tipo de descarga pedido y
siempre usa FTP — aunque el propio llamador (`InGameShopSystem.cpp`) ya pide
`HTTP`, y el sistema de descarga (`FileDownloader.cpp` → `HTTPConnecter`) YA
tiene un GET por HTTP totalmente funcional e implementado, solo que nunca se
usaba por ese hardcodeo.

Por eso "la tienda no se conecta" in-game: nunca llega a intentar nada
alcanzable, porque apunta a un host muerto por un protocolo (FTP) que además
está forzado incluso cuando se pidió HTTP.

## Qué se cambió (2 archivos, 2 líneas)

1. `src/source/GameShop/ShopListManager/FTPFileDownLoader.cpp`, línea ~115:

   ```diff
   - ServerInfo.SetDownloaderType(FTP);
   + ServerInfo.SetDownloaderType(type);
   ```

   Ahora respeta el tipo de descarga (`HTTP` o `FTP`) que le pasó el
   llamador, en vez de forzar siempre FTP.

2. `src/source/GameShop/InGameShopSystem.cpp`, línea ~105 (dentro de
   `CInGameShopSystem::ScriptDownload()`):

   ```diff
   - wcscpy(m_szScriptIPAddress, L"image.webzen.com");
   + wcscpy(m_szScriptIPAddress, L"mu-chilecito.playit.plus");
   ```

   Apunta el catálogo de la tienda a nuestro propio dominio en vez del de
   Webzen. Ese dominio ya sirve los 3 archivos por HTTP plano (puerto 80,
   sin HTTPS — el downloader del cliente no usa `INTERNET_FLAG_SECURE`, así
   que tiene que ser HTTP, no HTTPS) en la ruta
   `/Global/Payment/ProductTransfer/<versión>/`, confirmado con `curl` desde
   el servidor antes de pedir este build.

   **No se tocó** el banner de la tienda (`m_szBannerIPAddress`, misma
   función, ~10 líneas más abajo) — sigue apuntando a Webzen a propósito.
   El servidor todavía no envía el paquete de versión de banner
   (`PMSG_CASHSHOP_BANNER_UPDATE`), así que esa descarga nunca se dispara y
   no genera ningún error visible al jugador. Si en el futuro se agrega
   banner del lado servidor, ahí sí habría que aplicarle el mismo parche de
   dominio a esa línea.

## Qué hace falta hacer acá

1. Compilar el cliente en **Release** siguiendo
   [`GUIA_COMPILACION_MUMAIN_VS2026.md`](GUIA_COMPILACION_MUMAIN_VS2026.md)
   (la guía que ya existe en este repo). No hace falta ningún cambio de
   configuración de CMake ni de dependencias — es solo el parche de 2
   líneas de arriba, ya aplicado en esta rama.
2. Confirmar que compila sin errores nuevos (los únicos archivos tocados
   son los dos de arriba).
3. Avisar al usuario cuando el `.exe` esté listo — es el que reemplaza al
   que se comparte desde la página de registro (MediaFire).

## Cómo probar (si hay forma de correr el cliente contra el server real)

1. Iniciar sesión, abrir el Cash Shop in-game.
2. Debería mostrar productos (los que estén publicados desde el panel de
   admin) en vez de quedarse "sin conectar" o tirar un error.
3. Si aparece vacío pero sin error: puede ser que todavía no se publicó
   ningún producto desde el panel — no es un fallo del cliente.
4. Si sigue sin conectar: revisar que este build sea el que se está usando
   (no una copia vieja), y avisar para revisar del lado servidor.
