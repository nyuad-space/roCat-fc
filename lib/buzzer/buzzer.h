#ifndef BUZZER_H
#define BUZZER_H

#include <Arduino.h>
//Need to change (Swap with my taskschedular header)
#include <TaskScheduler.h>

enum tone_type
{
    SINGLE_TONE,
    ARMED_TONE,
    LAUNCHED_TONE,
    SUCCESS_TONE,
    FAIL_TONE
};

class Buzzer : public Task
{

    private:
    uint16_t pin;
    uint16_t frequency;
    tone_type which_tone;
    uint16_t tone_counter;

    public:
    Buzzer();
    ~Buzzer();

    void signal(uint16_t frequency, uint16_t duration);
    void singalTone();
    void signalArmed();
    void signalLaunched();
    void signalSuccess();
    void signalFail();

    bool Callback();
    bool Onenable();
    
    void OnDisable();
};

#endif