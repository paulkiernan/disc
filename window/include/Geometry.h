#ifndef GEOMETRY_H_INCLUDED
#define GEOMETRY_H_INCLUDED

#include "DrawingFrame.h"

#include <FastLED.h>

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <set>
#include <tuple>

class CDrawingFrame;

class CGeometry
{
    public:
        struct Coordinate
        {
            float x = -1.0;
            float y = -1.0;

            Coordinate() {}

            Coordinate(const Coordinate& rhs) :
                Coordinate(rhs.x, rhs.y)
            {
            }

            Coordinate(float x_in, float y_in) :
                x(x_in),
                y(y_in)
            {
            }

            inline bool operator <(const Coordinate& that) const {
                return std::tie(this->x, this->y) < std::tie(that.x, that.y);
            }
        };


    public:
        CGeometry();
        CGeometry(CDrawingFrame* frame);
        virtual ~CGeometry();

    public:
        virtual void Continue();

    private:
        static std::set<Coordinate> coords; 
        CDrawingFrame* p_frame;

};

#endif