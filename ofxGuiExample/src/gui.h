#ifndef _GUI
#define _GUI

const string dummy_Tags[] =
{
	"only",
	"works",
	"in",
	"GUI"
};

enum {
	triggerButton,
	switchButton,
	colorRGB,
	colorRGBA,
	files,
	knob,
	matrix,
	points,
	scope,
	slider,
	xyPad,
	swtch,
};

void testApp::setupGui(){
	ofxGuiPanel	*sliderAndKnobs = gui->addPanel(0, "Sliders&Knob", 10, 20, 12, OFXGUI_PANEL_SPACING);
	sliderAndKnobs->addSlider(slider, "slider", 125, 15, 0, 255, 60, kofxGui_Display_Int, 1);
	sliderAndKnobs->addKnob(knob, "knob", 55, 55, 0, 255, 128, kofxGui_Display_Int, 50);
	sliderAndKnobs->addColor(colorRGB, "colorRGB", 125, 30, ofRGBA(178,0,205,255), kofxGui_Color_RGB);
	sliderAndKnobs->addColor(colorRGBA, "colorRGBA", 125, 40, ofRGBA(68,25,180,125), kofxGui_Color_RGBA);
	sliderAndKnobs->addXYPad(xyPad, "XYPad", ofGetWidth()/6,ofGetHeight()/6, ofxPoint2f(0,0), ofxPoint2f(ofGetWidth(),ofGetHeight()),ofxPoint2f(350, 520), kofxGui_Display_Int, 1);

	ofxGuiPanel	*buttonsAndMatrix = gui->addPanel(0, "Buttons&Matrix", 215, 20, 12, OFXGUI_PANEL_SPACING);
	buttonsAndMatrix->addButton(triggerButton, "triggerButton", 10, 10, kofxGui_Button_Off, kofxGui_Button_Trigger, "");
	buttonsAndMatrix->addButton(switchButton, "switchButton", 10, 10, kofxGui_Button_Off, kofxGui_Button_Switch, "");
	buttonsAndMatrix->addMatrix(matrix, "matrix", 125, 125, 5, 5, 0, kofxGui_Matrix_Set, 6);
	buttonsAndMatrix->addFiles(files,"files", 125, 20, "verdana.ttf", "fonts/", "ttf");
	//[bb] This by me, the new Switch works in the GUI so far, and reports to console:
	buttonsAndMatrix->addSwitch(swtch, "switch test", 125, 25, 0, 3, 0, &dummy_Tags[0]);

	ofxGuiPanel	*pointsAndScope = gui->addPanel(0, "Points&Scope", 380, 20, 12, OFXGUI_PANEL_SPACING);
	pointsAndScope->addPoints(points, "points", 255, 60, ofxPoint2f(0.0f, 0.0f), ofxPoint2f(100.0, 1.0), ofxPoint2f(0.5f, 0.0f), kofxGui_Display_Float2, 0.1);
	pointsAndScope->addScope(scope, "scope", 255, 60, 50, ofxPoint2f(0.0f, 0.0f), kofxGui_Button_Switch);


	gui->forceUpdate(false);
	gui->activate(true);
}

void testApp::handleGui(int parameterId, int task, void* data, int length){
	switch(parameterId){
		case triggerButton:
			if(length == sizeof(bool))
				if(*(bool*)data)
					cout<<"triggerButton"<<endl;
			break;
		case switchButton:
			if(length == sizeof(bool))
				cout<<"switchButton value : "<<*(bool*)data<<endl;
			break;
		case colorRGB:
			if(length == sizeof(ofRGBA)){
				ofRGBA c = *(ofRGBA*)data;
				cout<<"colorRGB value : "<<c.r<<" "<<c.g<<" "<<c.b<<endl;
			}
			break;
		case colorRGBA:
			if(length == sizeof(ofRGBA)){
				ofRGBA c = *(ofRGBA*)data;
				cout<<"colorRGB value : "<<c.r<<" "<<c.g<<" "<<c.b<<" "<<c.a<<endl;
			}
			break;
		case knob:
			if(length == sizeof(float)){
				cout<<"knob value : "<<*(float*)data<<endl;
			}
			break;
		case matrix:
			if (task == kofxGui_Set_Cell)
				cout<<"matrix value : "<<*(int*)data<<endl;
			break;
		case files:
			if(length == sizeof(string)){
				cout<<"files value : "<<*(string*)data<<endl;
			}
			break;
		case points:
			if (task == kofxGui_Set_Point){
				//cout<<"points value : "<<(*(ofxPoint2f*)data).x<<" "<<(*(ofPoint*)data).y<<endl;
				bkg = (*(ofxPoint2f*)data).y * 255.0;
			}
			else if (task == kofxGui_Set_PointArray){
				vector<ofxPoint2f> points = *(vector<ofxPoint2f>*)data;
				cout<<"points value : "<<endl;
				for(int i=0; i<points.size(); i++)
					cout<<"    "<<points[i].x<<" "<<points[i].y<<endl;
			}

			break;
		case scope:
			if (task == kofxGui_Set_Point){
				cout<<"scope value : "<<(*(ofxPoint2f*)data).x<<" "<<(*(ofPoint*)data).y<<endl;
			}
			else if (task == kofxGui_Set_FloatArray){
				float* values = (float*)data;
				cout<<"scope value : "<<endl;
				for(int i=0; i<50; i++)
					cout<<"  "<<i<<":   "<<values[i]<<endl;
			}
			break;
		case slider:
			if(length == sizeof(float)){
				cout<<"slider value : "<<*(float*)data<<endl;
			}
			break;
		case xyPad:
			if (task == kofxGui_Set_Point){
				cout<<"xyPad value : "<<(*(ofxPoint2f*)data).x<<" "<<(*(ofPoint*)data).y<<endl;
			}
			break;
		case swtch:
			if(length == sizeof(int)){
				cout<<"Switch value : "<<dummy_Tags[*(int*)data]<<endl;
			}
			break;
	}
}

#endif
