#include <M5Stack.h>
#include "ma.png.h"
#include "sa.png.h"
#include "wa.png.h"
#include "da.png.h"

const int LEN = 120;
const int OFFSET = 20;

TFT_eSprite images[] = {
  TFT_eSprite(&M5.Lcd),
  TFT_eSprite(&M5.Lcd),
  TFT_eSprite(&M5.Lcd),
  TFT_eSprite(&M5.Lcd),
};

void setup() {
  M5.begin(true, false, true);
  
  M5.Power.begin();

  M5.Lcd.clear(WHITE);

  for (int i = 0; i < 4; i++) {
    images[i].createSprite(LEN, LEN);
  }
  images[0].pushImage(0, 0, LEN, LEN, ma);
  images[1].pushImage(0, 0, LEN, LEN, sa);
  images[2].pushImage(0, 0, LEN, LEN, wa);
  images[3].pushImage(0, 0, LEN, LEN, da);
}

int frame = 0;

// phase: 0 to 4
int phase = 0;

void loop() {
  M5.update();
  frame++;

  // render characters
  if (phase <= 0) randomSprite().pushSprite(OFFSET, 0);
  if (phase <= 1) randomSprite().pushSprite(M5.Lcd.width()/2 + OFFSET, 0);
  if (phase <= 2) randomSprite().pushSprite(OFFSET, M5.Lcd.height()/2);
  if (phase <= 3) randomSprite().pushSprite(M5.Lcd.width()/2 + OFFSET, M5.Lcd.height()/2);

  // handle button press
  if (M5.BtnA.wasPressed() || M5.BtnB.wasPressed() || M5.BtnC.wasPressed()) {
    phase++;
    phase %= 5;
    M5.Speaker.tone(frame * 10, 80);
    if (phase == 0) {
      frame = 0;
    }
  }

  yield();
}

TFT_eSprite randomSprite()
{
  return images[random(4)];
}
