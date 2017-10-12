close all
clear all
a1 = 2.87;
a2 = -0.65;
Kp_phi = -5/3;
Kp_chi = 3.75;
Ki_chi = 0.1954;
Kd_phi = 2.15;
Vg = 637/3.6; %Ground speed, m/s
g = 9.81;


G1 = tf([Kp_phi*a2],[1 a1+Kd_phi*a2 0]);
G2 = tf([(g*a2*Kp_phi*Kp_chi)/Vg (g*a2*Kp_phi*Ki_chi)/Vg],[1 a1+Kd_phi*a2 0 0 0]);
bode(G1, G2);
legend('\phi}\phi^c(s)','\chi/\chi^{c}(s)')
%grid on

figure
Kp_chi = Kp_chi*10;
Ki_chi = Ki_chi*100;

G3 = tf([Kp_phi*a2],[1 a1 0]);
G4 = tf([1/Vg*a2*Kp_phi*Kp_chi 1/Vg*a2*Kp_phi*Ki_chi],[1 a1 0 0 0]);
bode(G3, G4);
legend('\phi/\phi^c(s)','\chi/\chi^c(s)')
%grid on
title('Bode Diagram, \omega_{\phi} = \omega_{\chi}')