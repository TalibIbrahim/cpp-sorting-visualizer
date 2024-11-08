#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <raylib.h>

using namespace std;

const int SCREEN_WIDTH = 1600; // Updated screen width to 1600
const int SCREEN_HEIGHT = 900; // Updated screen height to 900
const int NUM_BARS = 50;
const int PADDING = 100;                                // Define padding on both sides
const int AVAILABLE_WIDTH = SCREEN_WIDTH - 2 * PADDING; // Available width for bars
const int BAR_WIDTH = AVAILABLE_WIDTH / NUM_BARS;       // Adjust bar width to fit available space

vector<int> generateArray()
{
    vector<int> array;
    for (int i = 0; i < NUM_BARS; i++)
    {
        array.push_back(rand() % SCREEN_HEIGHT); // Random height between 0 and SCREEN_HEIGHT
    }
    return array;
}

void drawArray(const vector<int> &array, bool isSorted)
{
    // Draw the bars with padding on the left and right sides
    for (int k = 0; k < array.size(); k++)
    {
        int xPos = PADDING + k * BAR_WIDTH; // Apply the left padding
        if (isSorted)
        {
            // If sorted, show green bars
            DrawRectangle(xPos, SCREEN_HEIGHT - array[k], BAR_WIDTH - 2, array[k], GREEN);
        }
        else
        {
            // Draw white bars by default
            DrawRectangle(xPos, SCREEN_HEIGHT - array[k], BAR_WIDTH - 2, array[k], WHITE);
        }
    }
}

void bubbleSort(vector<int> &array, bool &isSorted, bool &isSorting)
{
    int n = array.size();
    bool swapped = false;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            // Highlight the two bars being compared with red
            BeginDrawing();
            ClearBackground(BLACK); // Clear background each time before drawing

            // Show array with bars (red for comparing)
            for (int k = 0; k < array.size(); k++)
            {
                int xPos = PADDING + k * BAR_WIDTH; // Apply the left padding
                if (k == j || k == j + 1)
                {
                    // Color the bars being compared with red
                    DrawRectangle(xPos, SCREEN_HEIGHT - array[k], BAR_WIDTH - 2, array[k], RED);
                }
                else
                {
                    // Other bars are white
                    DrawRectangle(xPos, SCREEN_HEIGHT - array[k], BAR_WIDTH - 2, array[k], WHITE);
                }
            }

            EndDrawing();

            // Compare and swap if necessary
            if (array[j] > array[j + 1])
            {
                swap(array[j], array[j + 1]);
                swapped = true;
            }

            // Allow time for the visualization to update
            if (IsKeyPressed(49)) // Use the ASCII value for '1' key (49)
            {
                return; // Stop the sort if '1' is pressed
            }
        }

        // If no elements were swapped, array is sorted
        if (!swapped)
        {
            break;
        }
    }
    isSorted = true;   // Mark the array as sorted
    isSorting = false; // Stop sorting
}

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sorting Visualizer");
    SetTargetFPS(60);

    vector<int> array = generateArray(); // Generate an unsorted array
    bool isSorted = false;
    bool isSorting = false;

    while (!WindowShouldClose())
    {
        // Listen for key press (SPACE to regenerate the array, if not sorting)
        if (IsKeyPressed(KEY_SPACE) && !isSorting)
        {
            array = generateArray(); // Regenerate the array
            isSorted = false;        // Reset the sorted flag
        }

        // Check if '1' is pressed to start sorting
        if (IsKeyPressed(49) && !isSorting) // Use ASCII for '1' (49)
        {
            isSorting = true;
            isSorted = false; // Reset the sorted flag
        }

        // Run the sorting algorithm if not sorted
        if (!isSorted && isSorting)
        {
            bubbleSort(array, isSorted, isSorting); // Sort the array
        }

        // Display the sorting message and instructions
        BeginDrawing();
        ClearBackground(BLACK);

        // Show array (whether unsorted or sorted)
        drawArray(array, isSorted);

        // Show instructions
        DrawText("Press SPACE to regenerate the array", 5, 10, 20, RAYWHITE);
        DrawText("1: Bubble Sort", 420, 10, 20, BLUE);

        EndDrawing();
    }

    CloseWindow(); // Close window and OpenGL context
    return 0;
}
