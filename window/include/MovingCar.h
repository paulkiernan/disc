#ifndef MOVINGCAR_H_INCLUDED
#define MOVINGCAR_H_INCLUDED

#include "Geometry.h"

class CMovingCar: public CGeometry
{
    public:
        CMovingCar(CFrame* frame);
        ~CMovingCar();

    public:
        virtual void Continue();

    private:
        static constexpr uint8_t c_y_boundary_min = 4;
        static constexpr uint8_t c_y_boundary_max = 12;
        static constexpr uint8_t c_car_width      = 8;
        static constexpr uint8_t c_car_height     = 4;

    private:
        CFrame*              p_frame;
        std::set<Coordinate> m_coords; 
        size_t               m_movement_rate;  
        bool                 m_movement_direction;  
        size_t               m_min_x;  
        size_t               m_max_x;  
};

#endif