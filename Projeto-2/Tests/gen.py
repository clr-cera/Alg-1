from random import shuffle

f1 = open("test.in", "w")

print("Type desired length")

length = int(input())

numbers1 = [*range(length//2, length + length//2)]
numbers2 = [*range(length)]

shuffle(numbers1)
shuffle(numbers2)

f1.write(f"{length} {length}")

for number in numbers1:
    f1.write(f" {number}")

for number in numbers2:
    f1.write(f" {number}")

f1.write(f" 3")


f1.close()

