#include "Encoder.h"

Encoder::Encoder() {
	std::thread encoderThread(&Encoder::Update, this);
	encoderThread.detach();
}

void Encoder::Update() {
	while (true) {
		if (GetKeyState(VK_DOWN) & 0x8000) {
			Encoder::GetShaftButton()->Press(0, false);
		}
		else if(!(GetKeyState(VK_DOWN) & 0x8000)) {
			Encoder::GetShaftButton()->Release();
		}
		if (GetKeyState(VK_RIGHT) & 0x8000) {
			Encoder::TurnRight(this->numClicks);
		}
		if (GetKeyState(VK_LEFT) & 0x8000) {
			Encoder::TurnLeft(this->numClicks);
		}
	}
}

void Encoder::TurnLeft(unsigned char numClicks) {
	for (unsigned char i = 0; i < numClicks; i++) {
		this->B->Press(0, false);
		std::this_thread::sleep_for(std::chrono::milliseconds(this->millisPerClick));
		this->A->Press(0, false);
		std::this_thread::sleep_for(std::chrono::milliseconds(this->millisPerClick));
		this->B->Release();
		std::this_thread::sleep_for(std::chrono::milliseconds(this->millisPerClick));
		this->A->Release();
		std::this_thread::sleep_for(std::chrono::milliseconds(this->millisPerClick));
	}
}

void Encoder::TurnRight(unsigned char numClicks) {
	for (unsigned char i = 0; i < numClicks; i++) {
		this->A->Press(0, false);
		std::this_thread::sleep_for(std::chrono::milliseconds(this->millisPerClick));
		this->B->Press(0, false);
		std::this_thread::sleep_for(std::chrono::milliseconds(this->millisPerClick));
		this->A->Release();
		std::this_thread::sleep_for(std::chrono::milliseconds(this->millisPerClick));
		this->B->Release();
		std::this_thread::sleep_for(std::chrono::milliseconds(this->millisPerClick));
	}
}

void Encoder::Reset() {
	this->position = 0;
	this->direction = NONE;
}

Button* Encoder::GetAPin() const {
	return this->A.get();
}

Button* Encoder::GetBPin() const {
	return this->B.get();
}

Button* Encoder::GetShaftButton() const {
	return this->shaftButton.get();
}

signed char Encoder::GetPosition() const {
	return this->position;
}

signed char Encoder::GetIncrementAmt() const {
	return this->incrementAmount;
}

EncoderDirection Encoder::GetDirection() const {
	return this->direction;
}

const char* Encoder::GetDirectionStr() const {
	switch (Encoder::GetDirection()) {
	case NONE:
		return "N/A";
	case LEFT:
		return "Left";
	case RIGHT:
		return "Right";
	default:
		return "Unknown Direction";
	}
}

signed char Encoder::Read() {
	static unsigned char oldState = 3;
	static signed char value = 0;

	oldState <<= 2;
	if (this->A->ReadState()) oldState |= 0x02;
	if (this->B->ReadState()) oldState |= 0x01;

	value += this->directionStates[(oldState & 0x0F)];

	if (value > 3) {
		this->direction = RIGHT;
		this->position = ((this->position + this->incrementAmount) >= (signed char)127) ? (signed char)127 : (this->position + this->incrementAmount);
		value = 0;
	}
	else if (value < -3) {
		this->direction = LEFT;
		this->position = ((this->position - this->incrementAmount) <= (signed char)-128) ? (signed char)-128 : (this->position - this->incrementAmount);
		value = 0;
	}

	return Encoder::GetPosition();
}

void Encoder::SetPosition(signed char position) {
	signed char oldPos = this->position;
	this->position = (position >= (signed char)127) ? (signed char)127 : position;
	this->position = (position <= (signed char)-128) ? (signed char)-128 : position;
	this->direction = (position > oldPos) ? RIGHT : this->direction;
	this->direction = (position < oldPos) ? LEFT : this->direction;
}

void Encoder::SetIncrementAmt(signed char value) {
	this->incrementAmount = (value >= (signed char)127) ? (signed char)127 : value;
}