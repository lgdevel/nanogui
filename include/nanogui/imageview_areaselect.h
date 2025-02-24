#ifndef IMAGEVIEW_AREASELECT_H
#define IMAGEVIEW_AREASELECT_H

#include <nanogui/imageview.h>

NAMESPACE_BEGIN(nanogui)

class NANOGUI_EXPORT ImageViewAreaSelect : public ImageView {

    using ImageView::ImageView;

    // Widget implementation
    virtual bool mouse_drag_event(const Vector2i &p, const Vector2i &rel, int button, int modifiers) override;
};

NAMESPACE_END(nanogui)

#endif // IMAGEVIEW_AREASELECT_H
