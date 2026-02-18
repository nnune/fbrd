#include "main.h"

/////
// For installation, upgrading, documentations, and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

// These are out of 127
const int DRIVE_SPEED = 127;
const int TURN_SPEED = 90;
const int SWING_SPEED = 110;

///
// Constants
///
void default_constants() {
  // P, I, D, and Start I
  chassis.pid_drive_constants_set(20, 0.0, 30.0);         // Fwd/rev constants, used for odom and non odom motions
  chassis.pid_heading_constants_set(11.0, 0.0, 20.0);        // Holds the robot straight while going forward without odom
  chassis.pid_turn_constants_set(3.0, 0.05, 20.0, 15.0);     // Turn in place constants
  chassis.pid_swing_constants_set(6.0, 0.0, 65.0);           // Swing constants
  chassis.pid_odom_angular_constants_set(6.5, 0.0, 52.5);    // Angular control for odom motions
  chassis.pid_odom_boomerang_constants_set(5.8, 0.0, 32.5);  // Angular control for boomerang motions

  // Exit conditions
  chassis.pid_turn_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_swing_exit_condition_set(90_ms, 3_deg, 225_ms, 7_deg, 400_ms, 500_ms);
  chassis.pid_drive_exit_condition_set(90_ms, 1_in, 250_ms, 3_in, 500_ms, 500_ms);
  chassis.pid_odom_turn_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 250_ms, 750_ms);
  chassis.pid_odom_drive_exit_condition_set(90_ms, 1_in, 250_ms, 3_in, 250_ms, 750_ms);

  chassis.pid_turn_chain_constant_set(3_deg);
  chassis.pid_swing_chain_constant_set(5_deg);
  chassis.pid_drive_chain_constant_set(3_in);

  // Slew constants
  chassis.slew_turn_constants_set(3_deg, 70);
  chassis.slew_drive_constants_set(3_in, 70);
  chassis.slew_swing_constants_set(3_in, 80);

  // The amount that turns are prioritized over driving in odom motions
  // - if you have tracking wheels, you can run this higher.  1.0 is the max
  chassis.odom_turn_bias_set(0.9);

  chassis.odom_look_ahead_set(7_in);           // This is how far ahead in the path the robot looks at
  chassis.odom_boomerang_distance_set(16_in);  // This sets the maximum distance away from target that the carrot point can be
  chassis.odom_boomerang_dlead_set(0.625);     // This handles how aggressive the end of boomerang motions are

  chassis.pid_angle_behavior_set(ez::shortest);  // Changes the default behavior for turning, this defaults it to the shortest path there
}

void intakeBalls() {
    intakeRoller.move(127);
    //basketRollerFront.move(127);
    //basketRollerBack.move(127);
}

void highGoal() {
    intakeRoller.move(127);
    //basketRollerFront.move(-127);
    //basketRollerBack.move(-127);
    highGoalRoller.move(127);
}

///
// Drive Example
///
void High_Goal_Only() {
  chassis.pid_drive_constants_set(25, 0.0, 30.0);
  highGoalHood.set(false);
 
  intakeRoller.move(-127);
  middleRoller.move(127);
  highGoalRoller.move(127);

  descorerLeft.set(true);
  descorerRight.set(true);

  chassis.pid_odom_set(12_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(30_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_odom_set(6.7_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(137.4_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_odom_set(15.2_in, 80, true);
  chassis.pid_wait();

  chassis.pid_turn_set(180_deg, TURN_SPEED);
  chassis.pid_wait();

  matchLoader.set(true);
  pros::delay(500);

  chassis.drive_brake_set(MOTOR_BRAKE_HOLD);

  chassis.pid_odom_set(12_in, 60, false);
  chassis.pid_wait();

  //chassis.pid_odom_set(-0.2_in, DRIVE_SPEED, true);
  //chassis.pid_wait();
  pros::delay(500);

  chassis.drive_brake_set(MOTOR_BRAKE_BRAKE);


  chassis.pid_odom_set(-20_in, 80, true);
  chassis.pid_wait();

  descorerLeft.set(false);
  descorerRight.set(false);

  highGoalHood.set(true);

  chassis.pid_odom_set(0.8_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  pros::delay(3000);

  chassis.pid_odom_set(5_in, DRIVE_SPEED, true);
  chassis.pid_wait();
 
  chassis.pid_turn_set(120_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_odom_set(-5.8_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(180_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_odom_set(-12_in,70, true);
  chassis.pid_wait();

}

void RightSide_High_Goal_Only() {
  High_Goal_Only();
}

void LeftSide_High_Goal_Only() {
  chassis.odom_x_flip();
  chassis.odom_theta_flip();
  High_Goal_Only();
}

///
// Turn Example
///
void MiddleHigh_Right() {
  chassis.pid_drive_constants_set(24, 0.0, 40);
  
  chassis.pid_odom_drive_exit_condition_set(90_ms, 1_in, 220_ms, 3_in, 220_ms, 750_ms);
  chassis.pid_turn_exit_condition_set(90_ms, 3_deg, 220_ms, 7_deg, 220_ms, 500_ms);

  //chassis.pid_odom_turn_exit_condition_set(90_ms, 3_deg, 225_ms, 7_deg, 350_ms, 750_ms);

  intakeRoller.move(-127);
  middleRoller.move(127);
  highGoalRoller.move(127);

  //matchLoader.set(true);
  chassis.pid_odom_set(-20.5_in, DRIVE_SPEED, false);
  chassis.pid_wait();

  matchLoader.set(true);
  chassis.pid_turn_set(-90_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.drive_brake_set(MOTOR_BRAKE_HOLD);

  chassis.pid_odom_set(12_in, 80, false);
  chassis.pid_wait();

  pros::delay(350);
  chassis.drive_brake_set(MOTOR_BRAKE_BRAKE);
  
  chassis.pid_odom_set(-18.65_in, 80, true);
  chassis.pid_wait();
 
  chassis.pid_odom_set(0.8_in, DRIVE_SPEED, false);
  chassis.pid_wait();

  matchLoader.set(false);
  highGoalHood.set(true);
  //matchLoader.set(false);

  pros::delay(1500);

  
  chassis.pid_turn_set(-90_deg, TURN_SPEED);
  chassis.pid_wait();

  //pros::delay(800);
  //chassis.pid_drive_constants_set(35, 0.0, 40);
  highGoalHood.set(false);

  chassis.pid_swing_set(ez::LEFT_SWING, 24_deg, 70, -127);
  chassis.pid_wait();

 
  chassis.pid_odom_set(5.5_in, 100, false);
  chassis.pid_wait();
  chassis.pid_odom_set(6_in, 100, false);
  matchLoader.set(true);
  chassis.pid_wait();
  
  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();
  matchLoader.set(false);
  //pros::delay(300);

  chassis.pid_odom_set(21.3_in, 127, false);
  chassis.pid_wait();
  chassis.pid_odom_set(2.2_in, 127, false);
  matchLoader.set(true);
  chassis.pid_wait();

  //chassis.pid_drive_constants_set(22, 0.0, 40);
  matchLoader.set(false);

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_odom_set(-7.5_in, 50, false);
  chassis.pid_wait();

  intakeRoller.move(-127);
  middleRoller.move(100);
  highGoalRoller.move(-50);

  pros::delay(1200);

  middleRoller.move(80);
  highGoalRoller.move(-50);
  pros::delay(100);
  chassis.pid_odom_set(-2_in, DRIVE_SPEED, true);
}
  

void Solo_Auto_WP(){
    
  chassis.pid_odom_drive_exit_condition_set(90_ms, 1_in, 220_ms, 3_in, 200_ms, 750_ms);
  chassis.pid_turn_exit_condition_set(90_ms, 3_deg, 220_ms, 7_deg, 220_ms, 500_ms);

  intakeRoller.move(-127);
  middleRoller.move(127);
  highGoalRoller.move(127);

  //matchLoader.set(true);
  chassis.pid_odom_set(-20.5_in, DRIVE_SPEED, false);
  chassis.pid_wait();

  matchLoader.set(true);
  chassis.pid_turn_set(-90_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.drive_brake_set(MOTOR_BRAKE_HOLD);

  chassis.pid_odom_set(13_in, 127, false);
  chassis.pid_wait();

  pros::delay(210);
  chassis.drive_brake_set(MOTOR_BRAKE_BRAKE);
  
  chassis.pid_odom_set(-18.65_in, 127, true);
  chassis.pid_wait();
 
  chassis.pid_odom_set(0.8_in, DRIVE_SPEED, false);
  chassis.pid_wait();

  matchLoader.set(false);
  highGoalHood.set(true);

  pros::delay(1000);

  
  chassis.pid_turn_set(-90_deg, TURN_SPEED);
  chassis.pid_wait();

  highGoalHood.set(false);

  chassis.pid_swing_set(ez::LEFT_SWING, 28_deg, 127, -60);
  chassis.pid_wait();

 
  chassis.pid_odom_set(7.5_in, 100, false);
  chassis.pid_wait();
  chassis.pid_odom_set(2_in, 100, false);
  //matchLoader.set(true);
  chassis.pid_wait();
  
  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();
  //matchLoader.set(false);

  chassis.pid_odom_set(20.95_in, 127, false);
  chassis.pid_wait();
  chassis.pid_odom_set(2.2_in, 127, false);
  matchLoader.set(true);
  chassis.pid_wait();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait();

  matchLoader.set(false);

  chassis.pid_odom_set(-10.25_in, 127 , false);
  chassis.pid_wait();

  intakeRoller.move(20);
  middleRoller.move(-20);
  highGoalRoller.move(-60);

  intakeRoller.move(60);
  middleRoller.move(60);
  highGoalRoller.move(-127);

  pros::delay(300);

  intakeRoller.move(-127);
  middleRoller.move(127);
  highGoalRoller.move(127);

  chassis.pid_odom_set(21_in, DRIVE_SPEED, false);
  chassis.pid_wait();

  chassis.pid_odom_set(-15_in, 127, true);
  chassis.pid_wait();
 
  chassis.pid_odom_set(0.8_in, DRIVE_SPEED, false);
  chassis.pid_wait();

  highGoalRoller.move(127);
  highGoalHood.set(true);

}

  
  void skills_auton() {
  chassis.pid_drive_constants_set(20, 0.0, 30);
  
  chassis.pid_odom_drive_exit_condition_set(90_ms, 1_in, 220_ms, 3_in, 220_ms, 750_ms);
  chassis.pid_turn_exit_condition_set(90_ms, 3_deg, 220_ms, 7_deg, 220_ms, 500_ms);

  //chassis.pid_odom_turn_exit_condition_set(90_ms, 3_deg, 225_ms, 7_deg, 350_ms, 750_ms);

  chassis.pid_drive_constants_set(25, 0.0, 30.0);
  highGoalHood.set(false);
 
  intakeRoller.move(-127);
  middleRoller.move(127);
  highGoalRoller.move(127);

  descorerLeft.set(true);
  descorerRight.set(true);

  chassis.pid_odom_set(12_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(30_deg, TURN_SPEED);
  chassis.pid_wait();

  

  chassis.pid_odom_set(6.7_in, 72, true);
  chassis.pid_wait();

 // matchLoader.set(true);

  // chassis.pid_odom_set(4.2_in, DRIVE_SPEED, true);
  //chassis.pid_wait();

  chassis.pid_turn_set(137.4_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_odom_set(15.8_in, 80, true);
  chassis.pid_wait();

  chassis.pid_turn_set(180_deg, TURN_SPEED);
  chassis.pid_wait();

  matchLoader.set(true);
  pros::delay(500);

  


  chassis.drive_brake_set(MOTOR_BRAKE_HOLD);

  chassis.pid_odom_set(12_in, 60, false);
  chassis.pid_wait();

  pros::delay(1300);

  chassis.pid_turn_set(180_deg, TURN_SPEED);
  chassis.pid_wait();

  
  chassis.pid_odom_set(-5_in, DRIVE_SPEED, true);
  chassis.pid_wait();
 
  chassis.pid_turn_set(120_deg, TURN_SPEED);
  chassis.pid_wait();

  matchLoader.set(false);
  pros::delay(250);
  
  chassis.pid_odom_set(-7_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(180_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_odom_set(-35_in,70, true);
  chassis.pid_wait();
  
  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_odom_set(7.75_in,70, true);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_odom_set(-11_in,70, true);
  chassis.pid_wait();

  highGoalHood.set(true);

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();


  intakeRoller.move(127);
  middleRoller.move(-127);
  highGoalRoller.move(-127);

  pros::delay(100);

  intakeRoller.move(-127);
  middleRoller.move(127);
  highGoalRoller.move(127);

  pros::delay(3000);

  highGoalHood.set(false);

  matchLoader.set(true);
  pros::delay(500);

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_odom_set(20_in,70, true);
  chassis.pid_wait();

  pros::delay(1000);

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_odom_set(-21.5_in,70, true);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  highGoalHood.set(true);

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();


  intakeRoller.move(127);
  middleRoller.move(-127);
  highGoalRoller.move(-127);

  pros::delay(100);

  intakeRoller.move(-127);
  middleRoller.move(127);
  highGoalRoller.move(127);

  pros::delay(3000);
  
  matchLoader.set(false);
  pros::delay(500);
  
  chassis.pid_odom_set(5_in,70, true);
  chassis.pid_wait();

  chassis.pid_turn_set(-90_deg, TURN_SPEED);
  chassis.pid_wait();

  highGoalHood.set(false);

  chassis.pid_odom_set(46_in, 90, true);
  chassis.pid_wait();

  matchLoader.set(true);
  pros::delay(500);

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  intakeRoller.move(-127);
  middleRoller.move(127);
  highGoalRoller.move(127);


  chassis.pid_odom_set(12.75_in,70, true);
  chassis.pid_wait();

  pros::delay(1300);

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  
  chassis.pid_odom_set(-5_in, DRIVE_SPEED, true);
  chassis.pid_wait();
 
  chassis.pid_turn_set(-60_deg, TURN_SPEED);
  chassis.pid_wait();

  matchLoader.set(false);
  pros::delay(250);
  
  chassis.pid_odom_set(-7_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_odom_set(-35_in,70, true);
  chassis.pid_wait();
  
  chassis.pid_turn_set(-135_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_odom_set(9_in,70, true);
  chassis.pid_wait();

  chassis.pid_turn_set(180_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_odom_set(-11_in,70, true);
  chassis.pid_wait();

  //chassis.pid_odom_set(5_in, 70, true);
  //chassis.pid_wait();

  // chassis.pid_odom_set(-6_in, 120, true);
  //chassis.pid_wait();

  highGoalHood.set(true);

  chassis.pid_turn_set(180_deg, TURN_SPEED);
  chassis.pid_wait();


  intakeRoller.move(127);
  middleRoller.move(-127);
  highGoalRoller.move(-127);

  pros::delay(100);

  intakeRoller.move(-127);
  middleRoller.move(127);
  highGoalRoller.move(127);

  pros::delay(3000);

  highGoalHood.set(false);

  matchLoader.set(true);
  pros::delay(500);

  chassis.pid_odom_set(20_in,70, true);
  chassis.pid_wait();

  pros::delay(1325);

  chassis.pid_turn_set(180_deg, TURN_SPEED);
  chassis.pid_wait();


  chassis.pid_odom_set(-21.5_in,70, true);
  chassis.pid_wait();

  highGoalHood.set(true);

  intakeRoller.move(127);
  middleRoller.move(-127);
  highGoalRoller.move(-127);

  pros::delay(100);

  intakeRoller.move(-127);
  middleRoller.move(127);
  highGoalRoller.move(127);

  pros::delay(3000);

  highGoalHood.set(false);

  chassis.pid_turn_set(180_deg, TURN_SPEED);
  chassis.pid_wait();

   chassis.pid_odom_set(5_in,70, true);
  chassis.pid_wait();

  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_odom_set(10_in, 127, true);
  chassis.pid_wait();

  chassis.pid_turn_set(180_deg, TURN_SPEED);
  chassis.pid_wait();

   chassis.pid_odom_set(20_in, 127, true);
  chassis.pid_wait();














}



  


  

