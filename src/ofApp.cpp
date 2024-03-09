#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    bigW = ofGetWidth();
    bigH = ofGetHeight();
    particles.resize(bigW * bigH);
    
    buffer.allocate(particles, GL_DYNAMIC_DRAW);
    
    img1.load("desert1.jpg");
    img2.load("desert2.jpg");
    img1.resize(bigW, bigH);
    img2.resize(bigW,bigH);
    int offset = merge2imgs(img2, img1, particles, 0, 0, 0, 200);
    
    particles.resize(offset);
    buffer.updateData(0, particles);
    
    vbo.setVertexBuffer(buffer, 4, sizeof(Particle));
    vbo.setColorBuffer(buffer, sizeof(Particle), sizeof(glm::vec4)*2);
    buffer.bindBase(GL_SHADER_STORAGE_BUFFER, 0);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    vboshader.setupShaderFromFile(GL_COMPUTE_SHADER, "Shaders//vboshader.glsl");
    vboshader.linkProgram();
    vboshader.begin();
    vboshader.setUniform1f("time", ofGetElapsedTimef());
    vboshader.dispatchCompute(particles.size() / 20, 1, 1);
    vboshader.end();
    
    

    
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofBackground(0);
    vbo.draw(GL_POINTS, 0, particles.size());

}
//--------------------------------------------------------------
int merge2imgs(ofImage& img1, ofImage& img2, vector<Particle> &particles, int offx, int offy, int offset = 0, int cutoff = 256) {
		int W = img1.getWidth();
		int H = img1.getHeight();
		int i = offset;

		for (int x = 0; x < W; x += 2) {
			for (int y = 0; y < H; y++) {
				ofColor col1 = img1.getColor(x, y);
				ofColor col2 = img2.getColor(x, y);
				int tempx = offx + x;
				int tempy = offy + y;
				ofColor col;
				if (col1.getBrightness() < cutoff or col2.getBrightness() < cutoff) {
					Particle& p = particles.at(i);
					p.pos.x = tempx;
					p.pos.y = tempy;
					p.pos.z = 0;
					p.pos.w = 1;
					if (col1.getBrightness() > 1.5 * col2.getBrightness()) {
						col = col1;
					}
					else {
						col = col2;
					}
					p.color = col;
					i++;
					if (i == particles.size()) {
						return i;
					}
				}

			}
		}
		return i;
	}
