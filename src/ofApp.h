#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
	public:
        struct Particle {
    		glm::vec4 pos;
    		glm::vec4 vel ={0,0,0,0 };
    		ofFloatColor color;
	};
		void setup();
		void update();
		void draw();
        int merge2imgs();

		ofShader vboshader;
  
        
		vector<Particle> particles;
		ofBufferObject buffer;
		int bigW, bigH;
		ofVbo vbo;
		ofImage img1, img2;
};
