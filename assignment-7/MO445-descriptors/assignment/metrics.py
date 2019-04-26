import matplotlib
import pandas as pd
import numpy as np
from matplotlib import pyplot as plt
from sklearn import metrics as mt_s

matplotlib.use('agg')

def read_and_preprocessing(path):
    data = pd.read_csv(path,header=None,delimiter=' ')
    df = pd.DataFrame(data)
    types = np.array(['apple','bat','beetle','bell','bird','Bone','bottle','brick','butterfly','camel','car','carriage','cattle','cellular_phone','chicken','children','chopper','classic','Comma','crown','cup','deer','device0','device1','device2','device3','device4','device5','device6','device7','device8','device9','dog','elephant','face','fish','flatfish','fly','fork','fountain','frog','Glas','guitar','hammer','hat','HCircle','Heart','horse','horseshoe','jar','key','lizzard','lmfish','Misk','octopus','pencil','personal_car','pocket','rat','ray','sea_snake','shoe','spoon','spring','stef','teddy','tree','truck','turtle','watch'])

    for t in types:
        reg = '^' + t + '.*'
        df = df.replace(regex={reg:t})

    df_ss = df[df[0] == 1]
    df_mfd = df[df[0] == 2]

    df_ss = df_ss.drop([0],axis=1)
    df_mfd = df_mfd.drop([0],axis=1)

    df_ss = df_ss.values
    df_mfd = df_mfd.values

    df_ss_vec = np.ndarray((1400,1400)).astype(int)
    df_mfd_vec = np.ndarray((1400,1400)).astype(int)

    for row in range(df_ss.shape[0]):
        df_ss_vec[row] = df_ss[row][1:] == df_ss[row][0]
        df_mfd_vec[row] = df_mfd[row][1:] == df_mfd[row][0]

    ss_sum = np.sum(df_ss_vec,axis=0)
    mfd_sum = np.sum(df_mfd_vec,axis=0)

    return ss_sum, mfd_sum

def precision_and_recall(y_bool):
    precision = np.ndarray(y_bool.shape).astype(float)
    recall = np.ndarray(y_bool.shape).astype(float)
    for col in range(y_bool.shape[0]):
        precision[col] = np.sum(y_bool[0:col+1]) / ((col+1) * 1400.0)
        recall[col] = np.sum(y_bool[0:col+1]) / np.sum(y_bool)
    return precision, recall

def plot_and_save(ss_precision, ss_recall, mfd_precision, mfd_recall,path_save):
    plt.plot(ss_recall,ss_precision, label='Segment Saliences')
    plt.plot(mfd_recall,mfd_precision, label='Multi Fractal Dimensional')
    plt.xlabel('recall')
    plt.ylabel('precision')
    plt.title('Precision vs Recall')
    plt.legend(loc='best')

    plt.savefig('./'+path_save)

def main():
    path = 'results.csv'
    path_save = 'precision_vs_recall.png'

    ss_sum, mfd_sum = read_and_preprocessing(path)

    ss_precision, ss_recall = precision_and_recall(ss_sum)
    mfd_precision, mfd_recall = precision_and_recall(mfd_sum)

    plot_and_save(ss_precision, ss_recall, mfd_precision, mfd_recall, path_save)

if __name__ == '__main__':
    main()