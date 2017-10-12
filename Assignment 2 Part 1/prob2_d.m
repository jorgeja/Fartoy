close all
clear all

parameters


G1 = tf([Kp_phi*a_phi_2],[1 a_phi_1 0]);
G2 = tf([(g*a_phi_2*Kp_phi*Kp_chi)/Vg (g*a_phi_2*Kp_phi*Ki_chi)/Vg],[1 a_phi_1+Kd_phi*a_phi_2 a_phi_2*Kp_phi 0 0]);
bode(G1, G2);
legend('\phi/\phi_c(s)','\chi/\chi_{c}(s)')
grid on

figure
Kp_chi = Kp_chi*10;
Ki_chi = Ki_chi*100;

G3 = tf([Kp_phi*a_phi_2],[1 a_phi_1 0]);
G4 = tf([(g*a_phi_2*Kp_phi*Kp_chi)/Vg (g*a_phi_2*Kp_phi*Ki_chi)/Vg],[1 a_phi_1+Kd_phi*a_phi_2 a_phi_2*Kp_phi 0 0]);
bode(G3, G4);
legend('\phi/\phi_c(s)','\chi/\chi_{c}(s)')
grid on
title('Bode Diagram, \omega_{\phi} = \omega_{\chi}')