%���ֺ����75�����ݽ�����ϣ�������ϵõ��Ķ���ʽϵ�������Fit.mat�ļ���
load('final.mat');%����ֺ��������

Average_Speed_Cusion_Time=zeros(25,3);
for i=1:5;
   for j=1:5;
    eval(['Average_Speed_Cusion_Time(j,:)=polyfit(','a',num2str(i),num2str(j),'(:,3),','a',num2str(i),num2str(j),'(:,4),2)',';'])
   end
end

Average_Speed_Stop_Percentage=zeros(25,3);
for i=1:5;
   for j=1:5;
    eval(['Average_Speed_Stop_Percentage(j,:)=polyfit(','a',num2str(i),num2str(j),'(:,3),','a',num2str(i),num2str(j),'(:,5),2)',';'])
   end
end

Initial_Speed_Cusion_Time=zeros(25,3);
for i=1:5;
   for j=1:5;
    eval(['Initial_Speed_Cusion_Time(j,:)=polyfit(','b',num2str(i),num2str(j),'(:,1),','b',num2str(i),num2str(j),'(:,4),2)',';'])
   end
end

Initial_Speed_Stop_Percentage=zeros(25,3);
for i=1:5;
   for j=1:5;
    eval(['Initial_Speed_Stop_Percentage(j,:)=polyfit(','b',num2str(i),num2str(j),'(:,1),','b',num2str(i),num2str(j),'(:,5),2)',';'])
   end
end

RTT_Stop_Percentage_Cusion_Time=zeros(25,3);
for i=1:5;
   for j=1:5;
       eval(['RTT_Stop_Percentage_Cusion_Time(j,:)=polyfit(','c',num2str(i),num2str(j),'(:,2),','c',num2str(i),num2str(j),'(:,4),2)',';'])
   end
end


RTT_Stop_Percentage_Stop_Percentage=zeros(25,3);
for i=1:5;
   for j=1:5;
       eval(['RTT_Stop_Percentage_Stop_Percentage(j,:)=polyfit(','c',num2str(i),num2str(j),'(:,2),','c',num2str(i),num2str(j),'(:,5),2)',';'])
   end
end

save Fit;