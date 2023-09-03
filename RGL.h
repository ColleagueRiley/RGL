/*
* Copyright (c) 2021-23 ColleagueRiley ColleagueRiley@gmail.com
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
*
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following r estrictions:
*
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*
*
*/

/* 
MACOR #DEFINE ARGUMENTS

***
#define RGL_IMPLEMENTATION - include the RGL defines, this line must be included in at least one file or argument (-D), in your project
***

#define RGL_MODERN_OPENGL - Use the modern opengl backend (this is enabled by default)
#define RGL_LEGACY_OPENGL - Use the legacy opengl backend
#define RGL_NO_X64_OPTIMIZATIONS - Use x64 optimizations (x64 only), eg. SIMD
#define RGL_ALLOC_BATCHES - Allocate room for batches instead of using a stack-based c array
#define RGL_ALLOC_MATRIX_STACK - Allocate room for the matrix stack instead of using a stack-based c array

Values

#define RGL_MAX_BATCHES <x> - Set the max amount of batches (a batch is created when a different mode or texture is used), 
							By default this value is set to 256
#define RGL_MAX_BUFFER_ELEMENTS <x> - Set the max number of elements the renderer uses (verticies, colors, texture coords)
								 By Default this value is set to 8192
#define RGL_MAX_MATRIX_STACK_SIZE <x> - Set the max number of matrix stack layers that can be active at a time
										 By default this value is set to 32
#define RGL_MALLOC <x> - set the malloc function for RGL and GLAD to use, by default this is the c standard malloc
#define RGL_FREE <x> - set the free function for RGL and GLAD to use, by default this is the c standard free
#define PI <x> - set the default value for PI used, by default this value is 3.14159265358979323846f
#ifndef DEG2RAD - set the default value for deg2rad used, by default this value is (PI / 180.0f)
*/

/*
Credits :

RLGL (raylib / Raysay5) - A simular project, that this project's design is based on.
							RLGL was also used as a reference for some of this code.
*/


#if !defined(RGL_MODERN_OPENGL) && !defined(RGL_LEGACY_OPENGL)
#define RGL_MODERN_OPENGL
#endif

#ifndef RGL_MAX_MATRIX_STACK_SIZE
#define RGL_MAX_MATRIX_STACK_SIZE 32
#endif

#ifndef RGL_MAX_BATCHES
#define RGL_MAX_BATCHES 256
#endif

#ifndef RGL_MAX_BUFFER_ELEMENTS
#define RGL_MAX_BUFFER_ELEMENTS 8192
#endif

#if !defined(u8)
#include <stdint.h>

typedef uint8_t u8;
typedef int8_t i8;
typedef uint16_t u16;
typedef int16_t i16;
typedef uint32_t u32;
typedef int32_t i32;
typedef uint64_t u64;
typedef int64_t i64;
typedef u8 b8;
#endif

#ifdef RGL_MODERN_OPENGL
#ifndef RGL_MALLOC
#include <stdlib.h>
#define RGL_MALLOC malloc
#define RGL_FREE free
#endif /* ndef RGL_MALLOC */

#ifndef PI
#define PI 3.14159265358979323846f
#endif
#ifndef DEG2RAD
#define DEG2RAD (PI / 180.0f)
#endif

#define GLAD_MALLOC RGL_MALLOC
#define GLAD_FREE RGL_FREE

#ifdef RGL_IMPLEMENTATION
#define GLAD_GL_IMPLEMENTATION
#endif

#include "glad.h"

#include <math.h>
#else
#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif
#endif /* RGL_MODERN_OPENGL */

#ifndef RGL_TRIANGLES
#define RGL_LINES 0x0001	 /* GL_LINES */
#define RGL_TRIANGLES 0x0004 /* GL_TRIANGLES */
#define RGL_QUADS 0x0007	 /* GL_QUADS */
#endif						 /* ndef RGL_TRIANGLES */

#ifndef RGL_MODELVIEW
#define RGL_MODELVIEW 0x1700
#define RGL_PROJECTION 0x1701
#endif

/* make sure declares aren't declared twice */
#ifndef RGL_H
#define RGL_H

inline void rglInit(u32 width, u32 height, void *loader);
inline void rglUpdateFrameBufferSize(u32 width, u32 height);
inline void rglRenderBatch(void);
inline void rglRenderBatchWithShader(u32 program, u32 vertexLocation, u32 texCoordLocation, u32 colorLocation);
inline void rglSetTexture(u32 texture);
inline void rglClose(void);

#define rglViewport glViewport
#define rglLineWidth glLineWidth

#ifdef RGL_LEGACY_OPENGL
#define rglBegin glBegin
#define rglColor3f glColor3f
#define rglColor3ub glColor4ub
#define rglColor4f glColor4f
#define rglColor4ub glColor4ub
#define rglTexCoord2f glTexCoord2f
#define rglTexCoord3f glTexCoord3f
#define rglTranslatef glTranslatef
#define rglScalef glScalef
#define rglVertex2f glVertex2f
#define rglVertex3f glVertex3f
#define rglPushMatrix glPushMatrix
#define rglPopMatrix glPopMatrix
#define rglEnd glEnd
#define rglMatrixMode glMatrixMode
#define rglLoadIdentity glLoadIdentity
#define rglRotatef glRotatef
#define rglOrtho glOrtho
#define rglFrustum glFrustum
#define rglMultMatrixf glMultMatrixf
#else /* RGL_LEGACY_OPENGL (else) (RGL_MODERN_OPENGL) */

/* basics */
inline void rglBegin(u32 mode);
inline void rglColor3f(float r, float g, float b);
inline void rglColor3ub(u8 r, u8 g, u8 b);
inline void rglColor4f(float r, float g, float b, float a);
inline void rglColor4ub(u8 r, u8 g, u8 b, u8 a);
inline void rglTexCoord2f(float s, float t);
inline void rglTexCoord3f(float s, float t, float r);
inline void rglVertex2f(float x, float y);
inline void rglVertex3f(float x, float y, float z);
inline void rglEnd(void);

/* transformations */

inline void rglTranslatef(float x, float y, float z);
inline void rglScalef(float x, float y, float z);
inline void rglOrtho(double left, double right, double bottom, double top, double znear, double zfar);
inline void rglFrustum(double left, double right, double bottom, double top, double znear, double zfar);
inline void rglRotatef(float angle, float x, float y, float z);

/* matrix */
typedef struct {
	float m[16];
} RGL_MATRIX;

inline RGL_MATRIX rglInitMatrix(void);
inline RGL_MATRIX rglMultiplyMatrix(float left[16], float right[16]);

inline void rglPushMatrix(void);
inline void rglPopMatrix(void);
inline void rglLoadIdentity(void);
inline void rglMatrixMode(u32 mode);
inline void rglMultMatrixf(const float* m);

#ifdef RGL_DEBUG
inline void RGL_debug_shader(u32 src, const char *shader, const char *action);
inline void RGL_opengl_getError();
#endif
#endif /* else (RGL_MODERN_OPENGL) */
#endif /* ndef RGL_H */

#ifdef RGL_IMPLEMENTATION

#ifdef RGL_MODERN_OPENGL

#if !defined(RGL_NO_X64_OPTIMIZATIONS) && (defined(__x86_64__) || defined(__i386__))
#include <mmintrin.h>  /* MMX */
#include <xmmintrin.h> /* SSE */
#include <emmintrin.h> /* SSE */
#include <pmmintrin.h> /* SSE3 */
#include <tmmintrin.h> /* SSSE3 */
#include <smmintrin.h> /* SSE4.1 */
#include <nmmintrin.h> /* SSE4.2 */
#include <ammintrin.h> /* SSE4A */
#include <wmmintrin.h> /* AES */

#define RGL_X86
#endif

typedef struct {
	u32 mode;
	u32 tex;
	u32 start;
	u32 length;
} RGL_BATCH;

struct RGL_INFO {
	/* framebuffer data */
	u32 width;
	u32 height;

	/* rendering data */
	#ifndef RGL_ALLOC_BATCHES
	RGL_BATCH batches[RGL_MAX_BATCHES];
	#else
	RGL_BATCH* batches;
	#endif

	size_t batchLen;
	
	#ifndef RGL_ALLOC_MATRIX_STACK
	RGL_MATRIX stack[RGL_MAX_MATRIX_STACK_SIZE];
	#else
	RGL_MATRIX* stack;
	#endif

	u8 stackLen;

	RGL_MATRIX* matrix;
	RGL_MATRIX modelview;
	RGL_MATRIX projection;
	
	u32 matrixMode;
	u8 transformRequired;

	u32 tex;
	float color[4];
	float tcoord[3];

	float *verts;
	float *colors;
	float *tcoords;

	u16 *indices;

	GLuint vao, vbo, tbo, cbo, ebo, /* array object and array buffers */
		program, vShader, fShader;	/* shader program and data */

	i32 mvp;
};
struct RGL_INFO RGLinfo;

#ifdef RGL_DEBUG

void RGL_opengl_getError() {
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR) {
		switch (err) {
		case GL_INVALID_ENUM:
			printf("OpenGL error: GL_INVALID_ENUM\n");
			break;
		case GL_INVALID_VALUE:
			printf("OpenGL error: GL_INVALID_VALUE\n");
			break;
		case GL_INVALID_OPERATION:
			printf("OpenGL error: GL_INVALID_OPERATION\n");
			break;
		case GL_STACK_OVERFLOW:
			printf("OpenGL error: GL_STACK_OVERFLOW\n");
			break;
		case GL_STACK_UNDERFLOW:
			printf("OpenGL error: GL_STACK_UNDERFLOW\n");
			break;
		default:
			printf("OpenGL error: Unknown error code 0x%x\n", err);
			break;
		}
	}
}

void RGL_debug_shader(u32 src, const char *shader, const char *action) {
	GLint status;
	if (action[0] == 'l')
		glGetProgramiv(src, GL_LINK_STATUS, &status);
	else
		glGetShaderiv(src, GL_COMPILE_STATUS, &status);

	if (status == GL_TRUE)
		printf("%s Shader %s successfully.\n", shader, action);
	else {
		printf("%s Shader failed to %s.\n", shader, action);

		if (action[0] == 'c') {
			GLint infoLogLength;
			glGetShaderiv(src, GL_INFO_LOG_LENGTH, &infoLogLength);

			if (infoLogLength > 0) {
				GLchar *infoLog = (GLchar *)RGL_MALLOC(infoLogLength);
				glGetShaderInfoLog(src, infoLogLength, NULL, infoLog);
				printf("%s Shader info log:\n%s\n", shader, infoLog);
				free(infoLog);
			}
		}

		RGL_opengl_getError();
		exit(1);
	}
}
#endif /* RGL_DEBUG */
#endif /* RGL_MODERN_OPENGL */

#define RGL_MULTILINE_STR(...) #__VA_ARGS__

void rglInit(u32 width, u32 height, void *loader) {
#ifdef RGL_MODERN_OPENGL
	if (loader != NULL)
		gladLoadGL((GLADloadfunc)loader);

	rglUpdateFrameBufferSize(width, height);

	u8 i = 0;

	for (i = 0; i < 3; i++)
		RGLinfo.color[i] = 0;

	for (i = 0; i < 3; i++)
		RGLinfo.tcoord[i] = 0;

	RGLinfo.verts = (float*)RGL_MALLOC(sizeof(float) * RGL_MAX_BUFFER_ELEMENTS * 3 * 4);
	RGLinfo.tcoords = (float*)RGL_MALLOC(sizeof(float) * RGL_MAX_BUFFER_ELEMENTS * 3 * 4);
	RGLinfo.colors = (float*)RGL_MALLOC(sizeof(float) * RGL_MAX_BUFFER_ELEMENTS * 4 * 4);
	RGLinfo.indices = (u16*)RGL_MALLOC(sizeof(u16) * RGL_MAX_BATCHES * 6);

	#ifdef RGL_ALLOC_BATCHES
	RGLinfo.batches = (RGL_BATCH*)RGL_MALLOC(sizeof(RGL_BATCH) * RGL_MAX_BATCHES);
	#endif

	#ifdef RGL_ALLOC_MATRIX_STACK
	RGLinfo.stack = (RGL_MATRIX*)RGL_MALLOC(sizeof(RGL_MATRIX*) * RGL_MAX_MATRIX_STACK_SIZE)
	#endif

    RGLinfo.projection = rglInitMatrix();
    RGLinfo.modelview = rglInitMatrix();
    RGLinfo.matrix = &RGLinfo.modelview;

	RGLinfo.tex = 0;
	RGLinfo.stackLen = 1;

	RGLinfo.batchLen = 0;
	RGLinfo.batches[0].mode = 0;

	if (RGLinfo.vao != 0)
		return;

	/*
		create default shader program and init vertex buffers
	*/

	static const char *defaultVShaderCode = RGL_MULTILINE_STR(
		\x23version 330 core       \n
		layout(location = 0) in vec3 vertexPosition;
		layout(location = 1) in vec2 vertexTexCoord;
		layout(location = 2) in vec4 inColor;
		out vec2 fragTexCoord;
		out vec4 fragColor;

		uniform mat4 mvp;          \n 
		void main() {
			fragColor = inColor;
			if (mvp != mat4(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0))
				gl_Position = mvp * vec4(vertexPosition, 1.0);
			else
				gl_Position = vec4(vertexPosition, 1.0);
			fragTexCoord = vertexTexCoord;
		}
	);

	static const char *defaultFShaderCode = RGL_MULTILINE_STR(
		\x23version 330 core                \n
			out vec4 FragColor;

		in vec4 fragColor;
		in vec2 fragTexCoord;

		uniform sampler2D texture0;

		void main() {
			if (length(texture(texture0, fragTexCoord)) > 1)
				FragColor = texture(texture0, fragTexCoord) * fragColor;
			else
				FragColor = fragColor;
		}
	);

	glGenVertexArrays(1, &RGLinfo.vao);

	glBindVertexArray(RGLinfo.vao);

	glGenBuffers(1, &RGLinfo.vbo);
	glGenBuffers(1, &RGLinfo.tbo);
	glGenBuffers(1, &RGLinfo.cbo);
	glGenBuffers(1, &RGLinfo.ebo);

	/* compile vertex shader */
	RGLinfo.vShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(RGLinfo.vShader, 1, &defaultVShaderCode, NULL);
	glCompileShader(RGLinfo.vShader);

#ifdef RGL_DEBUG
	RGL_debug_shader(RGLinfo.vShader, "Vertex", "compile");
#endif

	/* compile fragment shader */
	RGLinfo.fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(RGLinfo.fShader, 1, &defaultFShaderCode, NULL);
	glCompileShader(RGLinfo.fShader);

#ifdef RGL_DEBUG
	RGL_debug_shader(RGLinfo.fShader, "Fragment", "compile");
#endif

	/* create program and link vertex and fragment shaders */
	RGLinfo.program = glCreateProgram();

	glAttachShader(RGLinfo.program, RGLinfo.vShader);
	glAttachShader(RGLinfo.program, RGLinfo.fShader);

	glBindAttribLocation(RGLinfo.program, 0, "vertexPosition");
	glBindAttribLocation(RGLinfo.program, 1, "vertexTexCoord");
	glBindAttribLocation(RGLinfo.program, 2, "inColor");

	glLinkProgram(RGLinfo.program);

#ifdef RGL_DEBUG
	RGL_debug_shader(RGLinfo.program, "Both", "link to the program");
#endif

	RGLinfo.mvp = glGetUniformLocation(RGLinfo.program, "mvp");

#ifdef RGL_DEBUG
	if (RGLinfo.mvp == -1)
		printf("Failed to get mvp location\n");
#endif
#endif /* RGL_MODERN_OPENGL */
}

void rglUpdateFrameBufferSize(u32 width, u32 height) {
#ifdef RGL_MODERN_OPENGL
	RGLinfo.width = width;
	RGLinfo.height = height;
#endif
}

void rglRenderBatch(void) {
	#ifdef RGL_MODERN_OPENGL
	rglRenderBatchWithShader(RGLinfo.program, 0, 1, 2);
	#endif
}

void rglRenderBatchWithShader(u32 program, u32 vertexLocation, u32 texCoordLocation, u32 colorLocation) {
#ifdef RGL_MODERN_OPENGL
	glEnable(GL_TEXTURE_2D);

	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_CULL_FACE);

	glEnable(GL_BLEND);

	glBindVertexArray(RGLinfo.vao);

	glUseProgram(program);

	RGL_MATRIX matMVP = rglMultiplyMatrix(RGLinfo.modelview.m, RGLinfo.projection.m);
	
	glUniformMatrix4fv(RGLinfo.mvp, 1, 0, matMVP.m);

	u16 i;
	for (i = 0; i < RGLinfo.batchLen; i++) {
		RGL_BATCH *batch = RGLinfo.batches + i;

		glEnableVertexAttribArray(vertexLocation);
		glBindBuffer(GL_ARRAY_BUFFER, RGLinfo.vbo);
		glBufferData(GL_ARRAY_BUFFER, batch->length * 3 * sizeof(float), RGLinfo.verts + (batch->start * 3), GL_DYNAMIC_DRAW);
		glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, 0, NULL);

		glEnableVertexAttribArray(texCoordLocation);
		glBindBuffer(GL_ARRAY_BUFFER, RGLinfo.tbo);
		glBufferData(GL_ARRAY_BUFFER, batch->length * 3 * sizeof(float), RGLinfo.tcoords + (batch->start * 3), GL_DYNAMIC_DRAW);
		glVertexAttribPointer(texCoordLocation, 3, GL_FLOAT, GL_FALSE, 0, NULL);

		glEnableVertexAttribArray(colorLocation);
		glBindBuffer(GL_ARRAY_BUFFER, RGLinfo.cbo);
		glBufferData(GL_ARRAY_BUFFER, batch->length * 4 * sizeof(float), RGLinfo.colors + (batch->start * 4), GL_DYNAMIC_DRAW);
		glVertexAttribPointer(colorLocation, 4, GL_FLOAT, GL_FALSE, 0, NULL);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, batch->tex);

		if (batch->mode != GL_QUADS)
			glDrawArrays(batch->mode, 0, batch->length);
		else {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, RGLinfo.ebo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, batch->length * 6 * sizeof(u16), RGLinfo.indices, GL_STATIC_DRAW);

			int k = 0;

			int j;
			for (j = 0; j < (6 * batch->length); j += 6) {
				RGLinfo.indices[j] = 4 * k;
				RGLinfo.indices[j + 1] = 4 * k + 1;
				RGLinfo.indices[j + 2] = 4 * k + 2;
				RGLinfo.indices[j + 3] = 4 * k;
				RGLinfo.indices[j + 4] = 4 * k + 2;
				RGLinfo.indices[j + 5] = 4 * k + 3;

				k++;
			}

			glDrawElements(GL_TRIANGLES, batch->length / 4 * 6, GL_UNSIGNED_SHORT, (GLvoid *)(batch->start / 4 * 6 * sizeof(GLushort)));
		}

		batch->length = 0;
		batch->mode = 0;
		batch->start = 0;
		batch->tex = 0;
	}

	RGLinfo.batchLen = 0;
	glUseProgram(0);

	glDisable(GL_TEXTURE_2D);

#endif
}

void rglSetTexture(u32 texture) {
#ifdef RGL_MODERN_OPENGL
	RGLinfo.tex = texture;
#else
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
#endif
}

void rglClose(void) {
#ifdef RGL_MODERN_OPENGL
	RGL_FREE(RGLinfo.verts);
	RGL_FREE(RGLinfo.colors);
	RGL_FREE(RGLinfo.tcoords);
	RGL_FREE(RGLinfo.indices);

	#ifdef RGL_ALLOC_BATCHES
	RGL_FREE(RGLinfo.batches);
	#endif

	if (RGLinfo.vao == 0)
		return;

	/* free vertex array */
	glDeleteVertexArrays(1, &RGLinfo.vao);
	RGLinfo.vao = 0;

	/* free buffers */
	glDeleteBuffers(1, &RGLinfo.tbo);
	glDeleteBuffers(1, &RGLinfo.vbo);

	/* free program data */
	glDeleteShader(RGLinfo.vShader);
	glDeleteShader(RGLinfo.fShader);
	glDeleteProgram(RGLinfo.program);
#endif
}

#ifdef RGL_MODERN_OPENGL
void rglBegin(u32 mode) {
	if (RGLinfo.batchLen != 0 &&
		((RGLinfo.batches[RGLinfo.batchLen - 1].mode == mode &&
		  RGLinfo.batches[RGLinfo.batchLen - 1].tex == RGLinfo.tex) ||
		 RGLinfo.batchLen >= RGL_MAX_BATCHES - 1))
		return;

	RGLinfo.batches[RGLinfo.batchLen].mode = mode;
	RGLinfo.batches[RGLinfo.batchLen].length = 0;
	RGLinfo.batches[RGLinfo.batchLen].start = (RGLinfo.batchLen) ? (RGLinfo.batches[RGLinfo.batchLen - 1].length) : (0);
	RGLinfo.batches[RGLinfo.batchLen].tex = RGLinfo.tex;
	RGLinfo.batchLen++;
}

void rglColor3f(float r, float g, float b) {
	rglColor4f(r, g, b, 1.0f);
}

void rglColor3ub(u8 r, u8 g, u8 b) {
	rglColor4f(r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);
}

void rglColor4ub(u8 r, u8 g, u8 b, u8 a) {
	rglColor4f(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
}

void rglColor4f(float r, float g, float b, float a) {
	RGLinfo.color[0] = r;
	RGLinfo.color[1] = g;
	RGLinfo.color[2] = b;
	RGLinfo.color[3] = a;
}

void rglTexCoord2f(float s, float t) {
	rglTexCoord3f(s, t, 0.0f);
}

void rglTexCoord3f(float s, float t, float r) {
	RGLinfo.tcoord[0] = s;
	RGLinfo.tcoord[1] = t;
	RGLinfo.tcoord[2] = r;
}

void rglVertex2f(float x, float y) {
	rglVertex3f(x, y, 0.0f);
}

void rglVertex3f(float x, float y, float z) {
	u8 i;

	RGL_BATCH *batch = RGLinfo.batches + RGLinfo.batchLen - 1;
	size_t start = batch->start + batch->length;

	float* matrix = RGLinfo.modelview.m;
	//printf("%f %f %f\n", matrix.m[4], matrix.m[8], matrix.m[12]);

	if (RGLinfo.transformRequired) {
		x = matrix[0] * x + matrix[4] * y + matrix[8] * z + matrix[12];
		y = matrix[1] * x + matrix[5] * y + matrix[9] * z + matrix[13];
		z = matrix[2] * x + matrix[6] * y + matrix[10] * z + matrix[14];
	}

	RGLinfo.verts[(start * 3)] = x;
	RGLinfo.verts[(start * 3) + 1] = y;
	RGLinfo.verts[(start * 3) + 2] = z;

	for (i = 0; i < 3; i++)
		RGLinfo.tcoords[(start * 3) + i] = RGLinfo.tcoord[i];

	for (i = 0; i < 4; i++)
		RGLinfo.colors[(start * 4) + i] = RGLinfo.color[i];

	batch->length++;
}

void rglEnd(void) {

}

/*
	transformations
*/

void rglTranslatef(float x, float y, float z) {
    float matTranslation[16] = {
        1.0f, 0.0f, 0.0f, x,
        0.0f, 1.0f, 0.0f, y,
        0.0f, 0.0f, 1.0f, z,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    *RGLinfo.matrix = rglMultiplyMatrix(matTranslation, RGLinfo.matrix->m);
}

void rglScalef(float x, float y, float z) {
    float matScale[16] = {
        x,      0.0f,   0.0f,   0.0f,
        0.0f,   y,      0.0f,   0.0f,
        0.0f,   0.0f,   z,      0.0f,
        0.0f,   0.0f,   0.0f,   1.0f
    };

    *RGLinfo.matrix = rglMultiplyMatrix(matScale, RGLinfo.matrix->m);
}

void rglOrtho(double left, double right, double bottom, double top, double znear, double zfar) {
	float rl = (float)(right - left);
	float tb = (float)(top - bottom);
	float fn = (float)(zfar - znear);

	float tx = -((float)(right + left) / rl);
	float ty = -((float)(top + bottom) / tb);
	float tz = -((float)(zfar + znear) / fn);

	float matOrtho[16] = 
			{
				2.0f / rl,   0.0f,          0.0f,    	  0.0f,
				0.0f,        2.0 / tb,      0.0f,         0.0f,   
				0.0f,        0.0f,          -2.0f / fn,   0.0f,
				tx,          ty,            tz,           1.0f
			};
	
	*RGLinfo.matrix = rglMultiplyMatrix(RGLinfo.matrix->m, matOrtho);
}

void rglFrustum(double left, double right, double bottom, double top, double znear, double zfar) {
	float rl = (float)(right - left);
	float tb = (float)(top - bottom);
	float fn = (float)(zfar - znear);

	float tx = -((float)(right + left) / rl);
	float ty = -((float)(top + bottom) / tb);
	float tz = -((float)(zfar + znear) / fn);

	float matFrustum[16] = 
			{
				((float) znear*2.0f)/rl,     0.0f,   				   0.0f,   								    0.0f,
				0.0f,   				    ((float) znear*2.0f)/tb,   0.0f,   								    0.0f,
				tx,   						ty,   					   tz,     								    -1.0f,
				0.0f,   					0.0f,   					-((float)zfar*(float)znear*2.0f)/fn,   	0.0f
			};

	*RGLinfo.matrix = rglMultiplyMatrix(RGLinfo.matrix->m, matFrustum);
}

void rglRotatef(float angle, float x, float y, float z) {
	// Axis vector (x, y, z) normalization
	float lengthSquared = x * x + y * y + z * z;
	if ((lengthSquared != 1.0f) && (lengthSquared != 0.0f)) {
		float inverseLength = 1.0f / sqrtf(lengthSquared);
		x *= inverseLength;
		y *= inverseLength;
		z *= inverseLength;
	}

	// Rotation matrix generation
	float sinres = sinf(DEG2RAD * angle);
	float cosres = cosf(DEG2RAD * angle);
	float t = 1.0f - cosres;

	float matRotation[16] = 
				{
					x * x * t + cosres,   	  	y * x * t + z * sinres,   	z * x * t - y * sinres,   	0.0f,
					x * y * t - z * sinres,   	y * y * t + cosres,   		z * y * t + x * sinres,   	0.0f,
					x * z * t + y * sinres,   	y * z * t - x * sinres,  	z * z * t + cosres,   		0.0f,
					0.0f,   					0.0f,   					0.0f,   					1.0f
				};

	*RGLinfo.matrix = rglMultiplyMatrix(matRotation, RGLinfo.matrix->m);
}

/*
	Matrix functions
*/
void rglPushMatrix(void) {
	if (RGLinfo.stackLen >= RGL_MAX_MATRIX_STACK_SIZE)
		return;
		
	RGLinfo.stack[RGLinfo.stackLen - 1] = *RGLinfo.matrix;
	RGLinfo.stackLen++;
	rglLoadIdentity();
}

void rglPopMatrix(void) {
	if (RGLinfo.stackLen <= 1)
		return;

	RGLinfo.stackLen--;
	*RGLinfo.matrix = RGLinfo.stack[RGLinfo.stackLen - 1];
}

void rglLoadIdentity(void) {
	RGLinfo.stack[RGLinfo.stackLen - 1] = rglInitMatrix();
}

void rglMatrixMode(u32 mode) {
	RGLinfo.matrixMode = mode;

	if (mode == RGL_MODELVIEW)
		RGLinfo.matrix = &RGLinfo.modelview;
	else
		RGLinfo.matrix = &RGLinfo.projection;
}

void rglMultMatrixf(const float* m) {
	*RGLinfo.matrix = rglMultiplyMatrix(RGLinfo.matrix->m, (float*)m);
}

RGL_MATRIX rglInitMatrix(void) {
	RGL_MATRIX result = {
		{
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		}
	};

	RGLinfo.transformRequired = 0;
	return result;
}

RGL_MATRIX rglMultiplyMatrix(float left[16], float right[16]) {
	RGL_MATRIX result;
	
	/*
	BASIC SIMD CODE
		__m128 valueA = _mm_set1_ps(0);
		__m128 valueB = _mm_set1_ps(2.0);
		__mm128 sum1 = _mm_add_ps(valueA, valueB);
		__mm128 sum2 = _mm_mul_ps(valueA, valueB);
	*/


	result.m[0] = left[0] * right[0] + left[1] * right[4] + left[2] * right[8] + left[3] * right[12];
	result.m[1] = left[0] * right[1] + left[1] * right[5] + left[2] * right[9] + left[3] * right[13];
	result.m[2] = left[0] * right[2] + left[1] * right[6] + left[2] * right[10] + left[3] * right[14];
	result.m[3] = left[0] * right[3] + left[1] * right[7] + left[2] * right[11] + left[3] * right[15];
	result.m[4] = left[4] * right[0] + left[5] * right[4] + left[6] * right[8] + left[7] * right[12];
	result.m[5] = left[4] * right[1] + left[5] * right[5] + left[6] * right[9] + left[7] * right[13];
	result.m[6] = left[4] * right[2] + left[5] * right[6] + left[6] * right[10] + left[7] * right[14];
	result.m[7] = left[4] * right[3] + left[5] * right[7] + left[6] * right[11] + left[7] * right[15];
	result.m[8] = left[8] * right[0] + left[9] * right[4] + left[10] * right[8] + left[11] * right[12];
	result.m[9] = left[8] * right[1] + left[9] * right[5] + left[10] * right[9] + left[11] * right[13];
	result.m[10] = left[8] * right[2] + left[9] * right[6] + left[10] * right[10] + left[11] * right[14];
	result.m[11] = left[8] * right[3] + left[9] * right[7] + left[10] * right[11] + left[11] * right[15];
	result.m[12] = left[12] * right[0] + left[13] * right[4] + left[14] * right[8] + left[15] * right[12];
	result.m[13] = left[12] * right[1] + left[13] * right[5] + left[14] * right[9] + left[15] * right[13];
	result.m[14] = left[12] * right[2] + left[13] * right[6] + left[14] * right[10] + left[15] * right[14];
	result.m[15] = left[12] * right[3] + left[13] * right[7] + left[14] * right[11] + left[15] * right[15];

	if (RGLinfo.matrixMode == RGL_MODELVIEW)
		RGLinfo.transformRequired = 1;
	return result;
}
#endif /* RGL_MODERN_OPENGL */

#endif /* RGL_IMPLEMENTATION */