#include "TrafficLight.h"
#include "Logging.h"
#include "ColorPalette.h"

bool CTrafficLight::s_stopped = true;
size_t CTrafficLight::s_time_elapsed = 0;
std::set<CGeometry::Coordinate> CTrafficLight::s_coords = {
                      {22, 0}, {23, 0}, {24, 0}, {25, 0}, {26, 0},
             {21, 1}, {22, 1}, {23, 1}, {24, 1}, {25, 1}, {26, 1},
    {20, 2}, {21, 2}, {22, 2}, {23, 2}, {24, 2}, {25, 2}, {26, 2},
                               //{23, 3}, {24, 3}, {25, 3}, {26, 3},
};

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
    //Log.infoln("traffic light doing its thing");
    for (auto itr = s_coords.begin(); itr != s_coords.end(); itr++){
        uint16_t index = p_frame->XYSafeInverted(itr->x, itr->y);
        p_frame->SetPixel(
            index, 
            blend(
                ColorPalette::StopLightGoColor,
                ColorPalette::DominantWindowColor,
                100
            )
        );
    }
}