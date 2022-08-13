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
        static std::set<Coordinate> coords; 
        CDrawingFrame* p_frame;

};

#endif