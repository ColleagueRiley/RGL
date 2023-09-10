ifeq '$(findstring ;,$(PATH))' ';'
    detected_OS := Windows
else
    detected_OS := $(shell uname 2>/dev/null || echo Unknown)
    detected_OS := $(patsubst CYGWIN%,Cygwin,$(detected_OS))
    detected_OS := $(patsubst MSYS%,MSYS,$(detected_OS))
    detected_OS := $(patsubst MINGW%,MSYS,$(detected_OS))
endif

ifeq ($(detected_OS),Windows)
	LIBS := -lopengl32 -lshell32 -lgdi32 -lm
endif
ifeq ($(detected_OS),Darwin)        # Mac OS X
	LIBS := -I./ext/Silicon/ ./ext/Silicon/*.o -lm -framework Foundation -framework AppKit -framework OpenGL -framework CoreVideo -w
endif
ifeq ($(detected_OS),Linux)
    LIBS := -I./include -lX11 -lGLX -lm -lGL
endif

all:
	@if [ $(shell uname) = Darwin ]; then\
		make ext/Silicon/mac.o;\
	fi

	make main
	make gl

ext/Silicon/mac.o:
	cd ext/Silicon/ && gcc -c *.m

main:
	gcc main.c $(LIBS) -I./ext -I../ -Wall -o main

gl:
	gcc main.c $(LIBS) -I./ext -I../ -Wall -D RGL_LEGACY_OPENGL -o gl

clean:
	rm main -f

debug:
	make clean

	gcc main.c $(LIBS) -I./ext -I../ -Wall -D RGL_DEBUG -o main
	gcc main.c $(LIBS) -I./ext -I../ -Wall -D RGL_DEBUG -D RGL_LEGACY_OPENGL -o gl

	./main
	./gl