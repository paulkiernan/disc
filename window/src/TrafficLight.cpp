#include "TrafficLight.h"
#include "Logging.h"
#include "ColorPalette.h"

std::set<CGeometry::Coordinate> CTrafficLight::s_coords = {
             {21, 0}, {22, 0}, {23, 0}, {24, 0}, {25, 0}, {26, 0},
    {20, 1}, {21, 1}, {22, 1}, {23, 1}, {24, 1}, {25, 1}, {26, 1},
                      {22, 2}, {23, 2}, {24, 2}, {25, 2}, {26, 2},
};
bool   CTrafficLight::s_stopped      = true;
size_t CTrafficLight::s_delay_until = 0;

CTrafficLight::CTrafficLight(CDrawingFrame* frame)
{
    Log.infoln("CTrafficLight::CTrafficLight: Initalizing Geometry");
    p_frame = frame;
}

CTrafficLight::~CTrafficLight()
{
    Log.infoln("CTrafficLight::CTrafficLight: destroying");
}

void CTrafficLight::Continue()
{
    size_t now = millis();

    if (s_stopped & (now > s_delay_until))
    {
        Log.verboseln("CTrafficLight::Continue: Switching stoplight to ON");
        for (auto itr = s_coords.begin(); itr != s_coords.end(); itr++){
            size_t index = p_frame->XYSafeInverted(itr->x, itr->y);
            p_frame->SetPixel(
                index, 
                blend(
                    ColorPalette::StopLightGo,
                    ColorPalette::DominantWindow,
                    120
                )
            );
        }
        s_stopped = false;
        s_delay_until = now + 60000;
    }

    if (!s_stopped & (millis() > s_delay_until))
    {
        Log.verboseln("CTrafficLight::Continue: Switching stoplight to OFF");
        for (auto itr = s_coords.begin(); itr != s_coords.end(); itr++){
            size_t index = p_frame->XYSafeInverted(itr->x, itr->y);
            p_frame->SetPixel(
                index, 
                blend(
                    ColorPalette::StopLightStop,
                    ColorPalette::DominantWindow,
                    120
                )
            );
        }
        s_stopped = true;
        s_delay_until = now + 60000;
    }
}