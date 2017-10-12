clear all
close all

parameters

Kp_chi = 10;
sim('task_2e.slx')
plot(tout(:),simout(:,3),tout(:),simout(:,2),'linewidth',2);
Kp_chi = 3.7547;
sim('task_2e.slx')
hold on
plot(tout(:),simout(:,2),'linewidth',2);
Kp_chi = 1;
sim('task_2e.slx')
hold on
plot(tout(:),simout(:,2),'linewidth',2);
grid on
legend('Course Set Point \chi_c','Course \chi, \zeta_\chi = 5, Kp_\chi = 18.77','Course \chi, \zeta_\chi = 1, Kp_\chi = 3.7547','Course \chi, \zeta_\chi = 0.5, Kp_\chi = 1.877');
title('Step response for Course Angle \chi');
xlabel('time(s)');
ylabel('\chi, Course angle (rads)')


