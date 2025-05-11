GFXINC  += $(GFXLIB)/boards/base/HHK
GFXSRC  +=
GFXDEFS += -DGFX_USE_OS_RAW32=GFXON -DGFX_OS_HEAP_SIZE=0 -DGFX_OS_NO_INIT=GFXON -DGFX_OS_INIT_NO_WARNING=GFXON
GFXLIBS += sdk

include $(GFXLIB)/drivers/gdisp/framebuffer/driver.mk
include $(GFXLIB)/drivers/ginput/touch/MCU/driver.mk
