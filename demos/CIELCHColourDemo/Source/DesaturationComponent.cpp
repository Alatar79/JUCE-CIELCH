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


#include "DesaturationComponent.h"


DesaturationComponent::DesaturationComponent()
{
    img = ImageCache::getFromMemory(BinaryData::jucelogo_128x128_png, BinaryData::jucelogo_128x128_pngSize);

    chromaSlider.setRange(0.0f, 1.0f);
    chromaSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    chromaSlider.setValue(0.5);
    chromaSlider.setTooltip("Change the LCH Chroma");
    chromaSlider.addListener(this);
    addAndMakeVisible(chromaSlider);

    saturationSlider.setRange(0.0f, 1.0f);
    saturationSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    saturationSlider.setValue(0.5);
    saturationSlider.setTooltip("Change the HSV Saturation");
    saturationSlider.addListener(this);
    addAndMakeVisible(saturationSlider);

}


void DesaturationComponent::paint(Graphics& g)
{
    drawImages(g, 105, 40);

    g.setColour(Colours::black);
    g.setFont(Font("Arial", 20, Font::plain));
    g.drawText("Comparison of desaturation. CIE LCH gives a more natural desaturation which preserves lightness:", 0, 0, getWidth(), 25, Justification::centredLeft);
    g.drawText("Original:", 0, 40, getWidth(), img.getHeight(), Justification::centredLeft);
    g.drawText("CIE LCH:", 300, 40, getWidth(), img.getHeight(), Justification::centredLeft);
    g.drawText("HSV:", 650, 40, getWidth(), img.getHeight(), Justification::centredLeft);

    g.drawText("Chroma *= " + String(chromaSlider.getValue(), 2), 420, 40 + 165, 200, 20, Justification::centredLeft);
    g.drawText("Saturation *= " + String(saturationSlider.getValue(), 2), 735, 40 + 165, 200, 20, Justification::centredLeft);
}

void DesaturationComponent::resized()
{
    chromaSlider.setBounds(400, 40 - 5, 20, img.getHeight() + 30 + 8);
    saturationSlider.setBounds(715, 40 - 5, 20, img.getHeight() + 30 + 8);
}

void DesaturationComponent::sliderValueChanged(Slider* /* slider */)
{
    repaint();
}

void DesaturationComponent::drawImages(Graphics& g, int  startx, int starty)
{

    int border = 15;
    int width = img.getWidth() + 2 * border;
    int height = img.getHeight() + 2 * border;

    drawBackgroundSquare(g, (float) startx, (float) starty, (float) width, (float) height);
    g.drawImageAt(img, startx + border, starty + border);

    int startx2 = (int) (startx + img.getWidth() * 2.46);
    drawBackgroundSquare(g, (float) startx2, (float) starty, (float) width, (float) height);

    int startx3 = (int) (startx2 + img.getWidth() * 2.46);
    drawBackgroundSquare(g, (float) startx3, (float) starty, (float) width, (float) height);

    for (int x = 0; x < img.getWidth(); x++)
    {
        for (int y = 0; y < img.getHeight(); y++)
        {
            CIELCHColour c = img.getPixelAt(x, y);
            bool imaginary;

            CIELCHColour CIEdesaturation = c.withMultipliedCIEChroma((float)chromaSlider.getValue(), imaginary);
            g.setColour(CIEdesaturation.getJuceColour());
            //g.setPixel(startx2 + border + x, starty + border + y);
            g.drawRect(startx2 + border + x, starty + border + y, 1, 1);

            Colour HSVdesaturation = c.getJuceColour().withMultipliedSaturation((float)saturationSlider.getValue());
            g.setColour(HSVdesaturation);
            g.drawRect(startx3 + border + x, starty + border + y, 1, 1);

        }
    }
}

void DesaturationComponent::drawBackgroundSquare(Graphics& g, float x, float y, float width, float height)
{
    g.setColour(Colours::lightgrey.brighter(0.3f));
    g.fillRoundedRectangle(x, y, width, height, 3);
    g.setColour(Colours::lightgrey);
    g.drawRoundedRectangle(x, y, width, height, 3, 2);
}