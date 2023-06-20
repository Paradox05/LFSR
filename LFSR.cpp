#include "LFSR.hpp"
#include <stdexcept>
#include <string>

LFSR::LFSR() {}

LFSR::LFSR(std::string initSeed, int iniTap) {
  // Set the seed initial seed
  this->setInitialSeed(initSeed);
  // Set the register
  this->setRegister(this->getInitialSeed());
  // Set the tap
  this->setTap(iniTap);
}
int LFSR::getTap() const {
  // Return the tap
  return this->tap_;
}
void LFSR::setTap(int tap) {
  // Set tap and make sure that the tap is greater than
  // the initial seed size - 1. Otherwise throws and exception.
  if (tap >= this->initialSeed_.size() - 1)
    throw std::invalid_argument("The tap must be less than the size "
                                "- 1 of the initial seed");
  this->tap_ = tap;
}
std::string LFSR::getInitialSeed() const {
  // Return the initial seed
  return this->initialSeed_;
}
void LFSR::setTemp(std::string temp) {
  // Set the temp variable
  this->temp_ = temp;
}
std::string LFSR::getTemp() const {
  // Return the temp variable
  return this->temp_;
}
void LFSR::setInitialSeed(std::string initSeed) {
  // Set the initial seed and make sure that the passed string is not
  // greater than 32 or equals to 0. Otherwise throws an invalid argument.
  if (initSeed.size() > BIT_CAP || initSeed.size() == 0) {
    throw std::invalid_argument("The string must bit <= 32 and > 0.");
  }
  for (int i = 0; i < initSeed.size(); i++)
    if (initSeed[i] == ’1’ || initSeed[i] == ’0’) {
      continue;
    } else {
      throw std::invalid_argument("The initial seed is not valid. Its 
                                  "
                                  "content must be binary digits.");
    }
  this->initialSeed_ = initSeed;
}
void LFSR::setRegister(std::string fRegister) {
  // Set the register
  this->fRegister_ = fRegister;
}
void LFSR::setRegister(char regChar, int idx) {
  // Create the string to be replace
  std::string shiftedInput(1, regChar);
  LFSR.cpp Tue Feb 26 1258 2019 2
      // Replace the above string by the given index
      this->fRegister_.replace(idx, 1, shiftedInput);
}
std::string LFSR::getRegister() const {
  // Return the register
  return this->fRegister_;
}
int LFSR::getRegisterSize() const {
  // Return the register size
  return static_cast<int>(this->fRegister_.size());
}
char LFSR::xorGate() {
  // Apply a xor gate to the register with the this->tap
  // TapComp is the bit to be compared
  char tapComp =
      this->getTemp()[(this->getRegisterSize() - 1) - this->getTap()];

  // Apply the logic of the xor gate
  if ((tapComp == ’0’ && this->getTemp()[0] == ’1’) ||
      (tapComp == ’1’ && this->getTemp()[0] == ’0’))
    return ’1’;
  else
    return ’0’;
}
int LFSR::step() {
  // Get the size of the register
  int registerSize = this->getRegisterSize() - 1;

  // Set temp to the current register
  this->setTemp(this->getRegister());

  // Apply the shift
  for (int i = registerSize; i > 0; i--)
    this->setRegister(this->temp_[i], i - 1);

  // Apply the xor gate to the register. See xorGate for details.
  this->setRegister(this->xorGate(), registerSize);

  // Return the bit at registerSize - 1.
  return this->getRegister().at(registerSize) - 48;
}
int LFSR::generate(int k) {
  // This function to the step k times and multiply
  // s by 2, and add the bit returned from step to it.
  int s = 0;
  for (int i = 0; i < k; i++) {
    int bit = this->step();
    s *= 2;
    s += bit;
  }
  // Return s
  return s;
}

std::ostream &operator<<(std::ostream &out, const LFSR &thisLFSR) {
  // This is the implementation of the << operator
  out << thisLFSR.getRegister();
  return out;
}
