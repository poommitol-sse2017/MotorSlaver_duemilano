#include <MeccanumWheel.h>

MeccanumWheel::MeccanumWheel()
{
    if (!_isInit)
    {
        _isInit = true;
        Motor MFL(MFL_EN, MFL_DIR);
        Motor MFR(MFR_EN, MFR_DIR);
        Motor MRL(MRL_EN, MRL_DIR);
        Motor MRR(MRR_EN, MRR_DIR);
    }
}