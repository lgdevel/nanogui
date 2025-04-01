#include <nanogui/imageview_areaselect.h>

//#include <nanogui/renderpass.h>
//#include <nanogui/shader.h>
//#include <nanogui/texture.h>
#include <nanogui/screen.h>
#include <nanogui/opengl.h>
//#include <nanogui_resources.h>

#include <iostream>
#include <algorithm>

NAMESPACE_BEGIN(nanogui)


bool ImageViewAreaSelect::mouse_drag_event(const Vector2i & p, const Vector2i &rel,
                                 int button, int modifiers) {
    if (!m_enabled || !m_image)
        return false;

    if( modifiers != GLFW_MOD_CONTROL ){ // moving image
        m_offset += rel * screen()->pixel_ratio();

        if( m_offset.x() > 1 ) m_offset.x() = 1;
        if( m_offset.y() > 1 ) m_offset.y() = 1;
        auto hor_limit = -m_image->size().x() + size().x() - 3;
        if( m_offset.x() < hor_limit ) m_offset.x() = hor_limit;
        auto ver_limit = -m_image->size().y() + size().y() - 3;
        if( m_offset.y() < ver_limit ) m_offset.y() = ver_limit;

        // std::cout << "m_image->size(): " << m_image->size() << std::endl;
        // std::cout << "size(): " << size() << std::endl;
        // std::cout << "m_offset: " << m_offset << std::endl;

        reset_selection();
    } else if( m_select_in_progress ) { // draw selection on image
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
            std::cout << "Point top-left: " << win_top_left() << "; bottom-right: " << win_bottom_right() << std::endl;
            std::cout << "scale(): " << scale() << std::endl;
        }

        // std::cout << "mouse_button_event:" << std::endl;
        // std::cout << "\tp: " << p << "; " << std::endl;
        // std::cout << "\tbutton: " << button << " " << (down ? "DOWN" : "UP") << std::endl;
        // std::cout << "\tmodifiers: " << modifiers << std::endl;
    } else if( button == GLFW_MOUSE_BUTTON_2 ){
        reset_selection();
    }

    return true;
}

void ImageViewAreaSelect::draw(NVGcontext *ctx)
{
    ImageView::draw(ctx);
    // auto rectColor = Color(255.f, 0.f, 0.f, 1.0f);
    if( m_select_in_progress ){
        //std::cout << "draw..." << std::endl;
        nvgBeginPath(ctx);
        nvgStrokeWidth(ctx, 1.0f);
        nvgStrokeColor(ctx, m_rectangle_color );
        nvgRect(ctx, m_first_point.x(), m_first_point.y(),
                     m_rect_size.x(), m_rect_size.y());
        nvgStroke(ctx);
    } else if( m_last_point.x() > 0 ){
        nvgBeginPath(ctx);
        nvgStrokeWidth(ctx, 1.0f);
        nvgStrokeColor(ctx, m_rectangle_color );
        nvgRect(ctx, m_first_point.x(), m_first_point.y(),
                m_last_point.x() - m_first_point.x() , m_last_point.y() - m_first_point.y());
        nvgStroke(ctx);
    }
}

void ImageViewAreaSelect::reset_selection()
{
    m_first_point = {0,0};
    m_last_point = {0,0};
    m_rect_size = {0,0};
    m_select_in_progress = false;
}

void ImageViewAreaSelect::set_color( Color c )
{
    m_rectangle_color = c;
}

Vector2i ImageViewAreaSelect::win_top_left() const
{
    return Vector2i( std::min(m_first_point.x(), m_last_point.x() ),
                     std::min(m_first_point.y(), m_last_point.y() ) );
}

Vector2i ImageViewAreaSelect::win_bottom_right() const
{
    return Vector2i( std::max(m_first_point.x(), m_last_point.x() ),
                     std::max(m_first_point.y(), m_last_point.y() ) );
}

NAMESPACE_END(nanogui)
