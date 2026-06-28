# Allwinner CedarX userspace library
Based on lindenis-v536 SDK

> **Fork note (mbt28 / carplay-linux — Allwinner F1C100s/F1C200s).**
> This fork adds a small, self-contained set of changes for **zero-copy hardware
> video** on the F1C100s/F1C200s:
>
> - **`ion_alloc_get_dmabuf_fd(void *vir_addr)`** — added in
>   `memory/ionMemory/ionAlloc.c`, declared in `ionAllocEntry.h`. Returns the ION
>   **dma-buf fd** backing a decoded buffer's CPU virtual address, so the frame can
>   be handed to DRM/KMS via PRIME for **zero-copy display**. (The upstream
>   decode/FBM path leaves `VideoPicture.nBufFd` unset, so callers look the fd up
>   in the allocator's buffer list.)
> - **Uncached ION decode buffers** — `alloc_data.flags` no longer sets the
>   `AW_ION_CACHED_*` bits, so the VideoEngine output is coherent for the display
>   engine / a CPU de-tile **without an explicit cache flush**.
> - **Dropped hardcoded `-Werror`** from the makefiles so this older vendor code
>   builds cleanly on modern cross-toolchains.
>
> Used by the F1C200s CarPlay receiver (cedar-decode-test / FastCarPlay) to feed
> the VideoEngine's NV12-tiled frame straight to the sun4i **DEFE** display
> front-end. Pairs with the kernel VE+ION driver at
> [mbt28/cedar](https://github.com/mbt28/cedar).

## Add package to buildroot system
- Copy dir "buildroot-package/libcedarc" to "buildroot/package"

- Modify "buildroot/package/Config.in", add package source to any menu you want
    ```
    source "package/libcedarc/Config.in"
    ```
    Demo
    ```
    menu "Hardware handling"
    source "package/libcedarc/Config.in" # <--Add
    source "package/acsccid/Config.in"
    source "package/bcm2835/Config.in"
    ```

## Build
- make menuconfig
- Select "libcedarc" package
- make

## Work with ffmpeg (tested with buildroot 2020.02.1)
- make menuconfig
- goto "> Target packages > Audio and video applications > ffmpeg"
- set "(--enable-omx) Additional parameters for ./configure"
- recompile ffmpeg
