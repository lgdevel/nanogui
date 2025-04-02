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
    Vector2i win_top_left() const;
    Vector2i win_bottom_right() const;
    Vector2i img_top_left() const;
    Vector2i img_bottom_right() const;

private:
    Vector2i m_first_point{0,0};
    Vector2i m_last_point{0,0};
    Vector2i m_rect_size{0,0};
    bool m_select_in_progress{false};
    Color m_rectangle_color{ 255.f, 0.f, 0.f, 1.0f };
    Vector2i const m_layout_offset{5,35};

    void reset_selection();
    Vector2i limit_selection_point( Vector2i const & p ) const;
    Vector2i layout_offset() const;
};

NAMESPACE_END(nanogui)

#endif // IMAGEVIEW_AREASELECT_H
