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


