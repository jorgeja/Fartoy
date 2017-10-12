clear all
close all

parameters

sim('task_3f.slx')

% Course 
figure(1)
plot(simout.Time,simout.Data(:,1),simout.Time,simout.Data(:,2),'linewidth', 2);
legend('Course Setpoint, \chi_c', 'Course, \chi');
xlabel('time(s)');
ylabel('Course angle (rads)')
grid on

%Aileron input
figure(2)
plot(simout.Time,simout.Data(:,3),simout.Time,simout.Data(:,4),'linewidth', 1);
legend('Aileron Input, \delta_a^c','Actual Aileron Angle, \delta_a');
xlabel('time(s)');
ylabel('Aileron angle (rads)')
grid on

%Roll
figure(3)
plot(simout.Time,simout.Data(:,10),'linewidth', 1);
hold on
plot(simout.Time,simout.Data(:,7),simout.Time,simout.Data(:,12),'linewidth',2);
legend('Measured Roll, \phi_{noise}','Actual Roll, \phi','Estimated Roll, \phi_e');
xlabel('time(s)');
ylabel('Roll angle (rads)')
grid on

%Roll rate
figure(4)
plot(simout.Time,simout.Data(:,9),'linewidth',1);
hold on
plot(simout.Time,simout.Data(:,6),simout.Time,simout.Data(:,13),'linewidth', 2);
legend('Measured Roll Rate, p_{noise}', 'Actual Roll Rate, p', 'Estimated Roll Rate, p_{e}');
xlabel('time(s)');
ylabel('Roll rate angle (rads)')
grid on

%Yaw rate
figure(5)
plot(simout.Time,simout.Data(:,8),'linewidth',1);
hold on
plot(simout.Time,simout.Data(:,5),simout.Time,simout.Data(:,14),'linewidth', 2);
legend('Measured Yaw Rate, r_{noise}', 'Actual Yaw Rate, r', 'Estimated Yaw Rate, r_{e}');
xlabel('time(s)');
ylabel('Yaw rate angle (rads)')
grid on

%State Estimate Covariance Matrix
figure(6)
plot(simout.Time(1:100),EstimateCovariance.Data(:,1:100),'linewidth',1);
xlabel('time(s)');
grid on