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
        // std::cout << "mouse_drag_event:" << std::endl;
        // std::cout << "\tp: " << p << "; " << "rel: " << rel << std::endl;
        // std::cout << "\tbutton: " << button << "; " << "modifiers: " << modifiers << std::endl;
    }
    return true;
}

bool ImageViewAreaSelect::mouse_button_event(const Vector2i &p, int button, bool down, int modifiers)
{
    if( modifiers == GLFW_MOD_CONTROL && button == GLFW_MOUSE_BUTTON_1 ){
        if( down ){
            m_select_in_progress = true;
            m_first_point = p;
        } else {
            m_select_in_progress = false;
            m_last_point = p;
            std::cout << "Selected area first: " << m_first_point << "; last: " << m_last_point << std::endl;
        }

        // std::cout << "mouse_button_event:" << std::endl;
        // std::cout << "\tp: " << p << "; " << std::endl;
        // std::cout << "\tbutton: " << button << " " << (down ? "DOWN" : "UP") << std::endl;
        // std::cout << "\tmodifiers: " << modifiers << std::endl;
    }

    return true;
}

bool ImageViewAreaSelect::mouse_motion_event(const Vector2i &p, const Vector2i &rel, int button, int modifiers)
{
    if( modifiers == GLFW_MOD_CONTROL ){

    }

    return true;
}

NAMESPACE_END(nanogui)
