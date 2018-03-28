#include <ModularDeviceBase.h>


ModularDeviceBase dev;

void setup()
{
  dev.setup();
  dev.startServer();
}

void loop()
{
  dev.update();
}
