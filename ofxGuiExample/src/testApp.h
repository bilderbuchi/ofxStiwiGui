#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "ofxGuiApp.h"


class testApp : public ofxGuiApp {

	public:

		void setup();
		void update();
		void draw();

		void setupGui();
		void handleGui(int parameterId, int task, void* data, int length);

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		
		float bkg;
};

#endif

