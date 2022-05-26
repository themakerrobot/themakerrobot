## Installation
sudo ./install.sh

## Check
 - baudrate : 9600, 19200, 38400, 57600, 115200(default)

## Command List
<pre><code>
  $ sudo servo help
  servo help
  servo version
  servo init
  servo move pos0<-900~900> pos1<-900~900> ... duration<0~...>
  servo mwrite pos0<-900~900> pos1<-900~900> ...
  servo write channel<0~9> value<-900~900>
  servo speed (channel<0~9> value<0-255>|all <0-255> <0-255> ...)
  servo acceleration (channel<0~9> value<0-255>|all <0-255> <0-255> ...)
  servo profile init
  servo profile offset set 1 2 3 4 5 6 7 8 9 10
  servo profile offset get
  servo profile pos get

  For Example:
    servo write 0 0
</code></pre>

