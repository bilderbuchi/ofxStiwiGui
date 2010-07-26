/*
 *  ofxGuiPoints.cpp
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

#include "ofxGuiPoints.h"

//	----------------------------------------------------------------------------------------------------

ofxGuiPoints::ofxGuiPoints()
{
	mParamType = kofxGui_Object_Points;
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiPoints::init(int id, string name, int x, int y, int width, int height, ofxPoint2f min, ofxPoint2f max, ofxPoint2f value, int display, int steps)
{
	int	textHeight	= (name == "") ? 0 : mGlobals->mParamFontHeight;

	mParamId		= id;
	mParamName		= name;

	mObjX			= x;
	mObjY			= y;

	mObjWidth		= width;
	mObjHeight		= textHeight + height;

	mDisplay		= display;
	mSteps			= steps;

	setRange(min, max);
	setValue(value);
	setControlRegion(0, textHeight, width, height);

	mList.points.push_back(ofxPoint2f(mMinVal.x, mMinVal.y + mValDlt.y * 0.5));
	mList.points.push_back(ofxPoint2f(mMaxVal.x, mMinVal.y + mValDlt.y * 0.5));

	float	size	= mGlobals->mPointSize / 2.0;
	float	x1		= size / mCtrWidth;
	float	y1		= size / mCtrHeight;
	float	x2		= x1 * mValDlt.x;
	float	y2		= y1 * mValDlt.y;

	mDistance		= sqrt(x2 * x2 + y2 * y2);
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiPoints::setValue(ofxPoint2f value)
{
	mValue = value;
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiPoints::setRange(ofxPoint2f min, ofxPoint2f max)
{
	mMinVal	= min;
	mMaxVal	= max;
	mValDlt	= mMaxVal / mMinVal;
}

//	----------------------------------------------------------------------------------------------------

bool ofxGuiPoints::update(int id, int task, void* data, int length)
{
	bool		handled	= false;
	ofxPoint2f	value	= mValue;

	if(id == mParamId)
	{
		if(task == kofxGui_Set_Float)
			setValue(ofxPoint2f(mMinVal.x + CLAMP(*(float*)data, 0.0, 1.0) * mValDlt.x, mValue.y));
		else if(task == kofxGui_Set_Point)
			mList.addPointAtPosition(*(ofxPoint2f*)data);


		handled = true;
	}

	if(value!= mValue)
	{
		mOutVal = bezier(mList.points, mList.points.size()-1, mList.positionToValue(mValue).x / (float) mMaxVal.x);
		mGlobals->mListener->handleGui(mParamId, kofxGui_Set_Point, &mOutVal, sizeof(ofxPoint2f));
	}

	return handled;
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiPoints::draw()
{
	glPushMatrix();

		glTranslatef(mObjX, mObjY, 0.0f);

		if(mParamName != "")
			drawParamString(0.0, 0.0, mParamName + ": " + pointToString(mList.activePoint != -1 ? mOutVal : mValue, mDisplay), false);

		ofxPoint2f	p	= fractionToLocal(valueToFraction(mValue));

		float		x	= mCtrWidth * p.x;
		float		y	= mCtrHeight * p.y;

		float		d	= mGlobals->mPointSize;
		float		r	= d / 2.0;

		ofFill();

		//	background
		glColor4f(mGlobals->mCoverColor.r, mGlobals->mCoverColor.g, mGlobals->mCoverColor.b, mGlobals->mCoverColor.a);
		ofRect(mCtrX, mCtrY, mCtrWidth, mCtrHeight);

		ofNoFill();

		//	lines
		glColor4f(mGlobals->mCurveColor.r, mGlobals->mCurveColor.g, mGlobals->mCurveColor.b, mGlobals->mCurveColor.a);
		/*
		ofBeginShape();
			for(int i = 0; i < mList.points.size(); i++)
			{
				ofxPoint2f p = fractionToLocal(valueToFraction(mList.points.at(i)));
				ofVertex(p.x, p.y);
			}
		ofEndShape(false);
		*/

			GLfloat* verts = new GLfloat[(int)mMaxVal.x*2];
			for (int i = 0; i < mMaxVal.x; i++)	{
						ofxPoint2f p = fractionToLocal(valueToFraction(bezier(mList.points, mList.points.size()-1, (float) i / (float) mMaxVal.x)));

						verts[i*2  ] = p.x;
						verts[i*2+1] = p.y;
			}

			glEnableClientState(GL_VERTEX_ARRAY);
			glVertexPointer(2, GL_FLOAT, 0, verts );
			glDrawArrays( GL_LINE_STRIP, 0, mMaxVal.x);
			glDisableClientState(GL_VERTEX_ARRAY);

		//	x-bar
		glColor4f(mGlobals->mAxisColor.r, mGlobals->mAxisColor.g, mGlobals->mAxisColor.b, mGlobals->mAxisColor.a);
		ofLine(p.x + 0.5, mCtrY, p.x + 0.5, mCtrBottom);

		if(mList.activePoint != -1)
		{
			//	y-bar
			glColor4f(mGlobals->mAxisColor.r, mGlobals->mAxisColor.g, mGlobals->mAxisColor.b,mGlobals->mAxisColor.a);
			ofLine(mCtrX, p.y + 0.5, mCtrRight, p.y + 0.5);
		}

		//	handles
		for(int i = 0; i < mList.points.size(); i++)
		{
			glColor4f(mGlobals->mHandleColor.r, mGlobals->mHandleColor.g, mGlobals->mHandleColor.b, mGlobals->mHandleColor.a);

			ofxPoint2f p	= fractionToLocal(valueToFraction(mList.points.at(i)));
			ofRect(p.x - r, p.y - r, d, d);
		}

		//	frame
		glColor4f(mGlobals->mFrameColor.r, mGlobals->mFrameColor.g, mGlobals->mFrameColor.b, mGlobals->mFrameColor.a);
		ofRect(mCtrX, mCtrY, mCtrWidth, mCtrHeight);

	glPopMatrix();
}

//	----------------------------------------------------------------------------------------------------

bool ofxGuiPoints::mouseDragged(int x, int y, int button)
{
	if(mMouseIsDown)
	{
		ofxPoint2f	value	= mValue;
		ofxPoint2f	point	= fractionToValue(mouseToFraction(mouseToLocal(x, y)));

		if(mList.activePoint > -1)
		{
			if(mList.activePoint == 0)
			{
				point.x = mMinVal.x;
				mList.points[mList.activePoint] = point;
			}
			else if(mList.activePoint == mList.points.size() - 1)
			{
				point.x = mMaxVal.x;
				mList.points[mList.activePoint] = point;
			}
			else
			{
				if(point.x < mList.points[mList.activePoint - 1].x)
					point.x = mList.points[mList.activePoint - 1].x;
				else if(point.x > mList.points[mList.activePoint + 1].x)
					point.x = mList.points[mList.activePoint + 1].x;

				mList.points[mList.activePoint] = point;
			}
		}

		setValue(point);

		if(value != mValue)
		{
			mOutVal = mList.positionToValue(point);
			mGlobals->mListener->handleGui(mParamId, kofxGui_Set_Point, &mOutVal, sizeof(ofxPoint2f));
			mGlobals->mListener->handleGui(mParamId, kofxGui_Set_PointArray, &mList.points, sizeof(vector<ofxPoint2f>));
		}
	}

	return mMouseIsDown;
}

//	----------------------------------------------------------------------------------------------------

bool ofxGuiPoints::mousePressed(int x, int y, int button)
{
	ofxPoint2f point = mouseToLocal(x, y);

	if(isPointInsideMe(point))
	{
		ofxPoint2f	inside	= fractionToValue(mouseToFraction(point));
		bool		onPoint	= isPointWithinDistance(inside);

		if(button == 2)
		{
			if(onPoint)
				mList.deleteActivePoint();
			else
				mList.addPointAtPosition(inside);
		}

		mMouseIsDown = true;
		mouseDragged(x, y, button);
	}
	else
	{
		mMouseIsDown = false;
	}

	return mMouseIsDown;
}

//	----------------------------------------------------------------------------------------------------

bool ofxGuiPoints::mouseReleased(int x, int y, int button)
{
	bool handled = mMouseIsDown;

	if(mMouseIsDown)
	{
		mMouseIsDown		= false;
		mList.activePoint	= -1;
	}

	return handled;
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiPoints::buildFromXml()
{
	int numberOfTags = mGlobals->mXml.getNumTags("POINT");

	if(numberOfTags > 0)
	{
		mList.points.clear();

		for(int i = 0; i < numberOfTags; i++)
		{
			mGlobals->mXml.pushTag("POINT", i);

			float	x = mGlobals->mXml.getValue("X", 0.0);
			float	y = mGlobals->mXml.getValue("Y", 0.0);

			mList.points.push_back(ofxPoint2f(x, y));

			mGlobals->mXml.popTag();
		}
	}

	mOutVal = mList.positionToValue(mValue);
	mGlobals->mListener->handleGui(mParamId, kofxGui_Set_Point, &mOutVal, sizeof(ofxPoint2f));
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiPoints::saveToXml()
{
	int id = saveObjectData();

	mGlobals->mXml.setValue("OBJECT:MIN_X", mMinVal.x, id);
	mGlobals->mXml.setValue("OBJECT:MIN_Y", mMinVal.y, id);
	mGlobals->mXml.setValue("OBJECT:MAX_X", mMaxVal.x, id);
	mGlobals->mXml.setValue("OBJECT:MAX_Y", mMaxVal.y, id);
	mGlobals->mXml.setValue("OBJECT:VALUE_X", mValue.x, id);
	mGlobals->mXml.setValue("OBJECT:VALUE_Y", mValue.y, id);

	mGlobals->mXml.pushTag("OBJECT", id);

	for(int i = 0; i < mList.points.size(); i++)
	{
		ofxPoint2f p	= mList.points.at(i);

		id = mGlobals->mXml.addTag("POINT");

		mGlobals->mXml.setValue("POINT:X", p.x, id);
		mGlobals->mXml.setValue("POINT:Y", p.y, id);
	}

	mGlobals->mXml.popTag();
}

//	----------------------------------------------------------------------------------------------------

ofxPoint2f ofxGuiPoints::valueToFraction(ofxPoint2f value)
{
	return ofxPoint2f((value.x - mMinVal.x) / mValDlt.x, (value.y - mMinVal.y) / mValDlt.y);
}

//	----------------------------------------------------------------------------------------------------

ofxPoint2f ofxGuiPoints::fractionToValue(ofxPoint2f fraction)
{
	return ofxPoint2f((mValDlt.x * fraction.x) + mMinVal.x, (mValDlt.y * fraction.y) + mMinVal.y);
}

ofxPoint2f ofxGuiPoints::bezier(vector<ofxPoint2f> p,int n,float mu)
{
  int k,kn,nn,nkn;
  float blend,muk,munk;
  ofxPoint2f b(0,0);

  muk = 1;
  munk = pow(1-mu,(float)n);

  for (k=0;k<=n;k++) {
    nn = n;
    kn = k;
    nkn = n - k;
    blend = muk * munk;
    muk *= mu;
    munk /= (1-mu);
    while (nn >= 1) {
      blend *= nn;
      nn--;
      if (kn > 1) {
        blend /= (float)kn;
        kn--;
      }
      if (nkn > 1) {
        blend /= (float)nkn;
        nkn--;
      }
    }

    b.x += p[k].x * blend;
    b.y += p[k].y * blend;
  }

  return(b);
}

//	----------------------------------------------------------------------------------------------------

bool ofxGuiPoints::isPointWithinDistance(ofxPoint2f position)
{
	mList.activePoint = -1;

	for(int i = 0; i < mList.points.size(); i++)
	{
		ofxPoint2f	point	= mList.points.at(i);
		float		delta	= point.distance(position);

		if(delta < mDistance)
		{
			mList.activePoint = i;
			break;
		}
	}

	return mList.activePoint != -1;
}
