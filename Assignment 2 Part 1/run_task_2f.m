clear all
close all

parameters

sim('task_2f.slx')

% Course 
figure(1)
hold on
plot(simout.Time(:),simout.Data(:,7));
plot(simout.Time(:),simout.Data(:,6));
legend('Course \chi','Course Set Point \chi_c');
grid on

%Measurements
figure(2)
hold on
plot(simout.Time(:),simout.Data(:,2));
plot(simout.Time(:),simout.Data(:,3));
plot(simout.Time(:),simout.Data(:,4));
plot(simout.Time(:),simout.Data(:,5));
legend('r','p','\beta','\phi');
grid on