#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofEnableDepthTest();
    ofDisableArbTex();
    ofSetWindowTitle("Night in the Snow Land");

    ofLoadImage(mSkyTexture, "sky.jpg");
    ofLoadImage(mSurfaceTexture, "surface.jpg");
    ofLoadImage(mWoodTexture, "wood.jpg");

    cam.setAutoDistance(false);
    cam.setPosition(50, 50, 150);

    mThemeSoundtrack.load("theme.mp3");
    mThemeSoundtrack.play();

    mFireSounds.load("fire.mp3");
    mFireSounds.setVolume(60);
    mFireSounds.play();

    mSkyInTheNight.setRadius(300);
    mSkyInTheNight.setResolution(100);

    for(int i = -150; i <= 150; i += 150)
    {
        snowSystem.push_back(SnowParticleSystem{ofVec3f(-150, 230, i)});
    }
}

//--------------------------------------------------------------
void ofApp::update()
{
    fireSystem.addNewParticle();
}

//--------------------------------------------------------------
void ofApp::draw()
{
    cam.begin();
    ofPushMatrix();
    mSkyTexture.bind();
    ofSetColor(0xFFFFFF);
    mSkyInTheNight.draw();
    mSkyTexture.unbind();
    ofPopMatrix();
    ofPushMatrix();
    mSurfaceTexture.bind();
    ofRotateX(90);
    ofSetColor(0xFFFFFF);
    ofDrawBox(600, 600, 0);
    mSurfaceTexture.unbind();
    ofPopMatrix();
    ofPushMatrix();
    mWoodTexture.bind();
    ofRotateX(45);
    ofDrawBox(ofVec3f(0, -1, -16),10, 25, 10);
    ofRotateX(270);
    ofDrawBox(ofVec3f(0, -1, 16),10, 25, 10);
    ofRotateZDeg(35);
    ofDrawBox(ofVec3f(16, -1, 8),10, 25, 10);
    ofRotateZDeg(115);
    ofDrawBox(ofVec3f(16, -1, 8),10, 25, 10);


    mWoodTexture.unbind();
    ofPopMatrix();
    fireSystem.runSystem();
    for(size_t i = 0; i < snowSystem.size(); i++)
    {
        snowSystem[i].addNewParticle();
        snowSystem[i].runSystem();
    }

    cam.end();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
