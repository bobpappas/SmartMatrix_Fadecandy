/*
 * Fadecandy Firmware
 *
 * Copyright (c) 2013 Micah Elizabeth Scott
 * Modifications (c) 2015 Louis Beaudoin (Pixelmatix)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

// Requires SmartMatrix 3.0 branch

// There are issues compiling, if you see "undefined reference" and "error: ld return 1", wait a few seconds then try compiling again
// the order of #includes is very sensitive, including <SmartMatrix.h> before "Layer_Fadecandy.h" will break things for example

#include "Layer_Fadecandy.h"
#include <SmartMatrix.h>

static fcBuffers buffers;
fcLinearLUT fcBuffers::lutCurrent;
SmartMatrix matrix;
SMLayerForeground foregroundLayer;
SMLayerFadecandy fadecandyLayer(&buffers);

extern "C" int usb_rx_handler(usb_packet_t *packet)
{
    // USB packet interrupt handler. Invoked by the ISR dispatch code in usb_dev.c
    return buffers.handleUSB(packet);
}

void setup() {
    matrix.addLayer(&fadecandyLayer);
    matrix.addLayer(&foregroundLayer);
    matrix.begin();
    foregroundLayer.scrollText("fadecandy",1);
}

void loop() {
    // load a single row into the refresh buffer
    //matrix.matrixCalculations();

    // We can switch to the next frame's buffer now.
    buffers.finalizeFrame();

    // Performance counter, for monitoring frame rate externally
    perf_frameCounter++;
}
