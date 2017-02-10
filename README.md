# Sumobot Jr.

Sumobot Jr. is an open source sumobot design made for [Nodebots Day](http://nodebotsday.com). Most existing sumo kits cost between $99 and $160. Since we're trying to keep our event costs down, I decided to try to design a bot that could be put together for around $50 including the cost of the Arduino. The name and design are inspired by the simplicity and zip-tied wooden beauty of the [Printrbot Jr](http://printrbot.com/).

<img src="https://github.com/makenai/sumobot-jr/raw/master/assets/sumobotjr.png">

## How ?

If you're planning on laser cutting the bots, you should use the OpenSCAD source file to generate a cutting plan for your specific type of laser cutter and material thickness. There's a wiki article for that!

[Laser Cutting with the OpenSCAD file](https://github.com/makenai/sumobot-jr/wiki/Working-with-the-OpenSCAD-file)

If you want to jump right into it, you can watch this instructional video, but note that you may not want to clip the wires if you plan to reuse the servos for something else:

[Sumobot Jr Assembly video for Nodebots Day 7/27](http://www.youtube.com/watch?v=0Q3hrKUwxDM)

[Customizing Sumobot Jr with Suziam and cats](http://www.youtube.com/watch?v=BB0vihv9ylM)

[IKEA-style Assembly Instruction Card](http://makenai.github.io/sumobot-jr/sumobot-instructions.pdf)

[Microsoft's version for Build 2015 on Raspberry Pi + Windows 10](https://www.youtube.com/watch?v=aKCieb-Gf2g)

[Katie K's No Solder Guide](http://katiek2.github.io/sumobot-nosolder/)

[Frank Hunleth's Arduino Mini Shield](https://oshpark.com/shared_projects/TEsKZkdg)

[Norfolk.js's Shopping List](https://github.com/norfolkjs/general-info/wiki/Norfolk.js-SumoBot-Kits)

[Sidepart adaptors for MG-6-48 DC-Motors from ghtomcat](https://github.com/ghtomcat/sumobot)

The main part of the design is a cutting sheet in EPS file format that is designed to be used with a laser cutter. You can find it in the cutting_plans directory. If you don't have a laser cutter, you can use a CNC, tape your printout to balsa wood and go at it with an x-acto knife, or send it to a laser cutting service like [Ponoko](https://www.ponoko.com/) and get the sheet done for about $10.

There is also a directory called 3d_print that contains an STL file for a ball caster designed by [sliptonic](http://www.thingiverse.com/thing:13782) - the STL is set up for a 16mm ball bearing, but you can make one for other sizes with the included OpenSCAD file.

**NEW** Microsoft has created a tutorial and version of the bot kit for [Build 2015](http://www.buildwindows.com/). You can find their version of the cutting plan for Ponoko in this repository, and also check out their [tutorial using Raspberry Pi and Windows 10](http://microsoft.hackster.io/windowsiot/robot-kit).

There is a completely 3D printable version available at [Thingiverse](http://www.thingiverse.com/thing:357369) now.

[<img src="https://github.com/makenai/sumobot-jr/raw/master/assets/3dprintsumo.png">](http://www.thingiverse.com/thing:357369)

## What if I don't have a Laser Cutter / 3D Printer?!

Neither do I! The best way to get some help creating the parts is to look up your local [Hackerspace or Makerspace ](http://hackerspaces.org) and connect with them. Our Johannesburg makerspace called [Makerlabs](http://makerlabs.co.za) hosted at [Made In Workshop](http://madeinworkshop.co.za/)

[<img src="https://github.com/makenai/sumobot-jr/raw/master/assets/synshop.png">](http://synshop.org)

If you don't have a hackerspace nearby, you can also use a mail order service like [Ponoko](http://ponoko.com) that does both 3D printing and laser cutting.

## Other Parts Needed

+ [Arduino](https://www.robotics.org.za/arduino-boards-and-accessories.html/arduino-uno-r3.html) - R189
+ [4xAA battery holder](https://www.robotics.org.za/battery-holder-4xaa.html?search=battery%20holder) - R18
+ 2 Cable ties 4.7 x198mm works well Hellermann Tyton T50R - ?
+ 5 3.0 x 12mm wood screws Eureka - ?
+ Thick rubber bands [Croxley No 64] - ?
+ 2 continuous servo motors [Power AR-3606HB](https://www.robotics.org.za/servo-motors-1821899125/power-hd-continuous-rot-servo-6-7kg-cm.html) - R225
+ Some wire or leads
+ 16mm steel ball from a Bearing shop like BMG - ~R6

## No-solder Wiring Diagram (thanks @katiek2)

<img src=https://github.com/KatieK2/sumobot-nosolder/blob/gh-pages/sumobot.png width=500 />

That's about it! Connect the red and black leads on the servos together, then connect them to the + and - terminals on the battery holder respectively. Then connect the black leads and - terminal to the ground of the Arduino. Finally, the white leads of each motor go to pins 9 and 10 (or whatever you like) on the Arduino - you're done!

## Sample Code

To run the sample code for the Sumobot Jr., you will first need to install [Node.js](http://nodejs.org/) and [git](https://git-scm.com).

Open a terminal application and clone this repository:
```
git clone https://github.com/makenai/sumobot-jr
```

Navigate to the code folder:
```
cd code_examples/node
```

Install code dependencies:

```
npm i
```

Run the code:

```
node sumobot.js
```

## License

[Creative Commons - Attribution - ShareAlike 3.0](http://creativecommons.org/licenses/by-sa/3.0/)

You are free to:

+ to Share — to copy, distribute and transmit the work, and
+ to Remix — to adapt the work
+ Under the following conditions:
    + Attribution — You must attribute the work in the manner specified by the author or licensor (but not in any way that suggests that they endorse you or your use of the work)
    + Share Alike — If you alter, transform, or build upon this work, you may distribute the resulting work only under the same, similar or a compatible license.

With the understanding that:

+ Waiver — Any of the above conditions can be waived if you get permission from the copyright holder.
+ Other Rights — In no way are any of the following rights affected by the license:
    + your fair dealing or fair use rights;
    + the author's moral rights; and
    + rights other persons may have either in the work itself or in how the work is used, such as publicity or privacy rights.

## Credits

Made by

<img src="https://github.com/makenai/sumobot-jr/raw/master/assets/amalgamation.png">

Design by [@makenai](http://twitter.com/makenai) with feedback and ideas from [@noopkat](http://twitter.com/noopkat) aka (by their powers combined) Amalgamation of Cats.
