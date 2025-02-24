#include <nanogui/opengl.h>
#include <nanogui/nanogui.h>

#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <memory>
#include <iostream>

namespace nanogui_app
{
using namespace nanogui;

class Application : public Screen {
public:
    Application();

private:
    using ImageHolder = std::unique_ptr<uint8_t[], void(*)(void*)>;

};

Application::Application()
    : Screen(Vector2i(1280, 1024), "NanoGUI Application")
{
    inc_ref();
    auto image_window = new Window( this, "My Image" );
    image_window->set_position( Vector2i(10, 10) );
    image_window->set_layout( new GroupLayout(3) );

    Vector2i size;
    int n = 0;
    ImageHolder texture_data(
        stbi_load( "img1.png", &size.x(), &size.y(), &n, 0),
        stbi_image_free );

    assert(n == 4);

    Texture *tex = new Texture(
        Texture::PixelFormat::RGBA,
        Texture::ComponentFormat::UInt8,
        size,
        Texture::InterpolationMode::Trilinear,
        Texture::InterpolationMode::Nearest );

    tex->upload(texture_data.get());
    ImageViewAreaSelect *image_view = new ImageViewAreaSelect(image_window);
    image_view->set_image( tex );
    image_view->set_size( Vector2i(1024, 768) );
    image_view->center();

    perform_layout();
}

}

int main()
{
    using std::cout, std::endl;
    using namespace nanogui;

    cout << "Area select" << endl;
    cout << "-----------" << endl;

    try {
        init();

        {
            nanogui::ref<nanogui_app::Application> app = new nanogui_app::Application();
            app->dec_ref();
            app->draw_all();
            app->set_visible(true);
            nanogui::mainloop(1 / 60.f * 1000);
        }

        nanogui::shutdown();
    } catch ( std::exception const& e ) {
        std::string error_msg = std::string("Caught a fatal error: ") + std::string(e.what());
        std::cerr << error_msg << std::endl;
        return -1;
    } catch (...) {
        std::cerr << "Caught an unknown error!" << std::endl;
    }

    return 0;
}
