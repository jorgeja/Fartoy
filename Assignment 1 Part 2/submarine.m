clear all
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

%% Rotation matrices
R_x = @(x) [1 0 0;0 cos(x) sin(x);-sin(x) cos(x) 0];
R_y = @(y) [cos(y) 0 -sin(y);0 1 0;sin(y) 0 cos(y)];
R_z = @(z) [cos(z) sin(z) 0;-sin(z) cos(z) 0;0 0 1];

R_n_c = R_y(alpha_c)'*R_z(-beta_c)';
R_n_b = R_z(-psi)*R_y(-theta);
R_b_c = inv(R_n_b)*R_n_c;

%% Vectors
v = @(t) [U*cos(omega*t);U*sin(omega*t);0];    %body fixed relative NED(rotated)
v_c = @(t) [U_c;0;0];                          %current velocity relative Flow frame

v_b_n = @(t) R_n_b*v(t);                       %body velocity relative NED(aligned)
v_c_n = @(t) R_n_c*v_c(t);                     %current velocity realtive NED(aligned)
v_c_b = @(t) R_b_c*v_c(t);                     %current velocity relative body frame
v_b_c = @(t) inv(R_b_c)*v(t);                  %body velocity relative current frame
v_r = @(t) v_b_n(t) - v_c_n(t);                %relative velocity NED(aligned)
v_r_2 = @(t) v(t) - v_c_b(t);                  %relative velocity BODY frame
v_r_3 = @(t) v_b_c(t) - v_c(t);                %relative velocity FLOW frame

%% Plotting
h = 0.1;
dim = 3;
endtime = 500;
length = (dim/h)*endtime;

v_c_n_plot(1:3) = v_c_n(0)
v_c_b_plot(1:3) = v_c_b(0);
   
for i= 1:3:length
   t = (i*h-1)/3; 
   
   v_plot(i:i+2) = v(t);
   v_b_n_plot(i:i+2) = v_b_n(t);
   v_b_c_plot(i:i+2) = v_b_c(t);
   v_r_plot(i:i+2) = v_r(t);
   v_r_2_plot(i:i+2) = v_r_2(t);
   v_r_3_plot(i:i+2) = v_r_3(t);
end

clf
figure(1)
hold on;
grid on;
plot3(v_plot(1:3:length),v_plot(2:3:length),v_plot(3:3:length),'Linewidth',2);
plot3(v_b_n_plot(1:3:length),v_b_n_plot(2:3:length),v_b_n_plot(3:3:length),'Linewidth',2);
plot3(v_b_c_plot(1:3:length),v_b_c_plot(2:3:length),v_b_c_plot(3:3:length),'Linewidth',2);
plot3(v_r_plot(1:3:length),v_r_plot(2:3:length),v_r_plot(3:3:length),'Linewidth',2);
plot3(v_r_2_plot(1:3:length),v_r_2_plot(2:3:length),v_r_2_plot(3:3:length),'Linewidth',2);
plot3(v_r_3_plot(1:3:length),v_r_3_plot(2:3:length),v_r_3_plot(3:3:length),'Linewidth',2);
legend('v','v_b_n','v_b_c','v_r_n','v_r_b','v_r_c');
xlabel('v1');
ylabel('v2');
zlabel('v3');