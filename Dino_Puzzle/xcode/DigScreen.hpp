//
//  DigScreen.hpp
//  Dino_Puzzle
//
//  Created by Andrew Cotter on 4/26/17.
//
//

#ifndef DigScreen_hpp
#define DigScreen_hpp

class DigScreen;

typedef std::shared_ptr<DigScreen> DigScreenRef;

class DigScreen
{
public:
    static DigScreenRef create();
    
    void update();
    void draw();
    
    
private:
    DigScreen();
    void setup();
    
};
#endif /* DigScreen_hpp */
