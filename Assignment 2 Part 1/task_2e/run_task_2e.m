clear all
close all

parameters

sim('task_2e_simulink.slx')

plot(tout(:),simout(:,3),tout(:),simout(:,2),'linewidth',2);
legend('Course Set Point \chi_c','Course \chi');
title('course step response');
xlabel('time(s)');
ylabel('\chi, Course angle (rads)')
grid on

figure(2)
plot(tout(:),simout(:,1),tout(:),-1*simout(:,4),'linewidth',2)
legend('Aileron input \delta_a','Roll angle \phi');
title('Aileron control input')
xlabel('time(s)');
ylabel('\delta_a, Aileron Angle (rads)')
grid on


