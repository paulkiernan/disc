#ifndef GEOMETRY_H_INCLUDED
#define GEOMETRY_H_INCLUDED

#include "Frame.h"

#include <FastLED.h>

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <set>
#include <tuple>

class CFrame;

class CGeometry
{
    public:
        struct Coordinate
        {
            mutable int x = -1;
            mutable int y = -1;

            Coordinate() {}

            Coordinate(const Coordinate& rhs) :
                Coordinate(rhs.x, rhs.y)
            {
            }

            Coordinate(size_t x_in, size_t y_in) :
                x(x_in),
                y(y_in)
            {
            }

            inline bool operator <(const Coordinate& that) const {
                return std::tie(this->x, this->y) < std::tie(that.x, that.y);
            }

            inline bool operator ==(const Coordinate& that) const {
                return (this->x == that.x) && (this->x == that.x);
            }
        };


    public:
        CGeometry();
        CGeometry(CFrame* frame);
        virtual ~CGeometry();

    public:
        virtual void Continue();

    private:
        static std::set<Coordinate> coords; 
        CFrame* p_frame;

};

#endif