/*
scatter(Average_Speed,RTTTime,'.')
scatter(Initial_Speed, Average_Speed,'.')
scatter(Initial_Speed, RTTTime,'.')
scatter(Initial_Speed, Stop_Percentage,'.')
scatter(RTTTime, Stop_Percentage,'.')
scatter(Average_Speed, Stop_Percentage,'.')
scatter(Average_Speed, Cusion_Time,'.')
scatter(Initial_Speed, Cusion_Time,'.')
scatter(RTTTime, Cusion_Time,'.')
[Normalized_Average_Speed,Average_Speed_Mean,Average_Speed_std]=zscore(Average_Speed);
[Normalized_Cusion_Time,Cusion_Time_Mean,Cusion_Time_std]=zscore(Cusion_Time);
[Normalized_RTTTime,RTTTimee_Mean,RTTTime_std]=zscore(RTTTime);
[Normalized_Initial_Speede,Initial_Speed_Mean,Initial_Speed_std]=zscore(Initial_Speed);
[Normalized_Initial_Speede,Initial_Speed_Mean,Initial_Speed_std]=zscore(Initial_Speed);
[Normalized_Initial_Speed,Initial_Speed_Mean,Initial_Speed_std]=zscore(Initial_Speed);
[Normalized_Stop_Percentage,Stop_Percentage_Mean,Stop_Percentage_std]=zscore(Stop_Percentage);
save origin
Normalized_Data=[Normalized_Initial_Speed,Normalized_RTTTime,Normalized_Average_Speed,Normalized_Average_Speed,Normalized_Cusion_Time, Normalized_Stop_Percentage];
sava origin
Undefined function or variable 'sava'.
 
save origin
uiopen('/Users/jiangwen/Desktop/Math_Modle/Origin_Data.xlsx',1)
min(Normalized_Data(:,1))

ans =

   -1.8255

Normalized_Data=[Normalized_Initial_Speed,Normalized_RTTTime,Normalized_Average_Speed,Normalized_Cusion_Time, Normalized_Stop_Percentage];
Normalized_Data(:,1)=Normalized_Data(:,1)+2;
min(Normalized_Data(:,2))

ans =

   -1.6636

Normalized_Data(:,2)=Normalized_Data(:,2)+2;
min(Normalized_Data(:,3))

ans =

   -6.3306

Normalized_Data(:,3)=Normalized_Data(:,3)+7;
min(Normalized_Data(:,4))

ans =

   -0.6954

Normalized_Data(:,4)=Normalized_Data(:,4)+7;
min(Normalized_Data(:,5))

ans =

   -0.0650

Normalized_Data=[Normalized_Initial_Speed,Normalized_RTTTime,Normalized_Average_Speed,Normalized_Cusion_Time, Normalized_Stop_Percentage];
save origin
save ND.txt Normalized_Data -ascii
save ND.txt Normalized_Data -ascii -double
save ND.txt Normalized_Data -ascii 
*/