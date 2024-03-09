#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	ofGLWindowSettings settings;
	settings.setGLVersion(4, 3);
	//settings.windowMode = OF_FULLSCREEN;
	settings.setSize(1080, 1080);
	settings.setPosition(glm::vec2(0, 0));
	ofCreateWindow(settings);
	ofRunApp(new ofApp());

}
