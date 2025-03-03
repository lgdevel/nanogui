#ifndef IMAGEVIEW_AREASELECT_H
#define IMAGEVIEW_AREASELECT_H

#include <nanogui/imageview.h>

NAMESPACE_BEGIN(nanogui)

class NANOGUI_EXPORT ImageViewAreaSelect : public ImageView {
public:
    using ImageView::ImageView;

    // Widget implementation
    virtual bool mouse_drag_event(const Vector2i &p, const Vector2i &rel, int button, int modifiers) override;
    virtual bool mouse_button_event(const Vector2i &p, int button, bool down, int modifiers) override;
    virtual void draw(NVGcontext *ctx) override;
    void set_color( Color c );

private:
    Vector2i m_first_point{0,0};
    Vector2i m_last_point{0,0};
    Vector2i m_rect_size{0,0};
    bool m_select_in_progress{false};
    Color m_rectangle_color{ 255.f, 0.f, 0.f, 1.0f };

    void reset_selection();
};

NAMESPACE_END(nanogui)

#endif // IMAGEVIEW_AREASELECT_H
