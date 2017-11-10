#include <engine/input/input-system.hpp>
#include <mnp/framework/ui/ui-context.hpp>

bool BaseUIContext::wantsFocus(const sf::Event &event){
    focusFlag = wantsFocusImpl(event);
    return focusFlag;
}

bool BaseUIContext::getFocus(){
    if (focusFlag){
        focusFlag = false;
        return true;
    }
    return false;
}

bool UIClickableContext::wantsFocusImpl(const sf::Event &event){
    return true;
}

bool UIClickableContext::handleInput(const sf::Event &event){
    if (event.type == sf::Event::MouseButtonPressed){
        if (event.mouseButton.button == sf::Mouse::Left){
            if (m_MyRect.collide(event.mouseButton.x,event.mouseButton.y)){
                clicked=true;
                return false;
            }
        }
    }
    return true;

}

bool BlankContext::handleInput(const sf::Event &event){
    return true;
}

void BlankContext::update(const float &deltaTime){}

bool BlankContext::wantsFocusImpl(const sf::Event &event){
    return false;
}
void UIClickableContext::update(const float &deltaTime){
    clicked = false;
}

void UIClickableContext::setRect(Rectangle r){
    m_MyRect = r;
}

UIClickableContext::UIClickableContext(){clicked=false;}
UIClickableContext::~UIClickableContext(){}
/*

UITextInputContext::UITextInputContext(){
    inFocus=false;
    StringInput = "";

}
UITextInputContext::~UITextInputContext(){}

bool UITextInputContext::wantsFocusImpl(sf::Event* event){
    return true;
}

void UITextInputContext::update(){

}

bool UITextInputContext::handleInput(sf::Event* event){
    std::cout << "\n TEXT WA: " <<inputText << std::endl;

    if (inFocus==true){
        if (checkExit(sf::Event* event) = 0){
            inFocus=false;
            return false;
        }
        else if (checkExit(sf::Event* event) = 1){
            inFocus=false;
            return true;
        }

        else if ((event.type == sf::Event::KeyPressed)&&(event.key.code == sf::Keyboard::BackSpace)){
            StringInput = "\b";
        }
        else if ((event.type == sf::Event::KeyPressed)&&(event.key.code == sf::Keyboard::Return)){
            std::cout << inputText << std::endl;
            StringInput =
            return false;

        }
        else if (event.type == sf::Event::TextEntered){
                //std::cout << "You Typed somethn" << std::endl;
            if (event.text.unicode < 128){
                inputText= inputText + static_cast<char>(event.text.unicode);
                return false;
            }
        }
    }

    else{
        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Tilde)){
            focus=true;
            return false;
        }
    }

    return true;
}
*/