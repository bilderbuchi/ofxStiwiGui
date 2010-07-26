/*
 *  ofxGuiObject.cpp
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

#include "ofxGuiObject.h"

//	----------------------------------------------------------------------------------------------------

ofxGuiObject::ofxGuiObject()
{
	mParamId		= -1;
	mParamType		= kofxGui_Object_Base;
	mParamName		= "";
	
	mObjX			= 0; 
	mObjY			= 0;
	mObjWidth		= 0; 
	mObjHeight		= 0;
	
	mMode			= 0;
	mDisplay		= kofxGui_Display_Float2;
	mSteps			= 0;
	
	mMouseIsDown	= false;
		
	mGlobals		= ofxGuiGlobals::Instance();
	
	setControlRegion(0, 0, 0, 0);
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiObject::drawHeadString(float x, float y, string text, bool center)
{
	glColor4f(mGlobals->mTextColor.r, mGlobals->mTextColor.g, mGlobals->mTextColor.b, mGlobals->mTextColor.a);

	if(center)
		x -= roundInt(mGlobals->mHeadFont.stringWidth(text) / 2.0f);
	else
		x += mGlobals->mHeadFontXOffset;
	
	y += mGlobals->mHeadFontYOffset;
	
	mGlobals->mHeadFont.drawString(text, x, y);
	//ofDrawBitmapString(text, x, y);
	
	//	debug rect to position font
	/*
	ofRectangle rect = uiGlobals->headFont.getStringBoundingBox(text, x, y);
	ofNoFill();
	glColor4f(1.0, 0.0, 0.0, 1.0);
	ofRect(x, y, rect.width, OFXGUI_HEAD_HEIGHT);
	*/
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiObject::drawParamString(float x, float y, string text, bool center)
{
	glColor4f(mGlobals->mTextColor.r, mGlobals->mTextColor.g, mGlobals->mTextColor.b, mGlobals->mTextColor.a);

	if(center)
		x -= roundInt(mGlobals->mParamFont.stringWidth(text) / 2.0f);
	else
		x += mGlobals->mParamFontXOffset;
		
	y += mGlobals->mParamFontYOffset;
	mGlobals->mParamFont.drawString(text, x, y);
	//ofDrawBitmapString(text, x, y);
	
	//	debug rect to position font
	/*
	ofRectangle rect = mGlobals->mParamFont.getStringBoundingBox(text, x, y);
	ofNoFill();
	glColor4f(1.0, 0.0, 0.0, 1.0);
	ofRect(x, y, rect.width, mGlobals->mParamFontHeight);
	*/
}

//	----------------------------------------------------------------------------------------------------

string ofxGuiObject::floatToString(float value, int display)
{
	string stringValue = "";
	
	switch(display)
	{
		case kofxGui_Display_Int:
			stringValue = ofToString((int)value, 0);
			break;
			
		case kofxGui_Display_Hex:
			char hex[64];
			sprintf(hex, "%X", (int)value);
			stringValue = hex;
			break;
			
		case kofxGui_Display_Float2:
			stringValue = ofToString(value, 2);	
			break;
			
		case kofxGui_Display_Float4:
			stringValue = ofToString(value, 4);
			break;
			
		default:
			stringValue = ofToString(value);
			break;
	}

	return stringValue;
}

//	----------------------------------------------------------------------------------------------------

string ofxGuiObject::pointToString(ofxPoint2f value, int display)
{
	return floatToString(value.x, display) + " " + floatToString(value.y, display);	
}

//	----------------------------------------------------------------------------------------------------

string ofxGuiObject::rgbaToString(ofRGBA value, int display)
{
	return value.toString(display);	
}

//	----------------------------------------------------------------------------------------------------

bool ofxGuiObject::isPointInsideMe(int x, int y) 
{	
	return (x >= mCtrX && x <= mCtrRight && y >= mCtrY && y <= mCtrBottom);
}

//	----------------------------------------------------------------------------------------------------

bool ofxGuiObject::isPointInsideMe(ofxPoint2f p) 
{	
	return (p.x >= mCtrX && p.x <= mCtrRight && p.y >= mCtrY && p.y <= mCtrBottom);
}

//	----------------------------------------------------------------------------------------------------

ofxPoint2f ofxGuiObject::mouseToLocal(int x, int y)
{
	return ofxPoint2f((float)(x - mObjX), (float)(y - mObjY));
}

//	----------------------------------------------------------------------------------------------------

ofxPoint2f ofxGuiObject::mouseToFraction(ofxPoint2f p)
{
	p.x = CLAMP(p.x, mCtrX, mCtrRight);
	p.y = CLAMP(p.y, mCtrY, mCtrBottom);
	
	p.x = (p.x - mCtrX) / mCtrWidth;
	p.y = (p.y - mCtrY) / mCtrHeight;
	
	return p;
}

//	----------------------------------------------------------------------------------------------------

ofxPoint2f ofxGuiObject::fractionToLocal(ofxPoint2f p)
{
	return ofxPoint2f(mCtrX + mCtrWidth * p.x, mCtrY + mCtrHeight * p.y);
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiObject::setControlRegion(int x, int y, int width, int height)
{
	mCtrX	= x;
	mCtrY	= y;
	mCtrWidth	= width;
	mCtrHeight	= height;
	mCtrRight	= mCtrX + mCtrWidth; 
	mCtrBottom	= mCtrY + mCtrHeight;
}

//	----------------------------------------------------------------------------------------------------

int ofxGuiObject::saveObjectData()
{
	int id	= mGlobals->mXml.addTag("OBJECT");
	
	mGlobals->mXml.setValue("OBJECT:ID", mParamId, id);
	mGlobals->mXml.setValue("OBJECT:TYPE", getTagName(), id);
	mGlobals->mXml.setValue("OBJECT:NAME", mParamName, id);

	mGlobals->mXml.setValue("OBJECT:LEFT", mObjX, id);
	mGlobals->mXml.setValue("OBJECT:TOP", mObjY, id);
	//	mGlobals->mXml.setValue("OBJECT:WIDTH", mObjWidth, id);
	//	mGlobals->mXml.setValue("OBJECT:HEIGHT", mObjHeight, id);
	
	//	mGlobals->mXml.setValue("OBJECT:CTRX", mCtrX, id);
	//	mGlobals->mXml.setValue("OBJECT:CTRY", mCtrY, id);
	
	mGlobals->mXml.setValue("OBJECT:WIDTH", mCtrWidth, id);
	mGlobals->mXml.setValue("OBJECT:HEIGHT", mCtrHeight, id);
	
	mGlobals->mXml.setValue("OBJECT:MODE", mMode, id);
	mGlobals->mXml.setValue("OBJECT:DISPLAY", mDisplay, id);
	mGlobals->mXml.setValue("OBJECT:STEPS", mSteps, id);
	
	return id;
}

//	----------------------------------------------------------------------------------------------------

string ofxGuiObject::getTagName()
{
	return kofxGui_Tags[mParamType];
}

//	----------------------------------------------------------------------------------------------------
