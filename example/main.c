#define RGL_IMPLEMENTATION
#define RGFW_IMPLEMENTATION
#define RGFW_PRINT_ERRORS
#define RGFW_NO_X11_CURSOR

#define STB_IMAGE_IMPLEMENTATION

//#define RGL_LEGACY_OPENGL

#include "RGL.h"

#include "RGFW.h"

#include "stb_image.h"

#include <stdbool.h>

unsigned int loadTexture(const void *data, int width, int height, unsigned char channels) {
    unsigned int id = 0;

    glBindTexture(GL_TEXTURE_2D, 0);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    glPixelStorei(GL_UNPACK_ROW_LENGTH, width);
    
    unsigned int c;

    switch (channels) {
        case 1: c = GL_RED; break;
        case 2: c = GL_RG; break;
        case 3: c = GL_RGB; break;
        case 4: c = GL_RGBA; break;
        default: break;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, c, width, height, 0, c, GL_UNSIGNED_BYTE, (unsigned char *)data);

    glBindTexture(GL_TEXTURE_2D, 0);

    return id;
}

typedef struct { int x, y, w, h; } rect;
typedef struct { int r, g, b, a; } color;

float rotate[3] = {120, 0, 0};

void glPrerequisites(rect r, color c) {
    int width = 500, height = 500;

    rglColor4ub(c.r, c.g, c.b, c.a);
    rglMatrixMode(RGL_PROJECTION);
    rglLoadIdentity();
    rglPushMatrix();

    rglOrtho(0, width, height, 0, -width, width);

    //rglTranslatef((r.x + (r.w / 2)), (r.x + (r.h / 2)), 0);
    /*rglRotatef(rotate[0],  0, 0, 1);
    rglRotatef(rotate[1], 0, 1, 0);
    rglRotatef(rotate[2], 1, 0, 0);*/

    //rglTranslatef(-(r.x + (r.w / 2)), -(r.x + (r.h / 2)), 0);
    rglMatrixMode(RGL_MODELVIEW);
}

int main() {
    RGFW_setGLVersion(3, 3);
    RGFW_window* win = RGFW_createWindow("RGFW Example Window", 500, 500, 500, 500, RGFW_ALLOW_DND);
    RGFW_window_makeCurrent(win);
    
    rglInit(500, 500, RGFW_getProcAddress);
    
    int w, h, c;
    u8* data = stbi_load("RSGL.png", &w, &h, &c, 0);

    u32 tex = loadTexture(data, w, h, c);
    free(data);

    data = stbi_load("RGFW.png", &w, &h, &c, 0);

    u32 tex2 = loadTexture(data, w, h, c);
    free(data);

    bool running = true;

    while (running) {  
        while(RGFW_window_checkEvent(win)) {   
            if (win->event.type == RGFW_quit) {
                running = false;
                break;
            }
        }

        glClearColor(255, 255, 255, 255);
        glClear(GL_COLOR_BUFFER_BIT);
        
        rglSetTexture(tex);

        glPrerequisites((rect){300, 300, 100, 100}, (color){255, 255, 255, 255});
        
        rglBegin(GL_TRIANGLES);
            rglColor3f(1, 0, 0); rglVertex2f(-0.6, -0.75);
            rglColor3f(0, 1, 0); rglVertex2f(0.6, -0.75);
            rglColor3f(0, 0, 1); rglVertex2f(0, 0.75);
        rglEnd();

        rglSetTexture(tex2);
        rglBegin(GL_QUADS);
        rglTexCoord3f(0, 0, 0);
        rglColor4f(1, 0, 0, 1); 
        rglVertex3f(300, 300, 0);
        
        rglTexCoord3f(1, 0, 0);
        rglColor4f(0, 1, 0, 1); 
        rglVertex3f(400, 300, 0);
        
        rglTexCoord3f(1, 0, 0);
        rglColor4f(0, 1, 0, 1); 
        rglVertex3f(400, 300, 0);
        
        rglTexCoord3f(0.5f, 1, 0);
        rglColor4f(0, 0, 1, 1); 
        rglVertex3f(250, 400, 0);
        rglEnd();
        rglPopMatrix();

        rglRenderBatch();
        RGFW_window_swapBuffers(win);
    }

    glDeleteTextures(1, &tex);
    glDeleteTextures(1, &tex2);

    rglClose();
    RGFW_window_close(win);
}