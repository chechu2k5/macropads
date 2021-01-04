#include <Arduino.h>
#include <MacroPad.h>

using namespace MacroPad;

#if defined(RYANBATES_6KEY_2ROTARY_BOARD) || defined(RYANBATES_13KEY_2ROTARY_BOARD)

#include "RyanBates.h"

namespace Board = RyanBates;

#else

#error UNKNOWN BOARD TYPE: Select the board via platformio.ini > build_flags

#endif

MacroPad::MacroPad const macroPad;

void setup()
{
  Serial.begin(9600);
  macroPad.begin();
  Board::init();
}

void loop()
{
  Board::update(macroPad);

  delay(1);
}
