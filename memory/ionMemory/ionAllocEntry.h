
/*
* Copyright (c) 2008-2016 Allwinner Technology Co. Ltd.
* All rights reserved.
*
* File : ionAllocEntry.h
* Description :
* History :
*   Author  : xyliu <xyliu@allwinnertech.com>
*   Date    : 2016/04/13
*   Comment :
*
*
*/
#ifndef ION_ENTRY_H
#define ION_ENTRY_H

struct ScMemOpsS* __GetIonMemOpsS();

/* carplay-linux: return the ION dma-buf fd backing a buffer's CPU virtual
 * address, for zero-copy hand-off to DRM/PRIME. Returns the fd, or -1. */
int ion_alloc_get_dmabuf_fd(void *vir_addr);

#endif
