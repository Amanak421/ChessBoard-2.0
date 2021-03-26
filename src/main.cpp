#include <Arduino.h>

#include "motor_movement.h"

  int board[8][8] = {
      {2, 3, 4, 5, 6, 4, 3, 2},
      {1, 1, 1, 1, 1, 1, 1, 1},
      {0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0},
      {1, 1, 1, 1, 1, 1, 1, 1},
      {2, 3, 4, 5, 6, 4, 3, 2}
  };

MotorMovement motor_move;

String command = "";

void setup() {
  Serial.begin(9600);

  Serial.print("Probehlo...");

  motor_move.setBoard(board);   //nastaví původní šachovnici
  motor_move.printBoard();

  Serial.println("Zadejte command: ");

  motor_move.moveToEndstop(MOTOR_X, 1);
  motor_move.moveToEndstop(MOTOR_X, -1);
  motor_move.moveToEndstop(MOTOR_Y, 1);
  motor_move.moveToEndstop(MOTOR_Y, -1);

  

}

void loop() {
  // put your main code here, to run repeatedly:


  if(Serial.available() > 0){
    command = Serial.readString();
    String _com = command.substring(0, command.indexOf(' '));
    if(_com == "cpmb"){
      Serial.print("Parametr 1: ");
      String par1 = command.substring(command.indexOf(' ') + 1, command.indexOf(' ') + 3);
      Serial.println(par1);
      Serial.print("Parametr 2: ");
      String par2 = command.substring(command.length() - 2, command.length());
      Serial.println(par2);

      motor_move.printBoard();
      motor_move.computeCellMovement(par1.toInt(), par2.toInt());
      motor_move.printMoves();
      motor_move.printBoard();
    }else if(_com == "clm"){
      motor_move.clearMoves();
      Serial.println("Pohyby vymazany");
    }else if(_com ==  "mte"){
      String _motor = command.substring(command.indexOf(' ') + 1, command.indexOf(' ') + 2);
      String _dir = command.substring(command.length() - 2, command.length());
      int dir = _dir.toInt();
      if(_motor == "X"){
        Serial.print("Motor X");
        Serial.print("DIR: ");
        Serial.println(dir);
        motor_move.moveToEndstop(MOTOR_X, dir);
      }else if(_motor == "Y"){
        Serial.print("Motor Y");
        Serial.print("DIR: ");
        Serial.println(dir);
        motor_move.moveToEndstop(MOTOR_Y, dir);
      }else{
        Serial.println("Nezname parametry!");
      }
    }else if(_com == "mst"){
      String _state = command.substring(command.indexOf(' ') + 1, command.indexOf(' ') + 2);
      int st = _state.toInt();
      if(st == 1){
        motor_move.setMagnetState(ON);
      }else if(st == 0){
        motor_move.setMagnetState(OFF);
      }else{
        Serial.println("Nezname parametry!");
      }
    }
  }

}