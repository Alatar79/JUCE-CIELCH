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


#ifndef GEOMETRYCOMPONENT_H_INCLUDED
#define GEOMETRYCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "../../../module/CIELCHColour.h"

class GeometryComponent : public Component,
                          public Slider::Listener,
                          public ComboBoxListener
{
public:

    GeometryComponent();

private:
    void paint(Graphics& g) override;
    void resized() override;
    
    void drawGeometries(Graphics& g, int startx, int starty);
    void drawBackgroundSquare(Graphics& g, float x, float y, float width, float height);

    void sliderValueChanged(Slider *slider) override;
    void comboBoxChanged(ComboBox* comboBox) override;

    enum ColourPlane
    {
        LoverC = 1,
        CoverH,
        LoverH,
        BoverS,
        SoverH,
        BoverH
    };

    Slider lchSlider;
    Slider hsvSlider;

    ComboBox lchChoice;
    ComboBox hsvChoice;

    String lchCaption;
    String lchXAxis;
    String lchYAxis;
    String hsvCaption;
    String hsvXAxis;
    String hsvYAxis;


private:

    Image img;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GeometryComponent);
};



#endif  // GEOMETRYCOMPONENT_H_INCLUDED
