DIAMETER_PROPELLER = 31;
DIAMETER_MOTOR = 8;
LAUNCHPAD_WIDTH = 53;
LAUNCHPAD_DEPTH = 69;
THICKNESS = 4;
HEIGHT = 15;

module propellerProtection(){
	/* general height */
	h0 = HEIGHT;
	/* propeller diameter */
	d0 = DIAMETER_PROPELLER;
	/* propeller diameter with border */
	d1 = DIAMETER_PROPELLER + (2 * THICKNESS);
	/* motor diameter */
	d2 = DIAMETER_MOTOR;
	/* motor diameter with border */
	d3 = DIAMETER_MOTOR + (2 * THICKNESS);
	/* thickness */
	t0 = THICKNESS;

	union(){
		difference(){
			cylinder(h = h0, d = d1, center = false);
			cylinder(h = h0, d = d0, center = false);
		}
		difference(){
			union(){
				cylinder(h = t0, d = d3, center = false);
				translate([- t0 / 2, - d0 / 2, 0])
					cube([t0, d0, t0], center = false);
				translate([- d0 / 2, - t0 / 2, 0])
					cube([d0, t0, t0], center = false);
			}
			cylinder(h = t0, d = d2, center = false);
		}
	}
}

module launchpadSupport(model){
	if(model == "tiva-c"){
		/* general height */
		h0 = HEIGHT;
		/* launchpad width */
		w0 = LAUNCHPAD_WIDTH;
		/* launchpad width with border */
		w1 = LAUNCHPAD_WIDTH + (2 * THICKNESS);
		/* launchpad depth */
		d0 = LAUNCHPAD_DEPTH;
		/* launchpad depth with border */
		d1 = LAUNCHPAD_DEPTH + (2 * THICKNESS);
		/* thickness */
		t0 = THICKNESS;

		union(){
			difference(){
				cube([w1, d1, h0]);
				translate([t0, t0, 0])
					cube([w0, d0, h0]);
			}
			cube([w1, 10, t0]);
			translate([0, 50, 0])
				// magic number = depth + (2 * THICKNESS) - 50
				cube([w1, 25, t0]);
		}
	}
}

module finalDraw(){
	/* propeller radius */
	r0 = DIAMETER_PROPELLER / 2;
	/* launchpad support x translation */
	x0 = (LAUNCHPAD_WIDTH / 2) + THICKNESS;
	/* launchpad support y translation */
	y0 = (LAUNCHPAD_DEPTH / 2) + THICKNESS;
	/* propeller offset */
	o0 = r0 / sqrt(2);

	translate([- x0, - y0, 0]) launchpadSupport("tiva-c");
	translate([x0 + o0, y0 + o0, 0]) propellerProtection();
	translate([- x0 - o0, y0 + o0, 0]) propellerProtection();
	translate([x0 + o0, - y0 - o0, 0]) propellerProtection();
	translate([- x0 - o0, - y0 - o0, 0]) propellerProtection();
}

//propellerProtection();
//launchpadSupport("tiva-c");
finalDraw();
