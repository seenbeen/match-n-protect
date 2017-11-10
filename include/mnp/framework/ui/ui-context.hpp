#pragma once
#include <SFML/Window/Event.hpp>
#include <mnp/framework/ui/shapes.hpp>

class BaseUIContext : public MNPInput::InputContext {
    bool focusFlag;
public:
    // Used by ui to re-order rendering
    // Will reset focus state when called
    bool getFocus();
    bool wantsFocus(const sf::Event &event);
    virtual bool wantsFocusImpl(const sf::Event &event) = 0;

};


class UIClickableContext : public BaseUIContext {

public:
    UIClickableContext();
    ~UIClickableContext();

    Rectangle m_MyRect;
    bool clicked;

    void setRect(Rectangle r);

    bool handleInput(const sf::Event &event);

    void update(const float &deltaTime);

    bool wantsFocusImpl(const sf::Event &event);
};


class BlankContext : public BaseUIContext {
public:
    bool handleInput(const sf::Event &event);
    void update(const float &deltaTime);

    bool wantsFocusImpl(const sf::Event &event);
};
/*

class UITextInputContext : public BaseUiContext {

public:
    UITextInputContext();
    ~UITextInputContext();

    bool inFocus;

    std::list<sf::Keyboard::Key*> inputKeys;

    void update(const float &deltaTime);
    bool handleInput(const sf::Event &event);
    bool wantsFocusImpl(const sf::Event &event);

    virtual bool checkEnter(const sf::Event &event) = 0;
    virtual int checkExit(const sf::Event &event) = 0;
};
*/