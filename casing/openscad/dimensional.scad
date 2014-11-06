use <relativity.scad>;

use <obiscad/vector.scad>
use <obiscad/attach.scad>
use <obiscad/bevel.scad>

CASE_DIMS = [105, 78, 2];

SCREEN_W = 70;
SCREEN_H = 43;

//plastic in .030" = .76mm
GLASS_DIMS = [78, 70, .030 * 25.4];

INSET_DIMS = [12, 17, 1];
INSET_OFFSET = [INSET_DIMS[0]/2 - CASE_DIMS[0]/2, 0, 0]; 

bit = .01;

rotate([180,0,0])
	casing_front();

module casing_front(){
	//casing front
	difference(){
		//basic outline of the front of the casing..
		box(CASE_DIMS);
	
		//screen cutout
		//box([SCREEN_W, SCREEN_H, CASE_DIMS[2]]);
	
		//cutout for glass
		translate([0, 0, CASE_DIMS[2] - GLASS_DIMS[2]])
			box(GLASS_DIMS + [0,0, bit]);
	
		//cutout for insert, so glass area isn't suspended when printing
		translate([2, 0, -bit])
			box([84, 75, CASE_DIMS[2] - GLASS_DIMS[2] + 2*bit]);
	
		//inset button area
		translate(INSET_OFFSET) {
			inset_cutout();
			
			
			//cutouts for round buttons
			translate([0, -22, -bit]) {
				rod(d=4.5, h=CASE_DIMS[2] + 1);
				translate([0, -8, 0])
					rod(d=4.5, h=CASE_DIMS[2] + 1);
			}
		}
	
		
		
	}
	
	//render insert
	//color("Aqua")
	//	insert();
	

	translate(INSET_OFFSET) {
		//color("Aqua")
			//inset();

		//inset_supports();
		insetChamfers();

	}

	standoffs();

	mirrored([1,0,0])
		mirrored([0,1,0])
			translate([48, -35, 0])
				*fitting();
}

module insert() {
	difference(){
		translate([2, 0, -bit])
			box([84, 75, CASE_DIMS[2] - GLASS_DIMS[2] + 2*bit]);
		translate([0, 0, -bit*2])
		box([SCREEN_W, SCREEN_H + 20, CASE_DIMS[2]]);
		
		translate([0,0, .02])
			standoffs();
	}
}

module inset_cutout() {
	translate([-bit, 0, -bit])
	box([INSET_DIMS[0] + bit*2, INSET_DIMS[1], CASE_DIMS[2] + bit * 2]);
}

module inset() {
	//inset button area + button cutouts
	
	difference(){
		translate([.25, 0, 0])
		box([12.5,20,1], anchor=[0,0,1]);

		mirrored([0, 1, 0])
			translate([0, 4, bit])
				box([8.5, 3, 1.02], anchor=[0,0,1]);
			
	}
}

module inset_supports() {
	//some support so things print cleaner..
	mirrored([0,1,0]) {
		translate([0,2.5,0])
			box([INSET_DIMS[0], .2, CASE_DIMS[2]], anchor=[0,1,-1]);
		translate([0,5.5,0])
			box([INSET_DIMS[0], .2, CASE_DIMS[2]], anchor=[0,-1,-1]);
	}
	translate([0, 0, 0])
		box([INSET_DIMS[0], .2, CASE_DIMS[2]]);

}

module insetChamfers() {
	//try a chamfer on recessed button area
	inside_c1 = [[0,8.5, 0], [-1,0, 0], 0];
	inside_c1n = [inside_c1[0], [0,-1, 1], 0];

	outside_c1 = [[.25,10, 0], [-1,0, 0], 0];
	outside_c1n = [outside_c1[0], [0,1, -1], 0];

	//%connector(inside_c1);
	//%connector(inside_c1n);
	mirrored([0, 1, 0])
	bconcave_corner_attach(inside_c1,inside_c1n, l=12, cres=0, cr=2, th=.01);

	//%connector(outside_c1);
	//%connector(outside_c1n);
	mirrored([0, 1, 0])
	bconcave_corner_attach(outside_c1,outside_c1n, l=12.5, cres=0, cr=1, th=.01);
}



module standoffs(PCBOFFSET = 5.2) {
	//screw standoffs to position circuit board

	//depth of the cutout that goes behind the glass.
	CUTOUT_DEPTH = CASE_DIMS[2] - GLASS_DIMS[2];

	mirrored([0, 1, 0])
	translate([0, 0, CUTOUT_DEPTH])
		rotate([180,0,0]) {
			translate([42, 20, 0])
				standoff(height=PCBOFFSET + CUTOUT_DEPTH);
			translate([-42, 13, 0])
				standoff(height=PCBOFFSET + CUTOUT_DEPTH);
	}
}

module standoff(height=6, id=3.1) {
	difference(){
		rod(d=5, h=height);
		translate([0,0, 2])
		rod(d=id, h=height);
	}
}

module fitting() {
	difference(){
		box([5,4,8], [0,0,1]);

		translate([0,0,-6])
			rotate([90,0,0])
			rod(d=3.1, h=6);
	}
}


//REFERENCE STUFF
//render the glass for reference
translate([0, 0, CASE_DIMS[2] - GLASS_DIMS[2]])
	*box([78,70, GLASS_DIMS[2]]);


//also render 'backing' plate that holds glass in place around screen
*difference() {
	translate([2, 0, 0])
		box([84,75, CASE_DIMS[2] - GLASS_DIMS[2]]);

	//screen cutout again
	box([70,43,2]);
}