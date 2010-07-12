/*
 *  ofxGuiColor.cpp
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

#include "ofxGuiColor.h"

//	----------------------------------------------------------------------------------------------------

ofxGuiColor::ofxGuiColor()
{
	mParamType = kofxGui_Object_Color;
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiColor::init(int id, string name, int x, int y, int width, int height, ofRGBA value, int mode)
{
	int	textHeight	= (name == "") ? 0 : mGlobals->mParamFontHeight;
	
	mParamId		= id;
	mParamName		= name;
	
	mObjX			= x; 
	mObjY			= y;
	
	mObjWidth		= width;
	mObjHeight		= textHeight + height;
	
	mMode			= mode;
	
	mSize			= (mode == kofxGui_Color_RGB ? 3 : 4);

	setValue(value);
	setControlRegion(0, textHeight, width, height);
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiColor::setValue(ofRGBA value)
{
	mValue = value;
}

//	----------------------------------------------------------------------------------------------------

bool ofxGuiColor::update(int id, int task, void* data, int length)
{
	bool handled = false;
	
	if(id == mParamId && length == sizeof(ofRGBA))
	{
		setValue(*(ofRGBA*)data);
		handled = true;
	}
	
	return handled;
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiColor::draw()
{
	glPushMatrix();
	
	glTranslatef(mObjX, mObjY, 0.0f);

	//	color
	glColor4f(1, 1, 1, 1);
	ofRect(mCtrX, mCtrY-17, mCtrWidth, 17);

	ofFill();
	
	glColor4f(0, 0, 0, 1);
	ofRect(mCtrX+1, mCtrY-16, mCtrWidth-2, 16);

	glColor4f(mValue.r, mValue.g, mValue.b, mValue.a);
	ofRect(mCtrX, mCtrY-16, mCtrWidth-1, 16);
	
	if(mParamName != ""){
		if((mValue.a) < 0.4){
			glColor4f(1, 1, 1, 1);
			mGlobals->mParamFont.drawString(mParamName + ": " + rgbaToString(mValue, mMode), 2+mGlobals->mParamFontXOffset, mGlobals->mParamFontYOffset);
		}
		else if((mValue.r+mValue.g+mValue.b+mValue.a) > 3.0){
			glColor4f(0, 0, 0, 1);
			mGlobals->mParamFont.drawString(mParamName + ": " + rgbaToString(mValue, mMode), 2+mGlobals->mParamFontXOffset, mGlobals->mParamFontYOffset);
		}
		else drawParamString(2.0, 0.0, mParamName + ": " + rgbaToString(mValue, mMode), false);
	}
	glColor4f(1, 1, 1, 1);
		

	
	//	background
	glColor4f(mGlobals->mCoverColor.r, mGlobals->mCoverColor.g, mGlobals->mCoverColor.b, mGlobals->mCoverColor.a);
	ofRect(mCtrX, mCtrY, mCtrWidth, mCtrHeight);

	

	float	height	= (mCtrHeight - 2.0 - mSize) / (float)mSize;
	float	posY	= mCtrY + 2.0;
	float	posX	= mCtrWidth * mValue.r;
	
	//	r
	glColor4f(1.0, 0.0, 0.0, 0.8);
	ofRect(mCtrX, posY, posX, height);
	glColor4f(mGlobals->mHandleColor.r, mGlobals->mHandleColor.g, mGlobals->mHandleColor.b, mGlobals->mHandleColor.a);
	ofRect(posX, posY, 1.0, height);
	
	posY	+= 1.0 + height;
	posX	 = mCtrWidth * mValue.g;
	
	//	g
	glColor4f(0.0, 1.0, 0.0, 0.8);
	ofRect(mCtrX, posY, posX, height);
	glColor4f(mGlobals->mHandleColor.r, mGlobals->mHandleColor.g, mGlobals->mHandleColor.b, mGlobals->mHandleColor.a);
	ofRect(posX, posY, 1.0, height);

	posY	+= 1.0 + height;
	posX	 = mCtrWidth * mValue.b;

	//	b
	glColor4f(0.0, 0.0, 1.0, 0.8);
	ofRect(mCtrX, posY, posX, height);
	glColor4f(mGlobals->mHandleColor.r, mGlobals->mHandleColor.g, mGlobals->mHandleColor.b, mGlobals->mHandleColor.a);
	ofRect(posX, posY, 1.0, height);
	
	if(mMode == kofxGui_Color_RGBA)
	{
		posY	+= 1.0 + height;
		posX	 = mCtrWidth * mValue.a;

		//	a
		glColor4f(1.0, 1.0, 1.0, 0.4);
		ofRect(mCtrX, posY, posX, height);
		glColor4f(mGlobals->mHandleColor.r, mGlobals->mHandleColor.g, mGlobals->mHandleColor.b, mGlobals->mHandleColor.a);
		ofRect(posX, posY, 1.0, height);
	}
	
	ofNoFill();
	
	//	frame
	glColor4f(mGlobals->mFrameColor.r, mGlobals->mFrameColor.g, mGlobals->mFrameColor.b, mGlobals->mFrameColor.a);
	ofRect(mCtrX, mCtrY, mCtrWidth, mCtrHeight);
	
	glPopMatrix();
}

//	----------------------------------------------------------------------------------------------------

bool ofxGuiColor::mouseDragged(int x, int y, int button)
{
	if(mMouseIsDown)
	{
		//	int value = mValue.toInt(mDisplay);
		mValue.setChanel(mSlider, mouseToFraction(mouseToLocal(x, y)).x);
		
		//	if(mValue.toInt(mDisplay) != value)
			mGlobals->mListener->handleGui(mParamId, kofxGui_Set_Color, &mValue, sizeof(ofRGBA));
	}
	
	return mMouseIsDown;
}

//	----------------------------------------------------------------------------------------------------

bool ofxGuiColor::mousePressed(int x, int y, int button)
{
	ofxPoint2f inside = mouseToLocal(x, y);
	mMouseIsDown = isPointInsideMe(inside);
	
	if(mMouseIsDown)
	{
		mSlider = mouseToSlider(mouseToFraction(inside).y);
		mouseDragged(x, y, button);
	}
	
	return mMouseIsDown;
}

//	----------------------------------------------------------------------------------------------------

bool ofxGuiColor::mouseReleased(int x, int y, int button)
{
	bool handled = mMouseIsDown;
	
	if(mMouseIsDown)
		mMouseIsDown = false;
	
	return handled;
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiColor::buildFromXml()
{
	mGlobals->mListener->handleGui(mParamId, kofxGui_Set_Color, &mValue, sizeof(ofRGBA));
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiColor::saveToXml()
{
	int id = saveObjectData();
	
	mGlobals->mXml.setValue("OBJECT:VALUE", rgbaToString(mValue, kofxGui_Color_RGBA), id);
}

//	----------------------------------------------------------------------------------------------------

int ofxGuiColor::mouseToSlider(float y)
{
	float position = (int)(y * mSize);
	
	return CLAMP(position, 0, mSize);
}

//	----------------------------------------------------------------------------------------------------
