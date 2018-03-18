#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofBackground(39);
	ofSetWindowTitle("Insta");
	
	ofEnableDepthTest();

	this->icoSphere.setRadius(250);
	this->icoSphere.setResolution(3);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(ofGetFrameNum() * 0.1);
	ofRotateY(ofGetFrameNum() * 0.25);

	vector<ofMeshFace> triangles = icoSphere.getMesh().getUniqueFaces();
	for (int i = 0; i < triangles.size(); i++) {

		ofPoint avg = (triangles[i].getVertex(0) + triangles[i].getVertex(1) + triangles[i].getVertex(2)) / 3;
		float noise_value = ofNoise(avg.x * 0.002, avg.y * 0.002, avg.z * 0.002, ofGetFrameNum() * 0.005);
		if (noise_value < 0.45) {

			noise_value = 0.4;
		}
		else if (noise_value > 0.7) {

			noise_value = 0.55;
		}
		else {

			noise_value = 0.5;
		}

		ofMesh mesh;

		mesh.addVertex(ofPoint(0, 0, 0));
		mesh.addVertex(triangles[i].getVertex(0) * noise_value);
		mesh.addVertex(triangles[i].getVertex(1) * noise_value);
		mesh.addVertex(triangles[i].getVertex(2) * noise_value);

		mesh.addIndex(0);
		mesh.addIndex(1);
		mesh.addIndex(2);

		mesh.addIndex(0);
		mesh.addIndex(2);
		mesh.addIndex(3);

		mesh.addIndex(0);
		mesh.addIndex(1);
		mesh.addIndex(3);

		mesh.addIndex(1);
		mesh.addIndex(2);
		mesh.addIndex(3);

		ofSetColor(39);
		mesh.drawFaces();

		ofSetColor(239);
		mesh.drawWireframe();
	}

	this->cam.end();
}


//========================================================================
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}