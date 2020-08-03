#include "config.h"

#define BOUNCE_WITH_PROMPT_DETECTION
#include <Bounce2.h>

class MyButton {
  public:
    MyButton(unsigned char pin, unsigned int keyCode, unsigned int modifiers = 0)
      : pin(pin), keyCode(keyCode), modifiers(modifiers) {}

    virtual void setup() {
      this->button = Bounce();
      this->button.attach(this->pin, INPUT_PULLUP);
      this->button.interval(DEBOUNCE_INTERVAL);
    }

    virtual bool process(bool force) {
      this->button.update();
      if (this->button.fell() || (force && this->button.read() == LOW)) {
        Keyboard.set_modifier(this->modifiers);
        Keyboard.press(this->keyCode);
        return true;
      } else if (this->button.rose() || (force && this->button.read() == HIGH)) {
        Keyboard.set_modifier(0);
        Keyboard.release(this->keyCode);
        return true;
      } else {
        return false;
      }
    }

  protected:
    unsigned char pin;
    unsigned int keyCode;
    unsigned int modifiers;
    Bounce button;
};

MyButton *createButton(unsigned char pin, unsigned int keyCode, unsigned int modifiers) {
  return new MyButton(pin, keyCode, modifiers);
}

const int numButtons = sizeof(buttons) / sizeof(MyButton *);

void setupButtons() {
  for (int i = 0; i < numButtons; ++i) {
    buttons[i]->setup();
  }
}

void processButtons(bool force) {
  for (int i = 0; i < numButtons; ++i)
    buttons[i]->process(force);
}

void setup() {
  Serial.begin(9600);
  Serial.println(numButtons);
  Serial.println(sizeof(MyButton));

  // init the keyboard states
  setupButtons();
  processButtons(true);
}

void loop() {
  processButtons(false);
}
