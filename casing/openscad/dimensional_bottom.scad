use <relativity.scad>;

use <obiscad/vector.scad>
use <obiscad/attach.scad>
use <obiscad/bevel.scad>

//plastic in .030" = .76mm
GLASS_THICKNESS = .030 * 25.4;

SHELL_THICKNESS = 2;

SHELL_DEPTH = 20;


bevel1 = [[-105/2 + 1,20/2, SHELL_DEPTH], [1, 0, 0], 0];
bevel_normal1 = [[-105/2 + 1,17/2, SHELL_DEPTH], [0, -1, 1], 0];
//%connector(bevel1);
//%connector(bevel_normal1);

//casing front
difference(){
	//basic outline of the bottom of the casing..
	box([105, 78, SHELL_DEPTH]);

	//main cutout cutout
	translate([0,0,2])	
		box([101,74,SHELL_DEPTH]);

	//inset button area
	translate([-105/2 + 1,0, SHELL_DEPTH - 1])
		box([4,20,2]);

	translate([-105/2+2,0, SHELL_DEPTH - 9])
		box([2,30,10]);

	mirrored([0,1,0])
		bevel(bevel1, bevel_normal1, cr = 1, cres=0, l=3);
}




module standoff(height=6, id=3.1) {
	difference(){
		rod(d=5, h=height);
		translate([0,0, 2])
		rod(d=id, h=height - 2);
	}
}