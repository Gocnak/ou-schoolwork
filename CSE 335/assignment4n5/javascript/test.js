

function NONRAND()
{
    return [75, -18, 216, 21, -6, 352, 39, -68, -318, 182];
}


function RANDOM()
{

    var seed = 867530942069;
    function random() {
        var x = Math.sin(seed++) * 10000;
        return x - Math.floor(x);
    }

    var nums = new Array;
    for (var element = 0; element < 10; element++)
    {
        nums[element] = Math.floor(random() * (1998)) -999;
    }

    return (nums);
}

function main() {
    
    function print(array) {
        array = array.sort((a, b) => a > b);
        console.log(array);
        console.log("Smallest number: " + array[0]);
        console.log("Largest number: " + array[array.length - 1]);
        console.log("Average: " + array.reduce((total, num) => total += num) / array.length);
    }

    var nonrands = NONRAND();
    print(nonrands);
    
    console.log("");
    var rands = RANDOM();
    print(rands);
    
}

main();

