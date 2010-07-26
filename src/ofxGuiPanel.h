/*
 *  ofxGuiPanel.h
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

#ifndef OFX_GUI_PANEL
#define OFX_GUI_PANEL

//	----------------------------------------------------------------------------------------------------

#include "ofxGuiObject.h"
#include "ofxGuiGlobals.h"
#include "ofxGuiSlider.h"
#include "ofxGuiXYPad.h"
#include "ofxGuiPoints.h"
#include "ofxGuiButton.h"
#include "ofxGuiFiles.h"
#include "ofxGuiColor.h"
#include "ofxGuiMatrix.h"
#include "ofxGuiScope.h"
#include "ofxGuiKnob.h"
#include "ofxGuiRadar.h"
#include "ofxGuiSwitch.h"

//	----------------------------------------------------------------------------------------------------

class ofxGuiPanel : public ofxGuiObject
{

public:

	ofxGuiPanel();

	void			init(int id, string name, int x, int y, int border, int spacing);

	bool			update(int parameterId, int task, void* data, int length);
	void			draw();

	bool			mouseDragged(int x, int y, int button);
	bool			mousePressed(int x, int y, int button);
	bool			mouseReleased(int x, int y, int button);
	
	ofxGuiSlider*	addSlider(int id, string name, int width, int height, float min, float max, float value, int display, int steps);
	ofxGuiXYPad*	addXYPad(int id, string name, int width, int height, ofxPoint2f min, ofxPoint2f max, ofxPoint2f value, int display, int steps);
	ofxGuiPoints*	addPoints(int id, string name, int width, int height, ofxPoint2f min, ofxPoint2f max, ofxPoint2f value, int display, int steps);
	ofxGuiButton*	addButton(int id, string name, int width, int height, bool value, int mode, string image);
	ofxGuiFiles*	addFiles(int id, string name, int width, int height, string value, string subPath, string suffix);
	ofxGuiColor*	addColor(int id, string name, int width, int height, ofRGBA value, int mode);
	ofxGuiMatrix*	addMatrix(int id, string name, int width, int height, int xGrid, int yGrid, int value, int mode, int spacing);
	ofxGuiScope*	addScope(int id, string name, int width, int height, int length, ofxPoint2f value, int mode);
	ofxGuiKnob*	addKnob(int id, string name, int width, int height, float min, float max, float value, int display, int steps);
	ofxGuiRadar*	addRadar(int id, string name, int width, int height, float min, float max, float value, int display, int steps);
	ofxGuiSwitch*	addSwitch(int id, string name, int width, int height,  int min, int max, int value, const string* paramStrings);	
	
	void			adjustToNewContent(int w, int h);

	void			buildFromXml();
	void			saveToXml();

	int				mBorder, mSpacing;
	
	vector			<ofxGuiObject*> mObjects;
};

//	----------------------------------------------------------------------------------------------------

#endif

//	----------------------------------------------------------------------------------------------------
