#ifndef PAYPHONELIGHT_H_INCLUDED
#define PAYPHONELIGHT_H_INCLUDED

#include "Geometry.h"

class CPayphoneLight: public CGeometry
{
    public:
        CPayphoneLight(CDrawingFrame* frame);
        ~CPayphoneLight();

    public:
        virtual void Continue();

    private:
        CDrawingFrame*              p_frame;
        static std::set<Coordinate> s_coords; 
        static uint8_t              s_flickerCount; 
        static uint8_t              s_flickersRemaining; 
        static bool                 s_flickerHigh; 
        static size_t               s_delayUntil; 

};

#endif