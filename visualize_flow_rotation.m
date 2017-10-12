%visualise rotation
function visualize_flow_rotation(alpha, beta)
close all
deg2rad = 3.14/180;
x = [1; 0; 0];
y = [0; 1; 0];
z = [0; 0; 1];

stab_x = Rzyx(0, alpha*deg2rad, 0)' * x;
stab_y = Rzyx(0, alpha*deg2rad, 0)' * y;
stab_z = Rzyx(0, alpha*deg2rad, 0)' * z;
zero = [0 0];
vc_ned = Rzyx(0, alpha*deg2rad, 0)' * Rzyx(0, 0, -beta*deg2rad)' * x;


hold on
plot3([0 vc_ned(1)],[0 vc_ned(2)],[0 vc_ned(3)], 'linewidth', 2)
plot3([0 vc_ned(1)],[0 0],[0 0], 'r', 'linewidth', 2)
plot3([vc_ned(1) vc_ned(1)],[0 vc_ned(2)],[0 0], 'g', 'linewidth', 2)
plot3([vc_ned(1) vc_ned(1)],[vc_ned(2) vc_ned(2)],[0 vc_ned(3)], 'b', 'linewidth', 2)
plot3([0 stab_x(1)], [0 stab_x(2)], [0 stab_x(3)], 'g')
plot3([0 stab_y(1)], [0 stab_y(2)], [0 stab_y(3)], 'g')
plot3([0 stab_z(1)], [0 stab_z(2)], [0 stab_z(3)], 'g')
legend('flow vector', 'north', 'east', 'down', 'stab frame')
end