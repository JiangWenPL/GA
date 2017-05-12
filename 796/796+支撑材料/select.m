
for i=1:5
    for j=1:5
final=Normalized_Data(:,1)>=(0.2*i-0.2)&Normalized_Data(:,1)<0.2*i&Normalized_Data(:,2)>=(0.2*j-0.2)&Normalized_Data(:,2)<0.2*j
 eval(['a',num2str(i),num2str(j),'=','Normalized_Data(final,:)',';']);
    end
end

for i=1:5
    for j=1:5
final=Normalized_Data(:,1)>=(0.2*i-0.2)&Normalized_Data(:,1)<0.2*i&Normalized_Data(:,3)>=(0.2*j-0.2)&Normalized_Data(:,3)<0.2*j
 eval(['b',num2str(i),num2str(j),'=','Normalized_Data(final,:)',';']);
    end
end

for i=1:5
    for j=1:5
final=Normalized_Data(:,2)>=(0.2*i-0.2)&Normalized_Data(:,2)<0.2*i&Normalized_Data(:,3)>=(0.2*j-0.2)&Normalized_Data(:,3)<0.2*j
 eval(['c',num2str(i),num2str(j),'=','Normalized_Data(final,:)',';']);
    end
end




        


        