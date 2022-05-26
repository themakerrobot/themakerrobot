#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include "config.hpp"

//#define DBG 
int fd;

int motor_pos[10] = {0, };
int motor_offset[10] = {0, };
int motor_range[10] = MOTOR_RANGE_VAL;

void showHelp()
{
  printf("\t%-65s\n\n",  "servo help");
  printf("\t%-65s\n\n",  "servo version");
  printf("\t%-65s\n\n",  "servo init");
  printf("\t%-65s\n\n",  "servo move pos0<-900~900> pos1<-900~900> ... duration<0~...>");
  printf("\t%-65s\n\n",  "servo mwrite pos0<-900~900> pos1<-900~900> ...");
  printf("\t%-65s\n\n",  "servo write channel<0~9> value<-900~900>");
  printf("\t%-65s\n\n",  "servo speed (channel<0~9> value<0-255>|all <0-255> <0-255> ...)");
  printf("\t%-65s\n\n",  "servo acceleration (channel<0~9> value<0-255>|all <0-255> <0-255> ...)");
  printf("\t%-65s\n\n",  "servo profile init");
  printf("\t%-65s\n\n",  "servo profile offset set 1 2 3 4 5 6 7 8 9 10");
  printf("\t%-65s\n\n",  "servo profile offset get");
  printf("\t%-65s\n\n",  "servo profile pos get");
  printf("\tFor Example:\n\n");
  printf("\t\tservo write 0 0\n\n");
}

// For motor calibration
int
get_motor_profile(int o, int p)
{
  FILE *fp;
  if(o && (fp = fopen(OFFSET_PATH, "r")))
  {
    fscanf(fp, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
      &motor_offset[0], &motor_offset[1], &motor_offset[2], &motor_offset[3], &motor_offset[4],
      &motor_offset[5], &motor_offset[6], &motor_offset[7], &motor_offset[8], &motor_offset[9]);
    fclose(fp);
  }

  if(p && (fp = fopen(POS_PATH, "r")))
  {
    fscanf(fp, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
      &motor_pos[0], &motor_pos[1], &motor_pos[2], &motor_pos[3], &motor_pos[4],
      &motor_pos[5], &motor_pos[6], &motor_pos[7], &motor_pos[8], &motor_pos[9]);
    fclose(fp);
  }
  return 0;
}

int
set_motor_profile(int o, int p)
{
  FILE * fp;
  if(o && (fp = fopen(OFFSET_PATH, "w")))
  {
    fprintf(fp, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
      motor_offset[0], motor_offset[1], motor_offset[2], motor_offset[3], motor_offset[4],
      motor_offset[5], motor_offset[6], motor_offset[7], motor_offset[8], motor_offset[9]);
    fclose(fp);
  }
  
  if(p && (fp = fopen(POS_PATH, "w")))
  {
    fprintf(fp, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
      motor_pos[0], motor_pos[1], motor_pos[2], motor_pos[3], motor_pos[4],
      motor_pos[5], motor_pos[6], motor_pos[7], motor_pos[8], motor_pos[9]);
    fclose(fp);
  }
  return 0;
}

int
set_interface_attribs (int fd, int speed, int parity)
{
  struct termios tty;
  memset (&tty, 0, sizeof tty);
  if (tcgetattr (fd, &tty) != 0)
  {
    printf ("error %d from tcgetattr", errno);
    return -1;
  }

  cfsetospeed (&tty, speed);
  cfsetispeed (&tty, speed);

  tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
  // disable IGNBRK for mismatched speed tests; otherwise receive break
  // as \000 chars
  tty.c_iflag &= ~IGNBRK;         // disable break processing
  tty.c_lflag = 0;                // no signaling chars, no echo,
  // no canonical processing
  tty.c_oflag = 0;                // no remapping, no delays
  tty.c_cc[VMIN]  = 0;            // read doesn't block
  tty.c_cc[VTIME] = 1;            // 0.5 seconds read timeout

  tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl
  tty.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,
  // enable reading
  tty.c_cflag &= ~(PARENB | PARODD);      // shut off parity
  tty.c_cflag |= parity;
  tty.c_cflag &= ~CSTOPB;
  tty.c_cflag &= ~CRTSCTS;
  if (tcsetattr (fd, TCSANOW, &tty) != 0)
  {
    printf ("error %d from tcsetattr", errno);
    return -1;
  }
  return 0;
}

void
set_blocking (int fd, int should_block)
{
  struct termios tty;
  memset (&tty, 0, sizeof tty);
  if (tcgetattr (fd, &tty) != 0)
  {
    printf ("error %d from tggetattr", errno);
    return;
  }

  tty.c_cc[VMIN]  = should_block ? 1 : 0;
  tty.c_cc[VTIME] = 1;            // 0.5 seconds read timeout

  if (tcsetattr (fd, TCSANOW, &tty) != 0)
    printf ("error %d setting term attributes", errno);
}

int devOpen(){
  FILE * fp;
  struct termios options;
  int ret = 0;

  // Config
  if(access(OFFSET_PATH, R_OK) == -1){
    fp = fopen(OFFSET_PATH, "w");
    if(fp){
      fprintf(fp,"0,0,0,0,0,0,0,0,0,0");
      fclose(fp);
      ret = -1;
    }
  }
  if(access(POS_PATH, R_OK) == -1){
    fp = fopen(POS_PATH, "w");
    if(fp){
      fprintf(fp,"0,0,0,0,0,0,0,0,0,0");
      fclose(fp);
      ret = -1;
    }
  }

  fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY);
  if (fd == -1){
    printf("not opened ttyACM0\n");
    close(fd);
    ret = -1;
  }

  tcgetattr(fd, &options);
  options.c_iflag &= ~(INLCR | IGNCR | ICRNL | IXON | IXOFF);
  options.c_oflag &= ~(ONLCR | OCRNL);
  options.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
  tcsetattr(fd, TCSANOW, &options);
  set_interface_attribs (fd, BAUDRATE_VAL, 0);
  set_blocking (fd, 0);
  return ret;
}

int devClose(){
  close(fd);
  return 0;
}

int SetTarget(unsigned char channel, int value)
{
  if(value == motor_pos[channel]){
#ifdef DBG
    printf("Not change pos:%d\n", value);
#endif
    return 0;
  }
  else{
    motor_pos[channel] = value;
  }
  unsigned short target = (unsigned short)((motor_pos[channel] + motor_offset[channel] + 1500)*4);

  unsigned short max = (1500 + motor_range[channel]) * 4;
  unsigned short min = (1500 - motor_range[channel]) * 4;

  if(target > max){
    target = max;
    printf("Warn > Target value change to [%d]:%d\n", channel, motor_range[channel]);
  }
  if(target < min){
    target = min;
    printf("Warn > Target value change to [%d]:%d\n", channel, 0 - motor_range[channel]);
  }
#ifdef DBG
  printf ("Entering the SetTarget channel:%d target: %d\n", channel, target);
#endif
  if(target < 2560 || target > 9216) // 640 * 4 = 2560,  2304 * 4 = 9216
  {
    printf("Error > Target value should be 640-2304 microseconds, was: %d\n", target);
    return 0;
  }

  if(/*channel < 0 || */channel > 9){
    printf("Error > Channel value should be 0-9, was: %d\n", channel);
    return 0;
  }

  unsigned char command[] = {0x84, channel, (unsigned char)(target & 0x7F), (unsigned char)(target >> 7 & 0x7F)};
  if (write(fd, command, sizeof(command)) == -1)
  {
    printf("error writing");
    return -1;
  }
  return 0;
}

int SetMultiTarget(int* pTarget)
{
  for(int ch =0; ch < 10; ch++){
    if(pTarget[ch] != NS)
      motor_pos[ch] = pTarget[ch];
  }
#ifdef DBG
  printf("Entering the setMultiTarget\n");
#endif
  int idx = 3;
  unsigned char command[23] = {0x9F,10,0,};

  for (int ch = 0;ch < 10;ch++)
  {
    unsigned short max = (1500 + motor_range[ch]) * 4;
    unsigned short min = (1500 - motor_range[ch]) * 4;
    unsigned short target = (unsigned short)((motor_pos[ch] + motor_offset[ch] + 1500)* 4);

    if(target > max){
      target = max;
      printf("Warn > Target value change to [%d]:%d\n", ch, motor_range[ch]);
    }
    if(target < min){
      target = min;
      printf("Warn > Target value change to [%d]:%d\n", ch, 0 - motor_range[ch]);
    }

    command[idx++] = target & 0x7F;
    command[idx++] = target >> 7 & 0x7F;
  }

  if (write(fd, command, sizeof(command)) == -1)
  {
    printf("error writing");
    return -1;
  }
  return 0;
}

int SetSpeed(unsigned char channel, unsigned short speed)
{
#ifdef DBG
  printf ("Entering the SetSpeed channel:%d speed: %d\n", channel, speed);
#endif
  if (/*speed < 0 || */speed > 255)
  {
    printf("Error > speed value should be 0-255, was:%d\n", speed);
    return 0;
  }

  if(/*channel < 0 || */channel > 9){
    printf("Error > Channel value should be 0-9, was: %d\n", channel);
    return 0;
  }

  unsigned char command[] = {0x87, channel, (unsigned char)(speed & 0x7F), (unsigned char)(speed >> 7 & 0x7F)};
  //usleep(5000);
  if (write(fd, command, sizeof(command)) == -1)
  {
    printf("error writing");
    return -1;
  }
  return 0;
}

int SetAcceleration(unsigned char channel, unsigned short value)
{
#ifdef DBG
  printf ("Entering the SetAcceleration channel:%d value: %d\n", channel, value);
#endif
  if (/*value < 0 || */value > 255)
  {
    printf("Error > Acceleration value should be 0-255, was:%d\n", value);
    return 0;
  }

  if(/*channel < 0 || */channel > 9){
    printf("Error > Channel value should be 0-9, was: %d\n", channel);
    return 0;
  }

  unsigned char command[] = {0x89, channel, (unsigned char)(value & 0x7F), (unsigned char)(value >> 7 & 0x7F)};
  //usleep(5000);
  if (write(fd, command, sizeof(command)) == -1)
  {
    printf("error writing");
    return -1;
  }
  return 0;
}

int ServoInit()
{
  unsigned char command[] = {0xA2};
  if (write(fd, command, sizeof(command)) == -1)
  {
    printf("error writing");
    return -1;
  }
  return 0;
}

int ErrCommand(int argc, char* argv[])
{
  printf(" ! No such command: ");
  for(int i=0;i<argc;i++) printf("%s ", argv[i]);
  printf("\n");
  return 0;
}

int SetMove_1011(int l, int r)
{
  int idx = 0;
  unsigned char command[7] = {0,};
  unsigned short target;

  command[idx++] = 0x9F;
  command[idx++] = 2;
  command[idx++] = 10;
  target = (unsigned short)((l + 1500)* 4);
  command[idx++] = target & 0x7F;
  command[idx++] = target >> 7 & 0x7F;
  target = (unsigned short)((r + 1500)* 4);
  command[idx++] = target & 0x7F;
  command[idx++] = target >> 7 & 0x7F;

  if (write(fd, command, sizeof(command)) == -1)
  {
    printf("error writing");
    return -1;
  }
  return 0;
}

const char * GetVersion()
{
  return SW_VERSION;
}
