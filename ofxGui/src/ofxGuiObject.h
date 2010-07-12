/*
 *  ofxGuiObject.h
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

#ifndef OFX_GUI_OBJECT
#define OFX_GUI_OBJECT

//	----------------------------------------------------------------------------------------------------

#include "ofxGuiTypes.h"
#include "ofxGuiGlobals.h"

//	----------------------------------------------------------------------------------------------------

class ofxGuiObject
{
	
public:

	ofxGuiObject();
	
	virtual	bool	update(int parameterId, int task, void* data, int length){return false;}
	virtual	void	draw(){}

	virtual bool	mouseDragged(int x, int y, int button){return false;}
	virtual bool	mousePressed(int x, int y, int button){return false;}
	virtual bool	mouseReleased(int x, int y, int button){return false;}

	virtual	void	buildFromXml(){}
	virtual	void	saveToXml(){}
	
	void			drawHeadString(float x, float y, string text, bool center);
	void			drawParamString(float x, float y, string text, bool center);
	
	string			floatToString(float value, int display);
	string			pointToString(ofxPoint2f value, int display);
	string			rgbaToString(ofRGBA value, int display);
	
	bool			isPointInsideMe(int x, int y);
	bool			isPointInsideMe(ofxPoint2f point);
	
	ofxPoint2f		mouseToLocal(int x, int y);
	ofxPoint2f		mouseToFraction(ofxPoint2f mouse);
	ofxPoint2f		fractionToLocal(ofxPoint2f fraction);
	
	void			setControlRegion(int x, int y, int width, int height);
	
	int				saveObjectData();
	string			getTagName();
	
	int				mParamId, mParamType, mMode, mDisplay, mSteps;
	string			mParamName, mDisplaySting;

	float			mObjX, mObjY, mObjWidth, mObjHeight;
	float			mCtrX, mCtrY, mCtrWidth, mCtrHeight, mCtrRight, mCtrBottom;
		
	bool			mMouseIsDown;
	
	ofxGuiGlobals*	mGlobals;
};

//	----------------------------------------------------------------------------------------------------

#endif

//	----------------------------------------------------------------------------------------------------
