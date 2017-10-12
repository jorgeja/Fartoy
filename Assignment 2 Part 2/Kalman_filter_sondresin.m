function [ x_hat_dot, P_dot ] = Kalman_filter( x_hat, y, P )
K = P*C'\R;
x_hat_dot = A*x_hat + B*u + K*(y - C*x_hat);
P_dot = A*P + P*A' + E*Q*E' - P*H'\R*H*P;
end
