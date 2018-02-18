#ifndef MeccanumWheel_H
#define MeccanumWheel_H

#include <Motor.h>



#define TRIGGER RISING
#define CPR 12 // Faulhaber motor
#define DIR_INVERSE !
#define REDUCTION_RATIO 64

class MeccanumWheel
{
  public:
    MeccanumWheel();

  private:
    bool _isInit = false;
    Motor MFL(MFL_EN, MFL_DIR);
    Motor MFR(MFR_EN, MFR_DIR);
    Motor MRL(MRL_EN, MRL_DIR);
    Motor MRR(MRR_EN, MRR_DIR);
};

#endif