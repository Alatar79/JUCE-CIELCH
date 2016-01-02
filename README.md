# JUCE-CIELCH
A CIELCH colour space for the JUCE framework. 

The CIE LCH colour space is a colour space, which reflects how humans perceive colours. LCH is an abbreviation for Lightness, Chroma and Hue. Picking and interpolating colours in the CIE LCH colour space gives more natural results, than if you would use a HSV/HSL colour space. You can read more on Wikipedia: https://en.wikipedia.org/wiki/Lab_color_space

I have subclassed the JUCE::Colour class and added functions, which support the CIE LCH colour space. 
JUCE is a C++ cross-platform framework for GUI and audio: https://github.com/julianstorer/JUCE

The repository contains the CIELCHColour class and a demo application, which shows how to use the class. 
