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
    } else if( m_select_in_progress ) {
        m_rect_size = p - m_first_point;
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

void ImageViewAreaSelect::draw(NVGcontext *ctx)
{
    ImageView::draw(ctx);
    if( m_select_in_progress ){
        //std::cout << "draw..." << std::endl;

        nvgBeginPath(ctx);
        nvgStrokeWidth(ctx, 1.0f);
        nvgStrokeColor(ctx, Color(255.f, 0.f, 0.f, 1.0f) );
        nvgRect(ctx, m_first_point.x(), m_first_point.y(),
                     m_rect_size.x(), m_rect_size.y());
        nvgStroke(ctx);
    } else if( m_last_point.x() > 0 ){
        nvgBeginPath(ctx);
        nvgStrokeWidth(ctx, 1.0f);
        nvgStrokeColor(ctx, Color(255.f, 0.f, 0.f, 1.0f) );
        nvgRect(ctx, m_first_point.x(), m_first_point.y(),
                m_last_point.x() - m_first_point.x() , m_last_point.y() - m_first_point.y());
        nvgStroke(ctx);
    }
}

NAMESPACE_END(nanogui)
