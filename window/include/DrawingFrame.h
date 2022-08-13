#ifndef DRAWINGFRAME_H_INCLUDED
#define DRAWINGFRAME_H_INCLUDED

#include <stddef.h>

class CDrawingFrame
{
    public: // singleton
        static CDrawingFrame& Instance();
        CDrawingFrame(const size_t width, const size_t height, struct CRGB* leds);
        ~CDrawingFrame();

    public:
        void Continue();
        void Show();
        static size_t Iteration() { return s_iteration; }
        size_t XY(size_t x, size_t y);
        size_t XYSafe(size_t x, size_t y);

    private:
        size_t m_gridWidth  = -1; 
        size_t m_gridHeight = -1;
        CRGB*  p_ledarray;

    private:
        static size_t s_iteration;
};

#endif