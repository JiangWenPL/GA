mnmx=zeros(size(Origin_Data,2),2);
Normalized_Data=zeros(size(Origin_Data,1),size(Origin_Data,2));
for i=1:1:5
    mnmx(i,:)=minmax(Origin_Data(:,i)');
    Normalized_Data(:,i)=(Origin_Data(:,i)-repmat(mnmx(i,1),size(Origin_Data,1),1))/(mnmx(i,2)-mnmx(i,1));
end
save MinMax_Normalized;