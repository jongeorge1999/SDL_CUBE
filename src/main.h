#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 960

typedef struct Vector3D{
    float x;
    float y;
    float z;
} vec3d_t;

typedef struct Vector2D{
    int x;
    int y;
} vec2d_t;

vec2d_t project3Dto2D(vec3d_t point, int scale);
void rotateX(vec3d_t *point, float angle);
void rotateY(vec3d_t *point, float angle);
void rotateZ(vec3d_t *point, float angle);