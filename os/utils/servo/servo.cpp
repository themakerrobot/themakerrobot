#include "servo.hpp"

int main(int argc, char* argv[])
{
  FILE * fp;
  int i;
  int channel, value;
  int pos, speed, accel;
  
  devOpen();
  // Command
  // servo move [servo0_pos] [servo1_pos] ... [servo9_pos] [move_time]
  if(strcmp(argv[1], "move_1011") == 0){
     int l = atoi(argv[2]);
     int r = atoi(argv[3]);
     SetMove_1011(l, r);
  }
  // servo move [servo0_pos] [servo1_pos] ... [servo9_pos] [move_time]
  else if(strcmp(argv[1], "move") == 0){
    int pPos[10] = {0,};

  // v` = (0.25us / 10ms) * v = 10degree / time(ms)
  // v = (10 / 0.25) * 10degree / (time(ms)+alpha) = 40 * 10degree / (time + alpha)
  // alpha = 10ms
  // v = 40 * 10degree/(time+10)

    float op = (float)40/(float)(atoi(argv[12])+10)*1.1;
    get_motor_profile(1,1);

    for(i = 0; i < 10;i++){
      pPos[i] = atoi(argv[i+2]);
      if(pPos[i] == NS || pPos[i] == motor_pos[i])continue;
      speed = abs(pPos[i]-motor_pos[i])*op;
      if(speed<4) speed=4;
      if(speed>50) speed=50;
      SetSpeed(i, speed);
      SetAcceleration(i, speed*0.8);
    }
    SetMultiTarget(pPos);
    set_motor_profile(0,1);
  }
  // servo mwrite [servo0_pos] [servo1_pos] ... [servo9_pos]
  else if(strcmp(argv[1], "mwrite") == 0){
    int pPos[10] = {0,};
    get_motor_profile(1,1);

    for(i = 0; i < 10;i++){
      pPos[i] = atoi(argv[i+2]);
    }
    SetMultiTarget(pPos);
    set_motor_profile(0,1);
  }
  // servo write [servo_number] [servo_pos]
  else if(strcmp(argv[1], "write") == 0){
    get_motor_profile(1,1);
    channel = atoi(argv[2]);
    pos = atoi(argv[3]);
    SetTarget(channel, pos);
    set_motor_profile(0,1);
  }
  // servo twrite [servo_number] [servo_speed] [server_accel] [servo_pos]
  else if(strcmp(argv[1], "twrite") == 0){
    get_motor_profile(1,1);
    channel = atoi(argv[2]);
    SetSpeed(channel, atoi(argv[3]));
    SetAcceleration(channel, atoi(argv[4]));
    pos = atoi(argv[5]);
    SetTarget(channel, pos);
    set_motor_profile(0,1);
  }
  // servo speed [servo_number] [servo_speed]
  // servo speed all [servo0_speed] [servo1_speed] ... [servo9_speed]
  else if(strcmp(argv[1], "speed") == 0){
    if(argv[2][0] == 'a') { // all
      for(i = 0; i < 10;i++)
      {
        speed = atoi(argv[i+3]);
        if(speed != NS){
          SetSpeed(i, speed);
        }
      }
    }
    else {
      channel = atoi(argv[2]);
      SetSpeed(channel, atoi(argv[3]));
    }
  }
  // servo accelerate [servo_number] [servo_accel]
  // servo accelerate all [servo0_accel] [servo1_accel] ... [servo9_accel]
  else if(strcmp(argv[1], "accelerate") == 0){
    if(argv[2][0] == 'a') { // all
      for(i = 0; i < 10;i++)
      {
        accel = atoi(argv[i+3]);
        if(accel != NS){
          SetAcceleration(i, accel);
        }
      }
    }
    else {
      channel = atoi(argv[2]);
      SetAcceleration(channel, atoi(argv[3]));
    }
  }
  // servo help
  else if(strcmp(argv[1], "help") == 0){
    showHelp();
  }
  // servo version
  else if(strcmp(argv[1], "version") == 0){
    printf("SW Version: %s\n", GetVersion());
  }
  // servo init
  else if(strcmp(argv[1], "init") == 0){
    for(i = 0; i < 10;i++)
    {
      SetSpeed(i, 30);
      SetAcceleration(i, 30);
    }
    //ServoInit();
    int pPos[10] = {0,0,-800,0,0,0,0,0,800,0};
    get_motor_profile(0,1);
    SetMultiTarget(pPos);
    set_motor_profile(0,1);
  }
  // servo profile
  else if(strcmp(argv[1], "profile") == 0){
    // servo profile init
    if(strcmp(argv[2], "init") == 0){
      if(fp = fopen(OFFSET_PATH, "w"))
      {
        fprintf(fp,"0,0,0,0,0,0,0,0,0,0");
        fclose(fp);
      }
      if(fp = fopen(POS_PATH, "w"))
      {
        fprintf(fp,"0,0,0,0,0,0,0,0,0,0");
        fclose(fp);
      }
    }
    // servo profile offset get
    // servo profile offset set [servo0_offset] [servo1_offset] ... [servo9_offset]
    else if(strcmp(argv[2], "offset") == 0){
      if(argv[3][0] == 'g'){ // get
        get_motor_profile(1,0);
        printf("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
          motor_offset[0], motor_offset[1], motor_offset[2], motor_offset[3], motor_offset[4],
          motor_offset[5], motor_offset[6], motor_offset[7], motor_offset[8], motor_offset[9]);
      }
      else if(argv[3][0] == 's'){ // set
        for(i = 0; i < 10; i++){
          motor_offset[i] = atoi(argv[i+4]);
        }
        set_motor_profile(1,0);
        printf("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
          motor_offset[0], motor_offset[1], motor_offset[2], motor_offset[3], motor_offset[4],
          motor_offset[5], motor_offset[6], motor_offset[7], motor_offset[8], motor_offset[9]);
      }
      else ErrCommand(argc, argv);
    }
    // servo profile pos get
    // servo profile pos set (not support)
    else if(strcmp(argv[2], "pos") == 0){
      if(argv[3][0] == 'g'){ // get
        get_motor_profile(0,1);
        printf("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
          motor_pos[0], motor_pos[1], motor_pos[2], motor_pos[3], motor_pos[4],
          motor_pos[5], motor_pos[6], motor_pos[7], motor_pos[8], motor_pos[9]);
      }
      else if(argv[3][0] == 's'){/* set */}
      else ErrCommand(argc, argv);
    }
  }
  else ErrCommand(argc, argv);

  devClose();
  return 0;
}

