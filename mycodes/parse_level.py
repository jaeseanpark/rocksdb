L0 = L1 = L2 = L3 = L4 = 0
with open("getlog.txt", 'r')as f:
    for line in f:
        tmp = line.split()
        if int(tmp[4]) == 0:
            L0 += 1
        elif int(tmp[4]) == 1:
            L1 += 1
        elif int(tmp[4]) == 2:
            L2 += 1
        elif int(tmp[4]) == 3:
            L3 += 1
        elif int(tmp[4]) == 4:
            L4 += 1

print("L0: " + str(L0))
print("L1: " + str(L1))
print("L2: " + str(L2))
print("L3: " + str(L3))
print("L4: " + str(L4))