#define MFL_DIR 4
#define MFL_EN 3
#define MFL_ENC A1

#define MRL_DIR 12
#define MRL_EN 11
#define MRL_ENC A0

#define MFR_DIR 8
#define MFR_EN 9
#define MFR_ENC A4

#define MRR_DIR 7
#define MRR_EN 10
#define MRR_ENC A2

volatile uint8_t oldPort = 0x00;
volatile uint8_t pciMskPort = 0x00;

Motor wheelFL(MFL_EN,MFL_DIR,MFL_ENC,false);
Motor wheelFR(MFR_EN,MFR_DIR,MFR_DIR,true);
Motor wheelRL(MRL_EN,MRL_DIR,MRL_DIR,false);
Motor wheelRR(MRR_EN,MRR_DIR,MRR_DIR,true);


void setPWM31250()
{
    TCCR1B = (TCCR1B & 0xf8) | 0x01; // Pin9,Pin10 PWM 31250Hz
    TCCR2B = (TCCR2B & 0xf8) | 0x01; // Pin3,Pin11 PWM 31250Hz
}

void pciSetup(byte pin)
{
    *digitalPinToPCMSK(pin) |= bit(digitalPinToPCMSKbit(pin)); // enable pin;
    PCIFR |= bit(digitalPinToPCICRbit(pin));                   // clear any outstanding interrupt
    PCICR |= bit(digitalPinToPCICRbit(pin));                   // enable interrupt for the group
    pciMskPort |= bit(digitalPinToPCMSKbit(pin));
    oldPort = PINC & pciMskPort;
}

void initialization(){
    setPWM31250();
    pciSetup(A0);
    pciSetup(A1);
    pciSetup(A2);
    pciSetup(A4);
}

void clear_inc(){
    wheelRR.clear();
    wheelFL.clear();
    wheelRL.clear();
    wheelFR.clear();
}

ISR(PCINT1_vect) // handle pin change interrupt for A0 to A5 here
{
    uint8_t newPort = PINC & 0b00010111;
    uint8_t changedPort = newPort ^ oldPort;
    oldPort = newPort;
    if ((changedPort & 0b00000001)) //A0
        wheelRL.count();
    if ((changedPort & 0b00000010)) //A1
        wheelFL.count();
    if ((changedPort & 0b00000100)) //A2
        wheelRR.count();
    if ((changedPort & 0b00010000)) //A4
        wheelFR.count();
}