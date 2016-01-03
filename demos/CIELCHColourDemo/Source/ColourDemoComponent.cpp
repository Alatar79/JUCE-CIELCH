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


#include "ColourDemoComponent.h"


ColourDemoComponent::ColourDemoComponent()
{
    setSize(940, 920);
    addAndMakeVisible(blenderExample);
    addAndMakeVisible(desaturationExample);
    addAndMakeVisible(geometryExample);

    tooltip = new TooltipWindow();
    tooltip->setMillisecondsBeforeTipAppears(200);
    getLookAndFeel().setColour(TooltipWindow::backgroundColourId, Colours::lightgrey);
    getLookAndFeel().setColour(TooltipWindow::textColourId, Colours::black);

    setOpaque(true);

}

ColourDemoComponent::~ColourDemoComponent() { }

void ColourDemoComponent::paint(Graphics& g)
{
    g.fillAll(Colours::white);

    g.setColour(Colours::black);
    g.setFont(Font("Arial", 25, Font::bold));
    g.drawText("Comparison of CIE LCH versus HSV colour space", 15, 0, getWidth() - 15, 50, Justification::centredLeft);
    g.drawLine(15, 40, (float)getWidth() - 15, 40, 1);
}

void ColourDemoComponent::resized()
{
    blenderExample.setBounds(15, 80, getWidth() - 15, 135);
    desaturationExample.setBounds(15, 260, getWidth() - 15, 240);
    geometryExample.setBounds(15, 525, getWidth() - 15, 382);
}

