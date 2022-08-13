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
        static uint8_t              s_flicker_count; 
        static uint8_t              s_flickers_remaining; 
        static bool                 s_flicker_high; 
        static size_t               s_delay_until; 
};

#endif