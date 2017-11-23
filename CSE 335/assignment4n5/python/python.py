import random

def NONRAND():
    return [75, -18, 216, 21, -6, 352, 39, -68, -318, 182]

def RANDOM():
    random.seed(867530942069L)
    return [random.randint(-999, 999) for x in xrange(10)]

def printarr(array, type):
    print("Here are the numbers for " + type)
    print(array)
    print("Smallest number: " + str(min(array)))
    print("Largest number: " + str(max(array)))
    print("Average: " + str(sum(array)/len(array)))

def main():
    print("Calling NONRAND...")
    nonrands = NONRAND()
    printarr(nonrands, "NONRAND")

    print("Calling RANDOM...")
    rands = RANDOM()
    printarr(rands, "RANDOM")

main();
