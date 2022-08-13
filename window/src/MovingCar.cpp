#include "MovingCar.h"
#include "Logging.h"
#include "ColorPalette.h"


CMovingCar::CMovingCar(CFrame* frame)
{
    Log.infoln("CMovingCar::CMovingCar: Initalizing Geometry");

    p_frame = frame;
    m_movement_rate = random(40, 80);
    m_movement_direction = random(0, 1);
    m_delay_until = millis() + random(1000, 5000);

    GeneratePlacement();
}

void CMovingCar::GeneratePlacement()
{
    // Generate bounded-random placement
    uint8_t starting_top_right_y = random(c_y_boundary_min, c_y_boundary_max);
    for (uint8_t y=starting_top_right_y; y<c_y_boundary_max; y++)
    {
        for (uint8_t x=0; x<(c_car_width+1); x++)
        {
            Log.verboseln("CMovingCar::GeneratePlacement: Placing car: (%u, %u)", x, y);
            m_coords.insert(Coordinate(x, y));
        }
    }
}

CMovingCar::~CMovingCar()
{
    Log.infoln("CMovingCar::CMovingCar: destroying");
}

void CMovingCar::Show()
{
    // Draw car position
    for (auto i = m_coords.begin(); i != m_coords.end(); i++)
    {
        if ((i->x < p_frame->GetGridWidth()) && (i->y < p_frame->GetGridHeight()))
        {
            uint16_t index = p_frame->XYSafeInverted(i->x, i->y);
            p_frame->SetPixel(
                index,
                ColorPalette::Black 
            );
        }
        else{
            m_coordinates_for_removal.insert(Coordinate(i->x, i->y));
        }
    }
}

void CMovingCar::Continue()
{
    size_t now = millis();

    // Remove any out-of-frame pixels
    if (m_coordinates_for_removal.size() > 0)
    {
        for (auto i = m_coordinates_for_removal.begin(); i != m_coordinates_for_removal.end(); i++){
            Log.verboseln("CMovingCar::Continue: Removing Coordinate: (x: %u, y: %u)", i->x, i->y);
            m_coords.erase(Coordinate(i->x, i->y));
        }
    }

    // Find boundaries of car
    m_max_x = 0;
    m_min_x = SIZE_MAX;
    for (auto i = m_coords.begin(); i != m_coords.end(); i++)
    {
        if (i->x > m_max_x)
        {
            m_max_x = i->x;
        }
        if (i->x < m_min_x)
        {
            m_min_x = i->x;
        }
    }

    // Advance if delay has been met
    if ((m_coords.size()) > 0 && (now > m_delay_until))
    {
        for (auto i = m_coords.begin(); i != m_coords.end(); i++)
        {
            if (i->x == m_min_x)
            {
                // Reset color
                p_frame->SetPixel(
                    p_frame->XYSafeInverted(i->x, i->y),
                    ColorPalette::DominantWindow
                );

                // Advance
                i->x += c_car_width;
            }
        }
        m_delay_until = now + m_movement_rate; 
    }

    if ((m_coords.size() == 0) && (now > m_delay_until))
    {
        GeneratePlacement();
    }

    Show();
}