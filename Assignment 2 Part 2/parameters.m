a_phi_1 = 2.87;
a_phi_2 = -0.65;

Kp_phi = -5/3;
Kd_phi = 2.15;

Ki_chi = 0.1954;
Kp_chi = 3.7547;

g = 9.81;
Vg = 637/3.6;

A = [-0.322 0.052 0.028 -1.12;
      0     0     1     -0.001;
     -10.6  0    -2.87   0.46;
      6.87  0    -0.04  -0.32];

B = [0.002 0 -0.65 -0.02]';

C = [0 0 0 1;    
     0 0 1 0;
     0 1 0 0];

D = zeros(3,1);

phi_noisePower = (2/180)^2;
p_noisePower = (0.5/180)^2;
r_noisePower = (0.2/180)^2;
phi_variance = (2*pi/180)^2;
p_variance = (0.5*pi/180)^2;
r_variance = (0.2*pi/180)^2;

Q = [10^-6, 10^-6, 10^-6, 10^-6];
Q = diag(Q);
R = [r_variance, p_variance, phi_variance];
R = diag(R);
R_inv = inv(R);
E = eye(4);
P0 = zeros(4,4);