CC = gcc

LIBS := -lopengl32 -lshell32 -lgdi32 -lm

ifneq (,$(filter $(CC),x86_64-w64-mingw32-gcc))
    detected_OS := Windows
else
ifeq '$(findstring ;,$(PATH))' ';'
    detected_OS := Windows
else
    detected_OS := $(shell uname 2>/dev/null || echo Unknown)
    detected_OS := $(patsubst CYGWIN%,Cygwin,$(detected_OS))
    detected_OS := $(patsubst MSYS%,MSYS,$(detected_OS))
    detected_OS := $(patsubst MINGW%,MSYS,$(detected_OS))
endif
endif

ifeq ($(detected_OS),Windows)
	LIBS := -lopengl32 -lshell32 -lgdi32 -lm
endif
ifeq ($(detected_OS),Darwin)        # Mac OS X
	LIBS := -lm -framework Foundation -framework AppKit -framework OpenGL -framework CoreVideo -w
endif
ifeq ($(detected_OS),Linux)
    LIBS := -I./include -lX11 -lm -lGL
endif

all:
	make main
	make gl

main:
	$(CC) main.c $(LIBS) -I./ext -I../ -Wall -o main

gl:
	$(CC) main.c $(LIBS) -I./ext -I../ -Wall -D RGL_OPENGL_LEGACY -o gl

clean:
	rm main -f

debug:
	make clean

	$(CC) main.c $(LIBS) -I./ext -I../ -Wall -D RGL_DEBUG -o main
	$(CC) main.c $(LIBS) -I./ext -I../ -Wall -D RGL_DEBUG -D RGL_OPENGL_LEGACY -o gl

	./main
	./gl
