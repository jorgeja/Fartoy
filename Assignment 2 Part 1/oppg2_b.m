a_phi_1 = 2.87;
a_phi_2 = -0.65;
Kp_phi = -5/3;
Kd_phi = 2.15;

Ki = -2.4:0.01:0;
Ki_2 = -5:0.1:5;


G = tf([a_phi_2],[1 a_phi_1+a_phi_2*Kd_phi a_phi_2*Kp_phi 0]);
[r,k] = rlocus(G,Ki);
figure(1)
rlocus(G,Ki);

[r1,k1] = rlocus(G,Ki_2);
figure(2)
rlocus(G,Ki_2)
