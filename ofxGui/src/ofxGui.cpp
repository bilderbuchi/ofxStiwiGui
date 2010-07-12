/*
 *  ofxGui.cpp
 *  openFrameworks
 *
 *  Created by Stefan Kirch on 18.06.08.
 *  Copyright 2008 alphakanal. All rights reserved.
 *
 */

//	----------------------------------------------------------------------------------------------------
#include "ofxGui.h"

//	----------------------------------------------------------------------------------------------------

ofxGui* ofxGui::Instance(ofxGuiListener* listener)
{
	static ofxGui gui(listener);	
	return &gui;
}

//	----------------------------------------------------------------------------------------------------

ofxGui::ofxGui(ofxGuiListener* listener) {
	ofAddListener(ofEvents.setup, listener, &ofxGuiListener::setupGui);
	ofAddListener(ofEvents.draw, this, &ofxGui::draw);
	ofAddListener(ofEvents.keyPressed, this, &ofxGui::keyPressed);
	ofAddListener(ofEvents.keyReleased, this, &ofxGui::keyReleased);
	ofAddListener(ofEvents.mouseDragged, this, &ofxGui::mouseDragged);
	ofAddListener(ofEvents.mouseReleased, this, &ofxGui::mouseReleased);
	ofAddListener(ofEvents.mousePressed, this, &ofxGui::mousePressed);

	mIsActive			= false;
	mDoUpdate			= false;
	mXmlDone			= true;
	mGlobals			= ofxGuiGlobals::Instance();
	mGlobals->mListener	= listener;
}

//	----------------------------------------------------------------------------------------------------

void ofxGui::update(int parameterId, int type, void* data, int length)
{
	if(mIsActive || mDoUpdate)
	{
		ofxGuiObject*	tmpObj;
		bool			handled;
		
		for(int i = 0; i < mObjects.size(); i++)
		{
			tmpObj	= (ofxGuiObject*)mObjects.at(i);
			handled	= tmpObj->update(parameterId, type, data, length);

			if(handled)
				break;
		}
	}
}

//	----------------------------------------------------------------------------------------------------

void ofxGui::draw()
{
	if(mIsActive)
	{
		ofEnableAlphaBlending();
		
		ofxGuiObject* tmpObj;
		
		for(int i = 0; i < mObjects.size(); i++)
		{
			tmpObj = (ofxGuiObject*)mObjects.at(i);
			tmpObj->draw();
		}
		
		ofDisableAlphaBlending();
	}
}
void ofxGui::draw(ofEventArgs & args)
{  
	int w, h;

	w = glutGet(GLUT_WINDOW_WIDTH);
	h = glutGet(GLUT_WINDOW_HEIGHT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, (float)w/(float)h, (float)h / 2.0 / tanf(PI * 60.0f / 360.0) / 10.0, (float)h / 2.0 / tanf(PI * 60.0f / 360.0) * 10.0);
	gluLookAt((float)w / 2.0, (float)h / 2.0, (float)h / 2.0 / tanf(PI * 60.0f / 360.0), (float)w / 2.0, (float)h / 2.0, 0.0, 0.0, 1.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	glScalef(1, -1, 1);
	glTranslatef(0, -h, 0); 

	glDisable(GL_BLEND);
	glDisable(GL_LIGHTING);

	draw();
}

//	----------------------------------------------------------------------------------------------------

void ofxGui::activate(bool activate)
{
	mIsActive = activate;
}

//	----------------------------------------------------------------------------------------------------

void ofxGui::forceUpdate(bool update)
{
	mDoUpdate = update;
}

//	----------------------------------------------------------------------------------------------------

void ofxGui::keyPressed(int key){	
}
void ofxGui::keyPressed(ofKeyEventArgs & args){	
	keyPressed(args.key);
}

//	----------------------------------------------------------------------------------------------------

void ofxGui::keyReleased(int key){	
}
void ofxGui::keyReleased(ofKeyEventArgs & args){	
	keyReleased(args.key);
}


//	----------------------------------------------------------------------------------------------------

void ofxGui::mouseDragged(int x, int y, int button)
{
	if(mIsActive)
	{
		ofxGuiObject*	tmpObj;
		bool			handled;

		for(int i = 0; i < mObjects.size(); i++)
		{
			tmpObj	= (ofxGuiObject*)mObjects.at(i);
			handled	= tmpObj->mouseDragged(x, y, button);

			if(handled)
				break;
		}
	}
}

void ofxGui::mouseDragged(ofMouseEventArgs & args){
	mouseDragged(args.x, args.y, args.button);
}
//	----------------------------------------------------------------------------------------------------

void ofxGui::mousePressed(int x, int y, int button)
{
	if(mIsActive)
	{
		ofxGuiObject*	tmpObj;
		bool			handled;
		
		for(int i = 0; i < mObjects.size(); i++)
		{
			tmpObj	= (ofxGuiObject*)mObjects.at(i);
			handled	= tmpObj->mousePressed(x, y, button);
			
			if(handled)
				break;
		}
	}
}

void ofxGui::mousePressed(ofMouseEventArgs & args){
	mousePressed(args.x, args.y, args.button);
}
//	----------------------------------------------------------------------------------------------------

void ofxGui::mouseReleased(int x, int y, int button)
{
	if(mIsActive)
	{
		ofxGuiObject* tmpObj;
		
		for(int i = 0; i < mObjects.size(); i++)
		{
			tmpObj = (ofxGuiObject*)mObjects.at(i);
			tmpObj->mouseReleased(x, y, button);
		}
	}
}
void ofxGui::mouseReleased(ofMouseEventArgs & args){
	mouseReleased(args.x, args.y, args.button);
}

//	----------------------------------------------------------------------------------------------------

ofxGuiPanel* ofxGui::addPanel(int id, string name, int x, int y, int border, int spacing)
{
	ofxGuiPanel* newPanel = new ofxGuiPanel();
	newPanel->init(id, name, x, y, border, spacing);
	mObjects.push_back(newPanel);
	
	return newPanel;
}

//	----------------------------------------------------------------------------------------------------

bool ofxGui::buildFromXml(string file)
{
	if(!mXmlDone)
		return false;
	
	if(!mGlobals->mXml.loadFile(file))
		return false;
	
	int numberOfTags = mGlobals->mXml.getNumTags("UI");
	
	if(numberOfTags != 1)
		return false;
	
	mObjects.clear();
	
	mXmlDone			= false;
	mGlobals->mXmlfile	= file;
	
	mGlobals->mXml.pushTag("UI", 0);

	mIsActive	= mGlobals->mXml.getValue("ISACTIVE", 0);
	mDoUpdate	= mGlobals->mXml.getValue("DOUPDATE", 0);

	mGlobals->buildFromXml();
	
	numberOfTags = mGlobals->mXml.getNumTags("OBJECT");
	
	if(numberOfTags > 0)
	{
		for(int i = 0; i < numberOfTags; i++)
		{
			mGlobals->mXml.pushTag("OBJECT", i);
			
			int		id		= mGlobals->mXml.getValue("ID", 0);
			string	type	= mGlobals->mXml.getValue("TYPE", "");
			string	name	= mGlobals->mXml.getValue("NAME", "");
			int		x		= mGlobals->mXml.getValue("LEFT", 0);
			int		y		= mGlobals->mXml.getValue("TOP", 0);
			int		border	= mGlobals->mXml.getValue("BORDER", 0);
			int		spacing	= mGlobals->mXml.getValue("SPACING", 0);
			
			if(type == "PANEL")
			{
				ofxGuiPanel* panel = addPanel(id, name, x, y, border, spacing);
				panel->buildFromXml();
			}
			
			mGlobals->mXml.popTag();
		}
	}
	
	mGlobals->mXml.popTag();
	
	mXmlDone = true;
	
	return true;
}

//	----------------------------------------------------------------------------------------------------

void ofxGui::saveToXml(string file)
{
	if(!mXmlDone)
		return;

	mXmlDone = false;

	mGlobals->mXml.clear();
		
	int id = mGlobals->mXml.addTag("UI");
	
	mGlobals->mXml.setValue("UI:VERSION", OFXGUI_VERSION, id);

	mGlobals->mXml.setValue("UI:ISACTIVE", mIsActive, id);
	mGlobals->mXml.setValue("UI:DOUPDATE", mDoUpdate, id);
		
	mGlobals->mXml.pushTag("UI", id);

	mGlobals->saveToXml();

	ofxGuiObject* tmpObj;

	for(int i = 0; i < mObjects.size(); i++)
	{
		tmpObj = (ofxGuiObject*)mObjects.at(i);
		tmpObj->saveToXml();
	}
	
	mGlobals->mXml.popTag();
	mGlobals->mXml.saveFile(file);

	mXmlDone = true;
}

//	----------------------------------------------------------------------------------------------------
