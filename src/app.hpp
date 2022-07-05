#ifndef APP_HPP
#define APP_HPP

#include <piksel/baseapp.hpp>

class App : public piksel::BaseApp {
public:
    App() : piksel::BaseApp(800, 800) {}
    void setup();
    void draw(piksel::Graphics& g);
    void keyPressed(int key);
};
#endif /* APP_HPP */