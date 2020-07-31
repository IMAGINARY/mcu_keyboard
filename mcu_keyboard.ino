class MyButton;
/***
 * Creates a button with specific key code and modifiers assigned to a certain pin.
 * 
 * @param pin Use the pin number of your MCU (e.g. https://www.pjrc.com/teensy/pinout.html)
 * @param keyCode The key code, see https://www.pjrc.com/teensy/td_keyboard.html
 * @param modifiers The modifier code, see https://www.pjrc.com/teensy/td_keyboard.html
 ***/
MyButton* createButton(unsigned char pin, unsigned int keyCode, unsigned int modifiers = 0);

/* BEGIN CONFIG */
MyButton* buttons[] = {
  createButton(0, KEY_0),
  createButton(1, KEY_1),
  createButton(2, KEY_2),
  createButton(3, KEY_3),
  createButton(4, KEY_4),
  createButton(5, KEY_5),
  createButton(6, KEY_6),
  createButton(7, KEY_7),
  createButton(8, KEY_8),
  createButton(9, KEY_9),
  createButton(10, KEY_SPACE),
  createButton(11, KEY_ENTER),
  createButton(12, KEY_ESC),
  createButton(13, KEY_UP),
  createButton(14, KEY_LEFT),
  createButton(15, KEY_DOWN),
  createButton(16, KEY_RIGHT),
  createButton(17, KEY_W),
  createButton(18, KEY_A),
  createButton(19, KEY_S),
  createButton(20, KEY_D),
  createButton(21, KEY_I),
  createButton(22, KEY_J),
  createButton(23, KEY_K),
  createButton(24, KEY_L),
  createButton(25, KEY_TAB),
  createButton(26, KEY_TAB, MODIFIERKEY_SHIFT),
};

#define DEBOUNCE_INTERVAL 20 // milli seconds
/* END CONFIG */

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
