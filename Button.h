#ifndef BUTTON_H
#define BUTTON_H

#include <atomic>
#include <thread>
#include <chrono>
#include <random>

class Button {
private:
	std::atomic<bool> state{ false };
	bool latched = false;
	unsigned char numBounces = 100;
	unsigned long long bounceCount = 0;

	bool SimulateBounce(bool endState = 0);//fix

public:
	Button() = default;
	~Button() = default;

	void Press(unsigned short timeMs, bool simBounce = true);
	void Release();
	bool ReadState();
};

#endif //BUTTON_H 