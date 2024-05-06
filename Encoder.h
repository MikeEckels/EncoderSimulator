
#ifndef ENCODER_H
#define ENCODER_H

#include <thread>
#include <chrono>
#include <Windows.h>
#include "Button.h"

enum EncoderDirection { NONE, LEFT, RIGHT };

class Encoder {
private:
	signed char position = 0;
	EncoderDirection direction = NONE;
	unsigned char numClicks = 1;
	signed char incrementAmount = 1;
	unsigned short timePerRotationMs = 150;
	unsigned short millisPerClick = (this->timePerRotationMs / (unsigned short)4);
	const signed char directionStates[16] = {0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0};
	
	std::unique_ptr<Button> A{ new Button };
	std::unique_ptr<Button> B{ new Button };
	std::unique_ptr<Button> shaftButton{ new Button };

	void Update();

public:
	Encoder();
	~Encoder() = default;

	void Reset();
	void TurnLeft(unsigned char numClicks);
	void TurnRight(unsigned char numClicks);

	Button* GetAPin() const;
	Button* GetBPin() const;
	Button* GetShaftButton() const;
	signed char GetPosition() const;
	signed char GetIncrementAmt() const;
	EncoderDirection GetDirection() const;
	const char* GetDirectionStr() const;

	signed char Read();
	void SetPosition(signed char position);
	void SetIncrementAmt(signed char value);

};

#endif //ENCODER_H
