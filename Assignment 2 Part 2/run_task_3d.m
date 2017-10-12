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
ylabel('Course angle (rads)')
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
ylabel('Roll angle (rads)')
grid on

%Roll rate
figure(4)
plot(simout.Time,simout.Data(:,8),'linewidth',1);
hold on
plot(simout.Time,simout.Data(:,5),simout.Time,simout.Data(:,12),'linewidth', 2);
legend('Roll Rate w Noise p_{noise}', 'Roll Rate p', 'Roll Rate Estimated p_{e}');
title('Roll Rate Angles');
xlabel('time(s)');
ylabel('Roll rate angle (rads)')
grid on

%Yaw rate
figure(5)
plot(simout.Time,simout.Data(:,7),'linewidth',1);
hold on
plot(simout.Time,simout.Data(:,4),simout.Time,simout.Data(:,13),'linewidth', 2);
legend('Yaw Rate w Noise r_{noise}', 'Yaw Rate r', 'Yaw Rate Estimated r_{e}');
title('Yaw Rate Angles');
xlabel('time(s)');
ylabel('Yaw rate angle (rads)')
grid on