#include "mainheader.h"
#include "ships.h"
#include <iostream>

int check = 0;
int ship_type = 0;
int randNum;

ships ship;
PirateKing enemy;
////////////////////////////////////////////////////////////////////////////////////
/* GUI Window to display the Main menu */
////////////////////////////////////////////////////////////////////////////////////

MainWindow::MainWindow() {
    this -> set_title("Main Menu");
    this -> set_border_width(5);
    image.set("menu.gif");
    grid.attach(image, 0, 0, 2, 1);

    play_game.add_label("Play Game");
    play_game.signal_pressed().connect(sigc::mem_fun( * this, & MainWindow::Play));
    grid.attach(play_game, 0, 1, 1, 1);

    tutorial.add_label("Tutorial");
    tutorial.signal_pressed().connect(sigc::mem_fun( * this, & MainWindow::Tutorial));
    grid.attach(tutorial, 1, 1, 1, 1);

    exit.add_label("Exit");
    exit.signal_pressed().connect(sigc::mem_fun( * this, & MainWindow::Exit));
    grid.attach(exit, 0, 2, 2, 1);

    grid.show_all();

    add(grid);
}

MainWindow::~MainWindow() {}

void MainWindow::Play() {
    //open shipwindow, closing main window
    check = 1;
    hide();
}

void MainWindow::Tutorial() {
    TutorialWindow window3;
    Gtk::Main::run(window3);
}

void MainWindow::Exit() {
    hide();
}

////////////////////////////////////////////////////////////////////////////////////
/* GUI Window to allow player to select their ship. */
////////////////////////////////////////////////////////////////////////////////////

//need to add labels next to each picture, detailing the ships status points.
ShipWindow::ShipWindow() {
    this -> set_title("Select Ship");
    this -> set_border_width(5);
    ship1.set("select_1.png");
    grid.attach(ship1, 0, 0, 2, 2);

    button1.add_label("Crusier");
    button1.signal_pressed().connect(sigc::mem_fun( * this, & ShipWindow::Selected_Cruiser));
    grid.attach(button1, 0, 3, 2, 2);

    ship2.set("select_2.png");
    grid.attach(ship2, 5, 0, 2, 2);

    button2.add_label("Bulwark");
    button2.signal_pressed().connect(sigc::mem_fun( * this, & ShipWindow::Selected_Bulwark));
    grid.attach(button2, 5, 3, 2, 2);

    ship3.set("select_3.png");
    grid.attach(ship3, 10, 0, 2, 2);

    button3.add_label("Mining");
    button3.signal_pressed().connect(sigc::mem_fun( * this, & ShipWindow::Selected_Mining));
    grid.attach(button3, 10, 3, 2, 2);

    grid.show_all();

    add(grid);
}

ShipWindow::~ShipWindow() {}

void ShipWindow::Selected_Cruiser() {
    ship_type = 1;
	cruiser temp;
	ship = temp;
    hide();
}

void ShipWindow::Selected_Bulwark() {
    ship_type = 2;
	bulwark temp;
	ship = temp;
    hide();
}

void ShipWindow::Selected_Mining() {
    ship_type = 3;
	mining temp;
	ship = temp;
    hide();
}

/////////////////////////////////////////////////////////////////////////////////////

/* GUI Window to display tutorial info */

////////////////////////////////////////////////////////////////////////////////////

TutorialWindow::TutorialWindow() {
    this -> set_title("Tutorial");
    image.set("tutorial.jpg");
    grid.attach(image,0 , 0, 1, 1);



        grid.show_all();

        add(grid);
}

TutorialWindow::~TutorialWindow() {}

////////////////////////////////////////////////////////////////////////////////////
/* GUI Window to display Play Window */
////////////////////////////////////////////////////////////////////////////////////

PlayWindow::PlayWindow() {
    this -> set_title("Main Control");
    this -> set_border_width(5);

    if (ship_type == 1) {
        ship1.set("background_1_moving.gif");
    } else if (ship_type == 2) {
        ship1.set("background_1_moving_2 (2).gif");
    } else if (ship_type == 3) {
        ship1.set("background_1_moving_3 (5).gif");
    }
    grid.attach(ship1, 0, 0, 4, 4);

    button2.add_label("Deploy solar panels");
    button2.signal_pressed().connect(sigc::mem_fun( * this, & PlayWindow::deploySolar));
    grid.attach(button2, 0, 4, 2, 2);

    button4.add_label("Mine asteroid");
    button4.signal_pressed().connect(sigc::mem_fun( * this, & PlayWindow::mineAsteroid));
    grid.attach(button4, 2, 4, 2, 2);

    button5.add_label("Ship Status");
    button5.signal_pressed().connect(sigc::mem_fun( * this, & PlayWindow::show_ship_status));
    grid.attach(button5, 0, 6, 4, 2);

    grid.show_all();

    add(grid);
}

PlayWindow::~PlayWindow() {}

void PlayWindow::mineAsteroid() {

  ship.mineAsteroid();

  float temp = ship.get_power_level();
  std::ostringstream sf;
  sf<<temp;
  std::string s1(sf.str());
    Gtk::MessageDialog dialog( * this, "Mining Asteroid", false, Gtk::MESSAGE_INFO);
    dialog.set_secondary_text("The power level is now: "+s1);
    dialog.run();

    if (ship_type == 1) {
        ship1.set("background_1_moving_astroid.gif");
    } else if (ship_type == 2) {
        ship1.set("background_2_moving_astroid.gif");
    } else if (ship_type == 3) {
        ship1.set("background_3_astroid.gif");
    }




	// 1/3 chance of combat
    randNum = rand() % (3);
    if (randNum == 1) {
		Gtk::MessageDialog dialog( * this, "Pirate King Attack", false, Gtk::MESSAGE_INFO);
		dialog.set_secondary_text("While mining, a pirate king attacks your ship.");
		dialog.run();
        hide();
    }
}

void PlayWindow::deploySolar() {
	ship.deploySolar();

	float temp = ship.get_power_level();

    std::ostringstream sf;
    sf << temp;
    std::string s1(sf.str());

    Gtk::MessageDialog dialog( * this, "Deploying solar panels", false, Gtk::MESSAGE_INFO);
    dialog.set_secondary_text("The power level is now: " + s1);
    dialog.run();

    if (ship_type == 1) {
        ship1.set("background_1_moving_solar_panel.gif");
    } else if (ship_type == 2) {
        ship1.set("background_1_moving_2_solar_panel.gif");
    } else if (ship_type == 3) {
        ship1.set("background_1_moving_3_solar_panel.gif");
    }



	// 1/4 chance of combat
    randNum = rand() % (4);
    if (randNum == 1) {
		Gtk::MessageDialog dialog( * this, "Pirate King Attack", false, Gtk::MESSAGE_INFO);
	    dialog.set_secondary_text("While charging your shields on solar energy, a pirate king attacks your ship.");
	    dialog.run();
        hide();
    }
}

void PlayWindow::show_ship_status() {
    StatsWindow window6;
    Gtk::Main::run(window6);
}

////////////////////////////////////////////////////////////////////////////////////
/* GUI Window to display Combat Info*/
////////////////////////////////////////////////////////////////////////////////////

/*
  Need to insert the combat logic in the below window.
*/

CombatWindow::CombatWindow() {
    this -> set_title("Under Attack");
    this -> set_border_width(5);
    if (ship_type == 1) {
        image.set("background_1_moving_enemy.gif");
        grid.attach(image, 0, 0, 4, 4);
    } else if (ship_type == 2) {
        image.set("background_1_moving_enemy_2.gif");
        grid.attach(image, 0, 0, 4, 4);
    } else if (ship_type == 3) {
        image.set("background_1_moving_enemy_3.gif");
        grid.attach(image, 0, 0, 4, 4);
    }

    button1.add_label("Attack");
    button1.signal_pressed().connect(sigc::mem_fun( * this, & CombatWindow::Attack));
    grid.attach(button1, 0, 4, 2, 2);

    button2.add_label("Retreat");
    button2.signal_pressed().connect(sigc::mem_fun( * this, & CombatWindow::Retreat));
    grid.attach(button2, 2, 4, 2, 2);

    button3.add_label("Divert power to Weapons");
    button3.signal_pressed().connect(sigc::mem_fun( * this, & CombatWindow::Divert_power_to_weapons));
    grid.attach(button3, 0, 6, 2, 2);

    button4.add_label("Divert power to shields");
    button4.signal_pressed().connect(sigc::mem_fun( * this, & CombatWindow::Divert_power_to_shields));
    grid.attach(button4, 2, 6, 2, 2);

    label1.set_text("Shield Strength");
    label2.set_text("Weapon Damage");
    label3.set_text("Ship Integrity");

    float temp1;
    float temp2;
    float temp3;

	temp1 = ship.get_shield_amount();
    temp2 = ship.get_attack();
    temp3 = ship.get_ship_integrity();


    std::ostringstream ss;
    ss << temp1;
    std::string s1(ss.str());

    std::ostringstream sd;
    sd << temp2;
    std::string s2(sd.str());

    std::ostringstream sf;
    sf << temp3;
    std::string s3(sf.str());

    //note, these will change based on the players actions.
    label4.set_text(s1);
    label5.set_text(s2);
    label6.set_text(s3);

    grid.attach(label1, 0, 8, 1, 1);
    grid.attach(label2, 1, 8, 2, 1);
    grid.attach(label3, 3, 8, 1, 1);

    grid.attach(label4, 0, 9, 1, 1);
    grid.attach(label5, 1, 9, 2, 1);
    grid.attach(label6, 3, 9, 1, 1);

    grid.show_all();

    add(grid);
}

CombatWindow::~CombatWindow() {}


//either we need to end the program if the user chooses this, or their ship is severly damaged.
void CombatWindow::Retreat() {

	Gtk::MessageDialog dialog( * this, "You Lose", false, Gtk::MESSAGE_INFO);
	dialog.set_secondary_text("Pirates dont allow retreats");
	dialog.run();
  exit(1);

}
void CombatWindow::Attack() {
	enemy.set_ship_integrity(enemy.get_ship_integrity() - ship.get_attack());

	enemy.runAi(ship);

    float temp1;
    float temp2;
    float temp3;

	temp1 = ship.get_shield_amount();
    temp2 = ship.get_attack();
    temp3 = ship.get_ship_integrity();

    std::ostringstream ss;
    ss << temp1;
    std::string s1(ss.str());

    std::ostringstream sd;
    sd << temp2;
    std::string s2(sd.str());

    std::ostringstream sf;
    sf << temp3;
    std::string s3(sf.str());

    //note, these will change based on the players actions.
    label4.set_text(s1);
    label5.set_text(s2);
    label6.set_text(s3);

	checkHealth();
}

void CombatWindow::Divert_power_to_shields() {
	if(ship.get_power_level() <= 10) {
		Gtk::MessageDialog dialog( * this, "Not enough power", false, Gtk::MESSAGE_INFO);
		dialog.set_secondary_text("Looks like you should have deployed those panels sooner");
		dialog.run();
	}
	else {
		ship.divertPowerToShields();
		Gtk::MessageDialog dialog( * this, "Shields are now 1.5x Strength", false, Gtk::MESSAGE_INFO);
		dialog.set_secondary_text("...");
		dialog.run();

		float temp1;

		temp1 = ship.get_shield_amount();

		std::ostringstream ss;
		ss << temp1;
		std::string s1(ss.str());

		label4.set_text(s1);
	}
}

void CombatWindow::Divert_power_to_weapons() {
	if(ship.get_power_level() <= 10) {
		Gtk::MessageDialog dialog( * this, "Not enough power", false, Gtk::MESSAGE_INFO);
		dialog.set_secondary_text("Looks like you should have deployed those panels sooner");
		dialog.run();
	}
	else {
		ship.divertPowerToWeapons();
		Gtk::MessageDialog dialog( * this, "Weapons are now 2x Strength", false, Gtk::MESSAGE_INFO);
		dialog.set_secondary_text("...");
		dialog.run();
		float temp1;

		temp1 = ship.get_attack();

		std::ostringstream ss;
		ss << temp1;
		std::string s1(ss.str());

		label5.set_text(s1);
	}
}

void CombatWindow::checkHealth(){
	if(ship.get_ship_integrity() <= 0) {
		Gtk::MessageDialog dialog( * this, "You Lose", false, Gtk::MESSAGE_INFO);
		dialog.set_secondary_text("Your ship was destroyed by pirates");
		dialog.run();
	}
	if (enemy.get_ship_integrity() <= 0) {
		Gtk::MessageDialog dialog( * this, "You WIn", false, Gtk::MESSAGE_INFO);
		dialog.set_secondary_text("You defeated the pirate king!");
		dialog.run();
    hide();
	}
	EnemyStatsWindow window6;
	Gtk::Main::run(window6);
}

////////////////////////////////////////////////////////////////////////////////////
/* GUI Window to display Ship status*/
////////////////////////////////////////////////////////////////////////////////////

StatsWindow::StatsWindow() {
    float temp1;
    float temp2;
    float temp3;
    float temp4;
    float temp5;

    temp1 = ship.get_attack();
    temp2 = ship.get_power_drain();
    temp3 = ship.get_ship_integrity();
    temp4 = ship.get_shield_capacity();
    temp5 = ship.get_shield_amount();

    this -> set_title("Ship Status");
    this -> set_border_width(5);

    label1.set_text("Ship Integrity");
    label2.set_text("Shield Capacity");
    label3.set_text("Attack Damage");
    label4.set_text("Shield Amount");
    label7.set_text("Power Drain");

    std::ostringstream ss;
    ss << temp1;
    std::string s1(ss.str());

    std::ostringstream sd;
    sd << temp2;
    std::string s2(sd.str());

    std::ostringstream sf;
    sf << temp3;
    std::string s3(sf.str());

    std::ostringstream sg;
    sg << temp4;
    std::string s4(sg.str());

    std::ostringstream sh;
    sh << temp5;
    std::string s5(sh.str());

    //put ship stats here.
    label8.set_text(s3);
    label9.set_text(s4);
    label10.set_text(s1);
    label11.set_text(s5);
    label14.set_text(s2);

    grid.attach(label1, 0, 0, 2, 1);
    grid.attach(label2, 0, 2, 2, 1);
    grid.attach(label3, 0, 4, 2, 1);
    grid.attach(label4, 0, 6, 2, 1);
    grid.attach(label7, 0, 8, 2, 1);
    grid.attach(label8, 2, 0, 2, 1);
    grid.attach(label9, 2, 2, 2, 1);
    grid.attach(label10, 2, 4, 2, 1);
    grid.attach(label11, 2, 6, 2, 1);
    grid.attach(label14, 2, 8, 2, 1);

    grid.show_all();

    add(grid);
}

StatsWindow::~StatsWindow() {}
////////////////////////////////////////////////////////////////////////////////////
/* GUI Window to display Enemy Ship status*/
////////////////////////////////////////////////////////////////////////////////////

EnemyStatsWindow::EnemyStatsWindow() {
    float temp1;
    float temp2;
    float temp3;
    float temp4;
    float temp5;

    temp1 = enemy.get_attack();
    temp2 = enemy.get_power_drain();
    temp3 = enemy.get_ship_integrity();
    temp4 = enemy.get_shield_capacity();
    temp5 = enemy.get_shield_amount();

    this -> set_title("ENEMY SHIP STATUS");
    this -> set_border_width(5);

    label1.set_text("Ship Integrity");
    label2.set_text("Shield Capacity");
    label3.set_text("Attack Damage");
    label4.set_text("Shield Amount");
    label7.set_text("Power Drain");

    std::ostringstream ss;
    ss << temp1;
    std::string s1(ss.str());

    std::ostringstream sd;
    sd << temp2;
    std::string s2(sd.str());

    std::ostringstream sf;
    sf << temp3;
    std::string s3(sf.str());

    std::ostringstream sg;
    sg << temp4;
    std::string s4(sg.str());

    std::ostringstream sh;
    sh << temp5;
    std::string s5(sh.str());

    //put ship stats here.
    label8.set_text(s3);
    label9.set_text(s4);
    label10.set_text(s1);
    label11.set_text(s5);
    label14.set_text(s2);

    grid.attach(label1, 0, 0, 2, 1);
    grid.attach(label2, 0, 2, 2, 1);
    grid.attach(label3, 0, 4, 2, 1);
    grid.attach(label4, 0, 6, 2, 1);
    grid.attach(label7, 0, 8, 2, 1);
    grid.attach(label8, 2, 0, 2, 1);
    grid.attach(label9, 2, 2, 2, 1);
    grid.attach(label10, 2, 4, 2, 1);
    grid.attach(label11, 2, 6, 2, 1);
    grid.attach(label14, 2, 8, 2, 1);

    grid.show_all();

    add(grid);
}

EnemyStatsWindow::~EnemyStatsWindow() {}
