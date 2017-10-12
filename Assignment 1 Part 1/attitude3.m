clear all;

% M-script for numerical integration of the attitude dynamics of a rigid 
% body represented by unit quaternions. The MSS m-files must be on your
% Matlab path in order to run the script.
%
% System:                      .
%                              q = T(q)w
%                              .
%                            I w - S(Iw)w = tau
% Control law:
%                            tau = constant
% 
% Definitions:             
%                            I = inertia matrix (3x3)
%                            S(w) = skew-symmetric matrix (3x3)
%                            T(q) = transformation matrix (4x3)
%                            tau = control input (3x1)
%                            w = angular velocity vector (3x1)
%                            q = unit quaternion vector (4x1)
%
% Author:                   2016-05-30 Thor I. Fossen 

%% USER INPUTS
h = 0.1;                     % sample time (s)
N  = 3000;                    % number of samples

% model parameters
I = diag([400 400 400]);       % inertia matrix
I_inv = inv(I);

% constants
deg2rad = pi/180;   
rad2deg = 180/pi;

phi = 10*deg2rad;            % initial Euler angles
theta = -5*deg2rad;
psi = 15*deg2rad;

q = euler2q(phi,theta,psi);   % transform initial Euler angles to q

w = [0 0 0]';                 % initial angular rates

table = zeros(N+1,17);        % memory allocation

Kd = 300 * diag([1 1 1]);

Kp = 10 * diag([1 1 1]);

%% FOR-END LOOP
for i = 1:N+1,
   t = (i-1)*h;                  % time
   
   phi_d = deg2rad*(10 * sin(0.1*t));
   theta_d = 0;
   psi_d = deg2rad*(15 * cos(0.05*t));
   
   Theta_d = [phi_d;theta_d;psi_d];
   T_inv = [1 0 -sin(theta_d);
       0 cos(phi_d) cos(theta_d)*sin(phi_d);
       0 -sin(phi_d) cos(theta_d)*cos(phi_d)];
       
   
   phi_d_dot = deg2rad*(cos(0.1*t));
   theta_d_dot = 0;
   psi_d_dot = deg2rad*(-0.75*sin(0.05*t));
   
   Theta_d_dot = [phi_d_dot;theta_d_dot;psi_d_dot];
   
   w_d = T_inv*Theta_d_dot;
   
   w_tilde = w - w_d;
   
   q_d = euler2q(phi_d, theta_d, psi_d);
   s_e_d = Smtrx(q_d(2:4));

   epsilon_tilde = q_d(1)*q(2:4)+q(1)*q_d(2:4)+s_e_d*q(2:4);
   tau = -Kd*w_tilde - Kp*epsilon_tilde;
   [phi,theta,psi] = q2euler(q); % transform q to Euler angles
   phi_e = phi_d - phi;
   theta_e = theta_d - theta;
   psi_e = phi_d - phi;
   
   [J,J1,J2] = quatern(q);       % kinematic transformation matrices
   
   q_dot = J2*w;                        % quaternion kinematics
   w_dot = I_inv*(Smtrx(I*w)*w + tau);  % rigid-body kinetics
   
   table(i,:) = [t q' phi theta psi w' tau' phi_e theta_e psi_e];  % store data in table
   
   q = q + h*q_dot;	             % Euler integration
   w = w + h*w_dot;
   
   q  = q/norm(q);               % unit quaternion normalization
end 

%% PLOT FIGURES
t       = table(:,1);  
q       = table(:,2:5); 
phi     = rad2deg*table(:,6);
theta   = rad2deg*table(:,7);
psi     = rad2deg*table(:,8);
w       = rad2deg*table(:,9:11);  
tau     = table(:,12:14);
phi_e     = rad2deg*table(:,15);
theta_e   = rad2deg*table(:,16);
psi_e     = rad2deg*table(:,17);

clf
figure(1)
subplot(221),plot(t,phi,t,theta,t,psi,'linewidth',1),xlabel('time [s]'),ylabel('angle [deg]'),title('attitude'),grid,legend('\phi', '\theta', '\psi')
subplot(222),plot(t,phi_e,t,theta_e,t,psi_e,'linewidth',1),xlabel('time [s]'),ylabel('angle [deg]'),title('tracking error'),grid,legend('\phi error', '\theta error', '\psi error')
subplot(223),plot(t,w,'linewidth',1),xlabel('time [s]'),ylabel('angular velocity [deg/s]'),title('w'),grid,legend('p', 'q', 'r')
subplot(224),plot(t,tau,'linewidth',1),xlabel('time [s]'),ylabel('torque [Nm]'),title('\tau'),grid,legend('K', 'M', 'N')