clear all
close all

parameters
sim('task_2e_simulink_copy.slx');
t_e = tout;
s_e = simout;

sim('task_2f_simulink.slx')

% Course 
figure(1)
plot(t_e,s_e(:,3),t_e,s_e(:,2),simout.Time,simout.Data(:,6), 'linewidth', 1);
legend('Course Set Point \chi_c', 'Course \chi simplified', 'Course \chi complete');
title('Comparison of heading response for simplified and complete model');
xlabel('time(s)');
ylabel('\chi, Course angle (rads)')
grid on

%Measurements
figure(2)
hold on
plot(simout.Time(11:160),simout.Data(11:160,1:5), 'linewidth', 1);
legend('\delta_c','r','p','\beta','\phi');
grid on
title('State dynamics for one course change manouvre');
xlabel('sec');
ylabel('rad, rad/sec');
