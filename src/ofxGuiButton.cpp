/*
 *  ofxGuiButton.cpp
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

#include "ofxGuiButton.h"

//	----------------------------------------------------------------------------------------------------

ofxGuiButton::ofxGuiButton()
{
	mParamType = kofxGui_Object_Button;
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiButton::init(int id, string name, int x, int y, int width, int height, bool value, int mode, string image = "")
{
	int	textWidth	= (name == "") ? 0 : mGlobals->mButtonXText + roundInt(mGlobals->mHeadFont.stringWidth(name));

	mParamId		= id;
	mParamName		= name;

	mObjX			= x;
	mObjY			= y;

	mObjWidth		= textWidth + width;
	mObjHeight		= height;

	mMode			= mode;

	setValue(value);
	setControlRegion(0, 0, width, height);

	if(image != "") logo.loadImage(image);
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiButton::setValue(bool value)
{
	mValue = value;
}

//	----------------------------------------------------------------------------------------------------

bool ofxGuiButton::update(int id, int task, void* data, int length)
{
	bool handled = false;

	if(id == mParamId && length == sizeof(bool))
	{
		setValue(*(bool*)data);
		handled = true;
	}

	return handled;
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiButton::draw()
{
	glPushMatrix();

		glTranslatef(mObjX, mObjY, 0.0f);

		if(mParamName != "")
			drawParamString(mCtrWidth + mGlobals->mButtonXText, mGlobals->mButtonYText, mParamName, false);

		ofFill();

		//	background
		glColor4f(mGlobals->mCoverColor.r, mGlobals->mCoverColor.g, mGlobals->mCoverColor.b, mGlobals->mCoverColor.a);
		ofRect(mCtrX, mCtrY, mCtrWidth, mCtrHeight);

		logo.draw(0,0, mCtrWidth, mCtrHeight);

		if(mValue == 1)
		{
			//	handle
			glColor4f(mGlobals->mButtonColor.r, mGlobals->mButtonColor.g, mGlobals->mButtonColor.b, mGlobals->mButtonColor.a);
			ofRect(mCtrX , mCtrY, mCtrWidth, mCtrHeight);
		}

		ofNoFill();

		//	frame
		glColor4f(mGlobals->mFrameColor.r, mGlobals->mFrameColor.g, mGlobals->mFrameColor.b, mGlobals->mFrameColor.a);
		ofRect(mCtrX, mCtrY, mCtrWidth, mCtrHeight);

	glPopMatrix();
}

//	----------------------------------------------------------------------------------------------------

bool ofxGuiButton::mouseDragged(int x, int y, int button)
{
	return mMouseIsDown;
}

//	----------------------------------------------------------------------------------------------------

bool ofxGuiButton::mousePressed(int x, int y, int button)
{
	mMouseIsDown = isPointInsideMe(mouseToLocal(x, y));

	if(mMouseIsDown)
	{
		if(mMode == kofxGui_Button_Trigger)
			setValue(true);
		else
			setValue(!mValue);

		mGlobals->mListener->handleGui(mParamId, kofxGui_Set_Bool, &mValue, sizeof(bool));
	}

	return mMouseIsDown;
}

//	----------------------------------------------------------------------------------------------------

bool ofxGuiButton::mouseReleased(int x, int y, int button)
{
	bool handled = mMouseIsDown;

	if(mMouseIsDown)
	{
		if(mMode == kofxGui_Button_Trigger)
		{
			setValue(false);
			mGlobals->mListener->handleGui(mParamId, kofxGui_Set_Bool, &mValue, sizeof(bool));
		}

		mMouseIsDown = false;
	}

	return handled;
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiButton::buildFromXml()
{
	mGlobals->mListener->handleGui(mParamId, kofxGui_Set_Bool, &mValue, sizeof(bool));
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiButton::saveToXml()
{
	int		id		= saveObjectData();
	bool	value	= (mMode == kofxGui_Button_Trigger) ? false : mValue;

	mGlobals->mXml.setValue("OBJECT:VALUE", value, id);
}

//	----------------------------------------------------------------------------------------------------
