## litebrowser-gdi

This is a fork of [litebrowser](https://github.com/litehtml/litebrowser), it uses win32_container/gdiplus_container
instead of cairo_container.

**Advantages:**
* a bit faster (?)
* less dependencies (depends only on litehtml)

**Disadvantages:**
* addressbar is disabled
* doesn't support alpha channel in background colors, borders and text (because those are handled by GDI)
* no rounded corners
* transcription on Obama wiki is displayed with gaps
* underline is broken under hoo-SAYN on Obama wiki
