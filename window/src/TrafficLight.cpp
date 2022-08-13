#include "TrafficLight.h"
#include "Logging.h"

bool CTrafficLight::s_stopped = true;
size_t CTrafficLight::s_timeElapsed = 0;
std::set<CGeometry::Coordinate> CTrafficLight::s_coords = {
    {15,  1}, {16,  1}, {17,  1}, {18,  1}, {19,  1}, {20,  1},
    {15,  2}, {16,  2}, {17,  2}, {18,  2}, {19,  2}, {20,  2},
    {15,  3}, {16,  3}, {17,  3}, {18,  3}, {19,  3}, {20,  3},
    {15,  4}, {16,  4}, {17,  4}, {18,  4}, {19,  4}, {20,  4},
    {15,  5}, {16,  5}, {17,  5}, {18,  5}, {19,  5}, {20,  5},
    {15,  6}, {16,  6}, {17,  6}, {18,  6}, {19,  6}, {20,  6}
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
        p_frame->SetPixel(index, CRGB::Black);
    }
}