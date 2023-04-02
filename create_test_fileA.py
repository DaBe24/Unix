size = 1 + 2**22
with open("fileA", "w+") as file:
    for i in range(size):
        file.write('\x01') if i == 0 or i == 10000 or i == size - 1 else file.write('\x00')