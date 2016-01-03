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


#include "GeometryComponent.h"

GeometryComponent::GeometryComponent()
{
    lchSlider.setRange(0.0f, 1.0f);
    lchSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    lchSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    lchSlider.setValue(0.77);
    lchSlider.addListener(this);
    addAndMakeVisible(lchSlider);

    hsvSlider.setRange(0.0f, 1.0f);
    hsvSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    hsvSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    hsvSlider.setValue(0.77);
    hsvSlider.addListener(this);
    addAndMakeVisible(hsvSlider);

    lchChoice.addItem("L - C", ColourPlane::LoverC);
    lchChoice.addItem("C - H", ColourPlane::CoverH);
    lchChoice.addItem("L - H", ColourPlane::LoverH);
    lchChoice.setSelectedId(ColourPlane::CoverH, NotificationType::sendNotification);
    lchChoice.setTooltip("Change the LCH colour plane");
    lchChoice.addListener(this);
    addAndMakeVisible(lchChoice);

    hsvChoice.addItem("B - S", ColourPlane::BoverS);
    hsvChoice.addItem("S - H", ColourPlane::SoverH);
    hsvChoice.addItem("B - H", ColourPlane::BoverH);
    hsvChoice.setSelectedId(ColourPlane::SoverH, NotificationType::sendNotification);
    hsvChoice.setTooltip("Change the HSV colour plane");
    hsvChoice.addListener(this);
    addAndMakeVisible(hsvChoice);

}

void GeometryComponent::paint(Graphics& g)
{
    drawGeometries(g, 105, 40);

    g.setColour(Colours::black);
    g.setFont(Font("Arial", 20, Font::plain));
    g.drawText("Comparison of geometry. CIE LCH has a rugged geometry, because it follows the human perception:", 0, 0, getWidth(), 25, Justification::centredLeft);
    g.drawText("CIE LCH:", 0, 40, getWidth(), 255, Justification::centredLeft);
    g.drawText("HSV:", 485, 40, getWidth(), 255, Justification::centredLeft);
    g.drawText(lchCaption + String((float)lchSlider.getValue(), 2), lchSlider.getX() + 5, lchSlider.getY() + 20, lchSlider.getWidth(), 20, Justification::centredLeft);
    g.drawText(hsvCaption + String((float)hsvSlider.getValue(), 2), hsvSlider.getX() + 5, hsvSlider.getY() + 20, hsvSlider.getWidth(), 20, Justification::centredLeft);

    g.setColour(Colours::darkgrey.darker());
    g.setFont(Font("Arial", 14, Font::plain));
    g.drawText(lchXAxis, lchSlider.getX() + 22, lchSlider.getY() - 20, 100, 15, Justification::centredLeft);
    g.drawText(hsvXAxis, hsvSlider.getX() + 22, hsvSlider.getY() - 20, 100, 15, Justification::centredLeft);

    g.addTransform(AffineTransform::rotation(-float_Pi / 2, (float) lchSlider.getX() + 22, (float) lchSlider.getY() - 20));
    g.drawText(lchYAxis, lchSlider.getX() + 25, lchSlider.getY() - 37, 100, 15, Justification::centredLeft);
    g.addTransform(AffineTransform::rotation(float_Pi / 2, (float) lchSlider.getX() + 22, (float) lchSlider.getY() - 20));
    g.addTransform(AffineTransform::rotation(-float_Pi / 2, (float) hsvSlider.getX() + 22, (float) hsvSlider.getY() - 20));
    g.drawText(hsvYAxis, hsvSlider.getX() + 25, hsvSlider.getY() - 37, 100, 15, Justification::centredLeft);

}

void GeometryComponent::resized()
{
    lchSlider.setBounds(100, 330, 325, 20);
    hsvSlider.setBounds(565, 330, 325, 20);

    lchChoice.setBounds(0, 40, 100, 35);
    hsvChoice.setBounds(465, 40, 100, 35);

}

void GeometryComponent::sliderValueChanged(Slider* /* slider */)
{
    repaint();
}

void GeometryComponent::comboBoxChanged(ComboBox* comboBox)
{
    ColourPlane id = static_cast<ColourPlane> (comboBox->getSelectedId());

    switch (id)
    {
        case ColourPlane::LoverC :
            lchYAxis = "Lightness";
            lchXAxis = "Chroma";
            lchCaption = "Hue = ";
            lchSlider.setTooltip("Change the LCH Hue");
            break;
        case ColourPlane::CoverH:
            lchYAxis = "Chroma";
            lchXAxis = "Hue";
            lchCaption = "Lightness = ";
            lchSlider.setTooltip("Change the LCH Lightness");
            break;
        case ColourPlane::LoverH:
            lchYAxis = "Lightness";
            lchXAxis = "Hue";
            lchCaption = "Chroma = ";
            lchSlider.setTooltip("Change the LCH Chroma");
            break;
        case ColourPlane::BoverS:
            hsvYAxis = "Brightness";
            hsvXAxis = "Saturation";
            hsvCaption = "Hue = ";
            hsvSlider.setTooltip("Change the HSV Hue");
            break;
        case ColourPlane::SoverH:
            hsvYAxis = "Saturation";
            hsvXAxis = "Hue";
            hsvCaption = "Brightness = ";
            hsvSlider.setTooltip("Change the HSV Brightness");
            break;
        case ColourPlane::BoverH:
            hsvYAxis = "Brightness";
            hsvXAxis = "Hue";
            hsvCaption = "Saturation = ";
            hsvSlider.setTooltip("Change the HSV Saturation");
            break;
        default:
            lchCaption = "Something went wrong! ";
            hsvCaption = "Something went wrong! ";
            break;
    }

    repaint();
}

void GeometryComponent::drawGeometries(Graphics& g, int startx, int starty)
{
    int width = 285;
    int height = 255;

    int border = 15;
    drawBackgroundSquare(g, (float) startx, (float) starty, (float) (width + 2 * border), (float) (height + 2 * border));

    int startx2 = startx + width + 2 * border + 10 * border;
    drawBackgroundSquare(g, (float) startx2, (float) starty, (float) (width + 2 * border), (float) (height + 2 * border));


    for (float x = 0; x < width; x++)
    {
        for (float y = 0; y < height; y++)
        {
            bool imaginary = false;
            CIELCHColour lchColour;
            float interpolate = (float)lchSlider.getValue();
            float phaseShift = 30.0f / 360;
            switch (lchChoice.getSelectedId())
            {
            case ColourPlane::LoverC:
                lchColour = CIELCHColour::fromCIELCH((height - y) / height, x / width, interpolate + phaseShift, 1.0, imaginary);
                break;
            case ColourPlane::CoverH:
                lchColour = CIELCHColour::fromCIELCH(interpolate, (height - y) / height, x / width, 1.0, imaginary);
                break;
            case ColourPlane::LoverH:
                lchColour = CIELCHColour::fromCIELCH((height - y) / height, interpolate, x / width, 1.0, imaginary);
                break;
            default:
                //should never happen
                lchColour = Colours::red;
                break;
            }

            if (!imaginary)
            {
                g.setColour(lchColour);
            }
            else
            {
                //draw checker board
                int qX = (int)round((x + 12.75f) / 25.5f);
                int qY = (int)round((y + 12.75f) / 25.5f);
                if ((qX + qY) % 2 == 0)
                    g.setColour(Colours::darkgrey);
                else
                    g.setColour(Colours::darkgrey.darker());
            }
            //setPixel for LCH geometry
            g.setPixel(startx + border + (int)x, starty + border + (int)y);

            CIELCHColour hsvColour;
            interpolate = (float)hsvSlider.getValue();
            switch (hsvChoice.getSelectedId())
            {
            case ColourPlane::BoverS:
                hsvColour = CIELCHColour::fromHSV(interpolate, x / width, (height - y) / height,  1.0);
                break;
            case ColourPlane::SoverH:
                hsvColour = CIELCHColour::fromHSV(x / width, (height - y) / height, interpolate, 1.0);
                break;
            case ColourPlane::BoverH:
                hsvColour = CIELCHColour::fromHSV(x / width, interpolate, (height - y) / height,  1.0);
                break;
            default:
                //should never happen
                hsvColour = Colours::red;
                break;
            }
            g.setColour(hsvColour);
            g.setPixel(startx2 + border + (int)x, starty + border + (int)y);

        }
    }
}

void GeometryComponent::drawBackgroundSquare(Graphics& g, float x, float y, float width, float height)
{
    g.setColour(Colours::lightgrey.brighter(0.3f));
    g.fillRoundedRectangle(x, y, width, height, 3);
    g.setColour(Colours::lightgrey);
    g.drawRoundedRectangle(x, y, width, height, 3, 2);
}