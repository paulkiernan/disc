#include "MovingCar.h"
#include "Logging.h"
#include "ColorPalette.h"


CMovingCar::CMovingCar(CFrame* frame)
{
    Log.infoln("CMovingCar::CMovingCar: Initalizing Geometry");

    p_frame = frame;
    m_movement_rate = random(500, 2000);
    m_movement_direction = random(0, 1);

    // Generate bounded-random placement
    uint8_t starting_top_right_y = random(c_y_boundary_min, c_y_boundary_max);
    for (uint8_t y=starting_top_right_y; y<c_y_boundary_max; y++)
    {
        for (uint8_t x=0; x<(c_car_width+1); x++)
        {
            Log.traceln("Car coords (%u, %u)", x, y);
            m_coords.insert({x, y});
        }

    }
}

CMovingCar::~CMovingCar()
{
    Log.infoln("CMovingCar::CMovingCar: destroying");
}

void CMovingCar::Continue()
{
    // Draw car position
    for (auto i = m_coords.begin(); i != m_coords.end(); i++){
        uint16_t index = p_frame->XYSafeInverted(i->x, i->y);
        p_frame->SetPixel(
            index,
            ColorPalette::Black 
        );
    }

    for (auto i = m_coords.begin(); i != m_coords.end(); i++){
        if (i->x == m_min_x)
        {
            m_coords.erase({i->x, i->y});
            m_max_x = m_min_x + c_car_width + 1;
            if (m_max_x <= p_frame->GetGridWidth())
            {
                m_coords.insert({m_max_x, i->y});
            }
        }
    }

    for (auto i = m_coords.begin(); i != m_coords.end(); i++){
        if (i->x == m_min_x)
        {
            Log.info("x: %u, y %u", i->x, i->y);
        }
    }
}