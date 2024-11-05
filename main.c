#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
/*========================Define Macros========================*/
#define SCREEN_HEIGHT 1000 // Window resolution1366x768
#define SCREEN_WIDTH 1920
#define FPS 0 // Max FPS (Set to 0 for unlimited)
#define COL_WIDTH (SCREEN_WIDTH/ARRAY_SIZE) // Bar width
#define ARRAY_SIZE 940 // Size of Array (Shouldn't exceed HEIGHT-60)
#define COL_HEIGHT ((SCREEN_HEIGHT-60)/ARRAY_SIZE) // Bar height (SCREEN_HEIGHT - 60(leaving headroom for text) / ARRAY_SIZE)

// Uncomment to try the worst case scenario mathematically
// #define WORST
#define SELECT_COLOR RED // Color of the bar being treated
#define ARRAY_COLOR GREEN // Color of the rest of the array
#define SUCCESS_COLOR GOLD // Color of the array after sorting
// Uncomment to get a gradiant
#define GRADIANT
#ifdef GRADIANT
#define COLOR1 PINK // First Color in the gradiant
#define COLOR2 WHITE // Second color in the gradiant
#endif
#define SELECTION // Use selection sort
//#define INSERTION // Use Insertion sort

#ifdef INSERTION
char algorithm[] = "Insertion sort"; // Algorithm name
#elifdef SELECTION
char algorithm[] = "Selection sort"; // Algorithm name
#endif


/*========================Define Macros========================*/
// NOLINTBEGIN
Color lerpRGB(const Color colorA, const Color colorB, const double t) {
    Color lerpRGB = {};
    lerpRGB.r = colorA.r + ((colorB.r - colorA.r) * t);
    lerpRGB.g = colorA.g + ((colorB.g - colorA.g) * t);
    lerpRGB.b = colorA.b + ((colorB.b - colorA.b) * t);
    lerpRGB.a = colorA.a + ((colorB.a - colorA.a) * t);
    return lerpRGB;
}
void outputArray(int array[], bool state_array[], int n) {
    ClearBackground(BLACK);
    for (int k = 0; k < ARRAY_SIZE && !WindowShouldClose(); ++k) {
        if (state_array[k])
            DrawRectangle(k * COL_WIDTH,SCREEN_HEIGHT - array[k] * COL_HEIGHT,COL_WIDTH, array[k] * COL_HEIGHT,
                          SELECT_COLOR);
        else {
#ifdef GRADIANT
            const double t = (double) array[k] / ARRAY_SIZE;
            DrawRectangle(k * COL_WIDTH,SCREEN_HEIGHT - array[k] * COL_HEIGHT,COL_WIDTH, array[k] * COL_HEIGHT,
                          lerpRGB(COLOR1,COLOR2, t));
#else
            DrawRectangle(k * COL_WIDTH,SCREEN_HEIGHT - array[k] * COL_HEIGHT,COL_WIDTH, array[k] * COL_HEIGHT,
                          ARRAY_COLOR);
#endif
        }
    }
    DrawText(TextFormat("Sorting Algorithm: %s\nSample Size : %d \nIteration N° %d\nTime : %lfs", algorithm,
                        ARRAY_SIZE, n, GetTime()),
             0, 0, 18,WHITE);
#ifdef WORST
    DrawText("Worst case scenario", 0, 60, 18,RED);
#endif
}

// NOLINTEND
int sortSelectionArray(int array[]) {
    int n = 0;
    bool state_array[ARRAY_SIZE] = {false};
    for (int i = 0; i < ARRAY_SIZE && !WindowShouldClose(); ++i) {
        int imin = i;
        for (int j = i; j < ARRAY_SIZE && !WindowShouldClose(); ++j) {
            BeginDrawing();
            n++;
            int imint = imin;
            if (array[imin] > array[j])
                imin = j;
            state_array[imint] = state_array[j] = true;
            state_array[i] = true;
            outputArray(array, state_array, n);
            state_array[imint] = state_array[j] = false;
            EndDrawing();
        }
        const int temp = array[imin];
        array[imin] = array[i];
        array[i] = temp;
        state_array[i] = false;
    }
    return n;
}

int sortInsertionArray(int array[]) {
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
            outputArray(array, state_array, n);
            state_array[j] = state_array[j - 1] = false;
            EndDrawing();
        }
    }
    return n;
}

int main(void) {
    int array[ARRAY_SIZE];
    for (int i = 0; i < ARRAY_SIZE; ++i) {
#ifdef WORST
        array[i]= ARRAY_SIZE-i;
#else
        array[i] = (int) arc4random_uniform(ARRAY_SIZE) + 1;
#endif
    }
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Projet ALSD : Sorting Algorithms");

    SetTargetFPS(FPS);
#ifdef SELECTION
    const int TotalIterations = sortSelectionArray(array);
#elifdef INSERTION
    const int TotalIterations = sortInsertionArray(array);
#endif

    const double time = GetTime();
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText(TextFormat("Sorting Algorithm: %s\nSample Size: %d \nTotal Iterations: %d\nTime: %lfs", algorithm,
                            ARRAY_SIZE,
                            TotalIterations, time), 0, 0, 18,WHITE);
#ifdef WORST
        DrawText("Worst case scenario", 0, 60, 18,RED);
#endif

        for (int k = 0; k < ARRAY_SIZE; ++k) {
#ifdef GRADIANT
            const double t = (double) array[k] / ARRAY_SIZE;
            DrawRectangle(k * COL_WIDTH,SCREEN_HEIGHT - array[k] * COL_HEIGHT,COL_WIDTH, array[k] * COL_HEIGHT,
                          lerpRGB(COLOR1,COLOR2, t));
#else
            DrawRectangle(k * COL_WIDTH,SCREEN_HEIGHT - array[k] * COL_HEIGHT,COL_WIDTH, array[k] * COL_HEIGHT,
                          SUCCESS_COLOR);
#endif
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
