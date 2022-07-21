import random 
import bisect 
import math 
from functools import reduce
import numpy as np
from tqdm import tqdm

class ZipfGenerator: 

    def __init__(self, n, alpha):
        self.n = n 
        # Calculate Zeta values from 1 to n: 
        tmp = np.power(np.arange(1, n+1) , -alpha)
        # print(tmp) 
        zeta = np.r_[0., np.cumsum(tmp)]
        # print(zeta)
        # Store the translation map: 
        self.distMap = [x / zeta[-1] for x in zeta] 
        # print(self.distMap)
        
    def next(self): 
        # Take a uniform 0-1 pseudo-random value: 
        u = random.random()  

        # Translate the Zipf variable: 
        return bisect.bisect(self.distMap, u) - 1
    def calc_probability(self):
        self.probability=[]
        for i in range(n):
          actual = self.distMap[i+1]-self.distMap[i]  
          self.probability.append(actual)
        return self.probability
    def calc_actual(self, k):
        self.total = k
        self.actual=[]
        for i in range(n):
          temp = round(k*(self.distMap[i+1]-self.distMap[i]))          
          self.actual.append(temp)
        return self.actual
    def firstk(self, k):
        i = sum = 0
        while(True):
          sum += self.actual[i]
          if sum > self.total * k/100:
            break
          i += 1
        return i
    def firstk_prob(self, k):
      #총 데이터의 k퍼센트가 상위 몇프로인지
        i = sum = 0
        while(True):
          sum += self.probability[i]
          if sum > k/100:
            break
          i += 1
        return (i+1)*100/self.n

print('loading keys')
keys = []  # keys
with open ('writelog.txt', 'r') as f:
  for line in f.readlines():
    keys.append(line)


# key chooser 
# randomly choose key 

  
alpha = 0.3
n = 8000000
updatelist = []
zipfian = ZipfGenerator(n, alpha)
act = zipfian.calc_actual(8000000)
print('making zipfian keys list')
for key, count in zip(keys, act):
  tmp = [key] * count
  updatelist.extend(tmp)
print('writing updatelist to a file')
with open('updatelist.txt', 'w') as f:
  for line in updatelist:
    f.write(line)




