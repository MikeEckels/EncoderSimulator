#include "Button.h"

void Button::Press(unsigned short timeMs, bool simBounce) {
    this->state.store(simBounce ? Button::SimulateBounce() : true);
    if (!timeMs) { this->latched = true; return; }
    std::this_thread::sleep_for(std::chrono::milliseconds(timeMs));
    Button::Release();
}

void Button::Release() {
    this->state.store(false);
    this->latched = false;
    this->bounceCount = 0;
}

bool Button::ReadState() {
    return this->state.load();
}

bool Button::SimulateBounce(bool endState) {
    endState = this->latched ? true : endState;
    this->state.store((this->bounceCount <= this->numBounces) ? (bool)(rand() % 2) : endState);
    this->bounceCount++;

    return this->state.load();
}