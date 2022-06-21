%scale(1000) import("pince_mot_1.stl");

%translate([0,56,0]) scale(1000) import("pince_mot_2.stl");

translate([-22.5,60,-15]) cube([39,5,55]);

translate([0,60,0]) rotate([90,0,0]) cylinder(5,23,23);

translate([0,5,0]) rotate([90,0,0]) cylinder(5,23,23);

translate([0,11,0]) rotate([90,0,0]) cylinder(6,11,11);

translate([-22.5,-5,-15]) cube([39,5,55]);

translate([-15,-19,110]) cube([3,84,15]);

translate([-15,-19,35]) cube([32,98,12]);

translate([-1.5,-19,47]) cube([19,98,60]);

translate([-15,-19,103]) cube([20,98,10]);