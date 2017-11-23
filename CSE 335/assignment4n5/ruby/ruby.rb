def NONRAND()
    return [75, -18, 216, 21, -6, 352, 39, -68, -318, 182]
end

def RANDOM()
    Random.srand(867530942069)
    toret = []
    10.times { toret << Random.rand(-999...999) }
    return toret
end

def printarr(array, type)
	print "Here are the numbers for " + type + "\n"
	print array.to_s + "\n"
	print "Smallest number: " + array.min.to_s + "\n"
	print "Largest number: " + array.max.to_s + "\n"
	print "Average: " + (array.inject(0, :+) / array.length).to_s + "\n"
end

def main()
	print "Calling NONRAND...\n"
	nonrands = NONRAND()
	printarr(nonrands, "NONRAND")
	print "\n"
	print "Calling RANDOM...\n"
	rands = RANDOM()
	printarr(rands, "RANDOM")
end

main()