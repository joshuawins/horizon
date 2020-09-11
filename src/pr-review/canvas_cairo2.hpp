#pragma once
#include "canvas/canvas.hpp"
#include <cairomm/cairomm.h>

namespace horizon {
class CanvasCairo2 : public Canvas {
public:
    CanvasCairo2();
    void push() override
    {
    }
    void request_push() override
    {
    }
    Cairo::RefPtr<Cairo::Surface> get_surface()
    {
        return surface;
    }
    Cairo::RefPtr<Cairo::Surface> get_image_surface();

private:
    //  void img_polygon(const Polygon &poly, bool tr) override;
    void img_line(const Coordi &p0, const Coordi &p1, const uint64_t width, int layer, bool tr = true) override;

    cairo_surface_t *recording_surface;
    Cairo::RefPtr<Cairo::Surface> surface;
    Cairo::RefPtr<Cairo::Context> cr;
};
} // namespace horizon
