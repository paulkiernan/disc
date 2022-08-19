#include <Arduino.h>
#include <esp_pm.h>
#include <soc/rtc.h>
#include<string.h>

#include "Matrix.h"
#include "CompositeGraphics.h"
#include "Mesh.h"
#include "Image.h"
#include "CompositeOutput.h"

#include "dragon.h"
#include "BigSkull.h"
#include "theman.h"

#include "ArcadeFont.h"

//PAL MAX, half: 324x268 full: 648x536
//NTSC MAX, half: 324x224 full: 648x448
const int XRES = 250;
const int YRES = 200;

//Graphics using the defined resolution for the backbuffer and fixed buffer for triangles
CompositeGraphics graphics(XRES, YRES, 1337);

//Composite output using the desired mode (PAL/NTSC) and twice the resolution. 
//It will center the displayed image automatically
CompositeOutput composite(CompositeOutput::NTSC, XRES * 2, YRES * 2);

Mesh<CompositeGraphics> dragonModel(
  dragon::vertexCount,
  dragon::vertices,
  0,
  0,
  dragon::triangleCount,
  dragon::triangles,
  dragon::triangleNormals
);
Mesh<CompositeGraphics> bigSkullModel(
  bigskull::vertexCount,
  bigskull::vertices,
  0,
  0,
  bigskull::triangleCount,
  bigskull::triangles,
  bigskull::triangleNormals
);
Mesh<CompositeGraphics> theManModel(
  theman::vertexCount,
  theman::vertices,
  0,
  0,
  theman::triangleCount,
  theman::triangles,
  theman::triangleNormals
);

const int fontWidth = 20;
const int fontHeight = 20;
Font<CompositeGraphics> font(fontWidth, fontHeight, arcadefont::pixels);
const int numTexts = 10; 
char *messages[numTexts] = {
  "CURFEW:00:00",
  " LOADING...",
  "RADIATION:          HIGH",
  "WEATHER:           DUSTY",
  "POWER GRID:      OFFLINE",
  " MOOD: SEXY",
  "  TV: BAD",
  "KNEES: HURT",
  " YEAR: 1999",
  "CONNECTION:         LOST",
};

void compositeCore(void *data)
{
  while (true)
  {
    //just send the graphics frontbuffer whithout any interruption 
    composite.sendFrameHalfResolution(&graphics.frame);
  }
}

void setup()
{
  //highest clockspeed needed
  esp_pm_lock_handle_t powerManagementLock;
  esp_pm_lock_create(ESP_PM_CPU_FREQ_MAX, 0, "compositeCorePerformanceLock", &powerManagementLock);
  esp_pm_lock_acquire(powerManagementLock);
  
  composite.init();        //initializing DMA buffers and I2S
  graphics.init();         //initializing graphics double buffer
  graphics.setFont(font);  //select font

  //running composite output pinned to first core
  xTaskCreatePinnedToCore(compositeCore, "compositeCoreTask", 1024, NULL, 1, NULL, 0);
  //rendering the actual graphics in the main loop is done on second core by default
}

void drawDragon()
{
  static Matrix perspective = Matrix::translation(graphics.xres / 2, graphics.yres / 2, 0) 
    * Matrix::scaling(100 * composite.pixelAspect, 100, 100) 
    * Matrix::perspective(90, 1, 10);
  static float u = 0;
  u += 0.02;
  Matrix rotation = Matrix::rotation(-1.8 + sin(u * 0.3) * 0.2, 1, 0, 0) * Matrix::rotation(u, 0, 0, 1);
  Matrix m0 = perspective * Matrix::translation(0, 1, 6) * rotation * Matrix::scaling(8);
  dragonModel.transform(m0, rotation);  
  dragonModel.drawTriangles(graphics, 40);
  graphics.flush();
}

void drawBigSkull()
{
  static Matrix perspective = Matrix::translation(graphics.xres / 2, graphics.yres / 2, 0)
    * Matrix::scaling(100 * composite.pixelAspect, 100, 100)
    * Matrix::perspective(90, 1, 10);
  static float u = 0;
  static float v = 0;
  u += 0.02;
  v += 0.01;
  Matrix rotation = Matrix::rotation(u, 0, 1, 0) * Matrix::rotation(v, 1, 0, 0);
  Matrix m0 = perspective * Matrix::translation(0, 1.7 * 0, 7) * rotation * Matrix::scaling(6);
  bigSkullModel.transform(m0, rotation);  
  bigSkullModel.drawTriangles(graphics, 40);
  graphics.flush();
}

void drawTheMan()
{
  static Matrix perspective = Matrix::translation(graphics.xres / 2, graphics.yres / 2, 0)
    * Matrix::scaling(100 * composite.pixelAspect, 100, 100)
    * Matrix::perspective(90, 1, 10);
  static float u = 0;
  static float z = 1;
  static bool grow = true;
  u += 0.02;
  if (grow)
  {
    z += 0.02;
  }
  else
  {
    z -= 0.02;
  }
  if (z >= 10.0 || z <= 1.0)
  {
    grow = !grow;
  }
  Matrix rotation = Matrix::rotation(-1.8 + sin(u * 0.3) * 0.2, 1, 0, 0) * Matrix::rotation(u, 0, 0, 1);
  Matrix m0 = perspective * Matrix::translation(0, 1.7 * 0, 6) * rotation * Matrix::scaling(z);
  theManModel.transform(m0, rotation);  
  theManModel.drawTriangles(graphics, 40);
  graphics.flush();
}

void draw()
{
  static int lastMillis = 0;
  static int scene = 0;
  static int lastSceneSwitch = millis();
  static int textIndex = random(0, numTexts);

  int t = millis();
  int fps = 1000 / (t - lastMillis);
  lastMillis = t;

  graphics.begin(0);
  switch(scene % 4)
  {
    case 0:
    {
      drawTheMan();
      break;
    }
    case 1:
    {
      drawBigSkull();
      break;
    }
    case 2:
    {
      drawDragon();
      break;
    }
    case 3:
    {
      graphics.setCursor(40, 50);
      graphics.print("FUCK YOUR");
      graphics.setCursor(90, 70);
      graphics.print("BURN");
      break;
    }
  }
  graphics.setTextColor(25);
  char* msg = messages[textIndex];
  graphics.setCursor(1, YRES-(((((strlen(msg)-1)/12))*fontHeight)+2+fontHeight));
  graphics.print(msg);
  /*
  graphics.print("free memory: ");
  graphics.print((int)heap_caps_get_free_size(MALLOC_CAP_DEFAULT));
  graphics.print(" fps: ");
  graphics.print(fps, 10, 2);
  graphics.print(" triangles/s: ");
  graphics.print(fps * model.triangleCount);
  */
  graphics.end();

  // Rotate text and scene
  if (lastMillis - lastSceneSwitch > 60000)
  {
    scene++;
    lastSceneSwitch = lastMillis;
    textIndex = random(0, numTexts);
  }
}

void loop()
{
  draw();
}
