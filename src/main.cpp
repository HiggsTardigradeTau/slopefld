#include <ti/getcsc.h>
#include <ti/screen.h>
#include <graphx.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define INPUT_SIZE  10

int main(void) {
    // char equationBuffer[INPUT_SIZE];
    // char xScaleBuffer[INPUT_SIZE];
    // char yScaleBuffer[INPUT_SIZE];
    // char spacingBuffer[INPUT_SIZE];

    os_ClrHome();

    // os_GetStringInput("dy / dx = ", equationBuffer, INPUT_SIZE);
    // os_NewLine();
    // os_GetStringInput("X Scale: ", xScaleBuffer, INPUT_SIZE);
    // os_NewLine();
    // os_GetStringInput("Y Scale: ", yScaleBuffer, INPUT_SIZE);
    // os_NewLine();
    // os_GetStringInput("Spacing: ", spacingBuffer, INPUT_SIZE);

    double xScale = 22; // atof(xScaleBuffer) / 2;
    double yScale = 22; // atof(yScaleBuffer) / 2;
    double spacing = 1; // atof(spacingBuffer);

    for (double x = -xScale; x < xScale; x += spacing) {
        for (double y = -yScale; y < yScale; y += spacing) {
            // char slopeBuffer[INPUT_SIZE];

            // for (int i = 0; i < sizeof(equationBuffer); i++) {
                // if (equationBuffer[i] == 'x') {
                    // slopeBuffer[i] = char(x);
                // } else if (equationBuffer[i] == 'y') {
                    // slopeBuffer[i] = char(y);
                // } else {
                    // slopeBuffer[i] = equationBuffer[i];
                // }
            // }

            double slope = x*y;
            double horizontal = pow(pow(3 * spacing / 8, 2) / (1 + pow(slope, 2)), 0.5);

            gfx_Begin();

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

            gfx_Line(x - horizontal, y - slope * horizontal, x + horizontal, y + slope * horizontal);

        }
    }

    while (!os_GetCSC());

    gfx_End();
    return 0;
}