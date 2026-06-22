clear all
%%%%%%%%%%const params%%%%%%%%%%%%
Cf_init=75000;
Cr_init=107200;
lf_init=1.64;
wheel_base= 3.9;
lr_init = wheel_base - lf_init;
Iz_init=39000;
mass_tractor=8093;%8093 the bobtail weight
gamma=1.0;
deta=0.8;
p=0.4;
%%%%%%%%%%the parameters need to be set%%%%%%%%%%%
% vecility_kph=80;
% vecility = vecility_kph/3.6; 
vecility = 25.0;
combined_weight=41000;%total weight of the truck(trailer+tractor)46000(heavy load)  19000(empty load)
steer_ratio=25.0;
steer_system_time_constant =0.4;
enable_delay_model=false;
enable_intergal=true;
enable_plot_step = true;%false true
enable_plot_poles = true;%false true
enable_plot_bode = false;
use_q_interpolate_directly = true;
%%%%%%%%%%%%%%%%%%%%%%to set the q matrix directly%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% enable delay model
% set_q_directly = [0.0003,0.25,0.59,0.0618942,0.0618942,0.0]; % 22.22m/s 41000kg
% set_q_directly = [0.0002,0.32,0.61,0.0397778,0.0397778,0.0]; % 25.0m/s 41000kg
% set_q_directly = [0.0002,0.32,0.60,0.0397778,0.0397778,0.0]; % 26.39m/s 41000kg
% set_q_directly = [0.00019,0.29,0.58,0.0397778,0.0397778,0.0]; % 27.78m/s 41000kg
%% disable delay model
% set_q_directly = [0.0003,0.25,0.59,0.0618942,0.0618942]; % 22.22m/s 41000kg
set_q_directly = [0.0002,0.32,0.61,0.0397778,0.0397778]; % 25.0m/s 41000kg
% set_q_directly = [0.0002,0.32,0.60,0.0397778,0.0397778]; % 26.39m/s 41000kg
% set_q_directly = [0.00019,0.29,0.58,0.0397778,0.0397778]; % 27.78m/s 41000kg
%% tuned disable delay model
%% config 2
% set_q_directly =[0.00062, 0.52, 1.05, 0.06189, 0.06189];  % 22.22m/s 41000kg tuned by zhenwei
% set_q_directly = [0.000375,0.606,1.0,0.0397778,0.0397778]; % 25.0m/s 41000kg
% set_q_directly = [0.00038,0.608,0.99,0.0397778,0.0397778]; % 26.39m/s 41000kg
% set_q_directly = [0.000394,0.60,1.04,0.0397778,0.0397778]; % 27.78m/s 41000kg
%% config 3
% set_q_directly = [0.0003,0.2,0.59,0.06189,0.0618942]; % 22.22m/s 41000kg
% set_q_directly = [0.0002,0.30,0.61,0.0397778,0.0397778]; % 25.0m/s 41000kg
% set_q_directly = [0.0002,0.30,0.60,0.0397778,0.0397778]; % 26.39m/s 41000kg
% set_q_directly = [0.00019,0.29,0.58,0.0397778,0.0397778]; % 27.78m/s 41000kg
%% config 4
% set_q_directly = [0.0003,0.2,0.59,0.06189,0.0618942]; % 22.22m/s 41000kg
% set_q_directly = [0.0002,0.25,0.61,0.0397778,0.0397778]; % 25.0m/s 41000kg
% set_q_directly = [0.0002,0.25,0.60,0.0397778,0.0397778]; % 26.39m/s 41000kg
% set_q_directly = [0.00019,0.24,0.58,0.0397778,0.0397778]; % 27.78m/s 41000kg
%% config 5
% set_q_directly = [0.0002,0.11,0.40,0.0618942,0.0618942]; % 22.22m/s 41000kg
% set_q_directly = [0.0002,0.12,0.39,0.0397778,0.0397778]; % 25.0m/s 41000kg
% set_q_directly = [0.0002,0.12,0.39,0.0397778,0.0397778]; % 26.39m/s 41000kg
% set_q_directly = [0.0002,0.12,0.39,0.0397778,0.0397778]; % 27.78m/s 41000kg
%% config 6 from jiaxuan
% set_q_directly = [0.0002,0.10,0.40,0.0618942,0.0618942]; % 22.22m/s 41000kg
% set_q_directly = [0.0002,0.10,0.39,0.0397778,0.0397778]; % 25.0m/s 41000kg
% set_q_directly = [0.0002,0.10,0.39,0.0397778,0.0397778]; % 26.39m/s 41000kg
% set_q_directly = [0.0002,0.10,0.39,0.0397778,0.0397778]; % 27.78m/s 41000kg
%% config 7 from jiaxuan
% set_q_directly = [0.0002,0.11,0.40,0.0618942,0.0618942]; % 22.22m/s 41000kg
% set_q_directly = [0.0002,0.11,0.39,0.0397778,0.0397778]; % 25.0m/s 41000kg
% set_q_directly = [0.0002,0.11,0.39,0.0397778,0.0397778]; % 26.39m/s 41000kg
% set_q_directly = [0.0002,0.11,0.39,0.0397778,0.0397778]; % 27.78m/s 41000kg
%% just for test config
% set_q_directly = [0.0001,0.12,0.80,0.0397778,0.0397778]; % 27.78m/s 41000kg
%% 80kph tuned by zhenwei
% set_q_directly =[0.00062, 0.52, 1.05, 0.06189, 0.06189];  % 22.22m/s 41000kg tuned by zhenwei
% try to tune a new 80kph Q matrix(WIP)
% set_q_directly = [0.00037,0.58,1.2,0.0618942,0.0618942]; % 22.22m/s 41000kg
%%%%%%%%%%%%%%%%%%%%%%%%heavy load%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%set_q =[0.0034,1.17,6.39,0.28,0.28,0];%20 heavy load verified
%set_q =[0.001,0.18,1.1,0.28,30,0];%40 heavy load need to be tune
%set_q =[0.001,0.16,1.08,0.28,0.28,0];%60 heavy load need to be tune
%set_q =[0.001,0.25,0.95,0.28,0.28,0];%60 heavy load need donglei update for big curvature
%set_q =[0.001,0.3,1.3,0.28,0.28,0];%70 heavy load need to be tune
% set_q =[0.001,0.4,1.3,0.28,0.28,0];%80 heavy load verified
%set_q =[0.001,0.4,1.7,0.28,0.28,0];%90 heavy load verified
%set_q =[0.001,0.42,1.75,0.28,0.28,0];%95 heavy load verified
%%%%%%%%%%%%%%%%%%%%%%%%%%%%bobtail%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%set_q =[0.001,0.18,2.5,0.2,0.2,0];%20 bobtail verified
%set_q =[0.001,0.08,0.5,0.2,0.2,0];%40 bobtail verified
set_q =[0.001,0.08,0.5,0.2,0.2,0];%60 bobtail verified
%set_q =[0.001,0.08,0.5,0.2,0.2,0];%70 bobtail verified
%set_q =[0.001,0.08,0.5,0.2,0.2,0];%80 bobtail verified
%set_q =[0.001,0.08,0.5,0.2,0.2,0];%90 bobtail verified
%%%%%%%%%%%%%%%%%%%%%%%%%empty load%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%set_q =[0.0008,0.12,2.0,0.2,0.2,0];%20 empty load verified
%set_q =[0.001,0.08,0.7,0.2,0.2,0];%40 empty load need to be tune
%set_q =[0.001,0.08,0.5,0.2,0.2,0];%60 empty load not verified
%set_q =[0.001,0.08,0.5,0.2,0.2,0];%70 empty load not verified
%set_q =[0.001,0.08,0.6,0.2,0.2,0];%80 empty load need to be tune
%set_q =[0.001,0.08,0.5,0.2,0.2,0];%90 empty load not verified
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%this is the test of params%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%set_q =[0.001,0.12,1.3,0.28,0.28,0];%[0.006,0.06,0.01,0.06,0.2,0] the param of master
%set_q =[0.001,0.12,1.3,0.28,0.28,0];% pole -0.3
%set_q =[0.001,0.4,0.8,0.28,0.28,0];
%set_q =[0.001,0.08,0.5,0.2,0.2,0];
%set_q =[0.001,0.08,0.8,0.2,0.2,0];
%set_q =[0.001,0.26,1.08,0.28,0.28,0];
%set_q =[0.0003,0.0231,0.1444,0.0467,0.0467,0];%just a test with peng
%set_q =[0.001,0.08,0.65,0.2,0.2,0];%try to tune the trucksim b5 model
%params1
%set_q =[0.001,1.0,2.3,0.2,0.2,0];%try to tune the trucksim b5 model params
%set_q =[0.006,0.06,0.01,0.06,0.2,0];%orignal params
%set_q =[0.001,0.08,0.5,0.2,0.2,0];%test for jiaxuan
%set_q =[1,0,0,0,0,0];%70 heavy load need to be tune
%set_q =[0.1,40,130,28,28,0];%80 heavy load verified
%set_q =[0.001,0.4,1.3,0.28,0.28,0];%80 heavy load verified
%set_q =[0.001,0.7,2.5,0.28,0.28,0];%80 heavy load verified
%set_q =[0.001,0.4,1.3,0.28,0.28];
lat_err_gain_scheduler_speed=[5.0,10.0,15.0,20.0,25.0,40.0];
lat_err_gain_scheduler_ratio=[1.5,1.0,0.7,0.4,0.15,0.15];
head_err_gain_scheduler_speed=[5.0,10.0,15.0,20.0,25.0,40.0];
head_err_gain_scheduler_ratio=[1.5,1.0,0.7,0.3,0.15,0.15];
mass_gain_scheduler_mass=[0,8000,15000,20000,40000];
mass_gain_scheduler_gain=[1.0,1.0,1.0,1.0,1.0];


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%vary params according to the trailer weight%%%%%%%%%%%%%%%%%%%
if combined_weight>11500
    trailer_weight=combined_weight-mass_tractor;
    w1=trailer_weight*p*(1-deta);
    w2=trailer_weight*p*deta;
    m_front=mass_tractor*lr_init/(lr_init+lf_init)+w1;
    m_rear=mass_tractor*lf_init/(lr_init+lf_init)+w2;
    mass = m_front + m_rear;
    lf=m_rear/mass*(lr_init+lf_init);
    lr=m_front/mass*(lr_init+lf_init);
    Cf=Cf_init*m_front/(mass_tractor*lr_init/(lr_init+lf_init))*gamma;
    Cr=Cr_init*m_rear/(mass_tractor*lf_init/(lr_init+lf_init))*gamma;
    Iz=Iz_init*mass/mass_tractor;
else
    mass=mass_tractor;
    trailer_weight=0.0;
    lf=lf_init;
    lr=lr_init;
    Cf=Cf_init;
    Cr=Cr_init;
    Iz=Iz_init;
end
lat_err_gain_scheduler_speed_i=interp1(lat_err_gain_scheduler_speed,lat_err_gain_scheduler_ratio,vecility,'linear');
head_err_gain_scheduler_speed_i=interp1(head_err_gain_scheduler_speed,head_err_gain_scheduler_ratio,vecility,'linear');
mass_gain_scheduler_mass_i=interp1(mass_gain_scheduler_mass,mass_gain_scheduler_gain,mass,'linear');
if enable_delay_model && enable_intergal
    q_interpolate=[set_q(1,1)*lat_err_gain_scheduler_speed_i*mass_gain_scheduler_mass_i
               set_q(1,2)*lat_err_gain_scheduler_speed_i*mass_gain_scheduler_mass_i
               set_q(1,3)*lat_err_gain_scheduler_speed_i*mass_gain_scheduler_mass_i
               set_q(1,4)*head_err_gain_scheduler_speed_i*mass_gain_scheduler_mass_i
               set_q(1,5)*head_err_gain_scheduler_speed_i*mass_gain_scheduler_mass_i
               0]';
          % disp("now is enable delay model")
elseif ~enable_delay_model && enable_intergal
    q_interpolate=[set_q(1,1)*lat_err_gain_scheduler_speed_i*mass_gain_scheduler_mass_i
               set_q(1,2)*lat_err_gain_scheduler_speed_i*mass_gain_scheduler_mass_i
               set_q(1,3)*lat_err_gain_scheduler_speed_i*mass_gain_scheduler_mass_i
               set_q(1,4)*head_err_gain_scheduler_speed_i*mass_gain_scheduler_mass_i
               set_q(1,5)*head_err_gain_scheduler_speed_i*mass_gain_scheduler_mass_i]';
          % disp("now is disable delay model")
else
    q_interpolate=[set_q(1,1)*lat_err_gain_scheduler_speed_i*mass_gain_scheduler_mass_i
               set_q(1,2)*lat_err_gain_scheduler_speed_i*mass_gain_scheduler_mass_i
               set_q(1,3)*lat_err_gain_scheduler_speed_i*mass_gain_scheduler_mass_i
               set_q(1,4)*head_err_gain_scheduler_speed_i*mass_gain_scheduler_mass_i]';
    %disp("now is without intergal and delay model now we are not use this")
end
if(use_q_interpolate_directly)
    q_interpolate = set_q_directly;
end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if enable_delay_model&&enable_intergal
    %delay model & intergal
    A=[[0 1 0 0 0 0];
       [0 0 1 0 0 0];
       [0 0 -2*(Cf+Cr)/(mass*vecility) 2*(Cf+Cr)/mass  2*(lr*Cr-lf*Cf)/(mass*vecility) 2*Cf/mass];
       [0 0 0 0 1 0];
       [0 0 2*(lr*Cr-lf*Cf)/(Iz*vecility) 2*(lf*Cf-lr*Cr)/Iz -2*(lf*lf*Cf + lr*lr*Cr)/(Iz*vecility) 2*lf*Cf/Iz]
       [0 0 0 0 0 -1/steer_system_time_constant]];
    B=[0;0;0;0;0;1/steer_system_time_constant/steer_ratio];
    C=[0,1,0,0,0,0];
    D=0;
    disp("now is enable delay model")
    if size(q_interpolate,2)~=6
        disp("the size of q is need set 6 col")
        return
    end
    Q=diag(q_interpolate);
    R=1;
elseif ~enable_delay_model&&enable_intergal
%with intergal
    A=[[0 1 0 0 0];
       [0 0 1 0 0];
       [0 0 -2*(Cf+Cr)/(mass*vecility) 2*(Cf+Cr)/mass  2*(lr*Cr-lf*Cf)/(mass*vecility)];
       [0 0 0 0 1 ];
       [0 0 2*(lr*Cr-lf*Cf)/(Iz*vecility) 2*(lf*Cf-lr*Cr)/Iz -2*(lf*lf*Cf + lr*lr*Cr)/(Iz*vecility)]];
    B=[0;0;2*Cf/mass/steer_ratio;0;2*lf*Cf/Iz/steer_ratio];
    C=[0,1,0,0,0];
    D=0;
    disp("now is disable delay model")
    if size(q_interpolate,2)~=5
        disp("the size of q is need set 5")
        return
    end
    Q=diag(q_interpolate);
    R=1;
else
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%without intergal
    A=[[0 1 0 0];
       [0 -2*(Cf+Cr)/(mass*vecility) 2*(Cf+Cr)/mass  2*(lr*Cr-lf*Cf)/(mass*vecility)];
       [0 0 0 1 ];
       [0 2*(lr*Cr-lf*Cf)/(Iz*vecility) 2*(lf*Cf-lr*Cr)/Iz -2*(lf*lf*Cf + lr*lr*Cr)/(Iz*vecility)]];
    B=[0;2*Cf/mass/steer_ratio; 0;2*lf*Cf/Iz/steer_ratio];
    C=[1,0,0,0];
    D=0;
    disp("now is without intergal")
    if size(set_q,2)~=4
        disp("the size of q is need set 4")
        return
    end
    Q=diag(set_q);
    R=1;
end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
[num,den]=ss2tf(A,B,C,D);
G=tf(num,den);

% figure(1)
% rlocus(G)
% title("Before state feedback")
% grid on

[K,S,e]=lqr(A,B,Q,R);
A_new=A-B*K;
[num,den]=ss2tf(A_new,B,C,D);
G1=tf(num,den);
if enable_plot_poles
    figure(1)
    rlocus(G1)
    title("After state feedback")
    grid on
end
if enable_plot_step
    figure(2)
    step(G1)
    grid on
    hold on
end
if enable_plot_bode
    figure(3)
    bode(G)
    grid on
    hold on
end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if combined_weight < 19000
    fprintf('bobtail : %d \n',combined_weight)
elseif combined_weight >= 19000 && combined_weight < 30000
    fprintf('empty load : %d \n',combined_weight)
else
    fprintf('heavy load : %d \n',combined_weight)
end
fprintf('current speed = %f kph \n',vecility * 3.6)
fprintf('current speed = %f m/s \n',vecility)
% for i = 1:1:size(set_q,2)
%     fprintf('q%d = %f \n',i-1,set_q(1,i))
% end
% fprintf('\n')
fprintf("set_q: \n")
for i = 1:1:size(q_interpolate,2)
    fprintf('q_interp%d = %f \n',i-1,q_interpolate(1,i))
end
fprintf('\n')
fprintf("feedback gain: \n")
%feedback gain
for i = 1:1:size(q_interpolate,2)
    fprintf('K%d = %f \n',i-1,K(1,i))
end
fprintf('\n')

[z,p,k]=tf2zp(num,den);
%e %eigenvalues
fprintf("eigenvalues: ")
fprintf('\n')
for i = 1:1:size(p,1)
    
    fprintf('p%d = ',i-1)
    disp(p(i,1))
end

fprintf('=============Gorgeous dividing line=========================\n')
%margin(G1)%绘制闭环bode图，观察幅值裕度，相角裕度
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% rlocus(G1)
% zeta=0.7;%根据超调公式计算zeta
% wn=1.8;%根据上升时间公式计算wn
% sgrid(zeta,wn)%选取符合条件的极点范围
% controlSystemDesigner(G1) %the tools of matlab to get the gain of close loop
%%%%%%%%%%%%%状态空间方程转传递函数%%%%%%%%%%%%%%%%%
% [num,den]=ss2tf(A,B,C,D);
% G=tf(num,den);
% bode(G)%频率响应图（bode图）
% margin(G)%幅值裕度，相角裕度
% rlocus(G)%绘制根轨迹
% G_zpk=zpk(G);%将传递函数转换成零极点形式
% [z,p,k]=tf2zp(num,den)%求解传递函数零极点及增益
% [num den]=zp2tf(z,p,k)%由零极点及增益求得传递函数
% printsys(num,den,'s')%打印传递函数
% step(A,B,C,D)
% zplane(z,p)%或者zplane(num,den)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Cs=G1*tf([1],[1 0]) %阶跃响应函数
% [num,den]=tfdata(G1,'v');%获得传递函数的分子分母
% [r,p,k]=residue(num,den)%将传递函数转换为展开式
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%[V,D]=eig(A_new)%V是特征向量，D是特征值，V的每一列向量对应一个特征值，其中V已经归一化
%norm(V(:,1))%求解向量二范数
%%%%%%%%%%%%%%%%%%%%拉氏变换%%%%%%%%%%%%%%%%%%
%需要时用syms定义符号变量
% syms s t
% [num,den]=tfdata(G1,'v');
% G2=poly2sym(num,s)/poly2sym(den,s);
% ilaplace(G2,s,t)%反拉氏变换
% laplace(G2)%拉氏变换
%%%%%%%%%%%%%%%系统能控能观性判断%%%%%%%%%%%%%%%%%%%%%%%
% Tc=ctrb(A,B);
% n=size(A);
% if rank(Tc)==n(1)
%     disp("The system is controlled")
% else
%     disp("The system is not controlled")
% end
% Tg=obsv(A,C);
% n=size(A);
% if rank(Tg)==n(1)
%     disp("The system is observed")
% else
%     disp("The system is not observed")
% end

%%%%%%%%%%极点配置%%%%%%%%%%%%%%
% P=[-5-3i,-5+3i,-7,-10];%配置极点
% K=place(A,B,P);
% A_new=A-B*k;
% [num,den]=ss2tf(A_new,B,C,D);
% G1=tf(num,den);
% figure(1)
% step(G1)

%%%%%%%%another method to calc the transfer function%%%%%%%%%%%%%%
% syms s
% tmp=[1,1,1,1];
% I=diag(tmp);
% G=C*inv(s*I-A)*B;

%%%%%%%%%%求解Riccati方程%%%%%%%%%
%[P,L,G] = care(A,B,Q,R)

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% wn=2*(Cf+Cr)/vecility*sqrt(Cf*Cr)/sqrt(mass*Iz)
% ksi=(mass*(lf*lf*Cf+lr*lr*Cr)+Iz*(Cf+Cr))/(2*(Cf+Cr)*sqrt(mass*Iz*Cf*Cr))