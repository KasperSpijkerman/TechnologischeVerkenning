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

//function mapInRange to scale numbers of an input range to an output range 
inline double mapInRange(double factor, double xLow, double xHigh, double yLow, double yHigh){ //dynamic function to calculate a point on y-axes
    double Output = (yLow * (xHigh - factor) + yHigh * (factor - xLow))/(xHigh - xLow);
    return Output;
}

// subclass OSC into a local class so we can provide our own callback
class LocalOSC : public OSC
{
  int realcallback(const char *path,const char *types,lo_arg **argv,int argc)
  {
  string msgpath=path;

    cout.precision(4);
    cout << "path: " << msgpath << endl;

  //GYRO
    if(!msgpath.compare("/ZIGSIM/1234/gyro")){
      float x = argv[0]->f; //variable for storing the x position of gyro
      float y = argv[1]->f; //variable for storing the y position of gyro
      float z = argv[2]->f; //variable for storing the z position of gyro

      cout << "x pos gyro: " << x << "\n" ;
      cout << "y pos gyro: " << y << "\n" ;
      cout << "z pos gyro: " << z << "\n" ;
      
    } // if gyro

  //ACCELERATION
    if(!msgpath.compare("/ZIGSIM/1234/accel")){
      float x = argv[0]->f; //variable for storing the x position of gyro
      float y = argv[1]->f; //variable for storing the y position of gyro
      float z = argv[2]->f; //variable for storing the z position of gyro
      float combinedXYZ = (x+y+z)/3;
      float combinedSpeed;
      float xSpeed;
      if(combinedXYZ < 0.015 && combinedXYZ > -0.015){ //smoothening for sending messages of the X, Y and Z combined 
        combinedSpeed = 0;
      } else {
        combinedSpeed = combinedXYZ;
      } 

      cout << "x pos accel: " << combinedSpeed << "\n" ;
      // cout << "y pos accel: " << y << "\n" ;
      // cout << "z pos accel: " << z << "\n" ;mak
    } // if accel

  //COMPASS
    if(!msgpath.compare("/ZIGSIM/1234/compass")){
      float compass = argv[0]->f; //variable for storing the x position of gyro
      float compassScaled = mapInRange(compass,0,360,0,100); //scaling 0-360 degrees to a value between 0-100 

      cout << "COMPASS: " << compassScaled << "\n" ;
    } // if compass

  //BLINK
    if(!msgpath.compare("/ZIGSIM/1234/faceeyeblinkleft")){
      //smoothen blink, if returns 1 the user blinks
      int blink;
      if(argv[0]->f > 0.5){
       blink = 1;
      }else{
        blink = 0;
      }; 
      cout << "BLINK: " << blink << "\n" ;
    } // if faceeyeblinkleft

  //SMILE
    if(!msgpath.compare("/ZIGSIM/1234/facemouthsmileleft")){
      //smoothen smile, if returns 1 the user smiles
      int smile;
      if(argv[0]->f > 0.3){
       smile = 1;
      }else{
        smile = 0;
      }; 
      cout << "SMILE: " << smile << "\n" ;
    } // if facemouthsmileleft

    return 0;
  } // realcallback()
};




int main()
{
int done = 0;
LocalOSC osc;
string serverport="7777";

  osc.init(serverport);
  osc.set_callback("/ZIGSIM/1234/gyro","fff");
  osc.set_callback("/ZIGSIM/1234/accel","fff");
  osc.set_callback("/ZIGSIM/1234/compass","ff");
  osc.set_callback("/ZIGSIM/1234/faceeyeblinkleft","f");
  osc.set_callback("/ZIGSIM/1234/facemouthsmileleft","f");
  osc.start();
  

  cout << "Listening on port " << serverport << endl;

  while (!done) 
  {
    usleep(1000);
  }

  return 0;
}

