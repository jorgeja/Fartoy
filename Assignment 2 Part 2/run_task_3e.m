clear all
close all

parameters
sim('task_2g_simulink.slx')

% Course 
figure(1)
plot(simout.Time,simout.Data(:,7),simout.Time,simout.Data(:,6),'linewidth', 2);
legend('Course Set Point \chi_c', 'Course \chi', 'Course \chi complete');
title('Integral Wind-Up protection');
xlabel('time(s)');
ylabel('\chi, Course angle (rads)')
grid on

%Measurements
% figure(2)
% hold on
% plot(simout.Time(10:110),simout.Data(10:110,1:5), 'linewidth', 1);
% legend('\delta_c','r','p','\beta','\phi');
% grid on
% title('State dynamics for one course change manouvre');
% xlabel('sec');
% ylabel('rad, rad/sec');
