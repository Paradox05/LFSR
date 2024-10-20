#ifndef LFSR_HPP
#define LFSR_HPP

#include <iostream>
#include <string>

#define BIT_CAP 32

class LFSR {
public:
  LFSR();

  LFSR(std::string initSeed, int tap);

  int step();

  int generate(int k);

  friend std::ostream &operator<<(std::ostream &out, const LFSR &mLFSR);

  int getTap() const;

  void setTap(int tap);

  const std::string &getInitialSeed() const;

  void setInitialSeed(const std::string &initSeed);

  const std::string &getRegister() const;

  int getRegisterSize() const;

  void setRegister(const std::string &reg);

  void setRegister(char c, int idx);

  void setTemp(const std::string &t);

  const std::string &getTemp() const;

  char xorGate();

private:
  LFSR &operator=(const LFSR &); // Prevent assignment

  int tap_;
  std::string initialSeed_;
  std::string fRegister_;
  std::string temp_;
};

#endif
