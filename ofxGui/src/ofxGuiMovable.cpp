/*  ofxGuiMovable.cpp
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

#include "ofxGuiMovable.h"


ofxGuiMovable::ofxGuiMovable(ofxGui* _gui){
	ofAddListener(ofEvents.mouseDragged, this, &ofxGuiMovable::mouseDragged);
	ofAddListener(ofEvents.mouseReleased, this, &ofxGuiMovable::mouseReleased);
	ofAddListener(ofEvents.mousePressed, this, &ofxGuiMovable::mousePressed);
	gui = _gui;
	obj = NULL;
}
ofxGuiMovable::~ofxGuiMovable(){
	ofRemoveListener(ofEvents.mouseDragged, this, &ofxGuiMovable::mouseDragged);
	ofRemoveListener(ofEvents.mouseReleased, this, &ofxGuiMovable::mouseReleased);
	ofRemoveListener(ofEvents.mousePressed, this, &ofxGuiMovable::mousePressed);
}
void ofxGuiMovable::mouseDragged(int x, int y, int button){
	if(obj!=NULL){
		ofxGuiPanel* p = (ofxGuiPanel*) obj;
		p->mObjX += (x-px);
		p->mObjY += (y-py);
	}
	px = x;
	py = y;
}

void ofxGuiMovable::mouseDragged(ofMouseEventArgs & args){
	mouseDragged(args.x, args.y, args.button);
}
//	----------------------------------------------------------------------------------------------------

void ofxGuiMovable::mousePressed(int x, int y, int button){
	obj = NULL;
	for(int i=0; i<gui->mObjects.size(); i++){
		if(gui->mObjects[i]->isPointInsideMe(gui->mObjects[i]->mouseToLocal(x, y))){
			if(gui->mObjects[i]->getTagName() == "PANEL"){
				ofxGuiPanel* panel = (ofxGuiPanel*) gui->mObjects[i];
				ofxVec2f m = panel->mouseToLocal(x, y);

				bool over = false;
				for(int j=0; j<panel->mObjects.size(); j++){
					if(panel->mObjects[j]->isPointInsideMe(panel->mObjects[j]->mouseToLocal(m.x, m.y))){
						over = true;
					}
				}
				over = panel->isPointInsideMe(m.x, m.y) && !over;
				if(over){
					obj = panel;
					break;
				}
			}
		}
	}
	px = x;
	py = y;
}

void ofxGuiMovable::mousePressed(ofMouseEventArgs & args){
	mousePressed(args.x, args.y, args.button);
}
//	----------------------------------------------------------------------------------------------------

void ofxGuiMovable::mouseReleased(int x, int y, int button){
	obj = NULL;
}
void ofxGuiMovable::mouseReleased(ofMouseEventArgs & args){
	mouseReleased(args.x, args.y, args.button);
}
