%scale(1000) import("pince_lib_1.stl");

%translate([0,56,0]) scale(1000) import("pince_lib_2.stl");

translate([-16.5,64,-15]) cube([44,5,62]);

translate([0,64,0]) rotate([90,0,0]) cylinder(8,23,23);

translate([0,4,0]) rotate([90,0,0]) cylinder(8,23,23);

translate([-16.5,-9,-15]) cube([44,5,62]);

translate([25,-19,110]) cube([3,84,15]);

translate([-15,-19,35]) cube([43,98,12]);

translate([-18,-19,47]) cube([19,98,61]);

translate([0,-19,103]) cube([27.5,98,12]);