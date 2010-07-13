/*  ofxGuiApp.h
 *  openFrameworks
 *
 *  Copyright 2008 alphakanal/Stefan Kirch.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef _OFXGUI_APP
#define _OFXGUI_APP

#include "ofTypes.h"
#include "ofxGui.h"
#include "ofxGuiMovable.h"

class ofxGuiApp : public ofBaseApp, public ofxGuiListener{

	public:
        ofxGuiApp() {
            mouseX = mouseY = 0;

			gui = ofxGui::Instance(this);
			mover = new ofxGuiMovable(gui);
        }

		virtual ~ofxGuiApp(){}

		virtual void setup(){}
		virtual void update(){}
		virtual void draw(){}
		virtual void exit(){}

		virtual void setupGui(){}
		virtual void handleGui(int parameterId, int task, void* data, int length){}


		virtual void windowResized(int w, int h){}

		virtual void keyPressed( int key ){}
		virtual void keyReleased( int key ){}

		virtual void mouseMoved( int x, int y ){}
		virtual void mouseDragged( int x, int y, int button ){}
		virtual void mousePressed( int x, int y, int button ){}
		virtual void mouseReleased(){}
		virtual void mouseReleased(int x, int y, int button ){}

		virtual void audioReceived( float * input, int bufferSize, int nChannels ){}
		virtual void audioRequested( float * output, int bufferSize, int nChannels ){}

		int mouseX, mouseY;			// for processing heads

		ofxGui*				gui;
		ofxGuiMovable*      mover;
};

#endif


