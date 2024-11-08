#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <raylib.h>

using namespace std;

const int SCREEN_WIDTH = 1400;
const int SCREEN_HEIGHT = 800;
const int BAR_WIDTH = 20;
const int NUM_BARS = SCREEN_WIDTH / BAR_WIDTH;

// Function to generate an array of random heights for bars
vector<int> generateArray()
{
    vector<int> array;
    for (int i = 0; i < NUM_BARS; i++)
    {
        array.push_back(rand() % SCREEN_HEIGHT); // Random height between 0 and SCREEN_HEIGHT
    }
    return array;
}

int main()
{
    srand(time(0)); // Seed for random number generation

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Array Visualizer");
    SetTargetFPS(60);

    // Initial array generation
    vector<int> array = generateArray();
    bool regenerate = false;

    while (!WindowShouldClose())
    {
        // Check for button press (space bar) to regenerate the array
        if (IsKeyPressed(KEY_SPACE))
        {
            regenerate = true;
        }

        // Regenerate array if button was pressed
        if (regenerate)
        {
            array = generateArray();
            regenerate = false;
        }

        BeginDrawing();
        ClearBackground(BLACK);

        // Draw the array as vertical bars
        for (int i = 0; i < array.size(); i++)
        {
            DrawRectangle(i * BAR_WIDTH, SCREEN_HEIGHT - array[i], BAR_WIDTH - 2, array[i], WHITE); // Draw each bar
        }

        // Draw instructions
        DrawText("Press SPACE to regenerate the array", 10, 10, 20, RAYWHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
