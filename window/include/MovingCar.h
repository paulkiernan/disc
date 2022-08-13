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
        static std::set<Coordinate> s_coords; 

    private:
        CFrame*              p_frame;
        size_t                      m_movement_rate;  
};

#endif