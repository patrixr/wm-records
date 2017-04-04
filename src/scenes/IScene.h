//
//  iScene.h
//  wm-label-visuals
//
//  Created by Patrick Rabier on 16/2/17.
//
//

#ifndef iScene_h
#define iScene_h


class IScene {
    
public:
    virtual void    setup() = 0;
    virtual void    draw() = 0;
    virtual void    update() = 0;
    
    virtual void    animateIn() = 0;
    virtual void    animateOut() = 0;
    virtual void    keyPressed(int key) = 0;
};



#endif /* iScene_h */
