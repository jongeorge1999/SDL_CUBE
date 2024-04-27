#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>
#include "main.h"

int main(int argc, char** argv) {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Event event;

    vec3d_t cube[8] = {
        { -1, -1, -1 },
        {  1, -1, -1 },
        {  1,  1, -1 },
        { -1,  1, -1 },
        { -1, -1,  1 },
        {  1, -1,  1 },
        {  1,  1,  1 },
        { -1,  1,  1 }
    };

    float rotX;
    float rotY;
    float rotZ;
    float spinSpeed = 0.001;
    int scale = 100;

    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("3D Cube", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    while (1) {
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT) {
            break;
        }

        rotX = spinSpeed;
        rotY = spinSpeed * 1.8;
        rotZ = spinSpeed * 1.9;

        for (int i = 0; i < 8; i++) {
            rotateX(&cube[i], rotX);
            rotateY(&cube[i], rotY);
            rotateZ(&cube[i], rotZ);
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

        for (int i = 0; i < 4; i++) {
            vec2d_t point1 = project3Dto2D(cube[i], scale);
            vec2d_t point2 = project3Dto2D(cube[(i + 1) % 4], scale);
            SDL_RenderDrawLine(renderer, point1.x, point1.y, point2.x, point2.y);

            point1 = project3Dto2D(cube[i + 4], scale);
            point2 = project3Dto2D(cube[(i + 1) % 4 + 4], scale);
            SDL_RenderDrawLine(renderer, point1.x, point1.y, point2.x, point2.y);

            point1 = project3Dto2D(cube[i], scale);
            point2 = project3Dto2D(cube[i + 4], scale);
            SDL_RenderDrawLine(renderer, point1.x, point1.y, point2.x, point2.y);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(1);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

vec2d_t project3Dto2D(vec3d_t point, int scale) {
    vec2d_t projected;
    projected.x = (int)(point.x * scale) + SCREEN_WIDTH / 2;
    projected.y = (int)(point.y * scale) + SCREEN_HEIGHT / 2;
    return projected;
}

void rotateX(vec3d_t *point, float angle) {
    point->y = point->y * cos(angle) - point->z * sin(angle);
    point->z = point->y * sin(angle) + point->z * cos(angle);
}

void rotateY(vec3d_t *point, float angle) {
    point->x = point->x * cos(angle) - point->z * sin(angle);
    point->z = point->x * sin(angle) + point->z * cos(angle);
}

void rotateZ(vec3d_t *point, float angle) {
    point->x = point->x * cos(angle) - point->y * sin(angle);
    point->y = point->x * sin(angle) + point->y * cos(angle);
}