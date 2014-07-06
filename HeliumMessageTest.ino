#include <assert.h>
#include <helium.h>
#include <SPI.h>

typedef uint32_t Milliseconds;

// Period between sending messages
const Milliseconds period = 10;

HeliumModem* modem = 0;

void setup()
{
  modem = new HeliumModem();
}

void loop()
{
  static uint64_t sequenceNumber = 0;
  static Milliseconds deadline = millis() + period;
  
  assert(modem);
  
  Milliseconds now = millis();

  while(deadline - now < 0x7fffffff)
  {
    delay(deadline - now);
    now = millis();
  }

  DataPack message(4);
  message.appendU64(sequenceNumber);
  message.appendU32(now);
  message.appendU32(deadline);
  message.appendString("\n");
  modem->sendPack(&message);

  ++sequenceNumber;
  deadline += period;
}

