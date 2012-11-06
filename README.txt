# CS 559 Project 1: Rail Gun Duckies
### Adam Sperling and Jacob Hanshaw

## Required Program Features

- All required modes and features specified:

	- The application should run forever (tested > 5 hours on).

	- The duck and gun are drawn using GL Display Lists

	- Beauty Modes for the duck, gun and balloon
		- All objects are properly lit with one white light.
		- All objects slowly rotate in order to be easily observed.
		

	- Manual and automated game modes
		- Three different camera modes: fixed, following, and first person
		- The duck does not render in first person mode
			
		- Railgun is controlled with the mouse, and the bottom of the screen is
		  equivalent to flat on the ground.
		
		- Game text is presented in an orthographic projection.
		
		- Balloon score is drawn above each balloon, and score accumulates as
		  balloons are hit.
		  
		- The game resets after 3 ducks have missed.
		
		- Ducks travel with ballistic trajectory.
		
	- Required Keys implemented:
		 - 'x' and Esc close the application
		 - 'w' toggles wireframe mode
		 - 'c' cycles through the camera modes
		 - 'f1' cycles through application modes
		 
## Bonus Features

- Full HD widescreen support for today's latest computers and displays

- The Balloons are drawn using vertex arrays

- The beauty modes are rendered inside a beautiful vertex array sky dome

- The game is played inside a beautiful and colorful world with gradient colors

- Fullscreen support

- The game remembers its state if modes are switched

- The duck has personality:
	- We made a model that is better than the reference
	- The duck changes color each time it is fired.
	
- We used C++11 random distributions and random engines in order to generate the random positions for the balloons and the random colors for the duck. This is better than just using a c-style rand().

- Extensive use of 'inline' functions help keep the code fast, but we're not sure if it really makes a difference. Let's assume it does.
  
- We place many balloons at once (more than the minimum of one at a time).
 
- Balloons use the alpha channel and blending to become semi transparent
 
- The railgun has user adjustible power settings. The higher the power, the farther the duck flies.
   
- The game can be paused at any time during play. 
 
- The lights can be turned on and off

- The game can be reset at any time by the user

- More information about the position of the gun is displayed on screen

- "Ghost Mode." (you just have to see it.)

- Automated mode actually makes a nice attempt to hit balloons. (The specification doesn't say whether automation requires hitting balloons or not!)

- 3 levels of difficulty!  Adjusting gun power is really helpful on hard mode.

- added a global camera to fully appreciate the world (control with arrow keys)

- even more camera modes: spectator modes that make watching automated mode more awesome.

- caps lock support (the program still works if caps lock is on and you don't realize it!)

- the balloons float up at different speeds and with increased value if the user turns on movement mode

- the amount of lives you have left is represented in the top left of the screen

- color of balloons reflects their value  

- there are different colors of clear color for use in ghost mode 

- balloons explode

- Extra keys implemented:
	- 'f' toggles fullscreen mode
	- 'p' toggles pause
	- 'l' toggles lights on and off'
	- 'm' turns on balloon movement
	- 'r' will reset the game
	- 'd' cycles difficulty level
	- 'g' toggles "Ghost Mode"
	- 't' cycles "Ghost Mode" colors
	- 'v' cycles between the spectator camera modes
	- '[' lowers gun power
	- ']' raises gun power
	- arrow keys: move global camera
	- clicking: fires railgun