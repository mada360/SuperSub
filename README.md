# SuperSub #

This is an example C++ application using the SDL library.
It tries to be as nicely C++11 as possible but do keep in
mind that SDL is written in C and, at some stage, you have
to interface with it.

## Story ##
The year is 2042 and you are the captain of the submersible vessel BAT-1337UMD more famously known
as THE ELITE! A submarine that has been on the fourfront of countless battles ending in victory.
An old enemy has arrisen however and the Nazis have returned from their base deep underground in the,
Kola superdeep borehole where they have been experimenting and building strength to rise up and strike.

In the great battle THE ELITE is transported back in time to 1942! as the Nazis fled, now is your
oportunity to wipe them from history!! But due to the flux capacitor being damaged in battle you have
limited power and so only have power to fire around 100 more times! So make every hit count!

**Good luck captain!!**


## Installation ##
You will have to have the SDL development libraries installed on
your system.  The easiest way to compile is to use a command-line
and run the included bash script by executing.
`$ ./bash.sh`
~~I would like to make a Makefile at some point~~ I have now added a Makefile, *It WILL show some errors
when ran, however, providing it doesn't return an error code it nothing to worry about.*
From the supersub root directory.


Alternatively running the following commands will have the same outcome.
`$ g++ -c src/Main.cpp`
`$ g++ -o supersub src/Main.o -lSDL -lSDL_image`

which will produce an executable file called "supersub" in the
top-level directory.  To execute this file do the following

`$ ./supersub`
 
from the top-level directory.  The game will expect to find the
`assets` directory under its current working directory.

## Credits ##
The sprites in this game come directly from 
[SpriteLib](http://www.widgetworx.com/widgetworx/portfolio/spritelib.html) and are used
under the terms of the [CPL 1.0](http://opensource.org/licenses/cpl1.0.php).


The event system is based on [Libsigc++](http://libsigc.sourceforge.net/)
and is used under the [LGPL](http://www.gnu.org/copyleft/lgpl.html).
