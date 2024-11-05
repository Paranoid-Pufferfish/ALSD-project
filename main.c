#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
/*========================Define Macros========================*/
#define SCREEN_HEIGHT 768 //Window resolution1366x768
#define SCREEN_WIDTH 1366
#define COL_WIDTH 10 // Bar width
#define ARRAY_SIZE (SCREEN_WIDTH/COL_WIDTH) // Size of Array (SCREEN_WIDTH/COL_WIDTH)
#define COL_HEIGHT ((SCREEN_HEIGHT-40)/ARRAY_SIZE) // Bar height (SCREEN_HEIGHT - 40(leaving headroom for text) / ARRAY_SIZE)

char algorithm[] = "Insertion sort"; // Algorithm name

// Uncomment to try the worst case scenario mathematically
// #define WORST
/*========================Define Macros========================*/
int sortArray(int array[]) {
    int n = 0;
    bool state_array[ARRAY_SIZE] = {false};
    for (int i = 1; i < ARRAY_SIZE && !WindowShouldClose(); ++i) {
        for (int j = i; j > 0 && array[j - 1] > array[j] && !WindowShouldClose(); --j) {
            BeginDrawing();
            const int temp = array[j];
            array[j] = array[j - 1];
            array[j - 1] = temp;
            state_array[j] = state_array[j - 1] = true;
            n++;
            ClearBackground(BLACK);
            for (int k = 0; k < ARRAY_SIZE && !WindowShouldClose(); ++k) {
                if (state_array[k])
                    DrawRectangle(k * COL_WIDTH,SCREEN_HEIGHT - array[k] * COL_HEIGHT,COL_WIDTH, array[k] * COL_HEIGHT,
                                  RED);
                else
                    DrawRectangle(k * COL_WIDTH,SCREEN_HEIGHT - array[k] * COL_HEIGHT,COL_WIDTH, array[k] * COL_HEIGHT,
                                  GREEN);
            }
            DrawText(TextFormat("Sorting Algorithm: %s\nSample Size : %d \nIteration N° %d", algorithm,ARRAY_SIZE, n),
                     0, 0, 18,WHITE);
#ifdef WORST
            DrawText("Worst case scenario",0,50,18,RED);
#endif

            state_array[j] = state_array[j - 1] = false;
            EndDrawing();
        }
    }
    return n;
}

int main(void) {
    unsigned int array[ARRAY_SIZE];
    for (int i = 0; i < ARRAY_SIZE; ++i) {
#ifdef WORST
        array[i]= ARRAY_SIZE-i;
#else
        array[i] = arc4random_uniform(ARRAY_SIZE) + 1;
#endif
    }
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Projet ALSD : Insertion");
#ifdef WORST
    SetTargetFPS(ARRAY_SIZE);
#else
    SetTargetFPS(60);
#endif

    const int TotalIterations = sortArray(array);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText(TextFormat("Sorting Algorithm: %s\nSample Size: %d \nTotal Iterations: %d", algorithm,ARRAY_SIZE,
                            TotalIterations), 0, 0, 18,WHITE);
#ifdef WORST
        DrawText("Worst case scenario",0,50,18,RED);
#endif

        for (int k = 0; k < ARRAY_SIZE; ++k) {
            DrawRectangle(k * COL_WIDTH,SCREEN_HEIGHT - array[k] * COL_HEIGHT,COL_WIDTH, (int) array[k] * COL_HEIGHT,
                          YELLOW);
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
