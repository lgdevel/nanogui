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
    virtual bool mouse_motion_event(const Vector2i &p, const Vector2i &rel, int button, int modifiers) override;

private:
    Vector2i m_first_point;
    Vector2i m_last_point;
    bool m_select_in_progress{false};
};

NAMESPACE_END(nanogui)

#endif // IMAGEVIEW_AREASELECT_H
