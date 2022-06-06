#include <ti/getcsc.h>
#include <ti/screen.h>
#include <graphx.h>
#include <math.h>
#include <keypadc.h>
#include <string.h>

// Screen resolution and calculated line length
const double lineLength = 0.8;
const int xPixels = 319;
const int halfXPixels = 159;
const int yPixels = 239;
const int halfYPixels = 119;

// Functions that define the differential equation being graphed
double solveNumerator(int x, int y) {
    return -y;
}

double solveDenominator(int x, int y) {
    return x;
}

// Functions that convert coordinate values from our arbitrary units to pixels
int xUnitsToPixels(double x, double xDimension) {
    return (x * halfXPixels / xDimension) + halfXPixels;
}

int yUnitsToPixels(double y, double yDimension) {
    return -(y * halfYPixels / yDimension) + halfYPixels;
}

int main(void) {

    // Dimensions of the field
    int xDimension = 10;
    int yDimension = 10;

    // Preparing the screen
    os_ClrHome();
    gfx_Begin();

    do {

        // Draw axes
        gfx_SetColor(OS_COLOR_BLACK);
        gfx_Line(halfXPixels, 0, halfXPixels, yPixels);
        gfx_Line(0, halfYPixels, xPixels, halfYPixels);

        // Draw axis tick marks
        for (int x = -xDimension; x <= xDimension; x++) {
            gfx_Line(xUnitsToPixels(x, xDimension), halfYPixels - 5,
                xUnitsToPixels(x, xDimension), halfYPixels + 5);
        }
        for (int y = -yDimension; y <= yDimension; y++) {
            gfx_Line(halfXPixels - 5, yUnitsToPixels(y, yDimension),
                halfXPixels + 5, yUnitsToPixels(y, yDimension));
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
                        xUnitsToPixels(x - horizontal, xDimension),
                        yUnitsToPixels(y - slope * horizontal, yDimension),
                        xUnitsToPixels(x + horizontal, xDimension), 
                        yUnitsToPixels(y + slope * horizontal, yDimension)
                    );
                }
            }
        }

        // Scan for keypad input and adjust dimensions accordingly
        kb_Scan();
        kb_key_t key = kb_Data[7];

        switch (key) {
            case kb_Up:
                yDimension++;
                gfx_End();
                gfx_Begin();
            case kb_Down:
                yDimension--;
                gfx_End();
                gfx_Begin();
            case kb_Left:
                xDimension--;
                gfx_End();
                gfx_Begin();
            case kb_Right:
                xDimension++;
                gfx_End();
                gfx_Begin();
            default:
                break;
        }
    } while (kb_Data[1] != kb_2nd);

    // Break the loop and end the program once the '2nd' key is pressed
    gfx_End();
    return 0;
}
