#define RGFW_WGL_NO_STENCIL
#define RGL_IMPLEMENTATION
#define RGFW_IMPLEMENTATION
#define RGFW_PRINT_ERRORS
#define RGFW_NO_X11_CURSOR

#define STB_IMAGE_IMPLEMENTATION

#include "RGL.h"

#include "RGFW.h"

#include "stb_image.h"

#include <stdbool.h>

typedef struct { int x, y, w, h; } rect;
typedef struct { int r, g, b, a; } color;

float rotate[3] = {0, 0, 0};

void glPrerequisites(rect r, color c) {
    int width = 500, height = 500;

    rglColor4ub(c.r, c.g, c.b, c.a);
    rglMatrixMode(RGL_PROJECTION);
    rglLoadIdentity();
    rglPushMatrix();

    rglMatrixMode(RGL_MODELVIEW);
    rglPushMatrix();

    rglOrtho(0, width, height, 0, -width, width);
    
    rglTranslatef((r.x + (r.w / 2)), (r.x + (r.h / 2)), 0);
    rglRotatef(rotate[0],  0, 0, 1);
    rglRotatef(rotate[1], 0, 1, 0);
    rglRotatef(rotate[2], 1, 0, 0);

    rglTranslatef(-(r.x + (r.w / 2)), -(r.x + (r.h / 2)), 0);
}

int main() {
    #ifdef RGL_MODERN_OPENGL
    RGFW_setGLVersion(3, 3);
    #endif
    
    RGFW_window* win = RGFW_createWindow("RGL Example Window", 500, 500, 500, 500, RGFW_CENTER);

    RGFW_window_makeCurrent(win);

    rglInit(500, 500, RGFW_getProcAddress);

    int w, h, c;
    u8* data = stbi_load("RSGL.png", &w, &h, &c, 0);

    u32 tex = rglCreateTexture(data, w, h, c);
    free(data);

    data = stbi_load("RGFW.png", &w, &h, &c, 0);

    u32 tex2 = rglCreateTexture(data, w, h, c);
    free(data);

    bool running = true;
    
    rglMatrixScale((float)win->w /(float)win->w, (float)win-> h / (float)win-> h, 1.0f);
    
    while (running) {  
        while(RGFW_window_checkEvent(win)) {   
            if (win->event.type == RGFW_quit) {
                running = false;
                break;
            }
        }
        

        glClearColor(255, 255, 255, 255);
        glClear(GL_COLOR_BUFFER_BIT);
        
        rglLegacy(1);
        
        rglBegin(RGL_LINES);
            rglColor3f(0, 1, 0); 
            rglVertex2f(0.6, -0.75);
            rglVertex2f(-0.6, -0.75);
        rglEnd();
        
        rglLegacy(0);

        rglBegin(RGL_LINES);
            rglColor3f(0, 1, 0); 
            rglVertex2f(0.6, 0.75);
            rglVertex2f(-0.6, 0.75);
        rglEnd();

        rglSetTexture(tex2);
        
        rglBegin(GL_QUADS);
            rglTexCoord2f(0, 0); rglColor3f(1, 0, 0); rglVertex2f(-0.6, -0.75);
            rglTexCoord2f(1, 0); rglColor3f(0, 1, 0); rglVertex2f(0.6, -0.75);
            rglTexCoord2f(1, 0); rglColor3f(0, 1, 0); rglVertex2f(0.6, -0.75);
            rglTexCoord2f(1, 1); rglColor3f(0, 0, 1); rglVertex2f(0, 0.75);
        rglEnd();

        glPrerequisites((rect){300, 300, 100, 100}, (color){255, 255, 255, 255});

        rglSetTexture(tex);
        rglBegin(GL_QUADS);
        rglTexCoord2f(0, 0);
        rglColor4f(1, 0, 0, 1); 
        rglVertex3f(300, 300, 0);
        
        rglTexCoord2f(1, 0);
        rglColor4f(0, 1, 0, 1); 
        rglVertex3f(400, 300, 0);
        
        rglTexCoord2f(1, 0);
        rglColor4f(0, 1, 0, 1); 
        rglVertex3f(400, 300, 0);
        
        rglTexCoord2f(0.5f, 1);
        rglColor4f(0, 0, 1, 1); 
        rglVertex3f(250, 400, 0);
        rglEnd();
        

        rglPopMatrix();
        rglPopMatrix();

        rglLoadIdentity();

        rglRenderBatch();

        RGFW_window_swapBuffers(win);
    }

    glDeleteTextures(1, &tex);
    glDeleteTextures(1, &tex2);

    rglClose();
    RGFW_window_close(win);
}