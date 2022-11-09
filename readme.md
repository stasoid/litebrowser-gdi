## litebrowser-gdi

This is a fork of [litebrowser](https://github.com/litehtml/litebrowser), it uses win32_container/gdiplus_container
instead of cairo_container.

**Advantages:**
* faster rendering due to faster text width computation
* less dependencies (depends only on litehtml)

**Disadvantages:**
* no addressbar
* doesn't support alpha channel in background colors, borders and text (because those are handled by GDI)
* no rounded corners
* underline is broken under hoo-SAYN on Obama wiki
