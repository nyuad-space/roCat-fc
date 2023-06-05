#include "buzzer.h"

Buzzer::Buzzer() : Task(TASK_IMMEDIATE, TASK_ONCE, &scheduler, false), pin(BUZZER)
{
    pinMode(pin, OUTPUT);
}

Buzzer::~Buzzer()
{}

void Buzzer::signal(uint16_t frequency, uint16_t duration)
{
    this->frequency = frequency;
    this->which_tone = SINGLE_TONE;
    this->setInterval(duration);
    this->restartDelayed();
}


/*SINGLE_TONE,
    ARMED_TONE,
    LAUNCHED_TONE,
    SUCCESS_TONE,
    FAIL_TONE*/
void Buzzer::signalArmed()
{}

void Buzzer::signalLaunched()
{}

void Buzzer::signalSuccess()
{}

void Buzzer::signalFail()
{}

bool Buzzer::Callback()
{}

bool Buzzer::Onenable()
{
    tone(this->pin, this->frequency);
    return true;
}

void Buzzer::OnDidable()
{
    noTone(this->pin);
    return;
}
