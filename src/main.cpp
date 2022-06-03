#include <ti/getcsc.h>
#include <ti/screen.h>
#include <graphx.h>
#include <math.h>

// Dimensions of the field
const int xDimension = 10;
const int yDimension = 10;

// Screen resolution and calculated line length
const double lineLength = 0.8;
const int xPixels = 319;
const int halfXPixels = ceil(xPixels / 2);
const int yPixels = 239;
const int halfYPixels = ceil(yPixels / 2);

// Functions that define the differential equation being graphed
double solveNumerator(int x, int y) {
    return -y;
}

double solveDenominator(int x, int y) {
    return x;
}

// Functions that convert coordinate values from our arbirary units to pixels.
int xUnitsToPixels(double x) {
    return (x * halfXPixels / xDimension) + halfXPixels;
}

int yUnitsToPixels(double y) {
    return -(y * halfYPixels / yDimension) + halfYPixels;
}

int main(void) {

    // Preparing the screen
    os_ClrHome();
    gfx_Begin();

    // Draw axes
    gfx_SetColor(OS_COLOR_BLACK);
    gfx_Line(halfXPixels, 0, halfXPixels, yPixels);
    gfx_Line(0, halfYPixels, xPixels, halfYPixels);

    // Draw axis tick marks
    for (int x = -xDimension; x <= xDimension; x++) {
        gfx_Line(xUnitsToPixels(x), halfYPixels - 5, xUnitsToPixels(x), halfYPixels + 5);
    }
    for (int y = -yDimension; y <= yDimension; y++) {
        gfx_Line(halfXPixels - 5, yUnitsToPixels(y), halfXPixels + 5, yUnitsToPixels(y));
    }

    // Draw slope field
    for (int x = -xDimension; x <= xDimension; x++) {
        for (int y = -yDimension; y <= yDimension; y++) {

            // Calculate slope for the line
            double numerator = solveNumerator(x, y);
            double denominator = solveDenominator(x, y);
            if (denominator != 0) {
                double slope = numerator / denominator;

                // Calculate horizontal offset
                double horizontal = lineLength / (2 * pow((1 + pow(slope, 2)), 0.5));

                // Determine which color to use
                if (slope >= 2) {
                    gfx_SetColor(OS_COLOR_RED);
                } else if (slope >= 1) {
                    gfx_SetColor(OS_COLOR_ORANGE);
                } else if (slope >= 0) {
                    gfx_SetColor(OS_COLOR_YELLOW);
                } else if (slope >= -1) {
                    gfx_SetColor(OS_COLOR_GREEN);
                } else if (slope >= -2) {
                    gfx_SetColor(OS_COLOR_LTBLUE);
                } else {
                    gfx_SetColor(OS_COLOR_NAVY);
                }

                // Convert coordinates to pixels and draw line
                gfx_Line(
                    xUnitsToPixels(x - horizontal),
                    yUnitsToPixels(y - slope * horizontal),
                    xUnitsToPixels(x + horizontal), 
                    yUnitsToPixels(y + slope * horizontal)
                );
            }
        }
    }

    // Close the program upon button press
    while (!os_GetCSC());
    gfx_End();
    return 0;
}
