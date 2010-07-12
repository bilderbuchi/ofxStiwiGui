/*
 *  ofxGuiScope.cpp
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

#include "ofxGuiScope.h"

//	----------------------------------------------------------------------------------------------------

ofxGuiScope::ofxGuiScope()
{
	mParamType		= kofxGui_Object_Scope;
	mBuffer			= NULL;
	mBufferLength	= 0;
}

//	----------------------------------------------------------------------------------------------------

ofxGuiScope::~ofxGuiScope()
{
	if(mBuffer)
		delete[] mBuffer;
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiScope::init(int id, string name, int x, int y, int width, int height, int length, ofxPoint2f value, int mode)
{
	int	textHeight	= (name == "") ? 0 : mGlobals->mParamFontHeight;
	
	mParamId		= id;
	mParamName		= name;
	
	mObjX			= x; 
	mObjY			= y;
	
	mObjWidth		= width;
	mObjHeight		= textHeight + height;
		
	mMode			= mode;
	
	setValue(value);
	setControlRegion(0, textHeight, width, height);

	if(mBuffer)
		delete[] mBuffer;
	
	mBufferLength	= length;
	mBuffer			= new float[mBufferLength];
	
	memset(mBuffer, 0, sizeof(float) * mBufferLength);

	mGlobals->mListener->handleGui(mParamId, kofxGui_Set_FloatArray, mBuffer, mBufferLength);
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiScope::setValue(ofxPoint2f value)
{
	//	todo:	steps
	
	mValue = value;
}

//	----------------------------------------------------------------------------------------------------

bool ofxGuiScope::update(int id, int task, void* data, int length)
{
	bool handled = false;
	
	if(id == mParamId)
	{
		if(task == kofxGui_Set_Float)
			setValue(ofxPoint2f(CLAMP(*(float*)data, 0.0, 1.0) * mBufferLength, mValue.y));
		else if(task == kofxGui_Set_Point)
			setValue(*(ofxPoint2f*)data);
		else if(task == kofxGui_Set_FloatArray){
			float* values = (float*)data;
			for(int i=0; i<mBufferLength; i++)
				mBuffer[i] = values[i];
		}
		
		handled = true;
	}
	
	return handled;
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiScope::draw()
{
	glPushMatrix();
	
	glTranslatef(mObjX, mObjY, 0.0);
	
	if(mParamName != "")
		drawParamString(0.0, 0.0, mParamName + 
						": sample " + floatToString(mValue.x, kofxGui_Display_Int) + 
						" value " + floatToString(mValue.y, kofxGui_Display_Float4), false);
	
	ofFill();
	
	//	background
	glColor4f(mGlobals->mCoverColor.r, mGlobals->mCoverColor.g, mGlobals->mCoverColor.b, mGlobals->mCoverColor.a);
	ofRect(mCtrX, mCtrY, mCtrWidth, mCtrHeight);
	
	if(mMouseIsDown)
	{
		ofxPoint2f p = fractionToLocal(valueToFraction(mValue));

		//	x-bar
		glColor4f(mGlobals->mAxisColor.r, mGlobals->mAxisColor.g, mGlobals->mAxisColor.b, mGlobals-> mAxisColor.a);
		ofLine(p.x + 0.5, mCtrY, p.x + 0.5, mCtrBottom);
		
		//	y-bar
		glColor4f(mGlobals->mAxisColor.r, mGlobals->mAxisColor.g, mGlobals->mAxisColor.b, mGlobals->mAxisColor.a);
		ofLine(mCtrX, p.y + 0.5, mCtrRight, p.y + 0.5);
	}
	
	ofNoFill();

	if(mBuffer && mBufferLength > 0)
	{
		//	scope
		glColor4f(mGlobals->mScopeColor.r, mGlobals->mScopeColor.g, mGlobals->mScopeColor.b, mGlobals->mScopeColor.a);
		
		float stretch		= mCtrWidth / (float)(mBufferLength - 1);
		float zeroOffset	= mCtrHeight / 2.0;
		
		glPushMatrix();	
			glTranslatef(mCtrX, mCtrY + zeroOffset, 0.0);
			/*ofBeginShape();
			
				for (int i = 0; i < mBufferLength - 1; i++)
				{
					ofVertex(i * stretch, mBuffer[i] * zeroOffset);
					ofVertex((i + 1) * stretch, mBuffer[i + 1] * zeroOffset);
				}
			
			ofEndShape(false);*/
			GLfloat* verts = new GLfloat[mBufferLength*2];
			for (int i = 0; i < mBufferLength; i++)	{
						verts[i*2  ] = GLfloat(i * stretch);
						verts[i*2+1] = GLfloat((CLAMP(mBuffer[i],-1, 1)) * zeroOffset);
			}

			glEnableClientState(GL_VERTEX_ARRAY);
			glVertexPointer(2, GL_FLOAT, 0, verts );
			glDrawArrays( GL_LINE_STRIP, 0, mBufferLength);
			glDisableClientState(GL_VERTEX_ARRAY);

			delete []verts;
			
		glPopMatrix();
	}
	
	//	frame
	glColor4f(mGlobals->mFrameColor.r, mGlobals->mFrameColor.g, mGlobals->mFrameColor.b, mGlobals->mFrameColor.a);
	ofRect(mCtrX, mCtrY, mCtrWidth, mCtrHeight);
	
	glPopMatrix();
}

//	----------------------------------------------------------------------------------------------------

bool ofxGuiScope::mouseDragged(int x, int y, int button)
{
	if(mMouseIsDown)
	{
		ofxPoint2f value = fractionToValue(mouseToFraction(mouseToLocal(x, y)));
		
		if(value != mValue)
		{
			setValue(value);
			mGlobals->mListener->handleGui(mParamId, kofxGui_Set_Point, &mValue, sizeof(ofxPoint2f));
			//mGlobals->mListener->handleGui(mParamId, kofxGui_Set_PointArray, &mBuffer, sizeof(float*));
		}
	}

	return mMouseIsDown;
}

//	----------------------------------------------------------------------------------------------------

bool ofxGuiScope::mousePressed(int x, int y, int button)
{
	mMouseIsDown = isPointInsideMe(mouseToLocal(x, y));
		
	if(mMouseIsDown)
		mouseDragged(x, y, button);

	return mMouseIsDown;
}

//	----------------------------------------------------------------------------------------------------

bool ofxGuiScope::mouseReleased(int x, int y, int button)
{
	bool handled = mMouseIsDown;
	
	if(mMouseIsDown)
		mMouseIsDown = false;
	
	return handled;
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiScope::buildFromXml()
{
	//	load sampledata embeded within xml?

	mGlobals->mListener->handleGui(mParamId, kofxGui_Set_Point, &mValue, sizeof(ofxPoint2f));
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiScope::saveToXml()
{
	int id = saveObjectData();

	mGlobals->mXml.setValue("OBJECT:LENGTH", mBufferLength, id);
	mGlobals->mXml.setValue("OBJECT:VALUE_X", mValue.x, id);
	mGlobals->mXml.setValue("OBJECT:VALUE_Y", mValue.y, id);
}

//	----------------------------------------------------------------------------------------------------

ofxPoint2f ofxGuiScope::valueToFraction(ofxPoint2f value)
{
	return ofxPoint2f(value.x / mBufferLength, value.y);
}

//	----------------------------------------------------------------------------------------------------

ofxPoint2f ofxGuiScope::fractionToValue(ofxPoint2f fraction)
{
	return ofxPoint2f(fraction.x * mBufferLength, fraction.y);
}

//	----------------------------------------------------------------------------------------------------

