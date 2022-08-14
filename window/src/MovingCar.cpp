#include "MovingCar.h"
#include "Logging.h"
#include "ColorPalette.h"

#include <limits.h> 

CMovingCar::CMovingCar(CFrame* frame)
{
    Log.infoln("CMovingCar::CMovingCar: Initalizing Geometry");
    p_frame = frame;
    GeneratePlacement();
}

void CMovingCar::GeneratePlacement()
{
    // Generate bounded-random placement
    uint8_t starting_top_right_y = random(c_y_boundary_min, c_y_boundary_max);
    for (int8_t y=starting_top_right_y; y<c_y_boundary_max; y++)
    {
        int x_start;
        int x_end;
        if (m_movement_direction) {
            x_start = -c_car_width;
            x_end   = 0;
        }
        else
        {
            x_start = p_frame->GetGridWidth();
            x_end   = p_frame->GetGridWidth() + c_car_width;
        }

        for (int8_t x=x_start; x<x_end; x++)
        {
            Log.verboseln("CMovingCar::GeneratePlacement: Placing car: (%i, %i)", x, y);
            m_coords.insert(Coordinate(x, y));
        }
    }

    m_is_entering        = true;
    m_delay_until        = millis() + random(1000, 5000);
    m_movement_direction = random(1, 100) > 50;
    m_movement_rate      = random(20, 60);
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
        if (
            ( (i->x > 0) && (i->x < (int)p_frame->GetGridWidth() )) && 
            ( (i->y > 0) && (i->y < (int)p_frame->GetGridHeight()))
        )
        {
            uint16_t index = p_frame->XYSafeInverted(i->x, i->y);
            p_frame->SetPixel(
                index,
                ColorPalette::Black 
            );
        }
        else {
            if (!m_is_entering)
            {
                m_coordinates_for_removal.insert(Coordinate(i->x, i->y));
            }
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
            Log.verboseln("CMovingCar::Continue: Removing Coordinate: (x: %i, y: %i)", i->x, i->y);
            m_coords.erase(Coordinate(i->x, i->y));
        }
        m_coordinates_for_removal.clear();
    }

    // Find boundaries of car
    m_max_x = INT_MIN;
    m_min_x = INT_MAX;
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

    // Car has fully entered the scene
    if (m_movement_direction && m_min_x > 0)
    {
        m_is_entering = false;
    }
    else if (!m_movement_direction && m_max_x < (int)p_frame->GetGridWidth())
    {
        m_is_entering = false;
    }

    // Advance
    if ((m_coords.size()) > 0 && (now > m_delay_until))
    {
        for (auto i = m_coords.begin(); i != m_coords.end(); i++)
        {
            if (
                ((i->x == m_min_x) && m_movement_direction) ||
                ((i->x == m_max_x) && !m_movement_direction)
            )
            {
                // Reset if in frame
                if (i->x > 0 && i->x < (int)p_frame->GetGridWidth())
                {
                    p_frame->SetPixel(
                        p_frame->XYSafeInverted(i->x, i->y),
                        ColorPalette::DominantWindow
                    );
                }

                // Advance
                if (m_movement_direction)
                {
                    i->x += c_car_width;
                }
                else
                {
                    i->x -= c_car_width;
                }
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