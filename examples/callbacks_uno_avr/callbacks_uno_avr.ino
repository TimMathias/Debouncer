#include <Debouncer.h>

int pin = 2;
int debounce_duration_ms = 50;

int rise_count = 0;
int fall_count = 0;

Debouncer debouncer(pin, debounce_duration_ms);

void onRise() { Serial.println("onRise"); }
void onFall() { Serial.println("onFall"); }

void setup()
{
    Serial.begin(115200);
    pinMode(pin, INPUT_PULLUP);

    delay(2000);

    // WARNING: for AVRs like Uno, only two callbacks can be added
    // add from lambda
    debouncer.subscribe(Debouncer::Edge::FALL, [](){
        Serial.print("fall : ");
        Serial.println(fall_count++);
    });
    // debouncer.subscribe(Debouncer::Edge::RISE, [](){
    //     Serial.print("rise : ");
    //     Serial.println(rise_count++);
    // });

    // also you can add callback like this
    // debouncer.subscribe(Debouncer::Edge::FALL, onFall);
    debouncer.subscribe(Debouncer::Edge::RISE, onRise);

    Serial.println("start");
}

void loop()
{
    debouncer.update();
}
