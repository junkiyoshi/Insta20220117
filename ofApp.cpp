#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");

	ofBackground(255);
	ofSetLineWidth(3);
	ofEnableDepthTest();

	this->line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face.clear();
	this->line.clear();

	int width = 10;
	for (int y = -150; y <= 150; y += width) {

		for (int len = 150; len <= 300; len += 2) {

			ofColor color;
			color.setHsb(ofRandom(255), 130, 255);
			int start_param = ofRandom(1000) + ofGetFrameNum() * ofRandom(0.5, 0.8);
			int end_param = start_param + 5;

			for (int param = start_param; param <= end_param; param++) {

				vector<glm::vec3> vertices;
				vertices.push_back(glm::vec3(this->make_point(len, param), width *  0.5 + y));
				vertices.push_back(glm::vec3(this->make_point(len, param), width * -0.5 + y));

				this->face.addVertices(vertices);
				this->line.addVertices(vertices);

				this->face.addColor(ofColor(0));
				this->face.addColor(ofColor(0));

				this->line.addColor(color);
				this->line.addColor(color);

				if (param > start_param) {

					this->face.addIndex(this->face.getNumVertices() - 1); this->face.addIndex(this->face.getNumVertices() - 2); this->face.addIndex(this->face.getNumVertices() - 4);
					this->face.addIndex(this->face.getNumVertices() - 1); this->face.addIndex(this->face.getNumVertices() - 3); this->face.addIndex(this->face.getNumVertices() - 4);

					this->line.addIndex(this->line.getNumVertices() - 1); this->line.addIndex(this->line.getNumVertices() - 3);
					this->line.addIndex(this->line.getNumVertices() - 2); this->line.addIndex(this->line.getNumVertices() - 4);
				}

				if (param % 25 == 0 || param == start_param) {

					this->line.addIndex(this->line.getNumVertices() - 1); this->line.addIndex(this->line.getNumVertices() - 2);
				}
			}

			this->line.addIndex(this->line.getNumVertices() - 1); this->line.addIndex(this->line.getNumVertices() - 2);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	
	ofRotateY(ofGetFrameNum() * 1.8);
	ofRotateX(ofGetFrameNum() * 1.2);

	this->face.draw();
	this->line.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
glm::vec2 ofApp::make_point(int len, int param) {

	param = param % 100;
	if (param < 25) {

		return glm::vec2(ofMap(param, 0, 25, -len * 0.5, len * 0.5), -len * 0.5);
	}
	else if (param < 50) {

		return glm::vec2(len * 0.5, ofMap(param, 25, 50, -len * 0.5, len * 0.5));
	}
	else if (param < 75) {

		return glm::vec2(ofMap(param, 50, 75, len * 0.5, -len * 0.5), len * 0.5);
	}
	else {

		return glm::vec2(-len * 0.5, ofMap(param, 75, 100, len * 0.5, -len * 0.5));
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}