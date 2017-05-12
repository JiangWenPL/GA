本文件夹所有代码均采用UTF-8编码
C++编译运行环境：编译平台: Mac OS Sierra 10.12.4 
编译器：Apple LLVM version 8.1.0 (clang-802.0.42) 
语言标准 C++ 11 
编译选项： -O3 -std=C++11
注意：由于采用了c++11的语言标准，请务必使用 -std=c++11  编译选项进行编译。
Y1_Best.txt Y1_Fit.xlsx Y1_Worst_Fitness.txt已经Y2前缀文件分别为各自因变量对应方程的每代最优解，最优与最劣适应度信息。
GA.cpp为遗传算法实现的核心代码。其运行需要依赖读取同文件夹内的Data.txt文件
MinMAx.m MinMAx_Normalized.mat 为归一化数据使用
Fit.m为在MATLAB中实现对已组合好的数据进行拟合的代码
select.m为在MATLAB中对归一化数据进行模糊聚类生成相似矩阵的代码
Polynomial coefficient.mat为由Fit.m导出的6组拟合好的二次多项式系数矩阵