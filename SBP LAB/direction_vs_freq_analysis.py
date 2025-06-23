
##########
# part 1 #
##########
import numpy as np
import math
import librosa
import librosa.display
import matplotlib.pyplot as plt
from scipy.io import wavfile
from scipy.signal import butter, lfilter

# bandpass
def butter_bandpass(lowcut, highcut, fs, order=5):
    nyq = 0.5 * fs  # Nyquist 頻率
    low = lowcut / nyq
    high = highcut / nyq
    b, a = butter(order, [low, high], btype='band')
    return b, a

def bandpass_filter(data, lowcut, highcut, fs, order=5):
    b, a = butter_bandpass(lowcut, highcut, fs, order=order)
    y = lfilter(b, a, data)
    return y

# set the range
lowcut = 500.0   # Hz
highcut = 20000.0 # Hz

##########
# part 2 #
##########
def split_intervals(y, sr):
    max_interval = math.floor((len(y)/sr/8))
    intervals = []
    for i in range(0, max_interval):
        intervals.append([i*8*sr, (i*8+5)*sr])
    return intervals

info = {}
deg_list = []
for i in range(0,180,15):
    deg_list.append(f"deg{i:03d}")
# init for each material
material_list = {"box", "IrregularBox"}
for material in material_list:
    info[material] = {}


    for deg in deg_list:
        filename = f'./training_data/20250616/{material}_{deg}_WhiteNoise.wav'
        y, sr = librosa.load(filename, sr=None)
        y_filtered = bandpass_filter(y, lowcut, highcut, sr, order=6)

        intervals = find_split_intervals_by_sample(y_filtered, tick_size=2048, diff_threshold=10)
        intervals = split_intervals(y_filtered, sr)
        # init for each deg
        info[material][deg] = {
            "DB":np.zeros(1025),
            "size":0
        }
        
        # start on interval
        for i in range(0,len(intervals)):
            start, end = intervals[i]
            duration = (end - start) / sr
            #有時候判斷很怪 所以<5 or >6 就不是正常的音檔
            if  duration <4.5 or duration > 6 :
                continue
            # 去頭尾 避免加到edge的值影響avg
            second_segment = y_filtered[start + sr*1 : end - sr*1]
            # 頻譜
            D = librosa.stft(second_segment)
            DB = librosa.amplitude_to_db(np.abs(D), ref=np.max)
            for f in range(0,len(DB)):
                for t in range(0, len(DB[f])):
                    info[material][deg]["DB"][f] += DB[f][t]
                    info[material][deg]["size"]+=1
            for f in range(0,len(DB)):
                info[material][deg]["DB"][f] /= info[material][deg]["size"]

##########
# part 3 #
##########
for material in material_list:
    Z = np.zeros((len(deg_list), len(info[material]["deg165"]["DB"])))
    deg_values = [int(d[3:]) for d in deg_list]
    for i, deg in enumerate(deg_list):
        Z[i, :] = info[material][deg]['DB']
    plt.figure(figsize=(12, 6))
    Y, X = np.meshgrid(librosa.fft_frequencies(sr=sr, n_fft=2048)
                    , deg_values)
    plt.pcolormesh(X, Y, Z, shading='auto', cmap='viridis')
    plt.xticks(deg_values)
    plt.ylabel('Frequency (Hz)')
    plt.xlabel('Degree')
    plt.title(f'Frequency vs Degree ({material})')
    plt.colorbar(label='Mean dB')
    plt.show()
