#ifndef CHIPOTLE_H
#define CHIPOTLE_H
#include <gtkmm.h>
#include <vector>
#include <iostream>

extern int check;
extern int ship_type;
extern int randNum;

using namespace std;

class MainWindow:public Gtk::Window
{
    public:
    MainWindow();
    virtual        ~MainWindow();

    protected:
      void        Play();
      void        Tutorial();
      void        Exit();

    Gtk::Image image;
    Gtk::Button play_game,tutorial,exit;
    Gtk::Grid grid;


};

class ShipWindow:public Gtk::Window
{
public:
  ShipWindow();
  virtual     ~ShipWindow();

protected:
  void        Selected_Cruiser();
  void        Selected_Bulwark();
  void        Selected_Mining();

    Gtk::Image ship1,ship2,ship3;
    Gtk::Button button1,button2,button3;
    Gtk::Grid grid;
};

class TutorialWindow:public Gtk::Window
{
    public:
    TutorialWindow();
    virtual ~TutorialWindow();

    protected:
      Gtk::Image image;
      Gtk::Grid grid;
};

class PlayWindow:public Gtk::Window
{
public:
  PlayWindow();
  virtual     ~PlayWindow();

protected:
  void Combat_Status();
  void mineAsteroid();
  void deploySolar();
  void show_ship_status();

  Gtk::Grid grid;
  Gtk::Image ship1;
  Gtk::Button button2,button3,button4,button5;
};

class CombatWindow:public Gtk::Window
{
public:
  CombatWindow();
  virtual ~CombatWindow();
protected:
  void         Retreat();
  void         Attack();
  void         Divert_power_to_weapons();
  void         Divert_power_to_shields();
  void checkHealth();

  Gtk::Image   image;
  Gtk::Button  button1,button2,button3,button4;
  Gtk::Label   label1,label2,label3,label4,label5,label6;
  Gtk::Grid    grid;
};

class StatsWindow:public Gtk::Window
{

public:
  StatsWindow();
  virtual ~StatsWindow();

protected:
  Gtk::Image   image;
  Gtk::Label   label1,label2,label3,label4,label5,label6,label7,label8,label9,label10,label11,label12,label13,label14;
  Gtk::Grid    grid;
};
class EnemyStatsWindow:public Gtk::Window
{

public:
  EnemyStatsWindow();
  virtual ~EnemyStatsWindow();

protected:
  Gtk::Image   image;
  Gtk::Label   label1,label2,label3,label4,label5,label6,label7,label8,label9,label10,label11,label12,label13,label14;
  Gtk::Grid    grid;
};
#endif
