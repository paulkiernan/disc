#include "MovingCar.h"
#include "Logging.h"
#include "ColorPalette.h"

std::set<CGeometry::Coordinate> CMovingCar::s_coords = {
    {20,  9}, {21,  9}, {22,  9}, {23,  9},
    {20, 10}, {21, 10}, {22, 10}, {23, 10},
    {20, 11}, {21, 11}, {22, 11}, {23, 11},
};

CMovingCar::CMovingCar(CFrame* frame)
{
    Log.infoln("CMovingCar::CMovingCar: Initalizing Geometry");
    p_frame = frame;
    m_movement_rate = random(500, 2000);
}

CMovingCar::~CMovingCar()
{
    Log.infoln("CMovingCar::CMovingCar: destroying");
}

void CMovingCar::Continue()
{
    //Log.infoln("CMovingCar::Continue: car moving, rate(%u)", m_movement_rate);
    for (auto itr = s_coords.begin(); itr != s_coords.end(); itr++){
        uint16_t index = p_frame->XYSafeInverted(itr->x, itr->y);
        p_frame->SetPixel(
            index,
            ColorPalette::Black 
        );
    }
}