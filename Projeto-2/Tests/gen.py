from random import shuffle

f1 = open("data1.in", "w")
f2 = open("data2.in", "w")

numbers1 = [*range(5000, 15000)]
numbers2 = [*range(10000)]

shuffle(numbers1)
shuffle(numbers2)

for number in numbers1:
    f1.write(f" {number}")

for number in numbers2:
    f2.write(f" {number}")

f1.close()
f2.close()

