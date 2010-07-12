/*
 *  ofxGui.h
 *  openFrameworks
 *
 *  Created by Stefan Kirch on 18.06.08.
 *  Copyright 2008 alphakanal. All rights reserved.
 *
 */

//	----------------------------------------------------------------------------------------------------

#ifndef OFX_GUI
#define OFX_GUI

//	----------------------------------------------------------------------------------------------------

#include "ofEvents.h"
#include "ofxGuiTypes.h"
#include "ofxGuiPanel.h"
#include "ofxGuiObject.h"
#include "ofxGuiGlobals.h"

//	----------------------------------------------------------------------------------------------------

class ofxGui{
	
public:
	
	static			ofxGui* Instance(ofxGuiListener* listener);
	
	void			update(int parameterId, int type, void* data, int length);
	void			draw();
	void			draw(ofEventArgs & args);
	
	void			activate(bool activate);
	void			forceUpdate(bool update);
	
	void			keyPressed(int key);
	void			keyPressed(ofKeyEventArgs & args);

	void			keyReleased(int key);
	void			keyReleased(ofKeyEventArgs & args);

	void			mouseDragged(int x, int y, int button);
	void			mouseDragged(ofMouseEventArgs & args);

	void			mousePressed(int x, int y, int button);
	void			mousePressed(ofMouseEventArgs & args);

	void			mouseReleased(int x, int y, int button);
	void			mouseReleased(ofMouseEventArgs & args);

	ofxGuiPanel*	addPanel(int id, string name, int x, int y, int border, int spacing);

	bool			buildFromXml(string file);
	void			saveToXml(string file);

	bool			mIsActive, mDoUpdate, mXmlDone;	
	
	ofxGuiGlobals*	mGlobals;
	vector			<ofxGuiObject*>	mObjects;

private:
	
	ofxGui(ofxGuiListener* listener);
};

//	----------------------------------------------------------------------------------------------------

#endif

//	----------------------------------------------------------------------------------------------------
