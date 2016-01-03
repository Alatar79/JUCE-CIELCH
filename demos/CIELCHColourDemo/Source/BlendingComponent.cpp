/*
==============================================================================

This file is part of the CIELCH Colour JUCE module
Copyright 2016 by Alatar79

The CIELCH JUCE module is hosted on github: https://github.com/Alatar79/JUCE-CIELCH

------------------------------------------------------------------------------

The CIELCH Colour JUCE module is provided under the terms of The MIT License (MIT):

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

==============================================================================
*/


#include "BlendingComponent.h"

BlendingComponent::BlendingComponent()
{

}

void BlendingComponent::paint(Graphics& g)
{
    drawBlender(g, 105, 40, CIELCHColour(0xffff7e00), CIELCHColour(0xff00caff));
    drawBlender(g, 375, 40, CIELCHColour(0xffff008c), CIELCHColour(0xff00caff));
    drawBlender(g, 645, 40, Colours::yellow, Colours::blue);

    g.setFont(Font("Arial", 20, Font::plain));
    g.setColour(Colours::black);
    g.drawText("Comparison of colour blending. CIE LCH gives smoother colour transitions:", 0, 0, getWidth(), 25, Justification::centredLeft);
    g.drawText("HSV:", 0, 50, 300, 25, Justification::centredLeft);
    g.drawText("CIE LCH:", 0, 92, 300, 25, Justification::centredLeft);

}

void BlendingComponent::drawColourRect(Graphics& g, float x, float y, float size, CIELCHColour& c)
{
    bool imaginary;

    g.setColour(c);
    g.fillRoundedRectangle(x, y, size, size, 3);
    g.setColour(c.withCIELightness(c.getCIELightness() - 0.1f, imaginary));
    g.drawRoundedRectangle(x + 1, y + 1, size - 2, size - 2, 3, 2);
    g.setColour(Colours::white);
    g.drawRoundedRectangle(x, y, size, size, 3, 2);
    g.setColour(Colours::lightgrey);
    g.drawRoundedRectangle(x - 1, y -1, size + 2, size + 2, 3, 2);

}


void BlendingComponent::drawBlender(Graphics& g, float startx, float starty, const CIELCHColour& start, const CIELCHColour& end)
{

    int steps = 6;
    float height = 40;
    float squareHeight = (height * 0.75f);
    float width = steps * height;
    float border = 0.25f * height;

    g.setColour(Colours::lightgrey.brighter(0.3f));
    g.fillRoundedRectangle(startx, starty, width + border, height * 2 + border, 3);
    g.setColour(Colours::lightgrey);
    g.drawRoundedRectangle(startx, starty, width + border, height * 2 + border, 3, 2);

    float sh, ss, sb;
    float eh, es, eb;
    start.getHSB(sh, ss, sb);
    end.getHSB(eh, es, eb);

    float sL, sC, sH;
    float eL, eC, eH;
    start.getCIELCH(sL, sC, sH);
    end.getCIELCH(eL, eC, eH);

    float deltah = (eh - sh) / (steps - 1);
    float deltas = (es - ss) / (steps - 1);
    float deltab = (eb - sb) / (steps - 1);

    float deltaL = (eL - sL) / (steps - 1);
    float deltaC = (eC - sC) / (steps - 1);
    float deltaH = (eH - sH) / (steps - 1);

    for (int x = 0; x < 6; x++)
    {
        CIELCHColour c;
        bool imaginary;

        c = juce::Colour::fromHSV(sh + x * deltah, ss + x * deltas, sb + x * deltab, 1.0);
        drawColourRect(g, startx + border + x * height, starty + border, squareHeight, c);

        c = c.fromCIELCH(sL + x * deltaL, sC + x * deltaC, 1.0f + sH + x * deltaH, 1.0f, imaginary);
        drawColourRect(g, startx + border + x * height, starty + border + height, squareHeight, c);

    }
}