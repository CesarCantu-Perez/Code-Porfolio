// Name: Cesar Cantu-Perez
// ID: 1001463763
// Due: Thurs. 3/10/2022



// 1. Starting with an array named inputtable that holds integers 1-10
var inputtable = [1,2,3,4,5,6,7,8,9,10];
//    Printing the result for verification
console.log(inputtable);

// 2a. Creating fiveTable using inputtable by multplying the inputtable values by 5 to get the multiples of 5
var fiveTable = inputtable.map(v => v * 5);
//    Printing the result for verification
console.log(fiveTable);

// 2b. Creating thirteen table using inputtable by multiplying the inputtable values by 13 to get multiples of 13
var thirteenTable = inputtable.map(v => v * 13);
//    Printing the result for verification
console.log(thirteenTable);

// 2c. For squaresTable I multiplied the values of inputtable by themselves to get the squares of the numbers in inputtable
var squaresTable = inputtable.map(v => v * v);
//    Printing the result for verification
console.log(squaresTable);

// 3. To get the odd multiples of 5 in oddmultTable, I multiplied the values in inputtable by 10 and the subtracted 5
//    NOTE: I also used inputtable in this line since there are only 10 odd multiples of 5 between 1 and 100 which matches the number of values in inputtable
var oddmultTable = inputtable.map(v => (v * 10) - 5);
//    Printing the result for verification
console.log(oddmultTable);

// 4. To get the sum of the even multiples of 7, first I created a function called isEven to check using the modulo operator, if a number is even or not
var isEven = x => x % 2 == 0;
//    After creating isEven, I counted 14 multiples of 7 between 1 and 100 so I could not use inputtable for this part. Instead I created another inputtable
//    called inputtable2 and made it have 14 values
var inputtable2 = [1,2,3,4,5,6,7,8,9,10,11,12,13,14];
//    Using the values in inputtable2 and the map function, I created sevenTable which held all of the multiples of 7 between 1 and 100
var sevenTable = inputtable2.map(v => v * 7);
//    Now that I had the sevenTable with all of the multiples of 7 I needed to get only the even multiples. To achieve this, I used the filter function
//    with the isEven function I had created earlier as the parameter. This would create a new table I called evenmult7Table with only the even multiples of 7
var evenmult7Table = sevenTable.filter(isEven);
//    I also needed to create and add function to be able to add the values in the new evenmult7Table. So I did using x and y as parameters for the function
var add = (x,y) => x + y;
//    With the add function created I was ready to add the even multiples of 7 together. Using the reduce function and the add function as a parameter of reduce,
//    I was able to add all the values in evenmult7Table to get the sum of the even multiples of 7 which I stored in the variable sumevenMult.
var sumevenMult = evenmult7Table.reduce(add, 0);
//    Printing the result for verification
console.log(sumevenMult);

// 5a. To curry the cylinder_volume function, I used the big arrow to point to r first then h so that only one of the parameters is checked at a time
//     Currying this function also removes the need for the "volume" variable present in the original function
var cylinder_volume = r => h => 3.14 * r * r * h;
//     Here all I did was call the cylinder_volume function and set r and h equal to 5 and 10 repectively
console.log(cylinder_volume(5)(10));

// 5b. I reused the function from 5a but with h = 17 instead of h = 10
console.log(cylinder_volume(5)(17));

// 5c. I reused the function from 5a but with h = 11 instead of h = 10
console.log(cylinder_volume(5)(11));

//6. First I wrote the code given to me by the lab instructions
makeTag = function(beginTag, endTag){
	return function(textcontent){
		return beginTag + textcontent + endTag;
	}
}
//   After that I wrote a function called table that was the return value for makeTag. This function would allow me to wrap whatever I call text I use it with with <table> and </table>
var table = makeTag("<table>","\n</table>");
//   I also wrote another function for row using the makeTag function provided to me. This function will wrap text with <tr> and </tr>
var row = makeTag("\n <tr>\n", " </tr>");
//   Next, I wrote another function called th which wrapped text with <th> and </th>
var th = makeTag("  <th>", "</th>\n");
//   Finally I made the last one for the <td> and </td> wrapping
var td = makeTag("  <td>", "</td>\n");
//   After making the functions I needed, I started using the functions th and td to wrap the data I would be using
var data1 = th("Pokemon");
//   I wrapped Dex Number so it would look like this: <th>Dex Number</th>
var data2 = th("Dex Number");
//   I wrapped Type so it would look like this: <th>Type</th>
var data3 = th("Type");
//   I wrapped Bulbasaur(using the td function now) so it would look like this: <td>Bulbasaur</td>
var data4 = td("Bulbasaur");
//   I wrapped #1 so it would look like this: <td>#1</td>
var data5 = td("#1");
//   I wrapped Grass/Poison so it would look like this: <td>Grass/Poison</td>
var data6 = td("Grass/Poison");
//   I wrapped Squirtle so it would look like this: <td>Squirtle</td>
var data7 = td("Squirtle");
//   I wrapped #7 so it would look like this: <td>#7</td>
var data8 = td("#7");
//   I wrapped Water so it would look like this: <td>Water</td>
var data9 = td("Water");
//   Now that I had all the data wrapped individually it was time to put it together. I created a variable called fullTable to store the finished product. To wrap more than just one bit
//   of text you have to use + to have the text continue. so I called the table function and created 3 rows inside the table using the row function which took the previouly wrapped data 
//   as its text content. Once the data was wrapped by row() then it would also be wrapped by table giving us the finished product you see when you run the code.
var fullTable = table(row(data1 + data2 + data3) + row(data4 + data5 + data6) + row(data7 + data8 + data9));
//   Here I used console.log to print the whole finished table in the terminal.
console.log(fullTable);


