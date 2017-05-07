function SaveMartixToTxt(N)
    pf=fopen('Data.txt','w');
    for i=1:1:size(N,1)
        for j=1:1:size(N,2)
            fprintf(pf,'%5.5f ',N(i,j));
        end
        fprintf(pf,'\n');
    end
    fclose(pf);
end