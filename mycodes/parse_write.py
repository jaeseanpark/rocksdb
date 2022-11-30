import sys

if len(sys.argv) <= 1:
    print('input at least one file')


def main():
    L0 = L1 = L2 = L3 = 0
    for logfile in sys.argv[1:]:
        with open(logfile, 'r') as f:
            for line in f:
                if "flush table" in line and line.endswith('OK\n'):
                    split = line.split()
                    L0 += int(split[10])
                    # print(line, end=' ')
                elif "Compacted" in line:
                    split = line.split()
                    numbytes = int(split[-2])
                    level = split[-4]
                    if level == "L1":
                        L1 += numbytes 
                    if level == "L2":
                        L2 += numbytes
                    if level == "L3":
                        L3 += numbytes
                    # print(line, end=' ') 
                elif "Moved" in line and "bytes" in line:
                    split = line.split()
                    numbytes = int(split[-13])
                    level = split[-14]
                    if level == 'level-1':
                        L1 += numbytes
                    elif level == 'level-2':
                        L2 += numbytes
                    elif level == 'level-3':
                        L3 += numbytes
                    # print(line, end=' ')
    print('writes per level(bytes):')
    print('L0: ' + str(L0) + '\n' + 
          'L1: ' + str(L1) + '\n' + 
          'L2: ' + str(L2) + '\n' + 
          'L3: ' + str(L3) + '\n')


if __name__ == '__main__':
    main()