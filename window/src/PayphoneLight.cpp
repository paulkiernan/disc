#include "PayphoneLight.h"
#include "Logging.h"
#include "ColorPalette.h"

std::set<CGeometry::Coordinate> CPayphoneLight::s_coords = {
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
uint8_t CPayphoneLight::s_flicker_count       = 0;
uint8_t CPayphoneLight::s_flickers_remaining  = 5;
bool    CPayphoneLight::s_flicker_high        = false;
size_t  CPayphoneLight::s_delay_until         = 0;

CPayphoneLight::CPayphoneLight(CFrame* frame)
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
    if (s_flickers_remaining > 0)
    {
        // flickerHigh starts low, so here we reset the color to the flicker
        // value when we're in an active flickermode
        if (!s_flicker_high)
        {
            Log.verboseln(
                "CPayphoneLight::Continue: flickering ON... remaining (%u), high (%u), count(%u)",
                s_flickers_remaining,
                s_flicker_high,
                s_flicker_count
            );
            for (auto itr = s_coords.begin(); itr != s_coords.end(); itr++){
                uint16_t index = p_frame->XYSafeInverted(itr->x, itr->y);
                p_frame->SetPixel(
                    index,
                    blend(
                        ColorPalette::White,
                        ColorPalette::PhoneLight,
                        200
                    )
                );
            }
            s_flicker_high = true;
            s_flicker_count++;
            s_delay_until = random(50, 100) + millis();
        }

        if (s_flicker_high && (millis() > s_delay_until))
        {
            size_t remaining = s_delay_until - millis();
            Log.verboseln(
                "CPayphoneLight::Continue: flickering OFF... remaining (%u), high (%u), count(%u), reminaing time (%u)",
                s_flickers_remaining,
                s_flicker_high,
                s_flicker_count,
                remaining
            );
            for (auto itr = s_coords.begin(); itr != s_coords.end(); itr++){
                uint16_t index = p_frame->XYSafeInverted(itr->x, itr->y);
                p_frame->SetPixel(
                    index,
                    blend(
                        ColorPalette::Black,
                        ColorPalette::DominantWindow,
                        200
                    )
                );
            }
            s_flicker_high = false;
            s_flicker_count++;
        }

        if (s_flicker_count == 2)
        {
            s_flickers_remaining--;
            s_flicker_count = 0;
        }
    }
    else
    {
        if (millis() > s_delay_until + 30000)
        {
            if (random(1000) < 5)
            {
                uint8_t num_flickers = random(3, 8);
                Log.verboseln("CPayphoneLight::Continue: Scheduling %u flickers", num_flickers);
                s_flickers_remaining = num_flickers;
            }
        }
        else
        {
            for (auto itr = s_coords.begin(); itr != s_coords.end(); itr++){
                uint16_t index = p_frame->XYSafeInverted(itr->x, itr->y);
                p_frame->SetPixel(
                    index,
                    blend(
                        ColorPalette::PhoneLight,
                        ColorPalette::DominantWindow,
                        150
                    )
                );
            }
        }
    }
}
