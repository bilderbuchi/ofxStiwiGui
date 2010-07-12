/*  ofxGui.h
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
