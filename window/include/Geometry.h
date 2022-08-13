#ifndef GEOMETRY_H_INCLUDED
#define GEOMETRY_H_INCLUDED

#include "FastLED.h"

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <set>

class Geometry
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
        };

    public:
        Geometry(const char* name, const std::set<Coordinate>);
        virtual ~Geometry();

    public:
        const char*  GetName() const           { return m_name; }
        void         SetName(const char* name) { strcpy(m_name, name); }
        virtual void Continue();

    protected:
        char m_name[32] = {};
};

#endif