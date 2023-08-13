#ifndef FRAME_H_INCLUDED
#define FRAME_H_INCLUDED

#include <stddef.h>
#include <vector>

class CGeometry;

class CFrame
{
    public: // singleton
        static CFrame& Instance();
        CFrame(const size_t width, const size_t height, struct CRGB* leds);
        ~CFrame();

    public:
        void                    Continue();
        void                    Show();
        void                    FastLEDShow();
        void                    Delay(size_t ms);
        static size_t           Iteration()                         { return s_iteration; }
        size_t                  XY(size_t x, size_t y);
        size_t                  XYSafe(size_t x, size_t y);
        size_t                  XYSafeInverted(size_t x, size_t y);
        void                    SetPixel(size_t index, CRGB rgb);
        void                    AddGeometry(CGeometry* geom);
        std::vector<CGeometry*> GetGeometries()                     { return m_geometries; }
        size_t                  GetGridWidth()                      { return m_grid_width; }
        size_t                  GetGridHeight()                     { return m_grid_height; }

    private:
        size_t                  m_grid_width  = -1;
        size_t                  m_grid_height = -1;
        CRGB*                   p_leds;
        std::vector<CGeometry*> m_geometries;

    private:
        static size_t s_iteration;
};

#endif
