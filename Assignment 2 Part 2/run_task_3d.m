clear all
close all

parameters

sim('task_3e.slx')

% Course 
figure(1)
plot(simout.Time,simout.Data(:,1),simout.Time,simout.Data(:,2),'linewidth', 2);
legend('Course Set Point \chi_c', 'Course \chi');
title('Course vs Course Set Point');
xlabel('time(s)');
ylabel('\chi, Course angle (rads)')
grid on

%Aileron input
figure(2)
plot(simout.Time,simout.Data(:,3),'linewidth', 1);
legend('Aileron Input');
title('Aileron Input');
xlabel('time(s)');
ylabel('Aileron angle (rads)')
grid on

%Roll
figure(3)
plot(simout.Time,simout.Data(:,9),'linewidth', 1);
hold on
plot(simout.Time,simout.Data(:,6),simout.Time,simout.Data(:,11),'linewidth',2);
legend('Roll w Noise \phi_{noise}','Roll \phi','Roll Estimated \phi_e');
title('Roll Angles');
xlabel('time(s)');
ylabel('\chi, Roll angle (rads)')
grid on

%Roll rate
figure(4)
plot(simout.Time,simout.Data(:,8),'linewidth',1);
hold on
plot(simout.Time,simout.Data(:,5),simout.Time,simout.Data(:,12),'linewidth', 2);
legend('Roll Rate w Noise p_{noise}', 'Roll Rate p', 'Roll Rate Estimated p_{e}');
title('Roll Rate Angles');
xlabel('time(s)');
ylabel('\chi, Roll angle (rads)')
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