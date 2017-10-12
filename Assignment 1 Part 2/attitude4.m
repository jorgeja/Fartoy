clear all
close all
%% Initial conditions 
deg2rad = 3.14/180;
rad2deg = 1/deg2rad;
x_0 = [-1*deg2rad; 0; 2*deg2rad; 0; 0]; %phi, p, theta, q, r
x_dot_0 = [0; 0; 0; 0; 0]; %p, p_dot, q, q_dot, r_dot

%% Parameters
delta_0 = 5 * deg2rad;
delta_700 = 10 * deg2rad;

T = 50;
K = 0.1;
zeta_p = 0.1;
w_p = 0.1;
zeta_q = 0.2;
w_q = 0.05;
U = 1.5;

A_angular_states =[
    0           1               0           0               0;
    -w_p^2      -2*zeta_p*w_p   0           0               0;
    0           0               0           1               0;
    0           0               -w_q^2      -2*zeta_q*w_q   0;
    0           0               0           0           -1/T];
B_angular_states = [0;0;0;0;K/T];

%% Current
Uc = [0.6 0 0]';
alpha = 10  *deg2rad;
beta = 45 * deg2rad;

%Current in NED
vc_ned = Rzyx(0,alpha,0)' * Rzyx(0,0,-beta)' * Uc;

%% Equations of motion
angular_states_dot = @(angular_states, delta) A_angular_states*angular_states + B_angular_states*delta;
nu = @(omega, t) [U*cos(omega * t);U*sin(omega * t);0];    %body fixed translational velocities relative NED, in body
delta = @(t) deg2rad * 5 * (1 + (t>700)); % Rudder angle
%vc_body_relative_ned = @(phi, theta, psi) Rzyx(phi,theta,psi)'*vc_ned;
beta = @(u,v) asin(v / sqrt(u^2 + v^2));
course = @(psi,beta) psi + beta;
%% Simulation
simtime = 1400;
h = 1;
N = simtime/h;
t_log = zeros(1,N/h);
angular_states_log = zeros(5, N/h);
psi_log = zeros(1,N/h);
delta_log = zeros(1,N/h);
pos_ned_log = zeros(3,N/h);
nu_ned_log = zeros(3,N/h);
nu_r_ned_log = zeros(3,N/h);
pos_r_ned_log = zeros(3,N/h);
nu_body_log = zeros(3,N/h);
nu_r_body_log = zeros(3,N/h);
beta_log = zeros(1,N/h);
beta_r_log = zeros(1,N/h);
course_log = zeros(1,N/h);

angular_states_log(:,1) = x_0;
nu_ned_log(:,1) = Rzyx(x_0(1), x_0(3), 0) * nu(0, 0);
nu_r_ned_log(:,1) = nu_ned_log(:,1) - vc_ned;

nu_body_log(:,1) = nu(0, 0);
nu_r_body_log(:,1) =  Rzyx(x_0(1), x_0(3), 0)' * nu_r_ned_log(:,1);
    
beta_log(1) = beta(nu_body_log(1,1),nu_body_log(2,1));
beta_r_log(1) = beta(nu_r_body_log(1,1),nu_r_body_log(2,1));
course_log(1) = course(0, beta_log(1));

for i = 2:N
   t = i*h; 
    t_log(i) = t;
    angular_states_log(:,i) = angular_states_log(:,i-1) + angular_states_dot(angular_states_log(:,i-1), delta(t))*h;
    delta_log(i) = rad2deg * delta(t);
    psi_log(i) = psi_log(i-1) + angular_states_log(5,i-1)*h;
    
    phi = angular_states_log(1,i);
    theta = angular_states_log(3,i);
    psi = psi_log(i);
    r = angular_states_log(5,i);
    nu_ned_log(:,i) = Rzyx(phi, theta, psi) * nu(r, t);
    pos_ned_log(:,i) = pos_ned_log(:,i-1) + nu_ned_log(:,i-1)*h;
    nu_r_ned_log(:,i) = nu_ned_log(:,i) - vc_ned;
    pos_r_ned_log(:,i) = pos_r_ned_log(:,i-1) + nu_r_ned_log(:,i-1)*h;
    
    nu_body_log(:,i) = nu(r, t);
    nu_r_body_log(:,i) =  Rzyx(phi, theta, psi)' * nu_r_ned_log(:,i);
    
    beta_log(i) = beta(nu_body_log(1,i),nu_body_log(2,i));
    beta_r_log(i) = beta(nu_r_body_log(1,i),nu_r_body_log(2,i));
    course_log(i) = course(psi, beta_log(i));
    
end

%% Plot
%angular_states: phi, p, theta, q, r
phi_log     = rad2deg*angular_states_log(1,:);
p_log       = rad2deg*angular_states_log(2,:); 
theta_log   = rad2deg*angular_states_log(3,:);
q_log       = rad2deg*angular_states_log(4,:);  
psi_log     = rad2deg*psi_log;
r_log       = rad2deg*angular_states_log(5,:);
beta_log       = rad2deg*beta_log;
beta_r_log       = rad2deg*beta_r_log;
course_log       = rad2deg*course_log;



figure(1)
subplot(211),plot(t_log,phi_log,t_log,theta_log,'linewidth',1),xlabel('time (s)'),ylabel('deg'),title('attitude'),grid,legend('\phi', '\theta')
subplot(212),plot(t_log,psi_log,'linewidth',1),xlabel('time (s)'),ylabel('deg'),title('attitude'),grid,legend('\psi')

figure(2)
subplot(211),plot(t_log,p_log,t_log,q_log,t_log,r_log,'linewidth',1),xlabel('time (s)'),ylabel('deg/s'),title('angular velocities'),grid,legend('p', 'q', 'r')
subplot(212),plot(t_log,delta_log,'linewidth',1),xlabel('time (s)'),ylabel('deg'),title('rudder angle'),grid,legend('rudder angle')

figure(3)
hold on
plot3(pos_ned_log(1,:),pos_ned_log(2,:),pos_ned_log(3,:))
plot3(pos_r_ned_log(1,:),pos_r_ned_log(2,:),pos_r_ned_log(3,:))
legend('\eta ned', '\eta_r ned')
xlabel('North'),ylabel('East'),zlabel('Down')
grid on

figure(4)
hold on
plot3(nu_ned_log(1,:),nu_ned_log(2,:),nu_ned_log(3,:))
plot3(nu_r_ned_log(1,:),nu_r_ned_log(2,:),nu_r_ned_log(3,:))
legend('\nu ned', '\nu_r ned')
xlabel('North'),ylabel('East'),zlabel('Down')
grid on

figure(5)
hold on
plot(t_log,beta_log, t_log,beta_r_log, t_log,course_log,'linewidth',1),xlabel('time (s)'),ylabel('deg'),title('Sideslip, crab and course angles'),grid,legend('crab angle \beta','sideslip \beta_r','course angle \chi');


%position
%relative velocity
%attitude
%angular velocity
%rudder input
%figure showing sideslip, crab and course