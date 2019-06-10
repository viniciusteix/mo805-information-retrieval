import pandas as pd
res = pd.read_csv('results.csv',header=None,delimiter=' ')
df = pd.DataFrame(res)
results1 = df[df[0] == 1]
results2 = df[df[0] == 2]
r1 = results1.iloc[:,1:]
r2 = results2.iloc[:,1:]
r1.to_csv('params/SS_results.txt',sep=" ", header=None,index=False)
r2.to_csv('params/MFD_results.txt',sep=" ", header=None,index=False)