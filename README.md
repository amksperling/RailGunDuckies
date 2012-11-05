# CS 559 Project 1: Rail Gun Duckies
### Adam Sperling and Jacob Hanshaw

## Required Program Features

- All required modes and features specified:

	- The duck and gun are drawn using GL Display Lists

	- Beauty Modes for the duck, gun an balloon
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

- The game saves its state if modes are switched

- The duck has personality:
	- We made a model that is better than the reference
	- The duck changes color each time it is fired.
	
- We used C++11 random distributions and random engines in order to generate the random positions for the balloons and the random colors for the duck. This is better than just using a c-style rand().
  
- We place many balloons at once (more than the minimun one at a time).
 
- Balloons use the alpha channel to become semi transparent
 
- The railgun has user adjustible power settings. The higher the power, the 
   farther the duck flies.
   
- The game can be paused at any time during play. 
 
- The lights can be turned on and off

- The game can be reset at any time by the user

- "Ghost Mode." (you just have to see it.)

- 3 levels of difficulty! (Easy, normal and hard)
   
- Extra keys implemented:
	- 'f' toggles fullscreen mode
	- 'p' toggles pause
	- 'l' toggles lights on and off
	- 'r' will reset the game
	- 'd' cycles difficulty level
	- 'g' toggles "Ghost Mode"
	- '[' lowers gun power
	- ']' raises gun power