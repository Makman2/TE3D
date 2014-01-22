TE3D
A software-based 3D terminal engine.



### What you can do and what you can't do ###

You can...
-	present 3D-graphics.
-	also present 2D-graphics with the right settings (See documentation for this purpose).
-	just do a bit vector math and work with 3D-models.
-	everything that comes in your mind.

You can't...
-	Hm, there's nothin' you can't do with this stuff :)



### Installation guide ###

LINUX
	1.	Download this project archive and extract it.

	2.	Open the terminal and switch into the extracted folder.

	3.	Run these three commands:
		make build
		sudo make install

	4.	You did it!



### How-to-use guide ###

Just include <TE3D.h> in your C-files.
For a detailed list of available functions and examples, see the documentation.

Note:
The name design is leaned on the object-orientated design, but it's not object-orientated. To provide
methods for structs (like classes), the functions naming convention is (most time):

prefix 'TE3D' + '_' + the belonging struct name + '_' + the 'function-name'

For example:
void TE3D_Matrix4x4f_mul(...)