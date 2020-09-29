TARGET = dungeon
OBJS = src/callback.o src/glib2d.o src/main.o

INCDIR += ./include
CFLAGS = -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR += ./libs
LDFLAGS =
LIBS =  -lintrafont -lpng -ljpeg -lg -lc -lGL -lGLU -lglut -lz -lm \
        -lpspvfpu -lpspvram \
        -L${PSPDEV}/psp/sdk/lib \
        -L${PSPDEV}/psp \
        -lpspdebug  -lpspgu -lpspctrl -lpspge -lpspirkeyb -lpsppower -lpsppower_driver \
        -lpspdisplay -lpsphprm  -lpspsdk -lpsprtc -lpspaudio -lpsputility \
         -lc -lpspuser

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = dungeon

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
