alpha_deg = 10;
beta_deg = 45;
deg2rad = 3.14/180;
alpha = alpha_deg * deg2rad;
beta = beta_deg * deg2rad;

U = [0.6; 0; 0];
v_c_ned = Rzyx(0, alpha, 0)' * Rzyx(0, 0, -beta)' * U;

psi = 30 * deg2rad;
theta = 0 * deg2rad;
phi = 2 * deg2rad;

v_c_body = Rzyx(phi, theta, psi)' * v_c_ned;

