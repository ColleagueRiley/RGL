NAME = main
CC = gcc

LIBS := -lopengl32 -lshell32 -lgdi32 -lm --static

ifneq (,$(filter $(CC),winegcc x86_64-w64-mingw32-gcc))
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

OUTPUT = $(NAME).exe

ifeq ($(detected_OS),Windows)
	LIBS := -lopengl32 -lshell32 -lgdi32 -lm --static
endif
ifeq ($(detected_OS),Darwin)        # Mac OS X, I hate you Steve Jobs
	LIBS := -lm -framework Foundation -framework AppKit -framework OpenGL -framework CoreVideo -w
	OUTPUT = $(NAME)
endif
ifeq ($(detected_OS),Linux)
    LIBS := -I./include -lX11 -lGLX -lm -lGL
	OUTPUT = $(NAME)
endif

all:
	make $(OUTPUT)
	make gl-$(OUTPUT)

$(OUTPUT):
	$(CC) main.c $(LIBS) -I./ext -I../ -Wall -o $(OUTPUT)

gl-$(OUTPUT):
	$(CC) main.c $(LIBS) -I./ext -I../ -Wall -D RGL_OPENGL_LEGACY -o gl-$(OUTPUT)

clean:
	rm $(OUTPUT) gl-$(OUTPUT) $(NAME) gl-$(OUTPUT) -f

debug:
	make clean

	$(CC) main.c $(LIBS) -I./ext -I../ -Wall -D RGL_DEBUG -o $(OUTPUT)
	$(CC) main.c $(LIBS) -I./ext -I../ -Wall -D RGL_DEBUG -D RGL_OPENGL_LEGACY -o gl-$(OUTPUT)

	./$(OUTPUT)
	./gl-$(OUTPUT)