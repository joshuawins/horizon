#include "canvas_cairo2.hpp"

namespace horizon {
CanvasCairo2::CanvasCairo2()
    : recording_surface(cairo_recording_surface_create(CAIRO_CONTENT_COLOR_ALPHA, NULL)),
      surface(new Cairo::Surface(recording_surface)), cr(Cairo::Context::create(surface))
{
    img_mode = true;
    cr->scale(2e-5, -2e-5);
    cr->set_source_rgb(0, 0, 0);
    cr->set_line_cap(Cairo::LineCap::LINE_CAP_ROUND);
}
void CanvasCairo2::img_line(const Coordi &p0, const Coordi &p1, const uint64_t width, int layer, bool tr)
{
    Coordi q0 = p0;
    Coordi q1 = p1;

    if (tr) {
        q0 = transform.transform(p0);
        q1 = transform.transform(p1);
    }
    cr->move_to(q0.x, q0.y);
    cr->line_to(q1.x, q1.y);
    cr->set_line_width(0.1e6);
    cr->stroke();
}

Cairo::RefPtr<Cairo::Surface> CanvasCairo2::get_image_surface()
{
    double x0, y0, width, height;
    cairo_recording_surface_ink_extents(recording_surface, &x0, &y0, &width, &height);
    auto isurf = Cairo::ImageSurface::create(Cairo::Format::FORMAT_ARGB32, width, height);
    auto icr = Cairo::Context::create(isurf);
    icr->set_source(surface, -x0, -y0);
    icr->paint();
    return isurf;
}

} // namespace horizon
