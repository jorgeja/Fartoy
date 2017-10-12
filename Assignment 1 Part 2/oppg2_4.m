clear all
close all
%% Given parameters
U = 1.5; %m/s
U_c = 0.6; %m/s
R = 100; %m
Uc = 0.6; %m/s
theta = 2; %deg
psi = 30; %deg
beta_c = 45; %deg
alpha_c = 10; %deg
omega = U/R;

x0 = 0;
y0 = 0;
z0 = 10;
p0 = [x0;y0;z0];        % Initial position

%% Rotation matrices
R_x = @(x) [1 0 0;0 cosd(x) -sind(x);sind(x) cosd(x) 0];
R_y = @(y) [cosd(y) 0 sind(y);0 1 0;-sind(y) 0 cosd(y)];
R_z = @(z) [cosd(z) -sind(z) 0;sind(z) cosd(z) 0;0 0 1];

R_n_c = R_y(alpha_c)'*R_z(-beta_c)';
R_n_b = R_z(psi)*R_y(theta);
R_b_c = inv(R_n_b)*R_n_c;

%% Velocities
v = @(t) [U*cos(omega*t);U*sin(omega*t);0];    %body fixed relative NED(rotated)
v_c = @(t) [U_c;0;0];                          %current velocity relative Flow frame

v_c_b = @(t) R_b_c*v_c(t);                     %current velocity relative NED(rotated) BODY frame
v_r_b = @(t) v(t) - v_c_b(t);                  %relative velocity relative NED(rotated) BODY frame
v_b_n = @(t) R_n_b*v(t);                       %body velocity relative NED(aligned)
v_c_n = @(t) R_n_c*v_c(t);                     %current velocity realtive NED(aligned)
v_r_n = @(t) v_b_n(t) - v_c_n(t);              %relative velocity NED(aligned)

%% Sideslip, crab and course angles
surge = @(t) [1 0 0]*v(t);
sway = @(t) [0 1 0]*v(t);
surge_r = @(t) [1 0 0]*v_r_b(t);
sway_r = @(t) [0 1 0]*v_r_b(t);

speed = @(t) sqrt(surge(t)^2+sway(t)^2);
speed_r = @(t) sqrt(surge_r(t)^2+sway_r(t)^2);


beta = @(t) asind(sway(t)/speed(t));
beta_r = @(t) asind(sway_r(t)/speed_r(t));
course = @(t) psi + beta(t);

%% Positions and Plotting
h = 0.1;
endtime = 500;
length = (1/h)*endtime;

p = zeros(3,length + 1);
p(1:3,1) = p0;
p_r(1:3,1) = p0;

v_c_n_plot = v_c_n(0)
v_c_b_plot = v_c_b(0)
   
for i= 1:length
   t = (i*h-1);
   time(i) = t;
   p(1:3,i+1) = [p(1,i);p(2,i);p(3,i)] + h*v_b_n(t);
   p_r(1:3,i+1) = [p_r(1,i);p_r(2,i);p_r(3,i)] + h*v_r_n(t);
   
   v_b_plot(1:3,i) = v(t);
   v_r_b_plot(1:3,i) = v_r_b(t);
   v_b_n_plot(1:3,i) = v_b_n(t);
   v_r_n_plot(1:3,i) = v_r_n(t);
   
   beta_plot(i) = beta(t);
   beta_r_plot(i) = beta_r(t);
   course_plot(i) = course(t);
end

figure(1)
hold on;
grid on;
p1 = gca;
p1.ZDir = 'reverse';
plot3(p(1,1:length+1),p(2,1:length+1),p(3,1:length+1),'linewidth',2);
plot3(p_r(1,1:length+1),p_r(2,1:length+1),p_r(3,1:length+1),'linewidth',2);
title('Position and Relative position in NED')
legend('p','p_r');
xlabel('North [m]')
ylabel('East [m]')
zlabel('down [m]')
%xlim([-220 180])
%ylim([-100 300])
%zlim([0 30])

figure(2)
hold on;
grid on;
plot3(v_b_n_plot(1,1:length),v_b_n_plot(2,1:length),v_b_n_plot(3,1:length),'linewidth',2);
plot3(v_r_n_plot(1,1:length),v_r_n_plot(2,1:length),v_r_n_plot(3,1:length),'linewidth',2);
plot3(v_b_plot(1,1:length),v_b_plot(2,1:length),v_b_plot(3,1:length),'linewidth',2);
plot3(v_r_b_plot(1,1:length),v_r_b_plot(2,1:length),v_r_b_plot(3,1:length),'linewidth',2);
title('Comparison of velocities in NED and BODY frame')
legend('v_b_n NED frame','v_r NED frame','v_b BODY frame','v_r BODY frame');
xlabel('v1 [m/s]')
ylabel('v2 [m/s]')
zlabel('v3 [m/s]')
xlim([-2.5 2])
ylim([-2.5 2.5])

figure(3)
hold on;
grid on;
plot(time,beta_plot,'linewidth',1);
plot(time,beta_r_plot,'linewidth',1);
plot(time,course_plot,'linewidth',1);
legend('crab angle \beta','sideslip \beta_r','course angle \chi');
title('Sideslip, crab and course angles')
xlabel('time [s]')
ylabel('angle [deg]')
xlim([0 500])
