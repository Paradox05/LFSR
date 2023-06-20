#ifndef PS2B_LFSR_CLASS_H
#define PS2B_LFSR_CLASS_H
#include <iostream>
#include <string>
#define BIT_CAP 32

class LFSR {
public:
  LFSR();

  explicit LFSR(std::string initSeed, int tap);

  int step();

  int generate(int k);

  friend std::ostream &operator<<(std::ostream &out, const LFSR &mLFS R);

  int getTap() const;

  void setTap(int tap);

  std::string getInitialSeed() const;

  void setInitialSeed(std::string initSeed);

  std::string getRegister() const;

  int getRegisterSize() const;

  void setRegister(std::string reg);

  void setRegister(char c, int idx);

  void setTemp(std::string t);

  std::string getTemp() const;
  char xorGate();

private:
  LFSR &operator=(const LFSR &);
  int tap_;
  std::string initialSeed_;
  std::string fRegister_;
  std::string temp_;
};
#endif
