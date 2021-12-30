file = open('test.txt', 'r')
lines = file.readlines()

numbers = list()

for line in lines:
  l = line.split()
  
  if (l[0] not in numbers): numbers.append(l[0])
  if (l[1] not in numbers): numbers.append(l[1])

print(f"Count : {len(numbers)}")
