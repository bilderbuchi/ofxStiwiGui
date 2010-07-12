/*
 *  ofxGuiButton.h
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

#ifndef OFX_GUI_BUTTON
#define OFX_GUI_BUTTON

//	----------------------------------------------------------------------------------------------------

#include "ofxGuiTypes.h"
#include "ofxGuiObject.h"

//	----------------------------------------------------------------------------------------------------

class ofxGuiButton : public ofxGuiObject
{
		
public:
	
	ofxGuiButton();
	
	void	init(int id, string name, int x, int y, int width, int height, bool value, int mode, string image);
	
	void	setValue(bool value);

	bool	update(int id, int task, void* data, int length);
	void	draw();
	
	bool	mouseDragged(int x, int y, int button);
	bool	mousePressed(int x, int y, int button);
	bool	mouseReleased(int x, int y, int button);
	
	void	buildFromXml();
	void	saveToXml();
	
	bool	mValue;

	ofImage	logo;
};

//	----------------------------------------------------------------------------------------------------

#endif

//	----------------------------------------------------------------------------------------------------
