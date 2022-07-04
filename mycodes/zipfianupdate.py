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
        tmp = [1. / (math.pow(float(i), alpha)) for i in range(1, n+1)]
        # print(tmp) 
        zeta = reduce(lambda sums, x: sums + [sums[-1] + x], tmp, [0]) 
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


keys = []  # keys
with open ('writelog.txt', 'r') as f:
  for line in f.readlines():
    keys.append(line)

# key chooser 
# randomly choose key 

with open('updatelist.txt', 'w') as f:
  
alpha = 0.3
n = 1000000

zipfian = ZipfGenerator(n, alpha)
prob = zipfian.calc_probability()
act = zipfian.calc_actual(1000000)
print(type(act))
print(act[0])
print(act[-1])
print(str(zipfian.firstk_prob(20)) + '%')
print(str(zipfian.firstk(20)) + 'th')




