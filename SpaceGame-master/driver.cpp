#include "mainheader.h"
#include <gtkmm.h> 
#include <iostream>

int main(int argc, char * argv[]) {

    Gtk::Main app(argc, argv);
    MainWindow window;
    Gtk::Main::run(window);

    if (check == 1) {
        ShipWindow window2;
        Gtk::Main::run(window2);
    }

    while (true) {
        if (ship_type > 0) {
            PlayWindow window4;
            Gtk::Main::run(window4);

            CombatWindow window5;
            Gtk::Main::run(window5);

        }
    }

    return 0;
}
