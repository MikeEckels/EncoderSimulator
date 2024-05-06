//#include <thread>
#include <iostream>
#include "Encoder.h"

std::unique_ptr<Encoder> encoder{ new Encoder };

//Prototypes
void printResults();

int main() {
    encoder.get()->SetIncrementAmt(5);
    encoder.get()->SetPosition(50);

    while (true) {
        printResults();

        if (encoder.get()->GetShaftButton()->ReadState()) {
            encoder.get()->Reset();
        }
        //std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

void printResults() {
    std::cout << "APin: " << encoder.get()->GetAPin()->ReadState() << " ";
    std::cout << "BPin: " << encoder.get()->GetBPin()->ReadState() << " ";
    std::cout << "Button: " << encoder.get()->GetShaftButton()->ReadState() << " ";
    std::cout << "EncoderPos: " << (int)encoder.get()->Read() << " ";
    std::cout << "EncoderDir: " << encoder.get()->GetDirectionStr() << std::endl;
}
