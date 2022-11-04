import random

def main(n):
    for i in range(n):
        print(str(random.randint(-5000,5000)) + " ", end='')

main (10000)