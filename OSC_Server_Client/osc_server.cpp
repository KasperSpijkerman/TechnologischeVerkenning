/**********************************************************************
*          Copyright (c) 2013, Hogeschool voor de Kunsten Utrecht
*                      Hilversum, the Netherlands
*                          All rights reserved
***********************************************************************
*  This program is free software: you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation, either version 3 of the License, or
*  (at your option) any later version.
*
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with this program.
*  If not, see <http://www.gnu.org/licenses/>.
***********************************************************************
*
*  File name     : osc_server.cpp
*  System name   : osc++ : Open Sound Control
* 
*  Description   : Demo program using C++ wrapper for liblo
*
*
*  Author        : Marc_G
*  E-mail        : marcg@dinkum.nl
*
**********************************************************************/

#include "osc.h"


// subclass OSC into a local class so we can provide our own callback
class GyroOSC : public OSC
{
  int realcallback(const char *path,const char *types,lo_arg **argv,int argc)
  {
  string msgpath=path;
    cout.precision(4);
    cout << "path: " << msgpath << endl;
    if(!msgpath.compare("/ZIGSIM/1234/gyro")){
      float x = argv[0]->f; //variable for storing the x position of gyro
      float y = argv[1]->f; //variable for storing the y position of gyro
      float z = argv[2]->f; //variable for storing the z position of gyro

      cout << "x pos gyro: " << x << "\n" ;
      cout << "y pos gyro: " << y << "\n" ;
      cout << "z pos gyro: " << z << "\n" ;
    } // if

    return 0;
  } // realcallback()
};

class AccelOSC : public OSC
{
  int realcallback(const char *path,const char *types,lo_arg **argv,int argc)
  {
  string msgpath=path;
    cout.precision(4);
    cout << "path: " << msgpath << endl;
    if(!msgpath.compare("/poop")){
      float x = argv[0]->f; //variable for storing the x position of gyro
      float y = argv[1]->f; //variable for storing the y position of gyro
      float z = argv[2]->f; //variable for storing the z position of gyro

      cout << "x pos accel: " << x << "\n" ;
      cout << "y pos accel: " << y << "\n" ;
      cout << "z pos accel: " << z << "\n" ;
    } // if

    return 0;
  } // realcallback()
};



int main()
{
int done = 0;
GyroOSC gyro;
AccelOSC accel;
string serverport="7777";

  gyro.init(serverport);
  gyro.set_callback("/ZIGSIM/1234/gyro","fff");
  gyro.start();
  
  accel.init(serverport);
  accel.set_callback("/poop","fff");
  accel.start();

  cout << "Listening on port " << serverport << endl;

  while (!done) 
  {
    usleep(1000);
  }

  return 0;
}

