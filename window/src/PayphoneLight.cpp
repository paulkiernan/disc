#include "PayphoneLight.h"
#include "Logging.h"

std::set<CGeometry::Coordinate> CPayphoneLight::coords = {
    {0,  0}, {1,  0},
    {0,  1}, {1,  1}, {2,  1},
    {0,  2}, {1,  2}, {2,  2},
    {0,  3}, {1,  3}, {2,  3}, {3,  3},
    {0,  4}, {1,  4}, {2,  4}, {3,  4},
    {0,  5}, {1,  5}, {2,  5}, {3,  5}, {4,  5},
    {0,  6}, {1,  6}, {2,  6}, {3,  6}, {4,  6},
    {0,  7}, {1,  7}, {2,  7}, {3,  7}, {4,  7}, {5,  7},
    {0,  8}, {1,  8}, {2,  8}, {3,  8}, {4,  8}, {5,  8},
    {0,  9}, {1,  9}, {2,  9}, {3,  9}, {4,  9}, {5,  9}, {6,  9},
    {0, 10}, {1, 10}, {2, 10}, {3, 10}, {4, 10}, {5, 10}, {6, 10},
    {0, 11}, {1, 11}, {2, 11}, {3, 11}, {4, 11}, {5, 11}, {6, 11}, {7, 11}
};

CPayphoneLight::CPayphoneLight(CDrawingFrame* frame)
{
    Log.infoln("CPayphoneLight::CPayphoneLight: Initalizing Geometry");
    p_frame = frame;
}

CPayphoneLight::~CPayphoneLight()
{
    Log.infoln("CPayphoneLight::CPayphoneLight: destroying");
}

void CPayphoneLight::Continue()
{
    int number_flickers = random(2, 6);

    for (int i=0; i < number_flickers; i++) {

        for (auto itr = coords.begin(); itr != coords.end(); itr++){
            uint16_t index = p_frame->XYSafe(itr->x, itr->y);
            p_frame->SetPixel(index, CRGB::Black);
        }

        p_frame->FastLEDShow();
        int delay_ms = random(50, 100);
        p_frame->Delay(delay_ms);

        for (auto itr = coords.begin(); itr != coords.end(); itr++){
            uint16_t index = p_frame->XYSafe(itr->x, itr->y);
            p_frame->SetPixel(index, CRGB::White);
        }
        p_frame->FastLEDShow();
    }
}