#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"

extern Drive chassis;

// Your motors, sensors, etc. should go here.  Below are examples

inline pros::Motor intakeRoller(-7);
inline pros::Motor middleRoller(4);
inline pros::Motor highGoalRoller(6);

inline ez::Piston highGoalHood('A');
inline ez::Piston matchLoader('D');
inline ez::Piston descorerLeft('H');
inline ez::Piston descorerRight('C');
//2inline pros::Optical optical_sensor(3);

// inline pros::adi::DigitalIn limit_switch('A');