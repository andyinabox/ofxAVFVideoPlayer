//
//  ofxAVFVideoPlayer.h
//  AVFoundationTest
//
//  Created by Sam Kronick on 5/31/13.
//
//

#pragma once

#include "ofMain.h"

#ifdef __OBJC__
#import "ofxAVFVideoRenderer.h"
#endif


class ofxAVFVideoPlayer  : public ofBaseVideoPlayer {
public:
    
    ofxAVFVideoPlayer();
    ~ofxAVFVideoPlayer();

    bool load(std::string name);
    bool                loadMovie(string path);
    
    void                closeMovie();
    void                close();
    
    void                idleMovie();
    void                update();
    void                play();
    void                stop();
    
    OF_DEPRECATED_MSG("Use getTexture()->bind() instead. Ensure decodeMode != OF_QTKIT_DECODE_PIXELS_ONLY.", void bind());
    OF_DEPRECATED_MSG("Use getTexture()->unbind() instead. Ensure decodeMode != OF_QTKIT_DECODE_PIXELS_ONLY.", void unbind());
    
    bool isFrameNew() const; //returns true if the frame has changed in this update cycle

    // Returns openFrameworks compatible RGBA pixels.
    // Be aware of your current render mode.
    
    ofPixels& getPixels();
    ofPixels& getPixels() const;
    ofPixels& getPixelsRef();
    
    // Returns openFrameworks compatible ofTexture pointer.
    // if decodeMode == OF_QTKIT_DECODE_PIXELS_ONLY,
    // the returned pointer will be NULL.
    ofTexture * getTexture();
    ofTexture& getTextureReference();
    
    float               getPosition();
    float               getPositionInSeconds();
    float               getSpeed();
    ofLoopType          getLoopState();
    float               getDuration();
    bool                getIsMovieDone();
    int                 getTotalNumFrames();
    int                 getCurrentFrame();
    
    void                setPaused(bool bPaused);
    void                setPosition(float pct);
    void                setVolume(float volume);
    void                setBalance(float balance);
    void                setLoopState(ofLoopType state);
    void                setSpeed(float speed);
    void                setFrame(int frame); // frame 0 = first frame...
    
    // ofQTKitPlayer only supports OF_PIXELS_RGB and OF_PIXELS_RGBA.
    bool                setPixelFormat(ofPixelFormat pixelFormat);
    ofPixelFormat       getPixelFormat() const;

    void                draw(float x, float y, float w, float h);
    void                draw(float x, float y);
    
    float               getWidth() const;
    float               getHeight() const;
    
    bool                isPaused() const;
    bool                isLoaded() const;
    bool                isLoading();
    bool                isPlaying() const;
    bool                errorLoading();
    
    
    void                firstFrame();
    void                nextFrame();
    void                previousFrame();
    
protected:
    
    ofLoopType currentLoopState;
    
    bool bPaused;
    bool bNewFrame;
    bool bHavePixelsChanged;
    
    float duration;
    float speed;
    
    string moviePath;
    
    bool bInitialized;
    
    
    // updateTexture() pulls texture data from the movie AVFoundation
    // renderer into our internal ofTexture.
    void updateTexture();
    void reallocatePixels();
    
    ofFbo fbo;
    ofTexture tex;
    
    ofPixels pixels;
    ofPixelFormat pixelFormat;
    
    // This #ifdef is so you can include this .h file in .cpp files
    // and avoid ugly casts in the .m file
#ifdef __OBJC__
    AVFVideoRenderer* moviePlayer;
#else
    void * moviePlayer;
#endif
    
};
