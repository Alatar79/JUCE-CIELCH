# Description
A CIELCH colour space for the JUCE framework (http://www.juce.com). 

The CIE LCH colour space is a colour space, which reflects how humans perceive colours. LCH is an abbreviation for Lightness, Chroma and Hue. Picking and interpolating colours in the CIE LCH colour space gives more natural results, than if you would use a HSV/HSL colour space. You can read more on Wikipedia: https://en.wikipedia.org/wiki/Lab_color_space

I have subclassed the JUCE::Colour class and added functions, which support the CIE LCH colour space. The new class is called CIELCHColour.

# Demo
The repository comes with a demo project, which shows how to use the CIELCHColour class:
https://github.com/Alatar79/JUCE-CIELCH/tree/master/demos/CIELCHColourDemo

Here is a screenshot of the colour demo: https://github.com/Alatar79/JUCE-CIELCH/blob/master/Screenshot.png

# Documentation
http://alatar79.github.io/CIELCH/Doc/html/classCIELCHColour.html

# Prerequisites
You need the JUCE framework in order to use the CIELCHColour class. JUCE is a C++ cross-platform framework for GUI and audio. Get it from here: http://www.juce.com

# License
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
