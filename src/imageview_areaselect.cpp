#include <nanogui/imageview_areaselect.h>

//#include <nanogui/renderpass.h>
//#include <nanogui/shader.h>
//#include <nanogui/texture.h>
#include <nanogui/screen.h>
#include <nanogui/opengl.h>
//#include <nanogui_resources.h>

#include <iostream>

NAMESPACE_BEGIN(nanogui)

bool ImageViewAreaSelect::mouse_drag_event(const Vector2i & p, const Vector2i &rel,
                                 int button, int modifiers) {
    if (!m_enabled || !m_image)
        return false;

    if( modifiers != GLFW_MOD_CONTROL ){
        m_offset += rel * screen()->pixel_ratio();
    } else {
        std::cout << "mouse_drag_event:" << std::endl;
        std::cout << "\tp: " << p << "; " << "rel: " << rel << std::endl;
        std::cout << "\tbutton: " << button << "; " << "modifiers: " << modifiers << std::endl;
    }
    return true;
}

NAMESPACE_END(nanogui)
