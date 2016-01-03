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


#include "../JuceLibraryCode/JuceHeader.h"
#include "ColourDemoComponent.h"

//==============================================================================
class CIELCH_ColourApplication  : public JUCEApplication
{
public:
    //==============================================================================
    CIELCH_ColourApplication() {}

    const String getApplicationName() override       { return ProjectInfo::projectName; }
    const String getApplicationVersion() override    { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed() override       { return true; }

    //==============================================================================
    void initialise (const String& /* commandLine */) override
    {
        // This method is where you should put your application's initialisation code..

        mainWindow = new MainWindow (getApplicationName());
   
    }

    void shutdown() override
    {
        // Add your application's shutdown code here..

        mainWindow = nullptr; // (deletes our window)
    }

    //==============================================================================
    void systemRequestedQuit() override
    {
        // This is called when the app is being asked to quit: you can ignore this
        // request and let the app carry on running, or call quit() to allow the app to close.
        quit();
    }

    void anotherInstanceStarted (const String& /* commandLine */) override
    {
        // When another instance of the app is launched while this one is running,
        // this method is invoked, and the commandLine parameter tells you what
        // the other instance's command-line arguments were.
    }

    //==============================================================================
    /*
        This class implements the desktop window that contains an instance of
        our MainContentComponent class.
    */
    class MainWindow    : public DocumentWindow
    {
    public:
        MainWindow (String name)  : DocumentWindow (name,
                                                    Colours::lightgrey,
                                                    DocumentWindow::allButtons)
        {
            setUsingNativeTitleBar (true);

            int bestWidth = 940;
            int bestHeight = 920;
            //Parent is the available desktop in this case
            int maxHeight = jmin(getParentHeight(), bestHeight);
            if (maxHeight < bestHeight)
                bestWidth = 960;
            int maxWidth = jmin(getParentWidth(), bestWidth);

            Viewport* viewport = new Viewport();
            viewport->setViewedComponent(new ColourDemoComponent(), true);
            viewport->setSize(maxWidth, maxHeight);
            setContentOwned(viewport, true);

            centreWithSize (maxWidth, maxHeight);
            setVisible (true);

            // Add OpenGL renderer to our main Window. 
            // Used automatically by all our 2D elements in the application. 
            // Very important to do this. Gives big 
            // performance gain, especially on Retina displays. 
            openGLContext.attachTo(*this);
            setOpaque(true);

        }

        void closeButtonPressed() override
        {
            // This is called when the user tries to close this window. Here, we'll just
            // ask the app to quit when this happens, but you can change this to do
            // whatever you need.
            JUCEApplication::getInstance()->systemRequestedQuit();
        }

        /* Note: Be careful if you override any DocumentWindow methods - the base
           class uses a lot of them, so by overriding you might break its functionality.
           It's best to do all your work in your content component instead, but if
           you really have to override any DocumentWindow methods, make sure your
           subclass also calls the superclass's method.
        */

    private:
        /** OpenGL context for speeding up 2D drawings */
        OpenGLContext openGLContext;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
    };

private:
    ScopedPointer<MainWindow> mainWindow;
};

//==============================================================================
// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION (CIELCH_ColourApplication)
