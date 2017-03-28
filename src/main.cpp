#include <Arduino.h>

#include <FastLED.h>
#include <Bounce2.h>

// defines
#define BUTTON 0
#define DATA_PIN 1
#define NUM_LEDS 1


// LEDS variables
CRGB leds[NUM_LEDS];
CRGB normalColor = CRGB::Yellow;
CRGB hotColor = CRGB::Red;
CRGB shotColor = normalColor;


// global brightness
const int brightness = 192;


// timer
unsigned long ledOnStart = 0;
const unsigned long leoOnDuration = 75;
unsigned long ledOffStart = 0;
const unsigned long leoOffDuration = 100;


// handle LED behaviour
bool ledOn = true;
int count = 0;
const int countMax = 30;
const int refresh = 3000;


// debouncing
Bounce debouncer = Bounce();
const int debouncerTimer = 10;


void blink();
void showOn();
void showOff();
void setAllLedColor(CRGB);


void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(brightness);
  pinMode(BUTTON, INPUT);
  debouncer.attach(BUTTON);
  debouncer.interval(debouncerTimer);
}

void loop() {
  debouncer.update();
  int value = debouncer.read();
  if (value == HIGH) {
    blink();
  } else {
    ledOn = true;
    showOff();
  }
  if (count > countMax - 3) {
    shotColor = hotColor;
  }
  if (count > countMax) {
    delay(refresh);
    count = 0;
    shotColor = normalColor;
  }
}

void blink() {
  if (ledOn) {
    showOn();
  } else {
    showOff();
  }
  if (millis() - ledOnStart > leoOnDuration and ledOn) {
    ledOn = false;
    ledOffStart = millis();
  }
  if (millis() - ledOffStart > leoOffDuration and !ledOn) {
    ledOn = true;
    ledOnStart = millis();
    count ++;
  }
}

void showOn() {
  setAllLedColor(shotColor);
}

void showOff() {
  setAllLedColor(CRGB::Black);
}

void setAllLedColor(CRGB color) {
  for (int led = 0; led < NUM_LEDS; led++) {
    leds[led] = color;
  }
  FastLED.show();
}
