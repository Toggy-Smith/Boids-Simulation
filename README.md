# Strategy Behavioural Design Pattern Demo

## How can I run this program?

At the top of this page, there will be a series of tabs. Below that is another series of tabs which should list commits, branches, packages, releases, etc. Click on the release tab and then click on the .exe file there to download the demo.

## How was this program written?

This program was written in the C++ language and uses the Simple Fast Multimedia Library (SFML) to draw graphics.

## What is the point of this program?

This program implements Craig Reynold's boid simulation (www.red3d.com/cwr/boids/). The simulation consists of small creatures referred to as "boids". These boids have three "steering behaviours": separation, alignment and cohesion.

To quote the original page:
- "Separation: steer to avoid crowding local flockmates"
- "Alignment: steer toward the average heading of local flockmates"
- "Cohesion: steer to move toward the average position of local flockmates"

These behaviours collectively produce a phenomenon where boids appear to be flocking like fish or birds. The program demonstrates how complicated patterns can emerge from very simple rules.
