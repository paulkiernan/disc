#ifndef TRAFFICLIGHT_H_INCLUDED
#define TRAFFICLIGHT_H_INCLUDED

#include "Geometry.h"

class CTrafficLight: public CGeometry
{
    public:
        CTrafficLight(CDrawingFrame* frame);
        ~CTrafficLight();

    public:
        virtual void Continue();

    private:
        CDrawingFrame*              p_frame;
        static std::set<Coordinate> s_coords; 
        static bool                 s_stopped;
        static size_t               s_delay_until;

};

#endif