/*
 *  ofxGuiGlobals.h
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

#ifndef OFX_GUI_GLOBALS
#define OFX_GUI_GLOBALS

//	----------------------------------------------------------------------------------------------------

#include "ofxGuiTypes.h"

//	----------------------------------------------------------------------------------------------------

class ofxGuiGlobals
{
		
public:
	
	static			ofxGuiGlobals* Instance();
	
	void			buildFromXml();
	void			saveToXml();

	void			loadFonts();
	
	ofxGuiListener*	mListener;

	ofTrueTypeFont	mHeadFont;
	ofTrueTypeFont	mParamFont;
	
	ofxXmlSettings	mXml;
	ofxDirList		mDir;

	string			mXmlfile;
	
	string			mHeadFontName;
	int				mHeadFontSize;
	int				mHeadFontXOffset;
	int				mHeadFontYOffset;
	int				mHeadFontHeight;
	
	string			mParamFontName;
	int				mParamFontSize;
	int				mParamFontXOffset;
	int				mParamFontYOffset;
	int				mParamFontHeight;

	int				mButtonXText;
	int				mButtonYText;
	
	int				mFilesXText;
	int				mFilesYText;
	
	int				mPointSize;
	
	int				mKnobSize;
	
	ofRGBA			mCoverColor, mTextColor, mBorderColor, mFrameColor, mSliderColor, mAxisColor, mHandleColor, mButtonColor, mCurveColor, mScopeColor, mMatrixColor;

private:
	
	ofxGuiGlobals();	
};

//	----------------------------------------------------------------------------------------------------

#endif

//	----------------------------------------------------------------------------------------------------
