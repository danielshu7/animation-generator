#ifdef __cplusplus
extern "C" {
#endif

#ifndef F_3D_H
#define F_3D_H

/* the clipping window */
static float xmin = 0.0;
static float xmax = 1.0;
static float ymin = 0.0;
static float ymax = 1.0;

static void set_clip_window(float, float, float, float);
static int clip_line(float *, float *, float *, float *);

// line drawing header
void draw_line(float, float, float, float);
int near_far_clip(float, float, float *, float *, float *, float *,
                  float *, float *);





#define ROW 4
#define COL 4

/* Definitions of the types of structures and variables used in the following
   code.  Use these or implement your own. */

/* structure definitions */
typedef struct
{
    float  mat[ROW][COL];
}  matrix_unit;

typedef struct
{
    float i;
    float j;
    float k;
} Vector;

typedef struct
{
    float x;
    float y;
    float z;
    float r;
    float g;
    float b;
} Vertex_unit;

typedef struct
{
    float mat41[ROW];
} matrix41;

extern float Near, Far;

const matrix_unit I = {
        { {1., 0., 0., 0.},
          {0., 1., 0., 0.},
          {0., 0., 1., 0.},
          {0., 0., 0., 1.}  },
};

extern int width, height;         /* height and width of frame buffer */

extern matrix_unit first;   // first matrix in stack

extern matrix_unit *stack[50];    /* array of pointers to act as a stack */

const int top = 0;                   /* points to top of the stack */

extern int perspflag;

extern matrix_unit orth;       /* global ortho and perspective matrices */
/* to be used in Vertex3f */
extern matrix_unit perspect;


int Mult_mat(matrix_unit *left, matrix_unit *right, matrix_unit *result);
int Copy_mat(matrix_unit *from, matrix_unit *to);

/* These go in your .h file */
void gtLookAt( float fx, float fy, float fz, float atx, float aty,
               float atz, float upx, float upy, float upz);
void gtVertex3f(float x, float y, float z);

#endif //F_3D_H

#ifdef __cplusplus
}
#endif