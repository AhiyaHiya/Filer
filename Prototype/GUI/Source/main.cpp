#include <gtkmm.h>

class BasicWindow : public Gtk::Window
{
public:
  BasicWindow();
};

BasicWindow::BasicWindow()
{
  set_title("GUI Prototype");
  set_default_size(200, 200);
}

int main(int argc, char* argv[])
{
  auto app = Gtk::Application::create("com.jaimerios.prototype.gui");

  return app->make_window_and_run<BasicWindow>(argc, argv);
}