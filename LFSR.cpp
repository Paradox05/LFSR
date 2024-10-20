#include "LFSR.hpp"
#include <stdexcept>
#include <string>
#include <bitset>

LFSR::LFSR() {}

LFSR::LFSR(std::string initSeed, int iniTap) {
    this->setInitialSeed(initSeed);
    this->setRegister(this->getInitialSeed());
    this->setTap(iniTap);
}

int LFSR::getTap() const {
    return this->tap_;
}

void LFSR::setTap(int tap) {
    if (tap < 0 || tap >= this->initialSeed_.size()) {
        throw std::invalid_argument("The tap must be between 0 and the size of the initial seed - 1.");
    }
    this->tap_ = tap;
}

const std::string &LFSR::getInitialSeed() const {
    return this->initialSeed_;
}

void LFSR::setTemp(const std::string &temp) {
    this->temp_ = temp;
}

const std::string &LFSR::getTemp() const {
    return this->temp_;
}

void LFSR::setInitialSeed(const std::string &initSeed) {
    if (initSeed.size() > BIT_CAP || initSeed.size() == 0) {
        throw std::invalid_argument("The string must be <= 32 bits and > 0.");
    }
    for (char c : initSeed) {
        if (c != '1' && c != '0') {
            throw std::invalid_argument("The initial seed must only contain binary digits.");
        }
    }
    this->initialSeed_ = initSeed;
}

void LFSR::setRegister(const std::string &fRegister) {
    this->fRegister_ = fRegister;
}

void LFSR::setRegister(char regChar, int idx) {
    std::string shiftedInput(1, regChar);
    this->fRegister_.replace(idx, 1, shiftedInput);
}

const std::string &LFSR::getRegister() const {
    return this->fRegister_;
}

int LFSR::getRegisterSize() const {
    return static_cast<int>(this->fRegister_.size());
}

char LFSR::xorGate() {
    char tapComp = this->getTemp()[(this->getRegisterSize() - 1) - this->getTap()];
    return ((tapComp == '0' && this->getTemp()[0] == '1') ||
            (tapComp == '1' && this->getTemp()[0] == '0')) ? '1' : '0';
}

int LFSR::step() {
    this->setTemp(this->getRegister());
    char xor_result = this->xorGate();

    for (int i = this->getRegisterSize() - 1; i > 0; i--) {
        this->setRegister(this->temp_[i - 1], i);
    }
    this->setRegister(xor_result, 0);

    return xor_result - '0';
}

int LFSR::generate(int k) {
    int s = 0;
    for (int i = 0; i < k; i++) {
        int bit = this->step();
        s = (s << 1) | bit;
    }
    return s;
}

std::ostream &operator<<(std::ostream &out, const LFSR &thisLFSR) {
    out << thisLFSR.getRegister();
    return out;
}
