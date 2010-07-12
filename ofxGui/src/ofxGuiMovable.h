/*
 *  ofxGuiMovable.h
 *  openFrameworks
 *
 */

//	----------------------------------------------------------------------------------------------------

#ifndef OFX_GUIMOVABLE
#define OFX_GUIMOVABLE

//	----------------------------------------------------------------------------------------------------

#include "ofMain.h"
#include "ofEvents.h"
#include "ofxGui.h"

//	----------------------------------------------------------------------------------------------------

class ofxGuiMovable{

public:

	ofxGuiMovable(ofxGui* _gui);
	~ofxGuiMovable();

	void			mouseDragged(int x, int y, int button);
	void			mouseDragged(ofMouseEventArgs & args);

	void			mousePressed(int x, int y, int button);
	void			mousePressed(ofMouseEventArgs & args);

	void			mouseReleased(int x, int y, int button);
	void			mouseReleased(ofMouseEventArgs & args);

private:

	ofxGui*			gui;
	ofxGuiObject*	obj;
	int				px, py;
};

//	----------------------------------------------------------------------------------------------------

#endif

//	----------------------------------------------------------------------------------------------------
