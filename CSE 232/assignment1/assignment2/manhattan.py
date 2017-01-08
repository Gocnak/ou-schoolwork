import random
import sys
import time


class Vector:
    """
    Used for calculating manhattan distances.
    """
    def __init__(self):
        self.x, self.y, self.z = random.randint(-10000, 10000), \
                                 random.randint(-10000, 10000), random.randint(-10000, 10000)

    def __mul__(self, num):
        ret = []
        for _ in xrange(num):
            ret.append(Vector())
        return ret

    def __str__(self):
        return '{} {} {}'.format(self.x, self.y, self.z)

    def manhattan(self, a):
        return abs(a.x - self.x) + abs(a.y - self.y) + abs(a.z - self.z)

    __repr__ = __str__


SIZE_V = 100000                 # The size of the random points of V
MAX_TRIES = 100                 # Number of tries to generate an average time of finding the point closest to A
trial_times = []                # List of performance times, used at the end to calculate average time
prgm_start = time.clock()       # Set the program's start time

for i in xrange(MAX_TRIES):
    V = Vector() * SIZE_V     # Generate the V list of random B vectors
    A = Vector()              # Generate the A vector to test distance for
    startTime = time.clock()  # Set the start time for this iteration
    smallest = sys.maxint     # Initialize the smallest distance to a very large number
    for B in V:
        smallest = min(smallest, B.manhattan(A))  # Find the smallest and set it to the variable, if it's smaller

    # Note: We don't actually care what the smallest distance or the closest B actually is here. If we did,
    # we would probably have a slightly different for-loop above, which could add some small amount of time to the
    # total runtime of this algorithm.

    trial_times.append(time.clock() - startTime)  # Append the time taken for this run through


print 'Average runtime for vector of size {}: {} seconds (total runtime {} seconds)'.format(SIZE_V,
                                                                                            sum(trial_times) / MAX_TRIES,
                                                                                            time.clock() - prgm_start)

"""
Notes from benchmarking:

* Any MAX_TRIES > 1000 (with a considerably large SIZE_V) will cause this benchmark to run for a long time.
* Any SIZE_V > 1000000 will cause this benchmark to run for a long time as well.
* Not caring for the smallest distance, or the B in the V list that gives you that distance causes the for loop to have
    considerably simple logic, which aids this program. Caring about any of the former two would change the for-loop
    and potentially slow it down.

So with those notes, I've kept the SIZE_V at 100000 and MAX_TRIES at 100, and found that the average time to find the
smallest distance was approximately 0.0797706737019 seconds on my machine. At SIZE_V of around 1000000, when the program
finally completed with an average of 0.792825547367 seconds.
"""