#pragma once

#include "ofMain.h"
#include <iostream>
#include <vector>

class Particle
{
private:
    ofVec3f mLocation;
    ofVec3f mVelocity;
    ofColor mColor;
    ofSpherePrimitive mMolecule;
    double mLifeSpan;
    double mCounter;
    double mRadius;
    double mDeltaTime = 0.1;
    double mPI = 3.14;
    double mGravity = 9.81;
    double mWeight;
    double n = 0.0000176;
    double mForceDirection;

    void update()
    {
        mVelocity.y += mForceDirection * ((mGravity * mWeight) - (6 * mPI * mVelocity.y * n * mRadius)) * mDeltaTime;
        mLocation.x += mVelocity.x;
        mLocation.y += mVelocity.y * mDeltaTime;
        mLocation.z += mVelocity.z;
        mLifeSpan -= mCounter;
    }

    void drawParticle()
    {
        ofSetColor(mColor);
        mMolecule.setPosition(mLocation);
        mMolecule.draw();
    }

public:


    Particle(ofVec3f location, ofVec3f velocity, double radius, double counter) : mLocation(location), mVelocity(velocity), mCounter(counter), mRadius(radius)
    {
        mWeight = ofRandom(0.1, 2);
        mLifeSpan = 255;
        mMolecule.setRadius(mRadius);
        mMolecule.setResolution(100);
    }

    bool isDead()
    {
        if(mLifeSpan < 0.0)
            return true;
        return false;
    }

    void setParticleColor(ofColor color)
    {
        mColor = color;
    }

    void setForceDirection(int direction)
    {
        mForceDirection = direction;
    }

    double getLifeSpan()
    {
        return mLifeSpan;
    }

    void run()
    {
        update();
        drawParticle();
    }
};

class ParticleSystem
{  
protected:
    std::vector<Particle> mParticles;
    ofColor mColor;
private:
    ofVec3f mOrigin;
    ofVec3f mVelocity;
    ofColor mParticleColor;
    double mForceDirection;
public:
    ParticleSystem(ofVec3f location): mOrigin(location){}

    void addParticle(double radius, double counter, ofVec3f velocity)
    {
        mParticles.push_back(Particle(mOrigin, velocity,  radius, counter));
    }

    void setForceDirection(int direction)
    {
        mForceDirection = direction;
    }

    void run()
    {
        std::vector<Particle>::iterator it = mParticles.begin();

        while(it != mParticles.end())
        {
            if(it->isDead())
                it = mParticles.erase(it);
            else
            {
                it->setForceDirection(mForceDirection);
                it->run();
                ++it;
            }
        }
    }
};

class FireParticleSystem: public ParticleSystem
{
private:
    ofVec3f mLocation;
    ofVec3f mVelocity;

    ofVec3f getRandomFireParticlesVelocity()
    {
        return ofVec3f(ofRandom(-1, 1), ofRandom(-2, 0), ofRandom(-1, 1));
    }

    ofColor getFireColor(int LifeSpanValue)
    {
        if(LifeSpanValue < 255 and LifeSpanValue >=210)
            return ofColor(128, 17, 0);
        else if(LifeSpanValue < 210 and LifeSpanValue >= 170)
            return ofColor(182, 34, 3);
        else if(LifeSpanValue < 170 and LifeSpanValue >= 130)
            return ofColor(215, 53, 2);
        else if(LifeSpanValue < 130 and LifeSpanValue >= 80)
            return ofColor(252, 100, 0);
        else if(LifeSpanValue < 80 and LifeSpanValue >= 40)
            return ofColor(255, 117, 0);
        else if(LifeSpanValue < 40 and LifeSpanValue >= 0)
            return ofColor(250, 192, 0);
        else
            return ofColor(0, 0, 0);
    }

public:
    FireParticleSystem(ofVec3f location) : ParticleSystem(location){}

    void addNewParticle()
    {
        ParticleSystem::setForceDirection(1);
        ParticleSystem::addParticle(3, 8.1, getRandomFireParticlesVelocity());
    }

    void runSystem()
    {
        for(size_t i = 0; i < ParticleSystem::mParticles.size(); i++)
        {
            ParticleSystem::mParticles[i].setParticleColor(getFireColor(ParticleSystem::mParticles[i].getLifeSpan()));
        }
        ParticleSystem::run();
    }
};

class SnowParticleSystem:public ParticleSystem
{
private:
    ofVec3f mLocation;
    ofVec3f mVelocity;

    ofVec3f getRandomSnowParticlesVelocity()
    {
        return ofVec3f(ofRandom(0, 5), ofRandom(-5, 0), 0);
    }

    ofColor getSnowColor(int LifeSpanValue)
    {
        if(LifeSpanValue < 255 and LifeSpanValue >=210)
            return ofColor(5, 115, 153);
        else if(LifeSpanValue < 210 and LifeSpanValue >= 170)
            return ofColor(3, 28, 52);
        else if(LifeSpanValue < 170 and LifeSpanValue >= 130)
            return ofColor(12, 39, 68);
        else if(LifeSpanValue < 130 and LifeSpanValue >= 80)
            return ofColor(66, 129, 165);
        else if(LifeSpanValue < 80 and LifeSpanValue >= 40)
            return ofColor(131, 168, 195);
        else if(LifeSpanValue < 40 and LifeSpanValue >= 0)
            return ofColor(248, 233, 213);
        else
            return ofColor(0, 0, 0);
    }

public:
    SnowParticleSystem(ofVec3f location) : ParticleSystem(location){}

    void addNewParticle()
    {
        ParticleSystem::setForceDirection(-1);
        ParticleSystem::addParticle(1, 4.5, getRandomSnowParticlesVelocity());
    }

    void runSystem()
    {
        for(size_t i = 0; i < ParticleSystem::mParticles.size(); i++)
        {
            ParticleSystem::mParticles[i].setParticleColor(getSnowColor(ParticleSystem::mParticles[i].getLifeSpan()));
        }
        ParticleSystem::run();
    }

};

class ofApp : public ofBaseApp{
public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
private:
        std::vector<SnowParticleSystem> snowSystem;
        FireParticleSystem fireSystem{ofVec3f(0, 10, 0)};
        ofSpherePrimitive mSkyInTheNight;
        ofTexture mSkyTexture;
        ofTexture mSurfaceTexture;
        ofTexture mWoodTexture;
        ofEasyCam cam;
        ofSoundPlayer mThemeSoundtrack;
        ofSoundPlayer mFireSounds;
};
